#include <iostream>
#include <vector>


//#define debug_statements

#define test_pivotIndex
#define test_binarySearch

#if defined test_pivotIndex || defined test_binarySearch
#include <assert.h>
#endif

using namespace std;
//class Solution {
//public:

    /* 
    Basic algorithm:
    1) Find the pivot: Use this basic algorithm.
        1) set the lower bound to left side and upper bound to right side of array
        2) Find the middle value of the interval
        3) If the middle value is greater than left bound's value, then set the left bound to index of middle value
        4) If the middle value is less than the right bound's values, then set the right bound to the index of middle value
        5) Repeat steps 2-4 until left bound equals right bound
    
    2) Pivot splits the array into 2 parts. Determine whether the left or the right part contains the target
    3) Binary search the side of the array that contains the target.
    
    */
    
    // Returns the index in nums of the element searched for
    int binarySearch (vector<int>& nums, int leftIndex, int rightIndex, int target) {
        // Ensure indexes are within array bounds
        if (leftIndex < 0) {
            leftIndex = 0;
        }
        if (rightIndex >= nums.size()) {
            rightIndex = nums.size() - 1;
        }
        
        // Ensure target is within the array values
        // if(target < nums[0] || nums[nums.size() - 1] < target) {
            // return -1;  // return not found if it is out of the possible values
        // }
        
        #ifdef debug_statements
            cout << "\tCalled binarySearch (leftIndex = " << leftIndex << ", rightIndex = " << rightIndex << ")" << endl;
        #endif
        
        
        
        int middleIndex = (leftIndex + rightIndex)/2;
        if (nums[middleIndex] == target) {
            return middleIndex;
        }
        if (leftIndex >= rightIndex) {
            return -1;
        }
        if (target < nums[middleIndex]) {
            return binarySearch(nums, leftIndex, middleIndex, target);
        }
        return binarySearch(nums, middleIndex + 1, rightIndex, target);

    }
    
    // Returns index of minimum value in array
    int pivotIndex (vector<int>& nums, int leftIndex, int rightIndex) {
        // Ensure indexes are within array bounds
        if (leftIndex < 0) {
            leftIndex = 0;
        }
        if (rightIndex >= nums.size()) {
            rightIndex = nums.size() - 1;
        }
        #ifdef debug_statements
            cout << "\tCalled pivotIndex (leftIndex = " << leftIndex << ", rightIndex = " << rightIndex << ")" << endl;
        #endif
        if (leftIndex >= rightIndex - 1) {
            if (nums[leftIndex] >= nums[rightIndex]) {
                return rightIndex;
            } else {
                return leftIndex;
            }
            
        }
        
        int middleIndex = (leftIndex + rightIndex)/2;
        
        
        if (nums[middleIndex] <= nums[rightIndex]) {
            rightIndex = middleIndex;
            #ifdef debug_statements
                cout << "\tmoving right index to " << rightIndex << endl;
            #endif
        } else if (nums[leftIndex] <= nums[middleIndex]) {
            leftIndex = middleIndex;
            #ifdef debug_statements
                cout << "\tmoving left index to " << leftIndex << endl;
            #endif
        }
        
        return pivotIndex (nums, leftIndex, rightIndex);
    }
    
    int search(vector<int>& nums, int target) {
        // Check that the array is not empty
        if (nums.size() <= 0) {
            return -1;
        }
        
        #ifdef debug_statements
            cout << "Called search!" << endl;
        #endif
        int pivotInd = pivotIndex (nums, 0, nums.size());
        
        #ifdef debug_statements
            cout << "Pivot index is: " << pivotInd << endl;
        #endif
        
        // Check if pivot is in the left side of the array:
        if (nums[0] <= target && target <= nums[pivotInd - 1]) {
            return binarySearch (nums, 0, pivotInd - 1, target);
        }
        
        // Check if pivot is in the right side of the array
        if (nums[pivotInd] <= target && target <= nums[nums.size() - 1]) {
            return binarySearch (nums, pivotInd, nums.size() - 1, target);
        }
        
        // If target is not found, return -1
        
        
        
        return -1;
    }
//};

void printArr (vector<int>& nums) {
    
    for (int i = 0; i < nums.size(); i++) {
        cout << i << "\t";
    }
    
    cout << endl;
    
    cout << nums[0];
    
    for (int i = 1; i < nums.size(); i++) {
        cout << ",\t" << nums[i];
    }
    
    cout << endl;
    
}

