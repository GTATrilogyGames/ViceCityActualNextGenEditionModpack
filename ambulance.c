#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
#include "mission_passed.h"

#include "car_seats.h"		/*rebusx: чтобы определять ближайшее к пассажиру пасс. место*/
#include "peds_hashes.h"	/*rebusx: чтобы случайно выбирать педов (пациентов)*/


#define PED_STATE_WAITING			1
#define PED_STATE_GO_TO_CAR			2
#define PED_STATE_INSIDE_CAR		3
#define PED_STATE_GO_TO_HOSPITAL	4
#define PED_STATE_LEAVE_CAR_TIMEOUT	5


#define	CONTROLLER_DPAD_UP	8


int bonus_first_drive_message = 0;
int flag_rescued_message = 0;
int flag_rescued = 0;
int flag_got_in_car_message = 0;
int flag_got_in_car = 0;
int flag_show_title = 1;
int timeout_flag = 0;
int failed_flag = 0;
int car, time_limit, time_limit_temp, peds_created, peds_on_this_level, brackets_var;
int timemin, timesec, timetemp;
int car_health_last, car_health_now, time_drop, max_peds_in_car, peds_in_car, score_am, bonus_first_drive;
int saved_peds, hospital_blip, time_chunk, mission_level, time_chunk_in_secs;
int hospital_blip_flag, mission_end_button_pressed, car_health, saved_peds_total;
int ped_1, ped_1_blip, ped_1_state;
int ped_2, ped_2_blip, ped_2_state;
int ped_3, ped_3_blip, ped_3_state;
int ped_4, ped_4_blip, ped_4_state;
int ped_5, ped_5_blip, ped_5_state;
int ped_6, ped_6_blip, ped_6_state;
int ped_7, ped_7_blip, ped_7_state;
int ped_8, ped_8_blip, ped_8_state;
int ped_9, ped_9_blip, ped_9_state;
int ped_10, ped_10_blip, ped_10_state;
int ped_11, ped_11_blip, ped_11_state;
int ped_12, ped_12_blip, ped_12_state;
float random_x, random_y, hospital_x, hospital_y, hospital_z;
float player1_a_x, player1_a_y, player1_a_z, hospital_door_x, hospital_door_y;
float ped_coord_x, ped_coord_y, ped_coord_z, ped_heading;
float difference_x_float_a, difference_y_float_a, sum_difference_a_xy;
float players_distance_from_ped, peds_distance_from_hospital, time_limit_float, time_chunk_divider;
float random_ped_heading;
int fon, textur;
int hospital_ID;



void setup_draw_text() {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
	SET_TEXT_SCALE(0.156, 0.267);
	return;
}

void setup_draw_value() {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
	SET_TEXT_SCALE(0.26, 0.445);
	return;
}

void setup_heading_draw()
{
	SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
	SET_TEXT_EDGE(1, 0, 0, 0, 255); //
	SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
	SET_TEXT_CENTRE(1); // задаём центр текста
}

void clean_up_blips()
{
	hospital_blip_flag = 0;
	REMOVE_BLIP(hospital_blip);
	REMOVE_BLIP(ped_1_blip);
	REMOVE_BLIP(ped_2_blip);
	REMOVE_BLIP(ped_3_blip);
	REMOVE_BLIP(ped_4_blip);
	REMOVE_BLIP(ped_5_blip);
	REMOVE_BLIP(ped_6_blip);
	REMOVE_BLIP(ped_7_blip);
	REMOVE_BLIP(ped_8_blip);
	REMOVE_BLIP(ped_9_blip);
	REMOVE_BLIP(ped_10_blip);
	REMOVE_BLIP(ped_11_blip);
	REMOVE_BLIP(ped_12_blip);
}

void mission_end() {
	clean_up_blips();
	if (mission_level < 13) {
		if (G_MEDIC == 0)
		{
			INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
		}
		SETTIMERA(0); //сбрасываем таймер 
		while (true)
		{
			setup_heading_draw();
			SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
			DISPLAY_TEXT(0.5, 0.4, "A_FAIL1");// Paramedic mission ended.

			setup_heading_draw();
			SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "A_SAVES", saved_peds_total);// PEOPLE SAVED: ~1~
			
			WAIT( 0 );
			if ( TIMERA() > 4000 )
			{
				break;
			}
		}
	}
	CLEAR_PRINTS();
	SET_WANTED_MULTIPLIER(1.0);
	if (ped_1_state > 0)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_1);
	}
	if (ped_2_state > 0)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_2);
	}
	if (ped_3_state > 0)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_3);
	}
	if (ped_4_state > 0)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_4);
	}
	if (ped_5_state > 0)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_5);
	}
	if (ped_6_state > 0)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_6);
	}
	if (ped_7_state > 0)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_7);
	}
	if (ped_8_state > 0)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_8);
	}
	if (ped_9_state > 0)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_9);
	}
	if (ped_10_state > 0)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_10);
	}
	if (ped_11_state > 0)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_11);
	}
	if (ped_12_state > 0)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&ped_12);
	}
	TERMINATE_THIS_SCRIPT();
}

void add_timelimit() {
	time_limit_float = peds_distance_from_hospital / time_chunk_divider;
	time_limit_float = time_limit_float * 1000.0;
	time_limit_temp = ROUND(time_limit_float);
	time_limit += time_limit_temp;
	return;
}

