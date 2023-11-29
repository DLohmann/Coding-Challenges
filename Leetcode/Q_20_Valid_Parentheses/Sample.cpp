#include"Sample.h"

#include<list>
#include<map>
#include<algorithm>
#include<iostream>

namespace sample {


bool Solution::isValid(std::string s) {
    // Records closing symbols and their corresponding opening symbols
    std::map<char, char> symbol_map = {
        {')','('},
        {'}','{'},
        {']','['}
    };
    std::list<int> to_close;
    for (char& c : s) {
        char symbol = c;
        std::map<char, char>::iterator symbol_map_it = symbol_map.find(symbol);
        // check for open or close symbol
        if (symbol_map_it == symbol_map.end()){
            // open symbol
            to_close.push_back(symbol);
        } else {
            // close symbol
            // check if the symbol to close is corresponding symbol
            if (to_close.back() == symbol_map_it->second) {
                to_close.pop_back();
            } else {
                return false;
            }
        }
    }
    if (!to_close.empty()) {
        return false;
    }
    return true;
}

} // namespace sample

