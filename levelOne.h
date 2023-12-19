#ifndef __LEVELONE_H_
#define __LEVELONE_H_
#include <iostream>
#include <vector>
#include "player.h"
#include "computer.h"

using namespace std; 
class Player;

class LevelOne: public Computer {

    public:
        LevelOne(Colour colour);
        bool makeMove(Board & b, bool whiteTurn, int origRow, int origCol, int newRow, int newCol) override;
};

#endif
