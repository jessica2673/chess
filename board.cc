#include <iostream>
#include "board.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "levelOne.h"
#include "levelTwo.h"
#include "levelThree.h"
#include "levelFour.h"

using namespace std;

Board::Board(): board{}, td{new TextDisplay()} {
    wd = new Xwindow(500, 500);
    gd = new GraphicsDisplay(*wd);
}

Board::~Board() {
    delete whitePlayer;
    delete blackPlayer;
    delete wd;
    delete td;
    delete gd;
}

void Board::clearBoard() {
    for (int i = 0; i < boardSize; ++i) {
        for (int j = 0; j < boardSize; ++j) {
            delete board[i][j];
            td->notify(nullptr, i, j);
            gd->notify(nullptr, i, j);
        }
    }
    whiteKing = nullptr;
    blackKing = nullptr;
    whitePieces.clear();
    blackPieces.clear();
    board.clear(); // Clear the board.
}

void Board::init(){
    board.resize(boardSize, vector<Piece *>(boardSize));
    for (int r = 0; r < boardSize; ++r) {
        board.resize(boardSize);
        for (int c = 0; c < boardSize; ++c) {
            board[r][c] = nullptr; 
        }
    }

    // Setup with default mode.
    placeNewPiece(PieceType::Rook, Colour::WHITE, "a1");
    placeNewPiece(PieceType::Knight, Colour::WHITE, "b1");
    placeNewPiece(PieceType::Bishop, Colour::WHITE, "c1");
    placeNewPiece(PieceType::Queen, Colour::WHITE, "d1");
    placeNewPiece(PieceType::King, Colour::WHITE, "e1");
    placeNewPiece(PieceType::Bishop, Colour::WHITE, "f1");
    placeNewPiece(PieceType::Knight, Colour::WHITE, "g1");
    placeNewPiece(PieceType::Rook, Colour::WHITE, "h1");
    for (int i = 0; i < 8; ++i) {
        placeNewPiece(PieceType::Pawn, Colour::WHITE, 6, i);
    }

    placeNewPiece(PieceType::Rook, Colour::BLACK, "a8");
    placeNewPiece(PieceType::Knight, Colour::BLACK, "b8");
    placeNewPiece(PieceType::Bishop, Colour::BLACK, "c8");
    placeNewPiece(PieceType::Queen, Colour::BLACK, "d8");
    placeNewPiece(PieceType::King, Colour::BLACK, "e8");
    placeNewPiece(PieceType::Bishop, Colour::BLACK, "f8");
    placeNewPiece(PieceType::Knight, Colour::BLACK, "g8");
    placeNewPiece(PieceType::Rook, Colour::BLACK, "h8");
    for (int i = 0; i < 8; ++i) {
        placeNewPiece(PieceType::Pawn, Colour::BLACK, 1, i);
    }
}

void Board::initEmpty() {

    board.resize(boardSize, vector<Piece *>(boardSize));
    for (int r = 0; r < boardSize; ++r) {
        board.resize(boardSize);
        for (int c = 0; c < boardSize; ++c) {
            board[r][c] = nullptr; 
        }
    }
}

int Board::getBoardSize() const {
    return boardSize;
}

Piece* Board::getPiece(int row, int col) const {
    return board[row][col];
}

void Board::setPiece(Piece * p, int row, int col) {
    board[row][col] = p;

    if (!p) {
        td->notify(nullptr, row, col);
        gd->notify(nullptr, row, col);
    }
}

vector<int> Board::getLastMove() const {
    return lastMove;
}

void Board::setLastMove(int origRow, int origCol, int newRow, int newCol) {
    // Sets the last move vector with this format: {origRow, origCol, newRow, newCol}.
    lastMove[0] = origRow; // Sets first value to the original row of the last move.
    lastMove[1] = origCol; // Sets second value to the original column of the last move.
    lastMove[2] = newRow; // Sets third value to the new row of the last move. 
    lastMove[3] = newCol; // Sets fourth value to the new col of the last move.
}

King * Board::getWhiteKing() const {
    return whiteKing;
}

void Board::setWhiteKing(King * whiteKing) {
    this->whiteKing = whiteKing;
}

King * Board::getBlackKing() const {
    return blackKing;
}

void Board::setBlackKing(King * blackKing) {
    this->blackKing = blackKing;
}

