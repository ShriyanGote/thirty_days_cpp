#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <unistd.h>
#include <fcntl.h>    // for O_RDONLY, open()
#include "LogEntry.hpp"


class LogReader{
    private:
        std::vector<LogEntry> _logs{};
        int _fd{-1};
        std::string _path{};
        void parseLine(const std::string& line) {
            if (line.empty()) return;
    
            size_t start = line.find('[');
            size_t end = line.find(']');
            std::string time = line.substr(start + 1, end - start - 1);
    
            size_t type_start = end + 2;
            size_t type_end = line.find(' ', type_start);
            std::string type_str = line.substr(type_start, type_end - type_start);
    
            log_type type = log_type::DEFAULT;
            if (type_str == "INFO")       type = log_type::INFO;
            else if (type_str == "WARN")  type = log_type::WARN;
            else if (type_str == "ERROR") type = log_type::ERROR;
            else if (type_str == "DEBUG") type = log_type::DEBUG;
    
            size_t lat_start = line.find("latency=") + 8;
            size_t lat_end = line.find("ms", lat_start);
            int lat = std::stoi(line.substr(lat_start, lat_end - lat_start));
    
            size_t msg_start = line.find('"', lat_end);
            size_t msg_end = line.rfind('"');
            std::string op = line.substr(msg_start + 1, msg_end - msg_start - 1);
    
            _logs.emplace_back(op, time, type, lat);
        }
    public:
        explicit LogReader(std::string path) : _path(std::move(path)){
            _fd = open(_path.c_str(), O_RDONLY);
            if (_fd == -1){
                throw std::runtime_error("failed to open: " + _path);
                // error handling: throw -> 
            }
        }; //no optimizations (copy, move etc)
        ~LogReader(){
            if (_fd != -1) close(_fd);
        }
        LogReader(const LogReader& other) = delete;
        LogReader& operator=(const LogReader& other) = delete;
        LogReader(LogReader&& other) noexcept : 
            _logs(std::move(other._logs)), 
            _fd(other._fd), 
            _path(std::move(other._path)) {
                other._fd = -1;
            }
        LogReader& operator=(LogReader&& other) noexcept {
            if (this != &other){
                _fd = other._fd;
                _path = std::move(other._path);
                _logs = std::move(other._logs);
                other._fd = -1;
            }
            return *this;
        }
        void read_all() {
            char buf[4096];
            std::string leftover;
            ssize_t n;
    
            while ((n = read(_fd, buf, sizeof(buf))) > 0) {
                leftover += std::string(buf, n);
                size_t pos;
                while ((pos = leftover.find('\n')) != std::string::npos) {
                    parseLine(leftover.substr(0, pos));
                    leftover = leftover.substr(pos + 1);
                }
            }
        }
        std::vector<LogEntry> get_logs(){
            return std::move(_logs);
        }
};
