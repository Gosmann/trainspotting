#include <stdio.h>
#include  "train.h"



int main(void)
{
    train_set_t *my_set = start_list_trains(98887,"222");
    //print_train_params(&my_set->train);

    add_train( my_set, RER, "234" );
    add_train( my_set, TER, "666" );

    add_train( my_set, 11, "234" );
    add_train( my_set, TGV, "126" );

    print_all_trains( my_set, 0 ); 

    remove_train( &my_set );

    print_all_trains( my_set, 0 ); 

}