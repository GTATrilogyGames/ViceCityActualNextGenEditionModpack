#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"

#include "car_seats.h"		/*rebusx: чтобы определять ближайшее к пассажиру пасс. место*/


#define CONTROLLER_DPAD_UP	8


int blip1_ct1, blip2_ct1, spray_blip_onscreen;
int taxi_car1, taxi_countdown_already_started;
int taxi_ped1, taxi_passed_this_shot, taxi_fucked_flag;
int taxi_countdown, taxi_score, TimeForFareMS_int, reward_base;
int taxi_finish_time, taxi_start_time, total_taxi_time_taken; 
int score_for_this_fare, speedbonus, in_a_row_cash, in_a_row_number;

int sp_bonus_countdown;	/*rebusx*/
Ped prev_passenger = 0;

float WMOCAestx1, WMOCAesty1, WMOCAestz1;
	/*rebusx: чтобы запоминать выбранное местоположение*/
float WMOCAestx_prev = 0.0;
float WMOCAesty_prev = 0.0;
float WMOCAestz_prev = 0.0;

float taxi_blipx, taxi_blipy, taxi_blipz;
float taxi_ped_x, taxi_ped_y, taxi_ped_z;
float x_diff, y_diff, x_diff_sq, y_diff_sq, TimeForFareMS; 
int fon, textur, max_peds_in_car, spray_taxi, been_in_taxi1_before, intaxi, animpld;
int first_passeng_done;
int dm, cdm, wl;



/*rebusx: область поиска пассажиров*/
#define SEARCH_AREA_X		50.0
#define SEARCH_AREA_Y		50.0
#define SEARCH_AREA_Z		30.0

/*rebusx: область вокруг назначенного пассажира для появления подсказки*/
#define HELP_AREA_X		25.0
#define HELP_AREA_Y		25.0
#define HELP_AREA_Z		10.0


void main(void);

int set_next_passenger(void);

void setup_draw_text(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.156, 0.267);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
}

void setup_draw_text2(int r, int g, int b, float scale_1, float scale_2)
{
	SET_TEXT_COLOUR(r, g, b, 255); // задаём цвет текста
	SET_TEXT_SCALE(scale_1, scale_2); // размеры шрифта
	SET_TEXT_EDGE(1, 0, 0, 0, 255); //
	SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
	SET_TEXT_CENTRE(1); // задаём центр текста
}

void setup_draw_value(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.26, 0.445);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
}

void cleanup_and_terminate(void) {
	REMOVE_BLIP(blip1_ct1);
	REMOVE_BLIP(blip2_ct1);
	RELEASE_TEXTURE(fon);
	REMOVE_TXD(textur);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&taxi_ped1);
	MARK_CAR_AS_NO_LONGER_NEEDED(&taxi_car1);
	CLEAR_HELP();
	CLEAR_PRINTS();	/*rebusx*/

	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		setup_draw_text2(95, 195, 247, 0.5, 0.7);
		DISPLAY_TEXT(0.5, 0.5, "TAXI6");// пишем "Миссия завершина"

		setup_draw_text2(30, 215, 135, 0.5, 0.7);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.4, "TSCORE", taxi_score);//

		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
		SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	}
	TERMINATE_THIS_SCRIPT();
	//main();
}

void taxi_ped_leave2(void) {
	WAIT(0);
	if ( (!IS_CHAR_DEAD(taxi_ped1)) && (!IS_CAR_DEAD(taxi_car1)) && (!IS_CHAR_IN_CAR(taxi_ped1, taxi_car1)) )
	{
		TASK_WANDER_STANDARD(taxi_ped1);
		MARK_CHAR_AS_NO_LONGER_NEEDED(&taxi_ped1);
	}
	if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
		SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	}
}

void mission_taxi1_failed(void) {
	if (G_TAXI == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
	}
	if ( (!IS_CHAR_DEAD(taxi_ped1)) && (!IS_CAR_DEAD(taxi_car1)) )
	{
		TASK_LEAVE_CAR(taxi_ped1, taxi_car1);
		if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
			SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
		}
	}
	if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
		SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	}
	cleanup_and_terminate();
}

void current_passenger_byebye(void) {
	REMOVE_BLIP(blip1_ct1);
	REMOVE_BLIP(blip2_ct1);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&taxi_ped1);
	WAIT(0);
	/*PRINT_NOW("TAXI1", 1500, 1);*/
}

void taxi_fail_button_pressed(void) {
	while (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
		WAIT(0);
		if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
			mission_taxi1_failed();
			return;
		}
	}
	mission_taxi1_failed();
}

