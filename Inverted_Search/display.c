#include "inverted.h"

void display_database(M_node *HT[])
{
    printf("----------------------------------------------------------------------------\n");
    printf("\t\t---->:: DATABASE INFORMATION ::<----\n");
    printf("----------------------------------------------------------------------------\n");
    printf("| %-5s | %-20s | %-10s | %-15s | %-10s |\n", "INDEX", "WORD", "FILE COUNT", "FILE NAME", "WORD COUNT");
    printf("----------------------------------------------------------------------------\n");
    for(int i = 0; i < 27; i++) // for each index in the hash table
    {
        if(HT[i] != NULL) // if there are main nodes at that index
        {
            M_node *mtemp = HT[i];  // traverse the main nodes at that index
            while(mtemp != NULL) // for each main node at that index
            {
                S_node *stemp = mtemp->sub_link; // traverse the sub nodes of the current main node
                int first = 1; // flag to indicate if it's the first sub node for the main node (used for formatting the output)
                while(stemp != NULL) // for each sub node of the current main node
                {
                    if(first) // if it's the first sub node for the main node, print the index, word, file count, file name and word count
                    {
                        printf("| %-5d | %-20s | %-10d | %-15s | %-10d |\n", i, mtemp->word ,mtemp->file_count ,stemp->filename ,stemp->word_count);
                        first = 0; // set the flag to 0 after printing the first sub node for the main node
                    }
                    else // if it's not the first sub node for the main node, print only the file name and word count
                    {
                        printf("| %-5s | %-20s | %-10s | %-15s | %-10d |\n" ,"" ,"" ,"" ,stemp->filename ,stemp->word_count);
                    }
                    stemp = stemp->sub_link; // move to the next sub node of the current main node
                }
                printf("----------------------------------------------------------------------------\n");
                mtemp = mtemp->main_link; // move to the next main node at that index
            }
        }
    }
}