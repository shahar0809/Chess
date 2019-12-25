#include "King.h"

bool King::isMoveValidPiece(std::string move)
{

}

void King::move(std::string move, Board& board)
{

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

}
