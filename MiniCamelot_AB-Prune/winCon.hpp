//
//  winCon.hpp
//  Mini Camelot
//
//

#ifndef winCon_hpp
#define winCon_hpp

#include <stdio.h>

#endif /* winCon_hpp */

#ifndef BoardClass_hpp
#include "BoardClass.hpp"
#endif

#ifndef PlayerClass_hpp
#include "PlayerClass.hpp"
#endif

//check castle win condition; returns true on game end, false otherwise
bool castleWinCon(Board& board);

//check pieces remaining win condition
bool zeroPieceWinCon(Player& human, Player& computer);

//check draw condition
bool drawCon(Player& human, Player& computer);

//win/draw condition function; returns true on game end. false otherwise
bool winCondition(Board& board, Player& player, Player& computer);
