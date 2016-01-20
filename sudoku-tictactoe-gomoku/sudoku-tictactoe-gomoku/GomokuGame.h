#ifndef GOMOKUGAME_H
#define GOMOKUGAME_H

#include "GameBase.h"
#include <vector>
#include <iostream>
#include <string>

//Michelle Yuan (michelleyuan@wustl.edu)
//Shefali Gupta (shefali.gupta@wustl.edu)
//Rebecca Siow (rebecca.siow@wustl.edu)
class GomokuGame : public GameBase {

protected:
	friend std::ostream &operator<< (std::ostream &os, const GomokuGame &gg);


private:
	std::vector<std::string> white_loc;
	std::vector<std::string> black_loc;
	unsigned int connect_wins;
	static const unsigned gg_board_side = 19;
	static const unsigned default_connect_wins = 5;
	bool winner;

public:
	virtual bool done();
	virtual bool stalemate();
	virtual int turn();
	virtual void print();
	virtual int save(std::ofstream &ofs);
	virtual int load(std::ifstream &ifs);

	GomokuGame();
	GomokuGame(int boardsize);
	GomokuGame(int boardsize, int connectwins);
};

std::ostream &operator<< (std::ostream &os, const GomokuGame &gg);

#endif