#include "deps.cpp"

class Solution {
private:
	struct node {
		char letter = '\0';
		map<char, node*> child;
		bool endOfWord; // states whether this node designates the end of a word
	};
	node root;
public:
	string longestWord(vector<string>& word) {
		for (int i = 0; i < word.size(); i++) {
			insertWord(word[i]);
		}
		return findLongest();
	}
	
	string findLongest() {
		// Use DFS to find longest word
	}
	
	void insertWord(string word) {
		node * currentNode = &root;
		map<char, node*>::iterator it;
		// Iterate through each letter
		for (int i = 0; i < word.length(); i++) {
			/*
			if (currentNode->child) {
				currentNode->child = new map<char, node*>();
			}
			*/
			// Check if the letter is at the next position
			it = (currentNode->child).find(word.at(i));
			if (it == (currentNode->child).end()) {
				// If the char is not the next position, then add to to the trie
				(currentNode->child)[word.at(i)] = new node();
				it = (currentNode->child).find(word.at(i));
			}
			// move to the next node
			currentNode = it->second;
		}
		currentNode->endOfWord = true;
	}

	Solution() {
		root.letter = '.';
		root.endOfWord = false;
	}

	~Solution() {
		//TODO(dlohmann): Use depth first search post order traversal to delete all nodes
	}
};
