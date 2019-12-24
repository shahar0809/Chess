#include "Board.h"

// c'tor.
Board::Board()
{
	
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
		this->_board[target->getCurrLocation()[0] - 'a'][target->getCurrLocation()[1] - '0'] = '#'; // Remove piece from board as well.
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
	this->_board[x - 'a'][y - '0'] = piece;
}