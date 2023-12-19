#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <vector>
#include "board.h"
#include "piece.h"
using namespace std;

enum class Colour;

// Player class is used to make moves with the Pieces.
class Player { 
    Colour colour;

    public:
        Player(Colour colour);

        // If the caller is a Player, it will check if the move from (origRow, origCol) to (newRow, newCol) is valid.
        // If caller is a Computer of any Level, it will find a valid move to make based on its Level.
        // It will make the move once it has determined either validity or found the best move.
        virtual bool makeMove(Board & b, bool whiteTurn, int origRow, int origCol, int newRow, int newCol);

        Colour getColour();
        virtual ~Player();
};

#endif
