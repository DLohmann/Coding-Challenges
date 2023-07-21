#ifndef MaximumXorWithElementFromArray_H_
#define MaximumXorWithElementFromArray_H_

#include<vector>


// This solution is O(nums.size() * queries.size()), which is too slow for leetcode.
namespace nums_size_times_queries_size_solution {

class Solution {
public:
    std::vector<int> maximizeXor(std::vector<int>& nums, std::vector<std::vector<int>>& queries);
};

}  // namespace nums_size_times_queries_size_solution

// TODO: Make solution using binary trie


#endif  // MaximumXorWithElementFromArray_H_
