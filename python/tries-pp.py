#!/usr/bin/env ipython
# coding=utf-8

import pickle
import sys

def insert_string(trie, s) :
    current_node = trie
    for c in s.lower() :
        if c not in current_node : # c is not a key in this dictionary
            new_node = {}
            current_node[c] = new_node
            current_node = new_node
        else :
            current_node = current_node[c]
    current_node['flag'] = True

def search(trie, s) :
    current_node = trie
    for c in s.lower() :
        if c not in current_node :
            return False
        else :
            current_node = current_node[c]
    return 'flag' in current_node and ['flag'] # guard condition


if __name__ == '__main__':
    if len(sys.argv) != 2 :
        sys.exit('Usage: %s <dict file name>' % sys.argv[0])

    trie = { } # Just the first node

    with open(sys.argv[1]) as f : # with => don't need a f.close()
        for line in f: # ASSUMPTION: one word per line
            insert_string(trie, line.strip())
            # print("After inserting %s: %s" % (line, trie))

    # Exercise: how do we save this in a persistent structure?
    with open("dict.pickle", "wb") as f : # wb = write binary (non-ASCII) file
        pickle.dump(trie, f)
    with open("dict.pickle", "rb") as f : # rb = read binary (non-ASCII) file
        unpickled_trie = pickle.load(f)

    while True:
        s = input("Enter word to search for: ")
        if s == "quit" : # Why can you not use "is" ?
            break
        if search(unpickled_trie, s) :
            print("Word found")
        else :
            print("Word not found")
