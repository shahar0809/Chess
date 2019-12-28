#pragma once


#include "moveValidator.h"
#include "King.h"
#include "Rook.h"

class Piece;
class King;
class Rook;


class Game
{
private:
	std::vector<Piece*> _pieces;
	Board _board;

public:
	Game();
	~Game();
	bool removePiece(std::string location);
	std::vector<Piece*> getAlivePieces();
	Piece* getPiece(std::string location);
	unsigned int makeMove(std::string move);
	King* getKing(bool isBlack);

};
