from typing import List

class Solution:
    def pacificAtlantic(self, heights: List[List[int]]) -> List[List[int]]:
        num_rows = len(heights)
        num_cols = len(heights[0])
        flows_to_pacific = set()
        flows_to_atlantic = set()

        def calculateFlow(row, col, flows):
            # print(f'\tcalculateFlow({row}, {col})')
            flows.add( (row, col) )
            # print('\tchecking neighbors')
            for neighbor_row, neighbor_col in [(row + 1, col), (row - 1, col), (row, col + 1), (row, col - 1)]:
                if neighbor_row < 0 or num_rows <= neighbor_row or neighbor_col < 0 or num_cols <= neighbor_col:
                    # print(f'\t\tneighbor ({neighbor_row}, {neighbor_col}) out of bounds')
                    continue
                if heights[neighbor_row][neighbor_col] < heights[row][col]:
                    # print(f'\t\tneighbor ({neighbor_row}, {neighbor_col}) is lower')
                    continue
                if (neighbor_row, neighbor_col) in flows:
                    # print(f'\t\tneighbor ({neighbor_row}, {neighbor_col}) already in flows')
                    continue
                calculateFlow(neighbor_row, neighbor_col, flows)
        
            # print(f'\tfinished checking neighbors for calculateFlow({row}, {col})')
        for row in range(num_rows):
            # print('row #', str(row))
            calculateFlow(row, 0, flows_to_pacific)
            calculateFlow(row, num_cols - 1, flows_to_atlantic)
        for col in range(num_cols):
            # print('col #', str(col))
            calculateFlow(0, col, flows_to_pacific)
            calculateFlow(num_rows - 1, col, flows_to_atlantic)
        return list(map(list, set.intersection(flows_to_pacific, flows_to_atlantic)))

# Thanks to:
# https://leetcode.com/problems/pacific-atlantic-water-flow/solutions/264494/python-very-concise-solution-using-dfs-set-128ms