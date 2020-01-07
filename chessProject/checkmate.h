#pragma once

#include "Board.h"

class board;
#define COL 0
#define ROW 1
class checkmate {

public:
	static CODES isCheckmate(Board& board, King* otherKing, Piece* attackers);
	static bool pieceBetween(std::string src, std::string dst, Board& board);
};