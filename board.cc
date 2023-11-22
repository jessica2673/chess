#include <iostream>
#include "board.h"
using namespace std;


Board::Board() {
    // default ctor
}

Board::~Board() {
    // dtor
}
  
bool Board::isWon() const {
    return isWon;
}; 

// Sets up an 8x8 chessboard
void Board::init(){
    
} 

// Places a piece at row, col.
void Board::placePiece(Piece & p, int row, int col) {

} 

    // ASK ASK ASK 
bool Board::makeMove(std::string origLocation, std::string newLocation) {
    
}

bool Board::computerMakeMove() {

}



ostream &operator<<(std::ostream &out, const Board &b) {
    out << *(b.td);
    return out;
}