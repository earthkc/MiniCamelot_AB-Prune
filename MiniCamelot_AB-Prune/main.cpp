//
//  main.cpp
//
//  Mini Camelot
//
//

#include <iostream>
#include <string>
#include <vector>
#include "moveValid.hpp"
#include "BoardClass.hpp"
#include "PlayerClass.hpp"
#include "precaptureCheck.hpp"
#include "commitMove.hpp"
#include "winCon.hpp"
#include "compAction.hpp"
using namespace std;

bool xInputCheck(int x){
    switch(x){
        case 0:
            return true;
        case 1:
            return true;
        case 2:
            return true;
        case 3:
            return true;
        case 4:
            return true;
        case 5:
            return true;
        case 6:
            return true;
        case 7:
            return true;
        default:
            return false;
    }
}

bool yInputCheck(int& x){
    switch(x){
        case 0:
            return true;
        case 1:
            return true;
        case 2:
            return true;
        case 3:
            return true;
        case 4:
            return true;
        case 5:
            return true;
        case 6:
            return true;
        case 7:
            return true;
        case 8:
            return true;
        case 9:
            return true;
        case 10:
            return true;
        case 11:
            return true;
        case 12:
            return true;
        case 13:
            return true;
        default:
            return false;
    }
}


// check's validity the player's chosen move
void playerMoveValidity(Board& board, int x, int y, int a, int b, Player& player, Player& computer){
//void playerMoveValidity(Board& board, Player& player, Player& computer){
    bool successfulMove = false;
    
    // checks for avaliable capturing moves
    bool MandatoryCapture = capturingCheck(board, player);
    
    while (successfulMove == false){
        if (MandatoryCapture == true)
            cout << "There is an avaliable obligatory capturing move.\n";
        
        //piece selection
        //int x;
        //int y;
        while (true){
            while (true){
                cout << "Enter the x-coordinate of the piece you want to move: \n";
                cin >> x;
                /*
                if (std::cin.fail()){
                    std::cout << "Invalid x-coordinate input. Non-integer entered\n";
                    std::cin.clear();
                    std::cin.ignore(INT_MAX, '\n');
                }
                else if ((x < 0) || (x > 7))
                    std::cout << "Invalid x-coordinate input. Out of bounds\n";
                else
                    break;
                 */
                if (xInputCheck(x) == true){
                    break;
                }
                else{
                    std::cout << "Invalid x-coordinate input.\n";
                    //std::cin.clear();
                    //std::cin.ignore(INT_MAX, '\n');
                }
            }
            while (true){
                cout << "Enter the y-coordinate of the piece you want to move: \n";
                cin >> y;
                if (yInputCheck(y) == true)
                    break;
                else{
                    std::cout << "Invalid y-coordinate input.\n";
                    //std::cin.clear();
                    //std::cin.ignore(INT_MAX, '\n');
                }
            }
            if (board.state[y][x] == player.colour) //confirming valid piece selection
                break;
            else{
                cout << "Invalid piece chosen. Please select again.\n";
                //std::cin.clear();
                //std::cin.ignore(INT_MAX, '\n');
            }
        }
        
        // player chooses the space to move to
        while (true){
            
            //move selection
            //int a;
            //int b;
            while (true){
                cout << "Enter the x-coordinate of the space you want " << x << "," << y << " to move to: \n";
                cin >> a;
                if (xInputCheck(a) == true){
                    break;
                }
                else{
                    std::cout << "Invalid x-coordinate input.\n";
                    //std::cin.clear();
                    //std::cin.ignore(INT_MAX, '\n');
                }
            }
            while (true){
                cout << "Enter the y-coordinate of the space you want " << x << "," << y << " to move to: \n";
                cin >> b;
                if (yInputCheck(y) == true)
                    break;
                else{
                    std::cout << "Invalid y-coordinate input.\n";
                    //std::cin.clear();
                    //std::cin.ignore(INT_MAX, '\n');
                }
            }
            
            
            if (board.spaceEmpty(a, b) == true){ //confirming the space to move to is unoccupied
                int xShift = x - a;
                int yShift = y - b;
                int xVictim = x - (xShift/2);
                int yVictim = y - (yShift/2);
                if (MandatoryCapture == true){
                    //capturing move
                    if ((board.state[yVictim][xVictim] == 'B') && (jumpValidity(x, y, a, b) == true)){
                        capturingMove(board, x, y, a, b, xVictim, yVictim, player, computer);
                        successfulMove = true;
                        break;
                    }
                    else{
                        cout << "Invalid move. There is an avaliable capturing move that must be taken.\n";
                        break;
                    }
                }
                
                
                //cantering move
                else if ((board.state[yVictim][xVictim] == 'W') && (jumpValidity(x, y, a, b) == true)){
                    canteringMove(board,x,y,a,b,player);
                    successfulMove = true;
                    break;
                }
                
                //plain move
                else if ((plainMoveValidity(x, y, a, b) == true)){
                    plainMove(board, x, y, a, b, player);
                    successfulMove = true;
                    break;
                    
                }
                
                else{
                    cout << "Invalid move chosen.\n";
                    break;
                }
            }
            
            else{ //space selected was found to be occupied
                cout << "Invalid move. Space was occupied or out of bounds.\n";
                break;
            }
        }
    }
}


