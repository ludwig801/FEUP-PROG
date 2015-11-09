/* ==========================================
TITLE: RADIO STATION MANAGER				|
											|
AUTHORS: Kevin Amorim - ei12057				|
		 Luís Magalhães - ei12054			|
											|
GROUP: T2G02								|
											|
DATE: 2013/05/28							|
											|
PURPOSE: Creates and manages a radio		|
station. Allows users to register on		|
the radio station and manage a playlist		|
from the available musics. An admin			|
can manage all the tracks on the radio		|
station, the top 10 musics and the			|
user with most hits.						|
											|
PARAMETERS:	No parameters needed.			|
											|
											|
   -->  DEVELOPED WITH WINDOWS 8.  <--		|
============================================*/
// ==========================================
// INCLUDES
// ==========================================
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <cmath>
#include <Windows.h>

#include "class_radio_station.h"
#include "class_administrator.h"
#include "class_user.h"
#include "class_musictrack.h"
#include "aux_functions.h"
#include "strings.h"

using namespace std;
// ==========================================
// ==========================================
// DATA STRUCTURES
// ==========================================
struct KEY_CODE
{
	static const int KEY = 224;
	static const int KEY_UP = 72;
	static const int KEY_RIGHT = 77;
	static const int KEY_DOWN = 80;
	static const int KEY_LEFT = 75;

	static const int KEY_ENTER = 13;
	static const int KEY_BACK = 8;

	static const int KEY_ESC = 27;

	static const int KEY_DEL = 83;
	static const int CTRL_DEL = 147; 
	
	static const int CTRL_A = 1;
	static const int CTRL_K = 11;
	static const int CTRL_R = 18;
	static const int CTRL_U = 21;

