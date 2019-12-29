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
	
	return stepsSideways ^ stepsForwardOrBackward;


	/*
	std::string src = move.substr(0, move.length() / 2);
	std::string dst = move.substr(DEST_COL, move.length() / 2);
	std::string currLocation = "00";
	char row = '0', col = '0', max = '0';
	bool blockingPieceFound = false;

	if (0 == numOfSteps)
	{
		return false;
	}

	/*Same column
	if (move[SRC_COL] == move[DEST_COL])
	{
		currLocation[SRC_COL] = move[SRC_COL];
		row = move[SRC_ROW] < move[DEST_ROW] ? move[SRC_ROW] : move[DEST_ROW];
		max = move[SRC_ROW] > move[DEST_ROW] ? move[SRC_ROW] : move[DEST_ROW];

		/*Checking if there's a piece between the src piece and the dest piece (in all the rows between them).
		for (row; row < max; row++)
		{
			currLocation[SRC_ROW] = row;


			for (int i = 0; i < pieces.size() || blockingPieceFound; i++)
			{
				if (pieces[i]->getCurrLocation() == currLocation)
					blockingPieceFound = true;
			}

			if (blockingPieceFound)
			{
				return false;
			}
			blockingPieceFound = false;
		}
	}
	/*Same row
	else
	{
		currLocation[SRC_ROW] = move[SRC_ROW];
		col = move[SRC_COL] < move[DEST_COL] ? move[SRC_COL] : move[DEST_COL];
		max = move[SRC_COL] > move[DEST_COL] ? move[SRC_COL] : move[DEST_COL];

		/*Checking if there's a piece between the src piece and the dest piece (in all the rows between them).
		for (col; col < max; col++)
		{
			currLocation[SRC_COL] = col;

			for (int i = 0; i < pieces.size() || blockingPieceFound; i++)
			{
				if (pieces[i]->getCurrLocation() == currLocation)
					blockingPieceFound = true;
			}

			if (blockingPieceFound)
			{
				return false;
			}
	
			blockingPieceFound = false;
		}
	}
	return true;*/
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
