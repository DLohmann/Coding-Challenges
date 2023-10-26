import unittest
import evaluate_reverse_polish_notation

class TestFizzbuzz(unittest.TestCase):
    '''Unit test for reverse Polish notation calculator.'''
    def test_example_1(self):
        self.assertEqual(evaluate_reverse_polish_notation.Solution().evalRPN(["2","1","+","3","*"]), 9)


if __name__ == "__main__":
    unittest.main()
