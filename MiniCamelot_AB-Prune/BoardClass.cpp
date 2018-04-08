//
//  BoardClass.cpp
//  Mini Camelot
//
//

#include "BoardClass.hpp"
#include <iostream>
using namespace std;


void Board::copyBoard(Board& oldBoard){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 14; j++){
            state[j][i] = oldBoard.state[j][i];
        }
    }
}

//unutilized?
void Board::checkWinCon(){
    if ((state[13][3] == 'W') && (state[13][4] == 'W')){
        cout << "PLAYER WHITE WINS\n";
    }
    if ((state[0][3] == 'B') && (state[0][4] == 'B')){
        cout << "PLAYER BLACK WINS\n";
    }
}

//may have to modify constructor for efficiency purposes
Board::Board(){
    makeBoard();
}

void Board::makeBoard(){
    // initalize the board into a blank state
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 14; j++){
            state[j][i] = '_';
        }
    }
    // blacks out the out of bounds tiles
    state[0][0] = ' ';
    state[0][1] = ' ';
    state[0][2] = ' ';
    state[0][5] = ' ';
    state[0][6] = ' ';
    state[0][7] = ' ';
    state[1][0] = ' ';
    state[1][1] = ' ';
    state[1][6] = ' ';
    state[1][7] = ' ';
    state[2][0] = ' ';
    state[2][7] = ' ';
    state[11][0] = ' ';
    state[11][7] = ' ';
    state[12][0] = ' ';
    state[12][1] = ' ';
    state[12][6] = ' ';
    state[12][7] = ' ';
    state[13][0] = ' ';
    state[13][1] = ' ';
    state[13][2] = ' ';
    state[13][5] = ' ';
    state[13][6] = ' ';
    state[13][7] = ' ';
    // add the starting positions of the black and white pieces
    state[4][2] = 'W';
    state[4][3] = 'W';
    state[4][4] = 'W';
    state[4][5] = 'W';
    state[5][3] = 'W';
    state[5][4] = 'W';
    state[8][3] = 'B';
    state[8][4] = 'B';
    state[9][2] = 'B';
    state[9][3] = 'B';
    state[9][4] = 'B';
    state[9][5] = 'B';
    // label the castles
    state[0][3] = '+';
    state[0][4] = '+';
    state[13][3] = '+';
    state[13][4] = '+';
}

void Board::printBoard(){
    // prints horizontal reference grid
    for (int k = 0; k < 8; k++)
        cout << k << " ";
    cout << endl;
    // prints the state of the board itself
    for (int j = 0; j < 14; j++){
        for (int i = 0; i < 8; i++){
            cout << state[j][i] << " ";
            if (i == 7){ // prints vertical reference grid
                cout << j;
                cout << endl;
                //cout << endl;
                //cout << "__________________________________\n";
            }
        }
    }
}


bool Board::spaceEmpty(int a, int b){
    if ((a > 7) || (a < 0))
        return false;
    if ((b > 13) || (b < 0))
        return false;
    if (state[b][a] == '_'){
        return true;
    }
    if (state[b][a] == '+'){
        return true;
    }
    else
        return false;
}

// checks if a tile was originally a castle tile
bool CastleCheck(int x, int y){
    if (y == 0){
        if (x == 3)
            return true;
        else if (x == 4)
            return true;
        else
            return false;
    }
    else if (y == 13){
        if (x == 3)
            return true;
        else if (x == 4)
            return true;
        else
            return false;
    }
    else
        return false;
}


