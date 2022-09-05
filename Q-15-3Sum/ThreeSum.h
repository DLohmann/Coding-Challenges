#ifndef ThreeSum_H_
#define GOOGLETEST_SAMPLES_SAMPLE3_INL_H_

#include<vector>

namespace three_sum {

class Solution {
public:
	static bool triplet_compare(std::vector<int> a, std::vector<int> b);
	std::vector<std::vector<int>> threeSum(std::vector<int>& input);
};

}  // namespace three_sum

#endif  // ThreeSum_H_
