#include "pawn.h"
#include <stdexcept>

Pawn::Pawn(Colour colour): Piece{colour, PieceType::Pawn}{}

bool Pawn::checkEnPassant(Board &b, int newRow, int newCol) {
    // If there is a piece in the position below your new movement, and the piece is a pawn, check if the last move was this pawn moving two squares.
    if (b.getPiece(getRow(), newCol) && b.getPiece(getRow(), newCol)->getState() == PieceType::Pawn) {
        vector<int> prevMove = b.getLastMove();
        if (prevMove[2] == getRow() && prevMove[3] == newCol && (abs(prevMove[2] - prevMove[0]) == 2)) {
            return true;
        }
    }
}

bool Pawn::checkMovementValid(Board &b, int newRow, int newCol, bool calledByPlayer) {
    int riseNeeded = 1;
    int rise = newRow - getRow();
    int run = newCol - getCol();
    bool moveMade = false;
    Colour colour = getColour();

    // A pawn moves "up" the board, meaning its row index decreases instead of increases.
    if (colour == Colour::WHITE) {
        riseNeeded = -1;
    } 

    // Checks if it can move two squares up for its first move.
    if (firstMove && rise == (2 * riseNeeded) && run == 0 && !b.getPiece(newRow - riseNeeded, newCol) && !b.getPiece(newRow, newCol)) {
        moveMade = true;     
    } else if (rise == riseNeeded && run == 0 && !b.getPiece(newRow, newCol)) { // Checks if it can move one square up.
        moveMade = true;
    } else if (rise == riseNeeded && (run == 1 || run == -1) && b.getPiece(newRow, newCol)) { // Checks if it can move to either side.
        moveMade = true;
    } 
    // Checks for an en passant move.
    else if (rise == riseNeeded && (run == 1 || run == -1) && b.getPiece(getRow(), newCol) && b.getPiece(getRow(), newCol)->getColour() != getColour()) {
        moveMade = checkEnPassant(b, newRow, newCol);
    }

    if (!calledByPlayer) return moveMade;

    // Throws if the pawn needs to be promoted.
    if ((newRow == 0 && colour == Colour::WHITE) || (newRow == 7 && colour == Colour::BLACK)) {
        throw std::logic_error{""};
    } 
    
    // Returns whether or not the move can be made.
    return moveMade;
}

void Pawn::placePiece(Board & b, int row, int col) {
    int origRow = getRow();
    int origCol = getCol();
    int run = col - origCol;
    
    // Checks if an en passant move is being performed, and performs en passant.
    if (abs(run) == 1 && !b.getPiece(row, col) && b.getPiece(origRow, col) && b.getPiece(origRow, col)->getState() == PieceType::Pawn) {
        performEnPassant(b, col);
    }

    // Moves the piece to its new location.
    setCoords(row, col);
    b.removePiece(row, col);
    b.setPiece(this, row, col);
    b.setPiece(nullptr, origRow, origCol);
    
    // No longer the first move.
    firstMove = false;

    // Notifies observers.
    this->notifyObservers(); 
}

void Pawn::performEnPassant(Board &b, int newCol) {
    // Removes the piece that you are passing by in an en passant move.
    b.removePiece(getRow(), newCol);
}

