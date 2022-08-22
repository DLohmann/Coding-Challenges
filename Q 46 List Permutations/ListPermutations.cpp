#include<iostream>
#include<vector>

using namespace std;

int factorial(int n) {
	int f = n;
	while (--n > 0) {
		f = f*n;
	}
	return f;
}

class Solution {
	static vector<vector<int>> scramble(vector<int>& nums) {
		if (nums.size() <= 1) {
			return { vector<int>(nums) };
		}
		vector<vector<int>> all_permuatations;
		all_permuatations.reserve(factorial(nums.size()));
		vector<int> next_iteration(nums);
		for (int i = nums.size() - 1; i >= 0; i--) {
			for 
		}
	}
public:
	vector<vector<int>> permute(vector<int>& nums) {
		return scramble(nums);
	}
};

bool EqualsVector(vector<int>& v1, vector<int>& v2)
{
	if (v1.size() != v2.size())
	{
		return false;
	}
	for (int i = 0; i < v1.size(); i++)
	{
		if (v1[i] != v2[i])
		{
			return false;
		}
	}
	return true;
}

bool EqualsMatrix(vector<vector<int>>& m1, vector<vector<int>>& m2)
{
	if (m1.size() != m2.size())
	{
		return false;
	}
	for (int i = 0; i < m1.size(); i++)
	{
		if (!EqualsVector(m1[i], m2[i]))
		{
			return false;
		}
	}
	return true;
}

bool EqualsMatrixUnordered(vector<vector<int>>& m1, vector<vector<int>>& m2)
{
	if (m1.size() != m2.size())
	{
		return false;
	}
	for (int i = 0; i < m1.size(); i++)
	{
		bool found = false;
		for (int j = 0; j < m2.size(); j++)
		{
			if (EqualsVector(m1[i], m2[j]))
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			return false;
		}
	}
	return true;
}

void printMatrix(vector<vector<int>>& mat){
	for (int row = 0; row < mat.size(); row++){
		cout << "[";
		for (int col = 0; col < mat[0].size(); col++) {
			cout << "\t" << mat[row][col];
		}
		cout << "]" << endl;
	}
}

int main() {
	Solution sol;
	vector<int> input = {1, 2, 3};
	vector<vector<int>> expected_output = {{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}};
	vector<vector<int>> actual_output = sol.permute(input);
	if (!EqualsMatrixUnordered(
		actual_output,
		expected_output
	)) {
		cout << "Matrices are not the same!" << endl;
		cout << "Output:\n";
		printMatrix(actual_output);
		cout << "Expected output:\n";
		printMatrix(expected_output);
		return 0;
	}
	if (factorial(6) != 720) {
		cout << "Error!" << endl;
		return 0;
	}
	cout << "Success!" << endl;
	return 0;
}