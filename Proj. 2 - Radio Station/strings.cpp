/* ==========================================
TITLE: STRINGS								|
											|
AUTHORS: Kevin Amorim - ei12057				|
		 Luis Magalhaes - ei12054			|
											|
GROUP: T2G02								|
											|
DATE: 2013/05/24							|
											|
PURPOSE: Returns all necessary strings for 	|
the main program.							|
											|
PARAMETERS:	No parameters needed.			|
											|
INSTRUCTIONS: Include "string.h" in the		|
file you need to use the strings.			|		
Then call the function containing the		|
message you want and the corresponding		|
string is returned.							|
											|
											|
   -->  DEVELOPED WITH WINDOWS 8.  <--		|
============================================*/

#include <string>
#include "strings.h"

// ==============================================================
// ========================= DELIMITER  =========================
// ==============================================================
std::string delimiter() {
	return ",";
}
// ==============================================================
// ======================= ERROR MESSAGES =======================
// ==============================================================
// ============ FILES ============
// ERROR 0.
std::string cantOpenFileMsg() {
	return "\n ERROR 0x000 (Can't open file)";
}
// ERROR 1.
std::string cantSaveFileMsg() {
	return "\n ERROR 0x001 (Can't save file)";
}
// ERROR 2.
std::string cantRemoveFileMsg() {
	return "\n ERROR 0x002 (Can't remove file)";
}
// ERROR 3.
std::string cantCreateFileMsg() {
	return "\n ERROR 0x003 (Can't create file)";
}
// ERROR 18
std::string cantRenameFileMsg() {
	return "\n ERROR 0x012 (Can't rename file)";
}
// ERROR 19.
std::string digitCountExceedMsg() {
	return "\n ERROR 0x013 (Digit count exceeded)";
}
// ===============================
// ========== VECTORS ============
// ERROR 4.
std::string vectorIsEmptyMsg() {
	return "\n ERROR 0x004 (Vector is empty)";
}
// ERROR 5.
std::string vectorSizeExceededMsg() {
	return "\n ERROR 0x005 (Vector size has been exceeded)";
}
// ===============================
// ======= RADIO STATION =========
// ERROR 6.
std::string cantCreateRadioStationMsg() {
	return "\n ERROR 0x006 (Can't create Radio Station)";
}
// ERROR 7.
std::string cantSaveRadioStationMsg() {
	return "\n ERROR 0x007 (Can't save Radio Station)";
}
// ERROR 8.
std::string cantLoadRadioStationMsg() {
	return "\n ERROR 0x008 (Can't load Radio Station)";
}
// ===============================
// =========== USERS =============
// ERROR 9.
std::string cantCreateUserMsg() {
	return "\n ERROR 0x009 (Can't create user)";
}
// ERROR 10.
std::string cantSaveUserMsg() {
	return "\n ERROR 0x00A (Can't save user)";
}
// ERROR 11.
std::string cantLoadUserMsg() {
	return "\n ERROR 0x00B (Can't load user)";
}
// ===============================
// =========== MUSICS ============
// ERROR 12.
std::string cantCreateMusicMsg() {
	return "\n ERROR 0x00C (Can't create music)";
}
// ERROR 13.
std::string cantSaveMusicMsg() {
	return "\n ERROR 0x00D (Can't save music)";
}
// ERROR 14.
std::string cantLoadMusicMsg() {
	return "\n ERROR 0x00E (Can't load music)";
}
// ERROR 15.
std::string cantRemoveMusicMsg() {
	return "\n ERROR 0x00F (Can't remove music)";
}
// ERROR 16.
std::string cantGenerateRandomPlaylistMsg() {
	return "\n ERROR 0x010 (Can't generate random playlist)";
}
// ERROR 17.
std::string cantRateMusicMsg() {
	return "\n ERROR 0x011 (Can't rate music)";
}
// ==============================================================
// ===================                       ====================
// ===================  PARTICULAR MESSAGES  ====================
// ===================                       ====================
// ==============================================================
// ===============================
// ======= RADIO STATION =========
std::string msg_radio_station_created() {
	return "\n Radio Station successfully created.";
}
std::string msg_radio_station_saved() {
	return "\n Radio Station successfully saved.";
}
std::string msg_radio_station_loaded() {
	return "\n Radio Station successfully loaded.";
}
// ===============================
// =========== USERS =============
std::string msg_user_created() {
	return "\n User successfully created.";
}
std::string msg_user_saved() {
	return "\n User successfully saved.";
}
std::string msg_user_loaded() {
	return "\n User successfully loaded.";
}
std::string msg_user_error_password() {
	return "\n The password you entered is incorrect.";
}
std::string msg_user_error_not_found() {
	return "\n No user with such username has been found.";
}
std::string msg_user_error_repeated()
{
	return "\n Username already in use!\n";
}
// ===============================
// ========= EDITORS =============
std::string msg_user_new_username() {
	return "\n New Username: ";
}
std::string msg_user_new_age() {
	return "\n What is your age: ";
}
std::string msg_user_new_password() {
	return "\n New Password: ";
}
std::string msg_user_new_gender_success() {
	return "\n Your gender has been changed.";
}
// ===============================
// =========== MUSICS ============
std::string msg_music_created() {
	return "\n Music successfully created.";
}
std::string msg_music_saved() {
	return "\n Music successfully saved.";
}
std::string msg_music_loaded() {
	return "\n Music successfully loaded.";
}
std::string msg_music_removed() {
	return "\n Music successfully removed.";
}
std::string msg_random_playlist_success() {
	return "\n Random playlist successfully generated.";
}
std::string msg_rating_sucessful() {
	return "\n Thanks for rating!";
}
// ===============================
// =========== SEARCH ============
std::string msg_keyword_not_found() {
	return "\n Your keyword has not been found. \n";
}
// ==============================================
// ===================         ==================
// ===================  MENUS  ==================
// ===================         ==================
// ==============================================
// ===============================
// ========== MAIN MENU ==========
std::string msg_title() {
	return "User: ";
}
std::string msg_item_BROWSE() {
	return "\n\n      Browse all music tracks     \n";
}
std::string msg_item_MY_PLAYLIST() {
	return "            My Playlist           \n";
}
std::string msg_item_TOP_TEN() {
	return "              Top Ten             \n";
}
std::string msg_item_SEARCH_MUSIC() {
	return "       Search a music track       \n";
}
std::string msg_item_SHOW_PLAYLIST_DAY() {
	return "     Show Playlist of the Day     \n";
}
std::string msg_item_GENERATE() {
	return "   Generate playlist of the day   \n";
}
std::string msg_item_RESET_HITS() {
	return "           Reset all hits         \n";
}
std::string msg_item_ADD_MUSIC() {
	return "          Add music track         \n";
}
std::string msg_item_PRIZE()
{
	return "           Awarded prize          \n";
}
std::string msg_item_CHANGE_PROFILE() {
	return "    Change Profile Information    \n";
}
std::string msg_item_LOGOFF() {
	return "              Log off             \n";
}
std::string msg_sub_menu_GENERATE()
{
	return "\n How many songs to generate --> ";
}
// ===============================
// ========= MENU CHOICE =========
std::string msg_choice_title()
{
	std::string text = "RADIO STATION: ";
	return text;
	//return "RADIO STATION: ";
}
std::string msg_choice_login_title()
{
	return "\n\n  [ Login ]       Register \n";
}
std::string msg_choice_register_title()
{
	return "\n\n    Login       [ Register ] \n";
}
// ===============================
// ===== MENU LOGIN/REGISTER =====
std::string msg_logReg_login()
{
	return " Login: ";
}
std::string msg_logReg_pass()
{
	return "  Pass: ";
}
// ===============================
// == MENU CREATE RADIO STATION ==
std::string msg_create_rstation_title()
{
	return "\n --> Welcome to the RadioStation Creator (v1.02) \n\n\n";
}
std::string msg_create_rstation_name()
{
	return " --> Please enter the name of the radio station: \n\n --> ";
}
std::string msg_create_rstation_name_error()
{
	return "   Error: Invalid name! Please try again.\n";
}
// ===============================
// ==== MENU CREATE NEW USER =====
std::string msg_create_new_user_name()
{
	return " Username: ";
}
std::string msg_create_new_user_pass()
{
	return " Password: ";
}
std::string msg_create_new_user_age()
{
	return " Age: ";
}
std::string msg_create_new_user_gender()
{
	return "Gender (M/F): ";
}
// ===============================
// === MENU EDIT USER PROFILE ====
std::string msg_edit_profile_title()
{
	return "User: ";
}
std::string msg_edit_profile_name()
{
	return "\n\n      Change Username       ";
}
std::string msg_edit_profile_age()
{
	return "\n        Change Age          ";
}
std::string msg_edit_profile_gender()
{
	return "\n       Change Gender        ";
}
std::string msg_edit_profile_pass()
{
	return "\n      Change Password       ";
}
// ===============================
// ========= SEARCH MENU =========
std::string msg_search_keyword()
{
	return "\n Keyword to search: ";
}
std::string msg_search_by_title()
{
	return "\n   Search by Title    \n";
}
std::string msg_search_by_author()
{
	return "   Search by Author   \n";
}
std::string msg_search_by_album()
{
	return "   Search by Album    \n";
}
std::string msg_search_by_genre()
{
	return "   Search by Genre    \n";
}
std::string msg_search_by_year()
{
	return "   Search by Year     \n";
}
// ===============================
// === MENU DISPLAY ALL TRACKS ===
std::string msg_display_all_empty_list()
{
	return "\n RadioStation has no music tracks availale.\n";
}
// ===============================
// === MENU DISPLAY MUSIC PAGE ===
std::string msg_display_page_unavailable()
{
	return "<unavailable>";
}
// ===============================
// ====== MENU MY PlAYLIST =======
std::string msg_playlist_empty()
{
	return "\n Playlist is Empty.\n";
}
// ===============================
// ===== SHOW DAY PLAYLIST =======
std::string msg_day_playlist_empty()
{
	return "\n No playlist yet generated.\n";
}
// ===============================
// ===== AUXILIARY KEY MENU ======
std::string msg_aux_key_like_error()
{
	return "\n You have already liked this music (you can only like once)\n";
}
std::string msg_aux_key_dislike_error()
{
	return "\n You have already disliked this music (you can only dislike once)\n";
}
std::string msg_aux_key_help()
{
	return "\n UP/DOWN    - SWITCH BETWEEN MUSICS;\n\n LEFT/RIGHT - SWITCH BETWEEN PAGES;\n\n ENTER      - DETAILED VIEW;\n\n        P   - ADD/REMOVE FROM PLAYLIST;\n\n        L   - LIKE MUSIC TRACK;\n\n        D   - DISLIKE MUSIC TRACK;\n\n";
}
std::string msg_aux_key_help_special()
{
	return "        E   - EDIT MUSIC TRACK;\n\n CTRL + U   - SET MUSIC TRACK AVAILABLE/NON AVAILABLE;\n\n CTRL + R   - RESET LIKES/DISLIKES FROM CURRENT MUSIC TRACK;\n\n CTRL + A   - RESET ALL LIKES/DISLIKES;\n\n CTRL + DEL - DELETE MUSIC TRACK;\n\n";
}
std::string msg_aux_key_edit()
{
	return "\n Edit? ";
}
// ===============================
// ========== RESET ALL ==========
std::string msg_reset_all_title()
{
	return " Reset like/dislike count\n\n Are you sure?";
}
// ===============================
// ======== INSTRUCTIONS =========
std::string msg_instr_main_menu() {
	return "\n\n     [ENTER] - Select\n\n [BACKSPACE] - Log off";
}
std::string msg_instr_menu_choice()
{
	return "\n\n [ESC] - quit";
}
std::string msg_instr_menuLogin_Register()
{
	return "\n Type [quit] to return.\n\n\n";
}
std::string msg_instr_createNewUser()
{
	return "\n Type [quit] to return.\n\n\n";
}
std::string msg_instr_createNewUser_age()
{
	return "\n Type [0] to return.\n\n";
}
std::string msg_instr_edit_profile()
{
	return "\n\n     [ENTER] - Select\n\n [BACKSPACE] - Return";
}
std::string msg_instr_search()
{
	return "\n\n [ENTER] - Select\n [BACKSPACE] - Return";
}
std::string msg_instr_display_all()
{
	return "\n\n [BACKSPACE] - Return";
}
std::string msg_instr_display_page()
{
	return "\n Help: CTRL + K\n\n";
}
std::string msg_instr_playlist()
{
	return "\n\n\n       [DEL] - Erase Music\n\n     [ENTER] - Detailed View\n\n [BACKSPACE] - Return";
}
std::string msg_instr_top_ten()
{
	return "     [ENTER] - detailed view\n\n [BACKSPACE] - Return";
}
// ==============================================
// =================             ================
// =================  MENUS END  ================
// =================             ================
// ==============================================
// ===============================
// ========== GENERIC ============
std::string msg_base_title()
{
	return "Title";
}
std::string msg_author()
{
	return "Author";
}
std::string msg_album()
{
	return "Album";
}
std::string msg_genre()
{
	return "Genre";
}
std::string msg_year()
{
	return "Year";
}
std::string msg_playlist()
{
	return "Playlist?";
}
std::string msg_popular()
{
	return "Popular";
}
std::string msg_like()
{
	return "Like?";
}
std::string msg_page()
{
	return "Page: ";
}
std::string msg_option_no()
{
	return "\n\n  [NO]     YES";
}
std::string msg_option_yes()
{
	return "\n\n   NO     [YES]";
}
std::string msg_vector_empty()
{
	return "\n Vector is empty. \n";
}
// ===============================
// =========== FILES =============
std::string msg_file_removed() {
	std::string text = "\n File successfully removed.";
	return text;
}
// ===============================
// =========== OTHERS ============
std::string msg_try_again() {
	return "\n Please try again.";
}
std::string msg_press_any_key() {
	return "\n Press any key to continue.";
}