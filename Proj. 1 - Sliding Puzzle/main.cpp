/* ==========================================
TITLE: [PROG] Project 1 - FEUP				|
											|
AUTHORS: Kevin Amorim - ei12057				|
		 Luís Magalhães - ei12054			|
											|
GROUP: T2G02								|
											|
DATE: 2013/04/21							|
											|
PURPOSE: Solve a sliding puzzle, that can	|
be choosed in 3 different sizes: 3x3, 4x4,	|
5x5.										|
There are 2 modes available. Training mode, |
that doesn't keep record of puzzles & time. |
Competition mode, that keep record of		|
puzzles & time.								|
											|
PARAMETERS:	No parameters needed. Just run	|
the .exe file and all the input is asked	|
on the console.								|
											|
INSTRUCTIONS: Start the .exe file to start	|
the game.									|
Choose the language from the available ones.|
Navigate through the options on the menu	|
using your keyboard arrows. Select an option|
by pressing ENTER.							|
When the puzzle size is asked you have to	|
introduce one of those strings: "3x3",		|
"4x4","5x5" exactly like this.				|
'q' or 'Q' can be pressed at any time to go |
back one menu or to exit the game if you're |
on the main menu.							|
In-game sound can easily be deactivaded on	|
the main menu.								|
											|
											|
   -->  DEVELOPED WITH WINDOWS 8.  <--		|
=============================================
*/

// =========================
// | Third-party libraries |
// =========================
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <vector>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <CONIO.H>
#include <dos.h>
#include <stdio.h>
#include <Windows.h>

using namespace std;

// =====================

/* =========== ERROR CODES =====================

0			- Everything OK!
1			- Puzzle array is empty, size = 0
2			- Text file couldn't be opened
3			- Not a valid input
4			- Not a valid size
5 / (-1)	- No puzzle to load
================================================= */


// Functions declaration
int mainMenu();
int load_puzzle(const int puzzle_size, vector <vector<int>> &puzzle);
void playSound();
// =====================


// ====== Data Structures ======
struct ZERO
{
	short int line;
	short int col;
	short int temp_line;
	short int temp_col;
	short int backup_line;
	short int backup_col;
} szero;

struct FINAL_TIME
{
	int minutes;
	int seconds;
} sfinal_time;

struct KEY_CODE
{
	static const int KEY_ARROW = 224;
	static const int KEY_UP = 72;
	static const int KEY_RIGHT = 77;
	static const int KEY_DOWN = 80;
	static const int KEY_LEFT = 75;
	static const int KEY_Q = 81;
	static const int KEY_q = 113;
	static const int KEY_ENTER = 13;

} skey_code;

struct MENU_ITEM 
{
	static const int TRAINING = 0;
	static const int COMPETITION = 1;
	static const int LANGUAGE = 2;
	static const int SOUND = 3;
	static const int QUIT = 4;
	static const int NEW = 0;
	static const int LOAD = 1;
	static const int BACK = 2;
} smenu_item;

struct LANG
{
	static const int PT = 0;
	static const int EN = 1;

} slang;

// ==============================================

//Global Variables Declaration
short int langSelected = slang.EN;
bool soundState = true;
// ===========================


/* ========================================
	         AUXILIARY FUNCTIONS
=========================================== */


/* ==========================================
    +++++++++++++ Clear Screen +++++++++++++     
   ==========================================
|												
|	Function to clear console windows. It's 
|	a lot better than the system("cls") function.
|	We had to search for some examples to see
|	how cleaning the console with Windows API was.
|	
|	We've found some information about that
|	on Cplusplus.com
|	
|	Source: http://www.cplusplus.com/articles/4z18T05o/
|
|	We've tested it and it appears to be almost
|	+16x faster than using system("cls"). 
|
|=============================================
*/
void clearScreen()
{
	// =====  VARIABLES  ======= 

	// Handle for the output console
	HANDLE hStdout;

	// Console info
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	// Initial cursor position
	COORD coordScreen = { 0, 0 };

	
	DWORD cCharsWritten;
	DWORD dwConSize;

	// =========================

	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	// Verifies if no errors getting the handle
	if(hStdout == INVALID_HANDLE_VALUE)
		return;

	// Gets console size
	if(!GetConsoleScreenBufferInfo(hStdout, &csbi))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill console with white spaces
	if(!FillConsoleOutputCharacter(hStdout, (TCHAR) ' ', dwConSize, coordScreen, &cCharsWritten))
		return;

	// Fill console with the current attributes
	if(!FillConsoleOutputAttribute(hStdout, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten))
		return;

	// Gets console size
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Resets cursor position
	SetConsoleCursorPosition( hStdout, coordScreen );

}

/* ==========================================
    +++++++++++ Get Key Code +++++++++++++     
   ==========================================
|												
|
|   Purposes: Prints key code for each pressed key.
|			  Finishes when UP ARROW key is pressed.
|
|   Parameters: None. 
|
|   Returns: Nothing. 
|
|=============================================
*/
void getKeyCode() {

	int key;

	do {

		cout << "press key" << endl;

		key = _getch();

		cout << key << endl;

	} while( key != skey_code.KEY_UP);

}

/* ==========================================
    +++++++++++ TIME CONVERTER +++++++++++++     
   ==========================================
|												
|
|   Purposes: Convert the time to seconds and
|			  and minutes.
|
|   Parameters: None. 
|
|   Returns: 0 if everything is done without
|   errors. 
|
|=============================================
*/
int convertTime(const double origTime)
{

	if(origTime < 60)
	{
		sfinal_time.minutes = 0;
		sfinal_time.seconds = (int) origTime;
	} else {
		sfinal_time.minutes = (int) origTime / 60;
		sfinal_time.seconds = (int) origTime - (sfinal_time.minutes * 60);
	}

	return 0;
}

/* ==========================================
    +++++++++++ CURSOR INFO +++++++++++++     
   ==========================================
|												
|
|   Purposes: Sets cursor to invisible.
|
|   Parameters: None. 
|
|   Returns: Nothing.
|
|=============================================
*/
void removeCursor()
{
	// Variables
	CONSOLE_CURSOR_INFO cursorInfo; // Cursor info struct
	HANDLE cursorOut = GetStdHandle(STD_OUTPUT_HANDLE); //Handle for the cursor

	// New cursor info
	cursorInfo.bVisible = false; // invisible
	cursorInfo.dwSize = 1; 

	// Sets cursor attributes
    SetConsoleCursorInfo(cursorOut,&cursorInfo);
}

/* ==========================================
    ++++++++ Change Sound State +++++++++++++     
   ==========================================
|												
|
|   Purposes: Turns ingame sound on/off.
|
|   Parameters: None. 
|
|   Returns: True if on, false if off.
|
|=============================================
*/
bool changeSoundState()
{
	if(soundState)
		return false;
	else return true;
}

/* ==========================================
       +++++++++++ LAUNCH COUNTER +++++++++++     
   ==========================================
|												
|
|   Purposes: allows the player to choose
|		      when to start playing. Also
|			  displays a loading bar as an
|			  extra.
|			  
|   Parameters: None. 
|
|   Returns: nothing.
|
|=============================================
*/

void launchCounter()
{
	clearScreen();

	cout << endl << endl << endl << endl;
	cout << "        [ ";

	for (int i=3; i>0; i--)
	{
		cout << i << " -- > ";
		playSound();
		Sleep(1000);
	}

	cout << "]" << endl << endl;

	if(soundState)
	{
		Beep(2200, 800);
	}

}

/* ==========================================
       +++++++++++ WAIT FOR KEY +++++++++++     
   ==========================================
|												
|
|   Purposes: Avoid the use of system("pause").
|			  
|   Parameters: None. 
|
|   Returns: nothing.
|
|=============================================
*/

void waitForKey()
{
	if (langSelected == slang.EN) cout << "Press any key...";
	else if (langSelected == slang.PT) cout << "Pressione uma tecla qualquer...";
	_getch();
}

// =========================================
// =========================================



// ========================================


// ======================================================
// ============= MAIN FUNCTIONS OF THE GAME =============
// ======================================================


/* ==========================================
   +++++++++++ initPuzzle +++++++++++     
   ==========================================
|												
|
|   Purposes: Creates initial solved puzzle.
|
|   Parameters: Puzzle vector by reference.  
|
|   Returns: 0 if no errors.
|
|=============================================
*/
int initPuzzle(vector <vector <int>> &puzzle)
{
	// Loops throuhg vector and sets initial values for each position
	for(unsigned int line = 0; line < puzzle.size(); line++)
		for(unsigned int col = 0; col < puzzle.size(); col++)
			puzzle[line][col] = puzzle.size() * line + (col + 1);
	puzzle[puzzle.size() - 1][puzzle.size() - 1] = 0;

	// Sets initial zero position (Data Structure)
	szero.line = puzzle.size() - 1;
	szero.col = puzzle.size() - 1;
			 
	return 0;
}

