#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
// начало миссии метод mission_ovalring_start()

int HG_BEST_NASCAR_RESULT, HG_NASCAR_BEST_TIME, HG_NASCAR_BEST_LAP_TIME; // глобалки для сохранения результатов

// дефолтные значения при загрузке игры
//HG_NASCAR_BEST_LAP_TIME = 999999;
//HG_NASCAR_BEST_TIME = 999999;
//HG_BEST_NASCAR_RESULT = 999999;

int showcase, showcase_timer, nascar_laps, player_result, gosub_result;
int heading_done_flag, gosub_nascar, gosub_driver, true_false, nascar_best_time_last;
int	nascar_lap_timer, nascar_time, nascar_lap_timer_start, do_winning_text_shite;
int players_nascar, players_nascar_health, skip_scut_button, miliseconds;
int hot_audio_flag, last_audio_played, hotring_finished_timer;
int textur, fon;

int nascar1, car1_laps, car1_result, nascar1_timer;
int nascar2, car2_laps, car2_result, nascar2_timer;
int nascar3, car3_laps, car3_result, nascar3_timer;
int nascar4, driver_car4, car4_cpcounter, car4_laps, car4_result, nascar4_timer;
int nascar5, driver_car5, car5_cpcounter, car5_laps, car5_result, nascar5_timer;
int nascar6, driver_car6, car6_cpcounter, car6_laps, car6_result, nascar6_timer;
int nascar7, driver_car7, car7_cpcounter, car7_laps, car7_result, nascar7_timer;
int nascar8, driver_car8, car8_cpcounter, car8_laps, car8_result, nascar8_timer;
int nascar9, driver_car9, car9_cpcounter, car9_laps, car9_result, nascar9_timer;
int nascar10, driver_car10, car10_cpcounter, car10_laps, car10_result, nascar10_timer;
int nascar11, driver_car11, car11_cpcounter, car11_laps, car11_result, nascar11_timer;
int nascar12, driver_car12, car12_cpcounter, car12_laps, car12_result, nascar12_timer;
int nascar13, driver_car13, car13_cpcounter, car13_laps, car13_result, nascar13_timer;
int nascar14, driver_car14, car14_cpcounter, car14_laps, car14_result, nascar14_timer;
int nascar15, driver_car15, car15_cpcounter, car15_laps, car15_result, nascar15_timer;

int car4_stuck_timer, car5_stuck_timer;
int car6_stuck_timer, car7_stuck_timer, car8_stuck_timer, car9_stuck_timer, car10_stuck_timer;
int car11_stuck_timer, car12_stuck_timer, car13_stuck_timer, car14_stuck_timer, car15_stuck_timer;

float car9_cp_x, car9_cp_y, car9_cp_z;
float car10_cp_x, car10_cp_y, car10_cp_z; 
float car11_cp_x, car11_cp_y, car11_cp_z; 
float car12_cp_x, car12_cp_y, car12_cp_z; 
float car13_cp_x, car13_cp_y, car13_cp_z; 
float car14_cp_x, car14_cp_y, car14_cp_z; 
float car15_cp_x, car15_cp_y, car15_cp_z; 

float car4_stuck_x, car4_stuck_y, car4_stuck_z;	
float car5_stuck_x, car5_stuck_y, car5_stuck_z;	
float car6_stuck_x, car6_stuck_y, car6_stuck_z;	
float car7_stuck_x, car7_stuck_y, car7_stuck_z;	
float car8_stuck_x, car8_stuck_y, car8_stuck_z;	
float car9_stuck_x, car9_stuck_y, car9_stuck_z;	
float car10_stuck_x, car10_stuck_y, car10_stuck_z; 
float car11_stuck_x, car11_stuck_y, car11_stuck_z; 
float car12_stuck_x, car12_stuck_y, car12_stuck_z; 
float car13_stuck_x, car13_stuck_y, car13_stuck_z; 
float car14_stuck_x, car14_stuck_y, car14_stuck_z; 
float car15_stuck_x, car15_stuck_y, car15_stuck_z;
float carH3, carHUD_y3;

float car4_cp_x, car4_cp_y, car4_cp_z;
float car5_cp_x, car5_cp_y, car5_cp_z;
float car6_cp_x, car6_cp_y, car6_cp_z;
float car7_cp_x, car7_cp_y, car7_cp_z;
float car8_cp_x, car8_cp_y, car8_cp_z;

int car;
int driver_car1, driver_car2, driver_car3;
int player_cpcounter, car1_cpcounter, car2_cpcounter, car3_cpcounter, gosub_cpcounter;
int position, mins, seconds, temp_int;
int players_car;
int car1_stuck_timer, car2_stuck_timer, car3_stuck_timer, game_timer;
float car_x, car_y, z;
float car_distance_from_cp, player1_distance_from_cp;
float player1_cp_x, player1_cp_y, player1_cp_z;
float car1_cp_x, car1_cp_y, car1_cp_z;
float car2_cp_x, car2_cp_y, car2_cp_z;
float car3_cp_x, car3_cp_y, car3_cp_z;
float car1_stuck_x, car1_stuck_y, car1_stuck_z;
float car2_stuck_x, car2_stuck_y, car2_stuck_z;
float car3_stuck_x, car3_stuck_y, car3_stuck_z;
float gosub_cp_x, gosub_cp_y, gosub_cp_z;
float cp1_x, cp1_y, cp1_z;
float cp2_x, cp2_y, cp2_z;
float cp3_x, cp3_y, cp3_z;
float cp4_x, cp4_y, cp4_z;
float cp5_x, cp5_y, cp5_z;
float cp6_x, cp6_y, cp6_z;
float cp7_x, cp7_y, cp7_z;
float cp8_x, cp8_y, cp8_z;
float cp9_x, cp9_y, cp9_z;
float cp10_x, cp10_y, cp10_z;
float finish_laps;
int cam;
int show_hud;
int sID;
uint hour, minute, weather;
uint car_HP1, car_HP2, car_HP3, car_HP4, car_HP5, car_HP6, car_HP7, car_HP8, car_HP9, car_HP10, car_HP11, car_HP12, car_HP13, car_HP14, car_HP15;
uint CarM1 = MODEL_CHAVOS;// 
uint CarM2 = MODEL_FELTZER;//
uint CarM3 = MODEL_FEROCI;//
uint PedM1 = MODEL_M_M_PINDUS_01;//


#define KEYBOARD_ENTER			28		/*rebusx*/
#define KEYBOARD_SPACE			57
#define CONTROL_KEYBOARD_HORN	54
#define CONTROL_MOUSE_LEFT		38

#define CONTROLLER_BUTTON_B		17

int check_skip_intro()
{
	if ( (!IS_USING_CONTROLLER() && (IS_GAME_KEYBOARD_KEY_PRESSED(KEYBOARD_ENTER) || IS_GAME_KEYBOARD_KEY_PRESSED(KEYBOARD_SPACE) || IS_CONTROL_PRESSED(2, CONTROL_KEYBOARD_HORN) || IS_CONTROL_PRESSED(2, CONTROL_MOUSE_LEFT)))
	|| (IS_USING_CONTROLLER() && IS_BUTTON_PRESSED(0, CONTROLLER_BUTTON_B)) )
	{
		return 1;
	}
	return 0;
}


void setup_text_shite_hot(void) {
	SET_TEXT_COLOUR(180, 180, 180, 255);
	SET_TEXT_JUSTIFY(1);
	SET_TEXT_RIGHT_JUSTIFY(0);
	SET_TEXT_DROPSHADOW(1, 0, 0, 0, 255);
	SET_TEXT_PROPORTIONAL(1);
	SET_TEXT_CENTRE(0);
	SET_TEXT_BACKGROUND(0);
	SET_TEXT_SCALE(0.3, 0.8);
}

void setup_draw_text(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.156, 0.267);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
}

void setup_draw_value(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.312, 0.534);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
}

void setup_draw_time(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.26, 0.445);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
}

void work_out_players_position(void) {
	if (player_result == gosub_result) {
		if (!IS_CAR_DEAD(car)) {
			GET_CAR_COORDINATES(car, &car_x, &car_y, &z);
			GET_DISTANCE_BETWEEN_COORDS_2D(car_x, car_y, player1_cp_x, player1_cp_y, &car_distance_from_cp);
			GET_CHAR_COORDINATES(GetPlayerPed(), &car_x, &car_y, &z);
			GET_DISTANCE_BETWEEN_COORDS_2D(car_x, car_y, player1_cp_x, player1_cp_y, &player1_distance_from_cp);
			if (player1_distance_from_cp > car_distance_from_cp) {
				position++;
			}
		}
	}
	if (player_result < gosub_result) {
		position++;
	}
	return;
}

void get_next_ovalring_checkpoint(void) {
	if (gosub_cpcounter == 0) {
		gosub_cp_x = cp1_x;
		gosub_cp_y = cp1_y;
		gosub_cp_z = cp1_z;
	}

	if (gosub_cpcounter == 1) {
		gosub_cp_x = cp2_x;
		gosub_cp_y = cp2_y;
		gosub_cp_z = cp2_z;
	}

	if (gosub_cpcounter == 2) {
		gosub_cp_x = cp3_x;
		gosub_cp_y = cp3_y;
		gosub_cp_z = cp3_z;
	}

	if (gosub_cpcounter == 3) {
		gosub_cp_x = cp4_x;
		gosub_cp_y = cp4_y;
		gosub_cp_z = cp4_z;
	}

	if (gosub_cpcounter == 4) {
		gosub_cp_x = cp5_x;
		gosub_cp_y = cp5_y;
		gosub_cp_z = cp5_z;
	}

	if (gosub_cpcounter == 5) {
		gosub_cp_x = cp6_x;
		gosub_cp_y = cp6_y;
		gosub_cp_z = cp6_z;
	}

	if (gosub_cpcounter == 6) {
		gosub_cp_x = cp7_x;
		gosub_cp_y = cp7_y;
		gosub_cp_z = cp7_z;
	}

	if (gosub_cpcounter == 7) {
		gosub_cp_x = cp8_x;
		gosub_cp_y = cp8_y;
		gosub_cp_z = cp8_z;
	}

	if (gosub_cpcounter == 8) {
		gosub_cp_x = cp9_x;
		gosub_cp_y = cp9_y;
		gosub_cp_z = cp9_z;
	}

	if (gosub_cpcounter == 9) {
		gosub_cp_x = cp10_x;
		gosub_cp_y = cp10_y;
		gosub_cp_z = cp10_z;
		gosub_cpcounter = -1;
	}

	gosub_cpcounter++;
	return;
}

void freeze_all_cars(void) {
	if (!IS_CAR_DEAD(nascar1)) {
		FREEZE_CAR_POSITION(nascar1, true_false);
	}
	if (!IS_CAR_DEAD(nascar2)) {
		FREEZE_CAR_POSITION(nascar2, true_false);
	}
	if (!IS_CAR_DEAD(nascar3)) {
		FREEZE_CAR_POSITION(nascar3, true_false);
	}
	if (!IS_CAR_DEAD(nascar4)) {
		FREEZE_CAR_POSITION(nascar4, true_false);
	}
	if (!IS_CAR_DEAD(nascar5)) {
		FREEZE_CAR_POSITION(nascar5, true_false);
	}
	if (!IS_CAR_DEAD(nascar6)) {
		FREEZE_CAR_POSITION(nascar6, true_false);
	}
	if (!IS_CAR_DEAD(nascar7)) {
		FREEZE_CAR_POSITION(nascar7, true_false);
	}
	if (!IS_CAR_DEAD(nascar8)) {
		FREEZE_CAR_POSITION(nascar8, true_false);
	}
	if (!IS_CAR_DEAD(nascar9)) {
		FREEZE_CAR_POSITION(nascar9, true_false);
	}
	if (!IS_CAR_DEAD(nascar10)) {
		FREEZE_CAR_POSITION(nascar10, true_false);
	}
	if (!IS_CAR_DEAD(nascar11)) {
		FREEZE_CAR_POSITION(nascar11, true_false);
	}
	if (!IS_CAR_DEAD(nascar12)) {
		FREEZE_CAR_POSITION(nascar12, true_false);
	}
	if (!IS_CAR_DEAD(nascar13)) {
		FREEZE_CAR_POSITION(nascar13, true_false);
	}
	if (!IS_CAR_DEAD(nascar14)) {
		FREEZE_CAR_POSITION(nascar14, true_false);
	}
	if (!IS_CAR_DEAD(nascar15)) {
		FREEZE_CAR_POSITION(nascar15, true_false);
	}
	if (!IS_CAR_DEAD(players_nascar)) {
		FREEZE_CAR_POSITION(players_nascar, true_false);
	}
	return;
}

