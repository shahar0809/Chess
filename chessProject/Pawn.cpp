#include "Pawn.h"

Pawn::Pawn(std::string location, bool isBlack) : Piece(location, isBlack)
{
	this->_isFirstMove = true;
}

Pawn::~Pawn()
{
}

// Returning the symbol of the Pawn.
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

/*
Checks if the move is valid for a Pawn.
Input: The move (string).
Output: Whether the move is valid or not.
*/
bool Pawn::isMoveValidPiece(std::string move)
{
	int deltaY = move[DEST_ROW] - move[SRC_ROW], deltaX = move[DEST_COL] - move[SRC_COL],
		isBlackP = this->isBlack() ? -1 : 1;

	/*Allowing two steps forwards if it's the pawn first move.*/
	if (this->_isFirstMove)
	{
		return (!deltaX && (deltaY == 1 * isBlackP || deltaY == 2 * isBlackP)) || (deltaY == 1 * isBlackP && abs(deltaX) == 1);
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