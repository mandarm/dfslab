#ifndef TRIE_H
#define TRIE_H

#define NUM_SYMS 26

typedef unsigned long int TRIE_NODE[NUM_SYMS + 1]; /* the last field stores how 
                                               * many times this string has
                                               * occurred as a complete word
                                               */

extern unsigned long max_nodes, num_nodes;
extern TRIE_NODE *trie;

extern int init_trie(), insert_node(), insert_string(), trie_dfs();

#endif // TRIE_H
