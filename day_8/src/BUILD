load("@rules_cc//cc:cc_binary.bzl", "cc_binary")

cc_binary(
    name = "log_aggregator",
    srcs = [
        "main.cpp",
        "LogEntry.hpp",
        "LogReader.hpp",
        "MetricStore.hpp",
        "ThreadPool.hpp",
        "ReportWriter.hpp",
    ],
    copts = ["-Wall", "-Wextra", "-std=c++17"],
)