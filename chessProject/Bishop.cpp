#include "Bishop.h"

Bishop::Bishop(std::string location, bool isBlack) : Piece(location, isBlack)
{
}

Bishop::~Bishop()
{
}

char Bishop::pieceType()
{
	if (this->isBlack())
	{
		return BLACK_BISHOP;
	}
	else
	{
		return WHITE_BISHOP;
	}
}

bool Bishop::isMoveValidPiece(std::string move)
{
	return moveValidator::moveDiagonally(move);
}