void setup_nascar_stuff(void) {
	if (heading_done_flag == 1) {
		SET_CAR_HEADING(gosub_nascar, 301.7480);
	}
	LOCK_CAR_DOORS(gosub_nascar, 1);
	SET_CAR_PROOFS(gosub_nascar, 0, 1, 1, 0, 0);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(gosub_nascar, 5.0);
	GET_DRIVER_OF_CAR(gosub_nascar, &gosub_driver);
	if (gosub_driver == 0) {
		CREATE_CHAR_INSIDE_CAR(gosub_nascar, 5, PedM1, &gosub_driver);
		SET_CHAR_CANT_BE_DRAGGED_OUT(gosub_driver, 1);
	}
	SET_DRIVE_TASK_CRUISE_SPEED(gosub_driver, 100.0);
	SET_CAR_ENGINE_ON(gosub_nascar, 1, 1);
	return;
}

void mission_ovalring_cleanup(void) {
	STOP_STREAM();
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);

	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar1);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar2);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar3);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar4);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar5);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar6);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar7);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar8);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar9);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar10);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar11);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar12);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar13);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar14);
	MARK_CAR_AS_NO_LONGER_NEEDED(&nascar15);
	MARK_CAR_AS_NO_LONGER_NEEDED(&gosub_driver);

	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car1);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car2);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car3);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car4);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car5);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car6);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car7);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car8);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car9);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car10);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car11);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car12);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car13);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car14);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car15);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&gosub_driver);

	RELEASE_TEXTURE( fon );
	REMOVE_TXD( textur );
	FORWARD_TO_TIME_OF_DAY(01, 05);//устанавливаем время
	FORCE_WEATHER_NOW( weather );//устанавливаем погода
	RELEASE_WEATHER();

	REMOVE_IPL("blodring");
	STOP_SOUND(sID);
	RELEASE_SOUND_ID(sID);
	AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED();
	SET_MAX_WANTED_LEVEL(6);
	ENABLE_FRONTEND_RADIO();
	CLEAR_HELP();
	TERMINATE_THIS_SCRIPT();
}

void mission_ovalring_passed(void) {
	if (!HAS_DEATHARREST_EXECUTED()) {
		while ((!IS_CHAR_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_ON_FOOT(GetPlayerPed()))) {
			WAIT(0);
		}
		if (IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
			WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), -669.7229, 1863.9585, 14.0290);
		} else {
			SET_CHAR_COORDINATES(GetPlayerPed(), -669.7229, 1863.9585, 14.0290);
		}
		SET_CHAR_HEADING(GetPlayerPed(), 274.1051);	
		LOAD_SCENE(-669.7229, 1863.9585, 14.0290);
		SET_CAM_BEHIND_PED(GetPlayerPed());
		DO_SCREEN_FADE_IN(1500);
	}
	mission_ovalring_cleanup();
}

void mission_ovalring_failed(void) {
	if (!HAS_DEATHARREST_EXECUTED()) {
		DO_SCREEN_FADE_OUT(1000);
		while (IS_SCREEN_FADING()) {
			WAIT(0);
		}
		while ((!IS_CHAR_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_ON_FOOT(GetPlayerPed()))) {
			WAIT(0);
		}
		if (IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
			WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), -669.7229, 1863.9585, 14.0290);
		} else {
			SET_CHAR_COORDINATES(GetPlayerPed(), -669.7229, 1863.9585, 14.0290);
		}
		SET_CHAR_HEADING(GetPlayerPed(), 274.1051);
		LOAD_SCENE(-669.7229, 1863.9585, 14.0290);
		SET_CAM_BEHIND_PED(GetPlayerPed());
		DO_SCREEN_FADE_IN(1000);
	}
	if (G_HOTRING == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
	}
	mission_ovalring_cleanup();
}

