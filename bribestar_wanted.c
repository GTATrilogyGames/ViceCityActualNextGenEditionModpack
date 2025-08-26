#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "features.h"



#define TOUCH_DISTANCE_ONFOOT	1.0
#define TOUCH_DISTANCE_INVEH	2.0

#define RESPAWN_TIME	300



struct bribestar
{
	int number;
	Object var;
	int resp_time;
};


struct bribestar bribe_1, bribe_2, bribe_3, bribe_4, bribe_5, bribe_6, bribe_7, bribe_8, bribe_9, bribe_10, bribe_11, bribe_12, bribe_13;

int always_wanted_mode = 0;
Ped ghost_cop;


int time_of_day_seconds_prev = -1;
int time_of_day_seconds_current = -1;



int big_time_pass()			/* проверка, был ли большой скачок времени вперёд */
{
	uint hours, minutes;
	GET_TIME_OF_DAY(&hours, &minutes);
	time_of_day_seconds_current = minutes*60 + hours*3600;
	if (time_of_day_seconds_prev == -1)
	{
		time_of_day_seconds_prev = time_of_day_seconds_current;
		return;
	}
	int time_diff_seconds = 0;
	if (time_of_day_seconds_current > time_of_day_seconds_prev)	/*не было перехода через 24 часа*/
	{
		time_diff_seconds = time_of_day_seconds_current - time_of_day_seconds_prev;
	}
	else if (time_of_day_seconds_current < time_of_day_seconds_prev)	/*был переход через 24 часа*/
	{
		int prev_day_part = (60*60*24) - time_of_day_seconds_prev;
		time_diff_seconds = prev_day_part + time_of_day_seconds_current;
	}
	time_of_day_seconds_prev = time_of_day_seconds_current;
	if (time_diff_seconds >= RESPAWN_TIME)
	{
		return 1;
	}
	return 0;
}


void bribe_coords(int bribe_num, float *x, float *y, float *z)
{
	if (bribe_num == 1)
	{
		*x = 549.96;
		*y = -779.49;
		*z = -0.59;
	}
	else if (bribe_num == 2)
	{
		*x = 826.65;
		*y = -126.5;
		*z = 5.73;
	}
	else if (bribe_num == 3)
	{
		*x = 826.47;
		*y = 472.96;
		*z = 6.48;
	}
	else if (bribe_num == 4)
	{
		*x = 904.97;
		*y = 602.69;
		*z = 6.16;
	}
	else if (bribe_num == 5)
	{
		*x = 815.12;
		*y = 897.82;
		*z = 6.04;
	}
	else if (bribe_num == 6)
	{
		*x = 855.7;
		*y = 1503.92;
		*z = 7.35;
	}
	else if (bribe_num == 7)
	{
		*x = 522.06;
		*y = 1420.37;
		*z = 5.72;
	}
	else if (bribe_num == 8)
	{
		*x = -388.78;
		*y = 1838.14;
		*z = 6.63;
	}
	else if (bribe_num == 9)
	{
		*x = -467.9;
		*y = 784.87;
		*z = 13.5;
	}
	else if (bribe_num == 10)
	{
		*x = -540.96;
		*y = 594.11;
		*z = 5.59;
	}
	else if (bribe_num == 11)
	{
		*x = -502.56;
		*y = 418.76;
		*z = 12.0;
	}
	else if (bribe_num == 12)
	{
		*x = -582.74;
		*y = -94.91;
		*z = 6.48;
	}
	else if (bribe_num == 13)
	{
		*x = -473.4;
		*y = -301.13;
		*z = 11.5;
	}
}


void create_bribestar(struct bribestar *bribe)
{
	REQUEST_MODEL(GET_HASH_KEY("bribestar"));
	while (!HAS_MODEL_LOADED(GET_HASH_KEY("bribestar"))) WAIT(0);	
	REQUEST_ANIMS("pink_tablet");
	while (!HAVE_ANIMS_LOADED("pink_tablet")) WAIT(0);
	float x, y, z;
	bribe_coords(bribe->number, &x, &y, &z);
	CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("bribestar"), x, y, z, &(bribe->var), 1);
	PLAY_OBJECT_ANIM(bribe->var, "bribestar", "pink_tablet", 10.0, 1, 0);
}


