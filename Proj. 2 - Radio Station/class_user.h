#ifndef CLASS_USER_H_INCLUDED
#define CLASS_USER_H_INCLUDED

/* ==========================================
TITLE: CLASS_USER							|
											|
AUTHORS: Kevin Amorim - ei12057				|
		 Luís Magalhães - ei12054			|
											|
GROUP: T2G02								|
											|
DATE: 2013/05/28							|
											|
PURPOSE: User object. Holds all user		|
information and function.					|
											|
PARAMETERS:	No parameters needed.			|
											|
											|
   -->  DEVELOPED WITH WINDOWS 8.  <--		|
============================================*/
// ============================================================
// INCLUDES
// ============================================================
#include<string>
#include<vector>
#include "class_musictrack.h"

using namespace std;
// ============================================================

class User
{

private:
	// Profile information
	unsigned int ID;
	string name;
	string pass;
	unsigned int age;
	string gender;
	bool special;

	// Number of hits the user already has.
	unsigned int numberOfHits;
	
	// Playlist
	vector<unsigned int> playList;

public:
	// ===================================================
	// Constructors
	// ===================================================
	User();
	User(unsigned int iID, string iName, unsigned int iAge, string iGender, bool iSpecial, 
		string iPass, unsigned int iNumberOfHits);
	User(unsigned int iID, string iName, unsigned int iAge, string iGender, bool iSpecial, 
		string iPass, unsigned int iNumberOfHits, bool temp);
	// ===================================================
	// ===================================================
	// Show User Profile Information
	// ===================================================
	// Returns user information.
	unsigned int getID();
	string getName();
	unsigned int getAge();
	string getGender();
	bool getSpecial();
	string getPass();
	unsigned int getNumberOfHits() const;
	// Displays user information, in a compiled way.
	void displayUserInformation() const;
	// ===================================================
	// ===================================================
	// Change User Profile Information
	// ===================================================
	// Functions used to change private members of the class.
	void setID(unsigned int inputID);
	void setName(string inputName);
	void setAge(unsigned int inputAge);
	void setGender(string inputGender);
	void setSpecial(bool inputSpecial);
	void setPass(string inputPass);
	void setNumberOfHits(unsigned int iNumberOfHits);
	// ===================================================
	// ===================================================
	// Text Files Handling
	// ===================================================
	// Writes user information to csv file.
	void saveToFile();
	// Saves user playlist to csv file.
	bool saveMusics() const;
	// Saves user rating to file.
	void saveRatingsToFile(std::vector< vector<int> > &ratingsVec);
	// Rewrites user information to csv file.
	void rewritesUserToFile() const;
	// Loads user information from csv file.
	void loadUserFromFile(const string &username);
	// Loads user playlist from csv file.
	void loadUserPlaylistFromFile();
	// ===================================================
	// ===================================================
	// Playlist Management
	// ===================================================
	// Returns playlist size.
	size_t size() const;
	//    === TRACKS MANAGEMENT ===
	// Adds track to user playlist. Receives music ID as parameter.
	void addTrack(unsigned const int iMusicID);
	// Removes track from user playlist. Receives music ID as parameter.
	void remTrack(unsigned const int iMusicID);
	// Checks if user exists or not on user playlist. Returns true if it exists.
	bool musicExists(unsigned const int iMusicID);
	// Returns music ID from user playlist.
	unsigned int getMusicID(unsigned const int value);
	// Rates a music. Receives music ID to rate as parameter.
	void rateMusic(int rate, int musicID);
	// Checks if a music is already rated. If true, returns rating.
	int rateExists(int iMusicID);
	// Displays all user musics.
	void displayList(unsigned const int line, vector<MusicTrack> &musicList, unsigned const int &page_number);
	// Displays a particular music from user playlist.
	void displayTrack(unsigned const int pos, vector<MusicTrack> &musicList);
	// Decrements user music ID's from playlist.
	void decrementMusicID(unsigned const int musicID);
	// Decrements user music ID's from ratings file.
	void decrementRatingsID(unsigned const int musicID);
	// Checks if user has hits on his/her playlist. If it founds an hit, it increments the number of hits.
	void checkForHits(vector<MusicTrack> & playlistOfTheDay);
	// Increments by one the number of hits on user's playlist.
	void incrementNumberOfHitsByOne();
	// ===================================================
	// Destructors
	// ===================================================
	~User();
};

#endif