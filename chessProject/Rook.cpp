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
CODES Rook::isMoveValidPiece(std::string move, Board& board, Game& game)
{
	int numOfSteps = moveValidator::moveSideways(move), col = 0, row = 0, max = 0;
	std::string src = move.substr(0, move.length() / 2);
	std::string dst = move.substr(DEST_COL, move.length() / 2);
	Piece* srcPiece = game.getPiece(src);
	Piece* dstPiece = game.getPiece(dst);
	King* currKing = game.getKing(board.getCurrPlayer());
	King* otherKing = game.getKing(!board.getCurrPlayer());
	std::string currLocation = "  ";
	CODES code = VALID_MOVE;

	code = this->isMoveValid(move, board, srcPiece, dstPiece);

	/*Check if basic conditions weren't met.*/
	if (0 != code)  
	{
		return code;
	}
	
	/*6 - Checking if the move is valid for the specific piece.*/
	if (0 == numOfSteps)
	{
		return INVALID_PIECE_MOVE;
	}

	/*4 - Checking if by moving, there will be a check on the current player.*/
	this->movePiece(move, board);
	if (currKing->isAttacked(board))
	{
		// Undoing the move
		this->movePiece(dst + src, board);
		dstPiece->setIsAlive(true);
		return SELF_CHECK;
	}

	// Undoing the move
	this->movePiece(dst + src, board);
	dstPiece->setIsAlive(true);

	
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
			if (game.getPiece(currLocation))
			{
				return INVALID_PIECE_MOVE;
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
			if (game.getPiece(currLocation))
			{
				return INVALID_PIECE_MOVE;
			}
		}
	}
	/*0 & 1 - Checking that the move is valid for the specific piece.*/
	this->movePiece(move, board);
	// Checking if a check is made by making the move.
	if (otherKing->isAttacked(board))
	{
		/*Undoing the move*/
		this->movePiece(dst + src, board); 
		dstPiece->setIsAlive(true);
		return VALID_MOVE_CHECK;
	}

	/*Undoing the move*/
	this->movePiece(dst + src, board);
	dstPiece->setIsAlive(true);
	return VALID_MOVE;
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
	if (this->isBlack())
	{
		return BLACK_ROOK;
	}
	else
	{
		return WHITE_ROOK;
	}
}
