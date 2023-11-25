#ifndef __ROOK_H__
#define __ROOK_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "piece.h"
// class Piece;
using namespace std;

class Rook : public Piece { // Concrete Subject
  PieceType type = PieceType::Rook;
  bool firstMove = true;
  // Add other private members if necessary

 public:
  Rook(Colour colour);
  Rook(int row, int col, Colour colour);  // Default constructor, COULD CHANGE THIS TO TAKE IN PARAMS LIKE LOCATION (where to put it)

  // Piece getState() const; // Returns a piece
  bool checkMovementValid(const Board &b, int newRow, int newCol) override;
  // void createPiece(Rook pieceType, string targetLocation, Colour colour) override;
  bool castleRookRight(const Board &b);
  bool castleRookLeft(const Board &b);

};

#endif
