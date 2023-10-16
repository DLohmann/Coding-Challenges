
class Node:
    def __init__(self, name: str = '', left = None, right = None, parent = None):
        self.name = name
        self.left = left
        self.right = right
        self.parent = parent
    
    def __eq__(self, __value: object) -> bool:
        return self is __value
    
    def __hash__(self) -> int:
        return id(self)
