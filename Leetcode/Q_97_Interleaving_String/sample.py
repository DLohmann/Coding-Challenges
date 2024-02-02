from typing import List

from collections import Counter #, deque

class Solution:
    def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
        '''Dynamic programming approach'''
        if len(s3) != len(s1) + len(s2):
            return False
        
        # Counter optimization. Not required.
        if Counter(s1 + s2) != Counter(s3):
            return False

        found_paths = set()
        found_paths.add( (len(s1), len(s2)) )

        for s1_i in range(len(s1), 0, -1):
            if s1[s1_i - 1] == s3[len(s2) + s1_i - 1] and (s1_i, len(s2)) in found_paths:
                found_paths.add( (s1_i - 1, len(s2)) )
        
        for s2_i in range(len(s2), 0, -1):
            if s2[s2_i - 1] == s3[len(s1) + s2_i - 1] and (len(s1), s2_i) in found_paths:
                found_paths.add( (len(s1), s2_i - 1) )

        for s1_i in range(len(s1) - 1, -1, -1):
            for s2_i in range(len(s2) - 1, -1, -1):
                if (s1[s1_i] == s3[s1_i + s2_i] and (s1_i + 1, s2_i    ) in found_paths) or  (s2[s2_i] == s3[s1_i + s2_i] and (s1_i    , s2_i + 1) in found_paths):
                    found_paths.add( (s1_i, s2_i) )
        return (0, 0) in found_paths
    
    # def isInterleave(self, s1: str, s2: str, s3: str) -> bool:
    #     '''Iterative backtracking approach'''
    #     if len(s3) != len(s1) + len(s2):
    #         return False
    #     s1_index = 0
    #     s2_index = 0
    #     stack = deque()
    #     while s1_index + s2_index < len(s3):
    #         c = s3[s1_index + s2_index]
    #         s1_match = False
    #         s2_match = False
    #         if s1_index < len(s1) and c == s1[s1_index]:
    #             s1_match = True
    #         if s2_index < len(s2) and c == s2[s2_index]:
    #             s2_match = True
            
    #         if s1_match and s2_match:
    #             stack.append( (s1_index, s2_index) )
    #             # Take path of s1 first
    #             s1_index += 1
    #         elif s1_match:
    #             s1_index += 1
    #         elif s2_match:
    #             s2_index += 1
    #         else:
    #             if len(stack) == 0:
    #                 return False
    #             else:
    #                 s1_index, s2_index = stack.pop()
    #                 # Take path of s2 next
    #                 s2_index += 1
    #     return True


  
