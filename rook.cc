#include "rook.h"

Rook::Rook(int row, int col, Colour colour): Piece{row, col, PieceType::Rook, colour} {}

bool Rook::checkMovementValid(const Board &b, int newRow, int newCol) {
    int rise = newCol - this->getCol();
    int run = newRow - this->getRow();
    int boardSize = b.getBoardSize();

    

    // Moving the piece
    setRow(newRow);
    setCol(newCol);

    return true;
}
