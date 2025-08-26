#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
#include "mission_passed.h"
int mission_set;
int bmx_1_trigger;
int print_text = 1;
int counter_laps, counter_gates;
int time_lapsed, time_now, time_start;
int time_off_bike, time_bailed, time_left_to_find_bike, time_left_to_find_bike_secs;
int record_bmx_1;
int counter_bmx_1_reward, bmx_1_reward;
int flag_bmx1_print, bmx1_minutes;
int kwayzee_biker1, kwayzee_biker2, kwayzee_biker3;
int kwayzee_moto1, kwayzee_moto2, kwayzee_moto3;
int flag_kwayzee1, flag_kwayzee2, flag_kwayzee3;
int var_kwayzee, var_moto, var_flag, change_cp, cp;

int record_bmx_2, flag_bmx2_print, counter_bmx_2_reward, bmx_2_reward;
int bmx2_minutes, irrate_bloke, blokes_car, timer_4x4;

int blip_1, blip_2, blip_3;
int blip_4, blip_5, blip_6;
int blip_7, blip_8, blip_9;
int blip_10, blip_11, blip_12;
int blip_13, blip_14, blip_15;
int blip_16, blip_17, blip_18;
int blip_19, blip_20, blip_21, blip_22, blip_23;
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
int flag_new_bmx_record_set;
int barrel_1, barrel_2, barrel_3, barrel_4;
int fon, textur;

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

void SET_CAR_RAM_CAR(int mainCar, int mainDriver, int tarDriver) {
	int seq2;
	OPEN_SEQUENCE_TASK(&seq2);	
	TASK_CAR_MISSION_PED_TARGET(0, mainCar, tarDriver, 2, 200.0, 2, 0, 10);
	CLOSE_SEQUENCE_TASK(seq2);
	TASK_PERFORM_SEQUENCE(mainDriver, seq2);
	CLEAR_SEQUENCE_TASK(seq2);
	return;
}

void mission_cleanup_bmx_2(void) {
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
	MARK_MODEL_AS_NO_LONGER_NEEDED(GET_HASH_KEY("barrel4"));
	MARK_MODEL_AS_NO_LONGER_NEEDED(GET_HASH_KEY("m_m_business_02"));
	MARK_CHAR_AS_NO_LONGER_NEEDED(&irrate_bloke);
	MARK_CAR_AS_NO_LONGER_NEEDED(&blokes_car);
	RELEASE_TEXTURE(fon);
	REMOVE_TXD(textur);
	DELETE_OBJECT(&barrel_1);
	DELETE_OBJECT(&barrel_2);
	DELETE_OBJECT(&barrel_3);
	DELETE_OBJECT(&barrel_4);
	RELEASE_WEATHER();
	//G_ONMISSION = 0;
	//main();
	TERMINATE_THIS_SCRIPT();
}

void mission_cleanup_bmx_1(void) {
	time_left_to_find_bike = 1;
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
	MARK_MODEL_AS_NO_LONGER_NEEDED(GET_HASH_KEY("barrel4"));
	MARK_MODEL_AS_NO_LONGER_NEEDED(GET_HASH_KEY("m_m_business_02"));
	MARK_MODEL_AS_NO_LONGER_NEEDED(GET_HASH_KEY("m_m_business_03"));
	MARK_CHAR_AS_NO_LONGER_NEEDED(&kwayzee_biker1);
	MARK_CAR_AS_NO_LONGER_NEEDED(&kwayzee_moto1);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&kwayzee_biker2);
	MARK_CAR_AS_NO_LONGER_NEEDED(&kwayzee_moto2);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&kwayzee_biker3);
	MARK_CAR_AS_NO_LONGER_NEEDED(&kwayzee_moto3);
	RELEASE_TEXTURE(fon);
	REMOVE_TXD(textur);
	DELETE_OBJECT(&barrel_1);
	DELETE_OBJECT(&barrel_2);
	DELETE_OBJECT(&barrel_3);
	DELETE_OBJECT(&barrel_4);
	RELEASE_WEATHER();
	//G_ONMISSION = 0;
	//main();
	TERMINATE_THIS_SCRIPT();
}

void mission_bmx_1_passed(void) {
	bmx_1_reward = counter_bmx_1_reward * 100;
	//PRINT_WITH_NUMBER_BIG("B_PASS", bmx_1_reward, 5000, 1);
	CLEAR_WANTED_LEVEL(GetPlayerIndex());
	if (G_BMX_1 == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
		G_GAME_PROGRESS += 1;
		SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
	}
	G_BMX_1 += 1;
	bmx_1_reward = G_BMX_1 * 100;
	INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, bmx_1_reward);
	ADD_SCORE(GetPlayerIndex(), bmx_1_reward);
	play_mission_complete_tune();
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "B_PASS", bmx_1_reward);//
		
		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	mission_cleanup_bmx_1();
}

