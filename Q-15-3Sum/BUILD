load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
  name = "ThreeSum",
  hdrs = ["ThreeSum.h"],
  srcs = ["ThreeSum.cpp"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "ThreeSum_test",
  size = "small",
  srcs = ["ThreeSum_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main",
          ":ThreeSum"],
)