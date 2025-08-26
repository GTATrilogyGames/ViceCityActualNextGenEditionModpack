#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"

#define MAX_STUNT_JUMPS 36
#define STUNT_JUMP_NONE 0
#define STUNT_JUMP_SUCCESS 1
#define STUNT_JUMP_FAIL 2

typedef struct _STUNT_JUMP
{
	float speed;
	float distance;
	float x;
	float y;
	float z;
	float camera_x;
	float camera_y;
	float camera_z;
} STUNT_JUMP, * PSTUNT_JUMP;

STUNT_JUMP stunt_jump[MAX_STUNT_JUMPS];
Car vehicle;
int stunt_jump_flag[MAX_STUNT_JUMPS];

void add_stunt_jump(int id, float speed, float distance, float x, float y, float z, float camera_x, float camera_y, float camera_z)
{
	stunt_jump[id].speed = speed;
	stunt_jump[id].distance = distance;
	stunt_jump[id].x = x;
	stunt_jump[id].y = y;
	stunt_jump[id].z = z;
	stunt_jump[id].camera_x = camera_x;
	stunt_jump[id].camera_y = camera_y;
	stunt_jump[id].camera_z = camera_z;
}

bool is_player_able_to_do_stunt_jump(void)
{
	if (!IS_PLAYER_PLAYING(GetPlayerIndex()) || IS_CHAR_DEAD(GetPlayerPed()) || HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()) || !IS_CHAR_IN_ANY_CAR(GetPlayerPed()) || IS_CHAR_IN_ANY_BOAT(GetPlayerPed()) || IS_CHAR_IN_FLYING_VEHICLE(GetPlayerPed()))
	{
		return false;
	}

	STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &vehicle);

	if (IS_CAR_DEAD(vehicle) || IS_CAR_IN_WATER(vehicle))
	{
		return false;
	}

	return true;
}

void display_stunt_jump_text(int reward)
{
	SETTIMERA(0);

	while (true)
	{
		WAIT(0);

		if (TIMERA() > 5000 || IS_CHAR_DEAD(GetPlayerPed()) || HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))
		{
			break;
		}

		SET_TEXT_COLOUR(0, 180, 130, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 250);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT(0.5, 0.4, "JUMPING_T1"); // UNIQUE STUNT BONUS!

		SET_TEXT_COLOUR(55, 95, 125, 255);
		SET_TEXT_SCALE(0.45, 0.65);
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 250);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "JUMPING_T2", reward); // REWARD $~1~
	}
}

