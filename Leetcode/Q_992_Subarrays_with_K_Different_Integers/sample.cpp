#include"sample.h"

#include<vector>
#include<unordered_map>


namespace sample {

// Don't forget 'Solution::' before function name
// void printSubseq(vector<int>& nums, int begin, int end) {
//     for (int i = begin; i < end; i ++) {
//         cout << nums[i] << ", ";
//     }
//     cout << nums[end] << endl;
// }

// void printMap(unordered_map<int, int>& d) {
//     for (pair<int, int> p : d) {
//         cout << "\td[" << p.first << "] = " << p.second << endl;
//     }
// }

void decrementAndRemoveZeros(std::unordered_map<int, int>& d, int val) {
    d[val] -= 1;
    if (d[val] == 0) {
        d.erase(val);
    }
}

int Solution::subarraysWithKDistinct(std::vector<int>& nums, int k) {
    int num_good = 0, start = 0, end = 0;
    std::unordered_map<int, int> d;

    d[nums[0]] = 1;
    while (nums.size() - start >= k) {
        int old_end = -1;
        // Expand sliding window right
        while (d.size() <= k and end < nums.size()) {
            if (d.size() == k) {
                num_good += 1;
                if (old_end == -1) {
                    old_end = end;
                }
            }
            end += 1;
            if (end == nums.size()) {
                break;
            }
            d[nums[end]] += 1;
        }
        
        // Contract back the right side of the sliding window to get to smallest size with k different integers
        for (int i = old_end + 1; i <= end and i < nums.size(); i++) {
            decrementAndRemoveZeros(d, nums[i]);
        }
        end = old_end;

        // Increment start
        decrementAndRemoveZeros(d, nums[start]);
        start += 1;
    }
    return num_good;
}

} // namespace sample




