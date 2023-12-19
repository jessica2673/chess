#include "knight.h"

Knight::Knight(Colour colour): Piece{colour, PieceType::Knight}{}

bool Knight::checkMovementValid(Board &b, int newRow, int newCol, bool calledByPlayer) {
    int row = getRow();
    int col = getCol();

    // Checks start on the top left square and move counter-clockwise.
    if ((newRow == row - 2) && (newCol == col - 1)) {
        return true;
    } else if ((newRow == row - 2) && (newCol == col + 1)) {
        return true;
    } else if ((newRow == row - 1) && (newCol == col + 2)) {
        return true;
    } else if ((newRow == row + 1) && (newCol == col + 2)) {
        return true;
    } else if ((newRow == row + 2) && (newCol == col + 1)) {
        return true;
    } else if ((newRow == row + 2) && (newCol == col - 1)) {
        return true;
    } else if ((newRow == row + 1) && (newCol == col - 2)) {
        return true;
    } else if ((newRow == row - 1) && (newCol == col - 2)) {
        return true;
    }

    return false;
}

vector<vector<int>> Knight::checkPossibleMoves(Board &b) {
    vector<vector<int>> possibleMoves;
    int row = getRow();
    int col = getCol();
    int boardSize = b.getBoardSize();
    Colour colour = getColour();

    // Check the top 2 squares.
    if (row - 2 >= 0) {
        if (col + 1 < boardSize) {
            if (!b.getPiece(row - 2, col + 1) || (b.getPiece(row - 2, col + 1)->getColour() != colour)) {
                possibleMoves.emplace_back(vector <int> {row - 2, col + 1});
            }            
        }
        if (col - 1 >= 0) {
            if (!b.getPiece(row - 2, col - 1) || (b.getPiece(row - 2, col - 1)->getColour() != colour)) {
                possibleMoves.emplace_back(vector <int> {row - 2, col - 1});
            }            
        }
    }

    // Check the bottom 2 squares.
    if (row + 2 < boardSize) {
        if (col + 1 < boardSize) {
            if (!b.getPiece(row + 2, col + 1) || (b.getPiece(row + 2, col + 1)->getColour() != colour)) {
                possibleMoves.emplace_back(vector <int> {row + 2, col + 1});
            }
        }
        if (col - 1 >= 0) {
            if (!b.getPiece(row + 2, col - 1) || (b.getPiece(row + 2, col - 1)->getColour() != colour)) {
                possibleMoves.emplace_back(vector <int> {row + 2, col - 1});
            }
        }
    }

    // Check the left and right squares.
    if (row + 1 < boardSize) {
        if (col + 2 < boardSize) {
            if (!b.getPiece(row + 1, col + 2) || (b.getPiece(row + 1, col + 2)->getColour() != colour)) {
                possibleMoves.emplace_back(vector <int> {row + 1, col + 2});
            }              
        } if (col - 2 >= 0) {
            if (!b.getPiece(row + 1, col - 2) || (b.getPiece(row + 1, col - 2)->getColour() != colour)) {
                possibleMoves.emplace_back(vector <int> {row + 1, col - 2});
            }              
        }
    }
    
    if (row - 1 >= 0) {
        if (col + 2 < boardSize) {
            if (!b.getPiece(row - 1, col + 2) || (b.getPiece(row - 1, col + 2)->getColour() != colour)) {
                possibleMoves.emplace_back(vector <int> {row - 1, col + 2});
            }             
        } if (col - 2 >= 0) {
            if (!b.getPiece(row - 1, col - 2) || (b.getPiece(row - 1, col - 2)->getColour() != colour)) {
                possibleMoves.emplace_back(vector <int> {row - 1, col - 2});
            }
        }
    }

    return possibleMoves;
}
