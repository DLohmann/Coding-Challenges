#include "Sample.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>

using ::sample::Solution;

TEST(Sample, Example1) {
    std::vector<int> input = {2,3,6,7};
    int target = 7;
    std::vector<std::vector<int>> output = Solution().combinationSum(input, target);
    EXPECT_EQ(output.size(), 2);
    EXPECT_THAT(output[0], ::testing::ElementsAre(2,2,3));
    EXPECT_THAT(output[1], ::testing::ElementsAre(7));
}

TEST(Sample, Example2) {
    std::vector<int> input = {2,3,5};
    int target = 8;
    std::vector<std::vector<int>> output = Solution().combinationSum(input, target);
    EXPECT_EQ(output.size(), 3);
    EXPECT_THAT(output[0], ::testing::ElementsAre(2,2,2,2));
    EXPECT_THAT(output[1], ::testing::ElementsAre(2,3,3));
    EXPECT_THAT(output[2], ::testing::ElementsAre(3,5));
}

TEST(Sample, Example3) {
    std::vector<int> input = {2};
    int target = 1;
    std::vector<std::vector<int>> output = Solution().combinationSum(input, target);
    EXPECT_EQ(output.size(), 0);
}
