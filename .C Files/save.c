#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "features.h"
#include "globals.h"

Vector3 save_position;
float save_angle;

void show_save_game_help_box(void)
{
	if (!IS_THIS_HELP_MESSAGE_BEING_DISPLAYED("NESAVINGHELP")) // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
	{
		PRINT_HELP_FOREVER("NESAVINGHELP"); // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
	}
}

bool has_player_pressed_save_game_key(void)
{
	if (!IS_USING_CONTROLLER() && IS_CONTROL_PRESSED(2, 181) || IS_USING_CONTROLLER() && IS_BUTTON_PRESSED(0, 16))
	{
		return true;
	}

	return false;
}

void show_save_game_menu(void)
{
	SET_PLAYER_CONTROL(GetPlayerIndex(), false);

	DO_SCREEN_FADE_OUT(1000);

	while (!IS_SCREEN_FADED_OUT())
	{
		WAIT(0);
	}

	uint hour, minute;
	GET_TIME_OF_DAY(&hour, &minute);
	FORWARD_TO_TIME_OF_DAY(hour + 6, minute);

	CLEAR_WANTED_LEVEL(GetPlayerIndex());
	CLEAR_AREA_OF_COPS(save_position.x, save_position.y, save_position.z, 100.0);
	SET_CHAR_HEALTH(GetPlayerPed(), 200);
	RESET_VISIBLE_PED_DAMAGE(GetPlayerPed());
	SET_CHAR_COORDINATES_NO_OFFSET(GetPlayerPed(), save_position.x, save_position.y, save_position.z);
	SET_CHAR_HEADING(GetPlayerPed(), save_angle);
	SET_CAM_BEHIND_PED(GetPlayerPed());

	ACTIVATE_SAVE_MENU();

	if (DID_SAVE_COMPLETE_SUCCESSFULLY())
	{
		INCREMENT_INT_STAT(STAT_SAVES_MADE, 1);
		SET_INT_STAT(STAT_KILLS_SINCE_LAST_SAVE, 0);
	}

	SET_PLAYER_CONTROL(GetPlayerIndex(), true);

	DO_SCREEN_FADE_IN(1000);

	while (!IS_SCREEN_FADED_IN())
	{
		WAIT(0);
	}
}

