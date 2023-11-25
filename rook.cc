#include "rook.h"

Rook::Rook(int row, int col, Colour colour): Piece{row, col, PieceType::Rook, colour} {}

bool Rook::checkMovementValid(const Board &b, int newRow, int newCol) {
    int rise = newCol - this->getCol();
    int run = newRow - this->getRow();
    int boardSize = b.getBoardSize();

    if (rise > 0 && run > 0) {
        return false;
    } else if (rise > 0) {
        for (int r = 0; r < rise; ++r) {
            if (b.getPiece(getRow() + r, getCol()) != nullptr) {
                return false;
            }
        }
    } else if (rise < 0) {
        for (int r = 0; r > rise; --r) {
            if (b.getPiece(getRow() + r, getCol()) != nullptr) {
                return false;
            }
        }
    } else if (run > 0) {
        for (int c = 0; c < run; ++c) {
            if (b.getPiece(getRow(), getCol() + c) != nullptr) {
                return false;
            }
        }
    } else {
        for (int c = 0; c > run; --c) {
            if (b.getPiece(getRow(), getCol() + c) != nullptr) {
                return false;
            }
        }
    }

    // Moving the piece
    setRow(newRow);
    setCol(newCol);

    return true;
}
