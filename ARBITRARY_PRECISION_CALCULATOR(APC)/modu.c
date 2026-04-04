#include "apc.h"

void modulus(node *head1, node *head_OPR2, node *tail_OPR2,node **headR, node **tailR)
{
    if (head_OPR2 == NULL || (head_OPR2->data == 0 && head_OPR2->next == NULL)) // Check if the second operand is zero or not
    {
        printf("Runtime error : Divide by zero\n"); // print the error message for divide by zero
        exit(0); // Exit the program if the second operand is zero
    }

    node *head_OPR1 = NULL, *tail_OPR1 = NULL; // Initialize head_OPR1 and tail_OPR1 to NULL
    node *temp = head1;// Initialize temp to head of the first operand list

    while (temp != NULL) // Traverse the first operand list until temp becomes NULL
    {
        insert_last(&head_OPR1, &tail_OPR1, temp->data); // Insert the current digit of the first operand
        remove_pre_zeros(&head_OPR1); // Remove the leading zeros after inserting the new digit
        //while (compare_list(head_OPR1, head_OPR2) == 1 || compare_list(head_OPR1, head_OPR2) == 2)
        while(compare_list(head_OPR1 , head_OPR2) != OPERAND2) // compare the head_OPR1 >= head_OPR2
        {
            node *head_SR = NULL, *tail_SR = NULL; // Initialize head_SR and tail_SR to NULL

            subtraction(tail_OPR1, tail_OPR2, &head_SR, &tail_SR); // Subtract the second operand from the intermediate result
            delete_list(&head_OPR1, &tail_OPR1); // Delete the previous intermediate result list after subtraction

            head_OPR1 = head_SR; // Update head_OPR1 to the new head after subtraction
            tail_OPR1 = tail_SR; // Update tail_OPR1 to the new tail after subtraction
            remove_pre_zeros(&head_OPR1); //Remove the leading zeros after subtraction
        }
        temp = temp->next;// Move temp to the next node in the first operand list
    }
    if(head_OPR1 == NULL) // If head_OPR1 is NULL, then the result of modulus is zero
        insert_last(headR, tailR, 0); //insert 0 in the result list
    else
    {
        *headR = head_OPR1; // Update headR to the new head of the result list after modulus operation
        *tailR = tail_OPR1; // Update tailR to the new tail of the result list after modulus operation
    }
}    