#include "Game.h"

Game::Game()
{
    P1 = 0, P2 = 0;
}

//Description: A get function. Gets the number of times algorithm 1 won a game
int Game::getP1Points()
{
    return P1;
}

//Description: A get function. Gets the number of times algorithm 2 won a game
int Game::getP2Points()
{
    return P2;
}

//Description: A get function. Gets the number of positions left on the board
int Game::getNumberOfPositionsLeft()
{
    return numberOfPositionsLeft;
}

//Description: A get function. Gets the position that the current algorithm just played on the board
int Game::getPosition()
{
    return position;
}

//Description: A get function. Gets the number of available positions on the board
int Game::getAvailablePositionsIndex()
{
    return availablePositionsIndex;
}

//Description: A get function. Gets the state of the  game (Wheyher it is over or not)
bool Game::getContinueGame()
{
    return continueGame;
}

//Description: A get function. Gets the algorithm whose turn it is
int Game::getCurrentPlayer()
{
    return currentPlayer;
}

//Description: Sets the algorithm whose turn it is supposed to be
void Game::setCurrentPlayer(int _player)
{
    currentPlayer = _player;
}

//Description: Increases algorithm 1's points after winning a game
void Game::increaseP1Points()
{
    P1++;
}

//Description: Increases algorithm 2's points after winning a game
void Game::increaseP2Points()
{
    P2++;
}

//Description: A set function. Sets the position after picking an available position on the grid
void Game::setPosition(int _PositionIndex)
{
    position = availablePositions[_PositionIndex];
}

//Description: A helper function. Clears out the grid and the availablePositions array before the start of the game
void Game::initializeBoard()
{
    numberOfPositionsLeft = 1;

    for(int rows = 0; rows < sizeOfGrid; rows++)
    {
        for(int cols = 0; cols < sizeOfGrid; cols++)
        {
            grid[numberOfPositionsLeft - 1][0] = 0;
            grid[numberOfPositionsLeft - 1][1] = 0;

            availablePositions[numberOfPositionsLeft-1] = 0;
            numberOfPositionsLeft++;
        }
    }
}

//Description: A helper function. Sets the conditions before the game begins
void Game::setConditions(int _sizeOfGrid)
{
    sizeOfGrid = _sizeOfGrid;
    term = sizeOfGrid - 5; //Used to store .i.e., if the sizeOfGrid = 6, then term = 1 and if sizeOfGrid = 7, tne term = 2 etc.
    continueGame = true;

    srand(time(0));
    currentPlayer = (rand() % 2) + 1;

    gridIndex = 0, availablePositionsIndex = 0;
}

//Description: A helper function. Places the algorithm that just played marker on the grid
void Game::placeAtThisPosition()
{
    grid[gridIndex][0] = position;

    if(currentPlayer == 1)
        grid[gridIndex][1] = 'X';
    else if(currentPlayer == 2)
        grid[gridIndex][1] = 'O';

    gridIndex++;
    numberOfPositionsLeft--;
}

//Description: A helper function. Clears out the availablePositions array after an algorithm just played
void Game::clearAvailablePositions()
{
    for(int i = 0; i < availablePositionsIndex; i++)
    {
        availablePositions[i] = 0;
    }

    availablePositionsIndex = 0;
}

//Description: A helper function. Collects all the available positions on the grid and stores them in the availablePositions array beofre an algorithm makes a move
void Game::collectAvailablePositions()
{
    clearAvailablePositions();
    int num = 1;
    for(int i = 0; i < sizeOfGrid * sizeOfGrid; i++)
    {
        bool found = false;

        //Used to go through the entire grid to check if a position has already been played on the grid
        for(int j = 0; j < gridIndex; j++)
        {
            //Checks if a position is already on the grid. If it isn't, then the position can be stored in the availablePositios array below
            if(num == grid[j][0])
            {
                found = true;
                break;
            }
        }

        if(found == false)
        {
            availablePositions[availablePositionsIndex] = num;
            availablePositionsIndex++;
        }
        num++;
    }
}


//Description: A helper function. Generates a position randomly for the an algorithm to play
void Game::pickPositionRandomly()
{
    srand(time(0));
    int random = rand()%(availablePositionsIndex);

    setPosition(random);
}

/*
Description: A helper function. Because the grid we are playing on is not a conventional one of equal dimensions, but only stores positions, this function converts
positions into a row and column, that is more understandable
*/
void Game::findingThePosition(int &r,int &c,int _position)
{
    int num = 1;
    for(int rows = 0; rows < sizeOfGrid; rows++)
    {
        for(int cols = 0; cols < sizeOfGrid; cols++)
        {
            if(_position == num)
            {
                r = rows, c = cols;
                return;
            }

            num++;
        }
    }
}

//Description: A helper function. Evaluates if a position is the best position for the algortihm to play, using the calculateValuePos(~) function
int Game::checkMostValuablePosition(int positionIndex)
{
    int value = calculateValueOfPos(availablePositions[positionIndex]);
    return value;
}

