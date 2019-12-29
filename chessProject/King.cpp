#include "King.h"

King::King(std::string location, bool isBlack) : Piece(location, isBlack)
{
}

King::~King()
{
}

bool King::isMoveValidPiece(std::string move, std::vector<Piece*> pieces)
{
	return true;
}

char King::pieceType()
{
	if (this->isBlack())
	{
		return BLACK_KING;
	}
	else
	{
		return WHITE_KING;
	}
}

bool King::isAttacked(Board& board)
{
	return false;
}
