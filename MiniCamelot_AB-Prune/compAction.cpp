//
//  compAction.cpp
//  Mini Camelot
//
//
//move ordering could use a better heuristic

#include "compAction.hpp"

#include <chrono>
#include <ctime>
#include <iostream>

#ifndef BoardClass_hpp
#include "BoardClass.hpp"
#endif

#ifndef PlayerClass_hpp
#include "PlayerClass.hpp"
#endif

#ifndef precaptureCheck_hpp
#include "precaptureCheck.hpp"
#endif

#ifndef commitMove_hpp
#include "commitMove.hpp"
#endif


bool failSafe(int x, int y, int a, int b, int m, int n){
    //FAILSAFE
    if ((a > 7) || (a < 0) || (x > 7) || (x < 0) || (m > 7) || (m < 0))
        return false;
    if ((b > 13) || (b < 0) || (y > 13) || (y < 0) || (m > 13) || (n < 0))
        return false;
    if ((x == 0) || (x == 7)){
        if ((y == 0) || (y == 1) || (y == 2) || (y == 3) || (y == 11) || (y == 12) || (y == 13))
            return false;
    }
    if ((x == 1) || (x == 6)){
        if ((y == 0) || (y == 1) || (y == 2) || (y == 12) || (y == 13))
            return false;
    }
    if ((x == 2) || (x == 5)){
        if ((y == 0) || (y == 13))
            return false;
    }
    if ((a == 0) || (a == 7)){
        if ((b == 0) || (b == 1) || (b == 2) || (b == 3) || (b == 11) || (b == 12) || (b == 13))
            return false;
    }
    if ((a == 1) || (a == 6)){
        if ((b == 0) || (b == 1) || (b == 2) || (b == 12) || (b == 13))
            return false;
    }
    if ((a == 2) || (a == 5)){
        if ((b == 0) || (b == 13))
            return false;
    }
    if ((m == 0) || (m == 7)){
        if ((n == 0) || (n == 1) || (n == 2) || (n == 3) || (n == 11) || (n == 12) || (n == 13))
            return false;
    }
    if ((m == 1) || (m == 6)){
        if ((n == 0) || (n == 1) || (n == 2) || (n == 12) || (n == 13))
            return false;
    }
    if ((m == 2) || (m == 5)){
        if ((n == 0) || (n == 13))
            return false;
    }
    return true;
}

bool failSafe(int x, int y, int a, int b){
    //FAILSAFE
    if ((a > 7) || (a < 0) || (x > 7) || (x < 0))
        return false;
    if ((b > 13) || (b < 0) || (y > 13) || (y < 0))
        return false;
    if ((x == 0) || (x == 7)){
        if ((y == 0) || (y == 1) || (y == 2) || (y == 3) || (y == 11) || (y == 12) || (y == 13))
            return false;
    }
    if ((x == 1) || (x == 6)){
        if ((y == 0) || (y == 1) || (y == 2) || (y == 12) || (y == 13))
            return false;
    }
    if ((x == 2) || (x == 5)){
        if ((y == 0) || (y == 13))
            return false;
    }
    if ((a == 0) || (a == 7)){
        if ((b == 0) || (b == 1) || (b == 2) || (b == 3) || (b == 11) || (b == 12) || (b == 13))
            return false;
    }
    if ((a == 1) || (a == 6)){
        if ((b == 0) || (b == 1) || (b == 2) || (b == 12) || (b == 13))
            return false;
    }
    if ((a == 2) || (a == 5)){
        if ((b == 0) || (b == 13))
            return false;
    }
    return true;
}


ABnode::ABnode(){
    x = 0;
    y = 0;
    a = 0;
    b = 0;
}

//alpha-beta node

void ABnode::newChild(ABnode& child, int x, int y, int a, int b){
    
    //set the parent node
    child.prev = this;
    
    /*
    //copy over the pruned branches to prevent duplication
    for (int i; i < pruned.size(); i++){
        child.pruned.push_back(pruned[i]);
    }
     */
    
    //copy over Player classes. copy constructor
    child.human.copyPlayer(human);
    child.comp.copyPlayer(comp);
    
    //copy over Board state. copy constructor
    child.currstate.copyBoard(currstate);
    
    //set the MAX/MIN flag
    if (isMax == true)
        child.isMax = false;
    else
        child.isMax = true;
    
    //initalize the pruned variable to say the new node is not pruned branch
    child.prunedAndDead = false;
    
    //set node x,y,a,b identifiers
    child.x = x;
    child.y = y;
    child.a = a;
    child.b = b;
}

