#include "ThreeSum.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<assert.h>

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
	std::vector<std::vector<int>> actual = solution.threeSumOther(input);
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
	for (int i = 0; i < expected.size(); i++) {
		EXPECT_THAT(actual[i], ElementsAreArray(expected[i]));
	}
}

TEST(ThreeSum, Example2) {
	std::vector<int> input = {0, 1, 1};
	Solution solution = Solution();
	std::vector<std::vector<int>> actual = solution.threeSumOther(input);
	std::vector<std::vector<int>> expected = {};
	std::cout << "Expected output matrix:";
	PrintMatrix(expected);
	
	std::cout << "Actual output matrix:";
	PrintMatrix(actual);
	
	sort(actual.begin(), actual.end(), Solution::triplet_compare);
	sort(expected.begin(), expected.end(), Solution::triplet_compare);
	
	EXPECT_EQ(actual.size(), expected.size());
	for (int i = 0; i < expected.size(); i++) {
		EXPECT_THAT(actual[i], ElementsAreArray(expected[i]));
	}
}

TEST(ThreeSum, Example3) {
	std::vector<int> input = {0, 0, 0};
	Solution solution = Solution();
	std::vector<std::vector<int>> actual = solution.threeSumOther(input);
	std::vector<std::vector<int>> expected = {{0, 0, 0}};
	std::cout << "Expected output matrix:";
	PrintMatrix(expected);
	
	std::cout << "Actual output matrix:";
	PrintMatrix(actual);
	
	sort(actual.begin(), actual.end(), Solution::triplet_compare);
	sort(expected.begin(), expected.end(), Solution::triplet_compare);
	
	EXPECT_EQ(actual.size(), expected.size());
	for (int i = 0; i < expected.size(); i++) {
		EXPECT_THAT(actual[i], ElementsAreArray(expected[i]));
	}
}
