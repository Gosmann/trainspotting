// TODO make good header

// desc. this file simulates a train control station (Radio Block Center)

#include <stdio.h>
#include "../include/railway.h"

int main( int argc, char ** argv ){

    train_set_t * railway = start_train_set( TGV, "123" ) ;

    print_all_trains( railway );

    add_train( railway, TER, "666" );
    add_train( railway, RER, "122" );
    add_train( railway, TGV, "985" );

    print_all_trains( railway );

    remove_train( &railway );

    print_all_trains( railway );

    remove_train( &railway );

    print_all_trains( railway );

    return 0;
}