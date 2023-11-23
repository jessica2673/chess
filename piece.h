#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"

enum class PieceType {Pawn, Bishop, Knight, Rook, Queen, King, Empty};

class Piece { // Piece is a Subject

  public:
    Piece();  // Default constructor

    enum class Colour { BLACK, WHITE };

    int getRow() const; // Returns the value of row.
    int getCol() const; // Returns the value of col.
    PieceType getState() const;
    Colour getColour() const;

    // void setCoords(int r, int c);  // Tells me my row and column number. MIGHT NEED THIS!?!?!????????????

    void attach(Observer *o);  // Attaches observers (TextDisplay and GraphicDisplay)

    void detach(Observer *o);  // Attaches observers (TextDisplay and GraphicDisplay) DON"T REALLY NEED THIS LOLLLL

    void notifyObservers();   // Piece will call this to let observers TextDisplay and GraphicDisplay know that they've moved so that the displays can update accordingly 

    std::vector<Piece> checkAttackingMe;

    virtual bool makeMove(int row, int col);

    virtual std::vector<int> checkPossibleMoves();

    virtual ~Piece() = 0; // makes the class abstract

  private:
    std::vector<Observer*> observers;
    int row, col;
    Colour colour;

};
#endif
