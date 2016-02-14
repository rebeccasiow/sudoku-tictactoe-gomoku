# sudoku-tictactoe-gomoku
C++ program where users can play sudoku, tictactoe and gomoku. 

Michelle Yuan, Rebecca Siow, Shefali Gupta
Lab 4
========================================================================
    CONSOLE APPLICATION : Lab4 Project Overview
========================================================================

All virtual stuff written in gamebase.cpp
even though we wrote what they were in gamebase, we can override in derived classes.
pure virtual cannot even be overriden. 
copy constructor - makes a copy of an existing game


Copy Control Design Decisions:
We did not use copy control features in our lab. We instead start a new game every
time but load the saved game from a file containing the game data.

Saved Game File Formatting Choices:
We stored the game data into a file as follows: the first line is the name of the
game. The next two lines have the board dimensions. The following lines contain
the coordinates of the game pieces, with each line alternating between each player
(e.g. for Gomoku: line 3 --> Black's coordinates, line 4 --> White's coordinates).


Work Distribution:
We split up the work evenly by meeting up to code outside of class. We set up
a BitBucket repository to allow us to work on the project individually as well 
and make sure we weren't coding the same things over and over.


Errors and Warnings:
We kept getting a vector subscript out of range error when trying to quit Sudoku 
from the command line.


method. This was because we copied and pasted the game board vector from Lab 2 
and it overwrote the vector we initialized in GameBase.cpp. We fixed this problem 
by removing the vector from the derived classes.


