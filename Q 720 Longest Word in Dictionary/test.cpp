#include <iostream>
#include <assert.h>
#include "src/longestword.cpp"

using namespace std;

int main () {
	Solution * sol;
	sol = new Solution();
	vector<string> words1 {"w","wo","wor","worl", "world"};
	assert(sol->longestWord(words1) == "world");
	delete sol;
	
	sol = new Solution();
	vector<string> words2 {"a", "banana", "app", "appl", "ap", "apply", "apple"};
	assert(sol->longestWord(words2) == "apple");
	delete sol;
	
	
	return 0;
}