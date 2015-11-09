#ifndef CLASS_MUSICTRACK_H_INCLUDED
#define CLASS_MUSICTRACK_H_INCLUDED

/* ==========================================
TITLE: CLASS_MUSIC_TRACK					|
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

using namespace std;
// ============================================================

class MusicTrack 
{

private:
	// Music information
	unsigned int ID;
	string title;
	string author;
	string album;
	string musicGenre;
	unsigned short int year;
	unsigned int likes;
	unsigned int dislikes;
	bool available;

public:

	// ===================================================
	// Constructors
	// ===================================================
	MusicTrack();
	// Basic constructor (without likes/dislikes)
	MusicTrack(string inputTitle, string inputAuthor, string inputAlbum, string inputGenre, 
		unsigned short int inputYear);
	// Complete constructor.
	MusicTrack(unsigned int inputID, string inputTitle, string inputAuthor, string inputAlbum, 
		string inputGenre, unsigned short int inputYear, int inputLikes, int inputDislikes, bool inputAvailable);
	// ===================================================
	// ===================================================
	// Show Music Information
	// ===================================================
	// Returns all music information.
	string getTitle() const;
	string getAuthor() const;
	string getAlbum() const;
	string getMusicGenre() const;
	unsigned short int getYear() const;
	unsigned int getID() const;
	unsigned int getLikes() const;
	unsigned int getDislikes() const;
	bool getAvailable() const;
	int getRatio() const;
	// ===================================================
	// ===================================================
	// Change Music Information
	// ===================================================
	// Changes class private members.
	void setID(unsigned const int inputID);
	void setTitle( string inputTitle );
	void setAuthor( string inputAuthor );
	void setAlbum( string inputAlbum );
	void setGenre( string inputGenre );
	void setYear( unsigned short int inputYear);		
	void setLikes( unsigned short int likesInput, bool add, bool take);			
	void setDislikes( unsigned short int dislikesInput, bool add, bool take);
	void setAvailable( bool value);
	// ===================================================
	// ===================================================
	// Other Functions
	// ===================================================
	// Displays music information on a complete way.
	void displayMusic();
	// Displays music information on a abreviated way.
	void display(const bool displayRatio);
	// ===================================================
	// ===================================================
	// Text Files Handling
	// ===================================================
	// Saves music information to file.
	void saveToFile();
	// ===================================================
	// ===================================================
	// Destructor
	// ===================================================
	~MusicTrack();

};

#endif