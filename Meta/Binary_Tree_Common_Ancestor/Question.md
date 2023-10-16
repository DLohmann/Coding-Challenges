# This question was from a Meta interview on 10/16/2023:

Given 2 nodes in the same binary tree, find their common ancestor.

Nodes are as such:
```python
class Node:
    def __init__(self):
        self.name = ''
        self.left = None
        self.right = None
```
```

          A
       /     \
      B       C
    /   \   /   \
   D     E F     G
 /        /
H        I

common_ancestor(D, E) -> B
common_ancestor(H, I) -> A

```

To run:
```bash
python3 -m unittest _____.py
```
