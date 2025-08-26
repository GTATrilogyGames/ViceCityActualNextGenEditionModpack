#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"


#define CONTROLLER_DPAD_UP	8		/*rebusx*/


int players_cop_car;
int criminal1_car, criminal1, criminal1_thug1, criminal1_thug2, criminal1_thug3;
int criminal2_car, criminal2, criminal2_thug1, criminal2_thug2, criminal2_thug3;
int criminal3_car, criminal3, criminal3_thug1, criminal3_thug2, criminal3_thug3;
int ped, tar_entity;

int copcar_level, random_seed, break_convoy_flag, total_criminals_killed;
int game_timer_start, vigilante_score, num_of_followers;
int copcar_timer, cop_time_limit, game_time_flag, copcar_cancelled_flag, game_time_present;
int game_time_difference, timer_in_secs, mission_end_button, cop_time_limit_int;
int players_cop_car_health, timer_on_screen_flag, criminal1_in_car_flag;
int criminal1_car_stuck_timer_start, criminal1_car_stuck_flag;
int criminal1_dead_flag, criminal1_thug1_dead_flag, criminal1_thug2_dead_flag, criminal1_thug3_dead_flag;
int criminal1_timera, criminal1_team_dead_flag, criminal2_in_car_flag;
int criminal2_car_stuck_timer_start, criminal2_car_stuck_flag;
int criminal2_dead_flag, criminal2_thug1_dead_flag, criminal2_thug2_dead_flag, criminal2_thug3_dead_flag;
int criminal2_timera, criminal2_team_dead_flag, criminal3_in_car_flag;
int criminal3_dead_flag, criminal3_thug1_dead_flag, criminal3_thug2_dead_flag, criminal3_thug3_dead_flag;
int criminal3_timera, criminal3_team_dead_flag;
int random_car_model;
int random_ped_model, in_copcar_nice_timer, copcar_print_level;
int criminal1_group, criminal2_group, criminal3_group;

float criminal2_x, criminal2_y;
float criminal2_car_stuck_x, criminal2_car_stuck_y, criminal2_car_stuck_z, criminal2_car_speed;
float criminal3_x, criminal3_y; 
float criminal3_car_stuck_x, criminal3_car_stuck_y, criminal3_car_stuck_z, criminal3_car_speed;
int criminal3_car_stuck_timer_start, criminal3_car_stuck_flag;

int criminal1_blip, criminal2_blip, criminal3_blip;
float car1_x, car1_y, car1_z, car2_x, car2_y, car2_z, car3_x, car3_y, car3_z, random_heading;
float player_dist_from_crim;
float distance_from_player;
float criminal1_x, criminal1_y;
float car_to_slow_x, car_to_slow_y, temp_float_x, temp_float_y; 
float tar_car_x, tar_car_y, gosub_car_to_slow_speed;
float dx, dy, temp_xy, car1_infront_car2, car2_infront_car1, car2_infront_car3, car3_infront_car2;
float criminal1_car_x, criminal1_car_y, criminal2_car_x, criminal2_car_y, criminal3_car_x, criminal3_car_y;
float forward_x, forward_y, temp_x, temp_y, time_bonus_divider, wanted_level_multiplier;
float criminal1_car_stuck_x, criminal1_car_stuck_y, criminal1_car_stuck_z, criminal1_car_speed;
float player_x, player_y, player_z;
float sum_x_y_temp, x_temp, y_temp, stuck_x, stuck_y, stuck_z, heading, z;
float coord_1_x, coord_1_y, coord_1_z, coord_2_x, coord_2_y, coord_c1_x, coord_c1_y, coord_c1_z;
int game_timer, frame_counter, gosub_stuck_car, car_stuck_flag, stuck_timer_start, gosub_ped;
int gosub_car_to_slow, random_int, max_passengers, game_time;
int incopcar, temp_group, fon, textur, car;

void main(void);

void next_criminal_to_kill(void);

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
void copcar_cancelled_checks(void) {
	if (!cop_time_limit == -100) {
		if (cop_time_limit < 1) {
			copcar_cancelled_flag = 1;
			PRINT_NOW("C_TIME", 3000, 1);
			return;
		}
	}
	if ((!IS_CHAR_IN_ANY_POLICE_VEHICLE(GetPlayerPed())) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("annihilator"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("fbi"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("buzzard"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("apc"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("biff"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("policeb"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("pstockade"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("patriot"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("polmav")))) {
		if (game_time_flag == 0) {
			GET_GAME_TIMER(&game_timer_start);
			if (cop_time_limit > 60000) {
				copcar_timer = 60000;
			} else {
				copcar_timer = cop_time_limit;
			}
			game_time_flag = 1;
		}
		GET_GAME_TIMER(&game_time_present);
		game_time_difference = game_time_present - game_timer_start;
		copcar_timer -= game_time_difference;
		game_timer_start = game_time_present;
		timer_in_secs = copcar_timer / 1000;
		if (timer_in_secs < 1) {
			timer_in_secs = 0;
			if (in_copcar_nice_timer < game_time_present) {
				PRINT_NOW("C_TIME", 3000, 1);
				copcar_cancelled_flag = 1;
				return;
			}
		} else {
			in_copcar_nice_timer = game_time_present + 1000;
		}
		PRINT_WITH_NUMBER_NOW("COPCART", timer_in_secs, 200, 1);
	}
	
	if ((IS_CHAR_IN_ANY_POLICE_VEHICLE(GetPlayerPed())) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("annihilator"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("fbi"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("buzzard"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("apc"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("biff"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("policeb"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("pstockade"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("patriot"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("polmav")))) {
		STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &players_cop_car);
		SET_CAN_BURST_CAR_TYRES(players_cop_car, 0);
		if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
			if (mission_end_button == 1) {
				mission_end_button = 2;
			}
		} else {
			if (mission_end_button == 0) {
				mission_end_button = 1;
			}
		}
		game_time_flag = 0;
	}
	if (mission_end_button == 2) {
		if (!(((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER())))) {
			PRINT_NOW("C_CANC", 3000, 1);
			copcar_cancelled_flag = 1;
			return;
		}
	}
	return;
}

void mission_cleanup_copcar(void) {
	SET_WANTED_MULTIPLIER(1.0);
	REMOVE_BLIP(criminal1_blip);
	REMOVE_BLIP(criminal2_blip);
	REMOVE_BLIP(criminal3_blip);
	REMOVE_GROUP(criminal1_group);
	REMOVE_GROUP(criminal2_group);
	REMOVE_GROUP(criminal3_group);
	MARK_MODEL_AS_NO_LONGER_NEEDED(random_car_model);
	RELEASE_TEXTURE(fon);
	REMOVE_TXD(textur);
	TERMINATE_THIS_SCRIPT();
	//main();
}

void copcar_failed(void) {
	if (G_COPCAR == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
	}
	mission_cleanup_copcar();
}

void mission_copcar_passed(void) {
	INCREMENT_INT_STAT(STAT_VIGILANTE_LEVELS_DONE, 1);
	copcar_level++;
	if ((IS_CHAR_IN_ANY_POLICE_VEHICLE(GetPlayerPed())) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("annihilator"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("fbi"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("buzzard"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("apc"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("biff"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("policeb"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("pstockade"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("patriot"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("polmav")))) {
		STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &players_cop_car);
		SET_CAN_BURST_CAR_TYRES(players_cop_car, 0);
		players_cop_car_health = GET_ENGINE_HEALTH(players_cop_car);
		players_cop_car_health += 100;
		SET_ENGINE_HEALTH(players_cop_car, players_cop_car_health);
	}
	MARK_CAR_AS_NO_LONGER_NEEDED(&criminal1_car);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal1);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal1_thug1);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal1_thug2);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal1_thug3);
	
	MARK_CAR_AS_NO_LONGER_NEEDED(&criminal2_car);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal2);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal2_thug1);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal2_thug2);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal2_thug3);

	MARK_CAR_AS_NO_LONGER_NEEDED(&criminal3_car);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal3);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal3_thug1);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal3_thug2);
	MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal3_thug3);
	
	REMOVE_BLIP(criminal1_blip);
	REMOVE_BLIP(criminal2_blip);
	REMOVE_BLIP(criminal3_blip);
	
	vigilante_score	= copcar_level * copcar_level;
	vigilante_score *= 50;

	//PRINT_WITH_NUMBER_BIG("C_PASS", vigilante_score, 5000, 5);
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.4, "C_PASS", vigilante_score);//
		
		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}

	ADD_SCORE(GetPlayerIndex(), vigilante_score);
	INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, vigilante_score);
	if (G_COPCAR == 0) {
		if (copcar_level == 12) {
			INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
			G_GAME_PROGRESS += 1;
			SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
			G_COPCAR = 1;
			PRINT_HELP("C_COMP1");// Vigilante mission level 12 complete: Your max Body Armor increased to 150
			WAIT(500);
			ADD_ARMOUR_TO_CHAR(GetPlayerPed(), 150);
		}
	}
	
	while ((!IS_CHAR_IN_ANY_POLICE_VEHICLE(GetPlayerPed())) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("annihilator"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("fbi"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("buzzard"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("apc"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("biff"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("policeb"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("pstockade"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("patriot"))) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("polmav")))) {	
		if (game_time_flag == 0) {
			GET_GAME_TIMER(&game_timer_start);
			if (cop_time_limit > 60000) {
				copcar_timer = 60000;
			} else {
				copcar_timer = cop_time_limit;
			}
			game_time_flag = 1;
		}
		GET_GAME_TIMER(&game_time_present);
		game_time_difference = game_time_present - game_timer_start;
		copcar_timer -= game_time_difference;
		game_timer_start = game_time_present;
		timer_in_secs = copcar_timer / 1000;
		if (timer_in_secs < 1) {
			timer_in_secs = 0;
			if (in_copcar_nice_timer < game_time_present) {
				PRINT_NOW("C_TIME", 3000, 1);
				copcar_cancelled_flag = 1;
				copcar_failed();
			}
		} else {
			in_copcar_nice_timer = game_time_present + 1000;
		}
		PRINT_WITH_NUMBER_NOW("COPCART", timer_in_secs, 200, 1);
		WAIT(0);
		if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
		{
			copcar_failed();
		}
	}
	
	if (IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
		STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &players_cop_car);
		SET_CAN_BURST_CAR_TYRES(players_cop_car, 0);
		players_cop_car_health = GET_ENGINE_HEALTH(players_cop_car);
		players_cop_car_health += 100;
		SET_ENGINE_HEALTH(players_cop_car, players_cop_car_health);
	}
	if (copcar_level < 13) {
		wanted_level_multiplier -= 0.05;
		SET_WANTED_MULTIPLIER(wanted_level_multiplier);
	}
	next_criminal_to_kill();
}

void slow_criminal_if_close(void) {
	if (tar_entity == -1) {
		GET_CHAR_COORDINATES(GetPlayerPed(), &tar_car_x, &tar_car_y, &temp_float_x);
	} else {
		GET_CAR_COORDINATES(tar_entity, &tar_car_x, &tar_car_y, &temp_float_x);
	}
	GET_CAR_COORDINATES(gosub_car_to_slow, &car_to_slow_x, &car_to_slow_y, &temp_float_x);
	temp_float_x = car_to_slow_x - tar_car_x;
	temp_float_y = car_to_slow_y - tar_car_y;
	temp_float_x = temp_float_x * temp_float_x;
	temp_float_y = temp_float_y * temp_float_y;
	temp_float_x = temp_float_x + temp_float_y;
	temp_float_x = SQRT(temp_float_x);
	gosub_car_to_slow_speed = temp_float_x + 3.0;
	if (gosub_car_to_slow_speed > 100.0) {
		gosub_car_to_slow_speed = 100.0;
	}
	if (gosub_car_to_slow_speed < 0.0) {
		gosub_car_to_slow_speed = 0.0;
	}
	return;
}

void criminal_steal_a_car(void) {
	if (!IS_CHAR_DEAD(gosub_ped)) {
		GET_CHAR_COORDINATES(gosub_ped, &coord_1_x, &coord_1_y, &coord_1_z);
		if (heading == 919.9) {
			CREATE_CAR(random_car_model, coord_1_x, coord_1_y, coord_1_z, &car, 1);
			SET_CAR_ON_GROUND_PROPERLY(car);
		}
		if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(GetPlayerPed(), gosub_ped, 40.0, 40.0, 0)) {
			coord_2_x = coord_1_x + 40.0;
			coord_2_y = coord_1_y + 40.0;
			coord_1_x = coord_1_x - 40.0;
			coord_1_y = coord_1_y - 40.0;
			MARK_CAR_AS_NO_LONGER_NEEDED(&car);
			car = -1;
			GET_RANDOM_CAR_OF_TYPE_IN_AREA_NO_SAVE(coord_1_x, coord_1_y, coord_2_x, coord_2_y, -1, &car);
			if ((car == -1) || (criminal1_car == car)) {
				TASK_COMBAT(gosub_ped, GetPlayerPed());
			} else {
				int enghp = GET_ENGINE_HEALTH(car);
				if (enghp > 400) {
					GET_NUMBER_OF_FOLLOWERS(gosub_ped, &num_of_followers);
					GET_MAXIMUM_NUMBER_OF_PASSENGERS(car, &max_passengers);
					if (!(num_of_followers > max_passengers)) {
						LOCK_CAR_DOORS(car, 1);
						TASK_ENTER_CAR_AS_DRIVER(gosub_ped, car, -1);
					} else {
						TASK_COMBAT(gosub_ped, GetPlayerPed());
					}
				} else {
					TASK_COMBAT(gosub_ped, GetPlayerPed());
					MARK_CAR_AS_NO_LONGER_NEEDED(&car);
					car = -1;
				}
			}
		} else {
			GET_CLOSEST_CAR_NODE_WITH_HEADING(coord_1_x, coord_1_y, coord_1_z, &coord_1_x, &coord_1_y, &coord_1_z, &heading);
			if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(coord_1_x, coord_1_y, coord_1_z, 3.0, 3.0, 2.0)) {
				if (HAS_MODEL_LOADED(random_car_model)) {
					MARK_CAR_AS_NO_LONGER_NEEDED(&car);
					CREATE_CAR(random_car_model, coord_1_x, coord_1_y, coord_1_z, &car, 1);
					SET_CAR_HEADING(car, heading);
					SET_CAR_ON_GROUND_PROPERLY(car);
					TASK_ENTER_CAR_AS_DRIVER(gosub_ped, car, -1);
				}
			} else {
				if (LOCATE_CHAR_ON_FOOT_3D(gosub_ped, coord_1_x, coord_1_y, coord_1_z, 3.0, 3.0, 2.0, 0)) {
					GET_CLOSEST_CAR_NODE(coord_1_x, coord_1_y, coord_1_z, &coord_1_x, &coord_1_y, &coord_1_z);
					TASK_FOLLOW_NAV_MESH_TO_COORD(gosub_ped, coord_1_x, coord_1_y, coord_1_z, 2, -1, 0.5);
				}
			}
		}
	}
	return;
}

