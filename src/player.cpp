#include <array>
#include <iostream>
#include <set>
#include <unordered_map>
#include "board.h"
using namespace std;

// Integer division in cpp is handy: int / int -> int so 1/3 -> 0
// Returns move of a player position [1, 9] in form [][]
std::pair<int, int> parseMove(int n) {
    int input = n - 1;
    int row = input / 3; // eg n = 5 -> 4/3 = 1 so row = 1
    int col = input % 3; // eg n = 5 -> 4 % 3 = 2 so col = 1
    return std::make_pair(row, col);
}

// Reverts a move [][] back into a position of [1, 9] form
int getPos(std::pair<int, int> move) {
    int row = move.first;
    int col = move.second;

    return ((row*3) + 1) + col;

}

// Takes a pos n [1, 9] and returns a set of potential winning lines
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

// Given the current player, a set of new winning lines, a set of dead lines, and the current line map:
// updatePlayerLines deduces player and opponent, then iterates over the proposed new winning lines,
// if a new line is in the opponents winning lines already, then that line is removed from the opponents lines,
// not added to players lines, and added to the set of dead lines. Similarly, if the line is already dead then 
// the same applies. Else, the winning line is put into players winning lines. 
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

// Prints set of lines to the terminal
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

// this function does a lot right now I should probably clean it up

// given a player, a board state, a set of dead lines, and the current winning lines for each player:
// playerMove first gets a pos 1-9 from the player, converts that to a move [][], then if that move
// is a available, plays that move for player. After move is played, winning lines are created for that
// move and the line map is updated with those lines.
void playerMove(int player, int b[3][3], set<array<int,3>>& dead_lines, unordered_map<int, set<array<int, 3>>>& line_map) {
    
    // get pos from player
    int pos{};
    std::cin >> pos;
    
    // check pos in [1, 9]
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

    // Get winning lines for move and update player lines
    set<array<int, 3>> new_lines = makeLines(pos);
    updatePlayerLines(player, new_lines, dead_lines, line_map);

}
