#include"Sample.h"

#include<list>
#include<unordered_map>
#include<unordered_set>
#include<algorithm>
#include<iostream>

using namespace std;

namespace sample {

Node* Solution::cloneGraph(Node* head) {
    if (head == nullptr) {
        return nullptr;
    }

    Node* clone_head = new Node(head->val);
    clone_head->neighbors.reserve(head->neighbors.size());

    unordered_map<Node*, Node*> node_to_clone;
    node_to_clone[head] = clone_head;

    unordered_set<Node*> visited;
    list<Node*> stack;
    stack.push_back(head);

    list<Node*> clone_stack;
    clone_stack.push_back(clone_head);
    while (!stack.empty()) {
        Node* current_node = stack.back();
        Node* current_clone = clone_stack.back();
        cout << "visited: " << current_node->val << endl;
        visited.insert(current_node);
        bool has_unvisited_neighbors = false;
        for (Node* neighbor : current_node->neighbors) {
            if (!visited.contains(neighbor)) {
                has_unvisited_neighbors = true;
                stack.push_back(neighbor);

                Node* clone_neighbor = new Node(neighbor->val);
                node_to_clone[neighbor] = clone_neighbor;
                clone_stack.push_back(clone_neighbor);
                clone_neighbor->neighbors.reserve(neighbor->neighbors.size());
                break;
            }
        }
        if (!has_unvisited_neighbors) {         
            for (Node* neighbor : current_node->neighbors) {
                Node* clone_neighbor = node_to_clone[neighbor];
                current_clone->neighbors.push_back(clone_neighbor);
            }
            sort(current_clone->neighbors.begin(), current_clone->neighbors.end());
            stack.pop_back();
            clone_stack.pop_back();
        }
    }
    
    return clone_head;
}

} // namespace sample

