/* "ALTERNATE" FORTRAN-STYLE IMPLEMENTATION */

#ifndef BST_ALT_H
#define BST_ALT_H

#include <time.h>

typedef int DATA;

typedef struct node {
    DATA data;
    int left, right;
} NODE;

typedef struct {
    unsigned int num_nodes, max_nodes;
    int root, free_list;
    NODE *nodelist;
} TREE;

extern void inorder(TREE *, int root);
extern void print_pstree(TREE*, int root);
extern int search(TREE *, int root, DATA d);
extern int detach_successor(TREE *, int node);

#endif /* BST_ALT_H */
