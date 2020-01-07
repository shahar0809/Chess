#include "Board.h"

// c'tor.
Board::Board()
{
	this->_currPlayer = 0;
	Piece* p = nullptr;
	std::string currLocation = "";
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

	currLocation = "00";
	/*Adding the 16 pawns*/
	for (char i = MIN_INDEX_COL; i <= MAX_INDEX_COL; i++)
	{
		currLocation[SRC_ROW] = MAX_INDEX_ROW - 1, currLocation[SRC_COL] = i;
		p = new Pawn(currLocation, true);
		this->_pieces.push_back(p);
		currLocation[SRC_ROW] = MIN_INDEX_ROW + 1;
		p = new Pawn(currLocation, false);
		this->_pieces.push_back(p);
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

/*Getters.*/
unsigned int Board::getNumOfPieces()
{
	return this->_pieces.size();
}


std::vector<Piece*> Board::getPieces()
{
	return this->_pieces;
}


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
		this->setBoard(location[SRC_ROW], location[SRC_COL], EMPTY_CELL); //Remove from board.
		target->setIsAlive(false); // Means dead.
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
	this->_board[(int)(BOARD_SIZE - (x - MIN_INDEX_ROW)) - 1][(int)(y - MIN_INDEX_COL)] = piece;
}

/*
This method searches for a piece on a current location on the board from the vector.
Input: The location of the piece to find.
Output: Returns a pointer to the piece if found, else nullptr.
*/
Piece* Board::getPiece(std::string location)
{
	Piece* target = nullptr;
	int len = 0;
	bool isTargetFound = false;

	len = this->_pieces.size();

	/*
	Searching for the piece in the pieces vector.
	The piece MUST be alive.
	*/
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

/*
The method checks if the king inputted is attacked by a piece of the other player (check).
Input: The king (a King object).
Output: Returns the attacker of the king (a Piece pointer).
*/
Piece* Board::isKingAttacked(King* king)
{
	bool isBlack = king->isBlack();
	std::string dst = king->getCurrLocation();
	Piece* p = nullptr;
	std::string src = "";

	for (int i = 0; i < this->_pieces.size(); i++)
	{
		p = this->_pieces[i];
		src = p->getCurrLocation();

		/*Checking if piece 'p' can eat the king.*/
		if ((p->isAlive()) &&                                                    // If the piece is alive.
			(p->pieceType() != king->pieceType()) &&                             // if the piece is not a king.
			(p->isBlack() != isBlack) &&										 // If the piece is of the other player.
			(p->isMoveValidPiece(src + dst)) &&	                                 // If the piece can eat the king.
			(!this->isBlockingPiece(dst, src, p->pieceType())))					 // If there isn't any piece blocking the piece from eating the king.
		{
			return p;
		}
	}
	return nullptr;
}

/*
This function checks if the move inputted is valid or not.
Input: The move (string), the board (reference to Board object).
Output: The code matching to the move (CODES enum).
*/
CODES Board::isMoveValid(std::string move)
{
	/*Getting the pieces at the src and dest cells.*/
	std::string src = move.substr(0, move.length() / GET_SRC);
	std::string dst = move.substr(DEST_COL, move.length() / GET_DST);
	Piece* srcPiece = this->getPiece(src);
	Piece* dstPiece = this->getPiece(dst);

	/*Getting the kings of each player.*/
	King* otherKing = this->getKing(!this->_currPlayer);
	King* currKing = this->getKing(this->_currPlayer);

	/*2 - Checking that there's a piece of the current player in the src cell.*/
	if (!srcPiece || srcPiece->isBlack() != this->getCurrPlayer())
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
	if (src == dst)
	{
		return SRC_IS_DST;
	}

	/*Specific checking for Pawn (in case of eating move).*/
	if (srcPiece->pieceType() == WHITE_PAWN || srcPiece->pieceType() == BLACK_PAWN)
	{
		/*If the pawn can't eat the dst piece.*/
		if (moveValidator::moveDiagonally(move) && !dstPiece)
		{
			return INVALID_PIECE_MOVE;
		}
	}

	/*6 - check if the move is valid for the piece and it is not blocked by other piece*/
	if (!srcPiece->isMoveValidPiece(move) || this->isBlockingPiece(dst, src, srcPiece->pieceType()))
	{
		return INVALID_PIECE_MOVE;
	}                           

	/*0,1,4 - Checking checks.*/
	/*Making the move.*/
	this->removePiece(dst);
	srcPiece->setLocation(dst);
	this->setBoard(dst[SRC_ROW], dst[SRC_COL], srcPiece->pieceType());
	this->setBoard(src[SRC_ROW], src[SRC_COL], EMPTY_CELL);

	if (currKing && this->isKingAttacked(currKing))
	{
		/*Undoing the move if a self check was made.*/
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
		/*Undoing the move if a check was made on the other king.*/
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

	/*Undoing the move.*/
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


/*
This method prints the board.
Input: None.
Output: None.
*/
void Board::printBoard()
{
	std::cout << std::endl;
	std::cout << "  a b c d e f g h" << std::endl;
	for (int i = BOARD_SIZE; i > 0; i--)
	{
		std::cout << i << " ";

		for (int j = BOARD_SIZE; j > 0; j--)
		{
			std::cout << this->_board[i - 1][j] << " ";
		}
	}
	
}

/*
This method makes the move only if it's valid.
Input: The move (string).
Output: The result code of the move (CODES enum).
*/
CODES Board::makeMove(std::string move)
{
	/*Getting the pieces at the dest and src locations.*/
	std::string src = move.substr(0, move.length() / 2);
	std::string dst = move.substr(DEST_COL, move.length() / 2);
	Piece* srcPiece = this->getPiece(src);
	Piece* dstPiece = this->getPiece(dst);
	CODES resultCode = this->isMoveValid(move);
	King* otherKing = nullptr;

	// printing code result.
	std::cout << "\n" << "RESULT CODE: " << (char)resultCode << "\n";

	// Making the move only if the move is valid.
	if (resultCode == VALID_MOVE || resultCode == VALID_MOVE_CHECK)
	{
		// Removing the piece at the destination (if there's is one), and moving the src piece to the dst location.
		this->removePiece(dst);
		srcPiece->setLocation(dst);
		this->setBoard(dst[SRC_ROW], dst[SRC_COL], srcPiece->pieceType());
		this->setBoard(src[SRC_ROW], src[SRC_COL], EMPTY_CELL);

		/*Changing the 'is first move' field of Pawn if a move was made on a Pawn piece.*/
		if (WHITE_PAWN == srcPiece->pieceType() || BLACK_PAWN == srcPiece->pieceType())
		{
			((Pawn*)(srcPiece))->setIsFirstMove(false);
		}
		if (resultCode == VALID_MOVE_CHECK)
		{
			otherKing = this->getKing(!this->getCurrPlayer());
			resultCode = checkmate::isCheckmate(*this, otherKing, this->isKingAttacked(otherKing));
			setCurrPlayer(!this->_currPlayer); // changing player.
		}
		setCurrPlayer(!this->_currPlayer); // changing player.
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

	// Returning the king according to the inputted player.
	for (unsigned int i = 0; i < this->_pieces.size(); i++)
	{
		if (this->_pieces[i]->pieceType() == typeOfKing)
		{
			return (King*)(this->_pieces[i]);
		}
	}
	return nullptr;
}

/*
The method checks if there's a piece that blocks the move.
Input: dst and src locations (strings), the type of piece in the src cell (char).
Output: If there is a blocking piece - TRUE / If there isn't - FALSE
*/
bool Board::isBlockingPiece(std::string dst, std::string src, char type)
{
	int index = SRC_COL; //Change the col.
	int change = 0; //check location.
	int sideChange = 0; //used for diagonal moves.
	bool isDiagonal = moveValidator::moveDiagonally(src + dst);

	/*Checking for a blocking piece when the src piece is a ROOK.*/
	if (type == WHITE_ROOK || type == BLACK_ROOK || ((type == WHITE_QUEEN || type == BLACK_QUEEN) && !isDiagonal))
	{
		if (dst[SRC_COL] == src[SRC_COL]) // Check what is changing, col or row.
		{
			index = SRC_ROW; // change the row.
		}
		change = dst[index] > src[index] ? 1 : -1;
		while (dst != src)
		{
			src[index] += change;
			if (this->getPiece(src) && src != dst)
			{
				return true;
			}
		}
	}

	/*Checking for a blocking piece when the src piece is a BISHOP.*/
	if (type == BLACK_BISHOP || type == WHITE_BISHOP || type == WHITE_QUEEN || type == BLACK_QUEEN)
	{
		/*Going over all the cells betweeen the src cell and the dst cell (bishop move).*/
		while (dst[SRC_ROW] != src[SRC_ROW])
		{
			change = src[SRC_COL] > dst[SRC_COL] ? -1 : 1;
			sideChange = src[SRC_ROW] > dst[SRC_ROW] ? -1 : 1;
			/*Moving to the next cell.*/
			src[SRC_COL] += change;
			src[SRC_ROW] += sideChange;

			/*Checking if there's a piece in current location.*/
			if (src != dst && getPieceAt(src[SRC_ROW], src[SRC_COL]) != EMPTY_CELL)
			{
				return true;
			}
		}
	}

	/*Checking for a blocking piece when the src piece is a PAWN.*/
	if (type == WHITE_PAWN || type == BLACK_PAWN)
	{
		/*Pawn eating move.*/
		if (abs(src[SRC_ROW] - dst[SRC_ROW]) == abs(src[SRC_COL] - dst[SRC_COL]) == 1) // A single move diagonally.
		{
			return false;
		}
		/*Normal move.*/
		else
		{
			return (this->getPieceAt(dst[SRC_ROW], dst[SRC_COL]) != EMPTY_CELL); // A single move forwards.
		}
	}

	/*No piece can block a KING and a KNIGHT.*/
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
		return this->_board[(int)(BOARD_SIZE - (x - MIN_INDEX_ROW)) - 1][(int)(y - MIN_INDEX_COL)];
	}
	/*Invalid Indices.*/
	else
	{
		return 0;
	}
}

/*
Creates the initial string to be sent to the front end.
Input: None.
Output: The inital string (a char pointer).
*/
char* Board::initialBoardString()
{
	char* initBoard = new char[BOARD_SIZE * BOARD_SIZE + 2];

	/*Copying the starting board of the game into the first 64 chars of the string.*/
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		initBoard[i] = STARTING_BOARD[i];
	}

	initBoard[BOARD_SIZE * BOARD_SIZE] = (char)('0' + this->getCurrPlayer()); // putting the starting player into the last char.
	initBoard[BOARD_SIZE * BOARD_SIZE + 1] = '\0';
	return initBoard;
}
