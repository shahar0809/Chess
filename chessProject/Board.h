#pragma once
#include <vector>
#include "Piece.h"

#define BOARD_SIZE 8

class Board
{
private:
	std::string _board[BOARD_SIZE];
	std::vector<Piece*> _alivePieces;

public:
	// c'tor and d'tor
	Board();
	~Board();

	// methods
	Piece* getPiece(std::string location);
	std::string* getBoard();
	std::vector<Piece*> getAlivePieces();
	void removePiece(std::string location);
	void setBoard(unsigned char x, unsigned char y, char piece);
};

