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

bool Solution::triplet_equals(std::vector<int> a, std::vector<int> b) {
	return (a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a.size() == 3 && b.size() == 3);
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
	
	return std::vector< std::vector<int> >(triplets.begin(), triplets.end());
}

std::vector<std::vector<int>> Solution::threeSumFaster(std::vector<int>& input) {
	if (input.size() < 3) {
		return std::vector<std::vector<int>> {};
	}
	// Sorts and removes duplicates (so that none of the solution sets have duplicates)
	std::vector<int> nums(input);
	sort(nums.begin(), nums.end());	
	std::vector<std::vector<int> > triplets;	
	for(unsigned int i = 0  ; i < nums.size() - 2; i++) {
		for(unsigned int j = i+1; j < nums.size() - 1; j++) {
			std::vector<int>::iterator it = lower_bound(nums.begin() + j + 1, nums.end(), -1*(nums[i] + nums[j]));
			// Prevent k from going out of bounds
			if (it == nums.end()){
				continue;
			}
			unsigned int k = it - nums.begin();
			if (nums[i] + nums[j] + nums[k] == 0) {
				std::vector<int> zero_triplet = {nums[i], nums[j], nums[k]};
				std::cout << "[" << nums[i] << ", " << nums[j] << ", " << nums[k] << "]" << std::endl;
				triplets.push_back(zero_triplet);
				continue;
			} else {
				std::cout << "\t(" << nums[i] << ", " << nums[j] << ", " << nums[k] << ")" << std::endl;
			}
			// TODO: Check for array index out of bounds
			while (nums[j] == nums[j + 1] && j < nums.size()) {
				j++;
			}
		}
		while (nums[i] == nums[i + 1] && i < nums.size()) {
			i++;
		}
	}
	return triplets;
}

void printArr(std::vector<int> arr) {
	std::cout << "[";
	for (int i : arr) {
		std::cout << " " << i;
	}
	std::cout << " ]" << std::endl;
}

struct search_result {
	bool found;
	unsigned int i;
	unsigned int j;
	unsigned int k;
};

search_result threeSumFastestSearch(std::vector<int> nums, unsigned int i, unsigned int k) {
	unsigned int j = -1;
	while (i + 1 < k) {
		int target = -1*(nums[i] + nums[k]);
		std::cout << "\titerating, i = " << i << ", k = " << k << std::endl << "\t\tsearching for target  " << target << " in ";
		printArr(std::vector<int>(nums.begin() + i + 1, nums.begin() + k));
		std::vector<int>::iterator it = // nums.end() + k;
			std::lower_bound(nums.begin() + i + 1, nums.begin() + k, -1*(nums[i] + nums[k]));
			
		// If all entries in subarray are less than target, then increment lower bound index i, to make the target smaller to fit in the interval.
		if (it == nums.begin() + k) {
			do {
				i++;
				std::cout << "\t\ti = " << i << std::endl;
			} while (nums[i - 1] == nums[i] && i + 1 < k);
			continue;
		}
		if (it == nums.begin() + i + 1 && target < *it) {
			do {
				k--;
				std::cout << "\t\tk = " << k << std::endl;
			} while (nums[k] == nums[k + 1] && i + 1 < k);
			continue;
		}
		
		j = it - nums.begin();
		search_result result = {false, i, j, k};
		if (target == *it) {
			std::cout << "\t\tFOUND: j = " << j << "\t(" << nums[i] << ", " << nums[j] << ", " << nums[k] << ")" << std::endl;
			result.found = true;
		}
		return result;
	}
	// Interval was too small to contain a solution
	return {false, i, j, k};
}

std::vector<std::vector<int>> Solution::threeSumFastest(std::vector<int>& input) {
	std::cout << "threeSumFastest" << std::endl;
	printArr(input);
	
	if (input.size() < 3) {
		return std::vector<std::vector<int>> {};
	}
	
	// Sorts and removes duplicates (so that none of the solution sets have duplicates)
	std::vector<int> nums(input);
	sort(nums.begin(), nums.end());
	std::cout << "Sorted: ";
	printArr(nums);
	// nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
	std::list<std::vector<int> > triplets;
	unsigned int i = 0, k = nums.size() - 1;
	do {
		std::cout << "outer search" << std::endl;
		search_result outer_search = threeSumFastestSearch(nums, i, k);
		if (outer_search.found) {
			triplets.push_back({nums[outer_search.i], nums[outer_search.j], nums[outer_search.k]});
		}
		
		// Tries moving both left bound i and right bound k in again separately
		unsigned int i_next = outer_search.i;
		do {
			i_next++;
		} while (nums[i_next - 1] == nums[i_next] && i_next + 1 < k);
		
		unsigned int k_next = outer_search.k;
		do {
			k_next--;
		} while (nums[k_next] == nums[k_next + 1] && i + 1 < k_next);
		
		
		std::cout << "right search" << std::endl;
		search_result right_search = threeSumFastestSearch(nums, i_next, k);
		if (right_search.found) {
			triplets.push_back({nums[right_search.i], nums[right_search.j], nums[right_search.k]});
		}
		std::cout << "left search" << std::endl;
		search_result left_search = threeSumFastestSearch(nums, i, k_next);
		if (left_search.found) {
			triplets.push_back({nums[left_search.i], nums[left_search.j], nums[left_search.k]});
		}
		// i = std::max(i + 1, outer_search.i);
		// k = std::min(k - 1, outer_search.k);
		
		i = i_next;
		k = k_next;
		// do {
		// 	k--;
		// 	std::cout << "\t\tk = " << k << std::endl;
		// } while (nums[k] == nums[k + 1] && i + 1 < k);
			
		// if (it == nums.begin() + i + 1 && sum != 0) {
		// 	k--;
		// 	continue;
		// }
	} while (i + 1 < k);
	
	return std::vector< std::vector<int> >(triplets.begin(), triplets.end());
}

