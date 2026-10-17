#include <array>
#include <iostream>
#include <set>
#include <unordered_map>
#include "board.h"
#include "player.h"
#include "engine.h"
using namespace std;

// player1 = p1 = 1
// player2 = p2 = 2


// IDEA: Infinite tic tac toe -> the first game is the "center"
// each move spawns a new game relative to the first center game
// so a top right move in the center game spawns a game top-right
// of the center. The first player to win 3 games in a row wins.




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

    for (int i = 0; i < 9; i++) {
        if (i % 2 == 0) {
            std::cout << "Player 1's Turn!" << "\n";
            playerMove(1, board, dead_lines, line_map);
            if (checkWin(board)) {
                std::cout << "Player 1 Wins!";
                break;
            }
            printBoard(board);
            printLines(p1_lines);
        } else {
            std::cout << "Player 2's Turn!" << "\n";
            playerMove(2, board, dead_lines, line_map);
            if (checkWin(board)) {
                std::cout << "Player 2 Wins!";
                break;
            }
            printBoard(board);
            printLines(p2_lines);
        }
    }

    return 0;
}
