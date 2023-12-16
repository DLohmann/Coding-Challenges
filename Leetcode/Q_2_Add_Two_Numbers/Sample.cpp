#include"Sample.h"

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
ListNode* Solution::addTwoNumbers(ListNode* l1, ListNode* l2) {
    int carryover = 0;
    ListNode* l1_current = l1;
    ListNode* l2_current = l2;
    ListNode* l_sum = nullptr;
    ListNode* l_sum_current = nullptr;
    while(l1_current != nullptr || l2_current != nullptr || carryover > 0) {
        ListNode* l_sum_new = new ListNode();
        if (l_sum == nullptr) {
            l_sum = l_sum_new;
        } else {
            l_sum_current->next = l_sum_new;
        }
        l_sum_current = l_sum_new;
        int l1_val = 0, l2_val = 0;
        if(l1_current != nullptr){
            l1_val = l1_current->val;
            l1_current = l1_current->next;
        }
        if(l2_current != nullptr){
            l2_val = l2_current->val;
            l2_current = l2_current->next;
        }
        int sum = carryover + l1_val + l2_val;
        l_sum_current->val = sum % 10;
        carryover = sum / 10;

    }
    return l_sum;
}

} // namespace sample

