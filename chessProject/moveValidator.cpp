#include "moveValidator.h"

//c'tor
moveValidator::moveValidator()
{

}

//d'tor
moveValidator::~moveValidator()
{

}

/*
This static function checks if a move is a sideways move.
Input: moving string.
Output: Returns the number of squares moved sideways. negative sign represents decrease of board position value.
*/
int moveValidator::moveSideways(std::string move)
{
	if (move[DEST_ROW] == move[SRC_ROW])
	{
		return move[DEST_COL] - move[SRC_COL];
	}
	return 0;

}

int moveValidator::moveBackOrForward(std::string move)
{
	if (move[DEST_COL] == move[SRC_COL])
	{
		return move[DEST_ROW] - move[SRC_ROW];
	}
	return 0;
}

/*
This static function checks if a move is a diagonal move.
Input: moving string.
Output: Returns the number of squares moved diagonaly. negative sign reprasants decrease of board position value.
*/
int moveValidator::moveDiagonally(std::string move)
{
	int stepCounter = 0; // Negative value refered only by forward or backwards moves.
	int deltaX = 0;
	int deltaY = 0;

	deltaX = move[DEST_COL] - move[SRC_COL];
	deltaY = move[DEST_ROW] - move[SRC_ROW];
	// 1 -> The incline of a diagonal movment. 
	if (1 == abs(double(deltaX)/deltaY)) //Convert to double to add accuracy.
	{
		stepCounter = deltaY;
	}
	return stepCounter;
}

/*
This static function checks if a move is only one square long.
Input: moving string.
Output: Returns 0 if not a single step,else 1, negative sign reprasants decrease of board position value.
*/
bool moveValidator::singleMove(std::string move)
{
	int side = 0; //Negative, in case of diagonal value refered only by forward or backwards moves.
	int forward = 0;

	side = moveSideways(move);
	forward = moveBackOrForward(move);
	
	if (abs(side) > 1 || abs(forward) > 1)
	{
		return false;
	}

	return true;
	
}

/*
This static function checks if a move is a knight move.
Input: moving string.
Output: Returns 1 if the move is a knight move. else 0 
*/
int moveValidator::knightMove(std::string move)
{
	int isKnightMove = 0;
	int deltaX = 0; //change in x pos
	int deltaY = 0;// change in y pos
	
	deltaX = move[DEST_ROW] - move[SRC_ROW];
	deltaY = move[DEST_COL] - move[SRC_COL];

	if (((1 == abs(deltaX)) && (KNIGHT_MOVING_PATTERN_NUm == abs(deltaY))) || ((KNIGHT_MOVING_PATTERN_NUm == abs(deltaX)) && (1 == abs(deltaY))))
	{
		isKnightMove = 1;
	}
	return isKnightMove;
}

/*
This static function checks if a move is a pawn eating move.
Input: moving string.
Output: Returns 1 if the move is a pawn eating move. else 0
*/
int moveValidator::pawnEatingMove(std::string move)
{
	int isPawnEating = 0;
	if (singleMove(move) && moveDiagonally(move))
	{
		isPawnEating = 1;
	}
	return 0;
}
