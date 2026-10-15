#include <array>
#include <iostream>
#include <set>
#include <unordered_map>
#include "board.h"
using namespace std;

// player1 = p1 = 1
// player2 = p2 = 2

// IDEA: Infinite tic tac toe -> the first game is the "center"
// each move spawns a new game relative to the first center game
// so a top right move in the center game spawns a game top-right
// of the center. The first player to win 3 games in a row wins.


// takes a player num and board state, inputs player num's move and returns true if game was won on player num's turn.
// bool playerMove(int player, int board[])
// {
//     std::cout << "Player " << player << "'s Turn \n";
//     int p{};
//     std::cin >> p;
//     board[p - 1] = player;
//     printBoard(board);
//     return win(board);
// }

// int / int -> int so 1/3 -> 0
// returns move of a player position 1-9 in form [][]
std::pair<int, int> parseMove(int n) {
    int input = n - 1;
    int row = input / 3; // eg n = 5 -> 4/3 = 1 so row = 1
    int col = input % 3; // eg n = 5 -> 4 % 3 = 2 so col = 1
    return std::make_pair(row, col);
}

// reverts a move back into a position of 1-9 form
int getPos(std::pair<int, int> move) {
    int row = move.first;
    int col = move.second;

    return ((row*3) + 1) + col;

}


// what if I made lines a hash map so you could see the lines each player has with a number??
// should do this

// Takes a pos n, and returns a set of winning lines
set<array<int, 3>> makeLines(int n) {

    set<array<int, 3>> lines;

    int row = parseMove(n).first;
    int col = parseMove(n).second;

    // row line
    array<int, 3> row_line;

    for (int i = 0; i < 3; i++) {
        std::pair<int, int> move;
        int pos;
        move = std::make_pair(row, i);
        pos = getPos(move);
        row_line[i] = pos;
    }

    lines.insert(row_line);

    // col line
    array<int, 3> col_line;

    for (int i = 0; i < 3; i++) {
        std::pair<int, int> move;
        int pos;
        move = std::make_pair(i, col);
        pos = getPos(move);
        col_line[i] = pos;
    }

    lines.insert(col_line);

    // diagonal lines
    // all approaches I found just seemed like more complicated hard coding
    set<int> d1set = {1, 5, 9};
    set<int> d2set = {3, 5, 7};
    array<int, 3> d1line = {1, 5, 9};
    array<int, 3> d2line = {3, 5, 7};

    if (d1set.contains(n)) {
        lines.insert(d1line);
    }

    if (d2set.contains(n)) {
        lines.insert(d2line);
    }

    return lines;
}
// assume the moves to make the lines have been made
// puts new lines into the players lines, unless the line is already in the opponents lines, then that line is removed from both players
void updatePlayerLines(int player, set<array<int,3>> lines, set<array<int,3>>& dead_lines, unordered_map<int, set<array<int,3>>>& line_map) {

    int opponent;

    if (player == 1) {
        opponent = 2;
    } else {
        opponent = 1;
    }

    set<array<int, 3>>::iterator itr;
    set<array<int, 3>>& player_lines = line_map.at(player);
    set<array<int, 3>>& opponent_lines = line_map.at(opponent);

    for (itr = lines.begin(); itr != lines.end(); itr++) {

        array<int, 3> line = *itr;

        if (opponent_lines.contains(line) || dead_lines.contains(line)) { // the opponent has played a move in that line
            opponent_lines.erase(line);
            dead_lines.insert(line);
        } else { // the opponent hasnt played a move in that line
            player_lines.insert(line);
        }
    }    

}



// prints set of winning lines to terminal
void printLines(set<array<int, 3>> lines) {
    
    set<array<int, 3>>::iterator itr;

    for (itr = lines.begin(); itr != lines.end(); itr++) {

        array<int, 3> line = *itr;

        for (int i = 0; i < 3; i++){
            std::cout << line[i] << ", ";
        }
        std::cout << "\n";
    }
}

// takes player num, board, and terminal input 
// then updates board with move if valid, else prompts again.\
// requires pos is an integer in [1,9]: will add guards later
void playerMove(int player, int b[3][3], set<array<int,3>>& dead_lines, unordered_map<int, set<array<int, 3>>>& line_map) {
    
    // get pos from player
    int pos{};
    std::cin >> pos;
    
    // check 1 <= pos <= 9
    if ((pos > 9) || (pos < 1)) {
        std::cout << "Invalid, choose again!";
        playerMove(player, b, dead_lines, line_map);
    }

    // convert pos to move
    std::pair move = parseMove(pos);
    
    // update board if move valid, else prompt again
    // maybe use memoisation to see if move has been played instead of rechecking board !!
    if (b[move.first][move.second] == 0) {
        b[move.first][move.second] = player;
    } else {
        std::cout << "Ivalid, choose again!";
        playerMove(player, b, dead_lines, line_map);
    }

    set<array<int, 3>> new_lines = makeLines(pos);
    updatePlayerLines(player, new_lines, dead_lines, line_map);

}


// initializes the board and begins the game loop
int main()
{

    int board[3][3] = { };

    // maps player num to their winning lines
    unordered_map<int, set<array<int, 3>>> line_map;
    line_map = {{1, {}}, {2, {}}};
    
    set<array<int, 3>> dead_lines;

    set<array<int, 3>>& p1_lines = line_map.at(1);
    set<array<int, 3>>& p2_lines = line_map.at(2);

    printBoard(board);

    // for (int i = 0; i < 9; i++)
    // {
    //     if (i % 2 == 0)
    //     {
    //         if (playerMove(1, board))
    //         {
    //             std::cout << "Player 1 Wins!! \n";
    //             return 0;
    //         }
    //     }
    //     else if (playerMove(2, board))
    //     {
    //         std::cout << "Player 2 Wins!! \n";
    //         return 0;
    //     }
    // }

    // std::cout << "Draw! \n";

    for (int i = 0; i < 9; i++) {
        if (i % 2 == 0) {
            std::cout << "Player 1's Turn!";
            playerMove(1, board, dead_lines, line_map);
            printBoard(board);
            printLines(p1_lines);
        } else {
            std::cout << "Player 2's Turn!";
            playerMove(2, board, dead_lines, line_map);
            printBoard(board);
            printLines(p2_lines);
        }
    }

    return 0;
}