/* ==========================================
   +++++++++++++ shufflePuzzle ++++++++++++++     
   ==========================================
|												
|
|   Purposes: Moves tiles randomly to create
|			  a new puzzle.
|
|   Parameters: Puzzle vector by reference. 
|
|   Returns: 0 if no errors. 
|
|=============================================
*/
int shufflePuzzle(vector <vector <int>> &puzzle)
{

	srand((unsigned int) time(NULL));
	 
	int shuffle_num = rand() % 500 + 500;
	//int shuffle_num = rand() % 4 + 1; // DEBUG MODE

	int shuffle_dir;

	// Shuffle directions:
	const int UP = 0;
	const int RIGHT = 1;
	const int DOWN = 2;
	const int LEFT = 3;

	while (shuffle_num > 0) 
	{

		// Backup old zero position
		szero.temp_line = szero.line;
		szero.temp_col = szero.col;

		shuffle_dir = rand() % 4; // Chooses direction to shuffle

		switch(shuffle_dir) {
		case UP: 
			if(szero.line == 0)
			{
				shuffle_num ++ ;
				break;
			}
			szero.line--;
			break;
		case RIGHT:
			if(szero.col == (puzzle.size() - 1))
			{
				shuffle_num ++ ;
				break;
			}
			szero.col++;
			break;
		case DOWN:
			if(szero.line == (puzzle.size() - 1))
			{
				shuffle_num ++ ;
				break;
			}
			szero.line++;
			break;
		case LEFT:
			if(szero.col == 0)
			{
				shuffle_num ++ ;
				break;
			}
			szero.col--;
			break;
		default:
			shuffle_num++;
			break;
		}

		// Switch tiles
		puzzle[szero.temp_line][szero.temp_col] = puzzle[szero.line][szero.col];
		puzzle[szero.line][szero.col] = 0;

		shuffle_num--;
	}


	return 0;

}

/* ==========================================
   +++++++++++++ Copy puzzle ++++++++++++++     
   ==========================================
|												
|
|   Purposes: Makes a backup of the original
|			  puzzle to another vector.
|
|   Parameters: Puzzle vector by reference.
|				Backup Puzzle vector by ref.
|
|   Returns: 0 if no errors. 
|
|=============================================
*/
int copyPuzzle(vector <vector <int>> &puzzle, vector <vector <int>> &backupPuzzle) {

	// Loops throuhg vector and copies values to another vector.
	for(unsigned int line = 0; line < puzzle.size(); line++)
		for(unsigned int col = 0; col < puzzle.size(); col++)
			backupPuzzle[line][col] = puzzle[line][col];

	szero.backup_line = szero.line;
	szero.backup_col = szero.col;

	return 0;
}

/* ==========================================
   +++++++++++++ Recopy puzzle ++++++++++++++     
   ==========================================
|												
|
|   Purposes: Moves puzzle from backup vector
|			  to game puzzle vector.
|
|   Parameters: Puzzle vector by reference.
|				Backup Puzzle vector by ref.
|
|   Returns: 0 if no errors. 
|
|=============================================
*/
int recopyPuzzle(vector <vector <int>> &backupPuzzle, vector <vector <int>> &puzzle) {
	// Loops throuhg vector and copies values to another vector.
	for(unsigned int line = 0; line < puzzle.size(); line++)
		for(unsigned int col = 0; col < puzzle.size(); col++)
			puzzle[line][col] = backupPuzzle[line][col];

	szero.line = szero.backup_line;
	szero.col = szero.backup_col;

	return 0;
}

/* ==========================================
   +++++++++++ ShowPuzzle +++++++++++     
   ==========================================
|												
|
|   Purposes: Prints puzzle to screen.
|
|   Parameters: Puzzle vector by reference.  
|
|   Returns: 0 if no errors. 1 if invalid size. 
|
|=============================================
*/
int showPuzzle(const vector <vector <int>> &puzzle) 
{

	cout << endl << endl;


	// ++++++ TITLE +++++++
	
	if(langSelected == slang.EN)
	{
		cout <<  " =======================================\n";
		cout <<  " +++++++++++++ PUZZLE GAME +++++++++++++\n";
		cout <<  " =======================================\n\n";
	}
	else if(langSelected == slang.PT)
	{
		cout <<  " =======================================\n";
		cout <<  " ++++++++++++ JOGO DO PUZZLE +++++++++++\n";
		cout <<  " =======================================\n\n";
	}

	// ++++++++++++++++++++

	// Verifies if puzzle size is > 0
	if(puzzle.size() == 0)
		return 1;

	// Prints puzzle
	for(unsigned int line = 0; line < puzzle.size(); line++)
	{
		for(unsigned int col = 0; col < puzzle.size(); col++)
			if (puzzle[line][col]==0) cout << setw(8) << " ";
			else cout << setw(8) << puzzle[line][col] ;
		cout << endl << endl;
	}

	// Prints instructions
	if(langSelected == slang.EN)
	{
		cout << "\n\n\n\n   [arrow keys]    play.\n";
		cout << "\n   ['q' or 'Q']    quit.\n";
	}
	else if(langSelected == slang.EN)
	{
		cout << "\n\n\n\n      [setas]   jogar.\n";
		cout << "\n ['q' ou 'Q']    sair.\n";
	}

	return 0;

}

/* ==========================================
   +++++++++++ Play Sounds +++++++++++     
   ==========================================
|												
|
|   Purposes: Makes a verification and plays
|			  a sound.
|
|   Parameters: None.  
|
|   Returns: Nothing. 
|
|=============================================
*/
void playSound(){
	if(soundState)
		Beep(1110,100);
}
void playSoundFinal(){
	if(soundState)
	{
		Sleep(500);
		Beep(880,200);
		Beep(1110,200);
		Beep(1320,200);
		Beep(1760,200);
		Sleep(200);
		Beep(1320,200);
		Beep(1760,800);
	}
}

/* ==========================================
   +++++++++++++ Play Again? +++++++++++++     
   ==========================================
|												
|
|   Purposes: Asks player if he wants to restart
|			  the puzzle.
|
|   Parameters: None.  
|
|   Returns: True if yes. False if no. 
|
|=============================================
*/
bool playAgain()
{

	int key; 
	bool itemSelected = true;
	bool done = false;


	do {
	clearScreen();

	if(langSelected==slang.EN)
	{
		cout << "\n\n\n\n            Restart?";
		cout << "\n\n\n            [YES]    [NO]" << endl;
	}
	else if(langSelected==slang.PT)
	{
		cout << "\n\n\n\n            Recomecar?";
		cout << "\n\n\n            [SIM]   [NAO]" << endl;
	}
	if(itemSelected)
		cout << "              ^" << endl;
	else
		cout << "                      ^" << endl;

	key = _getch();
	// If arrow key is pressed discard first value.
	if(key == skey_code.KEY_ARROW)
		key = _getch();
	// Go back.
	if(key == skey_code.KEY_q || key == skey_code.KEY_Q)
		return 0;

	// Handles arrow keys.
	switch(key) {
	case skey_code.KEY_RIGHT:
		if(itemSelected)
			itemSelected = false;
		break;
	case skey_code.KEY_LEFT:
		if(!itemSelected)
			itemSelected = true;
		break;
	default:
		done = false;
	}

	if(key == skey_code.KEY_ENTER)
		done = true;

	} while(!done);

	return itemSelected;
}

/* ==========================================
   +++++++++++ Move Arrows +++++++++++     
   ==========================================
|												
|
|   Purposes: Handles gameplay with the arrows.
|
|   Parameters: Puzzle vector by reference.  
|
|   Returns: 0 if no errors. 
|
|=============================================
*/
int moveArrows(vector <vector<int>> &puzzle) 
{
	bool done = false; // Waits for arrow to be pressed.

	int key; // Stores pressed key code.

	do
	{

		key = _getch();

		// Checks if first keycode is to be discarted or not. 
		if(key == skey_code.KEY_ARROW)
			key = _getch();

		// If 'q' or 'Q' is pressed goes back to main menu.
		if(key == skey_code.KEY_q || key == skey_code.KEY_Q)
			mainMenu();


		switch(key) {
		case skey_code.KEY_UP:
			if((unsigned) szero.line < puzzle.size() - 1) {
				playSound();
				puzzle[szero.line][szero.col] = puzzle[szero.line + 1][szero.col];
				puzzle[szero.line + 1][szero.col] = 0;
				szero.line++;
				done = true;
			}
			break;
		case skey_code.KEY_RIGHT:
			if((unsigned) szero.col > 0) {
				playSound();
				puzzle[szero.line][szero.col] = puzzle[szero.line][szero.col - 1];
				puzzle[szero.line][szero.col - 1] = 0;
				szero.col--;
				done = true;
			}
			break;
		case skey_code.KEY_DOWN:
			if((unsigned) szero.line > 0) {
				playSound();
				puzzle[szero.line][szero.col] = puzzle[szero.line - 1][szero.col];
				puzzle[szero.line - 1][szero.col] = 0;
				szero.line--;
				done = true;
			}
			break;
		case skey_code.KEY_LEFT:
			if((unsigned) szero.col < puzzle.size() - 1) {
				playSound();
				puzzle[szero.line][szero.col] = puzzle[szero.line][szero.col + 1];
				puzzle[szero.line][szero.col + 1] = 0;
				szero.col++;
				done = true;
			}
			break;
		default:
			done = false; // No valid key has been pressed. Repeats cycle. 
		}

	} while(!done);


	return 0;
}

