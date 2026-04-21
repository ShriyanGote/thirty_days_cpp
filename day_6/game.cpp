#include <iostream>
#include "game.h"


void Game::print_board(){
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            std::cout<<board[i][j]<< " ";
        }
        puts("\n");
    }
}

bool Game::enter_position(Move& move){
    if (move.row < 3 && move.col < 3 && board[move.row][move.col] == '_'){
        board[move.row][move.col] = player;
        return true;
    }
    return false;
}

bool Game::check_win(){
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            std::cout<<board[i][j]<< " ";
        }
        puts("\n");
    }
    return false;
}

bool Game::can_move(){
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
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
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
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
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
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
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
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

int Game::evaluate()
{
    // Checking for Rows for X or O victory.
    for (int row = 0; row<3; row++)
    {
        if (board[row][0]==board[row][1] &&
            board[row][1]==board[row][2])
        {
            if (board[row][0]==cpu)
                return +10;
            else if (board[row][0]==player)
                return -10;
        }
    }
    // Checking for Columns for X or O victory.
    for (int col = 0; col<3; col++)
    {
        if (board[0][col]==board[1][col] &&
            board[1][col]==board[2][col])
        {
            if (board[0][col]==cpu)
                return +10;

            else if (board[0][col]==player)
                return -10;
        }
    }
    // Checking for Diagonals for X or O victory.
    if (board[0][0]==board[1][1] && board[1][1]==board[2][2])
    {
        if (board[0][0]==cpu)
            return +10;
        else if (board[0][0]==player)
            return -10;
    }

    if (board[0][2]==board[1][1] && board[1][1]==board[2][0])
    {
        if (board[0][2]==cpu)
            return +10;
        else if (board[0][2]==player)
            return -10;
    }
    // Else if none of them have won then return 0
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
