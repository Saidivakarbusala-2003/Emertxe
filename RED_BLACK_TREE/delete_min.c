#include "rbt.h"

data_t delete_minimum(tree_t **root)
{
    tree_t *min = *root; // Start with root
    tree_t *x = NULL;   // Node to replace the deleted node
    tree_t *x_parent = NULL;  // Parent of x for fixup purposes

    if (min == NULL)
        return FAILURE;  // Tree is empty, nothing to delete

    /* Find minimum node */
    while (min->left != NULL) 
        min = min->left;

    /* Minimum node cannot have left child */
    x = min->right;

    /* Store parent for NULL fixup case */
    x_parent = min->parent;

    /* Replace minimum node with right child */
    if (min->parent == NULL)
        *root = x;

    else if (min == min->parent->left) // If min is a left child
        min->parent->left = x;

    else
        min->parent->right = x;  // If min is a right child

    if (x != NULL)
        x->parent = min->parent;  // Update parent pointer of x

    /* Fix RB violation if deleted node was BLACK */
    if (min->color == 1)
        delete_fixup(root, x, x_parent);

    free(min);  // Free the memory of the deleted node

    return SUCCESS;
}
