#pragma once
#include <vector>
#include <string>
#include "Piece.h"
#include "King.h"

#define MAX_INDEX_COL 'h'
#define MAX_INDEX_ROW '8'
#define MIN_INDEX_COL 'a'
#define MIN_INDEX_ROW '1'
#define BOARD_SIZE 8
#define STARTING_BOARD "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR"

class Piece;
class King;

=======

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
	Piece* getPiece(std::string location);
	std::string* getBoard();
	std::vector<Piece*> getAlivePieces();
	bool removePiece(std::string location);
	void setBoard(unsigned char x, unsigned char y, char piece);
	void setCurrPlayer(unsigned int newCurrPlayer);
	unsigned int getCurrPlayer();

	King* getKing(bool isBlack);
	unsigned int makeMove(std::string move);
=======

};

