#include "Sample.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>
#include<vector>

using namespace sample;

TEST(Sample, Test1) {
    ListNode l1 [] = {
        ListNode(2),
        ListNode(4),
        ListNode(3)
    };
    l1[0].next = &l1[1];
    l1[1].next = &l1[2];
    
    ListNode l2 [] = {
        ListNode(5),
        ListNode(6),
        ListNode(4)
    };
    l2[0].next = &l2[1];
    l2[1].next = &l2[2];

    ListNode expected [] = {
        ListNode(7),
        ListNode(0),
        ListNode(8)
    };
    expected[0].next = &expected[1];
    expected[1].next = &expected[2];    

    ListNode* output = Solution().addTwoNumbers(&l1[0], &l2[0]);
    
    ListNode* current_output = output;
    ListNode* current_expected = &expected[0];
    while (current_expected != nullptr || current_output != nullptr) {
        EXPECT_EQ(current_output->val, current_expected->val);
        EXPECT_TRUE((current_output->next == nullptr) == (current_expected->next == nullptr));
        current_expected = current_expected->next;
        current_output = current_output->next;
    }
    delete output;
}

TEST(Sample, Test2) {
    ListNode l1 [] = {
        ListNode(0)
    };
    
    ListNode l2 [] = {
        ListNode(0)
    };

    ListNode expected [] = {
        ListNode(0)
    };   

    ListNode* output = Solution().addTwoNumbers(&l1[0], &l2[0]);
    
    ListNode* current_output = output;
    ListNode* current_expected = &expected[0];
    while (current_expected != nullptr || current_output != nullptr) {
        EXPECT_EQ(current_output->val, current_expected->val);
        EXPECT_TRUE((current_output->next == nullptr) == (current_expected->next == nullptr));
        current_expected = current_expected->next;
        current_output = current_output->next;
    }
    delete output;
}

TEST(Sample, Test3) {
    ListNode l1 [] = {
        ListNode(9),
        ListNode(9),
        ListNode(9),
        ListNode(9),
        ListNode(9),
        ListNode(9),
        ListNode(9)
    };
    l1[0].next = &l1[1];
    l1[1].next = &l1[2];
    l1[2].next = &l1[3];
    l1[3].next = &l1[4];
    l1[4].next = &l1[5];
    l1[5].next = &l1[6];
    
    ListNode l2 [] = {
        ListNode(9),
        ListNode(9),
        ListNode(9),
        ListNode(9)
    };
    l2[0].next = &l2[1];
    l2[1].next = &l2[2];
    l2[2].next = &l2[3];

    ListNode expected [] = {
        ListNode(8),
        ListNode(9),
        ListNode(9),
        ListNode(9),
        ListNode(0),
        ListNode(0),
        ListNode(0),
        ListNode(1)
    };
    expected[0].next = &expected[1];
    expected[1].next = &expected[2];
    expected[2].next = &expected[3];
    expected[3].next = &expected[4];
    expected[4].next = &expected[5];
    expected[5].next = &expected[6];
    expected[6].next = &expected[7];

    ListNode* output = Solution().addTwoNumbers(&l1[0], &l2[0]);
    
    ListNode* current_output = output;
    ListNode* current_expected = &expected[0];
    while (current_expected != nullptr || current_output != nullptr) {
        EXPECT_EQ(current_output->val, current_expected->val);
        EXPECT_TRUE((current_output->next == nullptr) == (current_expected->next == nullptr));
        current_expected = current_expected->next;
        current_output = current_output->next;
    }
    delete output;
}
