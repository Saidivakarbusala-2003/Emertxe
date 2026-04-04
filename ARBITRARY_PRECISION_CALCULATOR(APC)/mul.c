#include "apc.h"

void multiplication(node *tail1, node *tail2, node **headR, node **tailR)
{
    node *temp2 = tail2; // Initialize temp2 to tail of the second list
    node *headR1 = NULL, *tailR1 = NULL; // Initialize headR1 and tailR1 to NULL for storing the intermediate result of multiplication
    int count = 0; // Initialize count to 0 for keeping track of the number of zeros to be added
    
    while(temp2 != NULL) // Traverse the second list until temp2 becomes NULL
    {
        node *temp1 = tail1; // Initialize temp1 to tail of the first list
        int carry = 0;
        for(int i = 0;i < count;i++) // Add zeros at the end of the intermediate result based on the position of the digit in the second list
        {
            insert_first(&headR1, &tailR1, 0);
        }
        while(temp1 != NULL) // Traverse the first list until temp1 becomes NULL
        {
            int prod = (temp1 -> data * temp2 -> data) + carry; //calculate the product 
            if(insert_first(&headR1, &tailR1, (prod % 10)) != 0) // Insert the last digit of the product
            {
                printf("INFO: Featching failure in result list\n");
                return;
            }  
            carry = prod / 10; // Update the carry for the next iteration by dividing the product by 10
            temp1 = temp1 -> prev; // Move temp1 to the previous node in the first list
        }
        if(carry != 0) // If there is a carry left after the multiplication
        { 
            insert_first(&headR1, &tailR1, carry);// Insert the carry at the beginning of the intermediate result list
        }
        if(headR != NULL) // If headR is not NULL, then we need to add the intermediate result to the final result
        {
            node *headAR = NULL, *tailAR = NULL; // Initialize headAR and tailAR to NULL 

            addition(*tailR, tailR1, &headAR, &tailAR); // Add the intermediate result to the final result 
            delete_list(headR,tailR); // Delete the previous result list
            delete_list(&headR1,&tailR1); // Delete the intermediate result list after adding it to the final result

            *headR = headAR; // Update headR to the new head of the final result list after addition
            *tailR = tailAR; // Update tailR to the new tail of the final result list after addition
        }
        temp2 = temp2 -> prev ; // Move temp2 to the previous node in the second list
        count++; // Increment the count for the next digit in the second list
    }
}

