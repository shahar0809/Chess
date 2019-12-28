#include "Board.h"

// c'tor.
Board::Board()
{
	this->_currPlayer = 0;
	Piece* p = nullptr;
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
	
}

//getters.
std::string* Board::getBoard()
{
	return this->_board;
}

unsigned int Board::getCurrPlayer()
{
	return this->_currPlayer;
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




