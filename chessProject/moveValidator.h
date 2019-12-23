#pragma once
#include <iostream>

class moveValidator
{
	unsigned int moveForward(std::string move);
	unsigned int moveSideways(std::string move);
	unsigned int moveDiagonally(std::string move);
	unsigned int singleMove(std::string move);
	unsigned int kinghtMove(std::string move);
	unsigned int pawnEatingMove(std::string move);
};

