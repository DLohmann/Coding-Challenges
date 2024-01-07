#include"Sample.h"

#include<vector>
#include<list>
#include<set>
#include<algorithm>
#include<iostream>

using namespace std;

namespace sample {


void printVector(vector<int>& v) {
    cout << "{";
    if (!v.empty()) {
        cout << v.front();
                for (vector<int>::iterator it = next(v.begin()); it != v.end(); it++) {
            cout << ", " << *it;
        }
            }
    cout << "}" << endl;

    // ostringstream oss;
    // copy(begin(v), end(v), std::ostream_iterator<int>(oss, ","));
    // cout << oss.str() << endl;
}

    Solution::Solution() {
        candidates = nullptr;
        result = vector< vector<int> >();
    }

    void Solution::dfs(int current_candidate, vector< int >& combo, int remainder) {
        // printVector(combo);
        if (remainder == 0) {
            result.push_back(vector< int >(combo.begin(), combo.end()));
            return;
        }
        if (remainder < 0) {
            return;
        }
        if (candidates->size() <= current_candidate) {
            return;
        }
                combo.push_back((*candidates)[current_candidate]);
        dfs(current_candidate, combo, remainder - (*candidates)[current_candidate]);
        
                combo.pop_back();
        dfs(current_candidate + 1, combo, remainder);
                return;
    }
    vector<vector<int>> Solution::combinationSum(vector<int>& c, int target) {
        sort(c.begin(), c.end());
        candidates = &c;
        vector<int> combo = vector<int>();
        dfs(0, combo, target);
        candidates = nullptr;
        return this->result;
    }

} // namespace sample

