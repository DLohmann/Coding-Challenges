from typing import List

class Solution:
    def trap(self, height: List[int]) -> int:
        decreases = []
        total_water = 0
        for i in range(len(height) - 1):
            diff = height[i + 1] - height[i]
            # print(f'diff[{i}] = {diff}')
            if diff < 0:
                decreases.append(i)
                # print(f'decreases: {decreases}')
                continue
            if diff == 0:
                continue
            if len(decreases) == 0:
                continue
            increase = i

            # Find previous decrease with height greater than or equal to increase height
            # decrease = decreases.pop()
            decrease      = len(decreases) - 1
            prev_decrease = len(decreases) - 2
            while 0 <= prev_decrease and height[decreases[decrease]] <= height[increase + 1]:
                if height[decreases[prev_decrease]] > height[decreases[decrease]]:
                    decrease = prev_decrease
                prev_decrease -= 1
            while decrease < len(decreases) - 1:
                decreases.pop()
            decrease = decreases[-1]
            # print(f'\tdecrease = {decrease}, decreases = {decreases}')
            
            limit_height = min(height[decrease], height[increase + 1])
            if height[decrease] == limit_height:
                decreases.pop()
            water_between = limit_height * (increase - decrease) - sum(height[decrease + 1: increase + 1])
            total_water += water_between
            for k in range(decrease + 1, increase + 1):
                height[k] = limit_height
            # print(f'\tFilled in between {decrease} and increase {increase}: {water_between} units. heights: {height}')
        return total_water

