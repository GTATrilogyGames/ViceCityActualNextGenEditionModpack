#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
#include "mission_passed.h"
// начало миссии метод mission_start_mm()

int mm_car1, mm_car2, mm_car3, mm_car4, mm_car5, mm_car6, mm_car7, mm_car8;
int mm_car9, mm_car10, mm_car11, mm_car12, mm_car13, mm_car14, mm_car15, mm_car16;
int mm_driver1, mm_driver2, mm_driver3, mm_driver4, mm_driver5;
int mm_driver6, mm_driver7, mm_driver8, mm_driver9, mm_driver10, mm_driver11;
int mm_driver12, mm_driver13, mm_driver14, mm_driver15, mm_driver16;
int mmplayer_car;

int random_garage, cars_created, mm_cars_killed, mm_countdown, mm_attempt, mm_best_time;
int mm_longest_time, mm_car_health, mm_car_health_divided, where_is_player, zero_where_player;
int zero1, zero2, zero3, zero4, time_to_beat, letting_cars_do_stuff;
int mm_audio_flag, mm_sound1, mm_sound_playing, mm_cuntie, mm_adding_health;

float random_car_node_x, random_car_node_y, random_car_node_z, mm_car_heading;
float rnd_float1x, rnd_float1y, rnd_float2x, rnd_float2y;
float rnd_float3x, rnd_float3y, rnd_float4x, rnd_float4y;
float player_x, player_y, player_z, ex, ey, ez;
float plyr_rndx, plyr_rndy, plyr_rndz, bonus_on, bonus_time, set_go, skip;
int plyr_checkpoint_blip, button_pressed;
int cam, fon, textur, sID;
uint hour, minute, weather, checkpoint1;
uint CarM1 = MODEL_PEYOTE;//
uint CarM2 = MODEL_WILLARD;//
uint PedM1 = MODEL_M_M_PINDUS_01;//


#define KEYBOARD_ENTER			28		/*rebusx*/
#define KEYBOARD_SPACE			57
#define CONTROL_KEYBOARD_HORN	54
#define CONTROL_MOUSE_LEFT		38

#define CONTROLLER_BUTTON_B		17

int check_skip_intro()		/*rebusx*/
{
	if ( (!IS_USING_CONTROLLER() && (IS_GAME_KEYBOARD_KEY_PRESSED(KEYBOARD_ENTER) || IS_GAME_KEYBOARD_KEY_PRESSED(KEYBOARD_SPACE) || IS_CONTROL_PRESSED(2, CONTROL_KEYBOARD_HORN) || IS_CONTROL_PRESSED(2, CONTROL_MOUSE_LEFT)))
	|| (IS_USING_CONTROLLER() && IS_BUTTON_PRESSED(0, CONTROLLER_BUTTON_B)) )
	{
		return 1;
	}
	return 0;
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

void texty_wexty(void) {
	SET_TEXT_JUSTIFY(1);
	SET_TEXT_RIGHT_JUSTIFY(0);
	SET_TEXT_PROPORTIONAL(1);
	SET_TEXT_CENTRE(0);
	SET_TEXT_BACKGROUND(0);
	SET_TEXT_SCALE(0.3, 0.8);
	SET_TEXT_DROPSHADOW(1, 0, 0, 0, 255);
	return;
}

void mission_cleanup_mm(void) {
	if (skip == 1)
	{
		if (G_BLOODRING == 0)
		{
			INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
		}
		MissionFailed();
	}
	else if (skip == 2)
	{
		SETTIMERA(0); //сбрасываем таймер 
		while (true)
		{
			WAIT(0);
			if ( TIMERA() > 4000 )
			{
				break;
			}
			SET_TEXT_COLOUR(0, 197, 145, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT(0.5, 0.45, "BLOD_10");// пишем "Миссия завершина"

			SET_TEXT_COLOUR(50, 182, 255, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "BLOD_09", 1000);// +5000$
			if (G_BLOODRING == 0)
			{
				INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
				G_GAME_PROGRESS += 1;
				SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				G_BLOODRING = 1;
			}
		}
	}
	DO_SCREEN_FADE_OUT(1000);
	while (IS_SCREEN_FADING()) {
		WAIT(0);
	}

	STOP_STREAM();
	REMOVE_BLIP(plyr_checkpoint_blip);
	DELETE_CHECKPOINT(checkpoint1);
	LOAD_SCENE(-668.0, 1864.0, 14.1);
	SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	CLEAR_THIS_PRINT("BLOD_05");
	CLEAR_THIS_PRINT("BLOD_06");
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);
	REMOVE_IPL("blodring");
	STOP_SOUND(sID);
	RELEASE_SOUND_ID(sID);
	AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED();
	ENABLE_FRONTEND_RADIO();

	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car1);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car2);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car3);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car4);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car5);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car6);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car7);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car8);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car9);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car10);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car11);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car12);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car13);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car14);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car15);
	MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car16);

	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver1);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver2);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver3);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver4);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver5);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver6);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver7);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver8);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver9);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver10);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver11);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver12);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver13);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver14);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver15);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver16);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&mmplayer_car);

	RELEASE_TEXTURE( fon );
	REMOVE_TXD( textur );
	FORWARD_TO_TIME_OF_DAY(01, 05);//устанавливаем время
	FORCE_WEATHER_NOW( weather );//устанавливаем погода
	RELEASE_WEATHER();

	if (!HAS_DEATHARREST_EXECUTED()) {
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
	TERMINATE_THIS_SCRIPT();
}

void bitches_hoars(void) {
	time_to_beat += 60000;
	//DO_SCREEN_FADE_OUT(1000);
	//while (IS_SCREEN_FADING()) {
	//	WAIT(0);
	//}
	SET_INSTANT_WIDESCREEN_BORDERS(0);
	CANCEL_OVERRIDE_RESTART();
	SET_FREE_HEALTH_CARE(GetPlayerIndex(), 0);
	CLEAR_PRINTS();
	CLEAR_WANTED_LEVEL(GetPlayerIndex());
	mission_cleanup_mm();
}

void bitches(void) {
	while (TIMERA() < 0) {
		WAIT(0);
		texty_wexty();
		SET_TEXT_COLOUR(0, 0, 0, 255);
		DISPLAY_TEXT_WITH_NUMBER(0.05, 0.67, "BLOD_07", mm_longest_time);
		texty_wexty();
		SET_TEXT_COLOUR(0, 0, 0, 255);
		DISPLAY_TEXT_WITH_NUMBER(0.05, 0.7, "BLOD_08", mm_cars_killed);
	}
	bitches_hoars();
}

void mission_passed_mm(void) {
	PLAY_SOUND_FRONTEND(sID, "DIRTRING_AIRHORN");
	while (!HAS_SOUND_FINISHED(sID)) {
		WAIT(0);
	}
	SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
	SET_INSTANT_WIDESCREEN_BORDERS(1);
	if (!IS_CAR_DEAD(mm_car1)) {
		FREEZE_CAR_POSITION(mm_car1, 1);
	}
	if (!IS_CAR_DEAD(mm_car2)) {
		FREEZE_CAR_POSITION(mm_car2, 1);
	}
	if (!IS_CAR_DEAD(mm_car3)) {
		FREEZE_CAR_POSITION(mm_car3, 1);
	}
	if (!IS_CAR_DEAD(mm_car4)) {
		FREEZE_CAR_POSITION(mm_car4, 1);
	}
	if (!IS_CAR_DEAD(mm_car5)) {
		FREEZE_CAR_POSITION(mm_car5, 1);
	}
	if (!IS_CAR_DEAD(mm_car6)) {
		FREEZE_CAR_POSITION(mm_car6, 1);
	}
	if (!IS_CAR_DEAD(mm_car7)) {
		FREEZE_CAR_POSITION(mm_car7, 1);
	}
	if (!IS_CAR_DEAD(mm_car8)) {
		FREEZE_CAR_POSITION(mm_car8, 1);
	}
	if (!IS_CAR_DEAD(mm_car9)) {
		FREEZE_CAR_POSITION(mm_car9, 1);
	}
	if (!IS_CAR_DEAD(mm_car10)) {
		FREEZE_CAR_POSITION(mm_car10, 1);
	}
	if (!IS_CAR_DEAD(mm_car11)) {
		FREEZE_CAR_POSITION(mm_car11, 1);
	}
	if (!IS_CAR_DEAD(mm_car12)) {
		FREEZE_CAR_POSITION(mm_car12, 1);
	}
	if (!IS_CAR_DEAD(mm_car13)) {
		FREEZE_CAR_POSITION(mm_car13, 1);
	}
	if (!IS_CAR_DEAD(mm_car14)) {
		FREEZE_CAR_POSITION(mm_car14, 1);
	}
	if (!IS_CAR_DEAD(mm_car15)) {
		FREEZE_CAR_POSITION(mm_car15, 1);
	}
	if (!IS_CAR_DEAD(mm_car16)) {
		FREEZE_CAR_POSITION(mm_car16, 1);
	}
	
	//PRINT_BIG("BLOD_10", 6000, 5);
	//PRINT_WITH_NUMBER_BIG("BLOD_09", 1000, 6000, 6);
	skip = 2;
	ADD_SCORE(GetPlayerIndex(), 1000);
	INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 1000);
	mm_longest_time = time_to_beat ;
	mm_longest_time /= 1000; 
	mm_attempt++;
	mm_best_time++;
	SETTIMERA(0);
	bitches();
}