void taxi_fucked(void) {
	WAIT(0);
	PRINT_NOW("TAXI3", 5000, 1);
	if (!IS_CHAR_DEAD(taxi_ped1)) {
		TASK_FLEE_CHAR_ANY_MEANS(taxi_ped1, taxi_car1, 250.0, -1, 0, 0, 0, 25.0);
	}
	taxi_fucked_flag = 1;
	mission_taxi1_failed();
}

void taxi_out_of_time(void) {
	PRINT_NOW("TAXI2A", 5000, 1);
	mission_taxi1_failed();
}

void score(void)
{
	INCREMENT_INT_STAT(STAT_NUMBER_OF_TAXI_FARES_COMPLETED, 1);
	/*if (TIMERB() > speedbonus)*/
	if (sp_bonus_countdown == 0)
	{
		score_for_this_fare = reward_base / 10;
	}
	else
	{		/*бонус за скорость*/
		score_for_this_fare = reward_base / 8;
	}
	SETTIMERA(0); //сбрасываем таймер 

	/*rebusx: здесь изменил порядок кода, чтобы 1) пассажир сразу вылез и игрок получил управление 2) игроку дали деньги 3) надпись что заказ выполнен */

	taxi_score += score_for_this_fare;
	taxi_passed_this_shot++;
	/*taxi_countdown += 10000;*/	/*rebusx: перенёс в "ped_get_in()"*/
	if ( (!IS_CHAR_DEAD(taxi_ped1)) && (!IS_CAR_DEAD(taxi_car1)) )
	{
		TASK_LEAVE_CAR(taxi_ped1, taxi_car1);
		if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
			SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
		}
		while (IS_CHAR_IN_CAR(taxi_ped1, taxi_car1)) {
			WAIT(0);
			if ((IS_CHAR_DEAD(taxi_ped1)) || (IS_CAR_DEAD(taxi_car1))) {
				taxi_ped_leave2();
			}
			if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
				taxi_ped_leave2();
			}
			if (!IS_CHAR_IN_CAR(GetPlayerPed(), taxi_car1)) {
				taxi_ped_leave2();
			}
			if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
				taxi_ped_leave2();
			}
		}
	}
	if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
		SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	}
	ADD_SCORE(GetPlayerIndex(), score_for_this_fare);
	INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, score_for_this_fare);
	if (taxi_passed_this_shot == in_a_row_number)
	{
		ADD_SCORE(GetPlayerIndex(), in_a_row_cash);
		INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, in_a_row_cash);
	}
	MARK_CHAR_AS_NO_LONGER_NEEDED(&taxi_ped1);	/*rebusx: чтобы сразу начал уходить, иначе - стоит на месте до выхода из след. цикла*/
	//TASK_WANDER_STANDARD(taxi_ped1);
	while (true)
	{
		setup_draw_text2(30, 215, 135, 0.5, 0.7);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "TSCORE2", score_for_this_fare);//

		setup_draw_text2(95, 195, 247, 0.5, 0.7);

		if (TIMERB() > speedbonus)
		{
			DISPLAY_TEXT(0.5, 0.4, "TAXI4");// пишем "Миссия завершина"
		}
		else
		{		/*бонус за скорость*/
			DISPLAY_TEXT(0.5, 0.4, "TAXI5");// пишем "Миссия завершина"
		}
		if (taxi_passed_this_shot == in_a_row_number)
		{
			setup_draw_text2(30, 215, 135, 0.5, 0.7);
			DISPLAY_TEXT_WITH_2_NUMBERS(0.5, 0.3, "IN_ROW", taxi_passed_this_shot, in_a_row_cash);
		}
		
		WAIT( 0 );
		if (taxi_passed_this_shot == in_a_row_number)
		{
			if ( TIMERA() > 5000 )
			{
				break;
			}
		}
		else
		{
			if ( TIMERA() > 4000 )
			{
				break;
			}
		}
	}
	if ((taxi_passed_this_shot >= 25) && (G_TAXI == 0))
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
		G_GAME_PROGRESS += 1;
		SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
		PRINT_HELP("NITRO");//All taxi's now have a boost jump! Just press the horn button.
		G_TAXI = 1;
	}
	if (taxi_passed_this_shot == in_a_row_number)
	{
		taxi_score += in_a_row_cash;
		in_a_row_number += 5;
		in_a_row_cash += 500;
	}
	first_passeng_done = 1;
}