void touch_bribestar(struct bribestar *bribe)
{
	int wanted_level;
	STORE_WANTED_LEVEL(GetPlayerIndex(), &wanted_level);
	if (wanted_level < 1)
	{
		return;
	}
	wanted_level -= 1;
	ALTER_WANTED_LEVEL(GetPlayerIndex(), wanted_level);
	APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
	DELETE_OBJECT(&(bribe->var));
	PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
	bribe->resp_time = RESPAWN_TIME;
}


void monitor_bribestar(struct bribestar *bribe)
{
	if (bribe->var == INVALID_HANDLE)
	{
		return;
	}
	Vehicle car;
	GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car);
	float player_x;
	float player_y;
	float player_z;
	float bribe_x;
	float bribe_y;
	float bribe_z;
	bribe_coords(bribe->number, &bribe_x, &bribe_y, &bribe_z);
	float dist;
	if (car == INVALID_HANDLE)		/*пешком*/
	{
		GET_CHAR_COORDINATES(GetPlayerPed(), &player_x, &player_y, &player_z);
		GET_DISTANCE_BETWEEN_COORDS_3D(player_x, player_y, player_z, bribe_x, bribe_y, bribe_z, &dist);
		if (dist < TOUCH_DISTANCE_ONFOOT)
		{
			touch_bribestar(bribe);
		}
	}
	else		/*внутри транспорта*/
	{
		GET_CAR_COORDINATES(car, &player_x, &player_y, &player_z);
		GET_DISTANCE_BETWEEN_COORDS_3D(player_x, player_y, player_z, bribe_x, bribe_y, bribe_z, &dist);
		if (dist < TOUCH_DISTANCE_INVEH)
		{
			touch_bribestar(bribe);
		}
	}
}


void decrement_resp_time()
{
	if (bribe_1.resp_time > 0)
	{
		bribe_1.resp_time -= 1;
	}
	if (bribe_2.resp_time > 0)
	{
		bribe_2.resp_time -= 1;
	}
	if (bribe_3.resp_time > 0)
	{
		bribe_3.resp_time -= 1;
	}
	if (bribe_4.resp_time > 0)
	{
		bribe_4.resp_time -= 1;
	}
	if (bribe_5.resp_time > 0)
	{
		bribe_5.resp_time -= 1;
	}
	if (bribe_6.resp_time > 0)
	{
		bribe_6.resp_time -= 1;
	}
	if (bribe_7.resp_time > 0)
	{
		bribe_7.resp_time -= 1;
	}
	if (bribe_8.resp_time > 0)
	{
		bribe_8.resp_time -= 1;
	}
	if (bribe_9.resp_time > 0)
	{
		bribe_9.resp_time -= 1;
	}
	if (bribe_10.resp_time > 0)
	{
		bribe_10.resp_time -= 1;
	}
	if (bribe_11.resp_time > 0)
	{
		bribe_11.resp_time -= 1;
	}
	if (bribe_12.resp_time > 0)
	{
		bribe_12.resp_time -= 1;
	}
	if (bribe_13.resp_time > 0)
	{
		bribe_13.resp_time -= 1;
	}
}