void ovalring_loop(void) {
	GET_GAME_TIMER(&game_timer);
	if (LOCATE_CHAR_ON_FOOT_3D(GetPlayerPed(), -935.3669, 1770.6904, 26.6631, 1.5, 2.0, 1.5, 1)) {
		PRINT_NOW("HOTR_14", 2500, 1);	// ~r~You have been disqualified!
		mission_ovalring_failed();		
	}
	if (showcase < 5) {
		if (showcase > -1) {
			if (check_skip_intro()) {		/*rebusx*/
				if (skip_scut_button == 1) {
					CLEAR_SMALL_PRINTS();
					showcase_timer = game_timer	- 100;
					showcase = 5;
				}
			} else {
				if (skip_scut_button == 0) {
					skip_scut_button = 1;
				}
			}
		}
	}
	
	if (showcase == -1) {
		do_winning_text_shite = 2;
		if (!IS_SCREEN_FADING()) {
			showcase_timer = game_timer + 3000;
			showcase = 0;
		}
	}
	
	if (showcase == 0) {
		if (game_timer > showcase_timer) {
			SET_CAM_POS(cam, -855.2798, 1787.7667, 25.5532);
			POINT_CAM_AT_COORD(cam, -856.2418, 1787.5203, 25.4369);
			showcase_timer = game_timer + 3000;
			showcase = 1;
		}
	}
	
	if (showcase == 1) {
		if (game_timer > showcase_timer) {
			SET_CAM_POS(cam, -843.6191, 1943.3262, 29.3251);
			POINT_CAM_AT_COORD(cam, -844.595, 1943.4907, 29.1815);
			PRINT_NOW("HOTR_02", 3500, 1);		// ~g~If your car is destroyed you will be disqualified.
			showcase_timer = game_timer + 3500;
			showcase = 2;
		}
	}
	
	if (showcase == 2) {
		if (game_timer > showcase_timer) {
			SET_CAM_POS(cam, -899.1445, 1971.0899, 30.8932);
			POINT_CAM_AT_COORD(cam, -900.0636, 1970.9577, 30.5222);
			PRINT_NOW("HOTR_03", 4500, 1);		// ~g~When your car is damaged you can get it repaired at the pitstop.
			showcase_timer = game_timer + 4500;
			showcase = 3;
		}
	}
	
	if (showcase == 3) {
		if (game_timer > showcase_timer) {
			SET_CAM_POS(cam, -917.81, 1787.146, 28.512);
			POINT_CAM_AT_COORD(cam, -927.77, 1777.356, 28.056);
			PRINT_NOW("HOTR_04", 4500, 1);	// ~g~This is the way to leave the stadium.
			showcase_timer = game_timer + 2500;
			showcase = 4;
		}
	}
	
	if (showcase == 4) {
		if (game_timer > showcase_timer) {
			SET_CAM_POS(cam, -928.9432, 1776.7494, 29.8074);
			POINT_CAM_AT_COORD(cam, -930.863, 1774.946, 28.955);
			showcase_timer = game_timer + 2000;
			showcase = 5;
		}	
	}
	
	if (showcase == 5) {
		if (game_timer > showcase_timer) {
			do_winning_text_shite = 0;
			ACTIVATE_SCRIPTED_CAMS(0, 0);
			SET_CAM_BEHIND_PED(GetPlayerPed());
			DISABLE_FRONTEND_RADIO();
			SET_INSTANT_WIDESCREEN_BORDERS(0);
			//PRINT_BIG("RACES_4", 1100, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			showcase_timer = game_timer + 1000;
			showcase = 6;
		}
	}
	
	if (showcase == 6) {
		SET_TEXT_FONT(4);
		SET_TEXT_COLOUR(235, 115, 18, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(2, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "HOTR_NB", 3);// 3
		if (game_timer > showcase_timer) {
			//PRINT_BIG("RACES_5", 1100, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			showcase_timer = game_timer + 1000;
			showcase = 7;
		}
	}
	
	if (showcase == 7) {
		SET_TEXT_FONT(4);
		SET_TEXT_COLOUR(235, 115, 18, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(2, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "HOTR_NB", 2);// 2
		if (game_timer > showcase_timer) {
			//PRINT_BIG("RACES_6", 1100, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			showcase_timer = game_timer + 1000;
			showcase = 8;
		}
	}
	
	if (showcase == 8) {
		SET_TEXT_FONT(4);
		SET_TEXT_COLOUR(235, 115, 18, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(2, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "HOTR_NB", 1);// 1
		if (game_timer > showcase_timer) {
			if (!IS_CAR_DEAD(players_nascar)) {
				true_false = 0;
				freeze_all_cars();
				//PRINT_BIG("RACES_7", 800, 1);
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_GO");
				SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
				SET_EVERYONE_IGNORE_PLAYER(GetPlayerIndex(), 0);
				SET_ALL_CARS_CAN_BE_DAMAGED(1);
				gosub_cpcounter = player_cpcounter;
				get_next_ovalring_checkpoint();
				player1_cp_x = gosub_cp_x;
				player1_cp_y = gosub_cp_y;
				player1_cp_z = gosub_cp_z;
				player_cpcounter = gosub_cpcounter;
				nascar_lap_timer_start = game_timer;
				SETTIMERC( 0 );
				SETTIMERB(0);
				show_hud = true;
				showcase = 9;
			}
		}
	}
	if (TIMERC() < 900)
	{
		SET_TEXT_FONT(4);
		SET_TEXT_COLOUR(235, 115, 18, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(2, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "RACES_7", 1); // пишем "GO"
	}

	if (showcase == 9) {
		if (show_hud) {
			DRAW_SPRITE(fon, 0.8765625, 0.7858, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
			DRAW_SPRITE(fon, 0.8765625, 0.8194, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
			DRAW_SPRITE(fon, 0.8765625, 0.853, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
			DRAW_SPRITE(fon, 0.8765625, 0.8866, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
			DRAW_SPRITE(0, 0.915054, 0.853, 0.059166, 0.014, 0.0, 27, 89, 130, 255);
			
			setup_draw_text();
			DISPLAY_TEXT(0.78815097, 0.77731852, "HOTR_09");
			if (position > 9) {
				setup_draw_value();
				DISPLAY_TEXT_WITH_NUMBER(0.91315097, 0.76831852, "HOTR_NB", position);
			} else {
				setup_draw_value();
				DISPLAY_TEXT_WITH_NUMBER(0.92015097, 0.76831852, "HOTR_NB", position);
			}
			if (position == 1) {
				setup_draw_text();
				DISPLAY_TEXT(0.93099, 0.7713666, "ST");
			} else if (position == 2) {
				setup_draw_text();
				DISPLAY_TEXT(0.93099, 0.7713666, "ND");
			} else if (position == 3) {
				setup_draw_text();
				DISPLAY_TEXT(0.93099, 0.7713666, "RD");
			} else {
				setup_draw_text();
				DISPLAY_TEXT(0.93099, 0.7713666, "TH");
			}
			
			setup_draw_text();
			DISPLAY_TEXT(0.78815097, 0.84451852, "HOTR_05");
			setup_draw_value();
			carH3 = players_nascar_health * 0.059166 / 100.0;
			carHUD_y3 = (0.915054 + carH3 / 2.0) - 0.059166 / 2.0;
			DRAW_SPRITE(0, carHUD_y3, 0.853, carH3, 0.014, 0.0, 97, 194, 247, 255);
			setup_draw_text();
			DISPLAY_TEXT(0.78815097, 0.81091852, "HOTR_06");		
			setup_draw_time();	
			if (nascar_laps > 8) {
				DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.80454074, "HOTR_L1", nascar_laps + 1);
			}
			else {
				DISPLAY_TEXT_WITH_NUMBER(0.91315097, 0.80454074, "HOTR_L1", nascar_laps + 1);
			}
			setup_draw_text();
			nascar_time = TIMERB();
			int timemin, timesec, timetemp;
			timesec = nascar_time / 1000;
			timemin = timesec / 60;
			timetemp = timemin * 60;
			timesec -= timetemp;
			setup_draw_text();	

			DISPLAY_TEXT(0.78815097, 0.87811852, "HOTR_1A");
			if ((timesec > 9) && (timemin > 9)) {
				setup_draw_time();
				DISPLAY_TEXT_WITH_2_NUMBERS(0.9088542, 0.87134074, "HOTR_T1", timemin, timesec);
			} else if ((timesec <= 9) && (timemin <= 9)) {
				setup_draw_time();
				DISPLAY_TEXT_WITH_2_NUMBERS(0.9088542, 0.87134074, "HOTR_T3", timemin, timesec);
			} else if ((timesec > 9) && (timemin <= 9)) {
				setup_draw_time();
				DISPLAY_TEXT_WITH_2_NUMBERS(0.9088542, 0.87134074, "HOTR_T2", timemin, timesec);
			} else if ((timesec <= 9) && (timemin > 9)) {
				setup_draw_time();
				DISPLAY_TEXT_WITH_2_NUMBERS(0.9088542, 0.87134074, "HOTR_T0", timemin, timesec);
			}
		}
		if (HAS_DEATHARREST_EXECUTED()) {
			mission_ovalring_failed();
		}
		position = 1;
		if (IS_CAR_DEAD(players_nascar)) {
			PRINT_NOW("HOTR_12", 2000, 1);	// ~r~Your car has been destroyed!
			mission_ovalring_failed();
		} else {
			if ((IS_CAR_STOPPED(players_nascar)) && (LOCATE_CAR_3D(players_nascar, -916.983, 1969.829, 25.971, 9.0, 4.0, 5.0, 1))) {
				if (IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), players_nascar)) {
					GET_CAR_HEALTH(players_nascar, &players_nascar_health);
					if (IS_CAR_ON_FIRE(players_nascar)) {
						EXTINGUISH_CAR_FIRE(players_nascar);
					}
					SET_ENGINE_HEALTH(players_nascar, 1000);
					players_nascar_health += 5;
					if (players_nascar_health > 1250) {
						players_nascar_health = 1250;
					}
					SET_CAR_HEALTH(players_nascar, players_nascar_health);
				}
			}
			GET_CAR_HEALTH(players_nascar, &players_nascar_health);
			players_nascar_health -= 250;
			players_nascar_health /= 10;
			if (players_nascar_health < 0) {
				players_nascar_health = 0;
			}
		}
		if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), player1_cp_x, player1_cp_y, player1_cp_z, 24.0, 24.0, 24.0, 0)) {
			gosub_cpcounter = player_cpcounter;
			get_next_ovalring_checkpoint();
			player1_cp_x = gosub_cp_x;
			player1_cp_y = gosub_cp_y;
			player1_cp_z = gosub_cp_z;
			player_cpcounter = gosub_cpcounter;
			if (player_cpcounter == 0) {
				nascar_laps++;
				nascar_lap_timer = game_timer - nascar_lap_timer_start;
				seconds = nascar_lap_timer / 1000;
				miliseconds = seconds * 1000;
				temp_int = nascar_lap_timer - miliseconds;
				miliseconds = temp_int / 10;
				if (HG_NASCAR_BEST_LAP_TIME > nascar_lap_timer) {
					HG_NASCAR_BEST_LAP_TIME = nascar_lap_timer;
					if (miliseconds > 9) {
						PRINT_WITH_2_NUMBERS_NOW("HOTR_11", seconds, miliseconds, 5000, 1);
					} else {
						PRINT_WITH_2_NUMBERS_NOW("HOTR_34", seconds, miliseconds, 5000, 1);
					}
				}
				nascar_lap_timer_start = game_timer;
			}
		}
		GET_CAR_HEALTH(nascar1, &car_HP1);
		GET_CAR_HEALTH(nascar2, &car_HP2);
		GET_CAR_HEALTH(nascar3, &car_HP3);
		GET_CAR_HEALTH(nascar4, &car_HP4);
		GET_CAR_HEALTH(nascar5, &car_HP5);
		GET_CAR_HEALTH(nascar6, &car_HP6);
		GET_CAR_HEALTH(nascar7, &car_HP7);
		GET_CAR_HEALTH(nascar8, &car_HP8);
		GET_CAR_HEALTH(nascar9, &car_HP9);
		GET_CAR_HEALTH(nascar10, &car_HP10);
		GET_CAR_HEALTH(nascar11, &car_HP11);
		GET_CAR_HEALTH(nascar12, &car_HP12);
		GET_CAR_HEALTH(nascar13, &car_HP13);
		GET_CAR_HEALTH(nascar14, &car_HP14);
		GET_CAR_HEALTH(nascar15, &car_HP15);
		GET_TIME_OF_DAY(&hour, &minute);

		if ((hour > 21) && (minute > 55)) {
			FORWARD_TO_TIME_OF_DAY(20, 25);//устанавливаем время
		}

		player_result = nascar_laps * 100;
		player_result += player_cpcounter;
		if (car_HP1 < 100) {
			EXPLODE_CAR(nascar1, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar1);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car1);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar1, 1);
				gosub_nascar = nascar1;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car1_laps < nascar_laps) {
					car1_laps = nascar_laps;
				}
				car1_cpcounter = 0;
				gosub_cpcounter = car1_cpcounter;
				get_next_ovalring_checkpoint();
				car1_cp_x = gosub_cp_x;
				car1_cp_y = gosub_cp_y;
				car1_cp_z = gosub_cp_z;
				int seq1;
				OPEN_SEQUENCE_TASK(&seq1);
				TASK_CAR_DRIVE_TO_COORD(0, nascar1, car1_cp_x, car1_cp_y, car1_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq1);
				TASK_PERFORM_SEQUENCE(driver_car1, seq1);
				CLEAR_SEQUENCE_TASK(seq1);
				SET_CAR_FORWARD_SPEED(nascar1, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar1, car1_cp_x, car1_cp_y, car1_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car1_cpcounter;
				get_next_ovalring_checkpoint();
				car1_cp_x = gosub_cp_x;
				car1_cp_y = gosub_cp_y;
				car1_cp_z = gosub_cp_z;
				car1_cpcounter = gosub_cpcounter;
				if (car1_cpcounter == 0) {
					car1_laps++;
				}
				int seq1;
				OPEN_SEQUENCE_TASK(&seq1);
				TASK_CAR_DRIVE_TO_COORD(0, nascar1, car1_cp_x, car1_cp_y, car1_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq1);
				TASK_PERFORM_SEQUENCE(driver_car1, seq1);
				CLEAR_SEQUENCE_TASK(seq1);
				car1_result = car1_laps * 100;
				car1_result += car1_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar1, car1_stuck_x, car1_stuck_y, car1_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car1_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar1, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar1, &car1_stuck_x, &car1_stuck_y, &car1_stuck_z);
				car1_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar1, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar1_timer < game_timer) {
					SET_CAR_HEALTH(nascar1, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar1);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car1);
					nascar1 = -1;
				}
			} else {
				nascar1_timer = game_timer + 3000;
			}
		}
		gosub_result = car1_result;
		car = nascar1;
		work_out_players_position();
		
		if (car_HP2 < 100) {
			EXPLODE_CAR(nascar2, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar2);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car2);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar2, 1);
				gosub_nascar = nascar2;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car2_laps < nascar_laps) {
					car2_laps = nascar_laps;
				}
				car2_cpcounter = 0;
				gosub_cpcounter = car2_cpcounter;
				get_next_ovalring_checkpoint();
				car2_cp_x = gosub_cp_x;
				car2_cp_y = gosub_cp_y;
				car2_cp_z = gosub_cp_z;
				int seq2;
				OPEN_SEQUENCE_TASK(&seq2);
				TASK_CAR_DRIVE_TO_COORD(0, nascar2, car2_cp_x, car2_cp_y, car2_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq2);
				TASK_PERFORM_SEQUENCE(driver_car2, seq2);
				CLEAR_SEQUENCE_TASK(seq2);
				SET_CAR_FORWARD_SPEED(nascar2, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar2, car2_cp_x, car2_cp_y, car2_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car2_cpcounter;
				get_next_ovalring_checkpoint();
				car2_cp_x = gosub_cp_x;
				car2_cp_y = gosub_cp_y;
				car2_cp_z = gosub_cp_z;
				car2_cpcounter = gosub_cpcounter;
				if (car2_cpcounter == 0) {
					car2_laps++;
				}
				int seq2;
				OPEN_SEQUENCE_TASK(&seq2);
				TASK_CAR_DRIVE_TO_COORD(0, nascar2, car2_cp_x, car2_cp_y, car2_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq2);
				TASK_PERFORM_SEQUENCE(driver_car2, seq2);
				CLEAR_SEQUENCE_TASK(seq2);
				car2_result = car2_laps * 100;
				car2_result += car2_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar2, car2_stuck_x, car2_stuck_y, car2_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car2_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar2, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar2, &car2_stuck_x, &car2_stuck_y, &car2_stuck_z);
				car2_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar2, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar2_timer < game_timer) {
					SET_CAR_HEALTH(nascar2, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar2);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car2);
					nascar2 = -1;
				}
			} else {
				nascar2_timer = game_timer + 3000;
			}
		}
		gosub_result = car2_result;
		car = nascar2;
		work_out_players_position();
		
		if (car_HP3 < 100) {
			EXPLODE_CAR(nascar3, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar3);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car3);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar3, 1);
				gosub_nascar = nascar3;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car3_laps < nascar_laps) {
					car3_laps = nascar_laps;
				}
				car3_cpcounter = 0;
				gosub_cpcounter = car3_cpcounter;
				get_next_ovalring_checkpoint();
				car3_cp_x = gosub_cp_x;
				car3_cp_y = gosub_cp_y;
				car3_cp_z = gosub_cp_z;
				int seq3;
				OPEN_SEQUENCE_TASK(&seq3);
				TASK_CAR_DRIVE_TO_COORD(0, nascar3, car3_cp_x, car3_cp_y, car3_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq3);
				TASK_PERFORM_SEQUENCE(driver_car3, seq3);
				CLEAR_SEQUENCE_TASK(seq3);
				SET_CAR_FORWARD_SPEED(nascar3, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar3, car3_cp_x, car3_cp_y, car3_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car3_cpcounter;
				get_next_ovalring_checkpoint();
				car3_cp_x = gosub_cp_x;
				car3_cp_y = gosub_cp_y;
				car3_cp_z = gosub_cp_z;
				car3_cpcounter = gosub_cpcounter;
				if (car3_cpcounter == 0) {
					car3_laps++;
				}
				int seq3;
				OPEN_SEQUENCE_TASK(&seq3);
				TASK_CAR_DRIVE_TO_COORD(0, nascar3, car3_cp_x, car3_cp_y, car3_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq3);
				TASK_PERFORM_SEQUENCE(driver_car3, seq3);
				CLEAR_SEQUENCE_TASK(seq3);
				car3_result = car3_laps * 100;
				car3_result += car3_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar3, car3_stuck_x, car3_stuck_y, car3_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car3_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar3, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar3, &car3_stuck_x, &car3_stuck_y, &car3_stuck_z);
				car3_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar3, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar3_timer < game_timer) {
					SET_CAR_HEALTH(nascar3, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar3);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car3);
					nascar3 = -1;
				}
			} else {
				nascar3_timer = game_timer + 3000;
			}
		}
		gosub_result = car3_result;
		car = nascar3;
		work_out_players_position();
		
		if (car_HP3 < 100) {
			EXPLODE_CAR(nascar3, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar3);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car3);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar3, 1);
				gosub_nascar = nascar3;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car3_laps < nascar_laps) {
					car3_laps = nascar_laps;
				}
				car3_cpcounter = 0;
				gosub_cpcounter = car3_cpcounter;
				get_next_ovalring_checkpoint();
				car3_cp_x = gosub_cp_x;
				car3_cp_y = gosub_cp_y;
				car3_cp_z = gosub_cp_z;
				int seq4;
				OPEN_SEQUENCE_TASK(&seq4);
				TASK_CAR_DRIVE_TO_COORD(0, nascar3, car3_cp_x, car3_cp_y, car3_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq4);
				TASK_PERFORM_SEQUENCE(driver_car3, seq4);
				CLEAR_SEQUENCE_TASK(seq4);
				SET_CAR_FORWARD_SPEED(nascar3, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar3, car3_cp_x, car3_cp_y, car3_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car3_cpcounter;
				get_next_ovalring_checkpoint();
				car3_cp_x = gosub_cp_x;
				car3_cp_y = gosub_cp_y;
				car3_cp_z = gosub_cp_z;
				car3_cpcounter = gosub_cpcounter;
				if (car3_cpcounter == 0) {
					car3_laps++;
				}
				int seq4;
				OPEN_SEQUENCE_TASK(&seq4);
				TASK_CAR_DRIVE_TO_COORD(0, nascar3, car3_cp_x, car3_cp_y, car3_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq4);
				TASK_PERFORM_SEQUENCE(driver_car3, seq4);
				CLEAR_SEQUENCE_TASK(seq4);
				car3_result = car3_laps * 100;
				car3_result += car3_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar3, car3_stuck_x, car3_stuck_y, car3_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car3_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar3, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar3, &car3_stuck_x, &car3_stuck_y, &car3_stuck_z);
				car3_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar3, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar3_timer < game_timer) {
					SET_CAR_HEALTH(nascar3, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar3);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car3);
					nascar3 = -1;
				}
			} else {
				nascar3_timer = game_timer + 3000;
			}
		}
		gosub_result = car3_result;
		car = nascar3;
		work_out_players_position();
		
		if (car_HP4 < 100) {
			EXPLODE_CAR(nascar4, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar4);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car4);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar4, 1);
				gosub_nascar = nascar4;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car4_laps < nascar_laps) {
					car4_laps = nascar_laps;
				}
				car4_cpcounter = 0;
				gosub_cpcounter = car4_cpcounter;
				get_next_ovalring_checkpoint();
				car4_cp_x = gosub_cp_x;
				car4_cp_y = gosub_cp_y;
				car4_cp_z = gosub_cp_z;
				int seq4;
				OPEN_SEQUENCE_TASK(&seq4);
				TASK_CAR_DRIVE_TO_COORD(0, nascar4, car4_cp_x, car4_cp_y, car4_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq4);
				TASK_PERFORM_SEQUENCE(driver_car4, seq4);
				CLEAR_SEQUENCE_TASK(seq4);
				SET_CAR_FORWARD_SPEED(nascar4, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar4, car4_cp_x, car4_cp_y, car4_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car4_cpcounter;
				get_next_ovalring_checkpoint();
				car4_cp_x = gosub_cp_x;
				car4_cp_y = gosub_cp_y;
				car4_cp_z = gosub_cp_z;
				car4_cpcounter = gosub_cpcounter;
				if (car4_cpcounter == 0) {
					car4_laps++;
				}
				int seq4;
				OPEN_SEQUENCE_TASK(&seq4);
				TASK_CAR_DRIVE_TO_COORD(0, nascar4, car4_cp_x, car4_cp_y, car4_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq4);
				TASK_PERFORM_SEQUENCE(driver_car4, seq4);
				CLEAR_SEQUENCE_TASK(seq4);
				car4_result = car4_laps * 100;
				car4_result += car4_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar4, car4_stuck_x, car4_stuck_y, car4_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car4_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar4, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar4, &car4_stuck_x, &car4_stuck_y, &car4_stuck_z);
				car4_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar4, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar4_timer < game_timer) {
					SET_CAR_HEALTH(nascar4, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar4);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car4);
					nascar4 = -1;
				}
			} else {
				nascar4_timer = game_timer + 3000;
			}
		}
		gosub_result = car4_result;
		car = nascar4;
		work_out_players_position();
		
		if (car_HP5 < 100) {
			EXPLODE_CAR(nascar5, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar5);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car5);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar5, 1);
				gosub_nascar = nascar5;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car5_laps < nascar_laps) {
					car5_laps = nascar_laps;
				}
				car5_cpcounter = 0;
				gosub_cpcounter = car5_cpcounter;
				get_next_ovalring_checkpoint();
				car5_cp_x = gosub_cp_x;
				car5_cp_y = gosub_cp_y;
				car5_cp_z = gosub_cp_z;
				int seq5;
				OPEN_SEQUENCE_TASK(&seq5);
				TASK_CAR_DRIVE_TO_COORD(0, nascar5, car5_cp_x, car5_cp_y, car5_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq5);
				TASK_PERFORM_SEQUENCE(driver_car5, seq5);
				CLEAR_SEQUENCE_TASK(seq5);
				SET_CAR_FORWARD_SPEED(nascar5, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar5, car5_cp_x, car5_cp_y, car5_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car5_cpcounter;
				get_next_ovalring_checkpoint();
				car5_cp_x = gosub_cp_x;
				car5_cp_y = gosub_cp_y;
				car5_cp_z = gosub_cp_z;
				car5_cpcounter = gosub_cpcounter;
				if (car5_cpcounter == 0) {
					car5_laps++;
				}
				int seq5;
				OPEN_SEQUENCE_TASK(&seq5);
				TASK_CAR_DRIVE_TO_COORD(0, nascar5, car5_cp_x, car5_cp_y, car5_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq5);
				TASK_PERFORM_SEQUENCE(driver_car5, seq5);
				CLEAR_SEQUENCE_TASK(seq5);
				car5_result = car5_laps * 100;
				car5_result += car5_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar5, car5_stuck_x, car5_stuck_y, car5_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car5_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar5, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar5, &car5_stuck_x, &car5_stuck_y, &car5_stuck_z);
				car5_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar5, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar5_timer < game_timer) {
					SET_CAR_HEALTH(nascar5, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar5);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car5);
					nascar5 = -1;
				}
			} else {
				nascar5_timer = game_timer + 3000;
			}
		}
		gosub_result = car5_result;
		car = nascar5;
		work_out_players_position();
		
		if (car_HP6 < 100) {
			EXPLODE_CAR(nascar6, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar6);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car6);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar6, 1);
				gosub_nascar = nascar6;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car6_laps < nascar_laps) {
					car6_laps = nascar_laps;
				}
				car6_cpcounter = 0;
				gosub_cpcounter = car6_cpcounter;
				get_next_ovalring_checkpoint();
				car6_cp_x = gosub_cp_x;
				car6_cp_y = gosub_cp_y;
				car6_cp_z = gosub_cp_z;
				int seq6;
				OPEN_SEQUENCE_TASK(&seq6);
				TASK_CAR_DRIVE_TO_COORD(0, nascar6, car6_cp_x, car6_cp_y, car6_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq6);
				TASK_PERFORM_SEQUENCE(driver_car6, seq6);
				CLEAR_SEQUENCE_TASK(seq6);
				SET_CAR_FORWARD_SPEED(nascar6, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar6, car6_cp_x, car6_cp_y, car6_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car6_cpcounter;
				get_next_ovalring_checkpoint();
				car6_cp_x = gosub_cp_x;
				car6_cp_y = gosub_cp_y;
				car6_cp_z = gosub_cp_z;
				car6_cpcounter = gosub_cpcounter;
				if (car6_cpcounter == 0) {
					car6_laps++;
				}
				int seq6;
				OPEN_SEQUENCE_TASK(&seq6);
				TASK_CAR_DRIVE_TO_COORD(0, nascar6, car6_cp_x, car6_cp_y, car6_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq6);
				TASK_PERFORM_SEQUENCE(driver_car6, seq6);
				CLEAR_SEQUENCE_TASK(seq6);
				car6_result = car6_laps * 100;
				car6_result += car6_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar6, car6_stuck_x, car6_stuck_y, car6_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car6_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar6, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar6, &car6_stuck_x, &car6_stuck_y, &car6_stuck_z);
				car6_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar6, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar6_timer < game_timer) {
					SET_CAR_HEALTH(nascar6, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar6);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car6);
					nascar6 = -1;
				}
			} else {
				nascar6_timer = game_timer + 3000;
			}
		}
		gosub_result = car6_result;
		car = nascar6;
		work_out_players_position();
		
		if (car_HP7 < 100) {
			EXPLODE_CAR(nascar7, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar7);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car7);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar7, 1);
				gosub_nascar = nascar7;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car7_laps < nascar_laps) {
					car7_laps = nascar_laps;
				}
				car7_cpcounter = 0;
				gosub_cpcounter = car7_cpcounter;
				get_next_ovalring_checkpoint();
				car7_cp_x = gosub_cp_x;
				car7_cp_y = gosub_cp_y;
				car7_cp_z = gosub_cp_z;
				int seq7;
				OPEN_SEQUENCE_TASK(&seq7);
				TASK_CAR_DRIVE_TO_COORD(0, nascar7, car7_cp_x, car7_cp_y, car7_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq7);
				TASK_PERFORM_SEQUENCE(driver_car7, seq7);
				CLEAR_SEQUENCE_TASK(seq7);
				SET_CAR_FORWARD_SPEED(nascar7, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar7, car7_cp_x, car7_cp_y, car7_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car7_cpcounter;
				get_next_ovalring_checkpoint();
				car7_cp_x = gosub_cp_x;
				car7_cp_y = gosub_cp_y;
				car7_cp_z = gosub_cp_z;
				car7_cpcounter = gosub_cpcounter;
				if (car7_cpcounter == 0) {
					car7_laps++;
				}
				int seq7;
				OPEN_SEQUENCE_TASK(&seq7);
				TASK_CAR_DRIVE_TO_COORD(0, nascar7, car7_cp_x, car7_cp_y, car7_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq7);
				TASK_PERFORM_SEQUENCE(driver_car7, seq7);
				CLEAR_SEQUENCE_TASK(seq7);
				car7_result = car7_laps * 100;
				car7_result += car7_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar7, car7_stuck_x, car7_stuck_y, car7_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car7_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar7, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar7, &car7_stuck_x, &car7_stuck_y, &car7_stuck_z);
				car7_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar7, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar7_timer < game_timer) {
					SET_CAR_HEALTH(nascar7, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar7);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car7);
					nascar7 = -1;
				}
			} else {
				nascar7_timer = game_timer + 3000;
			}
		}
		gosub_result = car7_result;
		car = nascar7;
		work_out_players_position();
		
		if (car_HP8 < 100) {
			EXPLODE_CAR(nascar8, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar8);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car8);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar8, 1);
				gosub_nascar = nascar8;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car8_laps < nascar_laps) {
					car8_laps = nascar_laps;
				}
				car8_cpcounter = 0;
				gosub_cpcounter = car8_cpcounter;
				get_next_ovalring_checkpoint();
				car8_cp_x = gosub_cp_x;
				car8_cp_y = gosub_cp_y;
				car8_cp_z = gosub_cp_z;
				int seq8;
				OPEN_SEQUENCE_TASK(&seq8);
				TASK_CAR_DRIVE_TO_COORD(0, nascar8, car8_cp_x, car8_cp_y, car8_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq8);
				TASK_PERFORM_SEQUENCE(driver_car8, seq8);
				CLEAR_SEQUENCE_TASK(seq8);
				SET_CAR_FORWARD_SPEED(nascar8, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar8, car8_cp_x, car8_cp_y, car8_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car8_cpcounter;
				get_next_ovalring_checkpoint();
				car8_cp_x = gosub_cp_x;
				car8_cp_y = gosub_cp_y;
				car8_cp_z = gosub_cp_z;
				car8_cpcounter = gosub_cpcounter;
				if (car8_cpcounter == 0) {
					car8_laps++;
				}
				int seq8;
				OPEN_SEQUENCE_TASK(&seq8);
				TASK_CAR_DRIVE_TO_COORD(0, nascar8, car8_cp_x, car8_cp_y, car8_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq8);
				TASK_PERFORM_SEQUENCE(driver_car8, seq8);
				CLEAR_SEQUENCE_TASK(seq8);
				car8_result = car8_laps * 100;
				car8_result += car8_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar8, car8_stuck_x, car8_stuck_y, car8_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car8_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar8, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar8, &car8_stuck_x, &car8_stuck_y, &car8_stuck_z);
				car8_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar8, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar8_timer < game_timer) {
					SET_CAR_HEALTH(nascar8, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar8);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car8);
					nascar8 = -1;
				}
			} else {
				nascar8_timer = game_timer + 3000;
			}
		}
		gosub_result = car8_result;
		car = nascar8;
		work_out_players_position();
		
		if (car_HP9 < 100) {
			EXPLODE_CAR(nascar9, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar9);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car9);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar9, 1);
				gosub_nascar = nascar9;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car9_laps < nascar_laps) {
					car9_laps = nascar_laps;
				}
				car9_cpcounter = 0;
				gosub_cpcounter = car9_cpcounter;
				get_next_ovalring_checkpoint();
				car9_cp_x = gosub_cp_x;
				car9_cp_y = gosub_cp_y;
				car9_cp_z = gosub_cp_z;
				int seq9;
				OPEN_SEQUENCE_TASK(&seq9);
				TASK_CAR_DRIVE_TO_COORD(0, nascar9, car9_cp_x, car9_cp_y, car9_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq9);
				TASK_PERFORM_SEQUENCE(driver_car9, seq9);
				CLEAR_SEQUENCE_TASK(seq9);
				SET_CAR_FORWARD_SPEED(nascar9, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar9, car9_cp_x, car9_cp_y, car9_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car9_cpcounter;
				get_next_ovalring_checkpoint();
				car9_cp_x = gosub_cp_x;
				car9_cp_y = gosub_cp_y;
				car9_cp_z = gosub_cp_z;
				car9_cpcounter = gosub_cpcounter;
				if (car9_cpcounter == 0) {
					car9_laps++;
				}
				int seq9;
				OPEN_SEQUENCE_TASK(&seq9);
				TASK_CAR_DRIVE_TO_COORD(0, nascar9, car9_cp_x, car9_cp_y, car9_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq9);
				TASK_PERFORM_SEQUENCE(driver_car9, seq9);
				CLEAR_SEQUENCE_TASK(seq9);
				car9_result = car9_laps * 100;
				car9_result += car9_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar9, car9_stuck_x, car9_stuck_y, car9_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car9_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar9, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar9, &car9_stuck_x, &car9_stuck_y, &car9_stuck_z);
				car9_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar9, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar9_timer < game_timer) {
					SET_CAR_HEALTH(nascar9, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar9);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car9);
					nascar9 = -1;
				}
			} else {
				nascar9_timer = game_timer + 3000;
			}
		}
		gosub_result = car9_result;
		car = nascar9;
		work_out_players_position();
		
		if (car_HP10 < 100) {
			EXPLODE_CAR(nascar10, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar10);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car10);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar10, 1);
				gosub_nascar = nascar10;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car10_laps < nascar_laps) {
					car10_laps = nascar_laps;
				}
				car10_cpcounter = 0;
				gosub_cpcounter = car10_cpcounter;
				get_next_ovalring_checkpoint();
				car10_cp_x = gosub_cp_x;
				car10_cp_y = gosub_cp_y;
				car10_cp_z = gosub_cp_z;
				int seq10;
				OPEN_SEQUENCE_TASK(&seq10);
				TASK_CAR_DRIVE_TO_COORD(0, nascar10, car10_cp_x, car10_cp_y, car10_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq10);
				TASK_PERFORM_SEQUENCE(driver_car10, seq10);
				CLEAR_SEQUENCE_TASK(seq10);
				SET_CAR_FORWARD_SPEED(nascar10, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar10, car10_cp_x, car10_cp_y, car10_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car10_cpcounter;
				get_next_ovalring_checkpoint();
				car10_cp_x = gosub_cp_x;
				car10_cp_y = gosub_cp_y;
				car10_cp_z = gosub_cp_z;
				car10_cpcounter = gosub_cpcounter;
				if (car10_cpcounter == 0) {
					car10_laps++;
				}
				int seq10;
				OPEN_SEQUENCE_TASK(&seq10);
				TASK_CAR_DRIVE_TO_COORD(0, nascar10, car10_cp_x, car10_cp_y, car10_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq10);
				TASK_PERFORM_SEQUENCE(driver_car10, seq10);
				CLEAR_SEQUENCE_TASK(seq10);
				car10_result = car10_laps * 100;
				car10_result += car10_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar10, car10_stuck_x, car10_stuck_y, car10_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car10_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar10, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar10, &car10_stuck_x, &car10_stuck_y, &car10_stuck_z);
				car10_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar10, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar10_timer < game_timer) {
					SET_CAR_HEALTH(nascar10, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar10);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car10);
					nascar10 = -1;
				}
			} else {
				nascar10_timer = game_timer + 3000;
			}
		}
		gosub_result = car10_result;
		car = nascar10;
		work_out_players_position();
		
		if (car_HP11 < 100) {
			EXPLODE_CAR(nascar11, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar11);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car11);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar11, 1);
				gosub_nascar = nascar11;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car11_laps < nascar_laps) {
					car11_laps = nascar_laps;
				}
				car11_cpcounter = 0;
				gosub_cpcounter = car11_cpcounter;
				get_next_ovalring_checkpoint();
				car11_cp_x = gosub_cp_x;
				car11_cp_y = gosub_cp_y;
				car11_cp_z = gosub_cp_z;
				int seq11;
				OPEN_SEQUENCE_TASK(&seq11);
				TASK_CAR_DRIVE_TO_COORD(0, nascar11, car11_cp_x, car11_cp_y, car11_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq11);
				TASK_PERFORM_SEQUENCE(driver_car11, seq11);
				CLEAR_SEQUENCE_TASK(seq11);
				SET_CAR_FORWARD_SPEED(nascar11, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar11, car11_cp_x, car11_cp_y, car11_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car11_cpcounter;
				get_next_ovalring_checkpoint();
				car11_cp_x = gosub_cp_x;
				car11_cp_y = gosub_cp_y;
				car11_cp_z = gosub_cp_z;
				car11_cpcounter = gosub_cpcounter;
				if (car11_cpcounter == 0) {
					car11_laps++;
				}
				int seq11;
				OPEN_SEQUENCE_TASK(&seq11);
				TASK_CAR_DRIVE_TO_COORD(0, nascar11, car11_cp_x, car11_cp_y, car11_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq11);
				TASK_PERFORM_SEQUENCE(driver_car11, seq11);
				CLEAR_SEQUENCE_TASK(seq11);
				car11_result = car11_laps * 100;
				car11_result += car11_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar11, car11_stuck_x, car11_stuck_y, car11_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car11_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar11, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar11, &car11_stuck_x, &car11_stuck_y, &car11_stuck_z);
				car11_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar11, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar11_timer < game_timer) {
					SET_CAR_HEALTH(nascar11, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar11);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car11);
					nascar11 = -1;
				}
			} else {
				nascar11_timer = game_timer + 3000;
			}
		}
		gosub_result = car11_result;
		car = nascar11;
		work_out_players_position();
		
		if (car_HP12 < 100) {
			EXPLODE_CAR(nascar12, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar12);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car12);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar12, 1);
				gosub_nascar = nascar12;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car12_laps < nascar_laps) {
					car12_laps = nascar_laps;
				}
				car12_cpcounter = 0;
				gosub_cpcounter = car12_cpcounter;
				get_next_ovalring_checkpoint();
				car12_cp_x = gosub_cp_x;
				car12_cp_y = gosub_cp_y;
				car12_cp_z = gosub_cp_z;
				int seq12;
				OPEN_SEQUENCE_TASK(&seq12);
				TASK_CAR_DRIVE_TO_COORD(0, nascar12, car12_cp_x, car12_cp_y, car12_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq12);
				TASK_PERFORM_SEQUENCE(driver_car12, seq12);
				CLEAR_SEQUENCE_TASK(seq12);
				SET_CAR_FORWARD_SPEED(nascar12, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar12, car12_cp_x, car12_cp_y, car12_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car12_cpcounter;
				get_next_ovalring_checkpoint();
				car12_cp_x = gosub_cp_x;
				car12_cp_y = gosub_cp_y;
				car12_cp_z = gosub_cp_z;
				car12_cpcounter = gosub_cpcounter;
				if (car12_cpcounter == 0) {
					car12_laps++;
				}
				int seq12;
				OPEN_SEQUENCE_TASK(&seq12);
				TASK_CAR_DRIVE_TO_COORD(0, nascar12, car12_cp_x, car12_cp_y, car12_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq12);
				TASK_PERFORM_SEQUENCE(driver_car12, seq12);
				CLEAR_SEQUENCE_TASK(seq12);
				car12_result = car12_laps * 100;
				car12_result += car12_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar12, car12_stuck_x, car12_stuck_y, car12_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car12_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar12, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar12, &car12_stuck_x, &car12_stuck_y, &car12_stuck_z);
				car12_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar12, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar12_timer < game_timer) {
					SET_CAR_HEALTH(nascar12, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar12);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car12);
					nascar12 = -1;
				}
			} else {
				nascar12_timer = game_timer + 3000;
			}
		}
		gosub_result = car12_result;
		car = nascar12;
		work_out_players_position();
		
		if (car_HP13 < 100) {
			EXPLODE_CAR(nascar13, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar13);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car13);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar13, 1);
				gosub_nascar = nascar13;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car13_laps < nascar_laps) {
					car13_laps = nascar_laps;
				}
				car13_cpcounter = 0;
				gosub_cpcounter = car13_cpcounter;
				get_next_ovalring_checkpoint();
				car13_cp_x = gosub_cp_x;
				car13_cp_y = gosub_cp_y;
				car13_cp_z = gosub_cp_z;
				int seq13;
				OPEN_SEQUENCE_TASK(&seq13);
				TASK_CAR_DRIVE_TO_COORD(0, nascar13, car13_cp_x, car13_cp_y, car13_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq13);
				TASK_PERFORM_SEQUENCE(driver_car13, seq13);
				CLEAR_SEQUENCE_TASK(seq13);
				SET_CAR_FORWARD_SPEED(nascar13, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar13, car13_cp_x, car13_cp_y, car13_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car13_cpcounter;
				get_next_ovalring_checkpoint();
				car13_cp_x = gosub_cp_x;
				car13_cp_y = gosub_cp_y;
				car13_cp_z = gosub_cp_z;
				car13_cpcounter = gosub_cpcounter;
				if (car13_cpcounter == 0) {
					car13_laps++;
				}
				int seq13;
				OPEN_SEQUENCE_TASK(&seq13);
				TASK_CAR_DRIVE_TO_COORD(0, nascar13, car13_cp_x, car13_cp_y, car13_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq13);
				TASK_PERFORM_SEQUENCE(driver_car13, seq13);
				CLEAR_SEQUENCE_TASK(seq13);
				car13_result = car13_laps * 100;
				car13_result += car13_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar13, car13_stuck_x, car13_stuck_y, car13_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car13_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar13, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar13, &car13_stuck_x, &car13_stuck_y, &car13_stuck_z);
				car13_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar13, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar13_timer < game_timer) {
					SET_CAR_HEALTH(nascar13, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar13);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car13);
					nascar13 = -1;
				}
			} else {
				nascar13_timer = game_timer + 3000;
			}
		}
		gosub_result = car13_result;
		car = nascar13;
		work_out_players_position();
		
		if (car_HP14 < 100) {
			EXPLODE_CAR(nascar14, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar14);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car14);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar14, 1);
				gosub_nascar = nascar14;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car14_laps < nascar_laps) {
					car14_laps = nascar_laps;
				}
				car14_cpcounter = 0;
				gosub_cpcounter = car14_cpcounter;
				get_next_ovalring_checkpoint();
				car14_cp_x = gosub_cp_x;
				car14_cp_y = gosub_cp_y;
				car14_cp_z = gosub_cp_z;
				int seq14;
				OPEN_SEQUENCE_TASK(&seq14);
				TASK_CAR_DRIVE_TO_COORD(0, nascar14, car14_cp_x, car14_cp_y, car14_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq14);
				TASK_PERFORM_SEQUENCE(driver_car14, seq14);
				CLEAR_SEQUENCE_TASK(seq14);
				SET_CAR_FORWARD_SPEED(nascar14, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar14, car14_cp_x, car14_cp_y, car14_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car14_cpcounter;
				get_next_ovalring_checkpoint();
				car14_cp_x = gosub_cp_x;
				car14_cp_y = gosub_cp_y;
				car14_cp_z = gosub_cp_z;
				car14_cpcounter = gosub_cpcounter;
				if (car14_cpcounter == 0) {
					car14_laps++;
				}
				int seq14;
				OPEN_SEQUENCE_TASK(&seq14);
				TASK_CAR_DRIVE_TO_COORD(0, nascar14, car14_cp_x, car14_cp_y, car14_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq14);
				TASK_PERFORM_SEQUENCE(driver_car14, seq14);
				CLEAR_SEQUENCE_TASK(seq14);
				car14_result = car14_laps * 100;
				car14_result += car14_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar14, car14_stuck_x, car14_stuck_y, car14_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car14_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar14, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar14, &car14_stuck_x, &car14_stuck_y, &car14_stuck_z);
				car14_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar14, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar14_timer < game_timer) {
					SET_CAR_HEALTH(nascar14, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar14);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car14);
					nascar14 = -1;
				}
			} else {
				nascar14_timer = game_timer + 3000;
			}
		}
		gosub_result = car14_result;
		car = nascar14;
		work_out_players_position();
		
		if (car_HP15 < 100) {
			EXPLODE_CAR(nascar15, 1, 1);
			MARK_CAR_AS_NO_LONGER_NEEDED(&nascar15);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car15);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-930.3308, 1760.2263, 25.6967, 4.0, 4.0, 2.0)) {
				CREATE_CAR(CarM1, -930.3308, 1760.2263, 25.6967, &nascar15, 1);
				gosub_nascar = nascar15;
				setup_nascar_stuff();
				driver_car1 = gosub_driver;
				if (car15_laps < nascar_laps) {
					car15_laps = nascar_laps;
				}
				car15_cpcounter = 0;
				gosub_cpcounter = car15_cpcounter;
				get_next_ovalring_checkpoint();
				car15_cp_x = gosub_cp_x;
				car15_cp_y = gosub_cp_y;
				car15_cp_z = gosub_cp_z;
				int seq15;
				OPEN_SEQUENCE_TASK(&seq15);
				TASK_CAR_DRIVE_TO_COORD(0, nascar15, car15_cp_x, car15_cp_y, car15_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq15);
				TASK_PERFORM_SEQUENCE(driver_car15, seq15);
				CLEAR_SEQUENCE_TASK(seq15);
				SET_CAR_FORWARD_SPEED(nascar15, 20.0);
			}		
		} else {
			if (LOCATE_CAR_3D(nascar15, car15_cp_x, car15_cp_y, car15_cp_z, 24.0, 24.0, 24.0, 0)) {
				gosub_cpcounter = car15_cpcounter;
				get_next_ovalring_checkpoint();
				car15_cp_x = gosub_cp_x;
				car15_cp_y = gosub_cp_y;
				car15_cp_z = gosub_cp_z;
				car15_cpcounter = gosub_cpcounter;
				if (car15_cpcounter == 0) {
					car15_laps++;
				}
				int seq15;
				OPEN_SEQUENCE_TASK(&seq15);
				TASK_CAR_DRIVE_TO_COORD(0, nascar15, car15_cp_x, car15_cp_y, car15_cp_z, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq15);
				TASK_PERFORM_SEQUENCE(driver_car15, seq15);
				CLEAR_SEQUENCE_TASK(seq15);
				car15_result = car15_laps * 100;
				car15_result += car15_cpcounter;
			}
			if (LOCATE_CAR_3D(nascar15, car15_stuck_x, car15_stuck_y, car15_stuck_z, 3.0, 3.0, 3.0, 0)) {
				if (car15_stuck_timer < game_timer) {
					SET_CAR_HEALTH(nascar15, 230);
				}
			} else {
				GET_CAR_COORDINATES(nascar15, &car15_stuck_x, &car15_stuck_y, &car15_stuck_z);
				car15_stuck_timer = game_timer + 5000;
			}
			if (LOCATE_CAR_3D(nascar15, -930.3308, 1760.2263, 25.6967, 5.0, 5.0, 3.0, 0)) {
				if (nascar15_timer < game_timer) {
					SET_CAR_HEALTH(nascar15, 100);
					MARK_CAR_AS_NO_LONGER_NEEDED(&nascar15);
					MARK_CHAR_AS_NO_LONGER_NEEDED(&driver_car15);
					nascar15 = -1;
				}
			} else {
				nascar15_timer = game_timer + 3000;
			}
		}
		gosub_result = car15_result;
		car = nascar15;
		work_out_players_position();
	} else {
		if (!IS_CAR_DEAD(nascar1)) {
			int seqb1;
			OPEN_SEQUENCE_TASK(&seqb1);
			TASK_CAR_TEMP_ACTION(driver_car1, nascar1, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb1);
			TASK_PERFORM_SEQUENCE(driver_car1, seqb1);
			CLEAR_SEQUENCE_TASK(seqb1);
		}
		if (!IS_CAR_DEAD(nascar2)) {
			int seqb2;
			OPEN_SEQUENCE_TASK(&seqb2);
			TASK_CAR_TEMP_ACTION(driver_car2, nascar2, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb2);
			TASK_PERFORM_SEQUENCE(driver_car2, seqb2);
			CLEAR_SEQUENCE_TASK(seqb2);
		}
		if (!IS_CAR_DEAD(nascar3)) {
			int seqb3;
			OPEN_SEQUENCE_TASK(&seqb3);
			TASK_CAR_TEMP_ACTION(driver_car3, nascar3, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb3);
			TASK_PERFORM_SEQUENCE(driver_car3, seqb3);
			CLEAR_SEQUENCE_TASK(seqb3);
		}
		if (!IS_CAR_DEAD(nascar4)) {
			int seqb4;
			OPEN_SEQUENCE_TASK(&seqb4);
			TASK_CAR_TEMP_ACTION(driver_car4, nascar4, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb4);
			TASK_PERFORM_SEQUENCE(driver_car4, seqb4);
			CLEAR_SEQUENCE_TASK(seqb4);
		}
		if (!IS_CAR_DEAD(nascar5)) {
			int seqb5;
			OPEN_SEQUENCE_TASK(&seqb5);
			TASK_CAR_TEMP_ACTION(driver_car5, nascar5, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb5);
			TASK_PERFORM_SEQUENCE(driver_car5, seqb5);
			CLEAR_SEQUENCE_TASK(seqb5);
		}
		if (!IS_CAR_DEAD(nascar6)) {
			int seqb6;
			OPEN_SEQUENCE_TASK(&seqb6);
			TASK_CAR_TEMP_ACTION(driver_car6, nascar6, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb6);
			TASK_PERFORM_SEQUENCE(driver_car6, seqb6);
			CLEAR_SEQUENCE_TASK(seqb6);
		}
		if (!IS_CAR_DEAD(nascar7)) {
			int seqb7;
			OPEN_SEQUENCE_TASK(&seqb7);
			TASK_CAR_TEMP_ACTION(driver_car7, nascar7, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb7);
			TASK_PERFORM_SEQUENCE(driver_car7, seqb7);
			CLEAR_SEQUENCE_TASK(seqb7);
		}
		if (!IS_CAR_DEAD(nascar8)) {
			int seqb8;
			OPEN_SEQUENCE_TASK(&seqb8);
			TASK_CAR_TEMP_ACTION(driver_car8, nascar8, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb8);
			TASK_PERFORM_SEQUENCE(driver_car8, seqb8);
			CLEAR_SEQUENCE_TASK(seqb8);
		}
		if (!IS_CAR_DEAD(nascar9)) {
			int seqb9;
			OPEN_SEQUENCE_TASK(&seqb9);
			TASK_CAR_TEMP_ACTION(driver_car9, nascar9, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb9);
			TASK_PERFORM_SEQUENCE(driver_car9, seqb9);
			CLEAR_SEQUENCE_TASK(seqb9);
		}
		if (!IS_CAR_DEAD(nascar10)) {
			int seqb10;
			OPEN_SEQUENCE_TASK(&seqb10);
			TASK_CAR_TEMP_ACTION(driver_car10, nascar10, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb10);
			TASK_PERFORM_SEQUENCE(driver_car10, seqb10);
			CLEAR_SEQUENCE_TASK(seqb10);
		}
		if (!IS_CAR_DEAD(nascar11)) {
			int seqb11;
			OPEN_SEQUENCE_TASK(&seqb11);
			TASK_CAR_TEMP_ACTION(driver_car11, nascar11, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb11);
			TASK_PERFORM_SEQUENCE(driver_car11, seqb11);
			CLEAR_SEQUENCE_TASK(seqb11);
		}
		if (!IS_CAR_DEAD(nascar12)) {
			int seqb12;
			OPEN_SEQUENCE_TASK(&seqb12);
			TASK_CAR_TEMP_ACTION(driver_car12, nascar12, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb12);
			TASK_PERFORM_SEQUENCE(driver_car12, seqb12);
			CLEAR_SEQUENCE_TASK(seqb12);
		}
		if (!IS_CAR_DEAD(nascar13)) {
			int seqb13;
			OPEN_SEQUENCE_TASK(&seqb13);
			TASK_CAR_TEMP_ACTION(driver_car13, nascar13, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb13);
			TASK_PERFORM_SEQUENCE(driver_car13, seqb13);
			CLEAR_SEQUENCE_TASK(seqb13);
		}
		if (!IS_CAR_DEAD(nascar14)) {
			int seqb14;
			OPEN_SEQUENCE_TASK(&seqb14);
			TASK_CAR_TEMP_ACTION(driver_car14, nascar14, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb14);
			TASK_PERFORM_SEQUENCE(driver_car14, seqb14);
			CLEAR_SEQUENCE_TASK(seqb14);
		}
		if (!IS_CAR_DEAD(nascar15)) {
			int seqb15;
			OPEN_SEQUENCE_TASK(&seqb15);
			TASK_CAR_TEMP_ACTION(driver_car15, nascar15, 1, 200);
			CLOSE_SEQUENCE_TASK(seqb15);
			TASK_PERFORM_SEQUENCE(driver_car15, seqb15);
			CLEAR_SEQUENCE_TASK(seqb15);
		}
	}
	
	if (do_winning_text_shite == 1) {
		hotring_finished_timer = game_timer + 5000;
		do_winning_text_shite = 3;
	}
	
	if (do_winning_text_shite == 0) {
		if (nascar_laps == 12) {
			show_hud = false;
			if (HG_BEST_NASCAR_RESULT > position) {
				HG_BEST_NASCAR_RESULT = position;
			}
			nascar_time /= 1000;
			nascar_best_time_last = HG_NASCAR_BEST_TIME;
			if (HG_NASCAR_BEST_TIME > nascar_time) {
				HG_NASCAR_BEST_TIME = nascar_time;
			}
			do_winning_text_shite = 1;
			mins = nascar_time / 60;
			temp_int = mins * 60;
			seconds = nascar_time - temp_int;
			if (seconds > 9) {
				PRINT_WITH_2_NUMBERS("HOTR_17", mins, seconds, 8000, 0);
			} else {
				PRINT_WITH_2_NUMBERS("HOTR_18", mins, seconds, 8000, 0);
			}
			if (position == 1) {
				//PRINT_BIG("HOTR_30", 6000, 5);
				//PRINT_WITH_NUMBER_BIG("HOTR_29", 5000, 6000, 6);
				finish_laps = 1;
				if (G_HOTRING == 0)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					G_HOTRING = 1;
				}
				ADD_SCORE(GetPlayerIndex(), 5000);
				INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 5000);
			}
			if (position == 2) {
				//PRINT_BIG("HOTR_31", 6000, 5);
				//PRINT_WITH_NUMBER_BIG("HOTR_29", 1500, 6000, 6);
				finish_laps = 1;
				ADD_SCORE(GetPlayerIndex(), 1500);
				INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 1500);
			}
			if (position == 3) {
				//PRINT_BIG("HOTR_32", 6000, 5);
				//PRINT_WITH_NUMBER_BIG("HOTR_29", 500, 6000, 6);
				finish_laps = 1;
				ADD_SCORE(GetPlayerIndex(), 500);
				INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 500);
			}
			if (position > 3) {
				do_winning_text_shite = 0;
				PRINT_NOW("HOTR_13", 2000, 1);	// ~r~You didn't win the race!
				DO_SCREEN_FADE_OUT(1500);
				while (IS_SCREEN_FADING()) {
					WAIT(0);
				}
				mission_ovalring_passed();
			}
		}
	}
	if (finish_laps == 1)
	{
		if (position == 1)
		{
			SET_TEXT_COLOUR(0, 197, 145, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT(0.5, 0.45, "HOTR_30");// пишем "Миссия завершина"

			SET_TEXT_COLOUR(50, 182, 255, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "HOTR_29", 5000);// +5000$
		}
		if (position == 2)
		{
			SET_TEXT_COLOUR(0, 197, 145, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT(0.5, 0.45, "HOTR_31");// пишем "Миссия завершина"

			SET_TEXT_COLOUR(50, 182, 255, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "HOTR_29", 1500);// +5000$
		}
		if (position == 3)
		{
			SET_TEXT_COLOUR(0, 197, 145, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT(0.5, 0.45, "HOTR_32");// пишем "Миссия завершина"

			SET_TEXT_COLOUR(50, 182, 255, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "HOTR_29", 500);// +5000$
		}
	}
	
	if (do_winning_text_shite > 1) {
		if (do_winning_text_shite == 4) {
			if (!IS_SCREEN_FADING()) {
				mission_ovalring_passed();
			}
		}
		if (do_winning_text_shite == 3) {
			if (hotring_finished_timer < game_timer) {
				DO_SCREEN_FADE_OUT(1500);
				do_winning_text_shite = 4;
			}
		}
		if (IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
			STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &players_car);
			GET_CAR_HEALTH(players_car, &players_nascar_health);
			SET_CAR_HEALTH(players_car, players_nascar_health);
		}

		if (do_winning_text_shite > 2) {
			//setup_text_shite_hot();
			//SET_TEXT_SCALE(0.4, 1.0);
			mins = nascar_time / 60;
			temp_int = mins * 60;
			seconds = nascar_time - temp_int;
			//if (seconds > 9) {
			//	setup_text_shite_hot();
			//	SET_TEXT_SCALE(0.4, 1.0);
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.046875, 0.513, "HOTR_15", mins, seconds);
			//} else {
			//	setup_text_shite_hot();
			//	SET_TEXT_SCALE(0.4, 1.0);
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.046875, 0.513, "HOTR_16", mins, seconds);
			//}
		}
		//if (HG_NASCAR_BEST_TIME == 999999) {
		//	setup_text_shite_hot();
		//	DISPLAY_TEXT(0.046875, 0.67, "HOTR_19");
		//} else {
		//	mins = HG_NASCAR_BEST_TIME / 60;
		//	temp_int = mins * 60;
		//	seconds = HG_NASCAR_BEST_TIME - temp_int;
		//	if (HG_NASCAR_BEST_TIME > nascar_best_time_last) {
		//		if (seconds > 9) {
		//			setup_text_shite_hot();
		//			DISPLAY_TEXT_WITH_2_NUMBERS(0.046875, 0.669, "HOTR_17", mins, seconds);			
		//		} else {
		//			setup_text_shite_hot();
		//			DISPLAY_TEXT_WITH_2_NUMBERS(0.046875, 0.669, "HOTR_18", mins, seconds);		
		//		}
		//	} else {
		//		if (seconds > 9) {
		//			setup_text_shite_hot();
		//			SET_TEXT_COLOUR(255, 128, 0, 255);
		//			DISPLAY_TEXT_WITH_2_NUMBERS(0.046875, 0.669, "HOTR_20", mins, seconds);
		//		} else {
		//			setup_text_shite_hot();
		//			SET_TEXT_COLOUR(255, 128, 0, 255);
		//			DISPLAY_TEXT_WITH_2_NUMBERS(0.046875, 0.669, "HOTR_21", mins, seconds);
		//		}
		//	}
		//}
		
		//if (HG_BEST_NASCAR_RESULT == 999999) {
		//	setup_text_shite_hot();
		//	DISPLAY_TEXT(0.046875, 0.703125, "HOTR_22");
		//}
		//if (HG_BEST_NASCAR_RESULT == 1) {
		//	setup_text_shite_hot();
		//	DISPLAY_TEXT(0.046875, 0.703125, "HOTR_23");
		//}
		//if (HG_BEST_NASCAR_RESULT == 2) {
		//	setup_text_shite_hot();
		//	DISPLAY_TEXT(0.046875, 0.703125, "HOTR_24");
		//}
		//if (HG_BEST_NASCAR_RESULT == 3) {
		//	setup_text_shite_hot();
		//	DISPLAY_TEXT(0.046875, 0.703125, "HOTR_25");
		//}
		//if ((HG_BEST_NASCAR_RESULT > 3) && (HG_BEST_NASCAR_RESULT < 17)) {
		//	setup_text_shite_hot();
		//	DISPLAY_TEXT_WITH_NUMBER(0.046875, 0.703125, "HOTR_26", HG_BEST_NASCAR_RESULT);
		//}
		
		//if (HG_NASCAR_BEST_LAP_TIME == 999999) {
		//	setup_text_shite_hot();
		//	DISPLAY_TEXT(0.046875, 0.7366, "HOTR_33");
		//} else {
		//	seconds = HG_NASCAR_BEST_LAP_TIME / 1000;
		//	miliseconds = seconds * 1000;
		//	temp_int = HG_NASCAR_BEST_LAP_TIME - miliseconds;
		//	miliseconds = temp_int / 10;
		//	if (miliseconds > 9) {
		//		setup_text_shite_hot();
		//		DISPLAY_TEXT_WITH_2_NUMBERS(0.046875, 0.7366, "HOTR_27", seconds, miliseconds);
		//	} else {
		//		setup_text_shite_hot();
		//		DISPLAY_TEXT_WITH_2_NUMBERS(0.046875, 0.7366, "HOTR_28", seconds, miliseconds);
		//	}
		//}
	}
	
	if (TIMERA() > 2500) {
		SETTIMERA(0);
		if (hot_audio_flag == 0) {
			hot_audio_flag = 1;
		}
	}
	
	if (hot_audio_flag == 3) {
		if (HAS_SOUND_FINISHED(sID)) {
			hot_audio_flag = 0;
		}
	}
	
	if (hot_audio_flag == 2) {
		hot_audio_flag = 3;		
	}
	
	if (hot_audio_flag == 1) {
		GENERATE_RANDOM_INT_IN_RANGE(1, 23, &temp_int);
		if (last_audio_played == temp_int) {
			temp_int++;
			if (temp_int > 22) {
				temp_int = 1;
			}
		}
		if (temp_int == 1) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT1");
		}
		if (temp_int == 2) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT2");
		}
		if (temp_int == 3) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT3");
		}
		if (temp_int == 4) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT4");
		}
		if (temp_int == 5) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT5");
		}
		if (temp_int == 6) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT6");
		}
		if (temp_int == 7) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT7");
		}
		if (temp_int == 8) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT8");
		}
		if (temp_int == 9) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT9");
		}
		if (temp_int == 10) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT10");
		}
		if (temp_int == 11) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT11");
		}
		if (temp_int == 12) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT12");
		}
		if (temp_int == 13) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT13");
		}
		if (temp_int == 14) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT14");
		}
		if (temp_int == 15) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_HOT15");
		}
		if ((temp_int == 16) || (temp_int == 22)) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_CHEER1");
		}
		if (temp_int == 17) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_CHEER2");
		}
		if (temp_int == 18) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_CHEER3");
		}
		if (temp_int == 19) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_CHEER4");
		}
		if (temp_int == 20) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_OOH1");
		}
		if (temp_int == 21) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_OOH2");
		}
		last_audio_played = temp_int;
		hot_audio_flag = 2;
	}
}