/* ==========================================
   +++++++++++ Verification +++++++++++     
   ==========================================
|												
|
|   Purposes: Verifies if puzzle is solved or not.
|
|   Parameters: Puzzle vector by reference. 
|
|   Returns: True if solved. False if not. 
|
|=============================================
*/
bool verification(const vector <vector<int>> &puzzle)
{

	int value = 1; // Value to check. 

	// Loops through puzzle vector
	for(unsigned int line=0; line < puzzle.size(); line++)
	{
		for(unsigned int col=0; col < puzzle.size(); col++)
		{
			if(puzzle[line][col] != value)
			{
				if(line == puzzle.size() - 1 && col == puzzle.size() - 1 && puzzle[line][col] == 0)
					return true;

				return false;
			}

			value++;
		}
	}

	return false;

}

/* ==========================================
    +++++++++++++ END SCREEN ++++++++++++++     
   ==========================================
|												
|
|   Purposes: Displays an end screen each time
|	a user successfully ends a game, no matter
|	the game mode (comp/training).
|
|   Parameters: None. 
|
|   Returns: 0 if everything is done without
|   errors. 
|
|=============================================
*/
int gameOverScreen()
{
	clearScreen();

	if (langSelected == slang.EN)
	{
		cout << "\n\n  =========================================="
			   << "\n  +++++++++++++++ FINISHED! ++++++++++++++++"
			   << "\n  ==========================================";

		cout << "\n\n\n\n You finished the puzzle in: "
			<< sfinal_time.minutes << " minute(s) and " << sfinal_time.seconds << " second(s)!\n\n\n\n";
	}
	else if (langSelected == slang.PT)
	{
		cout << "\n\n  =========================================="
			 <<   "\n  ++++++++++++++++ GANHOU! +++++++++++++++++"
			   << "\n  ==========================================";

		cout << "\n\n\n\n Acabou o puzzle em: "
			 << sfinal_time.minutes << " minuto(s) e " << sfinal_time.seconds << " segundo(s)!\n\n\n\n";
	} 

	waitForKey();

	return 0;

}

/* ==========================================
    +++++++++++++ Old Puzzle Init ++++++++++++++     
   ==========================================
|												
|
|   Purposes: Handles puzzle vector and calls
|			  load puzzle function.
|
|   Parameters: Puzzle.
|
|   Returns: Puzzle count.
|
|=============================================
*/
int initOldPuzzle(vector <vector <int>> &puzzle) {
	return load_puzzle(puzzle.size(), puzzle);
}

/* ==========================================
   ++++++++++++++ Start Game ++++++++++++++     
   ==========================================
|												
|
|   Purposes: The core game function. Initiates
|	the time count, calls the functions to
|	play the game and verifies if the player
|	has won.
|
|   Parameters: Puzzle vector by reference.
|
|   Returns: Final time.
|
|=============================================
*/
double startGame(vector <vector<int>> &puzzle)
{

	// Time variables
	time_t initialTime, finalTime;

	//Starts timer
	initialTime = time(0);


	// Main thread
	while(true)
	{

		clearScreen();

		showPuzzle(puzzle); // Prints puzzle
	
		moveArrows(puzzle); // Next Move?

		// Verifies if puzzle has been solved.
		if(verification(puzzle))
		{
			clearScreen();
			showPuzzle(puzzle);
			break;
		}

	}

	// Ends timer. 
	finalTime = time(0);

	return (double) (finalTime - initialTime);

}

// ===========================================
// ===========================================


// ===========================================================
// ==============  TEXT FILES HANDLING FUNCTIONS =============
// ===========================================================

/* ==========================================
   ++++++  Create Puzzle Number File  +++++++    
   ==========================================
|												
|
|   Purposes: Creates text file with the number
|			  of each type of puzzle that exists.
|
|   Parameters: None.
|
|   Returns: 0 if no errors. 
|
|=============================================
*/
int createPuzzleNumber()
{
	// Open text file in input mode
	ifstream numberFileCheck("puzzle_numbers.txt");

	// Checks if file is creates, if not, creates it.
	if(!numberFileCheck) {
		// Creates text file.
		ofstream numberFileInit("puzzle_numbers.txt");

		// Writes default values to text file.
		numberFileInit << "3x3 0" << endl;
		numberFileInit << "4x4 0" << endl;
		numberFileInit << "5x5 0" << endl;
		numberFileInit.close();
	}

	// Close text file
	numberFileCheck.close();

	return 0;
}

/* ==========================================
   +++++++++++ backupNumberLine  ++++++++++++     
   ==========================================
|												
|
|   Purposes: Gives each puzzle type count value
|		to the parameters.
|
|   Parameters: int size 3x3, size 4x4, 
|		size 5x5, by reference
|
|   Returns: 0 if no errors. 
|
|=============================================
*/
int backupNumberLine(int &size3, int &size4, int &size5) {

	// Variables
	
	string line1, line2, line3;
	string numberOfPuzzles;

	// opens text file in input mode. 
	ifstream file_puzzle_numbers("puzzle_numbers.txt");

	// Verifies if text file exists.
	if(!file_puzzle_numbers)
		return 6;

	// Gets all puzzle count lines
	getline(file_puzzle_numbers, line1);
	getline(file_puzzle_numbers, line2);
	getline(file_puzzle_numbers, line3);

	// Truncates the strings to keep only the puzzle count and converts it to integer.
	size3 = stoi(line1.substr(4, (line1.find("\n") - 4)));
	size4 = stoi(line2.substr(4, (line2.find("\n") - 4)));
	size5 = stoi(line3.substr(4, (line3.find("\n") - 4)));

	// Close file
	file_puzzle_numbers.close();

	return 0;

}

/* ==========================================
   +++++++++++ searchPuzzleNumber +++++++++++     
   ==========================================
|												
|
|   Purposes: Returns the numbers of puzzles 
|	of a determined size that exists.
|
|   Parameters: constant int puzzle_size.  
|
|   Returns: the number of puzzles of the
|	choosed size that are actually saved. 
|
|=============================================
*/
int searchPuzzleNumber(const int &puzzle_size)
{

	// Variables
	string line1, line2, line3;
	string numberOfPuzzles;

	int size3, size4, size5, finalNumber;

	backupNumberLine(size3, size4, size5); //Gets puzzle count of each puzzle size.

	// chooses the correct line
	switch (puzzle_size) {
	case 3:
		// Converts string to integer
		finalNumber = size3;
		break;
	case 4:
		// Converts string to integer
		finalNumber = size4;
		break;
	case 5:
		// Converts string to integer
		finalNumber = size5;
		break;
	}

	return finalNumber;
}

/* ==========================================
   ++++++++++ incrementPuzzleNumber +++++++++    
   ==========================================
|												
|
|   Purposes: Increments the number of certain
|		puzzle, and writes to the file.
|
|   Parameters: constant int puzzle_size.  
|
|   Returns: 0 if no errors. 
|
|=============================================
*/
int incrementPuzzleNumber(const int puzzle_size) {

	int size3, size4, size5;

	backupNumberLine(size3, size4, size5);

	// Verifies which puzzle size to increment.
	switch(puzzle_size) {
	case 3:
		size3++;
		break;
	case 4:
		size4++;
		break;
	case 5:
		size5++;
		break;
	default:
		return 4;
	}

	// Deletes old text file.
	remove("puzzle_numbers.txt");

	// Creates new text file.
	fstream numberFile("puzzle_numbers.txt"); 

	// Opens text file in output mode.
	numberFile.open("puzzle_numbers.txt", ios::out); 

	// Writes new values to text file.
	numberFile << "3x3 " << size3 << endl;
	numberFile << "4x4 " << size4 << endl;
	numberFile << "5x5 " << size5 << endl;

	numberFile.close();

	return 0;
}

