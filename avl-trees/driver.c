#include "common.h"
#include "avl.h"


int main(int ac, char *av[])
{
    int i;
    TREE t;

    init_tree(&t);
    for (i = 1; i < ac; i++) {
        printf("Inserting %d\n", atoi(av[i]));
        if (FAILURE == insert(&t, -1, &(t.root), atoi(av[i])))
            return FAILURE;
        fprintf(stderr, "\\begin{sideways}\n");
        print_pstree(&t, t.root);
        fprintf(stderr, "\\end{sideways}\n\\newpage\n");
    }

    for (i = 1; i < ac; i++) {
        printf("Starting deletion %d\n", atoi(av[i]));
        if (FAILURE == delete(&t, -1, &(t.root), atoi(av[i])))
            return FAILURE;
        fprintf(stderr, "\\begin{sideways}\n");
        print_pstree(&t, t.root);
        fprintf(stderr, "\\end{sideways}\n\\newpage\n");
    }
        
    return 0;
}
