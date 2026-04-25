#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>

#include "MetricStore.hpp"

class Formatter {
    public:
        virtual std::string format(const Metrics& m) = 0;
        virtual ~Formatter() = default;
    };

class PlainFormatter : public Formatter {
    public:
        std::string format(const Metrics& m) override{
            std::ostringstream out;
            out << "Average Latency: " << m.avg_latency << std::endl 
                << "Average Latency p50: " << m.p50_latency << std::endl 
                << "Average Latency p95: " << m.p95_latency << std::endl 
                << "Error Rate: " << m.error_rate << std::endl
                << "Total Entries: " << m.total_entries << std::endl;
            return out.str();
        }
    };

class JsonFormatter : public Formatter {
    public:
        std::string format(const Metrics& m) override{
            std::ostringstream out;
            out << "{\n"
                << "  \"avg_latency\": " << m.avg_latency << ",\n"
                << "  \"p50_latency\": " << m.p50_latency << ",\n"
                << "  \"p95_latency\": " << m.p95_latency << ",\n"
                << "  \"error_rate\": "  << m.error_rate  << ",\n"
                << "  \"total_entries\": " << m.total_entries << "\n"
                << "}\n";
            return out.str();
        }
    };


class ReportWriter {
    public:
        ReportWriter(std::unique_ptr<Formatter> f) : _formatter(std::move(f)){};
        void write_report(const Metrics& m){
            std::string out = _formatter->format(m);
            write(STDOUT_FILENO, out.data(), out.size());
        };
    private:
        std::unique_ptr<Formatter> _formatter;

};