#include "Knight.h"

Knight::Knight(std::string move, bool isBlack) : Piece(move, isBlack)
{
}

Knight::~Knight()
{
}

bool Knight::isMoveValidPiece(std::string move)
{
	return moveValidator::knightMove(move);
}

char Knight::pieceType()
{
	if (this->isBlack())
	{
		return BLACK_KNIGHT;
	}
	else
	{
		return WHITE_KNIGHT;
	}
}
