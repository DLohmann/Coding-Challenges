#include "ThreeSum.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<assert.h>


// Test with bazel from the test file directory:
// bazel test --test_output=all "//Q-15-3Sum:ThreeSum_test"

using ::three_sum::Solution;
using ::testing::ElementsAreArray;

// Test simple leetcode case
void PrintMatrix (std::vector<std::vector<int>> input) {
    std::cout << std::endl;
    for(std::vector<int> row : input) {
        std::cout << "[";
        for (int entry : row) {
            std::cout << " " << entry;
        }
        std::cout << " ]" << std::endl;
    }
    std::cout << std::endl;
}


TEST(ThreeSum, Example1) {
    std::vector<int> input = {-1, 0, 1, 2, -1, -4}; // sorted: -4, -1, -1, 0, 1, 2
    Solution solution = Solution();
    std::vector<std::vector<int>> actual = solution.threeSumFastest(input);
    std::vector<std::vector<int>> expected =
        {
            {-1, 0, 1},
            {-1, -1, 2}
        };
    std::cout << "Expected output matrix:";
    PrintMatrix(expected);
    
    std::cout << "Actual output matrix:";
    PrintMatrix(actual);
    
    sort(actual.begin(), actual.end(), Solution::triplet_compare);
    sort(expected.begin(), expected.end(), Solution::triplet_compare);
    
    EXPECT_EQ(actual.size(), expected.size());
    for (unsigned int i = 0; i < expected.size(); i++) {
        EXPECT_THAT(actual[i], ElementsAreArray(expected[i]));
    }
}

TEST(ThreeSum, Example2) {
    std::vector<int> input = {0, 1, 1};
    Solution solution = Solution();
    std::vector<std::vector<int>> actual = solution.threeSumFastest(input);
    std::vector<std::vector<int>> expected = {};
    std::cout << "Expected output matrix:";
    PrintMatrix(expected);
    
    std::cout << "Actual output matrix:";
    PrintMatrix(actual);
    
    sort(actual.begin(), actual.end(), Solution::triplet_compare);
    sort(expected.begin(), expected.end(), Solution::triplet_compare);
    
    EXPECT_EQ(actual.size(), expected.size());
    for (unsigned int i = 0; i < expected.size(); i++) {
        EXPECT_THAT(actual[i], ElementsAreArray(expected[i]));
    }
}

TEST(ThreeSum, Example3) {
    std::vector<int> input = {0, 0, 0};
    Solution solution = Solution();
    std::vector<std::vector<int>> actual = solution.threeSumFastest(input);
    std::vector<std::vector<int>> expected = {{0, 0, 0}};
    std::cout << "Expected output matrix:";
    PrintMatrix(expected);
    
    std::cout << "Actual output matrix:";
    PrintMatrix(actual);
    
    sort(actual.begin(), actual.end(), Solution::triplet_compare);
    sort(expected.begin(), expected.end(), Solution::triplet_compare);
    
    EXPECT_EQ(actual.size(), expected.size());
    for (unsigned int i = 0; i < expected.size(); i++) {
        EXPECT_THAT(actual[i], ElementsAreArray(expected[i]));
    }
}

TEST(ThreeSum, ZeroOneOne) {
    std::vector<int> input = {0, 1, 1};
    Solution solution = Solution();
    std::vector<std::vector<int>> actual = solution.threeSumFastest(input);
    std::vector<std::vector<int>> expected = {};
    std::cout << "Expected output matrix:";
    PrintMatrix(expected);
    
    std::cout << "Actual output matrix:";
    PrintMatrix(actual);
    
    sort(actual.begin(), actual.end(), Solution::triplet_compare);
    sort(expected.begin(), expected.end(), Solution::triplet_compare);
    
    EXPECT_EQ(actual.size(), expected.size());
    for (unsigned int i = 0; i < expected.size(); i++) {
        EXPECT_THAT(actual[i], ElementsAreArray(expected[i]));
    }
}
    
