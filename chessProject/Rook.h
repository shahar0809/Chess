#pragma once
#include "Piece.h"

class Piece;

class Rook : public Piece
{
public:
	//c'tor and d'tor
	Rook(std::string location, bool isBlack);
	~Rook();

	// virtual methods (from Piece)
	virtual bool isMoveValidPiece(std::string move);
	virtual char pieceType();
};

