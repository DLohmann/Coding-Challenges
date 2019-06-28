class Solution {
public:
    static bool triplet_compare(vector<int> a, vector<int> b) {
        // a < b
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
    vector<vector<int>> threeSum(vector<int>& nums) {
        if (nums.size() < 3) {
            return  vector<vector<int>> {};
        }
        
        sort(nums.begin(), nums.end());
        
        // Sort the nums vector, and remove duplicates (so that none of the solution sets have duplicates):
        /*
        set<int> s;
        unsigned size = nums.size();
        for( unsigned i = 0; i < size; ++i ) {
            s.insert( nums[i] );
        }
        nums.assign( s.begin(), s.end() );
        */
        cout << "nums is: " << nums[0];
        for (int i = 1; i < nums.size(); i++) {
            cout << ", " << nums[i];
        }
        cout << endl;
        
        list< vector<int> > triplets;
        int i, j, k;
        for(int i = 0  ; i < nums.size() - 2; i++) {
        for(int j = i+1; j < nums.size() - 1; j++) {
        for(int k = j+1; k < nums.size()    ; k++) {
            if (nums[i] + nums[j] + nums[k] == 0 && // Check if it's 0
               !binary_search(triplets.begin(), triplets.end(), vector<int>{nums[i], nums[j], nums[k]}, triplet_compare ) // Check if it's already in triplets
               ) {
                
                
                
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
        
        // Remove duplicates
        
        
        return sums;
    }
};

/*
Helpful links:
https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector

*/