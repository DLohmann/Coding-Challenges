#include <iostream>
#include <vector>
#include <list>
#include <algorithm> // has max_element, and find

#define testing_SudokuSolver
#define debug_statements_SudokuSolver


// Include testing libraries
#ifdef testing_SudokuSolver
#include <assert.h>


#endif

using namespace std;

#ifdef testing_SudokuSolver
void printMatrix (const vector< vector< char > >&);


#endif





// Description:
// Solves a sudoku puzzle.
// Based on this LeetCode challenge: https://leetcode.com/problems/sudoku-solver/

/*
Basic Algorithm:
1) Create a 9 by 9 (vector of vectors) matrix of empty lists.
2) For every number already in non-blank boxes of the puzzle, add these to the matrix list at the corresponding position
3) Iterate through each entry in the matrix. For each entry, iterate through the numbers 1-9 (all possible entries).
4) For all numbers that can go in a particular box, check which are valid (which are not already within the same 3 by 3 region, row, or column).
5) Add all numbers that can go into a box location to the list that corresponds to that box location. These numbers are the "candidates" because 
   they are the numbers that could possibly go at that location. So for each entry, find all the "candidate" numbers in [1, ... , 9] that are 
   not in the same row or column or region as that entry. And keep track of these in the list.
6) When there is only 1 candidate that is added to a list (only 1 candidate can go at that position), then add that candidate to the board, and 
   remove that number from that position's row, column, and region to avoid duplicates.
6) After iterating through the matrix, check if any changes were made to the matrix over the last pass (using a bolean that is set to false when beginning iterating
   through the matrix, and set to true when a change is made).If a change was made, then go back to step 3, iterating again. If not, then the 
   matrix is as solved as possible. If there is a unique solution, then it is found. If there are multiple solutions, then this structure 
   represents them.
7) If all lists in the matrix have a length of 1 (only 1 candidate), then the solution is unique, so the solution has been found.
*/


// Checks if the char 'val' can be correctly placed at the row and column in the sudoku puzzle 'board' without violating any rules of sudoku. 
bool isValidPlacement(vector< vector< char > >& board, char val, int row, int column) {
	// Check if val is in the row
	for (int position = 0; position < 9; position++) {
		if (board[row][position] == val) {
			return false;
		}
	}

	// Check if val is in the column
	for (int position = 0; position < 9; position++) {
		if (board[position][column] == val) {
			return false;
		}
	}

	int regionRow = 	row/3;
	int regionColumn = 	column/3;

	for (int position = 0; position < 9; position++) {
		int i = (3*regionRow)    + (position/3); // row    to compare to
		int j = (3*regionColumn) + (position%3); // column to compare to
		if (board[i][j] == val) {
			return false;
		}
	}

	// If no conflicts have been found, then the move is valid
	return true;
}

// returns whether the list contains the element
bool contains (list<char>& l, char val) {
	return find(l.begin(), l.end(), val) != l.end();
}

// Removes char 'val' from all the lists of candidates that are at the same row, column, or region as 'val''s position (row, column)
// After the char 'val' is KNOWN to be at position (row, column) and is the only a candidate, then remove all OTHER instances of 
// char 'val' in the SAME row, column, and region EXCEPT at the position (row, column).
void removeValue (vector< vector< list<char> > >& matrix, char val, int row, int column) {
	// Check if val is a candidate in the row
	for (int position = 0; position < 9; position++) {
		if (position == column) {	// Skip over the position that the value is supposed to be added in
			continue;
		}
		if (contains(matrix[row][position], val)) {	// Check if the list at that position (row and column) in the matrix contains the value to remove
			
			// Remove the value from the matrix
			matrix[row][position].remove(val);

		}
	}

	// Check if val is a candidate in the column
	for (int position = 0; position < 9; position++) {
		if (position == row) {	// Skip over the position that the value is supposed to be added in
			continue;
		}
		if (contains(matrix[position][column], val)) {
			// Remove the value from the matrix
			matrix[position][column].remove(val);
		}
	}

	// Check if val is a candidate in the region
	int regionRow = 	row/3;
	int regionColumn = 	column/3;
	for (int position = 0; position < 9; position++) {
		int i = (3*regionRow)    + (position/3); // row    to compare to
		int j = (3*regionColumn) + (position%3); // column to compare to

		if (i == row || j == column) {	// Skip over the position that the value is supposed to be added in (and positions that have already been removed from the row or column)
			continue;
		}

		if (contains(matrix[i][j], val)) {
			// Remove the value from the matrix
			matrix[i][j].remove(val);
		}
	}
}

