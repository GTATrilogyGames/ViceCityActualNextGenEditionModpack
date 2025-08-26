/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
#include "cutscenes.h"
#include "mission_passed.h"
#include "fast_travel.h"
float PlayX, PlayY, PlayZ, PlayR, blip_on, skip, textur, text_1, text_2, time_m, time_s, sound, play, store1, store2, store3, store4, store5, del_car, autosave;
float HealG_1, HealG_2, HealG_3, HealG_4, HealG_5, HealG_6, HealG_7, HealG_8, HealG_9, HealG_10, HealG_11, HealG_12, HealG_13, HealG_14, HealG_15, HealG_16, HealG_17, HealG_18, HealG_19, HealG_20, HealG_21, HealG_22, HealG_23, HealG_24, HealG_25;
float glassON_1, glassON_2, glassON_3, glassON_4, glassON_5, glassON_6, glassON_7, glassON_8, glassON_9, glassON_10, glassON_11, glassON_12, glassON_13, glassON_14, glassON_15, glassON_16, glassON_17, glassON_18, glassON_19, glassON_20, glassON_21, glassON_22, glassON_23, glassON_24, glassON_25;
float PedX, PedY, PedZ, PedX2, PedY2, PedZ2, PedX3, PedY3, PedZ3, PedX4, PedY4, PedZ4, stalking, stalkerR, in_car, in_cord, in_cord2, in_area;
int income, load_mashin, help;

