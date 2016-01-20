#include "stdafx.h"
#include "GamePiece.h"
#include "TicTacToeGame.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <iomanip>

using namespace std;

/*
//Michelle Yuan (michelleyuan@wustl.edu)
//Shefali Gupta (shefali.gupta@wustl.edu)
//Rebecca Siow (rebecca.siow@wustl.edu)
*/

TicTacToeGame::TicTacToeGame() :GameBase(tttg_board_side){
	ifstream ttt;
	ttt.open("TicTacToe");
	if (ttt.is_open()){
		load(ttt);
	}
}

ostream &operator<< (ostream &os, const TicTacToeGame &tttg) { //draw game_board
	for (int i = tttg.board_side - 1; i >= 0; --i){
		cout << i;
		for (int j = 0; j < tttg.board_side; ++j){
			cout << std::setw(tttg.longest_string) << tttg.game_board[(tttg.board_side *i) + j].looks;
		}
		cout << endl;
	}
	cout << " ";
	for (int i = 0; i < tttg.board_side; ++i){
		cout << std::setw(tttg.longest_string) << i;
	}
	cout << endl;
	return os;
}

bool TicTacToeGame::done() {
	for (size_t i = 1; i <= 3; ++i){ //checks columns
		if (game_board[(board_side * 1) + i].looks == " "){
			continue;
		}
		if (game_board[(board_side * 1) + i].looks == game_board[(board_side * 2) + i].looks
			&& game_board[(board_side * 1) + i].looks == game_board[(board_side * 3) + i].looks){
			return true;
		}
	}

	for (size_t i = 1; i <= 3; ++i){ //checks rows
		if (game_board[(board_side * i) + 1].looks == " "){
			continue;
		}
		if (game_board[(board_side*i) + 1].looks == game_board[(board_side*i) + 2].looks
			&& game_board[(board_side*i) + 1].looks == game_board[(board_side*i) + 3].looks){
			return true;
		}
	}

	if (game_board[(board_side * 1) + 1].looks == game_board[(board_side * 2) + 2].looks //checks diagonal
		&& game_board[(board_side * 1) + 1].looks == game_board[(board_side * 3) + 3].looks
		&& game_board[(board_side * 1) + 1].looks != " "){
		return true;
	}

	if (game_board[(board_side * 1) + 3].looks == game_board[(board_side * 2) + 2].looks //checks other diagonal
		&& game_board[(board_side * 1) + 3].looks == game_board[(board_side * 3) + 1].looks
		&& game_board[(board_side * 1) + 3].looks != " ")
	{
		return true;
	}
	return false;
}

bool TicTacToeGame::stalemate() { //checks if there is a tie
	if (done() || turns < 9){
		return false;
	}
	return true;
}


int TicTacToeGame::turn() {

	string player = "X"; //checks which player is playing
	if (player1) {
		cout << "Player X:" << endl;
	}
	else {
		cout << "Player O:" << endl;
		player = "O";
	}

	unsigned x;
	unsigned y;

	while (true) {
		int result = prompt(x, y);

		if (result != SUCCESS){
			return result;
		}

		if (game_board[board_side * y + x].looks != " "){
			cout << "spot already filled" << endl;
			continue;
		}

		game_board[board_side * y + x].looks = player;

		if (player == "X"){
			x_loc.push_back(to_string(x) + "," + to_string(y));
		}
		else{
			o_loc.push_back(to_string(x) + "," + to_string(y));
		}

		break;
	}

	cout << *this;

	if (player1){
		cout << "Player X: ";
		for (size_t i = 0; i < x_loc.size(); ++i){
			cout << x_loc[i] << ";";
		}
		cout << endl;
	}
	else {
		cout << "Player O: ";
		for (size_t i = 0; i < o_loc.size(); ++i){
			cout << o_loc[i] << ";";
		}
		cout << endl;
	}

	cout << endl;
	return SUCCESS;
}

void TicTacToeGame::print()
{
	cout << *this;
}

int TicTacToeGame::save(ofstream &ofs){
	ofs << "TicTacToe" << endl;
	ofs << x_loc.size() << endl;
	ofs << o_loc.size() << endl;
	for (unsigned int i = 0; i < x_loc.size(); ++i){
		ofs << x_loc[i] << endl;
	}
	for (unsigned int i = 0; i < o_loc.size(); ++i){
		ofs << o_loc[i] << endl;
	}
	return SUCCESS;
}

int TicTacToeGame::load(ifstream &ifs){
	string line;
	if (!getline(ifs, line)){
		return FILE_READ_INCORRECTLY;
	}
	if (!(line == "TicTacToe")){
		return WRONG_GAME;
	}
	//read x_loc.size()
	if (!getline(ifs, line)){
		return FILE_READ_INCORRECTLY;
	}
	int x_loc_size = atoi(line.c_str());

	//read o_loc.size()
	if (!getline(ifs, line)){
		return FILE_READ_INCORRECTLY;
	}
	int o_loc_size = atoi(line.c_str());
	;
	//get x placed pieces
	for (unsigned int i = 0; i < x_loc_size; ++i){
		if (!getline(ifs, line)){
			return FILE_READ_INCORRECTLY;
		}
		x_loc.push_back(line);
		std::replace(line.begin(), line.end(), ',', ' ');
		istringstream iss(line);
		int x, y;
		iss >> x;
		iss >> y;
		game_piece gp;
		gp.looks = "X";
		insert(gp, x, y);
	}
	for (unsigned int i = 0; i < o_loc_size; ++i){
		if (!getline(ifs, line)){
			return FILE_READ_INCORRECTLY;
		}
		o_loc.push_back(line);
		std::replace(line.begin(), line.end(), ',', ' ');
		istringstream iss(line);
		int x, y;
		iss >> x;
		iss >> y;
		game_piece gp;
		gp.looks = "O";
		insert(gp, x, y);

	}
	return SUCCESS;
}