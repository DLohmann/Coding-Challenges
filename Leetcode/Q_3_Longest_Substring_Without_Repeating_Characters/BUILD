load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
  name = "LongestUniqueSubstring",
  hdrs = ["longest_unique_substring.h"],
  srcs = ["longest_unique_substring.cpp"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "LongestUniqueSubstring_test",
  size = "small",
  srcs = ["longest_unique_substring_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main",
          "@com_google_googletest//:gtest",
          ":LongestUniqueSubstring"],
)