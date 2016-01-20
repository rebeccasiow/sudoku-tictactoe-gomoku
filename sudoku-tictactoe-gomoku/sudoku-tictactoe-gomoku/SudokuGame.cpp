#include "stdafx.h"
#include "SudokuGame.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <iomanip>
#include <set>
using namespace std;
//Michelle Yuan (michelleyuan@wustl.edu)
//Shefali Gupta (shefali.gupta@wustl.edu)
//Rebecca Siow (rebecca.siow@wustl.edu)

SudokuGame::SudokuGame() :GameBase(sg_boardsize){
	ifstream s;
	s.open("Sudoku");
	if (!s.is_open())
	{
		s.open("sudoku0");
		if (!s.is_open()){
			cout << "Saved Files cannot be opened. Empty Game will start." << endl;
		}
	}
	load(s);
}


SudokuGame::~SudokuGame()
{
}


void SudokuGame::print() {
	cout << *this;
}


ostream &operator<< (ostream &os, const SudokuGame &sg) { //draw game_board

	//sg.boardsize = 9, from 0 to 8 --> 9 iterations
	for (int i = sg.board_side - 1; i >= 0; --i) {
		cout << i << "||";

		//from 0 to 8
		for (int j = 0; j < sg.board_side; ++j) {
			cout << sg.game_board[(sg.board_side*i) + j].looks;

			if (j % 3 == 2) {
				cout << "||";
			}
			else {
				cout << "|";
			}
		}

		cout << endl;
		if (i % 3 == 0){
			cout << "=||=|=|=||=|=|=||=|=|=||" << endl;
		}
		else{
			cout << "-||-|-|-||-|-|-||-|-|-||" << endl;
		}
	}


	//printing the x-axis
	cout << "#||";
	for (int l = 0; l < sg.board_side; ++l) {
		cout << l;
		if (l % 3 == 2) {
			cout << "||";
		}
		else {
			cout << "|";
		}
	}

	cout << endl;
	return os;
}

void SudokuGame::prompt(unsigned int &x, unsigned int &y, unsigned int &number)
{
	while (true){
		cout << "enter valid coordinates <x>,<y>,<sudoku number> or 'quit' ";
		string command;
		getline(cin, command);
		if (command == "quit"){
			cout << "Would you like to save your game? ";
			string quitcommand;
			getline(cin, quitcommand);
			while (true){
				auto str = quitcommand.c_str();
				if (strcmp(str, "yes") == 0){
					cout << "HELLOOO" << endl;
					ofstream ofs;
					ofs.open("Sudoku");
					save(ofs);
					throw GAME_QUIT;
				}
				if (strcmp(str, "no") == 0){
					ofstream ofs;
					ofs.open(GameBase::gamename);
					ofs << "No Saved Data" << endl;
					throw GAME_QUIT;
				}
				cout << "please input <yes> or <no>" << endl;
			}
		}

		replace(command.begin(), command.end(), ',', ' ');

		istringstream iss(command);

		if (!(iss >> x && iss >> y && iss >> number)){
			cout << "invalid input, 1 or more values are not numbers" << endl;
			continue;
		}

		//checks if not correct case: greater than 9
		if (number > 9 || number == 0){
			cout << "number can only be between 1 and 9 inclusive" << endl;
			continue;
		}

		string extra;

		if (iss >> extra){
			cout << "invalid input, too many inputs" << endl;
			continue;
		}

		if (x >= 0 && x <= board_side - 1 && y >= 0 && y <= board_side - 1 && number <= 9) {
			break;
		}
		else {
			cout << "invalid input, coordinates must be between 0 and 8 inclusive" << endl;
			continue;
		}

		break;
	}
}

int SudokuGame::turn()
{
	unsigned x;
	unsigned y;
	unsigned number;
	try
	{
		SudokuGame::prompt(x, y, number);
	}
	catch (board_ret_val val){
		return val;
	}

	string snumber = std::to_string(number);

	//if empty square, add to filled_squares
	if (game_board[board_side * y + x].looks == " "){
		game_board[board_side * y + x].looks = snumber;
		++filled_squares;

	}
	else{
		game_board[board_side * y + x].looks = snumber;
	}

	cout << *this;
	return SUCCESS;
}

int SudokuGame::play() { //pulls everything together
	print();
	while (true)
	{
		if (turn() != SUCCESS){
			cout << "User quit. Turns played: " << turns << endl;
			return GAME_QUIT;
		}
		++turns; //increment # turns
		if (done()){
			cout << "You won!" << endl;
			return SUCCESS;
		}
	}
}





