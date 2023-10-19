// TODO add mmultiple includes protection safeguards

#define NUM_STD_TYPES 3 // Number of train types

// standard train types
typedef enum std_types {
    TGV, TER, RER
} std_types_t ;

// struct that defines a type for "trains"
typedef struct train_t {
    char type_id [5];             // string that holds type_id, ex. "TGV"
    char id [5];                  // string that holds train id number, ex. "123"
                                   
    int location;                 // current canton location [ 0 ~ 100 ]
    int eoa;                      // end_of_authority , max location the train is allowed to go
    int socket_fd;                // socket_fd
} train_t ;

// struct that defines the train sequence as a linked list
typedef struct train_set {
    train_t train;                // stores a train element in memory
    struct train_set * next;      // pointer to the next element
} train_set_t;

// functions on [train_t]

// this function populates a raw train element with a type and an id
//     can be thought as a constructor of the type train_t 
int create_train(train_t * train, int type, char * train_id);   
 
// prints the parameters of a train in the screen
void print_train_params(train_t* train);

// functions on [train_set_t]

// this functions creates a new train_set_t element from scratch
train_set_t * start_train_set(int type_id, char * train_id);

// adds an element to the set of trains
train_set_t * add_train(train_set_t * set, int type_id, char * train_id);

// removes the first element of the set (FIFO)
train_set_t * remove_train(train_set_t ** set);

// prints the parameters of all trains in the railway
void print_all_trains( train_set_t * set );