void criminal_car_stuck_checks(void) {
	GET_GAME_TIMER(&game_time);
	if (!IS_CAR_DEAD(gosub_stuck_car)) {
		if ((IS_CAR_UPSIDEDOWN(gosub_stuck_car)) && (IS_CAR_STOPPED(gosub_stuck_car))) {
			break_convoy_flag = 1;
			if (LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), gosub_stuck_car, 90.0, 90.0, 0)) {
				SET_UPSIDEDOWN_CAR_NOT_DAMAGED(gosub_stuck_car, 0);
				car_stuck_flag = -9;
			} else {
				if (!IS_CAR_ON_SCREEN(gosub_stuck_car)) {
					GET_CAR_COORDINATES(gosub_stuck_car, &coord_c1_x, &coord_c1_y, &coord_c1_z);
					GET_CLOSEST_CAR_NODE_WITH_HEADING(coord_c1_x, coord_c1_y, coord_c1_z, &coord_c1_x, &coord_c1_y, &coord_c1_z, &heading);
					SET_CAR_COORDINATES(gosub_stuck_car, coord_c1_x, coord_c1_y, coord_c1_z);
					SET_CAR_HEADING(gosub_stuck_car, heading);
				}
			}
		}
		
		if (LOCATE_CAR_3D(gosub_stuck_car, stuck_x, stuck_y, stuck_z, 4.0, 4.0, 4.0, 0)) {
			if (car_stuck_flag == 0) {
				stuck_timer_start = game_time;
				car_stuck_flag = 1;
			}
			game_time = game_time - stuck_timer_start;
			if (car_stuck_flag == 1) {
				if (game_time > 8000) {
					if (LOCATE_CHAR_ANY_MEANS_CAR_2D(GetPlayerPed(), gosub_stuck_car, 90.0, 90.0, 0)) {
						SET_UPSIDEDOWN_CAR_NOT_DAMAGED(gosub_stuck_car, 0);
						stuck_timer_start = game_time;
						car_stuck_flag = -9;
					} else {
						if (!IS_CAR_ON_SCREEN(gosub_stuck_car)) {
							GET_CAR_COORDINATES(gosub_stuck_car, &coord_c1_x, &coord_c1_y, &coord_c1_z);
							GET_CLOSEST_CAR_NODE_WITH_HEADING(coord_c1_x, coord_c1_y, coord_c1_z, &coord_c1_x, &coord_c1_y, &coord_c1_z, &heading);
							if (!IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(coord_c1_x, coord_c1_y, coord_c1_z,4.0, 4.0, 4.0)) {
								SET_CAR_COORDINATES(gosub_stuck_car, coord_c1_x, coord_c1_y, coord_c1_z);
								SET_CAR_HEADING(gosub_stuck_car, heading);
								stuck_timer_start = game_time;
								car_stuck_flag = 0;
								break_convoy_flag = 1;
							}
						}
					}
				}
			}
		}
		
		if (!LOCATE_CAR_3D(gosub_stuck_car, stuck_x, stuck_y, stuck_z, 4.0, 4.0, 4.0, 0)) {
			GET_CAR_COORDINATES(gosub_stuck_car, &stuck_x, &stuck_y, &stuck_z);
			car_stuck_flag = 0;
		}
	}
	return;
}

void criminal1_group_breaking(void) {
	if (!IS_CHAR_DEAD(criminal1)) {
		if (!IS_CHAR_DEAD(criminal1_thug1)) {
			if (!IS_GROUP_MEMBER(criminal1_thug1, criminal1_group)) {
				if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(criminal1_thug1, criminal1, 30.0, 30.0, 0)) {
					SET_GROUP_LEADER(criminal1_group, criminal1);
					SET_GROUP_MEMBER(criminal1_group, criminal1_thug1);
				} else {
					TASK_COMBAT(criminal1_thug1, GetPlayerPed());
				}
			}
		} else {
			MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal1_thug1);
		}
		
		if (!IS_CHAR_DEAD(criminal1_thug2)) {
			if (!IS_GROUP_MEMBER(criminal1_thug2, criminal1_group)) {
				if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(criminal1_thug2, criminal1, 30.0, 30.0, 0)) {
					SET_GROUP_LEADER(criminal1_group, criminal1);
					SET_GROUP_MEMBER(criminal1_group, criminal1_thug2);
				} else {
					TASK_COMBAT(criminal1_thug2, GetPlayerPed());
				}
			}
		} else {
			MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal1_thug2);
		}
		
		if (!IS_CHAR_DEAD(criminal1_thug3)) {
			if (!IS_GROUP_MEMBER(criminal1_thug3, criminal1_group)) {
				if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(criminal1_thug3, criminal1, 30.0, 30.0, 0)) {
					SET_GROUP_LEADER(criminal1_group, criminal1);
					SET_GROUP_MEMBER(criminal1_group, criminal1_thug3);
				} else {
					TASK_COMBAT(criminal1_thug3, GetPlayerPed());
				}
			}
		} else {
			MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal1_thug3);
		}
	}
	return;
}

