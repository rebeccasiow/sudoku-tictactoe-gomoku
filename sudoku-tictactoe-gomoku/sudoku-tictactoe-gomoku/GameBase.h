#ifndef GAMEBASE_H
#define GAMEBASE_H

#include "GamePiece.h"
#include "GameBase.h"
#include "Lab3.h"
#include <vector>
#include <iostream>
#include <string>
#include <memory>


/*
//Michelle Yuan (michelleyuan@wustl.edu)
//Shefali Gupta (shefali.gupta@wustl.edu)
//Rebecca Siow (rebecca.siow@wustl.edu)
*/

class GameBase {
protected:

	unsigned longest_string;
	bool player1 = true;
	int turns = 0;
	std::vector<game_piece> game_board;
	const int board_side;
	static std::shared_ptr<GameBase> gbpointer;

public:
	virtual bool done() = 0;
	virtual bool stalemate() = 0;
	virtual int prompt(unsigned int &x, unsigned int &y);
	virtual int turn() = 0;
	virtual int play();
	virtual int insert(game_piece gp, int xloc, int yloc);
	static void pick_game(int argc, char* argv[]);
	static std::shared_ptr<GameBase> instance();
	static std::string gamename;


	virtual void print() = 0;
	GameBase(int size);
	virtual int save(std::ofstream &ofs) = 0;
	virtual int load(std::ifstream &ifs) = 0;
};


enum values{
	PROG_NAME,
	GAMETYPE,
	NUM_ARGS,
	SPECIFIED_BOARDSIZE,
	NUM_CONSEQ_PIECES,
};
#endif
