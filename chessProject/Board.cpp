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
	
	/*Initializing board with the starting board.*/
	/*Adding the 4 rooks.*/
	p = new Rook("a8", true);
	this->_pieces.push_back(p);
	p = new Rook("h8", true);
	this->_pieces.push_back(p);
	p = new Rook("a1", false);
	this->_pieces.push_back(p);
	p = new Rook("h1", false);
	this->_pieces.push_back(p);

	/*Adding the 2 kings and queens.*/
	p = new King("e1", false);
	this->_pieces.push_back(p);
	p = new King("e8", true);
	this->_pieces.push_back(p);
	p = new Queen("d8", true);
	this->_pieces.push_back(p);
	p = new Queen("d1", false);
	this->_pieces.push_back(p);

	/*Adding the 4 bishops.*/
	p = new Bishop("c8", true);
	this->_pieces.push_back(p);
	p = new Bishop("c1", false);
	this->_pieces.push_back(p);
	p = new Bishop("f8", true);
	this->_pieces.push_back(p);
	p = new Bishop("f1", false);
	this->_pieces.push_back(p);
	
	/*Adding the 4 knights.*/
	p = new Knight("g8", true);
	this->_pieces.push_back(p);
	p = new Knight("b8", true);
	this->_pieces.push_back(p);
	p = new Knight("g1", false);
	this->_pieces.push_back(p);
	p = new Knight("b1", false);
	this->_pieces.push_back(p);

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
bool Board::removePiece(std::string location)
{
	int len = 0;
	Piece* target = nullptr;
	bool isTargetFound = false;
	target = this->getPiece(location);

	if (target)
	{
		// x && y of piece.

		this->setBoard(location[SRC_ROW], location[SRC_COL], EMPTY_CELL);

		target->setIsAlive(false);
		isTargetFound = true;
	}

	return isTargetFound;
}

/*
This method assigns a piece on a location on the board.
Input: The x and y of the piece and its siganture.
Output: None.
*/
void Board::setBoard(char x, char y, char piece)
{
	this->_board[(int)(x - MIN_INDEX_ROW)][(int)(y - MIN_INDEX_COL)] = piece;
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
		if (this->_pieces[i]->getCurrLocation() == location && this->_pieces[i]->isAlive())
		{
			target = this->_pieces[i];
			isTargetFound = true;
		}
	}
	return target;
}

bool Board::isKingAttacked(King* king)
{
	bool isBlack = king->isBlack();
	std::string dst = king->getCurrLocation();
	Piece* p = nullptr;
	std::string src = "";

	for (int i = 0; i< this->_pieces.size(); i++)
	{
		p = this->_pieces[i];
		src = p->getCurrLocation();

		/*Checking if piece p can eat the king.*/
		if ((p->pieceType() != king->pieceType()) && (p->isBlack() != isBlack) && (p->isMoveValidPiece(src + dst)) && (!this->isBlockingPiece(dst, src, p->pieceType())))
		{
			return true;
		}
	}
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

	/*2 - Checking that there's a piece of the current player in the src cell.*/
	if (!srcPiece)
	{
		return NO_PIECE_IN_SRC;
	}
	
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

	/*6 - check if the move is valid for the piece and it is not blocked by other piece*/
	if (!srcPiece->isMoveValidPiece(move) || this->isBlockingPiece(dst, src, srcPiece->pieceType()))
	{
		return INVALID_PIECE_MOVE;
	}

	/*0,1,4 - Checking checks.*/
	this->removePiece(dst);
	srcPiece->setLocation(dst);
	this->setBoard(dst[SRC_ROW], dst[SRC_COL], srcPiece->pieceType());
	this->setBoard(src[SRC_ROW], src[SRC_COL], EMPTY_CELL);

	if (currKing && this->isKingAttacked(currKing))
	{
		/*Undoing the move*/
		if (dstPiece)
		{
			this->setBoard(dst[SRC_ROW], dst[SRC_COL], dstPiece->pieceType());
			dstPiece->setIsAlive(true);
		}
		else
		{
			this->setBoard(dst[SRC_ROW], dst[SRC_COL], EMPTY_CELL);
		}
		srcPiece->setLocation(src);
		this->setBoard(src[SRC_ROW], src[SRC_COL], srcPiece->pieceType());

		return SELF_CHECK;
	}

	// Checking if a check is made by making the move.
	if (otherKing && this->isKingAttacked(otherKing))
	{
		/*Undoing the move*/
		if (dstPiece)
		{
			this->setBoard(dst[SRC_ROW], dst[SRC_COL], dstPiece->pieceType());
			dstPiece->setIsAlive(true);
		}
		else
		{
			this->setBoard(dst[SRC_ROW], dst[SRC_COL], EMPTY_CELL);
		}
		srcPiece->setLocation(src);
		this->setBoard(src[SRC_ROW], src[SRC_COL], srcPiece->pieceType());

		return VALID_MOVE_CHECK;
	}

	/*Undoing the move*/
	if (dstPiece)
	{
		this->setBoard(dst[SRC_ROW], dst[SRC_COL], dstPiece->pieceType());
		dstPiece->setIsAlive(true);
	}
	else
	{
		this->setBoard(dst[SRC_ROW], dst[SRC_COL], EMPTY_CELL);
	}
	srcPiece->setLocation(src);
	this->setBoard(src[SRC_ROW], src[SRC_COL], srcPiece->pieceType());

	return VALID_MOVE;
}

