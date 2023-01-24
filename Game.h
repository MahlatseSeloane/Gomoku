#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include <ctime>

class Game
{
public:
    Game();
    void setConditions(int sizeOfGrid);
    int getP1Points();
    int getP2Points();

    void initializeBoard();
    void pickPositionRandomly();
    void findingThePosition(int &r,int &c,int _position);

    int getPosition();
    int getNumberOfPositionsLeft();
    bool getContinueGame();
    int getCurrentPlayer();
    int getAvailablePositionsIndex();

    void setPosition(int _PositionIndex);
    void setCurrentPlayer(int _player);
    void increaseP1Points();
    void increaseP2Points();

    void placeAtThisPosition();
    void collectAvailablePositions();
    void clearAvailablePositions();

    int checkMostValuablePosition(int positionIndex);
    void checkPossibleWin();
    int calculateValueOfPos(int _position);
    int DiagonalFromLeftToRightCheck(int position,char myPiece);
    int DiagonalFromRightToLeftCheck(int position,char myPiece);
    int HorizontalCheck(int position,char myPiece);
    int VerticalCheck(int position,char myPiece);

private:
    int P1, P2, term;
    int sizeOfGrid, numberOfPositionsLeft, currentPlayer;
    int grid[225][2], availablePositions[225];
    bool continueGame;
    int gridIndex, position, availablePositionsIndex;
};

#endif // GAME_H
