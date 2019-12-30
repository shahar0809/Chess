#include "Queen.h"

Queen::Queen(std::string move, bool isBlack) : Piece(move, isBlack)
{
}

Queen::~Queen()
{
}

char Queen::pieceType()
{
	if (this->isBlack())
	{
		return BLACK_QUEEN;
	}
	else
	{
		return WHITE_QUEEN;
	}
}

bool Queen::isMoveValidPiece(std::string move)
{
	int stepsSideways = moveValidator::moveSideways(move),
		stepsForwardOrBackwards = moveValidator::moveBackOrForward(move),
		stepsDiagonally = moveValidator::moveDiagonally(move);

	/*The queen moves sideways, forward or backwards, or diagonally, but only one of these options each move.*/
	if (stepsSideways && !stepsForwardOrBackwards && !stepsDiagonally)
	{
		return true;
	}
	else if (!stepsSideways && stepsForwardOrBackwards && !stepsDiagonally)
	{
		return true;
	}
	else if (!stepsSideways && !stepsForwardOrBackwards && stepsDiagonally)
	{
		return true;
	}
	else
	{
		return false;
	}
}