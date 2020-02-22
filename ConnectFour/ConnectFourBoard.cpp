/*
    The ConnectFourBoard class sets up the game board, presents the user with a choice of where to place their checker, and places the
    checker. It validates whether a game has been won after every checker placed.
*/

#include <iostream>
#include <string>
#include "ConnectFourBoard.h"

using namespace std;

// Constructor. Initializes the game board
ConnectFourBoard::ConnectFourBoard()
{
    cout << "\n" << "~*~*~* Welcome To Connect Four! *~*~*~" << "\n";

    this->player1 = true;

    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->columns; j++)
        {
            this->gameBoard[i][j] = '_';
        }
    }
}

// Destructor
ConnectFourBoard::~ConnectFourBoard()
{
    cout << "\n" << "Thanks for playing!" << endl;
}

// resets the game board to its default status after the user wins a game
// and wishes to play a new game
void ConnectFourBoard::resetGameBoard()
{
    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->columns; j++)
        {
            this->gameBoard[i][j] = '_';
        }
    }
}

// the mainMenu() method presents the menu to the player and records their input
// on starting a new game or quitting. It returns an integer corresponding to
// their input
const int ConnectFourBoard::mainMenu()
{
    do
    {
        cout << "\n" << "0: Quit" << endl;
        cout << "1: New Game" << endl;
        cout << "Enter Choice: ";
        cin >> this->menuChoice;
    } while(!(validateMenuChoice(this->menuChoice)));

    if(this->menuChoice == 0)
        return 0;
    else
        return 1;
}

// validateMenuChoice() simply validates the players' menu choice, and makes
// sure they input the correct input. It returns true or false depending on if 
// they have or haven't entered the correct input
const bool ConnectFourBoard::validateMenuChoice(int menuChoice)
{
    if(cin.fail() || (menuChoice < 0 || menuChoice > 1))
    {
        cout << "\n" << "I'm sorry, but that's not a valid choice. Please try again." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
    else
    {
        return true;
    }
}

// printGameBoard() simply displays the current game board to the player
const void ConnectFourBoard::printGameBoard()
{
    cout << "\n" << "Current Board Status:" << "\n\n";

    cout << "0 1 2 3 4 5 6" << endl;

    for(int i = 0; i < this->rows; i++)
    {
        for(int j = 0; j < this->columns; j++)
        {
            cout << this->gameBoard[i][j] << " ";
        }

        cout << "\n";
    }
}

// getPlayerChoice() collects the players' option on where they want to place
// their checker on the game board. It returns the integer corresponding to the
// column they wish to place the checker.
const int ConnectFourBoard::getPlayerChoice()
{
    if(this->player1 == false)
    {
        this->playerColor = "Black";
        this->playerChecker = 'B';
    }
    else
    {
        this->playerColor = "Red";
        this->playerChecker = 'R';
    }
    
    do
    {
        cout << "\n" << "It is " << this->playerColor << "'s turn!" << endl;
        cout << "Enter column (0-6): ";
        cin >> this->playerChoice;
    } while (!(validatePlayerChoice(this->playerChoice)));

    return this->playerChoice;
}

// validatePlayerChoice() simply validates whether the input is correct. Returns
// true or false whether it is or not.
const bool ConnectFourBoard::validatePlayerChoice(int playerChoice)
{
    if(cin.fail() || (playerChoice < 0 || playerChoice > 6))
    {
        cout << "\n" << "I'm sorry, but that's not a valid choice. Please try again." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
    else if(this->gameBoard[0][playerChoice] != '_')
    {
        cout << "\n" << "I'm sorry, but that's not a valid choice. Please try again." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return false; 
    }
    else
    {
        return true;
    }
}

// placeChecker() changes the spot on the board the player chose into the
// checker (letter) that corresponds with their color (red 'R' or black 'B').
// Returns true or false depending on if the checker could be succesfully
// placed or not.
bool ConnectFourBoard::placeChecker(int col)
{
    bool check = true;
    int row = 5;

    while(check)
    {
        // if location is already filled with another checker, move up one spot
        if(gameBoard[row][col] != '_')
            row--;
        else
        {
            gameBoard[row][col] = this->playerChecker;
            check = false;
        }
    }
    bool gameOver = validateGameOver(row, col);

    if(gameOver == true)
    {
        printGameBoard();
        cout << "\n\n" << "~*~*~* " << this->playerColor << " Wins! *~*~*~" << "\n\n";
        return true;
    }
    else // change players turn
    {
        if(this->player1 == true)
            this->player1 = false;
        else
            this->player1 = true; 

        return false;       
    }     
}

// validateGameOver() determines if a game has been won with four in a row.
// Returns true if a player has won, false otherwise
const bool ConnectFourBoard::validateGameOver(int row, int col)
{
    // if four in a row has been detected, game over
    if(validateHorizontal(row, col) || validateVertical(row, col) ||
        validateRightDiagonal(row, col) || validateLeftDiagonal(row, col))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// validateHorizontal(), and the following methods, simply validate whether
// there is a combination of four in a row, either horizontally, vertically, or
// diagonally. They return bools based on whether they detect four in a row or not.
const bool ConnectFourBoard::validateHorizontal(int row, int col)
{
    int horizontalTotal = 1;

    int horizontal_right = col + 1;
    // if the checker to the right of the current one is of the same color 
    // increment the total
    while(gameBoard[row][horizontal_right] == this->playerChecker)
    {
        horizontalTotal++;
        if(horizontalTotal == 4)
            return true;
        horizontal_right++;
    }

    int horizontal_left = col - 1;
    // to the left of the current one
    while(gameBoard[row][horizontal_left] == this->playerChecker)
    {
        horizontalTotal++;
        if(horizontalTotal == 4)
            return true;
        horizontal_left--;
    }

    return false;
}

const bool ConnectFourBoard::validateVertical(int row, int col)
{
    int verticalTotal = 1;

    int vertical_down = row + 1;
    while(gameBoard[vertical_down][col] == this->playerChecker)
    {
        verticalTotal++;
        if(verticalTotal == 4)
            return true;
        vertical_down++;
    }
    
    return false;
}

const bool ConnectFourBoard::validateRightDiagonal(int row, int col)
{
    int rightDiagonalTotal = 1;

    int up = row - 1;
    int right = col + 1;
    while(gameBoard[up][right] == this->playerChecker)
    {
        rightDiagonalTotal++;
        if(rightDiagonalTotal == 4)
            return true;
        up--;
        right++;
    }

    int down = row + 1;
    int left = col - 1;
    while(gameBoard[down][left] == this->playerChecker)
    {
        rightDiagonalTotal++;
        if(rightDiagonalTotal == 4)
            return true;
        down++;
        left--;
    }
    
    return false;
}

const bool ConnectFourBoard::validateLeftDiagonal(int row, int col)
{
    int leftDiagonalTotal = 1;

    int up = row - 1;
    int left = col - 1;
    while(gameBoard[up][left] == this->playerChecker)
    {
        leftDiagonalTotal++;
        if(leftDiagonalTotal == 4)
            return true;
        up--;
        left--;
    }

    int down = row + 1;
    int right = col + 1;
    while(gameBoard[down][right] == this->playerChecker)
    {
        leftDiagonalTotal++;
        if(leftDiagonalTotal == 4)
            return true;
        down++;
        right++;
    }
    
    return false;
}