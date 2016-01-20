/*
//Michelle Yuan (michelleyuan@wustl.edu)
//Shefali Gupta (shefali.gupta@wustl.edu)
//Rebecca Siow (rebecca.siow@wustl.edu)
*/

#include "stdafx.h"
#include "GamePiece.h"
#include "GomokuGame.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <iomanip>

using namespace std;

GomokuGame::GomokuGame(int boardsize, int connectwins) :GameBase(boardsize + 2), winner(false), connect_wins(connectwins){}
GomokuGame::GomokuGame(int boardsize) : GomokuGame(boardsize, default_connect_wins){}
GomokuGame::GomokuGame() : GomokuGame(gg_board_side){
	ifstream gg;
	gg.open("Gomoku");
	if (gg.is_open()){
		load(gg);
	}
}

ostream &operator<< (ostream &os, const GomokuGame &gg) { //draw game_board
	for (int i = gg.board_side - 1; i >= 0; --i){
		cout << setw(gg.longest_string) << i;
		for (int j = 0; j < gg.board_side; ++j){
			cout << setw(gg.longest_string) << gg.game_board[(gg.board_side *i) + j].looks << " ";
		}
		cout << endl;
	}
	cout << setw(gg.longest_string) << "X";
	for (int i = 0; i <= gg.board_side - 1; ++i){
		cout << std::setw(gg.longest_string) << i << " ";
	}
	cout << endl;
	return os;
}

int GomokuGame::turn() {
	string player = "B"; //checks which player is playing
	if (player1) {
		cout << "Player Black:" << endl;
	}
	else {
		cout << "Player White:" << endl;
		player = "W";
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

		if (player == "B"){
			black_loc.push_back(to_string(x) + "," + to_string(y));
		}
		else{
			white_loc.push_back(to_string(x) + "," + to_string(y));
		}

		break;
	}

	cout << *this;

	if (player1){
		cout << "Player Black: ";
		for (size_t i = 0; i < black_loc.size(); ++i){
			cout << black_loc[i] << "; ";
		}
		cout << endl;
	}
	else {
		cout << "Player White: ";
		for (size_t i = 0; i < white_loc.size(); ++i){
			cout << white_loc[i] << "; ";
		}
		cout << endl;
	}

	cout << endl;


	int longest_seq = 0;

	int x_upperbound = x + (connect_wins - 1);
	int x_lowerbound = x - (connect_wins - 1);
	if (x_upperbound > (board_side - 2)){
		x_upperbound = (board_side - 2);
	}
	if (x_lowerbound < 1){
		x_lowerbound = 1;
	}

	int y_upperbound = y + (connect_wins - 1);
	int y_lowerbound = y - (connect_wins - 1);
	if (y_upperbound >(board_side - 2)){
		y_upperbound = (board_side - 2);
	}
	if (y_lowerbound < 1){
		y_lowerbound = 1;
	}

	for (int i = x_lowerbound; i <= x_upperbound; ++i){ //checks column
		if (game_board[(board_side * y) + i].looks != player){
			longest_seq = 0;
			continue;
		}
		longest_seq++;
		if (longest_seq == connect_wins){
			winner = true;
			return SUCCESS;
		}
	}

	longest_seq = 0;

	for (int i = y_lowerbound; i <= y_upperbound; ++i){ //checks rows
		if (game_board[(board_side * i) + x].looks != player){
			longest_seq = 0;
			continue;
		}
		longest_seq++;
		if (longest_seq == connect_wins){
			winner = true;
			return SUCCESS;
		}
	}

	longest_seq = 0;

	//checks diagonals

	int i, j;

	for (i = x_lowerbound, j = y_upperbound; i <= x_upperbound && j >= y_lowerbound; ++i, --j){ //checks column
		if (game_board[(board_side * i) + j].looks != player){
			longest_seq = 0;
			continue;
		}
		longest_seq++;
		if (longest_seq == connect_wins){
			winner = true;
			return SUCCESS;
		}
	}

	longest_seq = 0;

	for (i = x_upperbound, j = y_upperbound; i >= x_lowerbound && j >= y_lowerbound; --i, --j){ //checks column
		if (game_board[(board_side * i) + j].looks != player){
			longest_seq = 0;
			continue;
		}
		longest_seq++;
		if (longest_seq == connect_wins){
			winner = true;
			return SUCCESS;
		}
	}

	return SUCCESS;
}

void GomokuGame::print()
{
	cout << *this;
}

bool GomokuGame::stalemate() {
	int playable_board = board_side - 2;
	if (done() || turns < (playable_board*playable_board)){
		return false;
	}
	return true;
}

bool GomokuGame::done() {
	return winner;
}

int GomokuGame::save(ofstream &ofs){
	ofs << "Gomoku" << endl;
	ofs << white_loc.size() << endl;
	ofs << black_loc.size() << endl;
	for (unsigned int i = 0; i < white_loc.size(); ++i){
		ofs << white_loc[i] << endl;
	}
	for (unsigned int i = 0; i < black_loc.size(); ++i){
		ofs << black_loc[i] << endl;
	}
	return SUCCESS;

}

int GomokuGame::load(std::ifstream &ifs){
	string line;
	if (!getline(ifs, line)){
		return FILE_READ_INCORRECTLY;
	}
	if (!(line == "Gomoku")){
		return WRONG_GAME;
	}
	//read white_loc.size()
	if (!getline(ifs, line)){
		return FILE_READ_INCORRECTLY;
	}
	int white_loc_size = atoi(line.c_str());

	//read black_loc.size()
	if (!getline(ifs, line)){
		return FILE_READ_INCORRECTLY;
	}
	int black_loc_size = atoi(line.c_str());
	;
	//get white placed pieces
	for (int i = 0; i < white_loc_size; ++i){
		if (!getline(ifs, line)){
			return FILE_READ_INCORRECTLY;
		}
		black_loc.push_back(line);
		std::replace(line.begin(), line.end(), ',', ' ');
		istringstream iss(line);
		int x, y;
		iss >> x;
		iss >> y;
		game_piece gp;
		gp.looks = "W";
		insert(gp, x, y);
	}
	//get black placed pieces
	for (int i = 0; i < black_loc_size; ++i){
		if (!getline(ifs, line)){
			return FILE_READ_INCORRECTLY;
		}
		black_loc.push_back(line);
		std::replace(line.begin(), line.end(), ',', ' ');
		istringstream iss(line);
		int x, y;
		iss >> x;
		iss >> y;
		game_piece gp;
		gp.looks = "B";
		insert(gp, x, y);

	}
	return SUCCESS;
}
