#define NUM_LEDS 6

/*
Basic algorithm:

1) For the number of the "num" "on" bits, declare an array to track the index position (in the clock) of each "on" bit
2) Initialize the on bit positions to the leftmost, so the first bit is at index 0, the second is at 1 ... and the last is at n-1.
3) Increment the "travel" bit until it reaches the end. On each iteration, record the time and print it.
4) When the "travel" bit reaches the end, increment the next left bit by 1, and reset the bits to the right of it, so they are ascending from it.
5) Do this until all the travel bits reach the end (until the travel bit is 0, and the travel bit is in index NUM_LEDS - num)

Example n=3 
 0  1  2  3  4  5
[1, 1, 1, 0, 0, 0] Starting position
[1, 1, 0, 1, 0, 0]
[1, 1, 0, 0, 1, 0]
[1, 1, 0, 0, 0, 1] The "travel" bit reached the end. So increment the next bit, and then reset the travel bit next to it
[1, 0, 1, 1, 0, 0]
[1, 0, 1, 0, 1, 0]
...
[1, 0, 0, 0, 1, 1]
[0, 1, 1, 1, 0, 0] The "travel" bits have reached the end. So increment the next bits and reset all travel bits
...
[0, 0, 0, 1, 1, 1] all done!!!
...

During this process, the 3 bit indexes of bits a, b, and c where a is left of b which is left of c (a < b < c) are as such:
a, b, c
-------
0, 1, 2 Starting position
0, 1, 3
0, 1, 4
0, 1, 5 The "travel" bit reached the end. So increment the next bit, and then reset the right one
0, 2, 3
0, 2, 4
0, 2, 5
0, 3, 4
0, 3, 5 Travel bit is at end. Increment the previous bit and reset the travel bit and all bits to thr right of it
0, 4, 5
1, 2, 3 The "travel" bit reached the end. So increment the next bit, and then reset the right one
1, 2, 4
1, 2, 5 At end
1, 3, 4
1, 3, 5
1, 4, 5 // The travel bit, which is now 4, is at the end of it's journey (it is at index NUM_LEDS - num). So choose the new travel bit
2, 3, 4
2, 3, 5
2, 4, 5 // At end again. Reset again
3, 4, 5 all done!

*/

class Solution {
public:
    string toTimeStr (int hrs, int min) {
        //string hour (itoa(hrs, 10));
        string hour = to_string(hrs);
        char min_arr [2];
        snprintf(min_arr, 2, "%01d", min);
        //if (itoi)
        string minute (min_arr);
        
        return hour + ":" + minute;  
    }
    
    vector<string> readBinaryWatch(int num) {
        
        vector<string> times;
        //TODO: pre-allocate strings to size of C(NUM_LEDS, nums) using combination
        //times.resize() 
        
        // Ensure the number of "on" bits can actually represented on the given amount of LEDs
        assert(num <= NUM_LEDS);
        
        //vector<int> leds (0, NUM_LEDS);
        vector<int> led_indexes (num, 0);   // Index of each "on" LED.
        
        // index (from 0 to num) of the bit in led_indexes that needs to move next iteration
        //int travel_bit =  led_indexes.size() - 1;   
        //assert(travel_bit == num - 1);  // Should be same as num - 1
        
        
        
        int travel_bit = 0; // Used for initial setup, to set led_indexes to initial positions
        
        
        do {

            // At this state, travel_bit will have been the last bit that has moved
            // Set all the bits after the travel bit to positions immediately after it
            for (int i = travel_bit; i < led_indexes.size(); i++) {
                led_indexes[i] = i; // All bits after (right of) the travel bit are set to positions immediately after the travel bit
            }

            // Set the new travel bit
            // This should be the first "1" that has a "0" to the right of it.
            travel_bit = led_indexes.size() - 1;    // This is the last bit in led_indexes.size()
            for (; travel_bit > 0; travel_bit--) {
                
            }
            
            // print the binary
            
        
        } while (led_indexes[travel_bit] < NUM_LEDS - num && travel_bit != 0);
        
    }
};