void activate_stunt_jump(int id)
{
	Cam camera;
	CREATE_CAM(14, &camera);
	POINT_CAM_AT_PED(camera, GetPlayerPed());
	SET_CAM_POS(camera, stunt_jump[id].camera_x, stunt_jump[id].camera_y, stunt_jump[id].camera_z);
	SET_CAM_FOV(camera, 60.20001000);
	SET_CAM_ACTIVE(camera, 1);
	SET_CAM_PROPAGATE(camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	SET_WIDESCREEN_BORDERS(1);

	SETTIMERA(0);

	SET_TIME_SCALE(0.35);

	int old_result = stunt_jump_flag[id], new_result = STUNT_JUMP_NONE;

	while (true)
	{
		WAIT(0);

		DISABLE_PAUSE_MENU(1);

		if (!is_player_able_to_do_stunt_jump())
		{
			new_result = STUNT_JUMP_FAIL;
			break;
		}

		if (!IS_CAR_IN_AIR_PROPER(vehicle))
		{
			if (TIMERA() < 1000)
			{
				new_result = STUNT_JUMP_FAIL;
			}
			else
			{
				new_result = STUNT_JUMP_SUCCESS;
			}
			break;
		}
	}

	ACTIVATE_SCRIPTED_CAMS(0, 0);
	DESTROY_CAM(camera);
	SET_WIDESCREEN_BORDERS(0);
	SET_TIME_SCALE(1.0);

	int reward;

	if (old_result != STUNT_JUMP_SUCCESS)
	{
		stunt_jump_flag[id] = new_result;

		if (old_result == STUNT_JUMP_NONE)
		{
			INCREMENT_INT_STAT(STAT_STUNT_JUMPS_FOUND, 1);
		}

		if (new_result == STUNT_JUMP_SUCCESS)
		{
			INCREMENT_INT_STAT(STAT_STUNT_JUMPS_COMPLETED, 1);
			G_GAME_PROGRESS += 1;
			SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);

			reward = GET_INT_STAT(STAT_STUNT_JUMPS_COMPLETED) * 100;

			if (GET_INT_STAT(STAT_STUNT_JUMPS_COMPLETED) == MAX_STUNT_JUMPS)
			{
				reward = 10000;
			}

			ADD_SCORE(GetPlayerIndex(), reward);
		}
	}

	CLEAR_PRINTS();

	if (new_result != STUNT_JUMP_SUCCESS)
	{
		if (old_result != STUNT_JUMP_SUCCESS)
		{
			PRINT("USJFAIL", 2500, true); // Not good enough.
		}
		else
		{
			PRINT("USJFAILA", 2500, true); // Not good enough, but this stunt jump has been completed before.
		}
	}

	if (new_result == STUNT_JUMP_SUCCESS)
	{
		if (old_result != STUNT_JUMP_SUCCESS)
		{
			if (GET_INT_STAT(STAT_STUNT_JUMPS_COMPLETED) == MAX_STUNT_JUMPS)
			{
				PRINT_HELP("USJ_ALL"); // All stunt jumps completed.
			}

			PRINT("USJ", 2500, true); // Stunt jump completed.
		}
		else
		{
			PRINT("USJA", 2500, true); // Stunt jump completed again.
		}
	}

	if (GET_INT_STAT(STAT_STUNT_JUMPS_COMPLETED) == MAX_STUNT_JUMPS)
	{
		PRINT("USJ_ALL", 2500, true); // All stunt jumps completed.
	}
	else if (GET_INT_STAT(STAT_STUNT_JUMPS_COMPLETED) == MAX_STUNT_JUMPS - 1)
	{
		PRINT("USJ_1LEFT", 2500, true); // Just one stunt jump left to do.
	}
	else
	{
		PRINT_WITH_NUMBER("USJ_LEFT", MAX_STUNT_JUMPS - GET_INT_STAT(STAT_STUNT_JUMPS_COMPLETED), 2500, true); // ~1~ stunt jumps left to do.
	}

	if (new_result == STUNT_JUMP_SUCCESS && old_result != STUNT_JUMP_SUCCESS)
	{
		display_stunt_jump_text(reward);

		CLEAR_HELP();

		if (!G_ONMISSION && !IS_AUTO_SAVE_IN_PROGRESS())
		{
			DO_AUTO_SAVE();
		}
	}
}

void check_for_stunt_jump(void)
{
	if (!is_player_able_to_do_stunt_jump() || !IS_CAR_IN_AIR_PROPER(vehicle))
	{
		return;
	}

	int i;
	Vector3 player;
	GET_CHAR_COORDINATES(GetPlayerPed(), &player.x, &player.y, &player.z);

	for (i = 0; i < MAX_STUNT_JUMPS; i++)
	{
		float distance, speed;
		GET_DISTANCE_BETWEEN_COORDS_3D(player.x, player.y, player.z, stunt_jump[i].x, stunt_jump[i].y, stunt_jump[i].z, &distance);

		if (distance < stunt_jump[i].distance)
		{
			GET_CHAR_SPEED(GetPlayerPed(), &speed);

			if (speed > stunt_jump[i].speed)
			{
				activate_stunt_jump(i);
				break;
			}
		}
	}
	return;
}

