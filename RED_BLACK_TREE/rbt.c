#include "rbt.h"

#define RED     "\033[1;31m"
#define WHITE   "\033[1;37m"
#define RESET   "\033[0m"

static void print_tree(tree_t *root, int space)
{
    if(root == NULL) // If the current node is NULL, return from the function (base case for recursion)
        return; 

    space += 5; // Increase the space for the next level of the tree

    print_tree(root->right, space); // Recursively print the right subtree first (to display it on the right side)

    printf("\n");  

    for(int i = 5; i < space; i++) // Print spaces to create the visual structure of the tree
        printf(" ");

    if(root->color == 0) // If the color of the current node is RED (0), print the data in red color
        printf(RED "%d(R)\n" RESET, root->data);
    else
        printf(WHITE "%d(B)\n" RESET, root->data); // If the color of the current node is BLACK (1), print the data in white color

    print_tree(root->left, space); // Recursively print the left subtree after printing the current node (to display it on the left side)    
}

tree_t* bst_insert(tree_t *root, tree_t *node, char *dup)
{
    if (root == NULL) // If the current root is NULL, insert the new node here and return the new node as the new root of this subtree
        return node; 

    if (node->data < root->data) // If the data of the new node is smaller than the current root's data, insert it into the left subtree
    {
        root->left = bst_insert(root->left, node, dup); // Recursively call bst_insert on the left child of the current root to insert the new node
        if (root->left != NULL) // Update the parent pointer of the left child of the current root to the current root
            root->left->parent = root;
    }
    else if (node->data > root->data) // If the data of the new node is greater than the current root's data, insert it into the right subtree
    {
        root->right = bst_insert(root->right, node, dup);
        if (root->right != NULL) // Update the parent pointer of the right child of the current root to the current root
            root->right->parent = root;
    }
    else
    {
        printf("\nDuplicate already data present in RB Tree: %d\n", node->data);
        free(node); // Free the memory allocated for the new node since it is a duplicate and will not be inserted into the tree
        *dup = 0;   // mark as failed
        return root; // Return the current root without inserting the new node since it is a duplicate
    }
    return root;
}

void inorder(tree_t *root)
{
    print_tree(root, 0); // Call the print_tree function to display the RB tree in a structured format
}

void right_rotate(tree_t **root, tree_t *x)
{
    tree_t *y = x -> left; // Set y to the left child of x, which will become the new root of the subtree after the right rotation

    x -> left = y -> right; // Update the left child of x to be the right child of y (the subtree that will be moved from y to x)
    if (y -> right != NULL) //  If the right child of y is not NULL, update its parent pointer to x (the new parent after rotation)
        y -> right -> parent = x; // Update the parent pointer of the right child of y to x (the new parent after rotation)

    y -> parent = x -> parent; // Update the parent pointer of y to the parent of x (the new parent after rotation)

    if (x -> parent == NULL) // If x is the root of the tree, update the root pointer to y (the new root after rotation)
        *root = y;   // If x is a left child, update the left pointer of the parent of x to y (the new child after rotation)
    else if (x == x -> parent -> right) // If x is a right child, update the right pointer of the parent of x to y (the new child after rotation)
        x -> parent -> right = y; // If x is a left child, update the left pointer of the parent of x to y (the new child after rotation)
    else // If x is a left child, update the left pointer of the parent of x to y (the new child after rotation)
        x -> parent -> left = y;

    y -> right = x; // Update the right child of y to x (the new child after rotation)
    x -> parent = y;// Update the parent pointer of x to y (the new parent after rotation)
}

void left_rotate(tree_t **root, tree_t *x)
{
    tree_t *y = x -> right; // Set y to the right child of x, which will become the new root of the subtree after the left rotation

    x -> right = y -> left; // Update the right child of x to be the left child of y (the subtree that will be moved from y to x)
     if (y -> left != NULL) // If the left child of y is not NULL, update its parent pointer to x (the new parent after rotation)
         y -> left -> parent = x; // Update the parent pointer of the left child of y to x (the new parent after rotation)
    if (y -> left != NULL) // If the left child of y is not NULL, update its parent pointer to x (the new parent after rotation)
        y -> left -> parent = x; // Update the parent pointer of the left child of y to x (the new parent after rotation)

    y -> parent = x -> parent; //   Update the parent pointer of y to the parent of x (the new parent after rotation)

    if (x -> parent == NULL) // If x is the root of the tree, update the root pointer to y (the new root after rotation)
        *root = y;   
    else if (x == x -> parent -> left) // If x is a left child, update the left pointer of the parent of x to y (the new child after rotation)
        x -> parent -> left = y; // If x is a right child, update the right pointer of the parent of x to y (the new child after rotation)
    else // If x is a right child, update the right pointer of the parent of x to y (the new child after rotation)
        x -> parent -> right = y;

    y -> left = x; // Update the left child of y to x (the new child after rotation)
    x -> parent = y; // Update the parent pointer of x to y (the new parent after rotation)
}