bool Board::setWhitePlayer(string level) {
    // Set the appropriate White player type based on input where human is a Player,
    // computer[1] is a LevelOne computer, computer[2] is a LevelTwo computer, 
    // computer[3] is a LevelThree computer, computer[4] is a LevelFour computer.
    if (level == "human") {
        whitePlayer = new Player(Colour::WHITE);
        return false;
    } else if (level == "computer[1]") {
        whitePlayer = new LevelOne(Colour::WHITE);
        return true;
    } else if (level == "computer[2]") {
        whitePlayer = new LevelTwo(Colour::WHITE); 
        return true;
    } else if (level == "computer[3]") {
        whitePlayer = new LevelThree(Colour::WHITE); 
        return true;
    } else if (level == "computer[4]") {
        whitePlayer = new LevelFour(Colour::WHITE); 
        return true;
    } else {
        throw std::invalid_argument{"Not a valid player."};
    }
    return true;
}

bool Board::setBlackPlayer(string level) {
    // Set the appropriate Black player type based on input.
    if (level == "human") {
        blackPlayer = new Player(Colour::BLACK);
        return false;
    } else if (level == "computer[1]") {
        blackPlayer = new LevelOne(Colour::BLACK);
        return true;
    } else if (level == "computer[2]") {
        blackPlayer = new LevelTwo(Colour::BLACK); 
        return true;
    } else if (level == "computer[3]") {
        blackPlayer = new LevelThree(Colour::BLACK); 
        return true;
    } else if (level == "computer[4]") {
        blackPlayer = new LevelFour(Colour::BLACK); 
        return true;
    } else {
        throw std::invalid_argument{"Not a valid player."};
    }
    return true;
}

vector<Piece *> Board::getWhitePieces() const {
    return whitePieces;
}

vector<Piece *> Board::getBlackPieces() const {
    return blackPieces;
}

bool Board::sameColourSquare(Piece * first, Piece * second) {
    // If the sum of the row and column is odd, it is a white square.
    // If even, it is a white square.
    int whiteSquareColour = (first->getRow() + first->getCol()) % 2;
    int blackSquareColour = (second->getRow() + second->getCol()) % 2;

    // If the two squares have the same colour, return true.
    if (whiteSquareColour == blackSquareColour) {
        return true;
    }
    return false;
}

PieceType Board::convertStrToPiecetype(string type) {
    if (type == "K" || type == "k") {
        return PieceType::King;
    } else if (type == "Q" || type == "q") {
        return PieceType::Queen;
    } else if (type == "B" || type == "b") {
        return PieceType::Bishop;
    } else if (type == "N" || type == "n") {
        return PieceType::Knight;
    } else if (type == "R" || type == "r") {
        return PieceType::Rook;
    } else if (type == "P" || type == "p") {
        return PieceType::Pawn;
    } else {
        throw std::invalid_argument{"Not a valid piece."};
    }
}

int Board::convertLetterToIndex(string letter) {
    if (letter == "a") {
        return 0;
    } else if (letter == "b") {
        return 1;
    } else if (letter == "c") {
        return 2;
    } else if (letter == "d") {
        return 3;
    } else if (letter == "e") {
        return 4;
    } else if (letter == "f") {
        return 5;
    } else if (letter == "g") {
        return 6;
    } else if (letter == "h") {
        return 7;
    } else {
        return -1;
    }
}

vector<int> Board::convertStrToCoords(string location) {

    // if location is empty, that means it's computer's move
    if (location.empty()) return vector<int>{-1, -1};

    string strCol = location.substr(0, 1);
    int col = convertLetterToIndex(strCol);

    // Converting string to int.
    istringstream iss{location.substr(1, 2)};
    int row;
    iss >> row;
    row = 8 - row;

    // If the location's coordinates are out of bounds, it is not a valid coordinate.
    if (row < 0 || row >= 8) {
        throw std::invalid_argument{"Not a valid row."};
    } else if (col == -1) {
        throw std::invalid_argument{"Not a valid column."}; 
    }

    return vector <int> {row, col};
}

bool Board::validBoardSetup() {
    // Check the board contains exactly one white King and exactly one black King.
    if (!whiteKing) {
        throw std::domain_error{"There is not a white King on the board. Try again."};
    } else if (!blackKing) {
        throw std::domain_error{"There is not a black King on the board. Try again."};
    }
    // Check that no pawns are on the first or last row of the board.
    for (int c = 0; c < boardSize; ++c) {
        if (getPiece(0, c) && getPiece(0, c)->getState() == PieceType::Pawn) {
            throw std::domain_error{"There is a Pawn on the last row of the board. Try again."};
        } else if (getPiece(boardSize - 1, c) && getPiece(boardSize - 1, c)->getState() == PieceType::Pawn) {
            throw std::domain_error{"There is a Pawn on the first row of the board. Try again."};
        }
    }

    // Check that none of the Kings are in check.
    if (checkIfInCheck(Colour::WHITE)) {
        throw std::domain_error{"The white King is in check. Try again."};
    } else if (checkIfInCheck(Colour::BLACK)) {
        throw std::domain_error{"The black King is in check. Try again."};
    }

    return true;
}

