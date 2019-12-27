#include<vector>
#include<list>
#include<set>
#include<algorithm>
#include<iostream>
/* TODO:
1) Change the algorithm to use the algorithm at this link (https://leetcode.com/problems/3sum/discuss/317216/Optimized-java-solution), but keep using binary search lookup to tell if a triplet has already been found.

*/

class Solution {
public:
    static bool triplet_compare(std::vector<int> a, std::vector<int> b) {
        // a < b
        if (a[0] < b[0]) {
            return true;
        } else if (a[0] > b[0]) {
            return false;
        }
        //hi
        if (a[1] < b[1]) {
            return true;
        } else if (a[1] > b[1]) {
            return false;
        }
        
        if (a[2] < b[2]) {
            return true;
        } else if (a[2] > b[2]) {
            return false;
        }
        
        return false;
    }
    std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
        if (nums.size() < 3) {
            return std::vector<std::vector<int>> {};
        }
        
        sort(nums.begin(), nums.end());
        
        // Sort the nums std::vector, and remove duplicates (so that none of the solution sets have duplicates):
        
        std::set<int> s;
        unsigned size = nums.size();
        for(int num : nums) {
            s.insert( num );
        }
        nums.assign( s.begin(), s.end() );
        
        
        
        std::list<std::vector<int> > triplets;
        int i, j, k;    // Ensure i < j < k
        for(int i = 0  ; i < nums.size() - 2; i++) {
            for(int j = i+1; j < nums.size() - 1; j++) {
            //for(int k = j+1; k < nums.size()    ; k++) {
            k = lower_bound(nums.begin() + j + 1, nums.end(), -1*(nums[i] + nums[j])) - nums.begin();
            
            // Prevent k from going out of bounds
            if (k == nums.size()){
                k = 0;
            }
            if (nums[i] + nums[j] + nums[k] == 0 && // Check if it's 0
                !binary_search(triplets.begin(), triplets.end(), std::vector<int>{nums[i], nums[j], nums[k]}, triplet_compare ) // Check if it's already in triplets
            ) {
                std::vector<int> zero_triplet = {nums[i], nums[j], nums[k]};
                //sort(triplet.begin(), triplet.end());
                std::cout << "[" << nums[i] << ", " << nums[j] << ", " << nums[k] << "]" << std::endl;
                //std::cout << "[" << i << ", " << j << ", " << k << "]" << std::endl;
                triplets.push_back(zero_triplet);
                continue;

            } else {
                std::cout << "\t(" << nums[i] << ", " << nums[j] << ", " << nums[k] << ")" << std::endl;
                //std::cout << "\t(" << i << ", " << j << ", " << k << ")" << std::endl;

            }
            //}
            }
        }
        std::vector< std::vector<int> > sums {triplets.begin(), triplets.end()};
        
        // Remove duplicates
        
        
        return sums;
    }
};

/*
Helpful links:
https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
https://leetcode.com/problems/3sum/discuss/317216/Optimized-java-solution
*/