void mission_bmx_2_passed(void) {
	bmx_2_reward = counter_bmx_2_reward * 100;
	//PRINT_WITH_NUMBER_BIG("B_PASS", bmx_2_reward, 5000, 1);
	CLEAR_WANTED_LEVEL(GetPlayerIndex());
	if (G_BMX_2 == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
		G_GAME_PROGRESS += 1;
		SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
	}
	G_BMX_2 += 1;
	bmx_2_reward = G_BMX_2 * 100;
	INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, bmx_2_reward);
	ADD_SCORE(GetPlayerIndex(), bmx_2_reward);
	play_mission_complete_tune();
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "B_PASS", bmx_2_reward);//
		
		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	mission_cleanup_bmx_2();
}

void mission_bmx_2_failed(void) {
	if (G_BMX_2 == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
	}
	//PRINT_BIG("B_FAIL", 5000, 1);
	PRINT_NOW("BMXFAIL", 5000, 1);
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT(0.5, 0.45, "B_FAIL");// пишем "Миссия завершина"

		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	mission_cleanup_bmx_1();
}

void mission_bmx_1_failed(void) {
	if (G_BMX_1 == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
	}
	//PRINT_BIG("B_FAIL", 5000, 1);
	PRINT_NOW("BMXFAIL", 5000, 1);
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT(0.5, 0.45, "B_FAIL");// пишем "Миссия завершина"

		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	mission_cleanup_bmx_1();
}

void kwayzee_stuff(void) {
	if ((!IS_CHAR_DEAD(var_kwayzee)) && (var_flag == 0)) {
		if (!IS_CAR_DEAD(var_moto)) {
			if ((!IS_CHAR_IN_CAR(var_kwayzee, var_moto)) || (!IS_CHAR_IN_ANY_CAR(GetPlayerPed()))) {
				TASK_COMBAT(var_kwayzee, GetPlayerPed());
				var_flag = 1;
			}
		} else {
			TASK_COMBAT(var_kwayzee, GetPlayerPed());
			var_flag = 1;
		}
	}
	return;
}

void timing_malarkey(void) {
	bmx1_minutes = 0;
	while (time_lapsed > 59) {
		time_lapsed = time_lapsed - 60;
		bmx1_minutes++;
	}
	PRINT_WITH_2_NUMBERS_NOW("NEW_REC", bmx1_minutes, time_lapsed, 5000, 1);
	return;
}

void time_malarkey(void) {
	bmx2_minutes = 0;
	while (time_lapsed > 59) {
		time_lapsed = time_lapsed - 60;
		bmx2_minutes++;
	}
	PRINT_WITH_2_NUMBERS_NOW("NEW_REC", bmx2_minutes, time_lapsed, 5000, 1);
}

