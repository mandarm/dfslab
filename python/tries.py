#!/usr/bin/env ipython
# coding=utf-8

import sys

NUM_SYMBOLS = 26
INIT_SIZE = 10
max_nodes = INIT_SIZE
num_nodes = 1

def get_new_node(trie) :
    global num_nodes, max_nodes
    if num_nodes == max_nodes :
        trie.extend([ [ 0 ] * (NUM_SYMBOLS+1) for i in range(INIT_SIZE) ])
        max_nodes += INIT_SIZE
    num_nodes += 1
    return num_nodes - 1

def insert_string(trie, s) :
    index = 0
    for c in s.lower() :
        i = ord(c) - ord('a')    # get ASCII value
        if i < 0 or i >= NUM_SYMBOLS :
            # print("Unexpected character %c in string %s" % (c, s))
            continue
        if trie[index][i] == 0 : # need new node
            new_index = get_new_node(trie)
            trie[index][i] = new_index
            index = new_index
        else :
            index = trie[index][i]
    trie[index][NUM_SYMBOLS] += 1


if __name__ == '__main__': # can use code in this file via import (?)
    if len(sys.argv) != 2 : # == argc
        # Note the printf-like syntax below
        sys.exit('Usage: %s <dict file name>' % sys.argv[0]) 

    # CAUTION:
    # trie = [ [ 0 ] * (NUM_SYMBOLS+1) ] * INIT_SIZE WILL NOT WORK
    # The above creates copies of the SAME list, so when you modify 
    # one of them they all change.
    # See https://stackoverflow.com/questions/6667201/how-to-define-a-two-dimensional-array-in-python
    trie = [ [ 0 ] * (NUM_SYMBOLS+1) for i in range(INIT_SIZE) ]

    with open(sys.argv[1]) as f : # with => don't need a f.close()
        for line in f: # ASSUMPTION: one word per line
            insert_string(trie, line.strip())

    # As for C
    with open("dict.h", "w") as f :
        f.write("#include \"trie.h\"\n\nTRIE_NODE dict[] = {\n")
        for node in trie[:num_nodes] : 
            f.write("    { ")
            f.write(str(node).strip("[]") + ",") # Just to make comparison 
                                                 # with C output easy
            f.write("},\n")
        f.write("};\n")
