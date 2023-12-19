#ifndef __KING_H__
#define __KING_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "piece.h"
#include "rook.h"
#include <map>

using namespace std;

class King : public Piece {
  PieceType type = PieceType::King;
  bool firstMove = true;
  bool inCheck = false;
  bool justCastledRight = false;
  bool justCastledLeft = false;

 public:
  King(Colour colour); 

  bool checkMovementValid(Board &b, int newRow, int newCol, bool calledByPlayer = false) override;
  vector<vector<int>> checkPossibleMoves(Board &b) override;

  // Return whether or not the King is currently in check.
  bool isInCheck(const Board &b);

  // Set the King to in check.
  void setInCheck(bool kingInCheck);

  // Places the King at row, col on the board b.
  void placePiece(Board & b, int row, int col) override;

  // Check if either the White King or Black King is castling on the right.
  bool castleKingRight(Board &b);
  
  // Check if either the White King or Black King is castling on the left.
  bool castleKingLeft(Board &b); 
};

#endif
