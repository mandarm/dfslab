# All nodes of the tree are stored in a list.
# For a node, 'left' and 'right' store the indices of 
# the left and right child of that node.
# If a node has no left / right child, the corresponding 
# field is set to -1.

from random import *
import sys
import pickle

def generate_random_tree(tree, start_index, num_nodes) :
    left = randint(0,num_nodes-1)
    right = num_nodes - left - 1
    tree[start_index]['data'] = randint(1,10*num_nodes)
    if left > 0 :
        tree[start_index]['left'] = start_index + 1
        generate_random_tree(tree, start_index + 1, left)
    else :
        tree[start_index]['left'] = -1
    if right > 0 :
        tree[start_index]['right'] = start_index + left + 1
        generate_random_tree(tree, start_index + left + 1, right)
    else :
        tree[start_index]['right'] = -1
    return

def print_tree (tree, f) :
    N = len(tree)
    print(N, file=f)
    for i in range(N) :
        print(tree[i]['data'], tree[i]['left'], tree[i]['right'], file=f)
    return

def read_tree (filename) :
    with open(filename) as f : # with => don't need a f.close()
        for line in f:
            fields = list(map(int, line.split()))
            if len(fields) == 1 : # this is the first line
                N = int(fields[0])
                tree = [ {'data': None, 'left': None, 'right': None, 'parent': None}
                         for i in range(N) ]
                index = 0
            else :
                tree[index]['data'] = fields[0]
                tree[index]['left'] = fields[1]
                tree[index]['right'] = fields[2]
                index += 1
    return tree



if __name__ == '__main__':
    if len(sys.argv) != 3 :
        sys.exit('Usage: %s <number of nodes> <filename>' % sys.argv[0])

    N = int(sys.argv[1])
    tree = [ {'data': None, 'left': None, 'right': None, 'parent': None}
             for i in range(N) ]
    generate_random_tree(tree, 0, N)

    with open(sys.argv[2], "w") as f : # with => don't need a f.close()
        print_tree(tree, f)

    newtree = read_tree(sys.argv[2])
    # print_tree(newtree, sys.stdout)

    print(tree == newtree)

    # with open(sys.argv[2], "wb") as f : # with => don't need a f.close()
    #     pickle.dump(tree, f)
    
    # with open(sys.argv[2], "rb") as f : # with => don't need a f.close()
    #     newtree = pickle.load(f)

    # print(tree == newtree)
