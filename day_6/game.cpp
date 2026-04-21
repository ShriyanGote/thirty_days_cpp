#include <iostream>
#include "game.h"


void Game::print_board(){
    for (int i = 0; i < num_sides; ++i){
        for (int j = 0; j < num_sides; ++j){
            std::cout<<board[i][j]<< " ";
        }
        puts("\n");
    }
}

bool Game::enter_position(Move& move){
    if (move.row < num_sides && move.col < num_sides && board[move.row][move.col] == '_'){
        board[move.row][move.col] = player;
        return true;
    }
    return false;
}

bool Game::check_win(){
    for (int i = 0; i < num_sides; ++i){
        for (int j = 0; j < num_sides; ++j){
            std::cout<<board[i][j]<< " ";
        }
        puts("\n");
    }
    return false;
}

bool Game::can_move(){
    for (int i = 0; i < num_sides; ++i){
        for (int j = 0; j < num_sides; ++j){
            if (board[i][j] == '_'){
                return true;
            }
        }
    }
    return false;
}

Move Game::find_best_move(){
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    // Traverse all cells, evaluate minimax function for
    // all empty cells. And return the cell with optimal
    // value.
    for (int i = 0; i<num_sides; i++)
    {
        for (int j = 0; j<num_sides; j++)
        {
            // Check if cell is empty
            if (board[i][j]=='_')
            {
                board[i][j] = cpu;

                int moveVal = minimax(0, false);

                board[i][j] = '_';

                // If the value of the current move is
                // more than the best value, then update
                // best/
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    printf("The value of the best Move is : %d\n\n",
            bestVal);
    return bestMove;
}

int Game::minimax(int depth, bool isMax){
    int score = evaluate();

    if (score == 10)
        return score;
    if (score == -10)
        return score;

    if (!can_move())
        return 0;

    // If this maximizer's move
    if (isMax)
    {
        int best = -1000;
        for (int i = 0; i<num_sides; i++)
        {
            for (int j = 0; j<num_sides; j++)
            {
                if (board[i][j]=='_')
                {
                    board[i][j] = cpu;
                    best = std::max(best, minimax(depth+1, !isMax));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;
        for (int i = 0; i<num_sides; i++)
        {
            for (int j = 0; j<num_sides; j++)
            {
                if (board[i][j]=='_')
                {
                    board[i][j] = player;
                    best = std::min(best, minimax(depth+1, !isMax));
                    board[i][j] = '_';
                }
            }
        }
        return best;
    }
}


GameState Game::get_state() {
    // rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != '_' &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2]) {
            return (board[i][0] == cpu) ? GameState::CPU_WIN : GameState::PLAYER_WIN;
        }
    }

    // cols
    for (int j = 0; j < 3; j++) {
        if (board[0][j] != '_' &&
            board[0][j] == board[1][j] &&
            board[1][j] == board[2][j]) {
            return (board[0][j] == cpu) ? GameState::CPU_WIN : GameState::PLAYER_WIN;
        }
    }

    // diagonals
    if (board[0][0] != '_' &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2]) {
        return (board[0][0] == cpu) ? GameState::CPU_WIN : GameState::PLAYER_WIN;
    }

    if (board[0][2] != '_' &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0]) {
        return (board[0][2] == cpu) ? GameState::CPU_WIN : GameState::PLAYER_WIN;
    }

    if (!can_move()) return GameState::TIE;

    return GameState::ONGOING;
}

int Game::evaluate() {
    GameState state = get_state();

    if (state == GameState::CPU_WIN) return 10;
    if (state == GameState::PLAYER_WIN) return -10;
    return 0;
}

bool Game::cpu_move(){
    if (!can_move()){
        std::cout << "GAME OVER TIE GAME!\n";
        return false;
    }
    Move move = find_best_move();
    board[move.row][move.col] = cpu;
    return true;
}
