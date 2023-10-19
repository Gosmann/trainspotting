#include "train.h"


//Functions type_train
void print_train_params(train_t* train)
{   
    
    printf("TRAIN: [%s%s] --- LOCATION: %3d --- EOA: %3d  VELOCIDADE: %5.2f\n",
        train->type.id, train->id, train->location, train->end_of_authority,
            train->type.velocity);

}

//Functions type_train
void print_all_trains(train_set_t * set, int num)
{   
    printf("num : [%d] \n", num );
    print_train_params( &(set->train) );

    if( set->next != NULL )
        print_all_trains( set->next, num+1 );

}


//Functions train_t
int create_train(train_t * train, int type, char * train_id)
{
    int status = 0;

    switch (type)
    {
    case TGV:
        strcpy(train->type.id,"TGV");
        train->type.velocity = 1.0;
        break;

    case TER:
        strcpy(train->type.id,"TER");
        train->type.velocity = 0.5 ;
        break;

    case RER:
        strcpy(train->type.id,"RER"); 
        train->type.velocity = 0.25 ;
        break;

    default:
        //printf("ERROR")
        strcpy(train->type.id,"???"); 
        train->type.velocity = 0.6666666666666;
        status = -1;
    }

    train->location = 0;
    train->end_of_authority = 0;

    strcpy(train->id, train_id); 


    return status;
}

//Functions set_trains
train_set_t *start_list_trains( int type, char * train_id )
{
    train_set_t * first_train = (train_set_t *)malloc(sizeof(train_set_t));

    create_train(&(first_train->train), type, train_id );

    first_train->next = NULL ;

    return first_train;
}

int add_train(train_set_t * set, int type, char * train_id)
{

    if( set->next != NULL ){
        add_train(set->next, type, train_id );
    }
    else{
        // it is in the last element
        set->next = start_list_trains( type, train_id ) ;
    }

    return 0;
}

train_set_t * remove_train(train_set_t ** set){

    train_set_t * old = set[0] ; 
    
    set[0] = (set[0]->next);

    free( old ) ;

    return set[0];
}

