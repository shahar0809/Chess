#pragma once
#include "Piece.h"

class Piece;
class Board;

class King : public Piece
{
public:
	//c'tor and d'tor
	King(std::string location, bool isBlack);
	~King();

	// virtual methods (from Piece)
	virtual bool isMoveValidPiece(std::string move, std::vector<Piece*> pieces);
	virtual char pieceType();
	bool isAttacked(Board& board);
};

