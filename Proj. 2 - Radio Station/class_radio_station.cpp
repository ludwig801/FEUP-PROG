/* ==========================================
TITLE: CLASS_RADIO_STATION					|
											|
AUTHORS: Kevin Amorim - ei12057				|
		 Luís Magalhães - ei12054			|
											|
GROUP: T2G02								|
											|
DATE: 2013/05/27							|
											|
PURPOSE: Radio Station object. Holds		|
all radio station information and			|
functions.									|
											|
PARAMETERS:	No parameters needed.			|
											|
											|
											|
   -->  DEVELOPED WITH WINDOWS 8.  <--		|
============================================*/

// ============================================================
// INCLUDES
// ============================================================
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "class_radio_station.h"
#include "class_musictrack.h"
#include "aux_functions.h"
#include "strings.h"
// ============================================================

// ============================================================
// RADIO STATION
// ============================================================
// ============================================================
// Radio Station Constructor
// ============================================================
// Default constructor.
RadioStation::RadioStation() {
	radioStationName = "default";
	numberOfUsers = 0;
}
// Custom constructor.
RadioStation::RadioStation(const std::string &newRadioStationName) {
	radioStationName = newRadioStationName;
	numberOfUsers = 0;

	saveRadioStationToFile();

}
// ============================================================
// ============================================================
// Show Radio Station Information
// ============================================================
// Returns string with radio station name.
std::string RadioStation::getRadioStationName() const {
	return radioStationName;
}
// Returns vector with all radio station musics.
std::vector <MusicTrack> &RadioStation::getAllMusicsList() {
	return allMusicsList;
}
// Returns music from all musics list vector. If position exceeds vector size, returns last element.
MusicTrack &RadioStation::getMusicFromAllMusicsList(const unsigned int &musicPosition) {
	if(allMusicsList.empty()) {
		cerr << msg_playlist_empty() << endl;
		throw(0);
	}

	if(musicPosition < allMusicsList.size()) {
		return allMusicsList[musicPosition];
	} else {
		cerr << vectorSizeExceededMsg() << endl;
		return allMusicsList[allMusicsList.size()-1];
	}
}
// Returns vector with the playlist of the day musics.
std::vector <MusicTrack> &RadioStation::getPlaylistOfTheDay() {
	return playlistOfTheDay;
}
// Returns music from playlist of the day vector. If position exceeds vector size, returns last element.
MusicTrack &RadioStation::getMusicFromPlaylistOfTheDay(const unsigned int &musicPosition) {
	if(playlistOfTheDay.empty()) {
		cerr << msg_playlist_empty() << endl;
		throw(0);
	}

	if(musicPosition < playlistOfTheDay.size()) {
		return playlistOfTheDay[musicPosition];
	} else {
		cerr << vectorSizeExceededMsg() << endl;
		return playlistOfTheDay[allMusicsList.size()-1];
	}
}
// Returns number of user available on the radio station.
unsigned int RadioStation::getNumberOfUsers() const {
	return numberOfUsers;
}
// ============================================================
// ============================================================
// Change Radio Station Information
// ============================================================
// Changes radio station name. Receives string with new radio station name by reference.
void RadioStation::setRadioName(const std::string &newRadioStationName) {
	radioStationName = newRadioStationName;
}
// Increments number of users available on the radio station.
void RadioStation::incrementNumberOfUsers() {
	numberOfUsers++;
	saveRadioStationToFile();
}
// Adds a new instance of the class Music Track to the radio station music list vector.
void RadioStation::addNewMusicToRadioStation() {

	// ====================================
	// VARIABLES
	// ====================================
	enum {
		TITLE,
		AUTHOR,
		ALBUM,
		GENRE,
		YEAR
	};

	string inputTitle, inputAuthor, inputAlbum, inputGenre;
	char temp[100];
	unsigned short int inputYear;

	unsigned int option = 0;
	bool done = false;
	// ====================================

	clearScreen();

	do {
		clearScreen();
		cin.clear();

		switch(option) {
		case TITLE:
			cout << "Title: ";
			cin.getline(temp,100);
			inputTitle = temp;
			if(inputTitle == "quit") return;
			break;
		case AUTHOR:
			cout << "Author: ";
			cin.getline(temp,100);
			inputAuthor = temp;
			if(inputAuthor == "quit") return;
			break;
		case ALBUM:
			cout << "Album: ";
			cin.getline(temp,100);
			inputAlbum = temp;
			if(inputAlbum == "quit") return;
			break;
		case GENRE:
			cout << "Genre: ";
			cin.getline(temp,100);
			inputGenre = temp;
			if(inputGenre == "quit") return;
			break;
		case YEAR:
			cout << "Release year: ";
			cin >> inputYear;
			if(!cin.fail()) {
				if(inputYear == 0) return;
				done = true;
			}
			break;
		default:
			break;
		}

		if(!cin.fail()) {
			option++;
		}
		else
		{
			cout << "   Error: Invalid input! Please, try again.\n";
			cin.clear();
			cin.ignore();
		}

	} while(cin.fail() || (!done));

	// Clears input buffer.
	while (cin.get() != '\n');
	// ============================================================
	// ============================================================
	// Saves Music Track to vector
	// ============================================================
	// Creates a new instance of MusicTrack with the information given.
	allMusicsList.push_back(MusicTrack(inputTitle, inputAuthor, inputAlbum, inputGenre, inputYear));
	//Saves the new music to radioStationMusics.csv.
	allMusicsList[allMusicsList.size()-1].saveToFile();
	// ============================================================
	// Saves all radio station musics to file.
	saveRadioStationMusicsListToFile();

}
// Removes music from radio station music list.
void RadioStation::removeMusicFromRadioStation(const unsigned int &musicID) {
	for(unsigned int music = 0; music < allMusicsList.size(); music++) {
		if(allMusicsList[music].getID() == musicID) {
			allMusicsList.erase(allMusicsList.begin() + music);
		}
	}

	decrementMusicTracksID(musicID);

	saveRadioStationMusicsListToFile();
}
// Resets all like(dislikes count
void RadioStation::resetAllLikesAndDislikes()
{
	for(unsigned int music = 0; music < allMusicsList.size(); music++) {
		allMusicsList[music].setLikes(0,false,false);
		allMusicsList[music].setDislikes(0,false,false);
	}
}
// Deletes all rating files (is invoked when all likes/dislikes are reseted)
void RadioStation::deleteAllRatings() {

	std::string filename;
	std::string line;

	for(unsigned int tempID = 0; tempID < numberOfUsers; tempID++)
	{
		filename = createFilenameWithSequence("ratingsUser", ".csv", 3, tempID);

		fstream fileSave(filename);

		// Checks if playlist file already exists. If so, removes it.
		if(fileSave.good())
		{
			fileSave.close();
			if(remove(filename.c_str()) != 0)
			{
				cout << cantRemoveFileMsg() << endl;
				waitForKey();
			}
		}
		else
		{
			return;
		}
	}

}
// Edit a cetain music track's information
void RadioStation::editMusicTrack(const int &musicPos)
{
	// ====================================
	// VARIABLES
	// ====================================
	enum {
		TITLE,
		AUTHOR,
		ALBUM,
		GENRE,
		YEAR
	};

	string inputTitle, inputAuthor, inputAlbum, inputGenre;
	char temp[100];
	unsigned short int inputYear;

	unsigned int option = 0;
	bool done = false;

	do {
		clearScreen();
		cin.clear();

		switch(option)
		{
		case TITLE:
			cout << "\n simply press [Enter] if you want it to remain unchanged \n\n";
			cout << "Title: ";
			cin.getline(temp,100);
			inputTitle = temp;
			break;
		case AUTHOR:
			cout << "\n simply press [Enter] if you want it to remain unchanged \n\n";
			cout << "Author: ";
			cin.getline(temp,100);
			inputAuthor = temp;
			break;
		case ALBUM:
			cout << "\n simply press [Enter] if you want it to remain unchanged \n\n";
			cout << "Album: ";
			cin.getline(temp,100);
			inputAlbum = temp;
			break;
		case GENRE:
			cout << "\n simply press [Enter] if you want it to remain unchanged \n\n";
			cout << "Genre: ";
			cin.getline(temp,100);
			inputGenre = temp;
			break;
		case YEAR:
			cout << "\n simply type [0] if you want it to remain unchanged \n\n";
			cout << "Release year: ";
			cin >> inputYear;
			if(!cin.fail()) {
				done = true;
			}
			break;
		default:
			option++;
			break;
		}

		if(!cin.fail()) {
			option++;
		} else
		{
			cin.clear();
			cin.ignore();
		}

	} while(cin.fail() || (!done));

	// Creates a new instance of MusicTrack with the information given.
	if(inputTitle.size() > 0)
		allMusicsList[musicPos].setTitle(inputTitle);
	if(inputAuthor.size() > 0)
		allMusicsList[musicPos].setAuthor(inputAuthor);
	if(inputAlbum.size() > 0)
		allMusicsList[musicPos].setAlbum(inputAlbum);
	if(inputGenre.size() > 0)
		allMusicsList[musicPos].setGenre(inputGenre);
	if(inputYear > 0)
		allMusicsList[musicPos].setYear(inputYear);
	//Saves the new music to radioStationMusics.csv.
	allMusicsList[allMusicsList.size()-1].saveToFile();
	// ============================================================
	// Saves all radio station musics to file.
	clearScreen();
	saveRadioStationMusicsListToFile();
}
// Decrements music tracks ID's.
void RadioStation::decrementMusicTracksID(const unsigned int begin) {
	// Decrements ID's on radio station musics list. Starting with the removed music.
	for(unsigned int music = begin; music < allMusicsList.size(); music++) {
		allMusicsList[music].setID(allMusicsList[music].getID() - 1);
	}
		// Decrements music ID's from users playlist, starting with the removed music.
		User user1; 
		for(unsigned int userID = 0; userID < numberOfUsers; userID++) {
				user1.setID(userID); // Changes class instance ID.
				user1.loadUserPlaylistFromFile(); // Loads corresponding playlist.
				user1.remTrack(begin);	// Removes removed music from user playlist, if it exists.

				// Decrements ID's.
				for(int userMusicID = begin; userMusicID < (searchLastID("radioStationMusics.csv") + 1); userMusicID++) {
						user1.decrementMusicID(userMusicID);
				}
				user1.decrementRatingsID(begin);
				user1.saveMusics(); // Saves new playlist.
		}
}
// Reset (in the ratings file) the rating atributed to a certain music by the user
void RadioStation::resetRatingsFromMusic(unsigned const int musicID) {
	
	std::string filename;
	std::string line;

	for(unsigned int tempID = 0; tempID < numberOfUsers; tempID++)
	{
		filename = createFilenameWithSequence("ratingsUser", ".csv", 3, tempID);
		unsigned int idCounter = 0;

		std::vector < std::vector <int> > ratingsVec;
		vector<int> row;

		ifstream fileLoad(filename);
		fstream fileSave(filename);

		if(fileLoad.is_open()) {

			getline(fileLoad, line);
			while(getline(fileLoad, line)) {

				ratingsVec.push_back(row);
				ratingsVec[idCounter].push_back(convertStrInt(extractInfo(line)));
				ratingsVec[idCounter].push_back(convertStrInt(extractInfo(line)));

				if(ratingsVec[idCounter][0] == musicID) {
					ratingsVec.erase(ratingsVec.begin()+idCounter);
					idCounter--;
				}

				idCounter++;
			}
			fileLoad.close();
		}
		else 
		{
			return;
		}

		// ============================================================
		// ============== Saves vector to file ========================
		// ============================================================

		// Checks if playlist file already exists. If so, removes it.
		if(fileSave.good()) {
			fileSave.close();
			if(remove(filename.c_str()) != 0)
			{
				cout << cantSaveFileMsg() << endl;
				waitForKey();
			}
		}

		// Creates and opens new playlist file and adds fields.
		fileSave.open(filename, ios::out);
		if(fileSave.is_open())
		{
			if(fileSave.end) {
				fileSave << "MUSIC ID, RATE" << endl;
			}

			// Appends music id to text file.
			for(unsigned int i=0; i < ratingsVec.size(); i++)
			{
				fileSave << ratingsVec[i][0] << "," << ratingsVec[i][1] << endl;
			}

			fileSave.close();
		}
		else
		{
			return;
		}
	}

}
// Randomly generates a new playlist of the day.
void RadioStation::generatePlaylistOfTheDay(const unsigned int numberOfMusics) {
	srand((int)time(NULL));
	int MAXIMUM = searchLastID("radioStationMusics.csv") + 1;
	int musicToCopy;

	if(getAllMusicsList().size() != 0)
	{

		playlistOfTheDay.clear();

		for(unsigned int music = 0; music < numberOfMusics; music++) {
			do
			{
				musicToCopy = (rand() % MAXIMUM);
			} while(getMusicFromAllMusicsList(musicToCopy).getAvailable() == 0);
			playlistOfTheDay.push_back(allMusicsList[musicToCopy]);
		}
		checkForHitsOnAllUsers();
	}
	else
	{
		clearScreen();
		cout << msg_vector_empty();
		waitForKey();
	}

	savePlaylistOfTheDayToFile();
}
// Checks for users that have a hit on their playlist.
void RadioStation::checkForHitsOnAllUsers() {
	User userObj;
	// Vector that will hold all the user. Backup purposes.
	vector<User> allUsersVec;

	string line;

	unsigned int newID, newAge, newHits;
	string newName, newGender, newPass;
	bool newSpecial;
	
	string filename = "users.csv";
	ifstream file(filename);

	if(file.is_open()) {
		getline(file, line); // Gets fields titles.

		while(getline(file, line)) {

			newID = convertStrInt(extractInfo(line));
			newName = extractInfo(line);
			newAge = convertStrInt(extractInfo(line));
			newGender = extractInfo(line);
			newSpecial = convertToBool(convertStrInt(extractInfo(line)));
			newPass = extractInfo(line);
			newHits = convertStrInt(extractInfo(line));

			allUsersVec.push_back(User(newID, newName, newAge, newGender, newSpecial, newPass, newHits, true));
		}
		file.close();
	} else {
		return;
	}

	for(vector<User>::iterator vecPtr = allUsersVec.begin(); vecPtr != allUsersVec.end(); vecPtr++) {
		vecPtr->checkForHits(playlistOfTheDay);
	}
}
// Resets all hits on all users.
void RadioStation::resetAllHitsOnAllUsers() {
	std::vector <User> allUsersVec = loadAllUsersToVector();

	for(vector<User>::iterator vecPtr = allUsersVec.begin(); vecPtr != allUsersVec.end(); vecPtr++) {
		vecPtr->setNumberOfHits(0);
		vecPtr->rewritesUserToFile();
	}

}
// ============================================================
// ===================================================
// PRIZE
// ===================================================
// Prints all users in descending order (best number of hits to worst number of hits). Prints also the winner.
// Uses all below function (from PRIZE category)!
void RadioStation::prizeWinner() {

	vector <User> allUsersVec = loadAllUsersToVector();
	sortAllUsersByHits(allUsersVec);

	clearScreen();
	
	if(!allUsersVec.size() == 0) {

		cout << setw(8) << "Name"
			 << setw(8) << "Age"
			 << setw(8) << "Gender"
			 << setw(16) << "Number of Hits"
			 << endl;

		if(allUsersVec.size() > 10) {
			for(vector<User>::iterator vPtr = allUsersVec.begin(); vPtr != allUsersVec.begin()+10; vPtr++) {
				vPtr->displayUserInformation();
			}

		} else {

			for(vector<User>::iterator vPtr = allUsersVec.begin(); vPtr != allUsersVec.end(); vPtr++) {
				vPtr->displayUserInformation();
			}
		}

		cout << "\n\n\n\n The winner is --> " << userWithMostNumberOfHits(allUsersVec).getName() << endl << endl;
		waitForKey();

	}

}
// Returns vector with all users information.
std::vector<User> RadioStation::loadAllUsersToVector() {

	std::vector <User> allUsersVec;

	std::string filename = "users.csv";
	ifstream file(filename);

	std::string tempStr;

	// Temporary user information.
	unsigned int newID, newAge, newHits;
	std::string newName, newGender, newPass;
	bool newSpecial;

	if(file.is_open()) {
		getline(file, tempStr); // Get first line (fields titles).

		while(getline(file, tempStr)) {
			// Gets user information from file.
			newID = convertStrInt(extractInfo(tempStr));
			newName = extractInfo(tempStr);
			newAge = convertStrInt(extractInfo(tempStr));
			newGender = extractInfo(tempStr);
			newSpecial = convertToBool(convertStrInt(extractInfo(tempStr)));
			newPass = extractInfo(tempStr);
			newHits = convertStrInt(extractInfo(tempStr));
			// Stores user information to vector.
			allUsersVec.push_back(User(newID, newName, newAge, newGender, newSpecial, newPass, newHits, true));
		}

		file.close();
	}

	return allUsersVec;
}
// Sorts all users by number of hits, on all users vector.
void RadioStation::sortAllUsersByHits(std::vector <User> &allUsersVec) {
		std::sort(allUsersVec.begin(), allUsersVec.end(), sortingByHits);
}
// Returns the first user of all users vector. The user with most number of hits.
User RadioStation::userWithMostNumberOfHits(const std::vector <User> &allUsersVec) {
	return allUsersVec[0];
}
// ===================================================
// ============================================================
// Text Files Handling
// ============================================================
// Saves radio information to csv file.
void RadioStation::saveRadioStationToFile() const {
	// ============================================================
	// Variables
	// ============================================================
	std::string filename = "radioStationInformation.csv";
	ofstream file(filename);
	// ============================================================

	if(file.is_open()) {
		file << "Radio Station name:" << std::endl << radioStationName << std::endl;
		file << "Number of Users:" << std::endl << numberOfUsers;
	}

}
// Saves playlist of the day to csv file.
void RadioStation::savePlaylistOfTheDayToFile() {
	std::string filename = "playlistOfTheDay.csv";

	remove(filename.c_str());

	fstream file(filename); 

	file.open(filename, ios::out);

	file << "id,title,author,album,genre,year,likes,dislikes,available\n";

	for(vector<MusicTrack>::iterator vPtr = playlistOfTheDay.begin(); 
		vPtr != playlistOfTheDay.end(); vPtr++) {

			file << vPtr->getID() << delimiter() << vPtr->getTitle() << delimiter() << vPtr->getAlbum() 
				<< delimiter() << vPtr->getMusicGenre() << delimiter() << vPtr->getYear() 
				<< delimiter() << vPtr->getLikes() << delimiter() << vPtr->getDislikes()
				<< delimiter() << vPtr->getAvailable() << std::endl;

	}

}
// Saves Radio Station Music List to csv file. Returns true if successfully saved.
void RadioStation::saveRadioStationMusicsListToFile() const {
	// ============================================================
	// Variables
	// ============================================================
	std::string filename = "radioStationMusics.csv";
	fstream file(filename);
	// ============================================================

	// Checks if music list file already exists. If so, removes it.
	if(file.good()) {

		file.close();

		// Removes old file if it exists.
		if(remove(filename.c_str()) != 0)
		{
			return;
		}
	}

	// Creates and opens new playlist file and adds fields.
	file.open(filename, ios::out);

	if(file.is_open()) {
		
		// Verifies if file is really empty and writes to first line the name of the each field.
		if(file.end) {
			file << "id,title,author,album,genre,year,likes,dislikes,available" << std::endl;
		}

		// Appends musics to file.
		for(unsigned int music = 0; music < allMusicsList.size(); music++)
		{
			// Writes all music information to file.
			file << allMusicsList[music].getID() << "," << allMusicsList[music].getTitle() << "," 
				<< allMusicsList[music].getAuthor() << "," << allMusicsList[music].getAlbum() << ","
				<< allMusicsList[music].getMusicGenre() << "," << allMusicsList[music].getYear() << ","
				<< allMusicsList[music].getLikes() << "," << allMusicsList[music].getDislikes() << ","
				<< allMusicsList[music].getAvailable() << std::endl;
		}

		file.close();

	} 
}
// Loads radio information from csv file.
void RadioStation::loadRadioStationFromFile() {
	// ============================================================
	// Variables
	// ============================================================
	std::string filename = "radioStationInformation.csv";
	ifstream file(filename);
	std::string line;
	// ============================================================

	if(file.is_open()) {

		getline(file, line);
		getline(file, line); 

		radioStationName = line;

		getline(file, line);
		getline(file, line);

		numberOfUsers = convertStrInt(line);
	} 
}
// Loads Radio Station Music List from csv file. Returns true if successfully loaded.
void RadioStation::loadRadioStationMusicsListFromFile() {
	// ============================================================
	// Variables
	// ============================================================
	std::string filename = "radioStationMusics.csv";
	ifstream file(filename);
	
	std::string line;
	std::string delimiter = ",";
	size_t delimiter_pos = 0;
	std::vector <string> tokens;
	unsigned int pos;
	// ============================================================

	if(file.is_open()) {
		// Discards first line.
		getline(file, line);
		
		// Gets musics.
		while(getline(file, line)) {
			while((pos = line.find(delimiter)) != std::string::npos) {
				tokens.push_back(line.substr(0, pos));
				//std::cout << line.substr(0,pos) << std::endl;
				line.erase(0, pos + delimiter.length());
			}
			// Saves last token.
			tokens.push_back(line);
			// Saves song to vector.
			allMusicsList.push_back(MusicTrack(convertStrInt(tokens[0]), tokens[1], tokens[2], tokens[3], tokens[4],
				convertStrInt(tokens[5]), convertStrInt(tokens[6]), convertStrInt(tokens[7]), convertToBool(convertStrInt(tokens[8]))));
			// Clear tokens vector.
			tokens.clear();
			// Clear pos variable.
			pos = 0;
		}

		file.close();

	}
}
// Loads playlist of the day from csv file.
void RadioStation::loadPlaylistOfTheDayFromFile() {

	std::string newTitle, newAuthor, newAlbum, newGenre; 
	unsigned int newID, newYear, newLikes, newDislikes;
	bool newSpecial;

	std::string filename = "playlistOfTheDay.csv";
	std::string line;
	ifstream file(filename);

	if(file.is_open()) {

		playlistOfTheDay.clear();

		getline(file, line); // Gets fields titles.

		while(getline(file, line)) {

			newID = convertStrInt(extractInfo(line));
			newTitle = extractInfo(line);
			newAuthor = extractInfo(line);
			newAlbum = extractInfo(line);
			newGenre = extractInfo(line);
			newYear = convertStrInt(extractInfo(line));
			newLikes = convertStrInt(extractInfo(line));
			newDislikes = convertStrInt(extractInfo(line));
			newSpecial = convertToBool(convertStrInt(extractInfo(line)));

			playlistOfTheDay.push_back(MusicTrack(newID, newTitle, newAuthor, newAlbum, newGenre, newYear, 
				newLikes, newDislikes, newSpecial));
		}
		file.close();
	} else {
		return;
	}
	
}
// ============================================================