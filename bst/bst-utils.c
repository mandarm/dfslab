#include "common.h"
#include "bst.h"

int compare(NODE *n, DATA d)
{
    assert(n != NULL);
    return d - n->data;
}

void inorder(NODE *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
    return;
}

void print_tree(NODE *root, int indent) {
    int i;
    if (root == NULL)
        return;
    print_tree(root->left, indent + 1);
    putchar('\n');
    for (i = 0; i < indent; i++)
        putchar('\t');
    printf("%d\n", root->data);
    putchar('\n');
    print_tree(root->right, indent + 1);
    return;
}

void print_pstree(NODE *root) {
    if (root != NULL) {
        fprintf(stderr, "\\pstree{\\TCircle[radius=0.5]{%d}}{\n", root->data);
        print_pstree(root->left);
        print_pstree(root->right);
        fprintf(stderr, "}\n");
    }
    else
        fprintf(stderr, "\\pstree{\\Tn}{} \\pstree{\\Tn}{}");
    return;
}

NODE *search(NODE *root, DATA d) {
    if (root == NULL) 
        return NULL;
    int cmp = compare(root, d);
    if (cmp < 0) 
        return search(root->left, d);
    else if (cmp > 0) 
        return search(root->right, d);
    else 
        return root;
}

NODE *detach_successor(NODE *node) {
    NODE *nptr;
    assert(node != NULL);
    /* Go to right child, then as far left as possible */
    nptr = node->right;
    if (nptr == NULL) /* no successors */
        return NULL;
    if (nptr->left == NULL) {
        node->right = nptr->right;
        return nptr;
    }
    while (nptr->left != NULL) {
        node = nptr;
        nptr = nptr->left;
    }
    node->left = nptr->right;
    return nptr;
}