void create_ped(Ped *ped, int *ped_state, int *ped_blip)
{
	//CREATE_RANDOM_CHAR(ped_coord_x, ped_coord_y, ped_coord_z, ped);	/*rebusx*/
	int randint;
	GENERATE_RANDOM_INT_IN_RANGE(PED_HASHES_MIN_INDEX, PED_HASHES_MAX_INDEX, &randint);
	REQUEST_MODEL(peds_hashes[randint]);
	while ( !HAS_MODEL_LOADED(peds_hashes[randint]) )
	{
		WAIT(0);
	}
	CREATE_CHAR(PED_TYPE_CIV_MALE, peds_hashes[randint], ped_coord_x, ped_coord_y, ped_coord_z, ped, 1);
	MARK_MODEL_AS_NO_LONGER_NEEDED(peds_hashes[randint]);
	*ped_state = PED_STATE_WAITING;
	SET_CHAR_BLEEDING(*ped, 1);
	SET_CHAR_ONLY_DAMAGED_BY_PLAYER(*ped, 1);
	GENERATE_RANDOM_FLOAT_IN_RANGE(0.0, 359.9, &random_ped_heading);
	SET_CHAR_HEADING(*ped, random_ped_heading);
	ADD_BLIP_FOR_CHAR(*ped, ped_blip);
	CHANGE_BLIP_SPRITE(*ped_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
	CHANGE_BLIP_COLOUR(*ped_blip, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_SCALE(*ped_blip, 0.6); // масштаб иконки на радаре
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(*ped_blip, "BL_VTAR");
}

void create_one_injured_ped() {
	if (peds_created == 0) {
		create_ped(&ped_1, &ped_1_state, &ped_1_blip);
	}
	else if (peds_created == 1) {
		create_ped(&ped_2, &ped_2_state, &ped_2_blip);
	}
	else if (peds_created == 2) {
		create_ped(&ped_3, &ped_3_state, &ped_3_blip);
	}
	else if (peds_created == 3) {
		create_ped(&ped_4, &ped_4_state, &ped_4_blip);
	}
	else if (peds_created == 4) {
		create_ped(&ped_5, &ped_5_state, &ped_5_blip);
	}	
	else if (peds_created == 5) {
		create_ped(&ped_6, &ped_6_state, &ped_6_blip);
	}	
	else if (peds_created == 6) {
		create_ped(&ped_7, &ped_7_state, &ped_7_blip);
	}
	else if (peds_created == 7) {
		create_ped(&ped_8, &ped_8_state, &ped_8_blip);
	}
	else if (peds_created == 8) {
		create_ped(&ped_9, &ped_9_state, &ped_9_blip);
	}
	else if (peds_created == 9) {
		create_ped(&ped_10, &ped_10_state, &ped_10_blip);
	}
	else if (peds_created == 10) {
		create_ped(&ped_11, &ped_11_state, &ped_11_blip);
	}
	else if (peds_created == 11) {
		create_ped(&ped_12, &ped_12_state, &ped_12_blip);
	}
}

void ped_die_no_fail(Ped *ped, int *ped_state)
{
	CLEAR_CHAR_TASKS_IMMEDIATELY(*ped);
	SET_CHAR_HEALTH(*ped, 100);
	DAMAGE_CHAR(*ped, 200, 0);
	*ped_state = 0;
	MARK_CHAR_AS_NO_LONGER_NEEDED(ped);
}

void all_peds_die_no_fail()
{
	if (ped_1_state > 0)
	{
		ped_die_no_fail(&ped_1, &ped_1_state);
	}
	if (ped_2_state > 0)
	{
		ped_die_no_fail(&ped_2, &ped_2_state);
	}
	if (ped_3_state > 0)
	{
		ped_die_no_fail(&ped_3, &ped_3_state);
	}
	if (ped_4_state > 0)
	{
		ped_die_no_fail(&ped_4, &ped_4_state);
	}
	if (ped_5_state > 0)
	{
		ped_die_no_fail(&ped_5, &ped_5_state);
	}
	if (ped_6_state > 0)
	{
		ped_die_no_fail(&ped_6, &ped_6_state);
	}
	if (ped_7_state > 0)
	{
		ped_die_no_fail(&ped_7, &ped_7_state);
	}
	if (ped_8_state > 0)
	{
		ped_die_no_fail(&ped_8, &ped_8_state);
	}
	if (ped_9_state > 0)
	{
		ped_die_no_fail(&ped_9, &ped_9_state);
	}
	if (ped_10_state > 0)
	{
		ped_die_no_fail(&ped_10, &ped_10_state);
	}
	if (ped_11_state > 0)
	{
		ped_die_no_fail(&ped_11, &ped_11_state);
	}
	if (ped_12_state > 0)
	{
		ped_die_no_fail(&ped_12, &ped_12_state);
	}
}

void ped_fail_checks(Ped *ped, int *ped_state)
{
	if (IS_CHAR_DEAD(*ped)) {
		PRINT_NOW("A_FAIL3", 3000, 1);//~r~The patient is dead!!
		failed_flag = 1;
		return;
	}
	if (timeout_flag)
	{
		if (IS_CHAR_IN_ANY_CAR(*ped)) {
			*ped_state = PED_STATE_LEAVE_CAR_TIMEOUT;	/*пед сидит внутри скорой, должен погибнуть выйдя из неё*/
		}
	}
}

void ped_inside_car(int *ped, int *ped_state)
{
	if (car_health_now < car_health_last) {
		PANIC_SCREAM(*ped);
	}
	float car_speed;
	GET_CAR_SPEED(car, &car_speed);	
	if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), hospital_x, hospital_y, hospital_z, 6.0, 6.0, 2.0, 1) && (car_speed < 0.5) ) {
		TASK_FOLLOW_NAV_MESH_TO_COORD(*ped, hospital_door_x, hospital_door_y, 5.0, 2, -2, 2.0);
		*ped_state = PED_STATE_GO_TO_HOSPITAL;
	}
}