void main(void)
{
	THIS_SCRIPT_SHOULD_BE_SAVED();

	add_stunt_jump(0, 19.0, 3.6, -1054.781, -511.546, 12.707, -1088.964, -506.8505, 18.1338);
	add_stunt_jump(1, 19.0, 3.6, -919.695, -222.212, 22.673, -927.8242, -248.5606, 31.2329);
	add_stunt_jump(2, 19.0, 3.6, -783.49, -378.833, 13, -767.2437, -361.1972, 20.7296);
	add_stunt_jump(3, 19.0, 3.6, -819.139, -521.685, 16.016, -761.279, -494.8624, 16.979);
	add_stunt_jump(4, 19.0, 3.6, -1118.685, -542.674, 13.121, -1087.165, -540.3603, 18.1604);
	add_stunt_jump(5, 19.0, 3.6, -1162.712, -739.881, 13.068, -1131.454, -738.5879, 15.5915);
	add_stunt_jump(6, 19.0, 3.6, -1120.337, -697.952, 11.194, -1157.58, -714.3733, 20.3087);
	add_stunt_jump(7, 19.0, 3.6, -907.022, -465.257, 13.115, -922.2749, -464.9999, 18.0731);
	add_stunt_jump(8, 19.0, 3.6, 457.721, 1430.801, 19.103, 433.1404, 1411.404, 14.2009);
	add_stunt_jump(9, 19.0, 3.6, 111.972, -846.4981, 4.929, 121.9503, -866.5061, 3.6779);
	add_stunt_jump(10, 19.0, 3.6, 111.972, -743.589, 4.929, 118.4064, -767.2807, 3.4204);
	add_stunt_jump(11, 19.0, 3.6, -241.345, 1695.422, 23.916, -257.7014, 1732.213, 19.0565);
	add_stunt_jump(12, 19.0, 3.6, -96.84003, 1363.062, 92.71701, -110.2, 1376.4, 93.2);
	add_stunt_jump(13, 18.0, 3.6, -406.022, 1686.526, 25.94, -420.7, 1705.3, 18.4);
	add_stunt_jump(14, 19.0, 3.6, 120.553, 1642.196, 41.741, 140.5, 1635.7, 34);
	add_stunt_jump(15, 19.0, 3.6, -578.583, 502.902, 9.181, -571.154, 470.0057, 9.957);
	add_stunt_jump(16, 19.0, 3.6, -509.702, 418.494, 9.181, -497.7841, 407.5568, 6.218799);
	add_stunt_jump(17, 19.0, 3.6, -467.789, 793.804, 9.915, -473.6896, 771.6933, 10.5044);
	add_stunt_jump(18, 14.0, 3.6, -608.895, -36.323, 15.855, -622.6156, -55.86133, 12.1929);
	add_stunt_jump(19, 19.0, 3.6, 641.993, -430.672, 13.967, 666.5752, -427.8961, 15.5283);
	add_stunt_jump(20, 19.0, 3.6, 479.115, -431.415, 19.883, 496.3356, -434.6796, 22.5317);
	add_stunt_jump(21, 19.0, 3.6, 543.481, -697.6, 29.67, 517.5247, -725.3891, 25.4335);
	add_stunt_jump(22, 19.0, 3.6, 440.435, -712.895, 11.752, 437.1501, -741.4602, 13.7525);
	add_stunt_jump(23, 16.0, 3.6, 442.103, -793.505, 14.361, 426.5163, -822.1759, 14.045);
	add_stunt_jump(24, 19.0, 3.6, 651.05, -619, 6.84, 661.2427, -607.774, 8.4116);
	add_stunt_jump(25, 19.0, 3.6, 692.0561, -412.833, 6.84, 692.0202, -430.3474, 5.296);
	add_stunt_jump(26, 19.0, 3.6, 717.4732, 38.88571, 10, 701.9545, 63.37839, 9.2438);
	add_stunt_jump(27, 19.0, 3.6, 803.7901, -176.863, 13.895, 794.3011, -202.6794, 17.4501);
	add_stunt_jump(28, 19.0, 3.6, 894.589, 10.77002, 12.931, 859.6391, 8.953125, 6.3656);
	add_stunt_jump(29, 19.0, 3.6, 887.1049, 28.26401, 12.931, 889.6417, 0.9078979, 13.3283);
	add_stunt_jump(30, 19.0, 3.6, 893.91, 149.638, 8.222, 895.6723, 133.1857, 12.049);
	add_stunt_jump(31, 19.0, 3.6, 692.041, 52.392, 8.688, 715.5344, 53.15881, 4.4141);
	add_stunt_jump(32, 17.0, 3.6, 750.2051, 309.7988, 36.3731, 734.9448, 317.0932, 28.4501);
	add_stunt_jump(33, 19.0, 3.6, 877.5, 414.6, 10, 849.4033, 407.3275, 7.7649);
	add_stunt_jump(34, 19.0, 3.6, 868.8542, 198.6788, 9.897701, 853.6179, 165.4967, 8.1343);
	add_stunt_jump(35, 13.0, 3.6, 86.18201, 242.259, 6.926, 115.9934, 234.211, 9.3976);

	while (true)
	{
		WAIT(0);

		check_for_stunt_jump();
	}
}