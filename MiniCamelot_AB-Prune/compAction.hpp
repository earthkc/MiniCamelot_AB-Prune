//
//  compAction.hpp
//  Mini Camelot
//
//

#ifndef compAction_hpp
#define compAction_hpp

#include <stdio.h>

#endif /* compAction_hpp */

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


class ABnode{
public:
    ABnode* prev; //pointer to the previous node in the tree
    
    //actions, other nodes in the tree
    vector<ABnode*> actions; //next actions a node could take
    vector<ABnode*> pruned; //keeps track of pruned nodes
    bool fillActions(Player& now, Player& next); //find the next action
    bool moreActions; //true if there are more actions, false if there aren't
    bool checkDup(int x, int y, int a, int b); //check if a duplicate action was already generated
    
    ABnode(); //constructor
    //main identifiers
    int x; //x-coord of piece to be moved
    int y; //y-coord of piece to be moved
    int a; //x-coord of tile to be moved to   (also used to help root node determine action)
    int b; //y-coord of tile to be moved to   (also used to help root node determine action)
    bool isMax; //true if node is MAX player; false if node is MIN player
    bool prunedAndDead; //true if the node is part of a pruned branch
    //visited bool?
    //terminal bool? same as moreactions bool?
    
    //board states and properties
    Board currstate;
    bool captureMand; //true if node has a mandatory capture move
    void setCaptureMand(); //sets the captureMand variable
    
    int utility;
    void initState(Board& board); //copies the current active board state into the node's board state
    
    Player human;
    Player comp;
    void initPlayers(Player& hu, Player& co); //fill the player classes
    
    //destructor?
    
    //pseudo-copy constructor; copies many of previous node but makes adjustments necessary of a child node
    //ABnode(const ABnode & obj, int x, int y, int a, int b);
    void newChild(ABnode& child, int x, int y, int a, int b);
    void childGen(int moveFlag, int x, int y, int a, int b, int m, int n, Player& now, Player& next); //performs child node book-keeping
};


bool failSafe(int x, int y, int a, int b, int m, int n);
    


bool failSafe(int x, int y, int a, int b);


bool ABcutOffDepth(int &depth);

int ABeval(ABnode &node);

bool ABcutOff(clock_t& timer);


int ABminValue(ABnode &node, int  &alpha, int &beta,int &depth, int &max_depth, int &total_nodes, int &pruned_max, int &pruned_min, clock_t &timer);


int ABmaxValue(ABnode &node, int  &alpha, int &beta,int &depth, int &max_depth, int &total_nodes, int &pruned_max, int &pruned_min, clock_t &timer);

void ALPHAbetaSEARCH(ABnode &root, int &x, int&y, int&a, int&b);

void computerMove(Board& board, Player& human, Player& computer);