/* ==========================================
   +++++++++++++ Write Top Score ++++++++++++    
   ==========================================
|												
|
|   Purposes: If player beated a record, then 
|			  asks for name and age and writes
|			  information to text file.
|
|   Parameters: Saved Scores:
|					array times;
|					array ages;
|					array names;
|				New Score:
|					line;
|					time;
|					type;
|
|   Returns: itemSelected. 
|
|=============================================
*/
bool writeTopScore(double times[], int ages[], char gender[], string names[], const int &line,const double &time, const int &type)
{
	// Variables
	bool itemSelected = true;
	short int key;
	short int pos = 0;
	bool done = false;
	short int age = 10;
	string name = "AAA"; // Default name string.
	char gend = 'M';

	static const int TOP_SCORE = 1;
	

	do
	{
		clearScreen();
		if (langSelected == slang.EN)
		{
			cout << "Congratulations!" << endl;
			cout << "You scored a record! Do you wish to save it?" << endl << endl;
		}
		else if (langSelected == slang.PT)
		{
			cout << "Parabens!" << endl;
			cout << "Novo recorde! Deseja gravar?" << endl << endl;
		}

		if(itemSelected)
		{
			if (langSelected == slang.EN)
			{
				cout << "YES [X]" << endl;
				cout << "NO  [ ]" << endl;
			}
			else if (langSelected == slang.PT)
			{
				cout << "SIM [X]" << endl;
				cout << "NAO [ ]" << endl;
			}
		}
		else
		{
			if (langSelected == slang.EN)
			{
				cout << "YES [ ]" << endl;
				cout << "NO  [X]" << endl;
			}
			else if (langSelected == slang.PT)
			{
				cout << "SIM [ ]" << endl;
				cout << "NAO [X]" << endl;
			}
		}

		key = _getch();
		// If one of the arrow keys has been pressed.
		if(key == skey_code.KEY_ARROW)
			key = _getch();

		switch(key)
		{
		case skey_code.KEY_UP:
			if(!itemSelected)
				itemSelected = true;
			break;
		case skey_code.KEY_DOWN:
			if(itemSelected)
				itemSelected = false;
			break;
		case skey_code.KEY_ENTER:
			done = true;
			break;
		}
	} while(!done);
	
	
	if(itemSelected)
	{
		done = false;

		do
		{
			clearScreen();
			if (langSelected == slang.EN)
			{
				cout << "+----------------+" << endl;
				cout << "| Save Top Score |" << endl;
				cout << "+----------------+" << endl << endl;
				cout << "[arrow keys]:  Change" << endl;
				cout << "     [enter]:  Next / Finish" << endl << endl ;
			}
			else if (langSelected == slang.PT)
			{
				cout << "+----------------+" << endl;
				cout << "| Gravar Recorde |" << endl;
				cout << "+----------------+" << endl << endl;
				cout << "     [setas]:  Escolher" << endl;
				cout << "     [enter]:  Prox. / Terminar" << endl << endl ;
			}
			// Asks for name.
			if(pos < 3)
			{
				if (langSelected == slang.EN) cout << endl << "Name:  " << name << endl;
				else if (langSelected == slang.PT) cout << endl << "Nome:  " << name << endl;
				cout << setw(8);
				for(int i=8;i<8+pos;i++) cout << "-";
				cout << "^";
				for(int i=8+pos;i<10;i++) cout << "-";
				cout << endl;
			}
			// Asks for age.
			else if (pos == 3)
			{
				if (langSelected == slang.EN) cout <<endl <<      "Age:   " << age << endl;
				else if (langSelected == slang.PT) cout <<endl << "Idade: " << age << endl;
				cout << setw(9) << "--" << endl;
			}
			else
			{
				if (langSelected == slang.EN) cout <<endl << "Gender: " << gend << endl;
				else if (langSelected == slang.PT) cout <<endl << "Sexo:   " << gend << endl;
				cout << setw(9) << "-" << endl;
			}

			key = _getch();
			// If one of the arrow keys has been pressed.
			if(key == skey_code.KEY_ARROW)
				key = _getch();

			// Handles arrow keys.
			switch(key)
			{
			case skey_code.KEY_RIGHT:
				if(pos < 2)
				{
					pos++;
				}
				break;
			case skey_code.KEY_LEFT:
				if(pos > 0)
				{
					pos--;
				}
				break;
			case skey_code.KEY_UP:
				if(pos > 2)
				{
					if(pos == 3)
					{
						if(age < 99) age++;
						else age = 1;
					}
					else
					{
						if (gend == 'M')
							gend = 'F';
						else gend = 'M';
					}
				}
				else if(name[pos] < 'Z')
				{
					name[pos]++;
				}
				else name[pos] = 'A';
				break;
			case skey_code.KEY_DOWN:
				if(pos > 2)
				{
					if(pos == 3)
					{
						if(age > 1) age--;
						else age = 99;
					}
					else
					{
						if (gend == 'M')
							gend = 'F';
						else gend = 'M';
					}
				}
				else if(name[pos] > 'A')
				{
					name[pos]--;
				}
				else name[pos] = 'Z';
				break;
			case skey_code.KEY_ENTER:
				if(pos < 3)
				{
					pos = 3;
				}
				else if(pos==3)
				{
					pos = 4;
				}
				else 
					done = true;
				break;
			}
		} while(!done);

		// If the player beated any of the old records. 
		if(type == TOP_SCORE)
		{
			// Releases rank position for new record.
			for(int rank=9; rank > line; rank--)
			{
				names[rank] = names[rank-1];
				gender[rank] = gender[rank-1];
				ages[rank] = ages[rank-1];
				times[rank] = times[rank-1];
			}
		}

		// Writes new record.
		names[line] = name;
		gender[line] = gend;
		ages[line] = age;
		times[line] = time;

		return itemSelected;
	}

	else return itemSelected;
	
	return 0;
}

/* ==========================================
   +++++++++++++++ savePuzzle +++++++++++++++     
   ==========================================
|												
|
|   Purposes: Saves puzzle to file and calls
|		another function to increment puzzle
|		count.
|
|   Parameters: puzzle vector, 
|		constant int puzzle_size.  
|
|   Returns: 0 if no errors. 
|
|=============================================
*/
int savePuzzle(vector <vector<int>> &puzzle, const int puzzle_size)
{
	// Variables
	int num = searchPuzzleNumber(puzzle_size) + 1;
	
	// Text file title string.
	ostringstream oss;
	string records_title;

	// Creates text file title string.
	if (num < 10) {
		oss << "puzzle_" << puzzle_size << "x" << puzzle_size << "_00" << num << ".txt";
		records_title = oss.str();
	} else if ((num >= 10) && (num < 100)) {
		oss << "puzzle_" << puzzle_size << "x" << puzzle_size << "_0" << num << ".txt";
		records_title = oss.str();
	} else {
		oss << "puzzle_" << puzzle_size << "x" << puzzle_size << "_" << num << ".txt";
		records_title = oss.str();
	}

	// Creates text file.
	fstream records(records_title); 

	// Opens text file in output mode.
	records.open(records_title, ios::out); 


	// Verifies if the file has been opened.
	if(!records.is_open()) 
	{
		if(langSelected == slang.EN)
			cerr << "Can't open file " << records_title << endl;
		if(langSelected == slang.PT)
			cerr << "Impossivel abrir o ficheiro " << records_title << endl;
		waitForKey();
		return 2;
	}


	// Save puzzle to text file
	for(unsigned int line = 0; line < puzzle.size(); line++)
	{
		for(unsigned int col = 0; col < puzzle.size(); col++)
			records << setw(6) << puzzle[line][col] ;
		records << endl << endl;
	}

	// Writes default score to text file.
	for(unsigned int line = 0; line < 10; line++) records << "Empty  0   0     0\n";


	records.close(); 

	// Add one puzzle to puzzle count text file.
	incrementPuzzleNumber(puzzle_size);

	return 0;

}

