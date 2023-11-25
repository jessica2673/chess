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
      b->init();
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

          if (piece == "B") { // placing bishop
            Piece * bishop = new Bishop(Colour::WHITE);
            b->placeNewPiece(bishop, targetLocation);
          } else if (piece == "b") {
            Piece * bishop = new Bishop(Colour::BLACK);
            b->placeNewPiece(bishop, targetLocation);
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