int main(int argc, const char * argv[]) {
    Board board;
    Player Human;
    Human.setColour('W');
    Player Computer;
    Computer.setColour('B');
    
    //add pieces locations to player's vector
    //pair<x-coord, y-coord>
    
    Human.pieceLoc.push_back(make_pair(2,4));
    Human.pieceLoc.push_back(make_pair(3,4));
    Human.pieceLoc.push_back(make_pair(4,4));
    Human.pieceLoc.push_back(make_pair(5,4));
    Human.pieceLoc.push_back(make_pair(3,5));
    Human.pieceLoc.push_back(make_pair(4,5));
    Computer.pieceLoc.push_back(make_pair(3,8));
    Computer.pieceLoc.push_back(make_pair(4,8));
    Computer.pieceLoc.push_back(make_pair(2,9));
    Computer.pieceLoc.push_back(make_pair(3,9));
    Computer.pieceLoc.push_back(make_pair(4,9));
    Computer.pieceLoc.push_back(make_pair(5,9));
    
    cout << "Mini Camelot Game \n \n";
    board.printBoard();
    cout << "\nHuman Player is White 'W'. Computer is Black 'B' \n";
    cout << "'_' are empty spaces. '+' are castles. \n";
    cout << "White's castles are at the top. Black's castles are at the bottom. \n\n";
    
    cout << "Pieces can move horizontally, vertically or diagonally in one of three ways.\n";
    cout << "1. Plain move: move into an empty adjacent square in any direction.\n";
    cout << "2. Cantering move: leaping move over one of your own adjacent piece to an empty space \n";
    cout << "immediately beyond. \n";
    cout << "3. Capturing move: jump over an adjacent enemy piece to an empty space\n";
    cout << "immediately beyond. The enemy piece is removed from the board.\n";
    cout << "Capturing moves must be taken whenever they are possible.\n\n";
    
    std::cout << "Two ways to win:\n";
    std::cout << "1. Occupy the opponent's two castles with your own pieces.\n";
    std::cout << "2. Capture all of the enemy's pieces while retaining at least of your own pieces.\n";
    std::cout << "NOTE: A draw occurs if both players have only one piece left.\n\n";
    
    
    
    //Turn Setting
    cout << "Choose whether to move first or second.\n";
    cout << "Input '1' for first or '2' for second: ";
    int turn;
    cin >> turn;
    Human.setTurn(turn);
    if (Human.turn == true)
        Computer.setTurn(2);
    else
        Computer.setTurn(1);
    Human.showTurn();
    Computer.showTurn();
    cout << endl;
    
    
    //LET THE GAMES BEGIN
    cout << "GAME START\n";
    bool gameEnd = false;
    while (gameEnd == false){
        board.printBoard();
        std::cout << endl;
        
         int x; // player's chosen piece x-coord
         int y; // player's chosen piece y-coord
         int a; // player's chosen move
         int b; // player's chosen move
        
        if (Human.turn == true){ // Human goes first
            playerMoveValidity(board, x, y, a, b, Human, Computer); // player move function
            board.printBoard();
            std::cout << endl;
            if (winCondition(board, Human, Computer) == true){ // test win conditions
                gameEnd = true;
            }
            else{ // begin computer move
                std::cout << "Thinking... \n";
                computerMove(board, Human, Computer); // computer function
                std::cout << endl;
                if (winCondition(board, Human, Computer) == true){ // test win conditions
                    board.printBoard();
                    gameEnd = true;
                }
            }
        }
        else{ // Computer goes first
            std::cout << "Thinking... \n";
            computerMove(board, Human, Computer); // computer function
            board.printBoard();
            std::cout << endl;
            if (winCondition(board, Human, Computer) == true){ // test win conditions
                gameEnd = true;
            }
            else{
                playerMoveValidity(board, x, y, a, b, Human, Computer); // player move function
                std::cout << endl;
                if (winCondition(board, Human, Computer) == true){ // test win conditions
                    board.printBoard();
                    gameEnd = true;
                }
            }
            
        }
    }
    
    cout << "Game End. \n" << endl;
    return 0;
}
