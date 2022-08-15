#include "ThreeSum.cpp"

#include<iostream>
#include<vector>
#include<algorithm>
#include<assert.h>

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
void SimpleTest() {
	std::vector<int> input = {-1, 0, 1, 2, -1, -4}; // sorted: -4, -1, -1, 0, 1, 2
	Solution solution = Solution();
	std::vector<std::vector<int>> actual = solution.threeSum(input);
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
	assert(actual.size() == expected.size());
	for (int i = 0; i < expected.size(); i++) {
		assert(actual[i].size() == expected[i].size());
		for (int j = 0; j < expected[i].size(); j++) {
			assert(actual[i][j] == expected[i][j]);
		}
	}
}

int main() {
	std::cout << std::endl << "Beginning tests!" << std::endl;
	SimpleTest();
	std::cout << "All tests passed!" << std::endl;
	return 0;	
}