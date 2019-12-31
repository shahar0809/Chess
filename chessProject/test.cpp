
#include "Board.h"
#include "Rook.h"

int main(void)
{
	Board board = Board();

	std::string move = "";
	while (true)
	{
		board.printBoard();

		if (board.getCurrPlayer())
		{
			std::cout << "Player 2's turn (BLACK)" << std::endl;
		}
		else
		{
			std::cout << "Player 1's turn (WHITE)" << std::endl;
		}
		
		std::cin >> move;
		board.makeMove(move);
	}

	exit(0);
}