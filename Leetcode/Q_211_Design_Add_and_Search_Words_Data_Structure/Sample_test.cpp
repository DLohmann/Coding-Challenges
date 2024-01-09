#include "Sample.h"

#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include<iostream>

using ::sample::WordDictionary;

TEST(Sample, Example) {
    // std::vector<int> input;
    // EXPECT_THAT(Solution().sample(input), ::testing::ElementsAre(1, 2));
    WordDictionary wordDictionary = WordDictionary();
    wordDictionary.addWord("bad");
    wordDictionary.addWord("dad");
    wordDictionary.addWord("mad");
    EXPECT_FALSE(wordDictionary.search("pad")); // return False
    EXPECT_TRUE(wordDictionary.search("bad")); // return True
    EXPECT_TRUE(wordDictionary.search(".ad")); // return True
    EXPECT_TRUE(wordDictionary.search("b..")); // return True
}
