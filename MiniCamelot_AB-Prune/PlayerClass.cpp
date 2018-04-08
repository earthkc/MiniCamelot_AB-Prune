//
//  PlayerClass.cpp
//  Mini Camelot
//
//

#include "PlayerClass.hpp"
#include <iostream>

//copy constructor. Pass in the Player to be copied from
//Player::Player(const Player& p){
void Player::copyPlayer(const Player& p){
    pieces = p.pieces;
    colour = p.colour;
    //for (int i = 0; i < p.pieceLoc.size(); i++){ //EXC_BAD_ACCESS code 1
    for (int i = 0; i < p.pieces; i++){
        pieceLoc.push_back(p.pieceLoc[i]);
    }
}


int Player::findPiece(int x, int y){
    pair<int, int> iter = make_pair(x,y);
    for (int i = 0; i < pieceLoc.size(); i++){ //could be optimized to use the pieces variable instead
        if (pieceLoc[i] == iter){
            return i;
        }
    }
    return -1; //raise error?
}


void Player::removePiece(int x, int y){
    pieces = pieces - 1;
    int i = findPiece(x, y);
    pieceLoc.erase(pieceLoc.begin() + i);
}

void Player::modifyPiece(int x, int y, int a, int b){
    int i = findPiece(x, y);
    //pieceLoc[i] = make_pair(a, b);
    pieceLoc.erase(pieceLoc.begin() + i);
    pair<int, int> newPiece;
    newPiece = make_pair(a, b);
    pieceLoc.push_back(newPiece);
    
}

void Player::showTurn(){
    if (turn == true)
        cout << "Player " << colour << " is going first.\n";
    if (turn == false)
        cout << "Player " << colour << " is going second.\n";
}

void Player::setTurn(int x){
    while (true){
        if (x == 1){
            turn = true;
            break;
        }
        if (x == 2){
            turn = false;
            break;
        }
        else{
            cout << "Invalid turn input. Please reenter. First '1' or Second '2': ";
            cin >> x;
        }
    }
}

void Player::setColour(char x){
    colour = x;
}
