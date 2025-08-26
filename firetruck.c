#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"

/*rebusx: обозначения пасс. мест*/
#define PASS_SEAT_FRONT		0
#define PASS_SEAT_RL		1

#define CAR_FIRES_COUNT		50

#define FLAG_CAR_FIRE_EXT	10


#define CONTROLLER_DPAD_UP	8


bool fire_button_pressed = 0;
bool player_ignored = 0;

int onfire_car_blip;
int car_1, car_2, car_3;
int car_1_blip, car_2_blip, car_3_blip;
//int car_1_fire, car_2_fire, car_3_fire;
int car_1_flag, car_2_flag, car_3_flag;

int fires_count_car1, fires_count_car2, fires_count_car3;	/*rebusx*/

int onfire_ped_blip;
int ped_1, ped_2, ped_3, ped_4, ped_5, ped_6, ped_7, ped_8, ped_9;
int ped_1_blip, ped_2_blip, ped_3_blip, ped_4_blip, ped_5_blip, ped_6_blip, ped_7_blip, ped_8_blip, ped_9_blip;
int ped_1_flag, ped_2_flag, ped_3_flag, ped_4_flag, ped_5_flag, ped_6_flag, ped_7_flag, ped_8_flag, ped_9_flag;
int ped_1_fire, ped_2_fire, ped_3_fire, ped_4_fire, ped_5_fire, ped_6_fire, ped_7_fire, ped_8_fire, ped_9_fire;

int time, time_left;
float time_float;
int fires_extinguished;
int fires_extinguished_this_round;
int fires_to_extinguish;
int mission_level;
int intermediate_int;
int score;
int total_score;

int fail_flag;

int onfire_car_health;

int random_car_model, players_car;
int players_car_health;
float players_distance_from_fire;

//int game_timer;
float time_divider;
int displayed_timer, displayed_counter;
//int car_health_test_timer;

float random_car_heading;
float fire1_x, fire1_y, fire2_x, fire2_y, fire3_x, fire3_y, fire4_x, fire4_y, fire5_x, fire5_y;
float car1_x, car1_y, car1_z, car2_x, car2_y, car2_z, car3_x, car3_y, car3_z;
float dx, dy, temp_x, temp_y, temp_xy, sum_x_y_temp;
float objx, objy, objz;
float player_x, player_y, player_z;
float x, y, z;

int objtemp, fon, textur, inftk;


int car_model_hashes[50];