void mission_failed_mm(void) {
	//PRINT_BIG("BLOD_12", 5000, 1);
	skip = 1;
	mission_cleanup_mm();
	return;
}

void mm_sound(void) {
	GENERATE_RANDOM_INT_IN_RANGE(1, 22, &mm_sound1);
	if (mm_audio_flag == 0) {
		if (mm_cuntie == mm_sound1) {
			mm_sound1++;
			if (mm_sound1 > 21) {
				mm_sound1 = 1;
			}
		}
		
		if (mm_sound1 == 1) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE1");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 2) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE2");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 3) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE3");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 4) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE4");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 5) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE5");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 6) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE6");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 7) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE7");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 8) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE8");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 9) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE9");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 10) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE10");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 11) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE11");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 12) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE12");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 13) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE13");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 14) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE14");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 15) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE15");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 16) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_CHEER1");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 17) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_CHEER2");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 18) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_CHEER3");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 19) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_CHEER4");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 20) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_OOH1");
			mm_audio_flag = 1;
		}
		if (mm_sound1 == 21) {
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_OOH2");
			mm_audio_flag = 1;
		}
		mm_cuntie = mm_sound1;
	}
	
	if (mm_audio_flag == 1) {
		mm_audio_flag = 2;
	}
	if (mm_audio_flag == 2) {
		mm_audio_flag = 3;
	}
	if (mm_audio_flag == 3) {
		if (HAS_SOUND_FINISHED(sID)) {
			mm_audio_flag = 4;
		}
	}
	if (mm_audio_flag == 4) {
		mm_audio_flag = 0;
		mm_sound_playing = 0;
	}
	return;
}

void CAR_GOTO_COORDINATES_ACCURATE(int car, int driver, float fx, float fy, float fz) {
	int seq1;
	OPEN_SEQUENCE_TASK(&seq1);
	TASK_CAR_DRIVE_TO_COORD(0, car, fx, fy, fz, 30.0, 0, 0, 2, 10.0, -1);
	CLOSE_SEQUENCE_TASK(seq1);
	TASK_PERFORM_SEQUENCE(driver, seq1);
	CLEAR_SEQUENCE_TASK(seq1);
	return;
}

void SET_CAR_RAM_CAR(int mainCar, int mainDriver, int tarDriver) {
	int seq2;
	OPEN_SEQUENCE_TASK(&seq2);	
	TASK_CAR_MISSION_PED_TARGET(0, mainCar, tarDriver, 2, 200.0, 2, 0, 10);
	CLOSE_SEQUENCE_TASK(seq2);
	TASK_PERFORM_SEQUENCE(mainDriver, seq2);
	CLEAR_SEQUENCE_TASK(seq2);
	return;
}

void cunty_hoarz(void) {
	GENERATE_RANDOM_FLOAT_IN_RANGE(-810.614, -1028.614, &plyr_rndx);
	GENERATE_RANDOM_FLOAT_IN_RANGE(1804.186, 1917.186, &plyr_rndy);
	GET_GROUND_Z_FOR_3D_COORD(plyr_rndx, plyr_rndy, 41.311, &plyr_rndz);
	if (plyr_rndz > 19.311) {
		cunty_hoarz();
	}
	if (plyr_rndz < 8.311) {
		cunty_hoarz();
	}
	REMOVE_BLIP(plyr_checkpoint_blip);
	DELETE_CHECKPOINT(checkpoint1);
	checkpoint1 = CREATE_CHECKPOINT( 8, plyr_rndx, plyr_rndy, plyr_rndz+2, plyr_rndx, plyr_rndy, plyr_rndz+2, 0.50000000 );
	ADD_BLIP_FOR_COORD(plyr_rndx, plyr_rndy, plyr_rndz, &plyr_checkpoint_blip);
	CHANGE_BLIP_COLOUR(plyr_checkpoint_blip, BLIP_COLOR_YELLOW);
	return;
}

void random_garages(void) {
	GENERATE_RANDOM_INT_IN_RANGE(1, 4, &random_garage);
	WAIT(0);
	DRAW_CORONA(plyr_rndx, plyr_rndy, plyr_rndz, 5.0, 6, 0, 150, 150, 0);
	if (mm_sound_playing == 1) {
		mm_sound();
	}
	
	if (random_garage == 1) {
		if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-981.919, 1807.04, 21.5208, 5.0, 5.0, 5.0)) {
			random_car_node_x = -981.919;
			random_car_node_y = 1807.04;
			random_car_node_z = 21.5208;
			mm_car_heading = 345.6;
		} else {
			random_garages();
		}
	}
	
	if (random_garage == 2) {
		if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-944.308, 1800.45, 21.2782, 5.0, 5.0, 5.0)) {
			random_car_node_x = -944.308;
			random_car_node_y = 1800.45;
			random_car_node_z = 21.2782;
		} else {
			random_garages();
		}
	}
	
	if (random_garage == 3) {
		if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(-963.059, 1802.92, 21.4085, 5.0, 5.0, 5.0)) {
			random_car_node_x = -963.059;
			random_car_node_y = 1802.92;
			random_car_node_z = 21.4085;
			mm_car_heading = 351.4; 
		} else {
			random_garages();
		}
	}
	return;
}

