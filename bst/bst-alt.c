#include "common.h"
#include "bst-alt.h"
#include <time.h>

void insert(TREE *tree, int *rootptr, int d) {
    int root = *rootptr, next;

    if (root == -1) {
        assert(tree->num_nodes < tree->max_nodes);
        next = tree->num_nodes++;
        tree->nodelist[next].data = d;
        tree->nodelist[next].left = tree->nodelist[next].right = -1;
        *rootptr = next;
    }

    if (d < tree->nodelist[root].data)
        insert(tree, &(tree->nodelist[root].left), d);
    else if (d > tree->nodelist[root].data)
        insert(tree, &(tree->nodelist[root].right), d);
    return;
}



int main(int ac, char *av[])
{
    int N, i;
    NODE *nodeptr;
    TREE tree;

    if (ac != 2)
        ERR_MESG("Usage: bst <number>");
    N = atoi(av[1]); // max. number of nodes

    /* Initialise tree */
    tree.num_nodes = 0;
    tree.max_nodes = N;
    tree.root = -1;
    tree.free_list = 0;
    if (NULL == (tree.nodelist = Malloc(N, NODE)))
        ERR_MESG("bst: out of memory");

    /* Insert nodes */
    srandom((int) time(NULL));
    for (i = 0; i < N; i++)
        insert(&tree, &(tree.root), random() % 1000);

    print_pstree(&tree, tree.root);
    printf("%u\n", tree.num_nodes);
    for (i = 0, nodeptr = tree.nodelist; i < tree.num_nodes; i++, nodeptr++)
        printf("%d %d %d\n", nodeptr->data,
#ifdef LINENUM
               (nodeptr->left > 0) ? nodeptr->left + 2 : nodeptr->left,
               (nodeptr->right > 0) ? nodeptr->right + 2 : nodeptr->right
#else
               nodeptr->left, nodeptr->right
#endif
            );

    return 0;
}
