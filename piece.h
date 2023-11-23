#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "board.h"

enum class PieceType {Pawn, Bishop, Knight, Rook, Queen, King, Empty};
enum class Colour { BLACK, WHITE };

class Piece { // Piece is a Subject

  public:
    Piece(PieceType type, Colour colour);  // Default constructor

    int getRow() const; // Returns the value of row.
    int getCol() const; // Returns the value of col.
    PieceType getState() const;
    Colour getColour() const;

    void attach(Observer *o);  // Attaches observers (TextDisplay and GraphicDisplay)

    void detach(Observer *o);  // Attaches observers (TextDisplay and GraphicDisplay) DON"T REALLY NEED THIS LOLLLL

    void notifyObservers();   // Piece will call this to let observers TextDisplay and GraphicDisplay know that they've moved so that the displays can update accordingly 

    virtual bool placePiece(Board* b, int row, int col) = 0;

    std::vector<Piece> checkAttackingMe();
    virtual std::vector<int> checkPossibleMoves() = 0;

    virtual ~Piece() = 0; // makes the class abstract

  private:
    std::vector<Observer*> observers;
    int row, col;
    Colour colour;
    PieceType type;
 
};
#endif