#ifdef test_pivotIndex
    void testPivotIndex () {
        #ifdef debug_statements
            cout << "\n\nTESTING PIVOT_INDEX" << endl;
        #endif
        vector<int> nums_test;
        //           0, 1, 2, 3, 4, 5, 6
        nums_test = {1, 2, 4, 5, 6, 7, 0};
        assert (pivotIndex(nums_test, 0, nums_test.size()) == 6);
        
        nums_test = {2, 4, 5, 6, 7, 0, 1};
        assert (pivotIndex(nums_test, 0, nums_test.size()) == 5);
        
        nums_test = {4, 5, 6, 7, 0, 1, 2};
        assert (pivotIndex(nums_test, 0, nums_test.size()) == 4);
        
        nums_test = {5, 6, 7, 0, 1, 2, 4};
        assert (pivotIndex(nums_test, 0, nums_test.size()) == 3);
        
        nums_test = {6, 7, 0, 1, 2, 4, 5};
        assert (pivotIndex(nums_test, 0, nums_test.size()) == 2);
        
        nums_test = {7, 0, 1, 2, 4, 5, 6};
        assert (pivotIndex(nums_test, 0, nums_test.size()) == 1);
        
        nums_test = {0, 1, 2, 3, 4, 5, 6};
        assert (pivotIndex(nums_test, 0, nums_test.size()) == 0);
    }
#endif

#ifdef test_binarySearch
    void testBinarySearch() {
        #ifdef debug_statements
            cout << "\n\nTESTING BINARY SEARCH" << endl;
        #endif
        
        vector<int> nums_test;
        
        // Test with only one element
        nums_test = {1};
        assert (binarySearch(nums_test, 0, nums_test.size(), 1) == 0);
        assert (binarySearch(nums_test, 0, nums_test.size(), 2) == -1);
        
        // Test with empty vector
        nums_test = {};
        assert (binarySearch(nums_test, 0, nums_test.size(), 2) == -1);
        
        // test finding even numbers
        //           0, 1, 2, 3, 4, 5, 6
        nums_test = {0, 2, 4, 6, 8,10,12};
        for (int target = 0; target < nums_test.size(); target++) {
            
            // nums_test has only even numbers. So assert that even numbers were found and odd numbers were not
            if (target % 2 == 0) { // even numbers should be found
                assert(binarySearch(nums_test, 0, nums_test.size(), target) != -1);
            } else { // odd numbers should not be found
                assert(binarySearch(nums_test, 0, nums_test.size(), target) == -1);
            }
            
            // cout << "Target is: " << target << endl;
            // cout << "Array is:\n";
            // printArr(nums_test);
            // cout << "Array contains target?: " << search (nums, target) << endl;
            // cout << "Array contains target?: " << ((binarySearch(nums_test, 0, nums_test.size(), target) != -1)? "True" : "False") << "\n\n" << endl;
        }
        
        // test finding odd numbers
        //           0, 1, 2, 3, 4, 5, 6
        nums_test = {1, 3, 5, 7, 9, 11, 13};
        for (int target = 0; target < nums_test.size(); target++) {
            
            // nums_test has only odd numbers. So assert that odd numbers were found and even numbers were not
            if (target % 2 == 1) { // odd numbers should be found
                assert(binarySearch(nums_test, 0, nums_test.size(), target) != -1);
            } else { // even numbers should not be found
                assert(binarySearch(nums_test, 0, nums_test.size(), target) == -1);
            }
            
            // cout << "Target is: " << target << endl;
            // cout << "Array is:\n";
            // printArr(nums_test);
            // cout << "Array contains target?: " << search (nums, target) << endl;
            // cout << "Array contains target?: " << ((binarySearch(nums_test, 0, nums_test.size(), target) != -1)? "True" : "False") << "\n\n" << endl;
        }
        
    }
#endif

int main () {
    #ifdef test_pivotIndex
        testPivotIndex();
    #endif
    
    #ifdef test_binarySearch
        testBinarySearch();
    #endif
    
    
    vector <int> nums = {6, 7, 0, 1, 2, 4, 5};
    
    
    int target = 0;
    
    cout << "Array is: " << endl;
    printArr(nums);
    
    
    
    // Test findPivot
    cout << "Array pivot index is: " << pivotIndex(nums, 0, nums.size()-1) << "\n\n" << endl;
    
    
    
    return 0;
}