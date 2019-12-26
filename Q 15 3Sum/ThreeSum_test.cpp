#include "ThreeSum.cpp"

#include<iostream>
#include<vector>
#include<assert.h>

// Test simple leetcode case

void SimpleTest() {
	std::vector<int> input = {-1, 0, 1, 2, -1, -4};
	Solution solution = Solution();
	std::vector<std::vector<int>> actual = solution.threeSum(input);
	std::vector<std::vector<int>> expected =
		{
			{-1, 0, 1},
			{-1, -1, 2}
		};
	assert(actual.size() == expected.size());
	for (int i = 0; i < expected.size(); i++) {
		assert(actual[i].size() == expected[i].size());
		for (int j = 0; j < expected[i].size(); j++) {
			assert(actual[i][j] == expected[i][j]);
		}
	}
}

int main() {
	SimpleTest();
	std::cout << "All tests passed!" << std::endl;
	return 0;	
}