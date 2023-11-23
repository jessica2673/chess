#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "piece.h"
class Piece;

class Bishop : public Piece { // Concrete Subject
  int row, col;
  PieceType type = PieceType::Bishop;
  // Add other private members if necessary

 public:
  Bishop();  // Default constructor, COULD CHANGE THIS TO TAKE IN PARAMS LIKE LOCATION (where to put it)

  Piece getState() const; // Returns a piece

  bool makeMove(int row, int col) override; 
  /*
  int getRow() const; // Returns the value of r.
  int getCol() const; // Returns the value of c.
  */

  void setOn();          // Explicitly sets me to on.

  void setCoords(int r, int c);  // Tells me my row and column number.

         
  
};
#endif
