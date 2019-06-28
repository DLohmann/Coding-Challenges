class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // Sort the nums vector, and remove duplicates (so that none of the solution sets have duplicates):
        //sort(nums.begin(), nums.end());
        set<int> s;
        unsigned size = nums.size();
        for( unsigned i = 0; i < size; ++i ) {
            s.insert( nums[i] );
        }
        nums.assign( s.begin(), s.end() );
        
        cout << "nums is: " << nums[0];
        for (int i = 1; i < nums.size(); i++) {
            cout << ", " << nums[i];
        }
        cout << endl;
        
        list< vector<int> > triplets;
        for(int i = 0  ; i < nums.size() - 2; i++) {
        for(int j = i+1; i < nums.size() - 1; j++) {
        for(int k = j+1; i < nums.size()    ; k++) {
            if (nums[i] + nums[j] + nums[k] == 0) {
                
                vector<int> zero_triplet = {nums[i], nums[j], nums[k]};
                //sort(triplet.begin(), triplet.end());
                cout << "[" << nums[i] << ", " << nums[j] << ", " << nums[k] << "]" << endl;
                //cout << "[" << i << ", " << j << ", " << k << "]" << endl;
                triplets.push_back(zero_triplet);
                continue;
                
            } else {
                cout << "\t(" << nums[i] << ", " << nums[j] << ", " << nums[k] << ")" << endl;
                //cout << "\t(" << i << ", " << j << ", " << k << ")" << endl;
                
            }
        }
        }
        }
        vector< vector<int> > sums {triplets.begin(), triplets.end()};
        
        return sums;
    }
};

/*
Helpful links:
https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector

*/