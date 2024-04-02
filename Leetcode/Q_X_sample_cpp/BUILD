load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
  name = "sample",
  hdrs = ["sample.h"],
  srcs = ["sample.cpp"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "sample_test",
  size = "small",
  srcs = ["sample_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main",
          "@com_google_googletest//:gtest",
          ":sample"],
)