void Board::printBoard()
{
	std::cout << std::endl;
	std::cout << "  abcdefgh" << std::endl;
	for (int i = BOARD_SIZE; i > 0; i--)
	{
		std::cout << i << " ";
		std::cout << this->_board[i - 1] << std::endl;
	}
}

void Board::addPiece(Piece* piece)
{
	this->_pieces.push_back(piece);
	this->setBoard(piece->getCurrLocation()[1], piece->getCurrLocation()[0], piece->pieceType());
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
		this->_currPlayer = !this->_currPlayer; // change player.
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

bool Board::isBlockingPiece(std::string dst, std::string src, char type)
{
	int index = SRC_COL; //Change the col.
	int change = 0; //check location.
	
	if (type == WHITE_ROOK || type == BLACK_ROOK)
	{
		if (dst[SRC_COL] == src[SRC_COL]) // Check what is changing, col or row.
		{
			index = SRC_ROW; // change the row.
		}
		change = dst[index] > src[index] ? 1 : -1;
		while (dst != src)
		{
			src[index] += change;
			if (this->getPiece(src) &&  src != dst)
			{
				return true;
			}
		}
		return false;
	}

	if (WHITE_KING == type || BLACK_KING == type || WHITE_KNIGHT == type || BLACK_KING == type)
	{
		return false;
	}

	if (type == BLACK_BISHOP || type == WHITE_BISHOP)
	{
		std::string currLocation = src[SRC_ROW] < dst[SRC_ROW] ? src : dst;
		std::string maxLocation = src[SRC_ROW] > dst[SRC_ROW] ? src : dst;
		
		// If the src is on the right of the dst, then the loop checks from src (right) to dst (left). If not then from left to right.
		int addBy = src[SRC_COL] < dst[SRC_COL] ? 1 : -1; 

		/*Going over all the cells betweeen the src cell and the dst cell (bishop move).*/
		while (currLocation[SRC_ROW] != maxLocation[SRC_ROW] - 1)
		{
			/*Moving to the next cell.*/
			currLocation[SRC_COL] += addBy;
			currLocation[SRC_ROW]++;

			/*Checking if there's a piece in current location.*/
			if (getPieceAt(currLocation[SRC_ROW], currLocation[SRC_COL]) != EMPTY_CELL) // fix here!
			{
				return true;
			}
		}
		return false;
	}
	return false;
}

/*
Gets the type of piece in cell [x][y] in the board.
Input: Indices of the cell - x, y (chars).
Output: The type of piece in the cell (char).
*/
char Board::getPieceAt(char x, char y)
{
	if (x >= MIN_INDEX_ROW && x <= MAX_INDEX_ROW && y >= MIN_INDEX_COL && y <= MAX_INDEX_COL)
	{
		return this->_board[x - MIN_INDEX_ROW][y - MIN_INDEX_COL];
	}
	else
	{
		return 0;
	}
}
