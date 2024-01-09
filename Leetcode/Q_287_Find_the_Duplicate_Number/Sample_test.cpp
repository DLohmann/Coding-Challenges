#include "Sample.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>

using ::sample::Solution;

TEST(Sample, Example1) {
    std::vector<int> input = {1,3,4,2,2};
    EXPECT_EQ(Solution().findDuplicate(input), 2);
}

TEST(Sample, Example2) {
    std::vector<int> input = {3,1,3,4,2};
    EXPECT_EQ(Solution().findDuplicate(input), 3);
}
