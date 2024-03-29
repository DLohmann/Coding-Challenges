// #include <bits/stdc++.h>
#include<iostream>
#include<unordered_map>
#include<vector>
// Add any extra import statements you may need here

using namespace std;

// Add any helper functions you may need here



int numberOfWays(vector<int>& arr, int k) {
  // maps value to count of occurrences
  unordered_map<int, int> num_counts;
  int count_ways = 0;
  for (int val : arr) {
    cout << "val: " << val << ", complement num_counts[" << k - val << "] == " << num_counts[k - val] << ", [  ";
    for (int p : arr) {
      cout << p << ":" << num_counts[p] << "  ";
    }
    cout << "]" << endl;
    count_ways += num_counts[k - val];
    num_counts[val] += 1;
  }
  return count_ways;
}

// These are the tests we use to determine if the solution is correct.
// You can add your own at the bottom.

void printInteger(int n) {
  cout << "[" << n << "]";
}

int test_case_number = 1;

void check(int expected, int output) {
  bool result = (expected == output);
  const char* rightTick = u8"\u2713";
  const char* wrongTick = u8"\u2717";
  if (result) {
    cout << rightTick << "Test #" << test_case_number << "\n";
  }
  else {
    cout << wrongTick << "Test #" << test_case_number << ": Expected ";
    printInteger(expected); 
    cout << " Your output: ";
    printInteger(output);
    cout << endl; 
  }
  test_case_number++;
}

int main() {

  int k_1 = 6;
  vector <int> arr_1{1, 2, 3, 4, 3};
  int expected_1 = 2;
  int output_1 = numberOfWays(arr_1, k_1);
  check(expected_1, output_1);

  int k_2 = 6;
  vector <int> arr_2{1, 5, 3, 3, 3};
  int expected_2 = 4;
  int output_2 = numberOfWays(arr_2, k_2);
  check(expected_2, output_2);

  // Add your own test cases here
  return 0;
}