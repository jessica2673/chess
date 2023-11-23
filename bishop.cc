#include "bishop.h"

Bishop::Bishop(int row, int col, Colour colour): Piece{row, col, PieceType::Bishop, colour}{}

bool Bishop::checkMovementValid(int newRow, int newCol) {
    int rise = newCol - this->getCol();
    int run = newRow - this->getRow();

    if (abs(rise) == abs(run)) {
        return true;
    }
    return false;
}

