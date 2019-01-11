#include <iostream>
#include <vector>
#include <algorithm> // has max_element

#define testing_isValidSudoku
//#define debug_statements_isValidSudoku


// Include testing libraries
#ifdef testing_isValidSudoku
#include <assert.h>
#endif

// Description:
// Tests if a sudoku puzzle is valid.
// Based on this LeetCode challenge: https://leetcode.com/problems/sudoku-solver/


using namespace std;

bool isValidSudoku(vector< vector< char > >& board) {
	// Check that each row, column, and 3 by 3 cell contains at most one of each number 0-9
	
	// Check that dimensions are correct
	if (board.size() != 9) {
		#ifdef debug_statements_isValidSudoku
			cout << "Wrong dimensions: " << board.size()    << " rows." << endl;
		#endif
		return false;
	}
	if (board[0].size() != 9) {
		#ifdef debug_statements_isValidSudoku
			cout << "Wrong dimensions: " << board[0].size() << " columns." << endl;
		#endif
		return false;
	}
	
	// Check that all characters are valid ('0' - '9', and '.')
	for (int row = 0; row < board[0].size(); row++) {
		for (int column = 0; column < board.size(); column++) {
			
			// Skip over '.' characters, which mean the board is empty there
			if (board[row][column] == '.') {
				continue;
			}

			// Check that value is in rangle
			if (board[row][column] < '1' || '9' < board[row][column]) {
				#ifdef debug_statements_isValidSudoku
					cout << "Invalid character at board[" << row << "][" << column << "] == " << board[row][column] << endl;
				#endif
				return false;
			}
		}
	}

	// Contians count of each number
	vector <int> counter;

	// Check rows:
	for (int row = 0; row < board[0].size(); row++) {
		counter =  vector<int>(10, 0);	// Initialize to all 0's
		for (int column = 0; column < board.size(); column++) {
			// Convert the character to an integer, and increment the counter
			counter[ (int)(board[row][column] - '1') ] += 1;
		}
		// Check for duplicate values in the row
		if (*max_element(counter.begin(), counter.end()) > 1) {
			#ifdef debug_statements_isValidSudoku
				cout << "Error: Duplicate value(s) in row " << row << endl;
			#endif
			return false;
		}
	}
	

	// Check columns:
	for (int column = 0; column < board.size(); column++) {
		counter =  vector<int>(10, 0);	// Initialize to all 0's
		for (int row = 0; row < board[0].size(); row++) {
			// Convert the character to an integer, and increment the counter
			counter[ (int)(board[row][column] - '1') ] += 1;
		}
		// Check for duplicate values in the row
		if (*max_element(counter.begin(), counter.end()) > 1) {
			#ifdef debug_statements_isValidSudoku
				cout << "Error: Duplicate value(s) in column " << column << endl;
			#endif
			return false;
		}
	}

	// Check 3 by 3 regions (we think of each 3 by 3 region as being in a grid, where the entire region has it's own regionRow and regionColumn)
	//cout << endl;
	for (int regionRow = 0; regionRow < 3; regionRow++) {
		for (int regionColumn = 0; regionColumn < 3; regionColumn++) {
			counter =  vector<int>(10, 0);	// Initialize to all 0's
			//cout << "\tChecking region (" << regionRow << ", " << regionColumn << ")" << endl;
			for (int index = 0; index < 9; index++) {	// "index" is the position of the cell relative to the region
				int row = 		(3*regionRow)    + (index/3);
				int column = 	(3*regionColumn) + (index%3);
				int cell_element = (int)(board[row][column] - '1');
				//cout << "\t\tboard[" << row << "][" << column << "] == " << (char)board[row][column] << endl;
				counter [cell_element] += 1;
			}
			//cout << "\tCounter is: " << counter[0];
			//for (int i = 1; i < 9; i++) {
			//	cout << ", " << counter[i];
			//}
			//cout << endl;

			// Check for duplicate values in the region
			if (*max_element(counter.begin(), counter.end()) > 1) {
				#ifdef debug_statements_isValidSudoku
					cout << "Error: Duplicate value(s) in region (" << regionRow << ", " << regionColumn << ")" << endl;
				#endif
				return false;
			}
		}
	}

	// If the puzzle satisifies the above conditions (no duplicate numbers in row, column, or region, and all characters are '0' - '9'), then the puzzle is valid
	return true;
}

