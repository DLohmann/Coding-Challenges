class Solution {
public:
    vector<int> whitelist;
    
    // These 2 variables are only used if the blacklist is empty
    bool empty_blacklist = false;
    int empty_N_size = -1;
    
    Solution(int N, vector<int>& blacklist) {
        
        
        // If the blacklist is empty, we do not need to store it
        if (blacklist.size() == 0) {
            empty_blacklist = true;
            empty_N_size = N;
            
        } else {
            // If there are elements in the blacklist, then build a whitelist
            whitelist.resize( N - blacklist.size() );
            vector<int> black_sorted(blacklist);

            sort(black_sorted.begin(), black_sorted.end());

            int black_index = 0;
            int white_index = 0;
            for (int candidate = 0; candidate < N; candidate++) {
                if (black_index < black_sorted.size() && candidate == black_sorted[black_index]) {
                    black_index++;
                    continue;
                }

                // Add items not on blacklist
                whitelist[white_index] = candidate;
                white_index++;
            }
        }
    }
    
    int pick() {
        if (empty_blacklist) {
            return rand()%empty_N_size;
        }
        
        // If there is a blacklist, then choose only from the whitelist
        return whitelist[rand()%whitelist.size()];
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(N, blacklist);
 * int param_1 = obj->pick();
 */