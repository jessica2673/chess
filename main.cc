#include <iostream>
#include <string>
#include "board.h"
using namespace std;

int main() {
  string cmd, aux;
  Board * b = new Board();
  b->init();
  int moves = 0; // added

<<<<<<< Updated upstream
  cout << *b << endl;
=======
  // cout << *b << endl;
>>>>>>> Stashed changes


  // while (true) {
  //   cin >> cmd;
  //   if (!cin) break;  // added
  //   if (cmd == "game") {
  //       // write code here
  //       // game white-player black-player starts a new game. 
  //       // The parameters white-player and black-player can be either human or computer[1-4].
  //       string whitePlayer;
  //       string blackPlayer;
  //       cin >> whitePlayer;
  //       cin >> blackPlayer;
        
        
  //   } else if (cmd == "resign") {
  //     // write code here
  //     // concedes the game to your opponent. This is the only way, outside of winning or drawing the game, to end a game.
  //     exit(1);

  //   } else if (cmd == "move") {
  //     // write code here
  //     string origLocation;
  //     string newLocation;
  //     cin >> origLocation;
  //     cin >> newLocation;
  //     b->boardPlayerMove(origLocation, newLocation);

  //   } else if (cmd == "setup") {
  //     // write code here
  //     /*
  //     Upon completion of setup mode, you must verify that the board contains exactly one white king and exactly one black
  //     king; that no pawns are on the first or last row of the board; and that neither king is in check. The user cannot leave
  //     setup mode until these conditions are satisfied. 
  //     */
  //     string operation;

  //     cin >> operation;

  //     string piece;
  //     string targetLocation;
  //     while (true) {
  //       if (operation == "+") {
  //         cin >> piece;
  //         cin >> targetLocation;

  //         if (piece == "B") { // placing bishop
  //           // b->createPiece(PieceType::Bishop, targetLocation, Colour::WHITE);
  //         } else if (piece == "b") {
  //           // b->createPiece(PieceType::Bishop, targetLocation, Colour::BLACK);
  //         }
  
  //         cout << *b;

  //       } else if (operation == "-") {
  //         cin >> targetLocation;
<<<<<<< Updated upstream
  //         // b->removePiece(targetLocation);
=======
  //         b->removePiece(targetLocation);
>>>>>>> Stashed changes
  //         cout << *b;

  //       } else if (operation == "done") {
  //         break;
  //       }
  //     }
  //   }
  // }
}
