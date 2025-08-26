/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
#include "mission_passed.h"

#define OPPONENT_PLAYBACK_SPEED 0.62		/*rebusx*/

uint CarM2 = MODEL_SPEEDO;
Car car0, car1, car2, car3, car4, car5;
Ped ped1, ped2, ped3;
Cam camera;
Texture fon, timer;
Blip Blip_r, Blip_r2, Blip_c1, Blip_c2, Blip_c3;
uint checkpoint;

float textur, skip, start, poziteon, time_m, time_s, pley_rrr, zone;
float Blip_x2, Blip_y2, Blip_z2;
float PlayX, PlayY, PlayZ, Blip_x, Blip_y, Blip_z, PlayR, play_cord;
float Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, Ped1R, ped1_cord, ped1_lap;
float Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, Ped2R, ped2_cord, ped2_lap;
float Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, Ped3R, ped3_cord, ped3_lap;


int intro_skip = 0;		/*rebusx*/


#define KEYBOARD_ENTER			28
#define KEYBOARD_SPACE			57
#define CONTROL_KEYBOARD_HORN	54
#define CONTROL_MOUSE_LEFT		38

#define CONTROLLER_BUTTON_B		17

void check_skip_intro()
{
	if ( (!IS_USING_CONTROLLER() && (IS_GAME_KEYBOARD_KEY_PRESSED(KEYBOARD_ENTER) || IS_GAME_KEYBOARD_KEY_PRESSED(KEYBOARD_SPACE) || IS_CONTROL_PRESSED(2, CONTROL_KEYBOARD_HORN) || IS_CONTROL_PRESSED(2, CONTROL_MOUSE_LEFT)))
	|| (IS_USING_CONTROLLER() && IS_BUTTON_PRESSED(0, CONTROLLER_BUTTON_B)) )
	{
		intro_skip = 1;
	}
}

void SetTime_intro(uint time)		/*rebusx*/
{
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if (!intro_skip)
		{
			check_skip_intro();
		}
		if (intro_skip)
		{
			break;
		}
		if ((TIMERA() > time) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// поверка игрок мёртв/арестован
		{
			break;
		}
	}
}

void SetTime(uint time)
{
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if ((TIMERA() > time) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// поверка игрок мёртв/арестован
		{
			break;
		}
	}
}

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