TEST(ThreeSum, Example1ManyDuplicates) {
    std::vector<int> input = {-1, 0, 1, -1, 2, 0, -1, 4, 4, 4, 4, -4};
    // sorted: -4, -1, -1, -1, 0, 0, 1, 2, 4, 4, 4, 4
    Solution solution = Solution();
    std::vector<std::vector<int>> actual = solution.threeSumFastest(input);
    std::vector<std::vector<int>> expected =
        {
            {-4, 0, 4},
            {-1, 0, 1},
            {-1, -1, 2}
        };
    std::cout << "Expected output matrix:";
    PrintMatrix(expected);
    
    std::cout << "Actual output matrix:";
    PrintMatrix(actual);
    
    sort(actual.begin(), actual.end(), Solution::triplet_compare);
    sort(expected.begin(), expected.end(), Solution::triplet_compare);
    
    EXPECT_EQ(actual.size(), expected.size());
    for (unsigned int i = 0; i < expected.size(); i++) {
        EXPECT_THAT(actual[i], ElementsAreArray(expected[i]));
    }
}

TEST(ThreeSum, WeightedNegative) {
    std::vector<int> input = {-3, -2, 0, 0, 2};
    Solution solution = Solution();
    std::vector<std::vector<int>> actual = solution.threeSumFastest(input);
    std::vector<std::vector<int>> expected =
        {
            {-2, 0, 2}
        };
    std::cout << "Expected output matrix:";
    PrintMatrix(expected);
    
    std::cout << "Actual output matrix:";
    PrintMatrix(actual);
    
    sort(actual.begin(), actual.end(), Solution::triplet_compare);
    sort(expected.begin(), expected.end(), Solution::triplet_compare);
    
    EXPECT_EQ(actual.size(), expected.size());
    for (unsigned int i = 0; i < expected.size(); i++) {
        EXPECT_THAT(actual[i], ElementsAreArray(expected[i]));
    }
}

TEST(ThreeSum, WeightedPositive) {
    std::vector<int> input = {-2, 0, 0, 2, 3};
    Solution solution = Solution();
    std::vector<std::vector<int>> actual = solution.threeSumFastest(input);
    std::vector<std::vector<int>> expected =
        {
            {-2, 0, 2}
        };
    std::cout << "Expected output matrix:";
    PrintMatrix(expected);
    
    std::cout << "Actual output matrix:";
    PrintMatrix(actual);
    
    sort(actual.begin(), actual.end(), Solution::triplet_compare);
    sort(expected.begin(), expected.end(), Solution::triplet_compare);
    
    EXPECT_EQ(actual.size(), expected.size());
    for (unsigned int i = 0; i < expected.size(); i++) {
        EXPECT_THAT(actual[i], ElementsAreArray(expected[i]));
    }
}

TEST(ThreeSum, TestCornerCases) {
    std::vector<int> input = {-1, 0, 1, 2, -1, -4, -2, -3, 3, 0, 4};
    Solution solution = Solution();
    std::vector<std::vector<int>> actual = solution.threeSumFastest(input);
    std::vector<std::vector<int>> expected =
        {
            {-4,0,4},
            {-4,1,3},
            {-3,-1,4},
            {-3,0,3},
            {-3,1,2},
            {-2,-1,3},
            {-2,0,2},
            {-1,-1,2},
            {-1,0,1}
        };
    std::cout << "Expected output matrix:";
    PrintMatrix(expected);
    
    std::cout << "Actual output matrix:";
    PrintMatrix(actual);
    
    sort(actual.begin(), actual.end(), Solution::triplet_compare);
    sort(expected.begin(), expected.end(), Solution::triplet_compare);
    
    EXPECT_EQ(actual.size(), expected.size());
    for (unsigned int i = 0; i < expected.size(); i++) {
        EXPECT_THAT(actual[i], ElementsAreArray(expected[i]));
    }
}
