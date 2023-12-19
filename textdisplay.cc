#include <iostream>
#include <string>
#include "textdisplay.h"
#include "board.h"
#include "piece.h"
using namespace std;

char pieceToChar(PieceType p) {
    switch (p) {
        case PieceType::Pawn:
            return 'p';
        case PieceType::Bishop:
            return 'b';
        case PieceType::Knight:
            return 'n';
        case PieceType::Rook:
            return 'r';
        case PieceType::Queen:
            return 'q';
        case PieceType::King:
            return 'k';
        default:
            return ' ';
    }
}

TextDisplay::TextDisplay() {
    char whiteSquare = ' ';
    char darkSquare = '_';
    char curSquare = whiteSquare; // Start with a white square when filling theBoardDisplay.  
    int rowLabelIndex = 8; // Start lableing at 8.

    // Filling theBoardDisplay.
    for (int r = 0; r < boardSize; ++r) {
        // Creates a new row of chars to be inserted in theBoardDisplay row by row.
        std::vector<char> newRow;
        for (int c = 0; c < boardSize; ++c) {            
            // If r is even, start with a white square.
            // If r is odd, start with a dark square.
            newRow.emplace_back(curSquare);

            // Toggle square to alternate between white and black squares within a row.
            if (curSquare == darkSquare) {
                curSquare = whiteSquare;
            } else {
                curSquare = darkSquare;
            }
        }

        // Add the new row of chars to theBoardDisplay.
        theBoardDisplay.emplace_back(newRow);

        // Toggle starting square for next row.
        if (curSquare == darkSquare) {
            curSquare = whiteSquare;
        } else {
            curSquare = darkSquare;
        }

        // Add labels into a vector.
        rowLabels.emplace_back(rowLabelIndex);
        --rowLabelIndex;
        // Convert integer to char with character arithmetic to obtain the letters a to h.
        colLabels.emplace_back(char(r + 97));
    }
}

void TextDisplay::notify(Piece *p, int row, int col) {
    // If the Piece is empty, output a blank square depending on its colour.
    if (p == nullptr) {
        int rowParity = row % 2;
        int colParity = col % 2;
        if (rowParity == colParity) {
            theBoardDisplay[row][col] = ' ';
        } else {
            theBoardDisplay[row][col] = '_';
        }
        return;
    }

    // If the Piece is non-empty, output it as a capital letter if it is White
    // and lowercase if it is Black using character arithmetic.
    theBoardDisplay[row][col] = pieceToChar(p->getState());
    if (p->getColour() == Colour::WHITE) {
        theBoardDisplay[row][col] = theBoardDisplay[row][col] - 32;
    }
}

TextDisplay::~TextDisplay() {}

ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (int r = 0; r < td.boardSize; ++r) {
        // Output the row label before outputting each character in the row in the board.
        out << td.rowLabels[r] << ' ';
        for (int c = 0; c < td.boardSize; ++c) {
            out << td.theBoardDisplay[r][c];
        }
        // Add a line feed to the end of the row.
        out << endl;
    }

    // Output a blank line before outputting the column labels.
    out << endl << ' ' << ' ';

    // Output the column labels.
    for (int r = 0; r < td.boardSize; ++r) {
        out << td.colLabels[r];
    }

    return out;
}