int set_dest(char *zone, char *print_str, float x, float y, float z)
{
	if (IS_CHAR_IN_ZONE(GetPlayerPed(), zone))
	{
		return -1;
	}
	WMOCAestx1 = x;	   
	WMOCAesty1 = y;
	WMOCAestz1 = z;
	int x_new = (int) x;
	int y_new = (int) y;
	int z_new = (int) z;
	int x_old = (int) WMOCAestx_prev;
	int y_old = (int) WMOCAesty_prev;
	int z_old = (int) WMOCAestz_prev;
	if (x_new == x_old && y_new == y_old && z_new == z_old)
	{
		return -1;
	}
	WMOCAestx_prev = x;
	WMOCAesty_prev = y;
	WMOCAestz_prev = z;
	PRINT_NOW(print_str, 5000, 1);
	return 0;
}

int choose_dest(int value)
{
	if ((IS_CHAR_IN_ZONE(GetPlayerPed(), "LTBAY")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "FRANI")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "CASGC")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "PORTU")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "STHBO")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "WILLI"))) {
		if (value == 1) {
			if (set_dest("LTBAY", "MFARE1", -246.1, 1726.5, 4.4) != 0)
			{
				return -1;
			}
		}
		else if (value == 2) {
			if (set_dest("FRANI", "MFARE2", -1024.7, -292.1, 8.1) != 0)
			{
				return -1;
			}
		}
		else if (value == 3) {
			if (set_dest("STHBO", "WFARE3", -576.0, -347.9, 6.9) != 0)
			{
				return -1;
			}
		}
		else if (value == 4) {
			if (set_dest("WILLI", "WFARE4", -585.4, 728.9, 5.1) != 0)
			{
				return -1;
			}
		}
		else if (value == 5) {
			if (set_dest("STHBO", "WFARE5", -538.2, -144.2, 5.4) != 0)
			{
				return -1;
			}
		}
		else if (value == 6) {
			if (set_dest("LTBAY", "WFARE6", -167.6, 1200.3, 4.9) != 0)
			{
				return -1;
			}
		}
		else if (value == 7) {
			if (set_dest("STHBO", "WFARE7", -432.6, -144.0, 5.0) != 0)
			{
				return -1;
			}
		}
		else if (value == 8) {
			if (set_dest("LTBAY", "WFARE8", -228.7, 1288.7, 4.8) != 0)
			{
				return -1;
			}
		}
		else if (value == 9) {
			if (set_dest("LTBAY", "WFARE9", -367.4, 1700.8, 4.6) != 0)
			{
				return -1;
			}
		}
		else if (value == 10) {
			if (set_dest("STHBO", "WFARE10", -438.9, 66.2, 4.8) != 0)
			{
				return -1;
			}
		}
		else if (value == 11) {
			if (set_dest("LTBAY", "WFARE11", -591.6, 1865.8, 2.4) != 0)
			{
				return -1;
			}
		}
		else if (value == 12) {
			if (set_dest("WILLI", "WFARE12", -631.6, 617.0, 5.2) != 0)
			{
				return -1;
			}
		}
		else if (value == 13) {
			if (set_dest("LTBAY", "WFARE13", -445.6, 1328.7, 5.0) != 0)
			{
				return -1;
			}
		}
		else if (value == 14) {
			if (set_dest("PORTU", "WFARE14", -312.0, -731.0, 5.1) != 0)
			{
				return -1;
			}
		}
		else if (value == 15) {
			if (set_dest("WILLI", "WFARE15", -417.6, 441.4, 5.1) != 0)
			{
				return -1;
			}
		}
	} else {
		if (value == 1) {
			if (set_dest("MIDPA", "FARE1", 533.7, -943.8, 4.4) != 0)
			{
				return -1;
			}
		}
		else if (value == 2) {
			if (set_dest("STARJ", "FARE2", 938.8, 440.9, 4.4) != 0)
			{
				return -1;
			}
		}
		else if (value == 3) {
			if (set_dest("MIDPA", "FARE3", 189.7, -768.8, 1.9) != 0)
			{
				return -1;
			}
		}
		else if (value == 4) {
			if (set_dest("MIDPA", "FARE4", 380.5, -948.7, 3.1) != 0)
			{
				return -1;
			}
		}
		else if (value == 5) {
			if (set_dest("THTRI", "FARE5", 634.6, 42.7, 5.3) != 0)
			{
				return -1;
			}
		}
		else if (value == 6) {
			if (set_dest("STARJ", "FARE6", 916.3, 1657.3, 10.4) != 0)
			{
				return -1;
			}
		}
		else if (value == 7) {
			if (set_dest("STARJ", "FARE7", 827.8, 736.8, 4.9) != 0)
			{
				return -1;
			}
		}
		else if (value == 8) {
			if (set_dest("MIDPA", "FARE8", 915.3, -685.7, 4.7) != 0)
			{
				return -1;
			}
		}
		else if (value == 9) {
			if (set_dest("THTRI", "FARE9", 1033.0, -85.2, 6.2) != 0)
			{
				return -1;
			}
		}
		else if (value == 10) {
			if (set_dest("STARJ", "FARE10", 1169.2, 1026.1, 5.9) != 0)
			{
				return -1;
			}
		}
		else if (value == 11) {
			if (set_dest("MIDPA", "FARE11", 334.7, -442.7, 4.4) != 0)
			{
				return -1;
			}
		}
		else if (value == 12) {
			if (set_dest("STARJ", "FARE12", 864.1, 1238.3, 5.4) != 0)
			{
				return -1;
			}
		}
		else if (value == 13) {
			if (set_dest("THTRI", "FARE13", 836.9, 66.5, 4.1) != 0)
			{
				return -1;
			}
		}
		else if (value == 14) {
			if (set_dest("STARJ", "FARE14", 953.7, 1040.5, 5.1) != 0)
			{
				return -1;
			}
		}
		else if (value == 15) {
			if (set_dest("STARJ", "FARE15", 866.0, 601.1, 5.0) != 0)
			{
				return -1;
			}
		}
	}
	return 0;
}

