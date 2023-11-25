#include <iostream>
#include <string>
#include "textdisplay.h"
#include "board.h"
#include "piece.h"
using namespace std;

/*
In this display, capital letters denote white pieces, and lower case letters denote black pieces. Unoccupied squares are denoted
by a blank space for white squares, and an underscore character for dark squares. The above board also represents the initial
configuration of the game.
*/

char pieceToChar(PieceType p) {
    switch (p) {
        case PieceType::Pawn:
            return 'p';
        case PieceType::Bishop:
            return 'b';
        case PieceType::Knight:
            return 'k';
        case PieceType::Rook:
            return 'r';
        case PieceType::Queen:
            return 'q';
        case PieceType::King:
            return 'k';
        case PieceType::Empty:
            return ' ';
        
    }
}

TextDisplay::TextDisplay() {
    char whiteSquare = ' ';
    char darkSquare = '_';
    char curSquare = whiteSquare;    

<<<<<<< Updated upstream
    for (int r = 0; r < boardSize; ++r) {
        std::vector<char> newRow;
        for (int c = 0; c < boardSize; ++c) {
            // init row
            // if r is even, start with white
            // if r is odd, start with dark
            newRow.emplace_back(curSquare);

            // toggle square
            if (curSquare == darkSquare) {
                curSquare = whiteSquare;
            } else {
                curSquare = darkSquare;
            }
        }
        cout << "should print new line";
        newRow.emplace_back('n');
        theDisplay.emplace_back(newRow);
    }

    // Fill in the numbers on the left side of the board
    // for (int r = boardSize - 2; r < boardSize; ++r) {
    //     theDisplay[r][0] = boardSize - 2 - r;
    //     theDisplay[r][1] = ' ';
    // }
    
    // // Fill in the last row with letters
=======
    // for (int r = 0; r < boardSize - 2; ++r) {
    //     theDisplay[r][0] = boardSize - 2 - r;
    // }
    
>>>>>>> Stashed changes
    // char currLetter = 'a';
    // for (int c = 2; c < boardSize; ++c) {
    //     theDisplay[boardSize - 1][c] = currLetter;
    //     currLetter++;
<<<<<<< Updated upstream
    //     theDisplay[boardSize - 2][c] = ' ';
=======
    // }
    for (int i = 0; i < 3; ++i) {
      std::vector<char> newRow (9, '_');
      theDisplay.emplace_back(newRow);
    }
    // for (int r = 0; r < 8; ++r) {
    //     std::vector<char> newRow;
    //     for (int c = 0; c < boardSize - 2; ++c) {
    //         // init row
    //         // if r is even, start with white
    //         // if r is odd, start with dark
    //         newRow.emplace_back('_');

    //         // // toggle square
    //         // if (curSquare == darkSquare) {
    //         //     curSquare = whiteSquare;
    //         // } else {
    //         //     curSquare = darkSquare;
    //         // }
    //     }
    //     theDisplay.emplace_back(newRow);
>>>>>>> Stashed changes
    // }
}

void TextDisplay::init() {
    
}

void TextDisplay::notify(Piece *p, int row, int col) {
    if (p == nullptr) {
        int rowParity = row % 2;
        int colParity = col % 2;
        if (rowParity == colParity) {
            theDisplay[row][col + 2] == '_';
        } else {
            theDisplay[row][col + 2] == ' ';
        }
        return;
    }
    theDisplay[row][col + 2] == pieceToChar(p->getState());
    if (p->getColour() == Colour::WHITE) {
        theDisplay[row][col + 2] = theDisplay[row][col + 2] - 32;
    }

}

TextDisplay::~TextDisplay() {
    
}

ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    int size = td.boardSize;
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            out << td.theDisplay[r][c];
        }
    }
    return out;
}