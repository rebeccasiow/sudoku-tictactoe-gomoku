#ifndef TICTACTOEGAME_H
#define TICTACTOEGAME_H

#include "GameBase.h"
#include <vector>
#include <iostream>
#include <string>

/*
//Michelle Yuan (michelleyuan@wustl.edu)
//Shefali Gupta (shefali.gupta@wustl.edu)
//Rebecca Siow (rebecca.siow@wustl.edu)
*/

class TicTacToeGame : public GameBase {

private:
	std::vector<std::string> x_loc;
	std::vector<std::string> o_loc;
	static const unsigned tttg_board_side = 5;

protected:
	friend std::ostream &operator<< (std::ostream &os, const TicTacToeGame &tttg);

public:
	virtual bool done();
	virtual bool stalemate();
	virtual int turn();
	virtual void print();
	virtual int save(std::ofstream &ofs);
	virtual int load(std::ifstream &ifs);
	TicTacToeGame();
};

std::ostream &operator<< (std::ostream &os, const TicTacToeGame &tttg);

#endif