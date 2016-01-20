#include "stdafx.h"
#include "GamePiece.h"
#include "TicTacToeGame.h"
#include "Lab3.h"
#include "GameBase.h"
#include "GomokuGame.h"
#include "SudokuGame.h"
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


shared_ptr<GameBase> GameBase::gbpointer = nullptr;
string GameBase::gamename;

GameBase::GameBase(int size)
:longest_string(2), board_side(size)
{
	game_board = vector<game_piece>(board_side*board_side);
	for (size_t i = 0; i < game_board.size(); ++i){
		game_board[i].looks = " ";
	}
}

shared_ptr<GameBase> GameBase::instance(){
	if (gbpointer != nullptr){
		return gbpointer;
	}
	throw NULLPTR_RETURNED;
}

int GameBase::insert(game_piece gp, int xloc, int yloc){

	if (game_board[board_side * yloc + xloc].looks != " "){
		cout << "spot already filled" << endl;
		return PIECE_NOT_INSERTED;
	}
	game_board[board_side * yloc + xloc] = gp;

	if (longest_string < gp.looks.size()){
		longest_string = gp.looks.size();
	}
	return SUCCESS;
}

int GameBase::prompt(unsigned int &x, unsigned int &y) { //gets user input
	while (true){
		cout << "enter valid coordinates <x>,<y> or 'quit' ";
		string command;
		if (!getline(cin, command)){
			continue;
		}

		if (command == "quit"){
			cout << "Would you like to save your game?";
			string quitcommand;
			getline(cin, quitcommand);
			if (strcmp(quitcommand.c_str(), "yes") == 0){
				ofstream ofs;
				ofs.open(GameBase::gamename);
				save(ofs);
			}
			else {
				ofstream ofs;
				ofs.open(GameBase::gamename);
				ofs << "No Saved Data" << endl;
			}
			return GAME_QUIT;
		}

		int format = command.find(",");
		if (format != string::npos){
			command[format] = ' ';
		}
		else {
			continue;
		}

		istringstream iss(command);

		if (!(iss >> x && iss >> y)){
			cout << "invalid input, 1 or more values are not numbers" << endl;
			continue;
		}

		string extra;

		if (iss >> extra){
			cout << "invalid input, too many inputs" << endl;
			continue;
		}

		//correct case
		if (x > 0 && x < board_side - 1 && y > 0 && y < board_side - 1) {
			break;
		}
		else {
			cout << "invalid input, coordinates must be between 1 and " << board_side - 2 << ", inclusive" << endl;
		}
	}

	return SUCCESS;
}


int GameBase::play() { //pulls everything together
	print();
	while (true)
	{
		if (turn() != SUCCESS){
			cout << "User quit. Turns played: " << turns << endl;
			return GAME_QUIT;
		}
		++turns; //increment # turns
		if (done()){
			if (player1){
				cout << "Player 1 won!" << endl << "It took " << turns << " turns." << endl;
				return SUCCESS;
			}
			cout << "Player 2 won!" << endl << "It took " << turns << " turns." << endl;
			return SUCCESS;
		}
		if (stalemate()){
			cout << "It's a draw!" << endl;
			cout << "Turns played: " << turns << endl;
			return GAME_DRAW;
		}
		player1 = !player1; //change players
	}
}

void GameBase::pick_game(int argc, char* argv[]){
	if (gbpointer != nullptr){
		throw NOT_NULLPTR;
	}
	gamename = argv[GAMETYPE];
	if (argc == NUM_ARGS && strcmp(argv[GAMETYPE], "TicTacToe") == 0){
		TicTacToeGame* tttg = new TicTacToeGame;
		gbpointer = shared_ptr<GameBase>(tttg);
	}
	//if user inputs additional arguments
	else if (argc >= NUM_ARGS && strcmp(argv[GAMETYPE], "Gomoku") == 0){

		//if user only specifies a board size
		if (argc == SPECIFIED_BOARDSIZE){
			int boardx = atoi(argv[SPECIFIED_BOARDSIZE - 1]);
			int default_boardsize = 5;
			if (boardx < default_boardsize){
				GomokuGame* gg = new GomokuGame(boardx, boardx);
				gbpointer = shared_ptr<GameBase>(gg);
			}
			GomokuGame* gg = new GomokuGame(boardx);
			gbpointer = shared_ptr<GameBase>(gg);
		}

		//if user specifies a board size and the number of consecutive pieces needed to win
		if (argc == NUM_CONSEQ_PIECES){
			int boardx = atoi(argv[SPECIFIED_BOARDSIZE - 1]);
			int connectwins = atoi(argv[NUM_CONSEQ_PIECES - 1]);
			if (connectwins > boardx){
				connectwins = boardx;
			}
			GomokuGame* gg = new GomokuGame(boardx, connectwins);
			gbpointer = shared_ptr<GameBase>(gg);
		}
		else {
			GomokuGame* gg = new GomokuGame;
			gbpointer = shared_ptr<GameBase>(gg);
		}
	}
	else if (argc >= NUM_ARGS && strcmp(argv[GAMETYPE], "Sudoku") == 0){
		SudokuGame* sg = new SudokuGame;
		gbpointer = shared_ptr<GameBase>(sg);
	}
	else if (argc < NUM_ARGS){
		usage("Lab4.exe", "game name");
		throw BAD_GAME;
	}
}