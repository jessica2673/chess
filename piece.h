#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"

enum class PieceType {Pawn, Bishop, Knight, Rook, Queen, King, Empty};

class Piece { // Piece is a Subject
  // bool isOn = false;
  std::vector<Observer*> observers;
  int row, col;

  // Add other private members if necessary

 public:
  Piece();  // Default constructor

  int getRow() const; // Returns the value of row.
  int getCol() const; // Returns the value of col.
  PieceType getState() const;

  // void setOn();          // Explicitly sets me to on.
  // void toggle();         // Toggles me between on and off.
  // void setCoords(int r, int c);  // Tells me my row and column number. MIGHT NEED THIS!?!?!????????????

  void attach(Observer *o);  // Attaches observers (TextDisplay and GraphicDisplay)

  void detach(Observer *o);  // Attaches observers (TextDisplay and GraphicDisplay) DON"T REALLY NEED THIS LOLLLL

  void notifyObservers();   // Piece will call this to let observers TextDisplay and GraphicDisplay know that they've moved so that the displays can update accordingly 


  virtual bool makeMove(int row, int col);


  virtual ~Piece() = 0; // makes the class abstract

};
#endif