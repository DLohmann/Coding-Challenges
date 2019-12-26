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
		insertWords(word);
		return findLongest();
	}
	
	string findLongest() {
		// Use DFS to find longest word
		return "";
	}
	
	void insertWords(vector<string>& word) {
		cout << "Inserting words" << endl;
		for (int i = 0; i < word.size(); i++) {
			cout << "\tinserting word \"" << word[i] << "\"" << endl;
			insertWord(word[i]);
		}
		cout << "Finished inserting words" << endl;
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
				cout << "\t\tcreating node '" << word.at(i) << "'" << endl;
			}
			// move to the next node
			currentNode = it->second;
			currentNode->letter = word[i];
		}
		currentNode->endOfWord = true;
	}
	
	// Use traversal to find all words
	list<string> findAllWords () {
		cout << "Finding words" << endl;
		list<string> wordsFound;
		list<node *> nodesAbove;
		set<node*> explored;
		nodesAbove.push_back(&root);
		node* currentNode = nodesAbove.back();
		while (!nodesAbove.empty()) {
			
			visitNode:
			//for each child that has not been visited
			// TODO(dlohmann): For loop causes runtime error
			for (map<char, node*>::iterator it = (currentNode->child).begin(); it != (currentNode->child).end(); it++) {
				
				// skip over previously explored
				if (explored.find(it->second) != explored.end()) {
					continue;
				}
				
				//if child has no children, then print it and add it to explored
				if ((it->second)->child.empty()) {
					explored.emplace(it->second);
					if ((it->second)->endOfWord) {
						list<node*> wordLetters(nodesAbove);
						wordLetters.pop_front();
						wordLetters.pop_front();
						wordLetters.push_back(currentNode);
						wordLetters.push_back(it->second);
						wordsFound.push_back(makeWord(wordLetters));
						cout << "\tfound word \"" << wordsFound.back() << "\"" << endl;
					}
				} else {
					// TODO(dlohmann): Check if the node was explored before visiting it
					//else add currentNode to nodesAbove and visit it's children by setting currentNode to a child
					nodesAbove.push_back(currentNode);
					currentNode = it->second;
					cout << "\t\tvisiting node '" << currentNode->letter << "'" << endl;
					goto visitNode;
				}
				
				
			}
			
			//move back up one level, and pop off nodesAbove's back
			explored.emplace(currentNode);
			nodesAbove.pop_back();
			currentNode = nodesAbove.back();
			
		}
		cout << "Finished finding words" << endl;
		// Visit every child node
		return wordsFound;
	}
	
	string makeWord (list<node*>& nodes){
		char str [nodes.size() + 1];
		str[nodes.size()] = '\0';
		int i = 0;
		for (list<node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
			str[i] = (*it)->letter;
			i++;
		}
		return string(str);
	}
	
	Solution() {
		root.letter = '.';
		root.endOfWord = false;
	}

	~Solution() {
		//TODO(dlohmann): Use depth first search post order traversal to delete all nodes
		cout << "Beginning deletion" << endl;
		list<node *> nodesAbove;
		set<node*> explored;
		nodesAbove.push_back(&root);
		node* currentNode = nodesAbove.back();
		while (!nodesAbove.empty()) {
			
			visitNode:
			//for each child that has not been visited
			for (map<char, node*>::iterator it = (currentNode->child).begin(); it != (currentNode->child).end(); it++) {
				// skip over previously explored
				//if (explored.find(it->second) != explored.end()) {
				//	continue;
				//}
				//if child has no children, then print it and add it to explored
				if ((it->second)->child.empty()) {
					//explored.emplace(it->second);
					(currentNode->child).erase(it->second->letter);
					if ((it->second)->endOfWord) {
						list<node*> wordLetters(nodesAbove);
						wordLetters.pop_front();
						wordLetters.pop_front();
						wordLetters.push_back(currentNode);
						wordLetters.push_back(it->second);
						cout << "\tdeleted \"" << makeWord(wordLetters) << "\"" << endl;
					}
					delete it->second;
				} else {
					//else add currentNode to nodesAbove and visit it's children by setting currentNode to a child
					nodesAbove.push_back(currentNode);
					currentNode = it->second;
					goto visitNode;
				}
				
				
			}
			
			//move back up one level, and pop off nodesAbove's back
			nodesAbove.pop_back();
			currentNode = nodesAbove.back();
			cout << "ended deletion" << endl;
		}
		// Visit every child node
		
		/*
		node * currentNode = &root;
		list<node *> nodesAbove;
		while (!currentNode->child.empty()) {
			
			if () {
				// If a node has no children, then delete it, and move back up.
				// When moving up, remove the node's pointer from nodesAbove.
			} else {
				// If a child has children, then add it to nodesAbove and visit the child
				currentNode = currentNode->child.begin();
				nodesAbove.add(currentNode);
			}
			
			
		}
		currentNode = nodesAbove.back();
		*/
	}
};