/* ==========================================
   +++++++++++++ Save to Array ++++++++++++++     
   ==========================================
|												
|
|   Purposes: Writes loaded puzzle to vector.
|
|   Parameters: puzzle vector, 
|		constant int reference.  
|
|   Returns: 0 if no errors. 
|
|=============================================
*/
int save2Array(vector <vector<int>> &puzzle, const int &ref) {

	// Variables
	string valueTemp;
	int valueTempInt;

	// Text file title string.
	ostringstream oss;
	string puzzle_title;

	// Creates text file title string.
	if (ref < 10) {
		oss << "puzzle_" << puzzle.size() << "x" << puzzle.size() << "_00" << ref << ".txt";
		puzzle_title = oss.str();
	} else if ((ref >= 10) && (ref < 100)) {
		oss << "puzzle_" << puzzle.size() << "x" << puzzle.size() << "_0" << ref << ".txt";
		puzzle_title = oss.str();
	} else {
		oss << "puzzle_" << puzzle.size() << "x" << puzzle.size() << "_" << ref << ".txt";
		puzzle_title = oss.str();
	}

	// Opens text file in input mode.
	ifstream puzzleFile(puzzle_title); 
	
	// Verifies if text file exists.
	if(!puzzleFile)
		return 2;

	// Loops through text file and writes puzzle to vector. 
	for(unsigned int line = 0; line < puzzle.size(); line++)
		for(unsigned int col = 0; col < puzzle.size(); col++) 
		{
			puzzleFile >> valueTemp;
			valueTempInt = stoi(valueTemp);

			// sets zero position
			if(valueTempInt == 0) {
				szero.line = line;
				szero.col = col;
			}

			puzzle[line][col] = valueTempInt;
		}


	puzzleFile.close();

	return 0;
}

/* ==========================================
   +++++++++++++ Save Score ++++++++++++++     
   ==========================================
|												
|
|   Purposes: Checks if it's a top score. 
|			  Writes score to text file.
|
|   Parameters: constant int puzzle size. 
|				constant int reference.  
|				constant int time.
|
|   Returns: 0 if no errors. 
|
|=============================================
*/
int saveScore(const int &puzzle_size, const double &time, const int &ref) {

	// Variables
	string initialValue;
	string valueTemp;
	string names[10];
	int ages[10];
	char gender[10];
	double times[10];
	int tiles[26];
	int pos = 0;
	bool itemSelected = false;
	static const int NEW_SCORE = 0;
	static const int TOP_SCORE = 1;

	// Creates text file title string.
	ostringstream oss;
	string puzzle_title;

	if (ref < 10) {
		oss << "puzzle_" << puzzle_size << "x" << puzzle_size << "_00" << ref << ".txt";
		puzzle_title = oss.str();
	} else if ((ref >= 10) && (ref < 100)) {
		oss << "puzzle_" << puzzle_size << "x" << puzzle_size << "_0" << ref << ".txt";
		puzzle_title = oss.str();
	} else {
		oss << "puzzle_" << puzzle_size << "x" << puzzle_size << "_" << ref << ".txt";
		puzzle_title = oss.str();
	}

	// Opens text file.
	fstream puzzleFile(puzzle_title); 
	
	// Verifies if puzzle has been opened.
	if(!puzzleFile) {
		if(langSelected == slang.EN)
			cerr << "File not found!" << endl;
		if(langSelected == slang.PT)
			cerr << "Ficheiro nao encontrado!" << endl;
		waitForKey();
		return 2;
	}

	// Backup everything from opened file to arrays.
	for(int line = 0; line < (puzzle_size * puzzle_size); line++)
	{
		// Backup puzzle.
		puzzleFile >> tiles[line];
	}
	for(int line = 0; line < 10; line++)
	{
		// Backup scores.
		puzzleFile >> names[line];
		puzzleFile >> gender[line];
		puzzleFile >> times[line];
		puzzleFile >> ages[line];
	}

	puzzleFile.close();

	// Checks if score is a top score.
	for(int line = 0; line < 10; line++)
	{
		if(names[line] == "Empty")
		{
			itemSelected = writeTopScore(times,ages,gender,names,line,time,NEW_SCORE);
			line=10;
		}
		else if (time <= times[line])
		{
			itemSelected = writeTopScore(times,ages,gender,names,line,time,TOP_SCORE);
			line=10;
		}
	}

	
	// If user wants to save top score.
	if(itemSelected)
	{
		// Removes old puzzle file.
		remove(puzzle_title.c_str());

		// Creates and opens text file in output mode.
		puzzleFile.open(puzzle_title, ios::out);

		// Verifies if text file has successfully been created.
		if(!puzzleFile.is_open()) 
		{
			cerr << "Can't create text file. " << puzzle_title << endl; 
			return 2;
		}

		// Save puzzle and scores to text file.
		pos = 0;	

		for(int line = 0; line < puzzle_size; line++)
		{
			for(int col = 0; col < puzzle_size; col++)
			{
				puzzleFile << setw(6) << tiles[pos];
				pos++;
			}
			puzzleFile << endl << endl;
		}
		for(int line = 0; line < 10; line++)
			puzzleFile << setw(5) << names[line] << setw(3) << gender[line] << setw(4) << ages[line] <<  setw(6) << times[line] << endl;


		puzzleFile.close();
	}

	return 0;
}

/* ==========================================
   ++++++++++ Show saved puzzle +++++++++++++  
   ==========================================
|												
|
|   Purposes: Prints to screen loaded puzzle
|			  and respective scores.
|
|   Parameters: constant int puzzle size. 
|				constant int count  
|		
|   Returns: 0 if no errors. 
|
|=============================================
*/
int showSavedPuzzle(const int &puzzle_size, const int &puzzle_count) {

	// Variables
	string lineToGet;
	int number;
	
	// Text file string
	ostringstream oss;
	string puzzle_title;
	
	// Verifies if any puzzle of the choosen size is actually saved.
	if(puzzle_count == 0) {
		if(langSelected == slang.EN)
			cout << "No available puzzles..." << endl << endl;
		else 
			cout << "Nao existem puzzles..." << endl << endl;
		waitForKey();
		return 5;
	}
	
	// Creates text file title string.
	if (puzzle_count < 10) {
		oss << "puzzle_" << puzzle_size << "x" << puzzle_size << "_00" << puzzle_count << ".txt";
		puzzle_title = oss.str();
	} else if ((puzzle_count >= 10) && (puzzle_count < 100)) {
		oss << "puzzle_" << puzzle_size << "x" << puzzle_size << "_0" << puzzle_count << ".txt";
		puzzle_title = oss.str();
	} else {
		oss << "puzzle_" << puzzle_size << "x" << puzzle_size << "_" << puzzle_count << ".txt";
		puzzle_title = oss.str();
	}

	// Opens text file.
	ifstream puzzleFile(puzzle_title);

	// Verifies if text file has been opened.
	if(!puzzleFile) {
		cerr << "Can't open text file!" << endl;
		waitForKey();
		return 2;
	}

	// Prints Puzzle
	cout << "Puzzle: "<< puzzle_count << endl;	
	for (int line = 1; line <= puzzle_size; line++)
	{
		for (int col = 1; col <= puzzle_size; col++)
		{
			puzzleFile >> number;

			// If tile is zero...
			if(number == 0)
				cout << setw(6) << " ";
			else
				cout << setw(6) << number;
		}
		cout << endl << endl;

		getline(puzzleFile, lineToGet); 
	}

	// Prints Scores
	if (langSelected == slang.EN) cout << "Scores:" << endl << endl;
	else if (langSelected == slang.PT) cout << "Recordes:" << endl << endl;

	// Loops through scores
	for(int i = 1; i <= 10; i++)
	{
		puzzleFile >> lineToGet;

		if (lineToGet != "Empty")
		{
			if (langSelected == slang.EN)
			{
				cout << "  NAME: " << setw(6) << lineToGet;
				puzzleFile >> lineToGet;
				cout << "  GENDER: " << setw(2) << lineToGet;
				puzzleFile >> lineToGet;
				cout << "  AGE: " << setw(2) << lineToGet;
				puzzleFile >> lineToGet;
				cout << "  TIME: " << setw(4) << lineToGet << "sec" << endl;
			}
			else if (langSelected == slang.PT)
			{
				cout << "  NOME: " << setw(6) << lineToGet;
				puzzleFile >> lineToGet;
				cout << "  SEXO: " << setw(4) << lineToGet;
				puzzleFile >> lineToGet;
				cout << "  IDADE: " << setw(2) << lineToGet;
				puzzleFile >> lineToGet;
				cout << "  TEMPO: " << setw(4) << lineToGet << "seg" << endl;
			}
		}
		else
		{
			puzzleFile >> lineToGet;
			puzzleFile >> lineToGet;
			puzzleFile >> lineToGet;
		}
	}

	puzzleFile.close();

	return 0;

}

// ==========================================
// ==========================================



// ==========================================
// ======== OTHER GAME FUNCTIONS ============
// ==========================================


