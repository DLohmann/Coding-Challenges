#include "TwoSum.h"
#include "gmock/gmock.h"

#include<assert.h>
#include <gtest/gtest.h>
#include<iostream>
#include<vector>


// Test with bazel from the test file directory:
// bazel test --test_output=all Q_1_Two_Sum:all

using ::testing::ElementsAreArray;
using ::two_sum::Solution;

TEST(TwoSum, Test1) {
    std::vector<int> input = {2,7,11,15};
    Solution sol = Solution();
    EXPECT_THAT(sol.twoSum(input, 9), ElementsAreArray({0, 1}));
}

TEST(TwoSum, Test2) {
    std::vector<int> input = {3,2,4};
    Solution sol = Solution();
    EXPECT_THAT(sol.twoSum(input, 6), ElementsAreArray({1, 2}));
}
