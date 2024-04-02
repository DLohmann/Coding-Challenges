#include "sample.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>

using ::sample::Solution;

TEST(sample, TestExample1) {
    std::vector<int> nums = {1,2,1,2,3};
    int k = 2;
    EXPECT_EQ(Solution().subarraysWithKDistinct(nums, k), 7);
}

TEST(sample, TestExample2) {
    std::vector<int> nums = {1,2,1,3,4};
    int k = 3;
    EXPECT_EQ(Solution().subarraysWithKDistinct(nums, k), 3);
}

