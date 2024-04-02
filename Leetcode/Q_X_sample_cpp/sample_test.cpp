#include "sample.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>

using ::sample::Solution;

TEST(sample, Test1) {
    std::vector<int> input;
    EXPECT_THAT(Solution().sample(input), ::testing::ElementsAre(1, 2));
}
