#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
#include "mission_passed.h"
// в оригинале эти переменные являются глобалками
int flag_4x4_mission1_passed, flag_4x4one_trigger, flag_intro1_before, flag_launch_4x4_1_ok, record_4x4_one;

int pcj_seconds, pcj_minutes, pcj_reward, checkpoint_time_limit;
int flag_intro, flag_intro_jump, intro_time_lapsed;
int flag_timer, timer_4x4, counter_4x4_pickups;
int flag_truck_1, flag_truck_2, truck_1, truck_2, truck_driver1, truck_driver2;
int player_4x4, wanted_4x4, timer_4x4_secs;
int timer_intro_start, timer_intro_now;
int cam, textur, fon;
int print_text = 1;
int cp1, cp2, cp3, cp4, cp5;
int cp6, cp7, cp8, cp9, cp10;
int cp11, cp12, cp13, cp14, cp15;
int cp16, cp17, cp18, cp19, cp20;
int cp21, cp22, cp23, cp24;

int blip_1, blip_2, blip_3;
int blip_4, blip_5, blip_6;
int blip_7, blip_8, blip_9;
int blip_10, blip_11, blip_12;
int blip_13, blip_14, blip_15;
int blip_16, blip_17, blip_18;
int blip_19, blip_20, blip_21;
int blip_22, blip_23, blip_24;

int flag_blip_1, flag_blip_2, flag_blip_3, flag_blip_4; 
int flag_blip_5, flag_blip_6, flag_blip_7, flag_blip_8; 
int flag_blip_9, flag_blip_10, flag_blip_11, flag_blip_12;
int flag_blip_13, flag_blip_14, flag_blip_15, flag_blip_16;
int flag_blip_17, flag_blip_18, flag_blip_19, flag_blip_20;
int flag_blip_21, flag_blip_22, flag_blip_23, flag_blip_24;

float cam_4x4_X, cam_4x4_y, cam_4x4_z; 
float player_x, player_y, player_z; 

float x_1, y_1, z_1;
float x_2, y_2, z_2;
float x_3, y_3, z_3;
float x_4, y_4, z_4;
float x_5, y_5, z_5;
float x_6, y_6, z_6;
float x_7, y_7, z_7;
float x_8, y_8, z_8;
float x_9, y_9, z_9;
float x_10, y_10, z_10;
float x_11, y_11, z_11;
float x_12, y_12, z_12;
float x_13, y_13, z_13;
float x_14, y_14, z_14;
float x_15, y_15, z_15;
float x_16, y_16, z_16;
float x_17, y_17, z_17;
float x_18, y_18, z_18;
float x_19, y_19, z_19;
float x_20, y_20, z_20;
float x_21, y_21, z_21;
float x_22, y_22, z_22;
float x_23, y_23, z_23;
float x_24, y_24, z_24;

void main(void);

void setup_draw_text(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.156, 0.267);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
	return;
}

void setup_draw_value(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.26, 0.445);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
	return;
}

