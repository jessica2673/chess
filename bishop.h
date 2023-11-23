#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "piece.h"
class Piece;
using namespace std;

class Bishop : public Piece { // Concrete Subject
  PieceType type = PieceType::Bishop;
  // Add other private members if necessary

 public:
  Bishop(int row, int col, Colour colour);  // Default constructor, COULD CHANGE THIS TO TAKE IN PARAMS LIKE LOCATION (where to put it)

  // Piece getState() const; // Returns a piece
  bool checkMovementValid(const Board &b, int newRow, int newCol) override;
  /*
  int getRow() const; // Returns the value of r.
  int getCol() const; // Returns the value of c.
  */

         
  
};
#endif
