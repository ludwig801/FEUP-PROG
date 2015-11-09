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

#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "class_administrator.h"
#include "class_user.h"
#include "aux_functions.h"
#include "strings.h"

using namespace std;

// ============================================================
// ADMINISTRATOR
// ============================================================
// ============================================================
// Administrator Constructors
// ============================================================
// Default constructor
Administrator::Administrator() 
{
	ID = 0;
	name = "user";
	age = 0;
	gender = "EMPTY";
	special = true;
	pass = "pass";
};
// Creates new admin.
Administrator::Administrator(unsigned int iID, string iName, unsigned int iAge, string iGender, bool iSpecial, string iPass, unsigned int iNumberOfHits) {

	ID = iID;
	name = iName;
	age = iAge;
	gender = iGender;
	special = iSpecial;
	pass = iPass;
	numberOfHits = iNumberOfHits;

	loadUserPlaylistFromFile();

	saveToFile();
};
// Creates temporary Administrator.
Administrator::Administrator(unsigned int iID, string iName, unsigned int iAge, string iGender, bool iSpecial, string iPass, unsigned int iNumberOfHits, bool temp) {

		ID = iID;
		name = iName;
		age = iAge;
		gender = iGender;
		special = iSpecial;
		pass = iPass;
		numberOfHits = iNumberOfHits;

		loadUserPlaylistFromFile();
}

// ============================================================
// Shows Admin profile information
// ============================================================
// Return Admin ID.
unsigned int Administrator::getID() const {
	return ID;
}
// Returns Admin username string.
string Administrator::getName() const {
	return name;
}
// Returns Admin age integer.
unsigned int Administrator::getAge() const {
	return age;
}
// Converts Admin gender integer to respective string and returns it.
string Administrator::getGender() const {
	return gender;
}
// Returns Admin special status boolean.
bool Administrator::getSpecial() const {
	return special;
}
// Returns Admin access password.
string Administrator::getPass()const {
	return pass;
}
// Returns Admin number of hits.
unsigned int Administrator::getNumberOfHits() const {
	return numberOfHits;
}

// ============================================================
// Change user profile information
// ============================================================
// Sets Admin ID.
void Administrator::setID(unsigned int inputID) {
	ID = inputID;
}
// Sets new username.
void Administrator::setName(string inputName) {
	name = inputName;
}
// Sets new age.
void Administrator::setAge(unsigned int inputAge) {
	age = inputAge;
}
// Sets new gender.
void Administrator::setGender(string inputGender) {
	gender = inputGender;
}
// Sets special status.
void Administrator::setSpecial(bool inputSpecial) {
	special = inputSpecial;
}
// Sets new password.
void Administrator::setPass(string inputPass) {
	pass = inputPass;
}
// Sets new number of hits.
void Administrator::setNumberOfHits(unsigned int iNumberOfHits) {
	numberOfHits = iNumberOfHits;
}

