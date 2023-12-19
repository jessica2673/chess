#ifndef __QUEEN_H__
#define __QUEEN_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "piece.h"
class Piece;
using namespace std;

class Queen : public Piece { // Concrete Subject
  PieceType type = PieceType::Queen;
  // Add other private members if necessary

 public:
  // Constructs a new Queen with a colour.
  Queen(Colour colour);

  bool checkMovementValid(Board &b, int newRow, int newCol, bool calledByPlayer = false) override;
  vector<vector<int>> checkPossibleMoves(Board &b) override;

  
};

#endif
