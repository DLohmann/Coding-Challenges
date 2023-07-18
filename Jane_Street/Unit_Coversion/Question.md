
# Question from Jane Street mock interview: [on YouTube](https://youtu.be/V8DGdPkBBxg)

Write an algorithm to, given a list of units and conversion ratios, convert a certain quantity of one unit type to another unit type.

This is similar to the [equation division leetcode question](https://leetcode.com/problems/evaluate-division/).

My approach:
* Make a set of units (ie 'm', 'ft', etc).
* Make a map of conversion ratios going one way (ie 'm->ft': 3.28) and the other way (ie 'm->ft': 1.0 / 3.28). Treat these as edges in a graph.
* Use depth first search to, starting from the initial unit, find a "path" through different units to reach the target unit. Keep exploring searching for the target unit until all nodes are explored. Make sure to "retreat" from a node if all it's neighbors are explored. If all units connected directly or indirectly to the initial unit are explored, then return no solution.
* If a path through the graph from the initial unit to the target unit is found, then multiply all the conversion ratios together, and multiply by the initial amount.

## How to run:

`python3 -m unittest Jane_Street/Unit_Coversion/UnitConversion.py`

Running without `-m unittest` ***skips the tests!***