void criminal2_group_breaking(void) {
	if (!IS_CHAR_DEAD(criminal2)) {
		if (!IS_CHAR_DEAD(criminal2_thug1)) {
			if (!IS_GROUP_MEMBER(criminal2_thug1, criminal2_group)) {
				if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(criminal2_thug1, criminal2, 30.0, 30.0, 0)) {
					SET_GROUP_LEADER(criminal2_group, criminal2);
					SET_GROUP_MEMBER(criminal2_group, criminal2_thug1);
				} else {
					TASK_COMBAT(criminal2_thug1, GetPlayerPed());
				}
			}
		} else {
			MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal2_thug1);
		}
		
		if (!IS_CHAR_DEAD(criminal2_thug2)) {
			if (!IS_GROUP_MEMBER(criminal2_thug2, criminal2_group)) {
				if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(criminal2_thug2, criminal2, 30.0, 30.0, 0)) {
					SET_GROUP_LEADER(criminal2_group, criminal2);
					SET_GROUP_MEMBER(criminal2_group, criminal2_thug2);
				} else {
					TASK_COMBAT(criminal2_thug2, GetPlayerPed());
				}
			}
		} else {
			MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal2_thug2);
		}
		
		if (!IS_CHAR_DEAD(criminal2_thug3)) {
			if (!IS_GROUP_MEMBER(criminal2_thug3, criminal2_group)) {
				if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(criminal2_thug3, criminal2, 30.0, 30.0, 0)) {
					SET_GROUP_LEADER(criminal2_group, criminal2);
					SET_GROUP_MEMBER(criminal2_group, criminal2_thug3);
				} else {
					TASK_COMBAT(criminal2_thug3, GetPlayerPed());
				}
			}
		} else {
			MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal2_thug3);
		}
	}
	return;
}

void criminal3_group_breaking(void) {
	if (!IS_CHAR_DEAD(criminal3)) {
		if (!IS_CHAR_DEAD(criminal3_thug1)) {
			if (!IS_GROUP_MEMBER(criminal3_thug1, criminal3_group)) {
				if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(criminal3_thug1, criminal3, 30.0, 30.0, 0)) {
					SET_GROUP_LEADER(criminal3_group, criminal3);
					SET_GROUP_MEMBER(criminal3_group, criminal3_thug1);
				} else {
					TASK_COMBAT(criminal3_thug1, GetPlayerPed());
				}
			}
		} else {
			MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal3_thug1);
		}
		
		if (!IS_CHAR_DEAD(criminal3_thug2)) {
			if (!IS_GROUP_MEMBER(criminal3_thug2, criminal3_group)) {
				if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(criminal3_thug2, criminal3, 30.0, 30.0, 0)) {
					SET_GROUP_LEADER(criminal3_group, criminal3);
					SET_GROUP_MEMBER(criminal3_group, criminal3_thug2);
				} else {
					TASK_COMBAT(criminal3_thug2, GetPlayerPed());
				}
			}
		} else {
			MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal3_thug2);
		}
		
		if (!IS_CHAR_DEAD(criminal3_thug3)) {
			if (!IS_GROUP_MEMBER(criminal3_thug3, criminal3_group)) {
				if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(criminal3_thug3, criminal3, 30.0, 30.0, 0)) {
					SET_GROUP_LEADER(criminal3_group, criminal3);
					SET_GROUP_MEMBER(criminal3_group, criminal3_thug3);
				} else {
					TASK_COMBAT(criminal3_thug3, GetPlayerPed());
				}
			}
		} else {
			MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal3_thug3);
		}
	}
	return;
}

void print_text_for_zone_char_is_in(void) {
	if (!IS_CHAR_DEAD(criminal1)) {
		float crx, cry, crz;
		GET_CHAR_COORDINATES(criminal1, &crx, &cry, &crz);
		char* zonName = GET_NAME_OF_ZONE(crx, cry, crz);	
		PRINT_STRING_IN_STRING_NOW("C_BREIF", zonName, 5000, 1);
	}
	return;
}

void setup_ped_threats_etc(void) {
	MODIFY_CHAR_MOVE_STATE(ped, 3);
	SET_CHAR_ONLY_DAMAGED_BY_PLAYER(ped, 1);
	SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped, 1);
	SET_CHAR_RELATIONSHIP_GROUP(ped, 5);
	SET_CHAR_RELATIONSHIP(ped, 5, 0);
	SET_SENSE_RANGE(ped, 20.0);
	SET_CHAR_WILL_USE_COVER(ped, 1);
	SET_CHAR_SHOOT_RATE(ped, 25);
	
	if (copcar_level == 0) {
		GENERATE_RANDOM_INT_IN_RANGE(0, 2, &random_int);
	}
	if (copcar_level > 1) {
		GENERATE_RANDOM_INT_IN_RANGE(0, 3, &random_int);
	}
	if (copcar_level > 3) {
		GENERATE_RANDOM_INT_IN_RANGE(0, 4, &random_int);
	}
	if (copcar_level > 5) {
		GENERATE_RANDOM_INT_IN_RANGE(0, 5, &random_int);
	}
	if (copcar_level > 7) {
		GENERATE_RANDOM_INT_IN_RANGE(0, 6, &random_int);
	}
	if (random_int == 0) {
		GENERATE_RANDOM_INT_IN_RANGE(10, 13, &random_int);
		if (random_int == 10) {
			UpdateWeaponOfPed(ped, WEAPON_KNIFE);
		}
		if (random_int == 11) {
			UpdateWeaponOfPed(ped, WEAPON_BASEBALLBAT);
		}
	}
	if (random_int == 1) {
		UpdateWeaponOfPed(ped, WEAPON_PISTOL);
	}
	if (random_int == 2) {
		UpdateWeaponOfPed(ped, WEAPON_MP5);
	}
	if (random_int == 3) {
		UpdateWeaponOfPed(ped, WEAPON_AK47);
	}
	if ((random_int == 4) || (random_int == 5)) {
		UpdateWeaponOfPed(ped, WEAPON_SHOTGUN);
	}
	return;
}

