#ifndef RBT_H
#define RBT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SUCCESS 0
#define FAILURE -1

typedef int data_t;

typedef struct node
{
	data_t data;
	struct node *left;
	struct node *right;
	struct node *parent;
	char color;
}tree_t;

/* keep all the prototypes of the functions here */
data_t insert(tree_t **root, data_t item);
tree_t* find_minimum(tree_t *root);
tree_t* find_maximum(tree_t *root);
data_t delete(tree_t **root, data_t item);
data_t delete_minimum(tree_t **root);
data_t delete_maximum(tree_t **root);
tree_t* search(tree_t *root, data_t key);

tree_t* bst_insert(tree_t *root, tree_t *node, char *dup);
void left_rotate(tree_t **root, tree_t *x);
void right_rotate(tree_t **root, tree_t *x);
void fix_violation(tree_t **root, tree_t *node);
void inorder(tree_t *root);
// void delete_fixup(tree_t **root, tree_t *x);
void delete_fixup(tree_t **root, tree_t *x, tree_t *parent);

#endif
