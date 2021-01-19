import sys

class Node():
    """
    A single node in a binary tree.
    Attributes: data, left, right, parent.
    """

    def __init__(self, data, left, right, parent):
        self.data = data
        self.left = left
        self.right = right
        self.parent = parent

class BinaryTree():
    """
    Binary tree, with nodes stored in a list.
    left, right, parent attribute of each node contains the index in 
    the list of the left / right child / parent node.
    If a node has no left / right child, the corresponding field is 
    set to -1.
    """

    def __init__(self, capacity):
        self.capacity = capacity
        self.nodelist = [ Node(0, -1, -1, -1) for i in range(capacity) ]
        self.num_nodes = 0
        self.root = -1

    def read_tree (filename) :
        with open(filename) as f : # with => don't need a f.close()
            for line in f:
                fields = list(map(int, line.split()))
                if len(fields) == 1 : # this is the first line
                    N = int(fields[0])
                    tree = BinaryTree(N)
                    index = 0
                else :
                    tree.nodelist[index].data = fields[0]
                    tree.nodelist[index].left = fields[1]
                    tree.nodelist[index].right = fields[2]
                    index += 1
        tree.num_nodes = index
        tree.root = 0
        return tree

    def print_tree(self, f) :
        N = self.num_nodes
        print(N, file=f)
        for i in range(N) :
            print(self.nodelist[i].data, 
                  self.nodelist[i].left, self.nodelist[i].right, file=f) 
        return

    def preorder(self, start_index) :
        if start_index == -1: return []
        left = self.nodelist[start_index].left
        right = self.nodelist[start_index].right
        return [ self.nodelist[start_index].data ] + \
            self.preorder(left) + self.preorder(right)

    def inorder(self, start_index) :
        if start_index == -1: return []
        left = self.nodelist[start_index].left
        right = self.nodelist[start_index].right
        return self.inorder(left) + [ self.nodelist[start_index].data ] + self.inorder(right)

#---------------------------------------------------------------------------#

if __name__ == '__main__':
    if len(sys.argv) != 2 :
        sys.exit('Usage: %s <input tree>' % sys.argv[0])

    t = BinaryTree.read_tree(sys.argv[1])
    t.print_tree(sys.stdout)
    print(t.preorder(t.root))
