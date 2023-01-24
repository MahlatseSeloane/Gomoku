// <StudentNumber>
#include "Game.h"
#include <iostream>
#include <fstream>

using namespace std;

void BeginGame(Game &newGame,int sizeOfGrid,ofstream &output);
void DifferentAlg(int &valueOfPos,Game &newGame);

int main()
{
    ifstream input;
    ofstream output;
    input.open("input.txt");
    output.open("gomokuResults.txt");

    Game newGame; //Creating a new game

    //Used to store the various aizes of the grid read in from the input file
    int sizeOfGrid = 0;

    //Reading in an unspecified number of grid sizes from a file.
    while(input >> sizeOfGrid)
    {
        //Checking if the current grid size meets the requirement
        if(sizeOfGrid >= 6 && sizeOfGrid <= 15)
        {
            //Setting the initial conditions before the game
            newGame.setConditions(sizeOfGrid);

            //Outputting the size of the current grid to be played on
            output << "size=" << sizeOfGrid << endl;

            //Begin game for the current grid size
            BeginGame(newGame,sizeOfGrid,output);

            //Checking if the game ended in a draw
            if(newGame.getNumberOfPositionsLeft() == 0)
            {
                output << "draw" << endl << endl;
            }
            else
            {
                //Updating the points of the algorithm that won the game by checking which algorithm played the last move
                if(newGame.getCurrentPlayer() == 1)
                    newGame.increaseP1Points();
                else if(newGame.getCurrentPlayer() == 2)
                    newGame.increaseP2Points();

                //Outputting the algorithm that won for the the current grid size
                output << "win=alg" << newGame.getCurrentPlayer() << endl << endl;
            }
        }
    }

    //Outputting the number of times each algorithm won a game
    output << "wins alg1=" << newGame.getP1Points() << endl << "wins alg2=" << newGame.getP2Points();

    input.close();
    output.close();

    return 0;
}

/*
Description:
Parameters:
Returns:
*/
void BeginGame(Game &newGame,int sizeOfGrid,ofstream &output)
{
    int r = 0, c = 0; //Used to store the row and col of the position the players play

    //Setting up the grid before the next game begins
    newGame.initializeBoard();

    //Playing
    while(newGame.getNumberOfPositionsLeft() > 0 && newGame.getContinueGame() == true)
    {
        //Collecting all the empty positions on the grid and storing them in an array to make it easier to pick a position
        newGame.collectAvailablePositions();
        r = 0, c = 0;

        //Alternating turns between algorithms
        if(newGame.getCurrentPlayer() == 1)
            newGame.setCurrentPlayer(2);
        else if(newGame.getCurrentPlayer() == 2)
            newGame.setCurrentPlayer(1);

        //Algorithm 1 alternating turns with algorithm 2 at placing their markers in the grid.
        if(newGame.getCurrentPlayer() == 1)
        {
            //Algortihm 1 chooses where to play randomly
            newGame.pickPositionRandomly();
        }
        else
        {
            //Algorithm 2
            int valueOfPos = 0;
            DifferentAlg(valueOfPos,newGame);
            if(valueOfPos == 0)
                newGame.pickPositionRandomly();
        }

        //Locationg the row and col of the position the current algorithm played at
        newGame.findingThePosition(r,c,newGame.getPosition());

        //The algorithm that just played places their marker on the grid
        newGame.placeAtThisPosition();

        //Outputting the row and col where the current algorithm just played
        output << "r" << r << "c" << c << " alg" << newGame.getCurrentPlayer() << endl;

        //Checking if the move the current algorithm just made is a winning move
        newGame.checkPossibleWin();
    }
}

/*
Description:

*/
void DifferentAlg(int &valueOfPos,Game &newGame)
{
    int temp = 0, indexOfPosition = 0;

    for(int i = 0; i < newGame.getAvailablePositionsIndex(); i++)
    {
        //Checking the position with the most
        temp = newGame.checkMostValuablePosition(i);

        if(temp > valueOfPos)
        {
            valueOfPos = temp;
            indexOfPosition = i;
        }
    }

    newGame.setPosition(indexOfPosition);
}
