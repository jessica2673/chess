#include "levelFour.h"

using namespace std;

LevelFour::LevelFour(Colour colour):
    Computer{colour} {}

bool LevelFour::makeMove(Board & b, bool whiteTurn, int origRow, int origCol, int newRow, int newCol) {
    return levelFour(b, whiteTurn);
}
