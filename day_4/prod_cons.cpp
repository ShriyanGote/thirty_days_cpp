#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <queue>
#include <condition_variable>


std::mutex mtx; // avoid race
std::queue<int> q; // mimic shared memory
std::condition_variable cv; // like a flag between threads to indicate 


void consumer(){
    while (1){
        {
            std::unique_lock<std::mutex> lock(mtx); // always use unique i guess
            cv.wait(lock, [] { return !q.empty(); });
            std::cout << "Removing: " << q.front() << std::endl;
            q.pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500)); 
        // outside of mutex scope so its not called while mutex is held
    }
}

void producer(){
    while (1){
        {
            std::unique_lock<std::mutex> lock(mtx);
            int val = rand();
            std::cout << "Adding: " << val << std::endl;
            q.push(val);
            cv.notify_one();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

int main(){
    std::thread consumer_thread(consumer);
    std::thread producer_thread(producer);
    consumer_thread.join();
    producer_thread.join();
}