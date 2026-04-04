#include "apc.h"

void division(node *head1, node *head_OPR2, node *tail_OPR2,node **headR, node **tailR)
{
    if (head_OPR2 == NULL || (head_OPR2->data == 0 && head_OPR2->next == NULL)) // Check if the second operand is zero or not
    {
        printf("Runtime error : Divide by zero\n");
        exit(0);// Exit the program if the second operand is zero
    }

    node *head_OPR1 = NULL, *tail_OPR1 = NULL; // Initialize head_OPR1 and tail_OPR1 to NULL for storing the intermediate result of division
    node *temp = head1; // Initialize temp to head of the first operand list

    while (temp != NULL) // Traverse the first operand list until temp becomes NULL
    {
        insert_last(&head_OPR1, &tail_OPR1, temp->data); // Insert the current digit of the first operand
        remove_pre_zeros(&head_OPR1); // Remove the leading zeros
        int scount = 0; // Initialize scount to 0 for counting the number of times we can subtract
        while(compare_list(head_OPR1 , head_OPR2) != OPERAND2) // compare the head_OPR1 >= head_OPR2
        {
            node *head_SR = NULL, *tail_SR = NULL; // Initialize head_SR and tail_SR to NULL

            subtraction(tail_OPR1, tail_OPR2, &head_SR, &tail_SR); // Subtract the second operand
            delete_list(&head_OPR1, &tail_OPR1); // Delete the previous intermediate result list

            head_OPR1 = head_SR; // Update head_OPR1 to the new head of the intermediate result list after subtraction
            tail_OPR1 = tail_SR; // Update tail_OPR1 to the new tail of the intermediate result list after subtraction
            scount++; // Increment scount for each successful subtraction
        }
        insert_last(headR, tailR, scount); // Insert the count of how many times we can subtract
        temp = temp->next; // Move temp to the next node in the first operand list
    }
    remove_pre_zeros(headR); // Remove the leading zeros from the final result list after the division is complete
}