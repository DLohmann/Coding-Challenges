load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
  name = "TwoSum",
  hdrs = ["TwoSum.h"],
  srcs = ["TwoSum.cpp"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "TwoSum_test",
  size = "small",
  srcs = ["TwoSum_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main",
          "@com_google_googletest//:gtest",
          ":TwoSum"],
)