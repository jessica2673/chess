#include <vector>
#include "piece.h"

using namespace std;

Piece::Piece(Colour colour, PieceType type):
    colour{colour}, type{type} {}

Piece::Piece(int row, int col, PieceType type, Colour colour):
    row{row}, col{col}, type{type}, colour{colour} {} // Default constructor

// Returns thex value of row.
int Piece::getRow() const {
    return row;
}

// Returns the value of col.
int Piece::getCol() const {
    return col;
} 

void Piece::setRow(int r) {
    row = r;
}

void Piece::setCol(int c) {
    col = c;
}

PieceType Piece::getState() const {
    return type;
}

Colour Piece::getColour() const {
    return colour;
}

void Piece::setCoords(int r, int c) {  
    row = r;
    col = c;
}  

void Piece::attach(Observer *o) {
    observers.emplace_back(o);
}  // Attaches observers (TextDisplay and GraphicDisplay)

// Piece will call this to let observers TextDisplay and GraphicDisplay know that they've moved so that the displays can update accordingly 
void Piece::notifyObservers() {
    for (auto p: observers) {
        p->notify(this, getRow(), getCol());
	}
}

bool Piece::checkDiagonal(Board &b, int newRow, int newCol) {
    int rise = newRow - row;
    int run = newCol - col;
    int boardSize = b.getBoardSize();

    // Check that the path of the bishop is either y = x or y = -x.
    if (abs(rise) != abs(run)) {
        return false;
    }
    
    // Check SE direction.
    if (rise > 0 && run > 0) {
        for (int i = 1; i < rise && newRow + i < boardSize && newCol + i < boardSize; ++i) {
            if (!b.getPiece(row + i, col + i)) {
                return false;
            }
        }
    } 
    // Check NW direction.
    else if (rise < 0 && run < 0) {
        for (int i = 1; i < rise && newRow - i > 0 && newCol - i > 0; ++i) {
            if (b.getPiece(row - i, col - i) != nullptr) {
                return false;
            }
        }
    } 
    // Check NE direction.
    else if (rise < 0 && run > 0) {
        for (int i = 1; i < rise && newRow - i > 0 && newCol + i < boardSize; ++i) {
            if (b.getPiece(row - i, col + i) != nullptr) {
                return false;
            }
        }
    } 
    // Check SE direction.
    else {
        for (int i = 1; i < rise && newRow + i < boardSize && newCol - i > 0; ++i) {
            if (b.getPiece(row + i, col - i)) {
                return false;
            }
        }
    }

    // If there is nothing in the way, return true.
    return true;
}

bool Piece::checkHorizontalVertical(const Board &b, int newRow, int newCol) {
    int rise = newRow - row; // Rise is positive when you are moving down.
    int run = newCol - col;  // Run is positive when you are moving right.

    if ((abs(rise) > 0) && (abs(run) > 0)) { // Cannot move both on row and column simultaneously.
        return false;
    }
    
    if (run == 0 && rise > 0) {  // Checking vertical down.
        for (int i = 1; i < rise; ++i) {
            if (b.getPiece(row + i, col)) return false; // Piece found.
        }
    } else if (run == 0 && rise < 0) {  // Checking vertical up.
        for (int i = 1; i < abs(rise); ++i) {
            if (b.getPiece(row - i, col)) return false;
        }
    } else if (rise == 0 && run > 0) {  // Checking horizontal right.
        for (int i = 1; i < run; ++i) {
            if (b.getPiece(row, col + i)) return false;
        }
    } else if (rise == 0 && run < 0) {  // Checking horizontal left.
        for (int i = 1; i < abs(run); ++i) {
            if (b.getPiece(row, col - i)) return false;
        }
    }

    return true;
}

bool Piece::checkForCheckPreMove(Board &b, int newRow, int newCol) {
    int origRow = getRow();
    int origCol = getCol();
    Colour c = getColour();

    // Check if there are Pieces that attack king in the new position.
    Piece * attacking = b.getPiece(newRow, newCol); // Keep track of what we are temporarily removing.
    b.placePieceTemporarily(origRow, origCol, newRow, newCol);
    if (b.checkIfInCheck(c)) {
        b.placePieceTemporarily(newRow, newCol, origRow, origCol);
        b.setPiece(attacking, newRow, newCol);
        return false;
    }
     // Return Piece to original square.
    b.placePieceTemporarily(newRow, newCol, origRow, origCol);
    b.setPiece(attacking, newRow, newCol);

    return true;
}

void Piece::capturePiece(Board &b, int captureRow, int captureCol) {
    b.removePiece(captureRow, captureRow);
    // delete b.getPiece(captureRow, captureCol);
    // notifyObserversCapture(captureRow, captureCol);
}

void Piece::placePiece(Board & b, int row, int col) {
    int origRow = this->row;
    int origCol = this->col;
    setCoords(row, col);
    b.removePiece(row, col);
    b.setPiece(this, row, col);
    b.setPiece(nullptr, origRow, origCol);

    // b.removePiece(origRow, origCol);
    this->notifyObservers();
}