void ped_waiting(int *ped, int *ped_state)
{
	float car_speed;
	GET_CAR_SPEED(car, &car_speed);
	if (LOCATE_CHAR_IN_CAR_CHAR_3D(GetPlayerPed(), *ped, 10.0, 10.0, 2.0, 0) && (car_speed < 0.5) )
	{
		GET_NUMBER_OF_PASSENGERS(car, &peds_in_car);
		GET_MAXIMUM_NUMBER_OF_PASSENGERS(car, &max_peds_in_car);
		if (peds_in_car < max_peds_in_car) {
			MODIFY_CHAR_MOVE_STATE(*ped, 3);
			TASK_ENTER_CAR_AS_PASSENGER(*ped, car, 8000, closest_free_seat(*ped, car));
			//SET_CHAR_KEEP_TASK(*ped, 1);
			*ped_state = PED_STATE_GO_TO_CAR;
		} else {
			PRINT_NOW("A_FULL", 5000, 1);//~r~Ambulance full!!
		}
		GET_CAR_HEALTH(car, &car_health_last);
	}
}

void ped_go_to_car(Ped *ped, int *ped_state, int *ped_blip)
{
	if (!LOCATE_CHAR_IN_CAR_CHAR_2D(GetPlayerPed(), *ped, 20.0, 20.0, 0))
	{
		*ped_state = PED_STATE_WAITING;
		CLEAR_CHAR_TASKS_IMMEDIATELY(*ped);
		return;
	}
	if (!IS_CHAR_IN_ANY_CAR(*ped))
	{
		if (IS_CHAR_STOPPED(*ped) && !IS_CHAR_GETTING_IN_TO_A_CAR(*ped))
		{
			*ped_state = PED_STATE_WAITING;
		}
		return;		/*rebusx: ждём когда сядет в машину*/
	}
	else
	{
		REMOVE_BLIP(*ped_blip);
		if (hospital_blip_flag == 0) {
			ADD_BLIP_FOR_COORD(hospital_x, hospital_y, hospital_z, &hospital_blip);
			CHANGE_BLIP_SPRITE(hospital_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
			CHANGE_BLIP_COLOUR(hospital_blip, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
			CHANGE_BLIP_SCALE(hospital_blip, 0.6); // масштаб иконки на радаре
			CHANGE_BLIP_NAME_FROM_TEXT_FILE(hospital_blip, "BL_HTAR");
			hospital_blip_flag = 1;
		}
		time_chunk_in_secs = time_chunk / 1000;
		//PRINT_WITH_NUMBER_BIG("A_TIME", time_chunk_in_secs, 6000, 6);
		flag_got_in_car_message = 1;
		flag_got_in_car = 1;
		time_limit += time_chunk;
		*ped_state = PED_STATE_INSIDE_CAR;
	}
}

void ped_go_to_hospital(Ped *ped, int *ped_state)
{
	TASK_FOLLOW_NAV_MESH_TO_COORD(*ped, hospital_door_x, hospital_door_y, 5.0, 4, -2, 2.0);
	if (!IS_CHAR_IN_ANY_CAR(*ped)) {
		TASK_FOLLOW_NAV_MESH_TO_COORD(*ped, hospital_door_x, hospital_door_y, 5.0, 4, -2, 2.0);
		MARK_CHAR_AS_NO_LONGER_NEEDED(ped);
		//PRINT_BIG("A_PASS", 3000, 5);
		saved_peds++;
		*ped_state = 0;
		flag_rescued = 1;
		flag_rescued_message = 1;
	}
}

void ped_leave_car_timeout(Ped *ped, int *ped_state)
{
	TASK_LEAVE_ANY_CAR(*ped);
	if (IS_CHAR_IN_ANY_CAR(*ped))
	{
		return;
	}
	CLEAR_CHAR_TASKS_IMMEDIATELY(*ped);
}

bool ped_exists_in_area(Ped ped, float x, float y)
{
	if (!IS_CHAR_DEAD(ped) && LOCATE_CHAR_ANY_MEANS_2D(ped, x, y, 25.0, 25.0, 0)) {
		return 1;
	}
	return 0;
}


void set_ped_coord(int index)
{
	if (hospital_ID == 1)
	{
		if (index == 1) ped_coord_x = 923.811, ped_coord_y = -919.996, ped_coord_z = 5.97117;
		else if (index == 2) ped_coord_x = 827.219, ped_coord_y = -650.829, ped_coord_z = 6.4127;
		else if (index == 3) ped_coord_x = 626.29, ped_coord_y = -1013.84, ped_coord_z = 5.05129;
		else if (index == 4) ped_coord_x = 688.354, ped_coord_y = -795.464, ped_coord_z = 5.0762;
		else if (index == 5) ped_coord_x = 1065.97, ped_coord_y = -455.46, ped_coord_z = 6.4036;
		else if (index == 6) ped_coord_x = 964.701, ped_coord_y = -255.723, ped_coord_z = 5.35095;
		else if (index == 7) ped_coord_x = 295.024, ped_coord_y = -974.772, ped_coord_z = 4.68987;
		else if (index == 8) ped_coord_x = 484.996, ped_coord_y = -797.292, ped_coord_z = 4.44671;
		else if (index == 9) ped_coord_x = 393.229, ped_coord_y = -731.118, ped_coord_z = 4.46614;
		else if (index == 10) ped_coord_x = 247.166, ped_coord_y = -761.82, ped_coord_z = 4.60268;
		else if (index == 11) ped_coord_x = 521.715, ped_coord_y = -561.78, ped_coord_z = 4.45144;
		else if (index == 12) ped_coord_x = 684.22, ped_coord_y = -371.024, ped_coord_z = 4.27023;
		else if (index == 13) ped_coord_x = 537.887, ped_coord_y = -367.725, ped_coord_z = 4.48077;
		else if (index == 14) ped_coord_x = 1224.04, ped_coord_y = -74.5884, ped_coord_z = 5.98257;
		else if (index == 15) ped_coord_x = 838.104, ped_coord_y = -225.178, ped_coord_z = 5.16346;
		else if (index == 16) ped_coord_x = 764.913, ped_coord_y = -209.047, ped_coord_z = 4.30302;
		else if (index == 17) ped_coord_x = 892.093, ped_coord_y = -113.437, ped_coord_z = 5.05121;
		else if (index == 18) ped_coord_x = 826.184, ped_coord_y = -57.3056, ped_coord_z = 4.25235;
		else if (index == 19) ped_coord_x = 1081.34, ped_coord_y = 131.599, ped_coord_z = 5.12246;
		else if (index == 20) ped_coord_x = 898.62, ped_coord_y = 182.397, ped_coord_z = 4.332;
		else if (index == 21) ped_coord_x = 922.743, ped_coord_y = 356.292, ped_coord_z = 4.30287;
		else if (index == 22) ped_coord_x = 776.019, ped_coord_y = 206.324, ped_coord_z = 6.85035;
		else if (index == 23) ped_coord_x = 756.857, ped_coord_y = 54.3952, ped_coord_z = 4.06698;
		else if (index == 24) ped_coord_x = 610.635, ped_coord_y = -160.882, ped_coord_z = 4.57049;
		else if (index == 25) ped_coord_x = 646.914, ped_coord_y = 257.568, ped_coord_z = 6.51108;
	}
	else if (hospital_ID == 2)
	{
		if (index == 1) ped_coord_x = 752.648, ped_coord_y = 421.194, ped_coord_z = 5.45509;
		else if (index == 2) ped_coord_x = 710.899, ped_coord_y = 544.288, ped_coord_z = 5.07854;
		else if (index == 3) ped_coord_x = 1136.33, ped_coord_y = 459.608, ped_coord_z = 4.23849;
		else if (index == 4) ped_coord_x = 1259.66, ped_coord_y = 636.814, ped_coord_z = 7.03638;
		else if (index == 5) ped_coord_x = 1035.28, ped_coord_y = 641.327, ped_coord_z = 4.55954;
		else if (index == 6) ped_coord_x = 1114.61, ped_coord_y = 858.713, ped_coord_z = 6.52719;
		else if (index == 7) ped_coord_x = 941.791, ped_coord_y = 447.431, ped_coord_z = 4.67415;
		else if (index == 8) ped_coord_x = 941.126, ped_coord_y = 564.105, ped_coord_z = 5.09433;
		else if (index == 9) ped_coord_x = 876.197, ped_coord_y = 612.779, ped_coord_z = 5.40029;
		else if (index == 10) ped_coord_x = 780.445, ped_coord_y = 708.142, ped_coord_z = 5.38029;
		else if (index == 11) ped_coord_x = 594.281, ped_coord_y = 780.775, ped_coord_z = 13.2247;
		else if (index == 12) ped_coord_x = 867.538, ped_coord_y = 775.104, ped_coord_z = 5.63656;
		else if (index == 13) ped_coord_x = 759.031, ped_coord_y = 870.569, ped_coord_z = 5.78397;
		else if (index == 14) ped_coord_x = 933.798, ped_coord_y = 887.301, ped_coord_z = 5.11666;
		else if (index == 15) ped_coord_x = 888.682, ped_coord_y = 1009.59, ped_coord_z = 5.7268;
		else if (index == 16) ped_coord_x = 1078.86, ped_coord_y = 1146.85, ped_coord_z = 5.42168;
		else if (index == 17) ped_coord_x = 609.391, ped_coord_y = 1245.38, ped_coord_z = 5.05562;
		else if (index == 18) ped_coord_x = 1225.07, ped_coord_y = 1150.26, ped_coord_z = 5.72548;
		else if (index == 19) ped_coord_x = 1132.49, ped_coord_y = 1497.29, ped_coord_z = 10.7951;
		else if (index == 20) ped_coord_x = 1226.05, ped_coord_y = 1634.52, ped_coord_z = 10.7967;
		else if (index == 21) ped_coord_x = 981.301, ped_coord_y = 1473.12, ped_coord_z = 10.6915;
		else if (index == 22) ped_coord_x = 725.015, ped_coord_y = 1569.70, ped_coord_z = 7.40398;
		else if (index == 23) ped_coord_x = 717.988, ped_coord_y = 1470.06, ped_coord_z = 17.5589;
		else if (index == 24) ped_coord_x = 800.197, ped_coord_y = 1803.90, ped_coord_z = 11.4194;
		else if (index == 25) ped_coord_x = 930.516, ped_coord_y = 1820.10, ped_coord_z = 11.28;
	}
	else if (hospital_ID == 3)
	{
		if (index == 1) ped_coord_x = -625.459, ped_coord_y = -136.108, ped_coord_z = 5.82727;
		else if (index == 2) ped_coord_x = -702.999, ped_coord_y = -50.6241, ped_coord_z = 5.39642;
		else if (index == 3) ped_coord_x = -601.002, ped_coord_y = -363.448, ped_coord_z = 7.94889;
		else if (index == 4) ped_coord_x = -357.754, ped_coord_y = -398.051, ped_coord_z = 4.65194;
		else if (index == 5) ped_coord_x = -529.746, ped_coord_y = -788.781, ped_coord_z = 5.92711;
		else if (index == 6) ped_coord_x = -554.159, ped_coord_y = 262.488, ped_coord_z = 4.75223;
		else if (index == 7) ped_coord_x = -437.838, ped_coord_y = 239.086, ped_coord_z = 5.15;
		else if (index == 8) ped_coord_x = -269.06, ped_coord_y = -781.531, ped_coord_z = 5.12134;
		else if (index == 9) ped_coord_x = -708.334, ped_coord_y = 194.679, ped_coord_z = 4.89604;
		else if (index == 10) ped_coord_x = -432.918, ped_coord_y = -775.978, ped_coord_z = 5.90186;
		else if (index == 11) ped_coord_x = -758.072, ped_coord_y = 86.4716, ped_coord_z = 5.03526;
		else if (index == 12) ped_coord_x = -696.734, ped_coord_y = -550.518, ped_coord_z = 8.94838;
		else if (index == 13) ped_coord_x = -392.799, ped_coord_y = -931.721, ped_coord_z = 5.85313;
		else if (index == 14) ped_coord_x = -408.992, ped_coord_y = 751.714, ped_coord_z = 3.65603;
		else if (index == 15) ped_coord_x = -327.537, ped_coord_y = 646.528, ped_coord_z = 5.19749;
		else if (index == 16) ped_coord_x = -490.496, ped_coord_y = 572.067, ped_coord_z = 4.74208;
		else if (index == 17) ped_coord_x = -557.567, ped_coord_y = 500.965, ped_coord_z = 4.72281;
		else if (index == 18) ped_coord_x = -586.919, ped_coord_y = 703.232, ped_coord_z = 5.20626;
		else if (index == 19) ped_coord_x = -746.713, ped_coord_y = 340.483, ped_coord_z = 5.5517;
		else if (index == 20) ped_coord_x = -711.912, ped_coord_y = 535.736, ped_coord_z = 5.35827;
		else if (index == 21) ped_coord_x = -590.734, ped_coord_y = 207.411, ped_coord_z = 4.93168;
		else if (index == 22) ped_coord_x = -412.511, ped_coord_y = 406.763, ped_coord_z = 5.08229;
		else if (index == 23) ped_coord_x = -678.339, ped_coord_y = 137.908, ped_coord_z = 4.72986;
		else if (index == 24) ped_coord_x = -464.183, ped_coord_y = -548.865, ped_coord_z = 8.94073;
		else if (index == 25) ped_coord_x = -698.945, ped_coord_y = -213.534, ped_coord_z = 5.87798;
	}
	else if (hospital_ID == 4)
	{
		if (index == 1) ped_coord_x = -442.464, ped_coord_y = 842.49, ped_coord_z = 5.35085;
		else if (index == 2) ped_coord_x = -634.73, ped_coord_y = 1197.39, ped_coord_z = 8.68612;
		else if (index == 3) ped_coord_x = -243.94, ped_coord_y = 1569.4, ped_coord_z = 5.42447;
		else if (index == 4) ped_coord_x = 102.684, ped_coord_y = 1665.631, ped_coord_z = 3.45122;
		else if (index == 5) ped_coord_x = -578.712, ped_coord_y = 1865.27, ped_coord_z = 3.80708;
		else if (index == 6) ped_coord_x = -134.423, ped_coord_y = 1193.03, ped_coord_z = 5.04565;
		else if (index == 7) ped_coord_x = -614.008, ped_coord_y = 1452.05, ped_coord_z = 3.95715;
		else if (index == 8) ped_coord_x = -396.799, ped_coord_y = 1058.67, ped_coord_z = 5.10368;
		else if (index == 9) ped_coord_x = -246.556, ped_coord_y = 1046.56, ped_coord_z = 5.13573;
		else if (index == 10) ped_coord_x = 58.3412, ped_coord_y = 1427.451, ped_coord_z = 5.11934;
		else if (index == 11) ped_coord_x = -247.675, ped_coord_y = 881.244, ped_coord_z = 5.14566;
		else if (index == 12) ped_coord_x = -23.3048, ped_coord_y = 1361.24, ped_coord_z = 5.1582;
		else if (index == 13) ped_coord_x = -1142.25, ped_coord_y = 1807.82, ped_coord_z = 2.84965;
		else if (index == 14) ped_coord_x = -233.077, ped_coord_y = 1945.38, ped_coord_z = 6.1113;
		else if (index == 15) ped_coord_x = -325.586, ped_coord_y = 1854.27, ped_coord_z = 5.7434;
		else if (index == 16) ped_coord_x = -104.118, ped_coord_y = 1633.62, ped_coord_z = 5.14563;
		else if (index == 17) ped_coord_x = -247.872, ped_coord_y = 1273.81, ped_coord_z = 5.18049;
		else if (index == 18) ped_coord_x = -447.291, ped_coord_y = 2005.35, ped_coord_z = 5.99437;
		else if (index == 19) ped_coord_x = -119.794, ped_coord_y = 1124.33, ped_coord_z = 5.14156;
		else if (index == 20) ped_coord_x = -138.298, ped_coord_y = 2063.91, ped_coord_z = 4.32398;
		else if (index == 21) ped_coord_x = -245.037, ped_coord_y = 1461.18, ped_coord_z = 5.41025;
		else if (index == 22) ped_coord_x = 144.905, ped_coord_y = 1632.471, ped_coord_z = 16.7335;
		else if (index == 23) ped_coord_x = 56.6032, ped_coord_y = 1890.381, ped_coord_z = 5.95253;
		else if (index == 24) ped_coord_x = -56.3163, ped_coord_y = 1866.03, ped_coord_z = 5.82305;
		else if (index == 25) ped_coord_x = -445.254, ped_coord_y = 1317.15, ped_coord_z = 5.05703;
	}
}


void generate_random_coord() {
	while (1) {
		WAIT(0);
		GET_CHAR_COORDINATES(GetPlayerPed(), &player1_a_x, &player1_a_y, &player1_a_z);
		SET_RANDOM_SEED(ROUND(player1_a_x * player1_a_y * player1_a_z));
		
		//if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
		if (((IS_CONTROL_JUST_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_JUST_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
			mission_end_button_pressed = 1;
		}		
		if (mission_end_button_pressed == 1) {
			if (!((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || !((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
				PRINT_NOW("A_CANC", 3000, 1);//~r~Paramedic mission cancelled!
				failed_flag = 1;
				return;
			}
		}	
		if (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("ambulance"))) {
			PRINT_NOW("A_CANC", 3000, 1);//~r~Paramedic mission cancelled!
			failed_flag = 1;
			return;
		}

		int random_cord_index;
		GENERATE_RANDOM_INT_IN_RANGE(1, 25, &random_cord_index);
		set_ped_coord(random_cord_index);

		GENERATE_RANDOM_FLOAT_IN_RANGE(0, 360, &random_ped_heading);

		difference_x_float_a = player1_a_x - ped_coord_x;
		difference_y_float_a = player1_a_y - ped_coord_y;
		difference_x_float_a = difference_x_float_a * difference_x_float_a;
		difference_y_float_a = difference_y_float_a * difference_y_float_a;
		sum_difference_a_xy = difference_x_float_a + difference_y_float_a;
		players_distance_from_ped = SQRT(sum_difference_a_xy);
		
		if (players_distance_from_ped < 120.0) {
			continue;
		}
		
		difference_x_float_a = hospital_x - ped_coord_x;
		difference_y_float_a = hospital_y - ped_coord_y;
		difference_x_float_a = difference_x_float_a * difference_x_float_a;
		difference_y_float_a = difference_y_float_a * difference_y_float_a;
		sum_difference_a_xy = difference_x_float_a + difference_y_float_a;
		peds_distance_from_hospital = SQRT(sum_difference_a_xy);
		
		if ( (peds_distance_from_hospital < 100.0)
		|| (ped_1_state > 0 && ped_exists_in_area(ped_1, ped_coord_x, ped_coord_y) )
		|| (ped_2_state > 0 && ped_exists_in_area(ped_2, ped_coord_x, ped_coord_y) )
		|| (ped_3_state > 0 && ped_exists_in_area(ped_3, ped_coord_x, ped_coord_y) )
		|| (ped_4_state > 0 && ped_exists_in_area(ped_4, ped_coord_x, ped_coord_y) )
		|| (ped_5_state > 0 && ped_exists_in_area(ped_5, ped_coord_x, ped_coord_y) )
		|| (ped_6_state > 0 && ped_exists_in_area(ped_6, ped_coord_x, ped_coord_y) )
		|| (ped_7_state > 0 && ped_exists_in_area(ped_7, ped_coord_x, ped_coord_y) )
		|| (ped_8_state > 0 && ped_exists_in_area(ped_8, ped_coord_x, ped_coord_y) )
		|| (ped_9_state > 0 && ped_exists_in_area(ped_9, ped_coord_x, ped_coord_y) )
		|| (ped_10_state > 0 && ped_exists_in_area(ped_10, ped_coord_x, ped_coord_y) )
		|| (ped_11_state > 0 && ped_exists_in_area(ped_11, ped_coord_x, ped_coord_y) ) )
		{
			continue;
		}
		break;
	}
	return;
}

void start_next_level();

int process_injured_ped(int *ped, int *ped_state, int *ped_blip)
{
	ped_fail_checks(ped, ped_state);
	if (failed_flag == 1) {
		return 1;
	}
	if (*ped_state == PED_STATE_INSIDE_CAR)
	{
		ped_inside_car(ped, ped_state);
	}
	else if (*ped_state == PED_STATE_WAITING)
	{
		ped_waiting(ped, ped_state);
	}
	else if (*ped_state == PED_STATE_GO_TO_CAR)
	{
		ped_go_to_car(ped, ped_state, ped_blip);
	}
	else if (*ped_state == PED_STATE_GO_TO_HOSPITAL)
	{
		ped_go_to_hospital(ped, ped_state);
	}
	else if (*ped_state == PED_STATE_LEAVE_CAR_TIMEOUT)
	{
		ped_leave_car_timeout(ped, ped_state);
	}
	return 0;
}

int no_passengers_in_car()
{
	if (IS_CAR_PASSENGER_SEAT_FREE(car, PASS_SEAT_FRONT) && IS_CAR_PASSENGER_SEAT_FREE(car, PASS_SEAT_RL) && IS_CAR_PASSENGER_SEAT_FREE(car, PASS_SEAT_RR))
	{
		return 1;
	}
	return 0;
}

void check_car_damaged_1()
{
	if (no_passengers_in_car())
	{
		return;
	}
	GET_CAR_HEALTH(car, &car_health_now);
}

void check_car_damaged_2()
{
	if (no_passengers_in_car())
	{
		return;
	}
	if (car_health_now < car_health_last) {
		time_drop = car_health_last - car_health_now;
		time_drop = time_drop * 50;
		time_limit -= time_drop;		
		if (time_limit < 0) {
			time_limit = 0;
		}
		car_health_last = car_health_now;
	}
}

void timeout()
{
	if (!IS_CAR_STOPPED(car))
	{
		SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
		while(!IS_CAR_STOPPED(car))
		{
			WAIT(2000);
		}
		SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	}
	if (no_passengers_in_car())
	{
		all_peds_die_no_fail();
		failed_flag = 1;
	}
}

int ambulance_loop() {
	if (mission_level == 1)
	{
		PRINT("ATUTOR2", 5000, 1);
		//PRINT_NOW("ATUTOR2", 3000, 1);
		SETTIMERA(0); //сбрасываем таймер 
	}	
	PRINT_WITH_NUMBER("ALEVEL", mission_level, 3000, 4);
	
	SETTIMERC(0);
	while (true) {
		WAIT(0);
		if (TIMERC() >= 1000) {
			time_limit -= 1000;
			SETTIMERC(0);
		}
		if (time_limit <= 0)
		{
			time_limit = 0;
		}
		timesec = time_limit / 1000;
		timemin = timesec / 60;
		timetemp = timemin * 60;
		timesec -= timetemp;
		if ((timemin == 0) && (timesec < 1))
		{
			timeout_flag = 1;
		}
		
		check_car_damaged_1();
		
		if (ped_1_state > 0) {
			if (process_injured_ped(&ped_1, &ped_1_state, &ped_1_blip))
			{
				return 1;
			}
		}
		if (ped_2_state > 0) {
			if (process_injured_ped(&ped_2, &ped_2_state, &ped_2_blip))
			{
				return 1;
			}
		}
		if (ped_3_state > 0) {
			if (process_injured_ped(&ped_3, &ped_3_state, &ped_3_blip))
			{
				return 1;
			}
		}
		if (ped_4_state > 0) {
			if (process_injured_ped(&ped_4, &ped_4_state, &ped_4_blip))
			{
				return 1;
			}
		}
		if (ped_5_state > 0) {
			if (process_injured_ped(&ped_5, &ped_5_state, &ped_5_blip))
			{
				return 1;
			}
		}
		if (ped_6_state > 0) {
			if (process_injured_ped(&ped_6, &ped_6_state, &ped_6_blip))
			{
				return 1;
			}
		}
		if (ped_7_state > 0) {
			if (process_injured_ped(&ped_7, &ped_7_state, &ped_7_blip))
			{
				return 1;
			}
		}
		if (ped_8_state > 0) {
			if (process_injured_ped(&ped_8, &ped_8_state, &ped_8_blip))
			{
				return 1;
			}
		}
		if (ped_9_state > 0) {
			if (process_injured_ped(&ped_9, &ped_9_state, &ped_9_blip))
			{
				return 1;
			}
		}
		if (ped_10_state > 0) {
			if (process_injured_ped(&ped_10, &ped_10_state, &ped_10_blip))
			{
				return 1;
			}
		}
		if (ped_11_state > 0) {
			if (process_injured_ped(&ped_11, &ped_11_state, &ped_11_blip))
			{
				return 1;
			}
		}
		if (ped_12_state > 0) {
			if (process_injured_ped(&ped_12, &ped_12_state, &ped_12_blip))
			{
				return 1;
			}
		}
		
		check_car_damaged_2();
		
		if (timeout_flag)
		{
			timeout();
			//if ((timemin == 0) && (timesec < 1)){
			if (failed_flag){
				PRINT_NOW("A_FAIL2", 3000, 1);//~r~Your lack of urgency has been fatal to the patient!
				return 1;
			}
		}
		else
		{
			setup_draw_text();	
			DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");//TIME:
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
		}
		
		DRAW_CHECKPOINT( hospital_x, hospital_y, hospital_z, 4.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
		DRAW_SPRITE(fon, 0.8765625, 0.7858, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);

		if ((mission_level == 1) && (TIMERA() < 3000) && flag_show_title)
		{
			SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT(0.5, 0.45, "AMBUL_M");//
		}
		else if (TIMERA() >= 3000)
		{
			flag_show_title = 0;
		}

		//if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
		if (((IS_CONTROL_JUST_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_JUST_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
			mission_end_button_pressed = 1;
		}		
		if (mission_end_button_pressed == 1) {
			if (!((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || !((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
				PRINT_NOW("A_CANC", 3000, 1);//~r~Paramedic mission cancelled!
				return 1;
			}
		}		
		if (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("ambulance"))) {
			PRINT_NOW("A_CANC", 3000, 1);//~r~Paramedic mission cancelled!
			return 1;
		}
		
		if (flag_rescued)
		{
			if (bonus_first_drive == 1) {
				STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &car);
				GET_CAR_HEALTH(car, &car_health);
				car_health += 100;
				SET_CAR_HEALTH(car, car_health);
				SET_ENGINE_HEALTH(car, car_health);
				time_chunk_in_secs = time_chunk / 1000;
				//PRINT_WITH_NUMBER_BIG("A_TIME", time_chunk_in_secs, 6000, 6);
				time_limit += time_chunk;
				bonus_first_drive = 0;
				bonus_first_drive_message = 1;
			}
		}
		
		if (flag_got_in_car_message)
		{
			SETTIMERA(0); //сбрасываем таймер 
			flag_got_in_car_message = 0;
		}
		if (flag_got_in_car && (TIMERA() < 3000))
		{
			setup_heading_draw();
			SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "A_TIME", time_chunk_in_secs);//
		}
		if (flag_got_in_car && (TIMERA() >= 3000))
		{
			flag_got_in_car = 0;
		}
		
		if (flag_rescued_message)
		{
			SETTIMERA(0); //сбрасываем таймер
			flag_rescued_message = 0;
		}
		if (flag_rescued && (saved_peds < peds_on_this_level) && (TIMERA() < 3000))
		{
			SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT(0.5, 0.4, "A_PASS");//Citizen Rescued!
			if (bonus_first_drive_message)
			{
				setup_heading_draw();
				SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
				DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "A_TIME", time_chunk_in_secs);//
			}
		}
		if (flag_rescued && (TIMERA() >= 3000))
		{
			flag_rescued = 0;
			bonus_first_drive_message = 0;
		}
		
		if (saved_peds >= peds_on_this_level) {
			score_am = mission_level * mission_level;
			score_am *= 50;
			//PRINT_WITH_NUMBER_BIG("A_REW", score_am, 6000, 6);
			SETTIMERA(0); //сбрасываем таймер 
			while (true)
			{
				setup_heading_draw();
				SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
				DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "A_REW", score_am);//REWARD $~1~
				
				SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
				SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
				SET_TEXT_EDGE(1, 0, 0, 0, 255); //
				SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
				SET_TEXT_CENTRE(1); // задаём центр текста
				DISPLAY_TEXT(0.5, 0.4, "A_PASS");//Citizen Rescued!

				WAIT( 0 );
				if ( TIMERA() > 3000 )
				{
					break;
				}
			}
			saved_peds_total += saved_peds;
			saved_peds = 0;
			peds_created = 0;
			ADD_SCORE(GetPlayerIndex(), score_am);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, score_am);
			clean_up_blips();
			break;
		}
	}
	return 0;
}

void set_hospital_coords(float x, float y, float z, float door_x, float door_y)
{
	hospital_x = x;
	hospital_y = y;
	hospital_z = z;
	hospital_door_x	= door_x;
	hospital_door_y = door_y;
}

void start_next_level() {
	STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &car);
	bonus_first_drive_message = 0;
	flag_rescued_message = 0;
	flag_rescued = 0;
	flag_got_in_car_message = 0;
	flag_got_in_car = 0;

	time_limit = 0;
	peds_on_this_level = mission_level;
	while (peds_created < peds_on_this_level) {
		generate_random_coord();
		if (failed_flag == 1) {
			return;
		}
		create_one_injured_ped();
		add_timelimit();
		peds_created++;
	}
	
	if (mission_level >= 4) {
		bonus_first_drive = 1;
	} else {
		bonus_first_drive = 0;
	}
	
	time_chunk = time_limit / peds_on_this_level;
	time_chunk /= 2;
	brackets_var = peds_on_this_level + 1;
	time_chunk *= brackets_var;
	time_limit += time_chunk;
	time_limit = time_limit / peds_on_this_level;
	time_chunk = time_limit;
	time_chunk /= 2;
	
	if (G_ONMISSION == 0) {
		ADD_BLIP_FOR_COORD(hospital_x, hospital_y, hospital_z, &hospital_blip);
		CHANGE_BLIP_SPRITE(hospital_blip, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(hospital_blip, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
		CHANGE_BLIP_SCALE(hospital_blip, 0.6); // масштаб иконки на радаре
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(hospital_blip, "BL_HTAR");
	}
}


void main()
{
	if (G_MEDIC == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}
	init_ped_hashes();
	LOAD_ADDITIONAL_TEXT("AMBULAE", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	time_limit = 0;
	car = 0;
	car_health_last = 0;
	car_health_now = 0;
	time_drop = 0;
	max_peds_in_car = 0;
	peds_in_car = 0;
	peds_created = 0;
	ped_1_state = 0;
	ped_2_state = 0;
	ped_3_state = 0;
	ped_4_state = 0;
	ped_5_state = 0;
	ped_6_state = 0;
	ped_7_state = 0;
	ped_8_state = 0;
	ped_9_state = 0;
	ped_10_state = 0;
	ped_11_state = 0;
	ped_12_state = 0;
	saved_peds = 0;
	time_chunk_divider = 10.0;
	time_chunk = 0;
	time_chunk_in_secs = 0;
	score_am = 0;
	bonus_first_drive = 0;
	hospital_blip_flag = 0;
	mission_end_button_pressed = 0;
	saved_peds_total = 0;
	failed_flag = 0;
	ped_coord_x = 0.0;
	ped_coord_y = 0.0;
	ped_coord_z = 0.0;
	
	SET_WANTED_MULTIPLIER(0.5);
	
	if (LOCATE_CHAR_ANY_MEANS_2D(GetPlayerPed(), 794.298, -425.797, 1183.0, 1383.0, 0))
	{
		set_hospital_coords(300.0288, -448.1411, 4.4084, 299.3, -449.6);
		hospital_ID = 1;
	}
	else if (LOCATE_CHAR_ANY_MEANS_2D(GetPlayerPed(), 1007.234, 1174.203, 1183.0, 1283.0, 0))
	{
		set_hospital_coords(912.1241, 1243.7480, 5.3577, 929.5145, 1241.1912);
		hospital_ID = 2;
	}
	else if (LOCATE_CHAR_ANY_MEANS_2D(GetPlayerPed(), -705.702, -369.039, 1183.0, 1433.0, 0))
	{
		set_hospital_coords(-438.6317, 56.0081, 5.0683, -454.1110, 63.5340);
		hospital_ID = 3;
	}
	else if (LOCATE_CHAR_ANY_MEANS_2D(GetPlayerPed(), -592.766, 1380.961, 1283.0, 1383.0, 0))
	{
		set_hospital_coords(-390.1110, 1700.6761, 4.8744, -390.2640, 1673.0605);
		hospital_ID = 4;
	}
	
	mission_level = 1;
	//while(1)					/* Uncomment for endless levels */
	while(mission_level < 13)	/* and comment this */
	{
		start_next_level();
		if (failed_flag)
		{
			break;
		}
		if (ambulance_loop())
		{
			break;
		}
		mission_level++;
	}
	if (mission_level >= 13) {
		ADD_SCORE(GetPlayerIndex(), 15000);
		INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 15000);
		play_mission_complete_tune();
		if (G_MEDIC == 0)
		{
			INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
			G_GAME_PROGRESS += 1;
			SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
			G_MEDIC = 1;
		}
		//PRINT_WITH_NUMBER_BIG("A_COMP1", 15000, 5000, 5);
		SETTIMERA(0); //сбрасываем таймер 
		while (true)
		{
			setup_heading_draw();
			SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "A_COMP1", 15000);//Paramedic missions complete: $~1~
			
			WAIT( 0 );
			if ( TIMERA() > 4000 )
			{
				break;
			}
		}
		PRINT_HELP("A_COMP2");// Paramedic missions complete! You will never get tired when running!
	}
	mission_end();
}
