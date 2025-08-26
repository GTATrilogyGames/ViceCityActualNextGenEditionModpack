#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
#include "mission_passed.h"
// начало миссии метод mission_start_kickstart()

int player_checkpoint_kickstart, time_now_ks, time_off_bike_ks;
int time_bailed_ks, time_left_to_find_bike_ks;
int	time_left_to_find_bike_secs_ks, race_timer_kickstart;

float checkpoint1_x_kickstart, checkpoint1_y_kickstart, checkpoint1_z_kickstart;
int flag_done_checkpoint1_kickstart, checkpoint1_blip_kickstart, checkpoint1_obj;

float checkpoint2_x_kickstart, checkpoint2_y_kickstart, checkpoint2_z_kickstart;
int flag_done_checkpoint2_kickstart, checkpoint2_blip_kickstart, checkpoint2_obj;

float checkpoint3_x_kickstart, checkpoint3_y_kickstart, checkpoint3_z_kickstart;
int flag_done_checkpoint3_kickstart, checkpoint3_blip_kickstart, checkpoint3_obj;

float checkpoint4_x_kickstart, checkpoint4_y_kickstart, checkpoint4_z_kickstart;
int flag_done_checkpoint4_kickstart, checkpoint4_blip_kickstart, checkpoint4_obj;

float checkpoint5_x_kickstart, checkpoint5_y_kickstart, checkpoint5_z_kickstart;
int flag_done_checkpoint5_kickstart, checkpoint5_blip_kickstart, checkpoint5_obj;

float checkpoint6_x_kickstart, checkpoint6_y_kickstart, checkpoint6_z_kickstart;
int flag_done_checkpoint6_kickstart, checkpoint6_blip_kickstart, checkpoint6_obj;

float checkpoint7_x_kickstart, checkpoint7_y_kickstart, checkpoint7_z_kickstart;
int flag_done_checkpoint7_kickstart, checkpoint7_blip_kickstart, checkpoint7_obj;

float checkpoint8_x_kickstart, checkpoint8_y_kickstart, checkpoint8_z_kickstart;
int flag_done_checkpoint8_kickstart, checkpoint8_blip_kickstart, checkpoint8_obj;

float checkpoint9_x_kickstart, checkpoint9_y_kickstart, checkpoint9_z_kickstart;
int flag_done_checkpoint9_kickstart, checkpoint9_blip_kickstart, checkpoint9_obj;

float checkpoint10_x_kickstart, checkpoint10_y_kickstart, checkpoint10_z_kickstart;
int flag_done_checkpoint10_kickstart, checkpoint10_blip_kickstart, checkpoint10_obj;

float checkpoint11_x_kickstart, checkpoint11_y_kickstart, checkpoint11_z_kickstart;
int flag_done_checkpoint11_kickstart, checkpoint11_blip_kickstart, checkpoint11_obj;

float checkpoint12_x_kickstart, checkpoint12_y_kickstart, checkpoint12_z_kickstart;
int flag_done_checkpoint12_kickstart, checkpoint12_blip_kickstart, checkpoint12_obj;

float checkpoint13_x_kickstart, checkpoint13_y_kickstart, checkpoint13_z_kickstart;
int flag_done_checkpoint13_kickstart, checkpoint13_blip_kickstart, checkpoint13_obj;

float checkpoint14_x_kickstart, checkpoint14_y_kickstart, checkpoint14_z_kickstart;
int flag_done_checkpoint14_kickstart, checkpoint14_blip_kickstart, checkpoint14_obj;

float checkpoint15_x_kickstart, checkpoint15_y_kickstart, checkpoint15_z_kickstart;
int flag_done_checkpoint15_kickstart, checkpoint15_blip_kickstart, checkpoint15_obj;

float checkpoint16_x_kickstart, checkpoint16_y_kickstart, checkpoint16_z_kickstart;
int flag_done_checkpoint16_kickstart, checkpoint16_blip_kickstart, checkpoint16_obj;

float checkpoint17_x_kickstart, checkpoint17_y_kickstart, checkpoint17_z_kickstart;
int flag_done_checkpoint17_kickstart, checkpoint17_blip_kickstart, checkpoint17_obj;

float checkpoint18_x_kickstart, checkpoint18_y_kickstart, checkpoint18_z_kickstart;
int flag_done_checkpoint18_kickstart, checkpoint18_blip_kickstart, checkpoint18_obj;

float checkpoint19_x_kickstart, checkpoint19_y_kickstart, checkpoint19_z_kickstart;
int flag_done_checkpoint19_kickstart, checkpoint19_blip_kickstart, checkpoint19_obj;

float checkpoint20_x_kickstart, checkpoint20_y_kickstart, checkpoint20_z_kickstart;
int flag_done_checkpoint20_kickstart, checkpoint20_blip_kickstart, checkpoint20_obj;

float checkpoint21_x_kickstart, checkpoint21_y_kickstart, checkpoint21_z_kickstart;
int flag_done_checkpoint21_kickstart, checkpoint21_blip_kickstart, checkpoint21_obj;

float checkpoint22_x_kickstart, checkpoint22_y_kickstart, checkpoint22_z_kickstart;
int flag_done_checkpoint22_kickstart, checkpoint22_blip_kickstart, checkpoint22_obj;

float checkpoint23_x_kickstart, checkpoint23_y_kickstart, checkpoint23_z_kickstart;
int flag_done_checkpoint23_kickstart, checkpoint23_blip_kickstart, checkpoint23_obj;

float checkpoint24_x_kickstart, checkpoint24_y_kickstart, checkpoint24_z_kickstart;
int flag_done_checkpoint24_kickstart, checkpoint24_blip_kickstart, checkpoint24_obj;

float checkpoint25_x_kickstart, checkpoint25_y_kickstart, checkpoint25_z_kickstart;
int flag_done_checkpoint25_kickstart, checkpoint25_blip_kickstart, checkpoint25_obj;

float checkpoint26_x_kickstart, checkpoint26_y_kickstart, checkpoint26_z_kickstart;
int flag_done_checkpoint26_kickstart, checkpoint26_blip_kickstart, checkpoint26_obj;

float checkpoint27_x_kickstart, checkpoint27_y_kickstart, checkpoint27_z_kickstart;
int flag_done_checkpoint27_kickstart, checkpoint27_blip_kickstart, checkpoint27_obj;

float checkpoint28_x_kickstart, checkpoint28_y_kickstart, checkpoint28_z_kickstart;
int flag_done_checkpoint28_kickstart, checkpoint28_blip_kickstart, checkpoint28_obj;

float checkpoint29_x_kickstart, checkpoint29_y_kickstart, checkpoint29_z_kickstart;
int flag_done_checkpoint29_kickstart, checkpoint29_blip_kickstart, checkpoint29_obj;

float checkpoint30_x_kickstart, checkpoint30_y_kickstart, checkpoint30_z_kickstart;
int flag_done_checkpoint30_kickstart, checkpoint30_blip_kickstart, checkpoint30_obj;

float checkpoint31_x_kickstart, checkpoint31_y_kickstart, checkpoint31_z_kickstart;
int flag_done_checkpoint31_kickstart, checkpoint31_blip_kickstart, checkpoint31_obj;

float checkpoint32_x_kickstart, checkpoint32_y_kickstart, checkpoint32_z_kickstart;
int flag_done_checkpoint32_kickstart, checkpoint32_blip_kickstart, checkpoint32_obj;

int race_timer_seconds_kickstart, race_timer_mins_kickstart, race_timer_seconds2_kickstart;
int player_taken_too_long_kickstart, bike_kickstart, flag_bike_blip_on_kickstart;
int bike_blip_kickstart, number_of_checkpoints_kickstart;

float player_x_kickstart, player_y_kickstart, player_z_kickstart;
float bike_x_kickstart, bike_y_kickstart, bike_z_kickstart, skip, add_cash;

