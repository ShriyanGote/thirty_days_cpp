#include <iostream>
#include <thread>
#include <chrono>
#include "game.h"


int main(){
    std::cout << "Choose your symbol: ";
    char symbol{};
    Move move{};
    std::cin >> symbol;
    Game board(symbol);
    while (1){
        Move move{};
        board.print_board();
        std::cout << "Enter your move: ";
        std::cin >> move.row >> move.col;
        if (!board.enter_position(move)){
            std::cout<< "Try again!\n";
        };
        std::cout<< "Good move! CPU is playing...\n";
        std::this_thread::sleep_for(std::chrono::seconds(1));
        board.print_board();
        if (!board.cpu_move()){
            return 0;
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    return 0;
}