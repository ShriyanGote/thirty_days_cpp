#include <iostream>
#include <string>

enum class log_type {
    INFO,
    WARN,
    ERROR,
    DEBUG,
    DEFAULT
};

class LogEntry{
    public:
        LogEntry(std::string op, std::string time, log_type type, int lat) : _operation(std::move(op)), _timestamp(std::move(time)), _type(type), _latency(lat){};
        ~LogEntry() = default;
        LogEntry(const LogEntry& other){
            _operation = other._operation;
            _timestamp = other._timestamp;
            _type = other._type;
            _latency = other._latency;
        } //copy ctor
        LogEntry& operator=(const LogEntry& other){
            if (this != &other){
                _operation = other._operation;
                _timestamp = other._timestamp;
                _type = other._type;
                _latency = other._latency;
            }
            return *this;
        } // copy asgn
        LogEntry(LogEntry&& other) noexcept
            : _operation(std::move(other._operation))
            , _timestamp(std::move(other._timestamp))
            , _type(other._type)
            , _latency(other._latency) {
            other._latency = 0;  // zero out primitives in body
            other._type = log_type::DEFAULT;
        }
        LogEntry& operator=(LogEntry&& other) noexcept{
            if (this != &other){
                _operation = std::move(other._operation);
                _timestamp = std::move(other._timestamp);
                _type = other._type;
                _latency = other._latency;
            }
            return *this;
        }// move asgn
        //&& indicates an RVALUE (temporary object)
    private:
        std::string _operation{};
        std::string _timestamp{};
        log_type _type; //dont want to default to info
        int _latency{};

};