void check_respawn()
{
	if ((bribe_1.var == INVALID_HANDLE) && (bribe_1.resp_time <= 0))
	{
		create_bribestar(&bribe_1);
	}
	if ((bribe_2.var == INVALID_HANDLE) && (bribe_2.resp_time <= 0))
	{
		create_bribestar(&bribe_2);
	}
	if ((bribe_3.var == INVALID_HANDLE) && (bribe_3.resp_time <= 0))
	{
		create_bribestar(&bribe_3);
	}
	if ((bribe_4.var == INVALID_HANDLE) && (bribe_4.resp_time <= 0))
	{
		create_bribestar(&bribe_4);
	}
	if ((bribe_5.var == INVALID_HANDLE) && (bribe_5.resp_time <= 0))
	{
		create_bribestar(&bribe_5);
	}
	if ((bribe_6.var == INVALID_HANDLE) && (bribe_6.resp_time <= 0))
	{
		create_bribestar(&bribe_6);
	}
	if ((bribe_7.var == INVALID_HANDLE) && (bribe_7.resp_time <= 0))
	{
		create_bribestar(&bribe_7);
	}
	if ((bribe_8.var == INVALID_HANDLE) && (bribe_8.resp_time <= 0))
	{
		create_bribestar(&bribe_8);
	}
	if ((bribe_9.var == INVALID_HANDLE) && (bribe_9.resp_time <= 0))
	{
		create_bribestar(&bribe_9);
	}
	if ((bribe_10.var == INVALID_HANDLE) && (bribe_10.resp_time <= 0))
	{
		create_bribestar(&bribe_10);
	}
	if ((bribe_11.var == INVALID_HANDLE) && (bribe_11.resp_time <= 0))
	{
		create_bribestar(&bribe_11);
	}
	if ((bribe_12.var == INVALID_HANDLE) && (bribe_12.resp_time <= 0))
	{
		create_bribestar(&bribe_12);
	}
	if ((bribe_13.var == INVALID_HANDLE) && (bribe_13.resp_time <= 0))
	{
		create_bribestar(&bribe_13);
	}
}


void respawn_all()
{
	if (bribe_1.var == INVALID_HANDLE)
	{
		create_bribestar(&bribe_1);
		bribe_1.resp_time = 0;
	}
	if (bribe_2.var == INVALID_HANDLE)
	{
		create_bribestar(&bribe_2);
		bribe_2.resp_time = 0;
	}
	if (bribe_3.var == INVALID_HANDLE)
	{
		create_bribestar(&bribe_3);
		bribe_3.resp_time = 0;
	}
	if (bribe_4.var == INVALID_HANDLE)
	{
		create_bribestar(&bribe_4);
		bribe_4.resp_time = 0;
	}
	if (bribe_5.var == INVALID_HANDLE)
	{
		create_bribestar(&bribe_5);
		bribe_5.resp_time = 0;
	}
	if (bribe_6.var == INVALID_HANDLE)
	{
		create_bribestar(&bribe_6);
		bribe_6.resp_time = 0;
	}
	if (bribe_7.var == INVALID_HANDLE)
	{
		create_bribestar(&bribe_7);
		bribe_7.resp_time = 0;
	}
	if (bribe_8.var == INVALID_HANDLE)
	{
		create_bribestar(&bribe_8);
		bribe_8.resp_time = 0;
	}
	if (bribe_9.var == INVALID_HANDLE)
	{
		create_bribestar(&bribe_9);
		bribe_9.resp_time = 0;
	}
	if (bribe_10.var == INVALID_HANDLE)
	{
		create_bribestar(&bribe_10);
		bribe_10.resp_time = 0;
	}
	if (bribe_11.var == INVALID_HANDLE)
	{
		create_bribestar(&bribe_11);
		bribe_11.resp_time = 0;
	}
	if (bribe_12.var == INVALID_HANDLE)
	{
		create_bribestar(&bribe_12);
		bribe_12.resp_time = 0;
	}
	if (bribe_13.var == INVALID_HANDLE)
	{
		create_bribestar(&bribe_13);
		bribe_13.resp_time = 0;
	}
}