void mission_cleanup_4x4one(void) {
	SET_INSTANT_WIDESCREEN_BORDERS(0);
	SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	SET_EVERYONE_IGNORE_PLAYER(GetPlayerIndex(), 0);
	REMOVE_BLIP(blip_1);
	REMOVE_BLIP(blip_2);
	REMOVE_BLIP(blip_3);
	REMOVE_BLIP(blip_4);
	REMOVE_BLIP(blip_5);
	REMOVE_BLIP(blip_6);
	REMOVE_BLIP(blip_7);
	REMOVE_BLIP(blip_8);
	REMOVE_BLIP(blip_9);
	REMOVE_BLIP(blip_10);
	REMOVE_BLIP(blip_11);
	REMOVE_BLIP(blip_12);
	REMOVE_BLIP(blip_13);
	REMOVE_BLIP(blip_14);
	REMOVE_BLIP(blip_15);
	REMOVE_BLIP(blip_16);
	REMOVE_BLIP(blip_17);
	REMOVE_BLIP(blip_18);
	REMOVE_BLIP(blip_19);
	REMOVE_BLIP(blip_20);
	REMOVE_BLIP(blip_21);
	REMOVE_BLIP(blip_22);
	REMOVE_BLIP(blip_23);
	REMOVE_BLIP(blip_24);
	DELETE_CHECKPOINT(cp1);
	DELETE_CHECKPOINT(cp2);
	DELETE_CHECKPOINT(cp3);
	DELETE_CHECKPOINT(cp4);
	DELETE_CHECKPOINT(cp5);
	DELETE_CHECKPOINT(cp6);
	DELETE_CHECKPOINT(cp7);
	DELETE_CHECKPOINT(cp8);
	DELETE_CHECKPOINT(cp9);
	DELETE_CHECKPOINT(cp10);
	DELETE_CHECKPOINT(cp11);
	DELETE_CHECKPOINT(cp12);
	DELETE_CHECKPOINT(cp13);
	DELETE_CHECKPOINT(cp14);
	DELETE_CHECKPOINT(cp15);
	DELETE_CHECKPOINT(cp16);
	DELETE_CHECKPOINT(cp17);
	DELETE_CHECKPOINT(cp18);
	DELETE_CHECKPOINT(cp19);
	DELETE_CHECKPOINT(cp20);
	DELETE_CHECKPOINT(cp21);
	DELETE_CHECKPOINT(cp22);
	DELETE_CHECKPOINT(cp23);
	DELETE_CHECKPOINT(cp24);	
	//G_ONMISSION = 0;
	flag_launch_4x4_1_ok = 0;
	//main();
	TERMINATE_THIS_SCRIPT();
}

void time_calc(void) {
	pcj_seconds = record_4x4_one;
	pcj_minutes = 0;
	while (pcj_seconds > 59) {
		pcj_seconds = pcj_seconds - 60;
		pcj_minutes++;
	}
	PRINT_WITH_2_NUMBERS_NOW("NEW_REC", pcj_minutes, pcj_seconds, 5000, 1);
	pcj_reward = 1000;
	return;
}

void mission_4x4one_failed(void) {
	if (G_PCJ == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
	}
	//PRINT_BIG("M_FAIL", 2000, 1);
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT(0.5, 0.45, "M_FAIL");// пишем "Миссия завершина"

		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	mission_cleanup_4x4one();
}

void mission_4x4one_passed(void) {
	timer_4x4 = timer_4x4 * -1;
	timer_4x4 = timer_4x4 + 130000;
	timer_4x4 = timer_4x4 / 1000;
	
	if (flag_4x4_mission1_passed == 0) {
		record_4x4_one = timer_4x4;
		time_calc();
	}
	
	if (flag_4x4_mission1_passed == 1) {
		if (timer_4x4 < record_4x4_one) {
			record_4x4_one = timer_4x4;
			time_calc();
		} else {
			pcj_reward = 100;
		}
	}
	
	//PRINT_WITH_NUMBER_BIG("M_PASS", pcj_reward, 5000, 1);
	CLEAR_WANTED_LEVEL(GetPlayerIndex());
	ADD_SCORE(GetPlayerIndex(), pcj_reward);
	INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, pcj_reward);
	if (flag_4x4_mission1_passed == 0) {
		flag_4x4_mission1_passed = 1;
	}

	if (G_PCJ == 0)
	{
		G_PCJ = 1;
		INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
		G_GAME_PROGRESS += 1;
		SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
	}

	play_mission_complete_tune();
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "M_PASS", pcj_reward);//
		
		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	mission_cleanup_4x4one();
}