int player_in_end_area_kickstart, sphere_kickstart, player_been_rewarded_kickstart;
int audio_flag_cheer_kick, audio_flag_ohh_kick, flag_bike_dead_kickstart;
int cam, sID, fon, textur, plhp;
int bike_check_kickstart;
uint hour, minute, weather;
uint CarM1 = MODEL_SANCHEZ;//

int intro_skip = 0;		/*rebusx*/


#define KEYBOARD_ENTER			28
#define KEYBOARD_SPACE			57
#define CONTROL_KEYBOARD_HORN	54
#define CONTROL_MOUSE_LEFT		38

#define CONTROLLER_BUTTON_B		17

void check_skip_intro()
{
	if ( (!IS_USING_CONTROLLER() && (IS_GAME_KEYBOARD_KEY_PRESSED(KEYBOARD_ENTER) || IS_GAME_KEYBOARD_KEY_PRESSED(KEYBOARD_SPACE) || IS_CONTROL_PRESSED(2, CONTROL_KEYBOARD_HORN) || IS_CONTROL_PRESSED(2, CONTROL_MOUSE_LEFT)))
	|| (IS_USING_CONTROLLER() && IS_BUTTON_PRESSED(0, CONTROLLER_BUTTON_B)) )
	{
		intro_skip = 1;
	}
}

void SetTime_intro(uint time)		/*rebusx*/
{
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if (!intro_skip)
		{
			check_skip_intro();
		}
		if (intro_skip)
		{
			break;
		}
		if ((TIMERA() > time) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// поверка игрок мёртв/арестован
		{
			break;
		}
	}
}


void setup_draw_text(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.156, 0.267);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
}

void setup_draw_value(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.26, 0.445);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
}

void mission_cleanup_kickstart(void) {
	//REMOVE_SPHERE(sphere_kickstart);
	REMOVE_BLIP(checkpoint1_blip_kickstart);
	REMOVE_BLIP(checkpoint2_blip_kickstart);
	REMOVE_BLIP(checkpoint3_blip_kickstart);
	REMOVE_BLIP(checkpoint4_blip_kickstart);
	REMOVE_BLIP(checkpoint5_blip_kickstart);
	REMOVE_BLIP(checkpoint6_blip_kickstart);
	REMOVE_BLIP(checkpoint7_blip_kickstart);
	REMOVE_BLIP(checkpoint8_blip_kickstart);
	REMOVE_BLIP(checkpoint9_blip_kickstart);
	REMOVE_BLIP(checkpoint10_blip_kickstart);
	REMOVE_BLIP(checkpoint11_blip_kickstart);
	REMOVE_BLIP(checkpoint12_blip_kickstart);
	REMOVE_BLIP(checkpoint13_blip_kickstart);
	REMOVE_BLIP(checkpoint14_blip_kickstart);
	REMOVE_BLIP(checkpoint15_blip_kickstart);
	REMOVE_BLIP(checkpoint16_blip_kickstart);
	REMOVE_BLIP(checkpoint17_blip_kickstart);
	REMOVE_BLIP(checkpoint18_blip_kickstart);
	REMOVE_BLIP(checkpoint19_blip_kickstart);
	REMOVE_BLIP(checkpoint20_blip_kickstart);
	REMOVE_BLIP(checkpoint21_blip_kickstart);
	REMOVE_BLIP(checkpoint22_blip_kickstart);
	REMOVE_BLIP(checkpoint23_blip_kickstart);
	REMOVE_BLIP(checkpoint24_blip_kickstart);
	REMOVE_BLIP(checkpoint25_blip_kickstart);
	REMOVE_BLIP(checkpoint26_blip_kickstart);
	REMOVE_BLIP(checkpoint27_blip_kickstart);
	REMOVE_BLIP(checkpoint28_blip_kickstart);
	REMOVE_BLIP(checkpoint29_blip_kickstart);
	REMOVE_BLIP(checkpoint30_blip_kickstart);
	REMOVE_BLIP(checkpoint31_blip_kickstart);
	REMOVE_BLIP(checkpoint32_blip_kickstart);
	REMOVE_BLIP(sphere_kickstart);
	REMOVE_BLIP(bike_blip_kickstart);
	
	if (flag_done_checkpoint1_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint1_obj);
	}
	if (flag_done_checkpoint2_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint2_obj);
	}
	if (flag_done_checkpoint3_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint3_obj);
	}
	if (flag_done_checkpoint4_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint4_obj);
	}
	if (flag_done_checkpoint5_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint5_obj);
	}
	if (flag_done_checkpoint6_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint6_obj);
	}
	if (flag_done_checkpoint7_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint7_obj);
	}
	if (flag_done_checkpoint8_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint8_obj);
	}
	if (flag_done_checkpoint9_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint9_obj);
	}
	if (flag_done_checkpoint10_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint10_obj);
	}
	if (flag_done_checkpoint11_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint11_obj);
	}
	if (flag_done_checkpoint12_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint12_obj);
	}
	if (flag_done_checkpoint13_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint13_obj);
	}
	if (flag_done_checkpoint14_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint14_obj);
	}
	if (flag_done_checkpoint15_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint15_obj);
	}
	if (flag_done_checkpoint16_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint16_obj);
	}
	if (flag_done_checkpoint17_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint17_obj);
	}
	if (flag_done_checkpoint18_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint18_obj);
	}
	if (flag_done_checkpoint19_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint19_obj);
	}
	if (flag_done_checkpoint20_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint20_obj);
	}
	if (flag_done_checkpoint21_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint21_obj);
	}
	if (flag_done_checkpoint22_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint22_obj);
	}
	if (flag_done_checkpoint23_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint23_obj);
	}
	if (flag_done_checkpoint24_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint24_obj);
	}
	if (flag_done_checkpoint25_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint25_obj);
	}
	if (flag_done_checkpoint26_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint26_obj);
	}
	if (flag_done_checkpoint27_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint27_obj);
	}
	if (flag_done_checkpoint28_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint28_obj);
	}
	if (flag_done_checkpoint29_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint29_obj);
	}
	if (flag_done_checkpoint30_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint30_obj);
	}
	if (flag_done_checkpoint31_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint31_obj);
	}
	if (flag_done_checkpoint32_kickstart == 0) {
		DELETE_CHECKPOINT(checkpoint32_obj);
	}

	if (skip == 1)
	{
		if (G_DIRTRING == 0)
		{
			INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
		}
		MissionFailed();
	}
	else if (skip == 2)
	{
		INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, add_cash);
		MissionPassed(add_cash, "missionpassed", "CASH");
	}

	CLEAR_PRINTS();
	STOP_STREAM();

	DO_SCREEN_FADE_OUT(1000);
	while (IS_SCREEN_FADING()) {
		WAIT(0);
	}
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
	MARK_CAR_AS_NO_LONGER_NEEDED(&bike_kickstart);
	if (!HAS_DEATHARREST_EXECUTED()) {
		LOAD_SCENE(-668.0, 1864.0, 14.1);
		if (IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
			WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), -668.0, 1864.0, 14.1);
		} else {
			SET_CHAR_COORDINATES(GetPlayerPed(), -668.0, 1864.0, 14.1);
		}
		SET_CHAR_HEADING(GetPlayerPed(), 278.650);
		SET_CAM_BEHIND_PED(GetPlayerPed());
		DO_SCREEN_FADE_IN(1500);
		SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	}
	REMOVE_IPL("stadint");
	STOP_SOUND(sID);
	RELEASE_SOUND_ID(sID);
	AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED();
	ENABLE_FRONTEND_RADIO();

	RELEASE_TEXTURE( fon );
	REMOVE_TXD( textur );
	FORWARD_TO_TIME_OF_DAY(01, 05);//устанавливаем время
	FORCE_WEATHER_NOW( weather );//устанавливаем погода
	RELEASE_WEATHER();
	TERMINATE_THIS_SCRIPT();
}

