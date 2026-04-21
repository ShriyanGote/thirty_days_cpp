

#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <atomic>
#include <termios.h>
#include <unistd.h>
#include <mutex>
#include <sched.h>


static std::atomic<bool> running(false); // state of stopwatch
static std::atomic<bool> exit_flag(false); // if 'x' is pressed
std::mutex mtx;

std::string format_time(long long ms);

// controls updating stopwatch values
void worker_thread(std::chrono::steady_clock::time_point* start_time, 
        std::chrono::steady_clock::duration* duration){
    while (!exit_flag.load()){
        std::chrono::steady_clock::duration elapsed{};
        auto now = std::chrono::steady_clock::now(); // cur time
        {
            std::lock_guard<std::mutex>lock(mtx); // avoid race
            if (running.load()){
                elapsed = *duration + (now - *start_time); // total duration + running time
            } else {
                elapsed = *duration; // take total time if not running (q)
            }
        }
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count(); 
        std::cout << "\r" << format_time(ms) << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

std::string format_time(long long ms){
    long long seconds = ms / 1000;
    ms %= 1000;
    long long minutes = seconds / 60;
    seconds %= 60;
    std::ostringstream oss; // ostringstream obj for stream string commands '<<'
    oss << std::setfill('0') << std::setw(2) << minutes << ":"
        << std::setw(2) << seconds << "."
        << std::setw(3) << ms;
    return oss.str();
}
int main(){
    std::cout << std::thread::hardware_concurrency() << " cores available\n";
    // to get keyboard commands directly 
    struct termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

    auto start_time = std::chrono::steady_clock::now();
    auto duration = std::chrono::steady_clock::duration::zero();
    char input;
    std::thread my_thread(worker_thread, &start_time, &duration); // start worker thread
    while (1){
        input = getchar();
       if (input == 'q'){
         std::lock_guard<std::mutex>lock(mtx); // avoid race
         running = false;
         duration = std::chrono::steady_clock::duration::zero();
         std::cout << "\r00:00.000" << std::flush;
       } else if (input == 's'){
            std::lock_guard<std::mutex>lock(mtx);
            auto now = std::chrono::steady_clock::now();
            if (!running.load()){
                start_time = now;
                running = true;
            } else {
                duration += now - start_time;
                running = false;
            }
       } else if (input == 'x'){
            exit_flag = true;
            running = false;
            break;
       }
    }
    my_thread.join();
    std::cout << std::endl;
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term); // keyboard stuff
}


