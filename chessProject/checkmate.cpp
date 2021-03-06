#include "checkmate.h"

/*
This method checks if there is a checkmate.
Input: The board (a Board object), the king of the opponet (a pointer to King), the attacking piece (a pointer to Piece).
Output: If there is a checkmate - checkmate code / else - check code (CODES enum);
*/
CODES checkmate::isCheckmate(Board& board, King* otherKing, Piece* attacker)
{
	if (!attacker)
	{
		return VALID_MOVE_CHECK;
	}
	std::string kingLocation = otherKing->getCurrLocation(), attackerLocation = attacker->getCurrLocation(), squareBetween = kingLocation, move = "";
	bool isEscapingPath = false, canAttackerBeEated = false, isBlockingPiece = false;
	bool isCheckMate = false;

	/*Checking for a valid move to escape the attacker (checking if there's a valid King move for all possible destinations).*/

	board.setCurrPlayer(!board.getCurrPlayer()); // Check moves of the oppenet.

	isEscapingPath =
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[SRC_COL] + 1)) + kingLocation[SRC_ROW]) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[SRC_COL] - 1)) + kingLocation[SRC_ROW]) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[SRC_COL] + 1)) + ((char)(kingLocation[SRC_ROW] + 1))) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[SRC_COL] + 1)) + ((char)(kingLocation[SRC_ROW] - 1))) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[SRC_COL] - 1)) + ((char)(kingLocation[SRC_ROW] - 1))) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + ((char)(kingLocation[SRC_COL] - 1)) + ((char)(kingLocation[SRC_ROW] + 1))) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + kingLocation[SRC_COL] + ((char)(kingLocation[SRC_ROW] - 1))) ||
		NO_PIECE_IN_SRC > board.isMoveValid(kingLocation + kingLocation[SRC_COL] + ((char)(kingLocation[SRC_ROW] - 1)));

	board.setCurrPlayer(!board.getCurrPlayer());
	std::cout << isEscapingPath << std::endl;
	/*Checking if the attacker can be eaten.*/

	for (int i = 0; (i < board.getPieces().size()) && !canAttackerBeEated; i++)
	{
		if (NO_PIECE_IN_SRC > board.isMoveValid(board.getPieces()[i]->getCurrLocation() + attackerLocation))
		{
			canAttackerBeEated = true;
		}
	}


	isBlockingPiece = pieceBetween(attackerLocation, kingLocation, board);

	board.setCurrPlayer(!board.getCurrPlayer()); // Return the turn to the player.

	isCheckMate = ((!isEscapingPath) && (!canAttackerBeEated) && (!isBlockingPiece));


	return isCheckMate ? CHECKMATE_MOTHER_F$$KER : VALID_MOVE_CHECK;


	return !isEscapingPath && !canAttackerBeEated && !pieceBetween(attackerLocation, kingLocation, board) ? CHECKMATE_MOTHER_F$$KER : VALID_MOVE_CHECK;
}

/*
This method checks if a piece of the current player can be moved to block the move between the src piece and the dest piece.
Input: The src location (string), the dst location (string), the board (a Board object).
Output: Whether a piece can be moved to block the move or not.
*/
bool checkmate::pieceBetween(std::string src, std::string dst, Board& board)
{
	Piece* srcPiece = board.getPiece(src), *dstPiece = board.getPiece(dst);
	std::string squareBetween = dst, move = "";
	int colon = src[COL] - dst[COL], row = src[ROW] - dst[ROW];
	bool isBlockingPiece = false;
	char pieceType = srcPiece->pieceType();

	if (pieceType == BLACK_PAWN || pieceType == WHITE_PAWN || pieceType == BLACK_KNIGHT || pieceType == WHITE_KNIGHT)
	{
		return false;
	}

	/*Setting the change factors to go over the squares between the king and the attacker.*/
	if (colon != 0)
	{
		colon = colon < 0 ? -1 : 1;
	}
	if (row != 0)
	{
		row = row < 0 ? -1 : 1;
	}

	/*Going over all the squares bewteen the src piece and the dst piece.*/
	while (squareBetween != src)
	{
		/*Moving to the next square.*/
		squareBetween[ROW] += row;
		squareBetween[COL] += colon;

		if (squareBetween != src)
		{
			/*Checking if a piece of the curren tplayer can be moved to the current square.*/
			for (int i = 0; (i < board.getPieces().size()) && !isBlockingPiece; i++)
			{
				move = board.getPieces()[i]->getCurrLocation() + squareBetween; // A move from the current piece to the current square.
				if (NO_PIECE_IN_SRC > board.isMoveValid(move))
				{
					isBlockingPiece = true;
				}
			}
		}
	}
	return isBlockingPiece;
}