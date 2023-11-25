#include <iostream>
#include <string>
#include "board.h"
#include "bishop.h"
using namespace std;


int main() {
  string cmd, aux;
  Board * b = new Board();
  int moves = 0; // added

  cout << *b << endl;


  while (true) {
    cin >> cmd;
    if (!cin) break;  // added
    if (cmd == "game") {
        // write code here
        // game white-player black-player starts a new game. 
        // The parameters white-player and black-player can be either human or computer[1-4].
        string whitePlayer;
        string blackPlayer;
        cin >> whitePlayer;
        cin >> blackPlayer;
        
    // } else if (cmd == "resign") {
    //   // write code here
    //   // concedes the game to your opponent. This is the only way, outside of winning or drawing the game, to end a game.
    //   exit(1);

    // } else if (cmd == "move") {
    //   // write code here
    //   string origLocation;
    //   string newLocation;
    //   cin >> origLocation;
    //   cin >> newLocation;
    //   b->boardPlayerMove(origLocation, newLocation);

    } else if (cmd == "setup") {
      // write code here
      /*
      Upon completion of setup mode, you must verify that the board contains exactly one white king and exactly one black
      king; that no pawns are on the first or last row of the board; and that neither king is in check. The user cannot leave
      setup mode until these conditions are satisfied. 
      */
      string operation;

      cin >> operation;

      string piece;
      string targetLocation;
      while (true) {
        if (operation == "+") {
          cin >> piece;
          cin >> targetLocation;

          string strCol = targetLocation.substr(0, 1);
          int col;

          if (strCol == "a") {
              col = 0;
          } else if (strCol == "b") {
              col = 1;
          } else if (strCol == "c") {
              col = 2;
          } else if (strCol == "d") {
              col = 3;
          } else if (strCol == "e") {
              col = 4;
          } else if (strCol == "f") {
              col = 5;
          } else if (strCol == "g") {
              col = 6;
          } else {
              col = 7;
          }
          istringstream iss{targetLocation.substr(1, 2)};
          int row;
          iss >> row;

          if (piece == "B") { // placing bishop
            Piece * bishop = new Bishop(row, col, Colour::WHITE);
            // b->placePiece(bishop, row, col);
          } else if (piece == "b") {
            Piece * bishop = new Bishop(row, col, Colour::WHITE);
          }
  
          cout << *b;

        // } else if (operation == "-") {
        //   cin >> targetLocation;
        //   b->removePiece(targetLocation);
        //   cout << *b;

        } else if (operation == "done") {
          break;
        }
      }
    }
  }
}
