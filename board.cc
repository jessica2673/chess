#include <iostream>
#include "board.h"
using namespace std;

Board::Board(): board{}, won{false}, td{new TextDisplay()} {}

Board::~Board() {
    // dtor
    for (int r = 0; r < boardSize; ++r) {
        for (int c = 0; c < boardSize; ++c) {
            // Call each Piece's dtor and delete the pointer
            delete board[r][c];
        }
    }
    delete td;
}

void Board::clearBoard() {
  // Clear the board.
  board.clear();
}

bool Board::checkValid(int origRow, int origCol, int newRow, int newCol) {
    if (board[origRow][origCol] == nullptr) {
        return false;
    } if (board[newRow][newCol] != nullptr && (board[origRow][origCol]->getColour() == board[newRow][newCol]->getColour())) {
        return false;
    } if (!(board[origRow][origCol]->checkMovementValid(*this, newRow, newCol))) {
        return false;
    }
    placePiece(board[origRow][origCol], newRow, newCol);
    td->notify(nullptr, origRow, origCol);
    td->notify(board[newRow][newCol], newRow, newCol);
    return true;
}

Piece* Board::getPiece(int row, int col) const {
    return board[row][col];
}

int Board::getBoardSize() const {
    return boardSize;
}
  
bool Board::isWon() {
    return won;
}; 

// Sets up an 8x8 chessboard
void Board::init(){
    // clearBoard();
    td = new TextDisplay();

    board.resize(boardSize, vector<Piece *>(boardSize));
    for (int r = 0; r < boardSize; ++r) {
        board.resize(boardSize);
        for (int c = 0; c < boardSize; ++c) {
            board[r][c] = nullptr; // 
        }
    }

    // init all the Pieces here to start the board
} 

// void createPiece(PieceType pieceType, string targetLocation, Colour colour) {
//     // converting col to int THIS IS DIFF THAN BELOW
//     string strCol = targetLocation.substr(0, 1);
//     int col = convertLetterToIndex(strCol);

//     // converting string to int
//     istringstream iss{targetLocation.substr(1, 2)};
//     int row;
//     iss >> row; 

    
// }

// Places a piece at row, col.
void Board::placePiece(Piece * p, int row, int col) {
    delete board[row][col];
    board[row][col] = p;
}

// convertLetterToIndex returns letter corresponding to index or -1 if invalid
int convertLetterToIndex(string letter) {
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
        return -1; // SHOULD WE USE AN ERROR HERE?
    }
}

bool Board::boardPlayerMove(string origLocation, string newLocation) {
    if (origLocation == newLocation) {
        cout << "You're moving to the same spot. Try again." << endl;
        return false;
    }
    string strOrigRow = origLocation.substr(0, 1);
    int origRow = convertLetterToIndex(strOrigRow);

    if (origRow == -1) {
        cout << "The original location is invalid. Try again." << endl;
        return false;
    }

    istringstream iss{origLocation.substr(1, 2)};
    int origCol;
    iss >> origCol;

    string strNewRow = newLocation.substr(0, 1);
    int newRow = convertLetterToIndex(strNewRow);

    if (newRow == -1) {
        cout << "The new move location is invalid. Try again." << endl;
        return false;
    }

    istringstream iss2{newLocation.substr(1, 2)};
    int newCol;
    iss2 >> newCol;

    // board[origRow][origCol].checkValidMove(*this, newRow, newCol);
    placePiece(board[origRow][boardSize - origCol], newRow, boardSize - newCol);
    return true;
}

bool Board::computerMakeMove() {
    return false;
}

ostream &operator<<(std::ostream &out, const Board &b) {
    out << *(b.td);
    return out;
}
