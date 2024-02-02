import unittest
import sample

class TestIsInterleave(unittest.TestCase):
    '''Unit test for isInterleave function.'''
    def test_example_1(self):
        s1 = 'aabcc'
        s2 = 'dbbca'
        s3 = 'aadbbcbcac'
        self.assertEqual(sample.Solution().isInterleave(s1, s2, s3), True)
        
    def test_example_2(self):
        s1 = 'aabcc'
        s2 = 'dbbca'
        s3 = 'aadbbbaccc'
        self.assertEqual(sample.Solution().isInterleave(s1, s2, s3), False)
        
    def test_example_3(self):
        s1 = ''
        s2 = ''
        s3 = ''
        self.assertEqual(sample.Solution().isInterleave(s1, s2, s3), True)

    # This test case previously gave a "Time Exceeded" error on Leetcode for the
    # backrtacking-based algorithm, but not the dynamic programming algorithm.
    def test_example_long_test_case(self):
        s1 = 'bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa'
        s2 = 'babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab'
        s3 = 'babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab'
        self.assertEqual(sample.Solution().isInterleave(s1, s2, s3), False)

if __name__ == "__main__":
    unittest.main()
