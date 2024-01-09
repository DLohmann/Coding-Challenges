#ifndef Sample_H_
#define Sample_H_

#include<map>
#include<string>

namespace sample {

class WordDictionary {
protected:
    struct Node {
        Node* parent = nullptr;
        std::map<char, Node*> children;
        char c = '\0';
        int depth = 0;
        bool terminal = false;
    };
    Node* root = nullptr;

    // Iterates through the best matching path in the trie, and returns a pointer to the final  
    // node in the trie's matching path that matches the corresponding char in the  word string. 
    // If all the nodes match, then this should be the node corresponding to the last char in the 
    // string.
    //
    // Parameters:
    //  * start: A pointer to the parent node of the branch of trie to search down.
    //  * word:  The string to match.
    //  * depth: The initial depth of the start node. The depth of the start pointer in the trie.
    // Returns:
    //  * A pointer to the deepest matching node in matching path, or nullptr if all matches.
    //
    Node* nextNode(Node* start, std::string word, int depth);

    void deleteInorder(Node* current);
public:
    WordDictionary();

    ~WordDictionary();
    
    void addWord(std::string word);
    
    bool search(std::string word);
};


/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */

}  // namespace sample

#endif  // Sample_H_