void mission_kickstart_failed(void) {
	//PRINT_BIG("K_FAIL", 5000, 1);
	skip = 1;
	mission_cleanup_kickstart();
}

void mission_kickstart_passed(void) {
	if (G_DIRTRING == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
		G_GAME_PROGRESS += 1;
		SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
		G_DIRTRING = 1;
	}
	CLEAR_WANTED_LEVEL(GetPlayerIndex());
	if (player_been_rewarded_kickstart == 0) {
		if (race_timer_kickstart <= 300000) {
			//PRINT_WITH_NUMBER_BIG("K_PASS", 50000, 5000, 1);
			skip = 2;
			add_cash = 50000;
			ADD_SCORE(GetPlayerIndex(), 50000);
			player_been_rewarded_kickstart = 1;
		}
	}
	if (player_been_rewarded_kickstart == 0) {
		if (race_timer_kickstart <= 600000) {
			//PRINT_WITH_NUMBER_BIG("K_PASS", 10000, 5000, 1);
			skip = 2;
			add_cash = 10000;
			ADD_SCORE(GetPlayerIndex(), 10000);
			player_been_rewarded_kickstart = 1;
		}
	}
	if (player_been_rewarded_kickstart == 0) {
		if (race_timer_kickstart <= 3600000) {
			//PRINT_WITH_NUMBER_BIG("K_PASS", 5000, 5000, 1);
			skip = 2;
			add_cash = 5000;
			ADD_SCORE(GetPlayerIndex(), 5000);
			player_been_rewarded_kickstart = 1;
		}
	}
	race_timer_seconds_kickstart = race_timer_kickstart / 1000;
	race_timer_mins_kickstart = race_timer_seconds_kickstart / 60;
	race_timer_seconds2_kickstart = race_timer_mins_kickstart * 60 ;
	race_timer_seconds_kickstart = race_timer_seconds_kickstart - race_timer_seconds2_kickstart;
	if (race_timer_seconds_kickstart >= 10) {
		PRINT_WITH_2_NUMBERS_NOW("KICKTM", race_timer_mins_kickstart, race_timer_seconds_kickstart, 5000, 1);
	} else {
		PRINT_WITH_2_NUMBERS_NOW("KICKTM2", race_timer_mins_kickstart, race_timer_seconds_kickstart, 5000, 1);
	}
	//WAIT(3000);
	SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
	//DO_SCREEN_FADE_OUT(1000);
	//while (IS_SCREEN_FADING()) {
	//	WAIT(0);
	//}
	mission_cleanup_kickstart();
}

void checkpoints_kickstart(void) {
	SET_CHAR_HEALTH(GetPlayerPed(), plhp);
	if (audio_flag_ohh_kick == 0) {
		audio_flag_ohh_kick = 1;
	}
	if (audio_flag_ohh_kick == 1) {
		audio_flag_ohh_kick = 2;
	}
	if (audio_flag_ohh_kick == 3) {
		if (HAS_SOUND_FINISHED(sID)) {
			audio_flag_ohh_kick = 4;
		}
	}
	if (audio_flag_ohh_kick == 4) {
		audio_flag_ohh_kick = 0;
	}
	
	DRAW_CHECKPOINT( -955.68, 1903.46, 24.0675, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
	if (race_timer_kickstart >= 3600000) {
		player_taken_too_long_kickstart = 1;
	}
	if ((LOCATE_CHAR_ON_FOOT_3D(GetPlayerPed(), -955.6803, 1903.454, 23.632, 3.0, 3.0, 3.0, 0)) && (IS_CHAR_STOPPED(GetPlayerPed()))) {
		player_in_end_area_kickstart = 1;
	}
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_x_kickstart, &player_y_kickstart, &player_z_kickstart);
	if (player_z_kickstart < 12.911) {
		SET_CHAR_COORDINATES(GetPlayerPed(), -843.2783, 1823.331, 21.072);
		SET_CHAR_HEADING(GetPlayerPed(), 0.0);
	}
	if (IS_CAR_DEAD(bike_kickstart)) {
		PRINT_NOW("KICK1_7", 5000, 1);	// ~r~You have wrecked the bike!
		flag_bike_dead_kickstart = 1;
	} else {
		SET_ENGINE_HEALTH(bike_kickstart, 1000);
		GET_CAR_COORDINATES(bike_kickstart, &bike_x_kickstart, &bike_y_kickstart, &bike_z_kickstart);
		if (bike_z_kickstart < 12.911) {
			SET_CAR_COORDINATES(bike_kickstart, -841.9463, 1825.646, 21.061);
			SET_CAR_HEADING(bike_kickstart, 0.0);
		}
	}
	if (flag_done_checkpoint1_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint1_x_kickstart, checkpoint1_y_kickstart, checkpoint1_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint1_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint1_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint1_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint2_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint2_x_kickstart, checkpoint2_y_kickstart, checkpoint2_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				if (audio_flag_cheer_kick == 2) {
					if ((!(player_checkpoint_kickstart == 7)) && (!(player_checkpoint_kickstart == 15)) && (!(player_checkpoint_kickstart == 23)) && (!(player_checkpoint_kickstart == 31))) {
						PLAY_SOUND_FRONTEND(sID, "DIRTRING_CHEER1");
						audio_flag_cheer_kick = 3;
					}
				}
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint2_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint2_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint2_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint3_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint3_x_kickstart, checkpoint3_y_kickstart, checkpoint3_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint3_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint3_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint3_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint4_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint4_x_kickstart, checkpoint4_y_kickstart, checkpoint4_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint4_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint4_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint4_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint5_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint5_x_kickstart, checkpoint5_y_kickstart, checkpoint5_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint5_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint5_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint5_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint6_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint6_x_kickstart, checkpoint6_y_kickstart, checkpoint6_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				if (audio_flag_cheer_kick == 2) {
					if ((!(player_checkpoint_kickstart == 7)) && (!(player_checkpoint_kickstart == 15)) && (!(player_checkpoint_kickstart == 23)) && (!(player_checkpoint_kickstart == 31))) {
						PLAY_SOUND_FRONTEND(sID, "DIRTRING_CHEER1");
						audio_flag_cheer_kick = 3;
					}
				}
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint6_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint6_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint6_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint7_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint7_x_kickstart, checkpoint7_y_kickstart, checkpoint7_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				if (audio_flag_cheer_kick == 2) {
					if ((!(player_checkpoint_kickstart == 7)) && (!(player_checkpoint_kickstart == 15)) && (!(player_checkpoint_kickstart == 23)) && (!(player_checkpoint_kickstart == 31))) {
						PLAY_SOUND_FRONTEND(sID, "DIRTRING_CHEER1");
						audio_flag_cheer_kick = 3;
					}
				}
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint7_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint7_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint7_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint8_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint8_x_kickstart, checkpoint8_y_kickstart, checkpoint8_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				if (audio_flag_cheer_kick == 2) {
					if ((!(player_checkpoint_kickstart == 7)) && (!(player_checkpoint_kickstart == 15)) && (!(player_checkpoint_kickstart == 23)) && (!(player_checkpoint_kickstart == 31))) {
						PLAY_SOUND_FRONTEND(sID, "DIRTRING_CHEER1");
						audio_flag_cheer_kick = 3;
					}
				}
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint8_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint8_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint8_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint9_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint9_x_kickstart, checkpoint9_y_kickstart, checkpoint9_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint9_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint9_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint9_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint10_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint10_x_kickstart, checkpoint10_y_kickstart, checkpoint10_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint10_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint10_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint10_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint11_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint11_x_kickstart, checkpoint11_y_kickstart, checkpoint11_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint11_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint11_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint11_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint12_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint12_x_kickstart, checkpoint12_y_kickstart, checkpoint12_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint12_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint12_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint12_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint13_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint13_x_kickstart, checkpoint13_y_kickstart, checkpoint13_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint13_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint13_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint13_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint14_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint14_x_kickstart, checkpoint14_y_kickstart, checkpoint14_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint14_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint14_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint14_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint15_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint15_x_kickstart, checkpoint15_y_kickstart, checkpoint15_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint15_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint15_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint15_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint16_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint16_x_kickstart, checkpoint16_y_kickstart, checkpoint16_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint16_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint16_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint16_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint17_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint17_x_kickstart, checkpoint17_y_kickstart, checkpoint17_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint17_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint17_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint17_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint18_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint18_x_kickstart, checkpoint18_y_kickstart, checkpoint18_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint18_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint18_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint18_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint19_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint19_x_kickstart, checkpoint19_y_kickstart, checkpoint19_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint19_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint19_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint19_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint20_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint20_x_kickstart, checkpoint20_y_kickstart, checkpoint20_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint20_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint20_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint20_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint21_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint21_x_kickstart, checkpoint21_y_kickstart, checkpoint21_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint21_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint21_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint21_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint22_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint22_x_kickstart, checkpoint22_y_kickstart, checkpoint22_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint22_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint22_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint22_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint23_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint23_x_kickstart, checkpoint23_y_kickstart, checkpoint23_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint23_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint23_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint23_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint24_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint24_x_kickstart, checkpoint24_y_kickstart, checkpoint24_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint24_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint24_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint24_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint25_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint25_x_kickstart, checkpoint25_y_kickstart, checkpoint25_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint25_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint25_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint25_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint26_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint26_x_kickstart, checkpoint26_y_kickstart, checkpoint26_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint26_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint26_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint26_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint27_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint27_x_kickstart, checkpoint27_y_kickstart, checkpoint27_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint27_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint27_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint27_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint28_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint28_x_kickstart, checkpoint28_y_kickstart, checkpoint28_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint28_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint28_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint28_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint29_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint29_x_kickstart, checkpoint29_y_kickstart, checkpoint29_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint29_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint29_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint29_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint30_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint30_x_kickstart, checkpoint30_y_kickstart, checkpoint30_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint30_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint30_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint30_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint31_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint31_x_kickstart, checkpoint31_y_kickstart, checkpoint31_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint31_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint31_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint31_kickstart = 1;
			}
		}
	}
	
	if (flag_done_checkpoint32_kickstart == 0) {
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), checkpoint32_x_kickstart, checkpoint32_y_kickstart, checkpoint32_z_kickstart, 1.5, 1.5, 1.5, 0)) {
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
				PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
				PRINT_NOW("KICK1_6", 1000, 1);	// ~g~Well done!
				REMOVE_BLIP(checkpoint32_blip_kickstart);
				DELETE_CHECKPOINT(checkpoint32_obj);
				player_checkpoint_kickstart++;
				number_of_checkpoints_kickstart--;
				flag_done_checkpoint32_kickstart = 1;
			}
		}
	}
	return;
}

