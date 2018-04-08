//
//  moveValid.cpp
//  Mini Camelot
//
//

#include "moveValid.hpp"

// checks to see if a plain move is within the movement limit
bool plainMoveValidity(int x, int y, int a, int b){
    //x: x-coord of piece to be moved
    //y: y-coord of piece to be moved
    //a: x-coord of the new piece position
    //b: y-coord of the new piece position
    
    if (a == x){
        if (b == y - 1) //north
            return true;
        else if (b == y + 1) //south
            return true;
        else
            return false;
    }
    
    else if (a == x + 1){
        if (b == y) //east
            return true;
        else if (b == y - 1) //northeast
            return true;
        else if (b == y + 1) // southeast
            return true;
        else
            return false;
    }
    
    else if (a == x - 1){
        if (b == y - 1) //northwest
            return true;
        else if (b == y + 1) // southwest
            return true;
        else if (b == y) // west
            return true;
        else
            return false;
    }
    else
        return false;
}









// checks to see if a jump (capturing/cantering) move is within the movement limit
bool jumpValidity(int x, int y, int a, int b){
    //bool capturingValidity(Board& board, int x, int y, int a, int b, Player& victor, Player& loser){
    //x: x-coord of piece to be moved
    //y: y-coord of piece to be moved
    //a: x-coord of the new piece position
    //b: y-coord of the new piece position
    
    if (a == x){
        if (b == y - 2) //north
            return true;
        else if (b == y + 2) //south
            return true;
        else
            return false;
    }
    
    else if (a == x + 2){
        if (b == y) //east
            return true;
        else if (b == y - 2) //northeast
            return true;
        else if (b == y + 2) // southeast
            return true;
        else
            return false;
    }
    
    else if (a == x - 2){
        if (b == y - 2) //northwest
            return true;
        else if (b == y + 2) // southwest
            return true;
        else if (b == y) // west
            return true;
        else
            return false;
    }
    else
        return false;
}


