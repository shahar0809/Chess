#pragma once
#include "Game.h"

class Piece;
class Board;
class Game;

class Rook : public Piece
{
public:
	//c'tor and d'tor
	Rook(std::string location, bool isBlack);
	~Rook();

	// virtual methods (from Piece)
	virtual CODES isMoveValidPiece(std::string move, Board& board, Game& game);
	virtual void movePiece(std::string move, Board& board);
	virtual char pieceType();

	
};

