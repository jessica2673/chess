#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
class Piece;

/*
In this display, capital letters denote white pieces, and lower case letters denote black pieces. Unoccupied squares are denoted
by a blank space for white squares, and an underscore character for dark squares.
*/

// TextDisplay is an Observer of every Piece and inherits from Observer.
class TextDisplay: public Observer {
    std::vector<std::vector<char>> theBoardDisplay; // 2D vector used to store the text display.
    std::vector<int> rowLabels; // The row labels from 8 to 1
    std::vector<char> colLabels; // The column labels from a to h.

    const int boardSize = 8; // The size of the text display.

    public:
    // Constructs a new TextDisplay.
    TextDisplay();

    // Notifies the TextDisplay that there has been an update to the board.
    void notify(Piece *p, int row, int col) override;

    // Destructs the TextDisplay.
    ~TextDisplay();

    // Output operator overload.
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};

#endif
