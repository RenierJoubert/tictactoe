#include <iostream>
#include "board.h"

// // prints the 3 x 3 board to the terminal
// void printBoard(int b[])
// {
//     for (int i = 1; i < 10; i++)
//     {
//         if (i % 3 == 0)
//         {
//             std::cout << b[i - 1] << " \n";
//         }
//         else
//             std::cout << b[i - 1] << " ";
//     }
//     std::cout << "\n";
// }

void printBoard(int b[3][3]) {

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3;j++) {
            if (j == 2){
                std::cout << b[i][j] << " \n";
            } else std::cout << b[i][j] << " ";
        }
    }
}

// win detection
// bool win(int b[])
// {

//     // row victory
//     for (int i = 0; i < 6; i += 3)
//     {
//         if ((b[i] == b[i + 1]) && b[i] != 0)
//         {
//             if (b[i] == b[i + 2])
//                 return true;
//         }
//     }

//     // column victory
//     for (int i = 0; i < 3; i++)
//     {
//         if ((b[i] == b[i + 3]) && b[i] != 0)
//         {
//             if (b[i] == b[i + 6])
//                 return true;
//         }
//     }

//     // diagonal victory
//     if ((b[0] == b[4]) && b[0] != 0)
//     {
//         if (b[0] == b[8])
//             return true;
//     }
//     if ((b[2] == b[4]) && b[2] != 0)
//     {
//         if (b[2] == b[6])
//             return true;
//     }

//     return false;
// }