// The input to this function should be sorted
// std::vector<std::vector<int>> threeSumFastestRecursiveHelper(std::vector<int>& nums, unsigned int i, unsigned int k) {
// 	std::cout << "threeSumFastestRecursiveHelper: i = " << i << ", k = " << k << std::endl;
// 	std::vector< std::vector<int> > triplets;
// 	unsigned int j;
// 	while (i + 1 < k) {
// 		const int target = -1*(nums[i] + nums[k]);
// 		std::cout << "\titerating, i = " << i << ", k = " << k << ", searching for target " << target << " in ";
// 		printArr(std::vector<int>(nums.begin() + i + 1, nums.begin() + k));
// 		std::vector<int>::iterator it = // nums.end() + k;
// 			std::lower_bound(nums.begin() + i + 1, nums.begin() + k, -1*(nums[i] + nums[k]));
			
// 		// If all entries in subarray are less than target, then increment lower bound index i, to make the target smaller to fit in the interval.
// 		if (it == nums.begin() + k) {
// 			do {
// 				i++;
// 				std::cout << "\t\ti = " << i << std::endl;
// 			} while (nums[i - 1] == nums[i] && i + 1 < k);
// 			continue;
// 		}
// 		// If all entries in subarray are greater than or equal to the target, then decrement upper bound index k, to make the target larger to fit in the interval.
// 		if (it == nums.begin() + i + 1 && target < it[0]) {
// 			do {
// 				k--;
// 				std::cout << "\t\tk = " << k << std::endl;
// 			} while (nums[k] == nums[k + 1] && i + 1 < k);
// 			continue;
// 		}
// 		j = it - nums.begin();
// 		int sum = nums[i] + nums[j] + nums[k];
// 		if (sum == 0) {
// 			std::cout << "\t\tFound triplet: (" << nums[i] << ", " << nums[j] << ", " << nums[k]  << ")"<< std::endl;
// 			triplets.push_back({nums[i], nums[j], nums[k]});
// 		}
		
// 		unsigned int i_next = i;
// 		do {
// 			i_next++;
// 		} while (nums[i_next - 1] == nums[i_next] && i_next + 1 < k);
// 		std::cout << "\t\tCalling threeSumFastestRecursiveHelper: i = " << i_next << ", k = " << k << std::endl << std::endl;
// 		std::vector< std::vector<int> > right_subproblem = threeSumFastestRecursiveHelper(nums, i_next, k);
// 		triplets.insert(triplets.end(), right_subproblem.begin(), right_subproblem.end());
// 		right_subproblem.clear();
		
// 		unsigned int k_next = k;
// 		do {
// 			k_next--;
// 		} while (nums[k_next] == nums[k_next + 1] && i + 1 < k_next);
// 		std::cout << "\n\t\tCalling threeSumFastestRecursiveHelper: i = " << i << ", k = " << k_next << std::endl << std::endl;
// 		std::vector< std::vector<int> > left_subproblem = threeSumFastestRecursiveHelper(nums, i, k_next);
// 		triplets.insert(triplets.end(), left_subproblem.begin(), left_subproblem.end());
// 		left_subproblem.clear();
// 		break;
// 		// If all the entries in the subarray are more than the target, then decrement upper bound index k, to make the target larger to fit in the interval.
// 		// If the target was not found, maybe try the next number in the subarray.
			
// 		// If all the entries in the subarray are greater than target, then decrement upper bound index k.
// 		// If the first few entries are less than target, and last few are greater, than sum > 0. So
// 		// if (it == nums.begin() + i + 1 && sum != 0) {
// 		// 	k--;
// 		// 	continue;
// 		// }
// 	}
// 	return triplets;
// }
// std::vector<std::vector<int>> Solution::threeSumFastestRecursive(const std::vector<int>& input) {
// 	std::vector<int> nums(input);
// 	sort(nums.begin(), nums.end());
// 	std::cout << "Sorted initial array: ";
// 	printArr(nums);
// 	std::vector< std::vector<int> > result = threeSumFastestRecursiveHelper(nums, /*i =*/ 0, /*k =*/ nums.size() - 1);
	
// 	// TODO: Remove duplicates. Or prevent them from being added by keeping track of added triplets and not re-adding them
// 	sort(result.begin(), result.end(), Solution::triplet_compare);
// 	result.erase(unique(result.begin(), result.end(), Solution::triplet_equals), result.end());
	
// }

} // namespace three_sum

