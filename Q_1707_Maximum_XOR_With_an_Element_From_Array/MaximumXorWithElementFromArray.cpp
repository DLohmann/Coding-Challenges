#include"MaximumXorWithElementFromArray.h"

#include<vector>
#include<set>
#include<iostream>
#include<limits.h>

using namespace std;

namespace nums_size_times_queries_size_solution {
    vector<int> Solution::maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        //cout << "nums.size(): " << nums.size() << ", queries.size(): " << queries.size() << endl;
        vector<int> solution;
        solution.reserve(queries.size());
        set<int> nums_sorted = set<int>(nums.begin(), nums.end());
        for (vector<int>& query : queries) {
            int max_xor = INT_MIN;
            int x = query[0];
            int m = query[1];
            if (*nums_sorted.begin() > m) {
                solution.push_back(-1);
                continue;
            }
            set<int>::iterator num_range_end = nums_sorted.upper_bound(m);
            for (set<int>::iterator num_it = nums_sorted.begin(); num_it != num_range_end; num_it++) {
                int val = x ^ (*num_it);
                if (val > max_xor) {
                    max_xor = val;
                }
            }
            //cout << distance(nums_sorted.begin(), num_range_end) << " comparisons" << endl;
            solution.push_back(max_xor);
        }
        return solution;
    }
} // namespace nums_size_times_queries_size_solution

