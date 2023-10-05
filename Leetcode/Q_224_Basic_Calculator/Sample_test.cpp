#include "Sample.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>
#include<utility>

// Test with bazel from the test file directory:
// bazel test --test_output=all Q_224_Basic_Calculator:all

using namespace std;

using ::sample::Solution;


TEST(Sample, TestSingleNumber) {
    vector< pair<string, int> > input_and_expected_solution = {
        {"99", 99},
        {"0", 0},
        {"  0 ", 0},
        {"101 ", 101},
        {" 101", 101}
    };

    for (pair<string, int> p : input_and_expected_solution) {
        int output = Solution().calculate(p.first);
        EXPECT_EQ(output, p.second) << "Incorrect: " << p.first << " != " << output << endl << endl << endl << endl << endl;
    }
}

TEST(Sample, TestAddition) {
    vector< pair<string, int> > input_and_expected_solution = {
        {"45 + 13", 58},
        {"123456 + 654321", 777777},
        {"123456+654321", 777777}
    };

    for (pair<string, int> p : input_and_expected_solution) {
        int output = Solution().calculate(p.first);
        EXPECT_EQ(output, p.second) << "Incorrect: " << p.first << " != " << output << endl << endl << endl << endl << endl;
    }
}

TEST(Sample, TestMultiplication) {
    vector< pair<string, int> > input_and_expected_solution = {
        {"0*10", 0},
        {"1*123", 123},
        {"123*123", 15129},
        {"5 * 7", 35}
    };

    for (pair<string, int> p : input_and_expected_solution) {
        int output = Solution().calculate(p.first);
        EXPECT_EQ(output, p.second) << "Incorrect: " << p.first << " != " << output << endl << endl << endl << endl << endl;
    }
}

TEST(Sample, TestDivision) {
    vector< pair<string, int> > input_and_expected_solution = {
        {"99/3", 33},
        {"99/2", 49},
        {"4/3 + 9", 10},
        {"9 + 4/3", 10}
    };

    for (pair<string, int> p : input_and_expected_solution) {
        int output = Solution().calculate(p.first);
        EXPECT_EQ(output, p.second) << "Incorrect: " << p.first << " != " << output << endl << endl << endl << endl << endl;
    }
}

TEST(Sample, TestSubtraction) {
    vector< pair<string, int> > input_and_expected_solution = {
        {"1-2", -1},
        {"0 - 99", -99},
    };

    for (pair<string, int> p : input_and_expected_solution) {
        int output = Solution().calculate(p.first);
        EXPECT_EQ(output, p.second) << "Incorrect: " << p.first << " != " << output << endl << endl << endl << endl << endl;
    }
}

TEST(Sample, TestNegative) {
    vector< pair<string, int> > input_and_expected_solution = {
        {"-99", -99},
        {" -1 ", -1},
        {" - 1 ", -1},
        {" - - 1 ", 1},
        {"--1", 1},
        {"-0", 0}
    };

    for (pair<string, int> p : input_and_expected_solution) {
        int output = Solution().calculate(p.first);
        EXPECT_EQ(output, p.second) << "Incorrect: " << p.first << " != " << output << endl << endl << endl << endl << endl;
    }
}

TEST(Sample, TestNegativeWithOperation) {
    vector< pair<string, int> > input_and_expected_solution = {
        {"-99 * 2", -198},
        {"-99*2", -198},
        {"2 * - 99", -198},
        {"2 * -99", -198},
        {"2 *- 99", -198},
        {"2 *-99", -198},
        {"2* - 99", -198},
        {"2* -99", -198},
        {"2*- 99", -198},
        {"2*-99", -198},
        {" -1 *0", 0},
        {" - 1 * 100", -100},
        {"-1*-1", 1},
        {"-1*--1", -1},
        {"--1*-1", -1}
    };

    for (pair<string, int> p : input_and_expected_solution) {
        int output = Solution().calculate(p.first);
        EXPECT_EQ(output, p.second) << "Incorrect: " << p.first << " != " << output << endl << endl << endl << endl << endl;
    }
}

// TEST(Sample, TestNegativeGrouping) {
//     vector< pair<string, int> > input_and_expected_solution = {
//         {"-(1)", -1},
//         {"-(-1)", 1},
//         {"(-(-1))", 1},
//         {"-(-(-1))", -1},
//         {"-(1)-(1)", 0}
//     };

//     for (pair<string, int> p : input_and_expected_solution) {
//         int output = Solution().calculate(p.first);
//         EXPECT_EQ(output, p.second) << "Incorrect: " << p.first << " != " << output << endl << endl << endl << endl << endl;
//     }
// }

// TEST(Sample, TestBadInput) {
//     vector< pair<string, int> > input_and_expected_solution = {
//         {"1 2", INT_MIN},
//         {" - ", INT_MIN},
//         {" + ", INT_MIN},
//         {"safdsafdsafds", INT_MIN}
//     };

//     for (pair<string, int> p : input_and_expected_solution) {
//         int output = Solution().calculate(p.first);
//         EXPECT_EQ(output, p.second) << "Incorrect: " << p.first << " != " << output << endl << endl << endl << endl << endl;
//     }
// }

