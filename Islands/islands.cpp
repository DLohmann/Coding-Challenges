#include <iostream>
#include <vector>
#include <unordered_set>
#include <utility> // has pair
//#define debug
//#define usingEightNeighbors

using namespace std;

class Solution {
public:
    //int nearestNeighborID () {
        // takes in a grid and pixel coordinates, and outputs the ID of the neares island found so far. If not island has been found, then assign a new ID to this new island
    //}
    
    
};

unordered_set < int > exploredNodes;


int M;		// number of rows 
int N;		// number of columns

int convertToID (int i, int j) {	
    return (i * N) + j;
}

bool has (int i, int j) {
    return exploredNodes.find(convertToID(i, j)) != exploredNodes.end();
}

void insert (int i, int j) {
    exploredNodes.insert(convertToID(i, j));
}

void Dijkstras(vector<vector<char> >& grid, int i, int j) {
    
    // Check array bounds
    if (!(0 <= i && i < M && 0 <= j && j < N)) {
        return;
    }
    
    // skip zeros
    if (grid[i][j] == '0') {
        return;
    }
    // skip explored nodes
    if (has(i, j)) {
        return;
    }
    
    #ifdef debug
        cout << "Exploring node (" << i << ", " << j << ")" << endl;
    #endif
    
    // Add this node to explored nodes
    insert(i, j);
    
    // Explore neighbors
    Dijkstras (grid, i, j-1);
    Dijkstras (grid, i, j+1);
    Dijkstras (grid, i-1, j);
    Dijkstras (grid, i+1, j);
    
}

int numIslands( vector<vector<char> >& grid) {
    /*
    Algorithm:
    1) Iterate through each element of grid row by row
    2) Skip over '0's. Skip over '1's that are already in the exploredNodes.
    3) If an unexplored '1' is encountered, then add it to the exploredNodes, and call Dijkstra's algorithm on this node, which adds all the nodes in it's island to the explored nodes
    4) increment islandCount by 1
    5) Continue to end of grid
    */
	int islandCount = 0;
	
	M = (int)(grid.size());		// number of rows 
	
	if (M <= 0) {
		return 0;
	}
	
	N = (int)(grid[0].size());		// number of columns
	
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
			
			
			#ifdef debug
			cout << "visiting (" << i << ", " << j << ") " << endl;
			#endif
            
			// skip over 0's
			if (grid[i][j] == '0') {
                continue;
            }
            
            // skip over explored nodes
            if (has(i, j)) {
                continue;
            }
            
            //if code gets here, we are at a new node
            Dijkstras(grid, i, j);
            islandCount++;
			
			#ifdef debug
			cout << "Found new island. IslandCount is: " << islandCount<< "\n\n";
			#endif
			
		}
		
		
	
	
	}
	
	return islandCount;
        
}

int main () {
	
	vector<vector<char> > grid = {{'1','1','1','1','0'},
								  {'1','1','0','1','0'},
								  {'1','1','0','0','0'},
								  {'0','0','0','0','0'}};
	
    /*
	vector<vector<char> > grid = {{'1','1','1'},
								  {'0','1','0'},
								  {'1','1','1'}};
	*/  
	cout << numIslands(grid) << endl;
	
	return 0;
}
