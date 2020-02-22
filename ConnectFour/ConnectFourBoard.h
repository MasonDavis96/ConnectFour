/*
    Header file for ConnectFourBoard class. Sets up the member variables and functions necessary for game.
*/

#include <string>
using namespace std;

class ConnectFourBoard
{
    public:
        ConnectFourBoard();
        ~ConnectFourBoard();
        const int mainMenu();
        const void printGameBoard();
        void resetGameBoard();
        const int getPlayerChoice();
        bool placeChecker(int col);

    private:
        const bool validateMenuChoice(int menuChoice);
        const bool validatePlayerChoice(int playerChoice);
        const bool validateGameOver(int row, int col);
        const bool validateHorizontal(int row, int col);
        const bool validateVertical(int row, int col);
        const bool validateRightDiagonal(int row, int col);
        const bool validateLeftDiagonal(int row, int col);
        const int rows = 6;
        const int columns = 7;
        char gameBoard[6][7];
        bool player1;
        string playerColor;
        char playerChecker;
        int menuChoice;
        int playerChoice;

};