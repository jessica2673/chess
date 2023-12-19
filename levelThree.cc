#include "levelThree.h"

LevelThree::LevelThree(Colour colour):
    Computer{colour} {}

bool LevelThree::makeMove(Board & b, bool whiteTurn, int origRow, int origCol, int newRow, int newCol) {
    return levelThree(b, whiteTurn);
}

