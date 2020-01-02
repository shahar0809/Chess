#include "checkmate.h"

CODES checkmate::isCheckmate(Board& board, King* otherKing, Piece* attacker)
{
	std::string kingLocation = otherKing->getCurrLocation();
	bool isEscapingPath = false;
	bool canAttackerBeEated = false;
	isEscapingPath = (NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[COL] + 1)) + kingLocation[ROW])&& 
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[COL] -1)) + kingLocation[ROW]) &&
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[COL] + 1)) + ((char)(kingLocation[ROW] + 1))) && 
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[COL] + 1)) + ((char)(kingLocation[ROW] -1))) &&
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[COL] - 1)) + ((char)(kingLocation[ROW] - 1))) && 
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[COL] - 1)) + ((char)(kingLocation[ROW] + 1))) &&
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + kingLocation[COL] + ((char)(kingLocation[ROW] - 1))) &&
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + kingLocation[COL] + ((char)(kingLocation[ROW] - 1))));
	
	/*Checking if the attacker can be eaten.*/
	for (int i = 0; (i < board.getPieces().size()) && !canAttackerBeEated; i++)
	{
		if (NO_PIECE_IN_SRC > board.isMoveValid(board.getPieces()[i]->getCurrLocation() + attacker->getCurrLocation()))
		{
			canAttackerBeEated = true;
		}
	}

	/*
	insert code here
	*/

	if (!isEscapingPath && !canAttackerBeEated)
	{
		return CHECKMATE_MOTHER_F$$KER;
	}
	return VALID_MOVE;
}
