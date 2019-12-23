#pragma once
#include <iostream>

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

	// pure virtual methods
	virtual unsigned int isMoveValid(std::string move, std::string* board) = 0;
	virtual void move(std::string move, std::string* board) = 0;
	virtual char pieceType() = 0;
};