int countInRow (vector< vector< list<char> > >& matrix, int row, char val) {
	int count = 0;
	// Iterate through row, and count how many times val appears
	for (int col = 0; col < 9; col++) {
		if (contains(matrix[row][col], val)) {
			count++;
		}
	}
	return count;
}

void SudokuSolver(vector< vector< char > >& board) {
	// Check that each row, column, and 3 by 3 cell contains at most one of each number 0-9
	
	// Check that dimensions are correct
	if (board.size() != 9) {
		#ifdef debug_statements_SudokuSolver
			cout << "Wrong dimensions: " << board.size()    << " rows." << endl;
		#endif
		return;
	}
	if (board[0].size() != 9) {
		#ifdef debug_statements_SudokuSolver
			cout << "Wrong dimensions: " << board[0].size() << " columns." << endl;
		#endif
		return;
	}
	
	#ifdef debug_statements_SudokuSolver
		cout << "Puzzle is:" << endl;
		printMatrix(board);
	#endif	


	// Check that all characters are valid ('0' - '9', and '.')
	for (int row = 0; row < board[0].size(); row++) {
		for (int column = 0; column < board.size(); column++) {
			
			// Skip over '.' characters, which mean the board is empty there
			if (board[row][column] == '.') {
				continue;
			}

			// Check that value is in range
			if (board[row][column] < '1' || '9' < board[row][column]) {
				#ifdef debug_statements_SudokuSolver
					cout << "Invalid character at board[" << row << "][" << column << "] == " << board[row][column] << endl;
				#endif
				return;
			}
		}
	}

	vector< vector< list<char> > > matrix (9, vector< list<char> >(9, list<char>() ) );	// Create a 9 by 9 (vector of vectors) matrix of empty lists.
	
	// For every number already in non-blank boxes of the puzzle, add these to the matrix list at the corresponding position
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			if (board[i][j] == '.') {
				continue;
			}
			matrix[i][j].push_back(board[i][j]);
		}
	}

	// This loop is the heart of the algorithm:
	bool competingCandidatesFound;	// Stores whether there is at least 1 list in matrix with multiple candidates in the list there
	do {
		competingCandidatesFound = false;	// Initially, no competing candidates have been found
		
		//Iterate through each entry in the matrix. For each entry, iterate through the numbers 1-9 (all possible entries).
		for (int i = 0; i < matrix.size(); i++) {
			for (int j = 0; j < matrix[0].size(); j++) {

				// Skip values that have already been placed (exactly 1 candidate is available, and all the elements in the same row, column, and region have been removed) We can tell which these are, because the board contains en empty value here '.' instead of a number character '1'-'9'
				if (board[i][j] != '.') {
					continue;
				} else {
					competingCandidatesFound = true;
				}
				//if (matrix[i][j].size() == 1) {
				//	continue;
				//}

				// For all numbers that can go in a particular box, check which are valid (which are not already within the same 3 by 3 region, row, or column), and add them to the list of candidates.
				for (char val = '1'; val <= '9'; val++) {
					if (isValidPlacement(board, val, i, j)) {
						matrix[i][j].push_back(val);
					}
				}
				
				// Check if any candidate number is the only candidate of that digit that can go in that row, column, or region
				// This is called, horizontal scanning, vertical scanning, or region scanning
				/*
				for (list<char>::iterator it = matrix[i][j].begin(); it != matrix[i][j].end(); it++) {
					// Check if the char is the only instance of that char in the row, column, or region
					// If the char is unique to the row, column, or region, then clear all values in the candidates for this entry, except the candidate that is unique
					//Check row
					if (countInRow(matrix, i, *it) == 1) {
						char val = *it;
						// Clear all candidates except the one that is found to be unique
						matrix[i][j].clear();
						matrix[i][j].push_back(val);
						break;	// Exit the loop, since a unique value that must go in this entry is found
					}// else if (countInRow() <= 1) {
					//	printf("Error, countInRow")
					//}
					
					// Check column
					
					// Check region
				}
				*/
				// If there is only one candidate that can go there, then place it there
				if (matrix[i][j].size() == 1) {
					// Remove all candidates from the matrix with the same value in that row and column and region
					removeValue(matrix, *(matrix[i][j].begin()), i, j);

					// Place that value in the region on the board and the matrix
					//matrix[i][j].push_back(val);
					board[i][j] = *(matrix[i][j].begin());	// Place that value in the board. This keeps track of which positions in the matrix have already gotten rid of candidates in the same row, column, and region with the same value

					

				}
			}
			
		}
		
		// If there are entries in matrix that have multiple candidates, then this will loop again
	} while (competingCandidatesFound);

	



	// Check if the lengths of all the lists are 1, to ensure that there is only 1 unique solution.
	// Figure out if the solution exists, and if it is unique.
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			// Check that each entry has a solution for that value
			if (matrix[i][j].size() == 0) {
				cout << "No possible solution: Invalid start matrix?" << endl;
				return;
			}

			// Check if each entry solution is unique
			if (matrix[i][j].size() > 1) {
				cout << "Multiple possible solutions are valid. One such solution is:" << endl;
				goto stopCheckingForSolutionType;
			}
			
		}
	}
	stopCheckingForSolutionType:

	// Copy values to original matrix
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			if (matrix[i][j].size() == 0) {
				board[i][j] = '.';
				continue;
			}
			board[i][j] = *(matrix[i][j].begin());
		}
	}

	/*
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
			#ifdef debug_statements_SudokuSolver
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
			#ifdef debug_statements_SudokuSolver
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
				#ifdef debug_statements_SudokuSolver
					cout << "Error: Duplicate value(s) in region (" << regionRow << ", " << regionColumn << ")" << endl;
				#endif
				return false;
			}
		}
	}
	*/
	
	cout << "Final puzzle is: " << endl;
	printMatrix(board);

	// If the puzzle satisifies the above conditions (no duplicate numbers in row, column, or region, and all characters are '0' - '9'), then the puzzle is valid
	return;
}