void SetSpeech(void)
{
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if (!IS_SCRIPTED_CONVERSATION_ONGOING())
		{
			break;
		}
		else if (TIMERA() > 10000)
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
void versetty(void)
{
	blip_on = 0;
	autosave = 0;
	Blip tommy_ico;	
	WAIT(3000);
	load_mashin = 0;
	help = 0;
	uint rId9;
	//SET_CHAR_COORDINATES(GetPlayerPed(), 78.808, 6.345, 6.907);// перемещаем игрока
	while(true)
	{
		WAIT(0);
		if (autosave == 1)
		{
			CLEAR_WANTED_LEVEL(GetPlayerIndex());
			autosave = 0;
			DO_AUTO_SAVE();
			WAIT(500);
		}
//============================== Shakedown ======================================
		if ((G_ONMISSION == 0) && (G_PROTECT == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(54.62, -46.09, 19.19, &tommy_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(tommy_ico, BLIP_VLAD);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(tommy_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(tommy_ico, "LG_24");//иконка на радаре называние в истории карты "Версетти"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 54.62, -46.09, 19.19, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 54.62, -46.09, 19.19, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-288.2, -487.5, 9.8, 275.0);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(tommy_ico);//Удаляем иконку на радаре
				blip_on = 0;
				
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
				CLEAR_WANTED_LEVEL(GetPlayerIndex());
				DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}
				SET_CHAR_COORDINATES(GetPlayerPed(), 53.781, -12.191, 11.362);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 0.0);
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "BUD_1", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("bud_1");
				while (!HAS_CUTSCENE_LOADED())
				{
					WAIT(0);
				}

				PRINT_BIG("BUD_1", 5000, 2);//Shakedown
				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED())
				{
					WAIT(0);
				}

				if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
				{
					DO_SCREEN_FADE_IN(0);
				}

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				Car car1;
				Cam camera;
				Pickup sweap_1;
				Texture fon, timer;
				Object glass_1, glass_2, glass_3, glass_4, glass_5, glass_6, glass_7, glass_8, glass_9, glass_10, glass_11, glass_12, glass_13, glass_14, glass_15, glass_16, glass_17, glass_18, glass_19, glass_20, glass_21, glass_22, glass_23, glass_24, glass_25, sale;
				Blip shop_1,  shop_2,  shop_3,  shop_4,  shop_5,  shop_6,  shop_7,  shop_8,  shop_9,  shop_10,  shop_11,  shop_12,  shop_13,  shop_14,  shop_15,  shop_16,  shop_17,  shop_18,  shop_19,  shop_20,  shop_21,  shop_22,  shop_23,  shop_24,  shop_25;

				skip = 0; // переменная пропуска
				text_1 = 1;
				text_2 = 0;
				time_m = 5;
				time_s = 0;
				sound = 0;
				play = 0;
				store1 = 0;
				store2 = 0;
				store3 = 0;
				store4 = 0;
				store5 = 0;
				glassON_1 = 1;
				glassON_2 = 1;
				glassON_3 = 1;
				glassON_4 = 1;
				glassON_5 = 1;
				glassON_6 = 1;
				glassON_7 = 1;
				glassON_8 = 1;
				glassON_9 = 1;
				glassON_10 = 1;
				glassON_11 = 1;
				glassON_12 = 1;
				glassON_13 = 1;
				glassON_14 = 1;
				glassON_15 = 1;
				glassON_16 = 1;
				glassON_17 = 1;
				glassON_18 = 1;
				glassON_19 = 1;
				glassON_20 = 1;
				glassON_21 = 1;
				glassON_22 = 1;
				glassON_23 = 1;
				glassON_24 = 1;
				glassON_25 = 1;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				timer = GET_TEXTURE( textur, "timer_hud" );

				uint CarM1 = MODEL_COQUETTE;// Стингер
				uint WinM1 = showcase1;
				uint WinM2 = showcase2;
				uint WinM3 = showcase3;
				uint WinM4 = showcase4;
				uint Stend = stend_prodano;

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(WinM1);
				while (!HAS_MODEL_LOADED(WinM1)) WAIT(100);
				REQUEST_MODEL(WinM2);
				while (!HAS_MODEL_LOADED(WinM2)) WAIT(100);
				REQUEST_MODEL(WinM3);
				while (!HAS_MODEL_LOADED(WinM3)) WAIT(100);
				REQUEST_MODEL(WinM4);
				while (!HAS_MODEL_LOADED(WinM4)) WAIT(100);

				REQUEST_MODEL(Stend);
				while (!HAS_MODEL_LOADED(Stend)) WAIT(100);

				// создаём машину
				CREATE_CAR(CarM1, 82.193, 7.057, 7.336, &car1, TRUE);
				CREATE_PICKUP_ROTATE(w_uzi2, 3, 60, 80.036, 3.513, 7.914, 90.0, 0.0, 140.0, &sweap_1);// даём винтовку

				CREATE_OBJECT_NO_OFFSET(Stend, 0.5, 5.3, -4.4, &sale, TRUE); // Стенд "Продаётся"

				// создаём модели
				CREATE_OBJECT_NO_OFFSET(WinM3, 900.511, 1545.366, 14.448, &glass_1, TRUE); // магазин 1 (кофейня)
				CREATE_OBJECT_NO_OFFSET(WinM3, 893.847, 1538.747, 14.448, &glass_2, TRUE); // магазин 1 (кофейня)
				SET_OBJECT_HEADING(glass_1, 45.5);
				SET_OBJECT_HEADING(glass_2, 45.2);
				CREATE_OBJECT_NO_OFFSET(WinM3, 802.939, 1747.518, 14.463, &glass_3, TRUE); // магазин 2 (книжный)
				CREATE_OBJECT_NO_OFFSET(WinM4, 802.926, 1755.694, 14.444, &glass_4, TRUE); // магазин 2 (книжный)
				SET_OBJECT_HEADING(glass_3, 90.0);
				SET_OBJECT_HEADING(glass_4, 90.3);
				CREATE_OBJECT_NO_OFFSET(WinM2, 901.191, 1746.186, 14.167, &glass_5, TRUE); // магазин 3 (ювилирный)
				CREATE_OBJECT_NO_OFFSET(WinM4, 897.018, 1741.009, 14.167, &glass_6, TRUE); // магазин 3 (ювилирный)
				CREATE_OBJECT_NO_OFFSET(WinM2, 890.577, 1731.129, 14.126, &glass_7, TRUE); // магазин 3 (ювилирный)
				SET_OBJECT_HEADING(glass_5, -46.05);
				SET_OBJECT_HEADING(glass_6, -108.1);
				SET_OBJECT_HEADING(glass_7, 0.3);
				CREATE_OBJECT_NO_OFFSET(WinM4, 801.851, 1635.484, 20.651, &glass_8, TRUE); // магазин 4 (музыкальный)
				CREATE_OBJECT_NO_OFFSET(WinM4, 799.268, 1638.122, 20.651, &glass_9, TRUE); // магазин 4 (музыкальный)
				CREATE_OBJECT_NO_OFFSET(WinM4, 796.738, 1640.753, 20.65, &glass_10, TRUE); // магазин 4 (музыкальный)
				CREATE_OBJECT_NO_OFFSET(WinM4, 794.141, 1643.391, 20.65, &glass_11, TRUE); // магазин 4 (музыкальный)
				CREATE_OBJECT_NO_OFFSET(WinM4, 789.629, 1650.107, 20.65, &glass_12, TRUE); // магазин 4 (музыкальный)
				CREATE_OBJECT_NO_OFFSET(WinM4, 789.613, 1653.774, 20.65, &glass_13, TRUE); // магазин 4 (музыкальный)
				SET_OBJECT_HEADING(glass_8, -46.0);
				SET_OBJECT_HEADING(glass_9, -46.0);
				SET_OBJECT_HEADING(glass_10, -46.0);
				SET_OBJECT_HEADING(glass_11, -46.0);
				SET_OBJECT_HEADING(glass_12, -90.6);
				SET_OBJECT_HEADING(glass_13, -90.1);
				CREATE_OBJECT_NO_OFFSET(WinM1, 858.168, 1556.489, 14.551, &glass_14, TRUE); // магазин 5 (одежда)
				CREATE_OBJECT_NO_OFFSET(WinM1, 858.186, 1568.264, 14.551, &glass_15, TRUE); // магазин 5 (одежда)
				CREATE_OBJECT_NO_OFFSET(WinM3, 854.807, 1574.084, 14.551, &glass_16, TRUE); // магазин 5 (одежда)
				CREATE_OBJECT_NO_OFFSET(WinM1, 858.188, 1556.511, 20.665, &glass_17, TRUE); // магазин 5 (одежда)
				CREATE_OBJECT_NO_OFFSET(WinM1, 858.183, 1568.259, 20.665, &glass_18, TRUE); // магазин 5 (одежда)
				CREATE_OBJECT_NO_OFFSET(WinM3, 854.814, 1574.077, 20.665, &glass_19, TRUE); // магазин 5 (одежда)
				CREATE_OBJECT_NO_OFFSET(WinM3, 839.534, 1574.117, 14.55, &glass_20, TRUE); // магазин 5 (одежда)
				CREATE_OBJECT_NO_OFFSET(WinM1, 836.148, 1568.082, 14.55, &glass_21, TRUE); // магазин 5 (одежда)
				CREATE_OBJECT_NO_OFFSET(WinM1, 836.143, 1556.341, 14.55, &glass_22, TRUE); // магазин 5 (одежда)
				CREATE_OBJECT_NO_OFFSET(WinM3, 839.554, 1574.074, 20.665, &glass_23, TRUE); // магазин 5 (одежда)
				CREATE_OBJECT_NO_OFFSET(WinM1, 836.146, 1568.055, 20.665, &glass_24, TRUE); // магазин 5 (одежда)
				CREATE_OBJECT_NO_OFFSET(WinM1, 836.176, 1556.124, 20.665, &glass_25, TRUE); // магазин 5 (одежда)
				SET_OBJECT_HEADING(glass_14, 0.0);
				SET_OBJECT_HEADING(glass_15, 0.0);
				SET_OBJECT_HEADING(glass_16, 0.0);
				SET_OBJECT_HEADING(glass_17, 0.0);
				SET_OBJECT_HEADING(glass_18, 0.0);
				SET_OBJECT_HEADING(glass_19, 0.0);
				SET_OBJECT_HEADING(glass_20, 0.0);
				SET_OBJECT_HEADING(glass_21, 0.0);
				SET_OBJECT_HEADING(glass_22, 0.0);
				SET_OBJECT_HEADING(glass_23, 0.0);
				SET_OBJECT_HEADING(glass_24, 0.0);
				SET_OBJECT_HEADING(glass_25, 0.0);

				// блипы над моделями
				ADD_BLIP_FOR_COORD(900.511, 1545.366, 14.448, &shop_1);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(893.847, 1538.747, 14.448, &shop_2);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(802.939, 1747.518, 14.463, &shop_3);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(802.926, 1755.694, 14.444, &shop_4);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(901.191, 1746.186, 14.167, &shop_5);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(897.018, 1741.009, 14.167, &shop_6);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(890.577, 1731.129, 14.126, &shop_7);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(801.851, 1635.484, 20.651, &shop_8);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(799.268, 1638.122, 20.651, &shop_9);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(796.738, 1640.753, 20.65, &shop_10);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(794.141, 1643.391, 20.65, &shop_11);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(789.629, 1650.107, 20.65, &shop_12);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(789.613, 1653.774, 20.65, &shop_13);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(858.568, 1556.089, 14.551, &shop_14);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(858.586, 1567.864, 14.551, &shop_15);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(855.307, 1574.584, 14.551, &shop_16);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(857.688, 1557.011, 20.665, &shop_17);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(857.683, 1568.759, 20.665, &shop_18);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(854.314, 1573.577, 20.665, &shop_19);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(839.034, 1574.617, 14.55, &shop_20);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(835.648, 1567.582, 14.55, &shop_21);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(835.643, 1555.241, 14.55, &shop_22);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(840.054, 1573.574, 20.665, &shop_23);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(836.646, 1568.555, 20.665, &shop_24);//создаем иконку на радаре
				ADD_BLIP_FOR_COORD(836.576, 1556.624, 20.665, &shop_25);//создаем иконку на радаре

				CHANGE_BLIP_SPRITE(shop_1, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_2, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_3, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_4, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_5, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_6, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_7, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_8, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_9, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_10, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_11, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_12, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_13, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_14, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_15, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_16, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_17, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_18, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_19, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_20, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_21, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_22, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_23, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_24, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_SPRITE(shop_25, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"

				CHANGE_BLIP_COLOUR(shop_1, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_2, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_3, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_4, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_5, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_6, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_7, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_8, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_9, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_10, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_11, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_12, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_13, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_14, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_15, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_16, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_17, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_18, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_19, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_20, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_21, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_22, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_23, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_24, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_COLOUR(shop_25, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(shop_1, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_2, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_3, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_4, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_5, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_6, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_7, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_8, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_9, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_10, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_11, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_12, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_13, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_14, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_15, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_16, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_17, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_18, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_19, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_20, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_21, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_22, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_23, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_24, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_SCALE(shop_25, 0.5); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_1, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_2, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_3, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_4, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_5, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_6, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_7, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_8, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_9, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_10, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_11, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_12, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_13, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_14, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_15, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_16, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_17, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_18, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_19, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_20, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_21, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_22, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_23, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_24, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(shop_25, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				PRINT_STRING_IN_STRING("string", "PRO1_11", 5000, 1);//~g~Get to ~y~The North Point Mall~g~ in ~y~Vice Point~g~.

				SETTIMERA( 0 );
				SETTIMERB( 0 );

				while(true)
				{
					WAIT(0);
					if ((TIMERB() > 5000) && (text_1 == 1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "PRO1_01", 5000, 1);//~g~Do a hit and run on the shop fronts and the owners will be begging for protection.
						text_1 = 2;
						SETTIMERB( 0 );
					}
					else if ((TIMERB() > 5000) && (text_1 == 2))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "PRO1_13", 5000, 1);//~g~You have five minutes to smash them all.
						text_1 = 3;
					}
					// если игрок в зоне
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 822.234, 1534.483, 12.0, 802.234, 1784.049, 23.5, 0 )) && (text_2 == 0))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "PRO1_12", 5000, 1);//~g~Smash the panes of glass in each shop front and the owners will be begging for new protection.
						text_2 = 1;
					}
					else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 891.805, 1535.523, 12.0, 871.805, 1783.485, 18.0, 0 )) && (text_2 == 0))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "PRO1_12", 5000, 1);//~g~Smash the panes of glass in each shop front and the owners will be begging for new protection.
						text_2 = 1;
					}
					else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 905.033, 1647.742, 12.0, 788.964, 1667.742, 18.0, 0 )) && (text_2 == 0))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "PRO1_12", 5000, 1);//~g~Smash the panes of glass in each shop front and the owners will be begging for new protection.
						text_2 = 1;
					}

					//============================ HUD ============================
					// таймер тут
					if (TIMERA() > 999)
					{
						time_s -= 1;
						SETTIMERA( 0 );
					}
					if (time_s < 0)
					{
						time_m -= 1;
						time_s = 59;
					}

					// таймер
					DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
					//DRAW_SPRITE( timer, 0.8765625, 0.7838, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.
					if ((time_m == 0) && (time_s < 16))
					{
						SET_TEXT_COLOUR(235, 25, 35, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
						DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:

						SET_TEXT_COLOUR(235, 25, 35, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
						SET_TEXT_CENTRE(1);
						DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", time_m);// минуты

						SET_TEXT_COLOUR(235, 25, 35, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
						DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

						SET_TEXT_COLOUR(235, 25, 35, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
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
					else
					{
						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", time_m);// минуты

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
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

					if ((sound == 0) && (time_s == 15) && (time_m == 0))
					{
						DISABLE_FRONTEND_RADIO();
						while (!(PRELOAD_STREAM("MP_COUNTDOWN")));
						PRELOAD_STREAM("MP_COUNTDOWN");  // имя берется из sounds.dat15, также можно проиграть музыку из радио
						PLAY_STREAM_FRONTEND();
						sound = 1;
					}

					// выполнение миссии
					GET_OBJECT_HEALTH(glass_1, &HealG_1);
					GET_OBJECT_HEALTH(glass_2, &HealG_2);
					GET_OBJECT_HEALTH(glass_3, &HealG_3);
					GET_OBJECT_HEALTH(glass_4, &HealG_4);
					GET_OBJECT_HEALTH(glass_5, &HealG_5);
					GET_OBJECT_HEALTH(glass_6, &HealG_6);
					GET_OBJECT_HEALTH(glass_7, &HealG_7);
					GET_OBJECT_HEALTH(glass_8, &HealG_8);
					GET_OBJECT_HEALTH(glass_9, &HealG_9);
					GET_OBJECT_HEALTH(glass_10, &HealG_10);
					GET_OBJECT_HEALTH(glass_11, &HealG_11);
					GET_OBJECT_HEALTH(glass_12, &HealG_12);
					GET_OBJECT_HEALTH(glass_13, &HealG_13);
					GET_OBJECT_HEALTH(glass_14, &HealG_14);
					GET_OBJECT_HEALTH(glass_15, &HealG_15);
					GET_OBJECT_HEALTH(glass_16, &HealG_16);
					GET_OBJECT_HEALTH(glass_17, &HealG_17);
					GET_OBJECT_HEALTH(glass_18, &HealG_18);
					GET_OBJECT_HEALTH(glass_19, &HealG_19);
					GET_OBJECT_HEALTH(glass_20, &HealG_20);
					GET_OBJECT_HEALTH(glass_21, &HealG_21);
					GET_OBJECT_HEALTH(glass_22, &HealG_22);
					GET_OBJECT_HEALTH(glass_23, &HealG_23);
					GET_OBJECT_HEALTH(glass_24, &HealG_24);
					GET_OBJECT_HEALTH(glass_25, &HealG_25);
					//DISPLAY_TEXT_WITH_NUMBER(0.9203125, 0.68787074, "CP_TIME_NOZERO", HealG_1);// 
					//DISPLAY_TEXT_WITH_NUMBER(0.9203125, 0.72787074, "CP_TIME_NOZERO", HealG_2);// 

					if ((HealG_1 < 995) && (glassON_1 == 1))
					{
						glassON_1 = 0;
						REMOVE_BLIP(shop_1);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_1, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_2 < 995) && (glassON_2 == 1))
					{
						glassON_2 = 0;
						REMOVE_BLIP(shop_2);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_2, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_3 < 995) && (glassON_3 == 1))
					{
						glassON_3 = 0;
						REMOVE_BLIP(shop_3);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_3, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_4 < 995) && (glassON_4 == 1))
					{
						glassON_4 = 0;
						REMOVE_BLIP(shop_4);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_4, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_5 < 995) && (glassON_5 == 1))
					{
						glassON_5 = 0;
						REMOVE_BLIP(shop_5);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_5, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_6 < 995) && (glassON_6 == 1))
					{
						glassON_6 = 0;
						REMOVE_BLIP(shop_6);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_6, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_7 < 995) && (glassON_7 == 1))
					{
						glassON_7 = 0;
						REMOVE_BLIP(shop_7);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_7, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_8 < 995) && (glassON_8 == 1))
					{
						glassON_8 = 0;
						REMOVE_BLIP(shop_8);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_8, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_9 < 995) && (glassON_9 == 1))
					{
						glassON_9 = 0;
						REMOVE_BLIP(shop_9);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_9, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_10 < 995) && (glassON_10 == 1))
					{
						glassON_10 = 0;
						REMOVE_BLIP(shop_10);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_10, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_11 < 995) && (glassON_11 == 1))
					{
						glassON_11 = 0;
						REMOVE_BLIP(shop_11);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_11, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_12 < 995) && (glassON_12 == 1))
					{
						glassON_12 = 0;
						REMOVE_BLIP(shop_12);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_12, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_13 < 995) && (glassON_13 == 1))
					{
						glassON_13 = 0;
						REMOVE_BLIP(shop_13);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_13, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_14 < 995) && (glassON_14 == 1))
					{
						glassON_14 = 0;
						REMOVE_BLIP(shop_14);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_14, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_15 < 995) && (glassON_15 == 1))
					{
						glassON_15 = 0;
						REMOVE_BLIP(shop_15);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_15, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_16 < 995) && (glassON_16 == 1))
					{
						glassON_16 = 0;
						REMOVE_BLIP(shop_16);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_16, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_17 < 995) && (glassON_17 == 1))
					{
						glassON_17 = 0;
						REMOVE_BLIP(shop_17);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_17, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_18 < 995) && (glassON_18 == 1))
					{
						glassON_18 = 0;
						REMOVE_BLIP(shop_18);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_18, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_19 < 995) && (glassON_19 == 1))
					{
						glassON_19 = 0;
						REMOVE_BLIP(shop_19);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_19, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_20 < 995) && (glassON_20 == 1))
					{
						glassON_20 = 0;
						REMOVE_BLIP(shop_20);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_20, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_21 < 995) && (glassON_21 == 1))
					{
						glassON_21 = 0;
						REMOVE_BLIP(shop_21);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_21, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_22 < 995) && (glassON_22 == 1))
					{
						glassON_22 = 0;
						REMOVE_BLIP(shop_22);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_22, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_23 < 995) && (glassON_23 == 1))
					{
						glassON_23 = 0;
						REMOVE_BLIP(shop_23);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_23, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_24 < 995) && (glassON_24 == 1))
					{
						glassON_24 = 0;
						REMOVE_BLIP(shop_24);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_24, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}
					if ((HealG_25 < 995) && (glassON_25 == 1))
					{
						glassON_25 = 0;
						REMOVE_BLIP(shop_25);//Удаляем иконку на радаре
						SET_OBJECT_COORDINATES(glass_25, 1.1, 1.1, -1.1);
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
					}

					if ((glassON_1 == 0) && (glassON_2 == 0) && (store1 == 0))
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_UF", "PRO1_04", 0, 0);//My livelihood, destroyed!
						START_SCRIPT_CONVERSATION(1, 1);

						store1 = 1;
						play = 2;
						SETTIMERB( 0 );
					}
					if ((glassON_3 == 0) && (glassON_4 == 0 && (store2 == 0)))
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R4_UG", "PRO1_06", 0, 0);//I pay through the ass for protection!
						START_SCRIPT_CONVERSATION(1, 1);

						store2 = 1;
						play = 3;
						SETTIMERB( 0 );
					}
					if ((glassON_5 == 0) && (glassON_6 == 0) && (glassON_7 == 0) && (store3 == 0))
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_UH", "PRO1_05", 0, 0);//Ruined...RUINED!!
						START_SCRIPT_CONVERSATION(1, 1);

						store3 = 1;
						play = 1;
						SETTIMERB( 0 );
					}
					if ((glassON_8 == 0) && (glassON_9 == 0) && (glassON_10 == 0) && (glassON_11 == 0) && (glassON_12 == 0) && (glassON_13 == 0) && (store4 == 0))
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R4_UI", "PRO1_07", 0, 0);//My beautiful window display!
						START_SCRIPT_CONVERSATION(1, 1);

						store4 = 1;
						play = 1;
						SETTIMERB( 0 );
					}
					if ((glassON_14 == 0) && (glassON_15 == 0) && (glassON_16 == 0) && (glassON_17 == 0) && (glassON_18 == 0) && (glassON_19 == 0) && (glassON_20 == 0) && (glassON_21 == 0) && (glassON_22 == 0) && (glassON_23 == 0) && (glassON_24 == 0) && (glassON_25 == 0) && (store5 == 0))
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_UJ", "PRO1_08", 0, 0);//My store. My wonderful store.
						START_SCRIPT_CONVERSATION(1, 1);

						store5 = 1;
						play = 1;
						SETTIMERB( 0 );
					}

					if ((store1 == 1) && (store2 == 1) && (store3 == 1) && (store4 == 1) && (store5 == 1) && (play == 0))
					{
						if (sound == 1)
						{
							STOP_STREAM();
							ENABLE_FRONTEND_RADIO();
							sound = 1;
						}
						SET_OBJECT_COORDINATES(sale, 917.176, 443.684, 5.438);// ставим стенд "Продаётся"

						// камера на клуб малибу
						DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
						while(true)
						{
							WAIT(0);
							if (IS_SCREEN_FADED_OUT())
							{
								break;
							}
						}
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

						// ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 921.605, 458.283, 5.438); // куда смотрит камера
						SET_CAM_POS			( camera, 942.343, 422.414, 11.814 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );
						SetTime(200);

						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
						
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "BUYP1", 5000, 1);//You can now buy property in certain areas of the map.
						SetTime(7000);

						// смена ракурса камеры
						POINT_CAM_AT_COORD	( camera, 918.438, 444.097, 7.288 ); // куда смотрит камера
						SET_CAM_POS			( camera, 914.928, 435.082, 9.139 );//расположение камеры
						
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "BUYP2", 5000, 1);//If you see a green house pickup, you can buy that property.
						SetTime(7000);
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "BUYP3", 5000, 1);//Stand inside the pickup, then press the ~h~~k~~PED_ANSWER_PHONE~~w~ button to purchase that property.
						G_SALE_NO = 1;
						SetTime(7000);

						DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
						while(true)
						{
							WAIT(0);
							if (IS_SCREEN_FADED_OUT())
							{
								break;
							}
						}

						//убираем камеру
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана

						skip = 2;// переменная пропуска
						break;
					}

					if ((play == 1) || (play == 2) || (play == 3))
					{
						if (play == 2)
						{
							if (TIMERB() > 3000)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R4_UK", "PRO1_09", 0, 0);//Vercetti. Remember the name.
									START_SCRIPT_CONVERSATION(1, 1);
									SETTIMERB( 0 );
									play = 1;
								}
							}
						}
						else if (play == 3)
						{
							if (TIMERB() > 1900)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R4_UL", "PRO1_10", 0, 0);//I run this town now. ME!
									START_SCRIPT_CONVERSATION(1, 1);
									SETTIMERB( 0 );
									play = 1;
								}
							}
						}
						else
						{
							if (TIMERB() > 3000)
							{
								play = 0;
							}
						}
					}

					// провал миссии
					if ((time_m == 0) && (time_s == 0))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NETAXI2", 5000, 1);//~r~You're out of time!
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
				}

				WAIT( 10 );

				// удаляем блипы
				REMOVE_BLIP(shop_1);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_2);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_3);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_4);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_5);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_6);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_7);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_8);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_9);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_10);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_11);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_12);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_13);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_14);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_15);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_16);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_17);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_18);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_19);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_20);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_21);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_22);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_23);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_24);//Удаляем иконку на радаре
				REMOVE_BLIP(shop_25);//Удаляем иконку на радаре

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( timer );
				REMOVE_TXD( textur );

				if (sound == 1)
				{
					STOP_STREAM();
					ENABLE_FRONTEND_RADIO();
				}

				REMOVE_PICKUP(sweap_1);// выгружаем биту

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(WinM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(WinM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(WinM3);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(WinM4);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(Stend);//выгружаем модель

				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)

				// удаляем объекты
				DELETE_OBJECT(&glass_1);
				DELETE_OBJECT(&glass_2);
				DELETE_OBJECT(&glass_3);
				DELETE_OBJECT(&glass_4);
				DELETE_OBJECT(&glass_5);
				DELETE_OBJECT(&glass_6);
				DELETE_OBJECT(&glass_7);
				DELETE_OBJECT(&glass_8);
				DELETE_OBJECT(&glass_9);
				DELETE_OBJECT(&glass_10);
				DELETE_OBJECT(&glass_11);
				DELETE_OBJECT(&glass_12);
				DELETE_OBJECT(&glass_13);
				DELETE_OBJECT(&glass_14);
				DELETE_OBJECT(&glass_15);
				DELETE_OBJECT(&glass_16);
				DELETE_OBJECT(&glass_17);
				DELETE_OBJECT(&glass_18);
				DELETE_OBJECT(&glass_19);
				DELETE_OBJECT(&glass_20);
				DELETE_OBJECT(&glass_21);
				DELETE_OBJECT(&glass_22);
				DELETE_OBJECT(&glass_23);
				DELETE_OBJECT(&glass_24);
				DELETE_OBJECT(&glass_25);
				DELETE_OBJECT(&sale);

				// выгружаем витрины
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_4);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_5);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_6);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_7);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_8);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_9);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_10);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_11);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_12);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_13);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_14);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_15);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_16);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_17);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_18);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_19);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_20);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_21);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_22);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_23);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_24);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&glass_25);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&sale);

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_BUD_1" );//Shakedown
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(2000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +2000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 2000);
					G_PROTECT = 2;
					G_SALE_NO = 1;
					autosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}

