#include "common.h"
#include "trie.h"

char inbuf[BUF_LEN << 20]; /* 256 MB */

int main(int ac, char **av)
{
    char *word;
    unsigned int i;
    unsigned long j;
    FILE *fp;

    if (ac < 2)
        ERR_MESG("Usage: make-trie <file1> ... ");
    if (UNDEF == init_trie())
        exit(1);

    for (i = 1; i < ac; i++) {
        if (NULL == (fp = fopen(av[i], "r")))
            ERR_MESG("make-trie: error opening text file\n");
        fprintf(stderr, "%s\n", av[i]);
        j = 0;
        while (NULL != fgets(inbuf, BUF_LEN - 1, fp)) {
            j++;
            if (strncmp(inbuf, "<text>", 6) == 0)
                if (NULL != fgets(inbuf, (BUF_LEN << 20) - 1, fp)) {
                    j++;
                    unsigned int l = strlen(inbuf);
                    if (inbuf[l-1] == '\n')
                        inbuf[l-1] = '\0';
                    else
                        fprintf(stderr, "File: %s, incomplete line %lu ends in %c\n", av[i], j, inbuf[l-1]);
                    
                    if (NULL != (word = strtok(inbuf, " ")))
                        if (UNDEF == insert_string(word))
                            return UNDEF;
                    // fprintf(stderr, "%s\n", word);
                    while (NULL != (word = strtok(NULL, " "))) {
                        if (UNDEF == insert_string(word))
                            return UNDEF;
                        // fprintf(stderr, "%s\n", word);
                    }
                }
        }
        fclose(fp);
    }

    trie_dfs();

    return 0;
}
