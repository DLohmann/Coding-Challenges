import unittest
import sample

class TestLongestIncreasingPath(unittest.TestCase):
    '''Test cases from example 1 and example 2 in leetcode description.'''

    def test_Example_1(self):
        self.assertEqual(
            sample.Solution().longestIncreasingPath(
                matrix = [
                    [9,9,4],
                    [6,6,8],
                    [2,1,1]
                    ]),
            4)

    def test_Example_2(self):
        self.assertEqual(
            sample.Solution().longestIncreasingPath(
                matrix = [
                    [3,4,5],
                    [3,2,6],
                    [2,2,1]
                    ]),
            4)

if __name__ == "__main__":
    unittest.main()
