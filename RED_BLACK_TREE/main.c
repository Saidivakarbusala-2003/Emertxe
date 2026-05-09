#include "rbt.h"

int main()
{
	/* Declare the pointers */
	tree_t *root = NULL; // Initialize the root pointer to NULL, indicating an empty tree
	data_t data ,minimum ,maximum; // Declare variables to store user input for data, minimum, and maximum values
	char option;

	do
	{
		/* Display the menu */
		printf("\n--:: RED BLACK TREE MENU ::--\n1. Insert\n2. Delete\n3. Search\n4. Find Minimum\n5. Delete Minimum\n6. Find Maximum\n7. Delete Maximum\n8. Print RB tree\n\nEnter the number Which operation perform : ");

		data_t operation; // Declare a variable to store the user's choice of operation from the menu
		scanf("%d",&operation); // Read the user's choice of operation and store it in the variable 'operation' 

		switch (operation) // Use a switch statement to perform different actions based on the user's choice of operation
		{
			case 1: 
			// Insert a new node into the RB tree
				printf("\nEnter the data to be inserted into the RB Tree: ");
				scanf("%d", &data);

				if(insert(&root, data) == FAILURE)
				{
					break;
				}
				printf("\nINFO: After fix the node.\n");
				inorder(root);
				printf("\n");
				break;

			case 2:
			// Delete a node from the RB tree
			    if(root == NULL)
				{
					printf("\nINFO: RB Tree is empty\n");
					break;
				}
				printf("\nTree before deletion:\n");
				inorder(root);

				printf("\n\nEnter the data to be deleted from the RB Tree: ");
				scanf("%d", &data);
				if(delete(&root, data) == SUCCESS) // Call the delete function to remove the specified data from the RB tree, and check if the deletion was successful
				{
					printf("INFO: Node deleted successfully\n");
				}
				else{
					printf("INFO: Data not found\n");
					break;
				}
				/* Modify the above line to handle the error */
				
				printf("\nTree after deletion:\n");
				if(root == NULL)
                	printf("INFO: RB Tree is empty");
            	else
                	inorder(root);
				printf("\n");
				break;
			
			case 3: // Search for a node in the RB tree
				if(root == NULL)
				{
					printf("\nINFO: RB Tree is empty\n");
					break;
				}
				printf("\nEnter the data to be search the node from the RB Tree: ");
				scanf("%d", &data);
				tree_t *res = search(root, data);

				if (res != NULL)
				{
					printf("\nFound : (%d)-->(%s)\n", res->data, res->color == 0 ? "RED -> 0" : "BLACK -> 1");
				}
				else
				{
					printf("data Not Found\n");
				}
				break;	
				
			case 4: 
			    // Find the minimum value in the RB tree
				tree_t *resmin = find_minimum(root);
				/* Modify the above line to handle the error */
				if (resmin == NULL)
				{
					printf("\nINFO : RB Tree is empty\n");
				}
				else
				{
				    printf("\nINFO : Minimum value in the RB tree is : (%d)", resmin -> data);
					if (resmin -> color == 0)
						printf("-->(RED -> 0)\n");
					else
						printf("-->(BLACK -> 1)\n");	
				}
				break;

			case 5: 
			    // Delete the minimum value from the RB tree
				printf("\nTree before minimum node deletion:\n");
				if(root)
				{
					inorder(root);
				}
				if(delete_minimum(&root) == SUCCESS)
				{
					printf("\n\nINFO: Minimum node deleted successfully\n");

					printf("\nTree after minimum node deletion:\n");
					if(root)
					{
						inorder(root);
					}
					else
					{
						printf("INFO: RB Tree is empty");
					}
					printf("\n");
				}
				else
				{
					printf("\nINFO: RB Tree is empty\n");
				}
				break;

			case 6:
			    // Find the maximum value in the RB tree
				tree_t *resmax = find_maximum(root);
				
				if (resmax == NULL)
				{
					printf("\nINFO : RB Tree is empty\n");
				}
				else
				{
				    printf("\nINFO : Maximum value in the RB tree is : (%d)", resmax -> data);
					if (resmax -> color == 0)
					{
						printf("-->(RED -> 0)\n");
					}
					else
					{
						printf("-->(BLACK -> 1)\n");
					}	
				}
				break;	

			case 7:
			    // Delete the maximum value from the RB tree
				printf("\nTree before minimum node deletion:\n");
				if(root)
				{
					inorder(root);
				}
				if(delete_maximum(&root) == SUCCESS)
				{
					printf("\n\nINFO: Maximum node deleted successfully\n");

					printf("\nTree after maximum node deletion:\n");
					if(root)
					{
						inorder(root);
					}
					else
					{
						printf("INFO: RB Tree is empty");
					}
					printf("\n");
				}
				else
				{
					printf("\nINFO: RB Tree is empty\n");
				}

				break;	
			
			case 8:
			   // Print the RB tree
				if(root == NULL)
				{
					printf("\nINFO: RB Tree is empty\n");
					break;
				}
				printf("\nRB Tree is\n");
				inorder(root);
				printf("\n");
				break;

			default: // Handle invalid choices 
				printf("INFO: Invalid choice, enter only (1 to 7).\n");

		}

		printf("\nWant to continue? Press [yY | nN]: "); // Ask the user if they want to continue performing operations on the RB tree, and read their response into the variable 'option'
		scanf("\n%c", &option);

	}while (option == 'y' || option == 'Y'); // Continue the loop if the user enters 'y' or 'Y'
 
	return 0;
}
