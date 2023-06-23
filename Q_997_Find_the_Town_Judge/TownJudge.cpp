class Solution {
public:
    int findJudge(int N, vector<vector<int>>& trust) {
        // Read all data into matrix
        vector<vector<int>> mat (N, vector<int>(N, 0));
        
        // Assume each node trusts themself
        for (int i = 0; i < mat.size(); i++) {
            mat[i][i] = 1;
        }
        
        
        // Read in trust data
        for (int i = 0; i < trust.size(); i++) {
            mat[trust[i][0] - 1][trust[i][1] - 1] = 1;
        }
        
        for (int i = 0; i < N; i++) {
            
            // Check for a node that is trusted by all nodes
            bool potential_judge = true;
            for (int j = 0; j < N; j++) {
                if (mat[j][i] != 1) {
                    potential_judge = false;
                    break;
                }
            }
            if (potential_judge == true) {
                // Check that this node trusts no other nodes
                for (int j = 0; j < N; j++) {
                    if (mat[i][j] != 0 && i != j) {
                        potential_judge = false;
                        break;
                    }
                }
                if (potential_judge == true) {
                    return i+1;
                }
            }
        }
        return -1;
    }
};