#ifndef CLASS_RADIO_STATION_H_INCLUDED
#define CLASS_RADIO_STATION_H_INCLUDED

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
#include <string>
#include <vector>

#include "class_musictrack.h"
#include "class_user.h"
#include "class_administrator.h"
// ============================================================

class RadioStation {
private:
	std::string radioStationName;
	std::vector <MusicTrack> allMusicsList;
	std::vector <MusicTrack> playlistOfTheDay;
	unsigned int numberOfUsers;
	
	struct sortingStruct {
		bool operator() (User user1, User user2) { return (user1.getNumberOfHits() > user2.getNumberOfHits()); }
	} sortingByHits;

public:
	// ===================================================
	// Constructors
	// ===================================================
	RadioStation(); // Default.
	RadioStation(const std::string &newRadioStationName);
	// ===================================================
	// ===================================================
	// Get radio informations
	// ===================================================
	// Returns string with radio station name.
	std::string getRadioStationName() const;
	// Returns vector with all radio station musics.
	std::vector <MusicTrack> &getAllMusicsList();
	// Returns vector with the playlist of the day musics.
	std::vector <MusicTrack> &getPlaylistOfTheDay();
	// Returns music from all musics list vector. If position exceeds vector size, returns last element.
	MusicTrack &getMusicFromAllMusicsList(const unsigned int &musicPosition);
	// Returns music from playlist of the day vector. If position exceeds vector size, returns last element.
	MusicTrack &getMusicFromPlaylistOfTheDay(const unsigned int &musicPosition);
	// Returns number of user available on the radio station.
	unsigned int getNumberOfUsers() const;
	// ===================================================
	// ===================================================
	// Change radio information
	// ===================================================
	// Changes radio station name. Receives string with new radio station name by reference.
	void setRadioName(const std::string &newRadioStationName);
	// Increments number of users available on the radio station.
	void incrementNumberOfUsers();
	// Adds a new instance of the class Music Track to the radio station music list vector.
	void addNewMusicToRadioStation();
	// Removes music from radio station music list.
	void removeMusicFromRadioStation(const unsigned int &musicID);
	// Resets all like(dislikes count
	void resetAllLikesAndDislikes();
	// Edit a cetain music track's information
	void editMusicTrack(const int &musicPos);
	// Decrements music tracks ID's.
	void decrementMusicTracksID(const unsigned int begin);
	// Reset the rating atributed to a certain music by the user
	void resetRatingsFromMusic(unsigned const int musicID);
	// Deletes all rating files (is invoked when all likes/dislikes are reseted)
	void deleteAllRatings();
	// Randomly generates a new playlist of the day.
	void generatePlaylistOfTheDay(const unsigned int numberOfMusics);
	// Checks for users that have a hit on their playlist.
	void checkForHitsOnAllUsers();
	// Resets all hits on all users.
	void resetAllHitsOnAllUsers();
	// ===================================================
	// ===================================================
	// PRIZE
	// ===================================================
	// Prints all users in descending order (best number of hits to worst number of hits). Prints also the winner.
	// Uses all below function (from PRIZE category)!
	void prizeWinner();
	// Returns vector with all users information.
	std::vector<User> loadAllUsersToVector();
	// Sorts all users by number of hits, on all users vector.
	void sortAllUsersByHits(std::vector <User> &allUsersVec);
	// Returns the first user of all users vector. The user with most number of hits.
	User userWithMostNumberOfHits(const std::vector <User> &allUsersVec);
	// ===================================================
	// ===================================================
	// Text Files Handling
	// ===================================================
	// Saves radio information to csv file.
	void saveRadioStationToFile() const;
	// Saves Radio Station Music List to csv file.
	void saveRadioStationMusicsListToFile() const;
	// Saves Playlist of the day to csv file.
	void savePlaylistOfTheDayToFile();
	// Loads radio information from csv file.
	void loadRadioStationFromFile();
	// Loads Radio Station Music List from csv file. Returns true if successfully loaded.
	void loadRadioStationMusicsListFromFile();
	// Loads playlist of the day from csv file.
	void loadPlaylistOfTheDayFromFile();
	// ===================================================
};

#endif