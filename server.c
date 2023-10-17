// TODO create a nice header

#include <stdio.h>
#include <stdlib.h>

// from man socket
#include <sys/types.h>
#include <sys/socket.h>

#include <arpa/inet.h>      // from man htons
#include <unistd.h>     // from man close

#include <pthread.h>        // from man pthreads


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

    while( running ){
        // starts accepting connections
        struct sockaddr_in peer_addr;
        socklen_t addr_size_peer = sizeof( struct sockaddr_in );
        int accept_fd = accept( socket_fd, (struct sockaddr *)&peer_addr, &addr_size_peer ) ;
        
        if( accept_fd >= 0 ){
            printf("successfully accepted! [%d] [%s] [%d]\n", 
                accept_fd, inet_ntoa( peer_addr.sin_addr ), htons(peer_addr.sin_port) );
        
        }
        else{
            printf("error accepting! \n");
        }

        // running = 0;



    }

    close(socket_fd);

    return 0;
}