/* ==========================================
    ++++++++++++ OLD PUZZLE MENU +++++++++++     
   ==========================================
|												
|
|   Purposes: Allows the user to browse old 
|	saved games and play them again.
|
|   Parameters: None. 
|
|   Returns: 0 if everything is done without
|   errors. 
|
|=============================================
*/
int load_puzzle(const int puzzle_size, vector <vector<int>> &puzzle)
{

	int key;
	int puzzle_count = searchPuzzleNumber(puzzle_size);

	bool done = false;

	do {

		clearScreen();

		if(showSavedPuzzle(puzzle_size, puzzle_count) == 5)
		{
			if (langSelected == slang.EN) cerr << "No puzzle of this size saved.";
			else if (langSelected == slang.PT) cerr << "Sem puzzles deste tipo.";
			return -1;
		}
		else
		{
			cout << endl;
			if (langSelected == slang.EN)
			{
				cout << setw(12) << "[Enter]" << setw(6) << "  Play!" << endl;
				cout << setw(12) << "[q or Q]" << setw(6) << "  Return" <<endl;
				cout << setw(12) << "[Arrow Keys]" << setw(6) << "  Navigate" << endl;
			}
			else if (langSelected == slang.PT)
			{
				cout << setw(12) << "[Enter]" << setw(6) << "  Jogar!" << endl;
				cout << setw(12) << "[q or Q]" << setw(6) << "  Voltar ao menu" <<endl;
				cout << setw(12) << "[Setas]" << setw(6) << "  Escolher" << endl;
			}
			key = _getch();
			if(key == skey_code.KEY_ARROW)
				key = _getch();

			switch(key) {
			case skey_code.KEY_DOWN:
				if(puzzle_count > 1)
					puzzle_count--;
				break;
			case skey_code.KEY_UP:
				if(puzzle_count < searchPuzzleNumber(puzzle_size))
					puzzle_count++;
				break;
			case skey_code.KEY_ENTER:
				save2Array(puzzle, puzzle_count);
				return puzzle_count;
				break;
			case skey_code.KEY_Q:
				mainMenu();
				break;
			case skey_code.KEY_q:
				mainMenu();
				break;
			}
		}
	} while(!done);

	return 0;
}

/* ==========================================
    +++++++++++ MAIN GAME THREAD +++++++++++     
   ==========================================
|												
|
|   Purposes: Creates a puzzle to be played
|	and calls all necessary functions to play
|	the game.
|
|   Parameters:
|		constant int type:
|			0 - new competition puzzle
|					-> time:	YES
|					-> saves:	YES
|			1 - old competition puzzle (loads)
|					-> time:	YES
|					-> saves:	YES
|			2 - training puzzle
|					-> time:	YES
|					-> saves:	NO
|
|   Returns: 0 if everything is done without
|   errors. 
|
|=============================================
*/
int gameThread(const short int &type)
{

	// Variables Declaration
	
	double time;

	string puzzle_dimension;

	int puzzle_size;

	int puzzle_count;

	const int NEW = 0, OLD = 1, TRAINING = 2;

	// =====================


	do
	{
		// Display
		clearScreen();

		if(!(type == OLD))
		{
			if (type == NEW)
			{
				if (langSelected == slang.EN)
				{
					cout << setw(30) << "+-------------+" << endl;
					cout << setw(30) << "| Puzzle Size |" << endl;
					cout << setw(30) << "+-------------+" << endl << endl;
					cout << setw(36) << "['q' or 'Q'] Return to menu" << endl << endl;
				}
				else if (langSelected == slang.PT)
				{
					cout << setw(33) << "+-------------------+" << endl;
					cout << setw(33) << "| Tamanho do puzzle |" << endl;
					cout << setw(33) << "+-------------------+" << endl << endl;
					cout << setw(36) << "['q' ou 'Q'] Voltar ao menu" << endl << endl;
				}
			}
			else
			{
				if (langSelected == slang.EN)
				{
					cout << setw(31) << "+---------------+" << endl;
					cout << setw(31) << "| Training Mode |" << endl;
					cout << setw(31) << "+---------------+" << endl << endl;
					cout << setw(36) << "['q' or 'Q'] Return to menu" << endl << endl;
				}
				else if (langSelected == slang.PT)
				{
					cout << setw(31) << "+----------------+" << endl;
					cout << setw(31) << "| Modo de Treino |" << endl;
					cout << setw(31) << "+----------------+" << endl << endl;
					cout << setw(36) << "['q' or 'Q'] Voltar ao menu" << endl << endl;
				}
			}

			if (langSelected == slang.EN)
			{
				cout << "        []====== Puzzle Size ======[]" << endl;
				Sleep(100);
			}
			else if (langSelected == slang.PT)
			{
				cout << "        []=== Tamanho do Puzzle ===[]" << endl;
				Sleep(100);
			}

			cout << "        ||                         ||"<<endl; Sleep(100);
			cout << "        ||    3x3    4x4    5x5    ||"<<endl; Sleep(100);
			cout << "        ||                         ||"<<endl; Sleep(100);
			cout << "        []=========================[]" << endl << endl << endl; Sleep(100);
			if (langSelected == slang.EN){
				cout << "Write your choice like '3x3', '4x4' or '5x5'. Press ENTER to select.\n";
				cout << "Write your choice: ";
			}
			else if (langSelected == slang.PT) {
				cout << "Escreva a sua escolha, como por exemplo:'3x3', '4x4' ou '5x5'. \n Pressione ENTER para selecionar. \n";
				cout << "Escreva a sua escolha: ";
			}
		}
		else
		{
			if (langSelected == slang.EN)
			{
				cout << "+------------------------------+" << endl;
				cout << "| Load Old Puzzle: Puzzle Size |" << endl;
				cout << "|                              |" << endl;
				cout << "| 'q' or 'Q' to return to menu |" << endl;
				cout << "+------------------------------+" << endl << endl;
				cout << setw(15) << "[Size] : " << "( available )" << endl << endl;
				cout << setw(17) << "[3x3] : ( " << searchPuzzleNumber(3) << " )"<< endl;
				cout << setw(17) << "[4x4] : ( " << searchPuzzleNumber(4) << " )"<< endl;
				cout << setw(17) << "[3x3] : ( " << searchPuzzleNumber(5) << " )"<< endl << endl;
				cout << "Your Option: ";
			}
			else if (langSelected == slang.PT)
			{
				cout << "+--------------------------------+" << endl;
				cout << "|    Carregar Puzzle: Tamanho    |" << endl;
				cout << "|                                |" << endl;
				cout << "| 'q' ou 'Q' para voltar ao menu |" << endl;
				cout << "+--------------------------------+" << endl << endl;
				cout << setw(15) << "[Tamanho] : " << "( disponiveis )" << endl << endl;
				cout << setw(17) << "[3x3] : ( " << searchPuzzleNumber(3) << " )"<< endl;
				cout << setw(17) << "[4x4] : ( " << searchPuzzleNumber(4) << " )"<< endl;
				cout << setw(17) << "[3x3] : ( " << searchPuzzleNumber(5) << " )"<< endl << endl;
				cout << "Escolha: ";
			}
		}


		// Waits for puzzle dimension to be introduced.
		cin >> puzzle_dimension;

		// Verifies if valid string is inputed.
		if (!cin.fail())
		{
			// Goes back if 'q' or 'Q'.
			if ((puzzle_dimension=="q")||(puzzle_dimension=="Q"))
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				return 0;
			}
			else if ((puzzle_dimension=="3x3")||(puzzle_dimension=="4x4")||(puzzle_dimension=="5x5")
				|| (puzzle_dimension == "3X3") || (puzzle_dimension == "4X4") || (puzzle_dimension == "5X5"))
			{
				// Converts to integer.
				puzzle_size = atoi(puzzle_dimension.c_str());

				// Creates puzzle vector with correct size.
				vector<vector <int>> puzzle(puzzle_size, vector<int> (puzzle_size));
				// Creates backup puzzle vector. 
				vector<vector <int>> backupPuzzle(puzzle_size, vector<int> (puzzle_size));


				if(type == NEW)
				{
					// New puzzle.
					initPuzzle(puzzle);
					shufflePuzzle(puzzle);
					savePuzzle(puzzle, puzzle_size);
				} 
				// Load puzzle. 
				else if (type == OLD) {
					puzzle_count = initOldPuzzle(puzzle);
				} 
				// Training mode.
				else if (type == TRAINING)
				{
					initPuzzle(puzzle);
					shufflePuzzle(puzzle);
					copyPuzzle(puzzle, backupPuzzle);
				}

				// If error on loading puzzle.
				if((type == OLD) && (puzzle_count == -1))
				{
					return 5;
				}
				// If not, starts the game.
				else
				{
					if(type == NEW || type == OLD)
					{

						// Launch counter. 
						launchCounter();

						// Starts the game and starts timer.
						time = startGame(puzzle); 

						// Converts time to minutes and seconds to be displayed.
						convertTime(time);

						//Plays final sound
						playSoundFinal();

						// Displays time, and message.
						gameOverScreen();

					} else if(type == TRAINING) {
						do {
							launchCounter();
							time = startGame(puzzle);
							convertTime(time);
							if (soundState)
							{
								playSoundFinal();
							}
							gameOverScreen();
							recopyPuzzle(backupPuzzle, puzzle);
						} while(playAgain());
					}


					// Updates puzzle count.
					if(type == NEW) puzzle_count = searchPuzzleNumber(puzzle_size);

					// Saves score.
					if(type == NEW || type == OLD) saveScore(puzzle_size,time,puzzle_count);
					return 0;
				}
			}
		}
		// If input is incorrect.
		else
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			return 3;
		}
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		// Only exits thread if 'q' or 'Q' are inputed.
	} while(!((puzzle_dimension=="q")||(puzzle_dimension=="Q")));

	return 0;

}

