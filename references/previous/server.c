// TODO create a nice header

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

// from man socket
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>      // from man htons
#include <unistd.h>         // from man close

#include <pthread.h>        // from man pthreads

#include <errno.h>

#include <assert.h>




void * treat_client( int * socket_fd ){

    struct sockaddr_in peer_addr;        // this will hold info about the client
    socklen_t addr_size = sizeof(struct sockaddr_in);
    int res = getpeername( socket_fd[0] , (struct sockaddr *)&peer_addr, &addr_size);
    
    assert( res == 0 );

    printf("Hello World from another thread [%d] \n", gettid() );

    printf("successfully accepted! [%d] [%s] [%d]\n", 
        socket_fd[0], inet_ntoa( peer_addr.sin_addr ), htons(peer_addr.sin_port) );

    //printf("successfully accepted! [%d] \n", accept_fd );


    while(1){
        char buffer[256] = {0};
        int number = recv( socket_fd[0] , buffer, sizeof(buffer)+1, 0 ) ;
        
        if(number == -1 | number == 0 )
        //if(number == -1 )
            break;

        printf("[%s] [%d]\n", buffer, number);
    }

    printf("End of the thread [%d] \n", gettid() );

    close(socket_fd[0]);

}

int main(){

    printf("Hello World! from server \n");

    // socket file descriptor
    // int socket(int domain, int type, int protocol);
    int socket_fd = socket( AF_INET, SOCK_STREAM, 0 ) ;

    if( socket_fd != -1 ){
        printf("successfully created the socket! [%d] \n", socket_fd);
    }
    else {
        printf("error creating the socket! \n");
    }

    // bind (defining the addresses)
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET ;
    my_addr.sin_port = htons(1994);
    //my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    my_addr.sin_addr.s_addr = INADDR_ANY;
    
    // int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    int bind_r = bind( socket_fd, (struct sockaddr *)&my_addr, sizeof(my_addr)) ;

    if(bind_r != -1){
        printf("successfully binding! [%d] \n", bind_r);
    }
    else{
        printf("error binding! \n");
    }
    
    // listen
    //int listen(int sockfd, int backlog);
    int listen_r = listen( socket_fd, 10 );     // backlog int defines max queue
    
    if( listen_r == 0 ){
        printf("successfully listen! [%d] \n", listen_r);
    }
    else{
        printf("error listening! \n");
    }

    // now it will always be listening
    
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