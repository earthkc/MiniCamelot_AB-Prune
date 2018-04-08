//
//  commitMove.cpp
//  Mini Camelot
//
//

#include "commitMove.hpp"

#ifndef BoardClass_hpp
#include "BoardClass.hpp"
#endif

#ifndef PlayerClass_hpp
#include "PlayerClass.hpp"
#endif

using namespace std;


void plainMove(Board& board, int x, int y, int a, int b, Player& player){
    // x: x-coordinate of moving piece
    // y: y-coordinate of moving piece
    // a: x-coordinate of space to move to
    // b: y-coordinate of space to move to
    if (CastleCheck(x, y) == true)
        board.state[y][x] = '+';
    else
        board.state[y][x] = '_';
    board.state[b][a] = player.colour;
    player.modifyPiece(x,y,a,b);
}

void canteringMove(Board& board, int x, int y, int a, int b, Player& player){
    if (CastleCheck(x, y) == true)
        board.state[y][x] = '+';
    else
        board.state[y][x] = '_';
    board.state[b][a] = player.colour;
    player.modifyPiece(x,y,a,b);
}

// makes the necessary board and player adjustments of a caputuring move (records)
void capturingMove(Board& board, int x, int y, int a, int b, int m, int n, Player& victor, Player& loser){
    //x: x-coord of piece to be moved
    //y: y-coord of piece to be moved
    //a: x-coord of the new piece position
    //b: y-coord of the new piece position
    //m: x-coord of the struck down
    //n: y-coord of the struck down
    
    //remove the struck down piece
    board.state[n][m] = '_';
    loser.removePiece(m,n);
    
    //move the moved piece
    if (CastleCheck(x, y) == true)
        board.state[y][x] = '+';
    else
        board.state[y][x] = '_';
    board.state[b][a] = victor.colour;
    victor.modifyPiece(x,y,a,b);
}
