#include "checkmate.h"

CODES checkmate::isCheckmate(Board& board, King* otherKing, Piece* attacker)
{
	std::string kingLocation = otherKing->getCurrLocation();
	std::string attackerLocation = "";
	std::string squareBetween = "";
	std::string move = "";
	bool isEscapingPath = false;
	bool canAttackerBeEated = false;
	char pieceType = attacker->pieceType();
	bool isBlockingPiece = false;
	int colon = 0;
	int row = 0;
	int diagonal = 0;
	isEscapingPath = (NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[COL] + 1)) + kingLocation[ROW])&& 
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[COL] -1)) + kingLocation[ROW]) &&
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[COL] + 1)) + ((char)(kingLocation[ROW] + 1))) && 
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[COL] + 1)) + ((char)(kingLocation[ROW] -1))) &&
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[COL] - 1)) + ((char)(kingLocation[ROW] - 1))) && 
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[COL] - 1)) + ((char)(kingLocation[ROW] + 1))) &&
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + kingLocation[COL] + ((char)(kingLocation[ROW] - 1))) &&
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + kingLocation[COL] + ((char)(kingLocation[ROW] - 1))));
	
	attackerLocation += attacker->getCurrLocation();

	/*Checking if the attacker can be eaten.*/

	board.setCurrPlayer(!board.getCurrPlayer()); // Check moves of oppenet.

	for (int i = 0; (i < board.getPieces().size()) && !canAttackerBeEated; i++)
	{
		if (NO_PIECE_IN_SRC > board.isMoveValid(board.getPieces()[i]->getCurrLocation() + attackerLocation))
		{
			canAttackerBeEated = true;
		}
	}

	if (pieceType == BLACK_PAWN || pieceType == WHITE_PAWN || pieceType == BLACK_KNIGHT || pieceType == WHITE_KNIGHT)
	{
		isBlockingPiece = false;
	}
	else
	{
		colon = attackerLocation[COL] - kingLocation[COL];
		row = attackerLocation[ROW] - kingLocation[ROW];

		if (colon != 0)
		{
			colon = colon < 0 ? -1 : 1;
		}
		if (row != 0)
		{
			row = row < 0 ? -1 : 1;
		}
		squareBetween = kingLocation;
		
		while (squareBetween != attackerLocation)
		{
			
			squareBetween[ROW] += row;
			squareBetween[COL] += colon;
			if (squareBetween != attackerLocation)
			{
				for (int i = 0; (i < board.getPieces().size()) && !isBlockingPiece; i++)
				{
					move = board.getPieces()[i]->getCurrLocation() + squareBetween;
					if (NO_PIECE_IN_SRC > board.isMoveValid(move))
					{
						isBlockingPiece = true;
					}
				}
			}			
		}
		board.setCurrPlayer(!board.getCurrPlayer());
		
	}
	
	/*
	insert code here
	*/

	if (!isEscapingPath && !canAttackerBeEated && !isBlockingPiece)
	{
		return CHECKMATE_MOTHER_F$$KER;
	}
	return VALID_MOVE_CHECK;
}
