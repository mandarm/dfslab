#include "common.h"
#include "avl.h"

int grow_tree(TREE *tree) {
    int i;
    assert(tree != NULL &&
           tree->num_nodes == tree->max_nodes &&
           tree->free_list == -1);
    tree->max_nodes *= 2;
    if (NULL == (tree->nodelist = Realloc(tree->nodelist, tree->max_nodes, AVL_NODE)))
        ERR_MESG("grow_tree: out of memory");
    tree->free_list = tree->num_nodes;
    for (i = tree->num_nodes+1; i < tree->max_nodes; i++) {
        tree->nodelist[i-1].left = i;
        /* tree->nodelist[i-1].right = tree->nodelist[i-1].parent = -1; */
        /* tree->nodelist[i-1].height = 0; */
    }
    tree->nodelist[i-1].left = -1;
    return 0;
}

int get_new_node(TREE *tree) {
    int newnode;
    if (tree->free_list == -1 &&
        FAILURE == grow_tree(tree))
        return FAILURE;
    newnode = tree->free_list;
    tree->free_list = tree->nodelist[tree->free_list].left;
    return newnode;
}

void free_up_node(TREE *tree, int index) {
    tree->nodelist[index].left = tree->free_list;
    /* tree->nodelist[index].right = tree->nodelist[index].parent = -1; */
    /* tree->nodelist[index].height = 0; */
    tree->free_list = index;
    return;
}

int find_successor(TREE *tree, int node) {
    int child;
    assert(node != -1);
    /* Go to right child, then as far left as possible */
    child = tree->nodelist[node].right;
    if (child == -1) /* no successors */
        return -1;
    if (tree->nodelist[child].left == -1) {
        /* Don't do this here for AVL trees */
        /* tree->nodelist[node].right = tree->nodelist[child].right; */
        /* if (tree->nodelist[child].right != -1) */
        /*     tree->nodelist[tree->nodelist[child].right].parent = node; */
        return child;
    }
    while (tree->nodelist[child].left != -1) {
        node = child;
        child = tree->nodelist[child].left;
    }
    /* Don't do this here for AVL trees */
    /* tree->nodelist[node].left = tree->nodelist[child].right; */
    /* if (tree->nodelist[child].right != -1) */
    /*     tree->nodelist[tree->nodelist[child].right].parent = node; */
    return child;
}

void rotate_on_insert_LL(TREE *tree, int parent, int *node) {
    /* See Weiss, DS & AA in C++, 4 ed., Section 4.4.1, Figure 4.34 */
#ifdef DEBUG
        printf("LL (right) rotation at %d\n", tree->nodelist[*node].data);
#endif // DEBUG
    int k2 = *node;
    int k1 = tree->nodelist[k2].left;
    int Z = tree->nodelist[k2].right;
    int X = tree->nodelist[k1].left;
    int Y = tree->nodelist[k1].right;

    /* rotate */
    tree->nodelist[k2].left = Y;
    tree->nodelist[k1].right = k2;

    /* parents (optional) */
    tree->nodelist[k1].parent = parent;
    tree->nodelist[k2].parent = k1;
    if (Y != -1) tree->nodelist[Y].parent = k2;

    /* update heights */
    tree->nodelist[k2].height = 1 + MAX(HEIGHT(tree, Y), HEIGHT(tree, Z));
    tree->nodelist[k1].height = 1 + MAX(HEIGHT(tree, X), HEIGHT(tree, k2));

    *node = k1;
    return;
}

void rotate_on_insert_RR(TREE *tree, int parent, int *node) {
    /* See Weiss, DS & AA in C++, 4 ed., Section 4.4.1, Figure 4.36 */
#ifdef DEBUG
        printf("RR (left) rotation at %d\n", tree->nodelist[*node].data);
#endif // DEBUG
    int k1 = *node;
    int X = tree->nodelist[k1].left;
    int k2 = tree->nodelist[k1].right;
    int Y = tree->nodelist[k2].left;
    int Z = tree->nodelist[k2].right;

    /* rotate */
    tree->nodelist[k1].right = Y;
    tree->nodelist[k2].left = k1;

    tree->nodelist[k2].parent = parent;
    tree->nodelist[k1].parent = k2;
    if (Y != -1) tree->nodelist[Y].parent = k1;

    /* update heights */
    tree->nodelist[k1].height = 1 + MAX(HEIGHT(tree, X), HEIGHT(tree, Y));
    tree->nodelist[k2].height = 1 + MAX(HEIGHT(tree, k1), HEIGHT(tree, Z));

    *node = k2;
    return;
}

