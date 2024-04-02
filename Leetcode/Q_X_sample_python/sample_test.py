import unittest
import sample

class TestFizzbuzz(unittest.TestCase):
    '''Unit test for sample fizzbuzz function.'''

    # The test name must start with letters 'test' to inform the test runner about which methods represent tests.
    # Otherwise the method might be skipped by the test runner.
    # If the test runner finds 0 test methods, it should just pass.
    # https://docs.python.org/2/library/unittest.html#basic-example:~:text=start%20with%20the%20letters%20test
    def test_100(self):
        self.assertEqual(sample.Solution().fizzbuzz(100), 'buzz')


if __name__ == "__main__":
    unittest.main()
