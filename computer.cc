#include "computer.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include <random>
#include <stdlib.h>
#include <map>
#include "piece.h"

using namespace std;

Computer::Computer(Colour colour):
    Player{colour} {}

map<Piece *, vector<vector<int>>> Computer::captureOrAttackMoves(Board & b) {
    // Keep track of our Coloured Pieces and the enemy's Pieces.
    map<Piece *, vector<vector<int>>> levelTwoPieces;
    vector<Piece *> myPieces;
    Colour enemyKingColour;
    Colour colour = getColour();

    if (colour == Colour::WHITE) {
        enemyKingColour = Colour::BLACK;
        myPieces = b.getWhitePieces();
    } else if (colour == Colour::BLACK) {
        enemyKingColour = Colour::WHITE;
        myPieces = b.getBlackPieces();
    } 

    int origRow;
    int origCol;
    vector<vector<int>> levelTwoMoves;

    // For every Piece in own team's vector, add its possible capture or check moves to the map.
    for (int i = 0; i < myPieces.size(); ++i) {
        vector<vector<int>> myPossibleMoves = myPieces[i]->checkPossibleMoves(b);
        vector<vector<int>> enPassantAttacks = myPieces[i]->checkEnPassantMoves(b);

        // Set the coordinates of the i'th Piece.
        origRow = myPieces[i]->getRow();
        origCol = myPieces[i]->getCol();

        for (int j = 0; j < enPassantAttacks.size(); ++j) {
            if (enPassantAttacks[j][0] == -1 && enPassantAttacks[j][1] == -1) {
                break;
            }
            if (b.getPiece(origRow, origCol)->checkForCheckPreMove(b, enPassantAttacks[j][0], enPassantAttacks[j][1])) {
                levelTwoMoves.push_back(enPassantAttacks[j]);                
            }
        }


        // For each move in the possible moves of our i'th Piece, check if they can perform a check or capture.
        for (int j = 0; j < myPossibleMoves.size(); ++j) {
            // Set the coordinates of the current move in consideration.
            int newRow = myPossibleMoves[j][0];
            int newCol = myPossibleMoves[j][1];

            // Keep track of the empty square/Piece we are temporarily removing by capture.
            Piece * capturedSquare = b.getPiece(newRow, newCol);
            b.placePieceTemporarily(origRow, origCol, newRow, newCol);

            // Check that making this move does not put our King in check.
            if (!b.checkIfInCheck(colour)) {
                // If the square we moved to had an enemy Piece on it, add it as a move. 
                // We already know the Piece must be on enemy colour because we only check valid moves.
                if (capturedSquare) {
                    levelTwoMoves.emplace_back(vector<int>{newRow, newCol});
                } else {  // We must be moving to an empty square.
                    // If we are putting the enemy King in check by moving to that square, add it as a move.
                    if (b.checkIfInCheck(enemyKingColour)) {
                        levelTwoMoves.emplace_back(vector<int>{newRow, newCol});
                    }
                }
            }
            b.placePieceTemporarily(newRow, newCol, origRow, origCol); // undo moved piece's move
            b.setPiece(capturedSquare, newRow, newCol); 
        }
        // If the current piece has moves that do not put friendly king under attack AND captures or checks, add to map.
        if (levelTwoMoves.size() > 0) {
            levelTwoPieces[myPieces[i]] = levelTwoMoves;
            levelTwoMoves.clear();
        }
    }
    return levelTwoPieces; 
}