void rotate_on_insert_LR(TREE *tree, int parent, int *node) {
    /* See Weiss, DS & AA in C++, 4 ed., Section 4.4.2, Figure 4.38 */
#ifdef DEBUG
        printf("LR (double) rotation at %d\n", tree->nodelist[*node].data);
#endif // DEBUG
    int k3 = *node;
    int k1 = tree->nodelist[k3].left;
    int D = tree->nodelist[k3].right;
    int A = tree->nodelist[k1].left;
    int k2 = tree->nodelist[k1].right;
    int B = tree->nodelist[k2].left;
    int C = tree->nodelist[k2].right;

    /* rotate */
    tree->nodelist[k2].left = k1;
    tree->nodelist[k2].right = k3;
    tree->nodelist[k1].right = B;
    tree->nodelist[k3].left = C;

    /* TODO: update parent index of affected nodes */

    /* update heights */
    tree->nodelist[k1].height = 1 + MAX(HEIGHT(tree, A), HEIGHT(tree, B));
    tree->nodelist[k3].height = 1 + MAX(HEIGHT(tree, C), HEIGHT(tree, D));
    tree->nodelist[k2].height = 1 + MAX(HEIGHT(tree, k1), HEIGHT(tree, k3));

    *node = k2;
    return;
}

void rotate_on_insert_RL(TREE *tree, int parent, int *node) {
    /* See CMSC 420 Lecture Notes by David M. Mount, UMCP, pg. 39. */
#ifdef DEBUG
        printf("RL (double) rotation at %d\n", tree->nodelist[*node].data);
#endif // DEBUG
    int k1 = *node;
    rotate_on_insert_LL(tree, k1, &(tree->nodelist[k1].right));
    rotate_on_insert_RR(tree, parent, node);
    return;
}

void balance(TREE *tree, int parent, int *node) {
    int thisnode = *node;
    int left = tree->nodelist[thisnode].left;
    int right = tree->nodelist[thisnode].right;

    if (HEIGHT(tree, left) - HEIGHT(tree, right) > 1) {
#ifdef DEBUG
        printf("Left sub-tree too high at %d\n", tree->nodelist[thisnode].data);
#endif // DEBUG

        if (HEIGHT(tree, tree->nodelist[left].left) >= HEIGHT(tree, tree->nodelist[left].right))
            rotate_on_insert_LL(tree, parent, node);
        else
            rotate_on_insert_LR(tree, parent, node);
    }
    else if (HEIGHT(tree, right) - HEIGHT(tree, left) > 1) {
#ifdef DEBUG
        printf("Right sub-tree too high at %d\n", tree->nodelist[thisnode].data);
#endif // DEBUG
        if (HEIGHT(tree, tree->nodelist[right].right) >= HEIGHT(tree, tree->nodelist[right].left))
            rotate_on_insert_RR(tree, parent, node);
        else
            rotate_on_insert_RL(tree, parent, node);
    }

    thisnode = *node;
    left = tree->nodelist[thisnode].left;
    right = tree->nodelist[thisnode].right;
    tree->nodelist[thisnode].height = 1 +
        MAX(HEIGHT(tree, left), HEIGHT(tree, right));
    return;
}

void inorder(TREE *tree, int root) {
    if (root == -1)
        return;
    inorder(tree, tree->nodelist[root].left);
    printf("%d ", tree->nodelist[root].data);
    inorder(tree, tree->nodelist[root].right);
    return;
}

#if 0
void print_tree(TREE *tree, int root, int indent) {
    int i;
    if (root == -1)
        return;
    if (tree->nodelist[root].left != -1) {
        print_tree(tree, tree->nodelist[root].left, indent + 1);
        for (i = 0; i < indent; i++)
            printf("    ");
        printf("|\n");
    }
    for (i = 0; i < indent-1; i++)
        printf("    ");
    if (indent > 0) printf("--- ");
    printf("%d\n", tree->nodelist[root].data);
    if (tree->nodelist[root].right != -1) {
        for (i = 0; i < indent; i++)
            printf("    ");
        printf("|\n");
        print_tree(tree, tree->nodelist[root].right, indent + 1);
    }
    return;
}
#endif

void print_pstree(TREE *tree, int root) {
    if (root != -1) {
        fprintf(stderr, "\\pstree{\\TCircle[radius=1.0]{%d,%d}}{\n",
                tree->nodelist[root].data, tree->nodelist[root].height);
        print_pstree(tree, tree->nodelist[root].left);
        print_pstree(tree, tree->nodelist[root].right);
        fprintf(stderr, "}\n\n");
    }
    else
        fprintf(stderr, "\\pstree{\\Tn}{} \\pstree{\\Tn}{}");

    return;
}
