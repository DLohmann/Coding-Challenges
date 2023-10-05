
class Solution {
public:
    vector<vector<int>> minimumAbsDifference(vector<int>& arr) {
        cout<< "program began!" << endl; 
        if (arr.size() < 2){return vector<vector<int>>();}
        
        // Sort arr
        sort(arr.begin(), arr.end());
        // Find the min difference between adjacent elements
        // Pass through and find the min difference, and how many pairs with this difference there are.
        int min_diff = arr[1] - arr[0];
        int num_min_pairs = 0;
        for (vector<int>::iterator it = arr.begin(); it != --arr.end(); it++) {
            cout << "loop 1 iteration #" << it - arr.begin() << endl;
            int diff = *(it + 1) - *it;
            if (diff < min_diff) {
                min_diff = diff;
                num_min_pairs = 1;
            } else if (diff == min_diff) {
                num_min_pairs++;
            }
        }
        // Create a vector to hold the pairs
        vector<vector<int>> final_arr = vector(num_min_pairs, vector<int>(2));
        
        int final_arr_index = 0;
        // Pass through again and add the pairs to the final vector
        for (vector<int>::iterator it = arr.begin(); it != --arr.end(); it++) {
            cout << "loop 2 iteration #" << it - arr.begin() << endl;
            int diff = *(it + 1) - *it;
            if (diff < min_diff) {
                cout << "error!" << endl;
            } else if (diff == min_diff) {
                final_arr[final_arr_index][0] = *it;
                final_arr[final_arr_index][1] = *it;
                final_arr_index++;
            }
        }
        return final_arr;
    }
};