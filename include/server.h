#ifndef SERVER_H
#define SERVER_H

// from man socket
#include <sys/types.h>
#include <sys/socket.h>

#include "../include/railway.h"

int init_tcp_server( int port ) ;

int wait_for_connection( int socket_fd ) ;

int connect_to_train( train_set_t * train ) ;

int connect_to_server(char * ip, int port) ;

#endif

