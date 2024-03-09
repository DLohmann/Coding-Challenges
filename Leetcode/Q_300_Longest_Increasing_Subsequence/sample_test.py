import unittest
import sample

class TestLengthOfLIS(unittest.TestCase):
    '''Should find the longest increasing subsequence. Find the length of the longest strictly increasing sequence which could by performing 0 or more deletions of elements in the array.'''

    def test_example_1(self):
        nums = [10,9,2,5,3,7,101,18]
        self.assertEqual(sample.Solution().lengthOfLIS(nums), 4)

    def test_example_2(self):
        nums = [0,1,0,3,2,3]
        self.assertEqual(sample.Solution().lengthOfLIS(nums), 4)
        
    def test_example_3(self):
        nums = [7,7,7,7,7,7,7]
        self.assertEqual(sample.Solution().lengthOfLIS(nums), 1)

if __name__ == "__main__":
    unittest.main()
