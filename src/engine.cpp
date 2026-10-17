#pragma once
#include <array>
#include <iostream>
#include <set>
#include <unordered_map>
#include "board.h"
#include "player.h"
#include "engine.h"
using namespace std;


set<pair<int, int>> getMoves(int b[3][3]) {

    set<pair<int, int>> possibleMoves;

    for (int i = 1; i < 10; i++) {
        pair<int, int> move = parseMove(i);
        int row = move.first;
        int col = move.second;
        if (b[row][col] == 0) {
            possibleMoves.insert(move);
        }
    }

    return possibleMoves;

}

// bot is p2
int minimax(set<pair<int, int>> possibleMoves, int b[3][3], int depth) {

    return 0;

}