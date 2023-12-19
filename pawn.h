#ifndef __PAWN_H__
#define __PAWN_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "piece.h"
using namespace std;

enum class PieceType;
enum class Colour;
class Piece;

class Pawn : public Piece {
    PieceType type = PieceType::Pawn;
    bool firstMove = true;
    bool checkEnPassant(Board &b, int newRow, int newCol); // Checks if the pawn can perform an en passant move.

public:
    Pawn(Colour colour);

    bool checkMovementValid(Board &b, int newRow, int newCol, bool calledByPlayer = false);
    void placePiece(Board & b, int row, int col) override;
    void performEnPassant(Board &b, int newCol); // Performs an en passant move.
    vector<vector<int>> checkPossibleMoves(Board &b) override;
    vector<vector<int>> checkEnPassantMoves(Board &b) override; // Checks the possible moves that perform en passant.
    bool checkForPromotion(int row) override; // Checks if a pawn is eligible to be promoted.
    
};


#endif
