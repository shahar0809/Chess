#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
	// c'tor and d'tor
	Queen(std::string location, bool isBlack);
	~Queen();

	// virtual methods (from Piece)
	virtual bool isMoveValidPiece(std::string move);
	virtual char pieceType();
};

