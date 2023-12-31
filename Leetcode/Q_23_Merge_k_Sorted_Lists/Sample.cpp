#include"Sample.h"

#include<algorithm>
#include<list>
#include<tuple>

using namespace std;

namespace sample {

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 bool tupleCompareGreater(tuple<int, int>& a, tuple<int, int>& b) {
    return get<0>(a) > get<0>(b);
 }


ListNode* Solution::mergeKLists(vector<ListNode*>& lists) {
    ListNode* result = nullptr;
    ListNode* next_result;

    vector<ListNode*> current(lists.begin(), lists.end());

    vector< tuple<int, int> > heap;
    heap.reserve(lists.size());
    
    // int min_list_index = 0;
    for (int i = 0; i < lists.size(); i++) {
        if (lists[i] != nullptr) {
            heap.push_back(tie(lists[i]->val, i));
        }
    }
    make_heap(heap.begin(), heap.end(), tupleCompareGreater);
    
    while(!heap.empty()) {
        int min_val;
        int list_index;
        tie(min_val, list_index) = heap[0];
        pop_heap(heap.begin(), heap.end(), tupleCompareGreater);
        heap.pop_back();
        
        ListNode* min_node = current[list_index];
        

        if (result == nullptr) {
            result = min_node;
            next_result = min_node;
        } else {
            next_result->next = min_node;
            next_result = min_node;
        }

        
        current[list_index] = current[list_index]->next;
        if (current[list_index] != nullptr) {
            heap.push_back(tie(current[list_index]->val, list_index));
            push_heap(heap.begin(), heap.end(), tupleCompareGreater);
        }
    }
    return result;
}


} // namespace sample

