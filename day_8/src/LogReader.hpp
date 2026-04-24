#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "LogEntry.hpp"


class LogReader{
    private:
        std::vector<LogEntry> _logs{};
        int _fd{};
        std::string _path{};
    public:
        explicit LogReader(std::string path) : _path(std::move(path)){}; //no optimizations (copy, move etc)
        ~LogReader() = default;
        LogReader(const LogReader& other) = delete;
        LogReader& operator=(const LogReader& other) = delete;
        LogReader(LogReader&& other) noexcept : 
            _logs(std::move(other._logs)), 
            _fd(other._fd), 
            _path(std::move(other._path)) {}
        LogReader& operator=(LogReader&& other) noexcept {
            if (this != &other){
                _fd = other._fd;
                _path = std::move(other._path);
                _logs = std::move(other._logs);

            }
            return *this;
        }
        void read_all() {
            std::ifstream file(_path);
            std::string line;
        
            if (!file.is_open()) return;
        
            while (std::getline(file, line)) {
                // Example:
                // [2024-01-15 00:00:02] INFO  latency=179ms "db query"
        
                // 1. Extract timestamp
                size_t start = line.find('[');
                size_t end = line.find(']');
                std::string time = line.substr(start + 1, end - start - 1);
        
                // 2. Extract log type
                size_t type_start = end + 2; // skip "] "
                size_t type_end = line.find(' ', type_start);
                std::string type_str = line.substr(type_start, type_end - type_start);
        
                // Convert string → enum (you define this)
                log_type type{};
                if (type_str == "INFO") type = log_type::INFO;
                else if (type_str == "ERROR") type = log_type::ERROR;
                else if (type_str == "DEBUG") type = log_type::DEBUG;
                else type = log_type::DEFAULT;
        
                // 3. Extract latency
                size_t lat_start = line.find("latency=") + 8;
                size_t lat_end = line.find("ms", lat_start);
                int lat = std::stoi(line.substr(lat_start, lat_end - lat_start));
        
                // 4. Extract operation/message
                size_t msg_start = line.find('"', lat_end);
                size_t msg_end = line.rfind('"');
                std::string op = line.substr(msg_start + 1, msg_end - msg_start - 1);
        
                // 5. Store log entry
                _logs.emplace_back(op, time, type, lat);
            }
        
            file.close();
        }
};