void mission_start_kickstart(void) {
	if (G_DIRTRING == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}
	GET_CURRENT_WEATHER(&weather);
	FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
	FORWARD_TO_TIME_OF_DAY(20, 30);//устанавливаем время

	flag_bike_dead_kickstart = 0;
	bike_check_kickstart = 0;
	player_checkpoint_kickstart = 0;
	race_timer_kickstart = 0;
	time_left_to_find_bike_ks = 30000;
	
	checkpoint1_x_kickstart = -994.5952;
	checkpoint1_y_kickstart = 1859.514;
	checkpoint1_z_kickstart = 24.565;
	flag_done_checkpoint1_kickstart = 0;

	checkpoint2_x_kickstart = -843.6522;
	checkpoint2_y_kickstart = 1850.264;
	checkpoint2_z_kickstart = 24.41101;
	flag_done_checkpoint2_kickstart = 0;

	checkpoint3_x_kickstart = -845.6872;
	checkpoint3_y_kickstart = 1890.605;
	checkpoint3_z_kickstart = 22.659;
	flag_done_checkpoint3_kickstart = 0;

	checkpoint4_x_kickstart = -814.9272;
	checkpoint4_y_kickstart = 1865.771;
	checkpoint4_z_kickstart = 24.035;
	flag_done_checkpoint4_kickstart = 0;

	checkpoint5_x_kickstart = -812.9093;
	checkpoint5_y_kickstart = 1885.92;
	checkpoint5_z_kickstart = 24.091;
	flag_done_checkpoint5_kickstart = 0;

	checkpoint6_x_kickstart = -898.5823;
	checkpoint6_y_kickstart = 1857.972;
	checkpoint6_z_kickstart = 27.83002;
	flag_done_checkpoint6_kickstart = 0;

	checkpoint7_x_kickstart = -943.864;
	checkpoint7_y_kickstart = 1806.309;
	checkpoint7_z_kickstart = 37.74701;
	flag_done_checkpoint7_kickstart = 0;

	checkpoint8_x_kickstart = -927.6593;
	checkpoint8_y_kickstart = 1916.294;
	checkpoint8_z_kickstart = 24.604;
	flag_done_checkpoint8_kickstart = 0;

	checkpoint9_x_kickstart = -823.2533;
	checkpoint9_y_kickstart = 1874.038;
	checkpoint9_z_kickstart = 23.073;
	flag_done_checkpoint9_kickstart = 0;

	checkpoint10_x_kickstart = -822.4223;
	checkpoint10_y_kickstart = 1884.35;
	checkpoint10_z_kickstart = 23.978;
	flag_done_checkpoint10_kickstart = 0;

	checkpoint11_x_kickstart = -833.1562;
	checkpoint11_y_kickstart = 1863.597;
	checkpoint11_z_kickstart = 25.84702;
	flag_done_checkpoint11_kickstart = 0;

	checkpoint12_x_kickstart = -833.1973;
	checkpoint12_y_kickstart = 1849.068;
	checkpoint12_z_kickstart = 27.685;
	flag_done_checkpoint12_kickstart = 0;

	checkpoint13_x_kickstart = -854.3363;
	checkpoint13_y_kickstart = 1904.946;
	checkpoint13_z_kickstart = 24.91101;
	flag_done_checkpoint13_kickstart = 0;

	checkpoint14_x_kickstart = -858.2302;
	checkpoint14_y_kickstart = 1883.353;
	checkpoint14_z_kickstart = 21.55502;
	flag_done_checkpoint14_kickstart = 0;

	checkpoint15_x_kickstart = -888.4613;
	checkpoint15_y_kickstart = 1881.233;
	checkpoint15_z_kickstart = 22.91101;
	flag_done_checkpoint15_kickstart = 0;

	checkpoint16_x_kickstart = -898.1073;
	checkpoint16_y_kickstart = 1899.331;
	checkpoint16_z_kickstart = 22.84;
	flag_done_checkpoint16_kickstart = 0;

	checkpoint17_x_kickstart = -919.2053;
	checkpoint17_y_kickstart = 1894.461;
	checkpoint17_z_kickstart = 21.28101;
	flag_done_checkpoint17_kickstart = 0;

	checkpoint18_x_kickstart = -936.3762;
	checkpoint18_y_kickstart = 1892.453;
	checkpoint18_z_kickstart = 26.45602;
	flag_done_checkpoint18_kickstart = 0;

	checkpoint19_x_kickstart = -970.1383;
	checkpoint19_y_kickstart = 1882.36;
	checkpoint19_z_kickstart = 21.86301;
	flag_done_checkpoint19_kickstart = 0;

	checkpoint20_x_kickstart = -970.8304;
	checkpoint20_y_kickstart = 1842.712;
	checkpoint20_z_kickstart = 21.47501;
	flag_done_checkpoint20_kickstart = 0;

	checkpoint21_x_kickstart = -939.7363;
	checkpoint21_y_kickstart = 1823.104;
	checkpoint21_z_kickstart = 21.181;
	flag_done_checkpoint21_kickstart = 0;

	checkpoint22_x_kickstart = -910.5863;
	checkpoint22_y_kickstart = 1832.555;
	checkpoint22_z_kickstart = 21.19702;
	flag_done_checkpoint22_kickstart = 0;

	checkpoint23_x_kickstart = -935.1273;
	checkpoint23_y_kickstart = 1849.922;
	checkpoint23_z_kickstart = 24.35602;
	flag_done_checkpoint23_kickstart = 0;

	checkpoint24_x_kickstart = -924.8123;
	checkpoint24_y_kickstart = 1868.973;
	checkpoint24_z_kickstart = 25.89902;
	flag_done_checkpoint24_kickstart = 0;

	checkpoint25_x_kickstart = -889.0792;
	checkpoint25_y_kickstart = 1863.661;
	checkpoint25_z_kickstart = 25.66901;
	flag_done_checkpoint25_kickstart = 0;

	checkpoint26_x_kickstart = -876.4883;
	checkpoint26_y_kickstart = 1821.933;
	checkpoint26_z_kickstart = 22.85602;
	flag_done_checkpoint26_kickstart = 0;

	checkpoint27_x_kickstart = -856.7943;
	checkpoint27_y_kickstart = 1856.367;
	checkpoint27_z_kickstart = 21.94601;
	flag_done_checkpoint27_kickstart = 0;

	checkpoint28_x_kickstart = -1023.314;
	checkpoint28_y_kickstart = 1879.881;
	checkpoint28_z_kickstart = 23.91101;
	flag_done_checkpoint28_kickstart = 0;

	checkpoint29_x_kickstart = -1003.291;
	checkpoint29_y_kickstart = 1834.459;
	checkpoint29_z_kickstart = 24.25601;
	flag_done_checkpoint29_kickstart = 0;

	checkpoint30_x_kickstart = -1019.171;
	checkpoint30_y_kickstart = 1850.751;
	checkpoint30_z_kickstart = 23.267;
	flag_done_checkpoint30_kickstart = 0;

	checkpoint31_x_kickstart = -994.3692;
	checkpoint31_y_kickstart = 1825.858;
	checkpoint31_z_kickstart = 24.96002;
	flag_done_checkpoint31_kickstart = 0;

	checkpoint32_x_kickstart = -1006.865;
	checkpoint32_y_kickstart = 1888.82;
	checkpoint32_z_kickstart = 23.41101;
	flag_done_checkpoint32_kickstart = 0;

	race_timer_seconds_kickstart = 0;
	race_timer_seconds2_kickstart = 0;
	race_timer_mins_kickstart = 0;
	flag_bike_blip_on_kickstart = 0;
	player_taken_too_long_kickstart = 0;
	number_of_checkpoints_kickstart = 32;

	player_x_kickstart = 0.0;
	player_y_kickstart = 0.0;
	player_z_kickstart = 0.0;
	bike_x_kickstart = 0.0;
	bike_y_kickstart = 0.0;
	bike_z_kickstart = 0.0;
	skip = 0;

	player_in_end_area_kickstart = 0;
	player_been_rewarded_kickstart = 0;
	audio_flag_cheer_kick = 0;
	audio_flag_ohh_kick = 0;
	WAIT(0);
	LOAD_ADDITIONAL_TEXT("KICKSTT", 6);
	SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
	REQUEST_IPL("stadint");
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
	LOAD_SCENE(-741.8413, 1870.109, 21.051);
	REQUEST_MODEL(CarM1);
	while (!HAS_MODEL_LOADED(CarM1)) {
		WAIT(0);
	}

	GET_CHAR_HEALTH(GetPlayerPed(), &plhp);
	CREATE_CAM(14, &cam);
	SET_CAM_POS(cam, -849.4273, 1820.077, 22.85);
	POINT_CAM_AT_COORD(cam, -849.5693, 1820.589, 22.805);
	SET_CAM_ACTIVE(cam, 1);
	SET_CAM_PROPAGATE(cam, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	SET_CHAR_COORDINATES(GetPlayerPed(), -843.2783, 1823.331, 21.072);
	SET_CHAR_HEADING(GetPlayerPed(), 0.0);
	SET_CAM_BEHIND_PED(GetPlayerPed());
	CREATE_CAR(CarM1, -841.9463, 1825.646, 21.061, &bike_kickstart, 1);
	SET_CAR_PROOFS(bike_kickstart, 1, 1, 1, 1, 1);
	SET_CAR_STRONG(bike_kickstart, 1);

	//sphere_kickstart = ADD_SPHERE(-955.68, 1903.46, 24.0675, 3.0, 1);
	ADD_BLIP_FOR_COORD(-955.68, 1903.46, 24.0675, &sphere_kickstart);
	CHANGE_BLIP_SPRITE(sphere_kickstart, BLIP_OBJECTIVE);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(sphere_kickstart, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	//CHANGE_BLIP_NAME_FROM_TEXT_FILE(sphere_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(sphere_kickstart, 0.57999990); // масштаб иконки на радаре

	checkpoint1_obj = CREATE_CHECKPOINT(8, checkpoint1_x_kickstart, checkpoint1_y_kickstart, checkpoint1_z_kickstart, checkpoint1_x_kickstart, checkpoint1_y_kickstart, checkpoint1_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint1_x_kickstart, checkpoint1_y_kickstart, checkpoint1_z_kickstart, &checkpoint1_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint1_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint1_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint1_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint1_blip_kickstart, 0.77999990); // масштаб иконки на радаре

	
	checkpoint2_obj = CREATE_CHECKPOINT(8, checkpoint2_x_kickstart, checkpoint2_y_kickstart, checkpoint2_z_kickstart, checkpoint2_x_kickstart, checkpoint2_y_kickstart, checkpoint2_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint2_x_kickstart, checkpoint2_y_kickstart, checkpoint2_z_kickstart, &checkpoint2_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint2_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint2_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint2_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint2_blip_kickstart, 0.77999990); // масштаб иконки на радаре

	
	checkpoint3_obj = CREATE_CHECKPOINT(8, checkpoint3_x_kickstart, checkpoint3_y_kickstart, checkpoint3_z_kickstart, checkpoint3_x_kickstart, checkpoint3_y_kickstart, checkpoint3_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint3_x_kickstart, checkpoint3_y_kickstart, checkpoint3_z_kickstart, &checkpoint3_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint3_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint3_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint3_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint3_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint4_obj = CREATE_CHECKPOINT(8, checkpoint4_x_kickstart, checkpoint4_y_kickstart, checkpoint4_z_kickstart, checkpoint4_x_kickstart, checkpoint4_y_kickstart, checkpoint4_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint4_x_kickstart, checkpoint4_y_kickstart, checkpoint4_z_kickstart, &checkpoint4_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint4_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint4_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint4_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint4_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint5_obj = CREATE_CHECKPOINT(8, checkpoint5_x_kickstart, checkpoint5_y_kickstart, checkpoint5_z_kickstart, checkpoint5_x_kickstart, checkpoint5_y_kickstart, checkpoint5_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint5_x_kickstart, checkpoint5_y_kickstart, checkpoint5_z_kickstart, &checkpoint5_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint5_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint5_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint5_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint5_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint6_obj = CREATE_CHECKPOINT(8, checkpoint6_x_kickstart, checkpoint6_y_kickstart, checkpoint6_z_kickstart, checkpoint6_x_kickstart, checkpoint6_y_kickstart, checkpoint6_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint6_x_kickstart, checkpoint6_y_kickstart, checkpoint6_z_kickstart, &checkpoint6_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint6_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint6_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint6_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint6_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint7_obj = CREATE_CHECKPOINT(8, checkpoint7_x_kickstart, checkpoint7_y_kickstart, checkpoint7_z_kickstart, checkpoint7_x_kickstart, checkpoint7_y_kickstart, checkpoint7_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint7_x_kickstart, checkpoint7_y_kickstart, checkpoint7_z_kickstart, &checkpoint7_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint7_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint7_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint7_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint7_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint8_obj = CREATE_CHECKPOINT(8, checkpoint8_x_kickstart, checkpoint8_y_kickstart, checkpoint8_z_kickstart, checkpoint8_x_kickstart, checkpoint8_y_kickstart, checkpoint8_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint8_x_kickstart, checkpoint8_y_kickstart, checkpoint8_z_kickstart, &checkpoint8_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint8_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint8_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint8_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint8_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint9_obj = CREATE_CHECKPOINT(8, checkpoint9_x_kickstart, checkpoint9_y_kickstart, checkpoint9_z_kickstart, checkpoint9_x_kickstart, checkpoint9_y_kickstart, checkpoint9_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint9_x_kickstart, checkpoint9_y_kickstart, checkpoint9_z_kickstart, &checkpoint9_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint9_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint9_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint9_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint9_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint10_obj = CREATE_CHECKPOINT(8, checkpoint10_x_kickstart, checkpoint10_y_kickstart, checkpoint10_z_kickstart, checkpoint10_x_kickstart, checkpoint10_y_kickstart, checkpoint10_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint10_x_kickstart, checkpoint10_y_kickstart, checkpoint10_z_kickstart, &checkpoint10_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint10_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint10_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint10_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint10_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint11_obj = CREATE_CHECKPOINT(8, checkpoint11_x_kickstart, checkpoint11_y_kickstart, checkpoint11_z_kickstart, checkpoint11_x_kickstart, checkpoint11_y_kickstart, checkpoint11_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint11_x_kickstart, checkpoint11_y_kickstart, checkpoint11_z_kickstart, &checkpoint11_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint11_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint11_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint11_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint11_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint12_obj = CREATE_CHECKPOINT(8, checkpoint12_x_kickstart, checkpoint12_y_kickstart, checkpoint12_z_kickstart, checkpoint12_x_kickstart, checkpoint12_y_kickstart, checkpoint12_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint12_x_kickstart, checkpoint12_y_kickstart, checkpoint12_z_kickstart, &checkpoint12_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint12_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint12_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint12_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint12_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint13_obj = CREATE_CHECKPOINT(8, checkpoint13_x_kickstart, checkpoint13_y_kickstart, checkpoint13_z_kickstart, checkpoint13_x_kickstart, checkpoint13_y_kickstart, checkpoint13_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint13_x_kickstart, checkpoint13_y_kickstart, checkpoint13_z_kickstart, &checkpoint13_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint13_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint13_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint13_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint13_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint14_obj = CREATE_CHECKPOINT(8, checkpoint14_x_kickstart, checkpoint14_y_kickstart, checkpoint14_z_kickstart, checkpoint14_x_kickstart, checkpoint14_y_kickstart, checkpoint14_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint14_x_kickstart, checkpoint14_y_kickstart, checkpoint14_z_kickstart, &checkpoint14_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint14_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint14_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint14_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint14_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint15_obj = CREATE_CHECKPOINT(8, checkpoint15_x_kickstart, checkpoint15_y_kickstart, checkpoint15_z_kickstart, checkpoint15_x_kickstart, checkpoint15_y_kickstart, checkpoint15_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint15_x_kickstart, checkpoint15_y_kickstart, checkpoint15_z_kickstart, &checkpoint15_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint15_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint15_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint15_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint15_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint16_obj = CREATE_CHECKPOINT(8, checkpoint16_x_kickstart, checkpoint16_y_kickstart, checkpoint16_z_kickstart, checkpoint16_x_kickstart, checkpoint16_y_kickstart, checkpoint16_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint16_x_kickstart, checkpoint16_y_kickstart, checkpoint16_z_kickstart, &checkpoint16_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint16_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint16_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint16_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint16_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint17_obj = CREATE_CHECKPOINT(8, checkpoint17_x_kickstart, checkpoint17_y_kickstart, checkpoint17_z_kickstart, checkpoint17_x_kickstart, checkpoint17_y_kickstart, checkpoint17_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint17_x_kickstart, checkpoint17_y_kickstart, checkpoint17_z_kickstart, &checkpoint17_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint17_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint17_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint17_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint17_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint18_obj = CREATE_CHECKPOINT(8, checkpoint18_x_kickstart, checkpoint18_y_kickstart, checkpoint18_z_kickstart, checkpoint18_x_kickstart, checkpoint18_y_kickstart, checkpoint18_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint18_x_kickstart, checkpoint18_y_kickstart, checkpoint18_z_kickstart, &checkpoint18_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint18_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint18_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint18_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint18_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint19_obj = CREATE_CHECKPOINT(8, checkpoint19_x_kickstart, checkpoint19_y_kickstart, checkpoint19_z_kickstart, checkpoint19_x_kickstart, checkpoint19_y_kickstart, checkpoint19_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint19_x_kickstart, checkpoint19_y_kickstart, checkpoint19_z_kickstart, &checkpoint19_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint19_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint19_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint19_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint19_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint20_obj = CREATE_CHECKPOINT(8, checkpoint20_x_kickstart, checkpoint20_y_kickstart, checkpoint20_z_kickstart, checkpoint20_x_kickstart, checkpoint20_y_kickstart, checkpoint20_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint20_x_kickstart, checkpoint20_y_kickstart, checkpoint20_z_kickstart, &checkpoint20_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint20_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint20_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint20_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint20_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint21_obj = CREATE_CHECKPOINT(8, checkpoint21_x_kickstart, checkpoint21_y_kickstart, checkpoint21_z_kickstart, checkpoint21_x_kickstart, checkpoint21_y_kickstart, checkpoint21_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint21_x_kickstart, checkpoint21_y_kickstart, checkpoint21_z_kickstart, &checkpoint21_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint21_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint21_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint21_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint21_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint22_obj = CREATE_CHECKPOINT(8, checkpoint22_x_kickstart, checkpoint22_y_kickstart, checkpoint22_z_kickstart, checkpoint22_x_kickstart, checkpoint22_y_kickstart, checkpoint22_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint22_x_kickstart, checkpoint22_y_kickstart, checkpoint22_z_kickstart, &checkpoint22_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint22_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint22_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint22_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint22_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint23_obj = CREATE_CHECKPOINT(8, checkpoint23_x_kickstart, checkpoint23_y_kickstart, checkpoint23_z_kickstart, checkpoint23_x_kickstart, checkpoint23_y_kickstart, checkpoint23_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint23_x_kickstart, checkpoint23_y_kickstart, checkpoint23_z_kickstart, &checkpoint23_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint23_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint23_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint23_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint23_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint24_obj = CREATE_CHECKPOINT(8, checkpoint24_x_kickstart, checkpoint24_y_kickstart, checkpoint24_z_kickstart, checkpoint24_x_kickstart, checkpoint24_y_kickstart, checkpoint24_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint24_x_kickstart, checkpoint24_y_kickstart, checkpoint24_z_kickstart, &checkpoint24_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint24_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint24_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint24_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint24_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint25_obj = CREATE_CHECKPOINT(8, checkpoint25_x_kickstart, checkpoint25_y_kickstart, checkpoint25_z_kickstart, checkpoint25_x_kickstart, checkpoint25_y_kickstart, checkpoint25_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint25_x_kickstart, checkpoint25_y_kickstart, checkpoint25_z_kickstart, &checkpoint25_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint25_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint25_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint25_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint25_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint26_obj = CREATE_CHECKPOINT(8, checkpoint26_x_kickstart, checkpoint26_y_kickstart, checkpoint26_z_kickstart, checkpoint26_x_kickstart, checkpoint26_y_kickstart, checkpoint26_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint26_x_kickstart, checkpoint26_y_kickstart, checkpoint26_z_kickstart, &checkpoint26_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint26_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint26_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint26_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint26_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint27_obj = CREATE_CHECKPOINT(8, checkpoint27_x_kickstart, checkpoint27_y_kickstart, checkpoint27_z_kickstart, checkpoint27_x_kickstart, checkpoint27_y_kickstart, checkpoint27_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint27_x_kickstart, checkpoint27_y_kickstart, checkpoint27_z_kickstart, &checkpoint27_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint27_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint27_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint27_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint27_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint28_obj = CREATE_CHECKPOINT(8, checkpoint28_x_kickstart, checkpoint28_y_kickstart, checkpoint28_z_kickstart, checkpoint28_x_kickstart, checkpoint28_y_kickstart, checkpoint28_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint28_x_kickstart, checkpoint28_y_kickstart, checkpoint28_z_kickstart, &checkpoint28_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint28_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint28_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint28_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint28_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint29_obj = CREATE_CHECKPOINT(8, checkpoint29_x_kickstart, checkpoint29_y_kickstart, checkpoint29_z_kickstart, checkpoint29_x_kickstart, checkpoint29_y_kickstart, checkpoint29_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint29_x_kickstart, checkpoint29_y_kickstart, checkpoint29_z_kickstart, &checkpoint29_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint29_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint29_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint29_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint29_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint30_obj = CREATE_CHECKPOINT(8, checkpoint30_x_kickstart, checkpoint30_y_kickstart, checkpoint30_z_kickstart, checkpoint30_x_kickstart, checkpoint30_y_kickstart, checkpoint30_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint30_x_kickstart, checkpoint30_y_kickstart, checkpoint30_z_kickstart, &checkpoint30_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint30_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint30_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint30_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint30_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint31_obj = CREATE_CHECKPOINT(8, checkpoint31_x_kickstart, checkpoint31_y_kickstart, checkpoint31_z_kickstart, checkpoint31_x_kickstart, checkpoint31_y_kickstart, checkpoint31_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint31_x_kickstart, checkpoint31_y_kickstart, checkpoint31_z_kickstart, &checkpoint31_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint31_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint31_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint31_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint31_blip_kickstart, 0.77999990); // масштаб иконки на радаре
	
	checkpoint32_obj = CREATE_CHECKPOINT(8, checkpoint32_x_kickstart, checkpoint32_y_kickstart, checkpoint32_z_kickstart, checkpoint32_x_kickstart, checkpoint32_y_kickstart, checkpoint32_z_kickstart, 0.2);
	ADD_BLIP_FOR_COORD(checkpoint32_x_kickstart, checkpoint32_y_kickstart, checkpoint32_z_kickstart, &checkpoint32_blip_kickstart);
	CHANGE_BLIP_SPRITE(checkpoint32_blip_kickstart, BLIP_DESTINATION);//текстура иконки на радаре
	CHANGE_BLIP_COLOUR(checkpoint32_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(checkpoint32_blip_kickstart, "MO_TARGET");//иконка на радаре ""
	CHANGE_BLIP_SCALE(checkpoint32_blip_kickstart, 0.77999990); // масштаб иконки на радаре

	SET_INSTANT_WIDESCREEN_BORDERS(1);
	SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);
	SET_EVERYONE_IGNORE_PLAYER(GetPlayerIndex(), 1);
	WAIT(500);
	DO_SCREEN_FADE_IN(1500);
	SET_CAM_POS(cam, -842.7953, 1830.634, 22.898);
	POINT_CAM_AT_COORD(cam, -842.8343, 1831.631, 22.964);
	
	while (IS_SCREEN_FADING()) {
		WAIT(0);
		if (IS_CAR_DEAD(bike_kickstart)) {
			SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
			PRINT_NOW("KICK1_7", 5000, 1);	// ~r~You have wrecked the bike!
			//PRINT_BIG("K_FAIL", 5000, 1);
			//skip = 1;
			//DO_SCREEN_FADE_OUT(1000);
			//while (IS_SCREEN_FADING()) {
			//	WAIT(0);
			//}
			mission_kickstart_failed();
		} else {
			SET_ENGINE_HEALTH(bike_kickstart,  1000);
		}
		checkpoints_kickstart();
	}
	
	PRINT_NOW("KICK_10", 10000, 1);	// ~g~Use the Sanchez to complete the course by passing through all of the checkpoints.
	
	SetTime_intro(5000);		/*rebusx*/
	
	CLEAR_THIS_PRINT("KICK_10");
	SET_CHAR_COORDINATES(GetPlayerPed(), -969.9323, 1903.876, 24.389);
	
	if (!intro_skip)		/*rebusx*/
	{
		SET_CAM_POS(cam, -964.8133, 1898.472, 28.819);
		POINT_CAM_AT_COORD(cam, -963.9083, 1898.882, 28.701);
		PRINT_NOW("KICK_11", 10000, 1);	// ~g~To leave the mission stand in the ~q~pink marker~g~ on foot.
		SetTime_intro(5000);		/*rebusx*/
	}

	CLEAR_THIS_PRINT("KICK_11");
	SET_CHAR_COORDINATES(GetPlayerPed(), -843.2783, 1823.331, 21.072);
	WAIT(0);
	SET_CHAR_HEADING(GetPlayerPed(), 0.0);
	SET_INSTANT_WIDESCREEN_BORDERS(0);
	SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);
	SET_EVERYONE_IGNORE_PLAYER(GetPlayerIndex(), 0);
	SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	CAM_RESTORE_JUMPCUT();
	WARP_CHAR_INTO_CAR(GetPlayerPed(), bike_kickstart);
	WAIT(0);
	SET_CAM_BEHIND_PED(GetPlayerPed());
	PRINT_NOW("KICK1_1", 5000, 1);	// ~g~Complete the course as quickly as possible.
	
	SETTIMERA(0);
	SETTIMERC(0);
	while (!(player_checkpoint_kickstart == 32)) {
		if (TIMERC() >= 1000) {
			race_timer_kickstart += 1000;
			SETTIMERC(0);
		}
		if (HAS_DEATHARREST_EXECUTED()) {
			mission_kickstart_failed();
		}
		SET_CHAR_HEALTH(GetPlayerPed(), plhp);
		DRAW_SPRITE(fon, 0.8765625, 0.7858, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
		DRAW_SPRITE(fon, 0.8765625, 0.8194, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
		int timemin, timesec, timetemp;
		timesec = race_timer_kickstart / 1000;
		timemin = timesec / 60;
		timetemp = timemin * 60;
		timesec -= timetemp;
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "KICK1_T");
		if ((timesec > 9) && (timemin > 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9088542, 0.77031852, "HOTR_T1", timemin, timesec);
		} else if ((timesec <= 9) && (timemin <= 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9088542, 0.77031852, "HOTR_T3", timemin, timesec);
		} else if ((timesec > 9) && (timemin <= 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9088542, 0.77031852, "HOTR_T2", timemin, timesec);
		} else if ((timesec <= 9) && (timemin > 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9088542, 0.77031852, "HOTR_T0", timemin, timesec);
		}
		setup_draw_text();
		DISPLAY_TEXT(0.78815097, 0.81091852, "KICK1_C");
		if (number_of_checkpoints_kickstart > 9) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_NUMBER(0.92315097, 0.80491852, "HOTR_NB", number_of_checkpoints_kickstart);
		} else {
			setup_draw_value();
			DISPLAY_TEXT_WITH_NUMBER(0.93015097, 0.80491852, "HOTR_NB", number_of_checkpoints_kickstart);
		}

		GET_TIME_OF_DAY(&hour, &minute);
		if ((hour > 21) && (minute > 55)) {
			FORWARD_TO_TIME_OF_DAY(20, 25);//устанавливаем время
		}
			
		if (bike_check_kickstart == 0) {
			WAIT(0);			
			if (audio_flag_ohh_kick == 0) {
				audio_flag_ohh_kick = 1;
			}
			if (audio_flag_ohh_kick == 1) {
				audio_flag_ohh_kick = 2;
			}
			if (audio_flag_ohh_kick == 3) {
				if (HAS_SOUND_FINISHED(sID)) {
					audio_flag_ohh_kick = 4;
				}
			}
			if (audio_flag_ohh_kick == 4) {
				audio_flag_ohh_kick = 0;
			}
			
			if ((race_timer_kickstart >= 3600000) || (player_taken_too_long_kickstart == 1)) {
				SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
				//PRINT_BIG("K_FAIL", 5000, 1);
				PRINT_NOW("KICK_13", 5000, 1);	// ~r~You have taken too long!
				//skip = 1;
				//DO_SCREEN_FADE_OUT(1000);
				//while (IS_SCREEN_FADING()) {
				//	WAIT(0);
				//}
				mission_kickstart_failed();
			}
			
			if (((LOCATE_CHAR_ON_FOOT_3D(GetPlayerPed(), -955.6803, 1903.454, 23.632, 3.0, 3.0, 3.0, 0)) && (IS_CHAR_STOPPED(GetPlayerPed()))) || (player_in_end_area_kickstart == 1)) {
				SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
				//PRINT_BIG("K_FAIL", 5000, 1);
				PRINT_NOW("KICK_12", 5000, 1);	// ~r~You bottled it!
				//skip = 1;
				////REMOVE_SPHERE(sphere_kickstart);
				//DO_SCREEN_FADE_OUT(1000);
				//while (IS_SCREEN_FADING()) {
				//	WAIT(0);
				//}
				mission_kickstart_failed();
			}
			
			GET_CHAR_COORDINATES(GetPlayerPed(), &player_x_kickstart, &player_y_kickstart, &player_z_kickstart);
			if (player_z_kickstart < 12.911) {
				SET_CHAR_COORDINATES(GetPlayerPed(), -843.2783, 1823.331, 21.072);
				SET_CHAR_HEADING(GetPlayerPed(), 0.0);
			}
			
			if ((IS_CAR_DEAD(bike_kickstart)) || (flag_bike_dead_kickstart == 1)) {
				SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
				//PRINT_BIG("K_FAIL", 5000, 1);
				PRINT_NOW("KICK_7", 5000, 1);	// ~r~You have wrecked the bike!
				//skip = 1;
				//DO_SCREEN_FADE_OUT(1000);
				//while (IS_SCREEN_FADING()) {
				//	WAIT(0);
				//}
				mission_kickstart_failed();	
			} else {
				SET_ENGINE_HEALTH(bike_kickstart, 1000);
				GET_CAR_COORDINATES(bike_kickstart, &bike_x_kickstart, &bike_y_kickstart, &bike_z_kickstart);
				if (bike_z_kickstart < 12.911) {
					SET_CAR_COORDINATES(bike_kickstart, -841.9463, 1825.646, 21.061);
					SET_CAR_HEADING(bike_kickstart, 0.0);
				}
			}
			checkpoints_kickstart();
		}
		bike_check_kickstart = 0;
		if ((LOCATE_CHAR_ON_FOOT_3D(GetPlayerPed(), -955.6803, 1903.454, 24.632, 3.0, 3.0, 3.0, 0)) && (IS_CHAR_STOPPED(GetPlayerPed()))) {
			player_in_end_area_kickstart = 1;
		}
		if (!IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
			if (flag_bike_blip_on_kickstart == 0) {
				ADD_BLIP_FOR_CAR(bike_kickstart, &bike_blip_kickstart);
				CHANGE_BLIP_SPRITE(bike_blip_kickstart, BLIP_OBJECTIVE);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(bike_blip_kickstart, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(bike_blip_kickstart, "NE_CAR");//иконка на радаре ""
				CHANGE_BLIP_SCALE(bike_blip_kickstart, 0.57999990); // масштаб иконки на радаре

				if (audio_flag_ohh_kick == 2) {
					PLAY_SOUND_FRONTEND(sID, "DIRTRING_OOH1");
					audio_flag_ohh_kick = 3;
				}
				flag_bike_blip_on_kickstart = 1;
			}
			GET_GAME_TIMER(&time_bailed_ks);
			time_left_to_find_bike_ks = 30000;
			while (time_left_to_find_bike_ks > 0) {
				WAIT(0);
				if (HAS_DEATHARREST_EXECUTED()) {
					mission_kickstart_failed();
				}
				if (audio_flag_ohh_kick == 0) {
					audio_flag_ohh_kick = 1;
				}
				if (audio_flag_ohh_kick == 1) {
					audio_flag_ohh_kick = 2;
				}
				if (audio_flag_ohh_kick == 3) {
					if (HAS_SOUND_FINISHED(sID)) {
						audio_flag_ohh_kick = 4;
					}
				}
				if (audio_flag_ohh_kick == 4) {
					audio_flag_ohh_kick = 0;
				}
				
				if ((race_timer_kickstart >= 3600000) || (player_taken_too_long_kickstart == 1)) {
					SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
					//PRINT_BIG("K_FAIL", 5000, 1);
					PRINT_NOW("KICK_13", 5000, 1);	// ~r~You have taken too long!
					//skip = 1;
					//DO_SCREEN_FADE_OUT(1000);
					//while (IS_SCREEN_FADING()) {
					//	WAIT(0);
					//}
					mission_kickstart_failed();	
				}
				if (((LOCATE_CHAR_ON_FOOT_3D(GetPlayerPed(), -955.6803, 1903.454, 23.632, 3.0, 3.0, 3.0, 0)) && (IS_CHAR_STOPPED(GetPlayerPed()))) || (player_in_end_area_kickstart == 1)) {
					SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
					//PRINT_BIG("K_FAIL", 5000, 1);
					PRINT_NOW("KICK_12", 5000, 1);	// ~r~You bottled it!
					//skip = 1;
					////REMOVE_SPHERE(sphere_kickstart);
					//DO_SCREEN_FADE_OUT(1000);
					//while (IS_SCREEN_FADING()) {
					//	WAIT(0);
					//}
					mission_kickstart_failed();
				}
				GET_GAME_TIMER(&time_now_ks);
				time_off_bike_ks = time_now_ks - time_bailed_ks;
				time_bailed_ks = time_now_ks;
				time_left_to_find_bike_ks = time_left_to_find_bike_ks - time_off_bike_ks;
				time_left_to_find_bike_secs_ks = time_left_to_find_bike_ks / 1000;
				PRINT_WITH_NUMBER_NOW("GETBIKE", time_left_to_find_bike_secs_ks + 1, 1000, 1);
				if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SANCHEZ)) {
					CLEAR_THIS_PRINT("GETBIKE");
					time_left_to_find_bike_ks = 1;
					bike_check_kickstart = 1;
					break;
				}
			}
			if (bike_check_kickstart == 0) {
				if (time_left_to_find_bike_ks <= 0) {
					SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
					//PRINT_BIG("K_FAIL", 5000, 1);
					PRINT_NOW("KICK1_2", 5000, 1);	// ~r~You did not get back to the bike quickly enough!
					skip = 1;
					//DO_SCREEN_FADE_OUT(1000);
					//while (IS_SCREEN_FADING()) {
					//	WAIT(0);
					//}
					mission_kickstart_failed();
				} 
			}
		} else {
			CLEAR_THIS_PRINT("GETBIKE");
			if (flag_bike_blip_on_kickstart == 1) {
				REMOVE_BLIP(bike_blip_kickstart);
				flag_bike_blip_on_kickstart = 0;
			}
		}
	}
	mission_kickstart_passed();
}

void main(void) {
	mission_start_kickstart();
	if (HAS_DEATHARREST_EXECUTED()) {
		mission_kickstart_failed();
	}
	mission_cleanup_kickstart();
}