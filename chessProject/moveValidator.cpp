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
	// Same row.
	if (move[DEST_ROW] == move[SRC_ROW])
	{
		// If on the same column as well.
		return move[DEST_COL] - move[SRC_COL];
	}
	return 0;

}

/*
This static function checks if a move is backwards or forwards.
Input: moving string.
Output: Returns the number of squares moved backwards or forwards. negative sign represents decrease of board position value.
*/
int moveValidator::moveBackOrForward(std::string move)
{
	// Same column.
	if (move[DEST_COL] == move[SRC_COL])
	{
		// If on the same row as well.
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
	int deltaX = move[DEST_COL] - move[SRC_COL];
	int deltaY = move[DEST_ROW] - move[SRC_ROW];

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
	int side = moveSideways(move); //Negative, in case of diagonal value refered only by forward or backwards moves.
	int forward = moveBackOrForward(move);
	int diagonal = moveDiagonally(move);

	/*If the move is not a single one, and isn't a diagonal, backwards, forwards or sideways move.*/
	if (((abs(side) > 1) || (abs(forward) > 1) || (abs(diagonal) > 1) || ((0 == forward) && (0 == side) && (0 == diagonal))))
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
	int deltaX = move[DEST_ROW] - move[SRC_ROW]; //change in x pos
	int deltaY = move[DEST_COL] - move[SRC_COL]; // change in y pos
	
	if (((1 == abs(deltaX)) && (KNIGHT_MOVING_PATTERN_NUM == abs(deltaY))) || ((KNIGHT_MOVING_PATTERN_NUM == abs(deltaX)) && (1 == abs(deltaY))))
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