void init_car_model_hashes()
{
	car_model_hashes[0] = MODEL_BANSHEE;	/*2-дверные*/
	car_model_hashes[1] = MODEL_BENSON;
	car_model_hashes[2] = MODEL_BLISTA;
	car_model_hashes[3] = MODEL_BOBCAT;
	car_model_hashes[4] = MODEL_BOXVILLE;
	car_model_hashes[5] = MODEL_BUCCANEER;
	car_model_hashes[6] = MODEL_COMET;
	car_model_hashes[7] = MODEL_COQUETTE;
	car_model_hashes[8] = MODEL_EMPEROR;
	car_model_hashes[9] = MODEL_EMPEROR2;
	car_model_hashes[10] = MODEL_ESPERANTO;
	car_model_hashes[11] = MODEL_FACTION;
	car_model_hashes[12] = MODEL_FXT;
	car_model_hashes[13] = MODEL_HABANERO;
	car_model_hashes[14] = MODEL_INFERNUS;
	car_model_hashes[15] = MODEL_MULE;
	car_model_hashes[16] = MODEL_PHANTOM;
	car_model_hashes[17] = MODEL_REBLA;
	car_model_hashes[18] = MODEL_RANCHER;
	car_model_hashes[19] = MODEL_RUINER;
	car_model_hashes[20] = MODEL_SUPERGT;
	car_model_hashes[21] = MODEL_TRASH;
	car_model_hashes[22] = MODEL_TURISMO;
	car_model_hashes[23] = MODEL_VIRGO;
	car_model_hashes[24] = MODEL_YANKEE;
	car_model_hashes[25] = MODEL_STALION;
	car_model_hashes[26] = MODEL_ADMIRAL;	/*4-дверные*/
	car_model_hashes[27] = MODEL_BURRITO;
	car_model_hashes[28] = MODEL_BURRITO2;
	car_model_hashes[29] = MODEL_CABBY;
	car_model_hashes[30] = MODEL_FORTUNE;
	car_model_hashes[31] = MODEL_INGOT;
	car_model_hashes[32] = MODEL_LANDSTALKER;
	car_model_hashes[33] = MODEL_MERIT;
	car_model_hashes[34] = MODEL_MOONBEAM;
	car_model_hashes[35] = MODEL_PATRIOT;
	car_model_hashes[36] = MODEL_STRATUM;
	car_model_hashes[37] = MODEL_PINNACLE;
	car_model_hashes[38] = MODEL_PMP600;
	car_model_hashes[39] = MODEL_PONY;
	car_model_hashes[40] = MODEL_SENTINEL;
	car_model_hashes[41] = MODEL_STEED;
	car_model_hashes[42] = MODEL_STRETCH;
	car_model_hashes[43] = MODEL_SULTANRS;
	car_model_hashes[44] = MODEL_TAXI;
	car_model_hashes[45] = MODEL_TAXI2;
	car_model_hashes[46] = MODEL_VIGERO;
	car_model_hashes[47] = MODEL_VIGERO2;
	car_model_hashes[48] = MODEL_WASHINGTON;
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

void setup_draw_title()
{
	SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
	SET_TEXT_EDGE(1, 0, 0, 0, 255); //
	SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
	SET_TEXT_CENTRE(1); // задаём центр текста
}


void start_next_round(void);

void clean_up_car(int car)
{
	if (!IS_CAR_DEAD(car)) {
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(car, 0);
		EXPLODE_CAR(car, 1, 0);
	}
}

void car_not_needed(int *car)
{
	MARK_CAR_AS_NO_LONGER_NEEDED(car);
	if (!IS_CAR_DEAD(*car)) {
		SET_CAR_ONLY_DAMAGED_BY_PLAYER(*car, 0);
	}
}

void clean_up_ped(Ped *ped)
{
	if (!IS_CHAR_DEAD(*ped)) {
		SET_CHAR_ONLY_DAMAGED_BY_PLAYER(*ped, 0);
		EXPLODE_CHAR_HEAD(*ped);
	}
	if (*ped != INVALID_HANDLE)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(ped);
	}
}

void remove_blips()
{
	REMOVE_BLIP(onfire_car_blip);
	REMOVE_BLIP(car_1_blip);
	REMOVE_BLIP(car_2_blip);
	REMOVE_BLIP(car_3_blip);
	REMOVE_BLIP(onfire_ped_blip);
	REMOVE_BLIP(ped_1_blip);
	REMOVE_BLIP(ped_2_blip);
	REMOVE_BLIP(ped_3_blip);
	REMOVE_BLIP(ped_4_blip);
	REMOVE_BLIP(ped_5_blip);
	REMOVE_BLIP(ped_6_blip);
	REMOVE_BLIP(ped_7_blip);
	REMOVE_BLIP(ped_8_blip);
	REMOVE_BLIP(ped_9_blip);
}

void mission_end(void) {
	if (G_FIRE == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
	}
	//PRINT_BIG("F_FAIL1", 5000, 5);
	//PRINT_WITH_NUMBER_BIG("TSCORE", total_score, 6000, 6);
	SET_WANTED_MULTIPLIER(1.0);
	remove_blips();
	clean_up_ped(&ped_1);
	clean_up_ped(&ped_2);
	clean_up_ped(&ped_3);
	clean_up_ped(&ped_4);
	clean_up_ped(&ped_5);
	clean_up_ped(&ped_6);
	clean_up_ped(&ped_7);
	clean_up_ped(&ped_8);
	clean_up_ped(&ped_9);
	clean_up_car(car_1);
	clean_up_car(car_2);
	clean_up_car(car_3);
	MARK_MODEL_AS_NO_LONGER_NEEDED(random_car_model);
	RELEASE_TEXTURE(fon);
	REMOVE_TXD(textur);
	SET_MAX_WANTED_LEVEL(6);
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		setup_draw_title();
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		DISPLAY_TEXT(0.5, 0.4, "F_FAIL1");// пишем "Миссия завершина"

		setup_draw_title();
		SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "TSCORE", total_score);//
		
		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	WAIT( 100 );
	TERMINATE_THIS_SCRIPT();
	//main();
}

