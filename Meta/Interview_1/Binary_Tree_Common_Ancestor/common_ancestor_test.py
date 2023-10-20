from binary_tree import Node
import common_ancestor
import unittest

class TestCommonAncestor(unittest.TestCase):
    def test_nodes(self):
        
        A = Node('A')
        B = Node('B', parent = A)
        C = Node('C', parent = A)
        D = Node('D', parent = B)
        E = Node('E', parent = B)
        F = Node('F', parent = C)
        G = Node('G', parent = C)
        H = Node('H', parent = D)
        I = Node('I', parent = F)

        A.left = B
        A.right = C
        B.left = D
        B.right = E
        D.left = H
        C.left = F
        C.right = G
        F.left = I

        self.assertEqual(common_ancestor.solve(D, E), B)
        self.assertEqual(common_ancestor.solve(H, I), A)
        self.assertEqual(common_ancestor.solve(E, G), A)
        self.assertEqual(common_ancestor.solve(None, None), None)
        self.assertEqual(common_ancestor.solve(F, None), None)
        self.assertEqual(common_ancestor.solve(None, F), None)
        self.assertEqual(common_ancestor.solve(G, A), A)

        
        
