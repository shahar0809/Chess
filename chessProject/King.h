#pragma once
#include "Piece.h"
class Piece;
class Board;

class King : public Piece
{
	//c'tor and d'tor
	King();
	~King();

public:
	// virtual methods (from Piece)
	virtual bool isMoveValidPiece(std::string move);
	virtual void move(std::string move, Board& board);
	virtual char pieceType();
	bool isAttacked(Board& board);
};

