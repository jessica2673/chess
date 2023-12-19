#include "king.h"

King::King(Colour colour):
    Piece{colour, PieceType::King} {}

bool King::checkMovementValid(Board &b, int newRow, int newCol, bool calledByPlayer) {
    int origRow = getRow();
    int origCol = getCol();

    // Check if the move is a castle move.
    if (origCol - newCol == 2) {
        return castleKingLeft(b);
    } if (origCol - newCol == -2) {
        return castleKingRight(b);
    }

    // If the move is more than 1 square vertically or horizontally, it is invalid.
    if (abs(origRow - newRow) > 1) {
        return false;
    } else if (abs(origCol - newCol) > 1) {
        return false;
    }

    return true;
}

bool King::isInCheck(const Board &b) {
    return inCheck;
}

void King::setInCheck(bool kingInCheck) {
    inCheck = kingInCheck;
}

// In main, program must call castle for both rook and king simultaneously.
bool King::castleKingRight(Board &b) {
    if (!firstMove) {
        return false;
    }

    // If the king is in check, castling is invalid.
    if (b.checkIfInCheck(getColour())) {
        return false;
    }

    // Check that there is a rook where you are castling to. 
    if (!b.getPiece(getRow(), 7) || b.getPiece(getRow(), 7)->getState() != PieceType::Rook) {
        return false;
    }

    // Check if there are any Pieces attacking the square beside the King (col + 1).
    if (!checkForCheckPreMove(b, getRow(), getCol() + 1)) {
        return false;
    }

    // Check if there are pieces in between the king and the rook.
    if (b.getPiece(getRow(), getCol() + 1) || b.getPiece(getRow(), getCol() + 2)) {
        return false;
    }

    // Check if the rook can also castle.
    Rook * r;
    r = static_cast<Rook *>(b.getPiece(getRow(), 7));
    return r->castleRookLeft();
    delete r;
}

bool King::castleKingLeft(Board &b) {
    if (!firstMove) {
        return false;
    }

    if (b.checkIfInCheck(getColour())) {
        return false;
    }

    // Check if there is a rook where you are castling to.
    if (!b.getPiece(getRow(), 0) || b.getPiece(getRow(), 0)->getState() != PieceType::Rook) {
        return false;
    }

    // Check if there are any Pieces attacking the square beside the King (col - 1) (col - 3).
    if (!checkForCheckPreMove(b, getRow(), getCol() - 1) ||
        !checkForCheckPreMove(b, getRow(), getCol() - 3)) {
        return false;
    }

    // Check that the squares in between the king and rook are empty.
    if (b.getPiece(getRow(), getCol() - 1) || b.getPiece(getRow(), getCol() - 2) || b.getPiece(getRow(), getCol() - 3)) {
        return false;
    }

    // Check if the rook can also castle.
    Rook * r;
    r = static_cast<Rook *>(b.getPiece(getRow(), 0));
    return r->castleRookRight();
    delete r;
}

void King::placePiece(Board &b, int row, int col) {
    int origRow = getRow();
    int origCol = getCol();
    bool castleRight = false;
    bool castleLeft = false;

    // Moving 2 squares is castling.
    if (origCol - col == -2) {
        castleRight = castleKingRight(b);
    } else if (origCol - col == 2) {
        castleLeft = castleKingLeft(b);
    }

    setCoords(row, col);
    // Place the King in the correct location.
    b.removePiece(row, col);
    b.setPiece(this, row, col);
    b.setPiece(nullptr, origRow, origCol);
    this->notifyObservers();

    // Place the Rook in the correct location.
    if (castleRight) {
        b.getPiece(row, 7)->placePiece(b, row, 5);
    } else if (castleLeft) {
        b.getPiece(row, 0)->placePiece(b, row, 3);
    }

    firstMove = false;
}