// ============================================================
// Save to File
// ============================================================
// Writes administrator information to "users" csv file. 
// The new administrator information is appended to the end of the file.
void Administrator::saveToFile() const {

	ofstream saveFile;

	// Opens file in output mode and sets initial position to the end of the file.
	saveFile.open("users.csv", ios::out | ios::app);

	// Writes user info to csv file.
	if(saveFile.is_open()) {
		saveFile << ID << "," << name << "," << age << "," << gender << "," << special << "," << pass 
			<< "," << numberOfHits << "\n";
		saveFile.close();
	} else {
		cantOpenFileMsg();
		return;
	}
}
// Rewrites user information to csv file.
void Administrator::rewritesUserToFile() const {

	User userObj;
	// Vector that will hold all the user. Backup purposes.
	vector<User> allUsersVec;

	string line;

	unsigned int newID, newAge, newHits;
	string newName, newGender, newPass;
	bool newSpecial;
	
	string filename = "users.csv";
	ifstream file(filename);
	unsigned int tempID;

	if(file.is_open()) {
		getline(file, line); // Gets fields titles.

		while(getline(file, line)) {

			istringstream source(line);
			source >> tempID;

			// User to change...
			if(tempID == ID) {
				allUsersVec.push_back(User(ID, name, age, gender, special, pass, numberOfHits, true));
			} else {
				newID = convertStrInt(extractInfo(line));
				newName = extractInfo(line);
				newAge = convertStrInt(extractInfo(line));
				newGender = extractInfo(line);
				newSpecial = convertToBool(convertStrInt(extractInfo(line)));
				newPass = extractInfo(line);
				newHits = convertStrInt(extractInfo(line));

				allUsersVec.push_back(User(newID, newName, newAge, newGender, newSpecial, newPass, newHits, true));
			}
		}
		file.close();
		// Removes old file if it exists.
		if(remove(filename.c_str()) != 0) {
			return;
		}
	} else {
		return;
	}

	fstream finalFile("users.csv");
	finalFile.open("users.csv", ios::out);

	if(finalFile.is_open()) {
		if(finalFile.end)
		{
			finalFile << "id,name,age,gender,special,pass,hits\n";
		}
		finalFile.close();
	} else {
		return;
	}

	for(vector<User>::iterator vecPtr = allUsersVec.begin();
		vecPtr != allUsersVec.end(); vecPtr++) {
			vecPtr->saveToFile();
	}

}
// loads Admin from csv file
void Administrator::loadUserFromFile(const string &username) {

	string infoStr = loadFromFile(username);

	ID = convertStrInt(extractInfo(infoStr));
	name = extractInfo(infoStr);
	age = convertStrInt(extractInfo(infoStr));
	gender = extractInfo(infoStr);
	special = convertToBool(convertStrInt(extractInfo(infoStr)));
	pass = extractInfo(infoStr);
	numberOfHits = convertStrInt(extractInfo(infoStr));

}
// Saves musics to csv file.
bool Administrator::saveMusics() const {

	// ============================================================
	// CREATES USER PLAYLIST
	// ============================================================

	// Creates file title.
	stringstream filestream;
	string filename;

	if(ID <= 9) {
		filestream << "playListUser00" << ID << ".csv";
		filename = filestream.str();
	} else if((ID > 9) && (ID < 100)) {
		filestream << "playListUser0" << ID << ".csv";
		filename = filestream.str();
	} else {
		filestream << "playListUser" << ID << ".csv";
		filename = filestream.str();
	}

	// ============================================================
	// Variables
	// ============================================================
	fstream file(filename);
	// ============================================================
	
	file.open(filename, ios::out | ios::app);
	file.close();

	if(remove(filename.c_str()) != 0)
	{
		cout << cantRemoveFileMsg();
		waitForKey();
		return false;
	}

	file.open(filename, ios::out | ios::app);

	// Appends music id to text file.
	if(file.is_open()) {
		file << "MUSIC ID" << endl;
		for(unsigned int i=0; i < playList.size(); i++)
		{
			file << playList[i] << endl;
		}
		file.close();
		return true;
	}

	return false;
}
// Removes music from csv file.
void Administrator::removeMusicFile(unsigned const int musicID) const {

// Creates file title.
	stringstream filestream;
	string filename;

	if(ID <= 9) {
		filestream << "playListUser00" << ID << ".csv";
		filename = filestream.str();
	} else if((ID > 9) && (ID < 100)) {
		filestream << "playListUser0" << ID << ".csv";
		filename = filestream.str();
	} else {
		filestream << "playListUser" << ID << ".csv";
		filename = filestream.str();
	}

	// ============================================================
	// Variables
	// ============================================================
	ifstream playlistFile(filename);
	ofstream copyFile("backup.csv");
	string tempStr, line;
	stringstream iss;
	// ============================================================

	if(!playlistFile || !copyFile) {
		cantOpenFileMsg();
		waitForKey();
		return;
	}

	if(playlistFile.is_open() && copyFile.is_open()) {
		// copy fields titles to new file.
		getline(playlistFile, tempStr);
		copyFile << tempStr << endl;

		while(getline(playlistFile, line)) {
			if(!(convertStrInt(line) == musicID)) {
				copyFile << line << endl;
			}
		}
	
		playlistFile.close();
		copyFile.close();

		// Removes original file.
		if(remove(filename.c_str()) != 0)
			cantRemoveFileMsg();

		// Renames backup file to original file name.
		if(rename("backup.csv", filename.c_str()) != 0)
			cantRenameFileMsg();

	}
}
// Loads user playlist from csv file. Changes user playlist vector. 
void Administrator::loadUserPlaylistFromFile() {

	// ============================================================
	// Variables
	// ============================================================
	ifstream playListFile;
	string filename;

	string line;
	// ============================================================

	// Creates filename.
	filename = createFilenameWithSequence("playListUser", ".csv", 3, ID);

	playListFile.open(filename, ios::in);

	if(playListFile.is_open()) {

		// Discards first line.
		getline(playListFile, line);

		// Gets all ID's.
		while(getline(playListFile, line, '\n')) {
			// Saves ID in vector.
			playList.push_back(convertStrInt(line));
		}

		playListFile.close();
	}

}

