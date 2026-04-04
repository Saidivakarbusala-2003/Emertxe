#include "apc.h"

// Function definitions
int cla_validation(int argc, char *argv[])
{
    if(argc != 4) //check the num of arguments
    {
        printf("INFO: Invalid number of arguments.\n"); //print the error message
        return -1; // Return failure if the number of arguments is not 4 (including the program name)
    }
    if(strlen(argv[2]) != 1 || strchr("+-xX/%", argv[2][0]) == NULL) //check the operator id valide or not and single operator or not
    {
        printf("ERROR: Invalid Operator (Enter only +, -, x, X, /, %%)!\n\n"); //print error message for invalid operators
        exit(0); // Exit the program if the operator is invalid
    }
    for(int i = 1; i < argc; i += 2)   // operand1 and operand2
    {
        int j = 0; //Initialize j is 0

        if((argv[i][0] == '+' && isdigit(argv[i][1])) || (argv[i][0] == '-' && isdigit(argv[i][1]))) //check the operand 0th position sign or not and 1st position is digit or not
        {
            j = 1;   // skip sign
        }
        for(j; argv[i][j] != '\0'; j++) //run the loop
        {
            if(!isdigit(argv[i][j])) // //if any character is not a digit
            {
                printf("ERROR: Invalid OPERAND%d, Enter only numerics !\n\n", (i == 1) ? 1 : 2); //if operand1 or operand2 cantains non-digit characters print error
                exit(0); // Exit the program if the operand is invalid
            }
        }
    }
    return 0; // Return success if all validations are passed
}

void create_list(char *opr, node **head, node **tail)
{
    if(*opr == '+' || *opr == '-') // Skip sign if present
    {
        opr++; // Move the pointer to the next character if the first character is a sign
    }
    while (*opr != '\0' && isdigit(*opr)) // Traverse the string until reach the NULL character and check if the each character is a digit or not
    {
        int x = *opr - '0'; //convert the character into integer
        if(insert_last(head, tail, x) != 0) // insert the digit at end of the list
        {
            printf("INFO: Insert node at last is failure.\n");
        }
        opr++; // move to next character in the string
    }
}

int insert_first(node **head, node **tail, int data)
{
    node *new_node = malloc(sizeof(node)); // Allocate memory for a new node
    if(new_node == NULL) // Check if memory allocation was successful
    {
        printf("INFO: Memory is not allocated at insert first.\n");
        return -1; // Return failure if memory allocation failed
    }
    new_node -> data = data; // Set the data of the new node
    new_node -> prev = NULL;  // Set the previous pointer of the new node to NULL
    new_node -> next = NULL;  // Set the next pointer of the new node to NULL
    node *temp = *head;
    if(*head == NULL) // Check if the list is empty or not
    {
        *head = *tail = new_node; // If the list is empty, set both head and tail to the new node
        return 0; // Return success
    }
    else
    {
        temp -> prev = new_node; // Set the previous pointer of the current head to the new node
        new_node -> next = temp; // Set the next pointer of the new node to the current head
        *head = new_node;  // Update the head to the new node
        return 0; // Return success
    }
}

int insert_last(node **head, node **tail, int data)
{
    node *new_node = malloc(sizeof(node)); // Allocate memory for a new node
    if(!new_node) // Check if memory allocation was successful
    {
        printf("INFO: Memory is not allocated in insert last.\n");
        return -1;
    }
    new_node -> data = data;   // Set the data of the new node
    new_node -> prev = NULL;   // Set the previous pointer of the new node to NULL
    new_node -> next = NULL;   // Set the next pointer of the new node to NULL
    if(*head == NULL) // Check if the list is empty or not
    {
        *head = *tail = new_node; // If the list is empty, set both head and tail to the new node
        return 0; // Return success
    }
    else
    {
        (*tail) -> next = new_node; // Set the next pointer of the current tail to the new node
        new_node -> prev = *tail;   // Set the previous pointer of the new node to the current tail
        (*tail) = new_node;         // Update the tail to the new node
        return 0;    // Return success
    }
}

int delete_list(node **head, node **tail)
{
    if(*head == NULL) // Check if the list is empty
    {
        return -1; // Return failure if the list is empty
    }
    node *temp;
    while(*head != NULL) // Traverse the list until head becomes NULL
    {
        temp = *head; // Store the current head in temp
        *head = temp -> next; // Move head to the next node
        free(temp); // Free the memory allocated for temp
    }
    *tail = NULL; // Set tail to NULL after deleting the list
    return 0; // Return success
}

void print_list(node *head)
{
	if (head == NULL) //Cheking the list is empty or not
	{
		printf("INFO : List is empty.\n");
	}
	else
	{
        while (head) // Traverse the list until head becomes NULL character	
	    {
		    printf("%d", head -> data); //Printing the list one by one
		    head = head -> next; //Travering in forward direction or move the next node in the list
	    }
        printf("\n");
    }
}

int compare_list(node *head1, node *head2)
{
    int l1 = list_len(head1); // Get the length of the first list
    int l2 = list_len(head2); // Get the length of the second list
    if(l1 > l2) // If the length of the first list is greater than the second list, then return operand1
        return OPERAND1;
    else if(l1 < l2)    // If the length of the first list is less than the second list, then return operand2
        return OPERAND2; 
    else{
        node *temp1 = head1 , *temp2 = head2; // If the length of both lists is equal, then compare the data of each node
        while(temp1 != NULL) // Traverse the list until temp1 becomes NULL
        {
            if(temp1 -> data > temp2 -> data) // If the data of the first list is greater than the second list, then return operand1
                return  OPERAND1;
            else if(temp1 -> data < temp2 -> data) // If the data of the first list is less than the second list, then return operand2
                return  OPERAND2;
            else{
                temp1 = temp1 -> next; // Move temp1 to the next node
                temp2 = temp2 -> next; // Move temp2 to the next node
            }        
        }
        return SAME; // If the data of both lists is equal, then return same
    }          
}

int list_len(node *head)
{
    int count = 0; // Initialize count
    node *temp = head; // Initialize temp to head of the list
    while(temp  != NULL) // Traverse the list until temp becomes NULL character
    {
        count++; // Increment count for each node in the list
        temp = temp -> next; // Move temp to the next node in the list
    }
    return count; // Return the count of nodes in the list
}

void remove_pre_zeros(node **head) 
{
    if(*head == NULL) //check if the list is empty or not
	{
		return; // If the list is empty, return from the function
	}
    node *temp = *head; // point to head of the list
    while(temp -> next != NULL && temp -> data == 0) //traverse the list until the next node is not NULL and data of the current node is 0
    {
        *head = temp -> next; // point head to next node
        (*head) -> prev = NULL; // point prev of head to null
        free(temp); // free the temp node
        temp = *head;  // point temp to new head of the list 
    }
}


