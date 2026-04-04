#include "inverted.h"

void save_database(M_node *HT[])
{
    char filename[100]; // Buffer to store the file name entered by the user
    printf("Enter file name: "); // Prompt the user to enter the file name for saving the database
    scanf("%s", filename); // Read the file name from the user

    char *ext = strchr(filename, '.'); // Find the last occurrence of the '.' character in the file name to get the file extension
    if(ext == NULL) //  Check if the file name does not contain an extension
    {
        printf("\nINFO: %s => This file has without extension\n",filename);
        return;
    }
    else if(strcmp(ext, ".txt") != 0) // Check if the file extension is not ".txt"
    {
        printf("\nINFO: %s => This file not a .txt file\n", filename); 
        return;
    }
    
    FILE *fptr = fopen(filename, "w"); // Open the file in write mode to save the database.
    if(!fptr)
    {
        printf("File cannot open.\n");
    }
    for(int i = 0; i < 27; i++) // Loop through each index of the hash table to save the database contents
    {
        if(HT[i] != NULL) // Check if there are main nodes at that index in the hash table
        { 
            M_node *mtemp = HT[i]; // Traverse the main nodes at that index

            while(mtemp != NULL)    // For each main node at that index
            {
                fprintf(fptr, "#%d;%s;%d;", i, mtemp->word, mtemp->file_count); // Write the index, word, and file count for the main node to the file in a specific format
                S_node *stemp = mtemp->sub_link; // Traverse the sub nodes of the current main node to write their information to the file
                while(stemp != NULL) // For each sub node of the current main node, write the file name and word count to the file in a specific format
                {
                    fprintf(fptr, "%s;%d;", stemp->filename, stemp->word_count); // Write the file name and word count for the sub node to the file in a specific format
                    stemp = stemp->sub_link; // Move to the next sub node of the current main node
                }
                fprintf(fptr, "#\n"); // Write a '#' character followed by a newline to indicate the end of the main node's information in the file
                mtemp = mtemp->main_link; // Move to the next main node at that index in the hash table
            }
        }
    }
    fclose(fptr); // Close the file after writing all the database information to it
    printf("Database saved successfully in %s\n", filename); // Print a message to indicate that the database has been saved successfully along with the file name
}   
