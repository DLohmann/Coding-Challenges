from typing import List

class Solution:
    # brute force
    # def maximumsSplicedArray(self, nums1: List[int], nums2: List[int]) -> int:
    #     N = len(nums1)
    #     max_sum = max(sum(nums1), sum(nums2))
    #     for left in range(0, N):
    #         for right in range(left + 1, N):
    #             current_sum = max(
    #                 sum(nums1[:left] + nums2[left:right] + nums1[right:]),
    #                 sum(nums2[:left] + nums1[left:right] + nums2[right:])
    #             )
    #             max_sum = max(max_sum, current_sum)
    #     return max_sum

    # greedy
    def optimalSubarray(self, nums: List[int], f):
        # parameter "f" is the comparison function, to get the "better" value.
        # if f is int.__lt__ (<) get min sub-array.
        # if f is int.__gt__ (>) get max sub-array.

        # initially, the best and current subarray are the first element
        best_sum = nums[0]
        best_left = 0
        best_right = 1

        current_sum = nums[0]
        current_left = 0

        enumerate_nums = enumerate(nums)
        next(enumerate_nums) # skip initial value that was already set
        for i, n in enumerate_nums:
            # current_sum = f(n, current_sum + n)
            if f(n, current_sum + n):
                current_sum = n
                current_left = i
            else:
                current_sum = current_sum + n

            # best_sum = f(best_sum, current_sum)
            if f(current_sum, best_sum):
                best_sum = current_sum
                best_left = current_left
                best_right = i + 1

        return best_sum, best_left, best_right

    def maximumsSplicedArray(self, nums1: List[int], nums2: List[int]) -> int:
        diff = [num1 - num2 for num1, num2 in zip(nums1, nums2)]
        # print(f'diff: {diff}')
        # min subarray indicates the amount that nums1 can be increased by.
        # max subarray indicates the amount that nums2 can be increased by.

        min_subarray_sum, min_subarray_left, min_sumarray_right = self.optimalSubarray( diff, int.__lt__)
        # print(f'min_subarray: {diff[min_subarray_left: min_sumarray_right]}, sum = {min_subarray_sum}')
        max_subarray_sum, max_subarray_left, max_sumarray_right = self.optimalSubarray(diff, int.__gt__)
        # print(f'max_subarray: {diff[max_subarray_left: max_sumarray_right]}, sum = {max_subarray_sum}')

        # print(f'sum(nums1) - min_subarray_sum: {sum(nums1) - min_subarray_sum}')
        # print(f'sum(nums2) + max_subarray_sum: {sum(nums2) + max_subarray_sum}')
        return max(
            sum(nums1) - min_subarray_sum,
            sum(nums2) + max_subarray_sum
        )