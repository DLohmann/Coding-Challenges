from typing import List

class Solution:
    def __init__(self):
        self.longest_path = dict(default=1)
    
    def getLongestIncreasingPath(self, matrix: List[List[int]], row: int, col: int) -> int:
        # print(f'getLongestIncreasingPath({row}, {col})')
        if (row, col) in self.longest_path:
            # print(f'\tPre-computed length {self.longest_path[(row, col)]}')
            return self.longest_path[(row, col)]
        longest_path = 1
        for next_row, next_col in [(row - 1, col), (row, col - 1), (row + 1, col), (row, col + 1)]:
            if next_row < 0 or len(matrix) <= next_row or next_col < 0 or len(matrix[0]) <= next_col:
                continue
            if matrix[next_row][next_col] <= matrix[row][col]:
                continue
            path = 1 + self.getLongestIncreasingPath(matrix, next_row, next_col)
            # print(f'\tTo: ({next_row}, {next_col}, val: {matrix[next_row][next_col]}) length: {path}')
            longest_path = max(longest_path, path)
        self.longest_path[(row, col)] = longest_path
        return longest_path

    def longestIncreasingPath(self, matrix: List[List[int]]) -> int:
        longest_path = 0
        for row in range(len(matrix)):
            for col in range(len(matrix[0])):
                longest_path = max(longest_path, self.getLongestIncreasingPath(matrix, row, col))
        return longest_path
                
