//
//  winCon.cpp
//  Mini Camelot
//
//

#include "winCon.hpp"

#ifndef BoardClass_hpp
#include "BoardClass.hpp"
#endif

#ifndef PlayerClass_hpp
#include "PlayerClass.hpp"
#endif

#include <iostream> //ifndef problems?

using namespace std;

//check castle win condition; returns true on game end, false otherwise
bool castleWinCon(Board& board){
    if ((board.state[13][3] == 'W') && (board.state[13][4] == 'W')){
        cout << "PLAYER WHITE WINS\n";
        return true;
    }
    else if ((board.state[0][3] == 'B') && (board.state[0][4] == 'B')){
        cout << "PLAYER BLACK WINS\n";
        return true;
    }
    else
        return false;
}


//check pieces remaining win condition
bool zeroPieceWinCon(Player& human, Player& computer){
    if ((human.pieces >= 2) && (computer.pieces <= 1)){
        cout << "PLAYER WHITE WINS\n";
        return true;
    }
    if ((computer.pieces >=2) && (human.pieces <= 1)){
        cout << "PLAYER BLACK WINS\n";
        return true;
    }
    else
        return false;
}

//check draw condition
bool drawCon(Player& human, Player& computer){
    if ((human.pieces == 1) && (computer.pieces == 1)){
        cout << "DRAW\n";
        return true;
    }
    else return false;
}




//win/draw condition function; returns true on game end. false otherwise
bool winCondition(Board& board, Player& player, Player& computer){
    if (castleWinCon(board) == true)
        return true;
    if (zeroPieceWinCon(player, computer) == true)
        return true;
    if (drawCon(player, computer) == true)
        return true;
    return false;
}








