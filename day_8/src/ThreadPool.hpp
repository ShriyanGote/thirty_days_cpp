#include <iostream>
#include <string>
#include <random>
#include <vector>
#include <mutex>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>
#include <unistd.h>
#include <numeric>
#include "LogEntry.hpp"


class ThreadPool{
    private:
        std::vector<std::thread> _workers{};
        std::mutex _mtx;
        bool _stop = false;
        std::condition_variable _cv;
        std::queue<std::function<void()>> _tasks;

        void worker_loop(){
            while (1){
                std::function<void()> task;
                {
                    std::unique_lock<std::mutex> lock(_mtx); // always use unique i guess
                    _cv.wait(lock, [this] {
                        return !_tasks.empty() || _stop;
                    });
                    if (_stop && _tasks.empty()){
                        return;
                    }
                    task = std::move(_tasks.front());
                    _tasks.pop();
                }
                task();
            }
        };

    public:
        explicit ThreadPool(size_t num_threads){
            for (size_t i{}; i < num_threads; ++i){
                _workers.emplace_back(&ThreadPool::worker_loop, this);
            }
        };
        ~ThreadPool(){
            {
                std::lock_guard<std::mutex> lock(_mtx);
                _stop = true;
            }
            _cv.notify_all();
            for (auto& thread : _workers){
                thread.join();
            }
        };
        void enqueue(std::function<void()> task){
            
        };

};
