

// Max size that thw whitelist can take up, before using blacklist
#define MAX_WHITELIST_SIZE 1048576	//	2^20 //4294967296	// 2^32

// 1048576	//	2^20

// Probability that a randomly guessed number is not in the blacklist
#define MIN_PROBABILITY_OF_VALID_GUESS 0.50	// 50

/**
* ***** Algorithm: *****
1) Given a positive integer N and blacklist with B elements, calculate the probability that an random guess of an integer from [0, N) is not within B.
	P(k not in B) = (N - B)/N = 1 - (B/N) = 1 - P(k in B)
2) To reduce guesses that are blacklisted: Choose a threshold probability MIN_PROBABILITY_OF_VALID_GUESS to use guessing instead of whitelist.
   If the probability P (of a valid guess) is greater than or equal to 0.90 (90%) then it is more time-efficient to use a blacklist.
	ie: if (N - B)/N >= MIN_PROBABILITY_OF_VALID_GUESS then use blacklist
		1 - (B/N) >= 0.90
		1 >= (B/N) + 0.90
		0.10 >= B/N
		0.10*N >= B
		10*N >= 100*B
		
   
   To reduce memory footprint of whitelist:
   If the potential whitelist size (N - B) would be over MAX_WHITELIST_SIZE, then it is more memort-efficient use a blacklist.
	ie: if (N - B) > MAX_WHITELIST_SIZE then use blacklist
		N > B + MAX_WHITELIST_SIZE
	So guess randomly and check that the guess is not in a blacklist (by binary searching the blacklist).

3) Or else (if the probability P is less than 0.90 and the whitelist size is under MAX_WHITELIST_SIZE), then create a whitelist.
	
	So only pick numbers from the whitelist.
*/



class Solution {
public:

    
	// Will always be used
    vector<int> blacklist;	// Stores numbers that can NOT be used.
	
	// ONLY used if creating a whitelist, which depends on the ratio of N and the size of the blacklist.
	vector<int> whitelist;	// Stores numbers that CAN be used.
	
    bool using_blacklist = false;	// Indicates whether a blacklist or whitelist will be used
    int N;	// The range of random numbers is from [0, N)
    
    Solution(int N, vector<int>& blacklist) {
        this->N = N;	// Store the random integer range in a class variable
		
		// Create a copy of the blacklist (if it is not already sorted)
		printf("Copying blacklist ...\n");
		this->blacklist = vector<int>(blacklist);	// Create a copy of the blacklist
		printf("... Done copying blacklist\n");
		// Sort the blacklist
		printf("Sorting blacklist ...\n");
		sort((this->blacklist).begin(), (this->blacklist).end());
		printf("... Done sorting blacklist\n");
        // If the blacklist is empty, we do not need to store it
		
		//bool more_efficient_to_use_blacklist = (N * (100 - MIN_PROBABILITY_OF_VALID_GUESS) >= 100* blacklist.size())	// time-efficient
		//									|| (N - blacklist.size() >  MAX_WHITELIST_SIZE);					// memory-efficient
		
		bool more_efficient_to_use_blacklist = ((double)(N - blacklist.size()) / (double)N >= (double)MIN_PROBABILITY_OF_VALID_GUESS)	// time-efficient
											|| (N - blacklist.size() >  MAX_WHITELIST_SIZE);					// memory-efficient
		
        if (more_efficient_to_use_blacklist) {
            using_blacklist = true;
            
        } else {
			printf("Creating whitelist ...\n");
            // If there are elements in the blacklist, then build a whitelist
            whitelist.resize( N - blacklist.size() );

			// Build whitelist by finding every integer in [0, N) that is not in the blacklist.
			// Since the blacklist is now sorted, we can use a clever trick to add all numbers not in it, and only parsing the blacklist once.
            int black_index = 0;	// current index in blacklist
            int white_index = 0;	// current index in whitelist
            for (int candidate = 0; candidate < N; candidate++) {
                if (black_index < (this->blacklist).size() && candidate == this->blacklist[black_index]) {
                    black_index++;
                    continue;
                }

                // Add items not on blacklist
                whitelist[white_index] = candidate;
                white_index++;
            }
			printf("... Done creating whitelist\n");
        }
		printf("Setup is finished!\n");
    }
    
    int pick() {
        if (using_blacklist) {
			// if the blacklist is empty, we do not use it
			if (blacklist.size() == 0) {
				return rand() % N;
			}
			
			int random_guess;
			do {
				random_guess = rand() % N;
				
				// Check if random guess is in the blacklist
				// Use binary search (returns true if the number is in the list, and false otherwise)
				// Continue until a number is guessed that is not in the blacklist
				// Note: blacklist might be an empty vector
			} while ( binary_search(blacklist.begin(), blacklist.end(), random_guess) );
			
			return random_guess;
        }
        
        // If there is not a blacklist, then choose only from the whitelist
        return whitelist[rand()%whitelist.size()];
    }
};

/*
Probability that a guess is not on blacklist:
P = (N - B)/N = 1 - (B/N)



Case 2:		If P is close to 0, then we can create a whitelist (or blacklist), and pick from it.
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
	4) B is small and N is large
		Create a blacklist, and choose the a number not on it.

*/

// TODO: make your own random integer function that uses rand() as a seed (each time pick() is called), and can generate randomly many more random numbers. This can minimize calls to rand().
// TODO: Only copy the blacklist if it is not already sorted. Otherwise just reference the blacklist. This can save memory

// Some sample solutions:
// https://stackoverflow.com/questions/6443176/how-can-i-generate-a-random-number-within-a-range-but-exclude-some
// https://codereview.stackexchange.com/questions/213397/uniformly-generate-a-number-from-0-to-n-1-that-isnt-on-a-blacklist

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(N, blacklist);
 * int param_1 = obj->pick();
 */