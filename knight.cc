#include "knight.h"

Knight::Knight(Colour colour): Piece{colour, PieceType::Knight}{}

Knight::Knight(int row, int col, Colour colour): Piece{row, col, PieceType::Knight, colour}{}

bool Knight::checkMovementValid(const Board &b, int newRow, int newCol) {
    int rise = newRow - getRow();
    int run = newCol - getCol();

    if (!(abs(rise) + abs(run) == 3)) {
        return false;
    } else {
        moveMyself(newRow, newCol);
        notifyObservers();
        return true;
    }
}