// ============================================================
// Playlist management
// ============================================================
// Returns admin playlist size.
size_t Administrator::size() const {
	return playList.size();
}
// Adds a track to playlist.
void Administrator::addTrack(unsigned const int iMusicID) {

	playList.push_back(iMusicID);

	if(!saveMusics())
	{
		cerr << cantSaveFileMsg() << endl;
		waitForKey();
	}

}
// Removes a track from playlist.
void Administrator::remTrack(unsigned const int iMusicID) {
	
	if(playList.empty())
	{
		cout << msg_playlist_empty();
		waitForKey();
		return;
	}
	else
	{
		for (unsigned int i=0; i < playList.size(); i++)
		{
			if(playList[i] == iMusicID)
			{
				playList.erase(playList.begin() + i);
			}
		}
	}

	if(!saveMusics())
	{
		cerr << cantSaveFileMsg() << endl;
	}
}
// Returns true if music is in playlist
bool Administrator::musicExists(unsigned const int iMusicID) {

	for (unsigned int i=0;i < playList.size();i++)
	{
		if(playList[i] == iMusicID) return true;
	}
	return false;
}
// Returns a music ID
unsigned int Administrator::getMusicID(unsigned const int value)
{
	return playList[value];
}

// Rates a music and saves to file.
void Administrator::rateMusic(int rate, int musicID) {

	// ============================================================
	// CREATES USER RATING FILE
	// ============================================================

	// Creates file title.
	stringstream filestream;
	string filename;

	if(ID <= 9) {
		filestream << "ratingsUser00" << ID << ".csv";
		filename = filestream.str();
	} else if((ID > 9) && (ID < 100)) {
		filestream << "ratingsUser0" << ID << ".csv";
		filename = filestream.str();
	} else {
		filestream << "ratingsUser" << ID << ".csv";
		filename = filestream.str();
	}

	// ============================================================
	// Variables
	// ============================================================
	fstream file(filename);
	ofstream backupFile("backup.csv");
	string tempStr;

	unsigned int test_id;
	int rating_status;
	bool found = false;
	// ============================================================

	// Check if file is new. If true writes fields.
	file.open(filename, ios::out);
	if(file.end) {
		file << "MUSIC ID, RATE" << endl;
	}
	file.close();

	// Open file for reading.
	file.open(filename, ios::in);
	if(file.is_open() && backupFile.is_open()) {
		// copy fields titles to new file.
		getline(file, tempStr);
		backupFile << tempStr << endl;

		// Search for song id existence.
		while(file >> test_id) {
			if(test_id == musicID) {
				getline(file, tempStr);
				extractInfo(tempStr);
				rating_status = convertStrInt(extractInfo(tempStr));
				found = true;
				break;
			} else {
				getline(file, tempStr);
				backupFile << test_id << tempStr << endl;
			}
		}

		// Check and Change rating.
		if(found) {
			if(rate == rating_status) {
				// Do nothing because it's already rated.
				backupFile << test_id << "," << tempStr << endl;
			} else {
				// Give new rating to song.
				backupFile << musicID << "," << rate << endl;
			}
			// If music id not found on file appends it to file and gives rating.
		} else {
			backupFile << musicID << "," << rate << endl;
		}

		// Copy remaining lines to file.
		while(getline(file, tempStr)) {
			backupFile << tempStr << endl;
		}

		file.close();
		backupFile.close();

		// Removes original file.
		if(remove(filename.c_str()) != 0)
			cerr << cantRemoveFileMsg() << endl;

		// Renames backup file to original file name.
		if(rename("backup.csv", filename.c_str()) != 0)
			cerr << cantRemoveFileMsg() << endl;

	} else {
		cout << cantOpenFileMsg() << endl;
		waitForKey();
		clearScreen();
	}

}
// Checks if a user has liked or disliked a certain music track
int Administrator::rateExists(int iMusicID) {
	// ============================================================
	// CREATES USER RATING FILE
	// ============================================================

	// Creates file title.
	stringstream filestream;
	string filename;

	if(ID <= 9) {
		filestream << "ratingsUser00" << ID << ".csv";
		filename = filestream.str();
	} else if((ID > 9) && (ID < 100)) {
		filestream << "ratingsUser0" << ID << ".csv";
		filename = filestream.str();
	} else {
		filestream << "ratingsUser" << ID << ".csv";
		filename = filestream.str();
	}

	
	// ============================================================
	// Variables
	// ============================================================
	ifstream file(filename);
	string tempStr;

	unsigned int test_id;
	int rating_status;
	bool found = false;
	// ============================================================

	if(file.is_open()) {
		// copy fields titles to new file.
		getline(file, tempStr);

		// Search for song id existence.
		while(file >> test_id) {
			if(test_id == iMusicID) {
				getline(file, tempStr);
				extractInfo(tempStr);
				rating_status = convertStrInt(extractInfo(tempStr));
				found = true;
				return rating_status;
			} else {
				getline(file, tempStr);
			}
		}
		
		return -2; // Not found.
	}
	else
	{
		return -3; // Can't open file.
	}

}

