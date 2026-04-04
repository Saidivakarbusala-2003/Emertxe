#include "inverted.h"

void create_database(M_node *HT[], F_node *head)
{
    F_node *temp = head; // use a temporary pointer to traverse the file list
    while(temp != NULL) // traverse through the file list
    { 
        FILE *fptr = fopen(temp->f_name, "r"); // open the current file for reading
        if(!fptr) // check if the file was opened successfully
        {
            printf("File not opened\n");
            return;
        }
        char word[30]; // buffer to store each word read from the file

        while(fscanf(fptr, "%s", word) != EOF) // read each word until end of file
        {
            int index = get_index(word); // get the index for the word based on its first character

            if(HT[index] == NULL) // if there is no main node at this index, create one
            {
                create_node(HT, index, word, temp->f_name); // create a new main node and attach the file information
            }
            else
            {
                M_node *mtrvs = HT[index]; // traverse the main nodes at this index to find if the word already exists
                int found = 0;

                while(mtrvs != NULL) // traverse through the main nodes
                {
                    if(strcmp(mtrvs->word, word) == 0) // if the word already exists, update the file count and sub nodes 
                    {
                        found = 1;

                        S_node *strvs = mtrvs->sub_link; // traverse the sub nodes to find if the file already exists
                        S_node *prev = NULL; // keep track of the previous sub node for insertion if needed

                        while(strvs != NULL) // traverse through the sub nodes
                        {
                            if(strcmp(strvs->filename, temp->f_name) == 0)
                            {
                                strvs->word_count++; // if the file already exists in the sub nodes, increment the word count
                                break;
                            }
                            prev = strvs; // keep track of the previous sub node
                            strvs = strvs->sub_link; // move to the next sub node
                        }

                        if(strvs == NULL) // if the file does not exist in the sub nodes
                        {
                            S_node *sub_node = malloc(sizeof(S_node)); // create a new sub node for the file
                            if(!sub_node)
                            {
                                printf("Memory allocation failed\n"); // check if memory allocation was successful
                                fclose(fptr);
                                return;
                            }
                            strcpy(sub_node->filename, temp->f_name); // copy the file name to the sub node
                            sub_node->word_count = 1; // initialize the word count to 1 for the new file
                            sub_node->sub_link = NULL; // initialize the sub link to NULL
                            prev->sub_link = sub_node; // attach the new sub node to the end of the sub nodes list
                            mtrvs->file_count++; // increment the file count for the main node since a new file is added
                        }
                        break;
                    }
                    mtrvs = mtrvs->main_link; // move to the next main node
                }
                if(!found) // if the word does not exist in the main nodes
                {
                    create_node(HT, index, word, temp->f_name); // create a new main node and attach the file information
                }
            }
        }
        fclose(fptr); // close the file after processing
        temp = temp->link; // move to the next file in the file list
    }
    printf("Database created successfully\n"); // print a success message after creating the database
}