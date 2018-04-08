//
//  precaptureCheck.cpp
//  Mini Camelot
//
//

//SOUTH AND SOUTHEAST DO NOT WORK CORRECTLY if a white piece is at 2,8 (no other pieces have moved)

#include "precaptureCheck.hpp"


#ifndef BoardClass_hpp
#include "BoardClass.hpp"
#endif

#ifndef PlayerClass_hpp
#include "PlayerClass.hpp"
#endif

// checks if there is an avaliable capturing move
bool capturingCheck(Board& board, Player& player){
    char opposition;
    if (player.colour == 'W')
        opposition = 'B';
    //else if (player.colour == 'B')
    else
        opposition = 'W';
    //check if there is surrounding opposition and whether they can be captured
    int checkX, checkY;
    for (int i = 0; i < player.pieceLoc.size(); i++){
        //northwest
        checkX = player.pieceLoc[i].first - 1;
        checkY = player.pieceLoc[i].second - 1;
        if (board.state[checkY][checkX] == opposition){
            checkX = checkX - 1;
            checkY = checkY - 1;
            if (board.spaceEmpty(checkX, checkY) == true)
                return true;
        }
        //north
        checkX = player.pieceLoc[i].first;
        checkY = player.pieceLoc[i].second - 1;
        if (board.state[checkY][checkX] == opposition){
            checkX = checkX;
            checkY = checkY - 1;
            if (board.spaceEmpty(checkX, checkY) == true)
                return true;
        }
        //northeast
        checkX = player.pieceLoc[i].first + 1;
        checkY = player.pieceLoc[i].second - 1;
        if (board.state[checkY][checkX] == opposition){
            checkX = checkX + 1;
            checkY = checkY - 1;
            if (board.spaceEmpty(checkX, checkY) == true)
                return true;
        }
        //east
        checkX = player.pieceLoc[i].first + 1;
        checkY = player.pieceLoc[i].second;
        if (board.state[checkY][checkX] == opposition){
            checkX = checkX + 1;
            checkY = checkY;
            if (board.spaceEmpty(checkX, checkY) == true)
                return true;
        }
        //southeast
        checkX = player.pieceLoc[i].first + 1;
        checkY = player.pieceLoc[i].second + 1;
        if (board.state[checkY][checkX] == opposition){
            checkX = checkX + 1;
            checkY = checkY + 1;
            if (board.spaceEmpty(checkX, checkY) == true)
                return true;
        }
        //south
        checkX = player.pieceLoc[i].first;
        checkY = player.pieceLoc[i].second + 1;
        if (board.state[checkY][checkX] == opposition){
            checkX = checkX;
            checkY = checkY + 1;
            if (board.spaceEmpty(checkX, checkY) == true)
                return true;
        }
        //southwest
        checkX = player.pieceLoc[i].first - 1;
        checkY = player.pieceLoc[i].second + 1;
        if (board.state[checkY][checkX] == opposition){
            checkX = checkX - 1;
            checkY = checkY + 1;
            if (board.spaceEmpty(checkX, checkY) == true)
                return true;
        }
        //west
        checkX = player.pieceLoc[i].first - 1;
        checkY = player.pieceLoc[i].second;
        if (board.state[checkY][checkX] == opposition){
            checkX = checkX - 1;
            checkY = checkY;
            if (board.spaceEmpty(checkX, checkY) == true)
                return true;
        }
    }
    return false;
}