void round_passed(void) {
	//PRINT_BIG("F_PASS1", 5000, 5);
	score = mission_level * mission_level;
	score *= 50;
	total_score += score;
	//PRINT_WITH_NUMBER_BIG("F_REWD", score, 6000, 6);
	ADD_SCORE(GetPlayerIndex(), score);
	INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, score);

	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		setup_draw_title();
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		DISPLAY_TEXT(0.5, 0.4, "F_PASS1");// пишем "Миссия завершина"

		setup_draw_title();
		SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "F_REWD", score);//
		
		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	if (mission_level > 11) {
		if (G_FIRE == 0) {		// если пройдешь все уровни в первый раз, то покажет сообщение
			INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
			G_GAME_PROGRESS += 1;
			SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
			G_FIRE = 1;
			//MAKE_PLAYER_FIRE_PROOF(GetPlayerIndex(), 1);
			PRINT_HELP("FIREPRO");
		}
	}
	remove_blips();
	car_not_needed(&car_1);
	car_not_needed(&car_2);
	car_not_needed(&car_3);
		/*rebusx: будут помечены сразу после тушения*/
	/*MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_1);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_2);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_3);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_4);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_5);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_6);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_7);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_8);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_9);*/
	MARK_MODEL_AS_NO_LONGER_NEEDED(random_car_model);
}

void ped_fire_extinguished(int *ped, int *ped_flag, int *ped_blip)
{
	REMOVE_BLIP(*ped_blip);
	if (displayed_counter == 0) {
		displayed_counter = 1;
	}
	fires_extinguished++;
	fires_extinguished_this_round++;
	PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );	/*rebusx*/
	*ped_flag = 2;
	MARK_CHAR_AS_NO_LONGER_NEEDED(ped);		/*rebusx: чтобы уходили (в режиме "ignore" без этого будут стоять на месте и ждать прекращения режима "ignore")*/
}

void do_fire_on_ped_bit(int *ped, int *ped_flag, int *ped_fire, int *ped_blip) {
	if (*ped_flag == 2)
	{
		return;
	}
	if (IS_CHAR_IN_ANY_CAR(*ped))
	{
		Vehicle car;
		GET_CAR_CHAR_IS_USING(*ped, &car);
		TASK_LEAVE_CAR(*ped, car);
	}
	if (!IS_CHAR_DEAD(*ped)) {
		if (*ped_flag == 0) {
			if (!IS_CHAR_IN_ANY_CAR(*ped)) {
				*ped_fire = START_CHAR_FIRE(*ped);
				ADD_BLIP_FOR_CHAR(*ped, ped_blip);
				CHANGE_BLIP_DISPLAY(*ped_blip, 2);
				*ped_flag = 1;
			}
		}
		if (*ped_flag == 1) {
			if (IS_SCRIPT_FIRE_EXTINGUISHED(*ped_fire)) {
				ped_fire_extinguished(ped, ped_flag, ped_blip);
			}
		}
	} else {
		if (IS_CHAR_IN_WATER(*ped)) {
			if (*ped_flag == 1) {
				REMOVE_SCRIPT_FIRE(*ped_fire);
				ped_fire_extinguished(ped, ped_flag, ped_blip);
			} else {
				PRINT_NOW("F_FAIL2", 5000, 1);
				fail_flag = 1;
				return;
			}
		} else {
			PRINT_NOW("F_FAIL2", 5000, 1);
			fail_flag = 1;
			return;
		}
	}
}

void car_fire_extinguished(int car, int car_blip, int *car_flag)
{
	REMOVE_BLIP(car_blip);
	SET_CAR_PROOFS(car, 0, 0, 0, 0, 0);
	//FREEZE_CAR_POSITION(car, 0);		/*rebusx*/
	TASK_EVERYONE_LEAVE_CAR(car);
	if (displayed_counter == 0) {
		displayed_counter = 1;
	}
	*car_flag = FLAG_CAR_FIRE_EXT;
	fires_extinguished++;
	fires_extinguished_this_round++;
	PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );	/*rebusx*/
}