void copcar_oddjob_loop(void) {
	while (true) {
		WAIT(0);
		int old_total_criminals_killed = total_criminals_killed;
		if (TIMERC() >= 1000) {
			cop_time_limit -= 1000;
			SETTIMERC(0);
		}
		DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
		int timemin, timesec, timetemp;
		timesec = cop_time_limit / 1000;
		timemin = timesec / 60;
		timetemp = timemin * 60;
		timesec -= timetemp;
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:
		//if ((timesec > 9) && (timemin > 9)) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T1", timemin, timesec);
		//} else if ((timesec <= 9) && (timemin <= 9)) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T3", timemin, timesec);
		//} else if ((timesec > 9) && (timemin <= 9)) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T2", timemin, timesec);
		//} else if ((timesec <= 9) && (timemin > 9)) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T0", timemin, timesec);
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
		DISPLAY_TEXT(0.78815097, 0.73564852, "KILLS");
		if (total_criminals_killed > 9) {
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_NOZERO", total_criminals_killed);
		} else {
			setup_draw_value();
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_ZERO", total_criminals_killed);
		}
		GET_GAME_TIMER(&game_timer);
		GET_CHAR_COORDINATES(GetPlayerPed(), &player_x, &player_y, &player_z);
		copcar_cancelled_checks();
		if (copcar_cancelled_flag == 1) {
			copcar_failed();
		}
		if ((timemin == 0) && (timesec < 1))
		{
			PRINT_NOW("C_TIME", 3000, 1);
			copcar_failed();
		}
		else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
		{
			copcar_failed();
		}
		
		if ((criminal1_in_car_flag == -1) || (criminal2_in_car_flag == -1) || (criminal3_in_car_flag == -1)) {
			break_convoy_flag = 1;
		}
		frame_counter++;
		if (frame_counter > 2) {
			frame_counter = 0;
		}
		
		if (frame_counter == 0) {
			if (!IS_CHAR_DEAD(criminal1)) {
				if (IS_CHAR_SITTING_IN_ANY_CAR(criminal1)) {
					MARK_CAR_AS_NO_LONGER_NEEDED(&criminal1_car);
					STORE_CAR_CHAR_IS_IN_NO_SAVE(criminal1, &criminal1_car);
					if (criminal1_in_car_flag == -1) {
						GET_GROUP_SIZE(criminal1_group, &temp_group, &num_of_followers);
						if (num_of_followers > 0) {
							criminal1_timera = game_timer + 2000;
						} else {
							criminal1_timera = game_timer;
						}
						criminal1_in_car_flag = 0;
					}
					
					if (criminal1_in_car_flag == 0) {
						if (game_timer > criminal1_timera) {
							SET_DRIVE_TASK_CRUISE_SPEED(criminal1, 100.0);
							TASK_CAR_DRIVE_WANDER(criminal1, criminal1_car, 100.0, 2);
							criminal1_car_stuck_timer_start = game_timer;
							criminal1_in_car_flag = 1;
							criminal1_car_stuck_flag = 0;
						}
					}
					
					if (criminal1_in_car_flag > 0) {
						if (IS_CHAR_IN_CAR(GetPlayerPed(), criminal1_car)) {
							TASK_COMBAT(criminal1, GetPlayerPed());
						}
						gosub_stuck_car = criminal1_car;
						car_stuck_flag = criminal1_car_stuck_flag;
						stuck_timer_start = criminal1_car_stuck_timer_start;
						stuck_x = criminal1_car_stuck_x;
						stuck_y = criminal1_car_stuck_y;
						stuck_z = criminal1_car_stuck_z;
						if (criminal1_car_speed > 0.0) {
							criminal_car_stuck_checks();
						}
						criminal1_car_stuck_flag = car_stuck_flag;
						criminal1_car_stuck_timer_start = stuck_timer_start;
						criminal1_car_stuck_x = stuck_x;
						criminal1_car_stuck_y = stuck_y;
						criminal1_car_stuck_z = stuck_z;
						if (criminal1_car_stuck_flag == -9) {
							TASK_FLEE_CHAR_ANY_MEANS(criminal1, criminal1_car, 250.0, -1, 0, 0, 0, 25.0);
							criminal1_car_stuck_flag = 0;
						}
						int enghp = GET_ENGINE_HEALTH(criminal1_car);
						if (!(enghp > 400)) {
							TASK_COMBAT(criminal1, GetPlayerPed());
						}
						if (!(enghp > 251)) {
							TASK_FLEE_CHAR_ANY_MEANS(criminal1, criminal1_car, 250.0, -1, 0, 0, 0, 25.0);
							criminal1_timera = game_timer + 2000;
						} else {
							criminal1_timera = game_timer;
						}
						criminal1_group_breaking();
						GET_CHAR_COORDINATES(criminal1, &criminal1_x, &criminal1_y, &z);
						x_temp = player_x - criminal1_x;
						y_temp = player_y - criminal1_y;
						x_temp = x_temp * x_temp;
						y_temp = y_temp * y_temp;
						sum_x_y_temp = x_temp + y_temp;
						sum_x_y_temp = SQRT(sum_x_y_temp);
						criminal1_car_speed = 1000.0 / sum_x_y_temp;
						if (criminal1_car_speed > 100.0) {
							criminal1_car_speed = 100.0;
						}
						if (criminal1_car_speed < 15.0) {
							criminal1_car_speed = 15.0;
						}
						SET_DRIVE_TASK_CRUISE_SPEED(criminal1, criminal1_car_speed);
					}
				} else {
					criminal1_in_car_flag = -1;
					criminal1_group_breaking();
					if (game_timer > criminal1_timera) {
						if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(GetPlayerPed(), criminal1, 45.0, 45.0, 0)) {
							if (!IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
								TASK_COMBAT(criminal1, GetPlayerPed());
							} else {
								if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(GetPlayerPed(), criminal1, 30.0, 30.0, 0)) {
									TASK_COMBAT(criminal1, GetPlayerPed());
								} else {
									gosub_ped = criminal1;
									if (!IS_CAR_DEAD(criminal1_car)) {
										int enghp = GET_ENGINE_HEALTH(criminal1_car);
										if (enghp > 400) {
											if (LOCATE_CHAR_ANY_MEANS_CAR_2D(criminal1, criminal1_car, 40.0, 40.0, 0)) {
												TASK_ENTER_CAR_AS_DRIVER(criminal1, criminal1_car, -1);
											} else {
												criminal_steal_a_car();
											}
										} else {
											criminal_steal_a_car();
										}
									} else {
										criminal_steal_a_car();
									}
								}
							}
						} else {
							gosub_ped = criminal1;
							if (!IS_CAR_DEAD(criminal1_car)) {
								int enghp = GET_ENGINE_HEALTH(criminal1_car);
								if (enghp > 400) {
									if (LOCATE_CHAR_ANY_MEANS_CAR_2D(criminal1, criminal1_car, 40.0, 40.0, 0)) {
										TASK_ENTER_CAR_AS_DRIVER(criminal1, criminal1_car, -1);
									} else {
										criminal_steal_a_car();
									}
								} else {
									criminal_steal_a_car();
								}
							} else {
								criminal_steal_a_car();
							}
						}
					}
				}
			} else {
				REMOVE_BLIP(criminal1_blip);
				MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal1);
				if (criminal1_dead_flag == 0) {
					total_criminals_killed++;
					criminal1_dead_flag = 1;
				}
				if (!IS_CHAR_DEAD(criminal1_thug1)) {
					criminal1 = criminal1_thug1;
					criminal1_thug1 = -1;
					criminal1_dead_flag = 0;
					criminal1_thug1_dead_flag = 1;
					ADD_BLIP_FOR_CHAR(criminal1, &criminal1_blip);
					if (!IS_CHAR_DEAD(criminal1_thug2)) {
						SET_GROUP_LEADER(criminal1_group, criminal1);
						SET_GROUP_MEMBER(criminal1_group, criminal1_thug2);
						if (!IS_GROUP_MEMBER(criminal1_thug2, criminal1_group)) {
							TASK_COMBAT(criminal1_thug2, GetPlayerPed());
						}
					}
					if (!IS_CHAR_DEAD(criminal1_thug3)) {
						SET_GROUP_LEADER(criminal1_group, criminal1);
						SET_GROUP_MEMBER(criminal1_group, criminal1_thug3);
						if (!IS_GROUP_MEMBER(criminal1_thug3, criminal1_group)) {
							TASK_COMBAT(criminal1_thug3, GetPlayerPed());
						}
					}
				} else {
					MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal1_thug1);
					if (!IS_CHAR_DEAD(criminal1_thug2)) {
						criminal1 = criminal1_thug2;
						criminal1_thug2 = -1;
						criminal1_dead_flag = 0;
						criminal1_thug2_dead_flag = 1;
						ADD_BLIP_FOR_CHAR(criminal1, &criminal1_blip);
						if (!IS_CHAR_DEAD(criminal1_thug3)) {
							SET_GROUP_LEADER(criminal1_group, criminal1);
							SET_GROUP_MEMBER(criminal1_group, criminal1_thug3);
							if (!IS_GROUP_MEMBER(criminal1_thug3, criminal1_group)) {
								TASK_COMBAT(criminal1_thug3, GetPlayerPed());
							}
						}
					} else {
						MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal1_thug2);
						if (!IS_CHAR_DEAD(criminal1_thug3)) {
							criminal1 = criminal1_thug3;
							criminal1_thug3 = -1;
							criminal1_dead_flag = 0;
							criminal1_thug3_dead_flag = 1;
							ADD_BLIP_FOR_CHAR(criminal1, &criminal1_blip);
						} else {
							MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal1_thug3);
							criminal1_team_dead_flag = 1;
						}
					}
				}
			}
			if (IS_CHAR_DEAD(criminal1_thug1)) {
				if (criminal1_thug1_dead_flag == 0) {
					total_criminals_killed++;
					criminal1_thug1_dead_flag = 1;
				}
			}
			if (IS_CHAR_DEAD(criminal1_thug2)) {
				if (criminal1_thug2_dead_flag == 0) {
					total_criminals_killed++;
					criminal1_thug2_dead_flag = 1;
				}
			}
			if (IS_CHAR_DEAD(criminal1_thug3)) {
				if (criminal1_thug3_dead_flag == 0) {
					total_criminals_killed++;
					criminal1_thug3_dead_flag = 1;
				}
			}
		}
		
		if (frame_counter == 1) {
			if (!IS_CHAR_DEAD(criminal2)) {
				if (IS_CHAR_SITTING_IN_ANY_CAR(criminal2)) {
					MARK_CAR_AS_NO_LONGER_NEEDED(&criminal2_car);
					STORE_CAR_CHAR_IS_IN_NO_SAVE(criminal2, &criminal2_car);
					if (criminal2_in_car_flag == -1) {
						GET_GROUP_SIZE(criminal2_group, &temp_group, &num_of_followers);
						if (num_of_followers > 0) {
							criminal2_timera = game_timer + 2000;
						} else {
							criminal2_timera = game_timer;
						}
						criminal2_in_car_flag = 0;	
					}
					if (criminal2_in_car_flag == 0) {
						if (game_timer > criminal2_timera) {
							SET_DRIVE_TASK_CRUISE_SPEED(criminal2, 100.0);
							TASK_CAR_DRIVE_WANDER(criminal2, criminal2_car, 100.0, 2);
							if (break_convoy_flag == 0) {
								if (!IS_CAR_DEAD(criminal1_car)) {
									TASK_CAR_DRIVE_WANDER(criminal2, criminal2_car, 100.0, 2);
								} else {
									break_convoy_flag = 1;
								}
							}
							if (break_convoy_flag == 1) {
								MARK_CAR_AS_CONVOY_CAR(criminal2_car, 0);
								TASK_CAR_DRIVE_WANDER(criminal2, criminal2_car, 100.0, 2);
							}
							criminal2_car_stuck_timer_start = game_timer;
							criminal2_in_car_flag = 1;
							criminal2_car_stuck_flag = 0;
						}
					}
					if (criminal2_in_car_flag > 0) {
						if (IS_CHAR_IN_CAR(GetPlayerPed(), criminal2_car)) {
							TASK_COMBAT(criminal2, GetPlayerPed());
						}
						gosub_stuck_car = criminal2_car;
						car_stuck_flag = criminal2_car_stuck_flag;
						stuck_timer_start = criminal2_car_stuck_timer_start;
						stuck_x = criminal2_car_stuck_x;
						stuck_y = criminal2_car_stuck_y;
						stuck_z = criminal2_car_stuck_z;
						if (criminal2_car_speed > 0.0) {
							criminal_car_stuck_checks();
						}
						criminal2_car_stuck_flag = car_stuck_flag;
						criminal2_car_stuck_timer_start = stuck_timer_start;
						criminal2_car_stuck_x = stuck_x;
						criminal2_car_stuck_y = stuck_y;
						criminal2_car_stuck_z = stuck_z;
						if (criminal2_car_stuck_flag == -9) {
							TASK_FLEE_CHAR_ANY_MEANS(criminal2, criminal2_car, 250.0, -1, 0, 0, 0, 25.0);
							criminal2_car_stuck_flag = 0;
						}
						int enghp = GET_ENGINE_HEALTH(criminal2_car);
						if (!(enghp > 400)) {
							TASK_COMBAT(criminal2, GetPlayerPed());
						}
						if (!(enghp > 251)) {
							TASK_FLEE_CHAR_ANY_MEANS(criminal2, criminal2_car, 250.0, -1, 0, 0, 0, 25.0);
							criminal2_timera = game_timer + 2000;
						} else {
							criminal2_timera = game_timer;
						}
						criminal2_group_breaking();
						GET_CHAR_COORDINATES(criminal2, &criminal2_x, &criminal2_y, &z);
						x_temp = player_x - criminal2_x;
						y_temp = player_y - criminal2_y;
						x_temp = x_temp * x_temp;
						y_temp = y_temp * y_temp;
						sum_x_y_temp = x_temp + y_temp;
						sum_x_y_temp = SQRT(sum_x_y_temp);
						criminal2_car_speed = 1000.0 / sum_x_y_temp;
						if (criminal2_car_speed > 100.0) {
							criminal2_car_speed = 100.0;
						}
						if (criminal2_car_speed < 15.0) {
							criminal2_car_speed = 15.0;
						}
						
						if (break_convoy_flag == 0) {
							if (!IS_CAR_DEAD(criminal1_car)) {
								gosub_car_to_slow = criminal2_car;
								tar_entity = criminal1_car;
								slow_criminal_if_close();
								criminal2_car_speed = gosub_car_to_slow_speed;
								
								GET_CAR_FORWARD_X(criminal2_car, &forward_x);
								GET_CAR_FORWARD_Y(criminal2_car, &forward_y);
								GET_CAR_COORDINATES(criminal1_car, &criminal1_car_x, &criminal1_car_y, &z);
								GET_CAR_COORDINATES(criminal2_car, &criminal2_car_x, &criminal2_car_y, &z);
								temp_float_x = criminal2_car_x - criminal1_car_x;
								forward_x = forward_x * temp_float_x;
								temp_float_y = criminal2_car_y - criminal1_car_y;
								forward_y = forward_y * temp_float_y;
								car1_infront_car2 = forward_x + forward_y;
								
								GET_CAR_FORWARD_X(criminal1_car, &forward_x);
								GET_CAR_FORWARD_Y(criminal1_car, &forward_y);
								GET_CAR_COORDINATES(criminal2_car, &criminal2_car_x, &criminal2_car_y, &z);
								GET_CAR_COORDINATES(criminal1_car, &criminal1_car_x, &criminal1_car_y, &z);
								temp_float_x = criminal1_car_x - criminal2_car_x;
								forward_x = forward_x * temp_float_x;
								temp_float_y = criminal1_car_y - criminal2_car_y;
								forward_y = forward_y * temp_float_y;
								car2_infront_car1 = forward_x + forward_y;
								if (car1_infront_car2 > 0.0) {
									if (car2_infront_car1 < 0.0) {
										criminal2_car_speed = 0.0;
									}
								}
							} else {
								TASK_CAR_DRIVE_WANDER(criminal2, criminal2_car, 100.0, 2);
								break_convoy_flag = 1;
							}
						}
						
						if (criminal2_car_speed == 0.0) {
							TASK_CAR_TEMP_ACTION(criminal2, criminal2_car, 1, 17);
						} else {
							SET_DRIVE_TASK_CRUISE_SPEED(criminal2, criminal2_car_speed);
						}
					}
				} else {
					criminal2_in_car_flag = -1;
					criminal2_group_breaking();
					if (game_timer > criminal2_timera) {
						if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(GetPlayerPed(), criminal2, 40.0, 40.0, 0)) {
							if (!IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
								TASK_COMBAT(criminal2, GetPlayerPed());
							} else {
								if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(GetPlayerPed(), criminal2, 25.0, 25.0, 0)) {
									TASK_COMBAT(criminal2, GetPlayerPed());
								} else {
									gosub_ped = criminal2;
									if (!IS_CAR_DEAD(criminal2_car)) {
										int enghp = GET_ENGINE_HEALTH(criminal2_car);
										if (enghp > 400) {
											if (LOCATE_CHAR_ANY_MEANS_CAR_2D(criminal2, criminal2_car, 40.0, 40.0, 0)) {
												TASK_ENTER_CAR_AS_DRIVER(criminal2, criminal2_car, -1);
											} else {
												criminal_steal_a_car();
											}
										} else {
											criminal_steal_a_car();
										}
									} else {
										criminal_steal_a_car();
									}
								}
							}
						} else {
							gosub_ped = criminal2;
							if (!IS_CAR_DEAD(criminal2_car)) {
								int enghp = GET_ENGINE_HEALTH(criminal2_car);
								if (enghp > 400) {
									if (LOCATE_CHAR_ANY_MEANS_CAR_2D(criminal2, criminal2_car, 40.0, 40.0, 0)) {
										TASK_ENTER_CAR_AS_DRIVER(criminal2, criminal2_car, -1);
									} else {
										criminal_steal_a_car();
									}
								} else {
									criminal_steal_a_car();
								}
							} else {
								criminal_steal_a_car();
							}
						}
					}
				}
			} else {
				REMOVE_BLIP(criminal2_blip);
				MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal2);
				if (criminal2_dead_flag == 0) {
					total_criminals_killed++;
					criminal2_dead_flag = 1;
				}
				if (!IS_CHAR_DEAD(criminal2_thug1)) {
					criminal2 = criminal2_thug1;
					criminal2_thug1 = -1;
					criminal2_dead_flag = 0;
					criminal2_thug1_dead_flag = 1;
					ADD_BLIP_FOR_CHAR(criminal2, &criminal2_blip);
					if (!IS_CHAR_DEAD(criminal2_thug2)) {
						SET_GROUP_LEADER(criminal2_group, criminal2);
						SET_GROUP_MEMBER(criminal2_group, criminal2_thug2);
						if (!IS_GROUP_MEMBER(criminal2_thug2, criminal2_group)) {
							TASK_COMBAT(criminal2_thug2, GetPlayerPed());
						}
					}
					if (!IS_CHAR_DEAD(criminal2_thug3)) {
						SET_GROUP_LEADER(criminal2_group, criminal2);
						SET_GROUP_MEMBER(criminal2_group, criminal2_thug3);
						if (!IS_GROUP_MEMBER(criminal2_thug3, criminal2_group)) {
							TASK_COMBAT(criminal2_thug3, GetPlayerPed());
						}
					}
				} else {
					MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal2_thug1);
					if (!IS_CHAR_DEAD(criminal2_thug2)) {
						criminal2 = criminal2_thug2;
						criminal2_thug2 = -1;
						criminal2_dead_flag = 0;
						criminal2_thug2_dead_flag = 1;
						ADD_BLIP_FOR_CHAR(criminal2, &criminal2_blip);
						if (!IS_CHAR_DEAD(criminal2_thug3)) {
							SET_GROUP_LEADER(criminal2_group, criminal2);
							SET_GROUP_MEMBER(criminal2_group, criminal2_thug3);
							if (!IS_GROUP_MEMBER(criminal2_thug3, criminal2_group)) {
								TASK_COMBAT(criminal2_thug3, GetPlayerPed());
							}
						}
					} else {
						MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal2_thug2);
						if (!IS_CHAR_DEAD(criminal2_thug3)) {
							criminal2 = criminal2_thug3;
							criminal2_thug3 = -1;
							criminal2_dead_flag = 0;
							criminal2_thug3_dead_flag = 1;
							ADD_BLIP_FOR_CHAR(criminal2, &criminal2_blip);
						} else {
							MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal2_thug3);
							criminal2_team_dead_flag = 1;
						}
					}
				}
			}
			if (IS_CHAR_DEAD(criminal2_thug1)) {
				if (criminal2_thug1_dead_flag == 0) {
					total_criminals_killed++;
					criminal2_thug1_dead_flag = 1;
				}
			}
			if (IS_CHAR_DEAD(criminal2_thug2)) {
				if (criminal2_thug2_dead_flag == 0) {
					total_criminals_killed++;
					criminal2_thug2_dead_flag = 1;
				}
			}
			if (IS_CHAR_DEAD(criminal2_thug3)) {
				if (criminal2_thug3_dead_flag == 0) {
					total_criminals_killed++;
					criminal2_thug3_dead_flag = 1;
				}
			}
		}
		
		if (frame_counter == 2) {
			if (!IS_CHAR_DEAD(criminal3)) {
				if (IS_CHAR_SITTING_IN_ANY_CAR(criminal3)) {
					MARK_CAR_AS_NO_LONGER_NEEDED(&criminal3_car);
					STORE_CAR_CHAR_IS_IN_NO_SAVE(criminal3, &criminal3_car);
					if (criminal3_in_car_flag == -1) {
						GET_GROUP_SIZE(criminal3_group, &temp_group, &num_of_followers);
						if (num_of_followers > 0) {
							criminal3_timera = game_timer + 2000;
						} else {
							criminal3_timera = game_timer;
						}
						criminal3_in_car_flag = 0;
					}
					
					if (criminal3_in_car_flag == 0) {
						if (game_timer > criminal3_timera) {
							SET_DRIVE_TASK_CRUISE_SPEED(criminal3, 100.0);
							TASK_CAR_DRIVE_WANDER(criminal3, criminal3_car, 100.0, 2);
							if (break_convoy_flag == 0) {
								if (!IS_CAR_DEAD(criminal2_car)) {
									TASK_CAR_DRIVE_WANDER(criminal3, criminal3_car, 100.0, 2);
								} else {
									break_convoy_flag = 1;
								}
							}
							if (break_convoy_flag == 1) {
								MARK_CAR_AS_CONVOY_CAR(criminal3_car, 0);
								TASK_CAR_DRIVE_WANDER(criminal3, criminal3_car, 100.0, 2);
							}
							criminal3_car_stuck_timer_start = game_timer;
							criminal3_in_car_flag = 1;
							criminal3_car_stuck_flag = 0;
						}
					}
					if (criminal3_in_car_flag > 0) {
						if (IS_CHAR_IN_CAR(GetPlayerPed(), criminal3_car)) {
							TASK_COMBAT(criminal3, GetPlayerPed());
						}
						gosub_stuck_car = criminal3_car;
						car_stuck_flag = criminal3_car_stuck_flag;
						stuck_timer_start = criminal3_car_stuck_timer_start;
						stuck_x = criminal3_car_stuck_x;
						stuck_y = criminal3_car_stuck_y;
						stuck_z = criminal3_car_stuck_z;
						if (criminal3_car_speed > 0.0) {
							criminal_car_stuck_checks();
						}
						criminal3_car_stuck_flag = car_stuck_flag;
						criminal3_car_stuck_timer_start = stuck_timer_start;
						criminal3_car_stuck_x = stuck_x;
						criminal3_car_stuck_y = stuck_y;
						criminal3_car_stuck_z = stuck_z;
						if (criminal3_car_stuck_flag == -9) {
							TASK_FLEE_CHAR_ANY_MEANS(criminal3, criminal3_car, 250.0, -1, 0, 0, 0, 25.0);
							criminal3_car_stuck_flag = 0;
						}
						int enghp = GET_ENGINE_HEALTH(criminal3_car);
						if (!(enghp > 400)) {
							TASK_COMBAT(criminal3, GetPlayerPed());
						}
						if (!(enghp > 251)) {
							TASK_FLEE_CHAR_ANY_MEANS(criminal3, criminal3_car, 250.0, -1, 0, 0, 0, 25.0);
							criminal3_timera = game_timer + 2000;
						} else {
							criminal3_timera = game_timer;
						}
						
						criminal3_group_breaking();
						GET_CHAR_COORDINATES(criminal3, &criminal3_x, &criminal3_y, &z);
						x_temp = player_x - criminal3_x;
						y_temp = player_y - criminal3_y;
						x_temp = x_temp * x_temp;
						y_temp = y_temp * y_temp;
						sum_x_y_temp = x_temp + y_temp;
						sum_x_y_temp = SQRT(sum_x_y_temp);
						criminal3_car_speed = 1000.0 / sum_x_y_temp;
						if (criminal3_car_speed > 100.0) {
							criminal3_car_speed = 100.0;
						}
						if (criminal3_car_speed < 15.0) {
							criminal3_car_speed = 15.0;
						}
						if (break_convoy_flag == 0) {
							if (!IS_CAR_DEAD(criminal2_car)) {
								gosub_car_to_slow = criminal3_car;
								tar_entity = criminal2_car;
								slow_criminal_if_close();
								criminal3_car_speed = gosub_car_to_slow_speed;
								
								GET_CAR_FORWARD_X(criminal3_car, &forward_x);
								GET_CAR_FORWARD_Y(criminal3_car, &forward_y);
								GET_CAR_COORDINATES(criminal2_car, &criminal2_car_x, &criminal2_car_y, &z);
								GET_CAR_COORDINATES(criminal3_car, &criminal3_car_x, &criminal3_car_y, &z);
								temp_float_x = criminal3_car_x - criminal2_car_x;
								forward_x = forward_x * temp_float_x;
								temp_float_y = criminal3_car_y - criminal2_car_y;
								forward_y = forward_y * temp_float_y;
								car2_infront_car3 = forward_x + forward_y;
								
								GET_CAR_FORWARD_X(criminal2_car, &forward_x);
								GET_CAR_FORWARD_Y(criminal2_car, &forward_y);
								GET_CAR_COORDINATES(criminal3_car, &criminal3_car_x, &criminal3_car_y, &z);
								GET_CAR_COORDINATES(criminal2_car, &criminal2_car_x, &criminal2_car_y, &z);
								temp_float_x = criminal2_car_x - criminal3_car_x;
								forward_x = forward_x * temp_float_x;
								temp_float_y = criminal2_car_y - criminal3_car_y;
								forward_y = forward_y * temp_float_y;
								car3_infront_car2 = forward_x + forward_y;
								if (car2_infront_car3 > 0.0) {
									if (car3_infront_car2 < 0.0) {
										criminal3_car_speed = 0.0;
									}
								}
							} else {
								TASK_CAR_DRIVE_WANDER(criminal3, criminal3_car, 100.0, 2);
								break_convoy_flag = 1;
							}
						}
						if (criminal3_car_speed == 0.0) {
							TASK_CAR_TEMP_ACTION(criminal3, criminal3_car, 1, 17);
						} else {
							SET_DRIVE_TASK_CRUISE_SPEED(criminal3, criminal3_car_speed);
						}
					}
				} else {
					criminal3_in_car_flag = -1;
					criminal3_group_breaking();
					if (game_timer > criminal3_timera) {
						if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(GetPlayerPed(), criminal3, 40.0, 40.0, 0)) {
							if (!IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
								TASK_COMBAT(criminal3, GetPlayerPed());
							} else {
								if (LOCATE_CHAR_ANY_MEANS_CHAR_2D(GetPlayerPed(), criminal3, 25.0, 25.0, 0)) {
									TASK_COMBAT(criminal3, GetPlayerPed());
								} else {
									gosub_ped = criminal3;
									if (!IS_CAR_DEAD(criminal3_car)) {
										int enghp = GET_ENGINE_HEALTH(criminal3_car);
										if (enghp > 400) {
											if (LOCATE_CHAR_ANY_MEANS_CAR_2D(criminal3, criminal3_car, 40.0, 40.0, 0)) {
												TASK_ENTER_CAR_AS_DRIVER(criminal3, criminal3_car, -1);
											} else {
												criminal_steal_a_car();
											}
										} else {
											criminal_steal_a_car();
										}
									} else {
										criminal_steal_a_car();
									}
								}
							}
						} else {
							gosub_ped = criminal3;
							if (!IS_CAR_DEAD(criminal3_car)) {
								int enghp = GET_ENGINE_HEALTH(criminal3_car);
								if (enghp > 400) {
									if (LOCATE_CHAR_ANY_MEANS_CAR_2D(criminal3, criminal3_car, 40.0, 40.0, 0)) {
										TASK_ENTER_CAR_AS_DRIVER(criminal3, criminal3_car, -1);
									} else {
										criminal_steal_a_car();
									}
								} else {
									criminal_steal_a_car();
								}
							} else {
								criminal_steal_a_car();
							}
						}
					}
				}
			} else {
				REMOVE_BLIP(criminal3_blip);
				MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal3);
				if (criminal3_dead_flag == 0) {
					total_criminals_killed++;
					criminal3_dead_flag = 1;
				}
				if (!IS_CHAR_DEAD(criminal3_thug1)) {
					criminal3 = criminal3_thug1;
					criminal3_thug1 = -1;
					criminal3_dead_flag = 0;
					criminal3_thug1_dead_flag = 1;
					ADD_BLIP_FOR_CHAR(criminal3, &criminal3_blip);
					if (!IS_CHAR_DEAD(criminal3_thug2)) {
						SET_GROUP_LEADER(criminal3_group, criminal3);
						SET_GROUP_MEMBER(criminal3_group, criminal3_thug2);
						if (!IS_GROUP_MEMBER(criminal3_thug2, criminal3_group)) {
							TASK_COMBAT(criminal3_thug2, GetPlayerPed());
						}
					}
					if (!IS_CHAR_DEAD(criminal3_thug3)) {
						SET_GROUP_LEADER(criminal3_group, criminal3);
						SET_GROUP_MEMBER(criminal3_group, criminal3_thug3);
						if (!IS_GROUP_MEMBER(criminal3_thug3, criminal3_group)) {
							TASK_COMBAT(criminal3_thug3, GetPlayerPed());
						}
					}
				} else {
					MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal3_thug1);
					if (!IS_CHAR_DEAD(criminal3_thug2)) {
						criminal3 = criminal3_thug2;
						criminal3_thug2 = -1;
						criminal3_dead_flag = 0;
						criminal3_thug2_dead_flag = 1;
						ADD_BLIP_FOR_CHAR(criminal3, &criminal3_blip);
						if (!IS_CHAR_DEAD(criminal3_thug3)) {
							SET_GROUP_LEADER(criminal3_group, criminal3);
							SET_GROUP_MEMBER(criminal3_group, criminal3_thug3);
							if (!IS_GROUP_MEMBER(criminal3_thug3, criminal3_group)) {
								TASK_COMBAT(criminal3_thug3, GetPlayerPed());
							}
						}
					} else {
						MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal3_thug2);
						if (!IS_CHAR_DEAD(criminal3_thug3)) {
							criminal3 = criminal3_thug3;
							criminal3_thug3 = -1;
							criminal3_dead_flag = 0;
							criminal3_thug3_dead_flag = 1;
							ADD_BLIP_FOR_CHAR(criminal3, &criminal3_blip);
						} else {
							MARK_CHAR_AS_NO_LONGER_NEEDED(&criminal3_thug3);
							criminal3_team_dead_flag = 1;
						}
					}
				}
			}
			
			if (IS_CHAR_DEAD(criminal3_thug1)) {
				if (criminal3_thug1_dead_flag == 0) {
					total_criminals_killed++;
					criminal3_thug1_dead_flag = 1;
				}
			}
			if (IS_CHAR_DEAD(criminal3_thug2)) {
				if (criminal3_thug2_dead_flag == 0) {
					total_criminals_killed++;
					criminal3_thug2_dead_flag = 1;
				}
			}
			if (IS_CHAR_DEAD(criminal3_thug3)) {
				if (criminal3_thug3_dead_flag == 0) {
					total_criminals_killed++;
					criminal3_thug3_dead_flag = 1;
				}
			}
		}
		
		if ((criminal1_team_dead_flag == 1) && (criminal2_team_dead_flag == 1) && (criminal3_team_dead_flag == 1)) {
			mission_copcar_passed();
		}

		if (total_criminals_killed != old_total_criminals_killed)
		{
			INCREMENT_INT_STAT(STAT_CRIMINALS_KILLED, total_criminals_killed - old_total_criminals_killed);
		}
	}
}

