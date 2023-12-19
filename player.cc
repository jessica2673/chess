#include "player.h"

Player::Player(Colour colour): colour{colour} {}

// Called by a human player.
bool Player::makeMove(Board & b, bool whiteTurn, int origRow, int origCol, int newRow, int newCol) {

    // The Piece does not exist.
    if (!b.getPiece(origRow, origCol)) {
        throw std::invalid_argument{"There is no piece at that location. Try again."};
    }

    // White player trying to move a black piece.
    if (whiteTurn && (b.getPiece(origRow, origCol)->getColour() == Colour::BLACK)) {
        throw std::invalid_argument{"Not your turn."};
    }

    // Black player trying to move a white piece.
    if (!whiteTurn && (b.getPiece(origRow, origCol)->getColour() == Colour::WHITE)) {
        throw std::invalid_argument{"Not your turn."};
    }
    
    // Moving to the same spot.
    if ((origRow == newRow) && (origCol == newCol)) {
        throw std::invalid_argument{"You're moving to the same spot. Try again."};
    }

    // Move is not valid for some other reason.
    if (!b.checkValid(origRow, origCol, newRow, newCol, true)) {
        throw std::invalid_argument{"Move is not valid."};
    }
    
    // Move the piece.
    b.getPiece(origRow, origCol)->placePiece(b, newRow, newCol);
    b.setLastMove(origRow, origCol, newRow, newCol);
    
    return true;
}

Colour Player::getColour(){
    return colour;
}

Player::~Player(){}
