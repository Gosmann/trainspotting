// TODO create a nice header

#include <stdio.h>
#include <stdlib.h>

// from man socket
#include <sys/types.h>
#include <sys/socket.h>

// from man htons
#include <arpa/inet.h>

#include <unistd.h>     // from man close


int main(){

    //signal(SIGINT, handle_sigint);    // TODO this later

    printf("Hello World! from client \n");

    // socket file descriptor
    // int socket(int domain, int type, int protocol);
    int socket_fd = socket( AF_INET, SOCK_STREAM, 0 ) ;

    if( socket_fd != -1 ){
        printf("successfully created the socket! [%d] \n", socket_fd);
    }
    else {
        printf("error creating the socket! \n ");
    }

    // connect (defining the address)
    
    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET ;
    my_addr.sin_port = htons(1994);
    my_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    int connect_r = connect( socket_fd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr) ) ;
    
    if( connect_r != -1 ){
        printf("successfully connected the socket! [%d] \n", connect_r);
    }
    else {
        printf("error connecting the socket! \n");
    }

    while(1){

    }

    close(socket_fd);

    return 0;
}