void save_game(void)
{
	if (G_ONMISSION || !IS_PLAYER_PLAYING(GetPlayerIndex()) || IS_CHAR_DEAD(GetPlayerPed()) || HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()) || IS_CHAR_IN_ANY_CAR(GetPlayerPed()) || IS_AUTO_SAVE_IN_PROGRESS())
	{
		return;
	}

	if (G_COUNT > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), -643.221, 244.286, 5.832, -646.473, 246.34, 9.572, 0)) // Printworks
	{
		show_save_game_help_box();

		if (has_player_pressed_save_game_key())
		{
			save_position.x = -645.084;
			save_position.y = 246.738;
			save_position.z = 6.27582;
			save_angle = -5.0;

			show_save_game_menu();
		}
	}
	else if (G_BUSINES_SA > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), -595.019, -317.531, 6.782, -598.862, -313.54, 10.782, 0)) // Sunshine Autos
	{
		show_save_game_help_box();
		
		if (has_player_pressed_save_game_key())
		{
			save_position.x = -595.363;
			save_position.y = -318.285;
			save_position.z = 7.53234;
			save_angle = -150.0;

			show_save_game_menu();
		}
	}
	else if (G_PRON > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), 349.382, 1463.778, 4.527, 346.333, 1467.335, 8.02, 0)) // Interglobal Films (bed)
	{
		show_save_game_help_box();

		if (has_player_pressed_save_game_key())
		{
			save_position.x = 346.101;
			save_position.y = 1464.79;
			save_position.z = 5.03874;
			save_angle = 125.0;

			show_save_game_menu();
		}
	}
	else if (G_PRON > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), 344.294, 1471.025, 4.527, 342.19, 1473.941, 8.02, 0)) // Interglobal Films (couch)
	{
		show_save_game_help_box();

		if (has_player_pressed_save_game_key())
		{
			save_position.x = 341.992;
			save_position.y = 1471.62;
			save_position.z = 5.03874;
			save_angle = 125.0;

			show_save_game_menu();
		}
	}
	else if (G_ICECREAM > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), -445.067, -47.23, 4.972, -447.067, -4.102, 8.562, 0)) // Cherry Popper Icecreams
	{
		show_save_game_help_box();

		if (has_player_pressed_save_game_key())
		{
			save_position.x = -444.516;
			save_position.y = -45.5149;
			save_position.z = 5.47654;
			save_angle = -80.0;

			show_save_game_menu();
		}
	}
	else if (G_CABS > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), -564.786, 719.034, 5.225, -566.732, 722.27, 9.459, 0)) // Kaufman Cabs
	{
		show_save_game_help_box();

		if (has_player_pressed_save_game_key())
		{
			save_position.x = -567.321;
			save_position.y = 720.751;
			save_position.z = 5.67434;
			save_angle = 60.0;

			show_save_game_menu();
		}
	}
	else if (G_CLUB > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), 897.958, 479.305, 9.559, 893.964, 483.173, 12.29, 0)) // Malibu Club
	{
		show_save_game_help_box();

		if (has_player_pressed_save_game_key())
		{
			save_position.x = 896.001;
			save_position.y = 479.025;
			save_position.z = 9.93599;
			save_angle = -175.0;

			show_save_game_menu();
		}
	}
	else if (G_COKERUN > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), -234.66, -952.034, 7.566, -236.961, -949.769, 11.824, 0)) // The Boatyard
	{
		show_save_game_help_box();

		if (has_player_pressed_save_game_key())
		{
			save_position.x = -235.225;
			save_position.y = -949.423;
			save_position.z = 8.07865;
			save_angle = -25.0;

			show_save_game_menu();
		}
	}
	else if (G_STRIP > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), 508.048, -917.682, 4.345, 505.62, -915.054, 7.33, 0)) // Pole Position Club
	{
		show_save_game_help_box();

		if (has_player_pressed_save_game_key())
		{
			save_position.x = 507.606;
			save_position.y = -917.858;
			save_position.z = 4.84248;
			save_angle = -175.0;

			show_save_game_menu();
		}
	}
	else if (G_SWANKO > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), 863.972, 1132.26, 6.177, 858.972, 1137.26, 11.177, 0)) // El Swanko Casa
	{
		save_position.x = 861.53;
		save_position.y = 1139.81;
		save_position.z = 6.99313;
		save_angle = 0.0;

		show_save_game_menu();
	}
	else if (G_LINKS > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), 736.09, 906.963, 6.693, 731.09, 911.963, 11.693, 0)) // Links View Apartment
	{
		save_position.x = 737.991;
		save_position.y = 909.371;
		save_position.z = 7.45291;
		save_angle = -85.0;

		show_save_game_menu();
	}
	else if (G_CONDO > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), -400.854, 1841.342, 5.229, -404.119, 1845.572, 10.229, 0)) // Hyman Condo
	{
		save_position.x = -401.593;
		save_position.y = 1839.58;
		save_position.z = 5.7949;
		save_angle = -165.0;

		show_save_game_menu();
	}
	else if (G_HEIGHS > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), 453.212, -972.369, 6.965, 447.555, -969.353, 10.267, 0)) // Ocean Heighs Aprt
	{
		save_position.x = 451.255;
		save_position.y = -967.217;
		save_position.z = 7.52892;
		save_angle = -5.0;

		show_save_game_menu();
	}
	else if (G_WS_1102 > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), 521.188, -272.005, 5.308, 518.527, -269.363, 10.308, 0)) // 1102 Washington Street
	{
		save_position.x = 522.489;
		save_position.y = -272.164;
		save_position.z = 6.00446;
		save_angle = -120.0;

		show_save_game_menu();
	}
	else if (G_VP_3321 > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), 967.985, 1806.919, 11.92, 964.985, 1809.919, 16.438, 0)) // 3321 Vice Point
	{
		save_position.x = 963.529;
		save_position.y = 1805.22;
		save_position.z = 12.0903;
		save_angle = 130.0;

		show_save_game_menu();
	}
	else if (G_SHACK > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), -125.348, 1231.967, 14.033, -129.233, 1235.396, 17.309, 0)) // Skumole Shack
	{
		save_position.x = -127.19;
		save_position.y = 1236.19;
		save_position.z = 14.8111;
		save_angle = 0.0;

		show_save_game_menu();
	}
	else if (IS_CHAR_IN_AREA_3D(GetPlayerPed(), 662.561, -731.554, 13.874, 659.649, -728.9, 17.472, 0)) // Ocean View Hotel
	{
		show_save_game_help_box();

		if (has_player_pressed_save_game_key())
		{
			save_position.x = 661.254;
			save_position.y = -731.808;
			save_position.z = 14.4212;
			save_angle = -175.0;

			show_save_game_menu();
		}
	}
	else if (G_PROTECT > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), 29.714, -26.031, 12.711, 26.559, -24.301, 15.638, 0)) // Vercetti Mansion (couch 1 (1st floor))
	{
		show_save_game_help_box();

		if (has_player_pressed_save_game_key())
		{
			save_position.x = 28.115;
			save_position.y = -26.2823;
			save_position.z = 13.2436;
			save_angle = -175.0;

			show_save_game_menu();
		}
	}
	else if (G_PROTECT > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), 29.714, -30.213, 12.711, 26.559, -28.483, 15.638, 0)) // Vercetti Mansion (couch 2 (1st floor))
	{
		show_save_game_help_box();

		if (has_player_pressed_save_game_key())
		{
			save_position.x = 28.0589;
			save_position.y = -28.1805;
			save_position.z = 13.2436;
			save_angle = -10.0;

			show_save_game_menu();
		}
	}
	else if (G_PROTECT > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), 62.09, -60.884, 19.687, 59.834, -58.636, 24.098, 0)) // Vercetti Mansion (couch 1 (2nd floor))
	{
		show_save_game_help_box();

		if (has_player_pressed_save_game_key())
		{
			save_position.x = 60.0189;
			save_position.y = -58.3347;
			save_position.z = 20.0673;
			save_angle = 40.0;

			show_save_game_menu();
		}
	}
	else if (G_PROTECT > 0 && IS_CHAR_IN_AREA_3D(GetPlayerPed(), 48.989, -62.33, 19.687, 46.732, -59.231, 24.098, 0)) // Vercetti Mansion (couch 2 (2nd floor))
	{
		show_save_game_help_box();

		if (has_player_pressed_save_game_key())
		{
			save_position.x = 49.0995;
			save_position.y = -59.0782;
			save_position.z = 20.0673;
			save_angle = -45.0;

			show_save_game_menu();
		}
	}
	else
	{
		if (IS_THIS_HELP_MESSAGE_BEING_DISPLAYED("NESAVINGHELP")) // Press the ~INPUT_PHONE_ACCEPT~ button to save the game.
		{
			CLEAR_HELP();
		}
	}

	return;
}

void main(void)
{
	if (G_LAWYER >= 1)
	{
		SET_CHAR_HEALTH(GetPlayerPed(), 200);

		Vector3 player_position; 
		GET_CHAR_COORDINATES(GetPlayerPed(), &player_position.x, &player_position.y, &player_position.z);
		LOAD_SCENE(player_position.x, player_position.y, player_position.z);

		WAIT(4000);

		SET_CAM_BEHIND_PED(GetPlayerPed());

		DO_SCREEN_FADE_IN_UNHACKED(3000);
	}

	while (true)
	{
		WAIT(0);

		save_game();
	}
}