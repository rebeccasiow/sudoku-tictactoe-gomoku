Michelle Yuan, Rebecca Siow, Shefali Gupta

========================================================================
    CONSOLE APPLICATION : Sudoku-Tictactoe-Gomoku Project Overview
========================================================================

Users can take turns playing Sudoku, TictacToe or Gomoku games that allows saving and loading.
To run the program: build the solution, move into the Debug directory and enter the commands: tictactoe

Test Cases:
We ran the following test cases:

	TicTacToe:
	command:	Lab3.exe TicTacToe
	output:		A game board with a prompt as follows:
				4
				3
				2
				1
				0
				 0 1 2 3 4
				Player X:
				enter valid coordinates <x>,<y> or 'quit'

	command:	Lab3.exe TicTac
	output:		An error message with a suggestion on how to use the program.
				Usage: Lab3.exe <game name> 

	command:	Lab3.exe 
	output:		A usage message indicating how many arguments need to be specified.
				Usage: Lab3.exe <game name> 

	command:	Lab2.exe TicTacToe TicTacToe
	output:		A usage message indicating how many arguments need to be specified.
				Usage: Lab3.exe <game name>

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
	command:	Lab3.exe Gomoku
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


	command:	Lab3.exe Gomok
	output:		An error message with a suggestion on how to use the program.
				Usage: Lab3.exe <game name> <OPTIONAL specified board size> <OPTIONAL specified 
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


Summary:
Lab 3 implements a refactored Tic-Tac-Toe that allows the user to play Gomoku as well.


Extra Credit:
We generalized the Gomoku game board by creating parameterized constructors, one which
takes in an additional game board size variable, and a second that also accepts a value
specifying the number of pieces that must be consecutive in order to win.

	command:	Lab3.exe Gomoku 3
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

	command:	Lab3.exe Gomoku 3 3
	output:		A game board with a prompt as follows:
				 4
				 3
				 2
				 1
				 0
				 X 0  1  2  3  4
				Player Black:
				enter valid coordinates <x>,<y> or 'quit'

	command:	Lab3.exe Gomoku 6 2
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
				command: Lab3.exe Gomoku -3
				output: Invalid board size, must be greater than 0

				command: Lab3.exe Gomoku 0
				output: Invalid board size, must be greater than 0

				command: Lab3.exe Gomoku -3 -4
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