#ifdef testing_SudokuSolver
	void printMatrix (const vector< vector< char > >& A) {
		cout << endl << "\t\t";
		for (int j = 0; j < A[0].size(); j++) {
			cout << j << " ";
			if (j%3 == 2) {
				cout << "\t";
			}
		}
		cout << endl << "\t\t______\t______\t______" << endl;
		for (int i = 0; i < A.size(); i++) {
			for (int j = 0; j < A[0].size(); j++) {
				
				if (j%3 == 0) {
					cout << "\t";
				}
				if (j%9 == 0) {
					cout << "[" << i << "]\t";
				}
				cout << A[i][j] << " ";
			}
			cout << endl;
			if (i%3 == 2) {
				cout << endl;
			}
		}
		cout << endl;
	}

	bool matrix_equals (const vector< vector< char > >& A, const vector< vector< char > >& B) {
		// Check that dimensions are the same
		if (A.size() != B.size() || A[0].size() != B[0].size()) {
			cout << "Matrices not the same: Different dimensions! (" << A.size() << " rows, " << A[0].size() << " columns) vs (" << B.size() << " rows, " << B[0].size() << " columns)" << endl;
			return false;
		}

		for (int i = 0; i < A.size(); i++) {
			for (int j = 0; j < A[0].size(); j++) {
				if (A[i][j] != B[i][j]) {
					cout << "Matrices are different at position (" << i << ", " << j << "), which is " << A[i][j] << " vs " << B[i][j] << endl;
					return false;
				}
			}
		}
		return true;
	}

	void tester_SudokuSolver () {
		cout << "Testing \"Is Sudoku Solver\" function" << endl;

		vector< vector< char > > board;
		vector< vector< char > > solution;

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

		solution = {
			{'5','3','4',   '6','7','8',   '9','1','2'},
			{'6','7','2',   '1','9','5',   '3','4','8'},
			{'1','9','8',   '3','4','2',   '5','6','7'},

			{'8','5','9',   '7','6','1',   '4','2','3'},
			{'4','2','6',   '8','5','3',   '7','9','1'},
			{'7','1','3',   '9','2','4',   '8','5','6'},

			{'9','6','1',   '5','3','7',   '2','8','4'},
			{'2','8','7',   '4','1','9',   '6','3','5'},
			{'3','4','5',   '2','8','6',   '1','7','9'}
		};
		//solution = board;
		SudokuSolver(board);
		cout << "Solution is: " << endl;
		printMatrix (solution);
		assert(matrix_equals(board, solution) == true);
		cout << "passed!" << endl;
		
		/*
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
		assert(SudokuSolver(board) == true);
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
		assert(SudokuSolver(board) == false);
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
		assert(SudokuSolver(board) == false);
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
		assert(SudokuSolver(board) == false);
		cout << "passed!" << endl;
		*/
		return;
	}
#endif

int main () {
	#ifdef testing_SudokuSolver
		tester_SudokuSolver();
	#endif

	cout << "Hello world!" << endl;
	return 0;
}