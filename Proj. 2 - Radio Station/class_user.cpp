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
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

#include "class_user.h"
#include "class_musictrack.h"
#include "class_radio_station.h"
#include "aux_functions.h"
#include "strings.h"

using namespace std;
// ============================================================
// ============================================================
// USER
// ============================================================
// ============================================================
// User Constructor
// ============================================================
// Default constructor
User::User() {
	ID = 0;
	name = "user";
	age = 0;
	gender = "EMPTY";
	special = false;
	numberOfHits = 0;
}
// Creates new user.
User::User(unsigned int iID, string iName, unsigned int iAge, string iGender, bool iSpecial, 
	string iPass, unsigned int iNumberOfHits) {

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

User::User(unsigned int iID, string iName, unsigned int iAge, string iGender, bool iSpecial, 
	string iPass, unsigned int iNumberOfHits, bool temp) {

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
// ============================================================
// Shows user profile information
// ============================================================
// Return User ID.
unsigned int User::getID() {
	return ID;
}
// Returns User username string.
string User::getName(){
	return name;
}
// Returns User age integer.
unsigned int User::getAge(){
	return age;
}
// Converts User gender integer to respective string and returns it.
string User::getGender(){
	return gender;
}
// Returns if user has special status or not.
bool User::getSpecial(){
	return special;
}
// Returns user access password.
string User::getPass(){
	return pass;
}
// Returns user number of hits.
unsigned int User::getNumberOfHits() const {
	return numberOfHits;
}
// Displays all user information.
void User::displayUserInformation() const {
	cout << endl;
	if(name.size() > 8)
		cout << setw(8) << name.substr(0,7) + ".";
	else
		cout << setw(8) << name;

	cout << setw(8) << age;

	if(gender.size() > 8)
		cout << setw(8) << gender.substr(0,7) + ".";
	else
		cout << setw(8) << gender;

	cout << setw(16) << numberOfHits;
}
// ============================================================
// ============================================================
// Change user profile information
// ============================================================
// Sets user ID.
void User::setID(unsigned int inputID) {
	ID = inputID;
}
// Sets new username.
void User::setName(string inputName) {
	name = inputName;
}
// Sets new age.
void User::setAge(unsigned int inputAge) {
	age = inputAge;
}
// Sets new gender.
void User::setGender(string inputGender) {
	gender = inputGender;
}
// Sets new special status.
void User::setSpecial(bool inputSpecial) {
	special = inputSpecial;
}
// Sets new password.
void User::setPass(string inputPass) {
	pass = inputPass;
}
// Sets new number of hits.
void User::setNumberOfHits(unsigned int iNumberOfHits) {
	numberOfHits = iNumberOfHits;
}
// ============================================================
// ============================================================
// Files Handling
// ============================================================
// Writes user information to csv file.
void User::saveToFile(){

	// ============================================================
	// Variables
	// ============================================================
	ofstream saveFile;
	// ============================================================

	// Opens file in output mode and sets initial position to the end of the file.
	saveFile.open("users.csv", ios::out | ios::app);

	// Writes user info to csv file.
	if(saveFile.is_open()) {
		saveFile << ID << "," << name << "," << age << "," << gender << "," 
			<< special << "," << pass << "," << numberOfHits << "\n";
		saveFile.close();
	} else {
		cantOpenFileMsg();
		return;
	}
}
// Rewrites user information to csv file.
void User::rewritesUserToFile() const {

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
// Loads user information from csv file.
void User::loadUserFromFile(const string &username) {
	string infoStr = loadFromFile(username);

	ID = convertStrInt(extractInfo(infoStr));
	name = extractInfo(infoStr);
	age = convertStrInt(extractInfo(infoStr));
	gender = extractInfo(infoStr);
	special = convertToBool(convertStrInt(extractInfo(infoStr)));
	pass = extractInfo(infoStr);
	numberOfHits = convertStrInt(extractInfo(infoStr));

}
// Saves user playlist to csv file.
bool User::saveMusics() const {

	// ============================================================
	// Variables
	// ============================================================
	// Creates file title.
	string filename = createFilenameWithSequence("playListUser", ".csv", 3, ID);
	fstream file(filename);
	// ============================================================
	
	// Checks if playlist file already exists. If so, removes it.
	if(file.good()) {
		file.close();
		if(remove(filename.c_str()) != 0)
		{
			cantRemoveFileMsg();
			waitForKey();
			return false;
		}
	}

	// Creates and opens new playlist file and adds fields.
	file.open(filename, ios::out);
	if(file.is_open()) {
		if(file.end) {
			file << "MUSIC ID" << endl;
		}

		// Appends music id to text file.
		for(unsigned int i=0; i < playList.size(); i++)
		{
			file << playList[i] << endl;
		}

		file.close();
		return true;
	}
	return false;
}
// Saves user rating to file.
void User::saveRatingsToFile(std::vector< vector<int> > &ratingsVec) {
	// ============================================================
	// Variables
	// ============================================================
	// Creates file title.
	string filename = createFilenameWithSequence("ratingsUser", ".csv", 3, ID);
	fstream file(filename);
	// ============================================================
	
	// Checks if playlist file already exists. If so, removes it.
	if(file.good()) {
		file.close();
		if(remove(filename.c_str()) != 0)
		{
			cantRemoveFileMsg();
			waitForKey();
		}
	}

	// Creates and opens new playlist file and adds fields.
	file.open(filename, ios::out);
	if(file.is_open()) {
		if(file.end) {
			file << "MUSIC ID, RATE" << endl;
		}

		// Appends music id to text file.
		for(unsigned int i=0; i < ratingsVec.size(); i++)
		{
			file << ratingsVec[i][0] << "," << ratingsVec[i][1] << endl;
		}

		file.close();
	} else {
		return;
	}
}
// Loads user playlist from csv file. Changes user playlist vector. 
// No parameters required. Doesn't returns anything
void User::loadUserPlaylistFromFile() {

	// ============================================================
	// Variables
	// ============================================================
	ifstream playListFile;
	string filename;

	string line;
	// ============================================================

	// Clear playlist.
	playList.clear();

	// Creates filename.
	filename = createFilenameWithSequence("playListUser", ".csv", 3, ID);

	playListFile.open(filename, ios::in);

	if(!playListFile) {
		cantOpenFileMsg();
		return;
	}

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
// ============================================================
// Playlist Management
// ============================================================
// Returns list size.
size_t User::size() const {
	return playList.size();
}
// Adds a track to playlist.
void User::addTrack(unsigned const int iMusicID) {

	playList.push_back(iMusicID);

	if(!saveMusics())
	{
		cerr << "couldn't save... " << endl;
	}

}
// Removes a track from playlist.
void User::remTrack(unsigned const int iMusicID) {
	
	if(playList.empty())
	{
		return;
	}
	else
	{
		for (unsigned int i=0;i < playList.size();i++)
		{
			if(playList[i] == iMusicID)
			{
				playList.erase(playList.begin() + i);
			}
		}
	}

	if(!saveMusics())
	{
		cerr << "couldn't save... " << endl;
	}
}
// Returns true if music is in playlist
bool User::musicExists(unsigned const int iMusicID) {
	
	for (unsigned int i=0;i < playList.size();i++)
	{
		if(playList[i] == iMusicID) return true;
	}

	return false;
}
// Returns a music ID
unsigned int User::getMusicID(unsigned const int value)
{
	return playList[value];
}
// Rates a music and saves to file.
void User::rateMusic(int rate, int musicID) {

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
				cout << "You've already given that rating to that song.\n";
				backupFile << test_id << "," << tempStr << endl;
				waitForKey();
				clearScreen();
			} else {
				// Give new rating to song.
				backupFile << musicID << "," << rate << endl;
				cout << "Thanks for rating!\n";
				waitForKey();
				clearScreen();
			}
			// If music id not found on file appends it to file and gives rating.
		} else {
			backupFile << musicID << "," << rate << endl;
			cout << "Thanks for rating!\n";
			waitForKey();
			clearScreen();
		}

		// Copy remaining lines to file.
		while(getline(file, tempStr)) {
			backupFile << tempStr << endl;
		}

		file.close();
		backupFile.close();

		// Removes original file.
		if(remove(filename.c_str()) != 0)
			cerr << "Error deleting file!" << endl;

		// Renames backup file to original file name.
		if(rename("backup.csv", filename.c_str()) != 0)
			cerr << "Error renaming file!" << endl;

	} else {
		cout << "Can't open file!\n";
		waitForKey();
		clearScreen();
	}

}
// Checks if a user has liked or disliked a certain music track
int User::rateExists(int iMusicID) {
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
void User::displayList(unsigned const int line, vector<MusicTrack> &musicList, unsigned const int &page_number)
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
void User::displayTrack(unsigned const int pos, vector<MusicTrack> &musicList)
{
	for (unsigned int j=0;j < musicList.size(); j++)
			{
				if((musicList[j].getID()) == playList[pos])
				{
					musicList[j].displayMusic();
				}
			}
}
// Decrements user music ID's from playlist.
// Checks if user has hits on his/her playlist. If it founds an hit, it increments the number of hits.
void User::checkForHits(vector<MusicTrack> & playlistOfTheDay) {
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
void User::incrementNumberOfHitsByOne() {
	numberOfHits++;
}
// ============================================================
// ============================================================
// Ratings Management
// ============================================================
void User::decrementMusicID(unsigned const int musicID) {
	for(unsigned int music = 0; music < playList.size(); music++) {
		if(playList[music] == musicID) {
			playList[music]--;
		}
	}
}
// Decrements user music ID's from ratings file.
void User::decrementRatingsID(unsigned const int musicID) {
	std::string filename = createFilenameWithSequence("ratingsUser", ".csv", 3, ID);
	std::string line;
	unsigned int idCounter = 0;

	std::vector < std::vector <int> > ratingsVec;
	vector<int> row;

	ifstream file(filename);
	
	if(file.is_open()) {
		getline(file, line);
		while(getline(file, line)) {
			ratingsVec.push_back(row);
			ratingsVec[idCounter].push_back(convertStrInt(extractInfo(line)));
			ratingsVec[idCounter].push_back(convertStrInt(extractInfo(line)));

			if(ratingsVec[idCounter][0] == musicID) {
				ratingsVec.erase(ratingsVec.begin()+idCounter);
				idCounter--;
			} else if(ratingsVec[idCounter][0] > ((int) musicID)) {
				ratingsVec[idCounter][0]--;
			}

			idCounter++;
		}
		file.close();
		saveRatingsToFile(ratingsVec);
	} else {
		return;
	}

}
// ============================================================
// ============================================================
// Destructor
// ============================================================
User::~User()
{
};
