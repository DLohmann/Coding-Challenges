#include "Sample.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>
#include<unordered_set>

using ::sample::Solution;
using ::sample::Node;

void FindNodes(std::set<Node*>& found_nodes, Node* head) {
    std::cout << "Found node " << head->val << " with " << head->neighbors.size() << " neighbors." << std::endl;
    found_nodes.insert(head);
    for (Node* neighbor : head->neighbors) {
        if (!found_nodes.contains(neighbor)) {
            FindNodes(found_nodes, neighbor);
        }
    }
}

// Testing algorithm:
// 1) Create original graph. Ensure neighbors are sorted.
// 2) Find nodes in order using a certain graph traversal, in both the expected and output graphs. Use the same algorithm for both the expected and the output clone graphs.
// 3) Ensure expected node set and output node set have same size.
// 4) Iterate through each node in expected and output set.
// 5) For each node, in order, ensure that it's value is the same.
// 6) For each neighbor, in order, ensure that it's value is the same.
// 7) Delete the found nodes in the clone graph.


TEST(Sample, Example1) {
    // Input: adjList = [[2,4],[1,3],[2,4],[1,3]]
    // Output: [[2,4],[1,3],[2,4],[1,3]]
    // Explanation: There are 4 nodes in the graph.
    // 1st node (val = 1)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
    // 2nd node (val = 2)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
    // 3rd node (val = 3)'s neighbors are 2nd node (val = 2) and 4th node (val = 4).
    // 4th node (val = 4)'s neighbors are 1st node (val = 1) and 3rd node (val = 3).
    Node one = Node(1);
    Node two = Node(2);
    Node three = Node(3);
    Node four = Node(4);

    one.neighbors =   {&two, &four};
    two.neighbors =   {&one, &three};
    three.neighbors = {&two, &four};
    four.neighbors =  {&one, &three};

    Node* clone_head = Solution().cloneGraph(&one);

    std::set<Node*> found_nodes;
    std::cout << "Expected nodes" << std::endl;
    FindNodes(found_nodes, &one);

    std::set<Node*> found_clone_nodes;
    std::cout << "Clone nodes" << std::endl;
    FindNodes(found_clone_nodes, clone_head);

    EXPECT_EQ(found_clone_nodes.size(), found_nodes.size());

    std::set<Node*>::iterator found_nodes_it = found_nodes.begin();
    std::set<Node*>::iterator found_clone_nodes_it = found_clone_nodes.begin();
    while (found_nodes_it != found_nodes.end() || found_clone_nodes_it != found_clone_nodes.end()) {
        Node* node = *found_nodes_it;
        Node* clone = *found_clone_nodes_it;
        EXPECT_EQ(clone->val, node->val) << "Clone #" << clone->val << " was found in same order as node #" << node->val <<
            ". Corresponding nodes must have the same value.";
        
        EXPECT_EQ(clone->neighbors.size(), node->neighbors.size());
        for (int i = 0; i < node->neighbors.size(); i++) {
            EXPECT_EQ(clone->neighbors[i]->val, node->neighbors[i]->val) << 
                "Output clone node #"    << clone->val << " neighbor #" << i << " (" << clone->neighbors[i]->val << ")" <<
                " does not match node #" << node ->val << " neighbor #" << i << " (" << node ->neighbors[i]->val << ")" << std::endl;
        }

        found_nodes_it++;
        found_clone_nodes_it++;
    }

    for (Node* clone_node : found_clone_nodes) {
        delete clone_node;
    }
}
