#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <vector>
#include "piece.h"
#include "textdisplay.h"
// #include "graphicsdisplay.h"
// #include "window.h"

class Board {
    // WHAT IS OUR EQUIVALENT
  std::vector<std::vector<Piece *>> theBoard;  // The actual board.
  bool won;        // Grid in winning state
  TextDisplay *td; // The text display.

 public:
  Board();
  ~Board();
  
  bool isWon() const; // Call to determine if board is in a winning state.
  void init(); // Sets up an 8x8 chessboard
  void placePiece(Piece & p, int r, int c);  // Places a piece at row r, col c to On.

    // ASK ASK ASK 
  bool makeMove(std::string origLocation, std::string newLocation); 
  bool computerMakeMove(); 



  friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
