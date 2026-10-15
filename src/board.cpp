#include <iostream>
#include "board.h"

// prints the 3 x 3 board to the terminal
void printBoard(int b[3][3]) {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3;j++) {
            if (j == 2){
                std::cout << b[i][j] << " \n";
            } else std::cout << b[i][j] << " ";
        }
    }
}

