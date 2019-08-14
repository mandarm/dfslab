#include "common.h"
#include <stdlib.h>
#include <time.h>

typedef struct {
    /* All nodes of the tree are stored in an array.
     * For a node, 'left' and 'right' store the indices 
     * of the left and right child of that node.
     * If a node has no left / right child, the corresponding 
     * field is set to -1.
     */
    int value;
    int left, right;
} NODE;

#define MAX_VALUE 100

static void generate_random_tree(NODE *tree, unsigned int start_index, int N)
{
    unsigned int left, right;

    left = random() % N;
    right = N - left - 1;
    tree[start_index].value = random() % (10*N);
    if (left > 0) {
        tree[start_index].left = start_index + 1;
        generate_random_tree(tree, start_index + 1, left);
    }
    else
        tree[start_index].left = -1;
    if (right > 0) {
        tree[start_index].right = start_index + left + 1;
        generate_random_tree(tree, start_index + left + 1, right);
    }
    else
        tree[start_index].right = -1;
    return;
}

static void generate_random_bst(NODE *tree, unsigned int start_index, int N)
{
   return;
}

static void print_arity(NODE *tree, unsigned int root)
{
    NODE *node = tree + root;

    if (-1 == node->left && -1 == node->right) {
        putchar('0');
        return;
    }
    if (-1 == node->left) {
        putchar('1');
        print_arity(tree, node->right);
        return;
    }
    if (-1 == node->right) {
        putchar('1');
        print_arity(tree, node->left);
        return;
    }
    putchar('2');
    print_arity(tree, node->left);
    print_arity(tree, node->right);
    return;
}

int main(int ac, char *av[])
{
    unsigned int N, i;
    NODE *tree, *node;

    if (ac < 2)
        ERR_MESG("Usage: generate-random-tree number of nodes");
    N = atoi(av[1]);

    if (NULL == (tree = Malloc(N, NODE)))
        ERR_MESG("generate-random-tree: out of memory\n");

    srandom(time(NULL));
    generate_random_tree(tree, 0, N);
    printf("%u\n", N);
    for (node = tree, i = 0; i < N; node++, i++)
        printf("%d %d %d\n", node->value,
#ifdef LINENUM
               (node->left > 0) ? node->left + 2 : node->left,
               (node->right > 0) ? node->right +2 : node->right
#else
               node->left, node->right
#endif
            );
    // print_arity(tree, 0);
    putchar('\n');

    return 0;
}
