#include "Game.h"

std::vector<Piece*> Game::getAlivePieces()
{
	return this->_pieces;
}

/*
This method searches for a piece on a current location on the board.
Input: The location of the piece to find.
Output: Returns a pointer to the piece if found, else nullptr.
*/
Piece* Game::getPiece(std::string location)
{
	Piece* target = nullptr;
	int len = 0;
	bool isTargetFound = false;

	len = this->_pieces.size();

	for (int i = 0; (i < len) && !isTargetFound; i++)
	{
		if (this->_pieces[i]->getCurrLocation() == location)
		{
			target = this->_pieces[i];
			isTargetFound = true;
		}
	}
	return target;
}

// c'tor
Game::Game()
{
	
}

Game::~Game()
{
}

/*
This method remove a piece from the board and from the vector after it was eaten.
Input: The location of the piece to remove.
Output: True of the piece was found and deleted. else false.
*/
bool Game::removePiece(std::string location)
{
	int len = 0;
	Piece* target = nullptr;
	bool isTargetFound = false;
	target = this->getPiece(location);

	if (target)
	{
		// x && y of piece.
		
		this->_board.setBoard(target->getCurrLocation()[0] - MIN_INDEX_COL,target->getCurrLocation()[1] - MIN_INDEX_ROW - 1, '#');
		
		target->setIsAlive(false);
		isTargetFound = true;
	}

	return isTargetFound;
}

unsigned int Game::makeMove(std::string move)
{
	/*Getting the pieces at the dest and src locations.*/
	std::string src = move.substr(0, move.length() / 2);
	std::string dst = move.substr(DEST_COL, move.length() / 2);
	Piece* srcPiece = this->getPiece(src);
	Piece* dstPiece = this->getPiece(dst);

	unsigned int resultCode = srcPiece->isMoveValid(move, this->_board, this->getPiece(src), this->getPiece(dst));

	// Making the move only if move is valid.
	if (resultCode = VALID_MOVE || resultCode == VALID_MOVE_CHECK)
	{
		// Removing the piece at the destination (if there's is one)
		this->removePiece(dst);
		srcPiece->movePiece(move, this->_board);
	}

	return resultCode;
}


/*
The method finds the king in the inputted color.
Input: The color of the king.
Output: The king (a pointer to a King object)
*/
King* Game::getKing(bool isBlack)
{
	// Getting the type of the king.
	char typeOfKing = isBlack ? BLACK_KING : WHITE_KING;

	// Returning the matching king.
	for (unsigned int i = 0; i < this->_pieces.size(); i++)
	{
		if (this->_pieces[i]->pieceType() == typeOfKing)
		{
			return (King*)(this->_pieces[i]);
		}
	}
	return nullptr;
}

