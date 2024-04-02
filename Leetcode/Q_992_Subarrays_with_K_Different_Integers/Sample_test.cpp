#include "Sample.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>

using ::sample::Solution;

TEST(Sample, Test1) {
    std::vector<int> input;
    EXPECT_THAT(Solution().sample(input), ::testing::ElementsAre(1, 2));
}
