#ifndef LAB_3
#define LAB_3

#include <string>

/*
//Michelle Yuan (michelleyuan@wustl.edu)
//Shefali Gupta (shefali.gupta@wustl.edu)
//Rebecca Siow (rebecca.siow@wustl.edu)
*/

enum board_ret_val
{
	SUCCESS,
	//FILE_OPENED_INCORRECTLY,
	FILE_READ_INCORRECTLY,
	//NO_GAMEPIECES_READ,
	INVALID_USAGE_METHOD,
	GAME_QUIT,
	INCORRECT_INPUT_NUMBER,
	INCORRECT_INPUT,
	WRONG_FORMAT,
	PIECE_NOT_INSERTED,
	MEM_ALLOC_FAIL,
	GAME_DRAW,
	INVALID_BOARD_SIZE,
	INVALID_ADDITIONAL_ARGS,
	NULLPTR_RETURNED,
	NOT_NULLPTR,
	BAD_GAME,
	WRONG_GAME
};

int usage(std::string progname, std::string game);

#endif
