#include "rbt.h"

tree_t* find_minimum(tree_t *root)
{
	if(root == NULL) // If the tree is empty, return NULL
    {
        return NULL;
    }
    tree_t *temp = root; // Start with the root node
    while(temp -> left != NULL) // Traverse the left subtree until the leftmost node is reached
    {
        temp = temp -> left; // Move to the left child
    }
    return temp; // Return the leftmost node, which is the minimum node in the RB tree
}
