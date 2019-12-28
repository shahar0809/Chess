#include "Piece.h"
#include "King.h"
class King;

// c'tor


Piece::Piece(std::string location, bool isBlack)
{
	this->_currLocation = location;
	this->_isBlack = isBlack;
	this->_isAlive = true;
}


// d'tor


Piece::~Piece()
{
}


// setter
void Piece::setIsAlive(bool isAlive)
{
	this->_isAlive = isAlive;
}


//Getters.

bool Piece::isAlive()
{
	return this->_isAlive;
}

bool Piece::isBlack()
{
	return this->_isBlack;
}

std::string Piece::getCurrLocation()
{
	return this->_currLocation;
}


// methods
/*
This function checks if the move inputted is valid or not.
Input: The move (string), the board (reference to Board object).
Output: The code matching to the move.
*/
CODES Piece::isMoveValid(std::string move, Board& board, Piece* srcPiece, Piece* dstPiece)
{
	/*Getting the pieces at the src and dest cells.*/
	std::string src = move.substr(0, move.length() / 2);
	std::string dst = move.substr(DEST_COL, move.length() / 2);
	

	/*Getting the kings of each player.*/
	

	/*2 - Checking that there's a piece of the current player in the src cell.*/
	if (NULL == srcPiece || srcPiece->isBlack() != board.getCurrPlayer())
	{
		return NO_PIECE_IN_SRC;
	}

	/*3 - Checking that there isn't a piece of the current player in the dst cell.*/
	if (srcPiece || srcPiece->isBlack() == board.getCurrPlayer())
	{
		return PIECE_IN_DST;
	}

	/*5 - Cheking that the src and dest locations are valid.*/
	if ((move[SRC_COL] > MAX_INDEX_COL || move[SRC_ROW] > MAX_INDEX_ROW || move[DEST_COL] > MAX_INDEX_COL || move[DEST_ROW] > MAX_INDEX_ROW) ||
		(move[SRC_COL] < MIN_INDEX_COL || move[SRC_ROW] < MIN_INDEX_ROW || move[DEST_COL] < MIN_INDEX_COL || move[DEST_ROW] < MIN_INDEX_ROW))
	{
		return INVALID_INDEX;
	}

	
	/*7 - The src cell is also the dest cell.*/
	if (move[SRC_COL] == move[DEST_COL] && move[SRC_ROW] == move[DEST_ROW])
	{
		return SRC_IS_DST;
	}

	
	return VALID_MOVE;
}


