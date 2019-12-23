#include "Piece.h"

//c'tor
Piece::Piece(std::string location, bool isBlack)
{
	this->_currLocation = location;
	this->_isBlack = isBlack;
	this->_isAlive = true;
}
//d'tor
Piece::~Piece()
{
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

//setters.
void Piece::setIsAlive(bool isAlive)
{
	this->_isAlive = isAlive;
}