int near_paynspray()
{
	Ped player_ped = GetPlayerPed();
	if ( IS_CHAR_IN_AREA_2D(player_ped, 416.0,-718.0, 436.0,-730.0, 0)
	|| IS_CHAR_IN_AREA_2D(player_ped, 747.0,971.0, 770.0,955.0, 0)
	|| IS_CHAR_IN_AREA_2D(player_ped, -453.0,425.0, -426.0,403.0, 0)
	|| IS_CHAR_IN_AREA_2D(player_ped, -585.0,-297.0, -563.0,-325.0, 0)
	|| IS_CHAR_IN_AREA_2D(player_ped, -489.0,-713.0, -473.0,-745.0, 0) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void wanted_checks()
{
	int wanted_level;
	STORE_WANTED_LEVEL(GetPlayerIndex(), &wanted_level);
	float player_x;
	float player_y;
	float player_z;
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_x, &player_y, &player_z);
	if (wanted_level > 1)
	{
		if (!always_wanted_mode)
		{
			uint cop_model;
			GET_CURRENT_BASIC_COP_MODEL(&cop_model);
			CREATE_CHAR(RELATIONSHIP_GROUP_PLAYER, cop_model, player_x, player_y, player_z + 5.0, &ghost_cop, 1);
			SET_CHAR_INVINCIBLE(ghost_cop, 1);
			SET_CHAR_COLLISION(ghost_cop, 0);
			SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ghost_cop, 1);
			REMOVE_ALL_CHAR_WEAPONS(ghost_cop);
			SET_CHAR_VISIBLE(ghost_cop, 0);
			always_wanted_mode = 1;
		}
	}
	else
	{
		if (always_wanted_mode)
		{
			DELETE_CHAR(&ghost_cop);
			always_wanted_mode = 0;
		}
	}
	if (always_wanted_mode)
	{
		float vertical_dist;
		if ( near_paynspray() )
		{
			vertical_dist = 60.0;		/* чтобы невидимый коп не засекал нас, пока мы заезжаем в перекраску */
		}
		else
		{
			vertical_dist = 5.0;
		}
		SET_CHAR_COORDINATES_NO_OFFSET(ghost_cop, player_x, player_y, player_z + vertical_dist);
	}
}


void mute_ghost_cop()
{
	if (IS_ANY_SPEECH_PLAYING(ghost_cop))
	{
		CANCEL_CURRENTLY_PLAYING_AMBIENT_SPEECH(ghost_cop);
	}
}


void monitor()
{
	SETTIMERA(0);
	while (1)
	{
		monitor_bribestar(&bribe_1);
		monitor_bribestar(&bribe_2);
		monitor_bribestar(&bribe_3);
		monitor_bribestar(&bribe_4);
		monitor_bribestar(&bribe_5);
		monitor_bribestar(&bribe_6);
		monitor_bribestar(&bribe_7);
		monitor_bribestar(&bribe_8);
		monitor_bribestar(&bribe_9);
		monitor_bribestar(&bribe_10);
		monitor_bribestar(&bribe_11);
		monitor_bribestar(&bribe_12);
		monitor_bribestar(&bribe_13);
		if (TIMERA() >= 1000)
		{
			decrement_resp_time();
			check_respawn();
			if ( big_time_pass() )
			{
				respawn_all();
			}
			#if !defined DISABLE_STICKY_WANTED_ZONE
			wanted_checks();
			#endif
			SETTIMERA(0);
		}
		if (always_wanted_mode)
		{
			mute_ghost_cop();
		}
		WAIT(0);
	}
}


void main(void)
{
	bribe_1.number = 1;
	bribe_2.number = 2;
	bribe_3.number = 3;
	bribe_4.number = 4;
	bribe_5.number = 5;
	bribe_6.number = 6;
	bribe_7.number = 7;
	bribe_8.number = 8;
	bribe_9.number = 9;
	bribe_10.number = 10;
	bribe_11.number = 11;
	bribe_12.number = 12;
	bribe_13.number = 13;
	bribe_1.resp_time = 0;
	bribe_2.resp_time = 0;
	bribe_3.resp_time = 0;
	bribe_4.resp_time = 0;
	bribe_5.resp_time = 0;
	bribe_6.resp_time = 0;
	bribe_7.resp_time = 0;
	bribe_8.resp_time = 0;
	bribe_9.resp_time = 0;
	bribe_10.resp_time = 0;
	bribe_11.resp_time = 0;
	bribe_12.resp_time = 0;
	bribe_13.resp_time = 0;
	
	create_bribestar(&bribe_1);
	create_bribestar(&bribe_2);
	create_bribestar(&bribe_3);
	create_bribestar(&bribe_4);
	create_bribestar(&bribe_5);
	create_bribestar(&bribe_6);
	create_bribestar(&bribe_7);
	create_bribestar(&bribe_8);
	create_bribestar(&bribe_9);
	create_bribestar(&bribe_10);
	create_bribestar(&bribe_11);
	create_bribestar(&bribe_12);
	create_bribestar(&bribe_13);
	monitor();
}