Test Cases:
We ran the following test cases:

	TicTacToe:
	command:	Lab4.exe TicTacToe
	output:		A game board with a prompt as follows:
				4
				3
				2
				1
				0
				 0 1 2 3 4
				Player X:
				enter valid coordinates <x>,<y> or 'quit'

	command:	Lab4.exe TicTac
	output:		An error message with a suggestion on how to use the program.
				Usage: Lab4.exe <game name> <OPTIONAL specified board size> <OPTIONAL specified 
				connecting pieces to win>

	command:	Lab4.exe 
	output:		A usage message indicating how many arguments need to be specified.
				Usage: Lab4.exe <game name> <OPTIONAL specified board size> <OPTIONAL specified 
				connecting pieces to win>

	command:	Lab4.exe TicTacToe TicTacToe
	output:		A usage message indicating how many arguments need to be specified.
				Usage: Lab4.exe <game name> <OPTIONAL specified board size> <OPTIONAL specified 
				connecting pieces to win>

	Inputs while in-game:
	command:	1,1
	output:		4
				3
				2
				1  X
				0
				 0 1 2 3 4

				Player X: (1, 1)

				Player O:
				enter valid coordinates <x>,<y> or 'quit'


	command:	a,b
	output:		invalid input, 1 or more values are not numbers

	command:	
	output:		enter valid coordinates <x>,<y> or 'quit'

	command:	1,0
	output:		invalid input, coordinates must be between 1 and 3, inclusive

	command:	1,asdfglj
	output:		invalid input, 1 or more values are not numbers

	command:	1,2 dsjkgd
	output:		invalid input, too many inputs

	command:	1 4
	output:		enter valid coordinates <x>,<y> or 'quit'

	command:	quit
	output:		User quit. Turns played: 1



	Gomoku:
	command:	Lab4.exe Gomoku
	output:		A game board with a prompt as follows:
				20
				19
				18
				17
				16
				15
				14
				13
				12
				11
				10
				 9
				 8
				 7
				 6
				 5
				 4
				 3
				 2
				 1
				 0
				 X 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
				Player Black:
				enter valid coordinates <x>,<y> or 'quit'


	command:	Lab4.exe Gomok
	output:		An error message with a suggestion on how to use the program.
				Usage: Lab4.exe <game name> <OPTIONAL specified board size> <OPTIONAL specified 
				connecting pieces to win>


	Inputs while in-game:
	command:	2,2
	output:		A game board with a prompt as follows:
				20
				19
				18
				17
				16
				15
				14
				13
				12
				11
				10
				 9
				 8
				 7
				 6
				 5
				 4
				 3
				 2		 B
				 1
				 0
				 X 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
				Player Black: 2,2;

				Player White:
				enter valid coordinates <x>,<y> or 'quit'

	command:	quit
	output:		A prompt asking the user if they want to save the game as follows:
				Would you like to save your game?

	command:	yes
	output:		User quit. Turns played: 1

	command:	Lab4.exe Gomoku
	output:		A game board containing the pieces from the previously saved session:
				20
				19
				18
				17
				16
				15
				14
				13
				12
				11
				10
				 9
				 8
				 7
				 6
				 5
				 4
				 3
				 2       B
				 1
				 0
				 X 0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20
				Player Black:
				enter valid coordinates <x>,<y> or 'quit'

	command:	a,b
	output:		invalid input, 1 or more values are not numbers

	command:	
	output:		enter valid coordinates <x>,<y> or 'quit'

	command:	1,0
	output:		invalid input, coordinates must be between 1 and 3, inclusive

	command:	1,asdfglj
	output:		invalid input, 1 or more values are not numbers

	command:	1,2 dsjkgd
	output:		invalid input, too many inputs

	command:	1 4
	output:		enter valid coordinates <x>,<y> or 'quit'


	Sudoku:
	command:	Lab4.exe Sudoku
	output:		A game board with a prompt as follows:
				8|| | | || | | || | | || 
				-||-|-|-||-|-|-||-|-|-||
				7|| | | || | | || | | ||
				-||-|-|-||-|-|-||-|-|-||
				6|| | | || | | || | | ||
				=||=|=|=||=|=|=||=|=|=||
				5|| | | || | | || | | ||
				-||-|-|-||-|-|-||-|-|-||
				4|| | | || | | || | | ||
				-||-|-|-||-|-|-||-|-|-||
				3|| | | || | | || | | ||
				=||=|=|=||=|=|=||=|=|=||
				2|| | | || | | || | | ||
				-||-|-|-||-|-|-||-|-|-||
				1|| | | || | | || | | ||
				-||-|-|-||-|-|-||-|-|-||
				0|| | | || | | || | | ||
				=||=|=|=||=|=|=||=|=|=||
				#||0|1|2||3|4|5||6|7|8||
				enter valid coordinates <x>,<y> or 'quit'

	command:	Lab4.exe Sudo
	output:		An error message with a suggestion on how to use the program.
				Usage: Lab4.exe <game name> <OPTIONAL specified board size> <OPTIONAL specified 
				connecting pieces to win>

	Inputs while in-game:
	command:	1,1
	output:		4
				3
				2
				1  X
				0
				 0 1 2 3 4

				Player X: (1, 1)

				Player O:
				enter valid coordinates <x>,<y> or 'quit'


	command:	a,b
	output:		invalid input, 1 or more values are not numbers

	command:	
	output:		enter valid coordinates <x>,<y> or 'quit'

	command:	1,0
	output:		invalid input, coordinates must be between 1 and 3, inclusive

	command:	1,asdfglj
	output:		invalid input, 1 or more values are not numbers

	command:	1,2 dsjkgd
	output:		invalid input, too many inputs

	command:	1 4
	output:		enter valid coordinates <x>,<y> or 'quit'

	command:	quit
	output:		User quit. Turns played: 1

TEST CASE: File to Load contains alphabets and characters. 
RESULT: New game will start.

H:\My Documents\Visual Studio 2013\Projects\Lab4\Lab4\Debug>Lab4.exe Sudoku
Invalid input in file. Empty board will load.
8|| | | || | | || | | ||
-||-|-|-||-|-|-||-|-|-||
7|| | | || | | || | | ||
-||-|-|-||-|-|-||-|-|-||
6|| | | || | | || | | ||
=||=|=|=||=|=|=||=|=|=||
5|| | | || | | || | | ||
-||-|-|-||-|-|-||-|-|-||
4|| | | || | | || | | ||
-||-|-|-||-|-|-||-|-|-||
3|| | | || | | || | | ||
=||=|=|=||=|=|=||=|=|=||
2|| | | || | | || | | ||
-||-|-|-||-|-|-||-|-|-||
1|| | | || | | || | | ||
-||-|-|-||-|-|-||-|-|-||
0|| | | || | | || | | ||
=||=|=|=||=|=|=||=|=|=||
#||0|1|2||3|4|5||6|7|8||

