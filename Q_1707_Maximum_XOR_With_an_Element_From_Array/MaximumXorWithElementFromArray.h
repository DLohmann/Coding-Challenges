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


// This solution is O(nums.size() + queries.size()), which was accepted by leetcode.
namespace bit_trie_solution {

class Solution {
public:
    std::vector<int> maximizeXor(std::vector<int>& nums, std::vector<std::vector<int>>& queries);
};

}  // namespace bit_trie_solution
// TODO: Make solution using binary trie. Should work in O(nums.size() + queries.size()).


#endif  // MaximumXorWithElementFromArray_H_
