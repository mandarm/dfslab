#include "common.h"
#include "bst.h"

void insert(NODE **rootptr, DATA d) {
    NODE *root = *rootptr;
    if (root == NULL) {
        root = Malloc(1, NODE); /* check return value */
        root->data = d;
        root->left = root->right = NULL;
        *rootptr = root;
    }
    int cmp = compare(root, d);
    if (cmp < 0) insert(&(root->left), d);
    else if (cmp > 0) insert(&(root->right), d);
    return;
}

void delete(NODE **nodeptr, DATA d) {
    NODE *node, *s;

    assert(nodeptr != NULL);
    node = *nodeptr;
    if (node == NULL) return;

    int cmp = compare(node, d);
    if (cmp < 0) delete(&(node->left), d);
    else if (cmp > 0) delete(&(node->right), d);
    else {
        if (node->left == NULL &&
            node->right == NULL) {
            /* Case I: leaf, just delete */
            *nodeptr = NULL;
            free(node);
            return;
        }
        /* Case II: only one child */
        if (node->left == NULL) {
            *nodeptr = node->right;
            free(node);
            return;
        }
        if (node->right == NULL) {
            *nodeptr = node->left;
            free(node);
            return;
        }            
        /* Case III: both sub-trees present */
        s = detach_successor(node);
        node->data = s->data;
        free(s);
    }
    return;
}


int main(int ac, char *av[])
{
    int *data, num, i, j;
    NODE *root = NULL;

    if (ac != 2)
        ERR_MESG("Usage: bst <number>");
    srand((int) time(NULL));
    num = atoi(av[1]);
    if (NULL == (data = Malloc(num, int)))
        ERR_MESG("bst: out of memory");
    for (i = 0; i < num; i++) {
        data[i] = rand() % 100000;
        insert(&root, data[i]);
    }
    printf("Initial tree: ");
    inorder(root);
    printf("\n\n");

    for (i = 0; i < num; i++) {
        j = rand() % num;
        if (data[j] != -1) {
            printf("After deleting %d:\n", data[j]);
            delete(&root, data[j]);
            data[j] = -1;
            inorder(root);
            printf("\n\n");
        }
    }

    return 0;
}
