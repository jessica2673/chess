#include "rook.h"

Rook::Rook(Colour colour):
    Piece{colour, PieceType::Rook} {}

bool Rook::checkMovementValid(Board &b, int newRow, int newCol, bool calledByPlayer) {
    return checkHorizontalVertical(b, newRow, newCol);
}

void Rook::placePiece(Board & b, int row, int col) {
    int origRow = getRow();
    int origCol = getCol();
    setCoords(row, col);

    b.removePiece(row, col);
    b.setPiece(this, row, col);
    b.setPiece(nullptr, origRow, origCol);
    this->notifyObservers();

    // If any move is made, it is no longer the Rook's first move.
    firstMove = false;
}

vector<vector<int>> Rook::checkPossibleMoves(Board &b) {
    vector<vector<int>> possibleMoves;
    int boardSize = b.getBoardSize();

    // Check squares N of the Rook.
    int row = getRow() - 1;
    int col = getCol();

    // For all squares above the Rook, check if it can legally move to it.
    while (row >= 0) {
        Piece * p = b.getPiece(row, col);
        // If it is an empty square, it is a valid move.
        if (!p) {
            possibleMoves.emplace_back(vector<int>{row, col});
        } else if (p->getColour() != getColour()) {
            // If there is an enemy piece on the square, it is a valid capture move.
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        --row;
    }

    // Check squares E of the Rook.
    row = getRow();
    col = getCol() + 1;
    
    while (col < boardSize) {
        Piece * p = b.getPiece(row, col);
        if (!p) {
            possibleMoves.emplace_back(vector<int>{row, col});
        } else if (p->getColour() != getColour()) {
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        ++col;
    }

    // Check squares S of the Rook.
    row = getRow() + 1;
    col = getCol();

    while (row < boardSize) {
        Piece * p = b.getPiece(row, col);
        if (!p) {
            possibleMoves.emplace_back(vector<int>{row, col});
        } else if (p->getColour() != getColour()) {
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        ++row;
    }

    // Check squares W of the Rook.
    row = getRow();
    col = getCol() - 1;

    while (col >= 0) {
        Piece * p = b.getPiece(row, col);
        if (!p) {
            possibleMoves.emplace_back(vector<int>{row, col});
        } else if (p->getColour() != getColour()) {
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        --col;
    }

    return possibleMoves;
}

bool Rook::castleRookRight() {
    if (!firstMove) {
        throw std::invalid_argument{"Not the rook's first move"};
    }

    return true;
}

bool Rook::castleRookLeft() {
    if (!firstMove) {
        throw std::invalid_argument{"Not the rook's first move"};
    }

    return true;
}
