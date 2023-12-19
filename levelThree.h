#ifndef __LEVELTHREE_H_
#define __LEVELTHREE_H_
#include <iostream>
#include <vector>
#include "computer.h"

using namespace std; 

class LevelThree: public Computer {

 public:
    LevelThree(Colour colour);
    bool makeMove(Board & b, bool whiteTurn, int origRow, int origCol, int newRow, int newCol) override;
};

#endif
