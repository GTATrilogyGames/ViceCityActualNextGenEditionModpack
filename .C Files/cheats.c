#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "keys.h"

// #define WEAPON_PATCH_SUPPORT

#if !defined WEAPON_PATCH_SUPPORT
	#define WEAPONTYPE_UNARMED WEAPON_UNARMED
	#define WEAPONTYPE_BRASSKNUCKLE WEAPON_UNARMED
	#define WEAPONTYPE_SCREWDRIVER WEAPON_UNARMED
	#define WEAPONTYPE_GOLFCLUB WEAPON_POOLCUE
	#define WEAPONTYPE_NIGHTSTICK WEAPON_EPISODIC_24
	#define WEAPONTYPE_KNIFE WEAPON_KNIFE
	#define WEAPONTYPE_BASEBALLBAT WEAPON_BASEBALLBAT
	#define WEAPONTYPE_HAMMER WEAPON_EPISODIC_23
	#define WEAPONTYPE_CLEAVER WEAPON_EPISODIC_3
	#define WEAPONTYPE_MACHETE WEAPON_UNARMED
	#define WEAPONTYPE_KATANA WEAPON_UNARMED
	#define WEAPONTYPE_CHAINSAW WEAPON_FTHROWER
	#define WEAPONTYPE_GRENADE WEAPON_GRENADE
	#define WEAPONTYPE_DETONATOR_GRENADE WEAPON_UNARMED
	#define WEAPONTYPE_TEARGAS WEAPON_UNARMED
	#define WEAPONTYPE_MOLOTOV WEAPON_MOLOTOV
	#define WEAPONTYPE_COLT45 WEAPON_PISTOL
	#define WEAPONTYPE_PYTHON WEAPON_DEAGLE
	#define WEAPONTYPE_SHOTGUN WEAPON_SHOTGUN
	#define WEAPONTYPE_SPAS12_SHOTGUN WEAPON_BARETTA
	#define WEAPONTYPE_STUBBY_SHOTGUN WEAPON_UNARMED
	#define WEAPONTYPE_TEC9 WEAPON_UNARMED
	#define WEAPONTYPE_UZI WEAPON_UNARMED
	#define WEAPONTYPE_SILENCED_INGRAM WEAPON_MICRO_UZI
	#define WEAPONTYPE_MP5 WEAPON_MP5
	#define WEAPONTYPE_M4 WEAPON_M4
	#define WEAPONTYPE_RUGER WEAPON_AK47
	#define WEAPONTYPE_SNIPERRIFLE WEAPON_UNARMED
	#define WEAPONTYPE_LASERSCOPE WEAPON_SNIPERRIFLE
	#define WEAPONTYPE_ROCKETLAUNCHER WEAPON_RLAUNCHER
	#define WEAPONTYPE_FLAMETHROWER WEAPON_UNARMED
	#define WEAPONTYPE_M60 WEAPON_M40A1
	#define WEAPONTYPE_MINIGUN WEAPON_UNARMED
	#define WEAPONTYPE_DETONATOR WEAPON_UNARMED
	#define WEAPONTYPE_CAMERA WEAPON_CAMERA
#else
	#define WEAPONTYPE_UNARMED WEAPON_UNARMED
	#define WEAPONTYPE_BRASSKNUCKLE WEAPON_EPISODIC_9
	#define WEAPONTYPE_SCREWDRIVER WEAPON_EPISODIC_8
	#define WEAPONTYPE_GOLFCLUB WEAPON_POOLCUE
	#define WEAPONTYPE_NIGHTSTICK WEAPON_EPISODIC_24
	#define WEAPONTYPE_KNIFE WEAPON_KNIFE
	#define WEAPONTYPE_BASEBALLBAT WEAPON_BASEBALLBAT
	#define WEAPONTYPE_HAMMER WEAPON_EPISODIC_23
	#define WEAPONTYPE_CLEAVER WEAPON_EPISODIC_3
	#define WEAPONTYPE_MACHETE WEAPON_EPISODIC_1
	#define WEAPONTYPE_KATANA WEAPON_EPISODIC_4
	#define WEAPONTYPE_CHAINSAW WEAPON_FTHROWER
	#define WEAPONTYPE_GRENADE WEAPON_GRENADE
	#define WEAPONTYPE_DETONATOR_GRENADE WEAPON_EPISODIC_16
	#define WEAPONTYPE_TEARGAS WEAPON_UNARMED
	#define WEAPONTYPE_MOLOTOV WEAPON_MOLOTOV
	#define WEAPONTYPE_COLT45 WEAPON_PISTOL
	#define WEAPONTYPE_PYTHON WEAPON_DEAGLE
	#define WEAPONTYPE_SHOTGUN WEAPON_SHOTGUN
	#define WEAPONTYPE_SPAS12_SHOTGUN WEAPON_BARETTA
	#define WEAPONTYPE_STUBBY_SHOTGUN WEAPON_EPISODIC_11
	#define WEAPONTYPE_TEC9 WEAPON_EPISODIC_12
	#define WEAPONTYPE_UZI WEAPON_EPISODIC_13
	#define WEAPONTYPE_SILENCED_INGRAM WEAPON_MICRO_UZI
	#define WEAPONTYPE_MP5 WEAPON_MP5
	#define WEAPONTYPE_M4 WEAPON_M4
	#define WEAPONTYPE_RUGER WEAPON_AK47
	#define WEAPONTYPE_SNIPERRIFLE WEAPON_EPISODIC_15
	#define WEAPONTYPE_LASERSCOPE WEAPON_SNIPERRIFLE
	#define WEAPONTYPE_ROCKETLAUNCHER WEAPON_RLAUNCHER
	#define WEAPONTYPE_FLAMETHROWER WEAPON_EPISODIC_5
	#define WEAPONTYPE_M60 WEAPON_M40A1
	#define WEAPONTYPE_MINIGUN WEAPON_EPISODIC_14
	#define WEAPONTYPE_DETONATOR WEAPON_UNARMED
	#define WEAPONTYPE_CAMERA WEAPON_CAMERA
