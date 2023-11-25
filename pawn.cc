#include "pawn.h"

Pawn::Pawn(Colour colour): Piece{colour, PieceType::Pawn}{}

Pawn::Pawn(int row, int col, Colour colour): Piece{row, col, PieceType::Pawn, colour}{}

bool Pawn::checkMovementValid(const Board &b, int newRow, int newCol) {
    int rise = newRow - getRow();
    int run = newCol - getCol();
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
        moveMyself(newRow, newCol);
        notifyObservers();
        return true;
    } else {
        return false;
    }

}