bool Board::checkValid(int origRow, int origCol, int newRow, int newCol, bool calledByPlayer) {
    // Check that new location is within range of the board.
    if (newRow < 0 || newRow >= boardSize || newCol < 0 || newCol >= boardSize) return false; 

    // Check that we are not an empty Piece.
    if (board[origRow][origCol] == nullptr) {  
        return false;
    }

    // If we have a Piece of our team on the square, we cannot move there.
    if ((board[newRow][newCol]) && board[origRow][origCol]->getColour() == board[newRow][newCol]->getColour()) {
        return false;
    }

    // Check that the move does not put the King in check.
    if (!board[origRow][origCol]->checkForCheckPreMove(*this, newRow, newCol)) {
        return false;
    }

    // Call the specific Piece's checkMovementValid function to verify that it can move there.
    if (!(board[origRow][origCol]->checkMovementValid(*this, newRow, newCol, calledByPlayer))) {
        return false;
    }
    
    return true;
}

bool Board::checkIfInCheck(Colour c) {
    // Check if Black King is in check.
    if (c == Colour::BLACK) {
        vector <Piece *> attackers = blackKing->checkAttackingMe(*this, blackKing->getRow(), blackKing->getCol(), blackKing->getColour());
        if (attackers.size() > 0) { // in check
            blackKing->setInCheck(true);
            return true;
        } else {
            blackKing->setInCheck(false);
            return false;
        }
    }
    // Check if White King is in check.
    vector <Piece *> attackers = whiteKing->checkAttackingMe(*this, whiteKing->getRow(), whiteKing->getCol(), whiteKing->getColour());
    if (attackers.size() > 0) {
        whiteKing->setInCheck(true);
        return true;
    } else {
        whiteKing->setInCheck(false);
        return false;
    }
}