void mission_start_bmx_1(void) {
	if (G_BMX_1 == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}
	//G_ONMISSION = 1;
	LOAD_ADDITIONAL_TEXT("BMXALL", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	WAIT(0);
	counter_laps = 0;
	counter_gates = 1;
	time_lapsed = 0;
	flag_new_bmx_record_set = 0;
	flag_bmx1_print = 0;
	flag_kwayzee1 = 0;
	flag_kwayzee2 = 0;
	flag_kwayzee3 = 0;
	
	x_1 = -23.0;
	y_1 = 1950.9;
	z_1 = 9.24;

	x_2 = -34.8;
	y_2 = 1931.7;
	z_2 = 3.15;

	x_3 = -55.4;
	y_3 = 1958.9;
	z_3 = 9.5;

	x_4 = -83.8;
	y_4 = 1942.1;
	z_4 = 7.6;

	x_5 = -96.6;
	y_5 = 1963.0;
	z_5 = 4.6;

	x_6 = -123.4;
	y_6 = 1955.7;
	z_6 = 5.0;

	x_7 = -100.55;
	y_7 = 1988.6;
	z_7 = 5.3;

	x_8 = -127.0;
	y_8 = 1993.0;
	z_8 = 5.3;

	x_9 = -95.5;
	y_9 = 2009.9;
	z_9 = 5.5;

	x_10 = -102.0;
	y_10 = 2033.0;
	z_10 = 4.8;

	x_11 = -69.4;
	y_11 = 2007.6;
	z_11 = 6.3;

	x_12 = -67.6;
	y_12 = 2040.1;
	z_12 = 4.8;

	x_13 = -39.2;
	y_13 = 2023.5;
	z_13 = 6.0;

	x_14 = -66.3;
	y_14 = 1980.5;
	z_14 = 10.5;

	x_15 = -17.2;
	y_15 = 2014.4;
	z_15 = 4.8;

	x_16 = -7.6;
	y_16 = 1988.42;
	z_16 = 4.8;

	x_17 = 4.0;
	y_17 = 2024.8;
	z_17 = 5.1;

	x_18 = 15.0;
	y_18 = 1965.1;
	z_18 = 5.0;

	x_19 = -12.0;
	y_19 = 1972.5;
	z_19 = 5.4;

	x_20 = -20.5;
	y_20 = 1967.6;
	z_20 = 5.0;

	GET_GAME_TIMER(&time_start);
	ADD_BLIP_FOR_COORD(x_1, y_1, z_1, &blip_1);
	CHANGE_BLIP_COLOUR(blip_1, 5);
	cp = CREATE_CHECKPOINT(8, x_1, y_1, z_1, x_1, y_1, z_1, 0.2);
	if (counter_bmx_1_reward > 0) {
		REQUEST_MODEL(GET_HASH_KEY("barrel4"));
		while (!HAS_MODEL_LOADED(GET_HASH_KEY("barrel4"))) WAIT(0);
		float pz;
		GET_GROUND_Z_FOR_3D_COORD(20.0, 1967.4, 20.0, &pz);
		CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("barrel4"), 20.0, 1967.4, pz+0.5, &barrel_1, 1);
		SET_OBJECT_COLLISION(barrel_1, 1);
		GET_GROUND_Z_FOR_3D_COORD(28.36, 1980.12, 20.0, &pz);
		CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("barrel4"), 28.36, 1980.12, pz+0.5, &barrel_2, 1);
		SET_OBJECT_COLLISION(barrel_2, 1);
		GET_GROUND_Z_FOR_3D_COORD(33.0, 1988.5, 20.0, &pz);
		CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("barrel4"), 33.0, 1988.5, pz+0.5, &barrel_3, 1);
		SET_OBJECT_COLLISION(barrel_3, 1);
		GET_GROUND_Z_FOR_3D_COORD(31.73, 1998.0, 20.0, &pz);
		CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("barrel4"), 31.73, 1998.0, pz+0.5, &barrel_4, 1);
		SET_OBJECT_COLLISION(barrel_4, 1);	
	}
	if (counter_bmx_1_reward > 2) {
		REQUEST_MODEL(GET_HASH_KEY("m_m_business_02"));
		REQUEST_MODEL(GET_HASH_KEY("m_m_business_03"));
		REQUEST_MODEL(GET_HASH_KEY("sanchez"));
		while ((!HAS_MODEL_LOADED(GET_HASH_KEY("m_m_business_02"))) || (!HAS_MODEL_LOADED(GET_HASH_KEY("m_m_business_03"))) || (!HAS_MODEL_LOADED(GET_HASH_KEY("sanchez")))) WAIT(0);
		
		CREATE_CAR(GET_HASH_KEY("sanchez"), 45.7, 2057.0, 5.4, &kwayzee_moto1, 1);
		CHANGE_CAR_COLOUR(kwayzee_moto1, 0, 0);
		SET_CAR_HEADING(kwayzee_moto1, 190.0);
		CREATE_CHAR_INSIDE_CAR(kwayzee_moto1, 26, GET_HASH_KEY("m_m_business_02"), &kwayzee_biker1);
		UpdateWeaponOfPed(kwayzee_biker1, WEAPON_KNIFE);
		SET_CAR_RAM_CAR(kwayzee_moto1, kwayzee_biker1, GetPlayerPed()); 
			
		CREATE_CAR(GET_HASH_KEY("sanchez"), -43.7, 2055.0, 5.4, &kwayzee_moto2, 1);
		CHANGE_CAR_COLOUR(kwayzee_moto2, 0, 0);
		SET_CAR_HEADING(kwayzee_moto2, 190.0);
		CREATE_CHAR_INSIDE_CAR(kwayzee_moto2, 26, GET_HASH_KEY("m_m_business_02"), &kwayzee_biker2);
		UpdateWeaponOfPed(kwayzee_biker2, WEAPON_KNIFE);
		SET_CAR_RAM_CAR(kwayzee_moto2, kwayzee_biker2, GetPlayerPed());
		
		CREATE_CAR(GET_HASH_KEY("sanchez"), -47.7, 2058.0, 5.4, &kwayzee_moto3, 1);
		CHANGE_CAR_COLOUR(kwayzee_moto3, 0, 0);
		SET_CAR_HEADING(kwayzee_moto3, 190.0);
		CREATE_CHAR_INSIDE_CAR(kwayzee_moto3, 26, GET_HASH_KEY("m_m_business_02"), &kwayzee_biker3);
		UpdateWeaponOfPed(kwayzee_biker3, WEAPON_KNIFE);
		SET_CAR_RAM_CAR(kwayzee_moto3, kwayzee_biker3, GetPlayerPed());
	}
	
	while (counter_laps < 2) {
		WAIT(0);	
		if (print_text == 1)
		{
			SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT(0.5, 0.45, "BMX_1");//

			if ( TIMERA() > 5000 )
			{
				print_text = 0;
			}
		}

		GET_GAME_TIMER(&time_now);
		time_lapsed = time_now - time_start;
		DRAW_SPRITE(fon, 0.8765625, 0.7858, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
		int timemin, timesec, timetemp;
		timesec = time_lapsed / 1000;
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
		if ((timesec > 9) && (timemin > 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T1", timemin, timesec);
		} else if ((timesec <= 9) && (timemin <= 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T3", timemin, timesec);
		} else if ((timesec > 9) && (timemin <= 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T2", timemin, timesec);
		} else if ((timesec <= 9) && (timemin > 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T0", timemin, timesec);
		}

		if (flag_bmx1_print == 0) {
			PRINT_NOW("BMX_HOW", 5000, 1);
			flag_bmx1_print = 1;
		}
		if ((flag_bmx1_print == 1) && (time_lapsed > 5000)) {
			PRINT_NOW("BMXREW1", 5000, 1);
			flag_bmx1_print = 2;
		}
		if ((flag_bmx1_print == 2) && (time_lapsed > 10000)) {
			PRINT_NOW("BMXREW2", 5000, 1);
			flag_bmx1_print = 3;
		}
		
		if (counter_gates == 1) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_1, y_1, z_1, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_1);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_2, y_2, z_2, &blip_2);
				CHANGE_BLIP_COLOUR(blip_2, 5);
				cp = CREATE_CHECKPOINT(8, x_2, y_2, z_2, x_2, y_2, z_2, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 2) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_2, y_2, z_2, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_2);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_3, y_3, z_3, &blip_3);
				CHANGE_BLIP_COLOUR(blip_3, 5);
				cp = CREATE_CHECKPOINT(8, x_3, y_3, z_3, x_3, y_3, z_3, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 3) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_3, y_3, z_3, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_3);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_4, y_4, z_4, &blip_4);
				CHANGE_BLIP_COLOUR(blip_4, 5);
				cp = CREATE_CHECKPOINT(8, x_4, y_4, z_4, x_4, y_4, z_4, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 4) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_4, y_4, z_4, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_4);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_5, y_5, z_5, &blip_5);
				CHANGE_BLIP_COLOUR(blip_5, 5);
				cp = CREATE_CHECKPOINT(8, x_5, y_5, z_5, x_5, y_5, z_5, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 5) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_5, y_5, z_5, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_5);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_6, y_6, z_6, &blip_6);
				CHANGE_BLIP_COLOUR(blip_6, 5);
				cp = CREATE_CHECKPOINT(8, x_6, y_6, z_6, x_6, y_6, z_6, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 6) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_6, y_6, z_6, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_6);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_7, y_7, z_7, &blip_7);
				CHANGE_BLIP_COLOUR(blip_7, 5);
				cp = CREATE_CHECKPOINT(8, x_7, y_7, z_7, x_7, y_7, z_7, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 7) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_7, y_7, z_7, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_7);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_8, y_8, z_8, &blip_8);
				CHANGE_BLIP_COLOUR(blip_8, 5);
				cp = CREATE_CHECKPOINT(8, x_8, y_8, z_8, x_8, y_8, z_8, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 8) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_8, y_8, z_8, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_8);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_9, y_9, z_9, &blip_9);
				CHANGE_BLIP_COLOUR(blip_9, 5);
				cp = CREATE_CHECKPOINT(8, x_9, y_9, z_9, x_9, y_9, z_9, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 9) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_9, y_9, z_9, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_9);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_10, y_10, z_10, &blip_10);
				CHANGE_BLIP_COLOUR(blip_10, 5);
				cp = CREATE_CHECKPOINT(8, x_10, y_10, z_10, x_10, y_10, z_10, 0.2);
				counter_gates++;
				if ((flag_bmx1_print == 3) && (time_lapsed > 12000) && (counter_bmx_1_reward > 1)) {
					FORCE_WEATHER(4);
					PRINT_NOW("BMXRAIN", 4000, 1);
					flag_bmx1_print = 4;
				}
			}
		}
		if (counter_gates == 10) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_10, y_10, z_10, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_10);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_11, y_11, z_11, &blip_11);
				CHANGE_BLIP_COLOUR(blip_11, 5);
				cp = CREATE_CHECKPOINT(8, x_11, y_11, z_11, x_11, y_11, z_11, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 11) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_11, y_11, z_11, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_11);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_12, y_12, z_12, &blip_12);
				CHANGE_BLIP_COLOUR(blip_12, 5);
				cp = CREATE_CHECKPOINT(8, x_12, y_12, z_12, x_12, y_12, z_12, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 12) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_12, y_12, z_12, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_12);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_13, y_13, z_13, &blip_13);
				CHANGE_BLIP_COLOUR(blip_13, 5);
				cp = CREATE_CHECKPOINT(8, x_13, y_13, z_13, x_13, y_13, z_13, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 13) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_13, y_13, z_13, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_13);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_14, y_14, z_14, &blip_14);
				CHANGE_BLIP_COLOUR(blip_14, 5);
				cp = CREATE_CHECKPOINT(8, x_14, y_14, z_14, x_14, y_14, z_14, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 14) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_14, y_14, z_14, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_14);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_15, y_15, z_15, &blip_15);
				CHANGE_BLIP_COLOUR(blip_15, 5);
				cp = CREATE_CHECKPOINT(8, x_15, y_15, z_15, x_15, y_15, z_15, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 15) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_15, y_15, z_15, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_15);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_16, y_16, z_16, &blip_16);
				CHANGE_BLIP_COLOUR(blip_16, 5);
				cp = CREATE_CHECKPOINT(8, x_16, y_16, z_16, x_16, y_16, z_16, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 16) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_16, y_16, z_16, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_16);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_17, y_17, z_17, &blip_17);
				CHANGE_BLIP_COLOUR(blip_17, 5);
				cp = CREATE_CHECKPOINT(8, x_17, y_17, z_17, x_17, y_17, z_17, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 17) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_17, y_17, z_17, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_17);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_18, y_18, z_18, &blip_18);
				CHANGE_BLIP_COLOUR(blip_18, 5);
				cp = CREATE_CHECKPOINT(8, x_18, y_18, z_18, x_18, y_18, z_18, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 18) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_18, y_18, z_18, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_18);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_19, y_19, z_19, &blip_19);
				CHANGE_BLIP_COLOUR(blip_19, 5);
				cp = CREATE_CHECKPOINT(8, x_19, y_19, z_19, x_19, y_19, z_19, 0.2);
				counter_gates++;
			}
		}
		if (counter_gates == 19) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_19, y_19, z_19, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_19);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				counter_gates = 1;
				counter_laps++;
				if (counter_laps < 2) {
					ADD_BLIP_FOR_COORD(x_1, y_1, z_1, &blip_1);
					CHANGE_BLIP_COLOUR(blip_1, 5);
					cp = CREATE_CHECKPOINT(8, x_1, y_1, z_1, x_1, y_1, z_1, 0.2);
				}
			}
		}
		var_kwayzee = kwayzee_biker1;
		var_moto = kwayzee_moto1;
		var_flag = flag_kwayzee1;
		kwayzee_stuff();
		if (var_flag == 1) {
			flag_kwayzee1 = 1;
		}
		
		var_kwayzee = kwayzee_biker2;
		var_moto = kwayzee_moto2;
		var_flag = flag_kwayzee2;
		kwayzee_stuff();
		if (var_flag == 1) {
			flag_kwayzee2 = 1;
		}
		
		var_kwayzee = kwayzee_biker3;
		var_moto = kwayzee_moto3;
		var_flag = flag_kwayzee3;
		kwayzee_stuff();
		if (var_flag == 1) {
			flag_kwayzee3 = 1;
		}
		
		if (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sanchez"))) {
			GET_GAME_TIMER(&time_bailed);
			while (!(time_left_to_find_bike < 0)) {
				WAIT(0);
				if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())) || (!IS_PLAYER_PLAYING(GetPlayerIndex()))) {
					mission_bmx_1_failed();
				}
				GET_GAME_TIMER(&time_now);
				time_off_bike = time_now - time_bailed;
				time_left_to_find_bike = 15000 - time_off_bike;
				time_left_to_find_bike_secs = time_left_to_find_bike / 1000;
				PRINT_WITH_NUMBER_NOW("GETBIK2", time_left_to_find_bike_secs, 2000, 1);
				if (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sanchez"))) {
					time_left_to_find_bike = 1;
					break;
				}
			}
			if (!(time_left_to_find_bike == 1)) {
				mission_bmx_1_failed();
			}
		}
		
		if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())) || (!IS_PLAYER_PLAYING(GetPlayerIndex()))) {
			mission_bmx_1_failed();
		}
	}
	
	if (counter_laps == 2) {
		time_lapsed = time_lapsed / 1000;
		//if (flag_bmx_1_passed == 0) {
			record_bmx_1 = time_lapsed;
			flag_new_bmx_record_set	= 1;
			counter_bmx_1_reward = 1;
			timing_malarkey();
		/*} else {
			if (time_lapsed < record_bmx_1) {
				record_bmx_1 = time_lapsed;
				flag_new_bmx_record_set	= 1;
				counter_bmx_1_reward++;
				timing_malarkey();
			}
		}*/
		if (flag_new_bmx_record_set == 1) {
			mission_bmx_1_passed();
		}
	}
}

