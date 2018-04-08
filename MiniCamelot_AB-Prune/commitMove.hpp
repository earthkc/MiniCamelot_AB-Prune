//
//  commitMove.hpp
//  Mini Camelot
//
//

#ifndef commitMove_hpp
#define commitMove_hpp

#include <stdio.h>

#endif /* commitMove_hpp */


#ifndef BoardClass_hpp
#include "BoardClass.hpp"
#endif

#ifndef PlayerClass_hpp
#include "PlayerClass.hpp"
#endif

void plainMove(Board& board, int x, int y, int a, int b, Player& player);

void canteringMove(Board& board, int x, int y, int a, int b, Player& player);

void capturingMove(Board& board, int x, int y, int a, int b, int m, int n, Player& victor, Player& loser);