bool Board::checkForCheckmate(Colour colour) {
    // Set friendly and opponent Pieces.
    King * king;
    vector <Piece *> myPieces;

    if (colour == Colour::WHITE) {
        king = whiteKing;
        myPieces = getWhitePieces();
    } else {
        king = blackKing;
        myPieces = getBlackPieces();
    }

    int kingRow = king->getRow();
    int kingCol = king->getCol();

    // Obtain all the Pieces attacking the friendly King.
    vector <Piece *> attackers = king->checkAttackingMe(*this, kingRow, kingCol, colour);

    // Return false if there is at least one possible move.
    if (attackers.size() == 1) {
        // Get the Pieces which may capture the Piece attacking the King.
        for (Piece * defender:myPieces) {
            // If the defender can legally capture the attacking Piece, it is not checkmate.
            if (checkValid(defender->getRow(), defender->getCol(), attackers[0]->getRow(), attackers[0]->getCol())) {
                return false;
            }
        }

        // Check if there's a Piece of own team that can block the attack. This case is only applicable if 
        // only one Piece is checking the King. Only Queen, Bishop, and Rook attacks can be blocked.
        if ((attackers[0]->getState() == PieceType::Queen) || 
            (attackers[0]->getState() == PieceType::Bishop) || 
            (attackers[0]->getState() == PieceType::Rook)) {
            
            // Loop through all the squares between the King and attacking Piece.
            // Check if any Piece on your own team can move to one of these squares through checkAttackingMe of opposite Colour.
            // Checks are done from attacking King to attacking Piece.
            
            int attackerRow = attackers[0]->getRow();
            int attackerCol = attackers[0]->getCol();
            int r = kingRow;
            int c = kingCol;

            // If attacking Piece is N of King.
            r = kingRow - 1;
            c = kingCol;

            // Loop through all the squares in between the attacking Piece and the King.
            while (r > attackerRow && c == attackerCol) {
                for (Piece * p:myPieces) {
                    // Check if any friendly Pieces can move to that square.
                    if (checkValid(p->getRow(), p->getCol(), r, c)) {
                        return false;
                    }
                }
                r--;
            }

            // If attacking Piece is NE of King.
            r = kingRow - 1;
            c = kingCol + 1;
            while (r > attackerRow && c < attackerCol) {
                for (Piece * p:myPieces) {
                    if (checkValid(p->getRow(), p->getCol(), r, c)) {
                        return false;
                    }
                }
                r--;
                c++;
            }

            // If attacking Piece is E of King.
            r = kingRow;
            c = kingCol + 1;
            while (r == attackerRow && c < attackerCol) {
                for (Piece * p:myPieces) {
                    if (checkValid(p->getRow(), p->getCol(), r, c)) {
                        return false;
                    }
                }
                c++;
            }

            // If attacking Piece is SE of King.
            r = kingRow + 1;
            c = kingCol + 1;
            while (r < attackerRow && c < attackerCol) {
                for (Piece * p:myPieces) {
                    if (checkValid(p->getRow(), p->getCol(), r, c)) {
                        return false;
                    }
                }
                r++;
                c++;
            }

            // If attacking Piece is S of King.
            r = kingRow + 1;
            c = kingCol;
            while (r < attackerRow && c == attackerCol) {
                for (Piece * p:myPieces) {
                    if (checkValid(p->getRow(), p->getCol(), r, c)) {
                        return false;
                    }
                }
                r++;
            }

            // If attacking Piece is SW of King.
            r = kingRow + 1;
            c = kingCol - 1;
            while (r < attackerRow && c > attackerCol) {
                for (Piece * p:myPieces) {
                    if (checkValid(p->getRow(), p->getCol(), r, c)) {
                        return false;
                    }
                }
                r++;
                c--;
            }

            // If attacking Piece is W of King.
            r = kingRow;
            c = kingCol - 1;
            while (r == attackerRow && c > attackerCol) {
                for (Piece * p:myPieces) {
                    if (checkValid(p->getRow(), p->getCol(), r, c)) {
                        return false;
                    }
                }
                c--;
            }

            // If attacking Piece is NW of King.
            r = kingRow - 1;
            c = kingCol - 1;
            while (r > attackerRow && c > attackerCol) {
                for (Piece * p:myPieces) {
                    if (checkValid(p->getRow(), p->getCol(), r, c)) {
                        return false;
                    }
                }
                r--;
                c--;
            }
        }        
    }

    // Check if the King can move out of check by moving to a square beside it.
    // Check N of king.
    if (checkValid(kingRow, kingCol, kingRow - 1, kingCol)) {
        return false;
    }
    // Check NE of king.
    if (checkValid(kingRow, kingCol, kingRow - 1, kingCol + 1)) {
        return false;
    }
    // Check E of king.
    if (checkValid(kingRow, kingCol, kingRow, kingCol + 1)) {
        return false;
    }
    // Check SE of king.
    if (checkValid(kingRow, kingCol, kingRow + 1, kingCol + 1)) {
        return false;
    }
    // Check S of king.
    if (checkValid(kingRow, kingCol, kingRow + 1, kingCol)) {
        return false;
    }
    // Check SW of king.
    if (checkValid(kingRow, kingCol, kingRow + 1, kingCol - 1)) {
        return false;
    }
    // Check W of king.
    if (checkValid(kingRow, kingCol, kingRow, kingCol - 1)) {
        return false;
    }
    // Check NW of king.
    if (checkValid(kingRow, kingCol, kingRow - 1, kingCol - 1)) {
        return false;
    }

    return true;
}

