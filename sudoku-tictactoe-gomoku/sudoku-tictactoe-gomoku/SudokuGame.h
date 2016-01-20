#pragma once
#include "GameBase.h"
//Michelle Yuan (michelleyuan@wustl.edu)
//Shefali Gupta (shefali.gupta@wustl.edu)
//Rebecca Siow (rebecca.siow@wustl.edu)
class SudokuGame : public GameBase
{

private:
	static const unsigned sg_boardsize = 9;
	int filled_squares = 0;

protected:
	friend std::ostream &operator<< (std::ostream &os, const SudokuGame &sg);

public:
	SudokuGame();
	~SudokuGame();
	virtual bool done();
	virtual bool stalemate();
	virtual int load(std::ifstream &ifs);
	virtual int save(std::ofstream &ofs);
	virtual void print();
	virtual int turn();
	virtual int insert(game_piece gp, int xloc, int yloc);
	//new methods
	virtual void prompt(unsigned int &x, unsigned int &y, unsigned int &number);
	virtual int play();

};

