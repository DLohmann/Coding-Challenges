#include "Sample.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>

// Test with bazel from the test file directory:
// bazel test --test_output=all "//Q_X_Sample:Sample_test"

using namespace std;

using ::sample::Solution;

TEST(Sample, Test1) {
    vector<string> input = {
        "45 + 13",
        "1-2",
        "0*10",
        "99/3",
        "99/2",
        "4/3 + 9",
        "9 + 4/3",
    };
    vector<int> expected = {
        58,
        -1,
        0,
        33,
        49,
        10,
        10
    };

    for (long unsigned int i = 0; i < input.size(); i++) {
        int output = Solution().calculate(input[i]);
        cout << input[i] << " == " << output << endl;
        cout << endl << endl << endl << endl;
        EXPECT_EQ(output, expected[i]);
    }
}
