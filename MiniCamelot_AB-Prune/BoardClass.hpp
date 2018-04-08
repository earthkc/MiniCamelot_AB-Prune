//
//  BoardClass.hpp
//  Mini Camelot
//
//

#ifndef BoardClass_hpp
#define BoardClass_hpp

#include <stdio.h>

#endif /* BoardClass_hpp */


class Board{
public:
    void printBoard(); // prints the current board state along with grid reference numbers
    Board(); // constructor
    char state[14][8]; // 14 x 8 playing field
    void makeBoard(); // initializes the 14 x 8 board
    void checkWinCon(); // checks castle win condition 
    //bool CastleCheck(int x, int y); // checks if the tile is orginally a castle tile
    bool spaceEmpty(int a, int b); // checks if the space chosen is unoccupied and/or not out of bounds
    void copyBoard(Board& oldBoard); //copies board from another state
};

bool CastleCheck(int x, int y);
