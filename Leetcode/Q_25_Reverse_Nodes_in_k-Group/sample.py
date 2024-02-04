from typing import List, Optional

# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverseKGroup(self, head: Optional[ListNode], k: int) -> Optional[ListNode]:
        count = 0
        section_head = head
        current = head
        prev_section_tail = ListNode(val = -1) # dummy node
        new_head = head
        while current != None:
            print(f'At node {current.val}')
            if count % k == k - 1:
                if count == k - 1:
                    new_head = current
                prev_section_tail.next = current
                print(f'point {prev_section_tail.val} -> {current.val}')
                next_section_tail = current.next
                section_current = section_head
                section_next = section_head.next
                for _ in range(k - 1):
                    print(f'\tpoint {section_next.val} -> {section_current.val}')
                    temp = section_next.next
                    section_next.next = section_current
                    section_current = section_next
                    section_next = temp
                section_head.next = next_section_tail
                print(f'point {section_head.val} -> {str(next_section_tail.val) if next_section_tail != None else "None"}')
                prev_section_tail = section_head
                current = section_head
                section_head = current.next
                

            
            current = current.next
            count += 1
        return new_head