void get_random_car_coords(void) {
	copcar_cancelled_checks();
	if (copcar_cancelled_flag == 1) {
		copcar_failed();
	}
	if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
	{
		copcar_failed();
	}
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_x, &player_y, &z);
	//IF flag_baron_mission2_passed = 0
	//	GENERATE_RANDOM_FLOAT_IN_RANGE -247.43 683.41 car1_x
	//	GENERATE_RANDOM_FLOAT_IN_RANGE -1813.62 1308.102 car1_y
	//ELSE
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1369.615, -985.473, 163.134, 2124.896, 0)) {
			GENERATE_RANDOM_FLOAT_IN_RANGE(-1369.615, 163.134, &car1_x);
			GENERATE_RANDOM_FLOAT_IN_RANGE(-985.473, 2124.896, &car1_y);
		} else {
			GENERATE_RANDOM_FLOAT_IN_RANGE(186.43, 1116.41, &car1_x);
			GENERATE_RANDOM_FLOAT_IN_RANGE(-1280.62, 1841.102, &car1_y);
		}
		
	car1_z = 5.0;
	if (copcar_level < 4) {
		GET_CLOSEST_CAR_NODE_WITH_HEADING(car1_x, car1_y, car1_z, &car1_x, &car1_y, &car1_z, &random_heading);
		car1_z += 0.5;
	}
	if ((copcar_level > 3) && (copcar_level < 8)) {
		Vector3 car1_vec, car2_vec;
		int temp1, temp2;
		float temp3;
		GET_CLOSEST_ROAD(car1_x, car1_y, car1_z, 8.0, 1, &car1_vec, &car2_vec, &temp1, &temp2, &temp3);
		car1_x = car1_vec.x;
		car1_y = car1_vec.y;
		car1_z = car1_vec.z;
		car2_x = car2_vec.x;
		car2_y = car2_vec.y;
		car2_z = car2_vec.z;
		if ((car1_x == 0.0) && (car1_y == 0.0) && (car2_x == 0.0) && (car2_y == 0.0)) {
			WAIT(0);
			get_random_car_coords();
		}
		dx = car2_x - car1_x;
		dy = car2_y - car1_y;
		temp_x = dx * dx;
		temp_y = dy * dy;
		temp_xy = temp_x + temp_y;
		temp_xy = SQRT(temp_xy);
		sum_x_y_temp = 8.0 / temp_xy;
		temp_x = dx * sum_x_y_temp;
		car2_x = car1_x + temp_x;
		temp_y = dy * sum_x_y_temp;
		car2_y = car1_y + temp_y;
		
		sum_x_y_temp = 2.0 / temp_xy;
		temp_x = dx * sum_x_y_temp;
		car1_x = car1_x + temp_x;
		temp_y = dy * sum_x_y_temp;
		car1_y = car1_y + temp_y;
		car1_z += 0.5;
		car2_z += 0.5;
	}
	if ((copcar_level > 7) && (copcar_level < 12)) {
		Vector3 car1_vec, car3_vec;
		int temp1, temp2;
		float temp3;
		GET_CLOSEST_ROAD(car1_x, car1_y, car1_z, 8.0, 1, &car1_vec, &car3_vec, &temp1, &temp2, &temp3);
		car1_x = car1_vec.x;
		car1_y = car1_vec.y;
		car1_z = car1_vec.z;
		car3_x = car3_vec.x;
		car3_y = car3_vec.y;
		car3_z = car3_vec.z;
		if ((car1_x == 0.0) && (car1_y == 0.0) && (car3_x == 0.0) && (car3_y == 0.0)) {
			WAIT(0);
			get_random_car_coords();
		}
		dx = car3_x - car1_x;
		dy = car3_y - car1_y;
		temp_x = dx * dx;
		temp_y = dy * dy;
		temp_xy = temp_x + temp_y;
		temp_xy = SQRT(temp_xy);
		sum_x_y_temp = 13.0 / temp_xy;
		temp_x = dx * sum_x_y_temp;
		car3_x = car1_x + temp_x;
		temp_y = dy * sum_x_y_temp;
		car3_y = car1_y + temp_y;
		
		sum_x_y_temp = 2.0 / temp_xy;
		temp_x = dx * sum_x_y_temp;
		car1_x = car1_x + temp_x;
		temp_y = dy * sum_x_y_temp;
		car1_y = car1_y + temp_y;
		car2_x = car1_x	- car3_x;
		car2_x = car2_x / 2.0;
		car2_x = car2_x	+ car3_x;
		
		car2_y = car1_y	- car3_y;
		car2_y = car2_y / 2.0;
		car2_y = car2_y	+ car3_y;
		
		car2_z = car1_z	- car3_z;
		car2_z = car2_z / 2.0;
		car2_z = car2_z	+ car3_z;
		
		car1_z += 0.5;
		car2_z += 0.5;
		car3_z += 0.5;
	}
	if (car1_z < 2.0) {
		WAIT(0);
		get_random_car_coords();
	}
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_x, &player_y, &player_z);
	GET_DISTANCE_BETWEEN_COORDS_2D(player_x, player_y, car1_x, car1_y, &distance_from_player);
	if ((distance_from_player < 150.0) || (distance_from_player > 600.0)) {
		WAIT(0);
		get_random_car_coords();
	}
	if ((car1_x > -1472.785) && (car1_x < -672.785) && (car1_y > 1278.678) && (car1_y < 2306.513)) {
		WAIT(0);
		get_random_car_coords();
	}
	if ((car1_x > 168.018) && (car1_x < 603.188) && (car1_y > 258.942) && (car1_y < 2222.059)) {
		WAIT(0);
		get_random_car_coords();
	}
	if ((car1_x > 597.191) && (car1_x < 692.713) && (car1_y > 346.926) && (car1_y < 1164.97)) {
		WAIT(0);
		get_random_car_coords();
	}
	if ((car1_x > -298.729) && (car1_x < 170.334) && (car1_y > 529.399) && (car1_y < 595.853)) {
		WAIT(0);
		get_random_car_coords();
	}
	if ((car1_x > 253.88) && (car1_x < 497.112) && (car1_y > 34.183) && (car1_y < 116.519)) {
		WAIT(0);
		get_random_car_coords();
	}
	if ((car1_x > -329.855) && (car1_x < 261.566) && (car1_y > -134.099) && (car1_y < 309.382)) {
		WAIT(0);
		get_random_car_coords();
	}
	/*if (flag_baron_mission2_passed == 0) {
		if ((car1_x > -1894.212) && (car1_x < 172.402) && (car1_y > -1494.821) && (car1_y < 2427.426)) {
			WAIT(0);
			get_random_car_coords();
		}
		if ((car1_x > 168.018) && (car1_x < 603.188) && (car1_y > 258.942) && (car1_y < 2222.059)) {
			WAIT(0);
			get_random_car_coords();
		}
		if ((car1_x > 168.657) && (car1_x < 469.828) && (car1_y > -196.217) && (car1_y < 258.488)) {
			WAIT(0);                                                                                                                                                                                          
			get_random_car_coords();
		}
		if ((car1_x > 597.191) && (car1_x < 692.713) && (car1_y > 346.926) && (car1_y < 1164.97)) {
			WAIT(0);
			get_random_car_coords();
		}
	}*/
	
	GENERATE_RANDOM_INT(&random_seed);
	while (random_seed == 0) {
		GENERATE_RANDOM_INT(&random_seed);
	}
	while (!HAS_MODEL_LOADED(random_car_model)) {
		WAIT(0);
		copcar_cancelled_checks();
		if (copcar_cancelled_flag == 1) {
			copcar_failed();
		}
		if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
		{
			copcar_failed();
		}
	}
	CREATE_CAR(random_car_model, car1_x, car1_y, car1_z, &criminal1_car, 1);
	SET_ENGINE_HEALTH(criminal1_car, 800);
	SET_CAR_RANDOM_ROUTE_SEED(criminal1_car, random_seed);
	MARK_CAR_AS_CONVOY_CAR(criminal1_car, 1);
	SET_CAR_HEADING(criminal1_car, random_heading);
	SET_CAR_ON_GROUND_PROPERLY(criminal1_car);
	CREATE_RANDOM_CHAR_AS_DRIVER(criminal1_car, &criminal1);
	REMOVE_BLIP(criminal1_blip);
	ADD_BLIP_FOR_CHAR(criminal1, &criminal1_blip);
	ped = criminal1;
	setup_ped_threats_etc();
	if (copcar_level > 0) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(criminal1_car, 0, &criminal1_thug1);
		ped = criminal1_thug1;
		setup_ped_threats_etc();
	} else {
		criminal1_thug1_dead_flag = 1;
	}
	
	if (copcar_level > 1) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(criminal1_car, 1, &criminal1_thug2);
		ped = criminal1_thug2;
		setup_ped_threats_etc();
	} else {
		criminal1_thug2_dead_flag = 1;
	}
	
	if (copcar_level > 2) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(criminal1_car, 2, &criminal1_thug3);
		ped = criminal1_thug3;
		setup_ped_threats_etc();
	} else {
		criminal1_thug3_dead_flag = 1;
	}
	
	if (copcar_level > 3) {
		CREATE_CAR(random_car_model, car2_x, car2_y, car2_z, &criminal2_car, 1);
		MARK_CAR_AS_CONVOY_CAR(criminal2_car, 1);
		SET_CAR_HEADING(criminal2_car, random_heading);
		SET_CAR_ON_GROUND_PROPERLY(criminal2_car);
		SET_ENGINE_HEALTH(criminal2_car, 800);
		SET_CAR_RANDOM_ROUTE_SEED(criminal2_car, random_seed);
		while (IS_CAR_WAITING_FOR_WORLD_COLLISION(criminal2_car)) {
			WAIT(0);
			if (IS_CAR_DEAD(criminal2_car)) {
				copcar_failed();
			}
			if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
			{
				copcar_failed();
			}
			copcar_cancelled_checks();
			if (copcar_cancelled_flag == 1) {
				copcar_failed();
			}
		}	
		CREATE_RANDOM_CHAR_AS_DRIVER(criminal2_car, &criminal2);
		ped = criminal2;
		setup_ped_threats_etc();
		REMOVE_BLIP(criminal2_blip);
		ADD_BLIP_FOR_CHAR(criminal2, &criminal2_blip);
	} else {
		criminal2_team_dead_flag = 1;
		criminal2_dead_flag = 1;
	}
	
	if (copcar_level > 4) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(criminal2_car, 0, &criminal2_thug1);
		ped = criminal2_thug1;
		setup_ped_threats_etc();
	} else {
		criminal2_thug1_dead_flag = 1;
	}
	
	if (copcar_level > 5) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(criminal2_car, 1, &criminal2_thug2);
		ped = criminal2_thug2;
		setup_ped_threats_etc();
	} else {
		criminal2_thug2_dead_flag = 1;
	}
	
	if (copcar_level > 6) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(criminal2_car, 2, &criminal2_thug3);
		ped = criminal2_thug3;
		setup_ped_threats_etc();
	} else {
		criminal2_thug3_dead_flag = 1;
	}
	
	if (copcar_level > 7) {
		CREATE_CAR(random_car_model, car3_x, car3_y, car3_z, &criminal3_car, 1);
		MARK_CAR_AS_CONVOY_CAR(criminal3_car, 1);
		SET_CAR_HEADING(criminal3_car, random_heading);
		SET_CAR_ON_GROUND_PROPERLY(criminal3_car);
		SET_ENGINE_HEALTH(criminal3_car, 800);
		SET_CAR_RANDOM_ROUTE_SEED(criminal3_car, random_seed);
		while (IS_CAR_WAITING_FOR_WORLD_COLLISION(criminal3_car)) {
			WAIT(0);
			if (IS_CAR_DEAD(criminal3_car)) {
				copcar_failed();
			}
			if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
			{
				copcar_failed();
			}
			copcar_cancelled_checks();
			if (copcar_cancelled_flag == 1) {
				copcar_failed();
			}
		}	
		CREATE_RANDOM_CHAR_AS_DRIVER(criminal3_car, &criminal3);
		ped = criminal3;
		setup_ped_threats_etc();
		REMOVE_BLIP(criminal3_blip);
		ADD_BLIP_FOR_CHAR(criminal3, &criminal3_blip);
	} else {
		criminal3_team_dead_flag = 1;
		criminal3_dead_flag = 1;
	}
	
	if (copcar_level > 8) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(criminal3_car, 0, &criminal3_thug1);
		ped = criminal3_thug1;
		setup_ped_threats_etc();
	} else {
		criminal3_thug1_dead_flag = 1;
	}
	
	if (copcar_level > 9) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(criminal3_car, 1, &criminal3_thug2);
		ped = criminal3_thug2;
		setup_ped_threats_etc();
	} else {
		criminal3_thug2_dead_flag = 1;
	}
	
	if (copcar_level > 10) {
		CREATE_RANDOM_CHAR_AS_PASSENGER(criminal3_car, 2, &criminal3_thug3);
		ped = criminal3_thug3;
		setup_ped_threats_etc();
	} else {
		criminal3_thug3_dead_flag = 1;
	}
	
	MARK_MODEL_AS_NO_LONGER_NEEDED(random_car_model);
	copcar_print_level = copcar_level + 1;
	PRINT_WITH_NUMBER_NOW("CLEVEL", copcar_print_level, 2500, 1);
	WAIT(2500);
	print_text_for_zone_char_is_in();
	GET_CHAR_COORDINATES(criminal1, &criminal1_x, &criminal1_y, &z);
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_x, &player_y, &player_z);
	x_temp = player_x - criminal1_x;
	y_temp = player_y - criminal1_y;
	x_temp = x_temp * x_temp;
	y_temp = y_temp * y_temp;
	player_dist_from_crim = y_temp + y_temp;
	player_dist_from_crim = SQRT(player_dist_from_crim);
	
	player_dist_from_crim /= time_bonus_divider;
	player_dist_from_crim *= 1000.0;
	cop_time_limit_int = player_dist_from_crim;
	if (cop_time_limit_int < 40000) {
		cop_time_limit_int = 40000;
	}
	cop_time_limit += cop_time_limit_int;
	cop_time_limit_int /= 1000;
	
	if (timer_on_screen_flag == 1) {
		SETTIMERA(0); //сбрасываем таймер 
		while (true)
		{
			SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "A_TIME", cop_time_limit_int);//
			
			WAIT( 0 );
			if ( TIMERA() > 4000 )
			{
				break;
			}
		}
		//PRINT_WITH_NUMBER_BIG("A_TIME", cop_time_limit_int, 4000, 6);
	} else {
		if (cop_time_limit < 45000) {
			cop_time_limit = 45000;
		}
		cop_time_limit += 30000;
		timer_on_screen_flag = 1;
	}
	
	GET_GAME_TIMER(&game_timer);
	criminal1_timera = game_timer;
	criminal2_timera = game_timer;
	criminal3_timera = game_timer;
	CREATE_GROUP(0, &criminal1_group, 1);
	CREATE_GROUP(0, &criminal2_group, 1);
	CREATE_GROUP(0, &criminal3_group, 1);	
	if (copcar_level < 13) {
		time_bonus_divider -= 0.1;
	}
	copcar_oddjob_loop();
}

