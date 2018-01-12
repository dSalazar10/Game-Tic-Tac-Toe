//
//  tic-tac-toe.cpp
//
//  Created by DANIEL SALAZAR on 1/10/18.
//  Copyright © 2018 DANIEL SALAZAR. All rights reserved.
//
//  Play a simple game of tic-tac-toe
//  This was given as an assignment for my friend
//  Could be extended with minimax AI computer player

#include <iostream>
#include <sstream>

// input: a 3X3 character array
// process: prints the board to ostream
// output: none
void Display(char board[3][3])
{
    // Print Tick-Tac-Toe board
    for(int row = 0; row < 3; ++row)
    {
        for(int col = 0; col < 3; ++col)
        {
            // Print a character
            std::cout << "  " << board[row][col] << " ";
            // Print character separator
            if(col < 2) std::cout << " | ";
        }
        // Print a row seperator
        if(row < 2) std::cout << "\n-------------------" << std::endl;
    }
    // Make space for following text
    std::cout << std::endl << std::endl;
}
// input: a 3X3 character array
// process: Get and validate a move from the user
// output: a valid move from 1 - 9 that is available on the board
// return Error of -1 if while loop fails
int GetMove(char board[3][3])
{
    // variables
    std::string input = "";
    int choice;
    
    while(true) {
        // Print Menu
        std::cout << "Please Enter a position [1-9]" << std::endl;
        std::cout << "> ";
        
        // Get input
        getline(std::cin, input);
        std::stringstream myStream(input);
        
        // Stream into an int variable and test if 1 - 9
        if ((myStream >> choice) && (choice > 0 && choice < 10))
        {
            // if the chosen position is available, return choice
            switch(choice)
            {
                case 1: if(board[0][0] == '*') return choice;
                    break;
                case 2: if(board[0][1] == '*') return choice;
                    break;
                case 3: if(board[0][2] == '*') return choice;
                    break;
                case 4: if(board[1][0] == '*') return choice;
                    break;
                case 5: if(board[1][1] == '*') return choice;
                    break;
                case 6: if(board[1][2] == '*') return choice;
                    break;
                case 7: if(board[2][0] == '*') return choice;
                    break;
                case 8: if(board[2][1] == '*') return choice;
                    break;
                case 9: if(board[2][2] == '*') return choice;
                    break;
                default: // This should never occurr
                    std::cout << "Huh?";
            }
        }
        // else Failed to validate choice; start over
        Display(board);
        std::cout << "Invalid choice, please try again" << std::endl;
    }
    // This should never occurr
    return -1;
}
// input: the player count, a 3X3 character array, and a legal move
// process: pick piece and set it on the board
// output: none
void MakeMove(int player, char board[3][3], int position)
{
    // if player is even use X, else use O
    char piece = (player % 2 == 0) ? ('X') : ('O');
    // set the character in the board
    switch(position)
    {
        case 1: board[0][0] = piece;
            break;
        case 2: board[0][1] = piece;
            break;
        case 3: board[0][2] = piece;
            break;
        case 4: board[1][0] = piece;
            break;
        case 5: board[1][1] = piece;
            break;
        case 6: board[1][2] = piece;
            break;
        case 7: board[2][0] = piece;
            break;
        case 8: board[2][1] = piece;
            break;
        case 9: board[2][2] = piece;
            break;
        default: // This should never occurr
            std::cout << "Huh?";
    }
}
// input: a 3X3 character array, three rows, three cols, the player's peice
// process: cheks if all three pieces are the same
// output: true if same, false if different
bool checkLine(char board[3][3],int i[3], int j[3], char piece)
{
    if(board[i[0]][j[0]] == piece &&
       board[i[1]][j[1]] == piece &&
       board[i[2]][j[2]] == piece) return true;
    else return false;
}
// input: a 3X3 character array, the player's peice
// process: cheks all possible win conditions
// output: true if a win is found, false if none found
bool checkWin(char board[3][3], char piece)
{
    int topHorizontal[2][3] = {{0, 0, 0}, {0, 1, 2}},
    midHorizontal[2][3] = {{1, 1, 1}, {0, 1, 2}},
    bottomHorizontal[2][3] = {{2, 2, 2}, {0, 1, 2}},
    leftVertical[2][3] = {{1, 2, 3}, {0, 0, 0}},
    midVerticle[2][3] = {{1, 2, 3}, {1, 1, 1}},
    rightVerticle[2][3] = {{1, 2, 3}, {2, 2, 2}},
    leftDiagonal[2][3] = {{0, 1, 2}, {0, 1, 2}},
    rightDiagonal[2][3] = {{0, 1, 2}, {2, 1, 0}};
    
    // If there is a win, return true
    if(checkLine(board, topHorizontal[0], topHorizontal[1], piece) ||
       checkLine(board, midHorizontal[0], midHorizontal[1], piece) ||
       checkLine(board, bottomHorizontal[0], bottomHorizontal[1], piece) ||
       checkLine(board, leftVertical[0], leftVertical[1], piece) ||
       checkLine(board, midVerticle[0], midVerticle[1], piece) ||
       checkLine(board, rightVerticle[0], rightVerticle[1], piece) ||
       checkLine(board, leftDiagonal[0], leftDiagonal[1], piece) ||
       checkLine(board, rightDiagonal[0], rightDiagonal[1], piece)) return true;
    // No win return false
    else return false;
}
// input: the player count, a 3X3 character array
// process: Check for win/loss/tie from move 5 to move 9
// output: if (win/loss/stalemate) return false, else return true
bool Validate(int player, char board[3][3])
{
    // Possible win/loss
    if(player > 4)
    {
        // if player is even use X, else use O
        char piece = (player % 2 == 0) ? ('O') : ('X');
        // Check if board has a win
        if(checkWin(board, piece) == true)
        {
            std::cout << piece << " wins!";
            return false;
        }
    }
    // Max moves exhausted
    else if(player > 8)
    {
        std::cout << "Stalemate!" << std::endl;
        return false;
    }
    return true;
}
int main() {
    // The tick-toe-board
    char board[3][3] = {{'*', '*', '*'},{'*', '*', '*'},{'*', '*', '*'}};
    // Priming reed
    Display(board);
    /*
     Player 1 is even, Player 2 is odd
     Max number of moves is 9
     Check for win/loss/tie from move 5 to move 9
    */
    for(int player = 0; Validate(player, board); ++player)
    {
        // Get a move from the player and perform the move on the board
        MakeMove(player, board, GetMove(board));
        // Continuing Reed
        Display(board);
    }
    return 0;
}
