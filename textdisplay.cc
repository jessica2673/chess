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

    for (int r = 0; r < boardSize; ++r) {
        std::vector<char> newRow;
        for (int c = 0; c < boardSize; ++c) {
            // Do not add square color to the first 2 columns and last 2 rows
            if (c != 0 && c != 1 && r != 8 && r != 9) {
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
            } else {
                newRow.emplace_back(' ');
            }
        }
        if (curSquare == darkSquare) {
            curSquare = whiteSquare;
        } else {
            curSquare = darkSquare;
        }

        // Do not add new line to the last row of the board
        if (r != boardSize - 1) {
            newRow.emplace_back('\n');
        }
        theDisplay.emplace_back(newRow);
    }

    // Fill in the numbers on the left side of the board
    for (int r = boardSize - 3; r >= 0; --r) {
        theDisplay[r][0] = char(boardSize - 2 - r + 48);
        theDisplay[r][1] = ' ';
    }
    
    // Fill in the last row with letters
    char currLetter = 'a';
    for (int c = 2; c < boardSize; ++c) {
        theDisplay[boardSize - 1][c] = currLetter; // the last row in display
        currLetter++;
        theDisplay[boardSize - 2][c] = ' '; // the second last row should be spaces
    }
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
    theDisplay[row][col + 2] = pieceToChar(p->getState());
    if (p->getColour() == Colour::WHITE) {
        theDisplay[row][col + 2] = theDisplay[row][col + 2] - 32;
    }

}

TextDisplay::~TextDisplay() {
    
}

ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    int size = td.boardSize;
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size + 1; ++c) {
            out << td.theDisplay[r][c];
        }
    }
    return out;
}
