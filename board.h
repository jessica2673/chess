#ifndef __BOARD_H__
#define __BOARD_H__
#include <iostream>
#include <sstream>
#include <vector>
#include "piece.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"
#include "player.h"

using namespace std;

enum class PieceType;
enum class Colour;
class King;
class Rook;
class Player;
class GraphicsDisplay;

class Board {
    const int boardSize = 8; 
    vector<std::vector<Piece *>> board;  // The actual board containing Piece pointers.
    
    Xwindow *wd;
    TextDisplay *td; // The text display.
    GraphicsDisplay *gd;

    King * whiteKing;
    King * blackKing;

    // Players can be either a Player or Computer.
    Player * whitePlayer;
    Player * blackPlayer;

    vector<Piece *> whitePieces;
    vector<Piece *> blackPieces;
    vector<int> lastMove = {-1, -1, -1, -1};

    // Return true if the two Pieces are on the same coloured square.
    bool sameColourSquare(Piece * first, Piece * second);
    // Convert string type to PieceType.
    PieceType convertStrToPiecetype(string type);
    // Returns letter corresponding to index or -1 if invalid.
    int convertLetterToIndex(string letter);

    // Convert string to coordinates of form (row, col).
    vector<int> convertStrToCoords(string location);

    public:
        Board();
        ~Board();

        // Clears the board and destroys associated objects.
        void clearBoard(); 
        
        // Initialize the board and set the default position.
        void init();

        // Initialize an empty board.
        void initEmpty();

        // Return the size of the board.
        int getBoardSize() const;

        // Get the Piece on the board at (row, col).
        Piece* getPiece(int row, int col) const;

        // Set the square at (row, col) on the board to p.
        void setPiece(Piece * p, int row, int col);

        // Set the last move made from (origRow, origCol) to (newRow, newCol) for Pawn promotion.
        void setLastMove(int origRow, int origCol, int newRow, int newCol);

        // Get the last move made for Pawn promotion.
        vector<int> getLastMove() const;

        King * getWhiteKing() const;
        void setWhiteKing(King * whiteKing);
        King * getBlackKing() const;
        void setBlackKing(King * blackKing);

        // Create a Player and associated object based on level.
        bool setWhitePlayer(string level);
        bool setBlackPlayer(string level);

        // Get the board's current White and Black Pieces
        vector<Piece *> getWhitePieces() const;
        vector<Piece *> getBlackPieces() const;

        // Check that the board has a valid setup.
        bool validBoardSetup();

        // Check if the Piece can move from (origRow, origCol) to (newRow, newCol).
        bool checkValid(int origRow, int origCol, int newRow, int newCol, bool calledByPlayer = false);

        // Check if the King of Colour c is currently in check.
        bool checkIfInCheck(Colour c);

        // Check if the King of Colour c is in checkmate.
        bool checkForCheckmate(Colour c);

        // Check if the game is in stalemate depending on whose turn it is.
        bool checkForStalemate(bool whiteTurn);

        // Place a new Piece of specified type at the specified location.
        void placeNewPiece(string type, string location);

        // Place new Piece at (row, col).
        void placeNewPiece(PieceType type, Colour colour, int row, int col);
        void placeNewPiece(PieceType type, Colour colour, string location);
        void placeNewPiece(string pieceType, Colour colour, string location);
        
        // Temporarily move a Piece from (origRow, origCol) to (newRow, newCol) without notifying the displays.
        void placePieceTemporarily(int origRow, int origCol, int newRow, int newCol);

        // Remove the Piece at specified location in the board.
        void removePiece(string location);

        // Remove the Piece at (row, col) in the board.
        void removePiece(int row, int col);

        // Returns whether or not the Player can make a move from origLocation to newLocation.
        bool boardMakeMove(bool whiteTurn, string origLocation = "", string newLocation = "");
        
        // Promotes Piece to a new PieceType with specified type at the specified location.
        void promotePiece(bool whiteTurn, string origLocation, string newLocation, string newPieceType);
        void promotePiece(bool whiteTurn, int row, int col, PieceType pieceType);

        // Override the output operator.
        friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
