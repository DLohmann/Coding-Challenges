#include"TwoSum.h"

#include<algorithm>
#include<iostream>
#include<list>
#include<set>
#include<vector>

namespace two_sum {

bool Solution::NumCompare(Num a, Num b) {
	return a.val < b.val;
}

std::vector<int> Solution::twoSum(std::vector<int>& nums, int target) {
	std::vector<Num> values = std::vector<Num>(nums.size());
	for (int i = 0; i < nums.size(); i++) {
		values[i].val = nums[i];
		values[i].index = i;
	}
	std::sort(values.begin(), values.end(), NumCompare);
	for (std::vector<Num>::iterator it = values.begin(); it != values.end(); it++) {
		// std::cout << "it is at [" << it - values.begin() << "] = " << it->val << ", searching for " << target - (it->val) << std::endl;
		Num search_target {target - it->val, -1};
		std::vector<Num>::iterator search_result =
			std::lower_bound(it + 1, values.end(),
							 search_target,
							 Solution::NumCompare);
		if (search_result != values.end() && search_result->val + it->val == target){
			// std::cout << "found " << search_result->val << " at [" << search_result - values.begin() << "]" << std::endl;
			return {it->index, search_result->index};
		} else {
			// std::cout << "did not find" << std::endl;
		}
	}
	return {};
}

} // namespace two_sum

