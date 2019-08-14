#include "common.h"
#include "trie.h"


int main(int ac, char **av)
{
    char inbuf[BUF_LEN];
    unsigned int i, j;
    FILE *fp;

    if (ac < 2)
        ERR_MESG("Usage: make-trie <dict file>");
    if (UNDEF == init_trie())
        exit(1);

    if (NULL == (fp = fopen(av[1], "r")))
        ERR_MESG("make-trie: error opening dict file\n");
    while (NULL != fgets(inbuf, BUF_LEN - 1, fp))
        if (UNDEF == insert_string(inbuf))
            return UNDEF;
    fclose(fp);

    if (NULL == (fp = fopen("dict.h", "w")))
        ERR_MESG("make-trie: error opening output file\n");
    fprintf(fp, "#include \"trie.h\"\n\nTRIE_NODE dict[] = {\n");
    for (i = 0; i < num_nodes; i++) {
        fprintf(fp, "    { ");
        for (j = 0; j < NUM_SYMS + 1; j++)
            fprintf(fp, "%lu, ", trie[i][j]);
        fprintf(fp, "},\n");
    }
    fprintf(fp,"};\n");
    fclose(fp);

    return 0;
}
