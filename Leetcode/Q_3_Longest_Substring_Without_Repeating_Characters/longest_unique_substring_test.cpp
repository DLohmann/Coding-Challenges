#include "longest_unique_substring.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>
#include<string>


// Test with bazel from the test file directory:
// bazel test --test_output=all "//Q_X_LongestUniqueSubstring:LongestUniqueSubstring_test"

using ::longestuniquesubstring::Solution;

TEST(LongestUniqueSubstring, Test1) {
    Solution sol;
    EXPECT_EQ(sol.lengthOfLongestSubstring("abcabcbb"), 3);
    EXPECT_EQ(sol.lengthOfLongestSubstring("bbbbb"), 1);
    EXPECT_EQ(sol.lengthOfLongestSubstring("pwwkew"), 3);
}