//============================== Bar Brawl ======================================
		else if ((G_ONMISSION == 0) && (G_PROTECT == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(37.15, -28.26, 13.45, &tommy_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(tommy_ico, BLIP_VLAD);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(tommy_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(tommy_ico, "LG_24");//иконка на радаре называние в истории карты "Версетти"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 37.15, -28.26, 13.45, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 37.15, -28.26, 13.45, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-288.2, -487.5, 9.8, 275.0);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(tommy_ico);//Удаляем иконку на радаре
				blip_on = 0;

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
				CLEAR_WANTED_LEVEL(GetPlayerIndex());
				DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}
				SET_CHAR_COORDINATES(GetPlayerPed(), 53.781, -12.191, 11.362);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 0.0);

				Car car1, car2, car3, car4, car5, car6, car7;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14;
				Cam camera;
				Pickup sweap_1;
				Texture fon, timer;
				Blip guard_1,  guard_2,  guard_3,  guard_4,  guard_5;

				glassON_1 = 1;
				glassON_2 = 1;
				glassON_3 = 0;
				glassON_4 = 0;
				time_m = 5;
				time_s = 0;
				sound = 0;
				play = 0;
				text_1 = 0;
				stalking = 0;
				in_car = 0;
				skip = 0;
				del_car = 0;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				timer = GET_TEXTURE( textur, "timer_hud" );

				// грузим анимации
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				uint CarM1 = MODEL_SENTINEL;// Сентинейл
				uint CarM2 = MODEL_STOCKADE;// Секюрити
				uint CarM3 = MODEL_PMP600;// Океаник
				uint CarM4 = MODEL_PCJ;// PCJ
				uint CarM5 = MODEL_TROPIC;// Катер
				uint PedM1 = MODEL_IG_EDDIELOW;// Приспешник 1
				uint PedM2 = MODEL_IG_CLARENCE;// Приспешник 2
				uint PedM3 = MODEL_M_M_SECURITYMAN;// Охрана
				uint PedM4 = MODEL_M_M_LAWYER_02;// Бизнесмен

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(10);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(10);
				REQUEST_MODEL(CarM3);
				while (!HAS_MODEL_LOADED(CarM3)) WAIT(10);
				REQUEST_MODEL(CarM4);
				while (!HAS_MODEL_LOADED(CarM4)) WAIT(10);
				REQUEST_MODEL(CarM5);
				while (!HAS_MODEL_LOADED(CarM5)) WAIT(10);

				REQUEST_MODEL(PedM1);// Приспешник 1
				while (!HAS_MODEL_LOADED(PedM1)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Приспешник 2
				while (!HAS_MODEL_LOADED(PedM2)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// Охрана
				while (!HAS_MODEL_LOADED(PedM3)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM4);// // Бизнесмен
				while (!HAS_MODEL_LOADED(PedM4)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало

				// создаём машины
				CREATE_CAR(CarM1, 82.193, 7.057, 7.336, &car1, TRUE);// Сентинейл
				CREATE_CAR(CarM2, 299.551, -787.416, 5.445, &car2, TRUE);// Секюрити 1
				CREATE_CAR(CarM2, 295.942, -787.416, 5.445, &car3, TRUE);// Секюрити 2
				CREATE_CAR(CarM3, 292.585, -787.416, 5.445, &car4, TRUE);// Океаник
				CREATE_CAR(CarM4, 289.167, -787.416, 5.445, &car5, TRUE);// PCJ 1
				CREATE_CAR(CarM4, 286.008, -787.416, 5.445, &car6, TRUE);// PCJ 2
				CREATE_CAR(CarM5, -1631.2, -1267.36, 1.845, &car7, TRUE);// Катер
				LOCK_CAR_DOORS(car2, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car3, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car4, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car5, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car6, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car7, 3); //блокируем двери автомобиля для игрока
				CHANGE_CAR_COLOUR( car4, 112, 89 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car4, 112, 112 );//цвет отрожений машины

				// создаём педов
				CREATE_CHAR (26, PedM1, 55.874, -11.151, 11.316, &ped1, TRUE);// Приспешник 1
				CREATE_CHAR (26, PedM2, 56.223, -10.328, 11.316, &ped2, TRUE);// Приспешник 2
				CREATE_CHAR (26, PedM3, 675.769, -710.662, 5.259, &ped3, TRUE);// охранник
				CREATE_CHAR (26, PedM3, 676.254, -706.601, 5.259, &ped4, TRUE);// охранник
				CREATE_CHAR (26, PedM4, 299.279, -777.202, 5.06, &ped5, TRUE);// Бизнесмен
				CREATE_CHAR (26, PedM3, 295.473, -777.146, 5.06, &ped6, TRUE);// охранник
				CREATE_CHAR (26, PedM3, 296.554, -776.231, 5.06, &ped7, TRUE);// охранник
				CREATE_CHAR (26, PedM3, 295.473, -776.236, 5.06, &ped8, TRUE);// охранник
				CREATE_CHAR (26, PedM3, 293.161, -777.121, 5.06, &ped9, TRUE);// охранник
				CREATE_CHAR (26, PedM3, 292.095, -777.121, 5.06, &ped10, TRUE);// охранник
				SET_CHAR_HEADING(ped3, -90.0);
				SET_CHAR_HEADING(ped4, -90.0);

				// создаём охранника в машине
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM3, &ped11);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car5, 1, PedM3, &ped12);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car6, 1, PedM3, &ped13);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car7, 1, PedM3, &ped14);//создаём педа за рулём автомобиля

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "BUD_2", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("bud_2");
				while (!HAS_CUTSCENE_LOADED())
				{
					WAIT(0);
				}

				PRINT_BIG("BUD_2", 5000, 2);//Bar Brawl
				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED())
				{
					WAIT(0);
				}

				if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
				{
					DO_SCREEN_FADE_IN(0);
				}

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				CREATE_PICKUP_ROTATE(w_uzi, 3, 60, 80.036, 3.513, 7.914, 90.0, 0.0, 140.0, &sweap_1);// даём винтовку

				// создаём блипы
				ADD_BLIP_FOR_CHAR(ped3, &guard_1);
				CHANGE_BLIP_SPRITE(guard_1, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(guard_1, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(guard_1, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(guard_1, "MO_TARGET");//иконка на радаре называние в истории карты ""

				ADD_BLIP_FOR_CHAR(ped4, &guard_2);
				CHANGE_BLIP_SPRITE(guard_2, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(guard_2, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(guard_2, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(guard_2, "MO_TARGET");//иконка на радаре называние в истории карты ""

				// даём оружие
				UpdateWeaponOfPed(ped1, WEAPON_MP5);
				UpdateWeaponOfPed(ped2, WEAPON_MP5);
				UpdateWeaponOfPed(ped3, WEAPON_MP5);
				UpdateWeaponOfPed(ped4, WEAPON_MP5);
				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_MP5, TRUE);

				// лояльность игроку
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 0);
				SET_CHAR_RELATIONSHIP(ped1, 5, 24);
				SET_CHAR_RELATIONSHIP(ped2, 5, 24);

				SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
				SET_CHAR_RELATIONSHIP(ped3, 5, 0);
				SET_CHAR_RELATIONSHIP(ped4, 5, 0);
				SET_SENSE_RANGE(ped3, 10.0);
				SET_SENSE_RANGE(ped4, 10.0);
				SET_CHAR_WILL_USE_COVER(ped3, 1);
				SET_CHAR_WILL_USE_COVER(ped4, 1);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)

				PRINT_STRING_IN_STRING("string", "PRO2_01", 5000, 1);//~g~Take out the guards protecting the Front Page Bar and find out who supplied them.
				// часть 1 убить двух охранников
				while (true)
				{
					WAIT( 0 );
					// Педы сталкирят за Томми
					GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					GET_CHAR_COORDINATES(ped2,  &PedX2, &PedY2, &PedZ2);//вписываем координаты игрока в переменную
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную

					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+22, PedY+22, PedZ+15, PedX-22, PedY-22, PedZ-15, 0 )) || (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX2+22, PedY2+22, PedZ2+15, PedX2-22, PedY2-22, PedZ2-15, 0 )))
					{
						if (stalking == 0)
						{
							TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
							TASK_GO_TO_CHAR( ped2, GetPlayerPed(), -1, 13.50000000 );
							stalking = 1;
						}

						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &stalkerR);//проверка "игрок на координатах"
						if ((stalkerR < 1.5) && (stalking == 1) && (in_car == 0))
						{
							stalking = 2;
							TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
							TASK_GO_STRAIGHT_TO_COORD(ped2, PedX2, PedY2, PedZ2, 4, -2);
						}
						else if ((stalkerR > 5.5) && (stalking == 2) && (in_car == 0))
						{
							stalking = 0;
						}

						if (((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 0)) || ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (in_car == 0)))
						{
							in_car = 1;
							GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car1);
							TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, -1, 0);
							TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, -1, 1);
						}
						else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
						{
							if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
							{
								in_car = 0;
								TASK_LEAVE_CAR(ped1, car1);
								TASK_LEAVE_CAR(ped2, car1);
								MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
								TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
								TASK_GO_TO_CHAR( ped2, GetPlayerPed(), -1, 13.50000000 );
								stalking = 1;
							}
						}
					}
					else
					{
						if (stalking == 1)
						{
							stalking = 0;
							TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
							TASK_GO_STRAIGHT_TO_COORD(ped2, PedX2, PedY2, PedZ2, 4, -2);
						}
					}

					if (play == 0)
					{
						if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_AA", "PRO2_11", 0, 0);//Get in the car, useless.
							START_SCRIPT_CONVERSATION(1, 1);
							SETTIMERB( 0 );
							play = 2;
						}
					}

					if (glassON_1 == 1)
					{
						if ((IS_CHAR_DEAD(ped3)) || (IS_CHAR_FATALLY_INJURED(ped3)))//если пед мёртв или фатально ранен.
						{
							REMOVE_BLIP(guard_1);//Удаляем иконку на радаре
							glassON_1 = 0;
						}
					}
					if (glassON_2 == 1)
					{
						if ((IS_CHAR_DEAD(ped4)) || (IS_CHAR_FATALLY_INJURED(ped4)))//если пед мёртв или фатально ранен.
						{
							REMOVE_BLIP(guard_2);//Удаляем иконку на радаре
							glassON_2 = 0;
						}
					}
					if ((glassON_1 == 0) && (glassON_2 == 0))//если пед мёртв или фатально ранен.
					{
						ADD_BLIP_FOR_COORD(673.481, -708.465, 5.755, &guard_1);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(guard_1, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(guard_1, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(guard_1, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(guard_1, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "PRO2_09", 5000, 1);//~g~Go and speak to the Front Page Bar Owner.
						break;
					}
					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
				}
				// часть 2 встать на чекпойнт
				if (skip == 0)
				{
					while (true)
					{
						WAIT( 0 );
						// Педы сталкирят за Томми
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(ped2,  &PedX2, &PedY2, &PedZ2);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+22, PedY+22, PedZ+15, PedX-22, PedY-22, PedZ-15, 0 )) || (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX2+22, PedY2+22, PedZ2+15, PedX2-22, PedY2-22, PedZ2-15, 0 )))
						{
							if (stalking == 0)
							{
								TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
								TASK_GO_TO_CHAR( ped2, GetPlayerPed(), -1, 13.50000000 );
								stalking = 1;
							}

							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &stalkerR);//проверка "игрок на координатах"
							if ((stalkerR < 1.5) && (stalking == 1) && (in_car == 0))
							{
								stalking = 2;
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
								TASK_GO_STRAIGHT_TO_COORD(ped2, PedX2, PedY2, PedZ2, 4, -2);
							}
							else if ((stalkerR > 5.5) && (stalking == 2) && (in_car == 0))
							{
								stalking = 0;
							}

							if (((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 0)) || ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (in_car == 0)))
							{
								in_car = 1;
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car1);
								TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, -1, 0);
								TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, -1, 1);
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
								{
									in_car = 0;
									TASK_LEAVE_CAR(ped1, car1);
									TASK_LEAVE_CAR(ped2, car1);
									MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
									TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
									TASK_GO_TO_CHAR( ped2, GetPlayerPed(), -1, 13.50000000 );
									stalking = 1;
								}
							}
						}
						else
						{
							if (stalking == 1)
							{
								stalking = 0;
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
								TASK_GO_STRAIGHT_TO_COORD(ped2, PedX2, PedY2, PedZ2, 4, -2);
							}
						}
						DRAW_CHECKPOINT( 673.481, -708.465, 5.755, 0.8, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 673.481, -708.465, 5.755, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							stalking = 2;
							TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
							TASK_GO_STRAIGHT_TO_COORD(ped2, PedX2, PedY2, PedZ2, 4, -2);

							// ставим камеру
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 669.359, -708.205, 6.048); // куда смотрит камера
							SET_CAM_POS			( camera, 679.147, -708.836, 9.235 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							// выбигает бизнесмен
							SET_CHAR_COORDINATES(ped5, 667.893, -705.689, 6.547);// перемещаем игрока
							SET_CHAR_HEADING(ped5, 175.0);
							TASK_GO_STRAIGHT_TO_COORD(ped5, 672.549, -708.319, 6.147, 3, -2);// Томми идёт в двери
							SetTime(1500);

							// диалог
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_AB", "PRO2_02", 0, 0);//Your protection needs a little more protection.
							START_SCRIPT_CONVERSATION(1, 1);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_BA", "PRO2_03", 0, 0);//Aw hell, not again! I don't need this crap!
							START_SCRIPT_CONVERSATION(1, 1);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 8900 );//Воиспроизвидение анимации на педе
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R7_BB", "PRO2_04", 0, 0);//These idiots operate out of DBP Security around the block.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_BC", "PRO2_05", 0, 0);//You guys just sort it out amongst yourselves.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_BD", "PRO2_06", 0, 0);//I'll be seeing you later.
							START_SCRIPT_CONVERSATION(1, 1);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 1300 );//Воиспроизвидение анимации на педе
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_BD_QQQ1", "PRO2_07", 0, 0);//Yeah, yeah, whatever.
							START_SCRIPT_CONVERSATION(1, 1);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 1600 );//Воиспроизвидение анимации на педе
							SetSpeech();

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "PRO2_08", 5000, 1);//~g~DBP Security will know you are on your way, go and get them before they clear out.

							// перемещаем машины
							SET_CAR_COORDINATES(car4, 780.215, -194.302, 4.878);// перемещаем игрока
							SET_CAR_HEADING(car4, -110.0);
							TURN_OFF_VEHICLE_EXTRA(car4, 9, 0);// активировать экстру
							OPEN_CAR_DOOR(car4, 5);// открываем багажник

							// перемещаем охрану
							SET_CHAR_COORDINATES(ped6, 786.732, -200.144, 4.801);// перемещаем игрока
							SET_CHAR_COORDINATES(ped7, 783.313, -198.835, 4.801);// перемещаем игрока
							SET_CHAR_COORDINATES(ped8, 775.879, -195.068, 4.801);// перемещаем игрока
							SET_CHAR_COORDINATES(ped9, 777.811, -190.993, 4.801);// перемещаем игрока
							SET_CHAR_COORDINATES(ped10, 783.75, -192.732, 4.801);// перемещаем игрока
							SET_CHAR_HEADING(ped6, -20.0);
							SET_CHAR_HEADING(ped7, -20.0);
							SET_CHAR_HEADING(ped8, -65.0);
							SET_CHAR_HEADING(ped9, -125.0);
							SET_CHAR_HEADING(ped10, -170.0);

							// даём оружие
							UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_13);
							SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_13, TRUE);

							// агрим
							SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
							SET_CHAR_RELATIONSHIP(ped6, 5, 0);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);
							SET_CHAR_RELATIONSHIP(ped8, 5, 0);
							SET_CHAR_RELATIONSHIP(ped9, 5, 0);
							SET_CHAR_RELATIONSHIP(ped10, 5, 0);
							SET_SENSE_RANGE(ped6, 20.0);
							SET_SENSE_RANGE(ped7, 20.0);
							SET_SENSE_RANGE(ped8, 20.0);
							SET_SENSE_RANGE(ped9, 20.0);
							SET_SENSE_RANGE(ped10, 20.0);
							SET_CHAR_WILL_USE_COVER(ped6, 1);
							SET_CHAR_WILL_USE_COVER(ped7, 1);
							SET_CHAR_WILL_USE_COVER(ped8, 1);
							SET_CHAR_WILL_USE_COVER(ped9, 1);
							SET_CHAR_WILL_USE_COVER(ped10, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, FALSE);

							// создаём блипы
							REMOVE_BLIP(guard_1);//Удаляем иконку на радаре

							ADD_BLIP_FOR_CHAR(ped6, &guard_1);
							ADD_BLIP_FOR_CHAR(ped7, &guard_2);
							ADD_BLIP_FOR_CHAR(ped8, &guard_3);
							ADD_BLIP_FOR_CHAR(ped9, &guard_4);
							ADD_BLIP_FOR_CHAR(ped10, &guard_5);
							CHANGE_BLIP_SPRITE(guard_1, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_SPRITE(guard_2, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_SPRITE(guard_3, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_SPRITE(guard_4, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_SPRITE(guard_5, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(guard_1, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_COLOUR(guard_2, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_COLOUR(guard_3, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_COLOUR(guard_4, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_COLOUR(guard_5, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(guard_1, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_SCALE(guard_2, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_SCALE(guard_3, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_SCALE(guard_4, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_SCALE(guard_5, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(guard_1, "MO_TARGET");//иконка на радаре называние в истории карты ""
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(guard_2, "MO_TARGET");//иконка на радаре называние в истории карты ""
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(guard_3, "MO_TARGET");//иконка на радаре называние в истории карты ""
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(guard_4, "MO_TARGET");//иконка на радаре называние в истории карты ""
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(guard_5, "MO_TARGET");//иконка на радаре называние в истории карты ""

							glassON_1 = 1;
							glassON_2 = 1;
							glassON_3 = 1;
							glassON_4 = 1;
							glassON_5 = 1;
							SETTIMERA( 0 );
							break;
						}
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// часть 3 развалить охранное агенство
				if (skip == 0)
				{
					while (true)
					{
						WAIT( 0 );
						// Педы сталкирят за Томми
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(ped2,  &PedX2, &PedY2, &PedZ2);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+22, PedY+22, PedZ+15, PedX-22, PedY-22, PedZ-15, 0 )) || (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX2+22, PedY2+22, PedZ2+15, PedX2-22, PedY2-22, PedZ2-15, 0 )))
						{
							if (stalking == 0)
							{
								TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
								TASK_GO_TO_CHAR( ped2, GetPlayerPed(), -1, 13.50000000 );
								stalking = 1;
							}

							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &stalkerR);//проверка "игрок на координатах"
							if ((stalkerR < 1.5) && (stalking == 1) && (in_car == 0))
							{
								stalking = 2;
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
								TASK_GO_STRAIGHT_TO_COORD(ped2, PedX2, PedY2, PedZ2, 4, -2);
							}
							else if ((stalkerR > 5.5) && (stalking == 2) && (in_car == 0))
							{
								stalking = 0;
							}

							if (((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 0)) || ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (in_car == 0)))
							{
								in_car = 1;
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car1);
								TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, -1, 0);
								TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, -1, 1);
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
								{
									in_car = 0;
									TASK_LEAVE_CAR(ped1, car1);
									TASK_LEAVE_CAR(ped2, car1);
									MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
									TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
									TASK_GO_TO_CHAR( ped2, GetPlayerPed(), -1, 13.50000000 );
									stalking = 1;
								}
							}
						}
						else
						{
							if (stalking == 1)
							{
								stalking = 0;
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
								TASK_GO_STRAIGHT_TO_COORD(ped2, PedX2, PedY2, PedZ2, 4, -2);
							}
						}

						//============================ HUD ============================
						if (TIMERA() > 999)
						{
							time_s -= 1;
							SETTIMERA( 0 );
						}
						if (time_s < 0)
						{
							time_m -= 1;
							time_s = 59;
						}

						// таймер
						DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
						//DRAW_SPRITE( timer, 0.8765625, 0.7838, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.
						if ((time_m == 0) && (time_s < 16))
						{
							SET_TEXT_COLOUR(235, 25, 35, 255);
							SET_TEXT_SCALE(0.156, 0.267);
							SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
							DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:

							SET_TEXT_COLOUR(235, 25, 35, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", time_m);// минуты

							SET_TEXT_COLOUR(235, 25, 35, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
							DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

							SET_TEXT_COLOUR(235, 25, 35, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
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
						else
						{
							SET_TEXT_COLOUR(95, 195, 247, 255);
							SET_TEXT_SCALE(0.156, 0.267);
							SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
							DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:

							SET_TEXT_COLOUR(95, 195, 247, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", time_m);// минуты

							SET_TEXT_COLOUR(95, 195, 247, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
							DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

							SET_TEXT_COLOUR(95, 195, 247, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
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

						if ((sound == 0) && (time_s == 15) && (time_m == 0))
						{
							DISABLE_FRONTEND_RADIO();
							while (!(PRELOAD_STREAM("MP_COUNTDOWN")));
							PRELOAD_STREAM("MP_COUNTDOWN");  // имя берется из sounds.dat15, также можно проиграть музыку из радио
							PLAY_STREAM_FRONTEND();
							sound = 1;
						}

						// если охранники унечтожены
						if (glassON_1 == 1)
						{
							if ((IS_CHAR_DEAD(ped6)) || (IS_CHAR_FATALLY_INJURED(ped6)))//если пед мёртв или фатально ранен.
							{
								REMOVE_BLIP(guard_1);//Удаляем иконку на радаре
								glassON_1 = 0;
							}
						}
						if (glassON_2 == 1)
						{
							if ((IS_CHAR_DEAD(ped7)) || (IS_CHAR_FATALLY_INJURED(ped7)))//если пед мёртв или фатально ранен.
							{
								REMOVE_BLIP(guard_2);//Удаляем иконку на радаре
								glassON_2 = 0;
							}
						}
						if (glassON_3 == 1)
						{
							if ((IS_CHAR_DEAD(ped8)) || (IS_CHAR_FATALLY_INJURED(ped8)))//если пед мёртв или фатально ранен.
							{
								REMOVE_BLIP(guard_3);//Удаляем иконку на радаре
								glassON_3 = 0;
							}
						}
						if (glassON_4 == 1)
						{
							if ((IS_CHAR_DEAD(ped9)) || (IS_CHAR_FATALLY_INJURED(ped9)))//если пед мёртв или фатально ранен.
							{
								REMOVE_BLIP(guard_4);//Удаляем иконку на радаре
								glassON_4 = 0;
							}
						}
						if (glassON_5 == 1)
						{
							if ((IS_CHAR_DEAD(ped10)) || (IS_CHAR_FATALLY_INJURED(ped10)))//если пед мёртв или фатально ранен.
							{
								REMOVE_BLIP(guard_5);//Удаляем иконку на радаре
								glassON_5 = 0;
							}
						}

						if ((glassON_1 == 0) && (glassON_2 == 0) && (glassON_3 == 0) && (glassON_4 == 0) && (glassON_5 == 0))//если пед мёртв или фатально ранен.
						{
							if (sound == 1)
							{
								STOP_STREAM();
								ENABLE_FRONTEND_RADIO();
								sound = 1;
							}
							//загрузка путей
							REQUEST_CAR_RECORDING( 3040 );
							while (!HAS_CAR_RECORDING_BEEN_LOADED( 3040 )) WAIT(0);
							REQUEST_CAR_RECORDING( 3041 );
							while (!HAS_CAR_RECORDING_BEEN_LOADED( 3041 )) WAIT(0);

							// ставим камеру
							SetTime(1000);
							CLEAR_AREA(833.638, -203.526, 3.678, 25.0, 1);//очещаем зону загрузки
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 800.342, -195.908, 6.153); // куда смотрит камера
							SET_CAM_POS			( camera, 785.148, -184.415, 8.873 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 794.107, -192.312, 2.172, 804.107, -202.312, 12.172, 0 ))
							{
								SET_CHAR_COORDINATES(GetPlayerPed(), 789.287, -191.059, 4.842);// перемещаем игрока
								SET_CHAR_HEADING(GetPlayerPed(), -90.0);
							}

							// взрыв
							ADD_EXPLOSION( 799.176, -199.83, 5.885, 0, 1.5, 1, 0, 1.00000000 );
							SetTime(500);
							ADD_EXPLOSION( 797.658, -198.399, 5.885, 0, 1.5, 1, 0, 1.00000000 );
							SetTime(500);

							// байкеру уезжают
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car5, 3040, 0.0, 0.0, 0.0);
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car6, 3041, 0.0, 0.0, 0.0);
							SetTime(4000);
							STOP_PLAYBACK_RECORDED_CAR(car5);
							STOP_PLAYBACK_RECORDED_CAR(car6);
							REMOVE_CAR_RECORDING( 3040 );
							REMOVE_CAR_RECORDING( 3041 );
							LOCK_CAR_DOORS(car4, 1); //открываем двери автомобиля для игрока
							MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель машины
							MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
							del_car = 1;

							SET_CHAR_COORDINATES(ped12, 833.196, -217.525, 4.878);// перемещаем игрока
							SET_CHAR_COORDINATES(ped13, 830.75, -216.474, 4.878);// перемещаем игрока
							SET_CHAR_HEADING(ped12, 155.0);
							SET_CHAR_HEADING(ped13, 155.0);

							SET_CHAR_RELATIONSHIP_GROUP(ped12, 18);
							SET_CHAR_RELATIONSHIP_GROUP(ped13, 18);
							SET_SENSE_RANGE(ped12, 0.01);
							SET_SENSE_RANGE(ped13, 0.01);

							SET_CHAR_COORDINATES(ped11, 739.277, -421.165, 5.515);// перемещаем игрока
							SET_CHAR_HEADING(ped11, -5.0);
							SET_CHAR_COORDINATES(ped14, 702.487, -1223.615, 1.557);// перемещаем игрока
							SET_CHAR_HEADING(ped14, 95.0);

							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped11, car3, 830.75, -216.474, 5.398, 4, 3.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped12, car5, 699.157, -1211.003, 2.984, 4, 12.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped13, car6, 699.157, -1211.003, 2.984, 4, 12.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

							SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
							SET_CHAR_RELATIONSHIP(ped11, 5, 0);
							SET_SENSE_RANGE(ped11, 2000.0);
							SET_CHAR_WILL_USE_COVER(ped11, 0);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, 1);
							TASK_COMBAT(ped11, GetPlayerPed());

							glassON_1 = 1;
							glassON_2 = 1;
							glassON_3 = 1;
							ADD_BLIP_FOR_CHAR(ped12, &guard_1);
							ADD_BLIP_FOR_CHAR(ped13, &guard_2);
							CHANGE_BLIP_SPRITE(guard_1, BLIP_DESTINATION);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_SPRITE(guard_2, BLIP_DESTINATION);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(guard_1, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_COLOUR(guard_2, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(guard_1, 0.77999990); // масштаб иконки на радаре
							CHANGE_BLIP_SCALE(guard_2, 0.77999990); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(guard_1, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(guard_2, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							// даём оружие
							UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_13);
							//UpdateWeaponOfPed(ped12, WEAPON_M4);
							//UpdateWeaponOfPed(ped13, WEAPON_M4);
							SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_13, TRUE);
							//SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_M4, TRUE);
							//SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_M4, TRUE);

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "PRO2_10", 5000, 1);//~g~Two more have made a run for it. Track them down and finish this.
							break;
						}

						if ((time_m == 0) && (time_s == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NETAXI2", 5000, 1);//~r~You're out of time!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// часть 4 догнать байкеров
				if (skip == 0)
				{
					while (true)
					{
						WAIT( 0 );
						// Педы сталкирят за Томми
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(ped2,  &PedX2, &PedY2, &PedZ2);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+22, PedY+22, PedZ+15, PedX-22, PedY-22, PedZ-15, 0 )) || (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX2+22, PedY2+22, PedZ2+15, PedX2-22, PedY2-22, PedZ2-15, 0 )))
						{
							if (stalking == 0)
							{
								TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
								TASK_GO_TO_CHAR( ped2, GetPlayerPed(), -1, 13.50000000 );
								stalking = 1;
							}

							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &stalkerR);//проверка "игрок на координатах"
							if ((stalkerR < 1.5) && (stalking == 1) && (in_car == 0))
							{
								stalking = 2;
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
								TASK_GO_STRAIGHT_TO_COORD(ped2, PedX2, PedY2, PedZ2, 4, -2);
							}
							else if ((stalkerR > 5.5) && (stalking == 2) && (in_car == 0))
							{
								stalking = 0;
							}

							if (((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 0)) || ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (in_car == 0)))
							{
								in_car = 1;
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car1);
								TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, -1, 0);
								TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, -1, 1);
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
								{
									in_car = 0;
									TASK_LEAVE_CAR(ped1, car1);
									TASK_LEAVE_CAR(ped2, car1);
									MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
									TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
									TASK_GO_TO_CHAR( ped2, GetPlayerPed(), -1, 13.50000000 );
									stalking = 1;
								}
							}
						}
						else
						{
							if (stalking == 1)
							{
								stalking = 0;
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
								TASK_GO_STRAIGHT_TO_COORD(ped2, PedX2, PedY2, PedZ2, 4, -2);
							}
						}
						//============================ HUD ============================
						if (TIMERA() > 999)
						{
							time_s -= 1;
							SETTIMERA( 0 );
						}
						if (time_s < 0)
						{
							time_m -= 1;
							time_s = 59;
						}

						// таймер
						DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
						//DRAW_SPRITE( timer, 0.8765625, 0.7838, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.
						if ((time_m == 0) && (time_s < 16))
						{
							SET_TEXT_COLOUR(235, 25, 35, 255);
							SET_TEXT_SCALE(0.156, 0.267);
							SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
							DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:

							SET_TEXT_COLOUR(235, 25, 35, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", time_m);// минуты

							SET_TEXT_COLOUR(235, 25, 35, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
							DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

							SET_TEXT_COLOUR(235, 25, 35, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);
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
						else
						{
							SET_TEXT_COLOUR(95, 195, 247, 255);
							SET_TEXT_SCALE(0.156, 0.267);
							SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
							DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:

							SET_TEXT_COLOUR(95, 195, 247, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", time_m);// минуты

							SET_TEXT_COLOUR(95, 195, 247, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
							DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

							SET_TEXT_COLOUR(95, 195, 247, 255);
							SET_TEXT_SCALE(0.26, 0.445);
							SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
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

						if ((sound == 0) && (time_s == 15) && (time_m == 0))
						{
							DISABLE_FRONTEND_RADIO();
							while (!(PRELOAD_STREAM("MP_COUNTDOWN")));
							PRELOAD_STREAM("MP_COUNTDOWN");  // имя берется из sounds.dat15, также можно проиграть музыку из радио
							PLAY_STREAM_FRONTEND();
							sound = 1;
						}

						// Бонус
						if (text_1 == 0)
						{
							if (IS_CHAR_DEAD(ped11))
							{
								text_1 = 1;
								SETTIMERC(0); //сбрасываем таймер 
							}
						}
						else if (text_1 == 1)
						{
							SET_TEXT_COLOUR(255, 159, 255, 255); // задаём цвет текста
							SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
							SET_TEXT_EDGE(1, 0, 0, 0, 255); //
							SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
							SET_TEXT_CENTRE(1); // задаём центр текста
							DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "BONUS", 1000);//BONUS $~1~
							if ( TIMERC() > 3000 )
							{
								ADD_SCORE( GetPlayerIndex(), +1000 );//даём игроку денег
								INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 1000);
								text_1 = 2;
							}
						}

						// если байкеры унечтожены
						if (glassON_1 == 1)
						{
							if ((IS_CHAR_DEAD(ped12)) || (IS_CHAR_FATALLY_INJURED(ped12)))//если пед мёртв или фатально ранен.
							{
								REMOVE_BLIP(guard_1);//Удаляем иконку на радаре
								glassON_1 = 0;
							}
						}
						if (glassON_2 == 1)
						{
							if ((IS_CHAR_DEAD(ped13)) || (IS_CHAR_FATALLY_INJURED(ped13)))//если пед мёртв или фатально ранен.
							{
								REMOVE_BLIP(guard_2);//Удаляем иконку на радаре
								glassON_2 = 0;
							}
						}
						if ((glassON_1 == 0) && (glassON_2 == 0))//если пед мёртв или фатально ранен.
						{
							skip = 2;// переменная пропуска
							break;
						}

						// если байкеры на координатах
						GET_CHAR_COORDINATES(ped12,  &PedX3, &PedY3, &PedZ3);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(ped13,  &PedX4, &PedY4, &PedZ4);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX3, PedY3, PedZ3, 699.157, -1211.003, 2.984, &in_cord);//проверка "игрок на координатах"
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX4, PedY4, PedZ4, 699.157, -1211.003, 2.984, &in_cord2);//проверка "игрок на координатах"
						if ((in_cord < 3.0) || (in_cord2 < 3.0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "TEX1_5", 5000, 1);//~r~He got away!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((time_m == 0) && (time_s == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NETAXI2", 5000, 1);//~r~You're out of time!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
					}
				}

				// зачищаем скрипт
				WAIT(10);
				REMOVE_BLIP(guard_1);//Удаляем иконку на радаре
				REMOVE_BLIP(guard_2);//Удаляем иконку на радаре
				REMOVE_BLIP(guard_3);//Удаляем иконку на радаре
				REMOVE_BLIP(guard_4);//Удаляем иконку на радаре
				REMOVE_BLIP(guard_5);//Удаляем иконку на радаре

				REMOVE_PICKUP(sweap_1);// выгружаем биту

				if (sound == 1)
				{
					STOP_STREAM();
					ENABLE_FRONTEND_RADIO();
				}
				if (del_car == 0)
				{
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель машины
					MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
				}

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( timer );
				REMOVE_TXD( textur );

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM5);//выгружаем модель машины

				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель педа

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped9);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped10);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped11);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped12);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped13);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped14);//выгружаем модель педа(в последствии пед изчезнет

				// выгружаем из памяти транспорт
				if (car1 != 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				}
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car7);//выгружаем модель машины(в последствии машина изчезнет)

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_BUD_2" );//Bar Brawl
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(4000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +4000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 4000);
					G_PROTECT = 3;
					autosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}