//Description: A helper function. Checks if the current algorithm's move is a winning move, using the calculateValuePos(~) function
void Game::checkPossibleWin()
{
    int value = calculateValueOfPos(position);

    /*This if-statement checks if at the position in question, the are 4 or more of the algorithm's pieces in a unbroken line in any direction.
        - If there is, then the game is over for that given board size
    */
    if(value >= 4)
        continueGame = false;
}

/*
Description: A helper function. Counts the number of an algorithm's pieces in an unbroken line horizontally, vertically, diagonally left to right and diagonally
right to left respectively, from a position and returns the highest value counted at a position
*/
int Game::calculateValueOfPos(int _position)
{
    int valueOfPos[4] = {0}, temp = 0, largestIndex = 0;;
    char myPiece;

    //Setting which piece to check for depending on whose turn it is
    if(currentPlayer == 1)
        myPiece = 'X';
    else if(currentPlayer == 2)
        myPiece = 'O';

    valueOfPos[0] = VerticalCheck(_position,myPiece); //Checking vertically for an unbroken line
    valueOfPos[1] = HorizontalCheck(_position,myPiece); //Checking horizontally for an unbroken line
    valueOfPos[2] = DiagonalFromLeftToRightCheck(_position,myPiece); //Checking diagonally from left to right for an unbroken line
    valueOfPos[3] = DiagonalFromRightToLeftCheck(_position,myPiece); //Checking diagonally from right to left for an unbroken line

    //Bubble sorting the array and putting the largest value at the top of the array
    for (int i = 0; i < 4; i++)
    {
        largestIndex = i;
        for (int j = i + 1; j < 4; j++)
        {
            if(valueOfPos[j] > valueOfPos[largestIndex])
                largestIndex = j;
        }

        temp = valueOfPos[largestIndex];
        valueOfPos[largestIndex] = valueOfPos[i];
        valueOfPos[i] = temp;
    }

    return valueOfPos[0];
}

//Description: A helper function. Counts the number of an algorithm's pieces in an unbroken line vertically from a position and returns the value counted
int Game::VerticalCheck(int _position,char myPiece)
{
    int r = 0, c = 0, counter = 0, tempPos = _position, restriction = 0;

    //Restriction the function to remain with the bounds of the grid when checking for an unbroken line
    findingThePosition(r,c,_position); //Getting the column to keep the function restricted on
    restriction = c + 1; //Restricting at the top of the grid

ContinueCheckingVertUp:
    //Checking if the cuurent position isn't greater than the restriction
    if(_position > restriction)
    {
        //Subtracting the current position by the grid size to move directly up in the same column
        _position = _position - sizeOfGrid;

        for(int i = 0; i < gridIndex; i++)
        {
            //Checking if the position is on the grid and if so, does the piece at that position match that of the current algorithm
            if(grid[i][0] == _position && char(grid[i][1]) == myPiece)
            {
                //If both conditions are met, increase the counter and repeat the loop
                counter++;
                goto ContinueCheckingVertUp;
            }
        }
    }

    _position = tempPos;
    restriction = sizeOfGrid * (sizeOfGrid - 1) + (c + 1); //Restricting at the bottom of the grid

ContinueCheckingVertDown:
    //Checking if the cuurent position isn't lesser than the restriction
    if(_position < restriction)
    {
        //Adding the current position by the grid size to move directly down in the same column
        _position = _position + sizeOfGrid;

        for(int i = 0; i < gridIndex; i++)
        {
            //Checking if the position is on the grid and if so, does the piece at that position match that of the current algorithm
            if(grid[i][0] == _position && char(grid[i][1]) == myPiece)
            {
                //If both conditions are met, increase the counter and repeat the loop
                counter++;
                goto ContinueCheckingVertDown;
            }
        }
    }

    return counter;
}

//Description: A helper function. Counts the number of an algorithm's pieces in an unbroken line horizontally from a position and returns the value counted
int Game::HorizontalCheck(int _position,char myPiece)
{
    int r = 0, c = 0, counter = 0, tempPos = _position, restriction = 0;

    findingThePosition(r,c,_position); //Getting the row to keep the function restricted on
    restriction = (sizeOfGrid * r) + 1; //Restricting at the left of the grid

ContinueCheckingHoriLeft:
    //Checking if the cuurent position isn't greater than the restriction
    if(_position > restriction)
    {
        //Subtracting the current position by the 1 size to move directly to the left in the same row
        _position = _position - 1;

        for(int i = 0; i < gridIndex; i++)
        {
            //Checking if the position is on the grid and if so, does the piece at that position match that of the current algorithm
            if(grid[i][0] == _position && char(grid[i][1]) == myPiece)
            {
                //If both conditions are met, increase the counter and repeat the loop
                counter++;
                goto ContinueCheckingHoriLeft;
            }
        }
    }

    _position = tempPos;
    restriction = sizeOfGrid * (r + 1); //Restricting at the right of the grid

ContinueCheckingHoriRight:
    //Checking if the cuurent position isn't lesser than the restriction
    if(_position < restriction)
    {
        //Adding the current position by the 1 size to move directly to the right in the same row
        _position = _position + 1;

        for(int i = 0; i < gridIndex; i++)
        {
            //Checking if the position is on the grid and if so, does the piece at that position match that of the current algorithm
            if(grid[i][0] == _position && char(grid[i][1]) == myPiece)
            {
                //If both conditions are met, increase the counter and repeat the loop
                counter++;
                goto ContinueCheckingHoriRight;
            }
        }
    }

    return counter;
}

