#include "Board.h"

// c'tor.
Board::Board()
{
	this->_currPlayer = 0;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			this->_board[i] += STARTING_BOARD[i * BOARD_SIZE + j];
		}
	}

}

//d'tor.
Board::~Board()
{
	for (int i = 0; i < this->_pieces.size(); i++)
	{
		delete this->_pieces[i];
	}
}

//getters.
std::string* Board::getBoard()
{
	return this->_board;
}

std::vector<Piece*> Board::getAlivePieces()
{
	return this->_pieces;
}

unsigned int Board::getCurrPlayer()
{
	return this->_currPlayer;
}

/*
This method searches for a piece on a current location on the board.
Input: The location of the piece to find.
Output: Returns a pointer to the piece if found, else nullptr.
*/
Piece* Board::getPiece(std::string location)
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

/*
This method remove a piece from the board and from the vector after it was eaten.
Input: The location of the piece to remove.
Output: True of the piece was found and deleted. else false.
*/
bool Board::removePiece(std::string location)
{
	int len = 0;
	Piece* target = nullptr;
	bool isTargetFound = false;

	target = this->getPiece(location);

	if (target)
	{
		// x && y of piece.
		this->_board[target->getCurrLocation()[0] - MIN_INDEX_COL][target->getCurrLocation()[1] - MIN_INDEX_ROW - 1] = '#'; // Remove piece from board as well.
		target->isAlive = false;
		isTargetFound = true;
	}
	
	return isTargetFound;
}

/*
This method assigns a piece on a location on the board.
Input: The x and y of the piece and its siganture.
Output: None.
*/
void Board::setBoard(unsigned char x, unsigned char y, char piece)
{
	this->_board[x - MIN_INDEX_COL][y - MIN_INDEX_ROW - 1] = piece;
}

//setters.
void Board::setCurrPlayer(unsigned int newCurrPlayer)
{
	this->_currPlayer = newCurrPlayer;
}

unsigned int Board::makeMove(std::string move)
{
	/*Getting the pieces at the dest and src locations.*/
	std::string src = move.substr(0, move.length / 2);
	std::string dst = move.substr(DEST_COL, move.length / 2);
	Piece* srcPiece = this->getPiece(src);
	Piece* dstPiece = this->getPiece(dst);

	unsigned int resultCode = srcPiece->isMoveValid(move, *this);

	// Making the move only if move is valid.
	if (resultCode = VALID_MOVE || resultCode == VALID_MOVE_CHECK)
	{
		// Removing the piece at the destination (if there's is one)
		this->removePiece(dst);
		srcPiece->movePiece(move, *this);
	}

	return resultCode;
}

/*
The method finds the king in the inputted color.
Input: The color of the king.
Output: The king (a pointer to a King object)
*/
King* Board::getKing(bool isBlack)
{
	// Getting the type of the king.
	char typeOfKing = isBlack ? BLACK_KING : WHITE_KING;

	// Returning the matching king.
	for (int i = 0; i < this->_pieces.size(); i++)
	{
		if (this->_pieces[i]->pieceType() == typeOfKing)
		{
			return (King*)(this->_pieces[i]);
		}
	}
}