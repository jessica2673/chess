#include "bishop.h"

Bishop::Bishop(Colour colour):
    Piece{colour, PieceType::Bishop} {}

bool Bishop::checkMovementValid(Board &b, int newRow, int newCol, bool calledByPlayer) {
    return checkDiagonal(b, newRow, newCol);
}

vector<vector<int>> Bishop::checkPossibleMoves(Board & b) {
    vector<vector<int>> possibleMoves;
    int boardSize = b.getBoardSize();

    // Check squares NE of Bishop.
    int row = getRow() - 1;
    int col = getCol() + 1;
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


    // Check squares SE of Bishop.
    row = getRow() + 1;
    col = getCol() + 1;
    while (row < boardSize && col < boardSize) {
        Piece * p = b.getPiece(row, col);
        if (!p) {
            possibleMoves.emplace_back(vector <int> {row, col});
        } else if (p->getColour() != getColour()) {
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        ++row;
        ++col;
    }

    // Check squares SW of Bishop.
    row = getRow() + 1;
    col = getCol() - 1;

    while (col >= 0 && row < boardSize) {
        Piece * p = b.getPiece(row, col);
        if (!p) {
            possibleMoves.emplace_back(vector <int> {row, col});
        } else if (p->getColour() != getColour()) {
            possibleMoves.emplace_back(vector <int> {row, col});
            break;
        } else {
            break;
        }
        ++row;
        --col;
    }

    // Check squares NW of Bishop.
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

Bishop::~Bishop() {}
