from binary_search_tree import *
from random import *
import sys

DEBUG = False
DDEBUG = True

class AVLNode() :
    """A single node in an AVL tree.
Attributes: as for binary tree Node, but with additional attribute height

Following Weiss, DS & AA in C++, 4ed., we store the height of the
subtree rooted at a node, rather than a balance factor.
"""
    def __init__(self, data, left, right, parent, height):
        self.data = data
        self.left = left
        self.right = right
        self.parent = parent
        self.height = height


class AVLTree(BinarySearchTree):

    def __init__(self, capacity):
        self.capacity = capacity
        self.nodelist = [ AVLNode(0, -1, -1, -1, -1) for i in range(capacity) ]
        self.num_nodes = 0
        self.root = -1


    # search, etc. - inherited as is from BinarySearchTree

    def height(self, nodeindex) :
        if nodeindex == -1 : return -1 
        else : return self.nodelist[nodeindex].height

    def print_node(self, nodeindex) :
        if nodeindex != -1 : print("%d" % self.nodelist[nodeindex].data, end = " ")

    def rotate_LL(self, parent, start_index) :
        # See Weiss, DS & AA in C++, 4 ed., Section 4.4.1, Figure 4.34
        if DEBUG :
            print("LL (right) rotation at %d\n" % self.nodelist[start_index].data)
        k2 = start_index
        k1 = self.nodelist[k2].left
        Z = self.nodelist[k2].right
        X = self.nodelist[k1].left
        Y = self.nodelist[k1].right

        # rotate
        self.nodelist[k2].left = Y
        self.nodelist[k1].right = k2

        # parents (optional)
        self.nodelist[k1].parent = parent
        self.nodelist[k2].parent = k1
        if Y != -1 : self.nodelist[Y].parent = k2

        # update heights
        self.nodelist[k2].height = 1 + max(self.height(Y), self.height(Z))
        self.nodelist[k1].height = 1 + max(self.height(X), self.height(k2))

        return k1


    def rotate_RR(self, parent, start_index) :
        # See Weiss, DS & AA in C++, 4 ed., Section 4.4.1, Figure 4.36
        if DEBUG :
            print("RR (left) rotation at %d\n" % self.nodelist[start_index].data)
        k1 = start_index
        X = self.nodelist[k1].left
        k2 = self.nodelist[k1].right
        Y = self.nodelist[k2].left
        Z = self.nodelist[k2].right

        # rotate
        self.nodelist[k1].right = Y
        self.nodelist[k2].left = k1

        self.nodelist[k2].parent = parent
        self.nodelist[k1].parent = k2
        if Y != -1 : self.nodelist[Y].parent = k1

        # update heights
        self.nodelist[k1].height = 1 + max(self.height(X), self.height(Y))
        self.nodelist[k2].height = 1 + max(self.height(k1), self.height(Z))

        return k2


    def rotate_LR(self, parent, start_index) :
        # See CMSC 420 Lecture Notes by David M. Mount, UMCP, pg. 39.
        if DEBUG :
            print("LR (double) rotation at %d\n" % self.nodelist[start_index].data)
        k1 = start_index
        self.nodelist[k1].right = self.rotate_LL(k1, self.nodelist[k1].right)
        return self.rotate_RR(parent, start_index)


    def rotate_RL(self, parent, start_index) :
        # See Weiss, DS & AA in C++, 4 ed., Section 4.4.2, Figure 4.38
        if DEBUG :
            print("RL (double) rotation at %d\n" % self.nodelist[start_index].data)
        k3 = start_index
        k1 = self.nodelist[k3].left
        D = self.nodelist[k3].right
        A = self.nodelist[k1].left
        k2 = self.nodelist[k1].right
        B = self.nodelist[k2].left
        C = self.nodelist[k2].right

        # rotate
        self.nodelist[k2].left = k1
        self.nodelist[k2].right = k3
        self.nodelist[k1].right = B
        self.nodelist[k3].left = C

        # update parent index of affected nodes
        self.nodelist[k3].parent = k2
        self.nodelist[k1].parent = k2
        self.nodelist[B].parent = k1
        self.nodelist[C].parent = k3

        # update heights
        self.nodelist[k1].height = 1 + max(self.height(A), self.height(B))
        self.nodelist[k3].height = 1 + max(self.height(C), self.height(D))
        self.nodelist[k2].height = 1 + max(self.height(k1), self.height(k3))

        return k2


    def balance(self, parent, start_index) :
        thisnode = start_index
        left = self.nodelist[thisnode].left
        right = self.nodelist[thisnode].right

        if self.height(left) - self.height(right) > 1 :
            if DEBUG :
                print("Left sub-tree too high at %d\n" % self.nodelist[thisnode].data)

            if self.height(self.nodelist[left].left) >= self.height(self.nodelist[left].right) :
                return self.rotate_LL(parent, start_index)
            else :
                return self.rotate_RL(parent, start_index)

        elif self.height(right) - self.height(left) > 1 :
            if DEBUG :
                print("Right sub-tree too high at %d\n" % self.nodelist[thisnode].data)
            if self.height(self.nodelist[right].right) >= self.height(self.nodelist[right].left) :
                return self.rotate_RR(parent, start_index)
            else :
                return self.rotate_LR(parent, start_index)
        return start_index


    def insert(self, parent_index, start_index, d) :
        if start_index == -1 : # empty tree or have reached insertion point
            if self.capacity == self.num_nodes : # self.nodelist is full
                self.nodelist = self.nodelist + \
                    [ Node(0, -1, -1, -1) for i in range(capacity) ]
                self.capacity *= 2
            new_node_index = self.num_nodes
            self.nodelist[new_node_index].data = d
            self.nodelist[new_node_index].parent = parent_index
            self.nodelist[new_node_index].height = 0
            self.num_nodes += 1
            return new_node_index
        else:
            current_value = self.nodelist[start_index].data
            if d < current_value :
                # insert recursively in left if less
                left = self.nodelist[start_index].left
                self.nodelist[start_index].left = self.insert(start_index, left, d)
            elif d > current_value :
                # insert recursively in right if more
                right = self.nodelist[start_index].right
                self.nodelist[start_index].right = self.insert(start_index, right, d)
                # ignore if present

        # Re-balance and update height
        start_index = self.balance(parent_index, start_index)
        left = self.nodelist[start_index].left
        right = self.nodelist[start_index].right
        self.nodelist[start_index].height = 1 + \
            max(self.height(left), self.height(right))
        return start_index


    def find_successor(self, start_index) :
        assert start_index != -1
        # Go to right child, then as far left as possible
        child = self.nodelist[start_index].right
        # If this function has been called, node has both children
        assert child != -1
 
        if self.nodelist[child].left == -1 :
            # For AVL trees, don't do the actual deletion
            # self.nodelist[start_index].right = self.nodelist[child].right
            return child

        while self.nodelist[child].left != -1 :
            current_node = child
            child = self.nodelist[child].left

        # For AVL trees, don't do the actual deletion
        # self.nodelist[current_node].left = self.nodelist[child].right
        return child

    def delete(self, parent, start_index, d) :
        thisnode = start_index
        if thisnode == -1 :
            return thisnode
        if d < self.nodelist[thisnode].data :
            if DDEBUG :
                print("Deleting %d recursively from left subtree of %d" %
                      (d, self.nodelist[thisnode].data))
            self.nodelist[thisnode].left = self.delete(thisnode, self.nodelist[thisnode].left, d)    
        elif d > self.nodelist[thisnode].data :
            if DDEBUG :
                print("Deleting %d recursively from right subtree of %d" %
                      (d, self.nodelist[thisnode].data))
            self.nodelist[thisnode].right = self.delete(thisnode, self.nodelist[thisnode].right, d)
        else :
            # DELETE THIS NODE
            if (self.nodelist[thisnode].left != -1 and 
                self.nodelist[thisnode].right != -1) :
                successor = self.find_successor(thisnode)
                assert(successor != -1)
                if DDEBUG :
                    print("Replacing", end=" ") ; self.print_node(thisnode)
                    print("by successor", end=" ") ; self.print_node(successor)
                    print()
                self.nodelist[thisnode].data = self.nodelist[successor].data
                self.nodelist[thisnode].right = self.delete(thisnode, self.nodelist[thisnode].right, self.nodelist[successor].data)
            else :
                # EITHER LEAF or ONLY ONE CHILD
                if DDEBUG :
                    print("Deleting", end=" ") ; self.print_node(thisnode)
                    print("\n")
                if self.nodelist[thisnode].left != -1 :
                    thisnode = self.nodelist[thisnode].left
                    self.nodelist[thisnode].parent = parent
                elif self.nodelist[thisnode].right != -1 :
                    thisnode = self.nodelist[thisnode].right
                    self.nodelist[thisnode].parent = parent
                else :
                    thisnode = -1

            self.num_nodes -= 1
            return thisnode

        # Deletion done, now rebalance and update height
        start_index = self.balance(parent, start_index)
        left = self.nodelist[start_index].left
        right = self.nodelist[start_index].right
        self.nodelist[start_index].height = 1 + \
            max(self.height(left), self.height(right))
        return start_index


    def print_pstree(self, root) :
        if root != -1 :
            print("\\pstree{\\TCircle[radius=1.0]{%d,%d}}{\n" %
                  (self.nodelist[root].data, self.nodelist[root].height),
                  file=sys.stderr)
            self.print_pstree(self.nodelist[root].left)
            self.print_pstree(self.nodelist[root].right)
            print("}\n\n", file=sys.stderr)
        else :
            print("\\pstree{\\Tn}{} \\pstree{\\Tn}{}", file=sys.stderr)
        return



#---------------------------------------------------------------------------#

if __name__ == '__main__':
    if len(sys.argv) != 2 :
        sys.exit('Usage: %s <number>' % sys.argv[0])

    data = [3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9]
    N = len(data)
    bt = AVLTree(N)
    print("Data:", data)

    for i in range(N) :
        # print("Inserting %d\n" % data[i])
        bt.root = bt.insert(-1, bt.root, data[i])
        print("\\begin{sideways}\n", file=sys.stderr)
        bt.print_pstree(bt.root)
        print("\\end{sideways}\n\\newpage\n", file=sys.stderr)

    print(bt.inorder(bt.root))

    print(bt.search(bt.root, 14))

    for i in range(N) :
        print("Deleting %d\n" % data[i])
        bt.root = bt.delete(-1, bt.root, data[i])
        print("\\begin{sideways}\n", file=sys.stderr)
        bt.print_pstree(bt.root)
        print("\\end{sideways}\n\\newpage\n", file=sys.stderr)
