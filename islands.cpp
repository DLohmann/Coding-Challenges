#include <iostream>
#include <vector>

#define debug
//#define usingEightNeighbors

using namespace std;

class Solution {
public:
    //int nearestNeighborID () {
        // takes in a grid and pixel coordinates, and outputs the ID of the neares island found so far. If not island has been found, then assign a new ID to this new island
    //}
    
    
};

int numIslands( vector<vector<char> >& grid) {
        
	int islandCount = 0;
	
	int M = (int)(grid.size());		// number of rows 
	
	if (M <= 0) {
		return 0;
	}
	
	int N = (int)(grid[0].size());		// number of columns
	
	if (N <= 0) {
		return 0;
	}
	
	// grid ID's. -1 means water, or the item is a 0. Any positive integer is the island ID
	vector < vector <int> > ID (M, vector<int>(N, -1));
	
	
	//ID.resize (grid.size(), grid[0].size());
	// i is row number (vertical index)
	// j is column number (horizontal index)
	for (int i = 0; i < M; i++) { // iterate through each row
		for (int j = 0; j < N; j++) {   // iterate through each column
			if (grid[i][j] == '0') {
				ID[i][j] = -1;
				continue;
			}
			
			#ifdef debug
			cout << "visiting (" << i << ", " << j << ") " << endl;
			#endif
			
			// Check above and to left of current entry for non-zero entries, and assign the max of their ID's.
			// neighbor 0 is above and left of current point
			// neighbor 1 is above
			// neighbor 3 is above and right
			// neighbor 4 is left
			// 0 1 2
			// 3 
			
			// i is row number (vertical index)
			// j is column number (horizontal index)
			
			//                    0,  1,  2,  3
			int neighborID [] = {-1, -1, -1, -1};
			
			bool isRightSide = false;
			bool isLeftSide = false;
			bool isTopEdge = false;
			
			
			
			if (i - 1 < 0) {
				isTopEdge = true;
			}
			if (j - 1 < 0) {
				isLeftSide = true;
			}
			if (N <= j+1) {
				isRightSide = true;
			}
			
			
			if (!isTopEdge) {   // assign neighbors on top row
				
				#ifdef usingEightNeighbors
				if (!isLeftSide) {    //Only used for 8-neighbors, but not 4-neighbors 
					neighborID [0] = ID[i - 1][j - 1];
				}
				#endif
				
				neighborID[1] = ID[i - 1][j];
				
				#ifdef usingEightNeighbors
				if (!isRightSide) { //Only used for 8-neighbors, but not 4-neighbors 
					neighborID [2] = ID[i - 1][j + 1];
				}
				#endif
				
			}
			if (!isLeftSide) {
				neighborID [3] = ID[i][j - 1];
			}
			
			// find the max ID in neighborID
			int max = -1;
			
			#ifdef debug
			cout << "neighborID's are: ";
			#endif
			
			for (int k = 0; k < 4; k++) {
				#ifdef debug
				cout << " " << neighborID[k];
				#endif
				
				if (max < neighborID[k]) {
					max = neighborID[k];
				}
			}
			#ifdef debug
			cout << endl;
			#endif
			
			if (max >= 0) {
				ID[i][j] = max;
			} else {
				// entry is '1', but not connected to any island above and to left of it
				ID[i][j] = islandCount;
				islandCount++;
				
				
			}
			
			#ifdef debug
			cout << "my ID is: " << ID[i][j] << ", islandCount is: " << islandCount<< "\n\n";
			#endif
			
		}
		
		
	
	
	}
	
	return islandCount;
        
}

int main () {
	/*
	vector<vector<char> > grid = {{'1','1','1','1','0'},
								  {'1','1','0','1','0'},
								  {'1','1','0','0','0'},
								  {'0','0','0','0','0'}};
	*/
	vector<vector<char> > grid = {{'1','1','1'},
								  {'0','1','0'},
								  {'1','1','1'}};
								  
	cout << numIslands(grid) << endl;
	
	return 0;
}
