#ifndef __PAWN_H__
#define __PAWN_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "piece.h"
class Piece;
using namespace std;

class Pawn : public Piece {
    PieceType type = PieceType::Pawn;
    bool firstMove = true;
    bool passantEligible = false;
    bool justPassed = false;

public:
    Pawn(int row, int col, Colour colour);

    bool checkMovementValid(const Board &b, int newRow, int newCol);
    
};


#endif
