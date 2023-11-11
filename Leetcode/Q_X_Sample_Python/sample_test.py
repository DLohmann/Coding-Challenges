import unittest
import sample

class TestFizzbuzz(unittest.TestCase):
    '''Unit test for sample fizzbuzz function.'''
    def test_100(self):
        self.assertEqual(sample.Solution().fizzbuzz(100), 'buzz')


if __name__ == "__main__":
    unittest.main()
