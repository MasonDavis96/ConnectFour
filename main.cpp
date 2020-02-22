/*
    Mason Davis
    CS 360 Spring 2019
    Program #1

    Description: 
    This program seeks to create a rudimentary game of connect four. It
    contains the class to set up the game board, the steps, and rules
    involved in playing the game.
*/

#include <iostream>
#include "ConnectFourBoard.h"

using namespace std;

int main()
{
    // set up game board
    ConnectFourBoard game;
    int menuChoice = game.mainMenu(); // display menu, get option

    // if player wants to continue playing game
    while(menuChoice == 1)
    {
        game.printGameBoard();
        int playerChoice = game.getPlayerChoice(); 
        bool gameOver = game.placeChecker(playerChoice);
        if(gameOver)
        {
            // present menu again to continue playing or quit
            menuChoice = game.mainMenu();

            if(menuChoice == 1) // if continue playing
                game.resetGameBoard();
        }    
    }

    return 0;
}
