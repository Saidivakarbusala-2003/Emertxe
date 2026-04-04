/*
Name        : Busala Sai Divakar.

Date        : 25-03-2025.

Project     : Inverted Search Engine.

Description : This project implements an inverted search engine that allows users to create a database of words and their occurrences 
in a set of files. The program provides a menu-driven interface for users to create, display, save, search, and update the database. 
The database is implemented using a hash table to store the words and their associated file information efficiently. The program also 
includes error handling for invalid inputs and ensures that the database can only be created or updated once during the program's 
execution.
*/


#include "inverted.h"

int db_created = 0,db_updated = 0;
int main(int argc, char *argv[])
{
    F_node *head = NULL; //	 Initialize the head of the linked list of files to NULL
    M_node *HT[27]; // Declare a hash table (array of pointers to main nodes) with 27 slots (26 for letters and 1 for non-alphabetic characters)
	for(int i = 0; i < 27; i++) // Initialize all slots in the hash table to NULL
	{
		HT[i] = NULL; // Set each slot in the hash table to NULL
	}

	if(argc < 2) // Check if the number of command-line arguments is less than 2 (which means no files were provided)
    {
        printf("Error: Invalid arguments. Please pass at least two arguments.\n\n");
        exit(0);
    }
    
	validate_files(argv, &head);  // Validate_files

    int option; // Variable to store the user's menu choice
    do
    {
		printf("\nSelect your choice among following operations:\n1. Create Database\n2. Display Database\n3. Save Database\n4. Search\n5. Update Database\n6. Exit\n\nEnter your choice -> ");

		int x = scanf("%d", &option);  // Read the user's menu choice and check if it's a valid integer
		if(x != 1) // If the input is not a valid integer, print an error message and prompt the user again
        {
            printf("INFO : Please enter a valid option.\n");
            while(getchar() != '\n');   
            continue;
        }
		switch (option) // Handle the user's menu choice using a switch statement
		{
			case 1:
				if(!db_created) // If the database has not been created yet, create it using the validated files and set the db_created flag to 1
				{
					create_database(HT, head); // Create the database by reading the validated files and populating the hash table
					db_created = 1; // Set the flag to indicate that the database has been created
				}
				else
					printf("INFO: Already database is created, you cant create a data base again\n"); // If the database has already been created
				break;

			case 2:
				if(db_created || db_updated) // If the database has been created or updated, display its contents; otherwise
					display_database(HT);
				else
					printf("INFO: Database is empty. Please create or update it first.\n");	
				break;

			case 3:
				save_database(HT); // Save the current state of the database to a file 
				break;

			case 4:
				search_database(HT); // Search for a word in the database and display its information if found
				break;

			case 5:
				if(!db_updated && !db_created) // If the database has not been created or updated yet, 
				{
					update_database(HT, &head); // Update the database by reading the validated files again and modifying the hash table accordingly
					db_updated = 1; // Set the flag to indicate that the database has been updated
				}
				else
					printf("INFO: You have already database, You cant Re-Update DataBase.\n"); // If the database has already been created or updated
				break;

			case 6:
				break; // Exit the program

			default:
				printf("INFO : Please enter the valid option\n"); // If the user enters an option that is not in the menu, print an error message
		}
    }while( option != 6); // Continue to show the menu until the user chooses to exit
    return 0; // Return 0 to indicate that the program ended successfully
}
