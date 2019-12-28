#pragma once
#include <vector>
#include <string>
#include "Piece.h"


#define MAX_INDEX_COL 'h'
#define MAX_INDEX_ROW '8'
#define MIN_INDEX_COL 'a'
#define MIN_INDEX_ROW '1'
#define BOARD_SIZE 8
#define STARTING_BOARD "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR"


class Piece;
class Rook;
class King;


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
	void setBoard(unsigned char x, unsigned char y, char piece);
	void setCurrPlayer(unsigned int newCurrPlayer);
	unsigned int getCurrPlayer();
	CODES isMoveValid(std::string move);
	Piece* getPiece(std::string location);
	King* getKing(bool isBlack);
	bool isKingAttacked(King* king);
};