vector<vector<int>> Pawn::checkPossibleMoves(Board &b) {
    vector<vector<int>> possibleMoves;
    int boardSize = b.getBoardSize();
    int riseNeeded = 1;
    int row = getRow();
    int col = getCol();
    Colour colour = getColour();
    
    // Changing rise needed depending on colour.
    if (colour == Colour::WHITE) {
        riseNeeded = -1;
    }
    // Adds the standard moving up a square move.
    if ((row + riseNeeded < boardSize && row + riseNeeded >= 0) && !b.getPiece(row + riseNeeded, col)) {
        possibleMoves.emplace_back(vector <int> {row + riseNeeded, col});
    } 
    // Adds the diagonal moves.
    if (row + riseNeeded < boardSize && row + riseNeeded >= 0 && col - 1 >= 0) {
        if (b.getPiece(row + riseNeeded, col - 1) && b.getPiece(row + riseNeeded, col - 1)->getColour() != colour) {
            // Adds diagonal capture to the West.
            possibleMoves.emplace_back(vector <int> {row + riseNeeded, col - 1});
        } else if (!b.getPiece(row + riseNeeded, col - 1) && b.getPiece(row, col - 1) && b.getPiece(row, col - 1)->getColour() != colour && b.getPiece(row, col - 1)->getState() == PieceType::Pawn) {
            // Adds en passant to the West.
            if (checkEnPassant(b, row, col - 1)) {
                possibleMoves.emplace_back(vector <int> {row + riseNeeded, col - 1});
            }
        }
    }
    if ((row + riseNeeded < boardSize && row + riseNeeded >= 0 && col + 1 < boardSize)) {
        if (b.getPiece(row + riseNeeded, col + 1) && b.getPiece(row + riseNeeded, col + 1)->getColour() != colour) {
            // Adds diagonal capture to the East.
            possibleMoves.emplace_back(vector <int> {row + riseNeeded, col + 1});
        } else if (!b.getPiece(row + riseNeeded, col + 1) && b.getPiece(row, col + 1) && b.getPiece(row, col + 1)->getColour() != colour && b.getPiece(row, col + 1)->getState() == PieceType::Pawn) {
            // Adds en passant to the East.
            if (checkEnPassant(b, row, col + 1)) {
                possibleMoves.emplace_back(vector <int> {row + riseNeeded, col + 1});
            }
        }
    }
    // Adds the potential first move of moving up 2 squares.
    if ((row + 2 * riseNeeded < boardSize && row + 2 * riseNeeded >= 0) && firstMove && !b.getPiece(row + 2 * riseNeeded, col) && !b.getPiece(row + riseNeeded, col)) {
        possibleMoves.emplace_back(vector <int> {row + 2 * riseNeeded, col});
    }


    return possibleMoves;
}

vector<vector<int>> Pawn::checkEnPassantMoves(Board &b) {
    vector<vector<int>> enPassantMoves;
    int boardSize = b.getBoardSize();
    int riseNeeded = 1;
    int row = getRow();
    int col = getCol();
    Colour colour = getColour();

    if (colour == Colour::WHITE) {
        riseNeeded = -1;
    }

    // Checks en passant to the West with same logic as in checkPossibleMoves.
    if (row + riseNeeded < boardSize && row + riseNeeded >= 0 && col - 1 >= 0) {
        if (!b.getPiece(row + riseNeeded, col - 1) && b.getPiece(row, col - 1) && b.getPiece(row, col - 1)->getColour() != colour && b.getPiece(row, col - 1)->getState() == PieceType::Pawn) {
            if (checkEnPassant(b, row, col - 1)) {
                enPassantMoves.emplace_back(vector <int> {row + riseNeeded, col - 1});
            }
        }
    }

    // Checks en passant to the East with same logic as in checkPossibleMoves.
    if ((row + riseNeeded < boardSize && row + riseNeeded >= 0 && col + 1 < boardSize)) {
        if (!b.getPiece(row + riseNeeded, col + 1) && b.getPiece(row, col + 1) && b.getPiece(row, col + 1)->getColour() != colour && b.getPiece(row, col + 1)->getState() == PieceType::Pawn) {
            if (checkEnPassant(b, row, col + 1)) {
                enPassantMoves.emplace_back(vector <int> {row + riseNeeded, col + 1});
            }
        }
    }

    return enPassantMoves;
}

bool Pawn::checkForPromotion(int row) {
    // A white piece will be promoted if and only if it has made it to the top of the board (row index 0).
    if (row == 0 && getColour() == Colour::WHITE) {
        return true;
    } 
    // A black piece will be promoted if and only if it has made it to the bottom of the board (row index 7).
    else if (row == 7 && getColour() == Colour::BLACK) { 
        return true;
    } 
    // Otherwise, no promotion.
    else {
        return false;
    }
}
