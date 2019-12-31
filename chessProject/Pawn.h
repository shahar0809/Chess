#pragma once
#include "Piece.h"

class Pawn : public Piece
{
private:
	bool _isFirstMove;

public:
	Pawn(std::string location, bool isBlack);
	~Pawn();

	// setter
	void setIsFirstMove(bool isFirstMove);

	// virtual methods (from Piece)
	virtual bool isMoveValidPiece(std::string move);
	virtual char pieceType();
};