void begin_car_fire(int car)
{
	SET_ENGINE_HEALTH(car, -1);
	START_CAR_FIRE(car);
}

void do_fire_on_car_bit(int car, int *car_flag, int *fires_count, int car_blip) {
	if (!IS_CAR_DEAD(car)) {
		if (IS_CAR_ON_FIRE(car)) {
			if (GET_PETROL_TANK_HEALTH(car) <= 200.0)
			{
				SET_PETROL_TANK_HEALTH(car, 500.0);
				SET_CAR_HEALTH(car, 1000);
			}
			if (GET_ENGINE_HEALTH(car) <= -700.0)
			{
				SET_ENGINE_HEALTH(car, -200.0);
				SET_CAR_HEALTH(car, 1000);
			}
		}
		else {
			if (*fires_count > 0)		/*rebusx: продлить тушение машины*/
			{
				*fires_count -= 1;
				begin_car_fire(car);
			}
			else if (!(*car_flag == FLAG_CAR_FIRE_EXT)) {
				car_fire_extinguished(car, car_blip, car_flag);
				SET_CAR_HEALTH(car, 1000);
				SET_ENGINE_HEALTH(car, 100.0);
				SET_PETROL_TANK_HEALTH(car, 100.0);
			}
		}
	} else {
		if (IS_CAR_IN_WATER(car)) {
			if (!(*car_flag == FLAG_CAR_FIRE_EXT)) {
				car_fire_extinguished(car, car_blip, car_flag);
			}
		} else {
			PRINT_NOW("F_FAIL2", 5000, 1);
			fail_flag = 1;
			return;
		}
	}
}

void do_cancelled_checks(void) {
	if (displayed_timer == 1) {
		if (time < 1) {
			PRINT_NOW("F_FAIL2", 5000, 1);
			fail_flag = 1;
			return;
		}
	}
	if (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("firetruk"))) {
		if (mission_level < 13)
		{
			PRINT_NOW("F_CANC", 3000, 1);
		}
		fail_flag = 1;
		return;
	}
	if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
		if (mission_level < 13)
		{
			PRINT_NOW("F_CANC", 3000, 1);
		}
		fail_flag = 1;
		WAIT(1000);
		return;
	}
}