//Description: A helper function. Counts the number of an algorithm's pieces in an unbroken line diagonally from right to left from a position and returns the value counted
int Game::DiagonalFromRightToLeftCheck(int _position,char myPiece)
{
    int r = 0, c = 0, counter = 0, tempPos = _position, restriction = 0;

    findingThePosition(r,c,_position); //Getting the row and column to keep the function restricted on
    //Restricting at the top right of the grid
    if(r >= (sizeOfGrid - 1) - c)
        restriction = _position - (((sizeOfGrid - 1) - c) * (term + 4));
    else
        restriction = _position - (r * (term + 4));

ContinueCheckingDiagUpRight:
    //Checking if the cuurent position isn't greater than the restriction
    if(_position > restriction)
    {
        //Subtracting the current position by the a certain number to move directly to the up right
        _position = _position - (term + 4);
        for(int i = 0; i < gridIndex; i++)
        {
            //Checking if the position is on the grid and if so, does the piece at that position match that of the current algorithm
            if(grid[i][0] == _position && char(grid[i][1]) == myPiece)
            {
                //If both conditions are met, increase the counter and repeat the loop
                counter++;
                goto ContinueCheckingDiagUpRight;
            }
        }
    }

    _position = tempPos;
    //Restricting at the bottom left of the grid
    if(r >= (sizeOfGrid - 1) - c)
        restriction = _position + (((sizeOfGrid - 1) - r) * (term + 4));
    else
        restriction = _position + (c * (term + 4));

ContinueCheckingDiagDownLeft:
    //Checking if the cuurent position isn't lesser than the restriction
    if(_position < restriction)
    {
        //Adding the current position by the a certain number to move directly to the down left
        _position = _position + (term + 4);

        for(int i = 0; i < gridIndex; i++)
        {
            //Checking if the position is on the grid and if so, does the piece at that position match that of the current algorithm
            if(grid[i][0] == _position && char(grid[i][1]) == myPiece)
            {
                //If both conditions are met, increase the counter and repeat the loop
                counter++;
                goto ContinueCheckingDiagDownLeft;
            }
        }
    }

    return counter;
}

//Description: A helper function. Counts the number of an algorithm's pieces in an unbroken line diagonally from left to right from a position and returns the value counted
int Game::DiagonalFromLeftToRightCheck(int _position,char myPiece)
{
    int r = 0, c = 0, counter = 0, tempPos = _position, restriction = 0;

    findingThePosition(r,c,_position);
    //Restricting at the top left of the grid
    if(r >= c)
        restriction = _position - (c * (term + 6));
    else
        restriction = _position - (r * (term + 6));


ContinueCheckingDiagUpLeft:
    //Checking if the cuurent position isn't greater than the restriction
    if(_position > restriction)
    {
        //Subtracting the current position by the a certain number to move directly to the up left
        _position = _position - (term + 6);

        for(int i = 0; i < gridIndex; i++)
        {
            //Checking if the position is on the grid and if so, does the piece at that position match that of the current algorithm
            if(grid[i][0] == _position && char(grid[i][1]) == myPiece)
            {
                //If both conditions are met, increase the counter and repeat the loop
                counter++;
                goto ContinueCheckingDiagUpLeft;
            }
        }
    }

    _position = tempPos;

    //Restricting at the bottom right of the grid
    if(r >= c)
        restriction = _position + (((sizeOfGrid - 1) - r) * (term + 6));
    else
        restriction = _position + (((sizeOfGrid - 1) - c) * (term + 6));

ContinueCheckingDiagDownRight:
    //Checking if the cuurent position isn't lesser than the restriction
    if(_position < restriction)
    {
        //Subtracting the current position by the a certain number to move directly to the down right
        _position = _position + (term + 6);

        for(int i = 0; i < gridIndex; i++)
        {
            //Checking if the position is on the grid and if so, does the piece at that position match that of the current algorithm
            if(grid[i][0] == _position && char(grid[i][1]) == myPiece)
            {
                //If both conditions are met, increase the counter and repeat the loop
                counter++;
                goto ContinueCheckingDiagDownRight;
            }
        }
    }

    return counter;
}
