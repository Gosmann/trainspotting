// TODO make good header

// desc. this file simulates a train control station (Radio Block Center)

#include <stdio.h>
#include "../include/railway.h"

int main( int argc, char ** argv ){

    printf("Hello World ! \n");

    train_set_t * railway = start_train_set( TGV, "123" ) ;

    print_all_trains( railway, 0 );

    return 0;
}