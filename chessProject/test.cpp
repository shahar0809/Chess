#include "moveValidator.h"

int main(void)
{
	
	
	std::cout << moveValidator::knightMove("B8C7");
	std::cout << moveValidator::knightMove("D7D5");
	std::cout << moveValidator::knightMove("H5F6");
	std::cout << moveValidator::knightMove("A6G4");
	std::cout << moveValidator::knightMove("E5H2");
	std::cout << moveValidator::knightMove("H8F1");
	std::cout << moveValidator::knightMove("F3D2");

	return 0;
}