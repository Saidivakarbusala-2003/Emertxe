#include "apc.h"

void addition(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *temp1 = tail1 ,*temp2 = tail2; // Initialize temp1 to tail1 and temp2 to tail2
    int sum = 0,carry = 0; // Initialize sum and carry to 0
    while(temp1 != NULL || temp2 != NULL) // Traverse the lists until both temp1 and temp2 become NULL
    {
        int val1 = 0, val2 = 0; // Initialize val1 and val2 to 0
        if(temp1 != NULL)  // If temp1 is not NULL 
        {
            val1 = temp1->data; //then set val1 to the data of temp1
            temp1 = temp1->prev; // Move temp1 to the previous node
        }
        if(temp2 != NULL) // If temp2 is not NULL
        {
            val2 = temp2->data; //then set val2 to the data of temp2
            temp2 = temp2->prev; // Move temp2 to the previous node
        }
        sum = val1 + val2 + carry; // Calculate the sum of val1, val2 and carry
        carry = sum / 10; // Update the carry for the next iteration by dividing the sum by 10

        if(insert_first(headR, tailR, (sum % 10)) != 0) // Insert the last digit of the sum at the beginning of the result list
        {
            printf("Featching failure in result list\n");
        }
    }
    if(carry) // If there is a carry left after the addition
    {
        if(insert_first(headR, tailR, carry) != 0) // Insert the carry at the beginning of the result list
        {
            printf("Featching failure in result list\n");
        }
    }
}
