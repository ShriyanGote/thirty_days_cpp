#include <iostream>
#include <string>
#include "LogEntry.hpp"


class LogReader{
    public:
        explicit LogReader(std::string& path) : _path(std::move(path)){};
        ~LogReader() = default;
        LogReader(const LogReader& other) = delete;
        LogReader& operator=(const LogReader& other) = delete;
        LogReader(LogReader&& other) noexcept {
            

        }
        LogReader& operator=(LogReader&& other) noexcept {

        }
        void read_all();
    private:
        std::vector<LogEntry> _logs{};
        int _fd{};
        std::string _path{};
};
