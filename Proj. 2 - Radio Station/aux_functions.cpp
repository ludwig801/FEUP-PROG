/* ==========================================
TITLE: AUX FUNCTION							|
											|
AUTHORS: Kevin Amorim - ei12057				|
		 Luis Magalhaes - ei12054			|
											|
GROUP: T2G02								|
											|
DATE: 2013/05/28							|
											|
PURPOSE: Auxiliary functions for the		|
program to work. Has functions like			|
converters, console handlers and general	|
purposes functions.							|
											|
PARAMETERS:	No parameters needed.			|
											|
											|
											|
   -->  DEVELOPED WITH WINDOWS 8.  <--		|
============================================*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <locale>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <conio.h>
#include <iomanip>

#include "class_administrator.h"
#include "class_user.h"
#include "class_musictrack.h"
#include "class_radio_station.h"
#include "aux_functions.h"
#include "strings.h"

using namespace std;

using namespace std;

// ========================================
// STRUCTS
// ========================================
// Struct colors - used tu change text color in the program
struct COLORS
{
	static const int BLUE = 0xF9;		// 0000 1010

	static const int GREEN  = 0x0A;		// 0000 1010
	static const int CYAN   = 0x0B;		// 0000 1011
	static const int RED    = 0x0C;		// 0000 1100
	static const int PINK   = 0x0D;		// 0000 1101
	static const int YELLOW = 0x0E;		// 0000 1110

	static const int WHITE  = 0x0F;		// 0000 1111
	static const int BLACK  = 0xF0;		// 0000 1111

} scolor;
// Struct sorting - used so that sort() method can be used in getTopTen() function
struct sorting {
  bool operator() (MusicTrack a, MusicTrack b)
  {
	  return (a.getRatio() > b.getRatio());
  }
} sortingObj;

// ========================================
// CONVERTERS
// ========================================
// Converts given string to integer and returns int value.
int convertStrInt(string iStr) {
	stringstream ss(iStr);
	unsigned int id;
	ss >> id;

	return id;
}
// Converts given integer to boolean and returns bool value.
bool convertToBool(int input) {

	bool fBool = false;

	switch(input) {
	case 0:
		fBool = false;
		break;
	case 1:
		fBool = true;
		break;
	default:
		fBool = false;
		break;
	}

	return fBool;
}
// Checks if string is a number.
bool isNumber(std::string inputStr) {
	std::string::const_iterator it = inputStr.begin();
	locale loc;
	// Loops through string and checks if every character is a digit.
	while(it != inputStr.end() && std::isdigit(*it, loc)) {
		++it;
	}

	// Returns true if the string is not empty and if the iterator reached the end of the string, 
	// (means that every character is a digit).
	return (!inputStr.empty() && it == inputStr.end());
}

// ========================================
// CSV Files Handling 
// ========================================
// Creates all csv files necessary, if they doesn't exists.
void createAllFiles()
{
	fstream fileU("users.csv");
	fstream fileRSM("radioStationMusics.csv");

	fileU.open("users.csv", ios::out);

	if(fileU.is_open()) {
		if(fileU.end)
		{
			fileU << "id,name,age,gender,special,pass,hits\n";
		}
		fileU.close();
	}

	fileRSM.open("radioStationMusics.csv", ios::out);

	if(fileRSM.is_open()) {
		if(fileRSM.end)
		{
			fileRSM << "id,title,author,album,musicGenre,year,likes,dislikes,available\n";
		}
		fileRSM.close();
	}
}
// Returns string with filename including a sequence.
std::string createFilenameWithSequence(const std::string &prefixStr, const std::string &sufixStr, unsigned int numberOfDigits, const unsigned int &sequencePosition)
{

	stringstream filenameStream;

	unsigned int countSequencePositionDigits = 0;
	unsigned int backupSequencePosition = sequencePosition;

	// Count number of digits.
	if(0 == backupSequencePosition) {
		countSequencePositionDigits = 1;
	} else {
		while(backupSequencePosition > 0) {
			countSequencePositionDigits++;
			backupSequencePosition = backupSequencePosition / 10;
		}
	}

	// Creates filename prefix.
	filenameStream << prefixStr;

	if(numberOfDigits < countSequencePositionDigits) {
		cerr << digitCountExceedMsg();
		return "ERROR";
	}
	
	// Creates sequence.
	numberOfDigits -= countSequencePositionDigits;


	while(numberOfDigits > 0) {
		filenameStream << "0";
		numberOfDigits--;
	}

	// Adds sequence position to filename.
	filenameStream << sequencePosition;

	// Adds filename sufix.
	filenameStream << sufixStr;

	return filenameStream.str();
}
// Handles commas in csv files. 
string extractInfo(string & infoStr) {
	
	unsigned int pos = infoStr.find(",");
	string elementStr = infoStr.substr(0, pos);
	infoStr = infoStr.substr(pos+1, infoStr.size()-pos);

	return elementStr;
}
// Returns last ID saved in csv file.
int searchLastID(string filename)
{
	// ============================================================
	// Variables
	// ============================================================
	ifstream saveFile;
	int id;
	string line;

	saveFile.open(filename, ios::in);

	// Checks if text file has been opened.
	if(!saveFile) {
		cantOpenFileMsg();
		return -1;
	}

	if(saveFile.is_open()) {

		getline(saveFile, line);

		// Checks if file is empty. If true returns -1 as ID.
		if(saveFile.peek() == EOF) {
			id = -1;
		}

		// Search last line and returns last ID.
		while(!saveFile.eof()) {
			saveFile >> id;
			getline(saveFile, line);
		}

		saveFile.close();
	}

	return id;
}
// Returns ID of choosed username.
int searchID(string inputStr, string filename) {

	// ============================================================
	// Variables
	// ============================================================
	ifstream saveFile;
	int id;
	string line, tempStr;
	bool done = false;

	saveFile.open(filename, ios::in);

	// Checks if text file has been opened.
	if(!saveFile) {
		cantOpenFileMsg();
		return -1;
	}

	if(saveFile.is_open()) {

		getline(saveFile, tempStr); // Reads the first (useless) line

		while((!done) && (!(saveFile.eof()))) {
			// Saves temporary ID.
			saveFile >> id;

			// Gets username to 
			getline(saveFile, tempStr, ',');
			getline(saveFile, tempStr, ',');

			if(tempStr == inputStr) {
				done = true;
			}

			getline(saveFile, tempStr);

		}

		saveFile.close();

		if(done) { 
			return id;
		} else {
			return -1; // User not found.
		}
	}

	return -1;

}
// Checks if an ID exists on a file.
bool existsID(const string filename, const unsigned int ID) {
	// ============================================================
	// Variables
	// ============================================================
	ifstream saveFile;
	string line;
	int tempID;
	// ============================================================

	saveFile.open(filename, ios::in);

	if(saveFile.is_open()) {
		getline(saveFile, line);

		while(saveFile >> tempID) {
			if(ID == tempID) {
				return true;
			}
		}
	}

	return false;
}
// Checks if a file exists. Returns true if exists, returns false if not.
bool fileExists(const std::string &filename) {
	ifstream file(filename);
	return file;
}
// Loads user information from csv file and returns a string containing all the user information.
string loadFromFile(string username){

	// ============================================================
	// Variables
	// ============================================================
	ifstream saveFile;
	string line;
	int count;

	// Opens file in output mode and sets initial position to the end of the file.
	saveFile.open("users.csv", ios::in);

	// Checks if file has been opened/created.
	if(!saveFile) {
		cantOpenFileMsg();
		return "error";
	}

	if(saveFile.is_open()) {

		count = searchID(username, "users.csv");
		if(count < 0)
			return "NOT FOUND";

		count++; // to increment the first line of the .csv file

		while(count >= 0) {
			getline(saveFile, line);
			count--;
		}

		saveFile.close();
	}

	return line;
}
// Gets user password.
string getPassword(string username)
{
	string infoStr = loadFromFile(username);

	if(infoStr == "NOT FOUND") {
		return infoStr;
	}

	string password;

	for(unsigned int i = 0; i<6; i++) {
		password = extractInfo(infoStr);
	}

	return password;
}
// Gets user status (special user or not)
int getStatus(string username) {
	string infoStr = loadFromFile(username);
	int status;

	for(unsigned int i = 0; i<5; i++) {
		status = convertStrInt(extractInfo(infoStr));
	}

	return status;
}

// ========================================
// Search Engine
// ========================================
void searchAllMusicsByValue(const string &keyword, const int &value, vector<MusicTrack> &musicList) {

	enum {
		TITLE,
		AUTHOR,
		ALBUM,
		GENRE,
		YEAR
	};

	bool found = false;

	for(unsigned int i = 0; i < musicList.size(); i++)
	{
		switch(value)
		{
		case TITLE:
			if(musicList[i].getTitle() == keyword) {
				musicList[i].display(false);
				cout << endl;
				found = true;
			}
			break;
		case AUTHOR:
			if(musicList[i].getAuthor() == keyword) {
				musicList[i].display(false);
				cout << endl;
				found = true;
			}
			break;
		case ALBUM:
			if(musicList[i].getAlbum() == keyword) {
				musicList[i].display(false);
				cout << endl;
				found = true;
			}
			break;
		case GENRE:
			if(musicList[i].getMusicGenre() == keyword) {
				musicList[i].display(false);
				cout << endl;
				found = true;
			}
			break;
		case YEAR:
			if(musicList[i].getYear() == convertStrInt(keyword)) {
				musicList[i].display(false);
				cout << endl;
				found = true;
			}
			break;
		default:
			break;
		}
	}

	if(!found)
	{
		clearScreen();
		cout << msg_keyword_not_found();
		waitForKey();
	}
	else
	{
		cout << endl;
		waitForKey();
	}

}

// ========================================
// Music Tracks Handling
// ========================================
// Verifies if a certain music exists in a user Playlist
char isPlaylistMember(User &user, unsigned const int musicID)
{
	if (user.musicExists(musicID))
	{
		return 'X';
	}
	else return ' ';
}
// Verifies if a certain music exists in an admin Playlist
char isPlaylistMember(Administrator &user, unsigned const int musicID)
{
	if (user.musicExists(musicID))
	{
		return 'X';
	}
	return ' ';
}

// ========================================
// TOP TEN LIST
// ========================================
// Displays top ten list.
void displayTopTen(vector<MusicTrack> &topTenVector, const int &line)
{
	// ============================================================
	// Variables
	// ============================================================

	cout <<	setw(8)
		<< msg_base_title() << setw(8)
		<< msg_author()	<< setw(8)
		<< msg_album() << setw(8)
		<< msg_genre() << setw(8)
		<< msg_year() << setw(12)
		<< msg_popular();
	cout << endl << endl;

	for(unsigned int i = 0; i < topTenVector.size(); i++)
	{

		topTenVector[i].display(true);

		if(i == line)
			cout << "  < " << i + 1 << " >\n\n";
		else
			cout << "    " << i + 1 << "  \n\n";
	}
}
// Gets top ten list to a vector.
void getTopTen(RadioStation &radio1, vector<MusicTrack> &topTenVector)
{
	// Clears vector first.
	topTenVector.clear();
	// Loads all radioStation musics.
	topTenVector = radio1.getAllMusicsList();

	if(topTenVector.size() != 0)
	{
		// Sorts all musics by like ratio (likes - dislikes)
		sort(topTenVector.begin(), topTenVector.end(), sortingObj);

		// Truncates vector by a size of ten (Top Ten)
		if(topTenVector.size() >= 10)
			topTenVector.erase(topTenVector.begin() + 10, topTenVector.end());
	}

}

// ========================================
// Utilities
// ========================================
// Initializes program. Creates necessary resources and prepares console window.
void init() {
	// Removes the ticking cursor.
	removeCursor();
	// Creates all necessary csv files, if they don't already exists.
	createAllFiles();
}
// Waits for user to press key.
void waitForKey()
{
	cout << msg_press_any_key();
	_getch();
}
// Removes cursor from screen.
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
// Clears console screen.
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
// Gets keyboard key code.
void getKeyCode() {

	unsigned const int ENTER = 13;
	int key;

	do {

		cout << msg_press_any_key() << endl;

		key = _getch();

		cout << key << endl;

	} while( key != ENTER);

}
// Changes text color.
void changeTextColor( const string &color) {

	if ( "WHITE" == color )
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), scolor.WHITE );
	else if ( "BLACK" == color )
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), scolor.BLACK );
	else if ( "BLUE" == color )
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), scolor.BLUE );
	else if ( "CYAN" == color )
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), scolor.CYAN );
	else if ( "GREEN" == color )
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), scolor.GREEN );
	else if ( "RED" == color )
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), scolor.RED );
	else if ( "YELLOW" == color )
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), scolor.YELLOW );
	else if ( "PINK" == color )
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), scolor.PINK );
	else
		SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), scolor.WHITE );
}

