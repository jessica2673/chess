#ifndef __PIECE_H__
#define __PIECE_H__
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "observer.h"
#include "board.h"
using namespace std;

enum class PieceType {Pawn, Bishop, Knight, Rook, Queen, King, Empty};
enum class Colour { BLACK, WHITE };

class Piece {

  public:
    Piece(Colour colour, PieceType type);
    Piece(int row, int col, PieceType type, Colour colour);  

    int getRow() const; 
    int getCol() const;
    void setRow(int r);
    void setCol(int c);
    void setCoords(int r, int c);
    PieceType getState() const;
    Colour getColour() const;

    void attach(Observer *o);  // Attaches observers.

    void notifyObservers();   

    // Check if the Piece can move to (newRow, newCol) in the board b.
    virtual bool checkMovementValid(Board &b, int newRow, int newCol, bool calledByPlayer = false) = 0; 
    bool checkDiagonal(Board &b, int newRow, int newCol);                  // Checks diagonal moves. 
    bool checkHorizontalVertical(const Board &b, int newRow, int newCol);  // Checks horizontal and vertical moves. 
    void capturePiece(Board &b, int captureRow, int captureCol);  // Captures the piece at location captureRow, captureCol. 

    virtual void placePiece(Board & b, int row, int col);  // Places the piece on board at location row, col. 

    vector<Piece *> checkAttackingMe(const Board &b, int row, int col, Colour c);
    
    virtual vector<vector<int>> checkPossibleMoves(Board &b) = 0; 
    virtual vector<vector<int>> checkEnPassantMoves(Board &b);  // Checks the possible moves that perform en passant. 
    bool checkForCheckPreMove(Board &b, int newRow, int newCol); // Checks for check before move to location on board at newRow newCol. 
    virtual bool checkForPromotion(int row);  // Checks if piece is eligible for promotion.

    virtual ~Piece() = 0; 

  private:
    vector<Observer*> observers;
    int row, col;
    Colour colour;
    PieceType type;
 
};
#endif
