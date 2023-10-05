#include "MaximumXorWithElementFromArray.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>
#include<vector>

// Test with bazel from the test file directory:
// bazel test --test_output=all "//Q_1707_MaximumXorWithElementFromArray:MaximumXorWithElementFromArray_test"

using namespace std;
using namespace ::testing;

TEST(MaximumXorWithElementFromArray, Test1) {
    vector<int> nums = {0, 1, 2, 3, 4};
    vector<vector<int>> queries = {{3, 1},
                                   {1, 3},
                                   {5, 6}};
    EXPECT_THAT(::nums_size_times_queries_size_solution::Solution().maximizeXor(nums, queries), ElementsAre(3, 3, 7));
    EXPECT_THAT(::bit_trie_solution::Solution().maximizeXor(nums, queries), ElementsAre(3, 3, 7));
}

TEST(MaximumXorWithElementFromArray, Test2) {
    vector<int> nums = {5, 2, 4, 6, 6, 3};
    vector<vector<int>> queries = {{12, 4},
                                   {8, 1},
                                   {6, 3}};
    EXPECT_THAT(::nums_size_times_queries_size_solution::Solution().maximizeXor(nums, queries), ElementsAre(15, -1, 5));
    EXPECT_THAT(::bit_trie_solution::Solution().maximizeXor(nums, queries), ElementsAre(15, -1, 5));
}
