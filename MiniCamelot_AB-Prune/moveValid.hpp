//
//  moveValid.hpp
//  Mini Camelot
//
//

#ifndef moveValid_hpp
#define moveValid_hpp

#include <stdio.h>

#endif /* moveValid_hpp */

// checks to see if a plain move is within the movement limit
bool plainMoveValidity(int x, int y, int a, int b);

// checks to see if a jump (capturing/cantering) move is within the movement limit
bool jumpValidity(int x, int y, int a, int b);