void create_cars_mm(void) {
	random_garages();
	if (IS_CAR_DEAD(mm_car1)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car1);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car1);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver1);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car1, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car1, 5, PedM1, &mm_driver1);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car1, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car1, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver1, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car1, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car1, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car1);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver1, 0);
		SET_CAR_FORWARD_SPEED(mm_car1, 25.0);
		SET_CAR_RAM_CAR(mm_car1, mm_driver1, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car2)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car2);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car2);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver2);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car2, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car2, 5, PedM1, &mm_driver2);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car2, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car2, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver2, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car2, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car2, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car2);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver2, 0);
		SET_CAR_FORWARD_SPEED(mm_car2, 25.0);
		SET_CAR_RAM_CAR(mm_car2, mm_driver2, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car3)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car3);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car3);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver3);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car3, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car3, 5, PedM1, &mm_driver3);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car3, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car3, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver3, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car3, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car3, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car3);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver3, 0);
		SET_CAR_FORWARD_SPEED(mm_car3, 25.0);
		SET_CAR_RAM_CAR(mm_car3, mm_driver3, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car4)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car4);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car4);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver4);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car4, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car4, 5, PedM1, &mm_driver4);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car4, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car4, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver4, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car4, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car4, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car4);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver4, 0);
		SET_CAR_FORWARD_SPEED(mm_car4, 25.0);
		SET_CAR_RAM_CAR(mm_car4, mm_driver4, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car5)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car5);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car5);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver5);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car5, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car5, 5, PedM1, &mm_driver5);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car5, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car5, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver5, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car5, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car5, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car5);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver5, 0);
		SET_CAR_FORWARD_SPEED(mm_car5, 25.0);
		SET_CAR_RAM_CAR(mm_car5, mm_driver5, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car6)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car6);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car6);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver6);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car6, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car6, 5, PedM1, &mm_driver6);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car6, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car6, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver6, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car6, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car6, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car6);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver6, 0);
		SET_CAR_FORWARD_SPEED(mm_car6, 25.0);
		SET_CAR_RAM_CAR(mm_car6, mm_driver6, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car7)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car7);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car7);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver7);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car7, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car7, 5, PedM1, &mm_driver7);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car7, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car7, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver7, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car7, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car7, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car7);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver7, 0);
		SET_CAR_FORWARD_SPEED(mm_car7, 25.0);
		SET_CAR_RAM_CAR(mm_car7, mm_driver7, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car7)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car7);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car7);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver7);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car7, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car7, 5, PedM1, &mm_driver7);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car7, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car7, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver7, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car7, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car7, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car7);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver7, 0);
		SET_CAR_FORWARD_SPEED(mm_car7, 25.0);
		SET_CAR_RAM_CAR(mm_car7, mm_driver7, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car8)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car8);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car8);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver8);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car8, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car8, 5, PedM1, &mm_driver8);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car8, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car8, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver8, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car8, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car8, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car8);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver8, 0);
		SET_CAR_FORWARD_SPEED(mm_car8, 25.0);
		SET_CAR_RAM_CAR(mm_car8, mm_driver8, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car9)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car9);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car9);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver9);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car9, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car9, 5, PedM1, &mm_driver9);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car9, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car9, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver9, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car9, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car9, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car9);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver9, 0);
		SET_CAR_FORWARD_SPEED(mm_car9, 25.0);
		SET_CAR_RAM_CAR(mm_car9, mm_driver9, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car10)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car10);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car10);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver10);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car10, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car10, 5, PedM1, &mm_driver10);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car10, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car10, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver10, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car10, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car10, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car10);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver10, 0);
		SET_CAR_FORWARD_SPEED(mm_car10, 25.0);
		SET_CAR_RAM_CAR(mm_car10, mm_driver10, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car11)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car11);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car11);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver11);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car11, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car11, 5, PedM1, &mm_driver11);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car11, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car11, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver11, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car11, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car11, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car11);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver11, 0);
		SET_CAR_FORWARD_SPEED(mm_car11, 25.0);
		SET_CAR_RAM_CAR(mm_car11, mm_driver11, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car12)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car12);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car12);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver12);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car12, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car12, 5, PedM1, &mm_driver12);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car12, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car12, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver12, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car12, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car12, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car12);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver12, 0);
		SET_CAR_FORWARD_SPEED(mm_car12, 25.0);
		SET_CAR_RAM_CAR(mm_car12, mm_driver12, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car13)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car13);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car13);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver13);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car13, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car13, 5, PedM1, &mm_driver13);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car13, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car13, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver13, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car13, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car13, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car13);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver13, 0);
		SET_CAR_FORWARD_SPEED(mm_car13, 25.0);
		SET_CAR_RAM_CAR(mm_car13, mm_driver13, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car14)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car14);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car14);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver14);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car14, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car14, 5, PedM1, &mm_driver14);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car14, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car14, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver14, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car14, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car14, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car14);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver14, 0);
		SET_CAR_FORWARD_SPEED(mm_car14, 25.0);
		SET_CAR_RAM_CAR(mm_car14, mm_driver14, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car15)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car15);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car15);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver15);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car15, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car15, 5, PedM1, &mm_driver15);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car15, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car15, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver15, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car15, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car15, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car15);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver15, 0);
		SET_CAR_FORWARD_SPEED(mm_car15, 25.0);
		SET_CAR_RAM_CAR(mm_car15, mm_driver15, GetPlayerPed());
		cars_created++;
	}
	
	random_garages();
	if (IS_CAR_DEAD(mm_car16)) {
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
			//PRINT_WITH_NUMBER_BIG("BONUS", 100, 1000, 1);
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			bonus_on = 1;
			bonus_time = 0;
			ADD_SCORE(GetPlayerIndex(), 100);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
		}
		REMOVE_STUCK_CAR_CHECK(mm_car16);
		MARK_CAR_AS_NO_LONGER_NEEDED(&mm_car16);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&mm_driver16);
		CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car16, 1);
		CREATE_CHAR_INSIDE_CAR(mm_car16, 5, PedM1, &mm_driver16);
		SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car16, 255.0);
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(mm_car16, 1);
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver16, 100.0);
		ADD_STUCK_CAR_CHECK(mm_car16, 1.5, 4000);
		SET_CAR_ENGINE_ON(mm_car16, 1, 1);
		ADD_UPSIDEDOWN_CAR_CHECK(mm_car16);
		SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver16, 0);
		SET_CAR_FORWARD_SPEED(mm_car16, 25.0);
		SET_CAR_RAM_CAR(mm_car16, mm_driver16, GetPlayerPed());
		cars_created++;
	}
	return;
}

