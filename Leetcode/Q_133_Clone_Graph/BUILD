load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
  name = "Sample",
  hdrs = ["Sample.h"],
  copts = ["-std=c++20"],
  srcs = ["Sample.cpp"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "Sample_test",
  size = "small",
  copts = ["-std=c++20"],
  srcs = ["Sample_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main",
          "@com_google_googletest//:gtest",
          ":Sample"],
)