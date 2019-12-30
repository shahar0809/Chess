#pragma once
#include "Piece.h"

class Knight : public Piece
{
public:
	Knight(std::string move, bool isBlack);
	~Knight();

	// virtual methods (from Piece)
	virtual bool isMoveValidPiece(std::string move);
	virtual char pieceType();
};

