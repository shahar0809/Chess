#include "Piece.h"
#include "King.h"
class King;

// c'tor
Piece::Piece(std::string location, bool isBlack)
{
	this->_currLocation = location;
	this->_isBlack = isBlack;
	this->_isAlive = true;
}

// d'tor
Piece::~Piece()
{
}

// setters
void Piece::setIsAlive(bool isAlive)
{
	this->_isAlive = isAlive;
}

void Piece::setLocation(std::string location)
{
	if (!(location[SRC_COL] < MIN_INDEX_COL || location[SRC_COL] > MAX_INDEX_COL || location[SRC_ROW] < MIN_INDEX_ROW || location[SRC_ROW] > MAX_INDEX_ROW))
	{
		this->_currLocation = std::string(location);
	}
}

//Getters.
bool Piece::isAlive()
{
	return this->_isAlive;
}

bool Piece::isBlack()
{
	return this->_isBlack;
}

std::string Piece::getCurrLocation()
{
	return this->_currLocation;
}