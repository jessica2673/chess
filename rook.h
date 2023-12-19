#ifndef __ROOK_H__
#define __ROOK_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "piece.h"

using namespace std;

class Rook : public Piece {
    PieceType type = PieceType::Rook;
    bool firstMove = true; // Keep track of whether or not this is the Rook's first move.

    public:
        // Construct a new Rook with colour.
        Rook(Colour colour);

        bool checkMovementValid(Board &b, int newRow, int newCol, bool calledByPlayer = false) override;
        void placePiece(Board & b, int row, int col) override;
        vector<vector<int>> checkPossibleMoves(Board &b) override;

        // Checks whether or not the Rook can castle on the right and left side.
        bool castleRookRight();
        bool castleRookLeft();
};

#endif
