class Solution {
public:
    /*
    map<string, int> prefixes;
    string longestCommonPrefix(vector<string>& strs) {
        // Iterate though each string
        for (string & str : strs) {
            // Iterate through each prefix
            for (int i = 0; i < str.length; i++) {
                // Find each prefix
                string prefix = 
                // Check if the prefix is in the binary search tree
                // If the prefix is in the search tree, then increment it's count by 1
                // If the prefix is not in the binary search tree, then decrement it's count by 1
            }
            
        }
        
        
        
        // Find the value in tree with the highest count
    }
    */
    
    // Returns the length (in both strings) of the max common prefix of the 2 strings 
    int maxCommonPrefixLength (string& str1, string& str2) {
        int i = 0;
        for (; i < str1.length() && i < str2.length(); i++) {
            if (str1[i] != str2[i]) {
                break;
            }
        }
        return i;
    }
    
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) {
            return "";
        }
        
        string commonPrefix = strs[0];    // Initially, the max common substring to the 1st string is the 1st string
        
        // Iterate through each pair of string, and find the most common so far
        for (int i = 1; i < strs.size(); i++) {
            commonPrefix = commonPrefix.substr( 0, maxCommonPrefixLength(commonPrefix, strs[i]) );
        }
        return commonPrefix;
    }
};


// TODO: Speed this up by sorting the array. Then look for longest common substring, in 1 pass.