void mission_start_bmx_2(void) {
	if (G_BMX_2 == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}
	//G_ONMISSION = 1;
	LOAD_ADDITIONAL_TEXT("BMXALL", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	WAIT(0);
	counter_laps = 0;
	counter_gates = 19;
	timer_4x4 = 0;
	time_lapsed = 0;
	flag_new_bmx_record_set = 0;
	flag_bmx2_print = 0;
	flag_kwayzee1 = 0;
	flag_kwayzee2 = 0;
	flag_kwayzee3 = 0;
	
	x_1 = -23.0;
	y_1 = 1950.9;
	z_1 = 9.24;

	x_2 = -34.8;
	y_2 = 1931.7;
	z_2 = 3.15;

	x_3 = -55.4;
	y_3 = 1958.9;
	z_3 = 9.5;

	x_4 = -83.8;
	y_4 = 1942.1;
	z_4 = 7.6;

	x_5 = -96.6;
	y_5 = 1963.0;
	z_5 = 4.6;

	x_6 = -123.4;
	y_6 = 1955.7;
	z_6 = 5.0;

	x_7 = -100.55;
	y_7 = 1988.6;
	z_7 = 5.3;

	x_8 = -127.0;
	y_8 = 1993.0;
	z_8 = 5.3;

	x_9 = -95.5;
	y_9 = 2009.9;
	z_9 = 5.5;

	x_10 = -102.0;
	y_10 = 2033.0;
	z_10 = 4.8;

	x_11 = -69.4;
	y_11 = 2007.6;
	z_11 = 6.3;

	x_12 = -67.6;
	y_12 = 2040.1;
	z_12 = 4.8;

	x_13 = -39.2;
	y_13 = 2023.5;
	z_13 = 6.0;

	x_14 = -66.3;
	y_14 = 1980.5;
	z_14 = 10.5;

	x_15 = -17.2;
	y_15 = 2014.4;
	z_15 = 4.8;

	x_16 = -7.6;
	y_16 = 1988.42;
	z_16 = 4.8;

	x_17 = 4.0;
	y_17 = 2024.8;
	z_17 = 5.1;

	x_18 = 15.0;
	y_18 = 1965.1;
	z_18 = 5.0;

	x_19 = -12.0;
	y_19 = 1972.5;
	z_19 = 5.4;

	GET_GAME_TIMER(&time_start);
	ADD_BLIP_FOR_COORD(x_19, y_19, z_19, &blip_19);
	CHANGE_BLIP_COLOUR(blip_19, 5);
	cp = CREATE_CHECKPOINT(8, x_19, y_19, z_19, x_19, y_19, z_19, 0.2);
	if (counter_bmx_2_reward > 0) {
		REQUEST_MODEL(GET_HASH_KEY("barrel4"));
		while (!HAS_MODEL_LOADED(GET_HASH_KEY("barrel4"))) WAIT(0);
		float pz;
		GET_GROUND_Z_FOR_3D_COORD(20.0, 1967.4, 20.0, &pz);
		CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("barrel4"), 20.0, 1967.4, pz+0.5, &barrel_1, 1);
		SET_OBJECT_COLLISION(barrel_1, 1);
		GET_GROUND_Z_FOR_3D_COORD(28.36, 1980.12, 20.0, &pz);
		CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("barrel4"), 28.36, 1980.12, pz+0.5, &barrel_2, 1);
		SET_OBJECT_COLLISION(barrel_2, 1);
		GET_GROUND_Z_FOR_3D_COORD(33.0, 1988.5, 20.0, &pz);
		CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("barrel4"), 33.0, 1988.5, pz+0.5, &barrel_3, 1);
		SET_OBJECT_COLLISION(barrel_3, 1);
		GET_GROUND_Z_FOR_3D_COORD(31.73, 1998.0, 20.0, &pz);
		CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("barrel4"), 31.73, 1998.0, pz+0.5, &barrel_4, 1);
		SET_OBJECT_COLLISION(barrel_4, 1);	
	}
	if (counter_bmx_2_reward > 2) {
		REQUEST_MODEL(GET_HASH_KEY("m_m_business_02"));
		REQUEST_MODEL(GET_HASH_KEY("rancher"));
		while ((!HAS_MODEL_LOADED(GET_HASH_KEY("m_m_business_02"))) || (!HAS_MODEL_LOADED(GET_HASH_KEY("rancher")))) WAIT(0);
		
		CREATE_CAR(GET_HASH_KEY("rancher"), 45.7, 2057.0, 5.4, &blokes_car, 1);
		CHANGE_CAR_COLOUR(blokes_car, 0, 0);
		SET_CAR_HEADING(blokes_car, 190.0);
		CREATE_CHAR_INSIDE_CAR(blokes_car, 26, GET_HASH_KEY("m_m_business_02"), &irrate_bloke);
		UpdateWeaponOfPed(irrate_bloke, WEAPON_BASEBALLBAT);
		SET_CAR_RAM_CAR(blokes_car, irrate_bloke, GetPlayerPed()); 
	}
	
	while (counter_laps < 2) {
		WAIT(0);
		if (print_text == 1)
		{
			SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT(0.5, 0.45, "BMX_2");//

			if ( TIMERA() > 5000 )
			{
				print_text = 0;
			}
		}

		GET_GAME_TIMER(&time_now);
		time_lapsed = time_now - time_start;
		DRAW_SPRITE(fon, 0.8765625, 0.7858, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
		int timemin, timesec, timetemp;
		timesec = time_lapsed / 1000;
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
		if ((timesec > 9) && (timemin > 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T1", timemin, timesec);
		} else if ((timesec <= 9) && (timemin <= 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T3", timemin, timesec);
		} else if ((timesec > 9) && (timemin <= 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T2", timemin, timesec);
		} else if ((timesec <= 9) && (timemin > 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T0", timemin, timesec);
		}

		if (flag_bmx1_print == 0) {
			PRINT_NOW("BMX_HOW", 5000, 1);
			flag_bmx1_print = 1;
		}
		if ((flag_bmx1_print == 1) && (time_lapsed > 5000)) {
			PRINT_NOW("BMXREW1", 5000, 1);
			flag_bmx1_print = 2;
		}
		if ((flag_bmx1_print == 2) && (time_lapsed > 10000)) {
			PRINT_NOW("BMXREW2", 5000, 1);
			flag_bmx1_print = 3;
		}
		
		if (counter_gates == 1) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_1, y_1, z_1, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_1);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				counter_gates = 19;
				counter_laps++;
				if (counter_laps < 2) {
					ADD_BLIP_FOR_COORD(x_19, y_19, z_19, &blip_19);
					CHANGE_BLIP_COLOUR(blip_19, 5);
					cp = CREATE_CHECKPOINT(8, x_19, y_19, z_19, x_19, y_19, z_19, 0.2);
				}
			}
		}
		if (counter_gates == 2) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_2, y_2, z_2, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_2);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_1, y_1, z_1, &blip_1);
				CHANGE_BLIP_COLOUR(blip_1, 5);
				cp = CREATE_CHECKPOINT(8, x_1, y_1, z_1, x_1, y_1, z_1, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 3) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_3, y_3, z_3, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_3);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_2, y_2, z_2, &blip_2);
				CHANGE_BLIP_COLOUR(blip_2, 5);
				cp = CREATE_CHECKPOINT(8, x_2, y_2, z_2, x_2, y_2, z_2, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 4) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_4, y_4, z_4, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_4);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_3, y_3, z_3, &blip_3);
				CHANGE_BLIP_COLOUR(blip_3, 5);
				cp = CREATE_CHECKPOINT(8, x_3, y_3, z_3, x_3, y_3, z_3, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 5) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_5, y_5, z_5, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_5);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_4, y_4, z_4, &blip_4);
				CHANGE_BLIP_COLOUR(blip_4, 5);
				cp = CREATE_CHECKPOINT(8, x_4, y_4, z_4, x_4, y_4, z_4, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 6) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_6, y_6, z_6, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_6);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_5, y_5, z_5, &blip_5);
				CHANGE_BLIP_COLOUR(blip_5, 5);
				cp = CREATE_CHECKPOINT(8, x_5, y_5, z_5, x_5, y_5, z_5, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 7) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_7, y_7, z_7, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_7);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_6, y_6, z_6, &blip_6);
				CHANGE_BLIP_COLOUR(blip_6, 5);
				cp = CREATE_CHECKPOINT(8, x_6, y_6, z_6, x_6, y_6, z_6, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 8) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_8, y_8, z_8, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_8);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_7, y_7, z_7, &blip_7);
				CHANGE_BLIP_COLOUR(blip_7, 5);
				cp = CREATE_CHECKPOINT(8, x_7, y_7, z_7, x_7, y_7, z_7, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 9) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_9, y_9, z_9, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_9);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_8, y_8, z_8, &blip_8);
				CHANGE_BLIP_COLOUR(blip_8, 5);
				cp = CREATE_CHECKPOINT(8, x_8, y_8, z_8, x_8, y_8, z_8, 0.2);
				counter_gates--;
				if ((flag_bmx2_print == 3) && (time_lapsed > 12000) && (counter_bmx_2_reward > 3)) {
					FORCE_WEATHER(4);
					PRINT_NOW("BMXRAIN", 4000, 1);
					flag_bmx2_print = 4;
				}
			}
		}
		if (counter_gates == 10) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_10, y_10, z_10, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_10);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_9, y_9, z_9, &blip_9);
				CHANGE_BLIP_COLOUR(blip_9, 5);
				cp = CREATE_CHECKPOINT(8, x_9, y_9, z_9, x_9, y_9, z_9, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 11) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_11, y_11, z_11, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_11);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_10, y_10, z_10, &blip_10);
				CHANGE_BLIP_COLOUR(blip_10, 5);
				cp = CREATE_CHECKPOINT(8, x_10, y_10, z_10, x_10, y_10, z_10, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 12) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_12, y_12, z_12, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_12);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_11, y_11, z_11, &blip_11);
				CHANGE_BLIP_COLOUR(blip_11, 5);
				cp = CREATE_CHECKPOINT(8, x_11, y_11, z_11, x_11, y_11, z_11, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 13) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_13, y_13, z_13, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_13);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_12, y_12, z_12, &blip_12);
				CHANGE_BLIP_COLOUR(blip_12, 5);
				cp = CREATE_CHECKPOINT(8, x_12, y_12, z_12, x_12, y_12, z_12, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 14) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_14, y_14, z_14, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_14);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_13, y_13, z_13, &blip_13);
				CHANGE_BLIP_COLOUR(blip_13, 5);
				cp = CREATE_CHECKPOINT(8, x_13, y_13, z_13, x_13, y_13, z_13, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 15) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_15, y_15, z_15, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_15);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_14, y_14, z_14, &blip_14);
				CHANGE_BLIP_COLOUR(blip_14, 5);
				cp = CREATE_CHECKPOINT(8, x_14, y_14, z_14, x_14, y_14, z_14, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 16) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_16, y_16, z_16, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_16);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_15, y_15, z_15, &blip_15);
				CHANGE_BLIP_COLOUR(blip_15, 5);
				cp = CREATE_CHECKPOINT(8, x_15, y_15, z_15, x_15, y_15, z_15, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 17) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_17, y_17, z_17, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_17);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_16, y_16, z_16, &blip_16);
				CHANGE_BLIP_COLOUR(blip_16, 5);
				cp = CREATE_CHECKPOINT(8, x_16, y_16, z_16, x_16, y_16, z_16, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 18) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_18, y_18, z_18, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_18);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_17, y_17, z_17, &blip_17);
				CHANGE_BLIP_COLOUR(blip_17, 5);
				cp = CREATE_CHECKPOINT(8, x_17, y_17, z_17, x_17, y_17, z_17, 0.2);
				counter_gates--;
			}
		}
		if (counter_gates == 19) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_19, y_19, z_19, 3.0, 3.0, 3.0, 0)) {
				REMOVE_BLIP(blip_19);
				DELETE_CHECKPOINT(cp);
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				ADD_BLIP_FOR_COORD(x_18, y_18, z_18, &blip_18);
				CHANGE_BLIP_COLOUR(blip_18, 5);
				cp = CREATE_CHECKPOINT(8, x_18, y_18, z_18, x_18, y_18, z_18, 0.2);
				counter_gates--;
			}
		}
		
		if (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("landstalker"))) {
			PRINT_NOW("T4X4_F", 3000, 1);
			mission_bmx_2_failed();
		}
		
			
		if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())) || (!IS_PLAYER_PLAYING(GetPlayerIndex()))) {
			mission_bmx_2_failed();
		}
	}
	
	if (counter_laps == 2) {
		time_lapsed = time_lapsed / 1000;
		//if (flag_bmx_1_passed == 0) {
			record_bmx_2 = time_lapsed;
			flag_new_bmx_record_set	= 1;
			counter_bmx_2_reward = 1;
			time_malarkey();
		/*} else {
			if (time_lapsed < record_bmx_2) {
				record_bmx_2 = time_lapsed;
				flag_new_bmx_record_set	= 1;
				counter_bmx_2_reward++;
				time_malarkey();
			}
		}*/
		if (flag_new_bmx_record_set == 1) {
			mission_bmx_2_passed();
		}
	}
}

