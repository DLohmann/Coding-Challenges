### Instructions to setup Python directory for Leetcode Question
* Copy Q_X_sample_cpp
* Rename it to Q_{Leetcode #}_{problem name with _ for spaces}_Python (ensure path has no spaces).
* In Question.md:
    * In title replace `__X__` with leetcode number, `sample` with problem name, `leetcode_link` with leetcode link
    * In middle replace "TODO: Copy and paste question from HTML on LeetCode." with HTML element containing problem description on leetcode website.
    * In bazel command section, remove "(ensure path has no spaces)", and replace `Q_X_sample_cpp` with the path.


* In sample.cpp:
    * Copy code from Leetcode site, and paste it into sample.py, under `from typing import List`. Overwrite previous code except this first line.
* In sample_test.py
    * Replace the name `TestFizzbuzz` with `Test{name of leetcode function}`. If the leetcode function name uses camel case, capitalize the first letter to ensure that the first letter of each word is upper case.
    * Replace the description '''Unit test for sample fizzbuzz function.''' with another description.
    * Remove comment `# The test name must start with letters 'test' ...`.
    * Replace `test_100` with `test_example_1`. Maybe also add example, 2, 3, etc for all the test cases in the problem description.
    * Replace `fizzbuzz` with the leetcode function name.
    * Replace the outpuit with the expected output from the example.
    * Write the unit test.
* Run the unit test using the command in Question.md and make sure it passes. If it does not, then debug.

    
