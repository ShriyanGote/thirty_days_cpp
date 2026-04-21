#include <iostream>
#include <vector>
#include <unordered_map>
#include <array>


typedef struct {
    int row;
    int col;
} Move;

static constexpr int num_sides = 3;

enum class GameState {
    PLAYER_WIN,
    CPU_WIN,
    TIE,
    ONGOING
};

class Game {
    public:
        Game(char player) : player(player){
            if (player != '*'){
                cpu = '*';
            } else {
                cpu = 'x';
            }
            for (int i = 0; i < 3; ++i){
                for (int j = 0; j < 3; ++j){
                    board[i][j] = '_';
                }
            }
            std::cout << "init game!\n";
        }
        void print_board();
        bool enter_position(Move& move);
        bool cpu_move();
    private:
        bool check_win();
        GameState get_state();
        bool can_move();
        // minimax algorithm
        int evaluate();
        int minimax(int depth, bool isMax);
        Move find_best_move();
        char player;
        char cpu;
        std::array<std::array<char, 3>, 3> board;
};