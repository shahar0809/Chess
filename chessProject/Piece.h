#pragma once
#include "moveValidator.h"
#include <vector>

#define SRC_COL  0
#define SRC_ROW 1
#define DEST_COL 2
#define DEST_ROW 3

#define MAX_INDEX_COL 'h'
#define MAX_INDEX_ROW '8'
#define MIN_INDEX_COL 'a'
#define MIN_INDEX_ROW '1'

#define SRC_COL  0
#define SRC_ROW 1
#define DEST_COL 2
#define DEST_ROW 3

enum CODES
{
	VALID_MOVE = 0,
	VALID_MOVE_CHECK,
	NO_PIECE_IN_SRC,
	PIECE_IN_DST,
	SELF_CHECK,
	INVALID_INDEX,
	INVALID_PIECE_MOVE,
	SRC_IS_DST
};

enum PIECES_TYPES
{
	WHITE_ROOK = 'R', WHITE_BISHOP = 'B', WHITE_QUEEN = 'Q', WHITE_KING = 'K', WHITE_PAWN = 'P',
	BLACK_ROOK = 'r', BLACK_BISHOP = 'b', BLACK_QUEEN = 'q', BLACK_KING = 'k', BLACK_PAWN = 'p',
	EMPTY_CELL = '#'
};

/*Abstract class Piece*/
class Piece
{
protected:
	std::string _currLocation;
	bool _isAlive;
	bool _isBlack;

public:
	// c'tor and d'tor
	Piece(std::string location, bool isBlack);
	~Piece();

	// methods
	void setIsAlive(bool isAlive);
	bool isAlive();
	bool isBlack();
	std::string getCurrLocation();

	void setLocation(std::string location);

	// pure virtual methods
	virtual bool isMoveValidPiece(std::string move, std::vector<Piece*> pieces) = 0;

	virtual char pieceType() = 0;
};
