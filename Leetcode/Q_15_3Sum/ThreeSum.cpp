#include"ThreeSum.h"

#include<vector>
#include<list>
#include<set>
#include<algorithm>
#include<iostream>
/* TODO:
1) Change the algorithm to use the algorithm at this link (https://leetcode.com/problems/3sum/discuss/317216/Optimized-java-solution), but keep using binary search lookup to tell if a triplet has already been found.

*/
namespace three_sum {
// Used to sort the triplets in a standard order
bool Solution::triplet_compare(std::vector<int> a, std::vector<int> b) {
    if (a[0] < b[0]) {
        return true;
    } else if (a[0] > b[0]) {
        return false;
    }
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

bool Solution::triplet_equals(std::vector<int> a, std::vector<int> b) {
    return (a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a.size() == 3 && b.size() == 3);
}

std::vector<std::vector<int>> Solution::threeSum(std::vector<int>& input) {
    if (input.size() < 3) {
        return std::vector<std::vector<int>> {};
    }
    
    // Sorts and removes duplicates (so that none of the solution sets have duplicates)
    std::vector<int> nums(input);
    sort(nums.begin(), nums.end());
    // nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
    std::list<std::vector<int> > triplets;    
    for (unsigned int i = 0; i < nums.size() - 2; i++) {
        for (unsigned int j = i + 1; j < nums.size() - 1; j++) {
            for (unsigned int k = j + 1; k < nums.size(); k++) {
                if (nums[i] + nums[j] + nums[k] == 0) {
                    triplets.push_back({nums[i], nums[j], nums[k]});
                }
                while (nums[k] == nums[k + 1]) {
                    k++;
                }
            }
            while (nums[j] == nums[j + 1]) {
                j++;
            }
        }
        while (nums[i] == nums[i + 1]) {
            i++;
        }
    }
    
    return std::vector< std::vector<int> >(triplets.begin(), triplets.end());
}

std::vector<std::vector<int>> Solution::threeSumFaster(std::vector<int>& input) {
    if (input.size() < 3) {
        return std::vector<std::vector<int>> {};
    }
    // Sorts and removes duplicates (so that none of the solution sets have duplicates)
    std::vector<int> nums(input);
    sort(nums.begin(), nums.end());    
    std::vector<std::vector<int> > triplets;    
    for(unsigned int i = 0  ; i < nums.size() - 2; i++) {
        for(unsigned int j = i+1; j < nums.size() - 1; j++) {
            std::vector<int>::iterator it = lower_bound(nums.begin() + j + 1, nums.end(), -1*(nums[i] + nums[j]));
            // Prevent k from going out of bounds
            if (it == nums.end()){
                continue;
            }
            unsigned int k = it - nums.begin();
            if (nums[i] + nums[j] + nums[k] == 0) {
                std::vector<int> zero_triplet = {nums[i], nums[j], nums[k]};
                std::cout << "[" << nums[i] << ", " << nums[j] << ", " << nums[k] << "]" << std::endl;
                triplets.push_back(zero_triplet);
                continue;
            } else {
                std::cout << "\t(" << nums[i] << ", " << nums[j] << ", " << nums[k] << ")" << std::endl;
            }
            // TODO: Check for array index out of bounds
            while (nums[j] == nums[j + 1] && j < nums.size()) {
                j++;
            }
        }
        while (nums[i] == nums[i + 1] && i < nums.size()) {
            i++;
        }
    }
    return triplets;
}

void printArr(std::vector<int> arr) {
    std::cout << "[";
    for (int i : arr) {
        std::cout << " " << i;
    }
    std::cout << " ]" << std::endl;
}

std::vector<std::vector<int>> Solution::threeSumFastest(std::vector<int>& input) {
    std::cout << "threeSumFastest" << std::endl;
    printArr(input);
    
    if (input.size() < 3) {
        return std::vector<std::vector<int>> {};
    }
    
    std::vector<int> nums(input);
    sort(nums.begin(), nums.end());
    std::cout << "Sorted: ";
    printArr(nums);
    // nums.erase(std::unique(nums.begin(), nums.end()), nums.end());
    std::list<std::vector<int> > triplets;
    



        std::vector<int>::iterator it = nums.begin();
        while (it < nums.end() - 2) {
            std::vector<int>::iterator lower = it + 1;
            std::vector<int>::iterator upper = nums.end() - 1;
            std::cout << "it: " << distance(nums.begin(), it) << ", lower: " << distance(nums.begin(), lower) << ", upper: " << distance(nums.begin(), upper) << std::endl;
            while (lower < upper) {
                int sum = (*it) + (*lower) + (*upper);
                if (sum < 0) {
                    lower++;
                } else if (0 < sum) {
                    upper--;
                } else {
                    std::cout << "Found triplet " << *it << ", " << *lower << ", " << *upper << std::endl << "Moving lower and upper." << std::endl << "lower: ";
                    triplets.push_back({*it, *lower, *upper});
                    int previous_lower = *lower;
                    while (lower < upper && (previous_lower == *lower)) {
                        lower++;
                    }
                    std::cout << distance(nums.begin(), lower) << ", upper: ";
                    int previous_upper = *upper;
                    while (lower < upper && (*upper == previous_upper)) {
                        upper--;
                    }
                    std::cout << distance(nums.begin(), upper) << std::endl;
                }
            }
            int previous_it = *it;
            while (it < nums.end() - 2 && previous_it == *it) {
                it++;
            }
        }


    
    return std::vector< std::vector<int> >(triplets.begin(), triplets.end());
}

} // namespace three_sum

