from typing import List

from itertools import accumulate

class Solution:
    # Approach: separate start and end lists
    def minGroups(self, intervals: List[List[int]]) -> int:
        starts, ends = map(list, zip(*intervals))

        overlaps = list()
        overlaps.extend([start, +1] for start in starts)
        overlaps.extend([end,   -1] for end   in ends)
        overlaps.sort(key=lambda t: [t[0], -1 * t[1]] )
        
        return max(accumulate(num_groups for index, num_groups in overlaps))
        