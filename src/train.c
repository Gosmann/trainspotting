// TODO make good header

// desc. this file simulates the train control board of the conductor

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/railway.h"
#include "../include/server.h"

typedef enum {
    select_type,
    select_id,
    base_case,
} state_t ;

void print_menu( train_t * train, state_t state);

int main( int argc, char ** argv ){
    
    train_t train ;

    create_train( &train, TGV, "123" );

    int running = 1;
    state_t state = 0;
    
    // implement command line parsing to obtain :
    // TODO is there any other thing to obtain from command line interface?
    int port = 1994;
    if(argc == 2){
        port = atoi( argv[1] );
    }

    char * ip = "127.0.0.1";
    
    // start server integration
    //int socket_fd = init_tcp_server( port );
    int socket_fd = connect_to_server( ip, port );
    assert( socket_fd > 0 );    // has successfully created the socket
    

    if(argc > 2){
        /*
        if(argc == 3){  // has only type
            strcpy( train.type_id, argv[1] );
            state = select_id ;
        }
        */
        //else if(argc == 3){
        
        strcpy( train.type_id, argv[2] );
        strcpy( train.id, argv[3] );
        state = base_case ;
    

    }

    // MENU
    print_menu( &train, state);
    //print_menu( base_case, &train );

    
    // send train data
    int send_r = sendto( socket_fd, &train, sizeof(train_t)  , 0, NULL, 0);
    assert(send_r != -1);

    char buffer[256] = {0};
    // starts infinite loop for accepting connections
    while( running == 1 ){
        
        printf("$ : ");
        fgets( buffer, sizeof(buffer), stdin );

        int step = 1;
        step = atoi( &buffer[2] ) ;
        
        if(step == 0)
            step = 1;

        if( buffer[0] == 'm' ){
            
            if( (train.location + step) < train.eoa ){
                train.location += step;

                printf("[] \t [%d] | ", 0 );
                print_train_params( &train );
                printf("\n");
            }
            else{
                printf("❌ \t not allowed by \"end of autority\" (EOA) \n\n");
            }

            if( train.location >= 100 ){

                running = 0;
                // send command to end
                message_t message = { {"e"}, train } ;
                int send_r = sendto( socket_fd, &message, sizeof(message), 0, NULL, 0);
                assert(send_r != -1);

                //printf("[] \t [%d] | ", 0 );
                //print_train_params( &train );
                //printf("\n");
            }

            //int send_r = sendto( socket_fd, buffer, strlen(buffer) -1 , 0, NULL, 0);
            //assert(send_r != -1);

        }
        else if(buffer[0] == 'u' ){     // update location
            
            message_t message = { {"u"}, train } ;
            int send_r = sendto( socket_fd, &message, sizeof(message), 0, NULL, 0);
            assert(send_r != -1);

            int number = recv( socket_fd , &message, sizeof(message), 0 ) ;
            //printf("[%s]", message2.message);

            train.eoa = message.train.eoa ;

            printf("[] \t [%d] | ", 0 );
            print_train_params( &train );
            printf("\n");

        }
        else{
            printf("unknown command, try again...\n");            
        }

        //printf("[%s]", buffer);

        
    }

    printf("This is the end! \n");



    return 0;
}



void print_menu( train_t * train, state_t state){

    char buffer[256] = {0};
    
    printf("\n🚂🚂🚂🚂🚂🚂🚂🚂🚂🚂🚂🚂 ");
    printf("\nMACHINIST CONTROL PANEL \n\n");
            
    switch(state){
        case select_type:
            printf("write your train type [ex. \"TGV\"] : \n");
            printf("$ : ");

            while( 1 ){
                fflush(stdin);
                char * fgets_r = fgets(buffer, sizeof(buffer), stdin);

                if( strlen(buffer) != 3 + 1 ){      // TODO solve the magin numbers
                    printf("it must be exactly 3 chars \n");
                    printf("$ : ");
                }
                else{
                    buffer[3] = '\0';
                    strcpy(train->type_id, buffer);
                    break;
                }
                
            }
            

        case select_id:
            printf("write your train id [ex. \"123\"] : \n");
            printf("$ : ");

            while( 1 ){
                fflush(stdin);
                char * fgets_r = fgets(buffer, sizeof(buffer), stdin);

                if( strlen(buffer) != 3 + 1 ){
                    printf("it must be exactly 3 chars \n");
                    printf("$ : ");
                }
                else{
                    buffer[3] = '\0';
                    strcpy(train->id, buffer);
                    break;
                }
                
            }
            
        case base_case : 
            printf("print base case : \n");
            print_train_params( train );

            printf("\n");

            printf("possible commands: \n");
            printf("$ : m \t // move 1 unit forward \n");
            printf("$ : u \t // requests new EOA \n\n");
            
    }

    

}