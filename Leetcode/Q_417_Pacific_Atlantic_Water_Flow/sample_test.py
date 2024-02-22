import unittest
import sample

class TestPacificAtlantic(unittest.TestCase):
    '''Unit test for sample pacificAtlantic function.'''

    def test_example_1(self):
        heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
        expected = [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
        print(sample.Solution().pacificAtlantic(heights))
        self.assertCountEqual(sample.Solution().pacificAtlantic(heights), expected)

    def test_example_2(self):
        heights = [[1]]
        expected = [[0,0]]
        print(sample.Solution().pacificAtlantic(heights))
        self.assertCountEqual(sample.Solution().pacificAtlantic(heights), expected)

if __name__ == "__main__":
    unittest.main()
