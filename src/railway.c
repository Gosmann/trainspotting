#include "../include/railway.h"

#include <stdio.h>
#include <stdlib.h>

#include "string.h"

// functions on [train_t]

// this function populates a raw train element with a type and an id
//     can be thought as a constructor of the type train_t 
int create_train(train_t * train, int type, char * train_id) {
    int status = 0;

    switch (type) {
    case TGV:
        strcpy(train->type_id, "TGV");
        break;
    case TER:
        strcpy(train->type_id, "TER");
        break;
    case RER:
        strcpy(train->type_id, "RER"); 
        break;
    default:
        strcpy(train->type_id, "???"); 
        status = -1;
    }

    train->location = 0;            // starts at default location
    train->eoa = 0;                 // with no authorization at all

    strcpy(train->id, train_id);    // updates train_id

    return status;
}

// prints the parameters of a train in the screen
void print_train_params(train_t * train) {   
    
    printf("🚆 | [%s%s] | [LOC, EOA]: [%3d, %3d ] \n",
        train->type_id, train->id, train->location, train->eoa );

}


// functions on [train_set_t]

// this functions creates a new train_set_t element from scratch
train_set_t * start_train_set( int type_id, char * train_id ) {
    
    // initializes first element with memory from the head
    //     maybe use calloc
    train_set_t * first_train = (train_set_t *)calloc(sizeof(train_set_t), 1) ; 
    
    create_train( &(first_train->train), type_id, train_id ) ;
    
    first_train->next = NULL ;
    first_train->prev = NULL ;

    return first_train ;
}

train_set_t * create_empty_train_set( train_set_t * last_train ) {

    train_set_t * train = (train_set_t *)calloc(sizeof(train_set_t), 1) ; 
    train->next = NULL;
    train->prev = NULL;

    if( last_train != NULL ){
        last_train->next = train;
        train->prev = last_train;
    }
        
    return train ;
}

// adds an element to the set of trains
train_set_t * add_train(train_set_t * set, int type_id, char * train_id) {

    if( set->next != NULL ){
        add_train(set->next, type_id, train_id );
    }
    else{
        // it is in the last element
        set->next = start_train_set( type_id, train_id ) ;
        set->next->prev = set;
    }

    return set->next;   // returns the element just added
}

// removes the first element of the set (FIFO)
train_set_t * remove_train(train_set_t ** set){

    train_set_t * old = set[0] ; 
    
    if( set[0]->prev != NULL )
        set[0]->prev->next = set[0]->next ;
    
    if( set[0]->next != NULL )
        set[0]->next->prev = set[0]->prev;
    
    set[0] = (set[0]->next);
    
    free( old ) ;

    return set[0];  // returns the new first element
}

// Functions type_train
void print_all_trains( train_set_t * set )
{   
    int num = 0;
    printf("🚏 \t printing all trains : \n");

    while( set->prev != NULL ){
        set = set->prev ;   // goes to first element
    }

    while( set->next != NULL ){
        
        printf("[] \t [%d] | ", num );
        print_train_params( &(set->train) );

        set = set->next ;
        num++;
    }

    printf("\n");
}

// example and testing of the library
void testing( ){
    
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

}
  