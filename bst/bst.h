/* TRADITIONAL IMPLEMENTATION */

#ifndef BST_H
#define BST_H

#include <time.h>

typedef int DATA;

typedef struct node {
    DATA data;
    struct node *left, *right;
} NODE;

extern int compare(NODE *n, DATA d);
extern void inorder(NODE *root);
extern void print_tree(NODE *root, int indent);
extern void print_pstree(NODE *root);
extern NODE *search(NODE *root, DATA d);
extern NODE *detach_successor(NODE *node);

#endif /* BST_H */
