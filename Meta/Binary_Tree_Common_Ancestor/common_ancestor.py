
from binary_tree import Node
    

def solve(n1: Node, n2: Node)-> Node:
    n1_ancestors = set()
    while n1 != None:
        n1_ancestors.add(n1)
        n1 = n1.parent
    while n2 != None:
        if n2 in n1_ancestors:
            return n2
        n2 = n2.parent
    return None
