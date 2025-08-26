/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "features.h"
#include "globals.h"
#include "cutscenes.h"
#include "mission_passed.h"
#include "fast_travel.h"
float PlayX, PlayY, PlayZ, PlayR, blip_on, textur, text1, skip, start, Blip_x, Blip_y, Blip_z, Blip_x2, Blip_y2, Blip_z2, play_cord, speed, poziteon, ugol, time_m, time_s, sound, bike_in, wanted, autosave;
float Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, Ped1R, SetSped1, ped1_cord, sped_wall1, sped_wall2, sped_wall3;
float shkalaH1, shkalaH2, shkalaH3, shkalaHUD_y1, shkalaHUD_y2, shkalaHUD_y3, HUD_w, HUD_x, shkala;
float Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, Ped2R, SetSped2, ped2_cord;
float Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, Ped3R, SetSped3, ped3_cord;
float Ped1_c, Ped4_c, Ped5_c, Ped6_c, Ped7_c, Ped8_c, Ped9_c, Ped10_c, Ped11_c, Ped12_c, hate, PointN, PedX, PedY, PedZ, PedR, shoot, siren;

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
void bikers(void)
{
	blip_on = 0;
	autosave = 0;
	Blip bike_ico;
    uint cutscene_torso;	
	WAIT(3000);
	while(true)
	{
		WAIT(0);
		if (autosave == 1)
		{
			autosave = 0;
			DO_AUTO_SAVE();
			WAIT(500);
		}
//============================== Alloy Wheels of Steel ======================================
		if ((G_ONMISSION == 0) && (G_BIKE == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-164.663, 1185.16, 4.96332, &bike_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(bike_ico, BLIP_DATE);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(bike_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(bike_ico, "LG_03");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( -164.663, 1185.16, 4.96332, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -164.663, 1185.16, 4.96332, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("BIKE_1", 15000, CUTSCENE_BIKER);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-609.723, 658.861, 9.908, 279.440);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре
				blip_on = 0;

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
				CLEAR_WANTED_LEVEL(GetPlayerIndex());
				#if !defined SCRIPTED_CUTSCENES_BEFORE_ACTUAL_CUTSCENES
				DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}
				#endif
				SET_CHAR_COORDINATES(GetPlayerPed(), -164.834, 1186.85, 5.19596);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 0.0);

				Car car1, car2, car3;
				Ped ped1, ped2, ped3;
				Cam camera;
				Texture fon, timer;
				Blip Blip_r, Blip_r2, Blip_c1, Blip_c2, Blip_c3;
				uint checkpoint;

				text1 = 0;
				skip = 0;
				start = 0;
				time_m = 0;
				time_s = 0;
				
				Blip_x = -103.9255;
				Blip_y = 1206.656;
				Blip_z = 4.7;
				Blip_x2 = -42.2727;
				Blip_y2 = 1335.263;
				Blip_z2 = 4.71;
				play_cord = 1;

				ped1B_x = -103.9255;
				ped1B_y = 1206.656;
				ped1B_z = 4.7;
				SetSped1 = 0;
				ped1_cord = 1;

				ped2B_x = -103.9255;
				ped2B_y = 1206.656;
				ped2B_z = 4.7;
				SetSped2 = 0;
				ped2_cord = 1;

				ped3B_x = -103.9255;
				ped3B_y = 1206.656;
				ped3B_z = 4.7;
				SetSped3 = 0;
				ped3_cord = 1;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				timer = GET_TEXTURE( textur, "timer_hud" );

				uint CarM1 = MODEL_ZOMBIEB;// байк
				uint PedM1 = MODEL_M_Y_GALB_LO_01;// байкер 1
				uint PedM2 = MODEL_M_Y_GALB_LO_02;// байкер 2

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(PedM1);// Мерседес
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Мерседес
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало

				CREATE_CAR(CarM1, -157.506, 1193.88, 4.96332, &car1, TRUE);
				CREATE_CAR(CarM1, -157.832, 1195.92, 4.96332, &car2, TRUE);
				CREATE_CAR(CarM1, -158.158, 1197.97, 4.96332, &car3, TRUE);
				SET_CAR_HEADING(car1, -82.0);
				SET_CAR_HEADING(car2, -82.0);
				SET_CAR_HEADING(car3, -82.0);
				SET_CAN_BURST_CAR_TYRES(car1, 0); // шины автомобиля нельзя повредить
				SET_CAN_BURST_CAR_TYRES(car2, 0); // шины автомобиля нельзя повредить
				SET_CAN_BURST_CAR_TYRES(car3, 0); // шины автомобиля нельзя повредить

				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM2, &ped2);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM1, &ped3);//создаём педа за рулём автомобиля
				SET_CHAR_PROOFS(ped1, TRUE, TRUE, TRUE, TRUE, TRUE);//делает педа бесмертным
				SET_CHAR_PROOFS(ped2, TRUE, TRUE, TRUE, TRUE, TRUE);//делает педа бесмертным
				SET_CHAR_PROOFS(ped3, TRUE, TRUE, TRUE, TRUE, TRUE);//делает педа бесмертным

				uint hour, minute, weather;
				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(19, 30);//устанавливаем время

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "BIKE_1", 6 ); // загружаем субтитры из *.GTX
																	
							
				START_CUTSCENE_NOW("bike_1");
		
									
				while (!HAS_CUTSCENE_LOADED())
				{
					WAIT(0);
				}

				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED())
				{
					WAIT(0);
				}

				if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
				{
					DO_SCREEN_FADE_IN(0);
				}

				FORCE_WEATHER_NOW( weather );//устанавливаем погода
				RELEASE_WEATHER();
				FORWARD_TO_TIME_OF_DAY(hour, minute);//устанавливаем время

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				ADD_BLIP_FOR_COORD(-158.485, 1200.02, 4.69314, &bike_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(bike_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(bike_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(bike_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(bike_ico, "NE_POINT");//иконка на радаре называние в истории карты ""

				PRINT_STRING_IN_STRING("string", "BM1_1", 5000, 1);//~g~Get a Freeway or an Angel and get to the starting grid.
				CLEAR_AREA( -158.485, 1200.02, 4.69314, 65.0, 1);//очещаем зону загрузки

				while(true)
				{
					WAIT(0);
					DRAW_CHECKPOINT( -158.485, 1200.02, 4.69314, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -158.485, 1200.02, 4.69314, &PlayR);//проверка "игрок на координатах"
					if ( PlayR < 2.1)
					{
						if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_ZOMBIEB)) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_BOBBER)))
						{
							if (text1 == 1)
							{
								text1 = 0;
							}
							REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре
							// 3..2..1.. GO
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							CLEAR_PRINTS();

							//айдио тут
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R2_BA", "BIKE1_1", 0, 0);//All right, fancy clothes. Let's see what you can do.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_BB", " ", 0, 0);//
							START_SCRIPT_CONVERSATION(1, 1);
							SetTime(1000);

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
							SETTIMERA(0);
							start = 1;
							break;
						}
						else
						{
							if (text1 == 0)
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "BM1_2", 5000, 1);//~g~You need a Freeway or an Angel to compete!
								text1 = 1;
							}
						}
					}
					else if (!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) // если игрок поцарапал машину соперника
					{
						REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре
						SETTIMERA(0);
						start = 2;
						break;
					}
					else if (!IS_CHAR_SITTING_IN_ANY_CAR(ped2)) // если игрок поцарапал машину соперника
					{
						REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре
						SETTIMERA(0);
						start = 2;
						break;
					}
					else if (!IS_CHAR_SITTING_IN_ANY_CAR(ped3)) // если игрок поцарапал машину соперника
					{
						REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре
						SETTIMERA(0);
						start = 2;
						break;
					}
					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;
						break;
					}
				}
				// сама гонка тут
				if (skip == 0)
				{
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
					SETTIMERB( 0 );
					while(true)
					{
						WAIT(0);
						if ((start == 1) || (start == 3))
						{
							if (start == 1)
							{
								PLAY_AUDIO_EVENT( "FRONTEND_GAME_PICKUP_CHECKPOINT" );
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								
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

								start = 3;
							}
							if (TIMERA() < 900)
							{
								SET_TEXT_FONT(4);
								SET_TEXT_COLOUR(235, 115, 18, 255);
								SET_TEXT_SCALE(0.5, 0.7);
								SET_TEXT_EDGE(2, 0, 0, 0, 255);
								SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
								SET_TEXT_CENTRE(1);
								DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "GO", 1); // пишем "GO"
							}
							else
							{
								start = 99;
							}
						}
						else if ((start == 2) || (start == 4))
						{
							if (start == 2)
							{
								PLAY_AUDIO_EVENT( "FRONTEND_GAME_PICKUP_CHECKPOINT" );
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								
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

								start = 4;
							}
							if (TIMERA() < 900)
							{
								SET_TEXT_FONT(4);
								SET_TEXT_COLOUR(235, 115, 18, 255);
								SET_TEXT_SCALE(0.5, 0.7);
								SET_TEXT_EDGE(2, 0, 0, 0, 255);
								SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
								SET_TEXT_CENTRE(1);
								DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "NE_RACE4", 1); //3...2...1...GO!
							}
							else
							{
								start = 99;
							}
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

							if (play_cord == 2)
							{
								Blip_x2 = 47.85912;
								Blip_y2 = 1550.724;
								Blip_z2 = 3.26;
							}
							else if (play_cord == 3)
							{
								Blip_x2 = 134.3364; 
								Blip_y2 = 1818.371;
								Blip_z2 = 5.39;
							}
							else if (play_cord == 4)
							{
								Blip_x2 = -54.23398; 
								Blip_y2 = 1873.135;
								Blip_z2 = 5.39;
							}
							else if (play_cord == 5)
							{
								Blip_x2 = -302.6159; 
								Blip_y2 = 1849.695;
								Blip_z2 = 5.39;
							}
							else if (play_cord == 6)
							{
								Blip_x2 = -346.392;
								Blip_y2 = 1914.09;
								Blip_z2 = 5.21;
							}
							else if (play_cord == 7)
							{
								Blip_x2 = -250.012;
								Blip_y2 = 1924.68;
								Blip_z2 = 5.66;
							}
							else if (play_cord == 8)
							{
								Blip_x2 = -247.153;
								Blip_y2 = 1998.89;
								Blip_z2 = 5.72;
							}
							else if (play_cord == 9)
							{
								Blip_x2 = -351.048;
								Blip_y2 = 2010.8;
								Blip_z2 = 5.54;
							}
							else if (play_cord == 10)
							{
								Blip_x2 = -449.47;
								Blip_y2 = 1974.78;
								Blip_z2 = 5.54;
							}
							else if (play_cord == 11)
							{
								Blip_x2 = -437.7158; 
								Blip_y2 = 1861.706;
								Blip_z2 = 5.09;
							}
							else if (play_cord == 12)
							{
								Blip_x2 = -432.523; 
								Blip_y2 = 1639.889;
								Blip_z2 = 4.7;
							}
							else if (play_cord == 13)
							{
								Blip_x2 = -436.7519; 
								Blip_y2 = 1486.595;
								Blip_z2 = 4.7;
							}
							else if (play_cord == 14)
							{
								Blip_x2 = -436.8126; 
								Blip_y2 = 1309.289;
								Blip_z2 = 4.7;
							}
							else if (play_cord == 15)
							{
								Blip_x2 = -292.9197; 
								Blip_y2 = 1284.225;
								Blip_z2 = 4.72;
							}
							else if (play_cord == 16)
							{
								Blip_x2 = -190.5199; 
								Blip_y2 = 1278.889;
								Blip_z2 = 4.22;
							}
							else if (play_cord == 17)
							{
								Blip_x2 = -83.0294; 
								Blip_y2 = 1268.254;
								Blip_z2 = 4.45;
							}
							else if (play_cord == 18)
							{
								Blip_x2 = -163.568; 
								Blip_y2 = 1196.217;
								Blip_z2 = 4.71;
							}
							else if (play_cord == 19)
							{
								Blip_x2 = Blip_x2; 
								Blip_y2 = Blip_y2;
								Blip_z2 = Blip_z2;
							}
							else if (play_cord == 20)
							{
								skip = 2;
								break;
							}
							if (play_cord < 19)
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
								if (play_cord < 18)
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
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//иконка на радаре "Blip01" называние в истории карты
									CHANGE_BLIP_SCALE(Blip_r2, 0.77999990); // масштаб иконки на радаре
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

						if (play_cord > 1)
						{
							if (IS_CHAR_IN_CAR(GetPlayerPed(), car1))
							{
								MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
								GET_CHAR_COORDINATES(ped1,  &Ped1X, &Ped1Y, &Ped1Z);//вписываем координаты соперника в переменную
								GET_CHAR_HEADING(ped1, &ugol);
								CREATE_CAR(CarM1, Ped1X, Ped1Y, Ped1Z, &car1, TRUE);
								SET_CAR_HEADING(car1, ugol);
								WARP_CHAR_INTO_CAR(ped1, car1);// садим педа в ТС
							}
							else if (IS_CHAR_IN_CAR(GetPlayerPed(), car2))
							{
								MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
								GET_CHAR_COORDINATES(ped2,  &Ped2X, &Ped2Y, &Ped2Z);//вписываем координаты соперника в переменную
								GET_CHAR_HEADING(ped2, &ugol);
								CREATE_CAR(CarM1, Ped2X, Ped2Y, Ped2Z, &car2, TRUE);
								SET_CAR_HEADING(car2, ugol);
								WARP_CHAR_INTO_CAR(ped2, car2);// садим педа в ТС
							}
							else if (IS_CHAR_IN_CAR(GetPlayerPed(), car3))
							{
								MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
								GET_CHAR_COORDINATES(ped3,  &Ped3X, &Ped3Y, &Ped3Z);//вписываем координаты соперника в переменную
								GET_CHAR_HEADING(ped3, &ugol);
								CREATE_CAR(CarM1, Ped3X, Ped3Y, Ped3Z, &car3, TRUE);
								SET_CAR_HEADING(car3, ugol);
								WARP_CHAR_INTO_CAR(ped3, car3);// садим педа в ТС
							}
						}
//============================== соперник 1 ==============================


						GET_CHAR_COORDINATES(ped1,  &Ped1X, &Ped1Y, &Ped1Z);//вписываем координаты соперника в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, &Ped1R);//проверка "игрок на координатах"
						if ( Ped1R < 55.0)
						{
							if (SetSped1 == 0)
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 65.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
							if (SetSped1 == 1)
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
							if (SetSped1 == 2)
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 12.5, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
						}
						if ( Ped1R < 10.0)
						{
							ped1_cord += 1;

							if (ped1_cord == 2)
							{
								ped1B_x = -42.2727;
								ped1B_y = 1335.263;
								ped1B_z = 4.71;
								SetSped1 = 0;
							}
							else if (ped1_cord == 3)
							{
								ped1B_x = 47.85912;
								ped1B_y = 1550.724;
								ped1B_z = 3.26;
								SetSped1 = 0;
							}
							else if (ped1_cord == 4)
							{
								ped1B_x = 134.3364; 
								ped1B_y = 1818.371;
								ped1B_z = 5.39;
								SetSped1 = 1;
							}
							else if (ped1_cord == 5)
							{
								ped1B_x = -54.23398; 
								ped1B_y = 1873.135;
								ped1B_z = 5.39;
								SetSped1 = 0;
							}
							else if (ped1_cord == 6)
							{
								ped1B_x = -302.6159; 
								ped1B_y = 1849.695;
								ped1B_z = 5.39;
								SetSped1 = 1;
							}
							else if (ped1_cord == 7)
							{
								ped1B_x = -346.392;
								ped1B_y = 1914.09;
								ped1B_z = 5.21;
								SetSped1 = 2;
							}
							else if (ped1_cord == 8)
							{
								ped1B_x = -250.012;
								ped1B_y = 1924.68;
								ped1B_z = 5.66;
								SetSped1 = 1;
							}
							else if (ped1_cord == 9)
							{
								ped1B_x = -247.153;
								ped1B_y = 1998.89;
								ped1B_z = 5.72;
								SetSped1 = 1;
							}
							else if (ped1_cord == 10)
							{
								ped1B_x = -351.048;
								ped1B_y = 2010.8;
								ped1B_z = 5.54;
								SetSped1 = 0;
							}
							else if (ped1_cord == 11)
							{
								ped1B_x = -449.47;
								ped1B_y = 1974.78;
								ped1B_z = 5.54;
								SetSped1 = 1;
							}
							else if (ped1_cord == 12)
							{
								ped1B_x = -437.7158; 
								ped1B_y = 1861.706;
								ped1B_z = 5.09;
								SetSped1 = 0;
							}
							else if (ped1_cord == 13)
							{
								ped1B_x = -432.523; 
								ped1B_y = 1639.889;
								ped1B_z = 4.7;
								SetSped1 = 0;
							}
							else if (ped1_cord == 14)
							{
								ped1B_x = -436.7519; 
								ped1B_y = 1486.595;
								ped1B_z = 4.7;
								SetSped1 = 0;
							}
							else if (ped1_cord == 15)
							{
								ped1B_x = -436.8126; 
								ped1B_y = 1309.289;
								ped1B_z = 4.7;
								SetSped1 = 1;
							}
							else if (ped1_cord == 16)
							{
								ped1B_x = -292.9197; 
								ped1B_y = 1284.225;
								ped1B_z = 4.72;
								SetSped1 = 0;
							}
							else if (ped1_cord == 17)
							{
								ped1B_x = -190.5199; 
								ped1B_y = 1278.889;
								ped1B_z = 4.22;
								SetSped1 = 0;
							}
							else if (ped1_cord == 18)
							{
								ped1B_x = -83.0294; 
								ped1B_y = 1268.254;
								ped1B_z = 4.45;
								SetSped1 = 1;
							}
							else if (ped1_cord == 19)
							{
								ped1B_x = -163.568; 
								ped1B_y = 1196.217;
								ped1B_z = 4.71;
								SetSped1 = 0;
							}
							else if (ped1_cord == 20)
							{
								ped1B_x = ped1B_x; 
								ped1B_y = ped1B_y;
								ped1B_z = ped1B_z;
								SetSped1 = 0;
								skip = 1;
								PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
								break;
							}
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 60.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						}
//============================== соперник 2 ==============================


						GET_CHAR_COORDINATES(ped2,  &Ped2X, &Ped2Y, &Ped2Z);//вписываем координаты соперника в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, &Ped2R);//проверка "игрок на координатах"
						if ( Ped2R < 55.0)
						{
							if (SetSped2 == 0)
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 65.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
							if (SetSped2 == 1)
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
							if (SetSped2 == 2)
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 12.5, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
						}
						if ( Ped2R < 10.0)
						{
							ped2_cord += 1;

							if (ped2_cord == 2)
							{
								ped2B_x = -42.2727;
								ped2B_y = 1335.263;
								ped2B_z = 4.71;
								SetSped2 = 0;
							}
							else if (ped2_cord == 3)
							{
								ped2B_x = 47.85912;
								ped2B_y = 1550.724;
								ped2B_z = 3.26;
								SetSped2 = 0;
							}
							else if (ped2_cord == 4)
							{
								ped2B_x = 134.3364; 
								ped2B_y = 1818.371;
								ped2B_z = 5.39;
								SetSped2 = 1;
							}
							else if (ped2_cord == 5)
							{
								ped2B_x = -54.23398; 
								ped2B_y = 1873.135;
								ped2B_z = 5.39;
								SetSped2 = 0;
							}
							else if (ped2_cord == 6)
							{
								ped2B_x = -302.6159; 
								ped2B_y = 1849.695;
								ped2B_z = 5.39;
								SetSped2 = 1;
							}

							else if (ped2_cord == 7)
							{
								ped2B_x = -346.392;
								ped2B_y = 1914.09;
								ped2B_z = 5.21;
								SetSped2 = 2;
							}
							else if (ped2_cord == 8)
							{
								ped2B_x = -250.012;
								ped2B_y = 1924.68;
								ped2B_z = 5.66;
								SetSped2 = 1;
							}
							else if (ped2_cord == 9)
							{
								ped2B_x = -247.153;
								ped2B_y = 1998.89;
								ped2B_z = 5.72;
								SetSped2 = 1;
							}
							else if (ped2_cord == 10)
							{
								ped2B_x = -351.048;
								ped2B_y = 2010.8;
								ped2B_z = 5.54;
								SetSped2 = 0;
							}
							else if (ped2_cord == 11)
							{
								ped2B_x = -449.47;
								ped2B_y = 1974.78;
								ped2B_z = 5.54;
								SetSped2 = 1;
							}
							else if (ped2_cord == 12)
							{
								ped2B_x = -437.7158; 
								ped2B_y = 1861.706;
								ped2B_z = 5.09;
								SetSped2 = 0;
							}
							else if (ped2_cord == 13)
							{
								ped2B_x = -432.523; 
								ped2B_y = 1639.889;
								ped2B_z = 4.7;
								SetSped2 = 0;
							}
							else if (ped2_cord == 14)
							{
								ped2B_x = -436.7519; 
								ped2B_y = 1486.595;
								ped2B_z = 4.7;
								SetSped2 = 0;
							}
							else if (ped2_cord == 15)
							{
								ped2B_x = -436.8126; 
								ped2B_y = 1309.289;
								ped2B_z = 4.7;
								SetSped2 = 1;
							}
							else if (ped2_cord == 16)
							{
								ped2B_x = -292.9197; 
								ped2B_y = 1284.225;
								ped2B_z = 4.72;
								SetSped2 = 0;
							}
							else if (ped2_cord == 17)
							{
								ped2B_x = -190.5199; 
								ped2B_y = 1278.889;
								ped2B_z = 4.22;
								SetSped2 = 0;
							}
							else if (ped2_cord == 18)
							{
								ped2B_x = -83.0294; 
								ped2B_y = 1268.254;
								ped2B_z = 4.45;
								SetSped2 = 1;
							}
							else if (ped2_cord == 19)
							{
								ped2B_x = -163.568; 
								ped2B_y = 1196.217;
								ped2B_z = 4.71;
								SetSped2 = 0;
							}
							else if (ped2_cord == 20)
							{
								ped2B_x = ped2B_x; 
								ped2B_y = ped2B_y;
								ped2B_z = ped2B_z;
								SetSped2 = 0;
								skip = 1;
								PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
								break;
							}
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 60.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						}
//============================== соперник 3 ==============================


						GET_CHAR_COORDINATES(ped3,  &Ped3X, &Ped3Y, &Ped3Z);//вписываем координаты соперника в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, &Ped3R);//проверка "игрок на координатах"
						if ( Ped3R < 55.0)
						{
							if (SetSped3 == 0)
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 65.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
							if (SetSped3 == 1)
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
							if (SetSped3 == 2)
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 12.5, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
						}
						if ( Ped3R < 10.0)
						{
							ped3_cord += 1;
							if (ped3_cord == 2)
							{
								ped3B_x = -42.2727;
								ped3B_y = 1335.263;
								ped3B_z = 4.71;
								SetSped3 = 0;
							}
							else if (ped3_cord == 3)
							{
								ped3B_x = 47.85912;
								ped3B_y = 1550.724;
								ped3B_z = 3.26;
								SetSped3 = 0;
							}
							else if (ped3_cord == 4)
							{
								ped3B_x = 134.3364; 
								ped3B_y = 1818.371;
								ped3B_z = 5.39;
								SetSped3 = 1;
							}
							else if (ped3_cord == 5)
							{
								ped3B_x = -54.23398; 
								ped3B_y = 1873.135;
								ped3B_z = 5.39;
								SetSped3 = 0;
							}
							else if (ped3_cord == 6)
							{
								ped3B_x = -302.6159; 
								ped3B_y = 1849.695;
								ped3B_z = 5.39;
								SetSped3 = 1;
							}

							else if (ped3_cord == 7)
							{
								ped3B_x = -346.392;
								ped3B_y = 1914.09;
								ped3B_z = 5.21;
								SetSped3 = 2;
							}
							else if (ped3_cord == 8)
							{
								ped3B_x = -250.012;
								ped3B_y = 1924.68;
								ped3B_z = 5.66;
								SetSped3 = 1;
							}
							else if (ped3_cord == 9)
							{
								ped3B_x = -247.153;
								ped3B_y = 1998.89;
								ped3B_z = 5.72;
								SetSped3 = 1;
							}
							else if (ped3_cord == 10)
							{
								ped3B_x = -351.048;
								ped3B_y = 2010.8;
								ped3B_z = 5.54;
								SetSped3 = 0;
							}
							else if (ped3_cord == 11)
							{
								ped3B_x = -449.47;
								ped3B_y = 1974.78;
								ped3B_z = 5.54;
								SetSped3 = 1;
							}
							else if (ped3_cord == 12)
							{
								ped3B_x = -437.7158; 
								ped3B_y = 1861.706;
								ped3B_z = 5.09;
								SetSped3 = 0;
							}
							else if (ped3_cord == 13)
							{
								ped3B_x = -432.523; 
								ped3B_y = 1639.889;
								ped3B_z = 4.7;
								SetSped3 = 0;
							}
							else if (ped3_cord == 14)
							{
								ped3B_x = -436.7519; 
								ped3B_y = 1486.595;
								ped3B_z = 4.7;
								SetSped3 = 0;
							}
							else if (ped3_cord == 15)
							{
								ped3B_x = -436.8126; 
								ped3B_y = 1309.289;
								ped3B_z = 4.7;
								SetSped3 = 1;
							}
							else if (ped3_cord == 16)
							{
								ped3B_x = -292.9197; 
								ped3B_y = 1284.225;
								ped3B_z = 4.72;
								SetSped3 = 0;
							}
							else if (ped3_cord == 17)
							{
								ped3B_x = -190.5199; 
								ped3B_y = 1278.889;
								ped3B_z = 4.22;
								SetSped3 = 0;
							}
							else if (ped3_cord == 18)
							{
								ped3B_x = -83.0294; 
								ped3B_y = 1268.254;
								ped3B_z = 4.45;
								SetSped3 = 1;
							}
							else if (ped3_cord == 19)
							{
								ped3B_x = -163.568; 
								ped3B_y = 1196.217;
								ped3B_z = 4.71;
								SetSped3 = 0;
							}
							else if (ped3_cord == 20)
							{
								ped3B_x = ped3B_x; 
								ped3B_y = ped3B_y;
								ped3B_z = ped3B_z;
								SetSped3 = 0;
								skip = 1;
								PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
								break;
							}
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 60.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
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

						// HUD позицыя игрока 
						DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78815097, 0.73564852, "NE_RACE5"); //POSITION:

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.312, 0.534);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT_WITH_NUMBER(0.920052, 0.725462962, "CP_TIME_NOZERO", poziteon);

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
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

						DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.

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



						//==================== фиксы соперника в стене ====================
						GET_CHAR_SPEED(ped1, &sped_wall1);
						GET_CHAR_SPEED(ped2, &sped_wall2);
						GET_CHAR_SPEED(ped3, &sped_wall3);
						if (sped_wall1 < 2)
						{
							if (TIMERB() > 3000)
							{
								if (IS_CHAR_IN_AREA_3D( ped1, -223.827, 1266.457, 4.189, -253.827, 1296.457, 14.189, 0 ))
								{
									SET_CHAR_COORDINATES(ped1, -220.926, 1279.21, 5.7918);// перемещаем игрока
								}
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 60.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								SETTIMERB(0);
							}
						}
						if (sped_wall2 < 2)
						{
							if (TIMERB() > 3000)
							{
								if (IS_CHAR_IN_AREA_3D( ped2, -223.827, 1266.457, 4.189, -253.827, 1296.457, 14.189, 0 ))
								{
									SET_CHAR_COORDINATES(ped2, -220.926, 1279.21, 5.7918);// перемещаем игрока
								}
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 60.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								SETTIMERB(0);
							}
						}
						if (sped_wall3 < 2)
						{
							if (TIMERB() > 3000)
							{
								if (IS_CHAR_IN_AREA_3D( ped3, -223.827, 1266.457, 4.189, -253.827, 1296.457, 14.189, 0 ))
								{
									SET_CHAR_COORDINATES(ped3, -220.926, 1279.21, 5.7918);// перемещаем игрока
								}
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 60.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								SETTIMERB(0);
							}
						}
						if ((sped_wall1 > 2) && (sped_wall2 > 2) && (sped_wall3 > 2))
						{
							SETTIMERB(0);
						}



					}
				}
				// чистим скрипт тут
				WAIT(100);
				REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
				REMOVE_BLIP(Blip_r2);//Удаляем иконку на радаре
				REMOVE_BLIP(Blip_c1);//Удаляем иконку на радаре
				REMOVE_BLIP(Blip_c2);//Удаляем иконку на радаре
				REMOVE_BLIP(Blip_c3);//Удаляем иконку на радаре
				DELETE_CHECKPOINT(checkpoint);

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет

				// выгружаем из памяти транспорт
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( timer );
				REMOVE_TXD( textur );

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_BIKE_1" );//Alloy Wheels of Steel
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(1000, "missionpassed", "CASH");
					CLEAR_WANTED_LEVEL(GetPlayerIndex());
					ADD_SCORE( GetPlayerIndex(), +1000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 1000);
					G_BIKE = 2;
					autosave = 1;
				}

				G_ONMISSION = 0;
			}
		}