#endif

int cheat_key[26], cheat_buffer[30];
float timeScale = 1.0;

void reset_cheat_keys(void)
{
	cheat_key[0] = KEY_Q;
	cheat_key[1] = KEY_W;
	cheat_key[2] = KEY_E;
	cheat_key[3] = KEY_R;
	cheat_key[4] = KEY_T;
	cheat_key[5] = KEY_Y;
	cheat_key[6] = KEY_U;
	cheat_key[7] = KEY_I;
	cheat_key[8] = KEY_O;
	cheat_key[9] = KEY_P;
	cheat_key[10] = KEY_A;
	cheat_key[11] = KEY_S;
	cheat_key[12] = KEY_D;
	cheat_key[13] = KEY_F;
	cheat_key[14] = KEY_G;
	cheat_key[15] = KEY_H;
	cheat_key[16] = KEY_J;
	cheat_key[17] = KEY_K;
	cheat_key[18] = KEY_L;
	cheat_key[19] = KEY_Z;
	cheat_key[20] = KEY_X;
	cheat_key[21] = KEY_C;
	cheat_key[22] = KEY_V;
	cheat_key[23] = KEY_B;
	cheat_key[24] = KEY_N;
	cheat_key[25] = KEY_M;
}

void reset_cheat_buffer(void)
{
	int i;

	for (i = 0; i < 30; i++)
	{
		cheat_buffer[i] = 0;
	}
}

int get_pressed_cheat_key(void)
{
	int i;

	for (i = 0; i < 26; i++)
	{
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(cheat_key[i]))
		{
			return cheat_key[i];
		}
	}

	return 0;
}

void update_cheat_buffer(int key)
{
	int i;

	for (i = 1; i < 30; i++)
	{
		cheat_buffer[i - 1] = cheat_buffer[i];
	}

	cheat_buffer[29] = key;
}

void increment_time_scale(float value)
{
	timeScale += value;

	if (timeScale < 0.0)
	{
		timeScale = 0.2;
	}
	else if (timeScale > 2.4)
	{
		timeScale = 2.4;
	}

	SET_TIME_SCALE(timeScale);
}

void create_vehicle_in_front_of_player(char *name)
{
	REQUEST_MODEL(GET_HASH_KEY(name));

	while (!HAS_MODEL_LOADED(GET_HASH_KEY(name)))
	{
		WAIT(0);
	}

	Vector3 position;
	float heading;
	Vehicle vehicle;

	GET_CHAR_COORDINATES(GetPlayerPed(), &position.x, &position.y, &position.z);
	GET_CHAR_HEADING(GetPlayerPed(), &heading);

	heading += 90.0;
	position.x += COS(heading) * 6.0;
	position.y += SIN(heading) * 6.0;
	heading -= 180.0;

	CREATE_CAR(GET_HASH_KEY(name), position.x, position.y, position.z, &vehicle, 1);
	SET_CAR_HEADING(vehicle, heading);

	MARK_CAR_AS_NO_LONGER_NEEDED(&vehicle);
	MARK_MODEL_AS_NO_LONGER_NEEDED(GET_HASH_KEY(name));
}

void set_player_model(uint model)
{
	REQUEST_MODEL(model);

	while (!HAS_MODEL_LOADED(model))
	{
		WAIT(0);
	}

	uint weapon[10], ammo[10], unused;

	int i;

	for (i = 0; i < 10; i += 1)
	{
		GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), i, &weapon[i], &ammo[i], &unused);
	}

	int health, armour;
	float heading;

	GET_CHAR_HEADING(GetPlayerPed(), &heading);
	GET_CHAR_HEALTH(GetPlayerPed(), &health);
	GET_CHAR_ARMOUR(GetPlayerPed(), &armour);

	CHANGE_PLAYER_MODEL(GetPlayerIndex(), model);

	MARK_MODEL_AS_NO_LONGER_NEEDED(model);

	SET_CHAR_HEADING(GetPlayerPed(), heading);
	SET_CHAR_HEALTH(GetPlayerPed(), health);
	ADD_ARMOUR_TO_CHAR(GetPlayerPed(), armour);

	for (i = 0; i < 10; i += 1)
	{
		UpdateWeaponOfPed(GetPlayerPed(), weapon[i]);
		SET_CHAR_AMMO(GetPlayerPed(), weapon[i], ammo[i]);
	}
}

