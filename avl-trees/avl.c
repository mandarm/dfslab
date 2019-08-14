#include "common.h"
#include "avl.h"

int init_tree(TREE *tree) {
    int i;
    assert(tree != NULL);
    tree->num_nodes = 0;
    tree->max_nodes = MAX_NODES;
    if (NULL == (tree->nodelist = Malloc(tree->max_nodes, AVL_NODE)))
        ERR_MESG("init_tree: out of memory");
    tree->root = -1;
    tree->free_list = 0;
    for (i = 1; i < tree->max_nodes; i++) {
        tree->nodelist[i-1].left = i;
        tree->nodelist[i-1].right = -1;
    }
    tree->nodelist[i-1].left = -1;
    return 0;
}

int search(TREE *tree, int root, DATA d) {
    if (root == -1) 
        return -1;
    if (d < tree->nodelist[root].data) 
        return search(tree, tree->nodelist[root].left, d);
    else if (d > tree->nodelist[root].data)
        return search(tree, tree->nodelist[root].right, d);
    else 
        return root;
}

int insert(TREE *tree, int parent, int *root, DATA d) {
    int newnode, thisnode = *root;
    if (thisnode == -1) {
        /* INSERT HERE */
        if (FAILURE == (newnode = get_new_node(tree)))
            return FAILURE;
        tree->nodelist[newnode].data = d;
        tree->nodelist[newnode].left = -1;
        tree->nodelist[newnode].right = -1;
        tree->nodelist[newnode].parent = parent;
        tree->nodelist[newnode].height = 0;
        tree->num_nodes++;
        *root = newnode;
    }
    else if (d < tree->nodelist[thisnode].data &&
             FAILURE == insert(tree, thisnode, &(tree->nodelist[thisnode].left), d))
        return FAILURE;
    else if (d > tree->nodelist[thisnode].data &&
             FAILURE == insert(tree, thisnode, &(tree->nodelist[thisnode].right), d))
        return FAILURE;

    balance(tree, parent, root);
    return 0;
}

int delete(TREE *tree, int parent, int *root, DATA d) {
    int thisnode = *root;
    if (thisnode == -1)
        return 0;
    if (d < tree->nodelist[thisnode].data) {
#ifdef DEBUG
        printf("Deleting recursively from left subtree ");
        PRINT_NODE(tree, tree->nodelist[thisnode].left);
#endif        
        if (FAILURE == delete(tree, thisnode, &(tree->nodelist[thisnode].left), d))
            return FAILURE;
    }
    else if (d > tree->nodelist[thisnode].data) {
#ifdef DEBUG
        printf("Deleting recursively from right subtree ");
        PRINT_NODE(tree, tree->nodelist[thisnode].right);
#endif
        if (FAILURE == delete(tree, thisnode, &(tree->nodelist[thisnode].right), d))
            return FAILURE;
    }
    else {
        /* DELETE THIS NODE */
        if (tree->nodelist[thisnode].left != -1 &&
            tree->nodelist[thisnode].right != -1) {
            int successor = find_successor(tree, thisnode);
            assert(successor != -1);
            tree->nodelist[thisnode].data = tree->nodelist[successor].data;
#ifdef DEBUG
            printf("Replacing "); PRINT_NODE(tree, thisnode);
            printf(" by successor ");  PRINT_NODE(tree, thisnode);
#endif 
            if (FAILURE == delete(tree, thisnode, &(tree->nodelist[thisnode].right),
                                  tree->nodelist[successor].data))
                return FAILURE;
        }
        else {
            /* EITHER LEAF or ONLY ONE CHILD */
#ifdef DEBUG
            printf("Deleting "); PRINT_NODE(tree, thisnode);
#endif 
            if (tree->nodelist[thisnode].left != -1) {
                *root = tree->nodelist[thisnode].left;
                tree->nodelist[*root].parent = parent;
#ifdef DEBUG
            printf(" replacing by "); PRINT_NODE(tree, *root);
#endif 
            }
            else if (tree->nodelist[thisnode].right != -1) {
                *root = tree->nodelist[thisnode].right;
                tree->nodelist[*root].parent = parent;
#ifdef DEBUG
                printf(" replacing by "); PRINT_NODE(tree, *root);
#endif 
            }
            else {
#ifdef DEBUG
                printf(" (leaf)\n");
#endif 
                *root = -1;
            }
            free_up_node(tree, thisnode);
            tree->num_nodes--;
            if (parent != -1) {
                int left = tree->nodelist[parent].left;
                int right = tree->nodelist[parent].right;
                tree->nodelist[parent].height = 1 + 
                    MAX(HEIGHT(tree, left), HEIGHT(tree, right));
            }                    
        }
    }

    balance(tree, parent, root);
    return 0;
}