void request_random_car_model(void) {
	if (copcar_level > 1) {
		GENERATE_RANDOM_INT_IN_RANGE(26, 37, &random_int);
	} else {
		GENERATE_RANDOM_INT_IN_RANGE(0, 37, &random_int);
	}
	
	if (random_int == 0) {
		random_car_model = GET_HASH_KEY("pcj");
	}
	if (random_int == 1) {
		random_car_model = GET_HASH_KEY("faggio");
	}
	if (random_int == 2) {
		random_car_model = GET_HASH_KEY("zombieb");
	}
	if (random_int == 3) {
		random_car_model = GET_HASH_KEY("sanchez");
	}
	if (random_int == 4) {
		random_car_model = GET_HASH_KEY("comet");
	}
	if (random_int == 5) {
		random_car_model = GET_HASH_KEY("coquette");
	}
	if (random_int == 6) {
		random_car_model = GET_HASH_KEY("infernus");
	}
	if (random_int == 7) {
		random_car_model = GET_HASH_KEY("supergt");
	}
	if (random_int == 8) {
		random_car_model = GET_HASH_KEY("banshee");
	}
	if (random_int == 9) {
		random_car_model = GET_HASH_KEY("ruiner");
	}
	if (random_int == 10) {
		random_car_model = GET_HASH_KEY("habanero");
	}
	if (random_int == 11) {
		random_car_model = GET_HASH_KEY("emperor");
	}
	if (random_int == 12) {
		random_car_model = GET_HASH_KEY("phantom");
	}
	if (random_int == 13) {
		random_car_model = GET_HASH_KEY("manana");
	}
	if (random_int == 14) {
		random_car_model = GET_HASH_KEY("pony");
	}
	if (random_int == 15) {
		random_car_model = GET_HASH_KEY("mule");
	}
	if (random_int == 16) {
		random_car_model = GET_HASH_KEY("bobcat");
	}
	if (random_int == 17) {
		random_car_model = GET_HASH_KEY("esperanto");
	}
	if (random_int == 18) {
		random_car_model = GET_HASH_KEY("mrtasty");
	}
	if (random_int == 19) {
		random_car_model = GET_HASH_KEY("stalion");
	}
	if (random_int == 20) {
		random_car_model = GET_HASH_KEY("yankee");
	}
	if (random_int == 21) {
		random_car_model = GET_HASH_KEY("sabre");
	}
	if (random_int == 22) {
		random_car_model = GET_HASH_KEY("burrito");
	}
	if (random_int == 23) {
		random_car_model = GET_HASH_KEY("e109");
	}
	if (random_int == 24) {
		random_car_model = GET_HASH_KEY("perennial");
	}
	if (random_int == 25) {
		random_car_model = GET_HASH_KEY("steed");
	}
	if (random_int == 26) {
		random_car_model = GET_HASH_KEY("sentinel");
	}
	if (random_int == 27) {
		random_car_model = GET_HASH_KEY("moonbeam");
	}
	if (random_int == 28) {
		random_car_model = GET_HASH_KEY("washington");
	}
	if (random_int == 29) {
		random_car_model = GET_HASH_KEY("landstalker");
	}
	if (random_int == 30) {
		random_car_model = GET_HASH_KEY("stratum");
	}
	if (random_int == 31) {
		random_car_model = GET_HASH_KEY("admiral");
	}
	if (random_int == 32) {
		random_car_model = GET_HASH_KEY("marbella");
	}
	if (random_int == 33) {
		random_car_model = GET_HASH_KEY("pmp600");
	}
	if (random_int == 34) {
		random_car_model = GET_HASH_KEY("pinnacle");
	}
	if (random_int == 35) {
		random_car_model = GET_HASH_KEY("ingot");
	}
	if (random_int == 36) {
		random_car_model = GET_HASH_KEY("sultanrs");
	}
	REQUEST_MODEL(random_car_model);
	return;
}