void set_time(void)
{
	x_diff = taxi_ped_x - taxi_blipx;
	y_diff = taxi_ped_y - taxi_blipy;
	x_diff_sq = x_diff * x_diff;
	y_diff_sq = y_diff * y_diff;
	TimeForFareMS = SQRT(x_diff_sq + y_diff_sq);
	TimeForFareMS_int = ((float) TimeForFareMS) / 3;	/*rebusx: подстройка времени на поездку*/
	reward_base = TimeForFareMS_int;
	
	int multiplier = 150;
	TimeForFareMS_int *= multiplier;
	
	if (TimeForFareMS_int < 30000 || TimeForFareMS_int < 60000 || TimeForFareMS_int < 100000)
	{
		float x_diff_nosign = SQRT(x_diff*x_diff);
		float y_diff_nosign = SQRT(y_diff*y_diff);
		if (TimeForFareMS_int < 30000)
		{
			if (x_diff_nosign < y_diff_nosign)
			{
				x_diff = y_diff;
			}
			else if (y_diff_nosign < x_diff_nosign)
			{
				y_diff = x_diff;
			}
			x_diff *= 1.5;
			y_diff *= 1.5;
			x_diff_sq = x_diff * x_diff;
			y_diff_sq = y_diff * y_diff;
		}
		if (TimeForFareMS_int < 60000)
		{
			if (x_diff_nosign < y_diff_nosign)
			{
				x_diff = y_diff;
				x_diff_sq = x_diff * x_diff;
			}
			else if (y_diff_nosign < x_diff_nosign)
			{
				y_diff = x_diff;
				y_diff_sq = y_diff * y_diff;
			}
		}
		else if (TimeForFareMS_int < 100000)
		{
			if (x_diff_nosign < (y_diff_nosign / 2) )	/*rebusx: исключить случай очень острого треугольника*/
			{
				x_diff = y_diff / 2;
				x_diff_sq = x_diff * x_diff;
			}
			else if (y_diff_nosign < (x_diff_nosign / 2) )
			{
				y_diff = x_diff / 2;
				y_diff_sq = y_diff * y_diff;
			}
		}
		TimeForFareMS = SQRT(x_diff_sq + y_diff_sq);
		TimeForFareMS_int = ((float) TimeForFareMS) / 3;	/*rebusx: подстройка времени на поездку*/
		reward_base = TimeForFareMS_int;
		TimeForFareMS_int *= multiplier;
	}
	taxi_countdown += TimeForFareMS_int;
	
	/*speedbonus = ((TimeForFareMS_int / 100) * 65);*/
		/*rebusx: для скоростных поездок и уменьшенного времени пределы бонуса должны быть больше*/
	if (TimeForFareMS_int < 30000)
	{
		//speedbonus = ((TimeForFareMS_int / 100) * 83.5);	/*rebusx*/
		speedbonus = TimeForFareMS_int - 3000;
	}
	else if (TimeForFareMS_int < 60000)
	{
		//speedbonus = ((TimeForFareMS_int / 100) * 93.5);	/*rebusx*/
		speedbonus = TimeForFareMS_int - 3000;
	}
	else if (TimeForFareMS_int < 90000)
	{
		//speedbonus = ((TimeForFareMS_int / 100) * 95);	/*rebusx*/
		speedbonus = TimeForFareMS_int - 3000;
	}
	else if (TimeForFareMS_int < 120000)
	{
		//speedbonus = ((TimeForFareMS_int / 100) * 95);	/*rebusx*/
		speedbonus = TimeForFareMS_int - 5000;
	}
	else
	{
		//speedbonus = ((TimeForFareMS_int / 100) * 94.5);	/*rebusx*/
		speedbonus = TimeForFareMS_int - 7000;
	}
	sp_bonus_countdown = speedbonus;
	
	if (taxi_countdown <= 25000)
	{
		taxi_countdown += 10000;	/*rebusx: помощь, если выдало совсем мало времени на поездку (очень короткая поездка)*/
		sp_bonus_countdown += 4000;
	}
	else if (taxi_countdown < 60000)
	{
		taxi_countdown += 3000;
		sp_bonus_countdown += 1000;
	}
	
	SETTIMERB(0);
	if (taxi_countdown_already_started == 0) {
		taxi_countdown_already_started = 1;
	}
	if (taxi_countdown > 300000)	/*rebusx: предел 5 минут*/
	{
		taxi_countdown = 300000;
	}
	if (sp_bonus_countdown > 300000)	/*rebusx: предел 5 минут*/
	{
		sp_bonus_countdown = 300000;
	}
}