int firefighter_mission_loop(void) {
	while (true) {
		WAIT(0);
		if (TIMERC() >= 1000) {
			time -= 1000;
			SETTIMERC(0);
		}
		DRAW_SPRITE(fon, 0.8765625, 0.7858, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
		int timemin, timesec, timetemp;
		timesec = time / 1000;
		timemin = timesec / 60;
		timetemp = timemin * 60;
		timesec -= timetemp;
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
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
		if (fail_flag == 1) {
			return 1;
		}
		//GET_GAME_TIMER(&game_timer);
		do_cancelled_checks();
		if (fail_flag == 1) {
			return 1;
		}

		//if ((timemin == 0) && (timesec < 1))
		//{
		//	PRINT_NOW("F_FAIL2", 5000, 1);
		//	return 1;
		//}
		
		if (car_1_flag != FLAG_CAR_FIRE_EXT)
		{
			do_fire_on_car_bit(car_1, &car_1_flag, &fires_count_car1, car_1_blip);
			if (ped_1 != INVALID_HANDLE)
			{
				WARP_CHAR_INTO_CAR(ped_1, car_1);
			}
			if (ped_2 != INVALID_HANDLE)
			{
				WARP_CHAR_INTO_CAR_AS_PASSENGER(ped_2, car_1, PASS_SEAT_FRONT);
			}
			if (ped_3 != INVALID_HANDLE)
			{
				WARP_CHAR_INTO_CAR_AS_PASSENGER(ped_3, car_1, PASS_SEAT_RL);
			}
		}
		else
		{
			if (mission_level >= 2 && ped_1 != INVALID_HANDLE) {
				do_fire_on_ped_bit(&ped_1, &ped_1_flag, &ped_1_fire, &ped_1_blip);
			}
			if (mission_level >= 3 && ped_2 != INVALID_HANDLE) {
				do_fire_on_ped_bit(&ped_2, &ped_2_flag, &ped_2_fire, &ped_2_blip);
			}
			if (mission_level >= 4 && ped_3 != INVALID_HANDLE) {
				do_fire_on_ped_bit(&ped_3, &ped_3_flag, &ped_3_fire, &ped_3_blip);
			}
		}
		if (car_2_flag != FLAG_CAR_FIRE_EXT)
		{
			if (mission_level >= 5) {
				do_fire_on_car_bit(car_2, &car_2_flag, &fires_count_car2, car_2_blip);
			}
			if (ped_4 != INVALID_HANDLE)
			{
				WARP_CHAR_INTO_CAR(ped_4, car_2);
			}
			if (ped_5 != INVALID_HANDLE)
			{
				WARP_CHAR_INTO_CAR_AS_PASSENGER(ped_5, car_2, PASS_SEAT_FRONT);
			}
			if (ped_6 != INVALID_HANDLE)
			{
				WARP_CHAR_INTO_CAR_AS_PASSENGER(ped_6, car_2, PASS_SEAT_RL);
			}
		}
		else
		{
			if (mission_level >= 6 && ped_4 != INVALID_HANDLE) {
				do_fire_on_ped_bit(&ped_4, &ped_4_flag, &ped_4_fire, &ped_4_blip);
			}
			if (mission_level >= 7 && ped_5 != INVALID_HANDLE) {
				do_fire_on_ped_bit(&ped_5, &ped_5_flag, &ped_5_fire, &ped_5_blip);
			}
			if (mission_level >= 8 && ped_6 != INVALID_HANDLE) {
				do_fire_on_ped_bit(&ped_6, &ped_6_flag, &ped_6_fire, &ped_6_blip);
			}
		}
		if (car_3_flag != FLAG_CAR_FIRE_EXT)
		{
			if (mission_level >= 9) {
				do_fire_on_car_bit(car_3, &car_3_flag, &fires_count_car3, car_3_blip);
			}
			if (ped_7 != INVALID_HANDLE)
			{
				WARP_CHAR_INTO_CAR(ped_7, car_3);
			}
			if (ped_8 != INVALID_HANDLE)
			{
				WARP_CHAR_INTO_CAR_AS_PASSENGER(ped_8, car_3, PASS_SEAT_FRONT);
			}
			if (ped_9 != INVALID_HANDLE)
			{
				WARP_CHAR_INTO_CAR_AS_PASSENGER(ped_9, car_3, PASS_SEAT_RL);
			}
		}
		else
		{
			if (mission_level >= 10 && ped_7 != INVALID_HANDLE) {
				do_fire_on_ped_bit(&ped_7, &ped_7_flag, &ped_7_fire, &ped_7_blip);
			}
			if (mission_level >= 11 && ped_8 != INVALID_HANDLE) {
				do_fire_on_ped_bit(&ped_8, &ped_8_flag, &ped_8_fire, &ped_8_blip);
			}
			if (mission_level >= 12 && ped_9 != INVALID_HANDLE) {
				do_fire_on_ped_bit(&ped_9, &ped_9_flag, &ped_9_fire, &ped_9_blip);
			}
		}
		if (fires_extinguished_this_round >= fires_to_extinguish) {
			break;
		}
	}
	return 0;
}

void add_ped_to_car(Ped *ped, Car car, bool as_driver, int seat_index)
{
	if (as_driver)
	{
		CREATE_RANDOM_CHAR_AS_DRIVER(car, ped);
	}
	else
	{
		CREATE_RANDOM_CHAR_AS_PASSENGER(car, seat_index, ped);
	}
	SET_CHAR_ONLY_DAMAGED_BY_PLAYER(*ped, 1);
	fires_to_extinguish++;
}

void setup_car(int car, int *car_blip, bool is_first_car, float firstcar_x, float firstcar_y)
{
	//SET_CAR_ENGINE_ON(car, 0, 1);
	begin_car_fire(car);
	if (is_first_car)
	{
		SET_CAR_HEADING(car, random_car_heading);
		//FREEZE_CAR_POSITION(car, 1);		/*rebusx*/
	}
	else
	{
		TURN_CAR_TO_FACE_COORD(car, firstcar_x, firstcar_y);
	}
	SET_CAR_ON_GROUND_PROPERLY(car);
	WAIT(0);
	GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(car, 0.0, 2.0, 0.3, &objx, &objy, &objz);
	SET_CAR_PROOFS(car, 1, 1, 1, 1, 1);
	ADD_BLIP_FOR_CAR(car, car_blip);
	CHANGE_BLIP_DISPLAY(*car_blip, 2);
	SET_UPSIDEDOWN_CAR_NOT_DAMAGED(car, 1);
	fires_to_extinguish++;
}

void create_car(int *car, float *car_x, float *car_y, float *car_z)
{
	temp_x = *car_x - 5.0;
	x = temp_x + 10.0;
	GENERATE_RANDOM_FLOAT_IN_RANGE(temp_x, x, car_x);
	temp_y = *car_y - 5.0;
	y = temp_y + 10.0;
	GENERATE_RANDOM_FLOAT_IN_RANGE(temp_y, y, car_y);
	CREATE_CAR(random_car_model, *car_x, *car_y, *car_z, car, 1);
	WAIT(0);
}

int next_fire(void) {
	do_cancelled_checks();
	if (fail_flag == 1) {
		return 2;
	}
	
	//IF flag_baron_mission2_passed = 0
		GENERATE_RANDOM_FLOAT_IN_RANGE(186.43, 1116.41, &car1_x);
		GENERATE_RANDOM_FLOAT_IN_RANGE(-1280.62, 1841.102, &car1_y);
	//ELSE
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1369.615, -985.473, 163.134, 2124.896, 0)) {
			GENERATE_RANDOM_FLOAT_IN_RANGE(-1369.615, 163.134, &car1_x);
			GENERATE_RANDOM_FLOAT_IN_RANGE(-985.473, 2124.896, &car1_y);
		} else {
			GENERATE_RANDOM_FLOAT_IN_RANGE(186.43, 1116.41, &car1_x);
			GENERATE_RANDOM_FLOAT_IN_RANGE(-1280.62, 1841.102, &car1_y);
		}
		
	if (mission_level < 5) {
		GET_CLOSEST_CAR_NODE(car1_x, car1_y, 5.0, &car1_x, &car1_y, &car1_z);
	}
	else if (mission_level < 9) {
		Vector3 car1_vec, car2_vec;
		int temp1, temp2;
		float temp3;
		GET_CLOSEST_ROAD(car1_x, car1_y, 5.0, 12.0, 1, &car1_vec, &car2_vec, &temp1, &temp2, &temp3);
		car1_x = car1_vec.x;
		car1_y = car1_vec.y;
		car1_z = car1_vec.z;
		car2_x = car2_vec.x;
		car2_y = car2_vec.y;
		car2_z = car2_vec.z;
		if ((car1_x == 0.0) && (car1_y == 0.0) && (car2_x == 0.0) && (car2_y == 0.0)) {
			WAIT(0);
			return 1;
		}
		dx = car2_x - car1_x;
		dy = car2_y - car1_y;
		temp_x = dx * dx;
		temp_y = dy * dy;
		temp_xy = temp_x + temp_y;
		temp_xy = SQRT(temp_xy);
		sum_x_y_temp = 12.0 / temp_xy;
		temp_x = dx * sum_x_y_temp;
		car2_x = car1_x + temp_x;
		temp_y = dy * sum_x_y_temp;
		car2_y = car1_y + temp_y;
		
		car1_z += 0.5;
		car2_z += 0.5;
	}
	else {
		Vector3 car2_vec, car3_vec;
		int temp1, temp2;
		float temp3;
		GET_CLOSEST_ROAD(car1_x, car1_y, 5.0, 18.0, 1, &car2_vec, &car3_vec, &temp1, &temp2, &temp3);
		car2_x = car2_vec.x;
		car2_y = car2_vec.y;
		car2_z = car2_vec.z;
		car3_x = car3_vec.x;
		car3_y = car3_vec.y;
		car3_z = car3_vec.z;
		if ((car2_x == 0.0) && (car2_y == 0.0) && (car3_x == 0.0) && (car3_y == 0.0)) {
			WAIT(0);
			return 1;
		}
		dx = car3_x - car2_x;
		dy = car3_y - car2_y;
		temp_x = dx * dx;
		temp_y = dy * dy;
		temp_xy = temp_x + temp_y;
		temp_xy = SQRT(temp_xy);
		sum_x_y_temp = 18.0 / temp_xy;
		temp_x = dx * sum_x_y_temp;
		car3_x = car2_x + temp_x;
		temp_y = dy * sum_x_y_temp;
		car3_y = car2_y + temp_y;
		
		car1_x = car2_x	- car3_x;
		car1_x = car1_x / 2.0;
		car1_x = car1_x	+ car3_x;
		
		car1_y = car2_y	- car3_y;
		car1_y = car1_y / 2.0;
		car1_y = car1_y	+ car3_y;
		
		car1_z = car2_z	- car3_z;
		car1_z = car1_z / 2.0;
		car1_z = car1_z	+ car3_z;
		
		car2_z += 0.5;
		car1_z += 0.5;
		car3_z += 0.5;
	}
	
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_x, &player_y, &player_z);
	GET_DISTANCE_BETWEEN_COORDS_2D(player_x, player_y, car1_x, car1_y, &players_distance_from_fire);

	if ( (car1_z < 2.0)
	|| ((players_distance_from_fire < 150.0) || (players_distance_from_fire > 600.0))
	|| ((car1_x > -1475.785) && (car1_x < -672.785) && (car1_y > 1278.678) && (car1_y < 2306.513))
	|| ((car1_x > 168.018) && (car1_x < 603.188) && (car1_y > 258.942) && (car1_y < 2222.059))
	|| ((car1_x > 597.191) && (car1_x < 692.713) && (car1_y > 346.926) && (car1_y < 1164.97))
	|| ((car1_x > -298.729) && (car1_x < 170.334) && (car1_y > 529.399) && (car1_y < 595.853))
	|| ((car1_x > 253.88) && (car1_x < 497.112) && (car1_y > 34.183) && (car1_y < 116.519))
	|| ((car1_x > -329.855) && (car1_x < 261.566) && (car1_y > -134.099) && (car1_y < 309.382)) )
	{
		WAIT(0);
		return 1;
	}
	time_left = time/3;
	time_float = players_distance_from_fire / time_divider;
	time_float = time_float * 1000.0;
	intermediate_int = time_float;
	time += intermediate_int;
	if (fires_extinguished == 0) {
		if (time < 50000) {
			time = 50000;
		}
	}
	time += time_left;
	if (time > 300000)
	{
		time = 300000;	/*rebusx*/
	}
	
	while (!HAS_MODEL_LOADED(random_car_model)) {
		WAIT(0);
		do_cancelled_checks();
		if (fail_flag == 1) {
			return 2;
		}
	}
	GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_car_heading);
	CREATE_CAR(random_car_model, car1_x, car1_y, car1_z, &car_1, 1);
	WAIT(0);
	setup_car(car_1, &car_1_blip, 1, car1_x, car1_y);
	if (mission_level >= 2)
	{
		add_ped_to_car(&ped_1, car_1, 1, 0);
	}
	if (mission_level >= 3) {
		add_ped_to_car(&ped_2, car_1, 0, PASS_SEAT_FRONT);
	}
	if (mission_level >= 4) {
		add_ped_to_car(&ped_3, car_1, 0, PASS_SEAT_RL);
	}
	if (mission_level >= 5) {
		create_car(&car_2, &car2_x, &car2_y, &car2_z);
		setup_car(car_2, &car_2_blip, 0, car1_x, car1_y);
	}
	if (mission_level >= 6) {
		add_ped_to_car(&ped_4, car_2, 1, 0);
	}
	if (mission_level >= 7) {
		add_ped_to_car(&ped_5, car_2, 0, PASS_SEAT_FRONT);
	}
	if (mission_level >= 8) {
		add_ped_to_car(&ped_6, car_2, 0, PASS_SEAT_RL);
	}
	if (mission_level >= 9) {
		create_car(&car_3, &car3_x, &car3_y, &car3_z);
		setup_car(car_3, &car_3_blip, 0, car1_x, car1_y);
	}
	MARK_MODEL_AS_NO_LONGER_NEEDED(random_car_model);
	if (mission_level >= 10) {
		add_ped_to_car(&ped_7, car_3, 1, 0);
	}
	if (mission_level >= 11) {
		add_ped_to_car(&ped_8, car_3, 0, PASS_SEAT_FRONT);
	}
	if (mission_level >= 12) {
		add_ped_to_car(&ped_9, car_3, 0, PASS_SEAT_RL);
	}

	//if (!IS_CHAR_DEAD(ped_1)) {
	if (!IS_CAR_DEAD(car_1)) {
		char* zonName = GET_NAME_OF_ZONE(car1_x, car1_y, car1_z);	
		if (mission_level < 5) {
			PRINT_STRING_IN_STRING_NOW("F_START", zonName, 5000, 1);
		} else {
			PRINT_STRING_IN_STRING_NOW("F_STAR1", zonName, 5000, 1);
		}
	}
	PRINT_WITH_NUMBER("FIRELVL", mission_level, 3000, 1);
	if (displayed_timer == 0) {
		displayed_timer = 1;
	}
	//GET_GAME_TIMER(&game_timer);
	//car_health_test_timer = game_timer + 3000;
	return 0;
}