void fix_violation(tree_t **root, tree_t *node) //insetion fix function
{   // Fix the RB tree properties after inserting a new node
    while (node != *root && node -> parent -> color == 0) 
    {
        tree_t *parent = node -> parent; // Get the parent of the current node
        tree_t *grandparent = parent -> parent; // Get the grandparent of the current node

        if (parent == grandparent -> left) // If the parent is a left child of the grandparent
        {
            tree_t *uncle = grandparent -> right; // Get the uncle of the current node (the right child of the grandparent)
 
            if (uncle && uncle -> color == 0) // If the uncle exists and is RED (0), we have a case of red-red violation that can be resolved by recoloring
            {
                parent -> color = 1;
                uncle -> color = 1;
                grandparent -> color = 0; //
                node = grandparent;
            }
            else // If the uncle is BLACK (1) or does not exist, we have a case of red-red violation that requires rotations to fix
            {
                if (node == parent -> right)
                {
                    left_rotate(root, parent); // Perform a left rotation on the parent to convert the red-red violation into a case that can be fixed with a right rotation
                    node = parent;
                    parent = node -> parent;
                }
                right_rotate(root, grandparent); // Perform a right rotation on the grandparent to fix the red-red violation and restore the properties of the RB tree
                parent -> color = 1;
                grandparent -> color = 0;
            }
        }
        else // If the parent is a right child of the grandparent
        {
            tree_t *uncle = grandparent -> left;

            if (uncle && uncle -> color == 0)
            {
                parent -> color = 1;
                uncle -> color = 1;
                grandparent -> color = 0;
                node = grandparent;
            }
            else // If the uncle is BLACK (1) or does not exist, we have a case of red-red violation that requires rotations to fix
            {
                if (node == parent -> left)
                {
                    right_rotate(root, parent);
                    node = parent;
                    parent = node -> parent;
                }
                left_rotate(root, grandparent);
                parent -> color = 1;
                grandparent -> color = 0;
            }
        }
    }
    (*root) -> color = 1; // Ensure that the root of the tree is always BLACK (1) after fixing any violations
}

/* RB Delete Fixup */
void delete_fixup(tree_t **root, tree_t *x, tree_t *parent)
{
    tree_t *sibling; // Declare a pointer to the sibling of x

    while ((x != *root) && (x == NULL || x->color == 1))
    {
        if (parent == NULL) // If the parent is NULL, we have reached the root of the tree, so break out of the loop
            break;

        /* x is left child */
        if (x == parent->left)
        {
            sibling = parent->right;

            /* Case 1 : sibling RED */
            if (sibling != NULL && sibling->color == 0)
            {
                sibling->color = 1;
                parent->color = 0;

                left_rotate(root, parent);

                sibling = parent->right;
            }

            /* Case 2 : sibling BLACK and both children BLACK */
            if (sibling == NULL ||
               ((sibling->left == NULL || sibling->left->color == 1) &&
                (sibling->right == NULL || sibling->right->color == 1)))
            {
                if (sibling != NULL)
                    sibling->color = 0;

                x = parent;
                parent = x->parent;
            }
            else
            {
                /* Case 3 : sibling BLACK, inner RED child */
                if (sibling->right == NULL ||
                    sibling->right->color == 1)
                {
                    if (sibling->left != NULL)
                        sibling->left->color = 1;

                    sibling->color = 0;

                    right_rotate(root, sibling);

                    sibling = parent->right;
                }

                /* Case 4 : sibling BLACK, outer RED child */
                sibling->color = parent->color;
                parent->color = 1;

                if (sibling->right != NULL)
                    sibling->right->color = 1;

                left_rotate(root, parent);

                x = *root;
                break;
            }
        }

        /* x is right child */
        else
        {
            sibling = parent->left;

            /* Case 1 : sibling RED */
            if (sibling != NULL && sibling->color == 0)
            {
                sibling->color = 1;
                parent->color = 0;

                right_rotate(root, parent);

                sibling = parent->left;
            }

            /* Case 2 : sibling BLACK and both children BLACK */
            if (sibling == NULL ||
               ((sibling->left == NULL || sibling->left->color == 1) &&
                (sibling->right == NULL || sibling->right->color == 1)))
            {
                if (sibling != NULL)
                    sibling->color = 0;

                x = parent;
                parent = x->parent;
            }
            else
            {
                /* Case 3 : sibling BLACK, inner RED child */
                if (sibling->left == NULL ||
                    sibling->left->color == 1)
                {
                    if (sibling->right != NULL)
                        sibling->right->color = 1;

                    sibling->color = 0;

                    left_rotate(root, sibling);

                    sibling = parent->left;
                }

                /* Case 4 : sibling BLACK, outer RED child */
                sibling->color = parent->color;
                parent->color = 1;

                if (sibling->left != NULL)
                    sibling->left->color = 1;

                right_rotate(root, parent);

                x = *root;
                break;
            }
        }
    }

    if (x != NULL) // If x is not NULL, set its color to BLACK (1)
        x->color = 1;

    if (*root != NULL) // If the root is not NULL, set its color to BLACK (1) 
        (*root)->color = 1;
}