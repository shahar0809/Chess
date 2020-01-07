/*
This file servers as an example of how to use Pipe.h file.
It is recommended to use the following code in your project, 
in order to read and write information from and to the Backend
*/

#include "Pipe.h"
#include "Board.h"

#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::string;

void main()
{
	srand(time_t(NULL));
	char* message = nullptr;
	Pipe p;
	King* otherKing = nullptr;
	Board board = Board();
	bool isConnect = p.connect();
	string ans;

	/*If unable to connect to the front end.*/
	while (!isConnect)
	{
		cout << "cant connect to graphics" << endl;
		cout << "Do you try to connect again or exit? (0-try again, 1-exit)" << endl;
		std::cin >> ans;

		if (ans == "0")
		{
			cout << "trying connect again.." << endl;
			Sleep(5000);
			isConnect = p.connect();
		}
		else 
		{
			p.close();
			return;
		}
	}
	
	// msgToGraphics should contain the board string accord the protocol
	char msgToGraphics[1024];
	
	message = board.initialBoardString();
	strcpy_s(msgToGraphics, message); 
	
	p.sendMessageToGraphics(msgToGraphics);   // sending the board string.
	delete message;
	// get message from graphics
	string msgFromGraphics = p.getMessageFromGraphics();

	while (msgFromGraphics != "quit")
	{
		// should handle the string the sent from graphics.
		char resultCode = board.makeMove(msgFromGraphics);
		
		strcpy_s(msgToGraphics, &resultCode); // msgToGraphics should contain the result of the operation
		msgToGraphics[1] = '\0';

		// return result to graphics	
		/*Ending the game if there's a checkmate.*/
		if (resultCode == CHECKMATE_MOTHER_F$$KER) //check mate DOSENT WORK!!!!!!!!!!!!!
		{
			resultCode = VALID_MOVE_CHECK;
			strcpy_s(msgToGraphics, &resultCode); // msgToGraphics should contain the result of the operation.
			msgToGraphics[1] = '\0';
			p.sendMessageToGraphics(msgToGraphics);
			std::cout << "CHECKMATE\n";
			msgFromGraphics = p.getMessageFromGraphics();
		}
		else
		{
			p.sendMessageToGraphics(msgToGraphics);

			// get message from graphics
			msgFromGraphics = p.getMessageFromGraphics();
		}
	}

	p.close();
}