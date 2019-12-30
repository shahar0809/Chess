#pragma once
#include "Piece.h"

class Bishop : public Piece
{
public:
	// c'tor and d'tor
	Bishop(std::string location, bool isBlack);
	~Bishop();

	// virtual methods (from Piece)
	virtual bool isMoveValidPiece(std::string move);
	virtual char pieceType();
};

