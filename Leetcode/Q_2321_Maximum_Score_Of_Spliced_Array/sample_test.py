import unittest
from Leetcode.Q_2321_Maximum_Score_Of_Spliced_Array import sample

class TestMaximumsSplicedArray(unittest.TestCase):
    '''Unit test for spliced array solution.'''

    def test_example_1(self):
        nums1 = [60,60,60]
        nums2 = [10,90,10]
        expected = 210
        self.assertEqual(sample.Solution().maximumsSplicedArray(nums1, nums2), expected)

    def test_example_2(self):
        nums1 = [20,40,20,70,30]
        nums2 = [50,20,50,40,20]
        expected = 220
        self.assertEqual(sample.Solution().maximumsSplicedArray(nums1, nums2), expected)

    def test_example_3(self):
        nums1 = [7,11,13]
        nums2 = [1,1,1]
        expected = 31
        self.assertEqual(sample.Solution().maximumsSplicedArray(nums1, nums2), expected)


if __name__ == "__main__":
    unittest.main()