vector<Piece *> Piece::checkAttackingMe(const Board &b, int row, int col, Colour c) {
    vector<Piece *> pieces{};
    int boardSize = b.getBoardSize();
    Piece * currPiece;
    Piece * p;
    
    // Check diagonals and rows/columns for the first Queen, Rook, or Bishop or opposite Colour.
    int tempR = row - 1;
    int tempC = col;

    // Check N
    while (tempR >= 0) {
        p = b.getPiece(tempR, tempC);
        if (p && p->getColour() == getColour()) {
            break;
        } else if (p) {  // enemy piece
            if (p->getState() == PieceType::Queen || p->getState() == PieceType::Rook) {
                pieces.emplace_back(p);
            }
            break;
        }
        --tempR;
    }

    // Check E
    tempR = row;
    tempC = col + 1;
    while (tempC < boardSize) {
        p = b.getPiece(tempR, tempC);
        if (p && p->getColour() == getColour()) {
            break;
        } else if (p) {  // enemy piece
            if (p->getState() == PieceType::Queen || p->getState() == PieceType::Rook) {
                pieces.emplace_back(p);
            }
            break;
        }
        ++tempC;
    }

    // Check S
    tempR = row + 1;
    tempC = col;
    while (tempR < boardSize) {
        p = b.getPiece(tempR, tempC);
        if (p && p->getColour() == getColour()) {
            break;
        } else if (p) {  // enemy piece
            if (p->getState() == PieceType::Queen || p->getState() == PieceType::Rook) {
                pieces.emplace_back(p);
            }
            break;
        }
        ++tempR;
    }

    // Check W
    tempR = row;
    tempC = col - 1;
    while (tempC >= 0) {
        p = b.getPiece(tempR, tempC);
        if (p && p->getColour() == getColour()) {
            break;
        } else if (p) {  // enemy piece
            if (p->getState() == PieceType::Queen || p->getState() == PieceType::Rook) {
                pieces.emplace_back(p);
            }
            break;
        }
        --tempC;
    }

    // Check NE
    tempR = row - 1;
    tempC = col + 1;
    while (tempR >= 0 && tempC < boardSize) {
        p = b.getPiece(tempR, tempC);
        if (p && p->getColour() == getColour()) {
            break;
        } else if (p) {  // enemy piece
            if (p->getState() == PieceType::Queen || p->getState() == PieceType::Bishop) {
                pieces.emplace_back(p);
            }
            break;
        }
        --tempR;
        ++tempC;
    }


    // Check SE
    tempR = row + 1;
    tempC = col + 1;
    while (tempR < boardSize && tempC < boardSize) {
        p = b.getPiece(tempR, tempC);
        if (p && p->getColour() == getColour()) {
            break;
        } else if (p) {  // enemy piece
            if (p->getState() == PieceType::Queen || p->getState() == PieceType::Bishop) {
                pieces.emplace_back(p);
            }
            break;
        }
        ++tempR;
        ++tempC;
    }

    // Check SW
    tempR = row + 1;
    tempC = col - 1;

    while (tempC >= 0 && tempR < boardSize) {
        p = b.getPiece(tempR, tempC);
        if (p && p->getColour() == getColour()) {
            break;
        } else if (p) {  // enemy piece
            if (p->getState() == PieceType::Queen || p->getState() == PieceType::Bishop) {
                pieces.emplace_back(p);
            }
            break;
        }
        ++tempR;
        --tempC;
    }

    // Check NW
    tempR = row - 1;
    tempC = col - 1;
    while (tempC >= 0 && tempR >= 0) {
        p = b.getPiece(tempR, tempC);
        if (p && p->getColour() == getColour()) {
            break;
        } else if (p) {  // enemy piece
            if (p->getState() == PieceType::Queen || p->getState() == PieceType::Bishop) {
                pieces.emplace_back(p);
            }
            break;
        }
        --tempR;
        --tempC;
    }

    // Check for Pawns where White moves up the board and Black moves down.
    if (c == Colour::WHITE && row > 0) {
        if (col > 0) { // Check that there is a column to the left of you.
            // Check if there is a Piece NW of current Piece, and it is a Black Pawn.
            if (b.getPiece(row - 1, col - 1) && (b.getPiece(row - 1, col - 1)->getState() == PieceType::Pawn) && (b.getPiece(row - 1, col - 1)->getColour() == Colour::BLACK)) {
                pieces.emplace_back(b.getPiece(row - 1, col - 1));
            }
        }
        if (col + 1 < boardSize) { // Check that there is a column to the right of you.
            // Check if there is a Piece NE of current Piece, and it is a Black Pawn.
            if (b.getPiece(row - 1, col + 1) && (b.getPiece(row - 1, col + 1)->getState() == PieceType::Pawn) && (b.getPiece(row - 1, col + 1)->getColour() == Colour::BLACK)) {
                pieces.emplace_back(b.getPiece(row - 1, col + 1));
            }
        }
    } else if (row + 1 < boardSize) {
        if (col > 0) { // Check that there is a column to the left of you.
            // Check if there is a Piece SW of current Piece, and it is a White Pawn.
            if (b.getPiece(row + 1, col - 1) && (b.getPiece(row + 1, col - 1)->getState() == PieceType::Pawn) && (b.getPiece(row + 1, col - 1)->getColour() == Colour::WHITE)) {
                pieces.emplace_back(b.getPiece(row + 1, col - 1));
            }
        }
        if (col + 1 < boardSize) { // Check that there is a column to the right of you.
            // Check if there is a Piece SE of current Piece, and it is a White Pawn.
            if (b.getPiece(row + 1, col + 1) && (b.getPiece(row + 1, col + 1)->getState() == PieceType::Pawn) && (b.getPiece(row + 1, col + 1)->getColour() == Colour::WHITE)) {
                pieces.emplace_back(b.getPiece(row + 1, col + 1));
            }
        }
    }

    // Check for King.
    if (row + 1 < boardSize) {
        // Check S of p.
        currPiece = b.getPiece(row + 1, col);
        if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::King)) {
            pieces.emplace_back(currPiece);
        }
        // Check SE of p.
        if (col + 1 < boardSize) {
            currPiece = b.getPiece(row + 1, col + 1);
            if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::King)) {
                pieces.emplace_back(currPiece);
            }
        }
        // Check SW of p.
        if (col > 0) {
            currPiece = b.getPiece(row + 1, col - 1);
            if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::King)) {
                pieces.emplace_back(currPiece);
            }
        }
    }
    if (row > 0) {
        // Check N of p.
        currPiece = b.getPiece(row - 1, col);
        if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::King)) {
            pieces.emplace_back(currPiece);
        }
        // Check NE of p.
        if (col + 1 < boardSize) {
            currPiece = b.getPiece(row - 1, col + 1);
            if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::King)) {
                pieces.emplace_back(currPiece);
            }
        }
        // Check NW of p.
        if (col > 0) {
            currPiece = b.getPiece(row - 1, col - 1);
            if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::King)) {
                pieces.emplace_back(currPiece);
            }
        }
    }
    // Check E of p.
    if (col + 1 < boardSize) {
        currPiece = b.getPiece(row, col + 1);
        if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::King)) {
                pieces.emplace_back(currPiece);
            }
    }
    // Check W of p.
    if (col > 0) {
        currPiece = b.getPiece(row, col - 1);
        if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::King)) {
            pieces.emplace_back(currPiece);
        }
    }

    // Check Knights.
    // Check top-most two.
    if (row >= 2) {
        if (col + 1 < boardSize) {
            currPiece = b.getPiece(row - 2, col + 1);
            if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::Knight)) {
                pieces.emplace_back(currPiece);
            }
        }
        if (col > 0) {
            currPiece = b.getPiece(row - 2, col - 1);
            if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::Knight)) {
                pieces.emplace_back(currPiece);
            }
        }
    }
    // Check right-most two.
    if (col + 2 < boardSize) {  // we are in the 5 leftmost cols
        if (row + 1 < boardSize) {
            currPiece = b.getPiece(row + 1, col + 2);
            if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::Knight)) {
                pieces.emplace_back(currPiece);
            }
        }
        if (row > 0) {  // we are not in top row
            currPiece = b.getPiece(row - 1, col + 2);
            if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::Knight)) {
                pieces.emplace_back(currPiece);
            }
        }
    }
    // Check bottom-most two.
    if (row + 2 < boardSize) {  // top 5 rows
        if (col + 1 < boardSize) {
            currPiece = b.getPiece(row + 2, col + 1);
            if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::Knight)) {
                pieces.emplace_back(currPiece);
            }
        }
        if (col > 0) {  // we are not in leftmost col
            currPiece = b.getPiece(row + 2, col - 1);
            if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::Knight)) {
                pieces.emplace_back(currPiece);
            }
        }
    }
    //Check left-most two.
    if (col >= 2) {
        if (row + 1 < boardSize) {
            currPiece = b.getPiece(row + 1, col - 2);
            if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::Knight)) {
                pieces.emplace_back(currPiece);
            }
        }
        if (row > 0) {
            currPiece = b.getPiece(row - 1, col - 2);
            if (currPiece && (currPiece->getColour() != c) && (currPiece->getState() == PieceType::Knight)) {
                pieces.emplace_back(currPiece);
            }
        }
    }

    return pieces;
}

vector<vector<int>> Piece::checkEnPassantMoves(Board &b) {
    return vector<vector<int>>{{-1,-1}};
}

bool Piece::checkForPromotion(int row) {
    return false;
}


Piece::~Piece() {

}

