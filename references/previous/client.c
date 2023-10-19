// TODO create a nice header

#include <stdio.h>
#include <stdlib.h>

// from man socket
#include <sys/types.h>
#include <sys/socket.h>

// from man htons
#include <arpa/inet.h>

#include <unistd.h>     // from man close

#include <string.h>

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
    
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET ;
    server_addr.sin_port = htons(1994);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    int connect_r = connect( socket_fd, (struct sockaddr *)&server_addr, 
        sizeof(struct sockaddr) ) ;
    
    if( connect_r != -1 ){
        printf("successfully connected the socket! [%d] [%s] [%d] \n", 
            socket_fd, inet_ntoa( server_addr.sin_addr ), htons(server_addr.sin_port) );

    }
    else {
        printf("error connecting the socket! \n");
    }

    char buffer[256] = {0};

    while(1){

        fgets( buffer, sizeof(buffer), stdin );
        //sprintf( buffer, "Hello World! \n" );
        printf("[%s]", buffer);

        // send only if there is something to send
        if( strlen( buffer ) > 0 ){

            int send_to_r = sendto( socket_fd, buffer, strlen(buffer) -1 , 0, NULL, 0);

            if(send_to_r == -1){
                printf("error! \n");
            }

        }
        
    }

    close(socket_fd);

    return 0;
}