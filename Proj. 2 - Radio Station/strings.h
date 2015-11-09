#ifndef STRINGS_H_INCLUDED
#define STRING_H_INCLUDED

/* ==========================================
TITLE: STRINGS								|
											|
AUTHORS: Kevin Amorim - ei12057				|
		 Luís Magalhães - ei12054			|
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
Just have to call the function and			|
the corresponding string is returned.		|
											|
											|
   -->  DEVELOPED WITH WINDOWS 8.  <--		|
============================================*/

#include <string>

// ==============================================================
// ========================= DELIMITER  =========================
// ==============================================================
std::string delimiter();
// ==============================================================
// ======================= ERROR MESSAGES =======================
// ==============================================================
// ============ FILES ============
// ERROR 0.
std::string cantOpenFileMsg();
// ERROR 1.
std::string cantSaveFileMsg();
// ERROR 2.
std::string cantRemoveFileMsg();
// ERROR 3.
std::string cantCreateFileMsg();
// ERROR 18
std::string cantRenameFileMsg();
// ERROR 19
std::string digitCountExceedMsg();
// ===============================
// ========== VECTORS ============
// ERROR 4.
std::string vectorIsEmptyMsg();
// ERROR 5.
std::string vectorSizeExceededMsg();
// ===============================
// ======= RADIO STATION =========
// ERROR 6.
std::string cantCreateRadioStationMsg();
// ERROR 7.
std::string cantSaveRadioStationMsg();
// ERROR 8.
std::string cantLoadRadioStationMsg();
// ===============================
// =========== USERS =============
// ERROR 9.
std::string cantCreateUserMsg();
// ERROR 10.
std::string cantSaveUserMsg();
// ERROR 11.
std::string cantLoadUserMsg();
// ===============================
// =========== MUSICS ============
// ERROR 12.
std::string cantCreateMusicMsg();
// ERROR 13.
std::string cantSaveMusicMsg();
// ERROR 14.
std::string cantLoadMusicMsg();
// ERROR 15.
std::string cantRemoveMusicMsg();
// ERROR 16.
std::string cantGenerateRandomPlaylistMsg();
// ERROR 17.
std::string cantRateMusicMsg();
// ==============================================================
// ==============================================================
// ==================== PARTICULAR MESSAGES =====================
// ==============================================================
// ======= RADIO STATION =========
// Radio successfully created.
std::string msg_radio_station_created();
// Radio successfully saved.
std::string msg_radio_station_saved();
// Radio successfully loaded.
std::string msg_radio_station_loaded();
// ===============================
// =========== USERS =============
// User successfully created.
std::string msg_user_created();
// User successfully saved.
std::string msg_user_saved();
// User successfully loaded.
std::string msg_user_loaded();
// Wrong password.
std::string msg_user_error_password();
// User not found.
std::string msg_user_error_not_found();
// User already in use.
std::string msg_user_error_repeated();
// ===============================
// ========= EDITORS =============
// Asks for new username.
std::string msg_user_new_username();
// Asks for new age.
std::string msg_user_new_age();
// Asks for new password.
std::string msg_user_new_password();
// Gender changed.
std::string msg_user_new_gender_success();
// ===============================
// =========== MUSICS ============
// Music successfully created.
std::string msg_music_created();
// Music successfully saved.
std::string msg_music_saved();
// Music successfully loaded.
std::string msg_music_loaded();
// Music successfully removed.
std::string msg_music_removed();
// Random playlist successfully generated.
std::string msg_random_playlist_success();
// Confirms successfull music rating.
std::string msg_rating_successful();
// ===============================
// =========== SEARCH ============
// Keyword not found when trying to search.
std::string msg_keyword_not_found();
// ===============================
// ========== MAIN MENU ==========
std::string msg_title();
std::string msg_item_BROWSE();
std::string msg_item_MY_PLAYLIST();
std::string msg_item_TOP_TEN();
std::string msg_item_SEARCH_MUSIC();
std::string msg_item_SHOW_PLAYLIST_DAY();
std::string msg_item_GENERATE();
std::string msg_item_RESET_HITS();
std::string msg_item_ADD_MUSIC();
std::string msg_item_PRIZE();
std::string msg_item_CHANGE_PROFILE();
std::string msg_item_LOGOFF();
std::string msg_sub_menu_GENERATE();
// ===============================
// ========= MENU CHOICE =========
std::string msg_choice_title();
std::string msg_choice_login_title();
std::string msg_choice_register_title();
// ===============================
// ===== MENU LOGIN/REGISTER =====
std::string msg_logReg_login();
std::string msg_logReg_pass();
// ===============================
// == MENU CREATE RADIO STATION ==
std::string msg_create_rstation_title();
std::string msg_create_rstation_name();
std::string msg_create_rstation_name_error();
// ===============================
// ==== MENU CREATE NEW USER =====
std::string msg_create_new_user_name();
std::string msg_create_new_user_pass();
std::string msg_create_new_user_age();
std::string msg_create_new_user_gender();
// ===============================
// === MENU EDIT USER PROFILE ====
std::string msg_edit_profile_title();
std::string msg_edit_profile_name();
std::string msg_edit_profile_age();
std::string msg_edit_profile_gender();
std::string msg_edit_profile_pass();
// ===============================
// ========= MENU SEARCH =========
std::string msg_search_keyword();
std::string msg_search_by_title();
std::string msg_search_by_author();
std::string msg_search_by_album();
std::string msg_search_by_genre();
std::string msg_search_by_year();
// ===============================
// === MENU DISPLAY ALL TRACKS ===
std::string msg_display_all_empty_list();
// ===============================
// === MENU DISPLAY MUSIC PAGE ===
std::string msg_display_page_unavailable();
// ===============================
// ====== MENU MY PlAYLIST =======
std::string msg_playlist_empty();
// ===============================
// ===== SHOW DAY PLAYLIST =======
std::string msg_day_playlist_empty();
// ===============================
// ===== AUXILIARY KEY MENU ======
std::string msg_aux_key_like_error();
std::string msg_aux_key_dislike_error();
std::string msg_aux_key_help();
std::string msg_aux_key_help_special();
std::string msg_aux_key_edit();
// ===============================
// ========== RESET ALL ==========
std::string msg_reset_all_title();
// ===============================
// ======== INSTRUCTIONS =========
std::string msg_instr_main_menu();
std::string msg_instr_menu_choice();
std::string msg_instr_menuLogin_Register();
std::string msg_instr_createNewUser();
std::string msg_instr_createNewUser_age();
std::string msg_instr_edit_profile();
std::string msg_instr_search();
std::string msg_instr_display_all();
std::string msg_instr_display_page();
std::string msg_instr_playlist();
std::string msg_instr_top_ten();
// ===============================
// =========== GENERIC ===========
std::string msg_base_title();
std::string msg_author();
std::string msg_album();
std::string msg_genre();
std::string msg_year();
std::string msg_playlist();
std::string msg_popular();
std::string msg_like();
std::string msg_page();
std::string msg_option_no();
std::string msg_option_yes();
std::string msg_vector_empty();
// ===============================
// =========== FILES =============
std::string msg_file_removed();
// ===============================
// =========== OTHERS ============
// Simple try again message.
std::string msg_try_again();
// Press any key message.
std::string msg_press_any_key();
// ===============================
// ==============================================================
#endif