int passenger_destination() {
	WAIT(0);
	if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
		mission_taxi1_failed();
		return 1;
	}
	while(1)
	{
		GENERATE_RANDOM_INT_IN_RANGE(1, 16, &been_in_taxi1_before);
		if (choose_dest(been_in_taxi1_before) == 0)
		{
			break;
		}
	}
	ADD_BLIP_FOR_COORD(WMOCAestx1, WMOCAesty1, WMOCAestz1, &blip2_ct1);
	CHANGE_BLIP_SPRITE(blip2_ct1, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
	CHANGE_BLIP_COLOUR(blip2_ct1, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_SCALE(blip2_ct1, 0.6); // масштаб иконки на радаре
	CHANGE_BLIP_DISPLAY(blip2_ct1, 2);
	
	taxi_blipx = WMOCAestx1;	/*rebusx: этого присваивания не было, переменные были по 0*/
	taxi_blipy = WMOCAesty1;
	
	if (IS_CAR_DEAD(taxi_car1)) {
		mission_taxi1_failed();
		return 1;
	}
	set_time();
	while (true) {
		WAIT(0);
		if (TIMERC() >= 1000) {
			taxi_countdown -= 1000;
			if (sp_bonus_countdown > 0)
			{
				sp_bonus_countdown -= 1000;	/*rebusx*/
			}
			SETTIMERC(0);
		}
		DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		DRAW_SPRITE( fon, 0.8765625, 0.82547, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.		/*rebusx - для счётчика бонусного времени*/
		int timesec, timemin, seconds, minutesbyseconds;
		seconds = taxi_countdown / 1000;
		timemin = seconds / 60;
		minutesbyseconds = timemin * 60;
		timesec = seconds - minutesbyseconds;
		
		int b_timesec, b_timemin, b_seconds, b_minutesbyseconds;
		b_seconds = sp_bonus_countdown / 1000;	/*rebusx*/
		b_timemin = b_seconds / 60;
		b_minutesbyseconds = b_timemin * 60;
		b_timesec = b_seconds - b_minutesbyseconds;
		
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
		setup_draw_value();
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", timemin);// минуты
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
			/*rebusx: счётчик бонусного времени*/
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.81769260, "NF_STATUS_56");
		setup_draw_value();
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.80991482, "CP_TIME_ZERO", b_timemin);// минуты
		setup_draw_value();
		DISPLAY_TEXT(0.9203125, 0.80991482, "CP_TIME_SEP");
		setup_draw_value();
		SET_TEXT_CENTRE(1);
		if ( b_timesec > 9 )
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.80991482, "CP_TIME_NOZERO", b_timesec);// секунды
		}
		else
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.80991482, "CP_TIME_ZERO", b_timesec);// секунды
		}
		setup_draw_text();
		DISPLAY_TEXT(0.78815097, 0.73564852, "FARES");
		setup_draw_value();
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_NOZERO", taxi_passed_this_shot);
		DRAW_CHECKPOINT( WMOCAestx1, WMOCAesty1, WMOCAestz1, 5.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
		/*if ((LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), WMOCAestx1, WMOCAesty1, WMOCAestz1, 4.0, 4.0, 4.0, 1)) && (IS_CAR_STOPPED(taxi_car1)))*/
		float car_speed;
		GET_CAR_SPEED(taxi_car1, &car_speed);
		if ( LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), WMOCAestx1, WMOCAesty1, WMOCAestz1, 4.0, 4.0, 4.0, 1) && (car_speed < 0.5) )	/*rebusx: пассажир выходит без задержки */
		{
			break;
		}
		if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
			mission_taxi1_failed();
			return 1;
		}
		if (IS_CAR_DEAD(taxi_car1)) {
			mission_taxi1_failed();
			return 1;
		}
		if (!IS_CHAR_IN_CAR(GetPlayerPed(), taxi_car1)) {
			mission_taxi1_failed();
			return 1;
		}
		if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
			taxi_fail_button_pressed();
			return 1;
		}
		if (taxi_countdown <= 0) {
			taxi_out_of_time();
			return 1;
		}
		if ((IS_CAR_UPSIDEDOWN(taxi_car1)) && (IS_CAR_STOPPED(taxi_car1))) {
			taxi_fucked();
			return 1;
		}
	}
	return 0;
}


