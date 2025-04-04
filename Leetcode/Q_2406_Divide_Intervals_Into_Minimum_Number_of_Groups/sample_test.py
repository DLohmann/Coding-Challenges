import unittest
import sample

class TestMinGroups(unittest.TestCase):
    '''Unit test for sample minGroups function.'''

    def test_example_1(self):
        self.assertEqual(
            sample.Solution().minGroups(
                intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
            ),
            3
        )


    def test_example_2(self):
        self.assertEqual(
            sample.Solution().minGroups(
                intervals = [[1,3],[5,6],[8,10],[11,13]]
            ),
            3
        )


    def test_example_11(self):
        self.assertEqual(
            sample.Solution().minGroups(
                intervals = [[441459,446342],[801308,840640],[871890,963447],[228525,336985],[807945,946787],[479815,507766],[693292,944029],[751962,821744]]
            ),
            4
        )


if __name__ == "__main__":
    unittest.main()