// This function is called on our own coloured king.
map<Piece *, vector<vector<int>>> Computer::avoidCaptureMoves(Board & b) {
    // Keep track of our Coloured Pieces and the enemy's Pieces.
    vector<vector<int>> levelThreeMoves;
    map<Piece *, vector<vector<int>>> levelThreePieces;
    vector<Piece *> myPieces;
    Colour colour = getColour();
    int kingRow;
    int kingCol;

    if (colour == Colour::WHITE) {
        kingRow = b.getWhiteKing()->getRow();
        kingCol = b.getWhiteKing()->getCol();
        myPieces = b.getWhitePieces();
    } else if (colour == Colour::BLACK) {
        kingRow = b.getBlackKing()->getRow();
        kingCol = b.getBlackKing()->getCol();
        myPieces = b.getBlackPieces();
    } 

    int origRow;
    int origCol;

    // For every Piece in our team, add all possible evasion moves to the map.
    for (int i = 0; i < myPieces.size(); ++i) {
        vector<vector<int>> myPossibleMoves = myPieces[i]->checkPossibleMoves(b);
        origRow = myPieces[i]->getRow();
        origCol = myPieces[i]->getCol();
        bool underAttack = !myPieces[i]->checkAttackingMe(b, origRow, origCol, colour).empty();
        if (!underAttack) {
            continue;
        };

        for (int j = 0; j < myPossibleMoves.size(); ++j) {
            int newRow = myPossibleMoves[j][0];
            int newCol = myPossibleMoves[j][1];

            // Check that making this move will not put our own King in check.
            Piece * replacedPiece = b.getPiece(newRow, newCol);  // Keep track of the Piece/square we are temporarily removing.
            b.placePieceTemporarily(origRow, origCol, newRow, newCol);
            vector<Piece *> piecesAttackingFriendlyKing = myPieces[i]->checkAttackingMe(b, kingRow, kingCol, colour);
            if (!piecesAttackingFriendlyKing.empty()) {
                b.placePieceTemporarily(newRow, newCol, origRow, origCol); // Undo moved piece's move.
                b.setPiece(replacedPiece, newRow, newCol);  // Set replaced piece back.
                continue;
            }

            bool notUnderAttack = myPieces[i]->checkAttackingMe(b, newRow, newCol, colour).empty();
            if (notUnderAttack) {
                levelThreeMoves.emplace_back(vector<int>{newRow, newCol});
            }

            b.placePieceTemporarily(newRow, newCol, origRow, origCol); // Put the Piece back to where it came from.
            b.setPiece(replacedPiece, newRow, newCol); // Replace the Piece we temporarily removed.
        }

        // If the current piece has moves that do not put friendly king under attack AND avoids capture, add to map of possible moves. 
        if (levelThreeMoves.size() > 0) {
            levelThreePieces[myPieces[i]] = levelThreeMoves;
            levelThreeMoves.clear();
        }
    }
    return levelThreePieces; 
}

bool Computer::levelOne(Board & b, bool whiteTurn) {
    vector <Piece *> pieces;

    if (whiteTurn) {
        pieces = b.getWhitePieces();
    } else {
        pieces = b.getBlackPieces();
    }

    while (pieces.size() > 0) {
        srand (time(NULL));
        int randPieceIndex = rand() % pieces.size();
        
        // Generate all possible moves for the piece.
        vector <vector <int>> possibleMoves = pieces[randPieceIndex]->checkPossibleMoves(b);
        int origRow = pieces[randPieceIndex]->getRow();
        int origCol = pieces[randPieceIndex]->getCol();

        if (possibleMoves.size() > 0) {
            srand (time(NULL));
            int randMove = rand() % possibleMoves.size();
            
            int newRow = possibleMoves[randMove][0];
            int newCol = possibleMoves[randMove][1];
            
            // Check the random move puts friendly King in check.
            bool validMove = pieces[randPieceIndex]->checkForCheckPreMove(b, newRow, newCol);

            // Check if the random move must perform pawn promotion. 
            bool validPromotion = pieces[randPieceIndex]->checkForPromotion(newRow);

            if (validMove) {
                pieces[randPieceIndex]->placePiece(b, newRow, newCol);  // Place piece if valid move. 
                if (validPromotion) {                    // Promote piece if necessary by generating random piece to promote to. 
                    srand (time(NULL));
                    int randPieceType = rand() % promotionPieces.size();
                    b.promotePiece(whiteTurn, newRow, newCol, promotionPieces[randPieceType]); 
                }
                b.setLastMove(origRow, origCol, newRow, newCol);
                return true;           
            } else {  // If the move puts friendly King in check, remove it from the possible moves. 
                for (auto it = possibleMoves.begin(); it != possibleMoves.end(); ++it) {
                    if (*it == possibleMoves[randMove]) {
                        possibleMoves.erase(it);
                        break;
                    }
                }                   
            }
        } else {  // If there are no moves available for the piece, remove it from the set of pieces eligible to move. 
            for (auto it = pieces.begin(); it != pieces.end(); ++it) {
                if (*it == pieces[randPieceIndex]) {
                    pieces.erase(it);
                    break;
                }
            }
        }
    }
    return false;  // No possible move has been found. 
}

bool Computer::levelTwo(Board & b, bool whiteTurn) {    
    map<Piece *, vector<vector<int>>> levelTwoMoves; // Map of friendly Pieces and all their possible moves.
    levelTwoMoves = captureOrAttackMoves(b);

    if (levelTwoMoves.size() == 0) return levelOne(b, whiteTurn);

    // Generate a random move in levelTwoMoves.
    srand (time(NULL));
    int randPieceIdx = rand() % levelTwoMoves.size();
    int counter = 0;

    // Generate a random Piece from all possible Pieces in levelTwoMoves until a valid random move is found.
    for (auto &p: levelTwoMoves) {
        if (counter == randPieceIdx) {
            // Generate a random move from the array of possible moves of the random Piece.
            srand (time(NULL));
            int randMove = rand() % (p.second).size();
            vector<int> move = p.second[randMove];
            int origRow = p.first->getRow();
            int origCol = p.first->getCol();
            int newRow = move[0];
            int newCol = move[1];
            b.getPiece(p.first->getRow(), p.first->getCol())->placePiece(b, newRow, newCol);

            // Checks if the Piece is a Pawn and is able to promote.
            bool validPromotion = b.getPiece(newRow, newCol)->checkForPromotion(newRow);
            if (validPromotion) {
                // Generates a random Piece to promote to.
                srand (time(NULL));
                int randPieceType = rand() % promotionPieces.size();
                b.promotePiece(whiteTurn, newRow, newCol, promotionPieces[randPieceType]);
            }
            // Keep track of last move for enpassant purposes. 
            b.setLastMove(origRow, origCol, newRow, newCol);
            return true;           
        }
        ++counter;
    }

    // If no possible moves are found, generate a move from Level One.
    return levelOne(b, whiteTurn);
}

