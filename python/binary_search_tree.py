from binary_tree import *
from random import *
import sys

class BinarySearchTree(BinaryTree):
    # If no init is provided, the init inherited from the superclass'
    # will be called. Since that is all we're doing here, we don't
    # really need this __init__. 
    # NOTE: If we do provide an __init__, that init will not
    # automatically call super().__init__()
    def __init__(self, capacity):
        super().__init__(capacity)

    def search(self, start_index, d) :
        if start_index == -1 : return -1
        if d < self.nodelist[start_index].data :
            return self.search(self.nodelist[start_index].left, d)
        elif d > self.nodelist[start_index].data :
            return self.search(self.nodelist[start_index].right, d)
        else : return start_index

    def insert(self, start_index, d) :
        if start_index == -1 : # empty tree or have reached insertion point
            if self.capacity == self.num_nodes : # self.nodelist is full
                self.nodelist = self.nodelist + \
                    [ Node(0, -1, -1, -1) for i in range(capacity) ]
                self.capacity *= 2
            new_node_index = self.num_nodes
            self.nodelist[new_node_index].data = d
            self.num_nodes += 1
            return new_node_index

        current_value = self.nodelist[start_index].data
        if d < current_value :
            # insert recursively in left if less
            left = self.nodelist[start_index].left
            self.nodelist[start_index].left = self.insert(left, d)
        elif d > current_value :
            # insert recursively in right if more
            right = self.nodelist[start_index].right
            self.nodelist[start_index].right = self.insert(right, d)
        # ignore if present
        return start_index

    def detach_successor(self, start_index) :
        assert start_index != -1
        # Go to right child, then as far left as possible
        child = self.nodelist[start_index].right
        # If this function has been called, node has both children
        assert child != -1
 
        if self.nodelist[child].left == -1 :
            self.nodelist[start_index].right = self.nodelist[child].right
            return child

        while self.nodelist[child].left != -1 :
            current_node = child
            child = self.nodelist[child].left

        self.nodelist[current_node].left = self.nodelist[child].right
        return child

    def delete(self, start_index, d) :
        if start_index == -1 : # not found
            print(d, " not found")
            return None
        current_value = self.nodelist[start_index].data
        if d < current_value :
            # delete recursively from left if less
            # print("Deleting", d, " from left subtree")
            left = self.nodelist[start_index].left
            status = self.delete(left, d)
            if status != None : 
                self.nodelist[start_index].left = status
        elif d > current_value :
            # delete recursively from right if more
            # print("Deleting", d, " from right subtree")
            right = self.nodelist[start_index].right
            status = self.delete(right, d)
            if status != None : 
                self.nodelist[start_index].right = status
        else : # found it
            self.num_nodes -= 1
            print("Found", d)
            # Case I: value found at leaf node, just delete
            if self.nodelist[start_index].left == -1 and \
               self.nodelist[start_index].right == -1 :
                print("Deleting leaf node", d)
                return -1
            # Case II: only one child
            if self.nodelist[start_index].left == -1 :
                print("Deleted node has only one child")
                return self.nodelist[start_index].right
            if self.nodelist[start_index].right == -1 :
                print("Deleted node has only one child")
                return self.nodelist[start_index].left
            # Case III: both sub-trees present
            s = self.detach_successor(start_index)
            print("Successor:", self.nodelist[s].data)
            self.nodelist[start_index].data = self.nodelist[s].data
        return start_index

    def print_pstree(self, start_index, f):
        if start_index != -1 :
            print("\\pstree{\\TCircle[radius=0.5]{%d}}{\n" % self.nodelist[start_index].data, file=f)
            self.print_pstree(self.nodelist[start_index].left, f)
            self.print_pstree(self.nodelist[start_index].right, f)
            print("}\n", file=f)
        else :
            print("\\pstree{\\Tn}{} \\pstree{\\Tn}{}", file=f)

#---------------------------------------------------------------------------#

if __name__ == '__main__':
    if len(sys.argv) != 2 :
        sys.exit('Usage: %s <number>' % sys.argv[0])

    N = int(sys.argv[1])
    bt = BinarySearchTree(N)
    # data = [ randint(1, 100) for i in range(N) ]
    data = [79, 61, 68, 31, 55]
    print("Data:", data)
    for i in range(N) : 
        bt.root = bt.insert(bt.root, data[i])

    # print("Initial tree: ")
    # bt.print_tree(sys.stdout)

    # print(bt.inorder(bt.root))
    print(bt.search(0, 31))

    for i in range(N) :
        j = randint(0,N-1)
        if data[j] != -1 :
            print("Deleting", data[j])
            bt.root = bt.delete(bt.root, data[j])
            print("After deleting %d:" % data[j], end = " ")
            print(bt.inorder(bt.root))
            data[j] = -1
