#include"Sample.h"

#include<iostream>

using namespace std;

namespace sample {

    WordDictionary::Node* WordDictionary::nextNode(WordDictionary::Node* start, string word, int depth) {
        cout << "\tnextNode(" << start->c << ", \"" << word << "\", " << depth << ")" << endl;
        WordDictionary::Node* current = start;
        for (; depth < word.size(); depth++) {
            cout << "\t\tdepth: " << depth << endl;
            if (word[depth] == '.') {
                for (auto child : current->children) {
                    WordDictionary::Node* next;
                    int next_depth;
                    next = nextNode(child.second, word, depth + 1);
                    next_depth = next->depth;
                    if (next_depth == word.size() && next->terminal) {
                        cout << "\t\tusing '.' word \"" << word << "\" finished partially matching trie to depth: " << depth << endl;
                        return next;
                    }
                }
                cout << "\t\tnot match '.'" << endl;
                return current;
            }
            
            bool found_match = false;
            auto it = current->children.find(word[depth]);
            if (it == current->children.end()) {
                cout << "word \"" << word << "\" only matched to depth " << depth << " then mismatched at char '" << word[depth] << "'"<< endl;
                return current;
            }
            current = it->second;
            cout << "\t\tmatch '" << it->first << "'" << endl;
        }
        if (current->terminal) {
            cout << "\t\tword fully matches trie" << endl;
            return current;
        }
        cout << "\t\tword \"" << word << "\" finished matching string \"" <<  word<< "\" in trie to depth: " << depth << ", but at non-terminal node" << endl;
        return current;
    }

    void WordDictionary::deleteInorder(WordDictionary::Node* current) {
        for (auto child : current->children) {
            deleteInorder(child.second);
        }
        if (current == root) {
            cout << "Delete root" << endl;
        } else {
            cout << "Delete Node('" << current->c << "')" << endl;
        }
        delete current;
    }

    WordDictionary::WordDictionary() {
        cout << "Create root" << endl;
        root = new WordDictionary::Node();
    }

    WordDictionary::~WordDictionary() {
        deleteInorder(root);
    }
    
    void WordDictionary::addWord(string word) {
        cout << "addWord(\"" << word << "\")" << endl;
        WordDictionary::Node* current;
        current = nextNode(root, word, 0);
        int depth = current->depth;
        cout << "\tnextNode returned node: '" << current->c << "', depth: " << depth << endl;
        WordDictionary::Node* previous = current;
        for (; depth < word.size(); depth++) {
            current = new WordDictionary::Node();
            current->c = word[depth];
            cout << "Created Node('" << word[depth] << "') at depth " << depth + 1 << endl;
            current->parent = previous;
            previous->children.insert({current->c, current});
            current->depth = depth + 1;
            previous = current;
        }
        current->terminal = true;
    }
    
    bool WordDictionary::search(string word) {
        cout << "search(\"" << word << "\")" << endl;
        WordDictionary::Node* current;
        current = nextNode(root, word, 0);
        cout << "search(\"" << word << "\") -> " << (current->depth == word.size()? "true" : "false") << endl << endl;
        return current->depth == word.size() && current->terminal;
    }

} // namespace sample