vector<vector<int>> King::checkPossibleMoves(Board &b) {
    int row = getRow();
    int col = getCol();
    int boardSize = b.getBoardSize();
    Colour c = getColour();
    Piece * currPiece;
    vector<vector<int>> pieces{};

    if (row + 1 < boardSize) {
        // Check square S of p.
        currPiece = b.getPiece(row + 1, col);
        // Place Piece on square we want to move to before checkAttackingMe.
        if (!currPiece || (currPiece->getColour() != c)) {
            if (checkForCheckPreMove(b, row + 1, col)) {
                pieces.emplace_back(vector <int> {row + 1, col});
            }
        }
         
        // Check square SE of p.
        if (col + 1 < boardSize) {
            currPiece = b.getPiece(row + 1, col + 1);
            if (!currPiece || (currPiece->getColour() != c)) {
                if (checkForCheckPreMove(b, row + 1, col + 1)) {
                    pieces.emplace_back(vector <int> {row + 1, col + 1});
                }
            }
        }
        // Check square SW of p.
        if (col > 0) {
            currPiece = b.getPiece(row + 1, col - 1);
            if (!currPiece || (currPiece->getColour() != c)) {
                if (checkForCheckPreMove(b, row + 1, col - 1)) {
                    pieces.emplace_back(vector <int> {row + 1, col - 1});
                }
            }
        }
    }
    if (row > 0) {
        // Check square N of p.
        currPiece = b.getPiece(row - 1, col);
        if (!currPiece || (currPiece->getColour() != c)) {
            if (checkForCheckPreMove(b, row - 1, col)) {
                pieces.emplace_back(vector <int> {row - 1, col});
            }
        }       
        // Check square NE of p.
        if (col + 1 < boardSize) {
            currPiece = b.getPiece(row - 1, col + 1);
            if (!currPiece || (currPiece->getColour() != c)) {
                if (checkForCheckPreMove(b, row - 1, col + 1)) {
                    pieces.emplace_back(vector <int> {row - 1, col + 1});
                }
            }
        }
        // Check square NW of p.
        if (col > 0) {
            currPiece = b.getPiece(row - 1, col - 1);
            if (!currPiece || (currPiece->getColour() != c)) {
                if (checkForCheckPreMove(b, row - 1, col - 1)) {
                    pieces.emplace_back(vector <int> {row - 1, col - 1});
                }
            }
        }
    }
    // Check square E of p.
    if (col + 1 < boardSize) {
        currPiece = b.getPiece(row, col + 1);
        if (!currPiece || (currPiece->getColour() != c)) {
            if (checkForCheckPreMove(b, row, col + 1)) {
                 pieces.emplace_back(vector <int> {row, col + 1});
            }
        }
    }
    // Check square W of p.
    if (col > 0) {
        currPiece = b.getPiece(row, col - 1);       
        if (!currPiece || (currPiece->getColour() != c)) {
            if (checkForCheckPreMove(b, row, col - 1)) {
                pieces.emplace_back(vector <int> {row, col - 1});
            }
        }
    }

    // Check if castling is possible on either side.
    if (firstMove) {
        if (col + 2 < boardSize) {
            bool validCastleRight = checkMovementValid(b, row, col + 2);

            if (validCastleRight) {
                // Check that castling will not place the friendly King in check.
                currPiece = b.getPiece(row, col + 2);
                b.placePieceTemporarily(row, col, row, col + 2);
                b.placePieceTemporarily(row, 7, row, col + 1);
                if (this->checkAttackingMe(b, row, col + 2, c).size() == 0) {
                    pieces.emplace_back(vector <int> {row, col + 2});
                }
                b.placePieceTemporarily(row, col + 2, row, col);
                b.placePieceTemporarily(row, col + 1, row, 7);
            }
        }

        if (col - 2 > 0) {
            bool validCastleLeft = checkMovementValid(b, row, col - 2);

            if (validCastleLeft) {
                // Check that castling will not place the friendly King in check.
                currPiece = b.getPiece(row, col - 2);
                b.placePieceTemporarily(row, col, row, col - 2);
                b.placePieceTemporarily(row, 0, row, col - 1);
                if (this->checkAttackingMe(b, row, col - 2, c).size() == 0) {
                    pieces.emplace_back(vector <int> {row, col - 2});
                }
                b.placePieceTemporarily(row, col - 2, row, col);
                b.placePieceTemporarily(row, col - 1, row, 0);
            }
        }
    }

    return pieces;
}