//performs child node book-keeping
void ABnode::childGen(int moveFlag, int x, int y, int a, int b, int m, int n, Player& now, Player& next){
    //moveFlag: set to 1(capturing move), 2(cantering move), 3(plain move)
    ABnode *child = new ABnode;
    switch(moveFlag){
        case(1): //capturing move
            //generate the new node
            newChild(*child, x, y, a, b);
            //perform commit moves on the new node
            if (now.colour == 'B'){
                capturingMove(child->currstate, x, y, a, b, m, n, child->comp, child->human);
            }
            else
                capturingMove(child->currstate, x, y, a, b, m, n, child->human, child->comp);
            //mandatory capture check the new node
            child->setCaptureMand();
            //add it to the actions
            actions.push_back(child);
            break;
        case(2): //cantering move
            newChild(*child, x, y, a, b);
            if (now.colour == 'B')
                canteringMove(child->currstate, x, y, a, b, child->comp);
            else
                canteringMove(child->currstate, x, y, a, b, child->human);
            child->setCaptureMand();
            actions.push_back(child);
            break;
        case(3): //plain move
            newChild(*child, x, y, a, b);
            if (now.colour == 'B')
                plainMove(child->currstate, x, y, a, b, child->comp);
            else
                plainMove(child->currstate, x, y, a, b, child->human);
            child->setCaptureMand();
            actions.push_back(child);
            break;
    }
}



//check if a duplicate action was already generated
//returns true if a dup is found
//returns false if no duplicate was found
//MAY NEED TO COMPLETELY REWORK THE CHECKDUP FUNCTION; double check to make sure
bool ABnode::checkDup(int x, int y, int a, int b){
    for (int i = 0; i < actions.size(); i++){
        if ((actions[i]->x == x) && (actions[i]->y == y) && (actions[i]->a == a) && (actions[i]->b == b)){
            return true;
        }
    }
    for (int i = 0; i < pruned.size(); i++){
        if ((pruned[i]->x == x) && (pruned[i]->y == y) && (pruned[i]->a == a) && (pruned[i]->b == b)){
            return true;
        }
    }
    return false;
}


//sets the captureMand variable
void ABnode::setCaptureMand(){
    if (isMax == true) //current node is the computer
        captureMand = capturingCheck(currstate, comp);
    else //current node is the human player
        captureMand = capturingCheck(currstate, human);
}


void ABnode::initPlayers(Player& hu, Player& co){
    //copy over the number of pieces and colour for each player
    human.pieces = hu.pieces;
    comp.pieces = co.pieces;
    human.colour = hu.colour;
    comp.colour = co.colour;
    
    //copy over vector of piece locations
    for (int i = 0; i < hu.pieceLoc.size(); i++){ //more efficient to use pieces instead of size function?
        human.pieceLoc.push_back(hu.pieceLoc[i]);
    }
    for (int i = 0; i < co.pieceLoc.size(); i++){
        comp.pieceLoc.push_back(co.pieceLoc[i]);
    }
}