	static const int D = 100;
	static const int E = 101;
	static const int L = 108;
	static const int P = 112;
	

} skey_code;
// ==========================================
// ===========================================
// Functions Prototypes
// ===========================================
// ==== MAIN MENUS ====
template<typename T>
void mainMenu(T &user, const bool &special, RadioStation &radio1);
void menuChoice(RadioStation &radio1);
void menuLogin_Register(int menuOption, RadioStation &radio1);
void searchMenu(vector<MusicTrack> &musics);
// ==== SUB MENUS ====
template<typename T>
void editUserProfileMenu(T& userObj);
void subMenuGenerate();
RadioStation createRadioStation();
void createNewUser(bool isAdmin, bool isFirstTime, RadioStation &radioObj);
template<typename T>
void auxKeyMenu( const int &key, const unsigned int &musicPos, RadioStation &radio1, T &user);
// ==== MUSIC MANAGEMENT ====
template<typename T>
void displayAllTracks(T &user, RadioStation &radio1);
template<typename T>
unsigned int displayMusicPage(unsigned int &line, unsigned int &pages, unsigned int &page_number, RadioStation radio1, T user);
template<typename T>
void myPlaylist(T &user, RadioStation &radio1);
void TopTen(RadioStation &radio1);
// ==== HANDLERS ====
template<typename T>
T loadUser(string iUsername);
bool resetAll();
// ===========================================
// ==============================================================================================
// =======================================  MENUS ===============================================
// ==============================================================================================
// ========================================
// MAIN MENU
// ========================================
// Users and administrators main menu. Receives as parameters an user (special or not);
// a constant bool 
template<typename T>
void mainMenu(T &user, const bool &special, RadioStation &radioObj) {

	// =======================================
	// VARIABLES
	// =======================================
	enum ITEMS {
		BROWSE,
		MY_PLAYLIST,
		TOP_TEN,
		SEARCH_MUSIC,
		SHOW_PLAYLIST_DAY,
		GENERATE,
		RESET_HITS,
		ADD_MUSIC,
		PRIZE,
		CHANGE_PROFILE,
		LOGOFF
	};

	const int N_ITEMS = 11;

	int key;
	unsigned int selected_item = 0;
	// =======================================

	do
	{
		clearScreen();

		cout << msg_title() << user.getName();

		// =======================================
		// MENU
		// =======================================
		if(selected_item == BROWSE) changeTextColor("BLACK");
		cout << msg_item_BROWSE();
		changeTextColor("WHITE");

		if(selected_item == MY_PLAYLIST) changeTextColor("BLACK");
		cout << msg_item_MY_PLAYLIST();
		changeTextColor("WHITE");

		if(selected_item == TOP_TEN) changeTextColor("BLACK");
		cout << msg_item_TOP_TEN();
		changeTextColor("WHITE");

		if(selected_item == SEARCH_MUSIC) changeTextColor("BLACK");
		cout << msg_item_SEARCH_MUSIC();
		changeTextColor("WHITE");

		if(selected_item == SHOW_PLAYLIST_DAY) changeTextColor("BLACK");
		cout << msg_item_SHOW_PLAYLIST_DAY();
		changeTextColor("WHITE");

		// Special Options.
		if(special)
		{
			// display only if user as special access (is admin).
			if(selected_item == GENERATE) changeTextColor("BLACK");
			cout << msg_item_GENERATE();
			changeTextColor("WHITE");

			if(selected_item == RESET_HITS) changeTextColor("BLACK");
			cout << msg_item_RESET_HITS();
			changeTextColor("WHITE");

			if(selected_item == ADD_MUSIC) changeTextColor("BLACK");
			cout << msg_item_ADD_MUSIC();
			changeTextColor("WHITE");
		}

		if(selected_item == PRIZE) changeTextColor("BLACK");
		cout << msg_item_PRIZE();
		changeTextColor("WHITE");

		if(selected_item == CHANGE_PROFILE) changeTextColor("BLACK");
		cout << msg_item_CHANGE_PROFILE();
		changeTextColor("WHITE");

		if(selected_item == LOGOFF) changeTextColor("BLACK");
		cout << msg_item_LOGOFF();
		changeTextColor("WHITE");
		// =======================================

		// =======================================
		// INSTRUCTIONS
		// =======================================
		cout << msg_instr_main_menu();
		// =======================================

		// =======================================
		// HANDLES KEYS
		// =======================================
		key = _getch();

		// If arrow key is pressed.
		if(key == skey_code.KEY) {
			key = _getch();
		}
		if(key == skey_code.KEY_UP) {
			if(selected_item <= BROWSE)	{
				selected_item = N_ITEMS - 1;
			} else {
				// Jumps special options if not special user.
				if((!special) && (selected_item == PRIZE))	{
					selected_item = SHOW_PLAYLIST_DAY;
				} else {
					selected_item--;
				}
			}
		} else if(key == skey_code.KEY_DOWN) {
			if(selected_item >= (N_ITEMS - 1)) {
				selected_item = BROWSE;			
			} else {
				// Jumps special options if not special user.
				if((!special) && (selected_item == SHOW_PLAYLIST_DAY)) {
					selected_item = PRIZE;
				} else {
					selected_item++;
				}
			}
		}
		// =======================================
		// =======================================
		// ENTER KEY
		// =======================================
		else if(key == skey_code.KEY_ENTER) {
			switch(selected_item) {
			case BROWSE:
				displayAllTracks( user, radioObj);
				break;

			case MY_PLAYLIST:
				myPlaylist(user, radioObj);
				break;

			case TOP_TEN:
				TopTen(radioObj);
				break;

			case SEARCH_MUSIC:
				searchMenu(radioObj);
				break;

			case GENERATE:
				subMenuGenerate(radioObj);
				break;

			case RESET_HITS:
				radioObj.resetAllHitsOnAllUsers();
				break;

			case ADD_MUSIC:
				radioObj.addNewMusicToRadioStation();
				break;

			case PRIZE:
				radioObj.prizeWinner();
				break;

			case SHOW_PLAYLIST_DAY:
				displayPlaylistOfTheDay(radioObj);
				break;

			case CHANGE_PROFILE:
				editUserProfileMenu<T>(user);
				break;

			case LOGOFF:
				clearScreen();
				return;
				break;

			default:
				break;
			}
		}
		// =======================================
	} while(key != skey_code.KEY_BACK);
}
// ========================================
// INITIAL MENU
// ========================================
// Allows user to choose wether e wants to login or register a new user.
void menuChoice(RadioStation &radio1){

	// ===========================================
	// Variables
	// ===========================================
	const unsigned int OPTIONS = 2;

	enum {
		LOGIN,
		REGISTER
	};

	int key;

	int actualChoice = 0;
	// ===========================================

	// Waits for user choice and navigates through menu.
	do
	{
		clearScreen();
		changeTextColor("WHITE");

		cout << msg_choice_title() << radio1.getRadioStationName();

		// Prints available options.
		switch(actualChoice) {
		case LOGIN:
			cout << msg_choice_login_title();
			break;
		case REGISTER:
			cout << msg_choice_register_title();
			break;
		}

		cout << msg_instr_menu_choice();

		key = _getch();

		// Manages arrows.
		if (key == skey_code.KEY)
		{
			key = _getch();
			{
				if (key == skey_code.KEY_LEFT)
				{
					if (LOGIN == actualChoice) {
						actualChoice = OPTIONS - 1;
					} else {
						actualChoice--;
					}
				}
				else if (key == skey_code.KEY_RIGHT)
				{
					if ((OPTIONS - 1) == actualChoice) {
						actualChoice = LOGIN;
					} else {
						actualChoice++;
					}
				}
			}
			// If ENTER is pressed!
		} else if (key==skey_code.KEY_ENTER)
		{
			menuLogin_Register( actualChoice, radio1);
		}

	}while(key!=skey_code.KEY_ESC);
}
// ========================================
// LOGIN / REGISTER MENU
// ========================================
// Login/Register menu.
void menuLogin_Register(int menuOption, RadioStation &radio1)
{
	enum ITEMS {
		LOGIN,
		REGISTER
	};

	string tempPass, login, pass;
	unsigned int status;
	
	clearScreen();

	switch(menuOption)
	{

	case LOGIN:

		do
		{
			clearScreen();
			cin.clear();

			cout << msg_instr_menuLogin_Register();
			cout << msg_logReg_login();

			cin >> login;
		}while(cin.fail());

		if(login == "quit") return;

		tempPass = getPassword(login);

		// If user not found.
		if(tempPass == "NOT FOUND")
		{
			clearScreen();
			cout << msg_user_error_not_found();
			waitForKey();
			return;

		}
		else
		{

			do
			{
				cin.clear();

				char ch;

				cout << msg_logReg_pass();

				// Displays * while the user enters his/her pass (security purposes)
				while((ch = _getch()) != skey_code.KEY_ENTER)
				{
					clearScreen();

					cout << msg_instr_menuLogin_Register();
					cout << msg_logReg_login() << login << endl;
					cout << msg_logReg_pass();

					if(ch != skey_code.KEY_BACK) {
    					pass += ch;
					} else if (ch == skey_code.KEY_BACK) {
						if(pass.size() > 0) {
							pass.pop_back();
						}
					}

					for(unsigned int chars = 0; chars < pass.size();  chars++) {
    					cout << '*';
					}
				}

				//cin >> pass; 

			}while(cin.fail());

			cin.clear();
			cin.ignore(INT_MAX,'\n');

			if(pass == tempPass)
			{
				status = getStatus(login);

				if(status == 0) {
					User actualUser = loadUser <User> (login); // Loads normal user.
					actualUser.loadUserPlaylistFromFile();
					mainMenu(actualUser,false,radio1);
				} else if(status == 1) {
					Administrator actualUser = loadUser <Administrator> (login); // Loads admin.
					actualUser.loadUserPlaylistFromFile();
					mainMenu(actualUser,true,radio1);
				}

			}
			else
			{

				clearScreen();
				cout << msg_user_error_password();
				waitForKey();

			}
		}

		break;

	case REGISTER:	

		createNewUser(false, false, radio1);

		break;

	}
}
// ========================================
// CREATORS
// ========================================
// Creates Radio Station.
RadioStation createRadioStation() {

	clearScreen();

	string radioStationName;
	char tempRadioStationName[100];

	do {

		clearScreen();
		cin.clear();

		cout << msg_create_rstation_title();

		cout << msg_create_rstation_name();
		cin.getline(tempRadioStationName, 100);

		radioStationName = tempRadioStationName;

		if(!cin.fail()) {
			break;
		}

		cout << msg_create_rstation_name_error();
		waitForKey();

		cin.clear();
		cin.ignore();

	} while(cin.fail());

	clearScreen();

	RadioStation radioStationOnline(radioStationName);

	createNewUser(true, true, radioStationOnline);

	return radioStationOnline;
}
// Creates a new user. Receives a bool parameter to determine wether the user is administrator or not.
void createNewUser(bool isAdmin, bool isFirstTime, RadioStation &radioObj) {

	// ====================================
	// VARIABLES
	// ====================================
	enum {
		USERNAME,
		PASSWORD,
		AGE,
		GENDER
	};

	string userName, userPw, userGender;
	unsigned int userAge;

	unsigned int option = 0;
	bool done = false;
	// ====================================

	do {
		clearScreen();
		cin.clear();

		switch(option) {
		case USERNAME:
			if(!isFirstTime)
				cout << msg_instr_createNewUser();
			cout << msg_create_new_user_name();
			cin >> userName;
			if(!isFirstTime)
			{
				if(userName == "quit")
					return;
			}
			// Verifies if username is not already in use.
			if(!cin.fail()) {
				if(searchID(userName, "users.csv") < 0) {
					break;
				} else {
					cerr << msg_user_error_repeated();
					waitForKey();
					option--;
				}
			}
			break;

		case PASSWORD:
			if(!isFirstTime)
				cout << msg_instr_createNewUser();
			cout << msg_create_new_user_pass();
			cin >> userPw;
			if(!isFirstTime)
			{
				if(userPw == "quit")
					return;
			}
			break;

		case AGE:
			if(!isFirstTime)
				cout << msg_instr_createNewUser_age();
			cout << msg_create_new_user_age();
			cin >> userAge;
			if(!isFirstTime)
			{
				if(userAge == 0)
					return;
			}
			break;

		case GENDER:
			if(!isFirstTime)
				cout << msg_instr_createNewUser();
			cout << msg_create_new_user_gender();
			cin >> userGender;
			if(!isFirstTime)
			{
				if(userGender == "quit")
					return;
			}
			if(!cin.fail())
			{
				if((userGender == "M") || (userGender == "F"))
				{
					done = true;
				}
				else
				{
					option--;
				}
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
			cin.clear();
		}

		cin.ignore();

	} while(cin.fail() || (!done));

	cin.clear();

	radioObj.incrementNumberOfUsers();

	if(isAdmin) {
		Administrator adminOnline(searchLastID("users.csv") + 1, userName, userAge, userGender, isAdmin, userPw, 0);
	} else {
		User userOnline(searchLastID("users.csv") + 1, userName, userAge, userGender, isAdmin, userPw, 0);
	}

}
// ========================================
// ========================================
// EDITORS
// ========================================
template<typename T>
void editUserProfileMenu(T& userObj) {
	enum {
		USERNAME,
		AGE,
		GENDER,
		PASSWORD
	};

	const int N_ITEMS = 4;

	string newStr;

	int key;
	unsigned int selected_item = 0;

	std::string inputAgeStr;
	char inputTemp[100];

	bool done = false;
	// =======================================

	do
	{
		clearScreen();

		cout << msg_edit_profile_title() << userObj.getName();

		// =======================================
		// MENU
		// =======================================
		if(selected_item == USERNAME) changeTextColor("BLACK");
		cout << msg_edit_profile_name() << "[ " << userObj.getName() << " ]";
		changeTextColor("WHITE");

		if(selected_item == AGE) changeTextColor("BLACK");
		cout << msg_edit_profile_age() << "[ " << userObj.getAge() << " ]";
		changeTextColor("WHITE");

		if(selected_item == GENDER) changeTextColor("BLACK");
		cout << msg_edit_profile_gender() << "[ " << userObj.getGender() << " ]";
		changeTextColor("WHITE");

		if(selected_item == PASSWORD) changeTextColor("BLACK");
		cout << msg_edit_profile_pass() << "[ " << userObj.getPass() << " ]";
		changeTextColor("WHITE");

		cout << endl;
		// =======================================

		// =======================================
		// INSTRUCTIONS
		// =======================================
		cout << msg_instr_edit_profile();
		// =======================================

		// =======================================
		// HANDLES KEYS
		// =======================================
		key = _getch();

		// If arrow key is pressed.
		if(key == skey_code.KEY) {
			key = _getch();
		}
		if(key == skey_code.KEY_UP) {
			if(selected_item <= USERNAME)	{
				selected_item = N_ITEMS - 1;
			} else {
				selected_item--;
			}
		} else if(key == skey_code.KEY_DOWN) {
			if(selected_item >= (N_ITEMS - 1)) {
				selected_item = USERNAME;			
			} else {
				selected_item++;
			}
		}
		// =======================================
		// =======================================
		// ENTER KEY
		// =======================================
		else if(key == skey_code.KEY_ENTER) {
			switch(selected_item) {
			case USERNAME:
				do {
					clearScreen();
					cin.clear();
					cout << msg_user_new_username(); cin >> newStr;
					if(!cin.fail()) {
						if(searchID(newStr, "users.csv") < 0) {
							userObj.setName(newStr);
						} else {
							clearScreen();
							cerr << msg_user_error_repeated();
							waitForKey();
						}
					}
					cin.ignore();
				} while(cin.fail());
				userObj.rewritesUserToFile();
				break;
			case AGE:
				done = false;
				do {
					clearScreen();
					cin.clear();
					cout << msg_user_new_age(); 
					cin.getline(inputTemp, 100, '\n');
					inputAgeStr = inputTemp;
					if(isNumber(inputAgeStr)) {
						userObj.setAge(convertStrInt(inputAgeStr));
						done = true;
					}
				} while(!done);

				userObj.rewritesUserToFile();
				break;
			case GENDER:
				clearScreen();
				if(userObj.getGender() == "M") {
					userObj.setGender("F");
				} else {
					userObj.setGender("M");
				}
				//cout << msg_user_new_gender_success() << endl;
				//waitForKey();
				userObj.rewritesUserToFile();
				break;
			case PASSWORD:
				do {
					clearScreen();
					cin.clear();
					cout << msg_user_new_password(); cin >> newStr;
					if(!cin.fail()) {
						userObj.setPass(newStr);
					}
					cin.ignore();
				} while(cin.fail());
				userObj.rewritesUserToFile();
				break;
			default:
				break;
			}
		}
		// =======================================
	} while(key != skey_code.KEY_BACK);


}
// ========================================
// ========================================
// SEARCH MENU
// ========================================
// Search menu receives a vector as parameter by reference and displays results.
void searchMenu(RadioStation &radio1) {

	enum ITEMS {
		TITLE,
		AUTHOR,
		ALBUM,
		GENRE,
		YEAR
	};

	const unsigned int N_ITEMS = 5;

	unsigned int selected_item = TITLE;
	int key;

	string searchStr;
	char searchStrTemp[100];
	int value; 

	do
	{
		clearScreen();

		if(selected_item == TITLE) changeTextColor("BLACK");
		cout << msg_search_by_title();
		changeTextColor("WHITE");

		if(selected_item == AUTHOR) changeTextColor("BLACK");
		cout << msg_search_by_author();
		changeTextColor("WHITE");

		if(selected_item == ALBUM) changeTextColor("BLACK");
		cout << msg_search_by_album();
		changeTextColor("WHITE");

		if(selected_item == GENRE) changeTextColor("BLACK");
		cout << msg_search_by_genre();
		changeTextColor("WHITE");

		if(selected_item == YEAR) changeTextColor("BLACK");
		cout << msg_search_by_year();
		changeTextColor("WHITE");

		cout << msg_instr_search();


		key = _getch();

		if(key == skey_code.KEY)
		{
			key = _getch();
			if(key == skey_code.KEY_UP)
			{
				if(selected_item <= 0) 
					selected_item = N_ITEMS - 1;
				else
					selected_item--;
			}
			else if(key == skey_code.KEY_DOWN)
			{
				if(selected_item >= (N_ITEMS - 1))
					selected_item = 0;
				else
					selected_item++;
			}
		}
		else if(key == skey_code.KEY_ENTER)
		{
			value = selected_item;
			clearScreen();

			cout << msg_search_keyword();
			cin.getline(searchStrTemp,100,'\n');
			searchStr = searchStrTemp;

			cin.clear();

			cout << endl;
			cout <<	setw(8) << msg_base_title()
				<< setw(8) << msg_album()
				<< setw(8) << msg_author()
				<< setw(8) << msg_genre()
				<< setw(8) << msg_year();
			cout << endl << endl;

			searchAllMusicsByValue(searchStr, value, radio1.getAllMusicsList());
		}

	}while(key != skey_code.KEY_BACK);
}
// ===========================================
// ==============================================================================================
// ==============================================================================================
// ====================================== SECONDARY MENUS =======================================
// ==============================================================================================
// ========================================
// DISPLAY ALL TRACKS
// ========================================
// Displays all music tracks.
template<typename T>
void displayAllTracks(T &user, RadioStation &radio1)
{
	int key;
	unsigned int pages;

	unsigned int line = 0;
	unsigned int musicPos = 0;
	unsigned int page_number = 0;

	if(radio1.getAllMusicsList().size() <= 10)
	{
		pages = 0;
	}
	else
	{
		pages = (int) ceil((radio1.getAllMusicsList().size() / 10.0));
		pages--;

	}

	if(radio1.getAllMusicsList().size() != 0)	// If there are musics in the radioStation
	{
		do
		{

			clearScreen();

			// Calls display menu
			line = displayMusicPage( line, pages, page_number, radio1, user);

			// MusicPos points to the index of the musicTrack
			musicPos = line + (page_number * 10);

			cout << msg_instr_display_all();

			key = _getch();

			// SPECIAL KEY PRESSED (arrow or del)
			if (key == skey_code.KEY)
			{
				key = _getch();

				switch(key)
				{
					// UP ARROW KEY
					case skey_code.KEY_UP:
						if(line == 0)
						{
							if(page_number == pages)
								line = (radio1.getAllMusicsList().size() - (page_number*10) - 1);
							else
								line = 9;
						}
						else
							line--;
						break;
					// DOWN ARROW KEY
					case skey_code.KEY_DOWN:
						if((line == 9) || (line == (radio1.getAllMusicsList().size() - (page_number*10) - 1)))
							line = 0;
						else
							line++;
						break;
					// LEFT ARROW KEY
					case skey_code.KEY_LEFT:
						if(page_number == 0)
						{
							page_number = pages;
							line = 0;
						}
						else
						{
							page_number--;
							line = 0;
						}
						break;
					// RIGHT ARROW KEY
					case skey_code.KEY_RIGHT:
						if(page_number == pages)
						{
							page_number = 0;
							line = 0;
						}
						else
						{
							page_number++;
							line = 0;
						}
						break;
					//  CTRL + DEL
					case skey_code.CTRL_DEL:
						if (user.getSpecial())
						{

							radio1.removeMusicFromRadioStation(radio1.getMusicFromAllMusicsList(musicPos).getID());

							pages = (int) ceil((radio1.getAllMusicsList().size() / 10.0));

							if(pages > 0)
							{
								pages--;
							}
							else
								return;

							if(page_number > pages)
							{
								page_number--;
							}

						}
						break;
					default:
						break;
				}
			}
			else
			{
				auxKeyMenu( key, musicPos, radio1, user);
			}

		}while(key != skey_code.KEY_BACK);

		radio1.saveRadioStationMusicsListToFile();
	}
	// if there are NO musics in the radioStation
	else
	{
		clearScreen();
		cout << msg_display_all_empty_list();
		waitForKey();

	}
}
// Displays a page of musics
template<typename T>
unsigned int displayMusicPage(unsigned int &line, unsigned int &pages, unsigned int &page_number, RadioStation radio1, T user)
{
	unsigned int musicPos;
	bool color = true;


	cout << msg_instr_display_page();
	cout <<	setw(8)  << msg_base_title()
		 << setw(8)  << msg_author()
		 << setw(8)  << msg_album()
		 << setw(8)  << msg_genre()
		 << setw(8)  << msg_year()
		 << setw(10) << msg_playlist()
		 << setw(8)  << msg_popular()
		 << setw(6)  << msg_like()
		 << endl << endl;

	changeTextColor("WHITE");

	// DISPLAYS MUSIC TRACKS
	for(unsigned int i = 0; ((i < 10) && (i < (radio1.getAllMusicsList().size()) - page_number*10)); i++)
	{
		musicPos = i + (page_number * 10);

		if( radio1.getMusicFromAllMusicsList(musicPos).getAvailable())
		{
			// music display
			if(line == i)
			{
				changeTextColor("BLACK");
				color = false; 
			}
			radio1.getMusicFromAllMusicsList(musicPos).display(false);

				// checks wether is the music a member or not of the user's playlist
			cout << setw(10) << isPlaylistMember(user, radio1.getMusicFromAllMusicsList(musicPos).getID())  << setw(8)
				// like/dislike ratio (likes - dislikes)
				<< ((int) (radio1.getMusicFromAllMusicsList(musicPos).getLikes() - radio1.getMusicFromAllMusicsList(musicPos).getDislikes())) << setw(6);

			// Checks if user has liked/disliked the music track
			if(user.rateExists(radio1.getMusicFromAllMusicsList(musicPos).getID()) == 1) cout << "YES";
			else if(user.rateExists(radio1.getMusicFromAllMusicsList(musicPos).getID()) == -1) cout << "NO ";
			else cout << " ";

			if(line == i) cout << setw(4) << " <<";

			if (color == false)
			{
				changeTextColor("WHITE");
				color = true;
			}
		}
		else
		{
			changeTextColor("RED");
			cout << setw(15) << msg_display_page_unavailable();

			changeTextColor("WHITE");
			if(line == i)  cout << setw(53) << " <<";

		}
		cout << endl;
	}

	changeTextColor("WHITE");

	cout << endl << setw(60) << msg_page() << page_number + 1 << "/" << pages + 1;

	return line;
}
// ========================================
// ========================================
// DISPLAY USER PLAYLIST
// ========================================
// Displays a user playList.
template<typename T>
void myPlaylist(T &user, RadioStation &radio1)
{	
	unsigned int line = 0;
	unsigned int musicPos = 0;
	int key;

	unsigned int pages;
	unsigned int page_number = 0;

	clearScreen();

	// Checks if user's playlist is empty
	if(user.size() == 0)
	{
		cout << msg_playlist_empty();
		waitForKey();
		return;
	}
	else
	{
		pages = (int) ceil((user.size() / 10.0));
		pages--;

		do
		{
			clearScreen();

			cout <<	setw(10) << msg_base_title()
				 << setw(8) << msg_author()
				 << setw(8) << msg_album()
				 << setw(8) << msg_genre()
				 << setw(8) << msg_year();
			cout << endl << endl;

			//Displays the users playList
			user.displayList( line, radio1.getAllMusicsList(), page_number);

			cout << endl << endl << setw(39) << msg_page() << page_number + 1 << "/" << pages + 1;

			cout << msg_instr_playlist();

			key = _getch();

			if (key == skey_code.KEY)
			{
				key = _getch();

				if(key == skey_code.KEY_UP)
				{
					if(line == (page_number * 10))
					{
						if(page_number == pages)
						{
							musicPos = user.size() - 1;
							line = user.size() - 1;
						}
						else
						{
							musicPos = (page_number * 10) + 9;
							line = 9;
						}
					}
					else
					{
						musicPos--;
						line--;
					}
				}
				else if(key == skey_code.KEY_DOWN)
				{
					if((line == ((page_number * 10) + 9)) || (line == (user.size() - 1)))
					{
						musicPos = (page_number * 10);
						line = page_number * 10;
					}
					else
					{
						musicPos++;
						line++;
					}
				}
				else if(key == skey_code.KEY_LEFT)
				{
					if(page_number == 0)
					{
						page_number = pages;
						line = page_number * 10;
					}
					else
					{
						page_number--;
						line = page_number * 10;
					}
				}
				else if(key == skey_code.KEY_RIGHT)
				{
					if(page_number == pages)
					{
						page_number = 0;
						line = page_number * 10;
					}
					else
					{
						page_number++;
						line = page_number * 10;
					}
				}
				else if(key == skey_code.KEY_DEL)
				{
					user.remTrack(user.getMusicID(line));

					pages = (int) ceil((user.size() / 10.0));
					pages--;

					if(page_number > pages)
					{
						page_number--;
					}

					musicPos = (page_number * 10);

					line = page_number * 10;
				}
			}
			else if (key == skey_code.KEY_ENTER)
			{
				clearScreen();
				user.displayTrack( musicPos, radio1.getAllMusicsList());

				cout << endl;
				waitForKey();
			}

		}while((key != skey_code.KEY_BACK) && (user.size()));
	}
}
// ========================================
// ========================================
// DISPLAY TOP TEN LIST
// ========================================
void TopTen(RadioStation &radio1)
{
	int key;
	int line = 0;
	int size = 0;

	vector<MusicTrack> topTenVector;

	getTopTen(radio1, topTenVector);

	if(topTenVector.size() != 0)
	{
		do
		{

			clearScreen();

			displayTopTen(topTenVector,line);

			cout << msg_instr_top_ten();

			key = _getch();
		
			if (key == skey_code.KEY)
			{
				key = _getch();
				if (key == skey_code.KEY_UP)
				{
					if(line == 0)
					{
						line = topTenVector.size() - 1;
					}
					else
						line--;
				}
				else if (key == skey_code.KEY_DOWN)
				{
					if(line == topTenVector.size() - 1)
					{
						line = 0;
					}
					else
						line++;
				}

			}
			else if (key == skey_code.KEY_ENTER)
			{
				clearScreen();
				topTenVector[line].displayMusic();

				cout << endl;
				waitForKey();
			}

		}while(key != skey_code.KEY_BACK);
	}
	else
	{
		clearScreen();
		cout << msg_vector_empty();
		waitForKey();
	}
}
// ========================================
// ========================================
// DISPLAY PLAYLIST OF THE DAY
// ========================================
void displayPlaylistOfTheDay(RadioStation &radioObj) {

	clearScreen();

	if(radioObj.getPlaylistOfTheDay().size() == 0) {
		cerr << msg_day_playlist_empty();
	} else {
		for(unsigned int music = 0; music < radioObj.getPlaylistOfTheDay().size(); music++) {
			radioObj.getMusicFromPlaylistOfTheDay(music).display(false);
			cout << endl;
		}
	}

	waitForKey();
}
// ========================================
// ========================================
// DISPLAY ALL TRACKS
// ========================================
// Displays all music tracks.
void subMenuGenerate(RadioStation &radioObj)
{
	bool done = false;
	unsigned int numberOfMusics;
	do
	{
		cin.clear();
		clearScreen();
		cout << msg_sub_menu_GENERATE();
		cin >> numberOfMusics;
		if(!cin.fail())
		{
			done = true;
		}
		else
		{
			cin.clear();
			cin.ignore();
		}
	}while(!done);
	radioObj.generatePlaylistOfTheDay(numberOfMusics);
	cin.clear();
}
// ========================================
// ========================================
// AUXILIARY MENUS
// ========================================
// Auxiliary menu.
template<typename T>
void auxKeyMenu( const int &key, const unsigned int &musicPos, RadioStation &radio1, T &user)
{
	int auxKey = 0;
	int auxOption = 0;

	switch(key)
	{
		// [P] -> ADD/REMOVE FROM PLAYLIST
	case skey_code.P:
		if(((!user.getSpecial()) && (radio1.getMusicFromAllMusicsList(musicPos).getAvailable())) || (user.getSpecial()))
		{
			if(user.musicExists(radio1.getMusicFromAllMusicsList(musicPos).getID()))
			{
				user.remTrack(radio1.getMusicFromAllMusicsList(musicPos).getID());
			}
			else
			{
				user.addTrack(radio1.getMusicFromAllMusicsList(musicPos).getID());
			}
		}
		break;
		// [L] -> LIKE
	case skey_code.L:
		if(((!user.getSpecial()) && (radio1.getMusicFromAllMusicsList(musicPos).getAvailable())) || (user.getSpecial()))
		{
			clearScreen();
			if(user.rateExists(radio1.getMusicFromAllMusicsList(musicPos).getID()) == 1)
			{
				cout << msg_aux_key_like_error();
				waitForKey();
			}
			else if(user.rateExists(radio1.getMusicFromAllMusicsList(musicPos).getID()) == -1)
			{
				user.rateMusic(1,radio1.getMusicFromAllMusicsList(musicPos).getID());
				radio1.getMusicFromAllMusicsList(musicPos).setLikes(0,true,false);
				radio1.getMusicFromAllMusicsList(musicPos).setDislikes(0,false,true);
			}
			else
			{
				user.rateMusic(1,radio1.getMusicFromAllMusicsList(musicPos).getID());
				radio1.getMusicFromAllMusicsList(musicPos).setLikes(0,true,false);
			}
		}
		break;
		// [D] -> DISLIKE
	case skey_code.D:
		if(((!user.getSpecial()) && (radio1.getMusicFromAllMusicsList(musicPos).getAvailable())) || (user.getSpecial()))
		{
			clearScreen();
			if(user.rateExists(radio1.getMusicFromAllMusicsList(musicPos).getID()) == -1)
			{
				cout << msg_aux_key_dislike_error();
				waitForKey();
			}
			else if(user.rateExists(radio1.getMusicFromAllMusicsList(musicPos).getID()) == 1)
			{
				user.rateMusic(-1,radio1.getMusicFromAllMusicsList(musicPos).getID());
				radio1.getMusicFromAllMusicsList(musicPos).setLikes(0,false,true);
				radio1.getMusicFromAllMusicsList(musicPos).setDislikes(0,true,false);
			}
			else
			{
				user.rateMusic(-1,radio1.getMusicFromAllMusicsList(musicPos).getID());
				radio1.getMusicFromAllMusicsList(musicPos).setDislikes(0,true,false);
			}
		}
		break;
		// [ENTER] -> DISPLAY DETAILED VIEW
	case skey_code.KEY_ENTER:
		if(((!user.getSpecial()) && (radio1.getMusicFromAllMusicsList(musicPos).getAvailable())) || (user.getSpecial()))
		{
			clearScreen();
			radio1.getMusicFromAllMusicsList(musicPos).displayMusic();
			cout << endl;
			waitForKey();
		}
		break;
		// [CTRL + K] -> HELP SCREEN
	case skey_code.CTRL_K:
		clearScreen();

		cout << msg_aux_key_help();
		// Admin special options
		if (user.getSpecial())
		{
			cout << msg_aux_key_help_special();
		}

		waitForKey();
		break;
		// [E] -> EDIT MUSIC TRACK
	case skey_code.E:
		if(user.getSpecial())
		{
			do
			{
				clearScreen();
				cout << msg_aux_key_edit() << radio1.getMusicFromAllMusicsList(musicPos).getTitle();

				if(auxOption)
					cout << msg_option_yes();
				else
					cout << msg_option_no();

				auxKey = _getch();

				if(auxKey == skey_code.KEY)
				{
					auxKey = _getch();

					if ((auxKey == skey_code.KEY_LEFT) || (auxKey == skey_code.KEY_RIGHT))
					{
						auxOption = !auxOption;
					}
				}
				else if (auxKey == skey_code.KEY_ENTER)
				{
					if(auxOption)
					{
						radio1.editMusicTrack(musicPos);
						auxKey = skey_code.KEY_BACK;
					}
					else return;
				}

				cout << endl;

			}while(auxKey != skey_code.KEY_BACK);
		}
		waitForKey();
		break;
		// [CTRL + R] -> RESET LIKES/DISLIKES FROM A MUSIC TRACK
	case skey_code.CTRL_R:
		if(user.getSpecial())
		{
			radio1.getMusicFromAllMusicsList(musicPos).setLikes(0,false,false);
			radio1.getMusicFromAllMusicsList(musicPos).setDislikes(0,false,false);
			radio1.saveRadioStationMusicsListToFile();
			radio1.resetRatingsFromMusic(radio1.getMusicFromAllMusicsList(musicPos).getID());
		}
		break;
		// [CTRL + A] -> RESET ALL LIKES/DISLIKES
	case skey_code.CTRL_A:
		if(user.getSpecial() && resetAll())
		{
			radio1.resetAllLikesAndDislikes();
			radio1.saveRadioStationMusicsListToFile();
			radio1.deleteAllRatings();
		}
		break;
		// [CTRL + U] -> SIGNAL AS UNAVAILABLE
	case skey_code.CTRL_U:
		if(user.getSpecial())
		{
			bool tempAvailable = false;
			tempAvailable = radio1.getMusicFromAllMusicsList(musicPos).getAvailable();
			tempAvailable = !tempAvailable;
			radio1.getMusicFromAllMusicsList(musicPos).setAvailable(tempAvailable);
		}
		break;
	default:
		break;
	}
}
// ========================================
// ==============================================================================================
// ==============================================================================================
// ====================================== HANDLERS ==============================================
// ==============================================================================================
// ========================================
// USERS HANDLERS
// ========================================
// Loads user from file.
template<typename T>
T loadUser(string iUsername)
{

	T finalUser;

	
	finalUser.loadUserFromFile(iUsername);
	
	
	return finalUser;

}
// ========================================
// MUSIC HANDLERS
// ========================================
// Resets all like/dislike counters
bool resetAll()
{
	int key = 0;

	bool op = false;

	do
	{
		clearScreen();

		cout << msg_reset_all_title();

		if(op)
		{
			cout << msg_option_yes();
		}
		else
		{
			cout << msg_option_no();
		}

		key = _getch();

		if(key == skey_code.KEY)
		{
			key = _getch();

			if((key == skey_code.KEY_LEFT) || (key == skey_code.KEY_RIGHT))
			{
				if(op)
				{
					op = false;
				}
				else
				{
					op = true;
				}
			}
		}

	}while(key != skey_code.KEY_ENTER);

	return op;
}
// ========================================
// ==============================================================================================

int main()
{

	// Initializes all resources.
	init();

	// ================================================
	// CREATES RADIO STATION
	// ================================================
	// Checks if a radio station already exists.
	if(!fileExists("radioStationInformation.csv")) {
		RadioStation radioObj = createRadioStation();
		radioObj.loadRadioStationMusicsListFromFile();
		menuChoice(radioObj);
	}
	else
	{
		RadioStation radioObj;
		radioObj.loadRadioStationFromFile();
		radioObj.loadRadioStationMusicsListFromFile();
		radioObj.loadPlaylistOfTheDayFromFile();
		/*
		if(radioObj.getNumberOfUsers() == 0)
		{
			createNewUser(true, true, radioObj);
		}
		*/
		menuChoice(radioObj);
	}
	// ================================================

	return 0;
}