int ped_get_in_taxi(void) {
		/*rebusx: время на посадку*/
	if (taxi_countdown_already_started)
	{
		if (taxi_countdown < 20000)
		{
			taxi_countdown = 20000;
		}
		else
		{
			taxi_countdown += 10000;
		}
	}
	animpld = 0;
	int help_displayed = 0;
	while (1) {
		WAIT(0);
		if (first_passeng_done == 1) {
			if (TIMERC() >= 1000) {
				taxi_countdown -= 1000;
				SETTIMERC(0);
			}
		}
		if (!IS_CHAR_DEAD(taxi_ped1)) {
			/*if (TIMERA() > 1000) {
				TASK_TURN_CHAR_TO_FACE_CHAR(taxi_ped1, GetPlayerPed());
				SETTIMERA(0);
			}*/
			float car_speed;
			GET_CAR_SPEED(taxi_car1, &car_speed);
			/*if ( LOCATE_CHAR_IN_CAR_CHAR_3D(GetPlayerPed(), taxi_ped1, 7.0, 7.0, 2.0, 0) && IS_CAR_STOPPED(taxi_car1) )*/
			if ( LOCATE_CHAR_IN_CAR_CHAR_3D(GetPlayerPed(), taxi_ped1, 7.0, 7.0, 2.0, 0) && (car_speed < 0.7) )		/*rebusx: чтобы не тупил и сразу бежал к машине*/
			{
				CLEAR_CHAR_TASKS_IMMEDIATELY(taxi_ped1);
				MODIFY_CHAR_MOVE_STATE(taxi_ped1, 3);
				TASK_ENTER_CAR_AS_PASSENGER(taxi_ped1, taxi_car1, 8000, closest_pass_seat(taxi_ped1, taxi_car1));
				break;
			}
			else
			{
				/* rebusx: чтобы пассажир стоял и не дрыгался, пока мы не подъехали */
				TASK_STAND_STILL(taxi_ped1, 10);
				TASK_TURN_CHAR_TO_FACE_CHAR(taxi_ped1, GetPlayerPed());
			}
		}
		else {
			return 2;	/*перейти на этап - выбрать следующего пассажира*/
		}
		
		if ( (!help_displayed) && (TIMERA() > 3000) && LOCATE_CHAR_IN_CAR_CHAR_3D(GetPlayerPed(), taxi_ped1, HELP_AREA_X, HELP_AREA_Y, HELP_AREA_Z, 0) )
		{
			CLEAR_PRINTS();
			PRINT_HELP("TAXIH1");		/*rebusx*/
			help_displayed = 1;
		}
		DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		int timesec, timemin, seconds, minutesbyseconds;
		seconds = taxi_countdown / 1000;
		timemin = seconds / 60;
		minutesbyseconds = timemin * 60;
		timesec = seconds - minutesbyseconds;
		
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
		if (first_passeng_done == 1) {
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
		} else {
			setup_draw_value();
			//DISPLAY_TEXT(0.9018542, 0.76831852, "TAXNULL");
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT(0.9203125, 0.76954074, "TAXNULL");
		}
		setup_draw_text();
		DISPLAY_TEXT(0.78815097, 0.73564852, "FARES");
		setup_draw_value();
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_NOZERO", taxi_passed_this_shot);
		if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
			mission_taxi1_failed();
			return 1;
		}
		if (IS_CAR_DEAD(taxi_car1)) {
			mission_taxi1_failed();
			return 1;
		}
		if (!IS_CHAR_IN_CAR(GetPlayerPed(), taxi_car1)) {
			mission_taxi1_failed();
			return 1;
		}
		if (!LOCATE_CHAR_IN_CAR_CHAR_3D(GetPlayerPed(), taxi_ped1, SEARCH_AREA_X + 5, SEARCH_AREA_Y + 5, SEARCH_AREA_Z + 5, 0)) {
			return 2;	/*перейти на этап - выбрать следующего пассажира*/
		}
		if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
			taxi_fail_button_pressed();
			return 1;
		}
		if ((taxi_countdown_already_started == 1) && (taxi_countdown <= 0)) {
			mission_taxi1_failed();
			return 1;
		}
	}
	animpld = 0;
	while (!IS_CHAR_IN_CAR(taxi_ped1, taxi_car1)) {
		WAIT(0);
		DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		int timesec, timemin, seconds, minutesbyseconds;
		seconds = taxi_countdown / 1000;
		timemin = seconds / 60;
		minutesbyseconds = timemin * 60;
		timesec = seconds - minutesbyseconds;
		
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
		if (first_passeng_done == 1) {
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
		} else {
			setup_draw_value();
			//DISPLAY_TEXT(0.9018542, 0.76831852, "TAXNULL");
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT(0.9203125, 0.76954074, "TAXNULL");
		}
		setup_draw_text();
		DISPLAY_TEXT(0.78815097, 0.73564852, "FARES");
		setup_draw_value();
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_NOZERO", taxi_passed_this_shot);
		if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
			mission_taxi1_failed();
			return 1;
		}
		if (IS_CAR_DEAD(taxi_car1)) {
			mission_taxi1_failed();
			return 1;
		}
		if (IS_CHAR_DEAD(taxi_ped1)) {
			return 2;	/*перейти на этап - выбрать следующего пассажира*/
		}
		if (!IS_CHAR_IN_CAR(GetPlayerPed(), taxi_car1)) {
			mission_taxi1_failed();
			return 1;
		}
		if (!LOCATE_CHAR_IN_CAR_CHAR_3D(GetPlayerPed(), taxi_ped1, SEARCH_AREA_X + 5, SEARCH_AREA_Y + 5, SEARCH_AREA_Z + 5, 0)) {
			return 2;	/*перейти на этап - выбрать следующего пассажира*/
		}
		if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
			taxi_fail_button_pressed();
			return 1;
		}
		if ((taxi_countdown_already_started == 1) && (taxi_countdown <= 0)) {
			mission_taxi1_failed();
			return 1;
		}
		if (!LOCATE_CHAR_IN_CAR_CHAR_3D(GetPlayerPed(), taxi_ped1, 7.0, 7.0, 2.0, 0)) {
			/*ped_get_in_taxi();*/
			return -1;	/*rebusx: необходим перезапуск функции*/
		}
	}
	CLEAR_PRINTS();		/*rebusx - убрать надпись Ищите пассажиров */
	GET_CHAR_COORDINATES(taxi_ped1, &taxi_ped_x, &taxi_ped_y, &taxi_ped_z);
	REMOVE_BLIP(blip1_ct1);
	return 0;
}

