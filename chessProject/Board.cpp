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
	for (int i = 0; i < this->_pieces.size(); i++)
	{
		delete this->_pieces[i];
	}
}

unsigned int Board::getNumOfPieces()
{
	return this->_pieces.size();
}

std::vector<Piece*> Board::getPieces()
{
	return this->_pieces;
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
void Board::setBoard(char x, char y, char piece)
{
	this->_board[x - MIN_INDEX_ROW][y - MIN_INDEX_COL] = piece;
}

//setters.
void Board::setCurrPlayer(unsigned int newCurrPlayer)
{
	this->_currPlayer = newCurrPlayer;
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
	/*Getting the kings of each player.*/
	King* otherKing = this->getKing(!this->_currPlayer);
	King* currKing = this->getKing(this->_currPlayer);

	if (!srcPiece)
		return NO_PIECE_IN_SRC;

	/*2 - Checking that there's a piece of the current player in the src cell.*/
	if (srcPiece->isBlack() != this->getCurrPlayer())
	{
		return NO_PIECE_IN_SRC;
	}

	/*3 - Checking that there isn't a piece of the current player in the dst cell.*/
	if (dstPiece && dstPiece->isBlack() == this->getCurrPlayer())
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
	if (!srcPiece->isMoveValidPiece(move, this->_pieces))
	{
		return INVALID_PIECE_MOVE;
	}

	this->removePiece(dst);
	srcPiece->setLocation(dst);
	this->setBoard(dst[SRC_ROW], dst[SRC_COL], srcPiece->pieceType());
	this->setBoard(src[SRC_ROW], src[SRC_COL], EMPTY_CELL);

	// Checking if a check is made by making the move.
	if (otherKing && this->isKingAttacked(otherKing))
	{
		/*Undoing the move*/
		if (dstPiece)
		{
			this->setBoard(dst[SRC_ROW], dst[SRC_COL], dstPiece->pieceType());
			dstPiece->setIsAlive(true);
		}
		srcPiece->setLocation(src);
		this->setBoard(src[SRC_ROW], src[SRC_COL], srcPiece->pieceType());

		return VALID_MOVE_CHECK;
	}

	if (currKing && this->isKingAttacked(currKing))
	{
		/*Undoing the move*/
		if (dstPiece)
		{
			this->setBoard(dst[SRC_ROW], dst[SRC_COL], dstPiece->pieceType());
			dstPiece->setIsAlive(true);
		}
		srcPiece->setLocation(src);
		this->setBoard(src[SRC_ROW], src[SRC_COL], srcPiece->pieceType());
		return SELF_CHECK;
	}

	/*Undoing the move*/
	if (dstPiece)
	{
		this->setBoard(dst[SRC_ROW], dst[SRC_COL], dstPiece->pieceType());
		dstPiece->setIsAlive(true);
	}
	srcPiece->setLocation(src);
	this->setBoard(src[SRC_ROW], src[SRC_COL], srcPiece->pieceType());
	
	return VALID_MOVE;
}

void Board::printBoard()
{
	std::cout << std::endl;
	std::cout << "  abcdefgh" << std::endl;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		std::cout << i + 1 << " ";
		std::cout << this->_board[i] << std::endl;
	}
}

void Board::addPiece(Piece* piece)
{
	this->_pieces.push_back(piece);
	this->setBoard(piece->getCurrLocation()[1], piece->getCurrLocation()[0], piece->pieceType());
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

		this->setBoard(target->getCurrLocation()[0] - MIN_INDEX_COL, target->getCurrLocation()[1] - MIN_INDEX_ROW - 1, '#');

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

unsigned int Board::makeMove(std::string move)
{
	/*Getting the pieces at the dest and src locations.*/
	std::string src = move.substr(0, move.length() / 2);
	std::string dst = move.substr(DEST_COL, move.length() / 2);
	Piece* srcPiece = this->getPiece(src);
	Piece* dstPiece = this->getPiece(dst);
	CODES resultCode = this->isMoveValid(move);
	std::cout << "\n" << resultCode << "\n";
	// Making the move only if move is valid.
	if (resultCode == VALID_MOVE || resultCode == VALID_MOVE_CHECK)
	{
		// Removing the piece at the destination (if there's is one), and moving the src piece to the dst location.
		this->removePiece(dst);
		srcPiece->setLocation(dst);
		this->setBoard(dst[SRC_ROW], dst[SRC_COL], srcPiece->pieceType());
		this->setBoard(src[SRC_ROW], src[SRC_COL], EMPTY_CELL);
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
