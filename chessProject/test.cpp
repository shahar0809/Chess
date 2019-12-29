#include "Board.h"
#include "Rook.h"

int main(void)
{
	Board board = Board();
	board.printBoard();
	Rook* rook = new Rook("a8", false);
	Rook* rook2 = new Rook("a5", false);
	board.addPiece(rook);
	board.addPiece(rook2);
	board.printBoard();
	board.makeMove("a8a5");
	board.printBoard();
	
	return 0;
}