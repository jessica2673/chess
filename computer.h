#ifndef __COMPUTER_H_
#define __COMPUTER_H_
#include <iostream>
#include <vector>
#include "player.h"
#include <map>

using namespace std; 
class Player;

class Computer: public Player {
    vector<PieceType> promotionPieces = vector<PieceType>{PieceType::Queen, PieceType::Rook, PieceType::Bishop, PieceType::Knight};

    // Return all the possible moves which capture a Piece or attack the opponent King.
    map<Piece *, vector<vector<int>>> captureOrAttackMoves(Board & b);

    // Return all the possible moves which takes our Piece out of attack.
    map<Piece *, vector<vector<int>>> avoidCaptureMoves(Board & b);

 protected:
     // Generates a completely random move.
    bool levelOne(Board & b, bool whiteTurn);

    // Prefers capturing moves and checks over other moves.
    bool levelTwo(Board & b, bool whiteTurn);

    // Prefers avoiding capture over capturing moves and checks.
    bool levelThree(Board & b, bool whiteTurn); 

    // Prefers capturing moves and checks depending on the target piece's value before other moves. 
    bool levelFour(Board & b, bool whiteTurn);
    
 public:

    Computer(Colour colour);

    virtual ~Computer() = 0;
};

#endif
