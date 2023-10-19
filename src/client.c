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