#include "inverted.h"

/* Function definitions */
int insert_last(F_node **head, char *f_name)
{
    F_node *new_node = malloc(sizeof(F_node)); //create the new node in dma
    if(new_node == NULL)
    {
        return -1; //failure
    }
    strcpy(new_node->f_name, f_name);
    new_node -> link = NULL; //stored the null in new node link
    if(*head == NULL) //check head is empty or not
    {
        *head = new_node;
        return 0; //success
    }
    else //not empty
    {
        F_node *temp = *head; // create one temp pointer
        while(temp -> link != NULL) //loop runs 
        {
            temp = temp -> link; //store the next node into temp
        }
        temp -> link = new_node;  // strore the new node in temp link
    }
    return 0;//suceess
}

int delete_node(F_node** head, char* file_name)
{
    if(head == NULL || *head == NULL) // Check if the list is empty
        return 1;

    F_node* temp = *head; // Start from the head of the list
    F_node* prev = NULL; // To keep track of the previous node while traversing
    while(temp != NULL) // Traverse the list to find the node to delete
    {
        if(strcmp(temp->f_name, file_name) == 0) // If the file name matches the current node's file name
        {
            if(prev == NULL) // If the node to delete is the head of the list
            {
                *head = temp->link;    // Update the head to point to the next node
            }
            else
            {
                prev->link = temp->link; // Update the previous node's link to skip the current node
            }
            free(temp); // Free the memory allocated for the current node
            return 1; // success
        }
        prev = temp; // Move to the next node
        temp = temp->link; // Move to the next node
    }
    return 0; // not found
}

int check_duplicates(F_node *head, char *f_name)
{
    F_node *temp = head; // Start from the head of the list
    while(temp != NULL) // Traverse the list to check for duplicates
    {
        if(strcmp(temp -> f_name, f_name) == 0) // If the file name matches the current node's file name
        {
            return 1;// duplicate found
        }  
        temp = temp->link;  // move to next node
    }
    return 0;// no duplicate
}

int print_filenames(F_node *head)
{
    if (head == NULL) //Cheking the list is empty or not
	{
        printf("-> NULL\n");
        return -1;
	}
	else
	{
        while (head != NULL) // Traverse the list until head becomes NULL character	
	    {
		    printf("%s -> ", head -> f_name); //Printing the list one by one
		    head = head -> link; //Travering in forward direction or move the next node in the list
	    }
        printf("NULL\n");
    }
    return 0;
}

int get_index(char *word)
{
    if(word[0] >= 'a' && word[0] <= 'z') // Check if the first character of the word is a lowercase letter
    {
        return (word[0] - 97); // Return the index by subtracting the ASCII value of 'a' from the ASCII value of the first character of the word
    }
    if(word[0] >= 'A' && word[0] <= 'Z') // Check if the first character of the word is an uppercase letter
    {
        return (word[0] - 65); // Return the index by subtracting the ASCII value of 'A' from the ASCII value of the first character of the word
    }
    else
    {
        return 26; // Return 26 for non-alphabetic characters
    }
}

int create_node(M_node *HT[],int index,char *word,char *file_name)
{
    M_node *main_node = malloc(sizeof(M_node)); // Create a new main node in dynamic memory allocation
    if(!main_node) // Check if memory allocation for the main node was successful
    {
        printf("Memory not allocated in main node.\n");
        return -1;
    }
    strcpy(main_node -> word, word); // Copy the word to the main node's word field
    main_node -> file_count = 1; // Initialize the file count to 1 for the new main node since we are adding a new word for the first time
    main_node -> main_link = NULL; // Initialize the main link to NULL for the new main node
    main_node -> sub_link = NULL; // Initialize the sub link to NULL for the new main node

    S_node *sub_node = malloc(sizeof(S_node)); // Create a new sub node in dynamic memory allocation for the file associated with the word
    if(!sub_node)    
    {
        printf("Memory not allocated in sub node.\n");
        return -1;
    }
    strcpy(sub_node -> filename ,file_name); // Copy the file name to the sub node's filename field
    sub_node -> word_count = 1; // Initialize the word count to 1 for the new sub node since we are adding a new word for the first time in that file
    sub_node -> sub_link = NULL; // Initialize the sub link to NULL for the new sub node

    main_node -> sub_link = sub_node; // Link the new sub node to the main node's sub link

    if(HT[index] == NULL) // If there are no main nodes at that index in the hash table, set the new main node as the first node at that index
    {
        HT[index] = main_node; // Set the new main node as the first node at that index in the hash table
    }
    else
    {
        M_node *temp = HT[index]; // If there are already main nodes at that index, traverse to the end of the main node list and link the new main node there
        while(temp->main_link != NULL) //   Traverse the main node list at that index until the end is reached
        {
            temp = temp->main_link; // Move to the next main node in the list
        }
        temp->main_link = main_node; // Link the new main node to the end of the main node list at that index in the hash table
    }
    return 0;
}

void validate_files(char *argv[], F_node **head)
{
    for(int i = 1;argv[i] != NULL;i++) // Loop through the command line arguments starting from index 1 (since index 0 is the program name)
    {
        char *ext = strchr(argv[i], '.'); // Find the last occurrence of the '.' character in the file name to get the file extension
        if(ext == NULL)
        {
            printf("\nINFO: %s => This file has without extension\n",argv[i]);
            continue;
        }
        else if(strcmp(ext, ".txt") != 0) // Check if the file extension is not ".txt"
        {
            printf("\nINFO: %s => This file not a .txt file\n", argv[i]); 
            continue;
        }

        FILE *fptr = fopen(argv[i], "r"); // Try to open the file in read mode and check if it was successful
        if(fptr == NULL)
        {
            printf("\nINFO: %s => This file not present\n", argv[i]);
            continue;
        }

        fseek(fptr, 0, SEEK_END); // Move the file pointer to the end of the file to check if the file is empty
        if(ftell(fptr) == 0) // Check if the file pointer is at position 0, which indicates that the file is empty
        {
            printf("\nINFO: %s => This file is empty\n", argv[i]);
            fclose(fptr);
            continue;
        }
        fclose(fptr); // Close the file after validating it
        if(check_duplicates(*head, argv[i]) == 1) // Check if the file name already exists in the linked list of files
        {
            printf("\nINFO: %s file already exists\n", argv[i]);
            continue;
        }

        insert_last(head, argv[i]); // If the file is valid and not a duplicate, insert it at the end of the linked list of files
    }
    if(*head == NULL) // After validating all the files, check if the linked list of files is still empty
    {
        printf("\nINFO: Files are not there\nCreate database is not posible\n\n");
        print_filenames(*head); // Print the empty list of files
        exit(0);
    }
    printf("\nINFO: These files are passed by the user in the correct way\n"); // Print a message indicating that the files have been validated successfully
    print_filenames(*head);   // Print the list of valid files that will be used to create the database
}