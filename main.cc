#include <iostream>
#include <string>
#include "board.h"
#include <stdexcept>

using namespace std;

int main() {
    string cmd;
    Board b = Board();
    bool inGame = false;
    bool whiteTurn = true;

    bool whiteInCheck = false;
    bool blackInCheck = false;

    float whiteScore = 0;
    float blackScore = 0;

    bool isWhiteComputer = true;
    bool isBlackComputer = true;

    b.init();
    cout << b << endl;

    // Continue if there is input.
    while (cin >> cmd) {

        if (cin.eof()) break;
        if (cmd == "game") {
            inGame = true;
            whiteInCheck = false;
            blackInCheck = false;
            
            string whitePlayer;
            string blackPlayer;
            cin >> whitePlayer;
            cin >> blackPlayer;

            try {
                // Set the Computer to White or Black player depending on input.
                isWhiteComputer = b.setWhitePlayer(whitePlayer);
                isBlackComputer = b.setBlackPlayer(blackPlayer);
            } catch (std::invalid_argument & e) {
                cout << e.what() << endl;
            }

            cout << b << endl;
            if (whiteTurn) {
                cout << "White player's turn." << endl;
            } else {
                cout << "Black player's turn." << endl;
            }

            // Commands while in game.
            while (cin >> cmd) {

                if (cmd == "move") {

                    string origLocation = "";
                    string newLocation = "";

                    try {
                        // If the current player is a human, read in their original location and desired location.
                        if ((!isWhiteComputer && whiteTurn) || (!isBlackComputer && !whiteTurn)) {
                            vector <string> moves;
                            string move;

                            cin >> origLocation;
                            cin >> newLocation;

                            // Check if King is in check.
                            if (whiteInCheck) { 
                                // If White is in check, it must be White's move and it must move out of check.
                                // Check that the move takes the White King out of check.
                                if (b.boardMakeMove(whiteTurn, origLocation, newLocation)) {
                                    whiteInCheck = false;
                                    cout << b << endl;
                                    
                                } else {
                                    throw std::invalid_argument{"White is still in check."};
                                }
                            } else if (blackInCheck) {
                                // Otherwise it is checkmate.
                                if (b.boardMakeMove(whiteTurn, origLocation, newLocation)) {
                                    blackInCheck = false;
                                    cout << b << endl;
                                    
                                } else {
                                    throw std::invalid_argument{"Black is still in check."};
                                }
                            } else { 
                                // Executes if nothing is in check. 
                                if (b.boardMakeMove(whiteTurn, origLocation, newLocation)) {
                                    cout << b << endl;
                                }
                            }
                            
                        } else {  
                            // Computer's turn to make a move.
                            if (!b.boardMakeMove(whiteTurn)) {
                                break;
                            }
                            cout << b << endl;

                        }

                        // Toggle the turn.
                        whiteTurn = !whiteTurn;  

                        // Assumes whiteTurn has just been toggled.
                        if (!whiteTurn) {  
                            // Black player's turn to go next.
                            if (b.checkIfInCheck(Colour::BLACK)) {
                                blackInCheck = true;
                                cout << "Black is in check." << endl;
                            
                                if (b.checkForCheckmate(Colour::BLACK)) {
                                    cout << "Checkmate! White wins!" << endl;
                                    whiteScore++;
                                    break;
                                }
                            }
                        } else {  
                            // White player's turn to go next.
                            if (b.checkIfInCheck(Colour::WHITE)) {
                                whiteInCheck = true;
                                cout << "White is in check." << endl;
                            
                                if (b.checkForCheckmate(Colour::WHITE)) {
                                    cout << "Checkmate! Black wins!" << endl;
                                    blackScore++;
                                    break;
                                }
                            }
                        }

                        if (b.checkForStalemate(whiteTurn)) {
                            cout << "Stalemate!" << endl;
                            whiteScore += 0.5;
                            blackScore += 0.5;
                            break;
                        }

                        if (whiteTurn) {
                            cout << "White player's turn." << endl;
                        } else {
                            cout << "Black player's turn." << endl;
                        }

                    } catch (std::invalid_argument & e) {
                        cout << e.what() << endl;
                    } catch (std::logic_error & e) {
                        string newPieceType;
                        cin >> newPieceType;

                        // Promote the pawn which has already been moved.
                        b.promotePiece(whiteTurn, origLocation, newLocation, newPieceType);
                        whiteTurn = !whiteTurn;
                        cout << b << endl;
                    } 
                    
                    // End of move cmd.

                } else if (cmd == "resign") {
                    // Concedes the game to your opponent. This is the only way, outside of winning or drawing the game, to end a game.
                    if (whiteTurn) {
                        blackScore++;
                        cout << "Black wins!" << endl;
                    } else {
                        whiteScore++;
                        cout << "White wins!" << endl;
                    }          
                    break;
                } else if (cmd == "setup") {
                    cout << "Cannot enter setup mode while in game." << endl;
                }
            }
            
            inGame = false;

        } else if (cmd == "setup") {
            b.clearBoard();
            b.initEmpty();
            whiteTurn = true;

            // Prevent setup mode if game is in progress.
            if (inGame) continue;

            string operation;
            string piece;
            string targetLocation;

            cout << b << endl;

            while (true) {
                try {
                    cin >> operation;
                    if (cin.eof()) break;
                    if (operation == "+") {
                        cin >> piece;
                        cin >> targetLocation;

                        b.placeNewPiece(piece, targetLocation);

                    cout << b << endl;
                
                } else if (operation == "-") {
                    // Remove the piece at the specified location from the board.
                    cin >> targetLocation;
                    b.removePiece(targetLocation);
                    cout << b << endl;

                } else if (operation == "=") {
                    // Change whose turn it is to make a move.
                    string colour;
                    cin >> colour;

                        if (colour == "white") {
                            whiteTurn = true;
                        } else if (colour == "black") {
                            whiteTurn = false;
                        } else {
                            throw std::invalid_argument{"That is not a valid colour."};
                        }
                    } else if (operation == "done") {
                        try {
                            if (b.validBoardSetup()) {
                            cout << "Exit setup mode." << endl;

                                if (b.checkForStalemate(whiteTurn)) {
                                    cout << "Stalemate!" << endl;
                                    whiteScore += 0.5;
                                    blackScore += 0.5;
                                    b.clearBoard();
                                    b.init();
                                    break;
                                }
                                break;
                            }
                        } catch (std::domain_error & e) {
                            cout << e.what() << endl;
                        }
                    }
                } catch (std::invalid_argument & e) {
                    cout << e.what() << endl;
                }
            }
            
        }
    }

    // When the game ends, clear the board and print the score.
    b.clearBoard();
    cout << "Final Score:" << endl;
    cout << "White: " << whiteScore << endl;
    cout << "Black: " << blackScore << endl; 
}


