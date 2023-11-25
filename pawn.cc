#include "pawn.h"

Pawn::Pawn(int row, int col, Colour colour): Piece{row, col, PieceType::Pawn, colour}{}

bool Pawn::checkMovementValid(const Board &b, int newRow, int newCol) {
    int rise = newCol - getCol();
    int run = newRow - getRow();
    bool moveMade = false;

    if (rise < 1) {
        moveMade = false;
    }

    if (firstMove && rise == 2 && run == 0 && b.getPiece(newRow - 1, newCol) == nullptr) {
        moveMade = true;
        passantEligible = true;       
    } else if (rise == 1 && run == 0 && b.getPiece(newRow, newCol) == nullptr) {
        moveMade = true;
    } else if (rise == 1 && (run == 1 || run == -1) && b.getPiece(newRow, newCol) != nullptr) {
        moveMade = true;
    } else if (rise == 1 && (run == 1 || run == -1) && b.getPiece(newRow - 1, newCol)->getColour() != getColour()) {
        moveMade = true;
    }

    if (moveMade) {
        firstMove = false;
        setRow(newRow);
        setCol(newCol);
        return true;
    } else {
        return false;
    }

}

