#include "common.h"
#include "bst.h"

/**
 * Arguments: pointer to root, data
 * Returns: possibly modified pointer to root
 * If "root" is NULL (empty tree), it will be changed to point to 
 *     newly inserted node.
 * This (possibly changed) value of root is returned.
 * Caller is responsible for updating to the new, returned value (see 
 * recursive calls below, for example).
 */
NODE *insert(NODE *root, DATA d) {
    /* Base case */
    if (root == NULL) {
        root = Malloc(1, NODE); /* should check return value */
        root->data = d;
        root->left = root->right = NULL;
        return root;
    }
    /* Recurse */
    int cmp = compare(root, d);
    if (cmp < 0) 
        root->left = insert(root->left, d);
    else if (cmp > 0) 
        root->right = insert(root->right, d);
    return root;
}

NODE *delete(NODE *root, DATA d) {
    NODE *s;

    if (root == NULL) return NULL;

    int cmp = compare(root, d);
    if (cmp < 0)
        root->left = delete(root->left, d);
    else if (cmp > 0)
        root->right = delete(root->right, d);
    else {
        if (root->left == NULL &&
            root->right == NULL) {
            /* Case I: leaf, just delete */
            free(root);
            return NULL;
        }
        /* Case II: only one child */
        if (root->left == NULL) {
            s = root->right;
            free(root);
            return s;
        }
        if (root->right == NULL) {
            s = root->left;
            free(root);
            return s;
        }            
        /* Case III: both sub-trees present */
        s = detach_successor(root);
        root->data = s->data;
        free(s);
        return root;
    }

    return root;
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
        root = insert(root, data[i]);
        fprintf(stderr, "After inserting %d\n", data[i]);
        print_pstree(root);
        fprintf(stderr, "\n\n");
    }
    inorder(root);
    printf("\n\n");

    for (i = 0; i < num; i++) {
        j = rand() % num;
        if (data[j] != -1) {
            root = delete(root, data[j]);
            data[j] = -1;
            fprintf(stderr, "After deleting %d:\n", data[j]);
            print_pstree(root);
            fprintf(stderr, "\n\n");
        }
    }

    return 0;
}
