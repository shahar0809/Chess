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




/*
This method remove a piece from the board and from the vector after it was eaten.
Input: The location of the piece to remove.
Output: True of the piece was found and deleted. else false.
*/
bool pieceVectorMethods::removePiece(std::string location, std::vector<Piece*> pieces, Board& board)
{
	int len = 0;
	Piece* target = nullptr;
	bool isTargetFound = false;
	target = this->getPiece(location);

	if (target)
	{
		// x && y of piece.

		board.setBoard(target->getCurrLocation()[0] - MIN_INDEX_COL, target->getCurrLocation()[1] - MIN_INDEX_ROW - 1, '#');

		target->setIsAlive(false);
		isTargetFound = true;
	}

	return isTargetFound;
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

unsigned int pieceVectorMethods::makeMove(std::string move, std::vector<Piece*> pieces, Board& board)
{
	/*Getting the pieces at the dest and src locations.*/
	std::string src = move.substr(0, move.length() / 2);
	std::string dst = move.substr(DEST_COL, move.length() / 2);
	Piece* srcPiece = pieceVectorMethods::getPiece(src, pieces);
	Piece* dstPiece = pieceVectorMethods::getPiece(dst, pieces);

	unsigned int resultCode = srcPiece->isMoveValid(move, board, pieceVectorMethods::getPiece(src, pieces), pieceVectorMethods::getPiece(dst, pieces));

	// Making the move only if move is valid.
	if (resultCode = VALID_MOVE || resultCode == VALID_MOVE_CHECK)
	{
		// Removing the piece at the destination (if there's is one)
		pieceVectorMethods::removePiece(dst);
		srcPiece->movePiece(move, board);
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
	for (unsigned int i = 0; i < this->_pieces.size(); i++)
	{
		if (this->_pieces[i]->pieceType() == typeOfKing)
		{
			return (King*)(this->_pieces[i]);
		}
	}
	return nullptr;
}

bool Board::isKingAttacked(King* king)
{
	return false;
}



/*
This function checks if the move inputted is valid or not.
Input: The move (string), the board (reference to Board object).
Output: The code matching to the move.
*/
CODES Board::isMoveValid(std::string move)
{
	/*Getting the pieces at the src and dest cells.*/
	std::string src = move.substr(0, move.length() / 2);
	std::string dst = move.substr(DEST_COL, move.length() / 2);
	Piece* srcPiece = this->getPiece(src);
	Piece* dstPiece = this->getPiece(dst);
	King* otherKing = this->getKing(!this->_currPlayer);
	King* currKing = this->getKing(this->_currPlayer);


	/*Getting the kings of each player.*/


	/*2 - Checking that there's a piece of the current player in the src cell.*/
	if (NULL == srcPiece || srcPiece->isBlack() != this->getCurrPlayer())
	{
		return NO_PIECE_IN_SRC;
	}

	/*3 - Checking that there isn't a piece of the current player in the dst cell.*/
	if (srcPiece || srcPiece->isBlack() == this->getCurrPlayer())
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

	/*0 & 1 - Checking that the move is valid for the specific piece.*/
	//this->movePiece(move);
	// Checking if a check is made by making the move.
	if (this->isKingAttacked(otherKing))
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