#include "piece.h"

Piece::Piece(int row, int col, PieceType type, Colour colour):
    row{row}, col{col}, type{type}, colour{colour} {} // Default constructor

// Returns the value of row.
int Piece::getRow() const {
    return row;
}

// Returns the value of col.
int Piece::getCol() const {
    return col;
} 

PieceType Piece::getState() const {
    return type;
}

Colour Piece::getColour() const {
    return colour;
}

// void setCoords(int r, int c);  // Tells me my row and column number. MIGHT NEED THIS!?!?!????????????

void Piece::attach(Observer *o) {
    observers.emplace_back(o);
}  // Attaches observers (TextDisplay and GraphicDisplay)

void Piece::detach(Observer *o) {

}  // Attaches observers (TextDisplay and GraphicDisplay) DON"T REALLY NEED THIS LOLLLL

// Piece will call this to let observers TextDisplay and GraphicDisplay know that they've moved so that the displays can update accordingly 
void Piece::notifyObservers() {
    for (auto p: observers) {
	}
}

void Piece::moveMyself(int newRow, int newCol) {
    row = newRow;
    col = newCol;
}