int set_next_passenger(void) {
	/*PRINT_HELP("TAXIH1");*/		/*rebusx: перенёс в "ped_get_in_taxi()"*/
	PRINT_NOW("TAXI1", 60000, 1);
	SETTIMERA(0);					/*чтобы показывать надпись Ищите пассажиров не менее 3х секунд*/
	score_for_this_fare = 0;
	if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
		mission_taxi1_failed();
		return -1;
	}
	if (IS_CAR_DEAD(taxi_car1)) {
		mission_taxi1_failed();
		return -1;
	}
	if (!IS_CHAR_IN_CAR(GetPlayerPed(), taxi_car1)) {
		mission_taxi1_failed();
		return -1;
	}
	if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
		taxi_fail_button_pressed();
		return -1;
	}
	if ((taxi_countdown_already_started == 1) && (taxi_countdown <= 0)) {
		mission_taxi1_failed();
		return -1;
	}
	/*taxi_ped1 = -1;*/
	taxi_ped1 = 0;
	/*while (taxi_ped1 == -1) {*/
	while (taxi_ped1 == 0) {
		WAIT(0);
		float px, py, pz;
		GET_CHAR_COORDINATES(GetPlayerPed(), &px, &py, &pz);
		GET_RANDOM_CHAR_IN_AREA_OFFSET_NO_SAVE(px, py, pz, SEARCH_AREA_X, SEARCH_AREA_Y, SEARCH_AREA_Z, &taxi_ped1);
		/*if (taxi_ped1 != -1) {*/
		if (taxi_ped1 != 0) {
			if (prev_passenger != 0 && taxi_ped1 == prev_passenger)
			{
				MARK_CHAR_AS_NO_LONGER_NEEDED(&taxi_ped1);
				taxi_ped1 = 0;
				continue;
			}
			int ped_type;
			GET_PED_TYPE(taxi_ped1, &ped_type);
			if (ped_type == PED_TYPE_COP)		/*rebusx: копы не должны быть пассажирами*/
			{
				MARK_CHAR_AS_NO_LONGER_NEEDED(&taxi_ped1);
				taxi_ped1 = 0;
				continue;
			}
			SET_CHAR_AS_MISSION_CHAR(taxi_ped1);	/*rebusx*/
			float pedx, pedy, pedz;
			int pint;
			GET_CHAR_COORDINATES(taxi_ped1, &pedx, &pedy, &pedz);
			GET_INTERIOR_AT_COORDS(pedx, pedy, pedz, &pint);
			if (pint == 0) {
				prev_passenger = taxi_ped1;		/*rebusx: запомнить пассажира, чтобы не выбрать его же на след. поездку*/
				break;
			} else {
				MARK_CHAR_AS_NO_LONGER_NEEDED(&taxi_ped1);
				/*taxi_ped1 = -1;*/
				taxi_ped1 = 0;
			}
		}
	}
	ADD_BLIP_FOR_CHAR(taxi_ped1, &blip1_ct1);
	CHANGE_BLIP_COLOUR(blip1_ct1, 5);
	CHANGE_BLIP_SCALE(blip1_ct1, 0.77999990); // масштаб иконки на радаре
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(blip1_ct1, "TAXPSG");
	LOAD_CHAR_DECISION_MAKER(2, &dm);
	LOAD_COMBAT_DECISION_MAKER(3, &cdm);
	SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
	SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);
	SET_CHAR_DECISION_MAKER(taxi_ped1, dm);
	SET_COMBAT_DECISION_MAKER(taxi_ped1, cdm);
	SET_CHAR_STAY_IN_CAR_WHEN_JACKED(taxi_ped1, 1);
	SET_CHAR_RELATIONSHIP_GROUP(taxi_ped1, 23);
	SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(taxi_ped1, 0);
	SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(taxi_ped1, 0);
	SETTIMERC(0);
	return 0;
}

