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

uint CarM2 = MODEL_SPEEDO;
Car car0, car1, car2, car3, car4, car5;
Ped ped1, ped2, ped3;
Cam camera;
Texture fon, timer;
Blip Blip_r, Blip_r2, Blip_c1, Blip_c2, Blip_c3;
uint checkpoint;

float textur, skip, start, poziteon, time_m, time_s, play_lap, zone, pley_rrr;
float Blip_x2, Blip_y2, Blip_z2;
float PlayX, PlayY, PlayZ, Blip_x, Blip_y, Blip_z, PlayR, play_cord;
float Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, Ped1R, ped1_cord, ped1_lap;
float Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, Ped2R, ped2_cord, ped2_lap;
float Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, Ped3R, ped3_cord, ped3_lap;

int intro_skip = 0;		/*rebusx*/


#define KEYBOARD_ENTER			28		/*rebusx*/
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

void rc_bandit(void)
{
	if (!IS_BIT_SET(G_RC_1, 2))
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}
	skip = 0;
	start = 1;
	time_m = 0;
	time_s = 0;
	play_lap = 1;
	zone = 1;
	
	Blip_x = 1205.39;
	Blip_y = 1270.37;
	Blip_z = 11.7045;
	Blip_x2 = 1234.9;
	Blip_y2 = 1288.16;
	Blip_z2 = 10.0825;
	play_cord = 1;

	ped1B_x = 1205.39;
	ped1B_y = 1270.37;
	ped1B_z = 11.7045;
	ped1_cord = 1;

	ped2B_x = 1205.39;
	ped2B_y = 1270.37;
	ped2B_z = 11.7045;
	ped2_cord = 1;

	ped3B_x = 1205.39;
	ped3B_y = 1270.37;
	ped3B_z = 11.7045;
	ped3_cord = 1;

	textur = LOAD_TXD( "sunshine_race" );
	fon = GET_TEXTURE( textur, "fon_hud" );
	timer = GET_TEXTURE( textur, "timer_hud" );

	uint CarM1 = MODEL_DILETTANTE;// байк
	uint PedM1 = MODEL_M_Y_GALB_LO_01;// байкер 1

	REQUEST_MODEL(CarM1);
	while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
	REQUEST_MODEL(PedM1);// Мерседес
	while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало

	REQUEST_CAR_RECORDING( 3069 ); // полёт Основной
	while (!HAS_CAR_RECORDING_BEEN_LOADED( 3069 )) WAIT(0);
	REQUEST_CAR_RECORDING( 3070 ); // полёт Основной
	while (!HAS_CAR_RECORDING_BEEN_LOADED( 3070 )) WAIT(0);
	REQUEST_CAR_RECORDING( 3071 ); // полёт Основной
	while (!HAS_CAR_RECORDING_BEEN_LOADED( 3071 )) WAIT(0);

	CREATE_CAR(CarM1, 1172.924, 1245.585, 6.356184, &car4, TRUE);
	CREATE_CAR(CarM1, 1173.218, 1248.585, 6.241642, &car1, TRUE);
	CREATE_CAR(CarM1, 1173.547, 1251.001, 6.232541, &car2, TRUE);
	CREATE_CAR(CarM1, 1173.833, 1254.585, 6.270547, &car3, TRUE);
	SET_CAR_HEADING(car1, -97.0);
	SET_CAR_HEADING(car2, -97.0);
	SET_CAR_HEADING(car3, -97.0);
	SET_CAR_HEADING(car4, -97.0);

	CHANGE_CAR_COLOUR( car1, 133, 27 );//цвет машины
	CHANGE_CAR_COLOUR( car2, 89, 51 );//цвет машины
	CHANGE_CAR_COLOUR( car3, 83, 112 );//цвет машины
	CHANGE_CAR_COLOUR( car4, 112, 89 );//цвет машины

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
	START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3069, 0.0, 0.0, -0.53);
	START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 3070, 0.0, 0.0, -0.53);
	START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 3071, 0.0, 0.0, -0.53);
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
	POINT_CAM_AT_COORD	( camera, 1172.28, 1243.92, 6.35618 ); // куда смотрит камера
	SET_CAM_POS			( camera, 1178.89, 1260.78, 7.77962 );//расположение камеры
	DO_SCREEN_FADE_IN( 250 );// убирается затемнение экрана
	PRINT_STRING_IN_STRING("string", "RCR1_1", 5000, 1);//~g~Compete in a checkpoint race with 3 other RC Cars.
	SetTime_intro(5000);		/*rebusx*/
	
	if (!intro_skip)		/*rebusx*/
	{
		POINT_CAM_AT_COORD	( camera, 1235.38, 1295.301, 10.0825 ); // куда смотрит камера
		SET_CAM_POS			( camera, 1396.79, 1174.541, 66.6964 );//расположение камеры
		PRINT_STRING_IN_STRING("string", "RCR1_2", 5000, 1);//~g~Be the first to complete two laps of the track to win!
		SetTime_intro(5000);		/*rebusx*/
	}

	CLEAR_AREA( 1162.67, 1225.26, 8.77136, 5.0, 1);//очещаем зону загрузки
	
	if (!intro_skip)		/*rebusx*/
	{
		POINT_CAM_AT_COORD	( camera, 1172.33, 1249.89, 6.24164 ); // куда смотрит камера
		SET_CAM_POS			( camera, 1180.86, 1238.46, 10.4531 );//расположение камеры
		PRINT_STRING_IN_STRING("string", "RCR1_3", 5000, 1);//~g~If you wish to quit this mission press the ~h~~k~~PED_FIREWEAPON~ ~g~button to detonate your RC car.
		SetTime_intro(5000);		/*rebusx*/
	}

	CREATE_CAR(CarM2, 1162.67, 1225.26, 8.77136, &car5, TRUE);
	SET_CAR_HEADING(car5, -5);
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

	SET_FOLLOW_VEHICLE_CAM_SUBMODE(3);

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
			//пояснения текстом в низу экрана здесь
			PRINT_STRING_IN_STRING_NOW("string", "RACEFA", 5000, 1);//r~You failed to win the race!
			EXPLODE_CAR(car4, 1, 1);
			skip = 1;
			SetTime(1000);
			break;
		}
		else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1487.23, 1031.237, -6.613, 937.23, 1581.237, 50.0, 0 ))
		{
			//пояснения текстом в низу экрана здесь
			PRINT_STRING_IN_STRING_NOW("string", "RCR1_7", 5000, 1);//~r~Your RC Car went out of range!
			EXPLODE_CAR(car4, 1, 1);
			skip = 1;
			SetTime(1000);
			break;
		}
		if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1412.23, 1106.237, -5.613, 1012.23, 1506.237, 45.0, 0 )) && (zone == 1))
		{
			//текст подсказки:
			PRINT_HELP_FOREVER("RCR1_6"); //~g~Your RC Car is going out of range!
			zone = 0;
		}
		else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1412.23, 1106.237, -5.613, 1012.23, 1506.237, 45.0, 0 )) && (zone == 0))
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
			checkpoint = CREATE_CHECKPOINT( 6, Blip_x, Blip_y, (Blip_z+1.5), Blip_x2, Blip_y2, Blip_z2, 0.60000000 );
			
			ADD_BLIP_FOR_COORD(Blip_x2, Blip_y2, Blip_z2, &Blip_r2);//создаем иконку на радаре в переменной "Blip01"
			CHANGE_BLIP_SPRITE(Blip_r2, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
			CHANGE_BLIP_COLOUR(Blip_r2, 5);   //цвет иконка на радаре (0=белая)
			CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//иконка на радаре "Blip01" называние в истории карты
			CHANGE_BLIP_SCALE(Blip_r2, (0.77999990 / 1.50000000)); // масштаб иконки на радаре
			CHANGE_BLIP_ALPHA(Blip_r2, 125);
			SETTIMERB( 0 );
			pley_rrr = 1;
			start = 2;
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

		if ((TIMERB() > 500) && (pley_rrr == 1))
		{
			UNPAUSE_PLAYBACK_RECORDED_CAR(car1);
			UNPAUSE_PLAYBACK_RECORDED_CAR(car3);
			SETTIMERB( 0 );
			pley_rrr = 2;
		}
		if ((TIMERB() > 50) && (pley_rrr == 2))
		{
			UNPAUSE_PLAYBACK_RECORDED_CAR(car2);
			pley_rrr = 3;
		}

		// гонка тут
		DRAW_SPHERE(Blip_x, Blip_y, (Blip_z-4.5), 7.0);
		GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
		GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, Blip_x, Blip_y, Blip_z, &PlayR);//проверка "игрок на координатах"
		if ( PlayR < 8.5 )
		{
			play_cord += 1;
			Blip_x = Blip_x2; 
			Blip_y = Blip_y2;
			Blip_z = Blip_z2;
			PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );

			if ((play_cord == 2) || (play_cord == 26))
			{
				Blip_x2 = 1251.44;
				Blip_y2 = 1256.45;
				Blip_z2 = 9.9452;
				if (play_cord == 26)
				{
					play_lap = 2;
				}
			}
			else if ((play_cord == 3) || (play_cord == 27))
			{
				Blip_x2 = 1222.74;
				Blip_y2 = 1222.7;
				Blip_z2 = 9.73822;
			}
			else if ((play_cord == 4) || (play_cord == 28))
			{
				Blip_x2 = 1273.73;
				Blip_y2 = 1206.79;
				Blip_z2 = 8.06065;
			}
			else if ((play_cord == 5) || (play_cord == 29))
			{
				Blip_x2 = 1314.61;
				Blip_y2 = 1227.43;
				Blip_z2 = 7.53068;
			}
			else if ((play_cord == 6) || (play_cord == 30))
			{
				Blip_x2 = 1302.67;
				Blip_y2 = 1267.16;
				Blip_z2 = 14.09;
			}
			else if ((play_cord == 7) || (play_cord == 31))
			{
				Blip_x2 = 1290.41;
				Blip_y2 = 1308.23;
				Blip_z2 = 7.81097;
			}
			else if ((play_cord == 8) || (play_cord == 32))
			{
				Blip_x2 = 1312.89;
				Blip_y2 = 1337.47;
				Blip_z2 = 8.78701;
			}
			else if ((play_cord == 9) || (play_cord == 33))
			{
				Blip_x2 = 1321.08;
				Blip_y2 = 1371.53;
				Blip_z2 = 9.74834;
			}
			else if ((play_cord == 10) || (play_cord == 34))
			{
				Blip_x2 = 1307.35;
				Blip_y2 = 1399.94;
				Blip_z2 = 9.18205;
			}
			else if ((play_cord == 11) || (play_cord == 35))
			{
				Blip_x2 = 1248.8;
				Blip_y2 = 1414.5;
				Blip_z2 = 7.94941;
			}
			else if ((play_cord == 12) || (play_cord == 36))
			{
				Blip_x2 = 1241.5;
				Blip_y2 = 1384.38;
				Blip_z2 = 5.77478;
			}
			else if ((play_cord == 13) || (play_cord == 37))
			{
				Blip_x2 = 1257.74;
				Blip_y2 = 1360.11;
				Blip_z2 = 4.69158;
			}
			else if ((play_cord == 14) || (play_cord == 38))
			{
				Blip_x2 = 1228.35;
				Blip_y2 = 1354.6;
				Blip_z2 = 6.52973;
			}
			else if ((play_cord == 15) || (play_cord == 39))
			{
				Blip_x2 = 1199.22;
				Blip_y2 = 1368.07;
				Blip_z2 = 8.06161;
			}
			else if ((play_cord == 16) || (play_cord == 40))
			{
				Blip_x2 = 1183.06;
				Blip_y2 = 1415.09;
				Blip_z2 = 9.69333;
			}
			else if ((play_cord == 17) || (play_cord == 41))
			{
				Blip_x2 = 1159.08;
				Blip_y2 = 1373.02;
				Blip_z2 = 10.1963;
			}
			else if ((play_cord == 18) || (play_cord == 42))
			{
				Blip_x2 = 1189.24;
				Blip_y2 = 1325.24;
				Blip_z2 = 13.705;
			}
			else if ((play_cord == 19) || (play_cord == 43))
			{
				Blip_x2 = 1160.601;
				Blip_y2 = 1309.001;
				Blip_z2 = 7.40545;
			}
			else if ((play_cord == 20) || (play_cord == 44))
			{
				Blip_x2 = 1133.17;
				Blip_y2 = 1333.76;
				Blip_z2 = 8.59773;
			}
			else if ((play_cord == 21) || (play_cord == 45))
			{
				Blip_x2 = 1106.12;
				Blip_y2 = 1364.92;
				Blip_z2 = 10.859;
			}
			else if ((play_cord == 22) || (play_cord == 46))
			{
				Blip_x2 = 1105.15;
				Blip_y2 = 1331.63;
				Blip_z2 = 8.73177;
			}
			else if ((play_cord == 23) || (play_cord == 47))
			{
				Blip_x2 = 1125.79;
				Blip_y2 = 1294.66;
				Blip_z2 = 6.72605;
			}
			else if ((play_cord == 24) || (play_cord == 48))
			{
				Blip_x2 = 1174.04;
				Blip_y2 = 1249.25;
				Blip_z2 = 7.27924;
			}
			else if ((play_cord == 25) || (play_cord == 49))
			{
				if (play_cord == 49)
				{
					Blip_x2 = Blip_x2; 
					Blip_y2 = Blip_y2;
					Blip_z2 = Blip_z2;
				}
				else
				{
					Blip_x2 = 1205.39;
					Blip_y2 = 1270.37;
					Blip_z2 = 11.7045;
				}
			}
			else if (play_cord == 50)
			{
				skip = 2;
				break;
			}
			if (play_cord < 49)
			{
				REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
				REMOVE_BLIP(Blip_r2);//Удаляем иконку на радаре
				DELETE_CHECKPOINT(checkpoint);
				ADD_BLIP_FOR_COORD(Blip_x, Blip_y, (Blip_z + 0.1), &Blip_r);//создаем иконку на радаре в переменной "Blip01"
				CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(Blip_r, 5);   //цвет иконка на радаре (0=белая)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_RACE2");//иконка на радаре "Blip01" называние в истории карты
				CHANGE_BLIP_SCALE(Blip_r, 0.77999990); // масштаб иконки на радаре
				checkpoint = CREATE_CHECKPOINT( 6, Blip_x, Blip_y, (Blip_z+1.5), Blip_x2, Blip_y2, Blip_z2, 0.50000000 );
				if (play_cord < 48)
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
				checkpoint = CREATE_CHECKPOINT( 7, Blip_x, Blip_y, (Blip_z+1.5), Blip_x, Blip_y, Blip_z, 0.80000000 );
			}
		}
