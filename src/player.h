#pragma once

#include <array>
#include <set>
#include <unordered_map>
#include <utility>

using namespace std;

std::pair<int, int> parseMove(int n);

int getPos(std::pair<int, int> move);

set<array<int, 3>> makeLines(int n);

void updatePlayerLines(int player, set<array<int,3>> lines, set<array<int,3>>& dead_lines, unordered_map<int, set<array<int,3>>>& line_map);

void printLines(set<array<int, 3>> lines);

bool playerMove(int player, int b[3][3], set<array<int,3>>& dead_lines, unordered_map<int, set<array<int, 3>>>& line_map);

bool checkWin(int b[3][3]);