void skip_mm_initial_cutscene(void) {
	CLEAR_PRINTS();
	CAM_RESTORE_JUMPCUT();
	SET_CAM_BEHIND_PED(GetPlayerPed());
	SET_INSTANT_WIDESCREEN_BORDERS(0);
	
	PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
	SETTIMERA(0);
	while (true)
	{
		SET_TEXT_FONT(4);
		SET_TEXT_COLOUR(235, 115, 18, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(2, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", 3);// 3
		if (TIMERA() > 900)
		{
			break;
		}
		WAIT(0);
	}
	PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
	SETTIMERA(0);
	while (true)
	{
		SET_TEXT_FONT(4);
		SET_TEXT_COLOUR(235, 115, 18, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(2, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", 2);// 2
		if (TIMERA() > 900)
		{
			break;
		}
		WAIT(0);
	}
	PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
	SETTIMERA(0);
	while (true)
	{
		SET_TEXT_FONT(4);
		SET_TEXT_COLOUR(235, 115, 18, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(2, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", 1);// 1
		if (TIMERA() > 900)
		{
			break;
		}
		WAIT(0);
	}
	PLAY_AUDIO_EVENT( "FRONTEND_GAME_PICKUP_CHECKPOINT" );
	set_go = 1;

	//PRINT_BIG("RACE2", 1100, 4);
	//PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
	//WAIT(1000);
	//PRINT_BIG("RACE3", 1100, 4);
	//PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
	//WAIT(1000);
	//PRINT_BIG("RACE4", 1100, 4);
	//PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
	//WAIT(1000);
	//PRINT_BIG("RACE5", 1100, 4);
	//PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_GO");
	//WAIT(800);
	//CLEAR_PRINTS();
	SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	
	if (!IS_CAR_DEAD(mm_car1)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver1, 100.0);
		int seqb1;
		OPEN_SEQUENCE_TASK(&seqb1);
		TASK_CAR_TEMP_ACTION(0, mm_car1, 9, 5000);
		if (!IS_CAR_DEAD(mm_car2)) {
			TASK_CAR_MISSION_PED_TARGET(0, mm_car1, mm_driver2, 2, 200.0, 2, 0, 10);			
		}
		CLOSE_SEQUENCE_TASK(seqb1);
		TASK_PERFORM_SEQUENCE(mm_driver1, seqb1);
		CLEAR_SEQUENCE_TASK(seqb1);	
	}
	if (!IS_CAR_DEAD(mm_car2)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver2, 100.0);
		int seqb2;
		OPEN_SEQUENCE_TASK(&seqb2);
		TASK_CAR_TEMP_ACTION(0, mm_car2, 9, 5000);
		TASK_CAR_MISSION_PED_TARGET(0, mm_car2, GetPlayerPed(), 2, 200.0, 2, 0, 10);
		CLOSE_SEQUENCE_TASK(seqb2);
		TASK_PERFORM_SEQUENCE(mm_driver2, seqb2);
		CLEAR_SEQUENCE_TASK(seqb2);	
	}
	if (!IS_CAR_DEAD(mm_car3)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver3, 100.0);
		int seqb3;
		OPEN_SEQUENCE_TASK(&seqb3);
		TASK_CAR_TEMP_ACTION(0, mm_car3, 9, 5000);
		CLOSE_SEQUENCE_TASK(seqb3);
		TASK_PERFORM_SEQUENCE(mm_driver3, seqb3);
		CLEAR_SEQUENCE_TASK(seqb3);	
	}
	if (!IS_CAR_DEAD(mm_car4)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver4, 100.0);
		int seqb4;
		OPEN_SEQUENCE_TASK(&seqb4);
		TASK_CAR_TEMP_ACTION(0, mm_car4, 9, 5000);
		if (!IS_CAR_DEAD(mm_car5)) {
			TASK_CAR_MISSION_PED_TARGET(0, mm_car4, mm_driver5, 2, 200.0, 2, 0, 10);
		}
		CLOSE_SEQUENCE_TASK(seqb4);
		TASK_PERFORM_SEQUENCE(mm_driver4, seqb4);
		CLEAR_SEQUENCE_TASK(seqb4);	
	}
	if (!IS_CAR_DEAD(mm_car5)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver5, 100.0);
		int seqb5;
		OPEN_SEQUENCE_TASK(&seqb5);
		TASK_CAR_TEMP_ACTION(0, mm_car5, 9, 5000);
		if (!IS_CAR_DEAD(mm_car6)) {
			TASK_CAR_MISSION_PED_TARGET(0, mm_car5, mm_driver6, 2, 200.0, 2, 0, 10);
		}
		CLOSE_SEQUENCE_TASK(seqb5);
		TASK_PERFORM_SEQUENCE(mm_driver5, seqb5);
		CLEAR_SEQUENCE_TASK(seqb5);	
	}
	if (!IS_CAR_DEAD(mm_car6)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver6, 100.0);
		int seqb6;
		OPEN_SEQUENCE_TASK(&seqb6);
		TASK_CAR_TEMP_ACTION(0, mm_car6, 9, 5000);
		TASK_CAR_MISSION_PED_TARGET(0, mm_car6, GetPlayerPed(), 2, 200.0, 2, 0, 10);
		CLOSE_SEQUENCE_TASK(seqb6);
		TASK_PERFORM_SEQUENCE(mm_driver6, seqb6);
		CLEAR_SEQUENCE_TASK(seqb6);	
	}
	if (!IS_CAR_DEAD(mm_car7)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver7, 100.0);
		int seqb7;
		OPEN_SEQUENCE_TASK(&seqb7);
		TASK_CAR_TEMP_ACTION(0, mm_car7, 9, 5000);
		if (!IS_CAR_DEAD(mm_car8)) {
			TASK_CAR_MISSION_PED_TARGET(0, mm_car7, mm_driver8, 2, 200.0, 2, 0, 10);
		}
		CLOSE_SEQUENCE_TASK(seqb7);
		TASK_PERFORM_SEQUENCE(mm_driver7, seqb7);
		CLEAR_SEQUENCE_TASK(seqb7);	
	}
	if (!IS_CAR_DEAD(mm_car8)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver8, 100.0);
		int seqb8;
		OPEN_SEQUENCE_TASK(&seqb8);
		TASK_CAR_TEMP_ACTION(0, mm_car8, 9, 5000);
		if (!IS_CAR_DEAD(mm_car9)) {
			TASK_CAR_MISSION_PED_TARGET(0, mm_car8, mm_driver9, 2, 200.0, 2, 0, 10);
		}
		CLOSE_SEQUENCE_TASK(seqb8);
		TASK_PERFORM_SEQUENCE(mm_driver8, seqb8);
		CLEAR_SEQUENCE_TASK(seqb8);	
	}
	if (!IS_CAR_DEAD(mm_car9)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver9, 100.0);
		int seqb9;
		OPEN_SEQUENCE_TASK(&seqb9);
		TASK_CAR_TEMP_ACTION(0, mm_car9, 9, 5000);
		if (!IS_CAR_DEAD(mm_car10)) {
			TASK_CAR_MISSION_PED_TARGET(0, mm_car9, mm_driver10, 2, 200.0, 2, 0, 10);
		}
		CLOSE_SEQUENCE_TASK(seqb9);
		TASK_PERFORM_SEQUENCE(mm_driver9, seqb9);
		CLEAR_SEQUENCE_TASK(seqb9);	
	}
	if (!IS_CAR_DEAD(mm_car10)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver10, 100.0);
		int seqb10;
		OPEN_SEQUENCE_TASK(&seqb10);
		TASK_CAR_TEMP_ACTION(0, mm_car10, 9, 5000);
		CLOSE_SEQUENCE_TASK(seqb10);
		TASK_PERFORM_SEQUENCE(mm_driver10, seqb10);
		CLEAR_SEQUENCE_TASK(seqb10);	
	}
	if (!IS_CAR_DEAD(mm_car11)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver11, 100.0);
		int seqb11;
		OPEN_SEQUENCE_TASK(&seqb11);
		TASK_CAR_TEMP_ACTION(0, mm_car11, 9, 5000);
		if (!IS_CAR_DEAD(mm_car12)) {
			TASK_CAR_MISSION_PED_TARGET(0, mm_car11, mm_driver12, 2, 200.0, 2, 0, 10);
		}
		CLOSE_SEQUENCE_TASK(seqb11);
		TASK_PERFORM_SEQUENCE(mm_driver11, seqb11);
		CLEAR_SEQUENCE_TASK(seqb11);	
	}
	if (!IS_CAR_DEAD(mm_car12)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver12, 100.0);
		int seqb12;
		OPEN_SEQUENCE_TASK(&seqb12);
		if (!IS_CAR_DEAD(mm_car13)) {
			TASK_CAR_MISSION_PED_TARGET(0, mm_car12, mm_driver13, 2, 200.0, 2, 0, 10);
		}
		CLOSE_SEQUENCE_TASK(seqb12);
		TASK_PERFORM_SEQUENCE(mm_driver12, seqb12);
		CLEAR_SEQUENCE_TASK(seqb12);
	}
	if (!IS_CAR_DEAD(mm_car13)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver13, 100.0);
		int seqb13;
		OPEN_SEQUENCE_TASK(&seqb13);
		if (!IS_CAR_DEAD(mm_car14)) {
			TASK_CAR_MISSION_PED_TARGET(0, mm_car13, mm_driver14, 2, 200.0, 2, 0, 10);
		}
		CLOSE_SEQUENCE_TASK(seqb13);
		TASK_PERFORM_SEQUENCE(mm_driver13, seqb13);
		CLEAR_SEQUENCE_TASK(seqb13);
	}
	if (!IS_CAR_DEAD(mm_car14)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver14, 100.0);
		int seqb14;
		OPEN_SEQUENCE_TASK(&seqb14);
		if (!IS_CAR_DEAD(mm_car15)) {
			TASK_CAR_MISSION_PED_TARGET(0, mm_car14, mm_driver15, 2, 200.0, 2, 0, 10);
		}
		CLOSE_SEQUENCE_TASK(seqb14);
		TASK_PERFORM_SEQUENCE(mm_driver14, seqb14);
		CLEAR_SEQUENCE_TASK(seqb14);
	}
	if (!IS_CAR_DEAD(mm_car15)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver15, 100.0);
		int seqb15;
		OPEN_SEQUENCE_TASK(&seqb15);
		if (!IS_CAR_DEAD(mm_car16)) {
			TASK_CAR_MISSION_PED_TARGET(0, mm_car15, mm_driver16, 2, 200.0, 2, 0, 10);
		}
		CLOSE_SEQUENCE_TASK(seqb15);
		TASK_PERFORM_SEQUENCE(mm_driver15, seqb15);
		CLEAR_SEQUENCE_TASK(seqb15);
	}
	if (!IS_CAR_DEAD(mm_car16)) {
		SET_DRIVE_TASK_CRUISE_SPEED(mm_driver16, 100.0);
		int seqb16;
		OPEN_SEQUENCE_TASK(&seqb16);
		if (!IS_CAR_DEAD(mm_car1)) {
			TASK_CAR_MISSION_PED_TARGET(0, mm_car16, mm_driver1, 2, 200.0, 2, 0, 10);
		}
		CLOSE_SEQUENCE_TASK(seqb16);
		TASK_PERFORM_SEQUENCE(mm_driver16, seqb16);
		CLEAR_SEQUENCE_TASK(seqb16);
	}
	
	GENERATE_RANDOM_FLOAT_IN_RANGE(-1050.614, -904.614, &rnd_float1x);
	GENERATE_RANDOM_FLOAT_IN_RANGE(1860.186, 1788.186, &rnd_float1y);
	GENERATE_RANDOM_FLOAT_IN_RANGE(-1050.614, -904.614, &rnd_float2x);
	GENERATE_RANDOM_FLOAT_IN_RANGE(1860.186, 1921.186, &rnd_float2y);
	GENERATE_RANDOM_FLOAT_IN_RANGE(-785.614, -904.614, &rnd_float3x);
	GENERATE_RANDOM_FLOAT_IN_RANGE(1860.186, 1788.186, &rnd_float3y);
	GENERATE_RANDOM_FLOAT_IN_RANGE(-785.614, -904.614, &rnd_float4x);
	GENERATE_RANDOM_FLOAT_IN_RANGE(1860.186, 1921.186, &rnd_float4y);
	cunty_hoarz();
	SETTIMERA(0);
	SETTIMERB(0);
	SETTIMERC(0);
	while (mm_countdown > 0) {
		WAIT(0);
		if (TIMERC() >= 1000) {
			mm_countdown -= 1000;
			if ((bonus_on == 1)|| (set_go == 1)) bonus_time += 1;
			SETTIMERC(0);
			if (mm_countdown < 0) {
				mm_countdown = 0;
			}
		}

		if (set_go == 1)
		{
			SET_TEXT_FONT(4);
			SET_TEXT_COLOUR(235, 115, 18, 255);
			SET_TEXT_SCALE(0.5, 0.7);
			SET_TEXT_EDGE(2, 0, 0, 0, 255);
			SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "GO", 1); // пишем "GO"
			if (bonus_time > 1)
			{
				set_go = 0;
			}
		}
		if (bonus_on == 1)
		{
			SET_TEXT_COLOUR(255, 159, 255, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "BONUS", 100);//BONUS $~1~
			if (bonus_time > 2)
			{
				bonus_on = 0;
			}
		}

		GET_TIME_OF_DAY(&hour, &minute);
		if ((hour > 21) && (minute > 55)) {
			FORWARD_TO_TIME_OF_DAY(20, 25);//устанавливаем время
		}
		
		DRAW_SPRITE(fon, 0.8765625, 0.7858, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
		DRAW_SPRITE(fon, 0.8765625, 0.8194, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
		DRAW_SPRITE(0, 0.915054, 0.8194, 0.059166, 0.014, 0.0, 27, 89, 130, 255);
		int timemin, timesec, timetemp;
		timesec = mm_countdown / 1000;
		timemin = timesec / 60;
		timetemp = timemin * 60;
		timesec -= timetemp;
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "HOTR_1A");
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
		DISPLAY_TEXT(0.78815097, 0.81091852, "BLOD_04");
		setup_draw_value();
		float carH3 = mm_car_health_divided * 0.059166 / 100.0;
		float carHUD_y3 = (0.915054 + carH3 / 2.0) - 0.059166 / 2.0;
		DRAW_SPRITE(0, carHUD_y3, 0.8194, carH3, 0.014, 0.0, 97, 194, 247, 255);
		
		if (mm_attempt == 0) {
			PRINT_WITH_NUMBER("BLOD_05", mm_best_time, time_to_beat, 1);
		} else {
			PRINT_WITH_NUMBER("BLOD_06", mm_best_time, time_to_beat, 1);
		}
		if (mm_countdown > time_to_beat) {
			mission_passed_mm();
		}
		if (mm_sound_playing == 1) {
			mm_sound();
		}
		//DRAW_CHECKPOINT(plyr_rndx, plyr_rndy, plyr_rndz, 5.0, 150, 150, 0);
		if (LOCATE_CHAR_ANY_MEANS_3D(GetPlayerPed(), plyr_rndx, plyr_rndy, plyr_rndz, 7.0, 7.0, 7.0, 0)) {
			if (!IS_CAR_DEAD(mmplayer_car)) {
				mm_adding_health = GET_ENGINE_HEALTH(mmplayer_car);
				if (mm_adding_health < 1234) {
					mm_adding_health += 15;
					SET_ENGINE_HEALTH(mmplayer_car, mm_adding_health);
				} else {
					mm_adding_health = 1249;
					SET_ENGINE_HEALTH(mmplayer_car, mm_adding_health);
				}
			}
			mm_countdown += 15000;
			PLAY_SOUND_FRONTEND(sID, "DIRTRING_RACE_COUNT");
			cunty_hoarz();
		}
		if (!IS_CAR_DEAD(mm_car3)) {
			if (LOCATE_CAR_3D(mm_car3, plyr_rndx, plyr_rndy, plyr_rndz, 7.0, 7.0, 7.0, 0)) {
				cunty_hoarz();
			}
		}
		if (!IS_CAR_DEAD(mm_car10)) {
			if (LOCATE_CAR_3D(mm_car10, plyr_rndx, plyr_rndy, plyr_rndz, 7.0, 7.0, 7.0, 0)) {
				cunty_hoarz();
			}
		}
		if (mm_cars_killed < 0) {
			mm_cars_killed = 0;
		}
		
		if (!IS_CAR_DEAD(mmplayer_car)) {
			mm_car_health = GET_ENGINE_HEALTH(mmplayer_car);
			mm_car_health -= 249;
			if (mm_car_health < 0) {
				mm_car_health = 0;
			}
			mm_car_health_divided = mm_car_health / 10;
			if (mm_car_health_divided < 0) {
				mm_car_health_divided = 0;
			}
			if (IS_CAR_UPSIDEDOWN(mmplayer_car)) {
				if (IS_CAR_STOPPED(mmplayer_car)) {
					GET_CAR_COORDINATES(mmplayer_car, &player_x, &player_y, &player_z);
					GET_CAR_HEADING(mmplayer_car, &mm_car_heading);
					SET_CAR_COORDINATES(mmplayer_car, player_x, player_y, player_z);
					SET_CAR_HEADING(mmplayer_car, mm_car_heading);
				}
			}
		}
		
		if (IS_PLAYER_DEAD(GetPlayerIndex())) {
			//DO_SCREEN_FADE_OUT(1000);
			//while (IS_SCREEN_FADING()) {
			//	WAIT(0);
			//}
			mission_failed_mm();
		}
		if (GET_ENGINE_HEALTH(mmplayer_car) < 1) {
			//DO_SCREEN_FADE_OUT(1000);
			//while (IS_SCREEN_FADING()) {
			//	WAIT(0);
			//}
			PRINT_NOW("BLOD_13", 5000, 1);
			mission_failed_mm();
		}
		
		if (TIMERB() > 5000) {
			if (letting_cars_do_stuff == 0) {
				if (!IS_CAR_DEAD(mm_car3)) {
					CAR_GOTO_COORDINATES_ACCURATE(mm_car3, mm_driver3, plyr_rndx, plyr_rndy, -105.0);
				}
				if (!IS_CAR_DEAD(mm_car10)) {
					CAR_GOTO_COORDINATES_ACCURATE(mm_car10, mm_driver10, plyr_rndx, plyr_rndy, -105.0);
				}
			}
			
			if (zero_where_player == 1) {
				if (!IS_CAR_DEAD(mm_car1)) {
					if (!IS_CAR_DEAD(mm_car3)) {
						CAR_GOTO_COORDINATES_ACCURATE(mm_car3, mm_driver3, plyr_rndx, plyr_rndy, -105.0);
					}
					if (!IS_CAR_DEAD(mm_car4)) {
						SET_CAR_RAM_CAR(mm_car4, mm_driver4, mm_driver1);
					}
				}
				zero_where_player = 5;
			}
			
			if (where_is_player == 0) {
				if (zero_where_player == 5) {
					if (!IS_CAR_DEAD(mm_car1)) {
						GENERATE_RANDOM_FLOAT_IN_RANGE(-1050.614, -904.614, &rnd_float1x);
						GENERATE_RANDOM_FLOAT_IN_RANGE(1860.186, 1788.186, &rnd_float1y);
						CAR_GOTO_COORDINATES_ACCURATE(mm_car1, mm_driver1, rnd_float1x, rnd_float1y, -100.0);
					}
				}
			}
			
			if (zero_where_player == 11) {
				if (!IS_CAR_DEAD(mm_car1)) {
					SET_CAR_RAM_CAR(mm_car1, mm_driver1, GetPlayerPed());
				}
				if (!IS_CAR_DEAD(mm_car4)) {
					SET_CAR_RAM_CAR(mm_car4, mm_driver4, GetPlayerPed());
				}
				zero_where_player = 6;
			}
			
			if (zero_where_player == 2) {
				if (!IS_CAR_DEAD(mm_car5)) {
					if (!IS_CAR_DEAD(mm_car7)) {
						SET_CAR_RAM_CAR(mm_car7, mm_driver7, mm_driver5);
					}
					if (!IS_CAR_DEAD(mm_car8)) {
						SET_CAR_RAM_CAR(mm_car7, mm_driver7, mm_driver5);
					}
				}
				zero_where_player = 5;
			}
			
			if (where_is_player == 0) {
				if (zero_where_player == 5) {
					if (!IS_CAR_DEAD(mm_car5)) {
						GENERATE_RANDOM_FLOAT_IN_RANGE(-1050.614, -904.614, &rnd_float2x);
						GENERATE_RANDOM_FLOAT_IN_RANGE(1860.186, 1788.186, &rnd_float2y);
						CAR_GOTO_COORDINATES_ACCURATE(mm_car5, mm_driver5, rnd_float2x, rnd_float2y, -100.0);
					}
				}
			}
			
			if (zero_where_player == 12) {
				if (!IS_CAR_DEAD(mm_car5)) {
					SET_CAR_RAM_CAR(mm_car5, mm_driver5, GetPlayerPed());
				}
				if (!IS_CAR_DEAD(mm_car7)) {
					SET_CAR_RAM_CAR(mm_car7, mm_driver7, GetPlayerPed());
				}
				if (!IS_CAR_DEAD(mm_car8)) {
					SET_CAR_RAM_CAR(mm_car8, mm_driver8, GetPlayerPed());
				}
				zero_where_player = 6;
			}
			
			if (zero_where_player == 3) {
				if (!IS_CAR_DEAD(mm_car9)) {
					if (!IS_CAR_DEAD(mm_car10)) {
						CAR_GOTO_COORDINATES_ACCURATE(mm_car10, mm_driver10, plyr_rndx, plyr_rndy, -100.0);
					}
					if (!IS_CAR_DEAD(mm_car11)) {
						SET_CAR_RAM_CAR(mm_car11, mm_driver11, mm_driver9);
					}
					if (!IS_CAR_DEAD(mm_car12)) {
						SET_CAR_RAM_CAR(mm_car12, mm_driver12, mm_driver9);
					}
				}
				zero_where_player = 5;
			}
			
			if (where_is_player == 0) {
				if (zero_where_player == 5) {
					if (!IS_CAR_DEAD(mm_car9)) {
						GENERATE_RANDOM_FLOAT_IN_RANGE(-1050.614, -904.614, &rnd_float3x);
						GENERATE_RANDOM_FLOAT_IN_RANGE(1860.186, 1788.186, &rnd_float3y);
						CAR_GOTO_COORDINATES_ACCURATE(mm_car9, mm_driver9, rnd_float3x, rnd_float3y, -100.0);
					}
				}
			}
			
			if (zero_where_player == 13) {
				if (!IS_CAR_DEAD(mm_car9)) {
					SET_CAR_RAM_CAR(mm_car9, mm_driver9, GetPlayerPed());
				}
				if (!IS_CAR_DEAD(mm_car11)) {
					SET_CAR_RAM_CAR(mm_car11, mm_driver11, GetPlayerPed());
				}
				if (!IS_CAR_DEAD(mm_car12)) {
					SET_CAR_RAM_CAR(mm_car12, mm_driver12, GetPlayerPed());
				}
				zero_where_player = 6;
			}
			
			if (zero_where_player == 4) {
				if (!IS_CAR_DEAD(mm_car13)) {
					if (!IS_CAR_DEAD(mm_car14)) {
						SET_CAR_RAM_CAR(mm_car14, mm_driver14, mm_driver13);
					}
					if (!IS_CAR_DEAD(mm_car15)) {
						SET_CAR_RAM_CAR(mm_car15, mm_driver15, mm_driver13);
					}
					if (!IS_CAR_DEAD(mm_car16)) {
						SET_CAR_RAM_CAR(mm_car16, mm_driver16, mm_driver13);
					}
				}
				zero_where_player = 5;
			}
			
			if (where_is_player == 0) {
				if (zero_where_player == 5) {
					if (!IS_CAR_DEAD(mm_car13)) {
						GENERATE_RANDOM_FLOAT_IN_RANGE(-1050.614, -904.614, &rnd_float4x);
						GENERATE_RANDOM_FLOAT_IN_RANGE(1860.186, 1788.186, &rnd_float4y);
						CAR_GOTO_COORDINATES_ACCURATE(mm_car13, mm_driver13, rnd_float4x, rnd_float4y, -100.0);
					}
				}
				where_is_player = 1;
			}
			
			if (zero_where_player == 14) {
				if (!IS_CAR_DEAD(mm_car13)) {
					SET_CAR_RAM_CAR(mm_car13, mm_driver13, GetPlayerPed());
				}
				if (!IS_CAR_DEAD(mm_car14)) {
					SET_CAR_RAM_CAR(mm_car14, mm_driver14, GetPlayerPed());
				}
				if (!IS_CAR_DEAD(mm_car15)) {
					SET_CAR_RAM_CAR(mm_car15, mm_driver15, GetPlayerPed());
				}
				if (!IS_CAR_DEAD(mm_car16)) {
					SET_CAR_RAM_CAR(mm_car16, mm_driver16, GetPlayerPed());
				}
				zero_where_player = 6;
			}
			
			if (!IS_CAR_DEAD(mm_car1)) {
				if (IS_CAR_UPSIDEDOWN(mm_car1)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car1, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car1, GET_ENGINE_HEALTH(mm_car1) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car1)) {
					START_CAR_FIRE(mm_car1);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car1)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car2)) {
				if (IS_CAR_UPSIDEDOWN(mm_car2)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car2, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car2, GET_ENGINE_HEALTH(mm_car2) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car2)) {
					START_CAR_FIRE(mm_car2);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car2)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car3)) {
				if (IS_CAR_UPSIDEDOWN(mm_car3)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car3, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car3, GET_ENGINE_HEALTH(mm_car3) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car3)) {
					START_CAR_FIRE(mm_car3);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car3)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car4)) {
				if (IS_CAR_UPSIDEDOWN(mm_car4)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car4, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car4, GET_ENGINE_HEALTH(mm_car4) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car4)) {
					START_CAR_FIRE(mm_car4);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car4)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car5)) {
				if (IS_CAR_UPSIDEDOWN(mm_car5)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car5, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car5, GET_ENGINE_HEALTH(mm_car5) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car5)) {
					START_CAR_FIRE(mm_car5);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car5)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car6)) {
				if (IS_CAR_UPSIDEDOWN(mm_car6)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car6, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car6, GET_ENGINE_HEALTH(mm_car6) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car6)) {
					START_CAR_FIRE(mm_car6);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car6)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car7)) {
				if (IS_CAR_UPSIDEDOWN(mm_car7)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car7, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car7, GET_ENGINE_HEALTH(mm_car7) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car7)) {
					START_CAR_FIRE(mm_car7);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car7)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car8)) {
				if (IS_CAR_UPSIDEDOWN(mm_car8)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car8, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car8, GET_ENGINE_HEALTH(mm_car8) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car8)) {
					START_CAR_FIRE(mm_car8);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car8)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car9)) {
				if (IS_CAR_UPSIDEDOWN(mm_car9)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car9, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car9, GET_ENGINE_HEALTH(mm_car9) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car9)) {
					START_CAR_FIRE(mm_car9);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car9)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car10)) {
				if (IS_CAR_UPSIDEDOWN(mm_car10)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car10, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car10, GET_ENGINE_HEALTH(mm_car10) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car10)) {
					START_CAR_FIRE(mm_car10);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car10)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car11)) {
				if (IS_CAR_UPSIDEDOWN(mm_car11)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car11, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car11, GET_ENGINE_HEALTH(mm_car11) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car11)) {
					START_CAR_FIRE(mm_car11);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car11)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car12)) {
				if (IS_CAR_UPSIDEDOWN(mm_car12)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car12, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car12, GET_ENGINE_HEALTH(mm_car12) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car12)) {
					START_CAR_FIRE(mm_car12);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car12)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car13)) {
				if (IS_CAR_UPSIDEDOWN(mm_car13)) {	
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car13, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car13, GET_ENGINE_HEALTH(mm_car13) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car13)) {
					START_CAR_FIRE(mm_car13);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car13)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car14)) {
				if (IS_CAR_UPSIDEDOWN(mm_car14)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car14, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car14, GET_ENGINE_HEALTH(mm_car14) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car14)) {
					START_CAR_FIRE(mm_car14);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car14)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car15)) {
				if (IS_CAR_UPSIDEDOWN(mm_car15)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car15, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car15, GET_ENGINE_HEALTH(mm_car15) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car15)) {
					START_CAR_FIRE(mm_car15);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car15)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (!IS_CAR_DEAD(mm_car16)) {
				if (IS_CAR_UPSIDEDOWN(mm_car16)) {
					if (!LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), mm_car16, 7.0, 7.0, 0)) {
						SET_ENGINE_HEALTH(mm_car16, GET_ENGINE_HEALTH(mm_car16) - 1);
					}
				}
				if (IS_CAR_STUCK(mm_car16)) {
					START_CAR_FIRE(mm_car16);
				}
				if (IS_CAR_TOUCHING_CAR(mmplayer_car, mm_car16)) {
					int hp, curhp;
					GENERATE_RANDOM_INT_IN_RANGE(2, 5, &hp);
					curhp = GET_ENGINE_HEALTH(mmplayer_car);
					SET_ENGINE_HEALTH(mmplayer_car, curhp - hp);
				}
			}
			
			if (TIMERA() > 1500) {
				where_is_player = 0;
				SETTIMERA(0);
				if (mm_sound_playing == 0) {
					mm_sound_playing = 1;
				}
			}
			
			if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1788.186, 0)) {
				if (zero1 == 0) {
					zero_where_player = 11;
					zero1 = 1;
				}
			} else {
				if (zero1 == 1) {
					zero_where_player = 1;
					zero1 = 0;
				}
			}
			if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1050.614, 1860.186, -904.614, 1941.186, 0)) {
				if (zero2 == 0) {
					zero_where_player = 12;
					zero2 = 1;
				}
			} else {
				if (zero2 == 1) {
					zero_where_player = 2;
					zero2 = 0;
				}
			}
			if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -785.614, 1860.186, -904.614, 1788.186, 0)) {
				if (zero3 == 0) {
					zero_where_player = 13;
					zero3 = 1;
				}
			} else {
				if (zero3 == 1) {
					zero_where_player = 3;
					zero3 = 0;
				}
			}
			if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -785.614, 1860.186, -904.614, 1941.186, 0)) {
				if (zero4 == 0) {
					zero_where_player = 14;
					zero4 = 1;
				}
			} else {
				if (zero4 == 1) {
					zero_where_player = 4;
					zero4 = 0;
				}
			}
		}
		
		if (IS_CAR_DEAD(mm_car1)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car2)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car3)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car4)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car5)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car6)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car7)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car8)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car9)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car10)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car11)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car12)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car13)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car14)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car15)) {
			cars_created--;
			mm_cars_killed++;
		}
		if (IS_CAR_DEAD(mm_car16)) {
			cars_created--;
			mm_cars_killed++;
		}
		
		if (cars_created < 16) {
			create_cars_mm();
		}
	}
	
	SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
	//DO_SCREEN_FADE_OUT(1000);
	//while (IS_SCREEN_FADING()) {
	//	WAIT(0);
	//}
	PRINT_NOW("BLOD_11", 5000, 1);
	mission_failed_mm();
}

