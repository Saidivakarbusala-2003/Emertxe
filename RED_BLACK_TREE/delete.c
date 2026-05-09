#include "rbt.h"

/* RB Delete */
data_t delete(tree_t **root, data_t item)
{
    tree_t *z = *root; // Node to be deleted
    tree_t *x = NULL;   // Node to replace the deleted node
    tree_t *y = NULL;  // Node to be deleted or moved
    tree_t *x_parent = NULL;  // Parent of x for fixup purposes

    /* Search node */
    while (z != NULL) // Traverse the tree to find the node to delete
    {
        if (item < z->data)  // If the item to delete is smaller than the current node's data, go left
            z = z->left;

        else if (item > z->data) // If the item to delete is greater than the current node's data, go right
            z = z->right;

        else
            break; // Node with the item found, exit the loop
    }

    if (z == NULL)
        return FAILURE; // Item not found in the tree, return failure

    y = z;

    int y_original_color = y->color; // Store the original color of the node to be deleted for fixup purposes

    /* Case R-0 / B-0 */
    if (z->left == NULL)  // If the node to delete has no left child, replace it with its right child
    {
        x = z->right;
        x_parent = z->parent; // Store the parent of the node to be deleted for fixup purposes

        if (z->parent == NULL)  // If the node to be deleted is the root, update the root pointer
            *root = z->right;

        else if (z == z->parent->left)  // If the node to be deleted is a left child, update the parent's left pointer
            z->parent->left = z->right; 

        else
            z->parent->right = z->right; // If the node to be deleted is a right child, update the parent's right pointer

        if (z->right != NULL)
            z->right->parent = z->parent; // Update the parent pointer of the right child of the node to be deleted
    }

    /* Case R-1 / B-1 */
    else if (z->right == NULL) // If the node to delete has no right child, replace it with its left child
    {
        x = z->left; // Set x to the left child of the node to be deleted
        x_parent = z->parent;  // Store the parent of the node to be deleted for fixup purposes

        if (z->parent == NULL)  // If the node to be deleted is the root, update the root pointer
            *root = z->left;

        else if (z == z->parent->left) // If the node to be deleted is a left child, update the parent's left pointer
            z->parent->left = z->left;

        else
            z->parent->right = z->left; // If the node to be deleted is a right child, update the parent's right pointer

        if (z->left != NULL)
            z->left->parent = z->parent; // Update the parent pointer of the left child of the node to be deleted
    }

    /* Case R-2 / B-2 */
    else // If the node to delete has two children, find its in-order successor  and replace it with that successor
    {
        y = z->right; // Start with the right child of the node to be deleted

        while (y->left != NULL) // Traverse left to find the in-order successor (the smallest node in the right subtree)
            y = y->left;

        y_original_color = y->color; // Store the original color of the in-order successor for fixup purposes

        x = y->right; // Set x to the right child of the in-order successor (the in-order successor cannot have a left child)

        if (y->parent == z) // If the in-order successor is a direct child of the node to be deleted, update x_parent to y
        { 
            x_parent = y;

            if (x != NULL)
                x->parent = y; // Update the parent pointer of x to y (the in-order successor)
        }
        else
        {
            x_parent = y->parent; // Store the parent of the in-order successor for fixup purposes

            if (y == y->parent->left)
                y->parent->left = y->right; // If the in-order successor is a left child, update the parent's left pointer

            else
                y->parent->right = y->right; // If the in-order successor is a right child, update the parent's right pointer

            if (y->right != NULL) // Update the parent pointer of the right child of the in-order successor to the parent of the in-order successor
                y->right->parent = y->parent;

            y->right = z->right; // Replace the right child of the node to be deleted with the right child of the in-order successor
            y->right->parent = y; // Update the parent pointer of the right child of the in-order successor to y (the in-order successor)
        }

        if (z->parent == NULL) // If the node to be deleted is the root, update the root pointer to the in-order successor
            *root = y;

        else if (z == z->parent->left) // If the node to be deleted is a left child
            z->parent->left = y;

        else
            z->parent->right = y; // If the node to be deleted is a right child, update the parent's right pointer to the in-order successor

        y->parent = z->parent; // Update the parent pointer of the in-order successor to the parent of the node to be deleted

        y->left = z->left; // Replace the left child of the node to be deleted with the left child of the in-order successor
        y->left->parent = y; // Update the parent pointer of the left child of the in-order successor to y (the in-order successor)

        y->color = z->color; // Set the color of the in-order successor to the color of the node to be deleted 
    }

    free(z); // Free the memory of the deleted node

    /* FIXUP */
    if (y_original_color == 1) // If the original color of the node to be deleted was BLACK, perform fixup to maintain RB tree properties
        //delete_fixup(root, x , );
        delete_fixup(root, x, x_parent); // Pass x and its parent to the delete_fixup function to restore the properties of the RB tree

    return SUCCESS;
}
   