void rc_baron(void)
{
	if (!IS_BIT_SET(G_RC_1, 1))
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}
	skip = 0;
	start = 1;
	zone = 1;
	time_m = 0;
	time_s = 0;
	
	Blip_x = 750.926;
	Blip_y = 1752.88;
	Blip_z = 21.554;
	Blip_x2 = 754.35;
	Blip_y2 = 1635.11;
	Blip_z2 = 26.448;
	play_cord = 1;

	ped1B_x = 750.926;
	ped1B_y = 1752.88;
	ped1B_z = 21.554;
	ped1_cord = 1;

	ped2B_x = 750.926;
	ped2B_y = 1752.88;
	ped2B_z = 21.554;
	ped2_cord = 1;

	ped3B_x = 750.926;
	ped3B_y = 1752.88;
	ped3B_z = 21.554;
	ped3_cord = 1;

	textur = LOAD_TXD( "sunshine_race" );
	fon = GET_TEXTURE( textur, "fon_hud" );
	timer = GET_TEXTURE( textur, "timer_hud" );

	uint CarM1 = MODEL_TOURMAV;// байк
	uint PedM1 = MODEL_M_Y_GALB_LO_01;// байкер 1

	REQUEST_MODEL(CarM1);
	while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
	REQUEST_MODEL(PedM1);// Мерседес
	while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало

	REQUEST_CAR_RECORDING( 3066 ); // полёт Основной
	while (!HAS_CAR_RECORDING_BEEN_LOADED( 3066 )) WAIT(0);
	REQUEST_CAR_RECORDING( 3067 ); // полёт Основной
	while (!HAS_CAR_RECORDING_BEEN_LOADED( 3067 )) WAIT(0);
	REQUEST_CAR_RECORDING( 3068 ); // полёт Основной
	while (!HAS_CAR_RECORDING_BEEN_LOADED( 3068 )) WAIT(0);

	CREATE_CAR(CarM1, 746.0, 1771.332, 21.546, &car4, TRUE);
	CREATE_CAR(CarM1, 749.0, 1771.332, 21.554, &car1, TRUE);
	CREATE_CAR(CarM1, 752.0, 1771.332, 21.554, &car2, TRUE);
	CREATE_CAR(CarM1, 755.0, 1771.332, 21.554, &car3, TRUE);
	SET_CAR_HEADING(car1, 182.2);
	SET_CAR_HEADING(car2, 182.2);
	SET_CAR_HEADING(car3, 182.2);
	SET_CAR_HEADING(car4, 182.2);
	SET_CAR_LIVERY(car1, 2);
	SET_CAR_LIVERY(car2, 2);
	SET_CAR_LIVERY(car3, 2);
	SET_CAR_LIVERY(car4, 2);

	CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//создаём педа за рулём автомобиля
	CREATE_CHAR_INSIDE_CAR(car2, 1, PedM1, &ped2);//создаём педа за рулём автомобиля
	CREATE_CHAR_INSIDE_CAR(car3, 1, PedM1, &ped3);//создаём педа за рулём автомобиля
	SET_CHAR_PROOFS(ped1, TRUE, TRUE, TRUE, TRUE, TRUE);//делает педа бесмертным
	SET_CHAR_PROOFS(ped2, TRUE, TRUE, TRUE, TRUE, TRUE);//делает педа бесмертным
	SET_CHAR_PROOFS(ped3, TRUE, TRUE, TRUE, TRUE, TRUE);//делает педа бесмертным

	WAIT(100);
	SET_CHAR_VISIBLE(ped1, 0); //прозрачный игрок
	SET_CHAR_VISIBLE(ped2, 0); //прозрачный игрок
	SET_CHAR_VISIBLE(ped3, 0); //прозрачный игрок
	TASK_ENTER_CAR_AS_DRIVER(GetPlayerPed(), car4, TRUE);//садим игрока в верталёт
	WAIT(100);
	SET_CAR_ENGINE_ON(car4, 1, 1);		/*rebusx: исправление чтобы включать наш двигатель перед стартом*/

	START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3066, 0.0, 0.0, 0.0);
	START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 3067, 0.0, 0.0, 0.0);
	START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 3068, 0.0, 0.0, 0.0);
	SET_PLAYBACK_SPEED(car1, OPPONENT_PLAYBACK_SPEED);		/*rebusx*/
	SET_PLAYBACK_SPEED(car2, OPPONENT_PLAYBACK_SPEED);		/*rebusx*/
	SET_PLAYBACK_SPEED(car3, OPPONENT_PLAYBACK_SPEED);		/*rebusx*/
	PAUSE_PLAYBACK_RECORDED_CAR(car1);
	PAUSE_PLAYBACK_RECORDED_CAR(car2);
	PAUSE_PLAYBACK_RECORDED_CAR(car3);

	DO_SCREEN_FADE_OUT( 250 );// Затемняем экран
	while(true)
	{
		WAIT(0);
		if (IS_SCREEN_FADED_OUT())
		{
			break;
		}
	}
	SET_CAR_ENGINE_ON(car4, 1, 1);		/*rebusx: исправление чтобы включать наш двигатель перед стартом*/
	checkpoint = CREATE_CHECKPOINT( 4, 722.354, 1322.47, 22.426, 634.599, 1222.72, 22.896, 0.60000000 );
	POINT_CAM_AT_COORD	( camera, 747.992, 1768.75, 22.1365 ); // куда смотрит камера
	SET_CAM_POS			( camera, 759.072, 1777.28, 23.4156 );//расположение камеры
	DO_SCREEN_FADE_IN( 250 );// убирается затемнение экрана
	PRINT_STRING_IN_STRING("string", "NERCPL1_4", 5000, 1);//~g~Compete in a CHECKPOINT RACE with 3 other RC Plane's
	SetTime_intro(5000);		/*rebusx*/
	
	if (!intro_skip)		/*rebusx*/
	{
		POINT_CAM_AT_COORD	( camera, 723.923, 1319.87, 22.426 ); // куда смотрит камера
		SET_CAM_POS			( camera, 703.739, 1359.13, 27.223 );//расположение камеры
		PRINT_STRING_IN_STRING("string", "RCPL1_5", 5000, 1);//~g~Fly through the checkpoints scattered throughout Vice City.
		SetTime_intro(5000);		/*rebusx*/
	}

	CLEAR_AREA( 1162.67, 1225.26, 8.77136, 5.0, 1);//очещаем зону загрузки

	if (!intro_skip)		/*rebusx*/
	{
		POINT_CAM_AT_COORD	( camera, 753.116, 1773.84, 22.1365 ); // куда смотрит камера
		SET_CAM_POS			( camera, 742.441, 1767.64, 22.6977 );//расположение камеры
		PRINT_STRING_IN_STRING("string", "RCH1_8", 5000, 1);//~g~If you wish to quit this mission press the ~h~~k~~PED_FIREWEAPON~ ~g~button to detonate your RC Plane.
		SetTime_intro(5000);		/*rebusx*/
	}

	DELETE_CHECKPOINT(checkpoint);
	checkpoint = CREATE_CHECKPOINT( 4, Blip_x, Blip_y, (Blip_z+1.5), Blip_x2, Blip_y2, Blip_z2, 0.60000000 );

	CREATE_CAR(CarM2, 741.176, 1785.59, 22.1314, &car5, TRUE);
	SET_CAR_HEADING(car5, 180.0);
	SET_CAR_PROOFS(car5, 1, 1, 1, 1, 1);
	FREEZE_CAR_POSITION(car5, 1);

	DO_SCREEN_FADE_OUT( 250 );// Затемняем экран
	while(true)
	{
		WAIT(0);
		if (IS_SCREEN_FADED_OUT())
		{
			break;
		}
	}

	SET_CAM_BEHIND_PED( GetPlayerPed() );
	ACTIVATE_SCRIPTED_CAMS( 0, 0 );
	END_CAM_COMMANDS( &camera );
	SET_WIDESCREEN_BORDERS( 0 );
	DO_SCREEN_FADE_IN( 250 );// убирается затемнение экрана
	SetTime(1000);

	SET_FOLLOW_VEHICLE_CAM_SUBMODE(2);

	PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
	SETTIMERA(0);
	while (true)
	{
		SET_TEXT_FONT(4);
		SET_TEXT_COLOUR(235, 115, 18, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(2, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", 3);// 3
		if (TIMERA() > 900)
		{
			break;
		}
		WAIT(0);
	}
	PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
	SETTIMERA(0);
	while (true)
	{
		SET_TEXT_FONT(4);
		SET_TEXT_COLOUR(235, 115, 18, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(2, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", 2);// 2
		if (TIMERA() > 900)
		{
			break;
		}
		WAIT(0);
	}
	PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
	SETTIMERA(0);
	while (true)
	{
		SET_TEXT_FONT(4);
		SET_TEXT_COLOUR(235, 115, 18, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(2, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", 1);// 1
		if (TIMERA() > 900)
		{
			break;
		}
		WAIT(0);
	}
	SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// Размораживаем игрока

	// сама гонка тут
	ADD_BLIP_FOR_CHAR(ped1, &Blip_c1);
	CHANGE_BLIP_SPRITE(Blip_c1, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
	CHANGE_BLIP_COLOUR(Blip_c1, 12);   //цвет иконка на радаре (0=белая)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_c1, "NE_RACE1");//иконка на радаре "Blip01" называние в истории карты
	CHANGE_BLIP_SCALE(Blip_c1, 0.77999990); // масштаб иконки на радаре

	ADD_BLIP_FOR_CHAR(ped2, &Blip_c2);
	CHANGE_BLIP_SPRITE(Blip_c2, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
	CHANGE_BLIP_COLOUR(Blip_c2, 8);   //цвет иконка на радаре (0=белая)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_c2, "NE_RACE1");//иконка на радаре "Blip01" называние в истории карты
	CHANGE_BLIP_SCALE(Blip_c2, 0.77999990); // масштаб иконки на радаре

	ADD_BLIP_FOR_CHAR(ped3, &Blip_c3);
	CHANGE_BLIP_SPRITE(Blip_c3, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
	CHANGE_BLIP_COLOUR(Blip_c3, 19);   //цвет иконка на радаре (0=белая)
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_c3, "NE_RACE1");//иконка на радаре "Blip01" называние в истории карты
	CHANGE_BLIP_SCALE(Blip_c3, 0.77999990); // масштаб иконки на радаре

	SETTIMERA( 0 );
	SETTIMERC( 0 );
	while(true)
	{
		WAIT(0);
		SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);
		if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) || (GET_ENGINE_HEALTH(car4) < 200) || (IS_CAR_IN_WATER(car4)))//если игрок покинул или унечтожел вертолёт, тогда провал миссии
		{
			PRINT_STRING_IN_STRING_NOW("string", "RCH1_13", 7000, 1);//~r~The RC helicopter went out of range!
			EXPLODE_CAR(car4, 1, 1);
			skip = 1;
			SetTime(1000);
			break;
		}
		else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1111.464, -1224.025, -15.5, 0.111, 1929.629, 133.687, 0 ))
		{
			PRINT_STRING_IN_STRING_NOW("string", "RCH1_13", 7000, 1);//~r~The RC helicopter went out of range!
			EXPLODE_CAR(car4, 1, 1);
			SetTime(1000);
			skip = 1;
			break;
		}

		if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1081.499, -1193.107, -15.0, 30.077, 1898.711, 125.0, 0 )) && (zone == 1))
		{
			PRINT_HELP_FOREVER("RCH1_12"); //~g~The RC helicopter is getting too far out of range!
			zone = 0;
		}
		else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1081.499, -1193.107, -15.0, 30.077, 1898.711, 125.0, 0 )) && (zone == 0))
		{
			CLEAR_HELP(); // удаляем текст подсказки
			zone = 1;
		}

		if (start == 1)
		{
			PLAY_AUDIO_EVENT( "FRONTEND_GAME_PICKUP_CHECKPOINT" );
			//TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
			//TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
			//TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
			
			ADD_BLIP_FOR_COORD(Blip_x, Blip_y, Blip_z, &Blip_r);//создаем иконку на радаре в переменной "Blip01"
			CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
			CHANGE_BLIP_COLOUR(Blip_r, 5);   //цвет иконка на радаре (0=белая)
			CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_RACE2");//иконка на радаре "Blip01" называние в истории карты
			CHANGE_BLIP_SCALE(Blip_r, 0.77999990); // масштаб иконки на радаре
			
			ADD_BLIP_FOR_COORD(Blip_x2, Blip_y2, Blip_z2, &Blip_r2);//создаем иконку на радаре в переменной "Blip01"
			CHANGE_BLIP_SPRITE(Blip_r2, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
			CHANGE_BLIP_COLOUR(Blip_r2, 5);   //цвет иконка на радаре (0=белая)
			CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//иконка на радаре "Blip01" называние в истории карты
			CHANGE_BLIP_SCALE(Blip_r2, (0.77999990 / 1.50000000)); // масштаб иконки на радаре
			CHANGE_BLIP_ALPHA(Blip_r2, 125);
			start = 2;
			pley_rrr = 1;
			SETTIMERB( 0 );
		}
		if (TIMERC() < 990)
		{
			SET_TEXT_FONT(4);
			SET_TEXT_COLOUR(235, 115, 18, 255);
			SET_TEXT_SCALE(0.5, 0.7);
			SET_TEXT_EDGE(2, 0, 0, 0, 255);
			SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "GO", 1); // пишем "GO"
		}

		if (pley_rrr == 1)
		{
			UNPAUSE_PLAYBACK_RECORDED_CAR(car1);
			UNPAUSE_PLAYBACK_RECORDED_CAR(car2);
			UNPAUSE_PLAYBACK_RECORDED_CAR(car3);
			SETTIMERB( 0 );
			pley_rrr = 2;
		}

		// гонка тут
		//DRAW_SPHERE(Blip_x, Blip_y, (Blip_z-4.5), 7.0);
		GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
		GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, Blip_x, Blip_y, Blip_z, &PlayR);//проверка "игрок на координатах"
		if ( PlayR < 8.5 )
		{
			play_cord += 1;
			Blip_x = Blip_x2; 
			Blip_y = Blip_y2;
			Blip_z = Blip_z2;
			PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );

			if (play_cord == 2)
			{
				Blip_x2 = 750.778;
				Blip_y2 = 1482.34;
				Blip_z2 = 24.25;
			}
			else if (play_cord == 3)
			{
				Blip_x2 = 722.354;
				Blip_y2 = 1322.47;
				Blip_z2 = 22.426;
			}
			else if (play_cord == 4)
			{
				Blip_x2 = 634.599;
				Blip_y2 = 1222.72;
				Blip_z2 = 22.896;
			}
			else if (play_cord == 5)
			{
				Blip_x2 = 811.602;
				Blip_y2 = 1097.23;
				Blip_z2 = 15.846;
			}
			else if (play_cord == 6)
			{
				Blip_x2 = 779.553;
				Blip_y2 = 978.865;
				Blip_z2 = 14.168;
			}
			else if (play_cord == 7)
			{
				Blip_x2 = 764.891;
				Blip_y2 = 877.459;
				Blip_z2 = 13.385;
			}
			else if (play_cord == 8)
			{
				Blip_x2 = 770.064;
				Blip_y2 = 776.41;
				Blip_z2 = 19.428;
			}
			else if (play_cord == 9)
			{
				Blip_x2 = 840.542;
				Blip_y2 = 635.447;
				Blip_z2 = 19.134;
			}
			else if (play_cord == 10)
			{
				Blip_x2 = 765.597;
				Blip_y2 = 520.781;
				Blip_z2 = 20.134;
			}
			else if (play_cord == 11)
			{
				Blip_x2 = 717.866;
				Blip_y2 = 388.471;
				Blip_z2 = 17.046;
			}
			else if (play_cord == 12)
			{
				Blip_x2 = 658.013;
				Blip_y2 = 261.482;
				Blip_z2 = 14.929;
			}
			else if (play_cord == 13)
			{
				Blip_x2 = 627.309;
				Blip_y2 = 167.991;
				Blip_z2 = 14.146;
			}
			else if (play_cord == 14)
			{
				Blip_x2 = 612.89;
				Blip_y2 = 32.968;
				Blip_z2 = 12.304;
			}
			else if (play_cord == 15)
			{
				Blip_x2 = 604.669;
				Blip_y2 = -105.857;
				Blip_z2 = 12.328;
			}
			else if (play_cord == 16)
			{
				Blip_x2 = 582.798;
				Blip_y2 = -205.283;
				Blip_z2 = 11.001;
			}
			else if (play_cord == 17)
			{
				Blip_x2 = 528.276;
				Blip_y2 = -305.345;
				Blip_z2 = 10.527;
			}
			else if (play_cord == 18)
			{
				Blip_x2 = 410.301;
				Blip_y2 = -336.548;
				Blip_z2 = 11.142;
			}
			else if (play_cord == 19)
			{
				Blip_x2 = 325.847;
				Blip_y2 = -362.34;
				Blip_z2 = 13.43;
			}
			else if (play_cord == 20)
			{
				Blip_x2 = 242.523;
				Blip_y2 = -411.935;
				Blip_z2 = 15.094;
			}
			else if (play_cord == 21)
			{
				Blip_x2 = 246.695;
				Blip_y2 = -542.039;
				Blip_z2 = 27.099;
			}
			else if (play_cord == 22)
			{
				Blip_x2 = 239.984;
				Blip_y2 = -699.925;
				Blip_z2 = 11.655;
			}
			else if (play_cord == 23)
			{
				Blip_x2 = 268.544;
				Blip_y2 = -869.917;
				Blip_z2 = 11.294;
			}
			else if (play_cord == 24)
			{
				Blip_x2 = 317.674;
				Blip_y2 = -979.663;
				Blip_z2 = 10.455;
			}
			else if (play_cord == 25)
			{
				Blip_x2 = 421.182;
				Blip_y2 = -1043.65;
				Blip_z2 = 10.96;
			}
			else if (play_cord == 26)
			{
				Blip_x2 = 543.56;
				Blip_y2 = -1055.12;
				Blip_z2 = 11.516;
			}
			else if (play_cord == 27)
			{
				Blip_x2 = 607.464;
				Blip_y2 = -994.732;
				Blip_z2 = 15.699;
			}
			else if (play_cord == 28)
			{
				Blip_x2 = 692.539;
				Blip_y2 = -701.819;
				Blip_z2 = 27.351;
			}
			else if (play_cord == 29)
			{
				Blip_x2 = Blip_x2; 
				Blip_y2 = Blip_y2;
				Blip_z2 = Blip_z2;
			}
			else if (play_cord == 30)
			{
				skip = 2;
				break;
			}
			if (play_cord < 29)
			{
				REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
				REMOVE_BLIP(Blip_r2);//Удаляем иконку на радаре
				DELETE_CHECKPOINT(checkpoint);
				ADD_BLIP_FOR_COORD(Blip_x, Blip_y, (Blip_z + 0.1), &Blip_r);//создаем иконку на радаре в переменной "Blip01"
				CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(Blip_r, 5);   //цвет иконка на радаре (0=белая)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_RACE2");//иконка на радаре "Blip01" называние в истории карты
				CHANGE_BLIP_SCALE(Blip_r, 0.77999990); // масштаб иконки на радаре
				checkpoint = CREATE_CHECKPOINT( 4, Blip_x, Blip_y, (Blip_z+1.5), Blip_x2, Blip_y2, Blip_z2, 0.60000000 );
				if (play_cord < 28)
				{
					ADD_BLIP_FOR_COORD(Blip_x2, Blip_y2, (Blip_z2 + 0.1), &Blip_r2);//создаем иконку на радаре в переменной "Blip01"
					CHANGE_BLIP_SPRITE(Blip_r2, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
					CHANGE_BLIP_COLOUR(Blip_r2, 5);   //цвет иконка на радаре (0=белая)
					CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//иконка на радаре "Blip01" называние в истории карты
					CHANGE_BLIP_SCALE(Blip_r2, (0.77999990 / 1.50000000)); // масштаб иконки на радаре
					CHANGE_BLIP_ALPHA(Blip_r2, 125);
				}
				else
				{
					ADD_BLIP_FOR_COORD(Blip_x2, Blip_y2, (Blip_z2 + 0.1), &Blip_r2);//создаем иконку на радаре в переменной "Blip01"
					CHANGE_BLIP_SPRITE(Blip_r2, BLIP_FINISH_LINE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
					CHANGE_BLIP_COLOUR(Blip_r2, 0);   //цвет иконка на радаре (0=белая)
					CHANGE_BLIP_SCALE(Blip_r2, 0.77999990); // масштаб иконки на радаре
					CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//иконка на радаре "Blip01" называние в истории карты
					CHANGE_BLIP_ALPHA(Blip_r2, 125);
				}
			}
			else
			{
				REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
				REMOVE_BLIP(Blip_r2);//Удаляем иконку на радаре
				DELETE_CHECKPOINT(checkpoint);
				ADD_BLIP_FOR_COORD(Blip_x, Blip_y, (Blip_z + 0.1), &Blip_r);//создаем иконку на радаре в переменной "Blip01"
				CHANGE_BLIP_SPRITE(Blip_r, BLIP_FINISH_LINE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_RACE2");//иконка на радаре "Blip01" называние в истории карты
				CHANGE_BLIP_COLOUR(Blip_r, 0);   //цвет иконка на радаре (0=белая)
				checkpoint = CREATE_CHECKPOINT( 5, Blip_x, Blip_y, (Blip_z+1.5), Blip_x2, Blip_y2, Blip_z2, 0.60000000 );
			}
		}

//============================== соперник 1 ==============================
		GET_CHAR_COORDINATES(ped1,  &Ped1X, &Ped1Y, &Ped1Z);//вписываем координаты соперника в переменную
		GET_DISTANCE_BETWEEN_COORDS_3D( Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, &Ped1R);//проверка "игрок на координатах"
		if ( Ped1R < 10.0)
		{
			ped1_cord += 1;

			if (ped1_cord == 2)
			{
				ped1B_x = 754.35;
				ped1B_y = 1635.11;
				ped1B_z = 26.448;
			}
			else if (ped1_cord == 3)
			{
				ped1B_x = 750.778;
				ped1B_y = 1482.34;
				ped1B_z = 24.25;
			}
			else if (ped1_cord == 4)
			{
				ped1B_x = 722.354;
				ped1B_y = 1322.47;
				ped1B_z = 22.426;
			}
			else if (ped1_cord == 5)
			{
				ped1B_x = 634.599;
				ped1B_y = 1222.72;
				ped1B_z = 22.896;
			}
			else if (ped1_cord == 6)
			{
				ped1B_x = 811.602;
				ped1B_y = 1097.23;
				ped1B_z = 15.846;
			}
			else if (ped1_cord == 7)
			{
				ped1B_x = 779.553;
				ped1B_y = 978.865;
				ped1B_z = 14.168;
			}
			else if (ped1_cord == 8)
			{
				ped1B_x = 764.891;
				ped1B_y = 877.459;
				ped1B_z = 13.385;
			}
			else if (ped1_cord == 9)
			{
				ped1B_x = 770.064;
				ped1B_y = 776.41;
				ped1B_z = 19.428;
			}
			else if (ped1_cord == 10)
			{
				ped1B_x = 840.542;
				ped1B_y = 635.447;
				ped1B_z = 19.134;
			}
			else if (ped1_cord == 11)
			{
				ped1B_x = 765.597;
				ped1B_y = 520.781;
				ped1B_z = 20.134;
			}
			else if (ped1_cord == 12)
			{
				ped1B_x = 717.866;
				ped1B_y = 388.471;
				ped1B_z = 17.046;
			}
			else if (ped1_cord == 13)
			{
				ped1B_x = 658.013;
				ped1B_y = 261.482;
				ped1B_z = 14.929;
			}
			else if (ped1_cord == 14)
			{
				ped1B_x = 627.309;
				ped1B_y = 167.991;
				ped1B_z = 14.146;
			}
			else if (ped1_cord == 15)
			{
				ped1B_x = 612.89;
				ped1B_y = 32.968;
				ped1B_z = 12.304;
			}
			else if (ped1_cord == 16)
			{
				ped1B_x = 604.669;
				ped1B_y = -105.857;
				ped1B_z = 12.328;
			}
			else if (ped1_cord == 17)
			{
				ped1B_x = 582.798;
				ped1B_y = -205.283;
				ped1B_z = 11.001;
			}
			else if (ped1_cord == 18)
			{
				ped1B_x = 528.276;
				ped1B_y = -305.345;
				ped1B_z = 10.527;
			}
			else if (ped1_cord == 19)
			{
				ped1B_x = 410.301;
				ped1B_y = -336.548;
				ped1B_z = 11.142;
			}
			else if (ped1_cord == 20)
			{
				ped1B_x = 325.847;
				ped1B_y = -362.34;
				ped1B_z = 13.43;
			}
			else if (ped1_cord == 21)
			{
				ped1B_x = 242.523;
				ped1B_y = -411.935;
				ped1B_z = 15.094;
			}
			else if (ped1_cord == 22)
			{
				ped1B_x = 246.695;
				ped1B_y = -542.039;
				ped1B_z = 27.099;
			}
			else if (ped1_cord == 23)
			{
				ped1B_x = 239.984;
				ped1B_y = -699.925;
				ped1B_z = 11.655;
			}
			else if (ped1_cord == 24)
			{
				ped1B_x = 268.544;
				ped1B_y = -869.917;
				ped1B_z = 11.294;
			}
			else if (ped1_cord == 25)
			{
				ped1B_x = 317.674;
				ped1B_y = -979.663;
				ped1B_z = 10.455;
			}
			else if (ped1_cord == 26)
			{
				ped1B_x = 421.182;
				ped1B_y = -1043.65;
				ped1B_z = 10.96;
			}
			else if (ped1_cord == 27)
			{
				ped1B_x = 543.56;
				ped1B_y = -1055.12;
				ped1B_z = 11.516;
			}
			else if (ped1_cord == 28)
			{
				ped1B_x = 607.464;
				ped1B_y = -994.732;
				ped1B_z = 15.699;
			}
			else if (ped1_cord == 29)
			{
				ped1B_x = 692.539;
				ped1B_y = -701.819;
				ped1B_z = 27.351;
			}
			else if (ped1_cord == 30)
			{
				ped1B_x = ped1B_x; 
				ped1B_y = ped1B_y;
				ped1B_z = ped1B_z;
				skip = 1;
				PRINT_STRING_IN_STRING_NOW("string", "RACEFA", 5000, 1);//r~You failed to win the race!
				break;
			}
			//TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 60.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
		}

//============================== соперник 2 ==============================
		GET_CHAR_COORDINATES(ped2,  &Ped2X, &Ped2Y, &Ped2Z);//вписываем координаты соперника в переменную
		GET_DISTANCE_BETWEEN_COORDS_3D( Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, &Ped2R);//проверка "игрок на координатах"
		if ( Ped2R < 10.0)
		{
			ped2_cord += 1;

			if (ped2_cord == 2)
			{
				ped2B_x = 754.35;
				ped2B_y = 1635.11;
				ped2B_z = 26.448;
			}
			else if (ped2_cord == 3)
			{
				ped2B_x = 750.778;
				ped2B_y = 1482.34;
				ped2B_z = 24.25;
			}
			else if (ped2_cord == 4)
			{
				ped2B_x = 722.354;
				ped2B_y = 1322.47;
				ped2B_z = 22.426;
			}
			else if (ped2_cord == 5)
			{
				ped2B_x = 634.599;
				ped2B_y = 1222.72;
				ped2B_z = 22.896;
			}
			else if (ped2_cord == 6)
			{
				ped2B_x = 811.602;
				ped2B_y = 1097.23;
				ped2B_z = 15.846;
			}
			else if (ped2_cord == 7)
			{
				ped2B_x = 779.553;
				ped2B_y = 978.865;
				ped2B_z = 14.168;
			}
			else if (ped2_cord == 8)
			{
				ped2B_x = 764.891;
				ped2B_y = 877.459;
				ped2B_z = 13.385;
			}
			else if (ped2_cord == 9)
			{
				ped2B_x = 770.064;
				ped2B_y = 776.41;
				ped2B_z = 19.428;
			}
			else if (ped2_cord == 10)
			{
				ped2B_x = 840.542;
				ped2B_y = 635.447;
				ped2B_z = 19.134;
			}
			else if (ped2_cord == 11)
			{
				ped2B_x = 765.597;
				ped2B_y = 520.781;
				ped2B_z = 20.134;
			}
			else if (ped2_cord == 12)
			{
				ped2B_x = 717.866;
				ped2B_y = 388.471;
				ped2B_z = 17.046;
			}
			else if (ped2_cord == 13)
			{
				ped2B_x = 658.013;
				ped2B_y = 261.482;
				ped2B_z = 14.929;
			}
			else if (ped2_cord == 14)
			{
				ped2B_x = 627.309;
				ped2B_y = 167.991;
				ped2B_z = 14.146;
			}
			else if (ped2_cord == 15)
			{
				ped2B_x = 612.89;
				ped2B_y = 32.968;
				ped2B_z = 12.304;
			}
			else if (ped2_cord == 16)
			{
				ped2B_x = 604.669;
				ped2B_y = -105.857;
				ped2B_z = 12.328;
			}
			else if (ped2_cord == 17)
			{
				ped2B_x = 582.798;
				ped2B_y = -205.283;
				ped2B_z = 11.001;
			}
			else if (ped2_cord == 18)
			{
				ped2B_x = 528.276;
				ped2B_y = -305.345;
				ped2B_z = 10.527;
			}
			else if (ped2_cord == 19)
			{
				ped2B_x = 410.301;
				ped2B_y = -336.548;
				ped2B_z = 11.142;
			}
			else if (ped2_cord == 20)
			{
				ped2B_x = 325.847;
				ped2B_y = -362.34;
				ped2B_z = 13.43;
			}
			else if (ped2_cord == 21)
			{
				ped2B_x = 242.523;
				ped2B_y = -411.935;
				ped2B_z = 15.094;
			}
			else if (ped2_cord == 22)
			{
				ped2B_x = 246.695;
				ped2B_y = -542.039;
				ped2B_z = 27.099;
			}
			else if (ped2_cord == 23)
			{
				ped2B_x = 239.984;
				ped2B_y = -699.925;
				ped2B_z = 11.655;
			}
			else if (ped2_cord == 24)
			{
				ped2B_x = 268.544;
				ped2B_y = -869.917;
				ped2B_z = 11.294;
			}
			else if (ped2_cord == 25)
			{
				ped2B_x = 317.674;
				ped2B_y = -979.663;
				ped2B_z = 10.455;
			}
			else if (ped2_cord == 26)
			{
				ped2B_x = 421.182;
				ped2B_y = -1043.65;
				ped2B_z = 10.96;
			}
			else if (ped2_cord == 27)
			{
				ped2B_x = 543.56;
				ped2B_y = -1055.12;
				ped2B_z = 11.516;
			}
			else if (ped2_cord == 28)
			{
				ped2B_x = 607.464;
				ped2B_y = -994.732;
				ped2B_z = 15.699;
			}
			else if (ped2_cord == 29)
			{
				ped2B_x = 692.539;
				ped2B_y = -701.819;
				ped2B_z = 27.351;
			}
			else if (ped2_cord == 30)
			{
				ped2B_x = ped2B_x; 
				ped2B_y = ped2B_y;
				ped2B_z = ped2B_z;
				skip = 1;
				PRINT_STRING_IN_STRING_NOW("string", "RACEFA", 5000, 1);//r~You failed to win the race!
				break;
			}
			//TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 60.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
		}

//============================== соперник 3 ==============================
		GET_CHAR_COORDINATES(ped3,  &Ped3X, &Ped3Y, &Ped3Z);//вписываем координаты соперника в переменную
		GET_DISTANCE_BETWEEN_COORDS_3D( Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, &Ped3R);//проверка "игрок на координатах"
		if ( Ped3R < 10.0)
		{
			ped3_cord += 1;
			if (ped3_cord == 2)
			{
				ped3B_x = 754.35;
				ped3B_y = 1635.11;
				ped3B_z = 26.448;
			}
			else if (ped3_cord == 3)
			{
				ped3B_x = 750.778;
				ped3B_y = 1482.34;
				ped3B_z = 24.25;
			}
			else if (ped3_cord == 4)
			{
				ped3B_x = 722.354;
				ped3B_y = 1322.47;
				ped3B_z = 22.426;
			}
			else if (ped3_cord == 5)
			{
				ped3B_x = 634.599;
				ped3B_y = 1222.72;
				ped3B_z = 22.896;
			}
			else if (ped3_cord == 6)
			{
				ped3B_x = 811.602;
				ped3B_y = 1097.23;
				ped3B_z = 15.846;
			}
			else if (ped3_cord == 7)
			{
				ped3B_x = 779.553;
				ped3B_y = 978.865;
				ped3B_z = 14.168;
			}
			else if (ped3_cord == 8)
			{
				ped3B_x = 764.891;
				ped3B_y = 877.459;
				ped3B_z = 13.385;
			}
			else if (ped3_cord == 9)
			{
				ped3B_x = 770.064;
				ped3B_y = 776.41;
				ped3B_z = 19.428;
			}
			else if (ped3_cord == 10)
			{
				ped3B_x = 840.542;
				ped3B_y = 635.447;
				ped3B_z = 19.134;
			}
			else if (ped3_cord == 11)
			{
				ped3B_x = 765.597;
				ped3B_y = 520.781;
				ped3B_z = 20.134;
			}
			else if (ped3_cord == 12)
			{
				ped3B_x = 717.866;
				ped3B_y = 388.471;
				ped3B_z = 17.046;
			}
			else if (ped3_cord == 13)
			{
				ped3B_x = 658.013;
				ped3B_y = 261.482;
				ped3B_z = 14.929;
			}
			else if (ped3_cord == 14)
			{
				ped3B_x = 627.309;
				ped3B_y = 167.991;
				ped3B_z = 14.146;
			}
			else if (ped3_cord == 15)
			{
				ped3B_x = 612.89;
				ped3B_y = 32.968;
				ped3B_z = 12.304;
			}
			else if (ped3_cord == 16)
			{
				ped3B_x = 604.669;
				ped3B_y = -105.857;
				ped3B_z = 12.328;
			}
			else if (ped3_cord == 17)
			{
				ped3B_x = 582.798;
				ped3B_y = -205.283;
				ped3B_z = 11.001;
			}
			else if (ped3_cord == 18)
			{
				ped3B_x = 528.276;
				ped3B_y = -305.345;
				ped3B_z = 10.527;
			}
			else if (ped3_cord == 19)
			{
				ped3B_x = 410.301;
				ped3B_y = -336.548;
				ped3B_z = 11.142;
			}
			else if (ped3_cord == 20)
			{
				ped3B_x = 325.847;
				ped3B_y = -362.34;
				ped3B_z = 13.43;
			}
			else if (ped3_cord == 21)
			{
				ped3B_x = 242.523;
				ped3B_y = -411.935;
				ped3B_z = 15.094;
			}
			else if (ped3_cord == 22)
			{
				ped3B_x = 246.695;
				ped3B_y = -542.039;
				ped3B_z = 27.099;
			}
			else if (ped3_cord == 23)
			{
				ped3B_x = 239.984;
				ped3B_y = -699.925;
				ped3B_z = 11.655;
			}
			else if (ped3_cord == 24)
			{
				ped3B_x = 268.544;
				ped3B_y = -869.917;
				ped3B_z = 11.294;
			}
			else if (ped3_cord == 25)
			{
				ped3B_x = 317.674;
				ped3B_y = -979.663;
				ped3B_z = 10.455;
			}
			else if (ped3_cord == 26)
			{
				ped3B_x = 421.182;
				ped3B_y = -1043.65;
				ped3B_z = 10.96;
			}
			else if (ped3_cord == 27)
			{
				ped3B_x = 543.56;
				ped3B_y = -1055.12;
				ped3B_z = 11.516;
			}
			else if (ped3_cord == 28)
			{
				ped3B_x = 607.464;
				ped3B_y = -994.732;
				ped3B_z = 15.699;
			}
			else if (ped3_cord == 29)
			{
				ped3B_x = 692.539;
				ped3B_y = -701.819;
				ped3B_z = 27.351;
			}
			else if (ped3_cord == 30)
			{
				ped3B_x = ped3B_x; 
				ped3B_y = ped3B_y;
				ped3B_z = ped3B_z;
				skip = 1;
				PRINT_STRING_IN_STRING_NOW("string", "RACEFA", 5000, 1);//r~You failed to win the race!
				break;
			}
			//TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 60.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
		}
		if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
		{
			skip = 1;
			break;
		}

		//***************** позиция *****************
		GET_CHAR_COORDINATES(ped1,  &Ped1X, &Ped1Y, &Ped1Z);//вписываем координаты соперника в переменную
		GET_DISTANCE_BETWEEN_COORDS_3D( Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, &Ped1R);//проверка "игрок на координатах"
		GET_CHAR_COORDINATES(ped2,  &Ped2X, &Ped2Y, &Ped2Z);//вписываем координаты соперника в переменную
		GET_DISTANCE_BETWEEN_COORDS_3D( Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, &Ped2R);//проверка "игрок на координатах"
		GET_CHAR_COORDINATES(ped3,  &Ped3X, &Ped3Y, &Ped3Z);//вписываем координаты соперника в переменную
		GET_DISTANCE_BETWEEN_COORDS_3D( Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, &Ped3R);//проверка "игрок на координатах"
		GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
		GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, Blip_x, Blip_y, Blip_z, &PlayR);//проверка "игрок на координатах"

		if ((play_cord == ped1_cord) && (play_cord == ped2_cord) && (play_cord == ped3_cord))
		{
			if (PlayR < Ped1R) //1
			{
				if (PlayR < Ped2R) //1
				{
					if (PlayR < Ped3R) //1
					{
						poziteon = 1;
					}
					else if (PlayR > Ped3R)//0
					{
						poziteon = 2;
					}
				}
				else if (PlayR > Ped2R)//0
				{
					if (PlayR < Ped3R) //1
					{
						poziteon = 2;
					}
					else if (PlayR > Ped3R)//0
					{
						poziteon = 3;
					}
				}
			}
			else if (PlayR > Ped1R)//0
			{
				if (PlayR < Ped2R) //1
				{
					if (PlayR < Ped3R) //1
					{
						poziteon = 2;
					}
					else if (PlayR > Ped3R)//0
					{
						poziteon = 3;
					}
				}
				else if (PlayR > Ped2R)//0
				{
					if (PlayR < Ped3R) //1
					{
						poziteon = 3;
					}
					else if (PlayR > Ped3R)//0
					{
						poziteon = 4;
					}
				}
			}
		}
		else if ((play_cord == ped1_cord) && (play_cord == ped2_cord) && (play_cord > ped3_cord))
		{
			if (PlayR < Ped1R) //1
			{
				if (PlayR < Ped2R) //1
				{
					poziteon = 1;
				}
				else if (PlayR > Ped2R)//0
				{
					poziteon = 2;
				}
			}
			else if (PlayR > Ped1R) //0
			{
				if (PlayR < Ped2R) //1
				{
					poziteon = 2;
				}
				else if (PlayR > Ped2R)//0
				{
					poziteon = 3;
				}
			}
		}
		else if ((play_cord == ped1_cord) && (play_cord > ped2_cord) && (play_cord == ped3_cord))
		{
			if (PlayR < Ped1R) //1
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 1;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 2;
				}
			}
			else if (PlayR > Ped1R) //0
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 2;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 3;
				}
			}
		}
		else if ((play_cord > ped1_cord) && (play_cord == ped2_cord) && (play_cord == ped3_cord))
		{
			if (PlayR < Ped2R) //1
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 1;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 2;
				}
			}
			else if (PlayR > Ped2R) //0
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 2;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 3;
				}
			}
		}
		else if ((play_cord == ped1_cord) && (play_cord > ped2_cord) && (play_cord > ped3_cord))
		{
			if (PlayR < Ped1R) //1
			{
				poziteon = 1;
			}
			else if (PlayR > Ped1R) //0
			{
				poziteon = 2;
			}
		}
		else if ((play_cord > ped1_cord) && (play_cord == ped2_cord) && (play_cord > ped3_cord))
		{
			if (PlayR < Ped2R) //1
			{
				poziteon = 1;
			}
			else if (PlayR > Ped2R) //0
			{
				poziteon = 2;
			}
		}
		else if ((play_cord > ped1_cord) && (play_cord > ped2_cord) && (play_cord == ped3_cord))
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 1;
			}
			else if (PlayR > Ped3R) //0
			{
				poziteon = 2;
			}
		}
		else if ((play_cord > ped1_cord) && (play_cord > ped2_cord) && (play_cord > ped3_cord))
		{
			poziteon = 1;
		}
		else if ((play_cord == ped1_cord) && (play_cord == ped2_cord) && (play_cord < ped3_cord))
		{
			if (PlayR < Ped1R) //1
			{
				if (PlayR < Ped2R) //1
				{
					poziteon = 2;
				}
				else if (PlayR > Ped2R)//0
				{
					poziteon = 3;
				}
			}
			else if (PlayR > Ped1R) //0
			{
				if (PlayR < Ped2R) //1
				{
					poziteon = 3;
				}
				else if (PlayR > Ped2R)//0
				{
				poziteon = 4;
				}
			}
		}
		else if ((play_cord == ped1_cord) && (play_cord < ped2_cord) && (play_cord == ped3_cord))
		{
			if (PlayR < Ped1R) //1
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 2;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 3;
				}
			}
			else if (PlayR > Ped1R) //0
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 3;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 4;
				}
			}
		}
		else if ((play_cord < ped1_cord) && (play_cord == ped2_cord) && (play_cord == ped3_cord))
		{
			if (PlayR < Ped2R) //1
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 2;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 3;
				}
			}
			else if (PlayR > Ped2R) //0
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 3;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 4;
				}
			}
		}
		else if ((play_cord == ped1_cord) && (play_cord < ped2_cord) && (play_cord < ped3_cord))
		{
			if (PlayR < Ped1R) //1
			{
				poziteon = 3;
			}
			else if (PlayR > Ped1R) //0
			{
				poziteon = 4;
			}
		}
		else if ((play_cord < ped1_cord) && (play_cord == ped2_cord) && (play_cord < ped3_cord))
		{
			if (PlayR < Ped2R) //1
			{
				poziteon = 3;
			}
			else if (PlayR > Ped2R) //0
			{
				poziteon = 4;
			}
		}
		else if ((play_cord < ped1_cord) && (play_cord < ped2_cord) && (play_cord == ped3_cord))
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 3;
			}
			else if (PlayR > Ped3R) //0
			{
				poziteon = 4;
			}
		}
		else if ((play_cord < ped1_cord) && (play_cord < ped2_cord) && (play_cord < ped3_cord))
		{
			poziteon = 4;
		}
		//======
		else if ((play_cord > ped1_cord) && (play_cord < ped2_cord) && (play_cord == ped3_cord))
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 2;
			}
			else //0
			{
				poziteon = 3;
			}
		}
		else if ((play_cord > ped1_cord) && (play_cord == ped2_cord) && (play_cord < ped3_cord))
		{
			if (PlayR < Ped2R) //1
			{
				poziteon = 2;
			}
			else //0
			{
				poziteon = 3;
			}
		}

		else if ((play_cord < ped1_cord) && (play_cord > ped2_cord) && (play_cord == ped3_cord))
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 2;
			}
			else //0
			{
				poziteon = 3;
			}
		}
		else if ((play_cord < ped1_cord) && (play_cord == ped2_cord) && (play_cord > ped3_cord))
		{
			if (PlayR < Ped2R) //1
			{
				poziteon = 2;
			}
			else //0
			{
				poziteon = 3;
			}
		}
		else if ((play_cord > ped1_cord) && (play_cord < ped2_cord) && (play_cord < ped3_cord))
		{
			poziteon = 3;
		}
		else if ((play_cord > ped1_cord) && (play_cord > ped2_cord) && (play_cord < ped3_cord))
		{
			poziteon = 2;
		}
		else if ((play_cord > ped1_cord) && (play_cord < ped2_cord) && (play_cord > ped3_cord))
		{
			poziteon = 2;
		}

		else if ((play_cord < ped1_cord) && (play_cord > ped2_cord) && (play_cord > ped3_cord))
		{
			poziteon = 2;
		}
		else if ((play_cord < ped1_cord) && (play_cord > ped2_cord) && (play_cord < ped3_cord))
		{
			poziteon = 3;
		}
		else if ((play_cord < ped1_cord) && (play_cord > ped2_cord) && (play_cord < ped3_cord))
		{
			poziteon = 3;
		}
		
		//DRAW_SPRITE( fon, 0.8765625, 0.70045, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );
		DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );
		DRAW_SPRITE( fon, 0.8765625, 0.78381, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.

		// HUD позицыя игрока
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.73555, "NE_RACE5"); //POSITION:

		setup_draw_value();
		DISPLAY_TEXT_WITH_NUMBER(0.920052, 0.72795, "CP_TIME_NOZERO", poziteon);

		setup_draw_text();	
		if (poziteon == 1)
		{
			DISPLAY_TEXT(0.93099, 0.72916666, "ST");
		}
		else if (poziteon == 2)
		{
			DISPLAY_TEXT(0.93099, 0.72916666, "ND");
		}
		else if (poziteon == 3)
		{
			DISPLAY_TEXT(0.93099, 0.72916666, "RD");
		}
		else if (poziteon == 4)
		{
			DISPLAY_TEXT(0.93099, 0.72916666, "TH");
		}

		// HUD таймер
		if (TIMERA() > 999)
		{
			time_s += 1;
			SETTIMERA( 0 );
		}
		if (time_s > 59)
		{
			time_m += 1;
			time_s = 0;
		}



		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:

		setup_draw_value();
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", time_m);// минуты

		setup_draw_value();
		DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

		setup_draw_value();
		SET_TEXT_CENTRE(1);
		if ( time_s > 9 )
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", time_s);// секунды
		}
		else
		{
			DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_ZERO", time_s);// секунды
		}
	}

	// чистим скрипт тут
	WAIT(100);
	REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
	REMOVE_BLIP(Blip_r2);//Удаляем иконку на радаре
	REMOVE_BLIP(Blip_c1);//Удаляем иконку на радаре
	REMOVE_BLIP(Blip_c2);//Удаляем иконку на радаре
	REMOVE_BLIP(Blip_c3);//Удаляем иконку на радаре
	DELETE_CHECKPOINT(checkpoint);

	STOP_PLAYBACK_RECORDED_CAR(car1);
	STOP_PLAYBACK_RECORDED_CAR(car2);
	STOP_PLAYBACK_RECORDED_CAR(car3);
	REMOVE_CAR_RECORDING( 3066 ); // выгружаем пути транспорта
	REMOVE_CAR_RECORDING( 3067 ); // выгружаем пути транспорта
	REMOVE_CAR_RECORDING( 3068 ); // выгружаем пути транспорта

	// выгружаем из памяти модели
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины

	// выгружаем из памяти педов
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет

	// выгружаем из памяти транспорт
	MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
	MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
	MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
	MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)

	RELEASE_TEXTURE( fon );
	RELEASE_TEXTURE( timer );
	REMOVE_TXD( textur );

}
void main(void)
{
	//WAIT(5000);
	CLEAR_HELP(); // удаляем текст подсказки
	LOAD_ADDITIONAL_TEXT("RCPLNE1", 6);
	DO_SCREEN_FADE_OUT( 250 );// Затемняем экран
	while(true)
	{
		WAIT(0);
		if (IS_SCREEN_FADED_OUT())
		{
			break;
		}
	}

	SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);// Игрока игнорируют копы
	SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// Игрок бессмертный
	SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замараживаем игрока
	GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car0);//получаем автомобиль
	SET_CAR_COORDINATES_NO_OFFSET(car0, 741.176, 1785.59, 22.1314);
	SET_CAR_HEADING(car0, 180.0);
	SET_ENGINE_HEALTH(car0, 900);

	//выставляем камеру
	CREATE_CAM( 14, &camera );
	POINT_CAM_AT_COORD	( camera, 741.176, 1785.87, 22.1314 ); // куда смотрит камера
	SET_CAM_POS			( camera, 742.858, 1780.66, 25.0366 );//расположение камеры
	SET_CAM_ACTIVE( camera, 1 );
	SET_CAM_PROPAGATE( camera, 1 );
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	SET_CAM_FOV( camera, 45.0 );
	SET_WIDESCREEN_BORDERS( 1 );
	DO_SCREEN_FADE_IN( 250 );// убирается затемнение экрана

	//воспроизводим анимацию ухода в заднию чать фургона
	REQUEST_ANIMS( "ne_topfun" );//загружаем файл с анимацией
	while (!HAVE_ANIMS_LOADED( "ne_topfun" )) WAIT(0);
	SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, TRUE);
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "topfun_out", "ne_topfun", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
	SetTime(2000);
	SET_CHAR_VISIBLE(GetPlayerPed(), 0); //прозрачный игрок
	MARK_CAR_AS_NO_LONGER_NEEDED(&car0);//выгружаем из памяти фургон
	
	
	REQUEST_MODEL(CarM2);
	while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);
	rc_baron();

	DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
	while(true)
	{
		WAIT(0);
		if (IS_SCREEN_FADED_OUT())
		{
			break;
		}
	}
	CLEAR_AREA( 748.83, 1771.33, 22.1365, 10.0, 1);//очещаем зону загрузки

	//выставляем камеру на фургон
	CREATE_CAM( 14, &camera );
	POINT_CAM_AT_COORD	( camera, 741.176, 1785.87, 22.1314 ); // куда смотрит камера
	SET_CAM_POS			( camera, 742.858, 1780.66, 25.0366 );//расположение камеры
	SET_CAM_ACTIVE( camera, 1 );
	SET_CAM_PROPAGATE( camera, 1 );
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	SET_CAM_FOV( camera, 45.0 );
	SET_WIDESCREEN_BORDERS( 1 );
	WARP_CHAR_INTO_CAR(GetPlayerPed(), car5);
	DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана

	REQUEST_ANIMS( "ne_topfun" );//загружаем файл с анимацией
	while (!HAVE_ANIMS_LOADED( "ne_topfun" )) WAIT(0);
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "topfun_in", "ne_topfun", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
	SetTime(500);
	SET_CHAR_VISIBLE(GetPlayerPed(), 1); //прозрачный игрок
	SetTime(1000);
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
	MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)

	SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);// Игрока игнорируют копы
	SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// Игрок бессмертный
	SetTime(1000);

	SET_CAM_BEHIND_PED( GetPlayerPed() );
	ACTIVATE_SCRIPTED_CAMS( 0, 0 );
	END_CAM_COMMANDS( &camera );
	SET_WIDESCREEN_BORDERS( 0 );
	
	if (skip == 1)
	{
		if (!IS_BIT_SET(G_RC_1, 1))
		{
			INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
		}
		MissionFailed();
	}
	else if (skip == 2)
	{
		play_mission_complete_tune();
		MissionPassed(100, "missionpassed", "CASH");
		if (!IS_BIT_SET(G_RC_1, 1))
		{
			INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
			G_GAME_PROGRESS += 1;
			SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
			SET_BIT(&G_RC_1, 1);
		}
		if (time_s >= 10) {
			PRINT_WITH_2_NUMBERS_NOW("RCH1_9", time_m, time_s, 7000, 1);
		} else {
			PRINT_WITH_2_NUMBERS_NOW("RCH1_10", time_m, time_s, 7000, 1);
		}
		ADD_SCORE( GetPlayerIndex(), +100 );//даём игроку денег
		INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
	}
	TERMINATE_THIS_SCRIPT();
}
