#include "Sample.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>

using ::sample::Solution;

// Leetcode description example tests
TEST(Sample, LeetcodeExample1) {
    EXPECT_TRUE(Solution().isValid("()"));
}
TEST(Sample, LeetcodeExample2) {
    EXPECT_TRUE(Solution().isValid("()[]{}"));
}
TEST(Sample, LeetcodeExample3) {
    EXPECT_FALSE(Solution().isValid("(]"));
}


// Tests from Meta coding interview prep (https://www.metacareers.com/profile/coding_practice_question/?problem_id=211548593612944)
TEST(Sample, Test1Meta) {
    EXPECT_FALSE(Solution().isValid("{[(])}"));
}
TEST(Sample, Test2Meta) {
    EXPECT_TRUE(Solution().isValid("{{[[(())]]}}"));
}
