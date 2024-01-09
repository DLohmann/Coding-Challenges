#include"Sample.h"

using namespace std;

namespace sample {

int Solution::findDuplicate(vector<int>& nums) {
    // O(n) time solution, thanks to neetcode
    int fast = 0;
    int slow = 0;
    do {
        slow = nums[slow];
        fast = nums[nums[fast]];
    } while(slow != fast);

    int slow2 = 0;
    while (slow != slow2) {
        slow = nums[slow];
        slow2 = nums[slow2];
    }
    return slow;

    // O(n^2) time solution (too slow)
    // for (auto it_first = nums.begin(); it_first != nums.end() - 1; it_first++) {
    //     for (auto it_second = next(it_first); it_second != nums.end(); it_second++) {
    //         if (*it_first == *it_second) {
    //             return *it_first;
    //         }
    //     }
    // }
    // return -1;
}

} // namespace sample

