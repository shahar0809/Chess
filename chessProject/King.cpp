#include "King.h"

King::King(std::string location, bool isBlack) : Piece(location, isBlack)
{
}

King::~King()
{
}

CODES King::isMoveValidPiece(std::string move, Board& board, Game& game)
{
	return VALID_MOVE;
}

void King::movePiece(std::string move, Board& board)
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
	return false;
}