//============================== соперник 1 ==============================


		GET_CHAR_COORDINATES(ped1,  &Ped1X, &Ped1Y, &Ped1Z);//вписываем координаты соперника в переменную
		GET_DISTANCE_BETWEEN_COORDS_3D( Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, &Ped1R);//проверка "игрок на координатах"
		if ( Ped1R < 10.0)
		{
			ped1_cord += 1;
			FIX_CAR(car1);

			if ((ped1_cord == 2) || (ped1_cord == 27))
			{
				ped1B_x = 1234.9;
				ped1B_y = 1288.16;
				ped1B_z = 10.0825;
			}
			else if ((ped1_cord == 3) || (ped1_cord == 28))
			{
				ped1B_x = 1251.44;
				ped1B_y = 1256.45;
				ped1B_z = 9.9452;
			}
			else if ((ped1_cord == 4) || (ped1_cord == 29))
			{
				ped1B_x = 1222.74;
				ped1B_y = 1222.7;
				ped1B_z = 9.73822;
			}
			else if ((ped1_cord == 5) || (ped1_cord == 30))
			{
				ped1B_x = 1273.73;
				ped1B_y = 1206.79;
				ped1B_z = 8.06065;
			}
			else if ((ped1_cord == 6) || (ped1_cord == 31))
			{
				ped1B_x = 1314.61;
				ped1B_y = 1227.43;
				ped1B_z = 7.53068;
			}
			else if ((ped1_cord == 7) || (ped1_cord == 32))
			{
				ped1B_x = 1302.67;
				ped1B_y = 1267.16;
				ped1B_z = 14.09;
			}
			else if ((ped1_cord == 8) || (ped1_cord == 33))
			{
				ped1B_x = 1290.41;
				ped1B_y = 1308.23;
				ped1B_z = 7.81097;
			}
			else if ((ped1_cord == 9) || (ped1_cord == 34))
			{
				ped1B_x = 1312.89;
				ped1B_y = 1337.47;
				ped1B_z = 8.78701;
			}
			else if ((ped1_cord == 10) || (ped1_cord == 35))
			{
				ped1B_x = 1321.08;
				ped1B_y = 1371.53;
				ped1B_z = 9.74834;
			}
			else if ((ped1_cord == 11) || (ped1_cord == 36))
			{
				ped1B_x = 1307.35;
				ped1B_y = 1399.94;
				ped1B_z = 9.18205;
			}
			else if ((ped1_cord == 12) || (ped1_cord == 37))
			{
				ped1B_x = 1248.8;
				ped1B_y = 1414.5;
				ped1B_z = 7.94941;
			}
			else if ((ped1_cord == 13) || (ped1_cord == 38))
			{
				ped1B_x = 1241.5;
				ped1B_y = 1384.38;
				ped1B_z = 5.77478;
			}
			else if ((ped1_cord == 14) || (ped1_cord == 39))
			{
				ped1B_x = 1257.74;
				ped1B_y = 1360.11;
				ped1B_z = 4.69158;
			}
			else if ((ped1_cord == 15) || (ped1_cord == 40))
			{
				ped1B_x = 1228.35;
				ped1B_y = 1354.6;
				ped1B_z = 6.52973;
			}
			else if ((ped1_cord == 16) || (ped1_cord == 41))
			{
				ped1B_x = 1199.22;
				ped1B_y = 1368.07;
				ped1B_z = 8.06161;
			}
			else if ((ped1_cord == 17) || (ped1_cord == 42))
			{
				ped1B_x = 1183.06;
				ped1B_y = 1415.09;
				ped1B_z = 9.69333;
			}
			else if ((ped1_cord == 18) || (ped1_cord == 43))
			{
				ped1B_x = 1159.08;
				ped1B_y = 1373.02;
				ped1B_z = 10.1963;
			}
			else if ((ped1_cord == 19) || (ped1_cord == 44))
			{
				ped1B_x = 1189.24;
				ped1B_y = 1325.24;
				ped1B_z = 13.705;
			}
			else if ((ped1_cord == 20) || (ped1_cord == 45))
			{
				ped1B_x = 1160.601;
				ped1B_y = 1309.001;
				ped1B_z = 7.40545;
			}
			else if ((ped1_cord == 21) || (ped1_cord == 46))
			{
				ped1B_x = 1133.17;
				ped1B_y = 1333.76;
				ped1B_z = 8.59773;
			}
			else if ((ped1_cord == 22) || (ped1_cord == 47))
			{
				ped1B_x = 1106.12;
				ped1B_y = 1364.92;
				ped1B_z = 10.859;
			}
			else if ((ped1_cord == 23) || (ped1_cord == 48))
			{
				ped1B_x = 1105.15;
				ped1B_y = 1331.63;
				ped1B_z = 8.73177;
			}
			else if ((ped1_cord == 24) || (ped1_cord == 49))
			{
				ped1B_x = 1125.79;
				ped1B_y = 1294.66;
				ped1B_z = 6.72605;
			}
			else if ((ped1_cord == 25) || (ped1_cord == 50))
			{
				ped1B_x = 1174.04;
				ped1B_y = 1249.25;
				ped1B_z = 7.27924;
			}
			else if (ped1_cord == 26)
			{
				ped1B_x = 1205.39;
				ped1B_y = 1270.37;
				ped1B_z = 11.7045;
			}
			else if (ped1_cord == 51)
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
			FIX_CAR(car2);

			if ((ped2_cord == 2) || (ped2_cord == 27))
			{
				ped2B_x = 1234.9;
				ped2B_y = 1288.16;
				ped2B_z = 10.0825;
			}
			else if ((ped2_cord == 3) || (ped2_cord == 28))
			{
				ped2B_x = 1251.44;
				ped2B_y = 1256.45;
				ped2B_z = 9.9452;
			}
			else if ((ped2_cord == 4) || (ped2_cord == 29))
			{
				ped2B_x = 1222.74;
				ped2B_y = 1222.7;
				ped2B_z = 9.73822;
			}
			else if ((ped2_cord == 5) || (ped2_cord == 30))
			{
				ped2B_x = 1273.73;
				ped2B_y = 1206.79;
				ped2B_z = 8.06065;
			}
			else if ((ped2_cord == 6) || (ped2_cord == 31))
			{
				ped2B_x = 1314.61;
				ped2B_y = 1227.43;
				ped2B_z = 7.53068;
			}
			else if ((ped2_cord == 7) || (ped2_cord == 32))
			{
				ped2B_x = 1302.67;
				ped2B_y = 1267.16;
				ped2B_z = 14.09;
			}
			else if ((ped2_cord == 8) || (ped2_cord == 33))
			{
				ped2B_x = 1290.41;
				ped2B_y = 1308.23;
				ped2B_z = 7.81097;
			}
			else if ((ped2_cord == 9) || (ped2_cord == 34))
			{
				ped2B_x = 1312.89;
				ped2B_y = 1337.47;
				ped2B_z = 8.78701;
			}
			else if ((ped2_cord == 10) || (ped2_cord == 35))
			{
				ped2B_x = 1321.08;
				ped2B_y = 1371.53;
				ped2B_z = 9.74834;
			}
			else if ((ped2_cord == 11) || (ped2_cord == 36))
			{
				ped2B_x = 1307.35;
				ped2B_y = 1399.94;
				ped2B_z = 9.18205;
			}
			else if ((ped2_cord == 12) || (ped2_cord == 37))
			{
				ped2B_x = 1248.8;
				ped2B_y = 1414.5;
				ped2B_z = 7.94941;
			}
			else if ((ped2_cord == 13) || (ped2_cord == 38))
			{
				ped2B_x = 1241.5;
				ped2B_y = 1384.38;
				ped2B_z = 5.77478;
			}
			else if ((ped2_cord == 14) || (ped2_cord == 39))
			{
				ped2B_x = 1257.74;
				ped2B_y = 1360.11;
				ped2B_z = 4.69158;
			}
			else if ((ped2_cord == 15) || (ped2_cord == 40))
			{
				ped2B_x = 1228.35;
				ped2B_y = 1354.6;
				ped2B_z = 6.52973;
			}
			else if ((ped2_cord == 16) || (ped2_cord == 41))
			{
				ped2B_x = 1199.22;
				ped2B_y = 1368.07;
				ped2B_z = 8.06161;
			}
			else if ((ped2_cord == 17) || (ped2_cord == 42))
			{
				ped2B_x = 1183.06;
				ped2B_y = 1415.09;
				ped2B_z = 9.69333;
			}
			else if ((ped2_cord == 18) || (ped2_cord == 43))
			{
				ped2B_x = 1159.08;
				ped2B_y = 1373.02;
				ped2B_z = 10.1963;
			}
			else if ((ped2_cord == 19) || (ped2_cord == 44))
			{
				ped2B_x = 1189.24;
				ped2B_y = 1325.24;
				ped2B_z = 13.705;
			}
			else if ((ped2_cord == 20) || (ped2_cord == 45))
			{
				ped2B_x = 1160.601;
				ped2B_y = 1309.001;
				ped2B_z = 7.40545;
			}
			else if ((ped2_cord == 21) || (ped2_cord == 46))
			{
				ped2B_x = 1133.17;
				ped2B_y = 1333.76;
				ped2B_z = 8.59773;
			}
			else if ((ped2_cord == 22) || (ped2_cord == 47))
			{
				ped2B_x = 1106.12;
				ped2B_y = 1364.92;
				ped2B_z = 10.859;
			}
			else if ((ped2_cord == 23) || (ped2_cord == 48))
			{
				ped2B_x = 1105.15;
				ped2B_y = 1331.63;
				ped2B_z = 8.73177;
			}
			else if ((ped2_cord == 24) || (ped2_cord == 49))
			{
				ped2B_x = 1125.79;
				ped2B_y = 1294.66;
				ped2B_z = 6.72605;
			}
			else if ((ped2_cord == 25) || (ped2_cord == 50))
			{
				ped2B_x = 1174.04;
				ped2B_y = 1249.25;
				ped2B_z = 7.27924;
			}
			else if (ped2_cord == 26)
			{
				ped2B_x = 1205.39;
				ped2B_y = 1270.37;
				ped2B_z = 11.7045;
			}
			else if (ped2_cord == 51)
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
			FIX_CAR(car3);
			if ((ped3_cord == 2) || (ped3_cord == 27))
			{
				ped3B_x = 1234.9;
				ped3B_y = 1288.16;
				ped3B_z = 10.0825;
			}
			else if ((ped3_cord == 3) || (ped3_cord == 28))
			{
				ped3B_x = 1251.44;
				ped3B_y = 1256.45;
				ped3B_z = 9.9452;
			}
			else if ((ped3_cord == 4) || (ped3_cord == 29))
			{
				ped3B_x = 1222.74;
				ped3B_y = 1222.7;
				ped3B_z = 9.73822;
			}
			else if ((ped3_cord == 5) || (ped3_cord == 30))
			{
				ped3B_x = 1273.73;
				ped3B_y = 1206.79;
				ped3B_z = 8.06065;
			}
			else if ((ped3_cord == 6) || (ped3_cord == 31))
			{
				ped3B_x = 1314.61;
				ped3B_y = 1227.43;
				ped3B_z = 7.53068;
			}
			else if ((ped3_cord == 7) || (ped3_cord == 32))
			{
				ped3B_x = 1302.67;
				ped3B_y = 1267.16;
				ped3B_z = 14.09;
			}
			else if ((ped3_cord == 8) || (ped3_cord == 33))
			{
				ped3B_x = 1290.41;
				ped3B_y = 1308.23;
				ped3B_z = 7.81097;
			}
			else if ((ped3_cord == 9) || (ped3_cord == 34))
			{
				ped3B_x = 1312.89;
				ped3B_y = 1337.47;
				ped3B_z = 8.78701;
			}
			else if ((ped3_cord == 10) || (ped3_cord == 35))
			{
				ped3B_x = 1321.08;
				ped3B_y = 1371.53;
				ped3B_z = 9.74834;
			}
			else if ((ped3_cord == 11) || (ped3_cord == 36))
			{
				ped3B_x = 1307.35;
				ped3B_y = 1399.94;
				ped3B_z = 9.18205;
			}
			else if ((ped3_cord == 12) || (ped3_cord == 37))
			{
				ped3B_x = 1248.8;
				ped3B_y = 1414.5;
				ped3B_z = 7.94941;
			}
			else if ((ped3_cord == 13) || (ped3_cord == 38))
			{
				ped3B_x = 1241.5;
				ped3B_y = 1384.38;
				ped3B_z = 5.77478;
			}
			else if ((ped3_cord == 14) || (ped3_cord == 39))
			{
				ped3B_x = 1257.74;
				ped3B_y = 1360.11;
				ped3B_z = 4.69158;
			}
			else if ((ped3_cord == 15) || (ped3_cord == 40))
			{
				ped3B_x = 1228.35;
				ped3B_y = 1354.6;
				ped3B_z = 6.52973;
			}
			else if ((ped3_cord == 16) || (ped3_cord == 41))
			{
				ped3B_x = 1199.22;
				ped3B_y = 1368.07;
				ped3B_z = 8.06161;
			}
			else if ((ped3_cord == 17) || (ped3_cord == 42))
			{
				ped3B_x = 1183.06;
				ped3B_y = 1415.09;
				ped3B_z = 9.69333;
			}
			else if ((ped3_cord == 18) || (ped3_cord == 43))
			{
				ped3B_x = 1159.08;
				ped3B_y = 1373.02;
				ped3B_z = 10.1963;
			}
			else if ((ped3_cord == 19) || (ped3_cord == 44))
			{
				ped3B_x = 1189.24;
				ped3B_y = 1325.24;
				ped3B_z = 13.705;
			}
			else if ((ped3_cord == 20) || (ped3_cord == 45))
			{
				ped3B_x = 1160.601;
				ped3B_y = 1309.001;
				ped3B_z = 7.40545;
			}
			else if ((ped3_cord == 21) || (ped3_cord == 46))
			{
				ped3B_x = 1133.17;
				ped3B_y = 1333.76;
				ped3B_z = 8.59773;
			}
			else if ((ped3_cord == 22) || (ped3_cord == 47))
			{
				ped3B_x = 1106.12;
				ped3B_y = 1364.92;
				ped3B_z = 10.859;
			}
			else if ((ped3_cord == 23) || (ped3_cord == 48))
			{
				ped3B_x = 1105.15;
				ped3B_y = 1331.63;
				ped3B_z = 8.73177;
			}
			else if ((ped3_cord == 24) || (ped3_cord == 49))
			{
				ped3B_x = 1125.79;
				ped3B_y = 1294.66;
				ped3B_z = 6.72605;
			}
			else if ((ped3_cord == 25) || (ped3_cord == 50))
			{
				ped3B_x = 1174.04;
				ped3B_y = 1249.25;
				ped3B_z = 7.27924;
			}
			else if (ped3_cord == 26)
			{
				ped3B_x = 1205.39;
				ped3B_y = 1270.37;
				ped3B_z = 11.7045;
			}
			else if (ped3_cord == 51)
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

		
		DRAW_SPRITE( fon, 0.8765625, 0.70045, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );
		DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );
		DRAW_SPRITE( fon, 0.8765625, 0.78381, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.

		// HUD круг
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.69565, "RCR1_4"); //LAP:
		setup_draw_value();
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.9203125, 0.68625, "CP_TIME_NOZERO", play_lap);// 
		setup_draw_value();
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.68625, "OUTOF_NUM", 2);// 

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
	REMOVE_CAR_RECORDING( 3069 ); // выгружаем пути транспорта
	REMOVE_CAR_RECORDING( 3070 ); // выгружаем пути транспорта
	REMOVE_CAR_RECORDING( 3071 ); // выгружаем пути транспорта

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
	LOAD_ADDITIONAL_TEXT("RCRACE1", 6);
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
	SET_CAR_COORDINATES_NO_OFFSET(car0, 1162.67, 1225.26, 8.77136);
	SET_CAR_HEADING(car0, -5.0);
	SET_ENGINE_HEALTH(car0, 900);

	//выставляем камеру
	CREATE_CAM( 14, &camera );
	POINT_CAM_AT_COORD	( camera, 1162.54, 1225.101, 8.77136 ); // куда смотрит камера
	SET_CAM_POS			( camera, 1166.25, 1230.351, 10.9641 );//расположение камеры
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
	rc_bandit();

	DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
	while(true)
	{
		WAIT(0);
		if (IS_SCREEN_FADED_OUT())
		{
			break;
		}
	}

	//выставляем камеру на фургон
	CREATE_CAM( 14, &camera );
	POINT_CAM_AT_COORD	( camera, 1162.54, 1225.101, 8.77136 ); // куда смотрит камера
	SET_CAM_POS			( camera, 1166.25, 1230.351, 10.9641 );//расположение камеры
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
	CLEAR_AREA( 1226.34, 1306.24, 1.87054, 160.0, 1);//очещаем зону загрузки
	
	if (skip == 1)
	{
		if (!IS_BIT_SET(G_RC_1, 2))
		{
			INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
		}
		MissionFailed();
	}
	else if (skip == 2)
	{
		SETTIMERA(0); //сбрасываем таймер 
		play_mission_complete_tune();
		MissionPassed(100, "missionpassed", "CASH");
		if (!IS_BIT_SET(G_RC_1, 2))
		{
			INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
			G_GAME_PROGRESS += 1;
			SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
			SET_BIT(&G_RC_1, 2);
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
