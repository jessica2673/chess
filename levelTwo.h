#ifndef __LEVELTWO_H_
#define __LEVELTWO_H_
#include <iostream>
#include <vector>
#include <map>
#include "computer.h"

using namespace std;

class LevelTwo: public Computer {

 public:
    LevelTwo(Colour colour);
    bool makeMove(Board & b, bool whiteTurn, int origRow, int origCol, int newRow, int newCol) override;
};

#endif
