#include "bishop.h"

Bishop::Bishop(int row, int col, Colour colour): Piece{row, col, PieceType::Bishop, colour}{}

bool Bishop::checkMovementValid(const Board &b, int newRow, int newCol) {
    int rise = newCol - this->getCol();
    int run = newRow - this->getRow();
    int boardSize = b.getBoardSize();

    if (abs(rise) != abs(run)) {
        return false;
    }

    if (rise > 0 && run > 0) {
        for (int i = 1; i < rise && newRow + i < boardSize && newCol + i < boardSize; ++i) {
            if (b.getPiece(getRow() + i, getCol() + i) != nullptr) {
                return false;
            }
        }
    } else if (rise < 0 && run < 0) {
        for (int i = 1; i < rise && newRow - i > 0 && newCol - i > 0; ++i) {
            if (b.getPiece(getRow() - i, getCol() - i) != nullptr) {
                return false;
            }
        }
    } else if (rise < 0 && run > 0) {
        for (int i = 1; i < rise && newRow - i < 0 && newCol + i > boardSize; ++i) {
            if (b.getPiece(getRow() - i, getCol() + i) != nullptr) {
                return false;
            }
        }
    } else {
        for (int i = 1; i < rise && newRow + i < boardSize && newCol - i > 0; ++i) {
            if (b.getPiece(getRow() + i, getCol() - i)) {
                return false;
            }
        }
    }

    // Moving the piece
    setRow(newRow);
    setCol(newCol);

    return true;
}

// std::vector<int> checkPossibleMoves() {
//     return std::vector<int> {1, 0};
// }

Bishop::~Bishop() {

}
