#include "apc.h"

void subtraction(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *temp1 = tail1 ,*temp2 = tail2; // Initialize temp1 to tail of the first list and temp2 to tail of the second list
    int borrow = 0;  // Initialize borrow to 0
    while(temp1 != NULL || temp2 != NULL) // Traverse the lists until both temp1 and temp2 become NULL
    {
        int val1 = 0, val2 = 0; // Initialize val1 and val2 to 0
        if(temp1 != NULL)  // If temp1 is not NULL
        {
            val1 = temp1->data; //set val1 to the data of temp1
            temp1 = temp1->prev; //move temp1 to the previous node
        }
        if(temp2 != NULL) // If temp2 is not NULL
        {
            val2 = temp2->data; //set val2 to the data of temp2
            temp2 = temp2->prev; //move temp2 to the previous node
        }

        val1 = val1 - borrow; // Subtract the borrow from val1

        if(val1 < val2) // If val1 is less than val2
        {
            val1 = val1 + 10; // we need to borrow from the next higher place value
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        
        int digit = val1 - val2; // Calculate the digit to be stored in the result list by subtracting val2 from val1

        if(insert_first(headR, tailR, digit) != 0) // Insert the digit at the beginning of the result list
        {
            printf("INFO: Featching failure into result list\n");
        }
    }
    remove_pre_zeros(headR); //starting zeros are remove in result file
}