void next_criminal_to_kill(void) {
	criminal1_team_dead_flag = 0;
	criminal2_team_dead_flag = 0;
	criminal3_team_dead_flag = 0;
	break_convoy_flag = 0;

	criminal1_in_car_flag = 0;
	criminal1_car_stuck_timer_start = 0;
	criminal1_car_stuck_flag = 0;
	criminal1_dead_flag = 0;
	criminal1_thug1_dead_flag = 0;
	criminal1_thug2_dead_flag = 0;
	criminal1_thug3_dead_flag = 0;

	criminal2_in_car_flag = 0;
	criminal2_car_stuck_timer_start = 0;
	criminal2_car_stuck_flag = 0;
	criminal2_dead_flag = 0;
	criminal2_thug1_dead_flag = 0;
	criminal2_thug2_dead_flag = 0;
	criminal2_thug3_dead_flag = 0;

	criminal3_in_car_flag = 0;
	criminal3_car_stuck_timer_start = 0;
	criminal3_car_stuck_flag = 0;
	criminal3_dead_flag = 0;
	criminal3_thug1_dead_flag = 0;
	criminal3_thug2_dead_flag = 0;
	criminal3_thug3_dead_flag = 0;

	car1_infront_car2 = 0.0;
	car2_infront_car1 = 0.0;
	car2_infront_car3 = 0.0;
	car3_infront_car2 = 0.0;

	frame_counter = 0;	
	request_random_car_model();
	get_random_car_coords();
}

