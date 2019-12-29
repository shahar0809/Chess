#pragma once
#include <vector>
#include <string>
#include "Piece.h"

#define BOARD_SIZE 8
#define STARTING_BOARD "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR"


class Piece;
class Rook;
class King;
class pieceVectorMethods;

class Board
{
private:
	std::string _board[BOARD_SIZE];
	std::vector<Piece*> _pieces;
	unsigned int _currPlayer;

public:
	// c'tor and d'tor
	Board();
	~Board();

	// methods
	std::string* getBoard();
	void setBoard(char x, char y, char piece);
	void setCurrPlayer(unsigned int newCurrPlayer);
	unsigned int getCurrPlayer();
	CODES isMoveValid(std::string move);
	
	bool isKingAttacked(King* king);
	unsigned int getNumOfPieces();
	std::vector<Piece*> getPieces();
	void printBoard();
	void addPiece(Piece* piece);
	bool removePiece(std::string location);
	Piece* getPiece(std::string location);
	unsigned int makeMove(std::string move);
	King* getKing(bool isBlack);
};

