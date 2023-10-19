// TODO make good header

// desc. this file simulates the train control board of the conductor

#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "../include/railway.h"
#include "../include/server.h"

typedef enum {
    select_type,
    select_id,
    base,
} state_t ;

void print_menu( state_t state, train_t * train ){
    char buffer[10] = {0};
    
    printf("\n🚂🚂🚂🚂🚂🚂🚂🚂🚂🚂🚂🚂 ");
    printf("\nMACHINIST CONTROL PANEL \n\n");
            
    switch(state){
        case select_type:
            printf("select your train type : \n");
            printf("[1] -> TGV \n");
            printf("[2] -> TER \n");
            printf("[3] -> RER \n");
            printf("\n: $ ");

            while( 1 ){
                fflush(stdin);
                char * fgets_r = fgets(buffer, sizeof(buffer), stdin);

                if( strcmp(buffer, "1\n" ) == 0){
                    strcpy(train->type_id, "TGV");
                    break;
                } 
                else if( strcmp(buffer, "2\n" ) == 0 ){
                    strcpy(train->type_id, "TER" );
                    break;
                }
                else if( strcmp(buffer, "3\n" ) == 0){
                    strcpy(train->type_id, "RER");
                    break;
                }
                else{
                    printf("try again! \n");
                }
            }
            

        case select_id:
            printf("\ntype your train id [3 chars] : \n");
            printf("$ : ");
            char buffer[10] = {0};
            while(1){
                char * fgets_r = fgets(buffer, sizeof(buffer), stdin);
                if( fgets_r != NULL ){
                    strcpy(buffer, train->id);
                    break;
                }
                else
                    printf("try again! \n");
            }
        
        case base : 
            printf("\nprint base case : \n");
            print_train_params( train );



    }

    

}

int main( int argc, char ** argv ){
    
    train_t train ;

    create_train( &train, TGV, "123" );

    int running = 1;
    
    // implement command line parsing to obtain :
    // TODO is there any other thing to obtain from command line interface?
    int port = 1994;
    char * ip = "127.0.0.1";
    
    // MENU
    print_menu( select_type, &train );

    
    // start server integration
    //int socket_fd = init_tcp_server( port );
    int socket_fd = connect_to_server( ip, port );

    assert( socket_fd > 0 );    // has successfully created the socket
    
    


    char buffer[256] = {0};
    // starts infinite loop for accepting connections
    while( running ){
        
        fgets( buffer, sizeof(buffer), stdin );
        
        printf("[%s]", buffer);

        // send only if there is something to send
        if( strlen( buffer ) > 0 ){

            int send_r = sendto( socket_fd, buffer, strlen(buffer) -1 , 0, NULL, 0);

            assert(send_r != -1);

        }
        
    }

    printf("This is the end! \n");



    return 0;
}