// Displays a user playList
void Administrator::displayList(unsigned const int line, vector<MusicTrack> &musicList, unsigned const int &page_number)
{
	if(playList.empty())
	{
		return;
	}
	else
	{
		for (unsigned int i=0; i < playList.size();i++)
		{
			if(i == line)
			{
				changeTextColor("BLACK");
			}
			else
			{
				changeTextColor("WHITE");
			}

			for (unsigned int j = (page_number * 10); ((j < musicList.size()) && (j - (page_number * 10) < 10)); j++)
			{
				if((musicList[j].getID()) == playList[i])
				{
					musicList[j].display(false);
					cout << endl;
				}
			}
		}
	}
	changeTextColor("WHITE");
}
// Displays a single music in the playList
void Administrator::displayTrack(unsigned const int pos, vector<MusicTrack> &musicList)
{
	for (unsigned int j=0;j < musicList.size(); j++)
			{
				if((musicList[j].getID()) == playList[pos])
				{
					musicList[j].displayMusic();
				}
			}
}

// Checks if user has hits on his/her playlist. If it founds an hit, it increments the number of hits.
void Administrator::checkForHits(vector<MusicTrack> & playlistOfTheDay) {
	MusicTrack musicObj;
	bool found = false;
	bool alreadyIncremented = false;

	vector<int> incrementedMusics;

	// Cycles through playlist of the day.
	for(vector<MusicTrack>::iterator playDayPtr = playlistOfTheDay.begin(); 
		playDayPtr != playlistOfTheDay.end(); playDayPtr++)
	{
		alreadyIncremented = false;
			// Cycles through user's playlist.
			for(vector<unsigned int>::iterator playUserPtr = playList.begin();
				playUserPtr != playList.end(); playUserPtr++) 
			{
					musicObj = *playDayPtr;
					// Increments number of hits if musics ID's correspond.
					if((musicObj.getID()) == *playUserPtr) {
						for(vector<int>::iterator incrementedPtr = incrementedMusics.begin(); incrementedPtr != incrementedMusics.end();
							incrementedPtr++) 
						{
							if(*incrementedPtr == *playUserPtr) {
								alreadyIncremented = true;
							}
						}
						if(!alreadyIncremented) {
							incrementedMusics.push_back(musicObj.getID());
							incrementNumberOfHitsByOne();
							found = true;
							alreadyIncremented = false;
						}
					}
			}
	}

	if(found) {
		rewritesUserToFile();
	}
}
// Increments by one the number of hits on user's playlist.
void Administrator::incrementNumberOfHitsByOne() {
	numberOfHits++;
}

// ===================================================
// Admin Music Tracks Management
// ===================================================
// Adds music track to RadioStationMusics.csv
void Administrator::addMusicTrack( string title, string author, string album, string musicGenre, unsigned short int year, unsigned int likes, unsigned int dislikes)
{
	// ============================================================
	// Variables
	// ============================================================
	ofstream saveFile;

	// Opens file in output mode and sets initial position to the end of the file.
	saveFile.open("radioStationMusics.csv", ios::out | ios::app);

	// Writes user info to csv file.
	if(saveFile.is_open()) {
		saveFile << (searchLastID("radioStationMusics.csv") + 1) << "," << title << "," << author << "," << album << "," << musicGenre << "," << year << "," << likes << "," << dislikes << "\n";
		saveFile.close();
	} else {
		cantOpenFileMsg();
		return;
	}
}

// ============================================================
// Destructor
// ============================================================
Administrator::~Administrator()
{
	//clear();
};