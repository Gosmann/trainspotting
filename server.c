// TODO create a nice header

#include <stdio.h>
#include <stdlib.h>

// from man socket
#include <sys/types.h>
#include <sys/socket.h>

// from man htons
#include <arpa/inet.h>

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
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
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
    int listen_r = listen( socket_fd, 0 );     // backlog int defines max queue
    
    if( listen_r == 0 ){
        printf("successfully listen! [%d] \n", listen_r);
    }
    else{
        printf("error listening! \n");
    }

    // accept
    socklen_t addr_size_peer = sizeof( struct sockaddr_in );
    int accept_fd = accept( socket_fd, (struct sockaddr *)&my_addr, &addr_size_peer ) ;
    
    if( 1 ){
        printf("successfully accepted! [%d] \n", accept_fd);
    }
    else{
        printf("error accepting! \n");
    }
    
    while(1){


    }


    return 0;
}