void mission_start_mm(void) {
	if (G_BLOODRING == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}
	GET_CURRENT_WEATHER(&weather);
	FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
	FORWARD_TO_TIME_OF_DAY(20, 30);//устанавливаем время
	checkpoint1 = CREATE_CHECKPOINT( 8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.20000000 );

	REQUEST_IPL("blodring");
	DISABLE_FRONTEND_RADIO();
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
	SET_FREE_HEALTH_CARE(GetPlayerIndex(), 1);
	WAIT(0);
	LOAD_ADDITIONAL_TEXT("BLDRING", 6);
	
	random_garage = 0;
	cars_created = 16;
	mm_cars_killed = 0;
	if (mm_attempt == 0) {
		mm_best_time = 1;
		mm_longest_time = 60;
		time_to_beat = 60000;
	}
	mm_countdown = 30000;
	mm_car_health = 0;
	mm_car_health_divided = 0;
	where_is_player = 0;
	zero_where_player = 0;
	zero1 = 0;
	zero2 = 0;
	zero3 = 0;
	zero4 = 0;
	letting_cars_do_stuff = 0;
	bonus_on = 0;
	bonus_time = 0;
	set_go = 0;
	
	mm_audio_flag = 0;
	mm_sound1 = 0;
	mm_sound_playing = 0;
	mm_cuntie = 0;
	mm_adding_health = 0;
	
	random_car_node_x = 0.0;
	random_car_node_y = 0.0;
	random_car_node_z = 0.0;
	mm_car_heading = 0.0;
	player_x = 0.0;
	player_y = 0.0;
	player_z = 0.0;

	plyr_rndx = 0.0;
	plyr_rndy = 0.0;
	plyr_rndz = 0.0;
	
	REQUEST_MODEL(PedM1);
	REQUEST_MODEL(CarM1);
	REQUEST_MODEL(CarM2);
	while ((!HAS_MODEL_LOADED(PedM1)) || (!HAS_MODEL_LOADED(CarM1)) || (!HAS_MODEL_LOADED(CarM2))) {
		WAIT(0);
	}
	OVERRIDE_NEXT_RESTART(-671.4, 1864.2, 14.0, 271.2);
	SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
	SET_EVERYONE_IGNORE_PLAYER(GetPlayerIndex(), 1);
	CLEAR_WANTED_LEVEL(GetPlayerIndex());
	LOAD_SCENE(-899.914, 1865.186, 10.811);
	if (IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
		WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), -801.574, 1860.046, 21.111);
	} else {
		SET_CHAR_COORDINATES(GetPlayerPed(), -801.574, 1860.046, 21.111);
	}
	CREATE_CAR(CarM2, -801.574, 1860.046, 22.111, &mmplayer_car, 1);
	LOCK_CAR_DOORS(mmplayer_car, 4);
	WARP_CHAR_INTO_CAR(GetPlayerPed(), mmplayer_car);
	SET_CAR_STRONG(mmplayer_car, 1);
	SET_CAR_HEADING(mmplayer_car, 90.0);
	SET_CHAR_HEADING(GetPlayerPed(), 80.0);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mmplayer_car, 1);
	SET_ENGINE_HEALTH(mmplayer_car, 1249);
	SET_CAR_ENGINE_ON(mmplayer_car, 1, 1);
	
	random_car_node_x = -806.384;
	random_car_node_y = 1879.726;
	random_car_node_z = 23.311;
	mm_car_heading = 104.4;
	CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car1, 1);
	SET_CAR_HEADING(mm_car1, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car1, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car1, 5, PedM1, &mm_driver1);
	ADD_STUCK_CAR_CHECK(mm_car1, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car1, 1);
	SET_CAR_ENGINE_ON(mm_car1, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car1);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver1, 0);
	
	random_car_node_x = -820.114;
	random_car_node_y = 1895.926;
	random_car_node_z = 23.311;
	mm_car_heading = 132.6;
	CREATE_CAR(CarM2, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car2, 1);
	SET_CAR_HEADING(mm_car2, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car2, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car2, 5, PedM1, &mm_driver2);
	ADD_STUCK_CAR_CHECK(mm_car2, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car2, 1);
	SET_CAR_ENGINE_ON(mm_car2, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car2);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver2, 0);
	
	random_car_node_x = -839.914;
	random_car_node_y = 1908.006;
	random_car_node_z = 23.311;
	mm_car_heading = 135.4;
	CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car3, 1);
	SET_CAR_HEADING(mm_car3, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car3, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car3, 5, PedM1, &mm_driver3);
	ADD_STUCK_CAR_CHECK(mm_car3, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car3, 1);
	SET_CAR_ENGINE_ON(mm_car3, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car3);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver3, 0);
	
	random_car_node_x = -869.944;
	random_car_node_y = 1919.656;
	random_car_node_z = 23.311;
	mm_car_heading = 155.4;
	CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car4, 1);
	SET_CAR_HEADING(mm_car4, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car4, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car4, 5, PedM1, &mm_driver4);
	ADD_STUCK_CAR_CHECK(mm_car4, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car4, 1);
	SET_CAR_ENGINE_ON(mm_car4, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car4);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver4, 0);
	
	random_car_node_x = -904.944;
	random_car_node_y = 1923.736;
	random_car_node_z = 23.311;
	mm_car_heading = 173.2; 
	CREATE_CAR(CarM2, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car5, 1);
	SET_CAR_HEADING(mm_car5, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car5, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car5, 5, PedM1, &mm_driver5);
	ADD_STUCK_CAR_CHECK(mm_car5, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car5, 1);
	SET_CAR_ENGINE_ON(mm_car5, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car5);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver5, 0);
	
	random_car_node_x = -814.384;
	random_car_node_y = 1824.146;
	random_car_node_z = 23.311;
	mm_car_heading = 60.5;
	CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car6, 1);
	SET_CAR_HEADING(mm_car6, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car6, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car6, 5, PedM1, &mm_driver6);
	ADD_STUCK_CAR_CHECK(mm_car6, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car6, 1);
	SET_CAR_ENGINE_ON(mm_car6, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car6);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver6, 0);
	
	random_car_node_x = -939.384;
	random_car_node_y = 1922.726;
	random_car_node_z = 23.311;
	mm_car_heading = 180.4; 
	CREATE_CAR(CarM2, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car7, 1);
	SET_CAR_HEADING(mm_car7, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car7, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car7, 5, PedM1, &mm_driver7);
	ADD_STUCK_CAR_CHECK(mm_car7, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car7, 1);
	SET_CAR_ENGINE_ON(mm_car7, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car7);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver7, 0);
	
	random_car_node_x = -980.914;
	random_car_node_y = 1915.486;
	random_car_node_z = 23.311;
	mm_car_heading = 242.9; 
	CREATE_CAR(CarM2, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car8, 1);
	SET_CAR_HEADING(mm_car8, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car8, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car8, 5, PedM1, &mm_driver8);
	ADD_STUCK_CAR_CHECK(mm_car8, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car8, 1);
	SET_CAR_ENGINE_ON(mm_car8, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car8);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver8, 0);
	
	random_car_node_x = -1020.384;
	random_car_node_y = 1894.726;
	random_car_node_z = 23.311;
	mm_car_heading = 242.4; 
	CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car9, 1);
	SET_CAR_HEADING(mm_car9, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car9, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car9, 5, PedM1, &mm_driver9);
	ADD_STUCK_CAR_CHECK(mm_car9, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car9, 1);
	SET_CAR_ENGINE_ON(mm_car9, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car9);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver9, 0);
	
	random_car_node_x = -1034.384;
	random_car_node_y = 1851.726;
	random_car_node_z = 23.311;
	mm_car_heading = 271.4;
	CREATE_CAR(CarM2, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car10, 1);
	SET_CAR_HEADING(mm_car10, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car10, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car10, 5, PedM1, &mm_driver10);
	ADD_STUCK_CAR_CHECK(mm_car10, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car10, 1);
	SET_CAR_ENGINE_ON(mm_car10, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car10);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver10, 0);
	
	random_car_node_x = -1017.384;
	random_car_node_y = 1824.726;
	random_car_node_z = 23.311;
	mm_car_heading = 293.4;
	CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car11, 1);
	SET_CAR_HEADING(mm_car11, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car11, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car11, 5, PedM1, &mm_driver11);
	ADD_STUCK_CAR_CHECK(mm_car11, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car11, 1);
	SET_CAR_ENGINE_ON(mm_car11, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car11);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver11, 0);
	
	random_car_node_x = -981.919;
	random_car_node_y = 1807.04;
	random_car_node_z = 21.5208;
	mm_car_heading = 345.6; 
	CREATE_CAR(CarM2, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car12, 1);
	SET_CAR_HEADING(mm_car12, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car12, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car12, 5, PedM1, &mm_driver12);
	ADD_STUCK_CAR_CHECK(mm_car12, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car12, 1);
	SET_CAR_ENGINE_ON(mm_car12, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car12);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver12, 0);
	
	random_car_node_x = -944.308;
	random_car_node_y = 1800.45;
	random_car_node_z = 21.2782;
	mm_car_heading = 0.0;
	CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car13, 1);
	SET_CAR_HEADING(mm_car13, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car13, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car13, 5, PedM1, &mm_driver13);
	ADD_STUCK_CAR_CHECK(mm_car13, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car13, 1);
	SET_CAR_ENGINE_ON(mm_car13, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car13);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver13, 0);
	
	random_car_node_x = -884.384;
	random_car_node_y = 1797.626;
	random_car_node_z = 21.7666;
	mm_car_heading = 17.85; 
	CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car14, 1);
	SET_CAR_HEADING(mm_car14, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car14, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car14, 5, PedM1, &mm_driver14);
	ADD_STUCK_CAR_CHECK(mm_car14, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car14, 1);
	SET_CAR_ENGINE_ON(mm_car14, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car14);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver14, 0);
	
	random_car_node_x = -853.384;
	random_car_node_y = 1805.486;
	random_car_node_z = 23.311;
	mm_car_heading = 39.98; 
	CREATE_CAR(CarM2, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car15, 1);
	SET_CAR_HEADING(mm_car15, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car15, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car15, 5, PedM1, &mm_driver15);
	ADD_STUCK_CAR_CHECK(mm_car15, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car15, 1);
	SET_CAR_ENGINE_ON(mm_car15, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car15);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver15, 0);
	
	random_car_node_x = -963.059;
	random_car_node_y = 1802.92;
	random_car_node_z = 21.4085;
	mm_car_heading = 351.4;
	CREATE_CAR(CarM1, random_car_node_x, random_car_node_y, random_car_node_z, &mm_car16, 1);
	SET_CAR_HEADING(mm_car16, mm_car_heading);
	SET_CAR_DISTANCE_AHEAD_MULTIPLIER(mm_car16, 255.0);
	CREATE_CHAR_INSIDE_CAR(mm_car16, 5, PedM1, &mm_driver16);
	ADD_STUCK_CAR_CHECK(mm_car16, 1.5, 4000);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(mm_car16, 1);
	SET_CAR_ENGINE_ON(mm_car16, 1, 1);
	ADD_UPSIDEDOWN_CAR_CHECK(mm_car16);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(mm_driver16, 0);
	
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver1, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver2, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver3, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver4, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver5, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver6, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver7, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver8, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver9, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver10, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver11, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver12, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver13, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver14, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver15, 0.0);
	SET_DRIVE_TASK_CRUISE_SPEED(mm_driver16, 0.0);
	
	SET_INSTANT_WIDESCREEN_BORDERS(1);
	CREATE_CAM(14, &cam);
	SET_CAM_POS(cam, -787.114, 1907.986, 37.611);
	POINT_CAM_AT_COORD(cam, -860.514, 1874.986, 11.311);
	SET_CAM_ACTIVE(cam, 1);
	SET_CAM_PROPAGATE(cam, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	WAIT(500);
	DO_SCREEN_FADE_IN(1500);
	while (IS_SCREEN_FADING()) {
		WAIT(0);
	}
	if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
		SET_EVERYONE_IGNORE_PLAYER(GetPlayerIndex(), 0);
	}
	SETTIMERA(0);
	PRINT_NOW("BLOD_01", 5000, 1);
	while (TIMERA() < 5000) {
		WAIT(0);
		if (check_skip_intro()) {		/*rebusx*/
			if (button_pressed == 1) {
				button_pressed = 0;
				skip_mm_initial_cutscene();
			}
		} else {
			if (button_pressed == 0) {
				button_pressed = 1;
			}
		}
	}
	SETTIMERA(0);
	SET_CAM_POS(cam, -989.314, 1813.986, 22.211);
	POINT_CAM_AT_COORD(cam, -980.114, 1807.386, 20.911);
	PRINT_NOW("BLOD_02", 5000, 1);
	while (TIMERA() < 5000) {
		WAIT(0);
		if (IS_GAME_KEYBOARD_KEY_PRESSED(57)) {
			if (button_pressed == 1) {
				button_pressed = 0;
				skip_mm_initial_cutscene();
			}
		} else {
			if (button_pressed == 0) {
				button_pressed = 1;
			}
		}
	}
	SETTIMERA(0);
	SET_CAM_POS(cam, -783.314, 1862.386, 26.111);
	POINT_CAM_AT_COORD(cam, -798.214, 1861.186, 22.911);
	PRINT_NOW("BLOD_03", 5000, 1);
	while (TIMERA() < 5000) {
		WAIT(0);
		if (IS_GAME_KEYBOARD_KEY_PRESSED(57)) {
			if (button_pressed == 1) {
				button_pressed = 0;
				skip_mm_initial_cutscene();
			}
		} else {
			if (button_pressed == 0) {
				button_pressed = 1;
			}
		}
	}
	SETTIMERA(0);
	skip_mm_initial_cutscene();
}

void main(void) {
	mission_start_mm();
	if (HAS_DEATHARREST_EXECUTED()) {
		mission_failed_mm();
	}
	mission_cleanup_mm();
}