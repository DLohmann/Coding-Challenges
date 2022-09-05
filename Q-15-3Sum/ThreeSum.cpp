#include"ThreeSum.h"

#include<vector>
#include<list>
#include<set>
#include<algorithm>
#include<iostream>
/* TODO:
1) Change the algorithm to use the algorithm at this link (https://leetcode.com/problems/3sum/discuss/317216/Optimized-java-solution), but keep using binary search lookup to tell if a triplet has already been found.

*/
namespace three_sum {
// Used to sort the triplets in a standard order
bool Solution::triplet_compare(std::vector<int> a, std::vector<int> b) {
	if (a[0] < b[0]) {
		return true;
	} else if (a[0] > b[0]) {
		return false;
	}
	if (a[1] < b[1]) {
		return true;
	} else if (a[1] > b[1]) {
		return false;
	}
	if (a[2] < b[2]) {
		return true;
	} else if (a[2] > b[2]) {
		return false;
	}
	return false;
}

std::vector<std::vector<int>> Solution::threeSum(std::vector<int>& input) {
	if (input.size() < 3) {
		return std::vector<std::vector<int>> {};
	}
	
	// Sorts and removes duplicates (so that none of the solution sets have duplicates)
	std::vector<int> nums(input);
	sort(nums.begin(), nums.end());
	// nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	std::list<std::vector<int> > triplets;	
	for (unsigned int i = 0; i < nums.size() - 2; i++) {
		for (unsigned int j = i + 1; j < nums.size() - 1; j++) {
			for (unsigned int k = j + 1; k < nums.size(); k++) {
				if (nums[i] + nums[j] + nums[k] == 0) {
					triplets.push_back({nums[i], nums[j], nums[k]});
				}
				while (nums[k] == nums[k + 1]) {
					k++;
				}
			}
			while (nums[j] == nums[j + 1]) {
				j++;
			}
		}
		while (nums[i] == nums[i + 1]) {
			i++;
		}
	}
	
	// do {
	// 	std::vector<int>::iterator it = std::lower_bound(nums.begin() + i + 1, nums.begin() + k, -1*(nums[i] + nums[j]));
	// 	// If all entries in subarray are less than target, then increment lower bound index i.
	// 	if (it == nums.begin() + k) {
	// 		i++;
	// 		continue;
	// 	}
	// 	j = *it;
	// 	int sum = nums[i] + nums[j] + nums[k];
	// 	// If all the entries in the subarray are greater than target, then decrement upper bound index k.
	// 	// If the first few entries are less than target, and last few are greater, than sum > 0. So 
	// 	if (it == nums.begin() + i + 1 && sum != 0) {
	// 		k--;
	// 		continue;
	// 	}
	// 	// If target was found, then increment 
	// } while (i < k);
	
	return std::vector< std::vector<int> >(triplets.begin(), triplets.end());
}

std::vector<std::vector<int>> Solution::threeSumOther(std::vector<int>& input) {
	if (input.size() < 3) {
		return std::vector<std::vector<int>> {};
	}
	
	// Sorts and removes duplicates (so that none of the solution sets have duplicates)
	std::vector<int> nums(input);
	sort(nums.begin(), nums.end());	
	std::list<std::vector<int> > triplets;	
	for(unsigned int i = 0  ; i < nums.size() - 2; i++) {
		for(unsigned int j = i+1; j < nums.size() - 1; j++) {
			unsigned int k = lower_bound(nums.begin() + j + 1, nums.end(), -1*(nums[i] + nums[j])) - nums.begin();
			// Prevent k from going out of bounds
			if (k == nums.size()){
				continue;
			}
			if (nums[i] + nums[j] + nums[k] == 0) {
				std::vector<int> zero_triplet = {nums[i], nums[j], nums[k]};
				std::cout << "[" << nums[i] << ", " << nums[j] << ", " << nums[k] << "]" << std::endl;
				triplets.push_back(zero_triplet);
				continue;
			} else {
				std::cout << "\t(" << nums[i] << ", " << nums[j] << ", " << nums[k] << ")" << std::endl;
			}
			// TODO: Check for array index out of bounds
			while (nums[j] == nums[j + 1]) {
				j++;
			}
		}
		while (nums[i] == nums[i + 1]) {
			i++;
		}
	}
	return std::vector< std::vector<int> >(triplets.begin(), triplets.end());
}

} // namespace three_sum

