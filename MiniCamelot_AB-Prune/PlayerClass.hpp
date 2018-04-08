//
//  PlayerClass.hpp
//  Mini Camelot
//
//

#ifndef PlayerClass_hpp
#define PlayerClass_hpp

#include <stdio.h>

#endif /* PlayerClass_hpp */

#include <vector>
using namespace std;

class Player{
public:
    Player() : pieces(6){}; // constructor
    void setTurn(int x);
    void showTurn();
    void setColour(char x); // sets colour
    bool turn; // True: First ; False: Second
    int pieces; // how many pieces the player has left
    char colour; // what colour the player is
    vector<pair<int,int>> pieceLoc; //location of pieces stored in a vector
    void removePiece(int x, int y); //removes a piece from the vector
    void modifyPiece(int x, int y, int a, int b); //modifies a piece from the vector
    int findPiece(int x, int y); //finds the location of a piece in the vector
    //Player(const Player& p); //copy constructor. Pass in the Player to be copied from
    void copyPlayer(const Player& p); //copy constructor. Pass in the Player to be copied from
};
