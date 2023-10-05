#ifndef TwoSum_H_
#define TwoSum_H_

#include<vector>

namespace two_sum {

class Solution {
public:
	struct Num {
		int val;
		int index;
	};

	static bool NumCompare(Num a, Num b);

	std::vector<int> twoSum(std::vector<int>& nums, int target);
};

}  // namespace two_sum

#endif  // TwoSum_H_
