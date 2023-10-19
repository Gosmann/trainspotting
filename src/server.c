// TODO create a nice header

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <arpa/inet.h>      // from man htons
#include <unistd.h>         // from man close

#include <pthread.h>        // from man pthreads

#include <errno.h>

#include <assert.h>

#include "../include/server.h"

void * treat_client( train_set_t * train ){

    struct sockaddr_in peer_addr;        // this will hold info about the client
    socklen_t addr_size = sizeof(struct sockaddr_in);
    int res = getpeername( train->train.socket_fd , (struct sockaddr *)&peer_addr, &addr_size);
    
    assert( res == 0 );

    printf("🛜 \t new connection from [ip:%s] and [port:%d] at [PID:%d] \n",
        inet_ntoa( peer_addr.sin_addr ), htons(peer_addr.sin_port), gettid() );
    
    // obtain data of the arriving train:
    train_t train_data ;
    int recv_r = recv( train->train.socket_fd , &train_data, sizeof(train_t), 0 ) ;
    
    // update data
    strcpy( train->train.type_id, train_data.type_id );
    strcpy( train->train.id, train_data.id );

    // print current train params
    //print_train_params( &(train->train) );

    while(1){
        //print_train_params( &(train->train) );
        print_all_trains( train );

        char buffer[256] = {0};
        message_t message;
        int number = recv( train->train.socket_fd , &message, sizeof(message), 0 ) ;
        
        if(number == -1 | number == 0 )
        //if(number == -1 )
            break;
        
        if( message.message[0] == 'u' ){    // update position
            train->train.location = message.train.location;

            train->train.eoa = 66 ;
            message_t message_new = { {"EOA"}, train->train };
            int send_r = sendto(  train->train.socket_fd, &message_new, 
                sizeof(message_new), 0, NULL, 0);
            
            assert(send_r != -1);
        }

        
        
        //printf("[%s] [%d]\n", buffer, number);
    }

    remove_train( &train );

    printf("❌ \t end of connection from [ip:%s] and [port:%6d] at [PID:%d]\n\n",
        inet_ntoa( peer_addr.sin_addr ), htons(peer_addr.sin_port), gettid() );

    print_all_trains( train );

    close( train->train.socket_fd );
}

// inits the server to specified port
int init_tcp_server( int port ){

    // socket file descriptor
    // int socket(int domain, int type, int protocol);
    int socket_fd = socket( AF_INET, SOCK_STREAM, 0 ) ;

    if( socket_fd != -1 ){
        //printf("successfully created the socket! [%d] \n", socket_fd);
    }
    else {
        printf("error creating the socket! \n");
        return socket_fd;
    }

    // bind (defining the addresses)
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET ;
    my_addr.sin_port = htons(port);         // normally htons(1994)

    //my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    my_addr.sin_addr.s_addr = INADDR_ANY;   // listens from any address
    
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    int bind_r = bind( socket_fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) ;

    if(bind_r != -1){
        //printf("successfully binding! [%d] \n", bind_r);
    }
    else{
        printf("error binding! \n");
        return bind_r;
    }
    
    // listen
    //int listen(int sockfd, int backlog);
    int listen_r = listen( socket_fd, 10 );     // backlog int defines max queue
    
    if( listen_r == 0 ){
        //printf("successfully listen! [%d] \n", listen_r);
    }
    else{
        printf("error listening! \n");
        return listen_r;
    }

    // now it will always be listening
    printf("🔌 \t socket created successfully \n");

    return socket_fd;
}

int connect_to_server(char * ip, int port){
    
    // socket file descriptor
    // int socket(int domain, int type, int protocol);
    int socket_fd = socket( AF_INET, SOCK_STREAM, 0 ) ;

    assert( socket_fd > 0 );
    printf("🔌 \t socket created successfully \n");

    // connect (defining the address)
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET ;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    
    int connect_r = connect( socket_fd, (struct sockaddr *)&server_addr, 
        sizeof(struct sockaddr) ) ;
    
    assert( connect_r == 0 );

    printf("🛜 \t new connection made at [ip:%s] and [port:%d] at [PID:%d] \n",
        inet_ntoa( server_addr.sin_addr ), htons(server_addr.sin_port), gettid() );
    
    return socket_fd;
}

int wait_for_connection( int socket_fd ){

    struct sockaddr_in peer_addr;
    socklen_t addr_size_peer = sizeof( struct sockaddr_in );
    
    int accept_fd = accept( socket_fd, (struct sockaddr *)&peer_addr, &addr_size_peer ) ;
    

    //printf("successfully accepted! [%d] [%s] [%d]\n", 
    //    accept_fd, inet_ntoa( peer_addr.sin_addr ), htons(peer_addr.sin_port) );

    return accept_fd;
}

int connect_to_train( train_set_t * train ){
    
    // connect accept_fd to train_thread
    
    //int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
    int create_r =  pthread_create( &(train->train.thread), NULL, 
        (void *)(* treat_client ), (void *)( train ) );
    
    assert(create_r == 0);

    return create_r;
}

int old_main(){

    printf("Hello World! from server \n");

    int socket_fd = init_tcp_server(1994);
    
    int running = 1;
    int threads_count = 0;
    pthread_t my_threads[100] ;

    while( running ){
        
        // starts accepting connections
        // should create 1 thread for echo connection

        struct sockaddr_in peer_addr;
        socklen_t addr_size_peer = sizeof( struct sockaddr_in );
        int accept_fd = accept( socket_fd, (struct sockaddr *)&peer_addr, &addr_size_peer ) ;
        
        if( accept_fd >= 0 ){
            printf("successfully accepted! [%d] [%s] [%d]\n", 
                accept_fd, inet_ntoa( peer_addr.sin_addr ), htons(peer_addr.sin_port) );

            // treat accept_fd to new thread
            //int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
            int create_r =  pthread_create( &my_threads[ threads_count ], NULL, 
                (void *)(* treat_client ), (void *)( &accept_fd ) );

            //pthread_create( &thr[i], NULL, (void *)(* num_of_primes), (void *)( &(prime_data[i]) ) );

        // pthread_join( thr[i], (void **)&status[i]);
        

            if(create_r == 0){
                printf("success creating thread \n");
            }
            else{
                printf("error creating thread \n");
            }
            
            threads_count++;
        }
        else{
            printf("error accepting! \n");
        }


        
        
        

        //int number = recv( accept_fd, buffer, 255, 0 ) ;

        

    }

    printf("This is the end! \n");

    return 0;
}