void main(void) {

	SETTIMERA(0); //сбрасываем таймер 
	while (true) {
		WAIT(0);
		if (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sanchez"))) {
			//PRINT_BIG("BMX_1", 15000, 2);
			mission_set = 1;
			mission_start_bmx_1();
			if (HAS_DEATHARREST_EXECUTED()) {
				mission_bmx_1_failed();
			}
			mission_cleanup_bmx_1();
		}
		if (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("landstalker"))) {
			//PRINT_BIG("BMX_2", 15000, 2);
			mission_set = 2;
			mission_start_bmx_2();
			if (HAS_DEATHARREST_EXECUTED()) {
				mission_bmx_2_failed();
			}
			mission_cleanup_bmx_2();
		}
	}
	//while (true) {
	//	WAIT(0);
	//	if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
	//		if (G_ONMISSION == 0){
	//			if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sanchez"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("landstalker")))) {
	//				if (!IS_CHAR_IN_AREA_3D(GetPlayerPed(), 3.0, 1938.0, 3.5, 13.0, 1948.0, 7.5, 0)) {
	//					bmx_1_trigger = 1;
	//				}
	//			}
	//			if (bmx_1_trigger == 0) {
	//				if (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sanchez"))) {
	//					PRINT_BIG("BMX_1", 15000, 2);
	//					mission_set = 1;
	//					mission_start_bmx_1();
	//					if (HAS_DEATHARREST_EXECUTED()) {
	//						mission_bmx_1_failed();
	//					}
	//					mission_cleanup_bmx_1();
	//				}
	//				if (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("landstalker"))) {
	//					PRINT_BIG("BMX_2", 15000, 2);
	//					mission_set = 2;
	//					mission_start_bmx_2();
	//					if (HAS_DEATHARREST_EXECUTED()) {
	//						mission_bmx_2_failed();
	//					}
	//					mission_cleanup_bmx_2();
	//				}
	//			}
	//			if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
	//				if (!IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
	//					bmx_1_trigger = 0;
	//				}
	//			}
	//		}
	//	}
	//}
}