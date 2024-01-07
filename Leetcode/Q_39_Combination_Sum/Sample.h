#ifndef Sample_H_
#define Sample_H_

#include<vector>

namespace sample {


void printVector(std::vector<int>& v);

class Solution {
public:
    std::vector<int>* candidates;
    std::vector< std::vector<int> > result;
    Solution();

    void dfs(int current_candidate, std::vector< int >& combo, int remainder);
    std::vector<std::vector<int>> combinationSum(std::vector<int>& c, int target);
};

}  // namespace sample

#endif  // Sample_H_