//============================== Cop Land ======================================
		else if ((G_ONMISSION == 0) && (G_PROTECT == 3))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(86.074, -8.91, 11.05, &tommy_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(tommy_ico, BLIP_VLAD);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(tommy_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(tommy_ico, "LG_24");//иконка на радаре называние в истории карты "Версетти"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 86.074, -8.91, 11.05, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 86.074, -8.91, 11.05, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-288.2, -487.5, 9.8, 275.0);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(tommy_ico);//Удаляем иконку на радаре
				blip_on = 0;

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
				CLEAR_WANTED_LEVEL(GetPlayerIndex());
				DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}
				SET_CHAR_COORDINATES(GetPlayerPed(), 78.808, 6.345, 6.907);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 0.0);
				uint outfit = GET_CHAR_DRAWABLE_VARIATION(GetPlayerPed(), 1);
				ALTER_WANTED_LEVEL(GetPlayerIndex(), 0);
				APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				RELEASE_WEATHER();

				Car car1, car2, car3, car4;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16;
				Object tnt_1;
				Cam camera;
				Texture fon, timer;

				in_cord = 0;
				in_cord2 = 0;
				skip = 0;
				play = 0;
				stalking = 0;
				in_car = 0;
				in_area = 1;
				text_1 = 0;
				text_2 = 0;
				glassON_1 = 0;

				uint CarM1 = MODEL_SENTINEL;// Сентинейл
				uint CarM2 = MODEL_POLICE;// Копкар
				uint PedM1 = MODEL_IG_LILJACOB;// Ланс
				uint PedM2 = MODEL_M_Y_COP;// Коп
				uint PedM3 = MODEL_M_M_GBIK_LO_03;// Вояка
				uint dynamite_1 = dynamite;// динамит

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(10);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(10);

				REQUEST_MODEL(PedM1);// Ланс
				while (!HAS_MODEL_LOADED(PedM1)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Коп
				while (!HAS_MODEL_LOADED(PedM2)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// Вояка
				while (!HAS_MODEL_LOADED(PedM3)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(dynamite_1);// динамит
				while (!HAS_MODEL_LOADED(dynamite_1)) WAIT(0);

				// создаём машины
				CREATE_CAR(CarM1, 82.193, 7.057, 7.336, &car1, TRUE);// Сентинейл
				CREATE_CAR(CarM2, 299.551, -779.725, 5.445, &car3, TRUE);// Копкар 1
				CREATE_CAR(CarM2, 295.942, -779.725, 5.445, &car4, TRUE);// Копкар 2
				LOCK_CAR_DOORS(car3, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car4, 3); //блокируем двери автомобиля для игрока

				// создаём педов
				CREATE_CHAR (26, PedM1, 78.119, 5.207, 6.907, &ped1, TRUE);// Ланс
				CREATE_CHAR (26, PedM2, 300.219, -777.202, 5.06, &ped2, TRUE);// Коп 1
				CREATE_CHAR (26, PedM2, 299.042, -777.202, 5.06, &ped3, TRUE);// Коп 2
				CREATE_CHAR (26, PedM2, 296.626, -777.186, 5.06, &ped4, TRUE);// Коп 3
				CREATE_CHAR (26, PedM2, 295.473, -777.186, 5.06, &ped5, TRUE);// Коп 4
				CREATE_CHAR (26, PedM2, 293.161, -777.186, 5.06, &ped6, TRUE);// Коп 5
				CREATE_CHAR (26, PedM2, 292.095, -777.186, 5.06, &ped7, TRUE);// Коп 6
				CREATE_CHAR (26, PedM2, 289.762, -777.186, 5.06, &ped8, TRUE);// Коп 7
				CREATE_CHAR (26, PedM2, 288.738, -777.186, 5.06, &ped9, TRUE);// Коп 8
				CREATE_CHAR (26, PedM2, 286.533, -777.186, 5.06, &ped10, TRUE);// Коп 9
				CREATE_CHAR (26, PedM3, 285.552, -777.186, 5.06, &ped11, TRUE);// Вояка 1
				CREATE_CHAR (26, PedM3, 283.397, -777.186, 5.06, &ped12, TRUE);// Вояка 2
				CREATE_CHAR (26, PedM2, 300.081, -785.033, 5.06, &ped13, TRUE);// Коп 10
				CREATE_CHAR (26, PedM2, 299.098, -785.033, 5.06, &ped14, TRUE);// Коп 11
				CREATE_CHAR (26, PedM2, 300.081, -784.317, 5.06, &ped15, TRUE);// Коп 12
				CREATE_CHAR (26, PedM2, 299.098, -784.317, 5.06, &ped16, TRUE);// Коп 13
				CREATE_OBJECT_NO_OFFSET(dynamite_1, 875.146, 864.587, 5.441, &tnt_1, TRUE);


				// лояльность игроку
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 18);
				SET_CHAR_RELATIONSHIP(ped1, 5, 24);
				SET_SENSE_RANGE(ped1, 0.01);
				
				//Lance's Weapon
				UpdateWeaponOfPed(ped1, WEAPON_EPISODIC_11);
				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_EPISODIC_11, TRUE);				

				SET_CHAR_RELATIONSHIP_GROUP(ped2, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped4, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped5, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped6, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped7, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped8, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped9, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped10, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped11, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped12, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped13, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped14, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped15, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped16, 3);
				SET_CHAR_RELATIONSHIP(ped2, 3, 0);
				SET_CHAR_RELATIONSHIP(ped3, 3, 0);
				SET_SENSE_RANGE(ped2, 0.01);
				SET_SENSE_RANGE(ped3, 0.01);

				FORCE_WEATHER_NOW(WEATHER_SUNNY);
				RELEASE_WEATHER();
				FORWARD_TO_TIME_OF_DAY(6, 40);//устанавливаем время

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "BUD_3", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("bud_3");
				while (!HAS_CUTSCENE_LOADED())
				{
					WAIT(0);
				}

				PRINT_BIG("BUD_3", 5000, 2);//Cop Land
				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED())
				{
					WAIT(0);
				}

				if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
				{
					DO_SCREEN_FADE_IN(0);
				}
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				// создаём блип
				ADD_BLIP_FOR_COORD(890.653, 866.188, 6.196, &tommy_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(tommy_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(tommy_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(tommy_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(tommy_ico, "NE_POINT");//иконка на радаре называние в истории карты ""

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				SetTime(1500);

				// настройки "Свой-чужой" тут
				int dm, cdm;
				LOAD_CHAR_DECISION_MAKER(2, &dm);
				LOAD_COMBAT_DECISION_MAKER(3, &cdm);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);
				SET_CHAR_DECISION_MAKER(ped1, dm);
				SET_COMBAT_DECISION_MAKER(ped1, cdm);

				// часть 1 заехать в гараж
				while (true)
				{
					WAIT( 0 );
					if (play == 0)
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R7_BE", "PRO3_01", 0, 0);//Ok Lance, let's get the cops' attention!
						START_SCRIPT_CONVERSATION(1, 1);
						play = 1;
						SETTIMERB(0); //сбрасываем таймер 
					}
					else if (play == 1)
					{
						if ( TIMERB() > 3000 )
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "PRO3_21", 5000, 1);//~g~Get a wanted level so the cops will follow you into the lock-up.
							play = 2;
						}
					}

					if (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0)) //проверка розыска.
					{
						if (play == 2)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R7_BF", "PRO3_19", 0, 0);//Now that got them really irritated.
							START_SCRIPT_CONVERSATION(1, 1);
							play = 3;
							SETTIMERB(0); //сбрасываем таймер 
						}
						if (play == 3)
						{
							if ( TIMERB() > 4000 )
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "PRO3_20", 5000, 1);//~g~ Get two cops to follow you into the garage.
								play = 4;
							}
						}
						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 898.789, 858.731, 4.942, 881.807, 873.933, 9.942, 0 ))// если игрок в гараже
						{
							if ((IS_COP_PED_IN_AREA_3D_NO_SAVE(898.957, 861.261, 2.278, 880.936, 879.198, 12.278)) && (in_area == 1))
							{
								ALTER_WANTED_LEVEL(GetPlayerIndex(), 0);
								APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
								REMOVE_BLIP(tommy_ico);//Удаляем иконку на радаре
								CLEAR_AREA_OF_COPS(890.582, 877.8, 6.007, 15.0);

								// ставим камеру тут
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, 890.611, 867.155, 6.168); // куда смотрит камера
								SET_CAM_POS			( camera, 890.255, 889.411, 12.111 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );

								// заманиваем копов
								SET_CHAR_COORDINATES(ped2, 898.344, 878.841, 6.103);// перемещаем игрока
								SET_CHAR_COORDINATES(ped3, 884.498, 879.491, 6.007);// перемещаем игрока
								SET_CHAR_HEADING(ped2, 140.0);
								SET_CHAR_HEADING(ped3, -140.0);
								TASK_GO_STRAIGHT_TO_COORD(ped2, 889.717, 867.155, 6.007, 3, -2);// Коп2 бежит в гараж
								TASK_GO_STRAIGHT_TO_COORD(ped3, 889.717, 867.155, 6.007, 3, -2);// Коп1 бежит в гараж
								SetTime(2500);
								CLOSE_GARAGE("cop_g");// закрываем гараж
								CLEAR_AREA(889.621, 864.587, 6.007, 15.0, 1);//очещаем зону загрузки
								SetTime(3300);
								SET_CHAR_COORDINATES(ped2, 88.344, 88.841, 6.103);// перемещаем игрока
								SET_CHAR_COORDINATES(ped3, 84.498, 89.491, 6.007);// перемещаем игрока

								if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
								{
									SET_CHAR_COORDINATES(GetPlayerPed(), 886.124, 864.587, 6.007);// перемещаем игрока
									WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 893.162, 864.587, 6.007);//телепартируем из транспорта
								}
								else
								{
									SET_CHAR_COORDINATES(GetPlayerPed(), 893.162, 864.587, 6.007);// перемещаем игрока
									SET_CHAR_HEADING(GetPlayerPed(), 0.0);
								}
								
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
								{
									WARP_CHAR_FROM_CAR_TO_COORD(ped1, 58.191, 34.033, 5.84);//телепартируем из транспорта
								}
								else
								{
									SET_CHAR_COORDINATES(ped1, 98.344, 78.841, 6.103);// перемещаем игрока
								}

								if (car1 != 0)
								{
									MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
								}
								// меняем шкурку Ленсу и игроку
								MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
								uint PedM1 = MODEL_IG_LILJACOBW;// Ланс
								REQUEST_MODEL(PedM1);// Ланс
								while (!HAS_MODEL_LOADED(PedM1)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
								CREATE_CHAR (26, PedM1, 894.286, 864.587, 6.007, &ped1, TRUE);// Ланс
								SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 5, 0);
								SET_CHAR_COMPONENT_VARIATION(ped1, 1, 1, 0);
								SET_CHAR_DECISION_MAKER(ped1, dm);
								SET_COMBAT_DECISION_MAKER(ped1, cdm);
								
								CREATE_CAR(CarM2, 902.467, 868.767, 6.196, &car2, TRUE);// Копкар
								MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
								SET_OBJECT_COORDINATES(tnt_1, 901.374, 1537.375, 14.161);

								// лояльность игроку
								SET_CHAR_RELATIONSHIP_GROUP(ped1, 18);
								SET_CHAR_RELATIONSHIP(ped1, 5, 24);
								SET_SENSE_RANGE(ped1, 0.01);

								// расставляем копкары
								SET_CAR_COORDINATES(car3, 986.469, 1301.759, 5.539);// перемещаем автомобиль
								SET_CAR_COORDINATES(car4, 978.964, 1302.669, 5.539);// перемещаем автомобиль
								SET_CAR_HEADING(car3, -100.0);
								SET_CAR_HEADING(car4, 85.0);

								// расставляем копов
								SET_CHAR_COORDINATES(ped4, 813.562, 1526.806, 12.579);// перемещаем игрока
								SET_CHAR_COORDINATES(ped5, 884.224, 1527.792, 12.579);// перемещаем игрока
								SET_CHAR_COORDINATES(ped6, 781.951, 1655.757, 12.579);// перемещаем игрока
								SET_CHAR_COORDINATES(ped7, 912.132, 1658.914, 12.579);// перемещаем игрока
								SET_CHAR_COORDINATES(ped8, 881.051, 1790.347, 12.579);// перемещаем игрока
								SET_CHAR_COORDINATES(ped9, 810.407, 1790.641, 12.579);// перемещаем игрока
								SET_CHAR_COORDINATES(ped10, 797.297, 1741.683, 19.429);// перемещаем игрока
								SET_CHAR_COORDINATES(ped11, 897.536, 1543.841, 15.125);// перемещаем игрока
								SET_CHAR_COORDINATES(ped12, 895.744, 1541.958, 15.125);// перемещаем игрока
								SET_CHAR_COORDINATES(ped13, 987.781, 1302.982, 5.153);// перемещаем игрока
								SET_CHAR_COORDINATES(ped14, 984.776, 1303.433, 5.153);// перемещаем игрока
								SET_CHAR_COORDINATES(ped15, 980.882, 1303.824, 5.153);// перемещаем игрока
								SET_CHAR_COORDINATES(ped16, 977.471, 1304.206, 5.153);// перемещаем игрока
								SET_CHAR_HEADING(ped4, 180.0);
								SET_CHAR_HEADING(ped5, 180.0);
								SET_CHAR_HEADING(ped6, 90.0);
								SET_CHAR_HEADING(ped7, -90.0);
								SET_CHAR_HEADING(ped10, 90.0);
								SET_CHAR_HEADING(ped11, 45.0);
								SET_CHAR_HEADING(ped12, 45.0);
								SET_CHAR_HEADING(ped13, 170.0);
								SET_CHAR_HEADING(ped14, 175.0);
								SET_CHAR_HEADING(ped15, 165.0);
								SET_CHAR_HEADING(ped16, 175.0);

								// даём оружие
								//UpdateWeaponOfPed(ped1, WEAPON_PISTOL);
								UpdateWeaponOfPed(ped4, WEAPON_PISTOL);
								UpdateWeaponOfPed(ped5, WEAPON_PISTOL);
								UpdateWeaponOfPed(ped6, WEAPON_PISTOL);
								UpdateWeaponOfPed(ped7, WEAPON_PISTOL);
								UpdateWeaponOfPed(ped8, WEAPON_PISTOL);
								UpdateWeaponOfPed(ped9, WEAPON_PISTOL);
								UpdateWeaponOfPed(ped10, WEAPON_PISTOL);
								UpdateWeaponOfPed(ped11, WEAPON_M4);
								UpdateWeaponOfPed(ped12, WEAPON_M4);
								UpdateWeaponOfPed(ped13, WEAPON_PISTOL);
								UpdateWeaponOfPed(ped14, WEAPON_PISTOL);
								UpdateWeaponOfPed(ped15, WEAPON_PISTOL);
								UpdateWeaponOfPed(ped16, WEAPON_PISTOL);
								SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_M4, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_M4, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_PISTOL, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_PISTOL, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_PISTOL, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_PISTOL, TRUE);

								// создаём блип
								ADD_BLIP_FOR_COORD(901.317, 1538.974, 13.028, &tommy_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(tommy_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tommy_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(tommy_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tommy_ico, "NE_POINT");//иконка на радаре называние в истории карты ""

								// воспроизводим айдио диалог в гараже тут
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R7_CA", "PRO3_09", 0, 0);//Tie 'em up and gag 'em!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R7_CB", "PRO3_10", 0, 0);//Ooo. Fits perfectly!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R7_CC", "PRO3_11", 0, 0);//Bit tight around the crotch though...
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R7_CD", "PRO3_12", 0, 0);//Oh yeah yeah, mine too. Mine too.
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								//убираем камеру
								OPEN_GARAGE("cop_g");
								SetTime(1000);
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								END_CAM_COMMANDS( &camera );
								SET_WIDESCREEN_BORDERS( 0 );
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
								SetTime(1000);

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "PRO3_02", 5000, 1);//~g~ Take a cop car and go and plant the bomb at the Tarbrush Coffee Shop in the Mall.
								SET_MAX_WANTED_LEVEL(0);

								play = 0;
								in_cord = 0;
								in_cord2 = 0;
								stalking = 0;
								in_car = 0;
								break;
							}
						}
					}
					// Ленс сталкирит за Томми
					GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+22, PedY+22, PedZ+15, PedX-22, PedY-22, PedZ-15, 0 ))
					{
						if (stalking == 0)
						{
							TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
							stalking = 1;
							in_area = 1;
						}

						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &stalkerR);//проверка "игрок на координатах"
						if ((stalkerR < 1.5) && (stalking == 1) && (in_car == 0))
						{
							stalking = 2;
							TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
						}
						else if ((stalkerR > 5.5) && (stalking == 2) && (in_car == 0))
						{
							stalking = 0;
						}

						if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 0))
						{
							in_car = 1;
							in_area = 1;
							GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car1);
							TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, -1, 0);
							SETTIMERB( 0 );
						}
						else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
						{
							if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
							{
								in_car = 0;
								TASK_LEAVE_CAR(ped1, car1);
								MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
								TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
								stalking = 1;
							}
						}
						else if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 1) && (TIMERB() > 15000))
						{
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car1, 0);
						}
					}
					else
					{
						if (stalking == 1)
						{
							stalking = 0;
							in_area = 0;
							TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_23", 5000, 1);//~g~You've left Lance behind! Go and get him!
						}
					}

					// Открываем гараж
					if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 947.716, 840.652, 3.0, 847.716, 910.652, 18.0, 0 ))
					{
						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 925.846, 860.491, 3.0, 867.553, 900.411, 18.0, 0 ))
						{
							if (in_cord2 == 0)
							{
								OPEN_GARAGE("cop_g");
								in_cord2 = 1;
							}
							if (IS_GARAGE_CLOSED("cop_g"))
							{
								in_cord2 = 0;
							}
						}
						else
						{
							if (in_cord2 == 1)
							{
								in_cord2 = 0;
							}
						}
						if (in_cord == 0)
						{
							CREATE_CAR(CarM2, 902.467, 868.767, 6.196, &car2, TRUE);// Копкар
							MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
							in_cord = 1;
						}
					}
					else
					{
						if (in_cord == 1)
						{
							in_cord = 0;
						}
					}
					// условия провала миссии
					if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
						skip = 1;
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
				}

				// часть 2 на координатах кафе
				if (skip == 0)
				{
					while (true)
					{
						WAIT( 0 );
						// Ленс сталкирит за Томми
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+22, PedY+22, PedZ+15, PedX-22, PedY-22, PedZ-15, 0 ))
						{
							if (stalking == 0)
							{
								TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
								stalking = 1;
								in_area = 1;
							}

							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &stalkerR);//проверка "игрок на координатах"
							if ((stalkerR < 1.5) && (stalking == 1) && (in_car == 0))
							{
								stalking = 2;
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
							}
							else if ((stalkerR > 5.5) && (stalking == 2) && (in_car == 0))
							{
								stalking = 0;
							}

							if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 0))
							{
								in_car = 1;
								in_area = 1;
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car1);
								TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, -1, 0);
								SETTIMERB( 0 );
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
								{
									in_car = 0;
									TASK_LEAVE_CAR(ped1, car1);
									MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
									TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
									stalking = 1;
								}
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 1) && (TIMERB() > 15000))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car1, 0);
							}
						}
						else
						{
							if (stalking == 1)
							{
								stalking = 0;
								in_area = 0;
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GEN3_23", 5000, 1);//~g~You've left Lance behind! Go and get him!
							}
						}
						// отключаем трафик
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1073.344, 1130.861, -10.0, 593.344, 1880.861, 40.0, 0 )) && ( glassON_1 == 0))
						{
							glassON_1 = 1;
							SET_CAR_DENSITY_MULTIPLIER(0);// отключаем пути
						}
						else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1073.344, 1130.861, -10.0, 593.344, 1880.861, 40.0, 0 )) && ( glassON_1 == 1))
						{
							glassON_1 = 0;
							SET_CAR_DENSITY_MULTIPLIER(1);// включаем пути
						}
						// триггер "Копы так не ездят" тут
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1000.075, 1302.42, 3.094, 965.075, 1317.42, 13.094, 0 )) && (play == 0))
						{
							if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (IS_CHAR_SITTING_IN_ANY_CAR(ped1))) 
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R7_DA", "PRO3_13", 0, 0);//Easy brother! No cop drives this bad!
								START_SCRIPT_CONVERSATION(1, 1);
								play = 1;
								SETTIMERB(0); //сбрасываем таймер 
							}
						}
						if (play == 1)
						{
							if ( TIMERB() < 500 )
							{
								// выстрел в пустоту
								FIRE_PED_WEAPON(ped13, 987.781, 1302.982, 17.937);// пед стрелет в ГГ
								FIRE_PED_WEAPON(ped14, 984.776, 1303.433, 17.937);// пед стрелет в ГГ
								FIRE_PED_WEAPON(ped15, 980.882, 1303.824, 17.937);// пед стрелет в ГГ
								FIRE_PED_WEAPON(ped16, 977.471, 1304.206, 17.937);// пед стрелет в ГГ
							}
							if ( TIMERB() > 3000 )
							{
								play = 2;
							}
						}
						// триггер "Очень вежливо Ленс" тут
						if ((play == 0) || (play == 2))
						{
							if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped1))) 
							{
								if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 818.49, 1520.331, 11.554, 803.49, 1530.331, 16.554, 0 ))
								{
									// триггер "Очень вежливо Ленс" тут
									text_1 = 0;
									play = 3;
								}
								else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 890.218, 1520.751, 11.554, 875.218, 1530.751, 16.554, 0 ))
								{
									// триггер "Очень вежливо Ленс" тут
									text_1 = 0;
									play = 3;
								}
								else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 818.664, 1788.167, 11.554, 803.664, 1798.167, 16.554, 0 ))
								{
									// триггер "Очень вежливо Ленс" тут
									text_1 = 0;
									play = 3;
								}
								else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 890.393, 1788.167, 11.554, 875.393, 1798.167, 16.554, 0 ))
								{
									// триггер "Очень вежливо Ленс" тут
									text_1 = 0;
									play = 3;
								}
								else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 784.606, 1649.781, 11.554, 774.606, 1664.781, 16.554, 0 ))
								{
									// триггер "Очень вежливо Ленс" тут
									text_1 = 0;
									play = 3;
								}
								else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 918.3, 1649.781, 11.554, 908.3, 1664.781, 16.554, 0 ))
								{
									// триггер "Очень вежливо Ленс" тут
									text_1 = 0;
									play = 3;
								}
								else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 800.397, 1735.138, 19.02, 790.397, 1750.138, 24.02, 0 ))
								{
									// триггер "Очень вежливо Ленс" тут
									text_1 = 0;
									play = 3;
								}
							}
						}
						
						if (play == 3)
						{
							if (text_1 == 0)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R7_CE", "PRO3_14", 0, 0);//Remember - smile at the other cops.
								START_SCRIPT_CONVERSATION(1, 1);
								text_1 = 1;
								SETTIMERB(0); //сбрасываем таймер 
							}
							else if (text_1 == 1)
							{
								if ( TIMERB() > 2000 )
								{
									if (!IS_SCRIPTED_CONVERSATION_ONGOING())
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R7_CF", "PRO3_15", 0, 0);//Hey there officer. Nice badge, nice badge.
										START_SCRIPT_CONVERSATION(1, 1);

										SET_CHAR_COORDINATES(ped11, 897.536, 1543.841, 15.125);// перемещаем игрока
										SET_CHAR_COORDINATES(ped12, 895.744, 1541.958, 15.125);// перемещаем игрока
										text_1 = 2;
										SETTIMERB(0); //сбрасываем таймер 
									}
								}
							}
							else if (text_1 == 2)
							{
								if ( TIMERB() > 3550 )
								{
									if (!IS_SCRIPTED_CONVERSATION_ONGOING())
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R7_CG", "PRO3_16", 0, 0);// Real smooth, Lance.
										START_SCRIPT_CONVERSATION(1, 1);

										text_1 = 3;
										SETTIMERB(0); //сбрасываем таймер 
									}
								}
							}
							else if (text_1 == 3)
							{
								if ( TIMERB() > 1600 )
								{
									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "PRO3_23", 5000, 1);//~g~Walk into the marker to plant the bomb.
									play = 4;
									text_1 = 4;
								}
							}
						}

						// стрльба в зоне тут
						if ((IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), 905.125, 1536.022, 863.366, 1577.134, 0)) && (in_cord == 0))
						{
							SET_MAX_WANTED_LEVEL(6);
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 5);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "PRO3_07", 5000, 1);//~g~ You have blown your cover. Hurry up and plant the bomb!
							in_cord = 1;
						}

						// чекпойнт
						if (in_cord2 == 0)
						{
							DRAW_CHECKPOINT( 901.317, 1538.974, 13.028, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 901.317, 1538.974, 13.028, &PlayR);//проверка "игрок на координатах"
							if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
							{
								REQUEST_ANIMS( "amb@atm" );//загружаем файл с анимацией
								while (!HAVE_ANIMS_LOADED( "amb@atm" )) WAIT(0);
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "f_insertcard", "amb@atm", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								SetTime(1500);

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R7_DB", "PRO3_17", 0, 0);//Ok, timers are set, 5 seconds and ticking.
								START_SCRIPT_CONVERSATION(1, 1);

								REMOVE_BLIP(tommy_ico);//Удаляем иконку на радаре
								in_cord2 = 1;
								text_2 = 1;
								SETTIMERA(0); //сбрасываем таймер
								SETTIMERB(0); //сбрасываем таймер 
							}
						}
						else if (in_cord2 == 1)
						{
							if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 913.028, 1529.392, 12.492, 891.706, 1550.143, 18.605, 0 )) && (text_2 == 3))
							{
								// ставим камеру тут
								SET_CHAR_COORDINATES(ped1, 880.212, 1541.196, 13.442);// перемещаем игрока
								SET_CHAR_COORDINATES(GetPlayerPed(), 882.542, 1540.759, 13.442);// перемещаем игрока
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, 901.317, 1538.974, 13.953); // куда смотрит камера
								SET_CAM_POS			( camera, 870.802, 1552.197, 18.549 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );

								// анимации взрува
								SET_OBJECT_COORDINATES(tnt_1, 898.755, 1542.487, -5.294);
								ADD_EXPLOSION( 898.755, 1542.487, 14.125, 0, 1.5, 1, 0, 1.00000000 );
								ADD_EXPLOSION( 902.931, 1543.156, 14.125, 13, 1.5, 1, 0, 1.00000000 );
								SetTime(500);
								ADD_EXPLOSION( 896.861, 1540.657, 14.125, 0, 1.5, 1, 0, 1.00000000 );
								ADD_EXPLOSION( 895.912, 1536.321, 14.125, 13, 1.5, 1, 0, 1.00000000 );
								SetTime(500);
								ADD_EXPLOSION( 895.912, 1536.321, 14.125, 13, 1.5, 1, 0, 1.00000000 );
								SetTime(500);
								ADD_EXPLOSION( 902.931, 1543.156, 14.125, 13, 1.5, 1, 0, 1.00000000 );
								SetTime(500);

								in_cord2 = 2;
								SET_MAX_WANTED_LEVEL(6);
								ALTER_WANTED_LEVEL(GetPlayerIndex(), 5);
								APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
								glassON_1 = 1;

								// создаём блип
								ADD_BLIP_FOR_COORD(54.113, -17.044, 12.056, &tommy_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(tommy_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(tommy_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(tommy_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(tommy_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "PRO3_08", 5000, 1);//~g~ Get back to ~h~Vercetti Estate~g~ on ~h~Starfish Island~g~.

								//убираем камеру
								SetTime(1000);
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								END_CAM_COMMANDS( &camera );
								SET_WIDESCREEN_BORDERS( 0 );
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

								stalking = 0;
								in_car = 0;
								break;
							}
							else
							{
								if ( TIMERA() > 6000 )
								{
									SET_CHAR_COORDINATES(ped1, 880.212, 1541.196, 13.442);// перемещаем игрока
									SET_CHAR_COORDINATES(GetPlayerPed(), 882.542, 1540.759, 13.442);// перемещаем игрока
									SET_CHAR_HEADING(GetPlayerPed(), 150.0);
								}
							}
						}
						if (text_2 == 1)
						{
							if ( TIMERB() > 2650 )
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R7_EA", "PRO3_18", 0, 0);//5 seconds?!! We got to get the hell out of here!
									START_SCRIPT_CONVERSATION(1, 1);
									
									text_2 = 2;
									SETTIMERB(0); //сбрасываем таймер 
								}
							}
						}
						else if (text_2 == 2)
						{
							if ( TIMERB() > 2500 )
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "PRO3_24", 5000, 1);//~g~Get clear of the Cafe!
								text_2 = 3;
							}
						}

						// условия провала миссии
						if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// часть 3 на координатах Особняка
				if (skip == 0)
				{
					while (true)
					{
						WAIT( 0 );
						// Ленс сталкирит за Томми
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+22, PedY+22, PedZ+15, PedX-22, PedY-22, PedZ-15, 0 ))
						{
							if (stalking == 0)
							{
								TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
								stalking = 1;
								in_area = 1;
							}

							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &stalkerR);//проверка "игрок на координатах"
							if ((stalkerR < 1.5) && (stalking == 1) && (in_car == 0))
							{
								stalking = 2;
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
							}
							else if ((stalkerR > 5.5) && (stalking == 2) && (in_car == 0))
							{
								stalking = 0;
							}

							if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 0))
							{
								in_car = 1;
								in_area = 1;
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car1);
								TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, -1, 0);
								SETTIMERB( 0 );
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
								{
									in_car = 0;
									TASK_LEAVE_CAR(ped1, car1);
									MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
									TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
									stalking = 1;
								}
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 1) && (TIMERB() > 15000))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car1, 0);
							}
						}
						else
						{
							if (stalking == 1)
							{
								stalking = 0;
								in_area = 0;
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GEN3_23", 5000, 1);//~g~You've left Lance behind! Go and get him!
							}
						}
						//чекпойнт
						DRAW_CHECKPOINT( 54.113, -17.044, 12.056, 2.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 54.113, -17.044, 12.056, &PlayR);//проверка "игрок на координатах"
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 54.113, -17.044, 12.056, &in_cord);//проверка "игрок на координатах"
						if ((PlayR < 2.5) && (in_cord < 2.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							// прячем Ланса
							SET_CHAR_COORDINATES(ped1, 139.451, -93.681, 6.907);// перемещаем игрока

							// ставим камеру тут
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 54.436, -21.546, 15.853); // куда смотрит камера
							SET_CAM_POS			( camera, 54.304, 3.775, 13.849 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							// Томми забегат в особняк
							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 54.113, -32.102, 14.306, 3, -2);// Томми идёт в двери
							SetTime(3000);
							SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, outfit, 0);

							// меняем раурс камеры
							DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							POINT_CAM_AT_COORD	( camera, 52.907, -26.677, 15.604); // куда смотрит камера
							SET_CAM_POS			( camera, 53.137, 78.262, 38.317 );//расположение камеры
							SetTime(200);
							DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана

							// надпись в центре экрана "вы отстояли право собственности"
							SETTIMERA(0); //сбрасываем таймер 
							while (true)
							{
								SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
								SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
								SET_TEXT_EDGE(1, 0, 0, 0, 255); //
								SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
								SET_TEXT_CENTRE(1); // задаём центр текста
								DISPLAY_TEXT(0.5, 0.45, "PRO_AS1");//PROTECTION RING ASSET COMPLETED
								WAIT( 0 );
								if ( TIMERA() > 5000 )
								{
									break;
								}
							}

							POINT_CAM_AT_COORD	( camera, 60.925, -64.174, 20.743); // куда смотрит камера
							SET_CAM_POS			( camera, 57.996, -63.316, 22.499 );//расположение камеры
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "PRO_AS2", 5000, 1);//~g~Vercetti Estate will now generate revenue up to a maximum of $5000. Make sure you collect it regularly.

							//МАШИНКА СЧЁТКА ДЕНЕГ
							SETTIMERA(0); //сбрасываем таймер 
							SETTIMERB(0); //сбрасываем таймер
							
							uint rId9;
							int temp = 0;
							GET_SCRIPT_RENDERTARGET_RENDER_ID(&rId9);

							while(true)
							{
								WAIT(0);
								SET_TEXT_RENDER_ID(rId9);
								DRAW_SPRITE( 0, 0.5000000, 0.50000000, 1.00000000, 1.00000000, 0.00000000, 0, 0, 0, 255 );

								SET_TEXT_SCALE(4.0, 14.5);
								SET_TEXT_DROPSHADOW(45, 45, 45, 255, 0);
								SET_TEXT_COLOUR(51, 184, 18, 255);
								SET_TEXT_FONT(1);
								DISPLAY_TEXT_WITH_NUMBER(0.005, 0.005, "CASH", temp);//пишем сумму из переменной
							
								if ( TIMERA() > 500)
								{
									temp +=3;
									SETTIMERA(0); //сбрасываем таймер 
								}
								if ( TIMERB() > 6000)
								{
									break;
								}
							}
							WAIT( 100 );
							SET_TEXT_RENDER_ID(rId9);
							DRAW_RECT(0.5, 0.5, 1.0, 1.0, 0, 0, 0, 255);
							
							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							ALTER_WANTED_LEVEL(GetPlayerIndex(), 0);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
							skip = 2;// переменная пропуска
							break;
						}
						// активируем трафик
						if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1073.344, 1130.861, -10.0, 593.344, 1880.861, 40.0, 0 )) && ( glassON_1 == 1))
						{
							glassON_1 = 0;
							SET_CAR_DENSITY_MULTIPLIER(1);// включаем пути
						}
						// условия провала миссии
						if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// зачищаем скрипт
				WAIT( 100 );
				REMOVE_BLIP(tommy_ico);//Удаляем иконку на радаре
				SET_MAX_WANTED_LEVEL(6);

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(dynamite_1);//выгружаем модель

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped9);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped10);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped11);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped12);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped13);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped14);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped15);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped16);//выгружаем модель педа(в последствии пед изчезнет

				// выгружаем из памяти транспорт
				if (car1 != 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				}
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)

				DELETE_OBJECT(&tnt_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&tnt_1);

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_BUD_3" );//Cop Land
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(10000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +10000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 10000);
					G_PROTECT = 4;
					autosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}
		else if ((G_ONMISSION == 0) && (G_PROTECT == 4))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(54.6656, -28.26, 13.45, &tommy_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(tommy_ico, BLIP_VLAD);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(tommy_ico, 1.1); // масштаб иконки на радаре
				SET_BLIP_AS_SHORT_RANGE(tommy_ico, 1); // иконка пропадает если не в зоне радардиска
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(tommy_ico, "LG_24");//иконка на радаре называние в истории карты "Версетти"
				blip_on = 1;
			}
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(tommy_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}

		if (G_PROTECT == 4)
		{
			if ( TIMERC() > 576)// время фарма
			{
				if (income < 5000)// максимальный доход
				{
					income +=1;
				}
				SETTIMERC(0); //сбрасываем таймер 
			}

			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 62.241, -66.198, 19.549, 56.077, -61.306, 25.659, 0 ))
			{
				if (load_mashin == 0)
				{
					GET_SCRIPT_RENDERTARGET_RENDER_ID(&rId9);
					load_mashin = 1;
				}
				SET_TEXT_RENDER_ID(rId9);
				DRAW_SPRITE( 0, 0.5000000, 0.50000000, 1.00000000, 1.00000000, 0.00000000, 0, 0, 0, 255 );
				SET_TEXT_SCALE(4.0, 14.5);
				SET_TEXT_DROPSHADOW(45, 45, 45, 255, 0);
				SET_TEXT_COLOUR(51, 184, 18, 255);
				SET_TEXT_FONT(1);
				DISPLAY_TEXT_WITH_NUMBER(0.005, 0.005, "CASH", income);//пишем сумму из переменной
				if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), 61.623, -64.784, 58.952, -62.641, 0))
				{
					if (help == 0)
					{
						PRINT_HELP_FOREVER("NEGETMONEY"); // Press the ~INPUT_PHONE_ACCEPT~ button to cash out.
						help = 1;
					}
					if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
					{
						ADD_SCORE( GetPlayerIndex(), +income );// отнимаем у игрока сумму
						income = 0;
					}
				}
			}
			else
			{
				if (load_mashin == 1) 
				{
					CLEAR_HELP(); // удаляем текст подсказки
					WAIT( 100 );
					SET_TEXT_RENDER_ID(rId9);
					DRAW_RECT(0.5, 0.5, 1.0, 1.0, 35, 35, 35, 255);
					load_mashin = 0;
					help = 0;
				}
			}
		}
	}
}
void main(void)
{
	THIS_SCRIPT_SHOULD_BE_SAVED();
	versetty();
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
