#pragma once
#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <mutex>
#include <unistd.h>
#include <numeric>
#include "LogEntry.hpp"

typedef struct {
    int total_entries;
    double avg_latency;
    double error_rate;
    int p50_latency;
    int p95_latency;
} Metrics;


class MetricStore{
    private:
        std::mutex mtx{};
        std::vector<LogEntry> _entries{};
        Metrics _metrics{};
    public:
        void push(LogEntry&& entry){
            std::lock_guard<std::mutex> lock(mtx);
            _entries.push_back(std::move(entry));
        };
        Metrics snapshot(){
            std::lock_guard<std::mutex> lock(mtx);
            if (_entries.empty()) {
                return Metrics{};
            }
            std::vector<int> latencies{};
            double error_count{};
            for (size_t x{}; x < _entries.size(); ++x){
                latencies.push_back(_entries[x].get_latency());
                if (_entries[x].get_type() == log_type::ERROR) {
                    error_count++;
                }
            }
            std::sort(latencies.begin(), latencies.end());
            size_t latency_size = latencies.size();
            _metrics.total_entries = latency_size;
            _metrics.error_rate = (double)error_count / latency_size * 100.0;
            _metrics.avg_latency = std::accumulate(latencies.begin(), latencies.end(), 0.0) / latency_size;
            _metrics.p50_latency = latencies[(size_t)(latency_size * 0.5)];
            _metrics.p95_latency = latencies[(size_t)(latency_size * 0.95)];

            return _metrics;
        }

};
