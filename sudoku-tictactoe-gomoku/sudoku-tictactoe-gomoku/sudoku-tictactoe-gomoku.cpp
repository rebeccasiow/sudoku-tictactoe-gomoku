// sudoku-tictactoe-gomoku.cpp : Defines the entry point for the console application.
//
// Lab4.cpp : Defines the entry point for the console application.
//

/*
//Michelle Yuan (michelleyuan@wustl.edu)
//Shefali Gupta (shefali.gupta@wustl.edu)
//Rebecca Siow (rebecca.siow@wustl.edu)
*/

#include "stdafx.h"
#include "GamePiece.h"
#include "GameBase.h"
#include "TicTacToeGame.h"
#include "Lab3.h"
#include <memory>

using namespace std;

int usage(std::string progname, std::string game){
	cout << "Usage: " << progname << " <" << game << ">" << endl;
	return INCORRECT_INPUT;
}

int main(int argc, char* argv[])
{
	int with_boardsize = 3;
	int with_boardsize_connectwin = 4;
	if (argc == with_boardsize && atoi(argv[SPECIFIED_BOARDSIZE - 1]) < 1) {
		cout << "Invalid board size, must be greater than 0" << endl;
		return INVALID_BOARD_SIZE;
	}
	if (argc == with_boardsize_connectwin && (atoi(argv[SPECIFIED_BOARDSIZE - 1]) < 1 || atoi(argv[NUM_CONSEQ_PIECES - 1]) < 1)) {
		cout << "Invalid board size or connecting pieces to win, must be greater than 0" << endl;
		return INVALID_ADDITIONAL_ARGS;
	}
	if (argc == 1){
		usage(argv[PROG_NAME], "game name");
		return INVALID_USAGE_METHOD;
	}
	try
	{
		GameBase::pick_game(argc, argv);
		return GameBase::instance()->play();
	}
	catch (bad_alloc &ba)
	{
		cout << ba.what() << endl;
		return MEM_ALLOC_FAIL;
	}
	catch (board_ret_val val){
		usage(argv[PROG_NAME], "game name");
		return val;
	}

}


