#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <iostream>
#include <vector>
#include "observer.h"
#include "window.h"
#include "piece.h"

class GraphicsDisplay: public Observer {

    const int boardSize = 8; // The number of squares on the board, length-wise and height-wise.
    const int squareWidth = 500/9; // The width of a square (divided by 9 and not 8 to make room for the border).
    const int squareHeight = 500/9; // The height of a square.
    const int borderSize = (500/9) / 2; // The width of the border.
    Xwindow &xw; // The XWindow to open.

    public: 
        GraphicsDisplay(Xwindow &xw); // Constructs a new Graphics Display.

        // Notifies the Graphics Display that there has been an update to the board.
        void notify(Piece *p, int row, int col) override;

        // Destructs the Graphics Display.
        ~GraphicsDisplay();
};  

#endif