void mission_start_4x4one(void) {
	//G_ONMISSION = 1;
	DO_SCREEN_FADE_OUT(1000);
	if (G_PCJ == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}
	while (IS_SCREEN_FADING()) {
		WAIT(0);
	}
	LOAD_ADDITIONAL_TEXT("MIAMI_1", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	//PRINT_BIG("T4X4_1", 5000, 2);
	WAIT(0);
	counter_4x4_pickups = 0;
	timer_4x4 = 130000;
	flag_intro = 0;
	flag_timer = 0;
	flag_4x4one_trigger = 1;
	flag_intro_jump = 0;
	intro_time_lapsed = 0;
	
	checkpoint_time_limit = 130;
	pcj_reward = 100;
	pcj_minutes = 0;

	flag_truck_1 = 0;
	flag_truck_2 = 0;

	flag_blip_1 = 0;
	flag_blip_2 = 0;
	flag_blip_3 = 0;
	flag_blip_4 = 0;
	flag_blip_5 = 0;
	flag_blip_6 = 0;
	flag_blip_7 = 0;
	flag_blip_8 = 0;
	flag_blip_9 = 0;
	flag_blip_10 = 0;
	flag_blip_11 = 0;
	flag_blip_12 = 0;
	flag_blip_13 = 0;
	flag_blip_14 = 0;
	flag_blip_15 = 0;
	flag_blip_16 = 0;
	flag_blip_17 = 0;
	flag_blip_18 = 0;
	flag_blip_19 = 0;
	flag_blip_20 = 0;
	flag_blip_21 = 0;
	flag_blip_22 = 0;
	flag_blip_23 = 0;
	flag_blip_24 = 0;
	
	cam_4x4_X = 883.0;
	cam_4x4_y = 144.0;
	cam_4x4_z = 21.5;
	
	x_1 = 893.0;    
	y_1 = 133.4;
	z_1 = 13.0;

	x_2 = 893.0;    
	y_2 = 92.5;
	z_2 = 12.5;

	x_3 = 886.0;   
	y_3 = 16.83; 
	z_3 = 16.0;

	x_4 = 862.5;   
	y_4 = -47.6; 
	z_4 = 6.0;

	x_5 = 825.0;   
	y_5 = -128.3;
	z_5 = 6.5;

	x_6 = 799.5; 
	y_6 = -186.2; 
	z_6 = 18.3;

	x_7 = 782.5;   
	y_7 = -229.2; 
	z_7 = 19.0;

	x_8 = 775.26;   
	y_8 = -269.3; 
	z_8 = 6.5; 

	x_9 = 749.0;   
	y_9 = -325.0; 
	z_9 = 6.5;

	x_10 = 718.0;   
	y_10 = -357.0; 
	z_10 = 6.5;

	x_11 = 689.7;   
	y_11 = -422.0;
	z_11 = 12.0;

	x_12 = 675.5; 
	y_12 = -578.8; 
	z_12 = 6.5;

	x_13 = 661.6;    
	y_13 = -614.9;
	z_13 = 6.5;

	x_14 = 626.5;      
	y_14 = -770.3;
	z_14 = 6.2;

	x_15 = 634.44;  
	y_15 = -785.7;
	z_15 = 6.2;

	x_16 = 621.6;    
	y_16 = -824.5;
	z_16 = 6.2;

	x_17 = 600.2;   
	y_17 = -836.2;
	z_17 = 6.2;

	x_18 = 562.6;   
	y_18 = -804.8; 
	z_18 = 4.5;

	x_19 = 537.45;    
	y_19 = -786.7;
	z_19 = 0.5;

	x_20 = 511.7; 
	y_20 = -767.0;
	z_20 = 8.5;

	x_21 = 503.1;  
	y_21 = -687.4;
	z_21 = 6.0;

	x_22 = 445.5;  
	y_22 = -659.0;
	z_22 = 6.4;

	x_23 = 437.96; 
	y_23 = -720.5;
	z_23 = 16.6;

	x_24 = 452.8;  
	y_24 = -775.9;
	z_24 = 12.3;
	
	STORE_WANTED_LEVEL(GetPlayerIndex(), &wanted_4x4);
	CLEAR_WANTED_LEVEL(GetPlayerIndex());
	SET_EVERYONE_IGNORE_PLAYER(GetPlayerIndex(), 1);
	STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &player_4x4);
	if (!IS_CAR_DEAD(player_4x4)) {
		LOCK_CAR_DOORS(player_4x4, 1);
	}
	SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
	SET_INSTANT_WIDESCREEN_BORDERS(1);
	
	ADD_BLIP_FOR_COORD(x_1, y_1, z_1, &blip_1);
	ADD_BLIP_FOR_COORD(x_2, y_2, z_2, &blip_2);
	ADD_BLIP_FOR_COORD(x_3, y_3, z_3, &blip_3);
	ADD_BLIP_FOR_COORD(x_4, y_4, z_4, &blip_4);
	ADD_BLIP_FOR_COORD(x_5, y_5, z_5, &blip_5);
	ADD_BLIP_FOR_COORD(x_6, y_6, z_6, &blip_6);
	ADD_BLIP_FOR_COORD(x_7, y_7, z_7, &blip_7);
	ADD_BLIP_FOR_COORD(x_8, y_8, z_8, &blip_8);
	ADD_BLIP_FOR_COORD(x_9, y_9, z_9, &blip_9);
	ADD_BLIP_FOR_COORD(x_10, y_10, z_10, &blip_10);
	ADD_BLIP_FOR_COORD(x_11, y_11, z_11, &blip_11);
	ADD_BLIP_FOR_COORD(x_12, y_12, z_12, &blip_12);
	ADD_BLIP_FOR_COORD(x_13, y_13, z_13, &blip_13);
	ADD_BLIP_FOR_COORD(x_14, y_14, z_14, &blip_14);
	ADD_BLIP_FOR_COORD(x_15, y_15, z_15, &blip_15);
	ADD_BLIP_FOR_COORD(x_16, y_16, z_16, &blip_16);
	ADD_BLIP_FOR_COORD(x_17, y_17, z_17, &blip_17);
	ADD_BLIP_FOR_COORD(x_18, y_18, z_18, &blip_18);
	ADD_BLIP_FOR_COORD(x_19, y_19, z_19, &blip_19);
	ADD_BLIP_FOR_COORD(x_20, y_20, z_20, &blip_20);
	ADD_BLIP_FOR_COORD(x_21, y_21, z_21, &blip_21);
	ADD_BLIP_FOR_COORD(x_22, y_22, z_22, &blip_22);
	ADD_BLIP_FOR_COORD(x_23, y_23, z_23, &blip_23);
	ADD_BLIP_FOR_COORD(x_24, y_24, z_24, &blip_24);

	CHANGE_BLIP_COLOUR(blip_1, 5);
	CHANGE_BLIP_COLOUR(blip_2, 5);
	CHANGE_BLIP_COLOUR(blip_3, 5);
	CHANGE_BLIP_COLOUR(blip_4, 5);
	CHANGE_BLIP_COLOUR(blip_5, 5);
	CHANGE_BLIP_COLOUR(blip_6, 5);
	CHANGE_BLIP_COLOUR(blip_7, 5);
	CHANGE_BLIP_COLOUR(blip_8, 5);
	CHANGE_BLIP_COLOUR(blip_9, 5);
	CHANGE_BLIP_COLOUR(blip_10, 5);
	CHANGE_BLIP_COLOUR(blip_11, 5);
	CHANGE_BLIP_COLOUR(blip_12, 5);
	CHANGE_BLIP_COLOUR(blip_13, 5);
	CHANGE_BLIP_COLOUR(blip_14, 5);
	CHANGE_BLIP_COLOUR(blip_15, 5);
	CHANGE_BLIP_COLOUR(blip_16, 5);
	CHANGE_BLIP_COLOUR(blip_17, 5);
	CHANGE_BLIP_COLOUR(blip_18, 5);
	CHANGE_BLIP_COLOUR(blip_19, 5);
	CHANGE_BLIP_COLOUR(blip_20, 5);
	CHANGE_BLIP_COLOUR(blip_21, 5);
	CHANGE_BLIP_COLOUR(blip_22, 5);
	CHANGE_BLIP_COLOUR(blip_23, 5);
	CHANGE_BLIP_COLOUR(blip_24, 5);

	cp1 = CREATE_CHECKPOINT(8, x_1, y_1, z_1, x_1, y_1, z_1, 0.2);
	cp2 = CREATE_CHECKPOINT(8, x_2, y_2, z_2, x_2, y_2, z_2, 0.2);
	cp3 = CREATE_CHECKPOINT(8, x_3, y_3, z_3, x_3, y_3, z_3, 0.2);
	cp4 = CREATE_CHECKPOINT(8, x_4, y_4, z_4, x_4, y_4, z_4, 0.2);
	cp5 = CREATE_CHECKPOINT(8, x_5, y_5, z_5, x_5, y_5, z_5, 0.2);
	cp6 = CREATE_CHECKPOINT(8, x_6, y_6, z_6, x_6, y_6, z_6, 0.2);
	cp7 = CREATE_CHECKPOINT(8, x_7, y_7, z_7, x_7, y_7, z_7, 0.2);
	cp8 = CREATE_CHECKPOINT(8, x_8, y_8, z_8, x_8, y_8, z_8, 0.2);
	cp9 = CREATE_CHECKPOINT(8, x_9, y_9, z_9, x_9, y_9, z_9, 0.2);
	cp10 = CREATE_CHECKPOINT(8, x_10, y_10, z_10, x_10, y_10, z_10, 0.2);
	cp11 = CREATE_CHECKPOINT(8, x_11, y_11, z_11, x_11, y_11, z_11, 0.2);
	cp12 = CREATE_CHECKPOINT(8, x_12, y_12, z_12, x_12, y_12, z_12, 0.2);
	cp13 = CREATE_CHECKPOINT(8, x_13, y_13, z_13, x_13, y_13, z_13, 0.2);
	cp14 = CREATE_CHECKPOINT(8, x_14, y_14, z_14, x_14, y_14, z_14, 0.2);
	cp15 = CREATE_CHECKPOINT(8, x_15, y_15, z_15, x_15, y_15, z_15, 0.2);
	cp16 = CREATE_CHECKPOINT(8, x_16, y_16, z_16, x_16, y_16, z_16, 0.2);
	cp17 = CREATE_CHECKPOINT(8, x_17, y_17, z_17, x_17, y_17, z_17, 0.2);
	cp18 = CREATE_CHECKPOINT(8, x_18, y_18, z_18, x_18, y_18, z_18, 0.2);
	cp19 = CREATE_CHECKPOINT(8, x_19, y_19, z_19, x_19, y_19, z_19, 0.2);
	cp20 = CREATE_CHECKPOINT(8, x_20, y_20, z_20, x_20, y_20, z_20, 0.2);
	cp21 = CREATE_CHECKPOINT(8, x_21, y_21, z_21, x_21, y_21, z_21, 0.2);
	cp22 = CREATE_CHECKPOINT(8, x_22, y_22, z_22, x_22, y_22, z_22, 0.2);
	cp23 = CREATE_CHECKPOINT(8, x_23, y_23, z_23, x_23, y_23, z_23, 0.2);
	cp24 = CREATE_CHECKPOINT(8, x_24, y_24, z_24, x_24, y_24, z_24, 0.2);
	
	REQUEST_MODEL(GET_HASH_KEY("yankee"));
	while (!HAS_MODEL_LOADED(GET_HASH_KEY("yankee"))) {
		WAIT(0);
	}
	
	while (counter_4x4_pickups < 24) {
		WAIT(0);
		if ((flag_intro == 4) && (flag_timer == 1)) {
			if (TIMERB() > 1000) {
				timer_4x4 -= 1000;
				SETTIMERB(0);
			}
			DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
			DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.

			int timemin, timesec, timetemp;
			timesec = timer_4x4 / 1000;
			timemin = timesec / 60;
			timetemp = timemin * 60;
			timesec -= timetemp;
			setup_draw_text();	
			DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
			//if ((timesec > 9) && (timemin > 9)) {
			//	setup_draw_value();
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T1", timemin, timesec);
			//} else if ((timesec <= 9) && (timemin <= 9)) {
			//	setup_draw_value();
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T3", timemin, timesec);
			//} else if ((timesec > 9) && (timemin <= 9)) {
			//	setup_draw_value();
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T2", timemin, timesec);
			//} else if ((timesec <= 9) && (timemin > 9)) {
			//	setup_draw_value();
			//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T0", timemin, timesec);
			//}
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			if (timemin > 9)
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_NOZERO", timemin);// минуты
			}
			else
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", timemin);// минуты
			}
			setup_draw_value();
			DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

			setup_draw_value();
			SET_TEXT_CENTRE(1);
			if ( timesec > 9 )
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", timesec);// секунды
			}
			else
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_ZERO", timesec);// секунды
			}

			setup_draw_text();
			DISPLAY_TEXT(0.78815097, 0.73564852, "KICK1_9");
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			if ( counter_4x4_pickups >= 10 )
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.72787074, "CP_TIME_NOZERO", counter_4x4_pickups);// 
			}
			else
			{
				DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.72787074, "CP_TIME_ZERO", counter_4x4_pickups);// 
			}
			setup_draw_value();
			DISPLAY_TEXT_WITH_NUMBER(0.9203125, 0.72787074, "OUTOF_NUM", 24);// 


		}
		if (flag_timer == 1) {
			if (timer_4x4 < 1) {
				PRINT_NOW("TIMEOUT", 3000, 1);
				mission_4x4one_failed();
			}
		}
		if ((counter_4x4_pickups == 1) && (flag_timer == 0)) {
			flag_timer = 1;
		}
		if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("pcj"))) || (flag_intro < 4)) {
			if (flag_blip_1 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_1, y_1, z_1, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_1);
					DELETE_CHECKPOINT(cp1);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_1 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_2 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_2, y_2, z_2, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_2);
					DELETE_CHECKPOINT(cp2);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_2 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_3 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_3, y_3, z_3, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_3);
					DELETE_CHECKPOINT(cp3);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_3 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_4 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_4, y_4, z_4, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_4);
					DELETE_CHECKPOINT(cp4);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_4 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_5 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_5, y_5, z_5, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_5);
					DELETE_CHECKPOINT(cp5);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_5 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_6 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_6, y_6, z_6, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_6);
					DELETE_CHECKPOINT(cp6);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_6 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_7 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_7, y_7, z_7, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_7);
					DELETE_CHECKPOINT(cp7);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_7 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_8 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_8, y_8, z_8, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_8);
					DELETE_CHECKPOINT(cp8);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_8 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_9 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_9, y_9, z_9, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_9);
					DELETE_CHECKPOINT(cp9);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_9 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_10 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_10, y_10, z_10, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_10);
					DELETE_CHECKPOINT(cp10);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_10 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_11 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_11, y_11, z_11, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_11);
					DELETE_CHECKPOINT(cp11);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_11 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_12 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_12, y_12, z_12, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_12);
					DELETE_CHECKPOINT(cp12);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_12 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_13 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_13, y_13, z_13, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_13);
					DELETE_CHECKPOINT(cp13);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_13 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_14 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_14, y_14, z_14, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_14);
					DELETE_CHECKPOINT(cp14);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_14 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_15 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_15, y_15, z_15, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_15);
					DELETE_CHECKPOINT(cp15);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_15 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_16 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_16, y_16, z_16, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_16);
					DELETE_CHECKPOINT(cp16);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_16 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_17 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_17, y_17, z_17, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_17);
					DELETE_CHECKPOINT(cp17);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_17 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_18 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_18, y_18, z_18, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_18);
					DELETE_CHECKPOINT(cp18);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_18 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_19 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_19, y_19, z_19, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_19);
					DELETE_CHECKPOINT(cp19);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_19 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_20 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_20, y_20, z_20, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_20);
					DELETE_CHECKPOINT(cp20);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_20 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_21 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_21, y_21, z_21, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_21);
					DELETE_CHECKPOINT(cp21);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_21 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_22 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_22, y_22, z_22, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_22);
					DELETE_CHECKPOINT(cp22);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_22 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_23 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_23, y_23, z_23, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_23);
					DELETE_CHECKPOINT(cp23);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_23 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}
			if (flag_blip_24 == 0) {
				if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_24, y_24, z_24, 2.5, 2.5, 3.5, 0)) {
					REMOVE_BLIP(blip_24);
					DELETE_CHECKPOINT(cp24);
					counter_4x4_pickups++;
					PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
					flag_blip_24 = 1;
					//PRINT_WITH_NUMBER_NOW("T4X4_1C", counter_4x4_pickups, 3000, 1);
				}
			}		
		}
		
		if (flag_intro1_before == 1) {
			if ((flag_intro_jump == 0) && (flag_intro < 4)) {
				if (IS_GAME_KEYBOARD_KEY_PRESSED(57)) {
					intro_time_lapsed = 9501;
					flag_intro = 3;
					flag_intro_jump = 1;
				}
			}
		}
		


		if (flag_intro == 0) {
			GET_GAME_TIMER(&timer_intro_start);
			LOAD_SCENE(cam_4x4_X, cam_4x4_y, cam_4x4_z);
			CREATE_CAM(14, &cam);
			SET_CAM_POS(cam, cam_4x4_X, cam_4x4_y, cam_4x4_z);
			POINT_CAM_AT_COORD(cam, 892.5, 151.2, 9.0);
			SET_CAM_ACTIVE(cam, 1);
			SET_CAM_PROPAGATE(cam, 1);
			ACTIVATE_SCRIPTED_CAMS(1, 1);
			DO_SCREEN_FADE_IN(1000);
			while (IS_SCREEN_FADING()) {
				WAIT(0);
			}
			SETTIMERA(0); //сбрасываем таймер 
			PRINT_WITH_NUMBER_NOW("T4X4_1A", checkpoint_time_limit, 5000, 1 );
			flag_intro = 1;	
		}

		if (print_text == 1)
		{
			SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT(0.5, 0.40, "T4X4_1");//

			if ( TIMERA() > 5000 )
			{
				print_text = 0;
			}
		}
		
		if (flag_intro_jump == 0) {
			GET_GAME_TIMER(&timer_intro_now);
			intro_time_lapsed = timer_intro_now - timer_intro_start;
		}
		
		if ((intro_time_lapsed > 4000) && (flag_intro == 1)) {
			POINT_CAM_AT_COORD(cam, x_1, y_1, z_1);
			flag_intro = 2;
		}
		
		if ((intro_time_lapsed > 7000) && (flag_intro == 2)) {
			POINT_CAM_AT_COORD(cam, x_3, y_3, z_3);
			PRINT_NOW("T4X4_1B", 5000, 1);
			flag_intro = 3;
		}
		
		if ((intro_time_lapsed > 9500) && (flag_intro == 3)) {
			DO_SCREEN_FADE_OUT(1000);
			while (IS_SCREEN_FADING()) {
				WAIT(0);
			}
			CLEAR_PRINTS();
			GET_CHAR_COORDINATES(GetPlayerPed(), &player_x, &player_y, &player_z);
			LOAD_SCENE(player_x, player_y, player_z);
			ACTIVATE_SCRIPTED_CAMS(0, 0);
			SET_CAM_BEHIND_PED(GetPlayerPed());
			SET_INSTANT_WIDESCREEN_BORDERS(0);
			SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
			if (!IS_CAR_DEAD(player_4x4)) {
				LOCK_CAR_DOORS(player_4x4, 1);
			}
			ALTER_WANTED_LEVEL(GetPlayerIndex(), wanted_4x4);
			SET_EVERYONE_IGNORE_PLAYER(GetPlayerIndex(), 0);
			DO_SCREEN_FADE_IN(1000);
			while (IS_SCREEN_FADING()) {
				WAIT(0);
			}
			flag_intro = 4;
			flag_intro1_before = 1;
		}
		
		if (flag_truck_1 == 0) {
			if (LOCATE_CHAR_ANY_MEANS_2D(GetPlayerPed(), 707.0, -372.0, 10.0, 10.0, 0)) {
				CLEAR_AREA(711.0, -428.0, 5.0, 3.0, 1);
				CREATE_CAR(GET_HASH_KEY("yankee"), 711.0, -428.0, 5.0, &truck_1, 1);
				CREATE_RANDOM_CHAR_AS_DRIVER(truck_1, &truck_driver1);
				SET_CAR_HEADING(truck_1, 70.0 );
				SET_CAR_FORWARD_SPEED(truck_1, 15.0);
				int seq1;
				OPEN_SEQUENCE_TASK(&seq1);
				TASK_CAR_DRIVE_TO_COORD(0, truck_1, 554.5, -379.8, 5.0, 30.0, 0, 0, 2, 10.0, -1);
				CLOSE_SEQUENCE_TASK(seq1);
				TASK_PERFORM_SEQUENCE(truck_driver1, seq1);
				CLEAR_SEQUENCE_TASK(seq1);
				flag_truck_1 = 1;
			}
		}
		if (flag_truck_1 == 1) {
			if (!IS_CAR_DEAD(truck_1)) {
				if (LOCATE_CAR_2D(truck_1, 121.5, -912.88, 4.0, 4.0, 0)) {
					MARK_CHAR_AS_NO_LONGER_NEEDED(&truck_driver1);
					MARK_CAR_AS_NO_LONGER_NEEDED(&truck_1);
					flag_truck_1 = 2;
				}
			}
		}
		if (flag_truck_2 == 0) {
			if (LOCATE_CHAR_ANY_MEANS_2D(GetPlayerPed(), 672.0, -548.0, 10.0, 10.0, 0)) {
				CREATE_CAR(GET_HASH_KEY("yankee"), 643.1, -603.5, 5.3, &truck_2, 1);
				CREATE_RANDOM_CHAR_AS_DRIVER(truck_2, &truck_driver2);
				SET_CAR_HEADING(truck_2, 260.0);
				SET_CAR_FORWARD_SPEED(truck_2, 10.0);
				SET_DRIVE_TASK_CRUISE_SPEED(truck_driver2, 10.0);
				flag_truck_2 = 1;
			}
		}
		if (flag_truck_2 == 1) {
			if (!IS_CAR_DEAD(truck_2)) {
				if (LOCATE_CAR_2D(truck_1, 685.4, -609.4, 4.0, 4.0, 0)) {
					MARK_CHAR_AS_NO_LONGER_NEEDED(&truck_driver2);
					MARK_CAR_AS_NO_LONGER_NEEDED(&truck_2);
					flag_truck_2 = 2;
				}
			}
		}
		
		if (flag_intro > 3) {
			if (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("pcj"))) {
				while (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("pcj"))) {
					WAIT(0);
					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())) || (!IS_PLAYER_PLAYING(GetPlayerIndex()))) {
						mission_4x4one_failed();
					}
					if (flag_timer == 1) {
						if (TIMERB() > 1000) {
							timer_4x4 -= 1000;
							SETTIMERB(0);
						}
						timer_4x4_secs = timer_4x4 / 1000;
						if (timer_4x4_secs > 0) {
							PRINT_WITH_NUMBER_NOW("GETBIK1", timer_4x4_secs, 2000, 1);
						} else {
							PRINT_NOW("T4x4_F", 3000, 1);
							mission_4x4one_failed();
						}
					} else {
						PRINT_NOW("GETBIK3", 1000, 1);
					}
					
					if ((IS_CHAR_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("pcj")))) {
						PRINT_NOW("T4x4_F", 3000, 1);
						mission_4x4one_failed();
					}
				}
			}			
		}
		
		if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())) || (!IS_PLAYER_PLAYING(GetPlayerIndex()))) {
			mission_4x4one_failed();
		}
	}

	if (counter_4x4_pickups == 24) {
		mission_4x4one_passed();
	}
}

void main(void) {

	mission_start_4x4one();
	//while (true) {
	//	WAIT(0);
	//	if (flag_4x4_mission1_passed == 0) {
	//		record_4x4_one = 300;
	//	}
	//	if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
	//		if (G_ONMISSION == 0) {
	//			if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("pcj"))) && (!IS_CHAR_IN_AREA_3D(GetPlayerPed(), 937.4, 222.8, 7.0, 943.4, 228.8, 9.0, 0))) {
	//				flag_4x4one_trigger = 1;
	//			}
	//			if (!IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
	//				flag_4x4one_trigger = 0;
	//			}
	//			if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("pcj"))) && (flag_4x4one_trigger == 0)) {
	//				flag_launch_4x4_1_ok = 1;
	//			}
	//			if (flag_launch_4x4_1_ok == 1) {
	//				PRINT_BIG("T4X4_1", 15000, 2);
	//				WAIT(0);
	//				mission_start_4x4one();
	//			}
	//		}
	//	}
	//}
}