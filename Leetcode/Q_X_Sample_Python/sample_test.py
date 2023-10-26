import unittest
import sample

class TestFizzbuzz(unittest.TestCase):
    '''Unit test for sample fizzbuzz function.'''
    def test_100(self):
        self.assertEqual(sample.fizzbuzz(100), 'bezz')


if __name__ == "__main__":
    unittest.main()