// =====================================================
// =====================================================





// ==========================================
// ============ MENU FUNCTIONS ==============
// ==========================================


/* ==========================================
    +++++++++++ COMPETITION MENU +++++++++++     
   ==========================================
|												
|
|   Purposes: Displays a menu with 2
|   possible choices the user can choose from. 
|   The choice is made inputing the 
|   corresponding number. 
|
|	Choices:
|		1 - New Competition Puzzle
|		2 - Load Old Competition Puzzle
|
|   Parameters: None. 
|
|   Returns: 0 if everything is done without
|   errors. 
|
|=============================================
*/

int competition()
{

	const unsigned int ITEM_COUNT = 3;

	int key;
	int itemSelected = 0;

	bool done = false;


	do
	{
		clearScreen();
		if (langSelected == slang.EN)
		{
			cout << setw(31) << "+------------------+" << endl;
			cout << setw(31) << "| Competition Mode |" << endl;
			cout << setw(31) << "+------------------+" << endl << endl;
		}
		else if (langSelected == slang.PT)
		{
			cout << setw(31) << "+-----------------+" << endl;
			cout << setw(31) << "| Modo de Torneio |" << endl;
			cout << setw(31) << "+-----------------+" << endl << endl;
		}
		cout << "     ===============================\n";

		// Cicles through menu
		switch(itemSelected) {
		case smenu_item.NEW:
			if(langSelected==slang.EN) cout << "               +++ NEW  +++ \n";
			else if(langSelected==slang.PT) cout << "               +++ NOVO +++ \n";
			break;
		case smenu_item.LOAD:
			if(langSelected==slang.EN) cout << "               +++ LOAD +++ \n";
			else if(langSelected==slang.PT) cout << "             +++ CARREGAR +++ \n";
			break;
		case smenu_item.BACK:
			if(langSelected==slang.EN) cout << "               +++ BACK +++ \n";
			else if(langSelected==slang.PT) cout << "              +++ VOLTAR +++ \n";
			break;
		default:
			cout << "          +++ NOTHING SELECTED! +++ \n";
			break;
		}

		cout << "     ===============================\n";

		// Instructions
		if(langSelected==slang.EN)
		{
			cout << "\n\n\n           [Arrows]  Navigate" << endl;
			cout << "\n              [q/Q]      Exit" << endl;
		}
		else if(langSelected==slang.PT)
		{
			cout << "\n\n\n           [Setas]  Escolher" << endl;
			cout << "\n             [q/Q]      Sair" << endl;
		}


		key = _getch();
		// If arrow key is pressed discard first value.
		if(key == skey_code.KEY_ARROW)
			key = _getch();
		// Go back.
		if(key == skey_code.KEY_q || key == skey_code.KEY_Q)
			return 0;

		// Handles arrow keys.
		switch(key) {
		case skey_code.KEY_UP:
			if(itemSelected > 0)
				itemSelected--;
			break;
		case skey_code.KEY_DOWN:
			if(itemSelected < (ITEM_COUNT - 1))
				itemSelected++;
			break;
		default:
			done = false;
		}

		if(key == skey_code.KEY_ENTER)
			done = true;

	} while(!done);

	// Handles item selected.
	switch(itemSelected) {
	case smenu_item.NEW:
		gameThread(0);
		break;
	case smenu_item.LOAD:
		gameThread(1);
		break;
	case smenu_item.BACK:
		return 0;
		break;
	default:
		break;
	}

	return 0;
}

/* ==========================================
       +++++++++ CONFIRM DIALOG +++++++++++++     
   ==========================================
|												
|
|   Purposes: Asks user if he really wants to
|			  quit.
|
|   Parameters: None. 
|
|   Returns: True if "yes".
|
|=============================================
*/

bool confirm()
{

	// Variables
	bool itemSelected = true;
	bool done = false;

	int key;

	do {
	clearScreen();

	if(langSelected==slang.EN)
	{
		cout << "\n\n\n\n            Are you sure?";
		cout << "\n\n\n            [YES]    [NO]" << endl;
	}
	else if(langSelected==slang.PT)
	{
		cout << "\n\n\n\n            Tem a certeza?";
		cout << "\n\n\n            [SIM]   [NAO]" << endl;
	}
	if(itemSelected)
		cout << "              ^" << endl;
	else
		cout << "                      ^" << endl;

	key = _getch();
	// If arrow key is pressed discard first value.
	if(key == skey_code.KEY_ARROW)
		key = _getch();
	// Go back.
	if(key == skey_code.KEY_q || key == skey_code.KEY_Q)
		return 0;

	// Handles arrow keys.
	switch(key) {
	case skey_code.KEY_RIGHT:
		if(itemSelected)
			itemSelected = false;
		break;
	case skey_code.KEY_LEFT:
		if(!itemSelected)
			itemSelected = true;
		break;
	default:
		done = false;
	}

	if(key == skey_code.KEY_ENTER)
		done = true;

	} while(!done);

	return itemSelected;
}

/* ==========================================
    +++++++++ CHOOSE LANGUAGE ++++++++++++++     
   ==========================================
|												
|
|   Purposes: Allows the user to change the
|			  in-game language.
|
|   Parameters: None. 
|
|   Returns: 0
|
|=============================================
*/
int chooseLang()
{
	int key;
	do
	{
		clearScreen();

		if(langSelected==slang.EN)
		{
			cout << "[]=========================================[]\n";
			cout << "||                                         ||\n";
			cout << "||             GAME LANGUAGE               ||\n";
			cout << "||                                         ||\n";
			cout << "[]=========================================[]\n\n\n";

		}
		else if(langSelected==slang.PT)
		{
			cout << "[]=========================================[]\n";
			cout << "||                                         ||\n";
			cout << "||                 LINGUA                  ||\n";
			cout << "||                                         ||\n";
			cout << "[]=========================================[]\n\n\n";

		}
		cout <<     "          []====================[]" << endl << endl;
		// Cicles through menu
		switch(langSelected) {
		case slang.EN:
			cout << "                 English [X]\n";
			cout << "               Portugues [ ]\n";
			break;
		case slang.PT:
			cout << "                 English [ ]\n";
			cout << "               Portugues [X]\n";
			break;
		default:
			break;
		}

		cout << endl << "          []====================[]" << endl;

		switch(langSelected) {
		case slang.EN:
			cout << "\n\n\n [Arrows] Choose language. \n  [ENTER] Select.";
			break;
		case slang.PT:
			cout << "\n\n\n [Setas] Escolher lingua. \n [ENTER] Seleccionar.";
			break;
		}

		key = _getch();
		// If arrow key is pressed.
		if(key == skey_code.KEY_ARROW)
			key = _getch();
		if(key == skey_code.KEY_Q || key == skey_code.KEY_q)
			return 0;

		// Handles key pressed.
		switch(key) {
		case skey_code.KEY_UP:
			if(langSelected == slang.PT)
				langSelected++;
			break;
		case skey_code.KEY_DOWN:
			if(langSelected == slang.EN)
				langSelected--;
			break;
		default:
			break;
		}

		// If enter is pressed.
		if(key == skey_code.KEY_ENTER)
		{
			return 0;
		}
	} while(true);
	return 0;
}

