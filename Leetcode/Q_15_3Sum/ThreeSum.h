#ifndef ThreeSum_H_
#define GOOGLETEST_SAMPLES_SAMPLE3_INL_H_

#include<vector>

namespace three_sum {

class Solution {
public:
    static bool triplet_compare(std::vector<int> a, std::vector<int> b);
    
    static bool triplet_equals(std::vector<int> a, std::vector<int> b);
    
    // O(n^3)
    std::vector<std::vector<int>> threeSum(std::vector<int>& input);
    
    // O(n^2)
    std::vector<std::vector<int>> threeSumFaster(std::vector<int>& input);
    
    // O(n*log(n))
    std::vector<std::vector<int>> threeSumFastest(std::vector<int>& input);
    
    // O(n*log(n))
    // std::vector<std::vector<int>> threeSumFastestRecursive(const std::vector<int>& input);
};

}  // namespace three_sum

#endif  // ThreeSum_H_
