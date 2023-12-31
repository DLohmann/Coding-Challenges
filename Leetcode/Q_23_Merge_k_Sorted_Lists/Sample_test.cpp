#include "Sample.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>
#include<list>

using ::sample::Solution;
using namespace sample;

ListNode* makeListFromVector(std::vector<int> v) {
    ListNode* last = nullptr;
    for (std::vector<int>::reverse_iterator it = v.rbegin(); it != v.rend(); it++) {
        last = new ListNode(*it, last);
    }
    return last;
}

void DeleteList(ListNode* head) {
    std::list<ListNode*> nodes;
    ListNode* current = head;
    while (current != nullptr) {
        nodes.push_back(current);
        current = current->next;
    }
    for (std::list<ListNode*>::reverse_iterator it = nodes.rbegin(); it != nodes.rend(); it++) {
        delete *it;
    }
}

std::vector<int> makeVectorFromList(ListNode* head) {
    ListNode* current = head;
    std::vector<int> v;
    while (current != nullptr) {
        v.push_back(current->val);
        current = current->next;
    }
    return v;
}

TEST(Sample, Example1) {
    std::vector<ListNode*> input = {
        makeListFromVector({1,4,5}),
        makeListFromVector({1,3,4}),
        makeListFromVector({2,6})
    };
    ListNode* result = Solution().mergeKLists(input);
    EXPECT_THAT(makeVectorFromList(result), ::testing::ElementsAre(1,1,2,3,4,4,5,6));
    DeleteList(result);
}

TEST(Sample, Example2) {
    std::vector<ListNode*> input = {};
    ListNode* result = Solution().mergeKLists(input);
    std::vector<int> result_vector = makeVectorFromList(result);
    EXPECT_THAT(std::vector<int>(), ::testing::IsEmpty());
    DeleteList(result);
}

TEST(Sample, Example3) {
    std::vector<ListNode*> input = {
        makeListFromVector({})
    };
    ListNode* result = Solution().mergeKLists(input);
    EXPECT_THAT(makeVectorFromList(result), ::testing::IsEmpty());
    DeleteList(result);
}
