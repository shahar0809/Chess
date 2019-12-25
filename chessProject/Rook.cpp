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
bool Rook::isMoveValidPiece(std::string move, Board& board)
{
	int numOfSteps = moveValidator::moveSideways(move), col = 0, row = 0, max = 0;
	Piece* currPiece = NULL;
	std::string currLocation = "  ";

	/*If the move isn't sideways, then the move isn't valid.*/
	if (numOfSteps == 0)
	{
		return false;
	}
	
	/*Same column*/
	if (move[SRC_COL] == move[DEST_COL])
	{
		currLocation[SRC_COL] = move[SRC_COL];
		row = move[SRC_ROW] < move[DEST_ROW] ? move[SRC_ROW] : move[DEST_ROW];
		max = move[SRC_ROW] > move[DEST_ROW] ? move[SRC_ROW] : move[DEST_ROW];

		/*Checking if there's a piece between the src piece and the dest piece (in all the rows between them).*/
		for (row; row < max; row++)
		{
			currLocation[SRC_ROW] = row;
			if (board.getPiece(currLocation))
			{
				return false;
			}
		}
	}
	/*Same row*/
	else
	{
		currLocation[SRC_ROW] = move[SRC_ROW];
		col = move[SRC_COL] < move[DEST_COL] ? move[SRC_COL] : move[DEST_COL];
		max = move[SRC_COL] > move[DEST_COL] ? move[SRC_COL] : move[DEST_COL];

		/*Checking if there's a piece between the src piece and the dest piece (in all the columns between them).*/
		for (col; col < max; col++)
		{
			currLocation[SRC_COL] = col;
			if (board.getPiece(currLocation))
			{
				return false;
			}
		}
	}

	return true;
}

/*
This function moves the rook on the board according to the move inputted.
Input: The move (string), and the board (a reference to a Board object).
Output: None.
*/
void Rook::movePiece(std::string move, Board& board)
{
	int numOfSteps = moveValidator::moveSideways(move);
	
	// setting the new location of the rook
	if (move[SRC_COL] == move[DEST_COL])
	{
		this->_currLocation[SRC_ROW] += moveValidator::moveSideways(move);
	}
	else
	{
		this->_currLocation[SRC_COL] += moveValidator::moveSideways(move);
	}

	// Moving the rook on the board
	board.setBoard(move[SRC_ROW], move[SRC_COL], '#');
	board.setBoard(move[DEST_ROW], move[DEST_COL], this->pieceType());
}

/*
This function returns Rook's type, 'R' for a white rook, and 'r' for a black one.
Input: None.
Output: The rook's type (char).
*/
char Rook::pieceType()
{
	if (this->isBlack)
	{
		return BLACK_ROOK;
	}
	else
	{
		return WHITE_ROOK;
	}
}
