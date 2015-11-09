#ifndef CLASS_ADMINISTRATOR_H_INCLUDED
#define CLASS_ADMINISTRATOR_H_INCLUDED

/* ==========================================
TITLE: ADMINISTRATOR						|
											|
AUTHORS: Kevin Amorim - ei12057				|
		 Luis Magalhaes - ei12054			|
											|
GROUP: T2G02								|
											|
DATE: 2013/05/28							|
											|
PURPOSE: Manages every aspect of an			|
		 administrator (special user)		|
											|
PARAMETERS:	No parameters needed.			|
											|
											|
											|
   -->  DEVELOPED WITH WINDOWS 8.  <--		|
============================================*/

#include<string>
#include<vector>

#include "class_musictrack.h"
#include "class_user.h"

using namespace std;

class Administrator 
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
	// Default Constructor.
	Administrator();
	// Main Constructor. Receives all user information and loads playlist from file.
	Administrator(unsigned int iID, string iName, unsigned int iAge, string iGender, bool iSpecial, string iPass, unsigned int iNumberOfHits);
	// Creates a temporary admin. Receives all user information but doesn't load playlist from file.
	Administrator(unsigned int iID, string iName, unsigned int iAge, string iGender, bool iSpecial, string iPass, unsigned int iNumberOfHits, bool temp);

	// ===================================================
	// Show User Profile Information (get methods)
	// ===================================================
	unsigned int getID() const;
	string getName() const;
	unsigned int getAge() const;
	string getGender() const;
	bool getSpecial() const;
	string getPass() const;
	unsigned int getNumberOfHits() const;

	// ===================================================
	// Change User Profile Information (set methods)
	// ===================================================
	void setID(unsigned int inputID);
	void setName(string inputName);
	void setAge(unsigned int inputAge);
	void setGender(string inputGender);
	void setSpecial(bool inputSpecial);
	void setPass(string inputPass);
	void setNumberOfHits(unsigned int iNumberOfHits);

	// ===================================================
	// Text Files Handling
	// ===================================================
	// Writes administrator information to "users.csv" file.
	void saveToFile() const;
	// Rewrites user information to csv file.
	void rewritesUserToFile() const;
	// Loads administrator from "users.csv" file.
	void loadUserFromFile(const string &username);
	// Saves music tracks to csv file.
	bool saveMusics() const;	
	// Removes music tracks from csv file.
	void removeMusicFile(unsigned const int musicID) const;	
	// Loads user playlist from csv file. Changes user playlist vector. 
	// No parameters required. Doesn't returns anything
	void loadUserPlaylistFromFile();

	// ===================================================
	// Playlist Management
	// ===================================================
	// Returns admin playlist size.
	size_t size() const;
	// Adds a track to playlist.
	void addTrack(unsigned const int iMusicID);
	// Removes a track from playlist.
	void remTrack(unsigned const int iMusicID);
	// Returns true if music is in playlist
	bool musicExists(unsigned const int iMusicID);
	// Returns a music ID
	unsigned int getMusicID(unsigned const int value);
	// Rates a music and saves to file.
	void rateMusic(int rate, int musicID);
	// Checks if a user has liked or disliked a certain music track
	int rateExists(int iMusicID);
	// Displays a user playList
	void displayList(unsigned const int line, vector<MusicTrack> &musicList, unsigned const int &page_number);
	// Displays a single music in the playList
	void displayTrack(unsigned const int pos, vector<MusicTrack> &musicList);
	// Checks if user has hits on his/her playlist. If it founds an hit, it increments the number of hits.
	void checkForHits(vector<MusicTrack> & playlistOfTheDay);
	// Increments by one the number of hits on user's playlist.
	void incrementNumberOfHitsByOne();

	// ===================================================
	// Admin Music Tracks Management
	// ===================================================
	// Adds music track to RadioStationMusics.csv
	void addMusicTrack( string title, string author, string album, string musicGenre, unsigned short int year, unsigned int likes, unsigned int dislikes);

	// ===================================================
	// Destructors
	// ===================================================
	~Administrator();

};

#endif