//find the next actions and add to vector (with next state nodes)
//now: player is the current node
//next: opponent of the current node's player
//returns true if there are more actions to be found; false otherwise
bool ABnode::fillActions(Player& now, Player& next){
    //first find if there is an obilgatory capturing move
    //if there is, only run through the capturing moves
    enum directions {N, NW, NE, E, SE, S, SW, W};
    
    if (captureMand == true){ // capturing moves
        for (int i = 0; i < now.pieces; i++){
            int x = now.pieceLoc[i].first; //x-coordinate of player's piece
            int y = now.pieceLoc[i].second; //y-coordinate of player's piece
            int a; //x-coord of new piece location
            int b; //y-coord of new piece location
            int m; //x-coord of captured enemy piece
            int n; //y-coord of captured enemy piece
            
            
            
            
            for (int positions = 0; positions < 8; positions++){
                switch(positions){
                    case(NW):
                        a = x - 2;
                        b = y - 2;
                        m = x - 1;
                        n = y - 1;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == next.colour)){ //check if valid capturing move
                            if (checkDup(x, y, a, b) == true) //check if node was already generated
                                break;
                            else{
                                childGen(1, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(N):
                        a = x;
                        b = y - 2;
                        m = x;
                        n = y - 1;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == next.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(1, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(NE):
                        a = x + 2;
                        b = y - 2;
                        m = x + 1;
                        n = y - 1;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == next.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(1, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(E):
                        a = x + 2;
                        b = y;
                        m = x + 1;
                        n = y;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == next.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(1, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(SE):
                        a = x + 2;
                        b = y + 2;
                        m = x + 1;
                        n = y + 1;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == next.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(1, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(S):
                        a = x;
                        b = y + 2;
                        m = x;
                        n = y + 1;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == next.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(1, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(SW):
                        a = x - 2;
                        b = y + 2;
                        m = x - 1;
                        n = y + 1;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == next.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(1, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(W):
                        a = x - 2;
                        b = y;
                        m = x - 1;
                        n = y;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == next.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(1, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                }
            }
        }
        return false; //no more capturing moves. probably will never be executed
    }
    else{ // plain/cantering moves
        //priority given to plain moves
        
        //plain moves
        for (int i = 0; i < now.pieces; i++){
            int x = now.pieceLoc[i].first; //x-coordinate of player's piece
            int y = now.pieceLoc[i].second; //y-coordinate of player's piece
            int a; //x-coord of new piece location
            int b; //y-coord of new piece location
            
            
            
            
            for (int positions = 0; positions < 8; positions++){
                switch(positions){
                    case(NW):
                        a = x - 1;
                        b = y - 1;
                        if (failSafe(x, y, a, b) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(3, x, y, a, b, 0, 0, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(N):
                        a = x;
                        b = y - 1;
                        if (failSafe(x, y, a, b) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(3, x, y, a, b, 0, 0, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(NE):
                        a = x + 1;
                        b = y - 1;
                        if (failSafe(x, y, a, b) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(3, x, y, a, b, 0, 0, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(E):
                        a = x + 1;
                        b = y;
                        if (failSafe(x, y, a, b) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(3, x, y, a, b, 0, 0, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(SE):
                        a = x + 1;
                        b = y + 1;
                        if (failSafe(x, y, a, b) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(3, x, y, a, b, 0, 0, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(S):
                        a = x;
                        b = y + 1;
                        if (failSafe(x, y, a, b) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(3, x, y, a, b, 0, 0, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(SW):
                        a = x - 1;
                        b = y + 1;
                        if (failSafe(x, y, a, b) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(3, x, y, a, b, 0, 0, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(W):
                        a = x - 1;
                        b = y;
                        if (failSafe(x, y, a, b) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(3, x, y, a, b, 0, 0, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                }
            }
            
        }
        //cantering moves
        for (int i = 0; i < now.pieces; i++){
            int x = now.pieceLoc[i].first; //x-coordinate of player's piece
            int y = now.pieceLoc[i].second; //y-coordinate of player's piece
            int a; //x-coord of new piece location
            int b; //y-coord of new piece location
            int m; //x-coord of piece being leap over
            int n; //y-coord of piece being leap over
            
            
            
            
            
            for (int positions = 0; positions < 8; positions++){
                switch(positions){
                    case(NW):
                        a = x - 2;
                        b = y - 2;
                        m = x - 1;
                        n = y - 1;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == now.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(2, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(N):
                        a = x;
                        b = y - 2;
                        m = x;
                        n = y - 1;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == now.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(2, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(NE):
                        a = x + 2;
                        b = y - 2;
                        m = x + 1;
                        n = y - 1;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == now.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(2, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(E):
                        a = x + 2;
                        b = y;
                        m = x + 1;
                        n = y;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == now.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(2, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(SE):
                        a = x + 2;
                        b = y + 2;
                        m = x + 1;
                        n = y + 1;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == now.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(2, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(S):
                        a = x;
                        b = y + 2;
                        m = x;
                        n = y + 1;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == now.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(2, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(SW):
                        a = x - 2;
                        b = y + 2;
                        m = x - 1;
                        n = y + 1;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == now.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(2, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                    case(W):
                        a = x - 2;
                        b = y;
                        m = x - 1;
                        n = y;
                        if (failSafe(x, y, a, b, m, n) == false){
                            break;
                            //return false???????????????????????????????????
                        }
                        if (currstate.spaceEmpty(a, b) && (currstate.state[n][m] == now.colour)){
                            if (checkDup(x, y, a, b) == true)
                                break;
                            else{
                                childGen(2, x, y, a, b, m, n, now, next);
                                return true;
                            }
                        }
                        else
                            break;
                }
            }
        }
        return false; //no more actions can be generated
    }
    return false;
}


void ABnode::initState(Board& board){
    for (int i = 0; i < 14; i++){
        for (int j = 0; j < 8; j++){
            currstate.state[i][j] = board.state[i][j];
        }
    }
}


//checks if a state is terminal and returns its utility value
//returns -1 if it is not a terminal state
int terminalState(Board& board, Player& human, Player& computer){
    //max = computer
    //min = human
    if ((board.state[13][3] == 'W') && (board.state[13][4] == 'W')){
        return -1000; // MIN wins
    }
    else if ((board.state[0][3] == 'B') && (board.state[0][4] == 'B')){
        return 1000; // MAX wins
    }
    else if ((human.pieces >= 2) && (computer.pieces < 1)){
        return -1000; // MIN wins
    }
    else if ((computer.pieces >=2) && (human.pieces < 1)){
        return 1000; // MAX wins
    }
    else if ((human.pieces == 1) && (computer.pieces == 1)){
        return 0; // DRAW
    }
    else
        return -1; // not a terminal state
}

//evaluation function
int ABeval(ABnode &node){
    int evaluation = 0;
    const int pieceValue = 100;
    
    if (node.isMax == true){
        if (node.currstate.state[13][3] == 'W')
            evaluation = evaluation - 350;
        if (node.currstate.state[13][4] == 'W')
            evaluation = evaluation - 350;
        if (node.currstate.state[0][3] == 'B')
            evaluation = evaluation + 350;
        if (node.currstate.state[0][4] == 'B')
            evaluation = evaluation + 350;
    
        evaluation = evaluation - (node.human.pieces * pieceValue);
        evaluation = evaluation + (node.comp.pieces * pieceValue);
        return evaluation;
    }
    else{
        if (node.currstate.state[13][3] == 'W')
            evaluation = evaluation + 350;
        if (node.currstate.state[13][4] == 'W')
            evaluation = evaluation + 350;
        if (node.currstate.state[0][3] == 'B')
            evaluation = evaluation - 350;
        if (node.currstate.state[0][4] == 'B')
            evaluation = evaluation - 350;
        
        evaluation = evaluation + (node.human.pieces * pieceValue);
        evaluation = evaluation - (node.comp.pieces * pieceValue);
        return evaluation;
    }
    
}


//cut off function
bool ABcutOff(clock_t& timer){
    clock_t now = clock();
    const int max_time = 10; //time limit
    double elasped_seconds = double(now - timer) / CLOCKS_PER_SEC;
    if (elasped_seconds >= max_time)
        return true;
    else
        return false;
}

//cutoff depth based
bool ABcutOffDepth(int &depth){
    const int depth_limit = 50; //depth limit
    if (depth >= depth_limit)
        return true;
    else
        return false;
}




int ABminValue(ABnode &node, int  &alpha, int &beta,int &depth, int &max_depth, int &total_nodes, int &pruned_max, int &pruned_min, clock_t &timer){
    
    total_nodes = total_nodes + 1;
    depth = depth + 1;
    
    int v;
    //return if terminal
    v = terminalState(node.currstate, node.human, node.comp);
    if (v != -1){
        max_depth = std::max(depth, max_depth);
        depth = depth - 1;
        node.utility = v;
        return v;
    }
    
    
    //timer based cutoff function
    if (ABcutOff(timer) == true){
        v = ABeval(node);
        node.utility = v;
        max_depth = std::max(depth, max_depth);
        depth = depth - 1;
        return v;
    }
    
    
    //depth based cutoff function
    if (ABcutOffDepth(depth) == true){
        v = ABeval(node);
        node.utility = v;
        max_depth = std::max(depth, max_depth);
        depth = depth - 1;
        return v;
    }
    
    
    v = 1001;
    node.moreActions = node.fillActions(node.human, node.comp);
    int actionIterator = 0;
    while (node.moreActions == true){
        int max_Value = ABmaxValue(*node.actions[actionIterator], alpha, beta, depth, max_depth, total_nodes, pruned_max, pruned_min, timer);
        v = std::min(v, max_Value);
        node.utility = v;
        if (v <= alpha){
            max_depth = std::max(depth, max_depth);
            depth = depth - 1;
            pruned_min = pruned_min + 1;
            return v;
        }
        beta = std::min(beta, v);
        
        actionIterator++; //bug fux
        
        node.moreActions = node.fillActions(node.comp, node.human); // bug fix
        
    }
    max_depth = std::max(depth, max_depth);
    depth = depth - 1;
    return v;
}


int ABmaxValue(ABnode &node, int  &alpha, int &beta,int &depth, int &max_depth, int &total_nodes, int &pruned_max, int &pruned_min, clock_t& timer){
    
    total_nodes = total_nodes + 1;
    depth = depth + 1;
    
    int v;
    //return if terminal
    v = terminalState(node.currstate, node.human, node.comp);
    if (v != -1){
        max_depth = std::max(depth, max_depth);
        depth = depth - 1;
        node.utility = v;
        return v;
    }
    
    
    //timer based cutoff function
    if (ABcutOff(timer) == true){
        v = ABeval(node);
        node.utility = v;
        max_depth = std::max(depth, max_depth);
        depth = depth - 1;
        return v;
    }
    
    
    //depth based cutoff function
    if (ABcutOffDepth(depth) == true){
        v = ABeval(node);
        node.utility = v;
        max_depth = std::max(depth, max_depth);
        depth = depth - 1;
        return v;
    }
    
    
    
    v = -1001;
    node.moreActions = node.fillActions(node.comp, node.human);
    int actionIterator = 0;
    while (node.moreActions == true){
        int min_Value = ABminValue(*node.actions[actionIterator], alpha, beta, depth, max_depth, total_nodes, pruned_max, pruned_min, timer);
        v = std::max(v, min_Value);
        node.utility = v; //sets the current node v value
        if (v >= beta){
            //pruning
            max_depth = std::max(depth, max_depth);
            depth = depth - 1;
            pruned_max = pruned_max + 1;
            return v;
        }
        alpha = std::max(alpha, v);
        
        actionIterator++; //bug fux
        
        node.moreActions = node.fillActions(node.comp, node.human); // bug fix
        
    }
    max_depth = std::max(depth, max_depth);
    depth = depth - 1;
    return v;
}


//THE ALPHA-BETA-SEARCH ALGORITHM
void ALPHAbetaSEARCH(ABnode &root, int &x, int&y, int&a, int&b){
    int min_utility = -1000; //initial alpha
    int max_utility = 1000; //initial beta
    int depth = 0; //current depth of node
    int max_depth = 0; //maximum depth of tree so far
    int total_nodes = 1; //total number of nodes generated
    int pruned_max = 0; //number of times pruning occured in maxvalue function
    int pruned_min = 0; //number of times pruning occured in minvalue function
    
    /*
    //vector to store leaf nodes
    vector<ABnode*> leaf;
    //vector of utility values. used as iterator to reference leaf nodes
    vector<int> leafUtility;
     */
    
    //timer
    //std::chrono::high_resolution_clock Clock;
    //auto currTime = Clock.now();
    
    clock_t begin = clock();
    
    int v = ABmaxValue(root, min_utility, max_utility, depth, max_depth, total_nodes, pruned_max, pruned_min, begin);
    for (int i = 0; i < root.actions.size(); i++){
        if (root.actions[i]->utility == v){
            x = root.actions[i]->x;
            y = root.actions[i]->y;
            a = root.actions[i]->a;
            b = root.actions[i]->b;
            
            std::cout << "Maximum depth of game tree: " << max_depth << endl;
            std::cout << "Total number of nodes generated: " << total_nodes << endl;
            std::cout << "Number of prunes within MAX-VALUE function: "  << pruned_max << endl;
            std::cout << "Number of prunes within MIN-VALUE function: " << pruned_min << endl;
            
            clock_t end = clock();
            double time_elapsed = double(end - begin) / CLOCKS_PER_SEC;
            std::cout << "Time elapsed: " << time_elapsed << endl;
            
            return;
        }
    }
    
    
}


//function that main.cpp will call
void computerMove(Board& board, Player& human, Player& computer){
    //setting up the root node
    ABnode *root = new ABnode;
    root->initState(board);
    root->initPlayers(human, computer);
    root->moreActions = true;
    root->isMax = true;
    root->prunedAndDead = false;
    root->setCaptureMand();
    
    //actions to be returned
    int x = 0; //x-coord of piece that computer will select
    int y = 0; //y-coord of piece that computer will select
    int a = 0; //x-coord of tile computer will move to
    int b = 0; //x-coord of tile computer will move to
    
    ALPHAbetaSEARCH(*root, x, y, a, b);
    
    //determine what kind of move to commit
    int xShift = x - a;
    int yShift = y - b;
    
    if (((xShift == 2) || (xShift == -2)) || ((yShift == 2) || (yShift == -2))){
        int xVictim = x - (xShift/2);
        int yVictim = y - (yShift/2);
        if (board.state[yVictim][xVictim] == 'W'){
            capturingMove(board, x, y, a, b, xVictim, yVictim, computer, human);
        }
        else{
            canteringMove(board, x, y, a, b, computer);
        }
    }
    else{
        plainMove(board, x, y, a, b, computer);
    }
}
