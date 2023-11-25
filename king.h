#ifndef __KING_H__
#define __KING_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "piece.h"
class Piece;
using namespace std;

class King : public Piece { // Concrete Subject
  PieceType type = PieceType::King;
  bool firstMove = true;
  // Add other private members if necessary

 public:
  King(Colour colour);
  King(int row, int col, Colour colour);  // Default constructor, COULD CHANGE THIS TO TAKE IN PARAMS LIKE LOCATION (where to put it)

  // Piece getState() const; // Returns a piece
  bool checkMovementValid(const Board &b, int newRow, int newCol) override;
  // void createPiece(King pieceType, string targetLocation, Colour colour) override;
  bool castleKingRight(const Board &b); // Call this function if either White or Black is castling on the right
  bool castleKingLeft(const Board &b); // Call this function if either White or Black is castling on the left
};

#endif
