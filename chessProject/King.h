#pragma once
#include "Piece.h"
#include "Game.h"

class Piece;
class Board;
class Game;

class King : public Piece
{
public:
	//c'tor and d'tor
	King(std::string location, bool isBlack);
	~King();

	// virtual methods (from Piece)
	virtual CODES isMoveValidPiece(std::string move, Board& board, Game& game);
	virtual void movePiece (std::string move, Board& board);
	virtual char pieceType();
	bool isAttacked(Board& board);
};

