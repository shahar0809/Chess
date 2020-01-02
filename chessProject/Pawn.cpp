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
	int deltaY = 0;
	int deltaX = 0;
	int isBlackP = 0;


	isBlackP = this->isBlack();
	isBlackP = isBlackP ? -1 : 1;
	deltaY = move[DEST_ROW] - move[SRC_ROW];
	deltaX = move[DEST_COL] - move[SRC_COL];

	if (this->_isFirstMove)
	{
		return (!deltaX && (deltaY == 1*isBlackP || deltaY == 2*isBlackP)) || (deltaY == 1 * isBlackP && abs(deltaX) == 1);
	}
	else
	{
		/*If it's a normal move (forword / backwards) or if it's an eating move (diagnolly)*/
		return (!deltaX && deltaY == 1 * isBlackP) || (deltaY == 1 * isBlackP && abs(deltaX) == 1);
	}
}

void Pawn::setIsFirstMove(bool isFirstMove)
{
	this->_isFirstMove = isFirstMove;
}
