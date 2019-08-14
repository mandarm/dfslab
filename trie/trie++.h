#ifndef TRIEPP_H
#define TRIEPP_H

#include "avl.h"
#include "trie.h"

typedef struct {
    AVL_TREE alphabet;
    int count;
} TRIE_NODE;

typedef struct {
    unsigned long max_nodes, num_nodes;
    TRIE_NODE *trie;
} TRIEPP;

#endif // TRIEPP_H
