### Instructions to setup Python directory for Leetcode Question
* Copy Q_X_sample_cpp
* Rename it to Q_{Leetcode #}_{problem name with _ for spaces}_Python (ensure path has no spaces).
* In Question.md:
    * In title replace `__X__` with leetcode number, `sample` with problem name, `leetcode_link` with leetcode link
    * In middle replace "TODO: Copy and paste question from HTML on LeetCode." with HTML element containing problem description on leetcode website.
    * In bazel command section, remove "(ensure path has no spaces)", and replace `Q_X_sample_cpp` with the path.
* In sample.cpp:
    * Copy code from Leetcode site, and paste it into sample.py, under the `#include`'s inside the namespace. Overwrite previous code in the namespace.
    * Remove `class Solution {` and closing `}`.
    * Remove `public:` and other tags modifying member variable and member function visibility.
    * Add `'Solution::` before every function name.
    * Add `std::` before all containers.
* In sample.h
    * Copy all function declarations in `Solution` object into `sample.h` Add `;` after function declarations.
    * Add `std::` Before all containers.
* In sample_test.cpp
    * Replace `Solution().sample` with `Solution().{name of leetcode function}`.
    * Replace `Test1` with `TestExample1`. Maybe also add example, 2, 3, etc for all the test cases in the problem description.
    * Replace the output with the expected output from the example.
    * Write the unit test.

* Run the unit test using the command in Question.md and make sure it passes. If it does not, then debug.

    