//============================== Messing with the Man ======================================
		else if ((G_ONMISSION == 0) && (G_BIKE == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-164.663, 1185.16, 4.96332, &bike_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(bike_ico, BLIP_DATE);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(bike_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(bike_ico, "LG_03");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( -164.663, 1185.16, 4.96332, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -164.663, 1185.16, 4.96332, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("BIKE_2", 15000, CUTSCENE_BIKER);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-609.723, 658.861, 9.908, 279.440);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре
				blip_on = 0;
				
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
				CLEAR_WANTED_LEVEL(GetPlayerIndex());
				#if !defined SCRIPTED_CUTSCENES_BEFORE_ACTUAL_CUTSCENES
				DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}
				#endif

				SET_CHAR_COORDINATES(GetPlayerPed(), -164.834, 1186.85, 5.19596);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 0.0);

				uint hour, minute, weather;
				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(19, 30);//устанавливаем время

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "BIKE_3", 6 ); // загружаем субтитры из *.GTX
																	
							
				START_CUTSCENE_NOW("bike_3");
		
									
				while (!HAS_CUTSCENE_LOADED())
				{
					WAIT(0);
				}

				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED())
				{
					WAIT(0);
				}

				if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
				{
					DO_SCREEN_FADE_IN(0);
				}

				FORCE_WEATHER_NOW( weather );//устанавливаем погода
				RELEASE_WEATHER();
				FORWARD_TO_TIME_OF_DAY(hour, minute);//устанавливаем время
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				Texture fon, timer;
				uint random;
				Pickup sweap_1;


				skip = 0;
				time_m = 3;
				time_s = 0;
				shkala = 100;
				sound = 0;
				HUD_x = 0.922156;
				HUD_w = 0.0739583;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				timer = GET_TEXTURE( textur, "timer_hud" );

				PRINT_STRING_IN_STRING("string", "BM2_2", 5000, 1);//~g~You must fill the Chaos Meter in the time given to show us how much of a badass you are!
				CREATE_PICKUP_ROTATE(w_uzi, 3, 60, -162.254, 1180.55, 6.80878, -90.0, 0.0, 0.0, &sweap_1);// даём винтовку

				SETTIMERA( 0 );
				SETTIMERB( 0 );
				while(true)
				{
					WAIT(0);
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

					// расчёт полоски Хаоса тут
					GENERATE_RANDOM_INT_IN_RANGE( 1, 20, &random);
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					if (!IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0))
					{
						if (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 1))
						{
							wanted = 2;
						}
						else if (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 2))
						{
							wanted = 3;
						}
						else if (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 3))
						{
							wanted = 4;
						}
						else
						{
							wanted = 5;
						}
					}
					else
					{
						wanted = 1;
					}
					if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_ZOMBIEB)) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_BOBBER)))
					{
						bike_in = 2;
					}
					else
					{
						bike_in = 1;
					}


					if (TIMERB() > 1000)
					{
						if (IS_EXPLOSION_IN_SPHERE(-1, PlayX, PlayY, PlayZ, 55))
						{
							shkala += 10*(wanted*bike_in);
							shkala += random;
							SETTIMERB( 0 );
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
						}
					}
					if (TIMERB() > 2500)
					{
						if (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PlayX-12, PlayY-12, PlayX+12, PlayY+12, 0))//проверка Игрок начал пальбу на старте
						{
							shkala += 5.5*(wanted*bike_in);
							shkala += random;
							SETTIMERB( 0 );
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
						}
					}

					// -------------------------- Полоска --------------------------
					DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );
					DRAW_SPRITE( 0, 0.915054, 0.74213, 0.059166, 0.014, 0.0, 27, 89, 130, 255 );// рисуем фоновую текстуру.
					if (shkala > 901)
					{
						shkalaH1 = 900;
					}
					else
					{
						shkalaH1 = shkala-100;
					}
					
					shkalaH2 = HUD_w/1000;
					shkalaH3 = shkalaH2*shkalaH1;
					shkalaHUD_y1 = HUD_w-shkalaH3;
					shkalaHUD_y2 = shkalaHUD_y1/2;
					shkalaHUD_y3 = HUD_x-shkalaHUD_y2;
					DRAW_SPRITE( 0, shkalaHUD_y3, 0.74213, shkalaH3, 0.014, 0.0, 97, 194, 247, 255 );// рисуем фоновую текстуру.

					SET_TEXT_COLOUR(95, 195, 247, 255);
					SET_TEXT_SCALE(0.156, 0.267);
					SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
					DISPLAY_TEXT(0.78815097, 0.73564852, "BM2_1"); //CHAOSMETER:
					//DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.66954074, "CP_TIME_NOZERO", shkala);// секунды

					if (shkala > 899)
					{
						skip = 2;
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if ((time_m == 0) && (time_s == 0))
					{
						PRINT_STRING_IN_STRING("string", "BM2_4", 5000, 1);//~r~You failed to fill the Chaos Meter in time!
						skip = 1;// переменная пропуска
						break;
					}
				}

				// зачещаем скрипт 

				if (sound == 1)
				{
					STOP_STREAM();
					ENABLE_FRONTEND_RADIO();
				}

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( timer );
				REMOVE_TXD( textur );

				REMOVE_PICKUP(sweap_1);// выгружаем биту

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_BIKE_2" );//Messing with the Man
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(2000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +2000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 2000);
					G_BIKE = 3;
					autosave = 1;
				}

				G_ONMISSION = 0;
			}
		}
