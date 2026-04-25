#include "LogReader.hpp"
#include "MetricStore.hpp"
#include "ThreadPool.hpp"
#include "ReportWriter.hpp"
#include <dirent.h>
#include <chrono>


int main() {
    auto start = std::chrono::steady_clock::now();
    MetricStore store;

    {
        ThreadPool pool(6);

        DIR* dir = opendir("src/logs");
        if (!dir) {
            std::cerr << "Failed to open logs directory\n";
            return 1;
        }
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            std::string name = entry->d_name;
            if (name.find(".log") != std::string::npos) {
                std::string path = "src/logs/" + name;
                pool.enqueue([&store, path]() {
                    LogReader reader(path);
                    reader.read_all();
                    auto logs = reader.get_logs();
                    for (auto& log : logs) {
                        store.push(std::move(log));
                    }
                });
            }
        }
        closedir(dir);
    } // pool destructs here → joins all threads → all tasks complete

    Metrics m = store.snapshot();
    ReportWriter writer(std::make_unique<PlainFormatter>());
    writer.write_report(m);

    auto end = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Total time: " << ms << "ms\n";
}