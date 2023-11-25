#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <sstream>
#include <vector>
#include "piece.h"
#include "textdisplay.h"
// #include "graphicsdisplay.h"
// #include "window.h"

using namespace std;

class Board {
  const int boardSize = 8;
  std::vector<std::vector<Piece *>> board;  // The actual board containing Piece pointers.
  bool won;        // Grid in winning state
  TextDisplay *td; // The text display.

 public:
  Board();
  ~Board();
  
  void clearBoard(); // might not need?
  void init();
  bool checkValid(int origRow, int origCol, int newRow, int newCol);
  Piece* getPiece(int row, int col) const;
  int getBoardSize() const;
  bool isWon(); // Call to determine if board is in a winning state.

  void placePiece(Piece * p, string location);
  void placePiece(Piece * p, int r, int c);  // Places a piece at row r, col c
  void removePiece(string location);

  bool boardPlayerMove(string origLocation, string newLocation); // Takes in player move from main
  bool computerMakeMove(); 


  friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
