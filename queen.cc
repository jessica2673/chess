#include "queen.h"

Queen::Queen(Colour colour):
    Piece{colour, PieceType::Queen} {}

bool Queen::checkMovementValid(Board &b, int newRow, int newCol, bool calledByPlayer) {
    // Checks whether the move is either an appropriate diagonal move or a horizontal/vertical move.
    return (checkDiagonal(b, newRow, newCol) || checkHorizontalVertical(b, newRow, newCol));
}

vector<vector<int>> Queen::checkPossibleMoves(Board &b) {
    vector<vector<int>> possibleMoves;
    int boardSize = b.getBoardSize();

    // Check squares N of Queen.
    int row = getRow() - 1;
    int col = getCol();

    while (row >= 0) {
        Piece * p = b.getPiece(row, col);
        if (!p) {
            possibleMoves.emplace_back(vector<int>{row, col});
        } else if (p->getColour() != getColour()) {  // enemy piece
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        --row;
    }

    // Check squares E of Queen.
    row = getRow();
    col = getCol() + 1;
    
    while (col < boardSize) {
        Piece * p = b.getPiece(row, col);
        if (!p) {
            possibleMoves.emplace_back(vector<int>{row, col});
        } else if (p->getColour() != getColour()) {  // enemy piece
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        ++col;
    }

    // Check squares S of Queen.
    row = getRow() + 1;
    col = getCol();

    while (row < boardSize) {
        Piece * p = b.getPiece(row, col);
        if (!p) {
            possibleMoves.emplace_back(vector<int>{row, col});
        } else if (p->getColour() != getColour()) {  // enemy piece
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        ++row;
    }

    // Check squares W of Queen.
    row = getRow();
    col = getCol() - 1;
    while (col >= 0) {
        Piece * p = b.getPiece(row, col);
        if (!p) {
            possibleMoves.emplace_back(vector<int>{row, col});
        } else if (p->getColour() != getColour()) {  // enemy piece
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        --col;
    }

    // Check squares NE of Queen.
    row = getRow() - 1;
    col = getCol() + 1;
    while (row >= 0 && col < boardSize) {
        Piece * p = b.getPiece(row, col);
        if (!p) {
            possibleMoves.emplace_back(vector <int> {row, col});
        } else if (p->getColour() != getColour()) {
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        --row;
        ++col;
    }


    // Check squares SE of Queen.
    row = getRow() + 1;
    col = getCol() + 1;
    while (row < boardSize && col < boardSize) {
        Piece * p = b.getPiece(row, col);
        if (!p) {
            possibleMoves.emplace_back(vector<int>{row, col});
        } else if (p->getColour() != getColour()) {  // enemy piece
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        ++row;
        ++col;
    }

    // Check squares SW of Queen.
    row = getRow() + 1;
    col = getCol() - 1;

    while (col >= 0 && row < boardSize) {
        Piece * p = b.getPiece(row, col);
        if (!p) {
            possibleMoves.emplace_back(vector<int>{row, col});
        } else if (p->getColour() != getColour()) {  // enemy piece
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        ++row;
        --col;
    }

    // Check squares NW of Queen.
    row = getRow() - 1;
    col = getCol() - 1;
    while (col >= 0 && row >= 0) {
        Piece * p = b.getPiece(row, col);
        if (!p) {
            possibleMoves.emplace_back(vector<int>{row, col});
        } else if (p->getColour() != getColour()) {  // enemy piece
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        --row;
        --col;
    }

    return possibleMoves;
}