/* ==========================================
    +++++++++ INITIAL LANGUAGE +++++++++++++     
   ==========================================
|												
|
|   Purposes: Asks user what os the language
|			  he/she wants to play the game
|			  with.
|
|   Parameters: None. 
|
|   Returns: 0
|
|=============================================
*/
int initLang()
{
	string welcomePt = "Bem vindo ao Jogo do Puzzle";
	string welcomeEn = "Welcome to the Puzzle Game";
	int key;

	cout<<"          ";
	for(unsigned short int i = 0; i < welcomePt.length(); i++)
	{
		cout << welcomePt[i];
		Sleep(30);
	}
	cout<<endl;

	cout<<"          ";
	for(unsigned short int i = 0; i < welcomeEn.length(); i++)
	{
		cout << welcomeEn[i];
		Sleep(30);
	}
	cout << endl << endl;

	do
	{
		//Displays
		cout << "             ";
		cout << "Lingua? / Language?" << endl << endl;
		cout << "            []=================[]" << endl
			 << "            ||                 ||" << endl;
		switch(langSelected) {
		case slang.EN:
			cout << "            ";
			cout << "||   English  [X]  ||" << endl;
			cout << "            ";
			cout << "|| Portugues  [ ]  ||" << endl;
			break;
		case slang.PT:
			cout << "            ";
			cout << "||   English  [ ]  ||" << endl;
			cout << "            ";
			cout << "|| Portugues  [X]  ||" << endl;
			break;
		default:
			break;
		}
		cout << "            ||                 ||"<<  endl
			 << "            []=================[]"  << endl;

		// Print instructions
		switch(langSelected) {
		case slang.EN:
			cout << "\n\n\n [Arrows] Choose language. \n  [ENTER] Select.";
			break;
		case slang.PT:
			cout << "\n\n\n [Setas] Escolher linguagem. \n [ENTER] Seleccionar.";
			break;
		}

		key = _getch();
		// If arrow key is pressed.
		if(key == skey_code.KEY_ARROW)
			key = _getch();
		if(key == skey_code.KEY_Q || key == skey_code.KEY_q)
			exit(0);

		// Handles key pressed.
		switch(key) {
		case skey_code.KEY_UP:
			if(langSelected < 1)
				langSelected++;
			break;
		case skey_code.KEY_DOWN:
			if(langSelected > 0)
				langSelected--;
			break;
		default:
			break;
		}

		// If enter is pressed.
		if(key == skey_code.KEY_ENTER)
		{
			break;
		}

		//Second Display
		clearScreen();
		cout<<"          ";
		cout << welcomePt << endl;
		cout<<"          ";
		cout << welcomeEn << endl << endl;
	}while(true);

	return 0;
}

/* ==========================================
    +++++++++++++ INIT SOUND ++++++++++++++     
   ==========================================
|												
|
|   Purposes: Asks user if he/she wants or not
|			  sounds in his/her game.
|
|   Parameters: None. 
|
|   Returns: 0
|
|=============================================
*/
int initSound()
{
	int key;
	do
	{
		//Displays
		clearScreen();
		cout << "                      ";
		if (langSelected == slang.EN) cout << "Sound?" << endl << endl;
		else if (langSelected == slang.PT) cout << "Som?" << endl << endl;

		cout << "            []=================[]" << endl
			 << "            ||                 ||" << endl;
		switch(langSelected) {
		case slang.EN:
			if(soundState)
			{
				cout << "            ";
				cout << "||    ON   [X]     ||" << endl;
				cout << "            ";
				cout << "||    OFF  [ ]     ||" << endl;
			}
			else
			{
				cout << "            ";
				cout << "||    ON   [ ]     ||" << endl;
				cout << "            ";
				cout << "||    OFF  [X]     ||" << endl;
			}
			break;
		case slang.PT:
			if(soundState)
			{
				cout << "            ";
				cout << "||    SIM  [X]     ||" << endl;
				cout << "            ";
				cout << "||    NAO  [ ]     ||" << endl;
			}
			else
			{
				cout << "            ";
				cout << "||    SIM  [ ]     ||" << endl;
				cout << "            ";
				cout << "||    NAO  [X]     ||" << endl;
			}
			break;
		default:
			break;
		}
		cout << "            ||                 ||"<<  endl
			 << "            []=================[]"  << endl;

		key = _getch();
		// If arrow key is pressed.
		if(key == skey_code.KEY_ARROW)
			key = _getch();

		// Handles key pressed.
		switch(key) {
		case skey_code.KEY_UP:
				soundState = (!(soundState));
			break;
		case skey_code.KEY_DOWN:
				soundState = (!(soundState));
			break;
		default:
			break;
		}

		// If enter is pressed.
		if(key == skey_code.KEY_ENTER)
		{
			break;
		}

		//Second Display
	}while(true);

	return 0;
}

/* ==========================================
       +++++++++++ MAIN MENU +++++++++++     
   ==========================================
|												
|
|   Purposes: Displays a menu with 2
|   possible choices the user can choose from. 
|   The choice is made inputing the 
|   corresponding number. 
|
|   Parameters: None. 
|
|   Returns: 0 if everything is done without
|   errors. 
|
|=============================================
*/

int mainMenu()
{

	const unsigned int ITEM_COUNT = 5;

	int key;
	int itemSelected = 0;

	bool done = false;

	//Creates file puzzle_number
	createPuzzleNumber(); 

	do
	{
		clearScreen();

		if(langSelected==slang.EN)
		{
			cout << "============================================\n";
			cout << "|                                          |\n";
			cout << "|               PUZZLE GAME                |\n";
			cout << "|                                          |\n";
			cout << "|          Press ENTER to select!          |\n";
			cout << "|                                          |\n";
			cout << "============================================\n\n\n";

			cout << "     ===============================\n";
		}
		else if(langSelected==slang.PT)
		{
			cout << "============================================\n";
			cout << "|                                          |\n";
			cout << "|             JOGO DE PUZZLES              |\n";
			cout << "|                                          |\n";
			cout << "|      Pressione ENTER para selecionar     |\n";
			cout << "|                                          |\n";
			cout << "============================================\n\n\n";

			cout << "     ===============================\n";
		}

		// Cicles through menu
		switch(itemSelected) {
		case smenu_item.TRAINING:
			if(langSelected==slang.EN) cout << "          +++ TRAINING MODE +++ \n";
			else if(langSelected==slang.PT) cout << "           +++ MODO TREINO +++ \n";
			break;
		case smenu_item.COMPETITION:
			if(langSelected==slang.EN) cout << "        +++ COMPETITION MODE +++ \n";
			else if(langSelected==slang.PT) cout << "         +++ MODO DE TORNEIO +++ \n";
			break;
		case smenu_item.LANGUAGE:
			if(langSelected==slang.EN) cout << "             +++ LANGUAGE +++ \n";
			else if(langSelected==slang.PT) cout << "              +++ LINGUA +++ \n";
			break;
		case smenu_item.SOUND:
			if(langSelected==slang.EN) {
				cout << "            +++ SOUND:";
				if(soundState) cout << " ON +++ \n";
				else cout << " OFF +++ \n";
			}
			else if(langSelected==slang.PT) { 
				cout << "           +++ SOM:";
				if(soundState) cout << " LIGADO +++ \n";
				else cout << " DESLIGADO +++ \n";
			}
			break;
		case smenu_item.QUIT:
			if(langSelected==slang.EN) cout << "               +++ QUIT +++ \n";
			else if(langSelected==slang.PT) cout << "               +++ SAIR +++ \n";
			break;
		default:
			cout << "      +++ ERROR! +++ \n";
			break;
		}

		
		cout << "     ===============================";
		
		// Instructions
		if(langSelected==slang.EN)
		{
			cout << "\n\n\n           [Arrows]  Navigate" << endl;
			cout << "\n              [q/Q]      Exit" << endl;
		}
		else if(langSelected==slang.PT)
		{
			cout << "\n\n\n           [Setas]  Escolher" << endl;
			cout << "\n             [q/Q]      Sair" << endl;
		}

		// Credits
		cout << "\n\nDeveloped by Kevin Amorim and Luis Magalhaes.\n";
		cout << "FEUP @2013";


		key = _getch();
		// If arrow key is pressed.
		if(key == skey_code.KEY_ARROW)
			key = _getch();

		// If 'q' or 'Q' are pressed, exit game.
		if(key == skey_code.KEY_q || key == skey_code.KEY_Q)
				if (confirm()) exit(0);

		// Handles key pressed.
		switch(key) {
		case skey_code.KEY_UP:
			if(itemSelected > 0)
				itemSelected--;
			break;
		case skey_code.KEY_DOWN:
			if(itemSelected < (ITEM_COUNT - 1))
				itemSelected++;
			break;
		default:
			break;
		}

		// If enter is pressed.
		if(key == skey_code.KEY_ENTER)
		{
			switch(itemSelected)
			{
			case smenu_item.TRAINING:
				gameThread(2);
				break;
			case smenu_item.COMPETITION:
				competition();
				break;
			case smenu_item.LANGUAGE:
				chooseLang();
				break;
			case smenu_item.SOUND:
				soundState = changeSoundState();
				break;
			case smenu_item.QUIT:
				if (confirm()) exit(0);
				else break;
			default:
				break;
			}
		}
	} while(true);

	return 0;

}

// ============================================
// ============================================


// ===============================
// ======== MAIN FUNCTION ========
// ===============================

// Initializes the game and can be used to tests. 
int main() 
{
	removeCursor();
	initLang();
	initSound();
	mainMenu();

	return 0;
}
