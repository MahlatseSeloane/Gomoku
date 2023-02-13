
<h1>Gomoku</h1>
<p>For the project, using the IDE CodeBlocks, we were required to develop a computer program in C++ that facilitated the game of Gomoku between two different algorithms. The program was to read a number of board sizes of n × n where 6 ≤ n ≤ 15 from a file named input.txt, and facilitate the game for each board size between the two algorithms and record the games in an output file</p>

<p>Gomoku, also known as Gobang and Five-in-a-row is a two-player board game played traditionally on a 15 x 15 board. Players take alternating turns to place black or white pieces in empty blocks on the grid. A player wins the game by placing 5 of their pieces in an unbroken line, horizontally, vertically or diagonally.</p>

<h2>Code Requirements</h2>
<p>The requirements for the project were as follows:

- The code should not prompt the user for input nor produce any console output.
-	No global variables may be used as this would result in immediate failure.
- Use of at least one Class.
- Use of a Function.
-	Reading in and writing to files.
</p>                       

<h2>Input format</h2>
<p>The input file would contain a list of board sizes that would be used to test the two algorithms against each other. The input file had the following format</p>

PUT PICTURE HERE

<h2>Output format</h2>
<p>The program must produce an output file named gomokuResults. The file must contain the size of the board for the current game, each position filled followed by the
algorithm in order of placement, and the winner. The history for each board size listed in the input file must be appended to this file with one empty line inbetween different games. Once all games have been played a summary should be given of the number of wins for each algorithm.
Below is an exapmle of the output file for the games of the boardsizes in the input file:</p>

PUT PICTURE HERE
<p>Note that coordinates on the board are labelled using the value of the row (r) and column (c) where the top left position is r0c0 and bottom right is r5c5 for a board of size 6.</p>
