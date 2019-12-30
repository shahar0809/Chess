#include "Rook.h"

// c'tor
Rook::Rook(std::string location, bool isBlack) : Piece(location, isBlack)
{
}

// d'tor
Rook::~Rook()
{

}

/*
The method checks if the move inputted is valid for a rook.
Input: The move (string)
Output: Valid - true / Invalid - false
*/
bool Rook::isMoveValidPiece(std::string move)
{
	int stepsSideways = moveValidator::moveSideways(move);
	int stepsForwardOrBackward = moveValidator::moveBackOrForward(move);
	
	if ((!stepsSideways && stepsForwardOrBackward) || (stepsSideways && !stepsForwardOrBackward))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
This function returns Rook's type, 'R' for a white rook, and 'r' for a black one.
Input: None.
Output: The rook's type (char).
*/
char Rook::pieceType()
{
	if (this->isBlack())
	{
		return BLACK_ROOK;
	}
	else
	{
		return WHITE_ROOK;
	}
}
