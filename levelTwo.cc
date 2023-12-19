#include "levelTwo.h"
using namespace std;

LevelTwo::LevelTwo(Colour colour):
    Computer{colour} {}

bool LevelTwo::makeMove(Board & b, bool whiteTurn, int origRow, int origCol, int newRow, int newCol) {
    return levelTwo(b, whiteTurn);
}
