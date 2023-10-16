
# Given a maze, find the shortest path from the top left (0, 0) to the bottom right. Avoid 1's (walls) and follow 0's.
# graph=
# [
# [0, 1, 0, 0, 0, 0],
# [0, 1, 0, 1, 0, 0],
# [0, 1, 0, 0, 0, 0],
# [0, 1, 0, 1, 1, 0],
# [0, 0, 0, 1, 1, 0],
# [0, 1, 1, 1, 1, 0]
# ]

# [
#    0  1  2  3  4  5
# 0 [+, 1, 0, 0, 0, 0],
# 1 [+, 1, 0, 1, 0, 0],
# 2 [+, 1, +, +, +, +],
# 3 [+, 1, +, 1, 1, +],
# 4 [+, +, +, 1, 1, +],
# 5 [0, 1, 1, 1, 1, +]
# ]
# Return [(0, 0), (1, 0), (2, 0), (3, 0), (4, 0), (4, 1), (4, 2), (3, 2), (2, 2), (2, 3), (2, 4), (2, 5), (3, 5), (4, 5), (5, 5)]

# coords[0] row
# coords[1] col
    

explored = set()

def solve_step(graph: list[list[int]], coords):
    # print(coords, end='')
    # bounds
    if coords[0] < 0 or len(graph) <= coords[0] or coords[1] < 0 or len(graph[0]) <= coords[1]:
        # print(' out of bounds')
        return None
    # walls
    if graph[coords[0]][coords[1]] == 1:
        # print(' wall')
        return None
    # explored
    if coords in explored:
        # print(' explored')
        return None
    # finish
    if coords[0] == len(graph) - 1 and coords[1] == len(graph[0]) - 1:
        print(' FINISHED!')
        return [coords]
    
    explored.add(coords)
    print('\n\tNext step ' + str(coords))
    for delta_row, delta_col in [(-1, 0),(0, -1), (0, 1), (1, 0)]:
        next_step = solve_step(
                                graph, 
                                (
                                    coords[0] + delta_row,
                                    coords[1] + delta_col
                                )
                               )
        if next_step != None:
            next_step.append(coords)
            return next_step
    return None

def solve(graph: list[list[int]])-> list[tuple[int]]:
    '''Returns list of coordinates to get from (0, 0) to (len(graph), len(graph[0])).'''
    path = solve_step(graph, (0, 0))
    if not path:
        print('No solution')
        return []
    path.reverse()
    return path