bool Computer::levelThree(Board & b, bool whiteTurn) {
    vector <Piece *> myPieces;
    vector<Piece *> underAttack; // Array of friendly Pieces under attack.
    vector<vector<int>> possibleMoves;
    map<Piece *, vector<vector<int>>> levelThreeMoves; // Map of friendly Pieces and all their possible moves.

    levelThreeMoves = avoidCaptureMoves(b);

    // If no moves are found, generate a Level Two move.
    if (levelThreeMoves.size() == 0) {
        return levelTwo(b, whiteTurn);
    }

    // Generate a random index to choose a Piece from levelThreeMoves.
    srand (time(NULL));
    int randPieceIdx = rand() % levelThreeMoves.size();
    int counter = 0;

    for (auto &p: levelThreeMoves) {
        if (counter == randPieceIdx) {
            // Generate a random move from the vector of possible moves for the Piece.
            srand (time(NULL));
            int randMove = rand() % (p.second).size();

            vector<int> move = p.second[randMove];
            int origRow = p.first->getRow();
            int origCol = p.first->getCol();
            int newRow = move[0];
            int newCol = move[1];
            b.getPiece(p.first->getRow(), p.first->getCol())->placePiece(b, newRow, newCol);

            // Checks if the Piece is a Pawn and is able to promote.
            bool validPromotion = b.getPiece(newRow, newCol)->checkForPromotion(newRow);
            if (validPromotion) {
                // Generates a random Piece to promote to.
                srand (time(NULL));
                int randPieceType = rand() % promotionPieces.size();
                b.promotePiece(whiteTurn, newRow, newCol, promotionPieces[randPieceType]);
            }
            // Keep track of last move for enpassant purposes. 
            b.setLastMove(origRow, origCol, newRow, newCol);
            return true;
        }
        ++counter;
    }

    // If no moves are found, generate a Level Two move.
    return levelTwo(b, whiteTurn);
}

// Helper function to convert each piece type to its value. 
int convertTypeToScore(PieceType type) {
    if (type == PieceType::Queen) {
        return 4;
    } else if (type == PieceType::Rook) {
        return 3;
    } else if (type == PieceType::Bishop) {
        return 2;
    } else if (type == PieceType::Knight) {
        return 1;
    } else {
        return 0;
    }
}

bool Computer::levelFour(Board &b, bool whiteTurn) {
    // Moves that capture or puts enemy King under attack. 
    map<Piece *, vector<vector<int>>> capturesOrAttacks = captureOrAttackMoves(b);  

    if (capturesOrAttacks.size() == 0) return levelThree(b, whiteTurn);

    int bestScore = -1;
    vector<int>bestMove = {-1, -1, -1, -1};   // Vector of bestMove with original row, original column, new row, new column.
    
    for (auto & p: capturesOrAttacks) {
        int origRow = p.first->getRow();
        int origCol = p.first->getCol();

        for (int i = 0; i < p.second.size(); ++i) {
            int newRow = p.second[i][0];
            int newCol = p.second[i][1];
            Piece * currPiece = b.getPiece(origRow, origCol);  // Keep track of piece that makes the move. 
            Piece * targetPiece = b.getPiece(newRow, newCol);  // Keep track of target piece. 
            int score = 0;
            if (targetPiece) {  
                score = convertTypeToScore(targetPiece->getState());
            } 
            if (score > bestScore) {
                bool validMove = currPiece->checkForCheckPreMove(b, newRow, newCol);

                if (validMove) {
                    bestScore = score;
                    bestMove = vector<int>{origRow, origCol, newRow, newCol};
                }
            }
        }
    }
    
    // Check if the piece is eligible for pawn promotion. 
    bool validPromotion = b.getPiece(bestMove[0], bestMove[1])->checkForPromotion(bestMove[2]);
    b.getPiece(bestMove[0], bestMove[1])->placePiece(b, bestMove[2], bestMove[3]);
    
    // Promote pawn to Queen if eligible for pawn promotion.
    if (validPromotion) {
        b.promotePiece(whiteTurn, bestMove[2], bestMove[3], PieceType::Queen);
    }
    
    b.setLastMove(bestMove[0], bestMove[1], bestMove[2], bestMove[3]);
    return true;
}

Computer::~Computer() {}
