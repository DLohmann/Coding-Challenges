#include <iostream>
#include <vector>
#include <unordered_map>
#include <assert.h> // used for testing
//#include <limits.h> // used for INT_MIN
#include <math.h>	// has sqrt and sine and cosine

#define debug_max_line	// debugging flag for print statements
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



/*
Basic Algorithm:
0) Choose a minimum difference in angle "d", that the algorithm will be able to differentiate between. A line's slope will be rounded to the nearest multiple of this angle. Two lines with a difference in angle less than this will be recorded as though they have the same slope. In this code, d=1.
1) Create a 2D array called the "accumulator". It's dimensions should be "d" by sqrt(M^2 + N^2), where M and N are the number of rows and columns of the points matrix. Initialize every element in the accumulator to 0.
2) Iterate through each point in the points list. At each 0, skip over to the next element. At each 1, calculate every possible line that could go through this point (At every angle multiple of d). For each 1 entry in the points, matrix, at points (x, y), iterate through every value if theta at intervals of "d" from 0 to 180, and find the normalized form of a line y*sin(theta) + x*cos(theta) = rho. So for the angle theta, find the normalized form of the line (defined by rho and theta) that goes through the point at that angle, and increment the count of this line that has these values. So our accumulator matrix holds a count of how many points go through each line. So accumulator[theta][rho]+=1. Each entry in the accumulator corresponds to a line through points in the points matrix.
3) After iterating through every 1 in the points matrix, the accumulator now holds  a count of how many points go through each point in the accumulator matrix. So iterate through the accumulator matrix, and find maximum of the accumulator matrix. This coordinates of the max entry in the accumulator matrix correspond to the rho and theta values of the normalized form of the line with the maximum number of points in the points matrix.


*/
	
	


void printPoints (const vector<Point>& points) {
	
	cout << "points are: (" << points[0].x << " ," << points[0].y << ")";
	for (int i = 1; i < (int)points.size(); i++) {
		cout << ", (" << points[i].x << " ," << points[i].y << ")";
	}
	cout << endl;
}

float d = 1.0f; // The difference in angle that can be detected (in degrees)

int maxPoints(const vector<Point>& points) {
	#ifdef debug_max_line
		cout << "\n\nFINDING MAX LINE" << endl;
	#endif
	
	// Ensure points vector is not empty
	if ((int)points.size() == 0) {
		return 0;
	}
	
	
	
	
	// Iterate through all entries in the points vector, and calculate the max X and max Y coordinates
	int maxX = points[0].x, maxY = points[0].y;
	for (vector<Point>::const_iterator it = points.begin(); it != points.end(); it++) {	// Calculate the max X and Y coordinates
		if (it->x > maxX) {
			maxX = it->x;
		}
		if (it->y > maxY) {
			maxY = it->y;
		}
	}
	
	//TODO: Can decrease the size of the accumulator to save memory, if the min X and min Y values of all the points are greater than 0. So the accumulator doesn't need to store the extra 

	
	//Declare the accumulator matrix as an empty array of zeros:
	float theta_bound = 180.0f / d;	// theta will go from 0 to 180
	int num_angles = (int)ceil(theta_bound);	// theta will go from 0 to num_angles
	// rho will go from -num_amplitudes to num_amplitudes
	float rho_bound = sqrt((float)(maxY*maxY + maxX*maxX));	// rho will go from -sqrt(x^2 + y^2) to +sqrt(x^2 + y^2)
	int num_amplitudes = (int)ceil(rho_bound);	// The hypotenuse of the points matrix. The square root is an integer square root
	if (num_amplitudes <= 0) {	// If the points are all at the same position, and then the number of points that a line goes through is the number of points entered. Any line goes through all the points
		return (int)points.size();
	}
	vector< vector<int> > accumulator (2*num_amplitudes, vector<int>(num_angles, 0));
	
	// Iterate through every point in the points list
	for (vector<Point>::const_iterator it = points.begin(); it != points.end(); it++) {
		float x = (float)(it->x);
		float y = (float)(it->y);
		// Add each point to the accumulator, for every value of theta
		int theta_int = 0;
		for (float theta = 0.0f; theta < theta_bound; theta += d) {
			
			float rho = x*cos(theta * M_PI/180.0f) + y*sin(theta * M_PI/180.0f);	// Find rho, using normalized line form, and round to the nearest integer
			int rho_int = (int)rint(rho + rho_bound);	// Add the rho_bound to rho to ensure it is positive. Then round to the nearest integer
			//cout << "rho = "     << rho     << ", theta = "     << theta     << endl;
			//cout << "rho_int = " << rho_int << ", theta_int = " << theta_int << endl;
			accumulator[rho_int][theta_int] += 1;
			theta_int++;
		}
	}
	
	
	// Find the maximum entry in the accumulator
	int max = 0;
	for (int m = 0; m < (int)accumulator.size(); m++) {
		for (int n = 0; n < accumulator[0].size(); n++) {
			if (accumulator[m][n] > max) {
				max = accumulator[m][n];
			}
		}
	}
	
	#ifdef debug_max_line
		cout << "max count is: " << max << endl;
	#endif
	return max;
	
}


void test_max_line(int num_on_line, vector<Point>& points) {
	printPoints(points);
	int num_calculated = maxPoints(points);
	cout << "Points on line: " << num_on_line << " num calculated: " << num_calculated << endl << endl;
	assert (num_calculated == num_on_line);
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
	test_max_line(3, points);
	
	points = {Point(1,1),Point(3,2),Point(5,3),Point(4,1),Point(2,3),Point(1,4)};
	test_max_line(4, points);
	
	points = {Point(0,0)};
	test_max_line(1, points);
	
	points = {Point(0,0), Point(1,0)};
	test_max_line(2, points);
	
	cout << "All tests passed!" << endl;
	
	return 0;
}
