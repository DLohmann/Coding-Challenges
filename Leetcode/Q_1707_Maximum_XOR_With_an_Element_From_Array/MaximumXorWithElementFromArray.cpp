#include"MaximumXorWithElementFromArray.h"

#include<vector>
#include<set>
#include<list>
#include<iostream>
#include<limits.h>

using namespace std;

namespace nums_size_times_queries_size_solution {
    vector<int> Solution::maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        //cout << "nums.size(): " << nums.size() << ", queries.size(): " << queries.size() << endl;
        vector<int> solution;
        solution.reserve(queries.size());
        set<int> nums_sorted = set<int>(nums.begin(), nums.end());
        for (vector<int>& query : queries) {
            int max_xor = INT_MIN;
            int x = query[0];
            int m = query[1];
            if (*nums_sorted.begin() > m) {
                solution.push_back(-1);
                continue;
            }
            set<int>::iterator num_range_end = nums_sorted.upper_bound(m);
            for (set<int>::iterator num_it = nums_sorted.begin(); num_it != num_range_end; num_it++) {
                int val = x ^ (*num_it);
                if (val > max_xor) {
                    max_xor = val;
                }
            }
            //cout << distance(nums_sorted.begin(), num_range_end) << " comparisons" << endl;
            solution.push_back(max_xor);
        }
        return solution;
    }
} // namespace nums_size_times_queries_size_solution


namespace bit_trie_solution {
    struct Node {
        Node* parent = nullptr;
        Node* zero = nullptr;
        Node* one = nullptr;
        int min = INT_MAX;
    };
    
    class BinaryTrie {
        public:
            Node* root = nullptr;
            size_t trie_size = 0;
            BinaryTrie() {
                root = new Node();
            }

            ~BinaryTrie() {
                // Post-order traversal: delete node after deleting it's children.
                // Assumes at least 1 node (root) should be deleted.
                list<Node*> ancestors;
                ancestors.push_back(root);
                Node* current = root;
                while (true) {
                    if (current->zero != nullptr) {
                        current = current->zero;
                        ancestors.push_back(current);
                        continue;
                    }
                    if (current->one != nullptr) {
                        current = current->one;
                        ancestors.push_back(current);
                        continue;
                    }
                    ancestors.pop_back();
                    delete current;
                    if (ancestors.empty()) {
                        break;
                    }
                    if (ancestors.back()->zero == current) {
                        ancestors.back()->zero = nullptr;
                    } else if (ancestors.back()->one == current) {
                        ancestors.back()->one = nullptr;
                    } else {
                        cout << "Impossible case reached! Neither zero nor one child!" << endl;
                    }
                    current = ancestors.back();
                }
            }

            void addToBinaryTrie(int val) {
                if (root == nullptr) {
                    root = new Node();
                }
                Node* current = root;
                if (root->min > val) {
                    root->min = val;
                }
                for(int i = 0; i < sizeof(int) * 8; i++) {
                    int shift_amount = (sizeof(int) * 8 - 1) - i;
                    int bit = (val >> shift_amount) & 1;
                    if (bit == 0) {
                        if (current->zero == nullptr) {
                            current->zero = new Node();
                            current->zero->parent = current;
                        }
                        current = current->zero;
                    } else {
                        if (current->one == nullptr) {
                            current->one = new Node();
                            current->one->parent = current;
                        }
                        current = current->one;
                    }
                    if (current->min > val) {
                        current->min = val;
                    }
                }
                trie_size++;
            }
            Node* getRoot() {
                return root;
            }
            size_t size() {
                return trie_size;
            }

    };
    vector<int> Solution::maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
        vector<int> solution;
        solution.reserve(queries.size());

        BinaryTrie trie = BinaryTrie();
        
        for (int num : nums) {
            trie.addToBinaryTrie(num);
        }

        for (vector<int>& query : queries) {
            int x = query[0];
            int m = query[1];

            Node* root = trie.getRoot();
            int next_x_bit = x >> 31 & 1;
            Node* current = next_x_bit == 0 ? root->zero : root->one;
            if (m < root->min) {
                solution.push_back(-1);
                continue;
            }
            for (int i = 1; i < (sizeof(int) * 8); i++) {
                int shift_amount = (sizeof(int) * 8) - i;
                next_x_bit = (x >> (shift_amount - 1)) & 1;

                if (current->zero != nullptr && current->one == nullptr) {
                    current = current->zero;
                } else if (current->zero == nullptr && current->one != nullptr) {
                    current = current->one;
                } else if (current->zero->min <= m && current->one->min > m) {
                    current = current->zero;
                } else if (current->zero->min > m && current->one->min <= m) {
                    current = current->one;
                } else if (next_x_bit == 0) {
                    current = current->one;
                } else {
                    current = current->zero;
                }

            }
            solution.push_back(int(x ^ current->min));
        }
        return solution;
    }

}  // namespace bit_trie_solution
