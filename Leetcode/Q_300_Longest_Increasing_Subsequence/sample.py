from typing import List

from bisect import bisect_left

class Solution:
    # def lengthOfLIS(self, nums: List[int]) -> int:
    #     longest_terminated = [1 for _ in range(len(nums))]
    #     for i, current in enumerate(nums):
    #         next_length = 1 + longest_terminated[i]
    #         for j in range(i + 1, len(nums)):
    #             if current < nums[j] and longest_terminated[j] < next_length:
    #                 longest_terminated[j] = next_length
    #     return max(longest_terminated)

    # Based on https://leetcode.com/problems/longest-increasing-subsequence/solutions/1326308/c-python-dp-binary-search-bit-segment-tree-solutions-picture-explain-o-nlogn
    def lengthOfLIS(self, nums: List[int]) -> int:
        least_longest_sequence = []
        for i, current in enumerate(nums):
            j = bisect_left(least_longest_sequence, current)
            if j == len(least_longest_sequence):
                least_longest_sequence.append(current)
            else:
                least_longest_sequence[j] = current
            # print(least_longest_sequence)
        return len(least_longest_sequence)
        