TEST CASE: Input contains alphabets and unwanted characters.
RESULTS: No changes to board. Program will reprompt.

FROM COMMAND LINE:

enter valid coordinates <x>,<y>,<sudoku number> or 'quit' 2,2,1000
number can only be between 1 and 9 inclusive
enter valid coordinates <x>,<y>,<sudoku number> or 'quit' 010,10
invalid input, 1 or more values are not numbers
enter valid coordinates <x>,<y>,<sudoku number> or 'quit' 10,10,10
number can only be between 1 and 9 inclusive
enter valid coordinates <x>,<y>,<sudoku number> or 'quit' ja,a'd
invalid input, 1 or more values are not numbers
enter valid coordinates <x>,<y>,<sudoku number> or 'quit' 1
invalid input, 1 or more values are not numbers
enter valid coordinates <x>,<y>,<sudoku number> or 'quit'
invalid input, 1 or more values are not numbers
enter valid coordinates <x>,<y>,<sudoku number> or 'quit' s
invalid input, 1 or more values are not numbers

TEST CASE:
No Saved Data --> opens sudoku0 and if not, will start new game.




Summary:
Lab 4 implements a refactored Tic-Tac-Toe and Gomoku that allows users to play Sudoku as well,
and gives users the ability to save and load game sessions.


Extra Credit:
We generalized the Gomoku game board by creating parameterized constructors, one which
takes in an additional game board size variable, and a second that also accepts a value
specifying the number of pieces that must be consecutive in order to win.

	command:	Lab4.exe Gomoku 3
	output:		A game board with a prompt as follows:
				 4
				 3
				 2
				 1
				 0
				 X 0  1  2  3  4
				Player Black:
				enter valid coordinates <x>,<y> or 'quit'

	command:	3,1
	output:		 4
				 3
				 2
				 1			B
				 0
				 X 0  1  2  3  4
				Player Black: 3,1;

				Player White:
				enter valid coordinates <x>,<y> or 'quit'

	command:	Lab4.exe Gomoku 3 3
	output:		A game board with a prompt as follows:
				 4
				 3
				 2
				 1
				 0
				 X 0  1  2  3  4
				Player Black:
				enter valid coordinates <x>,<y> or 'quit'

	command:	Lab4.exe Gomoku 6 2
	output:		 7
				 6
				 5
				 4
				 3
				 2
				 1
				 0
				 X 0  1  2  3  4  5  6  7
				Player Black:
				enter valid coordinates <x>,<y> or 'quit'

				Winning case:
				 7
				 6
				 5
				 4
				 3
				 2    B
				 1    B              W
				 0
				 X 0  1  2  3  4  5  6  7
				Player Black: 1,1; 1,2;

				Player 1 won!
				It took 3 turns.

				Draw case:
				 4
				 3    B  W  B
				 2    W  W  B
				 1    B  B  W
				 0
				 X 0  1  2  3  4
				Player Black: 1,1; 3,3; 1,3; 2,1; 3,2;

				It's a draw!
				Turns played: 9

				Invalid cases:
				command: Lab4.exe Gomoku -3
				output: Invalid board size, must be greater than 0

				command: Lab4.exe Gomoku 0
				output: Invalid board size, must be greater than 0

				command: Lab4.exe Gomoku -3 -4
				output: Invalid board size or connecting pieces to win, must be greater than 0






AppWizard has created this Lab3 application for you.

This file contains a summary of what you will find in each of the files that
make up your Lab3 application.


Lab3.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Lab3.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Lab3.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Lab3.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
