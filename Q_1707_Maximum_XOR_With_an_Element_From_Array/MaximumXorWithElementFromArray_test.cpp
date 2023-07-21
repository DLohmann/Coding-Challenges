#include "MaximumXorWithElementFromArray.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>
#include<vector>

// Test with bazel from the test file directory:
// bazel test --test_output=all "//Q_1707_MaximumXorWithElementFromArray:MaximumXorWithElementFromArray_test"

using namespace std;
using namespace ::testing;
using ::nums_size_times_queries_size_solution::Solution;

TEST(MaximumXorWithElementFromArray, Test1) {
    vector<int> nums = {0, 1, 2, 3, 4};
    vector<vector<int>> queries = {{3, 1},
                                   {1, 3},
                                   {5, 6}};
    Solution sol;
    EXPECT_THAT(sol.maximizeXor(nums, queries), ElementsAre(3, 3, 7));
}

TEST(MaximumXorWithElementFromArray, Test2) {
    vector<int> nums = {5, 2, 4, 6, 6, 3};
    vector<vector<int>> queries = {{12, 4},
                                   {8, 1},
                                   {6, 3}};
    Solution sol;
    EXPECT_THAT(sol.maximizeXor(nums, queries), ElementsAre(15, -1, 5));
}
