#include "rbt.h"

data_t insert(tree_t **root, data_t data)
{
    tree_t *new_node = (tree_t *)malloc(sizeof(tree_t)); // Allocate memory for the new node
    if (!new_node) // Check if memory allocation was successful
    {
        printf("Memory not allocated\n"); // Print an error message if memory allocation fails
        return -1; // Return -1 to indicate failure
    }
    new_node -> data = data; // Set the data of the new node to the value provided by the user
    new_node -> left = NULL; // Initialize the left child of the new node to NULL
    new_node -> right = NULL; // Initialize the right child of the new node to NULL
    new_node -> parent = NULL; // Initialize the parent pointer of the new node to NULL
    new_node -> color = 0; // Set the color of the new node to RED (0) as per RB tree insertion rules

    char duplicate = 1; // Flag to check for duplicate values, initialized to 1 (true)

    *root = bst_insert(*root, new_node, &duplicate); // Insert the new node into the BST and update the root pointer, passing the duplicate flag by reference

    if (!duplicate) // Check if the duplicate flag was set to 0 (false) by the bst_insert function, indicating a duplicate value was found
        return -1;
    
    printf("\nINFO : New node insection successfully\n"); // Print a success message after inserting the new node  

    printf("\nINFO: Before fix the node.\n");
    inorder(*root); // Print the tree in-order before fixing any violations
    printf("\n"); // Print a newline for better readability

    fix_violation(root, new_node);   // Call the fix_violation function to restore the properties of the RB tree after insertion
    return 0;      
}