void mission_start_taxi1(void) {
	if (G_TAXI == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}
	taxi_countdown_already_started = 0;
	taxi_countdown = 0;
	taxi_passed_this_shot = 0;
	taxi_score = 0;
	taxi_ped1 = -1;
	taxi_fucked_flag = 0;
	in_a_row_number = 5;
	in_a_row_cash = 500;
	first_passeng_done = 0;
	LOAD_ADDITIONAL_TEXT("TAXI1", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	if (!IS_PLAYER_PLAYING(GetPlayerIndex())) {
		mission_taxi1_failed();
		return;
	}
	if (IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
		STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &taxi_car1);
	} else {
		mission_taxi1_failed();
		return;
	}
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		setup_draw_text2(30, 215, 135, 0.5, 0.6);
		DISPLAY_TEXT(0.5, 0.45, "TAXI_M");//

		WAIT( 0 );
		if ( TIMERA() > 3000 )
		{
			break;
		}
	}
	/*PRINT_NOW("TAXI1", 1500, 1);*/	/*rebusx: перенёс в "set_next_passenger()"*/
	WAIT(600);
}

void main(void) {
	mission_start_taxi1();
	while(1)
	{
		if (set_next_passenger() != 0)
		{
			break;
		}
		int ret_code;
		while(1)
		{
			ret_code = ped_get_in_taxi();
			if (ret_code != -1)
			{
				break;
			}
		}
		if (ret_code == 2)
		{
			current_passenger_byebye();
			continue;
		}
		if (ret_code == 1)
		{
			break;
		}
		if (passenger_destination() > 0)
		{
			break;
		}
		score();
		current_passenger_byebye();
	}
	cleanup_and_terminate();
}