bool process_cheat_buffer(void)
{
	// IFIWEREARICHMAN - Acquire $250,000 in cash
	if (cheat_buffer[15] == KEY_I && cheat_buffer[16] == KEY_F && cheat_buffer[17] == KEY_I && cheat_buffer[18] == KEY_W &&
		cheat_buffer[19] == KEY_E && cheat_buffer[20] == KEY_R && cheat_buffer[21] == KEY_E && cheat_buffer[22] == KEY_A &&
		cheat_buffer[23] == KEY_R && cheat_buffer[24] == KEY_I && cheat_buffer[25] == KEY_C && cheat_buffer[26] == KEY_H &&
		cheat_buffer[27] == KEY_M && cheat_buffer[28] == KEY_A && cheat_buffer[29] == KEY_N)
	{
		ADD_SCORE(GetPlayerIndex(), 250000);
	}

	// LEAVEMEALONE - Remove all wanted level
	else if (cheat_buffer[18] == KEY_L && cheat_buffer[19] == KEY_E && cheat_buffer[20] == KEY_A && cheat_buffer[21] == KEY_V && cheat_buffer[22] == KEY_E && cheat_buffer[23] == KEY_M && cheat_buffer[24] == KEY_E && cheat_buffer[25] == KEY_A && cheat_buffer[26] == KEY_L && cheat_buffer[27] == KEY_O && cheat_buffer[28] == KEY_N && cheat_buffer[29] == KEY_E)
	{
		CLEAR_WANTED_LEVEL(GetPlayerIndex());
	}
	// YOUWONTTAKEMEALIVE - Increase wanted level by two stars
	else if (cheat_buffer[12] == KEY_Y && cheat_buffer[13] == KEY_O && cheat_buffer[14] == KEY_U && cheat_buffer[15] == KEY_W && cheat_buffer[16] == KEY_O && cheat_buffer[17] == KEY_N && cheat_buffer[18] == KEY_T && cheat_buffer[19] == KEY_T && cheat_buffer[20] == KEY_A && cheat_buffer[21] == KEY_K && cheat_buffer[22] == KEY_E && cheat_buffer[23] == KEY_M && cheat_buffer[24] == KEY_E && cheat_buffer[25] == KEY_A && cheat_buffer[26] == KEY_L && cheat_buffer[27] == KEY_I && cheat_buffer[28] == KEY_V && cheat_buffer[29] == KEY_E)
	{
		uint wanted_level;

		STORE_WANTED_LEVEL(GetPlayerIndex(), &wanted_level);
		wanted_level += 2;

		if (wanted_level > 6)
		{
			wanted_level = 6;
		}

		ALTER_WANTED_LEVEL(GetPlayerIndex(), wanted_level);
		APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
	}

	// BOOOOOORING - Decrease game speed by half, down to x0.25 normal speed
	else if (cheat_buffer[19] == KEY_B && cheat_buffer[20] == KEY_O && cheat_buffer[21] == KEY_O && cheat_buffer[22] == KEY_O && cheat_buffer[23] == KEY_O && cheat_buffer[24] == KEY_O && cheat_buffer[25] == KEY_O && cheat_buffer[26] == KEY_R && cheat_buffer[27] == KEY_I && cheat_buffer[28] == KEY_N && cheat_buffer[29] == KEY_G)
	{
		increment_time_scale(-0.2);
	}
	// ONSPEED - Increase game speed by 2, up to x4 normal speed
	else if (cheat_buffer[23] == KEY_O && cheat_buffer[24] == KEY_N && cheat_buffer[25] == KEY_S && cheat_buffer[26] == KEY_P && cheat_buffer[27] == KEY_E && cheat_buffer[28] == KEY_E && cheat_buffer[29] == KEY_D)
	{
		increment_time_scale(0.2);
	}

	// ASPIRINE - Replenish player/vehicle health
	else if (cheat_buffer[22] == KEY_A && cheat_buffer[23] == KEY_S && cheat_buffer[24] == KEY_P && cheat_buffer[25] == KEY_I && cheat_buffer[26] == KEY_R && cheat_buffer[27] == KEY_I && cheat_buffer[28] == KEY_N && cheat_buffer[29] == KEY_E)
	{
		SET_CHAR_HEALTH(GetPlayerPed(), 200);

		if (IS_CHAR_IN_ANY_CAR(GetPlayerPed()))
		{
			Vehicle vehicle;
			STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &vehicle);
			FIX_CAR(vehicle);
			MARK_CAR_AS_NO_LONGER_NEEDED(&vehicle);
		}
	}
	// ICANTTAKEITANYMORE - Commit suicide
	else if (cheat_buffer[12] == KEY_I && cheat_buffer[13] == KEY_C && cheat_buffer[14] == KEY_A && cheat_buffer[15] == KEY_N && cheat_buffer[16] == KEY_T && cheat_buffer[17] == KEY_T && cheat_buffer[18] == KEY_A && cheat_buffer[19] == KEY_K && cheat_buffer[20] == KEY_E && cheat_buffer[21] == KEY_I && cheat_buffer[22] == KEY_T && cheat_buffer[23] == KEY_A && cheat_buffer[24] == KEY_N && cheat_buffer[25] == KEY_Y && cheat_buffer[26] == KEY_M && cheat_buffer[27] == KEY_O && cheat_buffer[28] == KEY_R && cheat_buffer[29] == KEY_E)
	{
		EXPLODE_CHAR_HEAD(GetPlayerPed());
	}
	// PRECIOUSPROTECTION - Replenish player armor
	else if (cheat_buffer[12] == KEY_P && cheat_buffer[13] == KEY_R && cheat_buffer[14] == KEY_E && cheat_buffer[15] == KEY_C && cheat_buffer[16] == KEY_I && cheat_buffer[17] == KEY_O && cheat_buffer[18] == KEY_U && cheat_buffer[19] == KEY_S && cheat_buffer[20] == KEY_P && cheat_buffer[21] == KEY_R && cheat_buffer[22] == KEY_O && cheat_buffer[23] == KEY_T && cheat_buffer[24] == KEY_E && cheat_buffer[25] == KEY_C && cheat_buffer[26] == KEY_T && cheat_buffer[27] == KEY_I && cheat_buffer[28] == KEY_O && cheat_buffer[29] == KEY_N)
	{
		ADD_ARMOUR_TO_CHAR(GetPlayerPed(), 100);
	}

	// THUGSTOOLS - Basic weapons set
	else if (cheat_buffer[20] == KEY_T && cheat_buffer[21] == KEY_H && cheat_buffer[22] == KEY_U && cheat_buffer[23] == KEY_G && cheat_buffer[24] == KEY_S && cheat_buffer[25] == KEY_T && cheat_buffer[26] == KEY_O && cheat_buffer[27] == KEY_O && cheat_buffer[28] == KEY_L && cheat_buffer[29] == KEY_S)
	{
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_BRASSKNUCKLE, 1, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_BASEBALLBAT, 1, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_MOLOTOV, 10, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_COLT45, 100, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_SHOTGUN, 50, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_TEC9, 150, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_RUGER, 120, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_SNIPERRIFLE, 25, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_FLAMETHROWER, 200, false);
	}
	// PROFESSIONALTOOLS - Intermediate weapons set
	else if (cheat_buffer[13] == KEY_P && cheat_buffer[14] == KEY_R && cheat_buffer[15] == KEY_O && cheat_buffer[16] == KEY_F && cheat_buffer[17] == KEY_E && cheat_buffer[18] == KEY_S && cheat_buffer[19] == KEY_S && cheat_buffer[20] == KEY_I && cheat_buffer[21] == KEY_O && cheat_buffer[22] == KEY_N && cheat_buffer[23] == KEY_A && cheat_buffer[24] == KEY_L && cheat_buffer[25] == KEY_T && cheat_buffer[26] == KEY_O && cheat_buffer[27] == KEY_O && cheat_buffer[28] == KEY_L && cheat_buffer[29] == KEY_S)
	{
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_KATANA, 1, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_DETONATOR_GRENADE, 10, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_PYTHON, 40, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_STUBBY_SHOTGUN, 25, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_SILENCED_INGRAM, 100, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_M4, 150, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_LASERSCOPE, 21, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_ROCKETLAUNCHER, 5, false);
	}
	// NUTTERTOOLS - Advanced weapons set
	else if (cheat_buffer[19] == KEY_N && cheat_buffer[20] == KEY_U && cheat_buffer[21] == KEY_T && cheat_buffer[22] == KEY_T && cheat_buffer[23] == KEY_E && cheat_buffer[24] == KEY_R && cheat_buffer[25] == KEY_T && cheat_buffer[26] == KEY_O && cheat_buffer[27] == KEY_O && cheat_buffer[28] == KEY_L && cheat_buffer[29] == KEY_S)
	{
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_CHAINSAW, AMMO_MAX, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_GRENADE, 10, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_PYTHON, 40, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_SPAS12_SHOTGUN, 30, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_MP5, 100, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_M4, 150, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_LASERSCOPE, 21, false);
		GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPONTYPE_MINIGUN, 500, false);
	}

	// ABITDRIEG - Overcast weather
	else if (cheat_buffer[21] == KEY_A && cheat_buffer[22] == KEY_B && cheat_buffer[23] == KEY_I && cheat_buffer[24] == KEY_T && cheat_buffer[25] == KEY_D && cheat_buffer[26] == KEY_R && cheat_buffer[27] == KEY_I && cheat_buffer[28] == KEY_E && cheat_buffer[29] == KEY_G)
	{
		FORCE_WEATHER_NOW(WEATHER_CLOUDY);
	}
	// APLEASANTDAY - Light clouds
	else if (cheat_buffer[18] == KEY_A && cheat_buffer[19] == KEY_P && cheat_buffer[20] == KEY_L && cheat_buffer[21] == KEY_E && cheat_buffer[22] == KEY_A && cheat_buffer[23] == KEY_S && cheat_buffer[24] == KEY_A && cheat_buffer[25] == KEY_N && cheat_buffer[26] == KEY_T && cheat_buffer[27] == KEY_D && cheat_buffer[28] == KEY_A && cheat_buffer[29] == KEY_Y)
	{
		FORCE_WEATHER_NOW(WEATHER_SUNNY);
	}
	// ALOVELYDAY - Sunny/clear weather
	else if (cheat_buffer[20] == KEY_A && cheat_buffer[21] == KEY_L && cheat_buffer[22] == KEY_O && cheat_buffer[23] == KEY_V && cheat_buffer[24] == KEY_E && cheat_buffer[25] == KEY_L && cheat_buffer[26] == KEY_Y && cheat_buffer[27] == KEY_D && cheat_buffer[28] == KEY_A && cheat_buffer[29] == KEY_Y)
	{
		FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
	}
	// CANTSEEATHING - Foggy weather
	else if (cheat_buffer[17] == KEY_C && cheat_buffer[18] == KEY_A && cheat_buffer[19] == KEY_N && cheat_buffer[20] == KEY_T && cheat_buffer[21] == KEY_S && cheat_buffer[22] == KEY_E && cheat_buffer[23] == KEY_E && cheat_buffer[24] == KEY_A && cheat_buffer[25] == KEY_T && cheat_buffer[26] == KEY_H && cheat_buffer[27] == KEY_I && cheat_buffer[28] == KEY_N && cheat_buffer[29] == KEY_G)
	{
		FORCE_WEATHER_NOW(WEATHER_FOGGY);
	}
	// CATSANDDOGS - Stormy weather
	else if (cheat_buffer[19] == KEY_C && cheat_buffer[20] == KEY_A && cheat_buffer[21] == KEY_T && cheat_buffer[22] == KEY_S && cheat_buffer[23] == KEY_A && cheat_buffer[24] == KEY_N && cheat_buffer[25] == KEY_D && cheat_buffer[26] == KEY_D && cheat_buffer[27] == KEY_O && cheat_buffer[28] == KEY_G && cheat_buffer[29] == KEY_S)
	{
		FORCE_WEATHER_NOW(WEATHER_RAINING);
	}

	// BETTERTHANWALKING - Spawn Caddy
	else if (cheat_buffer[13] == KEY_B && cheat_buffer[14] == KEY_E && cheat_buffer[15] == KEY_T && cheat_buffer[16] == KEY_T && cheat_buffer[17] == KEY_E && cheat_buffer[18] == KEY_R && cheat_buffer[19] == KEY_T && cheat_buffer[20] == KEY_H && cheat_buffer[21] == KEY_A && cheat_buffer[22] == KEY_N && cheat_buffer[23] == KEY_W && cheat_buffer[24] == KEY_A && cheat_buffer[25] == KEY_L && cheat_buffer[26] == KEY_K && cheat_buffer[27] == KEY_I && cheat_buffer[28] == KEY_N && cheat_buffer[29] == KEY_G)
	{
		create_vehicle_in_front_of_player("huntley");
	}
	// GETTHEREFAST - Spawn Sabre Turbo
	else if (cheat_buffer[18] == KEY_G && cheat_buffer[19] == KEY_E && cheat_buffer[20] == KEY_T && cheat_buffer[21] == KEY_T && cheat_buffer[22] == KEY_H && cheat_buffer[23] == KEY_E && cheat_buffer[24] == KEY_R && cheat_buffer[25] == KEY_E && cheat_buffer[26] == KEY_F && cheat_buffer[27] == KEY_A && cheat_buffer[28] == KEY_S && cheat_buffer[29] == KEY_T)
	{
		create_vehicle_in_front_of_player("sabregt");
	}
	// GETTHEREQUICKLY - Spawn Bloodring Banger (Glendale)
	else if (cheat_buffer[15] == KEY_G && cheat_buffer[16] == KEY_E && cheat_buffer[17] == KEY_T && cheat_buffer[18] == KEY_T && cheat_buffer[19] == KEY_H && cheat_buffer[20] == KEY_E && cheat_buffer[21] == KEY_R && cheat_buffer[22] == KEY_E && cheat_buffer[23] == KEY_Q && cheat_buffer[24] == KEY_U && cheat_buffer[25] == KEY_I && cheat_buffer[26] == KEY_C && cheat_buffer[27] == KEY_K && cheat_buffer[28] == KEY_L && cheat_buffer[29] == KEY_Y)
	{
		create_vehicle_in_front_of_player("willard");
	}
	// TRAVELINSTYLE - Spawn Bloodring Banger (Oceanic)
	else if (cheat_buffer[17] == KEY_T && cheat_buffer[18] == KEY_R && cheat_buffer[19] == KEY_A && cheat_buffer[20] == KEY_V && cheat_buffer[21] == KEY_E && cheat_buffer[22] == KEY_L && cheat_buffer[23] == KEY_I && cheat_buffer[24] == KEY_N && cheat_buffer[25] == KEY_S && cheat_buffer[26] == KEY_T && cheat_buffer[27] == KEY_Y && cheat_buffer[28] == KEY_L && cheat_buffer[29] == KEY_E)
	{
		create_vehicle_in_front_of_player("peyote");
	}
	// GETTHEREVERYFASTINDEED - Spawn Hotring Racer A
	else if (cheat_buffer[8] == KEY_G && cheat_buffer[9] == KEY_E && cheat_buffer[10] == KEY_T && cheat_buffer[11] == KEY_T && cheat_buffer[12] == KEY_H && cheat_buffer[13] == KEY_E && cheat_buffer[14] == KEY_R && cheat_buffer[15] == KEY_E && cheat_buffer[16] == KEY_V && cheat_buffer[17] == KEY_E && cheat_buffer[18] == KEY_R && cheat_buffer[19] == KEY_Y && cheat_buffer[20] == KEY_F && cheat_buffer[21] == KEY_A && cheat_buffer[22] == KEY_S && cheat_buffer[23] == KEY_T && cheat_buffer[24] == KEY_I && cheat_buffer[25] == KEY_N && cheat_buffer[26] == KEY_D && cheat_buffer[27] == KEY_E && cheat_buffer[28] == KEY_E && cheat_buffer[29] == KEY_D)
	{
		create_vehicle_in_front_of_player("chavos");
	}
	// GETTHEREAMAZINGLYFAST - Spawn Hotring Racer B
	else if (cheat_buffer[9] == KEY_G && cheat_buffer[10] == KEY_E && cheat_buffer[11] == KEY_T && cheat_buffer[12] == KEY_T && cheat_buffer[13] == KEY_H && cheat_buffer[14] == KEY_E && cheat_buffer[15] == KEY_R && cheat_buffer[16] == KEY_E && cheat_buffer[17] == KEY_A && cheat_buffer[18] == KEY_M && cheat_buffer[19] == KEY_A && cheat_buffer[20] == KEY_Z && cheat_buffer[21] == KEY_I && cheat_buffer[22] == KEY_N && cheat_buffer[23] == KEY_G && cheat_buffer[24] == KEY_L && cheat_buffer[25] == KEY_Y && cheat_buffer[26] == KEY_F && cheat_buffer[27] == KEY_A && cheat_buffer[28] == KEY_S && cheat_buffer[29] == KEY_T)
	{
		create_vehicle_in_front_of_player("feroci");
	}
	// PANZER - Spawn Rhino
	else if (cheat_buffer[24] == KEY_P && cheat_buffer[25] == KEY_A && cheat_buffer[26] == KEY_N && cheat_buffer[27] == KEY_Z && cheat_buffer[28] == KEY_E && cheat_buffer[29] == KEY_R)
	{
		create_vehicle_in_front_of_player("pstockade");
	}
	// ROCKANDROLLCAR - Spawn Love Fist
	else if (cheat_buffer[16] == KEY_R && cheat_buffer[17] == KEY_O && cheat_buffer[18] == KEY_C && cheat_buffer[19] == KEY_K && cheat_buffer[20] == KEY_A && cheat_buffer[21] == KEY_N && cheat_buffer[22] == KEY_D && cheat_buffer[23] == KEY_R && cheat_buffer[24] == KEY_O && cheat_buffer[25] == KEY_L && cheat_buffer[26] == KEY_L && cheat_buffer[27] == KEY_C && cheat_buffer[28] == KEY_A && cheat_buffer[29] == KEY_R)
	{
		create_vehicle_in_front_of_player("stretch");
	}
	// RUBBISHCAR - Spawn Trashmaster
	else if (cheat_buffer[20] == KEY_R && cheat_buffer[21] == KEY_U && cheat_buffer[22] == KEY_B && cheat_buffer[23] == KEY_B && cheat_buffer[24] == KEY_I && cheat_buffer[25] == KEY_S && cheat_buffer[26] == KEY_H && cheat_buffer[27] == KEY_C && cheat_buffer[28] == KEY_A && cheat_buffer[29] == KEY_R)
	{
		create_vehicle_in_front_of_player("trash");
	}
	// THELASTRIDE - Spawn Romero's Hearse
	else if (cheat_buffer[19] == KEY_T && cheat_buffer[20] == KEY_H && cheat_buffer[21] == KEY_E && cheat_buffer[22] == KEY_L && cheat_buffer[23] == KEY_A && cheat_buffer[24] == KEY_S && cheat_buffer[25] == KEY_T && cheat_buffer[26] == KEY_R && cheat_buffer[27] == KEY_I && cheat_buffer[28] == KEY_D && cheat_buffer[29] == KEY_E)
	{
		create_vehicle_in_front_of_player("romero");
	}

	// CHEATSHAVEBEENCRACKED - Play as Ricardo Diaz
	else if (cheat_buffer[9]  == KEY_C && cheat_buffer[10] == KEY_H && cheat_buffer[11] == KEY_E && cheat_buffer[12] == KEY_A && cheat_buffer[13] == KEY_T && cheat_buffer[14] == KEY_S && cheat_buffer[15] == KEY_H && cheat_buffer[16] == KEY_A && cheat_buffer[17] == KEY_V && cheat_buffer[18] == KEY_E && cheat_buffer[19] == KEY_B && cheat_buffer[20] == KEY_E && cheat_buffer[21] == KEY_E && cheat_buffer[22] == KEY_N && cheat_buffer[23] == KEY_C && cheat_buffer[24] == KEY_R && cheat_buffer[25] == KEY_A && cheat_buffer[26] == KEY_C && cheat_buffer[27] == KEY_K && cheat_buffer[28] == KEY_E && cheat_buffer[29] == KEY_D)
	{
		set_player_model(MODEL_IG_BLEDAR);
	}
	// FOXYLITTLETHING - Play as Mercedes Cortez
	else if (cheat_buffer[15] == KEY_F && cheat_buffer[16] == KEY_O && cheat_buffer[17] == KEY_X && cheat_buffer[18] == KEY_Y && cheat_buffer[19] == KEY_L && cheat_buffer[20] == KEY_I && cheat_buffer[21] == KEY_T && cheat_buffer[22] == KEY_T && cheat_buffer[23] == KEY_L && cheat_buffer[24] == KEY_E && cheat_buffer[25] == KEY_T && cheat_buffer[26] == KEY_H && cheat_buffer[27] == KEY_I && cheat_buffer[28] == KEY_N && cheat_buffer[29] == KEY_G)
	{
		set_player_model(MODEL_IG_ANNA);
	}
	// IDONTHAVETHEMONEYSONNY - Play as Sonny Forelli
	else if (cheat_buffer[9]  == KEY_I && cheat_buffer[10] == KEY_D && cheat_buffer[11] == KEY_O && cheat_buffer[12] == KEY_N && cheat_buffer[13] == KEY_T && cheat_buffer[14] == KEY_H && cheat_buffer[15] == KEY_A && cheat_buffer[16] == KEY_V && cheat_buffer[17] == KEY_E && cheat_buffer[18] == KEY_T && cheat_buffer[19] == KEY_H && cheat_buffer[20] == KEY_E && cheat_buffer[21] == KEY_M && cheat_buffer[22] == KEY_O && cheat_buffer[23] == KEY_N && cheat_buffer[24] == KEY_E && cheat_buffer[25] == KEY_Y && cheat_buffer[26] == KEY_S && cheat_buffer[27] == KEY_O && cheat_buffer[28] == KEY_N && cheat_buffer[29] == KEY_N)
	{
		set_player_model(MODEL_IG_VLAD);
	}
	// ILOOKLIKEHILARY - Play as Hilary King
	else if (cheat_buffer[15] == KEY_I && cheat_buffer[16] == KEY_L && cheat_buffer[17] == KEY_O && cheat_buffer[18] == KEY_O && cheat_buffer[19] == KEY_K && cheat_buffer[20] == KEY_L && cheat_buffer[21] == KEY_I && cheat_buffer[22] == KEY_K && cheat_buffer[23] == KEY_E && cheat_buffer[24] == KEY_H && cheat_buffer[25] == KEY_I && cheat_buffer[26] == KEY_L && cheat_buffer[27] == KEY_A && cheat_buffer[28] == KEY_R && cheat_buffer[29] == KEY_Y)
	{
		set_player_model(MODEL_IG_BULGARIN);
		SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 0, 0);
	}
	// IWANTBIGTITS - Play as Candy Suxxx
	else if (cheat_buffer[18] == KEY_I && cheat_buffer[19] == KEY_W && cheat_buffer[20] == KEY_A && cheat_buffer[21] == KEY_N && cheat_buffer[22] == KEY_T && cheat_buffer[23] == KEY_B && cheat_buffer[24] == KEY_I && cheat_buffer[25] == KEY_G && cheat_buffer[26] == KEY_T && cheat_buffer[27] == KEY_I && cheat_buffer[28] == KEY_T && cheat_buffer[29] == KEY_S)
	{
		set_player_model(MODEL_IG_SARAH);
	}
	// LOOKLIKELANCE - Play as Lance Vance
	else if (cheat_buffer[17] == KEY_L && cheat_buffer[18] == KEY_O && cheat_buffer[19] == KEY_O && cheat_buffer[20] == KEY_K && cheat_buffer[21] == KEY_L && cheat_buffer[22] == KEY_I && cheat_buffer[23] == KEY_K && cheat_buffer[24] == KEY_E && cheat_buffer[25] == KEY_L && cheat_buffer[26] == KEY_A && cheat_buffer[27] == KEY_N && cheat_buffer[28] == KEY_C && cheat_buffer[29] == KEY_E)
	{
		set_player_model(MODEL_IG_LILJACOB);
	}
	// MYSONISALAWYER - Play as Ken Rosenberg
	else if (cheat_buffer[16] == KEY_M && cheat_buffer[17] == KEY_Y && cheat_buffer[18] == KEY_S && cheat_buffer[19] == KEY_O && cheat_buffer[20] == KEY_N && cheat_buffer[21] == KEY_I && cheat_buffer[22] == KEY_S && cheat_buffer[23] == KEY_A && cheat_buffer[24] == KEY_L && cheat_buffer[25] == KEY_A && cheat_buffer[26] == KEY_W && cheat_buffer[27] == KEY_Y && cheat_buffer[28] == KEY_E && cheat_buffer[29] == KEY_R)
	{
		set_player_model(MODEL_IG_ROMAN);
	}
	// ONEARMEDBANDIT - Play as Phil Cassidy
	else if (cheat_buffer[16] == KEY_O && cheat_buffer[17] == KEY_N && cheat_buffer[18] == KEY_E && cheat_buffer[19] == KEY_A && cheat_buffer[20] == KEY_R && cheat_buffer[21] == KEY_M && cheat_buffer[22] == KEY_E && cheat_buffer[23] == KEY_D && cheat_buffer[24] == KEY_B && cheat_buffer[25] == KEY_A && cheat_buffer[26] == KEY_N && cheat_buffer[27] == KEY_D && cheat_buffer[28] == KEY_I && cheat_buffer[29] == KEY_T)
	{
		set_player_model(MODEL_IG_BRUCIE);
		SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 2, 0);
	}
	// ROCKANDROLLMAN - Play as Jezz Torrent
	else if (cheat_buffer[16] == KEY_R && cheat_buffer[17] == KEY_O && cheat_buffer[18] == KEY_C && cheat_buffer[19] == KEY_K && cheat_buffer[20] == KEY_A && cheat_buffer[21] == KEY_N && cheat_buffer[22] == KEY_D && cheat_buffer[23] == KEY_R && cheat_buffer[24] == KEY_O && cheat_buffer[25] == KEY_L && cheat_buffer[26] == KEY_L && cheat_buffer[27] == KEY_M && cheat_buffer[28] == KEY_A && cheat_buffer[29] == KEY_N)
	{
		set_player_model(MODEL_IG_KENNY);
	}
	// WELOVEOURDICK - Play as Dick
	else if (cheat_buffer[17] == KEY_W && cheat_buffer[18] == KEY_E && cheat_buffer[19] == KEY_L && cheat_buffer[20] == KEY_O && cheat_buffer[21] == KEY_V && cheat_buffer[22] == KEY_E && cheat_buffer[23] == KEY_O && cheat_buffer[24] == KEY_U && cheat_buffer[25] == KEY_R && cheat_buffer[26] == KEY_D && cheat_buffer[27] == KEY_I && cheat_buffer[28] == KEY_C && cheat_buffer[29] == KEY_K)
	{
		set_player_model(MODEL_IG_RICKY);
	}

	// BIGBANG - Explode all vehicles
	else if (cheat_buffer[23] == KEY_B && cheat_buffer[24] == KEY_I && cheat_buffer[25] == KEY_G && cheat_buffer[26] == KEY_B && cheat_buffer[27] == KEY_A && cheat_buffer[28] == KEY_N && cheat_buffer[29] == KEY_G)
	{
		Vector3 position;

		GET_CHAR_COORDINATES(GetPlayerPed(), &position.x, &position.y, &position.z);

		int i;

		for (i = 0; i < 20; i++)
		{
			int j;

			for (j = 0; j < 20; j++)
			{
				Vehicle vehicle;
				vehicle = GET_CLOSEST_CAR(position.x + (i * 10 - 100), position.y +(j * 10 - 100), position.z, 300.0, 0, 69);

				if (DOES_VEHICLE_EXIST(vehicle))
				{
					EXPLODE_CAR(vehicle, 1, 0);

					MARK_CAR_AS_NO_LONGER_NEEDED(&vehicle);
				}
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}

void process_cheats(void)
{
	if (!IS_PLAYER_PLAYING(GetPlayerIndex()))
	{
		return;
	}

	int key = get_pressed_cheat_key();

	if (key == 0)
	{
		return;
	}

	update_cheat_buffer(key);

	if (process_cheat_buffer())
	{
		update_cheat_buffer(0);

		PRINT_HELP("CHEAT1");

		INCREMENT_INT_STAT(STAT_TIMES_CHEATED, 1);
	}

	return;
}

void main(void)
{
	reset_cheat_keys();
	reset_cheat_buffer();

	while (true)
	{
		WAIT(0);

		process_cheats();
	}
}