#ifdef testing_isValidSudoku
	void tester_isValidSudoku () {
		cout << "Testing \"Is Valid Sudoku\" function" << endl;

		vector< vector< char > > board;

		cout << "Test case 1: ";
		// Test case 1 (from LeetCode example), a correct example
		board = {
			{'5','3','.',   '.','7','.',   '.','.','.'},
			{'6','.','.',   '1','9','5',   '.','.','.'},
			{'.','9','8',   '.','.','.',   '.','6','.'},

			{'8','.','.',   '.','6','.',   '.','.','3'},
			{'4','.','.',   '8','.','3',   '.','.','1'},
			{'7','.','.',   '.','2','.',   '.','.','6'},

			{'.','6','.',   '.','.','.',   '2','8','.'},
			{'.','.','.',   '4','1','9',   '.','.','5'},
			{'.','.','.',   '.','8','.',   '.','7','9'}
		};
		assert(isValidSudoku(board) == true);
		cout << "passed!" << endl;
		
		// Test case 2, an empty board is valid
		cout << "Test case 2: ";
		board = {
			{'.', '.', '.',   '.', '.', '.',   '.', '.', '.'},
			{'.', '.', '.',   '.', '.', '.',   '.', '.', '.'},
			{'.', '.', '.',   '.', '.', '.',   '.', '.', '.'},
			
			{'.', '.', '.',   '.', '.', '.',   '.', '.', '.'},
			{'.', '.', '.',   '.', '.', '.',   '.', '.', '.'},
			{'.', '.', '.',   '.', '.', '.',   '.', '.', '.'},
			
			{'.', '.', '.',   '.', '.', '.',   '.', '.', '.'},
			{'.', '.', '.',   '.', '.', '.',   '.', '.', '.'},
			{'.', '.', '.',   '.', '.', '.',   '.', '.', '.'}
		};
		assert(isValidSudoku(board) == true);
		cout << "passed!" << endl;

		// Test case 3 (From LeetCode example, but added a 2 in the same row as another 2), the only error should be a duplicate in a row
		cout << "Test case 3: ";
		board = {
			{'5','3','.',   '.','7','.',   '.','.','.'},
			{'6','.','.',   '1','9','5',   '.','.','.'},
			{'.','9','8',   '.','.','.',   '.','6','.'},

			{'8','.','.',   '.','6','.',   '.','.','3'},
			{'4','.','.',   '8','.','3',   '.','.','1'},
			{'7','.','.',   '.','2','.',   '.','.','6'},

			{'.','6','2',   '.','.','.',   '2','8','.'},
			{'.','.','.',   '4','1','9',   '.','.','5'},
			{'.','.','.',   '.','8','.',   '.','7','9'}
		};
		assert(isValidSudoku(board) == false);
		cout << "passed!" << endl;

		// Test case 4 (From LeetCode example, but added an 8 in the same column as another 8), the only error should be a duplicate in a column
		cout << "Test case 4: ";
		board = {
			{'5','3','.',   '.','7','.',   '.','.','.'},
			{'6','.','.',   '1','9','5',   '.','8','.'},
			{'.','9','8',   '.','.','.',   '.','6','.'},

			{'8','.','.',   '.','6','.',   '.','.','3'},
			{'4','.','.',   '8','.','3',   '.','.','1'},
			{'7','.','.',   '.','2','.',   '.','.','6'},

			{'.','6','.',   '.','.','.',   '2','8','.'},
			{'.','.','.',   '4','1','9',   '.','.','5'},
			{'.','.','.',   '.','8','.',   '.','7','9'}
		};
		assert(isValidSudoku(board) == false);
		cout << "passed!" << endl;

		// Test case 5 (From LeetCode example, but added a 6 in the same region as another 6), the only error should be a duplicate in a 3 by 3 region
		cout << "Test case 5: ";
		board = {
			{'5','3','.',   '.','7','.',   '.','.','.'},
			{'6','.','.',   '1','9','5',   '.','.','.'},
			{'.','9','8',   '.','.','.',   '.','6','.'},

			{'8','.','.',   '.','6','.',   '.','.','3'},
			{'4','.','.',   '8','.','3',   '.','.','1'},
			{'7','.','.',   '.','2','.',   '.','.','6'},

			{'.','6','.',   '.','.','.',   '2','8','.'},
			{'.','.','.',   '4','1','9',   '.','.','5'},
			{'.','.','6',   '.','8','.',   '.','7','9'}
		};
		assert(isValidSudoku(board) == false);
		cout << "passed!" << endl;
		return;
	}
#endif

int main () {
	#ifdef testing_isValidSudoku
		tester_isValidSudoku();
	#endif

	cout << "Hello world!" << endl;
	return 0;
}