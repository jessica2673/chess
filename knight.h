#ifndef __KNIGHT_H__
#define __KNIGHT_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "piece.h"
class Piece;
using namespace std;

class Knight : public Piece {
    PieceType type = PieceType::Knight;

public:
    Knight(Colour colour);
    Knight(int row, int col, Colour colour);

    bool checkMovementValid(const Board &b, int newRow, int newCol) override;
    
};


#endif
