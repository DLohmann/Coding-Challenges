#include <iostream>
#include <assert.h>
#include "src/longestword.cpp"

using namespace std;

int main () {
	
	Solution * sol;
	sol = new Solution();
	vector<string> words1 {"a","ab","abc","bc", "world"};
	sol->insertWords(words1);
	list<string> l = sol->findAllWords();
	for (string word : l) {
		cout << "\t" << word << endl;
	}
	cout << "Length of l is: " << l.size() << endl;
	//assert(sol->longestWord(words1) == "world");
	delete sol;
	
	/*
	Solution * sol;
	sol = new Solution();
	vector<string> words1 {"w","wo","wor","worl", "world"};
	assert(sol->longestWord(words1) == "world");
	delete sol;
	
	sol = new Solution();
	vector<string> words2 {"a", "banana", "app", "appl", "ap", "apply", "apple"};
	assert(sol->longestWord(words2) == "apple");
	delete sol;
	*/
	
	return 0;
}