bool Board::checkForStalemate(bool whiteTurn) {
    // Check combinations of Pieces that result in checkmate.
    if (whitePieces.size() == 1 && blackPieces.size() == 1) {
        return true;
    }

    // Check King vs Knight/Bishop and King.
    if (whitePieces.size() == 2 && blackPieces.size() == 1) {
        if (whitePieces[1]->getState() == PieceType::Bishop || whitePieces[0]->getState() == PieceType::Bishop) {
            return true;
        } else if (whitePieces[1]->getState() == PieceType::Knight || whitePieces[0]->getState() == PieceType::Knight) {
            return true;
        }
    }

    if (whitePieces.size() == 1 && blackPieces.size() == 2) {
        if (blackPieces[1]->getState() == PieceType::Bishop || blackPieces[0]->getState() == PieceType::Bishop) {
            return true;
        } else if (blackPieces[1]->getState() == PieceType::Knight || blackPieces[0]->getState() == PieceType::Knight) {
            return true;
        }
    }

    // King and Bishop vs King and Bishop on different color square as opponent's Bishop.
    if (whitePieces.size() == 2 && blackPieces.size() == 2) {
        if ((whitePieces[0]->getState() == PieceType::Bishop && blackPieces[0]->getState() == PieceType::Bishop)) {
            if (!sameColourSquare(whitePieces[0], blackPieces[0])) {
                return true;
            }
        } else if ((whitePieces[0]->getState() == PieceType::Bishop && blackPieces[1]->getState() == PieceType::Bishop)) {
            if (!sameColourSquare(whitePieces[0], blackPieces[1])) {
                return true;
            }
        } else if ((whitePieces[1]->getState() == PieceType::Bishop && blackPieces[0]->getState() == PieceType::Bishop)) {
            if (!sameColourSquare(whitePieces[1], blackPieces[0])) {
                return true;
            }
        } else if ((whitePieces[1]->getState() == PieceType::Bishop && blackPieces[1]->getState() == PieceType::Bishop)) {
            if (!sameColourSquare(whitePieces[1], blackPieces[1])) {
                return true;
            }
        }
    }

    // If there is at least one possible move, it is not stalemate.
    if (whiteTurn) {
        for (Piece * p: whitePieces) {
            if (p->checkPossibleMoves(*this).size() > 0) {
                return false;
            }
        }
    }
    
    if (!whiteTurn) {
        for (Piece * p: blackPieces) {
            if (p->checkPossibleMoves(*this).size() > 0) {
                return false;
            }
        }
    }

    return true;
}

void Board::placeNewPiece(string type, string location) {

    if (type == "K") {
        placeNewPiece(PieceType::King, Colour::WHITE, location);
    } else if (type == "k") {
        placeNewPiece(PieceType::King, Colour::BLACK, location);
    } else if (type == "Q") {
        placeNewPiece(PieceType::Queen, Colour::WHITE, location);
    } else if (type == "q") {
        placeNewPiece(PieceType::Queen, Colour::BLACK, location);
    } else if (type == "B") { 
        placeNewPiece(PieceType::Bishop, Colour::WHITE, location);
    } else if (type == "b") {
        placeNewPiece(PieceType::Bishop, Colour::BLACK, location);
    } else if (type == "N") {
        placeNewPiece(PieceType::Knight, Colour::WHITE, location);
    } else if (type == "n") {
        placeNewPiece(PieceType::Knight, Colour::BLACK, location);
    } else if (type == "R") {
        placeNewPiece(PieceType::Rook, Colour::WHITE, location);
    } else if (type == "r") {
        placeNewPiece(PieceType::Rook, Colour::BLACK, location);
    } else if (type == "P") {
        placeNewPiece(PieceType::Pawn, Colour::WHITE, location);
    } else if (type == "p") {
        placeNewPiece(PieceType::Pawn, Colour::BLACK, location);
    }
}

void Board::placeNewPiece(PieceType type, Colour colour, int row, int col) {
    Piece * p;

    // Create a new Piece of specified type of Colour.
    if (type == PieceType::King) {
        King * k = new King(colour);
        p = k;
        if (colour == Colour::BLACK) {
            setBlackKing(k);
        } else {
            setWhiteKing(k);
        }
    } else if (type == PieceType::Queen) {
        p = new Queen(colour);
    } else if (type == PieceType::Bishop) {
        p = new Bishop(colour);
    } else if (type == PieceType::Knight) {
        p = new Knight(colour);
    } else if (type == PieceType::Rook) {
        p = new Rook(colour);
    } else if (type == PieceType::Pawn) {
        p = new Pawn(colour);
    }

    // Attach the Piece to the displays as an Observer.
    p->attach(td);
    p->attach(gd);

    // Replace whatever was currently at (row, col) in the board with the new Piece.
    delete board[row][col];
    board[row][col] = p;
    p->setCoords(row, col);
    p->notifyObservers();

    // Add the new Piece to the vector of Pieces.
    if (colour == Colour::WHITE) {
        whitePieces.emplace_back(p);
    } else {
        blackPieces.emplace_back(p);
    }
}

void Board::placeNewPiece(PieceType type, Colour colour, string location) {
    // Convert the location to a vector of coordinates.
    vector <int> coords = convertStrToCoords(location);

    int row = coords[0];
    int col = coords[1];

    // Place the Piece with the location as integers.
    placeNewPiece(type, colour, row, col);
}

