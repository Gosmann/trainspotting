#include "string.h"
#include <stdio.h>
#include <stdlib.h>


#define NUM_STD_TYPES 3 // Number of train types


enum train_type
{
    TGV, //Equals 0
    TER, //Equals 1
    RER, //Equals 2

};



typedef struct train_type_t
{
    char id [5];
    double velocity;
}train_type_t;


typedef struct train_t
{
    train_type_t type;
    char id [5];
    int location;         //Cantons [1-100]
    int end_of_authority;
    int sd;
}train_t;

typedef struct train_set
{
    train_t train;     //
    struct train_set * next; // Next Element
}train_set_t;


//Functions type_train
void print_train_params(train_t* train);
void print_all_trains(train_set_t * set, int num);

//Functions set_trains
train_set_t *start_list_trains(int type, char * train_id);
int add_train(train_set_t * set, int type, char * train_id);
train_set_t * remove_train(train_set_t ** set);

//Functions train_t
int create_train(train_t * train, int type, char * train_id);





