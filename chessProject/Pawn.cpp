#include "Pawn.h"

Pawn::Pawn(std::string location, bool isBlack) : Piece(location, isBlack)
{
	this->_isFirstMove = true;
}

Pawn::~Pawn()
{
}

char Pawn::pieceType()
{
	if (this->isBlack())
	{
		return BLACK_PAWN;;
	}
	else
	{
		return WHITE_PAWN;
	}
}

bool Pawn::isMoveValidPiece(std::string move)
{
	if (this->_isFirstMove)
	{
		return ((move[SRC_COL] == move[DEST_COL] && abs(move[SRC_ROW] - move[DEST_ROW]) == 1) ||
			(abs(move[SRC_ROW] - move[DEST_ROW]) == 2) ||
			(abs(move[SRC_COL] - move[DEST_COL]) == 1 && abs(move[SRC_ROW] - move[DEST_ROW]) == 1));
	}
	else
	{
		/*If it's a normal move (forword / backwards) or if it's an eating move (diagnolly)*/
		return ((move[SRC_COL] == move[DEST_COL] && abs(move[SRC_ROW] - move[DEST_ROW]) == 1) ||
			(abs(move[SRC_COL] - move[DEST_COL]) == 1 && abs(move[SRC_ROW] - move[DEST_ROW]) == 1));
	}
}

void Pawn::setIsFirstMove(bool isFirstMove)
{
	this->_isFirstMove = isFirstMove;
}