void Board::placeNewPiece(string pieceType, Colour colour, string location) {
    PieceType type;

    // Create a new Piece based on the PieceType.
    if (pieceType == "K" || pieceType == "k") {
        type = PieceType::King;
    } else if (pieceType == "Q" || pieceType == "q") {
        type = PieceType::Queen;
    } else if (pieceType == "B" || pieceType == "b") {
        type = PieceType::Bishop;
    } else if (pieceType == "N" || pieceType == "n") {
        type = PieceType::Knight;
    } else if (pieceType == "R" || pieceType == "r") {
        type = PieceType::Rook;
    }

    // Place the Piece given the PieceType, colour, and location.
    placeNewPiece(type, colour, location);
}

void Board::placePieceTemporarily(int origRow, int origCol, int newRow, int newCol) {
    if (board[origRow][origCol]) {
        board[origRow][origCol]->setCoords(newRow, newCol);
    }

    // Remove what was originally in board[row][col]
    board[newRow][newCol] = nullptr;

    // Reassign it to new Piece.
    board[newRow][newCol] = board[origRow][origCol];

    // Assign original Piece to empty.
    board[origRow][origCol] = nullptr;
}

void Board::removePiece(string location) {

    vector <int> posToRemove = convertStrToCoords(location);
    int row = posToRemove[0];
    int col = posToRemove[1];

    removePiece(row, col);
}

void Board::removePiece(int row, int col) {
    // If there is a piece at row, col, remove it from whitePieces or blackPieces vector.
    if (getPiece(row, col)) {
        if (getPiece(row, col)->getColour() == Colour::WHITE) {
            for (int i = 0; i < whitePieces.size(); ++i) {
                // Find the White Piece to be removed.
                if (whitePieces[i] == board[row][col]) {
                    // Use an iterator to find the Piece in the vector and erase it.
                    for (auto it = whitePieces.begin(); it != whitePieces.end(); ++it) {
                        if (*it == whitePieces[i]) {
                            whitePieces.erase(it);
                            break;
                        }
                    }
                }
            }
        } else {
            for (int i = 0; i < blackPieces.size(); ++i) {
                // Find the Black Piece to be removed.
                if (blackPieces[i] == board[row][col]) {
                    // Use an iterator to find the Piece in the vector and erase it.
                    for (auto it = blackPieces.begin(); it != blackPieces.end(); ++it) {
                        if (*it == blackPieces[i]) {
                            blackPieces.erase(it);
                            break;
                        }
                    }
                }
            }
        }
    }

    // Delete the Piece from the board, and notify the displays.
    delete board[row][col];
    board[row][col] = nullptr;
    td->notify(nullptr, row, col);
    gd->notify(nullptr, row, col);
}

bool Board::boardMakeMove(bool whiteTurn, string origLocation, string newLocation) {
    // Convert the string locations to integer vectors as (row, col).
    vector <int> origCoords = convertStrToCoords(origLocation);
    vector <int> newCoords = convertStrToCoords(newLocation);

    // If the move is valid, make it and return true.
    if (whiteTurn) {
        if (whitePlayer->makeMove(*this, whiteTurn, origCoords[0], origCoords[1], newCoords[0], newCoords[1])) {
            return true; 
        }
    } else {
        if (blackPlayer->makeMove(*this, whiteTurn, origCoords[0], origCoords[1], newCoords[0], newCoords[1])) {
            return true;
        }
    }

    return false;
}

void Board::promotePiece(bool whiteTurn, string origLocation, string newLocation, string newPieceType) {
    // Remove the Pawn at the original location.
    removePiece(origLocation);

    // Place a new Piece based on the Piece we are promoting to on the board.
    if (whiteTurn && (newPieceType == "Q" || newPieceType == "B" || newPieceType == "N" || newPieceType == "R")) {
        placeNewPiece(newPieceType, Colour::WHITE, newLocation);
    } else if (!whiteTurn && (newPieceType == "q" || newPieceType == "b" || newPieceType == "n" || newPieceType == "r")) {
        placeNewPiece(newPieceType, Colour::BLACK, newLocation);
    }
}

void Board::promotePiece(bool whiteTurn, int row, int col, PieceType pieceType) {
    removePiece(row, col);

    if (whiteTurn) {
        // Creates a new Piece with PieceType type, Colour colour, int row, int col.
        placeNewPiece(pieceType, Colour::WHITE, row, col);
    } else {
        placeNewPiece(pieceType, Colour::BLACK, row, col);
    }
}

ostream &operator<<(std::ostream &out, const Board &b) {
    out << *(b.td);
    return out;
}
