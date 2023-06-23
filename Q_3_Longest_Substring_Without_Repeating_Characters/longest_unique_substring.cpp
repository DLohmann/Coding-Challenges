#include"longest_unique_substring.h"

#include<vector>
#include<list>
#include<set>
#include<algorithm>
#include<iostream>

namespace longestuniquesubstring {

int Solution::lengthOfLongestSubstring(std::string s) {
        if (s.empty()){
					return 0;
				}
				int max_length = -1;
				for (int start = 0; start < s.length(); start++){
					std::set<char> contained_characters;
					int current_length = 0;
					for (int end = start; end < s.length(); end++) {
						std::set<char>::iterator it = contained_characters.find(s.at(end));
						if (it == contained_characters.end()){
							contained_characters.insert(s.at(end));
							current_length++;
							if (current_length > max_length) {
								max_length = current_length;
							}
						} else {
							break;
						}
					}
				}
				return max_length;
    }

} // namespace longestuniquesubstring

