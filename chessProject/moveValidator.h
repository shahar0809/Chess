#pragma once
#include <iostream>
#include <math.h>
enum INDEX_MOVMENTS { SRC_COL = 0, SRC_ROW = 1, DEST_COL = 2, DEST_ROW = 3 };

#define KNIGHT_MOVING_PATTERN_NUm 2
class moveValidator
{
public:
	static int moveSideways(std::string move);
	static int moveBackOrForward(std::string move);
	static int moveDiagonally(std::string move);
	static bool singleMove(std::string move);
	static int knightMove(std::string move);
	static int pawnEatingMove(std::string move);
	moveValidator();
	~moveValidator();
};

