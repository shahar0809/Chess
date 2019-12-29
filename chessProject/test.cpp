
#include "Board.h"
#include "Rook.h"

int main(void)
{
	Board board = Board();
	std::string move = "";
	while (true)
	{
		board.printBoard();
		std::cin >> move;
		board.makeMove(move);
	}
	

}