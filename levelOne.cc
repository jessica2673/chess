#include "levelOne.h"
#include <random>
#include <stdlib.h>
#include <time.h> 

using namespace std;

LevelOne::LevelOne(Colour colour):
    Computer{colour} {}

bool LevelOne::makeMove(Board & b, bool whiteTurn, int origRow, int origCol, int newRow, int newCol) {
    return levelOne(b, whiteTurn);
}

