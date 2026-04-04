#include "inverted.h"

int update_database(M_node *HT[], F_node **head)
{ 
    char filename[100]; // buffer to store the file name input by the user
    printf("Enter file name: "); // prompt the user to enter the file name for updating the database
    scanf("%99s", filename);   // read the file name input from the user, limiting to 99 characters to prevent buffer overflow
    char *ext = strrchr(filename, '.'); // get the file extension by finding the last occurrence of '.' in the file name
    if(ext == NULL) // check if the file has an extension
    {
        printf("\nINFO: %s => File has no extension\n", filename);
        return 0;
    }
    else if(strcmp(ext, ".txt") != 0) // check if the file extension is not .txt
    {
        printf("\nINFO: %s => Not a .txt file\n", filename);
        return 0;
    }

    FILE *fptr = fopen(filename, "r"); // open the specified file for reading
    if(!fptr)
    {
        printf("File cannot open....!\n");
        return 0;
    }

    if(fgetc(fptr) != '#') // check if the file is a valid database file by checking if it starts with '#'
    {
        printf("Invalid database file....!\n"); // check if the file is a valid database file by checking if it starts with '#'
        fclose(fptr);
        return 0;
    }
    rewind(fptr); // reset the file pointer to the beginning of the file after checking the first character

    char idx[5], file_count[5], word_count[5]; // buffers to store the index, file count, and word count read from the file
    char word[100], file_name[100]; // buffers to store the word and file name read from the file

    while(fscanf(fptr, " #%[^;];%[^;];%[^;];", idx, word, file_count) == 3) // read the index, word, and file count for each main node until the end of the file
    {
        int index;
        if(isalpha(word[0]))
            index = tolower(word[0]) - 'a'; // calculate the index for the main node based on the first character of the word
        else
            index = 26; // use index 26 for words that do not start with an alphabetic character
        int fcount = atoi(file_count);  // convert the file count from string to integer for processing  

        M_node *main_node = malloc(sizeof(M_node)); // create a new main node for the word read from the file
        if(!main_node)
        {
            printf("Memory allocation failed\n"); // check if memory allocation for the main node was successful
            fclose(fptr);
            return 0;
        }
        strcpy(main_node->word, word); // copy the word to the main node
        main_node->file_count = fcount; // set the file count for the main node based on the value read from the file
        main_node->main_link = NULL; // initialize the main link to NULL for the new main node
        main_node->sub_link = NULL; // initialize the sub link to NULL for the new main node 

        if(HT[index] == NULL) // if there is no main node at the calculated index
        {
            HT[index] = main_node; // set the new main node as the head of the main nodes list at this index in the hash table 
        }
        else
        {
            M_node *temp = HT[index]; // use a temporary pointer to traverse the main nodes at this index in the hash table
            while(temp->main_link) // traverse to the end of the main nodes list at this index
                temp = temp->main_link; // move to the next main node
            temp->main_link = main_node; // attach the new main node to the end of the main nodes list at this index in the hash table
        }

        for(int i = 0; i < fcount; i++) // loop to read the file name and word count for each sub node associated with the current main node
        {
            if(fscanf(fptr, "%[^;];%[^;];", file_name, word_count) != 2) // read the file name and word count for the sub node
                break;
  
            S_node *sub_node = malloc(sizeof(S_node)); // create a new sub node for the file information read from the file
            if(!sub_node) // check if memory allocation for the sub node was successful
            {
                printf("Memory allocation failed\n");
                fclose(fptr);
                return 0;
            }
            strcpy(sub_node->filename, file_name); // copy the file name to the sub node
            sub_node->word_count = atoi(word_count); // set the word count for the sub node based on the value read from the file
            sub_node->sub_link = NULL; // initialize the sub link to NULL for the new sub node

            if(main_node->sub_link == NULL) // if there are no sub nodes for the current main node
            {
                main_node->sub_link = sub_node; // set the new sub node as the head of the sub nodes list for the current main node
            }
            else
            {
                S_node *stemp = main_node->sub_link; // use a temporary pointer to traverse the sub nodes for the current main node
                while(stemp->sub_link) // traverse to the end of the sub nodes list for the current main node
                    stemp = stemp->sub_link; // move to the next sub node
                stemp->sub_link = sub_node; // attach the new sub node to the end of the sub nodes list for the current main node
            }
        }
    }
    //remove the duplicate files
    F_node *temp = *head; // use a temporary pointer to traverse the file list
    {
        F_node *next = temp->link; // store the next file in the list 
        int found = 0;
        for(int i = 0; i < 27 && !found; i++) // loop through the hash table times
        {
            M_node *main = HT[i]; // use a temporary pointer to traverse the main nodes at the current index in the hash table
            while(main && !found) //    traverse through the main nodes at the current index in the hash table
            {
                S_node *sub = main->sub_link; // use a temporary pointer to traverse the sub nodes for the current main node

                while(sub) // traverse through the sub nodes for the current main node
                {
                    if(strcmp(sub->filename, temp->f_name) == 0) // if the file name in the sub node matches the current file in the file list
                    {
                        delete_node(head, temp->f_name); // delete the current file
                        found = 1; // set the found flag to indicate that the file has been found and deleted
                        break;
                    }
                    sub = sub->sub_link; // move to the next sub node
                }
                main = main->main_link; // move to the next main node
            }
        }
        temp = next; // move to the next file in the file list
    }
    fclose(fptr); // close the file after processing
    printf("Update Database successfully\n"); // print a success message after updating the database
    return 1; // return success status after updating the database
}