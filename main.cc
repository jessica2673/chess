#include <iostream>
#include <string>
#include "board.h"
using namespace std;

int main() {
  string cmd, aux;
  Board * b = new Board();
  int moves = 0; // added

  cout << b << endl;


  while (true) {
    cin >> cmd;
    if (!cin) break;  // added
    if (cmd == "game") {
        // write code here
    } else if (cmd == "resign") {
      // write code here
    } else if (cmd == "move") {
      // write code here
    } else if (cmd == "setup") {
      // write code here

      // setup enters setup mode, within which you can set up your own initial board configurations. 
      // This can only be done when a game is not currently running.

      // + K e1 places the piece K on the square e1. If a piece is already on that square, it is replaced.

      // e1 removes the piece from the square e1. If there is no piece at that square, take no action.

    }
  }
}
