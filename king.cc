#include "King.h"

King::King(Colour colour):
    Piece{colour, PieceType::King} {}

King::King(int row, int col, Colour colour): Piece{row, col, PieceType::King, colour} {}

bool King::checkMovementValid(const Board &b, int newRow, int newCol) {
    int origRow = getRow();
    int origCol = getCol();

    if (abs(origRow - newRow) > 1) {
        return false;
    } else if (abs(origCol - newCol) > 1) {
        return false;
    }

    // Moving the piece
    setRow(newRow);
    setCol(newCol);
    firstMove = false;

    return true;
}

// Side note: main must call castle for both rook and king simultaneously
bool King::castleKingRight(const Board &b) {
    if (!firstMove) {
        cout << "Not the king's first move" << endl;
        return false;
    }

    // check attacking on square beside king (col + 1) (col + 2)

    if (b.getPiece(getRow(), getCol() + 1) != nullptr || b.getPiece(getRow(), getCol() + 2)) {
        return false;
    }

    // Make the move.
    setCol(getCol() + 2);

    return true;
}

bool King::castleKingLeft(const Board &b) {
    if (!firstMove) {
        cout << "Not the king's first move" << endl;
        return false;
    }

    // check attacking on square beside king (col - 1) (col - 2) (col - 3)

    if (b.getPiece(getRow(), getCol() - 1) != nullptr || b.getPiece(getRow(), getCol() - 2) || b.getPiece(getRow(), getCol() - 3)) {
        return false;
    }

    // Make the move.
    setCol(getCol() - 2);

    return true;
}
