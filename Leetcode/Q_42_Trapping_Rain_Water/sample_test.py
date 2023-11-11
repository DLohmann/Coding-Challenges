import unittest
import sample

class TestTrap(unittest.TestCase):
    '''Unit test for sample trap function.'''
    def test_example_1(self):
        self.assertEqual(sample.Solution().trap(height = [0,1,0,2,1,0,1,3,2,1,2,1]), 6)
    
    def test_example_2(self):
        self.assertEqual(sample.Solution().trap(height = [4,2,0,3,2,5]), 9)

    def test_corner_case_1(self):
        self.assertEqual(sample.Solution().trap(height = [6,8,5,0,0,6,5]), 13)

if __name__ == "__main__":
    unittest.main()
