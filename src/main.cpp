#include <iostream>

// player1 = p1 = 1
// player2 = p2 = 2

// prints the 3 x 3 board to the terminal
void printBoard(int b[])
{
    for (int i = 1; i < 10; i++)
    {
        if (i % 3 == 0)
        {
            std::cout << b[i - 1] << " \n";
        }
        else
            std::cout << b[i - 1] << " ";
    }
    std::cout << "\n";
}

// win detection
bool win(int b[])
{

    // row victory
    for (int i = 0; i < 9; i += 3)
    {
        if ((b[i] == b[i + 1]) && b[i] != 0)
        {
            if (b[i] == b[i + 2])
                return true;
        }
    }

    // column victory
    for (int i = 0; i < 9; i++)
    {
        if ((b[i] == b[i + 3]) && b[i] != 0)
        {
            if (b[i] == b[i + 6])
                return true;
        }
    }

    // diagonal victory
    if ((b[0] == b[4]) && b[0] != 0)
    {
        if (b[0] == b[8])
            return true;
    }
    if ((b[2] == b[4]) && b[2] != 0)
    {
        if (b[2] == b[6])
            return true;
    }

    return false;
}

// takes a player num and board state, inputs player num's move and returns true if game was won on player num's turn.
bool playerMove(int player, int board[])
{
    std::cout << "Player " << player << "'s Turn \n";
    int p{};
    std::cin >> p;
    board[p - 1] = player;
    printBoard(board);
    return win(board);
}

// initializes the board and begins the game loop
int main()
{

    int board[9] = {};

    printBoard(board);

    for (int i = 0; i < 9; i++)
    {
        if (i % 2 == 0)
        {
            if (playerMove(1, board))
            {
                std::cout << "Player 1 Wins!! \n";
                return 0;
            }
        }
        else if (playerMove(2, board))
        {
            std::cout << "Player 2 Wins!! \n";
            return 0;
        }
    }

    std::cout << "Draw! \n";

    return 0;
}
