#ifndef AVL_H
#define AVL_H

#include <time.h>

#define MAX_NODES 100

typedef int DATA;

typedef struct node {
    DATA data;
    int left, right, parent, height; // following Weiss, DS & AA in C++, 4ed.
} AVL_NODE;

typedef struct {
    unsigned int num_nodes, max_nodes;
    int root, free_list;
    AVL_NODE *nodelist;
} TREE;


/* UTILITY FUNCTIONS */
extern int grow_tree(TREE *);
extern int get_new_node(TREE *);
extern void free_up_node(TREE *, int);
extern int find_successor(TREE *, int);
extern void rotate_on_insert_LL(TREE *, int , int *);
extern void rotate_on_insert_RR(TREE *, int , int *);
extern void rotate_on_insert_LR(TREE *, int , int *);
extern void rotate_on_insert_RL(TREE *, int , int *);
extern void balance(TREE *, int, int *);

extern void inorder(TREE *, int);
extern void print_tree(TREE *, int, int);
extern void print_pstree(TREE *, int);

#define HEIGHT(T, nodeindex) ( ((nodeindex) == -1) ? -1 : T->nodelist[nodeindex].height )
#define PRINT_NODE(T, nodeindex) { \
    if (nodeindex != -1) \
        printf("%d\n", T->nodelist[nodeindex].data); \
    }

/* API FUNCTIONS */
extern int init_tree(TREE *);
extern int search(TREE *, int , DATA);
extern int insert(TREE *, int , int *, DATA);
extern int delete(TREE *, int , int *, DATA);

#define DELETE_TREE(tree) free(tree->nodelist);

#endif /* AVL_H */
