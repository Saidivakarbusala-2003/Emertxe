#include "rbt.h"

tree_t* search(tree_t *root, data_t key)
{
    while (root != NULL) // Traverse the tree until we find the key or reach a NULL pointer
    {
        if (key == root->data) // If the key is found, return the current node
            return root;  // Return the node containing the key
        else if (key < root->data) // If the key is smaller than the current node's data, go left
            root = root->left; // If the key is greater than the current node's data, go right
        else
            root = root->right; // Move to the right child
    }
    return NULL; // If we reach a NULL pointer, the key is not found in the tree, so return NULL
}
