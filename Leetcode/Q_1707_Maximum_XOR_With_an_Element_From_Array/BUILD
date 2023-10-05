load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
  name = "MaximumXorWithElementFromArray",
  hdrs = ["MaximumXorWithElementFromArray.h"],
  srcs = ["MaximumXorWithElementFromArray.cpp"],
  visibility = ["//visibility:public"],
)

cc_test(
  name = "MaximumXorWithElementFromArray_test",
  size = "small",
  timeout = "moderate",
  srcs = ["MaximumXorWithElementFromArray_test.cpp"],
  deps = ["@com_google_googletest//:gtest_main",
          "@com_google_googletest//:gtest",
          ":MaximumXorWithElementFromArray"],
)