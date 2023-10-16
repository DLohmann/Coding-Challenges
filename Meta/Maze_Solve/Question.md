# This question was from a Meta interview on 10/16/2023:

Given a maze, find the shortest path from the top left (0, 0) to the bottom right. Avoid 1's (walls) and follow 0's.
```
graph=
[
[0, 1, 0, 0, 0, 0],
[0, 1, 0, 1, 0, 0],
[0, 1, 0, 0, 0, 0],
[0, 1, 0, 1, 1, 0],
[0, 0, 0, 1, 1, 0],
[0, 1, 1, 1, 1, 0]
]


[
   0  1  2  3  4  5
0 [+, 1, 0, 0, 0, 0],
1 [+, 1, 0, 1, 0, 0],
2 [+, 1, +, +, +, +],
3 [+, 1, +, 1, 1, +],
4 [+, +, +, 1, 1, +],
5 [0, 1, 1, 1, 1, +]
]
Return [(0, 0), (1, 0), (2, 0), (3, 0), (4, 0), (4, 1), (4, 2), (3, 2), (2, 2), (2, 3), (2, 4), (2, 5), (3, 5), (4, 5), (5, 5)]
```

To run:
```bash
python3 -m unittest maze_solve_test.py
```
