#pragma once
#include "Piece.h"

class Rook : public Piece
{
	//c'tor and d'tor
	Rook(std::string location, bool isBlack);
	~Rook();

	// virtual methods (from Piece)
	virtual bool isMoveValidPiece(std::string move, Board& board);
	virtual void movePiece(std::string move, Board& board);
	virtual char pieceType();
};

