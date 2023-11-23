#include <iostream>
#include "textdisplay.h"
#include "board.h"
using namespace std;

/*
In this display, capital letters denote white pieces, and lower case letters denote black pieces. Unoccupied squares are denoted
by a blank space for white squares, and an underscore character for dark squares. The above board also represents the initial
configuration of the game.
*/

char pieceToChar()

TextDisplay::TextDisplay() {
    char whiteSquare = ' ';
    char darkSquare = '_';
    char curSquare = darkSquare;

    for (int i = 0; i < boardSize; ++i) {
        std::vector<char> newRow;
        for (int j = 0; j < boardSize; ++j) {
            // init row
            // if i is even, start with dark
            // if i is odd, start with white
            newRow.emplace_back(curSquare);
        }
        theDisplay.emplace_back(newRow);
    }
}

void TextDisplay::notify(Piece &p) {
    
}

TextDisplay::~TextDisplay() {

}

ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    int size = td.boardSize;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            out << td.theDisplay[i][j];
        }
    }
    return out;
}