// TODO make good header
// TODO add date and time to main screen like a linux boot

// desc. this file simulates a train control station (Radio Block Center)

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../include/railway.h"
#include "../include/server.h"

int main( int argc, char ** argv ){
    
    train_set_t * railway = create_empty_train_set( NULL ) ;

    int running = 1;
    
    // implement command line parsing to obtain :
    // TODO is there any other thing to obtain from command line interface?
    int port = 1994;

    if(argc == 2){
        port = atoi( argv[1] );
    }
    

    // start server integration
    int socket_fd = init_tcp_server( port );

    assert( socket_fd > 0 );    // has successfully created the socket
    
    //train_set_t * current_train = railway;

    // starts infinite loop for accepting connections
    while( running ){
        
        // waits until a client connects
        int accept_fd = wait_for_connection( socket_fd );   

        assert( accept_fd > 0 ) ;   // client has logged in successfully

        //railway->train.socket_fd = accept_fd;
        railway->train.socket_fd = accept_fd;
        
        // make a thread to deal with this train
        int connect_r = connect_to_train( railway );

        assert( connect_r == 0);    // successfull thread connection
        
        railway = create_empty_train_set( railway );
        
    }

    printf("This is the end! \n");



    return 0;
}