void mission_ovalring_start(void) {
	WAIT(0);
	if (G_HOTRING == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}
	SETTIMERC( 1000 );
	LOAD_ADDITIONAL_TEXT("OVALRIG", 6);
	gosub_cpcounter = 0;
	player_cpcounter = 0;
	car1_cpcounter = 0;
	car2_cpcounter = 0;
	car3_cpcounter = 0;
	car4_cpcounter = 0;
	car5_cpcounter = 0;
	car6_cpcounter = 0;
	car7_cpcounter = 0;
	car8_cpcounter = 0;
	car9_cpcounter = 0;
	car10_cpcounter = 0;
	car11_cpcounter = 0;
	car12_cpcounter = 0;
	car10_cpcounter = 0;
	car14_cpcounter = 0;
	car15_cpcounter = 0;
	HG_NASCAR_BEST_LAP_TIME = 0;
	
	car1_laps = 0;
	car2_laps = 0;
	car3_laps = 0;
	car4_laps = 0;
	car5_laps = 0;
	car6_laps = 0;
	car7_laps = 0;
	car8_laps = 0;
	car9_laps = 0;
	car10_laps = 0;
	car11_laps = 0;
	car12_laps = 0;
	car13_laps = 0;
	car14_laps = 0;
	car15_laps = 0;
	finish_laps = 0;
	
	car1_stuck_timer = 0;
	car2_stuck_timer = 0;
	car3_stuck_timer = 0;
	car4_stuck_timer = 0;
	car5_stuck_timer = 0;
	car6_stuck_timer = 0;
	car7_stuck_timer = 0;
	car8_stuck_timer = 0;
	car9_stuck_timer = 0;
	car10_stuck_timer = 0;
	car11_stuck_timer = 0;
	car12_stuck_timer = 0;
	car13_stuck_timer = 0;
	car14_stuck_timer = 0;
	car15_stuck_timer = 0;
	
	nascar1_timer = 0;
	nascar2_timer = 0;
	nascar3_timer = 0;
	nascar4_timer = 0;
	nascar5_timer = 0;
	nascar6_timer = 0;
	nascar7_timer = 0;
	nascar8_timer = 0;
	nascar9_timer = 0;
	nascar10_timer = 0;
	nascar11_timer = 0;
	nascar12_timer = 0;
	nascar13_timer = 0;
	nascar14_timer = 0;
	nascar15_timer = 0;
	
	do_winning_text_shite = 0;
	showcase = -1;
	showcase_timer = 0;
	nascar_laps = 0;
	player_result = 0;
	gosub_result = 0;
	heading_done_flag = 0;
	gosub_nascar = -1;
	gosub_driver = -1;
	nascar_best_time_last = 0;
	nascar_time = 0;
	hot_audio_flag = 0;
	position = 0;
	skip_scut_button = 0;
	last_audio_played = 0;
	nascar_lap_timer_start = 0;
	players_nascar_health = 100;
	
	//gosub_cp_x = 0.0;
	//gosub_cp_y = 0.0;
	//gosub_cp_z = 0.0;

	gosub_cp_x = -809.59;
	gosub_cp_y = 1805.925;
	gosub_cp_z = 23.602;

	cp1_x = -809.59;
	cp1_y = 1805.925;
	cp1_z = 23.602;

	cp2_x = -777.699;
	cp2_y = 1861.097;
	cp2_z = 23.607;

	cp3_x = -817.363;
	cp3_y = 1921.379;
	cp3_z = 23.607;

	cp4_x = -886.986;
	cp4_y = 1940.976;
	cp4_z = 23.607;

	cp5_x = -939.849;
	cp5_y = 1942.316;
	cp5_z = 23.607;

	cp6_x = -1020.995;
	cp6_y = 1921.322;
	cp6_z = 23.607;

	cp7_x = -1060.622;
	cp7_y = 1861.097;
	cp7_z = 23.607;

	cp8_x = -1021.06;
	cp8_y = 1800.766;
	cp8_z = 23.607;

	cp9_x = -939.848;
	cp9_y = 1779.586;
	cp9_z = 23.607;

	cp10_x = -875.701;
	cp10_y = 1781.038;
	cp10_z = 23.607;
	
	GET_CURRENT_WEATHER(&weather);
	FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
	FORWARD_TO_TIME_OF_DAY(20, 30);//устанавливаем время

	SET_MAX_WANTED_LEVEL(0);
	SET_CHAR_COORDINATES(GetPlayerPed(), -941.47, 1861.099, 10.69);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	while (!REQUEST_AMBIENT_AUDIO_BANK("SCRIPT_MISSION/DIRTRING")) {
		WAIT(0);
	}
	sID = GET_SOUND_ID();
	while (!PRELOAD_STREAM("DIRTRING_AMB_MUSIC")) {
		WAIT(0);
	}
	SET_STREAM_PARAMS(11.0, 15000);
	PLAY_STREAM_FRONTEND();

	REQUEST_MODEL(PedM1);
	REQUEST_MODEL(CarM1);
	REQUEST_MODEL(CarM2);
	REQUEST_MODEL(CarM3);
	REQUEST_IPL("blodring");
	LOAD_SCENE(-910.7432, 1684.8137, 270.7988);
	LOAD_ALL_OBJECTS_NOW();
	while ((!(HAS_MODEL_LOADED(PedM1))) || (!(HAS_MODEL_LOADED(CarM1))) || (!(HAS_MODEL_LOADED(CarM2))) || (!(HAS_MODEL_LOADED(CarM3)))) {
		WAIT(0);
	}
	CREATE_CAM(14, &cam);
	SET_CAM_POS(cam, -838.8193, 1778.6455, 33.0706);
	POINT_CAM_AT_COORD(cam, -839.7324, 1778.9873, 32.8484);
	SET_CAM_ACTIVE(cam, 1);
	SET_CAM_PROPAGATE(cam, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	SET_INSTANT_WIDESCREEN_BORDERS(1);
	SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
	SET_EVERYONE_IGNORE_PLAYER(GetPlayerIndex(), 1);
	SET_ALL_CARS_CAN_BE_DAMAGED(0);
	if (!GET_MISSION_FLAG()) {
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &gosub_driver, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car1, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car2, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car3, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car4, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car5, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car6, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car7, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car8, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car9, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car10, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car11, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car12, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car13, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car14, 1);
		CREATE_CHAR(5, PedM1, 0.0, 0.0, 0.0, &driver_car15, 1);
	}
	CREATE_CAR(CarM1, -865.1008, 1787.9894, 23.1804, &nascar1, 1);
	SET_CAR_HEADING(nascar1, 284.8876);
	GET_CAR_COORDINATES(nascar1, &car1_cp_x, &car1_cp_y, &car1_cp_z);
	gosub_nascar = nascar1;
	setup_nascar_stuff();
	driver_car1 = gosub_driver;
	
	CREATE_CAR(CarM1, -864.0522, 1783.0925, 23.9305, &nascar2, 1);
	SET_CAR_HEADING(nascar2, 281.5068);
	GET_CAR_COORDINATES(nascar2, &car2_cp_x, &car2_cp_y, &car2_cp_z);
	gosub_nascar = nascar2;
	setup_nascar_stuff();
	driver_car2 = gosub_driver;
	
	CREATE_CAR(CarM1, -874.9105, 1785.5454, 23.2972, &nascar3, 1);
	SET_CAR_HEADING(nascar3, 282.7367);
	GET_CAR_COORDINATES(nascar3, &car3_cp_x, &car3_cp_y, &car3_cp_z);
	gosub_nascar = nascar3;
	setup_nascar_stuff();
	driver_car3 = gosub_driver;
	
	CREATE_CAR(CarM1, -873.4609, 1780.783, 24.0607, &nascar4, 1);
	SET_CAR_HEADING(nascar4, 284.2442);
	GET_CAR_COORDINATES(nascar4, &car4_cp_x, &car4_cp_y, &car4_cp_z);
	gosub_nascar = nascar4;
	setup_nascar_stuff();
	driver_car4 = gosub_driver;
	
	CREATE_CAR(CarM1, -884.3717, 1784.3344, 23.3261, &nascar5, 1);
	SET_CAR_HEADING(nascar5, 276.4275);
	GET_CAR_COORDINATES(nascar5, &car5_cp_x, &car5_cp_y, &car5_cp_z);
	gosub_nascar = nascar5;
	setup_nascar_stuff();
	driver_car5 = gosub_driver;
	
	CREATE_CAR(CarM1, -884.2843, 1779.4063, 24.0958, &nascar6, 1);
	SET_CAR_HEADING(nascar6, 277.8466);
	GET_CAR_COORDINATES(nascar6, &car6_cp_x, &car6_cp_y, &car6_cp_z);
	gosub_nascar = nascar6;
	setup_nascar_stuff();
	driver_car6 = gosub_driver;
	
	CREATE_CAR(CarM1, -894.4932, 1783.9103, 23.3289, &nascar7, 1);
	SET_CAR_HEADING(nascar7, 273.3020);
	GET_CAR_COORDINATES(nascar7, &car7_cp_x, &car7_cp_y, &car7_cp_z);
	gosub_nascar = nascar7;
	setup_nascar_stuff();
	driver_car7 = gosub_driver;
	
	CREATE_CAR(CarM3, -895.1748, 1778.3114, 24.2485, &nascar8, 1);
	SET_CAR_HEADING(nascar8, 272.9799);
	GET_CAR_COORDINATES(nascar8, &car8_cp_x, &car8_cp_y, &car8_cp_z);
	gosub_nascar = nascar8;
	setup_nascar_stuff();
	driver_car8 = gosub_driver;
	
	CREATE_CAR(CarM3, -904.2821, 1783.2029, 23.4254, &nascar9, 1);
	SET_CAR_HEADING(nascar9, 273.0015);
	GET_CAR_COORDINATES(nascar9, &car9_cp_x, &car9_cp_y, &car9_cp_z);
	gosub_nascar = nascar9;
	setup_nascar_stuff();
	driver_car9 = gosub_driver;
	
	CREATE_CAR(CarM3, -904.1959, 1778.159, 24.2656, &nascar10, 1);
	SET_CAR_HEADING(nascar10, 269.9305);
	GET_CAR_COORDINATES(nascar10, &car10_cp_x, &car10_cp_y, &car10_cp_z);
	gosub_nascar = nascar10;
	setup_nascar_stuff();
	driver_car10 = gosub_driver;
	
	CREATE_CAR(CarM3, -913.8371, 1782.9677, 23.4513, &nascar11, 1);
	SET_CAR_HEADING(nascar11, 270.1651);
	GET_CAR_COORDINATES(nascar11, &car11_cp_x, &car11_cp_y, &car11_cp_z);
	gosub_nascar = nascar11;
	setup_nascar_stuff();
	driver_car11 = gosub_driver;
	
	CREATE_CAR(CarM3, -913.7176, 1778.3086, 24.225, &nascar12, 1);
	SET_CAR_HEADING(nascar12, 270.3340);
	GET_CAR_COORDINATES(nascar12, &car12_cp_x, &car12_cp_y, &car12_cp_z);
	gosub_nascar = nascar12;
	setup_nascar_stuff();
	driver_car12 = gosub_driver;
	
	CREATE_CAR(CarM3, -922.7978, 1782.4495, 23.5203, &nascar13, 1);
	SET_CAR_HEADING(nascar13, 271.0722);
	GET_CAR_COORDINATES(nascar13, &car13_cp_x, &car13_cp_y, &car13_cp_z);
	gosub_nascar = nascar13;
	setup_nascar_stuff();
	driver_car13 = gosub_driver;
	
	CREATE_CAR(CarM1, -922.9892, 1778.3129, 24.2126, &nascar14, 1);
	SET_CAR_HEADING(nascar14, 266.2549);
	GET_CAR_COORDINATES(nascar14, &car14_cp_x, &car14_cp_y, &car14_cp_z);
	gosub_nascar = nascar14;
	setup_nascar_stuff();
	driver_car14 = gosub_driver;
	
	CREATE_CAR(CarM3, -932.7252, 1782.4673, 23.5191, &nascar15, 1);
	SET_CAR_HEADING(nascar15, 273.8779);
	GET_CAR_COORDINATES(nascar15, &car15_cp_x, &car15_cp_y, &car15_cp_z);
	gosub_nascar = nascar15;
	setup_nascar_stuff();
	driver_car15 = gosub_driver;
	
	CREATE_CAR(CarM2, -932.5627, 1778.176, 24.227, &players_nascar, 1);
	SET_CAR_HEADING(players_nascar, 271.2772);
	SET_CAR_HEALTH(players_nascar, 1250);
	SET_CAR_PROOFS(players_nascar, 0, 1, 1, 0, 0);
	GET_CAR_COORDINATES(players_nascar, &player1_cp_x, &player1_cp_y, &player1_cp_z);
	
	DO_SCREEN_FADE_IN(1500);
	WAIT(250);
	
	true_false = 1;
	freeze_all_cars();
	
	if (!IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
		if (!IS_CAR_DEAD(players_nascar)) {
			WARP_CHAR_INTO_CAR(GetPlayerPed(), players_nascar);
		}
	} else {
		WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), -1024.8125, 1930.1017, 24.5854);
		WAIT(0);
		if (!IS_CAR_DEAD(players_nascar)) {
			WARP_CHAR_INTO_CAR(GetPlayerPed(), players_nascar);
		}
	}
	SET_CAR_ENGINE_ON(players_nascar, 1, 1);
	PRINT_NOW("HOTR_01", 8000, 1);		// ~g~The Race lasts for 20 laps. Only 1st, 2nd and 3rd places qualify for winnings.
	GET_GAME_TIMER(&game_timer);
	heading_done_flag = 1;
	SETTIMERA(0);
	while (true) {
		WAIT(0);
		ovalring_loop();
	}
}

void main(void) {
	mission_ovalring_start();
	if (HAS_DEATHARREST_EXECUTED()) {
		mission_ovalring_failed();
	}
	mission_ovalring_cleanup();
}