//============================== Hog Tied ======================================
		else if ((G_ONMISSION == 0) && (G_BIKE == 3))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-164.663, 1185.16, 4.96332, &bike_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(bike_ico, BLIP_DATE);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(bike_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(bike_ico, "LG_03");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( -164.663, 1185.16, 4.96332, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -164.663, 1185.16, 4.96332, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("BIKE_3", 15000, CUTSCENE_BIKER);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-609.723, 658.861, 9.908, 279.440);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре

				Car car1, car2, car3, car4;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20;
				Pickup sweap_1, aid_1;
				int dm, cdm;
				Object fix_1, fix_2;
				Cam camera;

				blip_on = 0;
				skip = 0;
				hate = 0;
				shoot = 0;
				PointN = 0;
				Ped1_c = 0;
				Ped4_c = 0;
				Ped5_c = 0;
				Ped6_c = 0;
				Ped7_c = 0;
				Ped8_c = 0;
				Ped9_c = 0;
				Ped10_c = 0;
				Ped11_c = 0;
				Ped12_c = 0;
				siren = 0;

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
				CLEAR_WANTED_LEVEL(GetPlayerIndex());
				#if !defined SCRIPTED_CUTSCENES_BEFORE_ACTUAL_CUTSCENES
				DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}
				#endif

				SET_CHAR_COORDINATES(GetPlayerPed(), -164.834, 1186.85, 5.19596);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 0.0);
				SET_MAX_WANTED_LEVEL(0);
				
				uint hour, minute, weather;
				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(19, 30);//устанавливаем время

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "BIKE_2", 6 ); // загружаем субтитры из *.GTX
																	
							
				START_CUTSCENE_NOW("bike_2");
		
									
				while (!HAS_CUTSCENE_LOADED())
				{
					WAIT(0);
				}

				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED())
				{
					WAIT(0);
				}

				if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
				{
					DO_SCREEN_FADE_IN(0);
				}

				FORCE_WEATHER_NOW( weather );//устанавливаем погода
				RELEASE_WEATHER();
				FORWARD_TO_TIME_OF_DAY(hour, minute);//устанавливаем время
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				PRINT_STRING_IN_STRING("string", "BM3_1", 3500, 1);//~g~A local gang has stolen Mitch Baker's Angel. Get it back!
				SetTime(3500);
				PRINT_STRING_IN_STRING("string", "BM3_6", 3500, 1);//~g~They are holed up behind Ammu-Nation in the Downtown area.
				SetTime(3500);

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
				DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
				while (true)
				{
					if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
					{
						break;
					}
					WAIT( 0 );
				}

				DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, -240.539, 1676.1, 11.9703 ); // куда смотрит камера
				SET_CAM_POS			( camera, -254.179, 1640.7, 9.53429 );//расположение камеры
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_CAM_FOV( camera, 45.0 );
				SET_WIDESCREEN_BORDERS( 1 );

				PRINT_STRING_IN_STRING("string", "BM3_7", 4000, 1);//~g~You will need a fast bike to gain access to the roof.
				SetTime(4000);

				POINT_CAM_AT_COORD	( camera, -239.924, 1695.11, 21.442 ); // куда смотрит камера
				SET_CAM_POS			( camera, -251.808, 1672.72, 25.3362 );//расположение камеры
				PRINT_STRING_IN_STRING("string", "BM3_8", 4000, 1);//~g~Use the bike to jump from these stairs to the roof on the far side of the road.
				SetTime(4000);

				DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
				while (true)
				{
					if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
					{
						break;
					}
					WAIT( 0 );
				}

				DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

				//удяляем камеру тут
				SET_CAM_BEHIND_PED( GetPlayerPed() );
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				DESTROY_CAM( camera );
				SET_WIDESCREEN_BORDERS( 0 );
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				uint CarM1 = MODEL_ZOMBIEB; // Мопед
				uint CarM2 = MODEL_BURRITO2; // Фургон
				uint PedM1 = MODEL_M_Y_GIRI_LO_01;// охранник 1
				uint PedM2 = MODEL_M_Y_GIRI_LO_02;// охранник 2
				uint PedM3 = MODEL_M_Y_GALB_LO_01;// Байкер

				uint stairs_1 = stairs_fix_1;
				uint stairs_2 = stairs_fix_2;
				uint AudID1, AudID2, AudID3;

				LOAD_CHAR_DECISION_MAKER(2, &dm);
				LOAD_COMBAT_DECISION_MAKER(3, &cdm);

				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				//создаём пушку и аптечку
				CREATE_PICKUP_ROTATE(w_uzi, 3, 60, -162.254, 1180.55, 6.80878, -90.0, 0.0, 0.0, &sweap_1);// даём винтовку
				CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -270.407,1824.91,6.61801, -90.0, 0.0, -70.0, &aid_1);//Аптека

				REQUEST_MODEL(stairs_1);
				while (!HAS_MODEL_LOADED(stairs_1)) WAIT(0);
				REQUEST_MODEL(stairs_2);
				while (!HAS_MODEL_LOADED(stairs_2)) WAIT(0);

				CREATE_OBJECT_NO_OFFSET(stairs_1, -241.302, 1679.995, 13.4258, &fix_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(stairs_2, -323.301, 1815.471, 7.60105, &fix_2, TRUE);

				SET_OBJECT_DYNAMIC(fix_1, 0);
				SET_OBJECT_DYNAMIC(fix_2, 0);
				SET_OBJECT_INVINCIBLE(fix_1, 1);
				SET_OBJECT_INVINCIBLE(fix_2, 1);
				FREEZE_OBJECT_POSITION(fix_1, 1);
				FREEZE_OBJECT_POSITION(fix_2, 1);

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(0);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(0);
				REQUEST_MODEL(PedM1);//  Бос банды Акул
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Банда акул
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// Банда акул
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало

				CREATE_CAR(CarM1, -267.195, 1832.37, 6.26482, &car1, 1);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				CREATE_CAR(CarM2, 294.641, -787.452, 5.03766, &car2, 1);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				CREATE_CAR(CarM2, 290.701, -787.452, 5.03766, &car3, 1);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				CREATE_CAR(CarM2, 286.762, -787.452, 5.03766, &car4, 1);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				SET_CAR_HEADING(car1, 180.0);//градус поворота машины
				TURN_OFF_VEHICLE_EXTRA( car1, 9, 0 );//активируем внешний вид ""

				CREATE_CHAR (26, PedM2, -226.221, 1743.44, 18.0789, &ped1, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM3, 290.701, -778.676, 5.03766, &ped2, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, -328.247, 1781.57, 19.1239, &ped3, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах
				CREATE_CHAR (26, PedM1, -271.181, 1743.67, 18.0789, &ped4, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, -290.408, 1786.91, 5.75737, &ped5, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, -275.841, 1820.75, 5.75737, &ped6, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM1, -292.656, 1823.66, 5.75737, &ped7, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, -295.768, 1783.25, 5.75737, &ped8, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, -257.248, 1823.81, 5.75737, &ped9, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM1, -257.322, 1787.07, 5.75737, &ped10, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM1, -316.977, 1781.46, 5.75737, &ped11, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, -293.561, 1778.59, 5.75737, &ped12, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах
				CREATE_CHAR (26, PedM1, -269.625, 1835.11, 5.91157, &ped13, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM1, -270.427, 1832.56, 5.91157, &ped14, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM1, &ped15);// 
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM2, &ped16);// 
				CREATE_CHAR_INSIDE_CAR(car4, 1, PedM1, &ped17);// 
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM2, 0, &ped18);// 
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM1, 0, &ped19);// 
				CREATE_CHAR_AS_PASSENGER(car4, 1, PedM2, 0, &ped20);// 
				
				SET_CHAR_HEADING(ped2, 130.0);
				SET_CHAR_HEADING(ped3, -70.0);
				SET_CHAR_HEADING(ped13, -160.0);
				SET_CHAR_HEADING(ped14, -115.0);

				UpdateWeaponOfPed(ped1, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped3, WEAPON_SNIPERRIFLE);
				UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped13, WEAPON_BASEBALLBAT);
				UpdateWeaponOfPed(ped14, WEAPON_BASEBALLBAT);
				UpdateWeaponOfPed(ped15, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped16, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped17, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped18, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped19, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped20, WEAPON_EPISODIC_12);

				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_SNIPERRIFLE, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_BASEBALLBAT, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_BASEBALLBAT, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_EPISODIC_12, TRUE);

				SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped16, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped17, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped18, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped19, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped20, 5);

				SET_CHAR_RELATIONSHIP(ped1, 5, 0);
				SET_CHAR_RELATIONSHIP(ped3, 5, 0);
				SET_CHAR_RELATIONSHIP(ped4, 5, 0);
				SET_CHAR_RELATIONSHIP(ped5, 5, 0);
				SET_CHAR_RELATIONSHIP(ped6, 5, 0);
				SET_CHAR_RELATIONSHIP(ped7, 5, 0);
				SET_CHAR_RELATIONSHIP(ped8, 5, 0);
				SET_CHAR_RELATIONSHIP(ped9, 5, 0);
				SET_CHAR_RELATIONSHIP(ped10, 5, 0);
				SET_CHAR_RELATIONSHIP(ped11, 5, 0);
				SET_CHAR_RELATIONSHIP(ped12, 5, 0);
				SET_CHAR_RELATIONSHIP(ped15, 5, 0);
				SET_CHAR_RELATIONSHIP(ped16, 5, 0);
				SET_CHAR_RELATIONSHIP(ped17, 5, 0);
				SET_CHAR_RELATIONSHIP(ped18, 5, 0);
				SET_CHAR_RELATIONSHIP(ped19, 5, 0);
				SET_CHAR_RELATIONSHIP(ped20, 5, 0);

				SET_SENSE_RANGE(ped1, 45.0);
				SET_SENSE_RANGE(ped3, 45.0);
				SET_SENSE_RANGE(ped4, 35.0);
				SET_SENSE_RANGE(ped5, 35.0);
				SET_SENSE_RANGE(ped6, 35.0);
				SET_SENSE_RANGE(ped7, 35.0);
				SET_SENSE_RANGE(ped8, 35.0);
				SET_SENSE_RANGE(ped9, 50.0);
				SET_SENSE_RANGE(ped10, 50.0);
				SET_SENSE_RANGE(ped11, 50.0);
				SET_SENSE_RANGE(ped12, 50.0);
				SET_SENSE_RANGE(ped15, 1.0);
				SET_SENSE_RANGE(ped16, 1.0);
				SET_SENSE_RANGE(ped17, 1.0);
				SET_SENSE_RANGE(ped18, 1.0);
				SET_SENSE_RANGE(ped19, 1.0);
				SET_SENSE_RANGE(ped20, 1.0);

				SET_CHAR_WILL_USE_COVER(ped1, 1);
				SET_CHAR_WILL_USE_COVER(ped3, 1);
				SET_CHAR_WILL_USE_COVER(ped4, 1);
				SET_CHAR_WILL_USE_COVER(ped5, 1);
				SET_CHAR_WILL_USE_COVER(ped6, 1);
				SET_CHAR_WILL_USE_COVER(ped7, 1);
				SET_CHAR_WILL_USE_COVER(ped8, 1);
				SET_CHAR_WILL_USE_COVER(ped9, 1);
				SET_CHAR_WILL_USE_COVER(ped10, 1);
				SET_CHAR_WILL_USE_COVER(ped11, 1);
				SET_CHAR_WILL_USE_COVER(ped12, 1);
				SET_CHAR_WILL_USE_COVER(ped15, 1);
				SET_CHAR_WILL_USE_COVER(ped16, 1);
				SET_CHAR_WILL_USE_COVER(ped17, 1);
				SET_CHAR_WILL_USE_COVER(ped18, 1);
				SET_CHAR_WILL_USE_COVER(ped19, 1);
				SET_CHAR_WILL_USE_COVER(ped20, 1);

				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, 1);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, 1);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, 1);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, 1);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, 1);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, 1);

				ADD_BLIP_FOR_CAR(car1, &bike_ico);
				CHANGE_BLIP_SPRITE(bike_ico, BLIP_DESTINATION);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(bike_ico, 19);   //цвет иконка на радаре (0=белая)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(bike_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""
				SetTime(1000);

				//враги патрулирют лодочную мастерскую
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, -225.389, 1774.36, 18.3355, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped4, -310.589, 1741.64, 18.3355, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, -259.054, 1786.98, 5.75737, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, -275.416, 1793.91, 5.75737, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, -293.294, 1787.15, 5.75737, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped8, -295.029, 1821.56, 5.75737, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped9, -289.929, 1820.41, 5.75737, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped10, -257.182, 1822.16, 5.75737, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped11, -317.976, 1820.08, 5.75737, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped12, -322.805, 1778.74, 5.75737, 2, -2, 3.5);

				while (true)
				{
					WAIT( 0 );
					// патрули
					if (Ped1_c == 0)
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -225.389, 1774.36, 18.3355, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped1_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, -226.22, 1743.44, 18.0789, 2, -2, 3.5);
						}
					}
					else if (Ped1_c == 1)
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -226.22, 1743.44, 18.0789, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped1_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, -225.389, 1774.36, 18.3355, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped4_c == 0)
					{
						GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -310.589, 1741.64, 18.3355, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped4_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped4, -271.18, 1743.67, 18.0789, 2, -2, 3.5);
						}
					}
					else if (Ped4_c == 1)
					{
						GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -271.18, 1743.67, 18.0789, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped4_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped4, -310.589, 1741.64, 18.3355, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped5_c == 0)
					{
						GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -259.054, 1786.98, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped5_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, -290.408, 1786.9, 5.75737, 2, -2, 3.5);
						}
					}
					else if (Ped5_c == 1)
					{
						GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -290.408, 1786.9, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped5_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, -259.054, 1786.98, 5.75737, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped6_c == 0)
					{
						GET_CHAR_COORDINATES(ped6,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -275.416, 1793.9, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped6_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, -275.84, 1820.75, 5.75737, 2, -2, 3.5);
						}
					}
					else if (Ped6_c == 1)
					{
						GET_CHAR_COORDINATES(ped6,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -275.84, 1820.75, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped6_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, -275.416, 1793.9, 5.75737, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped7_c == 0)
					{
						GET_CHAR_COORDINATES(ped7,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -293.294, 1787.15, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped7_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, -292.656, 1823.66, 5.75737, 2, -2, 3.5);
						}
					}
					else if (Ped7_c == 1)
					{
						GET_CHAR_COORDINATES(ped7,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -292.656, 1823.66, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped7_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, -293.294, 1787.15, 5.75737, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped8_c == 0)
					{
						GET_CHAR_COORDINATES(ped8,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -295.029, 1821.56, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped8_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped8, -295.768, 1783.25, 5.75737, 2, -2, 3.5);
						}
					}
					else if (Ped8_c == 1)
					{
						GET_CHAR_COORDINATES(ped8,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -295.768, 1783.25, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped8_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped8, -295.029, 1821.56, 5.75737, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped9_c == 0)
					{
						GET_CHAR_COORDINATES(ped9,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -289.929, 1820.4, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped9_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped9, -257.248, 1823.81, 5.75737, 2, -2, 3.5);
						}
					}
					else if (Ped9_c == 1)
					{
						GET_CHAR_COORDINATES(ped9,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -257.248, 1823.81, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped9_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped9, -289.929, 1820.4, 5.75737, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped10_c == 0)
					{
						GET_CHAR_COORDINATES(ped10,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -257.182, 1822.16, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped10_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped10, -257.322, 1787.07, 5.75737, 2, -2, 3.5);
						}
					}
					else if (Ped10_c == 1)
					{
						GET_CHAR_COORDINATES(ped10,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -257.322, 1787.07, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped10_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped10, -257.182, 1822.16, 5.75737, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped11_c == 0)
					{
						GET_CHAR_COORDINATES(ped11,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -317.976, 1820.08, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped11_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped11, -316.977, 1781.46, 5.75737, 2, -2, 3.5);
						}
					}
					else if (Ped11_c == 1)
					{
						GET_CHAR_COORDINATES(ped11,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -316.977, 1781.46, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped11_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped11, -317.976, 1820.08, 5.75737, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped12_c == 0)
					{
						GET_CHAR_COORDINATES(ped12,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -322.805, 1778.74, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped12_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped12, -293.56, 1778.59, 5.75737, 2, -2, 3.5);
						}
					}
					else if (Ped12_c == 1)
					{
						GET_CHAR_COORDINATES(ped12,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -293.56, 1778.59, 5.75737, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped12_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped12, -322.805, 1778.74, 5.75737, 2, -2, 3.5);
						}
					}
					if (shoot == 0)
					{
						if ((IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), -223.566, 1730.804, -312.994, 1804.611, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped1, -223.566, 1730.804, -312.994, 1804.611, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped4, -223.566, 1730.804, -312.994, 1804.611, 0)))
						{
							SET_SENSE_RANGE(ped1, 0.01);
							SET_SENSE_RANGE(ped4, 0.01);
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, -261.243, 1746.69, 17.8387, 3, -2, 2.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped4, -261.243, 1746.69, 17.8387, 3, -2, 2.5);
							shoot = 1;
						}
					}
					else if (shoot == 1)
					{
						if ((IS_CHAR_IN_AREA_3D( ped1, -259.743, 1745.191, 17.839, -262.743, 1748.191, 22.839, 0 )) || (IS_CHAR_IN_AREA_3D( ped4, -259.743, 1745.191, 17.839, -262.743, 1748.191, 22.839, 0 )))
						{
							shoot = 2;
							SET_SENSE_RANGE(ped1, 55.01);
							SET_SENSE_RANGE(ped4, 55.01);

							// аудио тут
							while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/RB4_MUSEUM_PIECE" )))
							{
								 WAIT(0);
							}
							AudID1 = GET_SOUND_ID();
							PLAY_SOUND_FROM_POSITION(AudID1, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", -259.38, 1747.82, 19.09);
							AudID2 = GET_SOUND_ID();
							PLAY_SOUND_FROM_POSITION(AudID2, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", -298.75, 1793.15, 6.73);
							AudID3 = GET_SOUND_ID();
							PLAY_SOUND_FROM_POSITION(AudID3, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", -262.58, 1829.72, 6.73);

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "INTRUDE", 5000, 1);//~g~You've been spotted!
							siren = 1;
						}
					}
					
					// Рабочие атакуют игрока тут
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -260.027, 1823.191, 5.445, -275.104, 1838.246, 10.445, 0 )) && (hate == 0))
					{
						SET_SENSE_RANGE(ped13, 50.0);
						SET_CHAR_DECISION_MAKER(ped13, dm);
						SET_COMBAT_DECISION_MAKER(ped13, cdm);
						SET_CHAR_KEEP_TASK(ped13, 1);
						TASK_COMBAT(ped13, GetPlayerPed());
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, 0);

						SET_SENSE_RANGE(ped14, 50.0);
						SET_CHAR_DECISION_MAKER(ped14, dm);
						SET_COMBAT_DECISION_MAKER(ped14, cdm);
						SET_CHAR_KEEP_TASK(ped14, 1);
						TASK_COMBAT(ped14, GetPlayerPed());
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, 0);
						hate = 1;
					}

					if ((IS_CHAR_DEAD(ped7)) || (IS_CHAR_INJURED(ped7)))
					{
						DELETE_CHAR(&ped7);//удаляем модель педа
						//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет
						CREATE_CHAR (26, PedM1, -300.136, 1796.01, 5.75737, &ped7, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
						SET_CHAR_HEADING(ped7, -95.0);
						UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_12);
						SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_12, TRUE);
						SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
						SET_CHAR_RELATIONSHIP(ped7, 5, 0);
						SET_SENSE_RANGE(ped7, 65.0);
						SET_CHAR_WILL_USE_COVER(ped7, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
						TASK_COMBAT(ped7, GetPlayerPed());
						Ped7_c = 2;
					}
					if ((IS_CHAR_DEAD(ped10)) || (IS_CHAR_INJURED(ped10)))
					{
						DELETE_CHAR(&ped10);//удаляем модель педа
						//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped10);//выгружаем модель педа(в последствии пед изчезнет
						CREATE_CHAR (26, PedM1, -258.113, 1831.5, 5.75737, &ped10, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
						SET_CHAR_HEADING(ped10, 180.0);
						UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_12);
						SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_12, TRUE);
						SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
						SET_CHAR_RELATIONSHIP(ped10, 5, 0);
						SET_SENSE_RANGE(ped10, 65.0);
						SET_CHAR_WILL_USE_COVER(ped10, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
						TASK_COMBAT(ped10, GetPlayerPed());
						Ped10_c = 2;
					}

					//чекпойнт сброса лодки
					if ((!IS_CAR_IN_AREA_3D(car1, -248.25, 1749.447, 3.467, -314.344, 1837.654, 23.467, 0)) && (!IS_CAR_IN_AREA_3D(car1, -309.474, 1745.853, 3.467, -334.59, 1821.711, 23.467, 0)))
					{
						SET_CHAR_COORDINATES(ped15, -309.266, 1841.41, 6.26482);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						SET_CHAR_COORDINATES(ped16, -259.518, 1856.37, 6.26482);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						SET_CHAR_COORDINATES(ped17, -362.808, 1909.42, 6.26482);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						SET_CHAR_HEADING(ped15, 95.0);
						SET_CHAR_HEADING(ped16, 95.0);
						SET_CHAR_HEADING(ped17, -90.0);
						PointN = 0;
						break;
					}
					if (IS_CHAR_IN_CAR(GetPlayerPed(), car1))
					{
						if (PointN == 0)
						{
							REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_COORD(-170.075, 1187.86, 4.90098, &bike_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(bike_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(bike_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(bike_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(bike_ico, "NE_POINT");//иконка на радаре называние в истории карты ""

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BM3_3", 5000, 1);//~g~Get the bike back to the bar!
							PointN = 1;
						}
					}
					else
					{
						if (PointN == 1)
						{
							REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_CAR(car1, &bike_ico);
							CHANGE_BLIP_SPRITE(bike_ico, BLIP_DESTINATION);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(bike_ico, 19);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(bike_ico, "MO_TARGET");//иконка на радаре называние в истории карты "ЛОДКА"

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BM3_4", 5000, 1);//~g~Get on the bike!
							PointN = 0;
						}
					}

					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
					{
						skip = 1;
						break;
					}
					else if (IS_CAR_DEAD(car1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "BM3_2", 5000, 1);//~r~You were supposed to bring the bike back, not destroy it!
						skip = 1;
						break;
					}
				}

				if (skip == 0)
				{
					//агрим новых врагов
					SET_SENSE_RANGE(ped15, 25.0);
					SET_SENSE_RANGE(ped16, 25.0);
					SET_SENSE_RANGE(ped17, 25.0);
					SET_SENSE_RANGE(ped18, 25.0);
					SET_SENSE_RANGE(ped19, 25.0);
					SET_SENSE_RANGE(ped20, 25.0);
					TASK_COMBAT(ped15, GetPlayerPed());// агрим охраника
					TASK_COMBAT(ped16, GetPlayerPed());// агрим охраника
					TASK_COMBAT(ped17, GetPlayerPed());// агрим охраника
					TASK_COMBAT(ped18, GetPlayerPed());// агрим охраника
					TASK_COMBAT(ped19, GetPlayerPed());// агрим охраника
					TASK_COMBAT(ped20, GetPlayerPed());// агрим охраника
					PointN = 0;

					while (true)
					{
						WAIT( 0 );
						if (IS_CHAR_IN_CAR(GetPlayerPed(), car1))
						{
							if (PointN == 1)
							{
								REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_COORD(-170.075, 1187.86, 4.90098, &bike_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(bike_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(bike_ico, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_SCALE(bike_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(bike_ico, "NE_POINT");//иконка на радаре называние в истории карты ""
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "BM3_3", 5000, 1);//~g~Get the bike back to the bar!
								PointN = 0;
							}
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							DRAW_CHECKPOINT( -170.075, 1187.86, 4.90098, 4.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -170.075, 1187.86, 4.90098, &PlayR);//проверка "игрок на координатах"
							if (PlayR < 5.5)
							{
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, -169.511, 1187.54, 5.30201 ); // куда смотрит камера
								SET_CAM_POS			( camera, -167.122, 1198.68, 8.9424 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );
								SetTime(500);
								TASK_LEAVE_CAR(GetPlayerPed(), car1);// томми слазит с байка
								
								SetTime(1500);
								SET_CHAR_COORDINATES(ped2, -162.992, 1182.32, 5.87116);// перемещаем игрока
								SET_CHAR_HEADING(ped2, 60.0);
								SETTIMERA(0);

								TASK_ENTER_CAR_AS_DRIVER(ped2, car1, 10000);// байкер содится на байк
								while (true)
								{
									WAIT( 0 );
									if ((IS_CHAR_SITTING_IN_ANY_CAR(ped2)) || (TIMERA() > 8000))
									{
										break;
									}
								}
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car1, -228.428, 1141.56, 4.90098, 4, 50.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								SetTime(3000);

								//удяляем камеру тут
								SET_CAM_BEHIND_PED( GetPlayerPed() );
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								DESTROY_CAM( camera );
								SET_WIDESCREEN_BORDERS( 0 );
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
								skip = 2;
								break;
							}
						}
						else
						{
							if (PointN == 0)
							{
								REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CAR(car1, &bike_ico);
								CHANGE_BLIP_SPRITE(bike_ico, BLIP_DESTINATION);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(bike_ico, 19);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(bike_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "BM3_4", 5000, 1);//~g~Get on the bike!
								PointN = 1;
							}
						}

						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						else if (IS_CAR_DEAD(car1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BM3_2", 5000, 1);//~r~You were supposed to bring the bike back, not destroy it!
							skip = 1;
							break;
						}
					}
				}

				// завершение миссии
				WAIT( 100 );
				SET_MAX_WANTED_LEVEL(6);

				if (siren == 1)
				{
					STOP_SOUND(AudID1);
					STOP_SOUND(AudID2);
					STOP_SOUND(AudID3);
					RELEASE_SOUND_ID(AudID1);
					RELEASE_SOUND_ID(AudID2);
					RELEASE_SOUND_ID(AudID3);
					AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED();
				}
				REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре
				REMOVE_PICKUP(sweap_1);// выгружаем оружие
				REMOVE_PICKUP(aid_1);// выгружаем оружие
				
				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(stairs_1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(stairs_2);//выгружаем модель

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
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped17);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped18);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped19);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped20);//выгружаем модель педа(в последствии пед изчезнет

				// выгружаем из памяти транспорт
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)

				// удаляем объекты
				DELETE_OBJECT(&fix_1);
				DELETE_OBJECT(&fix_2);

				// выгружаем стропы
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&fix_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&fix_2);


				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_BIKE_3" );//Hog Tied
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(4000, "missionpassed", "CASH");
					CLEAR_WANTED_LEVEL(GetPlayerIndex());
					ADD_SCORE( GetPlayerIndex(), +4000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 4000);
					G_BIKE = 4;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
		else if ((G_ONMISSION == 0) && (G_BIKE == 4))
		{
			break;
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(bike_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}
	}
}
void main(void)
{
	//THIS_SCRIPT_SHOULD_BE_SAVED();
	if (G_BIKE < 4)
	{
		bikers();
	}
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
