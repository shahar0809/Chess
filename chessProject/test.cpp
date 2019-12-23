#include "moveValidator.h"
#include "Board.h"
int main(void)
{
	
	Board b;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			std::cout << b.getBoard()[i][j] << ',';
		}
		std::cout << '\n';
	}
	return 0;
}