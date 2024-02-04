import unittest
import sample
from sample import ListNode

class TestReverseKGroup(unittest.TestCase):
    '''Unit test for sample reverseKGroup function.'''

    def get_list_node_vals(self, head: ListNode):
        current = head
        result = []
        while current != None:
            result.append(current.val)
            current = current.next
        return result
    
    def test_example_1(self):
        n1 = ListNode(val = 1)
        n2 = ListNode(val = 2)
        n3 = ListNode(val = 3)
        n4 = ListNode(val = 4)
        n5 = ListNode(val = 5)
        n1.next = n2
        n2.next = n3
        n3.next = n4
        n4.next = n5
        expected = [2, 1, 4, 3, 5]
        actual = self.get_list_node_vals(sample.Solution().reverseKGroup(n1, 2))
        self.assertEqual(actual, expected)

    def test_example_2(self):
        n1 = ListNode(val = 1)
        n2 = ListNode(val = 2)
        n3 = ListNode(val = 3)
        n4 = ListNode(val = 4)
        n5 = ListNode(val = 5)
        n1.next = n2
        n2.next = n3
        n3.next = n4
        n4.next = n5
        expected = [3, 2, 1, 4, 5]
        actual = self.get_list_node_vals(sample.Solution().reverseKGroup(n1, 3))
        self.assertEqual(actual, expected)

if __name__ == "__main__":
    unittest.main()
