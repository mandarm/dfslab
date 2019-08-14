#include "bst-alt.h"

void inorder(TREE *tree, int root) {
    if (root == -1)
        return;
    inorder(tree->nodelist[root].left);
    printf("%d ", tree->nodelist[root].data);
    inorder(tree->nodelist[root].right);
    return;
}

void print_pstree(TREE *tree, int root) {
    if (root != -1) {
        fprintf(stderr, "\\pstree{\\TCircle[radius=0.5]{%d}}{\n", tree->nodelist[root].data);
        print_pstree(tree, tree->nodelist[root].left);
        print_pstree(tree, tree->nodelist[root].right);
        fprintf(stderr, "}\n");
    }
    else
        fprintf(stderr, "\\pstree{\\Tn}{} \\pstree{\\Tn}{}");

    return;
}

int search(TREE *tree, int root, DATA d) {
    if (root == -1) 
        return -1;
    if (d < tree->nodelist[root].data) 
        return search(tree, tree->nodelist[root].left, d);
    else if (cmp > 0) 
        return search(tree, tree->nodelist[root].right, d);
    else 
        return root;
}

int detach_successor(TREE *tree, int node) {
    int child;
    assert(node != -1);
    /* Go to right child, then as far left as possible */
    child = tree->nodelist[node].right;
    if (child == -1) /* no successors */
        return -1;
    if (tree->nodelist[child].left == -1) {
        tree->nodelist[node].right = tree->nodelist[child].right;
        return child;
    }
    while (tree->nodelist[child].left != -1) {
        node = child;
        child = tree->nodelist[child].left;
    }
    tree->nodelist[node].left = tree->nodelist[child].right;
    return child;
}
