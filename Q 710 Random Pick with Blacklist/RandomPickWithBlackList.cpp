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

/*
Probability that a guess is not on blacklist:
P = (N - B)/N = 1 - (B/N)



Case 2:		If P is close to 0, then we can create a whitelist, and pick from it.
Case 1&3:	If P is close to 1, we can just guess.


Cases:
	1) Empty blacklist.
		Guess a random number
		
		Constructor:	O(1) runtime, O(1) memory
		Pick:			O(1) runtime, O(1) memory
	2) N < 100000.
		Create a whitelist, and choose from it.
	
		Constructor:	O(N + (B*log(B)) ) runtime, O(N-B) memory
		Pick:			O(1) runtime, O(N-B) memory
	3) N >= 100000
		Keep guessing a random number, and stop if it is not in blacklist.
		

*/

// Some sample solutions:
// https://stackoverflow.com/questions/6443176/how-can-i-generate-a-random-number-within-a-range-but-exclude-some
// https://codereview.stackexchange.com/questions/213397/uniformly-generate-a-number-from-0-to-n-1-that-isnt-on-a-blacklist

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(N, blacklist);
 * int param_1 = obj->pick();
 */