#ifndef AUX_FUNCTIONS_H_INCLUDED
#define AUX_FUNCTIONS_H_INCLUDED

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

#include <string>
#include <vector>

#include "class_administrator.h"
#include "class_radio_station.h"
#include "class_user.h"
#include "class_musictrack.h"

using namespace std;

// ========================================
// CONVERTERS
// ========================================
// Converts given string to integer and returns int value.
int convertStrInt(std::string iStr);
// Converts given integer to boolean and returns bool value.
bool convertToBool(int input);
// Checks if string is a number.
bool isNumber(std::string inputStr);

// ========================================
// CSV Files Handling 
// ========================================
// Creates .csv files if necessary
void createAllFiles();
// Returns string with filename including a sequence.
std::string createFilenameWithSequence(const std::string &prefixStr, const std::string &sufixStr, unsigned int numberOfDigits, const unsigned int &sequencePosition);
// Loads user information from csv file and returns a string containing all the user information.
std::string loadFromFile(std::string username);
// Handles commas in csv files.
std::string extractInfo(std::string & infoStr);
// Search ID by username.
int searchID(std::string username, std::string filename); // Not implemented
// Returns last saved ID in csv file.
int searchLastID(std::string filename);
// Returns the password associated to a certain login.
std::string getPassword(std::string login);
// Returns the status associated to a certain login.
int getStatus(std::string login);
// Checks if a file exists. Returns true if exists, returns false if not.
bool fileExists(const std::string &filename);
// Checks if an ID exists on a file.
bool existsID(const string filename, const unsigned int ID);
// Decrements an ID from a file.
void decrementIDFromFile(const string filename, const unsigned int originalID, const unsigned int newID);

// ========================================
// Search Engine
// ========================================
void searchAllMusicsByValue(const string &keyword, const int &value, vector<MusicTrack> &musicList);

// ========================================
// Music Tracks Handling
// ========================================
// Verifies if a certain music exists in a user Playlist
char isPlaylistMember(User &user, unsigned const int musicID);
// Verifies if a certain music exists in an admin Playlist
char isPlaylistMember(Administrator &user, unsigned const int musicID);

// ========================================
// Top ten list
// ========================================
// Displays top ten list.
void displayTopTen(vector<MusicTrack> &topTenVector, const int &line);
// Gets top ten list to a vector.
void getTopTen(RadioStation &radio1, vector<MusicTrack> &topTenVector);

// ========================================
// Utilities
// ========================================
// Initializes program. Creates necessary resources and prepares console window.
void init();
// Waits for user to press a key.
void waitForKey();
// Removes cursor from screen.
void removeCursor();
// Clears all console screen.
void clearScreen();
// Gets keyboard key code.
void getKeyCode();
// Changes text color.
void changeTextColor(const string &color);

#endif