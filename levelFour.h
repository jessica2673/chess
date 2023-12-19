#ifndef __LEVELFOUR_H_
#define __LEVELFOUR_H_
#include <iostream>
#include <vector>
#include <map>
#include "computer.h"

using namespace std;

class LevelFour: public Computer {

 public:
    LevelFour(Colour colour);
    bool makeMove(Board & b, bool whiteTurn, int origRow, int origCol, int newRow, int newCol) override;
};

#endif
