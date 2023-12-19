#ifndef __BISHOP_H__
#define __BISHOP_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "piece.h"

using namespace std;

class Bishop : public Piece {
    PieceType type = PieceType::Bishop;

    public:
        Bishop(Colour colour);

        bool checkMovementValid(Board &b, int newRow, int newCol, bool calledByPlayer = false) override;
        vector<vector<int>> checkPossibleMoves(Board &b) override;

        ~Bishop() override;
};

#endif
