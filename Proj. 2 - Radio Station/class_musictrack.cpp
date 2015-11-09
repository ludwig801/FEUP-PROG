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
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "class_musictrack.h"
#include "aux_functions.h"
#include "strings.h"

using namespace std;
// ============================================================
// ===================================================
// Constructors
// ===================================================
// Default constructor.
MusicTrack::MusicTrack()
{
	ID = searchLastID("radioStationMusics.csv") + 1;
	title = "title";
	author = "author";
	album = "album";
	musicGenre = "others";
	year = 1999;

	likes = 0;
	dislikes = 0;

	available = false;
};

MusicTrack::MusicTrack(string inputTitle, string inputAuthor, string inputAlbum, string inputGenre, unsigned short int inputYear)
{	
	ID = searchLastID("radioStationMusics.csv") + 1;
	title = inputTitle;
	author = inputAuthor;
	album = inputAlbum;
	musicGenre = inputGenre;
	year = inputYear;
	
	likes = 0;
	dislikes = 0;

	available = true;
};

MusicTrack::	MusicTrack(unsigned int inputID, string inputTitle, string inputAuthor, string inputAlbum, 
		string inputGenre, unsigned short int inputYear, int inputLikes, int inputDislikes, bool inputAvailable)
{	
	ID = inputID;
	title = inputTitle;
	author = inputAuthor;
	album = inputAlbum;
	musicGenre = inputGenre;
	year = inputYear;

	likes = inputLikes;
	dislikes = inputDislikes;

	available = inputAvailable;
};
// ===================================================
// ===================================================
// ===================================================
// Show Music Information
// ===================================================
// Returns all music information.
// Return Music title.
string MusicTrack::getTitle() const {
	return title;
}
// Return Music author.
string MusicTrack::getAuthor() const {
	return author;
}
// Return Music album.
string MusicTrack::getAlbum() const {
	return album;
}
// Return Music genre.
string MusicTrack::getMusicGenre() const {
	return musicGenre;
}
// Return Music year.
unsigned short int MusicTrack::getYear() const {
	return year;
}
// Return Music likes.
unsigned int MusicTrack::getLikes() const {
	return likes;
}
// Return Music dislikes.
unsigned int MusicTrack::getDislikes() const {
	return dislikes;
}
// Return Music unique ID.
unsigned int MusicTrack::getID() const {
	return ID;
}
// Return true/false due to availability
bool MusicTrack::getAvailable() const {
	return available;
}
// Returns like/dislike ratio
int MusicTrack::getRatio() const {
	int likesTotal = likes;
	int dislikesTotal = dislikes;

	return (likesTotal - dislikesTotal);
}
// ===================================================
// ===================================================
// Change Music Information
// ===================================================
// Changes class private members.
// Sets music ID
void MusicTrack::setID(unsigned const int inputID) {
	ID = inputID;
}
// Sets music title
void MusicTrack::setTitle( string inputTitle )
{
	title = inputTitle;
}
// Sets music author
void MusicTrack::setAuthor( string inputAuthor )
{
	author = inputAuthor;
}
// Sets music album
void MusicTrack::setAlbum( string inputAlbum )
{
	album = inputAlbum;
}
// Sets music genre
void MusicTrack::setGenre( string inputGenre )
{
	musicGenre = inputGenre;
}
// Sets music year
void MusicTrack::setYear( unsigned short int inputYear)
{
	year = inputYear;
}
// Sets music likes
void MusicTrack::setLikes( unsigned short int likesInput, bool add, bool take)
{

	if((add == false) && (take == false))
	{
		likes = likesInput;
	}
	else
	{
		if(add)
		{
			likes++;
		}
		if((take) && (likes > 0))
		{
			likes--;
		}
	}
}
// Sets music dislikes
void MusicTrack::setDislikes( unsigned short int dislikesInput, bool add, bool take)
{
	if((add == false) && (take == false))
	{
		dislikes = dislikesInput;
	}
	else
	{
		if(add)
		{
			dislikes++;
		}
		if((take) && (dislikes > 0))
		{
			dislikes--;
		}
	}
}
// Sets availability
void MusicTrack::setAvailable( bool value)
{
	available = value;
}
// ===================================================
// ===================================================
// Other Functions
// ===================================================
// Displays music information on a abreviated way.
void MusicTrack::display(const bool displayRatio) {

	if(title.size() > 8)
		cout << setw(8) << (title.substr(0,6) + ".");
	else
		cout << setw(8) << title;

	if(author.size() > 8)
		cout << setw(8) << (author.substr(0,6) + ".");
	else
		cout << setw(8) << author;

	if(album.size() > 8)
		cout << setw(8) << (album.substr(0,6) + ".");
	else
		cout << setw(8) << album;

	if(musicGenre.size() > 8)
		cout << setw(8) << (musicGenre.substr(0,6) + ".");
	else
		cout << setw(8) << musicGenre;

	cout << setw(8) << year;
	
	if(displayRatio) {
		cout << setw(12) << getRatio();
	}
}
// Displays music information on a complete way.
void MusicTrack::displayMusic() {
	
	cout << setw(8);

	cout << msg_base_title() << ": " << title;
	cout << endl;
	cout << setw(8);

	cout << msg_author() << ": " << author;
	cout << endl;
	cout << setw(8);

	cout << msg_album() << ": " << album;
	cout << endl;
	cout << setw(8);

	cout << msg_genre() << ": " << musicGenre;
	cout << endl;
	cout << setw(8);

	cout << msg_year() << ": " << year;
}
// ===================================================
// ===================================================
// Text Files Handling
// ===================================================
// Saves a music track to file
void MusicTrack::saveToFile()
{
	// ============================================================
	// Variables
	// ============================================================
	ofstream saveFile;

	// Opens file in output mode and sets initial position to the end of the file.
	saveFile.open("radioStationMusics.csv", ios::out | ios::app);

	// Writes user info to csv file.
	if(saveFile.is_open()) {
		saveFile << ID << "," << title << "," << author << "," << album << "," << musicGenre << "," << year << "," << likes << "," << dislikes << "\n";
		saveFile.close();
	} else {
		cantOpenFileMsg();
		return;
	}
}
// ===================================================
// ===================================================
// Destructor
// ===================================================
MusicTrack::~MusicTrack()
{
	//clear();
};
// ===================================================