void mission_start_copcar(void) {
	WAIT(0);
	if (G_COPCAR == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}
	LOAD_ADDITIONAL_TEXT("COPCAR", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	copcar_level = 0;
	cop_time_limit = -100;
	copcar_cancelled_flag = 0;
	total_criminals_killed = 0;
	timer_on_screen_flag = 0;
	mission_end_button = 0;
	break_convoy_flag = 0;
	game_timer_start = 0;
	players_cop_car_health = 0;
	vigilante_score = 0;
	num_of_followers = 0;
	copcar_timer = 0;
	game_time_flag = 0;
	game_time_present = 0;
	game_time_difference = 0;
	timer_in_secs = 0;
	cop_time_limit_int = 0;
	random_car_model = 0;
	random_ped_model = 0;
	time_bonus_divider = 4.0;
	wanted_level_multiplier = 1.0;
	in_copcar_nice_timer = 0;

	heading = 0.0;
	gosub_car_to_slow_speed = 0.0;

	criminal1_car_stuck_x = 0.0;
	criminal1_car_stuck_y = 0.0;
	criminal1_car_stuck_z = 0.0;
	criminal1_car_speed = 0.0;

	criminal2_car_stuck_x = 0.0;
	criminal2_car_stuck_y = 0.0;
	criminal2_car_stuck_z = 0.0;
	criminal2_car_speed = 0.0;

	criminal3_car_stuck_x = 0.0;
	criminal3_car_stuck_y = 0.0;
	criminal3_car_stuck_z = 0.0;
	criminal3_car_speed = 0.0;
	SET_WANTED_MULTIPLIER(0.5);
	if (IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
		STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &players_cop_car);
		SET_CAN_BURST_CAR_TYRES(players_cop_car, 0);
		SWITCH_CAR_SIREN(players_cop_car, 1);
	}

	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		WAIT( 0 );
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста

		if (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("buzzard")) || IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("annihilator"))) {
			DISPLAY_TEXT(0.5, 0.45, "COP_M3");//
		} else if (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("noose"))) {
			DISPLAY_TEXT(0.5, 0.45, "COP_M2");//
		} else {
			DISPLAY_TEXT(0.5, 0.45, "COP_M");//
		}
		
		if ( TIMERA() > 3000 )
		{
			break;
		}
	}

	next_criminal_to_kill();
}

void main(void) {

	mission_start_copcar();
	copcar_failed();

	/*while (true) {
		WAIT(0);
		if ((IS_CHAR_IN_ANY_POLICE_VEHICLE(GetPlayerPed())) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("annihilator"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("fbi")))) {
			if (G_ONMISSION == 0) {
				if (incopcar == 0) {
					PRINT_HELP("CTUTOR");
					incopcar = 1;
				}
				if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER()))) {
					G_ONMISSION = 1;
					mission_start_copcar();
					if (HAS_DEATHARREST_EXECUTED()) {
						copcar_failed();
					}
					mission_cleanup_copcar();
					copcar_failed();
					G_ONMISSION = 0;
					WAIT(1000);
				}
			}
		} else {
			CLEAR_HELP();
			incopcar = 0;
		}
	}*/
}