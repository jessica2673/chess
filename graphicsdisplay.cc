#include "graphicsdisplay.h"
using namespace std;

string whitePiecetoString(PieceType p) {
  switch (p) {
    case PieceType::Pawn:
      return "P";
    case PieceType::Bishop:
      return "B";
    case PieceType::Knight:
      return "N";
    case PieceType::Rook:
      return "R";
    case PieceType::Queen:
      return "Q";
    case PieceType::King:
      return "K";
    case PieceType::Empty:
      return " ";
  }
}

string blackPiecetoString(PieceType p) {
  switch (p) {
    case PieceType::Pawn:
      return "p";
    case PieceType::Bishop:
      return "b";
    case PieceType::Knight:
      return "n";
    case PieceType::Rook:
      return "r";
    case PieceType::Queen:
      return "q";
    case PieceType::King:
      return "k";
    case PieceType::Empty:
      return " ";
  }
}

string chartoString(char c) {
  switch(c) {
    case 'a':
      return "a";
    case 'b':
      return "b";
    case 'c':
      return "c";
    case 'd':
      return "d";
    case 'e':
      return "e";
    case 'f':
      return "f";
    case 'g':
      return "g";
    case 'h':
      return "h";
  }
}

GraphicsDisplay::GraphicsDisplay(Xwindow &xw):
    xw{xw} {
    
    xw.fillRectangle(0, 0, 500, 500, Xwindow::Red); // Makes the background red.
    xw.drawString(200, 20, "Christmas Mode"); // Writes "Christmas Mode" on top.
    bool currWhite = true; // Start with a white square when filling the Graphics Display.
    
    for (int i = 0; i < boardSize; ++i) {
      for (int j = 0; j < boardSize; ++j) {
        int topLeftX = (i * squareWidth) + borderSize; // The top left X coordinate of the square, accounting for borders.
        int topLeftY = (j * squareHeight) + borderSize; // The top left Y coordinate of the square, accounting for borders.
        // If the square is white, fill the Graphics Display with a white square, anchored at X,Y. Otherwise, fill the Graphics Display with a green square.
        if (currWhite) {
            xw.fillRectangle(topLeftX, topLeftY, squareWidth, squareHeight, Xwindow::White);
            currWhite = !currWhite;
        } else {
            xw.fillRectangle(topLeftX, topLeftY, squareWidth, squareHeight, Xwindow::Green);
            currWhite = !currWhite;
        }
      }
      // Toggles the square colour.
      currWhite = !currWhite;
    }
    
    // Fills in the border with guiding numbers and letters
    char start = 'a';
    int numStart = 8;
    for (int i = 0; i < boardSize; ++i) {
        int x = borderSize / 2; // The middle x coordinate of the numbers.
        int y = (((i + 1) * squareHeight) + (i * squareHeight)) / 2 + borderSize; // The middle y coordinate of the letters.
        string n = to_string(numStart); // Converts the number character to a string.

        // Draws the line of numbers going down from the top.
        xw.drawString(x, y, n);
        // Draws the line of letters going up from the left. The x coordinate is now the y coordinate, and the y coordinate is the x but at the bottom of the display, hence 500 - x.
        xw.drawString(y, 500 - x, chartoString(start));
        ++start;
        --numStart;
    }
    
  }

void GraphicsDisplay::notify(Piece *p, int row, int col) {
    int rowParity = row % 2;
    int colParity = col % 2;
    int topLeftX = (col * squareWidth) + borderSize; // The top left X of the square being notified.
    int topLeftY = (row * squareHeight) + borderSize; // The top left Y of the square being notified.
    PieceType pieceType;

    // If the piece is nullptr, set the PieceType to Empty. Otherwise, get the PieceType.
    if (p == nullptr) {
        pieceType = PieceType::Empty;
    } else {
        pieceType = p->getState();
    }

    int middleX = (topLeftX + borderSize + ((col + 1) * squareWidth)) / 2;
    int middleY = (topLeftY + borderSize + ((row + 1) * squareWidth)) / 2;
    
    // If the parity of the row is equal to the parity of the column, it is a white square. Otherwise, it is green.
    if (rowParity == colParity) {
        xw.fillRectangle(topLeftX, topLeftY, squareWidth, squareHeight, Xwindow::White);
    } else {
        xw.fillRectangle(topLeftX, topLeftY, squareWidth, squareHeight, Xwindow::Green);
    }

    // If there is a piece on the square being notified, draw the piece onto the square.
    if (pieceType != PieceType::Empty) {
        if (p->getColour() == Colour::WHITE) {
            xw.drawString(middleX, middleY, whitePiecetoString(pieceType));
        } else {
            // Doubles up on black pieces, as it is hard to distinguish uppercase and lowercase on the graphic display at times.
            xw.drawString(middleX, middleY, (blackPiecetoString(pieceType) + blackPiecetoString(pieceType))); 
        }
    } 
}

GraphicsDisplay::~GraphicsDisplay() { }