int SudokuGame::save(std::ofstream &ofs) {
	//sudoku0 doesn't require a "Sudoku" header like the rest
	for (int i = 0; i <board_side; --i){
		for (int j = 0; j < board_side; ++j){
			ofs << game_board[(board_side*i) + j].looks << " ";
			if (game_board[(board_side*i) + j].looks == " "){
				ofs << "0 ";
			}
		}
		ofs << endl;
	}
	return SUCCESS;
}
int SudokuGame::load(std::ifstream &ifs) {
	string line;
	for (int j = 0; j < board_side; ++j){

		if (!getline(ifs, line)){
			return FILE_READ_INCORRECTLY;
		}

		istringstream iss(line);

		if (strcmp(line.c_str(), "No Saved Data") == 0){
			ifstream s;
			s.open("sudoku0");
			if (!s.is_open()){
				cout << "Saved Files cannot be opened. Empty Game will start." << endl;
			}
			load(s);
			break;
		}

		for (int i = 0; i < board_side; ++i){

			string number;
			iss >> number;

			if (number != "0"){
				int check_valid = strtol(number.c_str(), NULL, 10);
				if (check_valid > 0 && check_valid < 10){
					game_piece gp;
					gp.looks = number;
					insert(gp, i, j);
					++filled_squares;
				}
				else{
					ifstream s;
					s.open("sudoku0");
					if (s.is_open()){
						cout << "Saved Files cannot be opened. sudoku0 is opened." << endl;
						load(s);
						return SUCCESS;
					}
					cout << "Invalid input in file and sudoku0 not found. Empty board loaded." << endl;
					for (size_t i = 0; i < game_board.size(); ++i){
						game_board[i].looks = " ";
					}
					return SUCCESS;
				}
			}

		}
	}
	return SUCCESS;
}
bool SudokuGame::done() {

	bool rows_cols = false;
	bool small_sq = false;

	//if all 9 rows and 9 columns contain elements, will return true
	int filled_row_count = 0;
	int sq_count = 0;

	//if full board
	if (filled_squares == 81){

		//for entire board
		for (int i = board_side - 1; i >= 0; --i) {

			std::set<int> row_fill;

			for (int j = 0; j < board_side; ++j) {

				int number = atoi(game_board[(board_side*i) + j].looks.c_str());
				row_fill.insert(number);

				/**
				//for k = 0 to 8,
				for (int k = j; k < board_side; ++k){

				if (strcmp(game_board[(board_side*i) + j].looks.c_str(),
				game_board[(board_side*i) + k].looks.c_str()) == 0){
				return false;
				}
				}**/
			}
			if (row_fill.size() == 9){
				++filled_row_count;
			}
			else {
				return false;
			}

		}
		if (filled_row_count = 18){
			rows_cols = true;
		}

		//FIRST 3 SQUARES
		//from columns i = 0 to i = 2, check 3 small squares
		std::set<int> sq_fill;
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				int number = atoi(game_board[(board_side*i) + j].looks.c_str());
				sq_fill.insert(number);

			}

		}
		if (sq_fill.size() == 9){
			++sq_count;
		}

		sq_fill.clear();
		for (int i = 0; i < 3; ++i) {
			for (int j = 3; j < 6; ++j) {
				int number = atoi(game_board[(board_side*i) + j].looks.c_str());
				sq_fill.insert(number);

			}

		}
		if (sq_fill.size() == 9){
			++sq_count;
		}

		sq_fill.clear();
		for (int i = 0; i < 3; ++i) {
			for (int j = 6; j < 9; ++j) {
				int number = atoi(game_board[(board_side*i) + j].looks.c_str());
				sq_fill.insert(number);

			}

		}
		if (sq_fill.size() == 9){
			++sq_count;
		}

		//SECOND 3 SQUARES
		//from columns i = 3 to i = 6, check 3 small squares
		sq_fill.clear();
		for (int i = 3; i < 6; ++i) {
			for (int j = 0; j < 3; ++j) {
				int number = atoi(game_board[(board_side*i) + j].looks.c_str());
				sq_fill.insert(number);

			}

		}
		if (sq_fill.size() == 9){
			++sq_count;
		}

		sq_fill.clear();
		for (int i = 3; i < 6; ++i) {
			for (int j = 3; j < 6; ++j) {
				int number = atoi(game_board[(board_side*i) + j].looks.c_str());
				sq_fill.insert(number);

			}

		}
		if (sq_fill.size() == 9){
			++sq_count;
		}

		sq_fill.clear();
		for (int i = 3; i < 6; ++i) {
			for (int j = 6; j < 9; ++j) {
				int number = atoi(game_board[(board_side*i) + j].looks.c_str());
				sq_fill.insert(number);

			}

		}
		if (sq_fill.size() == 9){
			++sq_count;
		}

		//THIRD 3 SQUARES
		//from columns i = 6 to i = 8, check 3 small squares
		sq_fill.clear();
		for (int i = 6; i < 9; ++i) {
			for (int j = 0; j < 3; ++j) {
				int number = atoi(game_board[(board_side*i) + j].looks.c_str());
				sq_fill.insert(number);


			}

		}
		if (sq_fill.size() == 9){
			++sq_count;
		}

		sq_fill.clear();
		for (int i = 6; i < 9; ++i) {
			for (int j = 3; j < 6; ++j) {
				int number = atoi(game_board[(board_side*i) + j].looks.c_str());
				sq_fill.insert(number);

			}

		}
		if (sq_fill.size() == 9){
			++sq_count;
		}

		sq_fill.clear();
		for (int i = 6; i < 9; ++i) {
			for (int j = 6; j < 9; ++j) {
				int number = atoi(game_board[(board_side*i) + j].looks.c_str());
				sq_fill.insert(number);

			}

		}
		if (sq_fill.size() == 9){
			++sq_count;
		}

		if (sq_count == 9){
			small_sq = true;
		}
		if (small_sq && rows_cols){
			return true;
		}
	}
	return false;
}
int SudokuGame::insert(game_piece gp, int xloc, int yloc){
	game_board[board_side * yloc + xloc] = gp;

	if (longest_string < gp.looks.size()){
		longest_string = gp.looks.size();
	}
	return SUCCESS;
}

bool SudokuGame::stalemate() {
	return false;
}