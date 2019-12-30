
#include "Board.h"
#include "Rook.h"

int main(void)
{
	Board board = Board();
	/*board.printBoard();
	board.setCurrPlayer(1);
	board.makeMove("h8h1");
	board.printBoard();

	board.makeMove("f1h3");
	board.printBoard();

	board.makeMove("b8c6");
	board.printBoard();*/

	std::string move = "";
	while (true)
	{
		board.printBoard();
		std::cin >> move;
		board.makeMove(move);
	}

	exit(0);
}