#include <iostream>
#include <assert.h>
#include <string.h>
#include <vector>
#include <unordered_set>

//#define debug_statements

using namespace std;


//class Solution {
//public:

/*
Basic Algorithm:
1) Iterate through the 2D vector of letters, and check if the each letter is the same as the first letter in the first letter in the word
2) If so, then call bool isWord(board, string word, int m, int n) at this letter's coordinates. This function isWord will:
	1) Check if the length of word is 0. If so, then return true.
	2) If the coordinates m or n are out of bounds of the board, then clear the list of explored coordinates, setting it to the empty set. And return false
	3) If the current coordinates have already been visited, then clear the list of explored coordinates, setting it to the empty set. And return false
	4)) If the first letter of word is not equal to the letter at coordinate (m, n), then return false.
	5) Remove the first letter from the word
	6) For each "neighbor" grid coordinate of coordinate (m, n), and call isWord on that coordinate, with the word that has the first character removed.
	7) Check if any of these function calls returns true				 // Iterate through every grid entry "neighbor" element of board. If the 
	8) If so, then add this letter's position (m, n) to the list of explored the set of explored coordinates, and return true 
	9) If not, then clear the list of explored coordinates, setting it to the empty set. And return false
3) If isWord, when called from exist, returns true, then return true.
4) If isWord returns false, then iterate to the next position in vector board.
5) If exists gets to the end of board without finding any matches, then return false.
*/

int M;  // M is the number of rows in the board.
int N;  // N is the number of columns.

unordered_set < int > exploredNodes;

int convertToID (int i, int j) {	
	return (i * N) + j;
}

bool isWord (vector<vector<char>>& board, string word, int m, int n) {
	// Check if a word match has already been found
	if (word.length() == 0) {
		#ifdef debug_statements
			cout << "A match has been found!" << endl;
		#endif
		return true;
	}
	// Check that coordinates are within board bounds
	if (!(0 <= m && m < M && 0 <= n && n < N)) {
		return false;
	}
	
	// Check if the letter matches what is searched for
	if (word[0] != board[m][n]) {
		return false;
	}
	#ifdef debug_statements
		cout << "Checking coordinate (" << m << ", " << n << ") at character '" << word[0] << "'" << endl;
	#endif
	
	// Remove first letter from word
	string newWord = word.substr(1);
	
	// Check if the position has been visited before
	if (exploredNodes.find(convertToID(m, n)) != exploredNodes.end()) {
		#ifdef debug_statements
			cout << "\texplored before" << endl;
		#endif
		return false;
	}
	
	// Add this position to list of explored positions
	auto position = exploredNodes.insert(convertToID(m, n));
	
	// Iterate through each neighbor, and check if any neighbor returns true.
	if (
		isWord (board, newWord, m	, n + 1) ||
		isWord (board, newWord, m	, n - 1) ||
		isWord (board, newWord, m + 1, n	) ||
		isWord (board, newWord, m - 1, n	)
	) {
		exploredNodes.clear();
		return true;
	}
	
	// Remove this letter from already visited letters
	exploredNodes.erase (exploredNodes.find(convertToID(m, n)));
	
	return false;
}

bool exist(vector<vector<char>>& board, string word) {
	#ifdef debug_statements
		cout << "\n\nCHECKING WORD \"" << word << "\"" << endl;
	#endif
	int len = word.length();
	if (len == 0) {
		return true;
	}
	M = board.size();
	if (M == 0) {
		return false;
	}
	N = board[0].size();	// Assume the board matrix is square (ie board[0].size() == board[1].size() == board[i].size() for all i)
	if (N == 0) {
		return false;
	}
	
	for (int m = 0; m < M; m++) {
		for (int n = 0; n < N; n++) {
			if (isWord(board, word, m, n)) {
				return true;
			}
		}
	}
	return false;
}
//};



int main () {
	
	vector< vector <char> > board =
	{	//0   1   2   3
		{'A','B','C','E'}, // 0
		{'S','F','C','S'}, // 1
		{'A','D','E','E'}  // 2
	};
	
	cout << "Beginning tests: " << endl;
	assert(exist(board, "ABCCED")	 == true);	// Given word = "ABCCED", return true.
	assert(exist(board, "SEE")		 == true);	// Given word = "SEE", return true.
	assert(exist(board, "ABCB")		 == false);	// Given word = "ABCB", return false.
	cout << "All tests passed!" << endl;
	
	
	return 0;
}


