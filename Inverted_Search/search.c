#include "inverted.h"

void search_database(M_node *HT[])
{
    char str[100]; // Buffer to store the word entered by the user for searching in the database
    printf("Enter the seaching word: ");
    scanf("%s",str); // Read the word from the user that they want to search in the database
    getchar(); // Consume the newline character left in the input buffer after reading the word

    int index = get_index(str); // Get the index for the entered word 
    if(HT[index] == NULL) // Check if there is null or not
    {
        printf("INFO: Word is not found...!\n"); // Print a message 
        return;
    }
    M_node *mtemp = HT[index]; // Traverse the main nodes 
    while(mtemp != NULL) // For each main node at that index, check if the word matches the entered word
    {
        if(strcmp(mtemp->word, str) == 0) // If the word matches the current main node's word
        {
            printf("INFO: Word is found....!\n"); // Print a message to indicate that the word is found in the database
            printf("Index      : %d\nWord       : %s\nFile Count : %d\n",index,str,mtemp->file_count);
            S_node *stemp = mtemp->sub_link; // Traverse the sub nodes 

            while(stemp != NULL) // For each sub node of the current main node
            {
                printf("File Name  : %s\nWord Count : %d\n",stemp->filename, stemp->word_count);
                stemp = stemp->sub_link; // Move to the next sub node of the current main node 
            }
            return;
        }
        mtemp = mtemp -> main_link; // Move to the next main node 
    }
    printf("INFO: Word is not found...!\n"); // word not found
}
