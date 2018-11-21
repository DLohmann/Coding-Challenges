#include <iostream>
#include <vector>
#include <unordered_map>
#include <assert.h> // used for testing
#include <limits.h> // used for INT_MIN
#include <tuple>

using namespace std;



/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
 

struct Point {
	int x;
	int y;
	Point() : x(0), y(0) {}
	Point(int a, int b) : x(a), y(b) {}
};

typedef tuple <int, int> line;	// The 'a' and 'b' values that define a line when in the form a*x + b*y = 1
struct line {
	int a;
	int b;
	line() : a(0), b(0) {}
	line(int a, int b) : a(a), b(b) {}
	int hash () {
		return (a << 16) | b;
	}
}

unordered_map < line, int > lineCounts;	// can make this an unordered_map (a hashtable) to do the n insertions in O(1) time and 1 minimum finding in O(n) time, so total time is n*O(1) + 1*O(n) = O(n), though this makes inefficient use of memory, since it uses a hashtable. Or we can make this an ordered_map (a binary tree)to do n insertions in O(log(n)) time, and 1 minimum finding in O(1) time, so total time is n*O(log(n)) + 1*O(1) = O(n*log(n)), though this makes a more efficient use of memory.

// int convertToID (int i, int j) {	
	// return (i * N) + j;
// }

/*
Basic Algorithm:
) Iterate through every pair of different points.
) For every pair of points, calculate the equation of the line between them (the values of 'a' and 'b' in  the equation ax + by = 1)
) When 'a' and 'b' are calculated, use the pair of these as a key in a data structure (ie: a hashmap to make lookups faster, or a binary tree to look up the max faster later), which counts the amount of times that this pair has been seen. Add 1 to the count of the pair (a, b)
) When finished iterating, find the pair (a, b) with the maximum count, and print it's count
*/
tuple <int, int> calculateLine (Point& p1, Point& p2) {
	// Returns the 'a' and 'b' values of the line in the form a*x + b*y = 1
	
	// Ensure that the points are not at the same position
	if (get<0>p1 == get<0>p2 && get<1>p1 == get<1>p2) {
		return make_tuple(INT_MIN, INT_MIN);	// Use the coordinate (INT_MIN, INT_MIN) to designate that the indexes are the same
	}
	
	int a = 0;
	int b = 0;
	
	
	return make_tuple (a, b);
}

int maxPoints(vector<Point>& points) {
	lineCounts.clear();
	if (points.size() == 0) {
		return 0;
	}
	
	// Iterate through all pairs of points that are not the same, at indexes i and j. This means that i < j
	for (int i = 0; i < points.size() - 1; i++) {
		for (int j = i + 1; i < points.size(); j++) {
			line lineVals = calculateLine (points[i], points[j]);
			
			// Check if the points were the same. If so, skip over them
			if (get<0>lineVals == INT_MIN && get<1>line == INT_MIN) {
				continue;
			}
			
			// Increase the count of this point by 1
			
			
		}
	}
	
}


int main () {
	
	// Example 1:
	// Input: [[1,1],[2,2],[3,3]]
	// Output: 3
	// Explanation:
	// ^
	// |
	// |        o
	// |     o
	// |  o  
	// +------------->
	// 0  1  2  3  4
	// Example 2:
	// Input: [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
	// Output: 4
	// Explanation:
	// ^
	// |
	// |  o
	// |     o        o
	// |        o
	// |  o        o
	// +------------------->
	// 0  1  2  3  4  5  6
	
	vector <Point> points;
	
	cout << "Beginning tests: " << endl;
	
	points = {Point(1,1),Point(2,2),Point(3,3)};
	assert (maxPoints(points) == 3);
	
	points = {Point(1,1),Point(3,2),Point(5,3),Point(4,1),Point(2,3),Point(1,4)};
	assert (maxPoints(points) == 4);
	
	cout << "All tests passed!" << endl;
	
	return 0;
}
