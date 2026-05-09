#include "rbt.h"

data_t delete_maximum(tree_t **root)
{
    tree_t *max = *root; // Start with root
    tree_t *x = NULL;     // Node to replace the deleted node
    tree_t *x_parent = NULL;  // Parent of x for fixup purposes

    if (max == NULL)
        return FAILURE; // Tree is empty, nothing to delete

    /* Find maximum node */
    while (max->right != NULL)
        max = max->right;

    /* Maximum node cannot have right child */
    x = max->left;

    /* Store parent for NULL fixup case */
    x_parent = max->parent;

    /* Replace maximum node with left child */
    if (max->parent == NULL)
        *root = x;

    else if (max == max->parent->right) // If max is a right child
        max->parent->right = x;

    else
        max->parent->left = x; // If max is a left child

    if (x != NULL)
        x->parent = max->parent; // Update parent pointer of x

    /* Fix RB violation if deleted node was BLACK */
    if (max->color == 1)
        delete_fixup(root, x, x_parent);

    free(max);  // Free the memory of the deleted node

    return SUCCESS;
}