void start_next_round(void) {
	fires_to_extinguish = 0;
	fires_extinguished_this_round = 0;
	
	fires_count_car1 = CAR_FIRES_COUNT;
	fires_count_car2 = CAR_FIRES_COUNT;
	fires_count_car3 = CAR_FIRES_COUNT;

	car_1_flag = 0;
	car_2_flag = 0;
	car_3_flag = 0;
	ped_1_flag = 0;
	ped_2_flag = 0;
	ped_3_flag = 0;
	ped_4_flag = 0;
	ped_5_flag = 0;
	ped_6_flag = 0;
	ped_7_flag = 0;
	ped_8_flag = 0;
	ped_9_flag = 0;
	//PRINT_WITH_NUMBER("FIRELVL", mission_level, 3000, 1);
	int random_int;
	if (mission_level <= 3)
	{
		GENERATE_RANDOM_INT_IN_RANGE(1, 49, &random_int);	/*rebusx: включая 2-дверные*/
	}
	else
	{
		GENERATE_RANDOM_INT_IN_RANGE(27, 49, &random_int);	/*rebusx: исключая 2-дверные*/
	}
	random_car_model = car_model_hashes[random_int - 1];
	REQUEST_MODEL(random_car_model);
}

void main(void) {
	if (G_FIRE == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}

	SET_MAX_WANTED_LEVEL(0);
	WAIT( 100 );
	
	LOAD_ADDITIONAL_TEXT("FIRETRK", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	time = 0;
	score = 0;
	displayed_timer = 0;
	fires_extinguished = 0;
	displayed_counter = 0;
	total_score = 0;
	time_divider = 5.5;
	fail_flag = 0;
	random_car_model = 0;
	intermediate_int = 0;
	players_car_health = 0;
	car_1 = -1;
	car_2 = -1;
	car_3 = -1;
	//car_health_test_timer = 0;
	
	init_car_model_hashes();
	
	ped_1_fire = 0;
	ped_2_fire = 0;
	ped_3_fire = 0;
	ped_4_fire = 0;
	ped_5_fire = 0;
	ped_6_fire = 0;
	ped_7_fire = 0;
	ped_8_fire = 0;
	ped_9_fire = 0;
	SET_WANTED_MULTIPLIER(0.5);
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT(0.5, 0.45, "FIRE_M");//

		WAIT( 0 );
		if ( TIMERA() > 3000 )
		{
			break;
		}
	}
	SET_EVERYONE_IGNORE_PLAYER(GetPlayerIndex(), 1);	/*rebusx: чуть более лучшая мера чтобы предотвратить злобность педов*/
	bool exit = 0;
	mission_level = 1;
	while (1)
	{
		start_next_round();
		while(1)
		{
			int ret_code = next_fire();
			if (ret_code == 1)
			{
				continue;
			}
			else if (ret_code == 2)
			{
				exit = 1;
				break;
			}
			break;
		}
		if (exit)
		{
			break;
		}
		if (firefighter_mission_loop() != 0)
		{
			break;
		}
		round_passed();
		mission_level++;
	}
	SET_EVERYONE_IGNORE_PLAYER(GetPlayerIndex(), 0);	/*rebusx*/
	mission_end();
}
