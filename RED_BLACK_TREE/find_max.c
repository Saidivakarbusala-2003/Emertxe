#include "rbt.h"

tree_t* find_maximum(tree_t *root)
{
	if(root == NULL) // If the tree is empty, return NULL
    {
        return NULL;
    }
    tree_t *temp = root;  // Start with the root node
    while(temp -> right != NULL)    // Traverse the right subtree until the rightmost node is reached
    {
        temp = temp -> right; // Move to the right child
    }
    return temp;  // Return the rightmost node, which is the maximum node in the RB tree
}
