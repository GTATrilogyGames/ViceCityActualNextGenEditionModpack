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
float PlayX, PlayY, PlayZ, PlayR, PedX, PedY, PedZ, PedR, blip_on, skip, cam_on, sprint, PointX, PointY, PointZ, PointN, car_speed, hate, textur, res, res_on, play, sound, autosave;
float explo2, explo3, explo4, explo5, explo6, explo7, explo8, explo9, carHUD_x, carHUD_w, carH1, carH2, carH3, carHUD_y1, carHUD_y2, carHUD_y3, text1, time_sub, del_car, in_car, play_Speech;
float Ped1_c, Ped4_c, Ped5_c, Ped6_c, Ped7_c, Ped8_c, Ped9_c, Ped10_c, Ped11_c, Ped12_c, Health, stalking, stalkerR;

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
void baron_diaz(void)
{
	blip_on = 0;
	autosave = 0;
	Blip diaz_ico;
	WAIT(3000);
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
//============================== The Chase ======================================
		if ((G_ONMISSION == 0) && (G_DIAZ == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(55.627, -13.084, 11.174, &diaz_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DWAYNE);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(diaz_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "LG_05");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 55.627, -13.084, 11.174, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 55.627, -13.084, 11.174, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("COK_1", 15000, CUTSCENE_BARON);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-288.2, -487.5, 9.8, 275.0);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
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

				SET_CHAR_COORDINATES(GetPlayerPed(), 54.81, -8.80, 12.028);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 358.0);
				
				//------------ катсцена тут ----------------
				LOAD_ADDITIONAL_TEXT( "COK_1", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("cok_1");
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

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				ADD_BLIP_FOR_COORD(814.0, 781.2, 4.761, &diaz_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(diaz_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(diaz_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(diaz_ico, 0.6); // масштаб иконки на радаре

				SetTime(1000);
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R14_XA", "", 0, 0);//
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "NE_POINT");//иконка на радаре называние в истории карты ""
				PRINT_STRING_IN_STRING("string", "COK1_10", 5000, 1);//~g~Go to the thief's house and find out where he's stashing the money.
				SetTime(2000);

				Car car1, car2;
				Ped ped1, ped2;
				Object barrel_1, barrel_2;
				Cam camera;

				uint PedM1 = MODEL_IG_RAY_BOCCINO;// Бос банды Акул
				uint PedM2 = MODEL_M_Y_GIRI_LO_01;// Банда акул
				uint CarM1 = MODEL_HABANERO; // транспорт банды Акул
				uint CarM2 = MODEL_FAGGIO; // скутер
				uint barrel = barrel4; // бочка
				uint car_heal1;
				skip = 0;
				sprint = 0;
				hate = 0;

				REQUEST_MODEL(barrel);
				while (!HAS_MODEL_LOADED(barrel)) WAIT(0);
				CREATE_OBJECT_NO_OFFSET(barrel, 780.781, 950.424, 16.07, &barrel_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 784.986, 949.192, 16.07, &barrel_2, TRUE);

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(0);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);
				REQUEST_MODEL(PedM1);//  Бос банды Акул
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Банда акул
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало

				CREATE_CAR(CarM1, 286.232, -791.79, 5.445, &car1, TRUE);
				LOCK_CAR_DOORS(car1, 3); //блокируем двери автомобиля для игрока
				CREATE_CAR(CarM2, 289.629, -791.79, 5.445, &car2, TRUE);
				SET_CAR_ENGINE_ON(car2, 1, 1);
				CREATE_CHAR (26, PedM1, 286.386, -785.672, 5.06, &ped1, TRUE);//  Бос банды Акул
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM2, &ped2);//создаём педа за рулём автомобиля

				//грузим анимацию
				REQUEST_ANIMS( "ped" );//загружаем файл с анимацией
				while (!HAVE_ANIMS_LOADED( "ped" )) WAIT(0);

				// часть 1
				while (TRUE)
				{
					WAIT(0);
					DRAW_CHECKPOINT( 814.0, 781.2, 4.761, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 814.0, 781.2, 4.761, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

						//ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 825.686, 785.054, 11.536 ); // куда смотрит камера
						SET_CAM_POS			( camera, 815.734, 776.458, 7.953 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						PRINT_STRING_IN_STRING("string", "COK1_11", 5000, 1);//~g~Have a look through his window.
						SetTime(2000);

						// убираем камеру
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// разморозить игрока

						REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
						ADD_BLIP_FOR_COORD(824.75, 784.14, 9.398, &diaz_ico);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(diaz_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
						CHANGE_BLIP_COLOUR(diaz_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(diaz_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "NE_POINT");//иконка на радаре называние в истории карты "магазин одежды"
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
					{
						skip = 1;
						break;
					}
				}

				// часть 2
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						DRAW_CHECKPOINT( 824.75, 784.14, 9.398, 1.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 824.75, 784.14, 9.398, &PlayR);//проверка "игрок на координатах"
						
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							SET_CHAR_VISIBLE(GetPlayerPed(), 0); //прозрачный игрок
							
							//ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 827.4, 785.5, 11.2 ); // куда смотрит камера
							SET_CAM_POS			( camera, 823.88, 783.774, 11.633 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							SET_CHAR_COORDINATES(ped1, 804.395, 789.414, 13.762);// возвращаем игрока на исходную позицию рядом с чекпойнтом
							SET_CHAR_HEADING(ped1, -115.5);


							// Движение камеры
							PedX = 827.4;
							PedY = 785.5;
							PedZ = 11.2;
							SetTime(200);
							cam_on = 1;
							while (TRUE)
							{
								WAIT(15);
								if (cam_on == 1)
								{
									if (PedY > 783.4)
									{
										PedY -= 0.02;
									}
									else
									{
										SetTime(200);
										cam_on = 2;
									}
								}
								else if (cam_on == 2)
								{
									if (PedY < 785.5)
									{
										PedY += 0.02;
									}
									else
									{
										SetTime(200);
										cam_on = 3;
									}
								}
								else if (cam_on == 3)
								{
									if (PedZ < 13.7)
									{
										PedZ += 0.02;
									}
									if (PedX > 817.0)
									{
										PedX -= 0.1;
									}
									else
									{
										break;
									}
								}
								POINT_CAM_AT_COORD	( camera, PedX, PedY, PedZ ); // куда смотрит камера
							}

							SetTime(200);
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_BC", "COK1_1", 0, 0);//Ooh shit!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 788.488, 811.915, 18.537, 3, -2, 5.5);// пед убегает
							SetTime(1000);

							// убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );

							SET_CHAR_VISIBLE(GetPlayerPed(), 1); //видимый игрок
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// разморозить игрока
							SET_CHAR_COORDINATES(ped1, 788.488, 811.915, 18.537);// возвращаем игрока на исходную позицию рядом с чекпойнтом
							SET_CHAR_HEADING(ped1, -115.5);
							UpdateWeaponOfPed(ped1, WEAPON_AK47);
							SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_AK47, TRUE);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COK1_7", 5000, 1);//~g~He's escaped to the roof, keep on his tail but don't kill him!
							
							ADD_BLIP_FOR_CHAR(ped1, &diaz_ico);
							CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DESTINATION);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(diaz_ico, 19);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "MO_TARGET");//иконка на радаре называние в истории карты "Цель"
							CHANGE_BLIP_SCALE(diaz_ico, 0.77999990); // масштаб иконки на радаре
							
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COK1_9", 5000, 1);//~r~You're supposed to follow him, not kill him!
							skip = 1;
							break;
						}
					}
				}

				// часть 3
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 807.305, 797.795, 17.545, &PlayR);//проверка "игрок на координатах"
						if ( PlayR < 2.5)
						{
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							TASK_AIM_GUN_AT_COORD(ped1, 807.587, 798.465, 16.937, 10000);

							//ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 806.667, 797.199, 19.072 ); // куда смотрит камера
							SET_CAM_POS			( camera, 785.186, 813.273, 19.431 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(GetPlayerPed(), 807.587, 798.465, 16.937, 3, -2, 2.0);// пед убегает
							SetTime(500);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "duck_cower", "ped", 2.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе

							SETTIMERB( 0 );
							while (TRUE)
							{
								WAIT(0);
								FIRE_PED_WEAPON(ped1, 807.587, 798.465, 17.937);// пед стрелет в ГГ
								if (TIMERB() > 500)
								{
									break;
								}
							}
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_BD", "COK1_4", 0, 0);//Loser.
							START_SCRIPT_CONVERSATION(1, 1);
							SetTime(1000);
							TASK_AIM_GUN_AT_COORD(ped1, PlayX, PlayY, PlayZ, 0);

							// убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// разморозить игрока
							SET_CHAR_COORDINATES(ped1, 785.256, 840.455, 13.381);// возвращаем игрока на исходную позицию рядом с чекпойнтом
							SET_CHAR_HEADING(ped1, 0.2);

							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 790.781, 944.749, 13.856, 3, -2, 2.5);// пед убегает
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COK1_9", 5000, 1);//~r~You're supposed to follow him, not kill him!
							skip = 1;
							break;
						}
						else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 739.717, 754.862, -0.1, 839.717, 1024.862, 50.0, 0 ))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "TEX1_5", 5000, 1);//~r~He got away!
							skip = 1;
							break;
						}
					}
				}

				// часть 4
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты педа в переменную

						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 20.5) && (sprint == 0))
						{
							// Томми начинсет устовать
							DISABLE_PLAYER_SPRINT(GetPlayerIndex(), 1);
							sprint = 1;
						}
						else if (( PlayR > 25.5) && (sprint == 1))
						{
							// Томми снова бодр
							DISABLE_PLAYER_SPRINT(GetPlayerIndex(), 0);
							sprint = 0;
						}

						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 785.749, 944.575, 13.049, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 15.5) || ( PedZ < 8 ))
						{
							if (PedZ < 8)
							{
								SET_CHAR_HEALTH(ped1, 1000);
								SET_CHAR_COORDINATES(GetPlayerPed(), 778.282, 938.726, 13.995);// возвращаем игрока на исходную позицию рядом с чекпойнтом
								SET_CHAR_HEADING(GetPlayerPed(), 1.07);
							}
							DISABLE_PLAYER_SPRINT(GetPlayerIndex(), 1);
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 795.194, 968.881, 12.856, 3, -2, 5.5);// пед убегает
							SET_CHAR_COORDINATES(ped1, 795.194, 968.881, 12.856);// возвращаем игрока на исходную позицию рядом с чекпойнтом
							SET_CHAR_HEADING(ped1, 154.437);
							TASK_AIM_GUN_AT_COORD(ped1, 780.781, 950.424, 15.583, 10000);

							//ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 783.905, 949.619, 15.957 ); // куда смотрит камера
							SET_CAM_POS			( camera, 796.036, 971.877, 14.195 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R2_BE", "COK1_2", 0, 0);//Too slow grandad!
							START_SCRIPT_CONVERSATION(1, 1);
							SetTime(500);

							SETTIMERB( 0 );
							while (TRUE)
							{
								WAIT(0);
								FIRE_PED_WEAPON(ped1, 784.986, 949.192, 16.583);// // пед стреляет в бочки
								if (TIMERB() > 500)
								{
									break;
								}
							}
							ADD_EXPLOSION( 780.781, 950.424, 15.583, 0, 1.50000000, 1, 0, 1.00000000 );
							ADD_EXPLOSION( 784.986, 949.192, 15.583, 0, 1.50000000, 1, 0, 1.00000000 );
							SET_OBJECT_COORDINATES(barrel_1, 0.1, 0.1, 0.1);
							SET_OBJECT_COORDINATES(barrel_2, 1.1, 1.1, 1.1);
							TASK_AIM_GUN_AT_COORD(ped1, PlayX, PlayY, PlayZ, 0);
							SetTime(800);

							// убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// разморозить игрока
							SetTime(500);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_BF", "COK1_5", 0, 0);//You better keep on running, asshole!
							START_SCRIPT_CONVERSATION(1, 1);

							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 806.724, 997.807, 14.466, 3, -2, 2.5);// пед убегает
							SET_CAR_COORDINATES(car1, 802.812, 1013.104, 6.216);
							SET_CAR_COORDINATES(car2, 812.142, 1008.045, 6.216);
							SET_CAR_HEADING(car1, -55.5);
							SET_CAR_HEADING(car2, -8.837);
							SetSpeech();
							SetTime(1000);
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COK1_9", 5000, 1);//~r~You're supposed to follow him, not kill him!
							skip = 1;
							break;
						}
						else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 739.717, 754.862, -0.1, 839.717, 1024.862, 50.0, 0 ))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "TEX1_5", 5000, 1);//~r~He got away!
							skip = 1;
							break;
						}
					}
				}

				// часть 5
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 806.724, 997.807, 14.466, &PedR);//проверка "игрок на координатах"
						if (( PedR < 5.5) || (PedZ < 8))
						{
							if (PedZ < 8)
							{
								SET_CHAR_HEALTH(ped1, 1000);
								SET_CHAR_COORDINATES(GetPlayerPed(), 806.724, 997.807, 14.466);// возвращаем игрока на исходную позицию рядом с чекпойнтом
								SET_CHAR_HEADING(GetPlayerPed(), 2.437);
							}
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							//ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 804.249, 1008.145, 6.969 ); // куда смотрит камера
							SET_CAM_POS			( camera, 816.963, 1015.829, 8.494 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							SET_CHAR_COORDINATES(ped1, 808.675, 1004.901, 8.837);// возвращаем игрока на исходную позицию рядом с чекпойнтом
							SET_CHAR_HEADING(GetPlayerPed(), 0.2);
							TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, 10000, 3);
							SHUT_CAR_DOOR(car1, 1);

							SETTIMERB( 0 );
							while (TRUE)
							{
								WAIT(0);
								if ((IS_CHAR_IN_CAR(ped1, car1)) || (TIMERB() > 5000))
								{
									break;
								}
							}
							// убираем камеру
							CHANGE_BLIP_SCALE(diaz_ico, 1.1); // масштаб иконки на радаре
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );

							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car1, 0);
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// разморозить игрока
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COK1_8", 5000, 1);//~g~Quick! Grab some wheels and follow him!
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COK1_9", 5000, 1);//~r~You're supposed to follow him, not kill him!
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_FATALLY_INJURED(ped2)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK1_D", 5000, 1);//~r~His driver is dead!
							skip = 1;
							break;
						}
					}
				}

				// часть 6
				if (skip == 0)
				{
					DISABLE_PLAYER_SPRINT(GetPlayerIndex(), 0);
					UpdateWeaponOfPed(ped1, WEAPON_MP5);
					SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_MP5, TRUE);
					PointX = 969.7484;
					PointY = 1013.461;
					PointZ = 5.062624;
					car_speed = 0; // скорость
					PointN = 1; // номер чекпойнта
					SET_MAX_WANTED_LEVEL(0);

					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car1, PointX, PointY, PointZ, 4, 10.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
					while(true)
					{
						WAIT(0);

						GET_CAR_HEALTH(car1, &car_heal1);
						if (( car_heal1 < 600) || (GET_ENGINE_HEALTH(car1) < 600) || (GET_PETROL_TANK_HEALTH(car1) < 600))
						{
							FIX_CAR(car1);
						}
						else if (!IS_CHAR_IN_CAR(ped1, car1))
						{
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car1, 0);
						}

						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, PointX, PointY, PointZ, &PedR);//проверка "игрок на координатах"
						if (( PedR < 55.5) && ( car_speed == 0))
						{
							car_speed = 1;
							if ((PointN == 11) || (PointN == 8) || (PointN == 7) || (PointN == 6))
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car1, PointX, PointY, PointZ, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
							else
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car1, PointX, PointY, PointZ, 4, 11.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
						}
						else if (( PedR < 15.0 ) && ( car_speed == 1 ))
						{
							car_speed = 2;
							PointN += 1;
						}
						else if ((car_speed == 2) && (PointN < 14))
						{
							if (PointN == 2 )
							{
								PointX = 995.9073;
								PointY = 1393.834;
								PointZ = 7.986374;
							}
							else if (PointN == 3 )
							{
								PointX = 930.639;
								PointY = 1614.154;
								PointZ = 11.62415;
							}
							else if (PointN == 4 )
							{
								PointX = 950.4051;
								PointY = 1795.558;
								PointZ = 10.66148;
							}
							else if (PointN == 5 )
							{
								PointX = 659.0934;
								PointY = 1794.603;
								PointZ = 11.18943;
							}
							else if (PointN == 6 )
							{
								PointX = 670.0879;
								PointY = 1755.52;
								PointZ = 11.32486;
							}
							else if (PointN == 7 )
							{
								PointX = 717.2022;
								PointY = 1729.146;
								PointZ = 11.81174;
							}
							else if (PointN == 8 )
							{
								PointX = 708.173;
								PointY = 1646.663;
								PointZ = 11.73535;
							}
							else if (PointN == 9 )
							{
								PointX = 749.6264;
								PointY = 1402.945;
								PointZ = 11.93876;
							}
							else if (PointN == 10 )
							{
								PointX = 853.9798;
								PointY = 1373.269;
								PointZ = 11.93876;
							}
							else if (PointN == 11 )
							{
								PointX = 830.0705;
								PointY = 1479.305;
								PointZ = 7.417959;
							}
							else if (PointN == 12 )
							{
								PointX = 473.9977;
								PointY = 1561.728;
								PointZ = 4.812687;
							}
							else if (PointN == 13 )
							{
								PointX = 470.554;
								PointY = 1618.824;
								PointZ = 8.705763;
							}
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car1, PointX, PointY, PointZ, 4, 35.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							car_speed = 0;
						}
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//проверка "игрок на координатах"

						if ( PlayR > 250)
						{
							PRINT_STRING_IN_STRING("string", "TEX1_5", 5000, 1);//~r~He got away!
							skip = 1;
							break;
						}
						else if (!IS_CHAR_SITTING_IN_ANY_CAR( ped2 ))
						{
							SET_CAR_COORDINATES(car1, PedX, PedY, PedZ+1);
							FIX_CAR(car1);
							WARP_CHAR_INTO_CAR(ped2, car1);
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car1, 0);
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car1, PointX, PointY, PointZ, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						}
						else if ((PlayR < 80) && (hate == 0) && (PointN > 1))
						{
							SET_CHAR_RELATIONSHIP_GROUP(ped1, 24);
							SET_CHAR_RELATIONSHIP(ped1, 5, 0);
							SET_SENSE_RANGE(ped1, 100.0);
							TASK_COMBAT(ped1, GetPlayerPed());// агрим педа
							hate = 1;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							PRINT_STRING_IN_STRING("string", "COK1_9", 5000, 1);//~r~You're supposed to follow him, not kill him!
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_FATALLY_INJURED(ped2)))//если пед мёртв или фатально ранен.
						{
							PRINT_STRING_IN_STRING("string", "NECOK1_D", 5000, 1);//~r~His driver is dead!
							skip = 1;
							break;
						}

						else if (( PedR < 15.0 ) && ( PointN == 14 ) && ( PlayR < 50))
						{
							// =====Миссия пройдена=====
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
							SET_CHAR_RELATIONSHIP(ped1, 0, 24);
							SET_SENSE_RANGE(ped1, 0.01);

							DO_SCREEN_FADE_OUT( 100 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())//если игрок мёртв или аврестован, если лодка унечтожена
								{
									break;
								}
							}

							//ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 505.985, 1617.865, 13.324 ); // куда смотрит камера
							SET_CAM_POS			( camera, 492.803, 1608.3, 10.203 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							WARP_CHAR_FROM_CAR_TO_COORD(ped1, 493.708, 1615.576, 10.898);//телепартируем из катера
							SET_CHAR_HEADING(ped1, -90.437);
							DO_SCREEN_FADE_IN( 100 );// убирается затемнение экрана
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 509.995, 1616.462, 10.598, 3, -2, 1.5);// пед убегает
							SetTime(3000);
							DO_SCREEN_FADE_OUT( 100 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())//если игрок мёртв или аврестован, если лодка унечтожена
								{
									break;
								}
							}
							// убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							DO_SCREEN_FADE_IN( 100 );// убирается затемнение экрана

							SET_CHAR_COORDINATES(ped1, 806.724, 997.807, 6.466);// возвращаем игрока на исходную позицию рядом с чекпойнтом
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// разморозить игрока
							skip = 2;
							break;
						}
					}
				}
				// завершение миссии
				REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
				SET_MAX_WANTED_LEVEL(6);

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(barrel);//выгружаем модель

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет

				// выгружаем из памяти транспорт
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)

				// удаляем объекты
				DELETE_OBJECT(&barrel_1);
				DELETE_OBJECT(&barrel_2);

				// выгружаем бочки
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_2);

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_COK_1" );//The Chase
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(1000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +1000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 1000);
					G_DIAZ = 2;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}

//============================== Phnom Penh '86 ======================================
		else if ((G_ONMISSION == 0) && (G_DIAZ == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(55.627, -13.084, 11.174, &diaz_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DWAYNE);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(diaz_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "LG_05");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 55.627, -13.084, 11.174, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 55.627, -13.084, 11.174, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("COK_2", 15000, CUTSCENE_BARON);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-288.2, -487.5, 9.8, 275.0);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
				blip_on = 0;
				skip = 0;
				PointN = 1;
				explo2 = 0;
				explo3 = 0;
				explo4 = 0;
				explo5 = 0;
				explo6 = 0;
				explo7 = 0;
				explo8 = 0;
				explo9 = 0;
				carHUD_x = 0.8421875;
				carHUD_w = 0.0739583;
				play_Speech = 0;

				SET_MAX_WANTED_LEVEL(0);
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

				Car car1, car2, car3, car4, car5, car6, car7, car8, car9;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11;
				Object barrel_1, barrel_2, barrel_3, barrel_4, barrel_5, barrel_6, barrel_7, barrel_8, barrel_9, barrel_10;
				Pickup bag;
				Texture fon, car;
				Cam camera;

				uint barrel = barrel4;
				uint CarM1 = MODEL_MAVERICK;
				uint CarM2 = MODEL_BURRITO2;
				uint CarM3 = MODEL_BOBCAT;
				uint CarM4 = MODEL_MARQUIS;
				uint CarM5 = MODEL_TROPIC;
				uint CarM6 = MODEL_HUNTLEY;
				uint CarM7 = MODEL_SPARROW;

				uint PedM1 = MODEL_IG_LILJACOB;// Ланс
				uint PedM2 = MODEL_M_Y_GIRI_LO_01;// Банда акул1
				uint PedM3 = MODEL_M_Y_GIRI_LO_02;// Банда акул2
				uint PedM4 = MODEL_M_Y_GIRI_LO_03;// Банда акул3
				uint PedM5 = MODEL_IG_RAY_BOCCINO;// Бос банды Акул
				uint PedM6 = MODEL_IG_TUNA;// рабочий на мосту
				uint PedM7 = MODEL_M_M_GRU2_HI_02;// Гольфмен1
				uint PedM8 = MODEL_M_M_GRU2_LO_02;// Гольфмен2
				uint car_heal1, car_heal2, car_heal3, car_heal4, car_heal5, car_heal6, car_heal7, car_heal8, car_heal9;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				car = GET_TEXTURE( textur, "hel_hud" );

				// грузим модели
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);
				REQUEST_MODEL(CarM3);
				while (!HAS_MODEL_LOADED(CarM3)) WAIT(100);
				REQUEST_MODEL(CarM4);
				while (!HAS_MODEL_LOADED(CarM4)) WAIT(100);
				REQUEST_MODEL(CarM5);
				while (!HAS_MODEL_LOADED(CarM5)) WAIT(100);
				REQUEST_MODEL(CarM6);
				while (!HAS_MODEL_LOADED(CarM6)) WAIT(100);
				REQUEST_MODEL(CarM7);
				while (!HAS_MODEL_LOADED(CarM7)) WAIT(100);

				REQUEST_MODEL(PedM1);
				while (!HAS_MODEL_LOADED(PedM1)) WAIT(100);
				REQUEST_MODEL(PedM2);
				while (!HAS_MODEL_LOADED(PedM2)) WAIT(100);
				REQUEST_MODEL(PedM3);
				while (!HAS_MODEL_LOADED(PedM3)) WAIT(100);
				REQUEST_MODEL(PedM4);
				while (!HAS_MODEL_LOADED(PedM4)) WAIT(100);
				REQUEST_MODEL(PedM5);
				while (!HAS_MODEL_LOADED(PedM5)) WAIT(100);
				REQUEST_MODEL(PedM6);
				while (!HAS_MODEL_LOADED(PedM6)) WAIT(100);
				REQUEST_MODEL(PedM7);
				while (!HAS_MODEL_LOADED(PedM7)) WAIT(100);
				REQUEST_MODEL(PedM8);
				while (!HAS_MODEL_LOADED(PedM8)) WAIT(100);

				//Грузим пути
				REQUEST_CAR_RECORDING( 3018 ); // полёт Основной
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3018 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3019 ); // релокация Ленса
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3019 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3020 ); // прилёт Ленса (эвакуация)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3020 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3021 );// улёт Ленса (эвакуация)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3021 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3022 ); // мимо пролетает верталёт 1
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3022 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3023 ); // мимо пролетает верталёт 2
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3023 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3024 ); // подскок Буррито 1
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3024 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3025 ); // подскок Буррито 2
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3025 )) WAIT(0);

				// создаём транспорт
				CREATE_CAR(CarM1, 450.837, 1700.35, 33.581, &car1, TRUE);
				CHANGE_CAR_COLOUR( car1, 112, 30 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car1, 127, 127 );//цвет машины
				SET_CAR_HEALTH(car1, 2500);

				// Яхты
				CREATE_CAR(CarM4, 68.724, 306.467, 1.477, &car2, TRUE);
				CREATE_CAR(CarM4, 34.538, -227.762, 1.477, &car3, TRUE);
				CREATE_CAR(CarM4, 80.127, -240.915, 1.477, &car4, TRUE);
				CREATE_CAR(CarM5, 91.53, -240.915, 1.477, &car5, TRUE);
				SET_CAR_HEADING(car3, -80.0);
				SET_CAR_HEADING(car4, 15.0);
				SET_CAR_HEADING(car5, 100.0);

				// Гольфкары
				CREATE_CAR(CarM6, 274.352, 1025.605, 10.324, &car6, TRUE);
				SET_CAR_HEADING(car6, 120.0);
				CREATE_CAR(CarM6, 275.196, 1032.668, 10.324, &car7, TRUE);
				SET_CAR_HEADING(car7, 80.0);

				// Верталёты
				CREATE_CAR(CarM7, 332.46, 1072.503, 8.735, &car8, TRUE);
				SET_CAR_HEADING(car8, 90.0);
				CREATE_CAR(CarM7, 332.46, 1084.741, 8.735, &car9, TRUE);
				SET_CAR_HEADING(car9, 90.0);

				// создаём моделей педов
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//создаём педа за рулём автомобиля (Ленс)
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM7, &ped2);//создаём педа за рулём автомобиля 
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM8, &ped3);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car4, 1, PedM7, &ped4);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car5, 1, PedM8, &ped5);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car8, 1, PedM7, &ped6);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car9, 1, PedM8, &ped7);//создаём педа за рулём автомобиля

				CREATE_CHAR (26, PedM6, 323.596, 1079.535, 8.828, &ped8, TRUE);// создаём педа (Прыгун)
				CREATE_CHAR (26, PedM7, 268.696, 1031.373, 10.081, &ped9, TRUE);// создаём педа
				SET_CHAR_HEADING(ped9, -60.0);
				CREATE_CHAR (26, PedM8, 269.781, 1030.586, 10.081, &ped10, TRUE);// создаём педа
				SET_CHAR_HEADING(ped10, -15.0);
				CREATE_CHAR (26, PedM7, 269.688, 1032.668, 10.081, &ped11, TRUE);// создаём педа
				SET_CHAR_HEADING(ped11, -170.0);

				CREATE_OBJECT_NO_OFFSET(barrel, 498.763, 1635.162, 27.045, &barrel_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 519.434, 1633.204, 27.045, &barrel_2, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 526.728, 1645.109, 19.903, &barrel_3, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 458.143, 1728.001, 12.754, &barrel_4, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 438.217, 1741.801, 15.859, &barrel_5, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 421.251, 1751.754, 15.859, &barrel_6, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 391.001, 1722.386, 15.858, &barrel_7, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 384.238, 1653.211, 25.385, &barrel_8, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 451.966, 1681.897, 25.011, &barrel_9, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 509.788, 1619.213, 19.921, &barrel_10, TRUE);

				FORCE_WEATHER_NOW( WEATHER_EXTRA_SUNNY );//устанавливаем погода
				FORWARD_TO_TIME_OF_DAY(5, 30);//устанавливаем время
				RELEASE_WEATHER();

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "COK_2A", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("cok_2a");
				while (!HAS_CUTSCENE_LOADED())
				{
					WAIT(0);
				}

				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED())
				{
					WAIT(0);
				}

				LOAD_ADDITIONAL_TEXT( "COK_2B", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("cok_2b");
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

				START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3018, 0.0, 0.0, 0.0);
				WAIT(10);
				TASK_ENTER_CAR_AS_PASSENGER(GetPlayerPed(), car1, 1, 1);

				//ставим камеру
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, 45.657, -37.678, 35.08 ); // куда смотрит камера
				SET_CAM_POS			( camera, 26.871, -50.819, 35.412 );//расположение камеры
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_CAM_FOV( camera, 45.0 );
				SET_WIDESCREEN_BORDERS( 1 );
				SetTime(4000);
				DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
				while(true)
				{
					WAIT(0);
					if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
					{
						break;
					}
				}
				SET_CAM_BEHIND_PED( GetPlayerPed() );
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				END_CAM_COMMANDS( &camera );
				SET_WIDESCREEN_BORDERS( 0 );

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

				SET_CHAR_INVINCIBLE(ped1, 1);
				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// Игрок бессмертный
				UpdateWeaponOfPed(GetPlayerPed(), WEAPON_M40A1);
				SetTime(3500);
				SETTIMERB( 0 );
				text1 = 1;
				res = 0;
				res_on = 0;

				// часть миссии 1
				while(true)
				{
					WAIT(0);
					DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
					DRAW_SPRITE( car, 0.8765625, 0.80925926, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.
					DRAW_SPRITE( 0, 0.8421875, 0.80925926, 0.0739583, 0.014, 0.0, 97, 194, 247, 255 );// рисуем фоновую текстуру.

					// ----- Диалог 1
					if (text1 == 1)
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R2_BG", "COK2_1", 0, 0);//One thing puzzling me, What's with 'Quentin!?
						START_SCRIPT_CONVERSATION(1, 1);
						play_Speech = 1;
						text1 = 2;
					}
					else if (text1 == 2)
					{
						if (play_Speech == 0)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_BH", "COK2_2", 0, 0);//I dunno, I always kinda liked it...Quentin Vance...
							START_SCRIPT_CONVERSATION(1, 1);
							play_Speech = 1;
							text1 = 3;
						}
					}
					else if (text1 == 3)
					{
						if (play_Speech == 0)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_BH_QQQ1", "COK2_3", 0, 0);//Vance? Your name's Lance Vance?
							START_SCRIPT_CONVERSATION(1, 1);
							play_Speech = 1;
							text1 = 4;
						}
					}
					else if (text1 == 4)
					{
						if (play_Speech == 0)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R2_BI", "COK2_4", 0, 0);//Hey! I got enough of that at school!
							START_SCRIPT_CONVERSATION(1, 1);
							play_Speech = 1;
							text1 = 5;
						}
					}
					else if (text1 == 5)
					{
						if (play_Speech == 0)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_BJ", "COK2_13", 0, 0);//Lance Vance. Poor bastard.
							START_SCRIPT_CONVERSATION(1, 1);
							play_Speech = 1;
							text1 = 6;
							SETTIMERB( 0 );
						}
					}
					else if (text1 == 6)
					{
						if (TIMERB() > 3500)
						{
							text1 = 7;
						}
					}
					else if (text1 == 7)
					{
						if (play_Speech == 0)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_BK", "COK2_8", 0, 0);//Where the hell are we headed anyway?
							START_SCRIPT_CONVERSATION(1, 1);
							play_Speech = 1;
							text1 = 8;
						}
					}
					else if (text1 == 8)
					{
						if (play_Speech == 0)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R2_BL", "COK2_9", 0, 0);//Prawn Island
							START_SCRIPT_CONVERSATION(1, 1);
							play_Speech = 1;
							text1 = 9;
							SETTIMERB( 0 );
						}
					}
					else if (text1 == 9)
					{
						if (TIMERB() > 4000)
						{
							text1 = 10;
						}
					}
					else if (text1 == 10)
					{
						if (play_Speech == 0)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_BM", "COK2_5", 0, 0);//You ever fired one of those from a whirly?
							START_SCRIPT_CONVERSATION(1, 1);
							play_Speech = 1;
							text1 = 11;
						}
					}
					else if (text1 == 11)
					{
						if (play_Speech == 0)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_BN", "COK2_6", 0, 0);//No. I'll get a bit of practice on the way though.
							START_SCRIPT_CONVERSATION(1, 1);
							play_Speech = 1;
							text1 = 12;
						}
					}

					if (play_Speech == 1)
					{
						if (!IS_SCRIPTED_CONVERSATION_ONGOING())
						{
							play_Speech = 0;
						}
					}

					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 178.35, 585.05, 7.92, 163.35, 590.05, 17.92, 0 )) && (PointN == 1))
					{
						// дебаг
						SET_CAR_COORDINATES(car3, 232.816, 940.724, 1.477);// перемещаем яхту
						SET_CAR_COORDINATES(car4, 235.118, 924.104, 1.477);// перемещаем яхту
						SET_CAR_COORDINATES(car5, 248.082, 937.364, 1.477);// перемещаем яхту
						SET_CHAR_COORDINATES(ped8, 166.0, 594.631, 22.48);// перемещаем прыгуна
						PointN = 2;
					}
					else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 248.05, 831.89, 11.37, 233.05, 836.89, 21.37, 0 )) && (PointN == 2))
					{
						START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car8, 3022, 0.0, 0.0, -10.0);
						START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car9, 3023, 0.0, 0.0, -5.0);
						SET_PLAYBACK_SPEED(car8, 0.75);
						SET_PLAYBACK_SPEED(car9, 0.75);
						PointN = 3;
					}
					else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 363.08, 1211.6, 41.76, 348.08, 1216.6, 51.76, 0 )) && (PointN == 3))
					{
						res = 1;
						res_on = 1;
						break;
					}

					GET_CAR_HEALTH(car1, &car_heal1);
					GET_CAR_HEALTH(car2, &car_heal2);
					GET_CAR_HEALTH(car3, &car_heal3);
					GET_CAR_HEALTH(car4, &car_heal4);
					GET_CAR_HEALTH(car5, &car_heal5);
					GET_CAR_HEALTH(car6, &car_heal6);
					GET_CAR_HEALTH(car7, &car_heal7);
					GET_CAR_HEALTH(car8, &car_heal8);
					GET_CAR_HEALTH(car9, &car_heal9);

					if ((car_heal2 < 850) && (explo2 == 0))
					{
						EXPLODE_CAR(car2, 1, 1);
						explo2 = 1;
					}
					else if ((car_heal3 < 850) && (explo3 == 0))
					{
						EXPLODE_CAR(car3, 1, 1);
						explo3 = 1;
					}
					else if ((car_heal4 < 850) && (explo4 == 0))
					{
						EXPLODE_CAR(car4, 1, 1);
						explo4 = 1;
					}
					else if ((car_heal5 < 850) && (explo5 == 0))
					{
						EXPLODE_CAR(car5, 1, 1);
						explo5 = 1;
					}
					else if ((car_heal6 < 850) && (explo6 == 0))
					{
						//EXPLODE_CAR(car6, 1, 1);
						explo6 = 1;
					}
					else if ((car_heal7 < 650) && (explo7 == 0))
					{
						//EXPLODE_CAR(car7, 1, 1);
						explo7 = 1;
					}
					else if ((car_heal8 < 900) && (explo8 == 0))
					{
						EXPLODE_CAR(car8, 1, 1);
						explo8 = 1;
					}
					else if ((car_heal9 < 900) && (explo9 == 0))
					{
						EXPLODE_CAR(car9, 1, 1);
						explo9 = 1;
					}

					if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))// Игрок покинул транспорт
					{
						ABORT_SCRIPTED_CONVERSATION( 0 );
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NECOK2_H", 5000, 1);//~r~You fell out of the helicopter.
						skip = 1;
						WAIT(100);
						break;
					}
					else if (car_heal1 < 10)// вертолёт унечтожен
					{
						SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// Игрок смертный
						EXPLODE_CAR(car1, 1, 1);
						ABORT_SCRIPTED_CONVERSATION( 0 );
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "WRECKED", 5000, 1);//~r~The vehicle is wrecked!
						skip = 1;
						break;
					}
					else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
					{
						ABORT_SCRIPTED_CONVERSATION( 0 );
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
						skip = 1;
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// игрок мёртв/арестован
					{
						skip = 1;
						break;
					}
				}

				// часть миссии 2
				if (skip == 0)
				{
					PointN = 1;
					explo2 = 0;
					explo3 = 0;
					explo4 = 0;
					explo5 = 0;
					explo6 = 0;
					explo7 = 0;
					explo8 = 0;
					explo9 = 0;

					// останавливаем пути
					STOP_PLAYBACK_RECORDED_CAR(car8);
					STOP_PLAYBACK_RECORDED_CAR(car9);

					// выгружаем пути транспорта
					REMOVE_CAR_RECORDING( 3022 ); // выгружаем пути транспорта
					REMOVE_CAR_RECORDING( 3023 ); // выгружаем пути транспорта

					// выгружаем из памяти транспорт
					MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
					MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
					MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
					MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)

					// создаём новые тачки
					CREATE_CAR(CarM2, 451.466, 1690.589, 14.033, &car2, TRUE);
					CREATE_CAR(CarM2, 443.973, 1690.589, 14.033, &car3, TRUE);
					CREATE_CAR(CarM3, 450.871, 1745.972, 15.94, &car4, TRUE);
					SET_CAR_HEADING(car4, 60.0);
					CREATE_CAR(CarM3, 418.117, 1739.229, 15.94, &car5, TRUE);
					SET_CAR_HEADING(car5, 175.0);

					FIX_CAR(car1);
					SET_CAR_HEALTH(car1, 3000);
					SET_ENGINE_HEALTH(car1, 3500);
					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_M40A1);
					text1 = 1;
					play = 0;
					sound = 1;
					SETTIMERB( 0 );
					while(true)
					{
						WAIT(0);
						SET_CHAR_INVINCIBLE(ped1, 1);
						SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// Игрок бессмертный
						// ------------------- HUD -------------------
						GET_CAR_HEALTH(car1, &car_heal1);
						DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
						DRAW_SPRITE( car, 0.8765625, 0.80925926, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.
						DRAW_SPRITE( 0, 0.8421875, 0.80925926, 0.0739583, 0.014, 0.0, 27, 89, 130, 255 );// рисуем фоновую текстуру.

						if (car_heal1 < 5)
						{
							carH1 = 0;
						}
						else
						{
							carH1 = car_heal1;
						}
						carH2 = carHUD_w/3000;
						carH3 = carH2*carH1;
						carHUD_y1 = carHUD_w-carH3;
						carHUD_y2 = carHUD_y1/2;
						carHUD_y3 = carHUD_x-carHUD_y2;
						DRAW_SPRITE( 0, carHUD_y3, 0.80925926, carH3, 0.014, 0.0, 97, 194, 247, 255 );// рисуем фоновую текстуру.

						// ----- Диалог 2
						if (text1 == 1)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_BO", "COK2_14", 0, 0);//Ok, we're almost there.
							START_SCRIPT_CONVERSATION(1, 1);
							play_Speech = 1;
							text1 = 2;
						}
						else if (text1 == 2)
						{
							if (play_Speech == 0)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R2_CA", "COK2_15", 0, 0);//We'll make a couple of passes.
								START_SCRIPT_CONVERSATION(1, 1);
								play_Speech = 1;
								text1 = 3;
							}
						}
						else if (text1 == 3)
						{
							if (play_Speech == 0)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R2_CB", "COK2_16", 0, 0);//So take out as many guns as you can.
								START_SCRIPT_CONVERSATION(1, 1);
								play_Speech = 1;
								text1 = 4;
							}
						}
						else if (text1 == 4)
						{
							if (play_Speech == 0)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R2_CC", "COK2_17", 0, 0);//Then I'll set you down and you're on your way.
								START_SCRIPT_CONVERSATION(1, 1);
								play_Speech = 1;
								text1 = 5;
							}
						}

						if (play_Speech == 1)
						{
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								play_Speech = 0;
							}
						}

						// Реплики о повреждении тут
						if ((car_heal1 < 2995) && (sound == 1))
						{
							if (play == 0)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R2_CD", "COK2_20", 0, 0);//Damn! This is a war zone! Take out some of those gunmen!
								START_SCRIPT_CONVERSATION(1, 1);
								sound = 2;
								play = 1;
							}
						}
						else if ((car_heal1 < 1750) && (sound == 2))
						{
							if (play == 0)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R2_CE", "COK2_21", 0, 0);//We're taking hits here, man!
								START_SCRIPT_CONVERSATION(1, 1);
								sound = 3;
								play = 1;
							}
						}
						else if ((car_heal1 < 595) && (sound == 3))
						{
							if (play == 0)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R2_CF", "COK2_22", 0, 0);//This thing ain't cheap to fix! Take them out!
								START_SCRIPT_CONVERSATION(1, 1);
								sound = 4;
								play = 1;
							}
						}
						if (play == 1)
						{
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								play = 0;
							}
						}

						// взрывы машин
						GET_CAR_HEALTH(car2, &car_heal2);
						GET_CAR_HEALTH(car3, &car_heal3);
						GET_CAR_HEALTH(car4, &car_heal4);
						GET_CAR_HEALTH(car5, &car_heal5);
						if ((car_heal2 < 800) && (explo2 == 0))
						{
							EXPLODE_CAR(car2, 1, 1);
							explo2 = 1;
						}
						else if ((car_heal3 < 750) && (explo3 == 0))
						{
							EXPLODE_CAR(car3, 1, 1);
							GET_CAR_COORDINATES(car3, &PedX, &PedY, &PedZ);//вписываем координаты в переменную
							SET_CAR_COORDINATES(car3, PedX, PedY, PedZ);
							explo3 = 1;
						}
						else if ((car_heal4 < 800) && (explo4 == 0))
						{
							EXPLODE_CAR(car4, 1, 1);
							explo4 = 1;
						}
						else if ((car_heal5 < 800) && (explo5 == 0))
						{
							EXPLODE_CAR(car5, 1, 1);
							explo5 = 1;
						}

						GET_CHAR_COORDINATES(ped1,  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 534.5, 1603.5, 20.0, 529.5, 1618.5, 30.0, 0 )) && (PointN == 1))// разморозка педов 1
						{
							FREEZE_CHAR_POSITION(ped8, 0);
							FREEZE_CHAR_POSITION(ped9, 0);
							FREEZE_CHAR_POSITION(ped10, 0);
							FREEZE_CHAR_POSITION(ped11, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped8, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped9, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped10, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped11, 0);
							PointN = 2;
						}
						else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 544.34, 1688.27, 20.07, 529.34, 1693.27, 30.07, 0 )) && (PointN == 2))// бассейн
						{
							UpdateWeaponOfPed(GetPlayerPed(), WEAPON_M40A1);
							res = 2;
							res_on = 1;
							PointN = 3;
						}

						else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 430.5, 1757.5, 17.7, 425.5, 1772.5, 27.7, 0 )) && (PointN == 3))// площадка
						{
							UpdateWeaponOfPed(GetPlayerPed(), WEAPON_M40A1);
							res = 3;
							res_on = 1;
							PointN = 4;
						}
						else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 412.5, 1728.5, 26.5, 397.5, 1733.5, 36.5, 0 )) && (PointN == 4))// здание2-3
						{
							UpdateWeaponOfPed(GetPlayerPed(), WEAPON_M40A1);
							res = 4;
							res_on = 1;
							PointN = 5;
						}
						else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 429.5, 1654.5, 37.0, 424.5, 1669.5, 47.0, 0 )) && (PointN == 5))// разморозка педов 2
						{
							FREEZE_CHAR_POSITION(ped7, 0);
							FREEZE_CHAR_POSITION(ped8, 0);
							FREEZE_CHAR_POSITION(ped9, 0);
							FREEZE_CHAR_POSITION(ped10, 0);
							FREEZE_CHAR_POSITION(ped11, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped7, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped8, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped9, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped10, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped11, 0);
							PointN = 6;
						}
						else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 455.5, 1643.5, 30.0, 450.5, 1658.5, 40.0, 0 )) && (PointN == 6))// босс
						{
							UpdateWeaponOfPed(GetPlayerPed(), WEAPON_M40A1);
							res = 5;
							res_on = 1;
							PointN = 7;
						}
						else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 471.5, 1628.837, 25.0, 456.5, 1639.598, 40.0, 0 )) && (PointN == 7))// камера
						{
							if ((!IS_CHAR_DEAD(ped2)) || (!IS_CHAR_FATALLY_INJURED(ped2)))//если пед мёртв или фатально ранен.
							{
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
								UpdateWeaponOfPed(ped2, WEAPON_AK47);
								SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_AK47, TRUE);
								SET_CHAR_HEALTH(ped2, 200);
								FREEZE_CHAR_POSITION(ped2, 1);
								SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped2, 1);

								//ставим камеру
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, PlayX, PlayY, PlayZ ); // куда смотрит камера
								SET_CAM_POS			( camera, 527.47, 1621.499, 31.196 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );

								//----------- шестая чатсь диалога
								ABORT_SCRIPTED_CONVERSATION( 0 );
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R2_CF_QQQ1", "COK2_27", 0, 0);//You're on MY turf asshole!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R2_CG", "COK2_28", 0, 0);//You're going down!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();
								SetTime(2000);

								//убираем камеру
								SET_CAM_BEHIND_PED( GetPlayerPed() );
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								END_CAM_COMMANDS( &camera );
								SET_WIDESCREEN_BORDERS( 0 );
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							}
							SET_CHAR_HEALTH(ped3, 200);
							SET_CHAR_HEALTH(ped4, 200);
							SET_CHAR_HEALTH(ped5, 200);
							SET_CHAR_HEALTH(ped6, 200);
							SET_CHAR_HEALTH(ped7, 200);
							SET_CHAR_HEALTH(ped8, 200);
							SET_CHAR_HEALTH(ped9, 200);
							SET_CHAR_HEALTH(ped10, 200);
							SET_CHAR_HEALTH(ped11, 200);

							FREEZE_CHAR_POSITION(ped5, 1);
							FREEZE_CHAR_POSITION(ped6, 1);
							FREEZE_CHAR_POSITION(ped7, 1);
							FREEZE_CHAR_POSITION(ped8, 1);
							FREEZE_CHAR_POSITION(ped9, 1);
							FREEZE_CHAR_POSITION(ped10, 1);
							FREEZE_CHAR_POSITION(ped11, 1);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped5, 1);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped6, 1);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped7, 1);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped8, 1);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped9, 1);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped10, 1);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped11, 1);

							CLEAR_AREA(456.463, 1603.771, 1.752, 27.5, 0);//очещаем зону загрузки
							PointN = 8;
						}
						else if ((PointN == 8) && (PlayZ < 10.0))
						{
							break;
						}

						// высыпаем педов
						if (res_on == 1)
						{
							res_on = 0;
							// выгружаем из памяти педов
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

							if (res == 1) // первое здание
							{
								CREATE_CHAR (26, PedM2, 499.5311, 1628.488, 27.23817, &ped2, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 509.1311, 1631.702, 27.23817, &ped3, TRUE);// создаём педа
								CREATE_CHAR (26, PedM4, 503.2476, 1637.191, 27.23817, &ped4, TRUE);// создаём педа
								CREATE_CHAR (26, PedM2, 515.6788, 1633.139, 27.23817, &ped5, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 505.3156, 1619.715, 20.23586, &ped6, TRUE);// создаём педа
								CREATE_CHAR (26, PedM4, 513.3373, 1618.388, 20.23586, &ped7, TRUE);// создаём педа
								CREATE_CHAR (26, PedM2, 527.2284, 1630.244, 20.20692, &ped8, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 527.5781, 1642.782, 20.20692, &ped9, TRUE);// создаём педа
								CREATE_CHAR (26, PedM4, 527.6659, 1640.961, 13.41278, &ped10, TRUE);// создаём педа
								CREATE_CHAR (26, PedM2, 523.9052, 1651.408, 20.20692, &ped11, TRUE);// создаём педа
								SET_CHAR_HEADING(ped2, 180.0);
								SET_CHAR_HEADING(ped3, 180.0);
								SET_CHAR_HEADING(ped4, 180.0);
								SET_CHAR_HEADING(ped5, 180.0);
								SET_CHAR_HEADING(ped6, 180.0);
								SET_CHAR_HEADING(ped7, 180.0);
								SET_CHAR_HEADING(ped8, -90.0);
								SET_CHAR_HEADING(ped9, -90.0);
								SET_CHAR_HEADING(ped10, -90.0);
								SET_CHAR_HEADING(ped11, -90.0);
								FREEZE_CHAR_POSITION(ped8, 1);
								FREEZE_CHAR_POSITION(ped9, 1);
								FREEZE_CHAR_POSITION(ped10, 1);
								FREEZE_CHAR_POSITION(ped11, 1);
								SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped8, TRUE);
								SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped9, TRUE);
								SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped10, TRUE);
								SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped11, TRUE);
							}
							else if (res == 2) // бассейн
							{
								/*/
								CREATE_CHAR (26, PedM3, 459.5424, 1736.075, 14.40884, &ped3, TRUE);// создаём педа
								//*/
								CREATE_CHAR (26, PedM2, 437.7209, 1733.959, 14.40884, &ped2, TRUE);// создаём педа
								CREATE_CHAR (26, PedM4, 323.596, 1079.535, 8.828, &ped3, TRUE);// создаём педа
								CREATE_CHAR (26, PedM4, 457.1077, 1742.261, 16.19898, &ped4, TRUE);// создаём педа
								CREATE_CHAR (26, PedM2, 454.0889, 1728.231, 12.98335, &ped5, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 447.3544, 1745.027, 16.19898, &ped6, TRUE);// создаём педа
								CREATE_CHAR (26, PedM4, 434.7601, 1743.938, 15.63101, &ped7, TRUE);// создаём педа
								//создаём педов в автомобиле
								CREATE_CHAR_INSIDE_CAR(car2, 1, PedM2, &ped8);
								CREATE_CHAR_AS_PASSENGER(car2, 1, PedM3, 0, &ped9);
								CREATE_CHAR_AS_PASSENGER(car2, 1, PedM4, 1, &ped10);
								CREATE_CHAR_AS_PASSENGER(car2, 1, PedM2, 2, &ped11);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 3024, 0.0, 0.0, 0.0);
							}
							else if (res == 3) // спортивная площадка
							{
								/*/
								CREATE_CHAR (26, PedM4, 416.019, 1738.672, 15.671, &ped2, TRUE);// создаём педа
								CREATE_CHAR (26, PedM2, 413.807, 1734.175, 15.599, &ped7, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 410.983, 1731.549, 15.599, &ped6, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 401.152, 1735.649, 15.599, &ped3, TRUE);// создаём педа
								//*/
								CREATE_CHAR (26, PedM4, 323.596, 1079.535, 8.828, &ped2, TRUE);// создаём педа
								CREATE_CHAR (26, PedM2, 325.596, 1079.535, 8.828, &ped7, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 327.596, 1079.535, 8.828, &ped6, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 329.596, 1079.535, 8.828, &ped3, TRUE);// создаём педа
								CREATE_CHAR (26, PedM2, 394.828, 1733.286, 15.599, &ped4, TRUE);// создаём педа
								CREATE_CHAR (26, PedM4, 401.541, 1719.955, 15.599, &ped5, TRUE);// создаём педа
								//создаём педов в автомобиле
								CREATE_CHAR_INSIDE_CAR(car3, 1, PedM4, &ped8);
								CREATE_CHAR_AS_PASSENGER(car3, 1, PedM3, 0, &ped9);
								CREATE_CHAR_AS_PASSENGER(car3, 1, PedM2, 1, &ped10);
								CREATE_CHAR_AS_PASSENGER(car3, 1, PedM4, 2, &ped11);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 3025, 0.0, 0.0, 0.0);
							}
							else if (res == 4)// здание 2-3
							{
								CREATE_CHAR (26, PedM3, 390.875, 1650.392, 25.205, &ped2, TRUE);// создаём педа
								CREATE_CHAR (26, PedM4, 386.224, 1656.767, 25.205, &ped3, TRUE);// создаём педа
								CREATE_CHAR (26, PedM2, 377.709, 1657.395, 25.205, &ped4, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 373.587, 1651.828, 25.205, &ped5, TRUE);// создаём педа
								CREATE_CHAR (26, PedM4, 390.221, 1655.435, 25.205, &ped6, TRUE);// создаём педа
								CREATE_CHAR (26, PedM2, 447.745, 1681.026, 24.773, &ped7, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 454.279, 1679.611, 24.773, &ped8, TRUE);// создаём педа
								CREATE_CHAR (26, PedM4, 461.358, 1679.611, 15.743, &ped9, TRUE);// создаём педа
								CREATE_CHAR (26, PedM2, 440.195, 1679.611, 15.743, &ped10, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 445.601, 1679.611, 17.752, &ped11, TRUE);// создаём педа
								SET_CHAR_HEADING(ped7, 180.0);
								SET_CHAR_HEADING(ped8, 180.0);
								SET_CHAR_HEADING(ped9, 180.0);
								SET_CHAR_HEADING(ped10, 180.0);
								SET_CHAR_HEADING(ped11, 180.0);

								FREEZE_CHAR_POSITION(ped7, 1);
								FREEZE_CHAR_POSITION(ped8, 1);
								FREEZE_CHAR_POSITION(ped9, 1);
								FREEZE_CHAR_POSITION(ped10, 1);
								FREEZE_CHAR_POSITION(ped11, 1);
								SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped7, TRUE);
								SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped8, TRUE);
								SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped9, TRUE);
								SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped10, TRUE);
								SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped11, TRUE);
							}
							else if (res == 5)// Босс
							{
								CREATE_CHAR (26, PedM5, 500.367, 1631.954, 26.839, &ped2, TRUE);// создаём педа
								CREATE_CHAR (26, PedM4, 496.771, 1632.476, 26.839, &ped3, TRUE);// создаём педа
								CREATE_CHAR (26, PedM2, 498.658, 1628.221, 26.839, &ped4, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 495.924, 1640.781, 22.626, &ped5, TRUE);// создаём педа
								CREATE_CHAR (26, PedM4, 499.931, 1634.356, 19.746, &ped6, TRUE);// создаём педа
								CREATE_CHAR (26, PedM2, 516.038, 1637.676, 19.746, &ped7, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 507.765, 1647.499, 17.502, &ped8, TRUE);// создаём педа
								CREATE_CHAR (26, PedM4, 511.891, 1642.674, 13.015, &ped9, TRUE);// создаём педа
								CREATE_CHAR (26, PedM2, 497.831, 1628.534, 13.015, &ped10, TRUE);// создаём педа
								CREATE_CHAR (26, PedM3, 512.865, 1645.961, 15.171, &ped11, TRUE);// создаём педа
								SET_CHAR_HEADING(ped2, 120.0);
								SET_CHAR_HEADING(ped3, 100.0);
								SET_CHAR_HEADING(ped4, 100.0);
								SET_CHAR_HEADING(ped6, 180.0);
								SET_CHAR_HEADING(ped7, 180.0);
								SET_CHAR_HEADING(ped8, 180.0);
								SET_CHAR_HEADING(ped9, 180.0);
								SET_CHAR_HEADING(ped10, -55.0);
								SET_CHAR_HEADING(ped11, 180.0);
							}

							SET_CHAR_HEALTH(ped2, 100);
							SET_CHAR_HEALTH(ped3, 100);
							SET_CHAR_HEALTH(ped4, 100);
							SET_CHAR_HEALTH(ped5, 100);
							SET_CHAR_HEALTH(ped6, 100);
							SET_CHAR_HEALTH(ped7, 100);
							SET_CHAR_HEALTH(ped8, 100);
							SET_CHAR_HEALTH(ped9, 100);
							SET_CHAR_HEALTH(ped10, 100);
							SET_CHAR_HEALTH(ped11, 100);

							UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_12);
							UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_12);
							UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_12);
							UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_12);
							UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_12);
							UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_12);
							UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_12);
							UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_12);
							UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_12);
							UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_12);

							SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_EPISODIC_12, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_12, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_12, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_12, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_12, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_12, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_12, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_12, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_12, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_12, TRUE);

							SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);

							SET_CHAR_RELATIONSHIP(ped2, 5, 0);
							SET_CHAR_RELATIONSHIP(ped3, 5, 0);
							SET_CHAR_RELATIONSHIP(ped4, 5, 0);
							SET_CHAR_RELATIONSHIP(ped5, 5, 0);
							SET_CHAR_RELATIONSHIP(ped6, 5, 0);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);
							SET_CHAR_RELATIONSHIP(ped8, 5, 0);
							SET_CHAR_RELATIONSHIP(ped9, 5, 0);
							SET_CHAR_RELATIONSHIP(ped10, 5, 0);
							SET_CHAR_RELATIONSHIP(ped11, 5, 0);

							SET_SENSE_RANGE(ped2, 55.0);
							SET_SENSE_RANGE(ped3, 55.0);
							SET_SENSE_RANGE(ped4, 55.0);
							SET_SENSE_RANGE(ped5, 55.0);
							SET_SENSE_RANGE(ped6, 55.0);
							SET_SENSE_RANGE(ped7, 55.0);
							SET_SENSE_RANGE(ped8, 55.0);
							SET_SENSE_RANGE(ped9, 55.0);
							SET_SENSE_RANGE(ped10, 55.0);
							SET_SENSE_RANGE(ped11, 55.0);

							SET_CHAR_WILL_USE_COVER(ped2, 1);
							SET_CHAR_WILL_USE_COVER(ped3, 1);
							SET_CHAR_WILL_USE_COVER(ped4, 1);
							SET_CHAR_WILL_USE_COVER(ped5, 1);
							SET_CHAR_WILL_USE_COVER(ped6, 1);
							SET_CHAR_WILL_USE_COVER(ped7, 1);
							SET_CHAR_WILL_USE_COVER(ped8, 1);
							SET_CHAR_WILL_USE_COVER(ped9, 1);
							SET_CHAR_WILL_USE_COVER(ped10, 1);
							SET_CHAR_WILL_USE_COVER(ped11, 1);

							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
						}

						if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))// Игрок покинул транспорт
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_H", 5000, 1);//~r~You fell out of the helicopter.
							skip = 1;
							WAIT(100);
							break;
						}
						else if (car_heal1 < 10)// вертолёт унечтожен
						{
							SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// Игрок смертный
							EXPLODE_CAR(car1, 1, 1);
							ABORT_SCRIPTED_CONVERSATION( 0 );
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "WRECKED", 5000, 1);//~r~The vehicle is wrecked!
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// игрок мёртв/арестован
						{
							skip = 1;
							break;
						}
					}
				}

				// часть миссии 3
				if (skip == 0)
				{
					SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// Игрок смертный
					SET_MAX_WANTED_LEVEL(6);

					NEW_SCRIPTED_CONVERSATION();
					ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
					ADD_LINE_TO_CONVERSATION(0, "R2_CH", "COK2_23", 0, 0);//Ok, you're on your own from here! Good luck, brother!
					START_SCRIPT_CONVERSATION(1, 1);

					SetTime(1000);
					GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_M40A1, 100, FALSE);
					SET_CHAR_AMMO(GetPlayerPed(), WEAPON_M40A1, 100);
					TASK_LEAVE_CAR(GetPlayerPed(), car1);
					SET_PLAYBACK_SPEED(car1, 1.5);
					play = 1;
					PointN = 0;
					SETTIMERB( 0 );
					while(true)
					{
						WAIT(0);
						if ((TIMERB() > 3000) && (play == 1))
						{
							if ((!IS_CHAR_DEAD(ped2)) || (!IS_CHAR_FATALLY_INJURED(ped2)))//если пед мёртв или фатально ранен.
							{
								ADD_BLIP_FOR_CHAR(ped2, &diaz_ico);
								CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(diaz_ico, 19);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "MO_TARGET");//иконка на радаре "Товар"
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NECOK2_M", 5000, 1);//~COL_NET_12~Kill the betrayer and take the money.
							}
							FIX_CAR(car1);
							play = 0;
						}
						if (play == 0)
						{
							if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_FATALLY_INJURED(ped2)))//если пед мёртв или фатально ранен.
							{
								REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
								GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
								GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &PedZ);
								CREATE_PICKUP( mission_keis, 22, PedX+0.2, PedY+0.2, PedZ+0.2, &bag, 0 );// сумка
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NECOK2_M2", 5000, 1);//~COL_NET_12~Take the money.

								ADD_BLIP_FOR_PICKUP(bag, &diaz_ico);
								CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(diaz_ico, 19);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "MO_TARGET");//иконка на радаре "Товар"
								break;
							}
						}
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 524.046, 1623.101, 12.505, 492.423, 1650.812, 30.608, 0 )) && (PointN == 0))// релокация Ленса
						{
							STOP_PLAYBACK_RECORDED_CAR(car1);
							REMOVE_CAR_RECORDING( 3018 ); // выгружаем пути транспорта
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3019, 0.0, 0.0, 0.0);
							FREEZE_CHAR_POSITION(ped3, 0);
							FREEZE_CHAR_POSITION(ped9, 0);
							FREEZE_CHAR_POSITION(ped10, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped3, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped9, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped10, 0);
							PointN = 1;
						}
						if (IS_CAR_DEAD(car1))// вертолёт унечтожен
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "WRECKED", 5000, 1);//~r~The vehicle is wrecked!
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// игрок мёртв/арестован
						{
							skip = 1;
							break;
						}
					}
				}
				// часть миссии 4
				if (skip == 0)
				{
					play = 0;
					while(true)
					{
						WAIT(0);
						if ((HAS_PICKUP_BEEN_COLLECTED( bag )) && (play == 0))
						{
							SET_PLAYBACK_SPEED(car1, 1);
							STOP_PLAYBACK_RECORDED_CAR(car1);
							REMOVE_CAR_RECORDING( 3019 ); // выгружаем пути транспорта
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3020, 0.0, 0.0, 0.0);
							SET_PLAYBACK_SPEED(car1, 1.5);

							REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_CHAR(ped1, &diaz_ico);
							CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(diaz_ico, 19);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "MO_TARGET");//иконка на радаре "Товар"
							PRINT_STRING_IN_STRING("string", "NECOK2_V", 5000, 1);//~COL_NET_12~Get on the helicopter.
							play = 1;
						}
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 524.046, 1623.101, 12.505, 492.423, 1650.812, 30.608, 0 )) && (PointN == 0))// релокация Ленса
						{
							// если игрок в здании меняем местоположение Ленса
							STOP_PLAYBACK_RECORDED_CAR(car1);
							REMOVE_CAR_RECORDING( 3018 ); // выгружаем пути транспорта
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3019, 0.0, 0.0, 0.0);

							FREEZE_CHAR_POSITION(ped3, 0);
							FREEZE_CHAR_POSITION(ped9, 0);
							FREEZE_CHAR_POSITION(ped10, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped3, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped9, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped10, 0);

							PointN = 1;
						}

						if (PointN == 1)
						{
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//проверка "игрок на координатах"
							if (PlayR < 3.2)
							{
								FIX_CAR(car1);
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
								TASK_ENTER_CAR_AS_PASSENGER(GetPlayerPed(), car1, 10000, 3);
								PointN = 2;
							}
						}
						else if (PointN == 2)
						{
							if (IS_CHAR_IN_CAR(GetPlayerPed(), car1))
							{
								SET_PLAYBACK_SPEED(car1, 1);
								STOP_PLAYBACK_RECORDED_CAR(car1);
								REMOVE_CAR_RECORDING( 3020 ); // выгружаем пути транспорта
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3021, 0.0, 0.0, 0.0);
								//ставим камеру
								
								GET_CHAR_COORDINATES(ped1,  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, PlayX, PlayY, PlayZ ); // куда смотрит камера
								SET_CAM_POS			( camera, 493.67, 1624.809, 29.511 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );
								SETTIMERA( 0 );
								PointN = 3;
							}
						}
						else if (PointN == 3)
						{
							GET_CHAR_COORDINATES(ped1,  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							POINT_CAM_AT_COORD	( camera, PlayX, PlayY, PlayZ ); // куда смотрит камера
							if (TIMERA() > 5000)
							{
								DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
								while(true)
								{
									WAIT(0);
									if (IS_SCREEN_FADED_OUT())
									{
										break;
									}
								}
								PointN = 4;
								skip = 2;
								break;
							}
						}

						if (IS_CAR_DEAD(car1))// вертолёт унечтожен
						{
							PRINT_STRING_IN_STRING("string", "WRECKED", 5000, 1);//~r~The vehicle is wrecked!
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// игрок мёртв/арестован
						{
							skip = 1;
							break;
						}
					}
				}

				// завершение миссии
				if (skip == 2)
				{
					INCREASE_PLAYER_MAX_HEALTH(GetPlayerIndex(), 1);
					WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 54.916, -7.17, 11.796);//телепартируем из катера
					SET_CAM_BEHIND_PED( GetPlayerPed() );
					ACTIVATE_SCRIPTED_CAMS( 0, 0 );
					END_CAM_COMMANDS( &camera );
					SET_WIDESCREEN_BORDERS( 0 );
					ALTER_WANTED_LEVEL(GetPlayerIndex(), 0);
					APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
					SetTime(1000);
					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				}
				
				REMOVE_PICKUP(bag);// выгружаем оружие
				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( car );
				REMOVE_TXD( textur );
				REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
				SET_CHAR_INVINCIBLE(ped1, 0);
				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// Игрок смертный
				SET_MAX_WANTED_LEVEL(6);

				STOP_PLAYBACK_RECORDED_CAR(car1);
				STOP_PLAYBACK_RECORDED_CAR(car2);
				STOP_PLAYBACK_RECORDED_CAR(car3);
				STOP_PLAYBACK_RECORDED_CAR(car4);
				STOP_PLAYBACK_RECORDED_CAR(car5);
				STOP_PLAYBACK_RECORDED_CAR(car6);
				STOP_PLAYBACK_RECORDED_CAR(car7);
				STOP_PLAYBACK_RECORDED_CAR(car8);
				STOP_PLAYBACK_RECORDED_CAR(car9);

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM5);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM6);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM7);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM6);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM7);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM8);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(barrel);//выгружаем модель

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

				// выгружаем из памяти транспорт
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car7);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car8);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car9);//выгружаем модель машины(в последствии машина изчезнет)

				// удаляем объекты
				DELETE_OBJECT(&barrel_1);
				DELETE_OBJECT(&barrel_2);
				DELETE_OBJECT(&barrel_3);
				DELETE_OBJECT(&barrel_4);
				DELETE_OBJECT(&barrel_5);
				DELETE_OBJECT(&barrel_6);
				DELETE_OBJECT(&barrel_7);
				DELETE_OBJECT(&barrel_8);
				DELETE_OBJECT(&barrel_9);
				DELETE_OBJECT(&barrel_10);

				// выгружаем бочки
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_4);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_5);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_6);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_7);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_8);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_9);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_10);

				// выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3018 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3019 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3020 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3021 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3022 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3023 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3024 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3025 ); // выгружаем пути транспорта


				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_COK_2" );//Phnom Penh '86
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(2000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +2000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 2000);
					G_DIAZ = 3;
					autosave = 1;
				}

				G_ONMISSION = 0;
			}
		}
//============================== The Fastest Boat ======================================
		else if ((G_ONMISSION == 0) && (G_DIAZ == 3))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(55.627, -13.084, 11.174, &diaz_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DWAYNE);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(diaz_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "LG_05");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 55.627, -13.084, 11.174, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 55.627, -13.084, 11.174, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("COK_3", 15000, CUTSCENE_BARON);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-288.2, -487.5, 9.8, 275.0);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
				blip_on = 0;
				skip = 0;
				cam_on = 0;
				hate = 0;
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

				SET_CHAR_COORDINATES(GetPlayerPed(), 54.81, -8.80, 12.028);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 358.0);
				FORCE_WEATHER_NOW( WEATHER_EXTRA_SUNNY );//устанавливаем погода
				//FORWARD_TO_TIME_OF_DAY(11, 30);//устанавливаем время
				RELEASE_WEATHER();
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "COK_3", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("cok_3");
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

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				SET_MAX_WANTED_LEVEL(0);

				Car car1;
				Ped ped1,ped2,ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20;
				Pickup sweap_1, aid_1;
				int dm, cdm;
				Object strop;
				Cam camera;

				uint CarM1 = MODEL_SQUALO; // самая быстрая лодка
				uint PedM1 = MODEL_M_M_PINDUS_01;// рабочий
				uint PedM2 = MODEL_M_Y_DEALER;// охранник 1
				uint PedM3 = MODEL_M_Y_DORK_02;// охранник 2
				uint PedM4 = MODEL_M_Y_DRUG_01;// охранник 3
				uint stropa = ne_fast_strop;

				LOAD_CHAR_DECISION_MAKER(2, &dm);
				LOAD_COMBAT_DECISION_MAKER(3, &cdm);

				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				//создаём пушку и аптечку
				CREATE_PICKUP_ROTATE(w_m4, 3, 60, -277.321, -937.242, 5.736, -75.0, -80.0, 170.0, &sweap_1);// даём винтовку
				CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -226.841, -952.511, 9.276, -90.0, 0.0, 0.0, &aid_1);//Аптека

				REQUEST_MODEL(stropa);
				while (!HAS_MODEL_LOADED(stropa)) WAIT(0);
				CREATE_OBJECT_NO_OFFSET(stropa, -163.554, -974.8, 14.095, &strop, TRUE);

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(0);
				REQUEST_MODEL(PedM1);//  Бос банды Акул
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Банда акул
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// Банда акул
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM4);// Банда акул
				while (!HAS_MODEL_LOADED(PedM4));////проверка "пед загрузился" если нет то начанаем с начало

				CREATE_CAR(CarM1, -162.55, -975.273, 9.726, &car1, 1);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				SET_CAR_HEADING(car1, -110.5);//градус поворота машины
				CHANGE_CAR_COLOUR( car1, 25, 83 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car1, 113, 0 );//цвет отрожений машины
				FREEZE_CAR_POSITION(car1, 1);

				CREATE_CHAR (26, PedM2, -170.292, -953.067, 7.048, &ped1, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM1, -229.616, -948.984, 8.244, &ped2, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM3, -240.293, -927.673, 7.048, &ped4, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM4, -246.201, -953.496, 7.048, &ped5, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, -184.271, -976.312, 7.048, &ped6, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM3, -236.761, -941.223, 8.278, &ped7, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM4, -201.082, -946.918, 8.278, &ped8, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, -182.784, -950.537, 5.615, &ped9, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM3, -173.649, -977.676, 5.615, &ped10, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM4, -166.085, -978.308, 2.503, &ped11, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, -133.283, -971.511, 2.503, &ped12, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах
				CREATE_CHAR (26, PedM1, -229.135, -949.874, 8.244, &ped13, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM1, -230.281, -949.741, 8.244, &ped14, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, -329.281, -1008.74, 8.244, &ped15, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM3, -329.281, -1008.74, 8.244, &ped16, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM4, -329.281, -1008.74, 8.244, &ped17, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, -329.281, -1008.74, 8.244, &ped18, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM3, -329.281, -1008.74, 8.244, &ped19, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM4, -329.281, -1008.74, 8.244, &ped20, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok

				SET_CHAR_HEADING(ped1, 67.802);
				SET_CHAR_HEADING(ped2, 147.556);
				SET_CHAR_HEADING(ped4, 67.802);
				SET_CHAR_HEADING(ped5, -112.11);
				SET_CHAR_HEADING(ped6, 67.802);
				SET_CHAR_HEADING(ped7, -96.346);
				SET_CHAR_HEADING(ped8, 153.168);
				SET_CHAR_HEADING(ped9, -134.587);
				SET_CHAR_HEADING(ped10, 67.802);
				SET_CHAR_HEADING(ped11, -109.918);
				SET_CHAR_HEADING(ped12, 67.802);
				SET_CHAR_HEADING(ped13, 67.28);
				SET_CHAR_HEADING(ped14, -51.39);

				UpdateWeaponOfPed(ped1, WEAPON_AK47);
				UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_8);
				UpdateWeaponOfPed(ped4, WEAPON_AK47);
				UpdateWeaponOfPed(ped5, WEAPON_AK47);
				UpdateWeaponOfPed(ped6, WEAPON_AK47);
				UpdateWeaponOfPed(ped7, WEAPON_AK47);
				UpdateWeaponOfPed(ped8, WEAPON_AK47);
				UpdateWeaponOfPed(ped9, WEAPON_AK47);
				UpdateWeaponOfPed(ped10, WEAPON_AK47);
				UpdateWeaponOfPed(ped11, WEAPON_AK47);
				UpdateWeaponOfPed(ped12, WEAPON_AK47);
				UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_23);
				UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_23);
				UpdateWeaponOfPed(ped15, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped16, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped17, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped18, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped19, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped20, WEAPON_EPISODIC_12);

				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_EPISODIC_8, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_EPISODIC_23, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_EPISODIC_23, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_EPISODIC_12, TRUE);

				SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
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
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, FALSE);

				ADD_BLIP_FOR_CAR(car1, &diaz_ico);
				CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DESTINATION);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(diaz_ico, 19);   //цвет иконка на радаре (0=белая)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "MO_TARGET");//иконка на радаре называние в истории карты "ЛОДКА"
				PRINT_STRING_IN_STRING("string", "COK3_8", 5000, 1);//~g~Go to the boatyard at the docks and steal the fastest boat.
				SetTime(1000);
				{
					WAIT(3000);
				}
				PRINT_HELP("VCANGE2"); // Thanks part two!
				SetTime(5000);

				//враги патрулирют лодочную мастерскую
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, -223.508, -932.199, 7.048, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped4, -249.613, -952.128, 7.048, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, -207.867, -967.923, 7.048, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, -244.966, -953.561, 7.048, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, -204.882, -953.826, 8.278, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped8, -207.062, -962.801, 8.278, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped9, -165.565, -957.381, 5.615, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped10, -200.412, -967.063, 6.908, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped11, -140.69, -989.188, 2.503, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped12, -174.126, -956.399, 2.408, 2, -2, 3.5);

				while (true)
				{
					WAIT( 0 );
					// патрули
					if (Ped1_c == 0)
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -223.508, -932.199, 7.048, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped1_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, -170.292, -953.067, 7.048, 2, -2, 3.5);
						}
					}
					else if (Ped1_c == 1)
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -170.292, -953.067, 7.048, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped1_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, -223.508, -932.199, 7.048, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped4_c == 0)
					{
						GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -249.613, -952.128, 7.048, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped4_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped4, -240.293, -927.673, 7.048, 2, -2, 3.5);
						}
					}
					else if (Ped4_c == 1)
					{
						GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -240.293, -927.673, 7.048, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped4_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped4, -249.613, -952.128, 7.048, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped5_c == 0)
					{
						GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -207.867, -967.923, 7.048, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped5_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, -246.201, -953.496, 7.048, 2, -2, 3.5);
						}
					}
					else if (Ped5_c == 1)
					{
						GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -246.201, -953.496, 7.048, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped5_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, -207.867, -967.923, 7.048, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped6_c == 0)
					{
						GET_CHAR_COORDINATES(ped6,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -244.966, -953.561, 7.048, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped6_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, -180.457, -978.327, 7.048, 2, -2, 3.5);
						}
					}
					else if (Ped6_c == 1)
					{
						GET_CHAR_COORDINATES(ped6,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -180.457, -978.327, 7.048, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped6_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, -244.966, -953.561, 7.048, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped7_c == 0)
					{
						GET_CHAR_COORDINATES(ped7,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -204.882, -953.826, 8.278, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped7_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, -236.761, -941.223, 8.278, 2, -2, 3.5);
						}
					}
					else if (Ped7_c == 1)
					{
						GET_CHAR_COORDINATES(ped7,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -236.761, -941.223, 8.278, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped7_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, -204.882, -953.826, 8.278, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped8_c == 0)
					{
						GET_CHAR_COORDINATES(ped8,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -207.062, -962.801, 8.278, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped8_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped8, -201.082, -946.918, 8.278, 2, -2, 3.5);
						}
					}
					else if (Ped8_c == 1)
					{
						GET_CHAR_COORDINATES(ped8,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -201.082, -946.918, 8.278, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped8_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped8, -207.062, -962.801, 8.278, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped9_c == 0)
					{
						GET_CHAR_COORDINATES(ped9,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -165.565, -957.381, 5.615, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped9_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped9, -182.784, -950.537, 5.615, 2, -2, 3.5);
						}
					}
					else if (Ped9_c == 1)
					{
						GET_CHAR_COORDINATES(ped9,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -182.784, -950.537, 5.615, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped9_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped9, -165.565, -957.381, 5.615, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped10_c == 0)
					{
						GET_CHAR_COORDINATES(ped10,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -200.412, -967.063, 6.908, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped10_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped10, -173.649, -977.676, 5.615, 2, -2, 3.5);
						}
					}
					else if (Ped10_c == 1)
					{
						GET_CHAR_COORDINATES(ped10,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -173.649, -977.676, 5.615, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped10_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped10, -200.412, -967.063, 6.908, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped11_c == 0)
					{
						GET_CHAR_COORDINATES(ped11,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -140.69, -989.188, 2.503, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped11_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped11, -166.085, -978.308, 2.503, 2, -2, 3.5);
						}
					}
					else if (Ped11_c == 1)
					{
						GET_CHAR_COORDINATES(ped11,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -166.085, -978.308, 2.503, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped11_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped11, -140.69, -989.188, 2.503, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped12_c == 0)
					{
						GET_CHAR_COORDINATES(ped12,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -174.126, -956.399, 2.408, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped12_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped12, -133.283, -971.511, 2.503, 2, -2, 3.5);
						}
					}
					else if (Ped12_c == 1)
					{
						GET_CHAR_COORDINATES(ped12,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -133.283, -971.511, 2.503, &PedR);//проверка "игрок на координатах"
						if (PedR < 4.0)
						{
							Ped12_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped12, -174.126, -956.399, 2.408, 2, -2, 3.5);
						}
					}

					//если игрок в зоне камера на лодку
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -195.725, -955.059, 4.36, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 20.5) && (cam_on == 0))
					{
						//если игрок в зоне камера на лодку
						cam_on = 1;
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замараживаем игрока
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, -161.348, -971.08, 9.819 ); // куда смотрит камера
						SET_CAM_POS			( camera, -184.896, -975.011, 12.363 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );
						PRINT_STRING_IN_STRING("string", "NECOK3_F", 5000, 1);//~COL_NET_12~Find a way to lower the boat.
						SetTime(3000);

						//удяляем камеру тут
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
					}

					// Рабочие атакуют игрока тут
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -207.655, -957.678, 7.159, -216.223, -942.365, 13.585, 0 )) && (hate == 0))// релокация Ленса
					{
						// Рабочие атакуют игрока
						SET_SENSE_RANGE(ped2, 50.0);
						SET_CHAR_DECISION_MAKER(ped2, dm);
						SET_COMBAT_DECISION_MAKER(ped2, cdm);
						SET_CHAR_KEEP_TASK(ped2, 1);
						TASK_COMBAT(ped2, GetPlayerPed());
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, 0);

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


					//чекпойнт сброса лодки
					GET_OBJECT_HEALTH(strop, &Health);
					DRAW_CHECKPOINT( -232.421, -951.538, 7.695, 0.8, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -232.421, -951.538, 7.695, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замараживаем игрока
						SET_CHAR_HEADING(GetPlayerPed(), 156.425);

						//анимация тут
						REQUEST_ANIMS( "amb@atm" );//загружаем файл с анимацией
						while (!HAVE_ANIMS_LOADED( "amb@atm" )) WAIT(0);
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "f_insertcard", "amb@atm", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						SetTime(1500);

						//камера на лодку
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, -161.275, -974.05, 3.093 ); // куда смотрит камера
						SET_CAM_POS			( camera, -163.901, -954.338, 22.13 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						SET_OBJECT_COORDINATES(strop, -0.61, -0.35, -13.61);
						FREEZE_CAR_POSITION(car1, 0);
						SetTime(3000);

						//удяляем камеру тут
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

						SET_CHAR_COORDINATES(ped15, -202.931, -947.621, 8.278);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						SET_CHAR_COORDINATES(ped16, -202.931, -947.621, 8.278);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						SET_CHAR_COORDINATES(ped17, -202.931, -947.621, 8.278);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						SET_CHAR_COORDINATES(ped18, -207.561, -959.525, 8.278);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						SET_CHAR_COORDINATES(ped19, -207.561, -959.525, 8.278);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						SET_CHAR_COORDINATES(ped20, -207.561, -959.525, 8.278);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						break;
					}
					else if (Health < 995)
					{
						SET_OBJECT_COORDINATES(strop, -0.61, -0.35, -13.61);
						FREEZE_CAR_POSITION(car1, 0);

						SET_CHAR_COORDINATES(ped15, -206.1, -945.1, 8.278);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						SET_CHAR_COORDINATES(ped16, -206.1, -945.1, 8.278);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						SET_CHAR_COORDINATES(ped17, -206.1, -945.1, 8.278);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						SET_CHAR_COORDINATES(ped18, -211.2, -958.8, 8.278);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						SET_CHAR_COORDINATES(ped19, -211.2, -958.8, 8.278);// возвращаем игрока на исходную позицию рядом с чекпойнтом
						SET_CHAR_COORDINATES(ped20, -211.2, -958.8, 8.278);// возвращаем игрока на исходную позицию рядом с чекпойнтом

						// Рабочие атакуют игрока
						SET_SENSE_RANGE(ped2, 50.0);
						SET_CHAR_DECISION_MAKER(ped2, dm);
						SET_COMBAT_DECISION_MAKER(ped2, cdm);
						SET_CHAR_KEEP_TASK(ped2, 1);
						TASK_COMBAT(ped2, GetPlayerPed());
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, 0);

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
						break;
					}

					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
					{
						skip = 1;
						break;
					}
					else if (IS_CAR_DEAD(car1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COK3_7", 5000, 1);//~r~You destroyed the boat!
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
					CLEAR_PRINTS();
					PRINT_STRING_IN_STRING("string", "COK3_9", 5000, 1);//~g~Now get into the boat.
					PointN = 1;

					while (true)
					{
						WAIT( 0 );
						if (IS_CHAR_IN_CAR(GetPlayerPed(), car1))
						{
							if (PointN == 1)
							{
								REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_COORD(52.5, -127.149, -0.657, &diaz_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(diaz_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(diaz_ico, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_SCALE(diaz_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "COK3_6", 5000, 1);//~g~Get the boat to the mansion.
								PointN = 0;
							}
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							DRAW_CHECKPOINT( 52.5, -127.149, -0.657, 8.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 52.5, -127.149, -0.657, &PlayR);//проверка "игрок на координатах"
							if (PlayR < 8.5)
							{
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
								DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
								while(true)
								{
									WAIT(0);
									if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
									{
										break;
									}
								}
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, 45.3, -120.512, 1.349 ); // куда смотрит камера
								SET_CAM_POS			( camera, 65.448, -134.244, 6.214 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );

								//паркуем катер
								REQUEST_CAR_RECORDING( 3026 );
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3026 )) WAIT(0);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3026, 0.0, 0.0, 0.0);
								DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
								SetTime(4000);

								STOP_PLAYBACK_RECORDED_CAR(car1);
								REMOVE_CAR_RECORDING( 3025 ); // выгружаем пути транспорта
								DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
								while(true)
								{
									WAIT(0);
									if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
									{
										break;
									}
								}
								
								//удяляем камеру тут
								SET_CAM_BEHIND_PED( GetPlayerPed() );
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								END_CAM_COMMANDS( &camera );
								SET_WIDESCREEN_BORDERS( 0 );
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
								WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 58.38, -122.03, 2.5);//телепартируем из катера
								ALTER_WANTED_LEVEL(GetPlayerIndex(), 0);
								APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
								SetTime(1000);
								DO_SCREEN_FADE_IN( 800 );// убирается затемнение экрана
								skip = 2;
								break;
							}
						}
						else
						{
							if (PointN == 0)
							{
								REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CAR(car1, &diaz_ico);
								CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DESTINATION);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(diaz_ico, 19);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "MO_TARGET");//иконка на радаре называние в истории карты "ЛОДКА"
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NECOK3_R", 5000, 1);//~COL_NET_12~Return to the boat.
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
							PRINT_STRING_IN_STRING("string", "COK3_7", 5000, 1);//~r~You destroyed the boat!
							skip = 1;
							break;
						}
					}
				}

				// завершение миссии
				REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
				REMOVE_PICKUP(sweap_1);// выгружаем оружие
				REMOVE_PICKUP(aid_1);// выгружаем оружие
				
				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(stropa);//выгружаем модель

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
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

				// удаляем объекты
				DELETE_OBJECT(&strop);

				// выгружаем стропы
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&strop);

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_COK_3" );//The Fastest Boat
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(4000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +4000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 4000);
					G_DIAZ = 4;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== Supply & Demand ======================================
		else if ((G_ONMISSION == 0) && (G_DIAZ == 4))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(55.627, -13.084, 11.174, &diaz_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DWAYNE);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(diaz_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "LG_05");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 55.627, -13.084, 11.174, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 55.627, -13.084, 11.174, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("COK_4", 15000, CUTSCENE_BARON);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-288.2, -487.5, 9.8, 275.0);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
				blip_on = 0;
				skip = 0;
				explo3 = 0;
				explo4 = 0;
				explo5 = 0;
				explo6 = 0;
				res_on = 0;
				res = 0;
				hate = 0;
				text1 = 0;
				play = 0;
				play_Speech = 0;
				carHUD_x = 0.8421875;
				carHUD_w = 0.0739583;

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

				SET_CHAR_COORDINATES(GetPlayerPed(), 21.402, -83.133, 10.136);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -80.802);
				SET_CAR_DENSITY_MULTIPLIER(0);// отключаем пути
				SET_MAX_WANTED_LEVEL(0);
				

				Car car1, car2, car3, car4, car5, car6, car7;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19;
				Texture fon, car;
				Object barrel_1, barrel_2, barrel_3;
				Cam camera;

				// грузим всё тут
				uint CarM1 = MODEL_MARQUIS;// барыга
				uint CarM2 = MODEL_DINGHY;// конкуренты
				uint CarM3 = MODEL_SQUALO;// игрок
				uint CarM4 = MODEL_MAVERICK;// вертуха
				uint PedM1 = MODEL_IG_LILJACOB;// Ланс
				uint PedM2 = MODEL_M_Y_GLAT_LO_01;// Кубинец 1

				uint barrel = barrel4;
				uint boatHEAL, vehHEAL;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				car = GET_TEXTURE( textur, "boat_hud" );

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(0);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(0);
				REQUEST_MODEL(CarM3);
				while (!HAS_MODEL_LOADED(CarM3)) WAIT(0);
				REQUEST_MODEL(CarM4);
				while (!HAS_MODEL_LOADED(CarM4)) WAIT(0);
				REQUEST_MODEL(PedM1);
				while (!HAS_MODEL_LOADED(PedM1)) WAIT(0);
				REQUEST_MODEL(PedM2);
				while (!HAS_MODEL_LOADED(PedM2)) WAIT(0);
				REQUEST_MODEL(barrel);
				while (!HAS_MODEL_LOADED(barrel)) WAIT(0);

				//Грузим пути
				REQUEST_CAR_RECORDING( 3027 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3027 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3028 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3028 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3029 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3029 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3030 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3030 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3031 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3031 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3032 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3032 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3033 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3033 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3034 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3034 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3035 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3035 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3036 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3036 )) WAIT(0);

				// Лодка SQUALO;
				CREATE_CAR(CarM3, 57.78, -127.52, 1.4, &car1, TRUE);
				SET_CAR_HEADING(car1, 270.0);
				CHANGE_CAR_COLOUR( car1, 25, 83 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car1, 113, 0 );//цвет отрожений машины
				SET_CAR_HEALTH(car1, 2000);
				SET_CAR_ENGINE_ON(car1, 1, 1);
				LOCK_CAR_DOORS(car1, 3); //блокируем двери автомобиля для игрока

				CREATE_CAR(CarM1, 752.88, 1105.45, 0.9, &car2, TRUE);// барыга
				SET_CAR_HEADING(car2, -18.916);

				CREATE_CAR(CarM4, 448.778, 1692.379, 14.872, &car3, TRUE);// вертуха
				SET_CAR_HEADING(car3, 180.0);

				// соперники
				CREATE_CAR(CarM2, 391.0, 1644.5, 9.5, &car4, TRUE);
				CREATE_CAR(CarM2, 388.3, 1644.5, 9.5, &car5, TRUE);
				CREATE_CAR(CarM2, 385.6, 1644.5, 9.5, &car6, TRUE);
				CREATE_CAR(CarM2, 382.8, 1644.5, 9.5, &car7, TRUE);

				// создаём педов тут
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//Ленс
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM2, &ped2);// Водитель верталёта
				CREATE_CHAR_INSIDE_CAR(car4, 1, PedM2, &ped3);// Водитель лодки 1
				CREATE_CHAR_INSIDE_CAR(car5, 1, PedM2, &ped4);// Водитель лодки 2
				CREATE_CHAR_INSIDE_CAR(car6, 1, PedM2, &ped5);// Водитель лодки 3
				CREATE_CHAR_INSIDE_CAR(car7, 1, PedM2, &ped6);// Водитель лодки 4

				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM2, 1, &ped7);// Пассажир верталёта 1
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM2, 2, &ped8);// Пассажир верталёта 2
				CREATE_CHAR_AS_PASSENGER(car4, 1, PedM2, 0, &ped9);// Пассажир лодки 1
				CREATE_CHAR_AS_PASSENGER(car5, 1, PedM2, 0, &ped10);// Пассажир лодки 2
				CREATE_CHAR_AS_PASSENGER(car6, 1, PedM2, 0, &ped11);// Пассажир лодки 3
				CREATE_CHAR_AS_PASSENGER(car7, 1, PedM2, 0, &ped12);// Пассажир лодки 4

				CREATE_CHAR (26, PedM2, 285.901, -785.033, 5.06, &ped13, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, 289.048, -785.033, 5.06, &ped14, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, 292.287, -785.033, 5.06, &ped15, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, 293.268, -785.033, 5.06, &ped16, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, 295.563, -785.033, 5.06, &ped17, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, 296.544, -785.033, 5.06, &ped18, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok
				CREATE_CHAR (26, PedM2, 299.098, -785.033, 5.06, &ped19, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах//ok

				// создаём бочки
				CREATE_OBJECT_NO_OFFSET(barrel, 286.008, -787.416, 5.445, &barrel_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 289.167, -787.416, 5.445, &barrel_2, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 292.585, -787.416, 5.445, &barrel_3, TRUE);

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "COK_4A", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("cok_4a");
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
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				FORCE_WEATHER_NOW( WEATHER_SUNNY );//устанавливаем погоду
				FORWARD_TO_TIME_OF_DAY(18, 20);//устанавливаем время

				ADD_BLIP_FOR_COORD(54.246, -116.908, 4.154, &diaz_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(diaz_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(diaz_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(diaz_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "NE_POINT");//иконка на радаре называние в истории карты "магазин одежды"
				PRINT_STRING_IN_STRING("string", "COK4_31", 5000, 1);//~g~Go to the fastest boat at the jetty!

				UpdateWeaponOfPed(ped7, WEAPON_M4);
				UpdateWeaponOfPed(ped8, WEAPON_M4);
				UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_13);

				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_M4, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_M4, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_13, TRUE);

				SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);

				SET_CHAR_RELATIONSHIP(ped7, 5, 0);
				SET_CHAR_RELATIONSHIP(ped8, 5, 0);
				SET_CHAR_RELATIONSHIP(ped9, 5, 0);
				SET_CHAR_RELATIONSHIP(ped10, 5, 0);
				SET_CHAR_RELATIONSHIP(ped11, 5, 0);
				SET_CHAR_RELATIONSHIP(ped12, 5, 0);

				SET_SENSE_RANGE(ped7, 55.0);
				SET_SENSE_RANGE(ped8, 55.0);
				SET_SENSE_RANGE(ped9, 55.0);
				SET_SENSE_RANGE(ped10, 55.0);
				SET_SENSE_RANGE(ped11, 55.0);
				SET_SENSE_RANGE(ped12, 55.0);

				SET_CHAR_KEEP_TASK(ped1, 1);
				SET_CHAR_KEEP_TASK(ped2, 1);
				SET_CHAR_KEEP_TASK(ped3, 1);
				SET_CHAR_KEEP_TASK(ped4, 1);
				SET_CHAR_KEEP_TASK(ped5, 1);
				SET_CHAR_KEEP_TASK(ped6, 1);
				SET_CHAR_KEEP_TASK(ped7, 1);
				SET_CHAR_KEEP_TASK(ped8, 1);
				SET_CHAR_KEEP_TASK(ped9, 1);
				SET_CHAR_KEEP_TASK(ped10, 1);
				SET_CHAR_KEEP_TASK(ped11, 1);
				SET_CHAR_KEEP_TASK(ped12, 1);

				while (true)
				{
					WAIT( 0 );
					DRAW_CHECKPOINT( 54.246, -116.908, 4.154, 2.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 54.246, -116.908, 4.154, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
						DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
						while(true)
						{
							WAIT(0);
							if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
							{
								break;
							}
						}
						SET_CAR_COORDINATES(car1, 96.83, -127.9, 1.5);
						FORWARD_TO_TIME_OF_DAY(18, 30);//устанавливаем время

						//==============================
						//катсцена
						LOAD_ADDITIONAL_TEXT( "COK_4A2", 6 ); // загружаем субтитры из *.GTX
						START_CUTSCENE_NOW("cok_4a2");
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

						// Воспроизводим пути
						START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car4, 3027, 0.0, 0.0, -0.515);
						START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car5, 3028, 0.0, 0.0, -0.515);
						START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car6, 3029, 0.0, 0.0, -0.515);
						START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car7, 3030, 0.0, 0.0, -0.515);

						DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 156.604, -174.536, 5.136 ); // куда смотрит камера
						SET_CAM_POS			( camera, 118.491, -182.894, 6.453 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						SetTime(1500);
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R2_CI", "COK4_8", 0, 0);//We got some competition!
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(2500);

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COK4_28", 5000, 1);//~g~Get to the yacht before the other boats do!
						SetTime(1000);

						APPLY_FORCE_TO_CAR( car1, 1, 0, 15, -1.5, 0, 0, 0, 1, 1, 1, 1 );
						LOCK_CAR_DOORS(car1, 1); //убираем блокировку дверей

						DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
						while(true)
						{
							WAIT(0);
							if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
							{
								break;
							}
						}

						//убираем камеру
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

						WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car1, 0);
						WARP_CHAR_INTO_CAR(GetPlayerPed(), car1);
						DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
					{
						skip = 1;
						break;
					}
					else if (IS_CAR_DEAD(car1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COK3_7", 5000, 1);//~r~You destroyed the boat!
						skip = 1;
						break;
					}
					else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен. 
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
						skip = 1;
						break;
					}
				}

				if (skip == 0)
				{
					UpdateWeaponOfPed(ped1, WEAPON_MP5);
					SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_MP5, TRUE);

					SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
					SET_CHAR_RELATIONSHIP(ped1, 5, 5);
					SET_SENSE_RANGE(ped1, 75.0);

					ADD_BLIP_FOR_CAR(car2, &diaz_ico);
					CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
					CHANGE_BLIP_SCALE(diaz_ico, 1.1); // масштаб иконки на радаре
					CHANGE_BLIP_COLOUR(diaz_ico, 5);   //цвет иконка на радаре (0=белая)
					CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "NE_POINT");//иконка на радаре называние в истории карты "Курьер"
					text1 = 1;

					while (true)
					{
						WAIT( 0 );
						SET_CHAR_INVINCIBLE(ped1, 1);
						SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// Игрок бессмертный

						// ----- Диалог
						if (text1 == 1)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R2_CJ", "COK4_1", 0, 0);//So Tommy, we know it was Diaz busted our deal..
							START_SCRIPT_CONVERSATION(1, 1);
							play_Speech = 1;
							text1 = 2;
						}
						else if (text1 == 2)
						{
							if (play_Speech == 0)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R2_CK", "COK4_3", 0, 0);//So why the hell are we running errands for him?
								START_SCRIPT_CONVERSATION(1, 1);
								play_Speech = 1;
								text1 = 3;
							}
						}
						else if (text1 == 3)
						{
							if (play_Speech == 0)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R2_CK_QQQ1", "COK4_4", 0, 0);//The more we learn now, the less we have to learn when we take this town over!
								START_SCRIPT_CONVERSATION(1, 1);
								play_Speech = 1;
								text1 = 4;
							}
						}
						else if (text1 == 4)
						{
							if (play_Speech == 0)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R2_CL", "COK4_5", 0, 0);//I like your style, man. Real fresh.
								START_SCRIPT_CONVERSATION(1, 1);
								play_Speech = 1;
								text1 = 5;
							}
						}
						else if (text1 == 5)
						{
							if (TIMERB() > 2500)
							{
								text1 = 6;
							}
						}
						else if (text1 == 6)
						{
							if (play_Speech == 0)
							{
								if (IS_CHAR_SHOOTING_IN_AREA(ped1, PlayX-25, PlayY-25, PlayX+25, PlayY+25, 0))//проверка Игрок начал пальбу
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R2_CM", "COK4_9A", 0, 0);//It's time for the Lance Vance Dance!
									START_SCRIPT_CONVERSATION(1, 1);
									play_Speech = 1;
									text1 = 7;
								}
							}
						}

						if (play_Speech == 1)
						{
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								play_Speech = 0;
							}
						}
						
						if (!IS_CHAR_SITTING_IN_ANY_CAR(ped1))
						{
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car1, 0);
							SET_CHAR_KEEP_TASK(ped1, 1);
						}

						// стоп пути
						if ((IS_CHAR_DEAD(ped3)) && (explo3 == 0))
						{
							explo3 = 1;
							STOP_PLAYBACK_RECORDED_CAR(car4);
						}
						else if ((IS_CHAR_DEAD(ped4)) && (explo4 == 0))
						{
							explo4 = 1;
							STOP_PLAYBACK_RECORDED_CAR(car5);
						}
						else if ((IS_CHAR_DEAD(ped5)) && (explo5 == 0))
						{
							explo5 = 1;
							STOP_PLAYBACK_RECORDED_CAR(car6);
						}
						else if ((IS_CHAR_DEAD(ped6)) && (explo6 == 0))
						{
							explo6 = 1;
							STOP_PLAYBACK_RECORDED_CAR(car7);
						}

						// проверка соперники опередили игрока
						GET_CHAR_COORDINATES(ped3,  &PedX, &PedY, &PedZ);//вписываем координаты водитель лодки1 в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 752.88, 1105.45, 0.9, &PedR);//проверка "игрок на координатах"
						if ( PedR < 20.5 )
						{
							hate = 1;
						}
						GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//вписываем координаты водитель лодки1 в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 752.88, 1105.45, 0.9, &PedR);//проверка "игрок на координатах"
						if ( PedR < 20.5 )
						{
							hate = 1;
						}
						GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//вписываем координаты водитель лодки1 в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 752.88, 1105.45, 0.9, &PedR);//проверка "игрок на координатах"
						if ( PedR < 20.5 )
						{
							hate = 1;
						}
						GET_CHAR_COORDINATES(ped6,  &PedX, &PedY, &PedZ);//вписываем координаты водитель лодки1 в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 752.88, 1105.45, 0.9, &PedR);//проверка "игрок на координатах"
						if ( PedR < 20.5 )
						{
							hate = 1;
						}

						// Вернитесь в лодку тут
						if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (text1 == 7))
						{
							if (res == 0)
							{
								REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CAR(car1, &diaz_ico);
								CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DESTINATION);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(diaz_ico, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "MO_TARGET");//иконка на радаре называние в истории карты "ЛОДКА"
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NECOK3_R", 5000, 1);//~COL_NET_12~Return to the boat.
								res = 1;
							}
						}
						else
						{
							if ((res == 1) && (text1 == 7))
							{
								REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CAR(car2, &diaz_ico);
								CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
								CHANGE_BLIP_SCALE(diaz_ico, 1.1); // масштаб иконки на радаре
								CHANGE_BLIP_COLOUR(diaz_ico, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "NE_POINT");//иконка на радаре называние в истории карты "Курьер"
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "COK4_28", 5000, 1);//~g~Get to the yacht before the other boats do!
								res = 0;
							}
						}

						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 752.88, 1105.45, 0.9, &PlayR);//проверка "игрок на координатах"
						if ( PlayR < 20.5 )
						{
							break;
						}
						else if (hate == 1)
						{
							// переходим к провалу миссии
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						else if (IS_CAR_DEAD(car1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COK3_7", 5000, 1);//~r~You destroyed the boat!
							skip = 1;
							break;
						}
						else if (IS_CAR_DEAD(car2))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK4_D", 5000, 1);//~r~Courier is dead, mission failed.
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен. 
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;
							break;
						}
						else if ((IS_CAR_UPSIDEDOWN(car1)) && ( res_on == 0))
						{
							SETTIMERB( 0 );
							res_on = 1;
						}

						if ( res_on == 1)
						{
							if (TIMERB() > 2000)
							{
								if (IS_CAR_UPSIDEDOWN(car1))
								{
									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "COK3_7", 5000, 1);//~r~You destroyed the boat!
									skip = 1;
									break;
								}
								else
								{
									res_on = 0;
								}
							}
						}
					}
				}

				if (skip == 0)
				{
					REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
					FIX_CAR(car1);
					SET_CAR_HEALTH(car1, 5500);
					SET_ENGINE_HEALTH(car1, 7500);

					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
					DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
					while(true)
					{
						WAIT(0);
						if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							break;
						}
					}

					STOP_PLAYBACK_RECORDED_CAR(car4);
					STOP_PLAYBACK_RECORDED_CAR(car5);
					STOP_PLAYBACK_RECORDED_CAR(car6);
					STOP_PLAYBACK_RECORDED_CAR(car7);

					//SET_CAR_COORDINATES(car4, 1.1, 0.1, 0.1);
					//SET_CAR_COORDINATES(car5, 2.1, 0.1, 0.1);
					//SET_CAR_COORDINATES(car6, 3.1, 0.1, 0.1);
					//SET_CAR_COORDINATES(car7, 4.1, 0.1, 0.1);

					// прячим тела
					//SET_CHAR_COORDINATES(ped3, 0.1, 1.1, 0.1);// возвращаем игрока на исходную позицию рядом с чекпойнтом
					//SET_CHAR_COORDINATES(ped4, 0.1, 2.1, 0.1);// возвращаем игрока на исходную позицию рядом с чекпойнтом
					//SET_CHAR_COORDINATES(ped5, 0.1, 3.1, 0.1);// возвращаем игрока на исходную позицию рядом с чекпойнтом
					//SET_CHAR_COORDINATES(ped6, 0.1, 4.1, 0.1);// возвращаем игрока на исходную позицию рядом с чекпойнтом
					//SET_CHAR_COORDINATES(ped9, 1.1, 0.1, 0.1);// возвращаем игрока на исходную позицию рядом с чекпойнтом
					//SET_CHAR_COORDINATES(ped10, 2.1, 0.1, 0.1);// возвращаем игрока на исходную позицию рядом с чекпойнтом
					//SET_CHAR_COORDINATES(ped11, 3.1, 0.1, 0.1);// возвращаем игрока на исходную позицию рядом с чекпойнтом
					//SET_CHAR_COORDINATES(ped12, 4.1, 0.1, 0.1);// возвращаем игрока на исходную позицию рядом с чекпойнтом

					// удаляем педов
					DELETE_CHAR(&ped3);//выгружаем модель педа(в последствии пед изчезнет)
					DELETE_CHAR(&ped4);//выгружаем модель педа(в последствии пед изчезнет)
					DELETE_CHAR(&ped5);//выгружаем модель педа(в последствии пед изчезнет)
					DELETE_CHAR(&ped6);//выгружаем модель педа(в последствии пед изчезнет)
					DELETE_CHAR(&ped9);//выгружаем модель педа(в последствии пед изчезнет)
					DELETE_CHAR(&ped10);//выгружаем модель педа(в последствии пед изчезнет)
					DELETE_CHAR(&ped11);//выгружаем модель педа(в последствии пед изчезнет)
					DELETE_CHAR(&ped12);//выгружаем модель педа(в последствии пед изчезнет)

					// уладяем лодки
					DELETE_CAR(&car4);//выгружаем модель машины(в последствии машина изчезнет)
					DELETE_CAR(&car5);//выгружаем модель машины(в последствии машина изчезнет)
					DELETE_CAR(&car6);//выгружаем модель машины(в последствии машина изчезнет)
					DELETE_CAR(&car7);//выгружаем модель машины(в последствии машина изчезнет)

					// грузим новые лодки
					CREATE_CAR(CarM2, 391.0, 1644.5, 9.5, &car4, TRUE);
					CREATE_CAR(CarM2, 388.3, 1644.5, 9.5, &car5, TRUE);
					CREATE_CAR(CarM2, 385.6, 1644.5, 9.5, &car6, TRUE);
					CREATE_CAR(CarM2, 382.8, 1644.5, 9.5, &car7, TRUE);

					// грузим новых педов
					CREATE_CHAR_INSIDE_CAR(car4, 1, PedM2, &ped3);// Водитель лодки 1
					CREATE_CHAR_INSIDE_CAR(car5, 1, PedM2, &ped4);// Водитель лодки 2
					CREATE_CHAR_INSIDE_CAR(car6, 1, PedM2, &ped5);// Водитель лодки 3
					CREATE_CHAR_INSIDE_CAR(car7, 1, PedM2, &ped6);// Водитель лодки 4

					CREATE_CHAR_AS_PASSENGER(car4, 1, PedM2, 0, &ped9);// Пассажир лодки 1
					CREATE_CHAR_AS_PASSENGER(car5, 1, PedM2, 0, &ped10);// Пассажир лодки 2
					CREATE_CHAR_AS_PASSENGER(car6, 1, PedM2, 0, &ped11);// Пассажир лодки 3
					CREATE_CHAR_AS_PASSENGER(car7, 1, PedM2, 0, &ped12);// Пассажир лодки 4
					WARP_CHAR_INTO_CAR_AS_PASSENGER(ped13, car4, 2);
					WARP_CHAR_INTO_CAR_AS_PASSENGER(ped14, car5, 2);

					// создаём педов на пристани
					SET_CHAR_COORDINATES(ped15, 830.5306, 338.5532, 2.391025);
					SET_CHAR_COORDINATES(ped16, 830.9352, 345.6001, 2.391025);
					SET_CHAR_COORDINATES(ped17, 833.6221, 353.6065, 2.391025);
					SET_CHAR_COORDINATES(ped18, 834.0308, 360.2887, 2.391025);
					SET_CHAR_COORDINATES(ped19, 834.4027, 370.4794, 2.391025);
					SET_CHAR_HEADING(ped15, -90.0);
					SET_CHAR_HEADING(ped16, -90.0);
					SET_CHAR_HEADING(ped17, -90.0);
					SET_CHAR_HEADING(ped18, -90.0);
					SET_CHAR_HEADING(ped19, -90.0);

					// переносим бочки
					SET_OBJECT_COORDINATES(barrel_1, 828.001, 341.093, 1.899);
					SET_OBJECT_COORDINATES(barrel_2, 829.436, 353.956, 1.899);
					SET_OBJECT_COORDINATES(barrel_3, 830.827, 367.108, 1.899);

					UpdateWeaponOfPed(GetPlayerPed(), WEAPON_AK47);
					UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_13);
					UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_13);
					UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_12);
					UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_12);
					UpdateWeaponOfPed(ped13, WEAPON_AK47);
					UpdateWeaponOfPed(ped14, WEAPON_AK47);

					SET_CHAR_KEEP_TASK(ped2, 1);
					SET_CHAR_KEEP_TASK(ped3, 1);
					SET_CHAR_KEEP_TASK(ped4, 1);
					SET_CHAR_KEEP_TASK(ped5, 1);
					SET_CHAR_KEEP_TASK(ped6, 1);
					SET_CHAR_KEEP_TASK(ped7, 1);
					SET_CHAR_KEEP_TASK(ped8, 1);
					SET_CHAR_KEEP_TASK(ped9, 1);
					SET_CHAR_KEEP_TASK(ped10, 1);
					SET_CHAR_KEEP_TASK(ped11, 1);
					SET_CHAR_KEEP_TASK(ped12, 1);
					SET_CHAR_KEEP_TASK(ped13, 1);
					SET_CHAR_KEEP_TASK(ped14, 1);

					SET_CHAR_HEALTH(ped2, 200);
					SET_CHAR_HEALTH(ped3, 200);
					SET_CHAR_HEALTH(ped4, 200);
					SET_CHAR_HEALTH(ped5, 200);
					SET_CHAR_HEALTH(ped6, 200);
					SET_CHAR_HEALTH(ped7, 200);
					SET_CHAR_HEALTH(ped8, 200);
					SET_CHAR_HEALTH(ped9, 200);
					SET_CHAR_HEALTH(ped10, 200);
					SET_CHAR_HEALTH(ped11, 200);
					SET_CHAR_HEALTH(ped12, 200);
					SET_CHAR_HEALTH(ped13, 200);
					SET_CHAR_HEALTH(ped14, 200);

					SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_12, TRUE);
					SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_12, TRUE);
					SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_MP5, TRUE);
					SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_MP5, TRUE);
					SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_AK47, TRUE);
					SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_AK47, TRUE);

					SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);

					SET_CHAR_RELATIONSHIP(ped9, 5, 0);
					SET_CHAR_RELATIONSHIP(ped10, 5, 0);
					SET_CHAR_RELATIONSHIP(ped11, 5, 0);
					SET_CHAR_RELATIONSHIP(ped12, 5, 0);
					SET_CHAR_RELATIONSHIP(ped13, 5, 0);
					SET_CHAR_RELATIONSHIP(ped14, 5, 0);

					SET_SENSE_RANGE(ped9, 55.0);
					SET_SENSE_RANGE(ped10, 55.0);
					SET_SENSE_RANGE(ped11, 55.0);
					SET_SENSE_RANGE(ped12, 55.0);
					SET_SENSE_RANGE(ped13, 55.0);
					SET_SENSE_RANGE(ped14, 55.0);

					UpdateWeaponOfPed(ped15, WEAPON_AK47);
					UpdateWeaponOfPed(ped16, WEAPON_EPISODIC_12);
					UpdateWeaponOfPed(ped17, WEAPON_AK47);
					UpdateWeaponOfPed(ped18, WEAPON_AK47);
					UpdateWeaponOfPed(ped19, WEAPON_MP5);

					SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_AK47, TRUE);
					SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_EPISODIC_12, TRUE);
					SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_AK47, TRUE);
					SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_AK47, TRUE);
					SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_MP5, TRUE);

					SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped16, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped17, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped18, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped19, 5);

					SET_CHAR_RELATIONSHIP(ped1, 0, 0);
					SET_CHAR_RELATIONSHIP(ped15, 5, 0);
					SET_CHAR_RELATIONSHIP(ped16, 5, 0);
					SET_CHAR_RELATIONSHIP(ped17, 5, 0);
					SET_CHAR_RELATIONSHIP(ped18, 5, 0);
					SET_CHAR_RELATIONSHIP(ped19, 5, 0);

					SET_SENSE_RANGE(ped15, 55.0);
					SET_SENSE_RANGE(ped16, 55.0);
					SET_SENSE_RANGE(ped17, 55.0);
					SET_SENSE_RANGE(ped18, 55.0);
					SET_SENSE_RANGE(ped19, 55.0);
					SET_SENSE_RANGE(ped1, 0.01);

					FORWARD_TO_TIME_OF_DAY(19, 20);//устанавливаем время

					//============= катсцена =================
					LOAD_ADDITIONAL_TEXT( "COK_4B", 6 ); // загружаем субтитры из *.GTX
					START_CUTSCENE_NOW("cok_4b");
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

					// воспроизводим пути погони
					WARP_CHAR_INTO_CAR_AS_PASSENGER(GetPlayerPed(), car1, 1);
					START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3031, 0.0, 0.0, -0.515);
					SetTime(800);
					START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car4, 3032, 0.0, 0.0, -0.515);																		   
					START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 3034, 0.0, 0.0, -0.515);
					START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car5, 3033, 0.0, 0.0, -0.515);																		   
					START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car6, 3035, 0.0, 0.0, -0.515);
					START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car7, 3036, 0.0, 0.0, -0.515); //removed extra two boats
					WARP_CHAR_INTO_CAR(ped1, car1);
					WARP_CHAR_INTO_CAR_AS_PASSENGER(GetPlayerPed(), car1, 0);

					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//замораживаем игрока
					explo2 = 0;
					explo3 = 0;
					explo4 = 0;
					explo5 = 0;
					explo6 = 0;
					explo7 = 0;
					explo8 = 0;
					explo9 = 0;
					text1 = 1;
					play = 0;

					while (true)
					{
						WAIT( 0 );
						GET_CAR_HEALTH(car1, &boatHEAL);
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты водитель лодки1 в переменную

						// Игрок покинул лодку
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, PlayX, PlayY, PlayZ, &PlayR);//проверка "игрок на координатах"
						if ((boatHEAL < 10) || ( PlayR > 80.0 ))
						{
							SET_CHAR_INVINCIBLE(ped1, 0);
							SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// Игрок смертный
							EXPLODE_CAR(car1, 1, 1);
							WAIT(100);
							if (!IS_CHAR_DEAD(GetPlayerPed()))
							{
								PRINT_STRING_IN_STRING("string", "COK3_7", 5000, 1);//~r~You destroyed the boat!
							}
							break;
							skip = 1;
						}
						else
						{
							SET_CHAR_INVINCIBLE(ped1, 1);
							SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// Игрок бессмертный
						}

						// смертность соперников
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 765.95, 636.33, 1.7, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 10.0 ) && (explo2 == 0))
						{
							UpdateWeaponOfPed(GetPlayerPed(), WEAPON_AK47);
							//SET_CHAR_INVINCIBLE(ped3, 0);
							//SET_CHAR_INVINCIBLE(ped4, 0);
							explo2 = 1;
						}
						//else if (explo2 == 0)
						//{
						//	SET_CHAR_INVINCIBLE(ped3, 1);
						//	SET_CHAR_INVINCIBLE(ped4, 1);
						//}

						// выкрики Томми
						if (text1 == 1)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_CM_QQQ1", "COK4_12", 0, 0);//Watch yourself, they're coming from all over!
							START_SCRIPT_CONVERSATION(1, 1);
							play_Speech = 1;
							text1 = 2;
						}
						else if (text1 == 2)
						{
							if (play_Speech == 0)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R2_CN", "COK4_13", 0, 0);//Got 'em. Head for Diaz's as fast as you can!
								START_SCRIPT_CONVERSATION(1, 1);
								play_Speech = 1;
								text1 = 3;
							}
						}
						else if (text1 == 3)
						{
							if (play_Speech == 0)
							{
								if (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PlayX-25, PlayY-25, PlayX+25, PlayY+25, 0))//проверка Игрок начал пальбу
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R2_DA", "COK4_16", 0, 0);//Eat it! EAT IT!
									START_SCRIPT_CONVERSATION(1, 1);
									play_Speech = 1;
									text1 = 4;
								}
							}
						}
						else if (text1 == 4)
						{
							if (play_Speech == 0)
							{
								if (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PlayX-25, PlayY-25, PlayX+25, PlayY+25, 0))//проверка Игрок начал пальбу
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R2_DB", "COK4_15", 0, 0);//Sleep with the fish!
									START_SCRIPT_CONVERSATION(1, 1);
									play_Speech = 1;
									text1 = 5;
								}
							}
						}
						else if (text1 == 5)
						{
							if (play_Speech == 0)
							{
								if (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PlayX-25, PlayY-25, PlayX+25, PlayY+25, 0))//проверка Игрок начал пальбу
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R2_DC", "COK4_14", 0, 0);//You want some of this?!
									START_SCRIPT_CONVERSATION(1, 1);
									play_Speech = 1;
									text1 = 6;
								}
							}
						}
						else if (text1 == 6)
						{
							if (play_Speech == 0)
							{
								GET_DISTANCE_BETWEEN_COORDS_3D(  PlayX, PlayY, PlayZ, 846.84, 438.12, 1.7, &PlayR);//проверка "игрок на координатах"
								if ( PlayR < 10.0 )
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R2_DD", "COK4_20", 0, 0);//There are gunmen on that jetty!
									START_SCRIPT_CONVERSATION(1, 1);
									play_Speech = 1;
									text1 = 7;
								}
							}
						}
						else if (text1 == 7)
						{
							if (play_Speech == 0)
							{
								GET_DISTANCE_BETWEEN_COORDS_3D(  PlayX, PlayY, PlayZ, 727.99, 85.03, 1.7, &PlayR);//проверка "игрок на координатах"
								if ( PlayR < 10.0 )
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R2_EA", "COK4_19", 0, 0);//More trouble up ahead!
									START_SCRIPT_CONVERSATION(1, 1);
									play_Speech = 1;
									text1 = 8;
								}
							}
						}
						

						if (play_Speech == 1)
						{
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								play_Speech = 0;
							}
						}

						// ------------------- HUD -------------------
						DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
						DRAW_SPRITE( car, 0.8765625, 0.80925926, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.
						DRAW_SPRITE( 0, 0.8421875, 0.80925926, 0.0739583, 0.014, 0.0, 27, 89, 130, 255 );// рисуем фоновую текстуру.

						if (boatHEAL < 5)
						{
							carH1 = 0;
						}
						else
						{
							carH1 = boatHEAL;
						}
						carH2 = carHUD_w/5500;
						carH3 = carH2*carH1;
						carHUD_y1 = carHUD_w-carH3;
						carHUD_y2 = carHUD_y1/2;
						carHUD_y3 = carHUD_x-carHUD_y2;
						DRAW_SPRITE( 0, carHUD_y3, 0.80925926, carH3, 0.014, 0.0, 97, 194, 247, 255 );// рисуем фоновую текстуру.

						// взрыв вертолёта
						GET_CAR_HEALTH(car3, &vehHEAL);
						if ((vehHEAL < 600) && (explo9 == 0))
						{
							EXPLODE_CAR(car3, 1, 1);
							explo9 = 1;
						}

						// пересаживаем второго стрелка с верталёта
						if ((IS_CHAR_DEAD(ped8)) && (explo8 == 0))
						{
							if ((!IS_CHAR_DEAD(ped7)) && (explo7 == 0))
							{
								TASK_LEAVE_CAR(ped8, car3);
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped7, car3, 2);
								explo7 = 1;
							}
							explo8 = 1;
						}

						// стоп путей
						if ((IS_CHAR_DEAD(ped3)) && (explo3 == 0))
						{
							explo3 = 1;
							STOP_PLAYBACK_RECORDED_CAR(car4);
						}
						if ((IS_CHAR_DEAD(ped4)) && (explo4 == 0))
						{
							explo4 = 1;
							STOP_PLAYBACK_RECORDED_CAR(car5);
						}
						if ((IS_CHAR_DEAD(ped5)) && (explo5 == 0))
						{
							explo5 = 1;
							STOP_PLAYBACK_RECORDED_CAR(car6);
						}
						if ((IS_CHAR_DEAD(ped6)) && (explo6 == 0))
						{
							explo6 = 1;
							STOP_PLAYBACK_RECORDED_CAR(car7);
						}

						// финалим миссию
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 99.77, -128.93, 1.5, &PedR);//проверка "игрок на координатах"
						if ( PedR < 10.0 )
						{
							FIX_CAR(car1);
							STOP_PLAYBACK_RECORDED_CAR(car1);
							STOP_PLAYBACK_RECORDED_CAR(car3);
							STOP_PLAYBACK_RECORDED_CAR(car4);
							STOP_PLAYBACK_RECORDED_CAR(car5);
							STOP_PLAYBACK_RECORDED_CAR(car6);
							STOP_PLAYBACK_RECORDED_CAR(car7);
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
								{
									break;
								}
							}

							// прячем вертолёт и лодки соперников
							SET_CAR_COORDINATES(car1, 57.78, -127.52, 1.4);
							SET_CAR_COORDINATES(car3, 752.88, 1105.45, 0.9);
							SET_CAR_COORDINATES(car4, 753.88, 1105.45, 0.9);
							SET_CAR_COORDINATES(car5, 752.88, 1106.45, 0.9);
							SET_CAR_COORDINATES(car6, 753.88, 1106.45, 0.9);
							SET_CAR_COORDINATES(car7, 751.88, 1104.45, 0.9);
							WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 56.41, -122.91, 2.2);//телепартируем из катера
							SET_CHAR_HEADING(GetPlayerPed(), 169.87);
							WARP_CHAR_INTO_CAR(ped1, car1);// садим Ленса за руль

							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 58.431, -125.217, 2.447 ); // куда смотрит камера
							SET_CAM_POS			( camera, 69.101, -120.321, 3.991 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							SetTime(500);
							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

							// грузим анимации
							REQUEST_ANIMS( "amb@hang_str_idls" );
							while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_EB", "COK4_24", 0, 0);//Good shooting, my friend. You're a real, proper, grade A lunatic.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R2_FC", "COK4_25", 0, 0);//Well, thank you.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_GA", "COK4_26", 0, 0);//See you around, Tommy.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_GB", "COK4_27", 0, 0);//Okay, Mr. Lance Vance Dance.
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 1500 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -11.77, -190.93, 1.5, 4, 90.0, 2, 5, 10);// пед едит на нужные координаты
							SetTime(4000);
							GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_AK47, 30, FALSE);
							SET_CHAR_AMMO(GetPlayerPed(), WEAPON_AK47, 60);

							DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
								{
									break;
								}
							}

							// убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// разморозить игрока

							SET_CAR_COORDINATES(car1, 1907.78, 1927.52, 1.4);// телепортируем Ланса и его катер
							DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
							skip = 2;
							break;
						}
					}
				}

				// завершение миссии
				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( car );
				REMOVE_TXD( textur );

				SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);// Игрок смертный
				SET_CAR_DENSITY_MULTIPLIER(1);// включаем пути
				SET_MAX_WANTED_LEVEL(6);
				RELEASE_WEATHER();
				REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре

				STOP_PLAYBACK_RECORDED_CAR(car1);
				STOP_PLAYBACK_RECORDED_CAR(car3);
				STOP_PLAYBACK_RECORDED_CAR(car4);
				STOP_PLAYBACK_RECORDED_CAR(car5);
				STOP_PLAYBACK_RECORDED_CAR(car6);
				STOP_PLAYBACK_RECORDED_CAR(car7);

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(barrel);//выгружаем модель

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

				// выгружаем из памяти транспорт
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car7);//выгружаем модель машины(в последствии машина изчезнет)

				// удаляем объекты
				DELETE_OBJECT(&barrel_1);
				DELETE_OBJECT(&barrel_2);
				DELETE_OBJECT(&barrel_3);

				// выгружаем объекты
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_3);

				// выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3027 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3028 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3029 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3030 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3031 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3032 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3033 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3034 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3035 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3036 ); // выгружаем пути транспорта

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();	
				}
				else if (skip == 2)
				{
					PRINT_HELP("CLOTH9"); //Tracksuit outfit delivered to Jocksport in Downtown.
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_COK_4" );//Supply & Demand
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(10000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +10000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 10000);
					G_DIAZ = 5;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== Death Row ======================================
		else if ((G_ONMISSION == 0) && (G_DIAZ == 7))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(925.599, 453.827, 5.389, &diaz_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(diaz_ico, BLIP_KATIE);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(diaz_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "LG_06");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 925.599, 453.827, 5.389, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 925.599, 453.827, 5.389, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("KENT_1", 15000, CUTSCENE_KENT);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(512.591, -74.900, 9.573, 189.24);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
				blip_on = 0;
				skip = 0;

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

				SET_CHAR_COORDINATES(GetPlayerPed(), 925.06, 453.041, 5.763);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -128.321);

				// меняем погоду
				//FORCE_WEATHER_NOW(WEATHER_RAINING);
				FORCE_WEATHER(WEATHER_LIGHTNING);
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "RESC_1A", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("resc_1a");
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

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20;
				Car car1, car2, car3, car4, car5, car6, car7, car8;
				Pickup sweap_1, sweap_2, aid_1;
				Texture fon;
				Cam camera;
				carHUD_x = 0.922156;
				carHUD_w = 0.0739583;
				del_car = 0;
				in_car = 0;
				stalking = 0;
				hate = 0;

				uint PedM1 = MODEL_M_Y_GMAF_HI_02;// мафиозник 1
				uint PedM2 = MODEL_M_Y_GMAF_LO_01;// мафиозник 2
				uint PedM3 = MODEL_IG_LILJACOBW;// Ленс
				uint CarM1 = MODEL_SENTINEL;//
				uint CarM2 = MODEL_COMET;//

				REQUEST_MODEL(CarM1);//загрузка модели машины из переменной
				while (!HAS_MODEL_LOADED(CarM1));//проверка "машина загрузилась" если нет то начанаем с начало
				REQUEST_MODEL(CarM2);//загрузка модели машины из переменной
				while (!HAS_MODEL_LOADED(CarM2));//проверка "машина загрузилась" если нет то начанаем с начало
				REQUEST_MODEL(PedM1);// мафиозник 1
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// мафиозник 2
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// Ленс
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало

				// грузим текстуры
				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );

				// грузим анимации
				REQUEST_ANIMS( "amb@hospital_idles_b" );
				while (!HAVE_ANIMS_LOADED( "amb@hospital_idles_b" )) WAIT(0);
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				// грузим пути
				REQUEST_CAR_RECORDING( 3037 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3037 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3038 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3038 )) WAIT(0);

				CREATE_CAR(CarM1, -859.371, 687.583, 6.024, &car1, TRUE);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				SET_CAR_HEADING(car1, 180.0);
				CREATE_CAR(CarM1, -804.949, 540.607, 6.024, &car2, TRUE);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				CREATE_CAR(CarM1, 280.497, -789.48, 5.134, &car3, TRUE);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				CREATE_CAR(CarM1, 285.003, -789.48, 5.134, &car4, TRUE);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				CREATE_CAR(CarM2, 290.229, -789.48, 5.134, &car5, TRUE);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				CREATE_CAR(CarM2, 294.735, -789.48, 5.134, &car6, TRUE);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				CREATE_CAR(CarM2, 299.961, -789.48, 5.134, &car7, TRUE);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				LOCK_CAR_DOORS(car2, 3); // запераем автомобиль
				LOCK_CAR_DOORS(car5, 3); // запераем автомобиль
				LOCK_CAR_DOORS(car6, 3); // запераем автомобиль
				LOCK_CAR_DOORS(car7, 3); // запераем автомобиль

				// создаём педов
				CREATE_CHAR (26, PedM3, -877.801, 698.787, 6.087, &ped1, TRUE);// Ленс
				SET_CHAR_HEADING(ped1, -85.0);
				CREATE_CHAR (26, PedM2, -806.318, 543.247, 6.376, &ped2, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped2, -90.0);
				CREATE_CHAR (26, PedM1, -832.028, 551.219, 6.376, &ped3, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped3, -90.0);
				CREATE_CHAR (26, PedM2, -829.532, 569.635, 6.376, &ped4, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped4, -135.0);
				CREATE_CHAR (26, PedM1, -823.867, 589.372, 6.376, &ped5, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped5, 70.0);
				CREATE_CHAR (26, PedM2, -833.512, 589.755, 6.376, &ped6, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped6, -90.0);
				CREATE_CHAR (26, PedM2, -839.194, 595.568, 6.376, &ped7, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped7, -40.0);
				CREATE_CHAR (26, PedM1, -828.775, 604.308, 6.376, &ped8, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped8, 45.0);
				CREATE_CHAR (26, PedM1, -826.28, 626.677, 6.376, &ped9, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped9, -175.0);
				CREATE_CHAR (26, PedM2, -834.626, 628.5, 6.376, &ped10, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped10, 135);
				CREATE_CHAR (26, PedM1, -843.056, 629.552, 6.376, &ped11, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped11, -90.0);
				CREATE_CHAR (26, PedM2, -852.833, 646.328, 6.376, &ped12, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped12, -105.0);
				CREATE_CHAR (26, PedM1, -841.6, 654.367, 6.376, &ped13, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped13, 35.0);
				CREATE_CHAR (26, PedM2, -851.658, 658.97, 6.376, &ped14, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped14, -160.0);
				CREATE_CHAR (26, PedM1, -846.861, 674.119, 6.376, &ped15, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped15, 50.0);
				CREATE_CHAR (26, PedM1, -859.724, 674.275, 12.058, &ped16, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped16, -125.0);
				CREATE_CHAR (26, PedM2, -877.905, 687.239, 6.376, &ped17, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped17, -140.0);
				CREATE_CHAR (26, PedM2, -869.438, 688.449, 6.376, &ped18, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped18, 160.0);
				CREATE_CHAR (26, PedM2, -868.151, 662.902, 6.376, &ped19, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped19, -90.0);
				CREATE_CHAR (26, PedM2, -806.372, 538.009, 6.376, &ped20, TRUE);// Сбитый прохожий
				SET_CHAR_HEADING(ped20, -90.0);

				// вооружаем
				UpdateWeaponOfPed(ped2, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped15, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped16, WEAPON_M4);
				SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_M4, TRUE);
				UpdateWeaponOfPed(ped17, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped18, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped19, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped20, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_AK47, TRUE);

				// Money
				SET_CHAR_MONEY(ped2, 650);
				SET_CHAR_MONEY(ped3, 650);
				SET_CHAR_MONEY(ped4, 650);
				SET_CHAR_MONEY(ped5, 650);
				SET_CHAR_MONEY(ped6, 650);
				SET_CHAR_MONEY(ped7, 650);
				SET_CHAR_MONEY(ped8, 650);
				SET_CHAR_MONEY(ped9, 650);
				SET_CHAR_MONEY(ped10, 650);
				SET_CHAR_MONEY(ped11, 650);
				SET_CHAR_MONEY(ped12, 650);
				SET_CHAR_MONEY(ped13, 650);
				SET_CHAR_MONEY(ped14, 650);
				SET_CHAR_MONEY(ped15, 650);
				SET_CHAR_MONEY(ped16, 650);
				SET_CHAR_MONEY(ped17, 650);
				SET_CHAR_MONEY(ped18, 650);
				SET_CHAR_MONEY(ped19, 650);
				SET_CHAR_MONEY(ped20, 650);

				// агрим
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
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
				SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped16, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped17, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped18, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped19, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped20, 5);

				SET_CHAR_RELATIONSHIP(ped2, 5, 0);
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
				SET_CHAR_RELATIONSHIP(ped13, 5, 0);
				SET_CHAR_RELATIONSHIP(ped14, 5, 0);
				SET_CHAR_RELATIONSHIP(ped15, 5, 0);
				SET_CHAR_RELATIONSHIP(ped16, 5, 0);
				SET_CHAR_RELATIONSHIP(ped17, 5, 0);
				SET_CHAR_RELATIONSHIP(ped18, 5, 0);
				SET_CHAR_RELATIONSHIP(ped19, 5, 0);
				SET_CHAR_RELATIONSHIP(ped20, 5, 0);

				SET_SENSE_RANGE(ped2, 35.0);
				SET_SENSE_RANGE(ped3, 35.0);
				SET_SENSE_RANGE(ped4, 35.0);
				SET_SENSE_RANGE(ped5, 35.0);
				SET_SENSE_RANGE(ped6, 35.0);
				SET_SENSE_RANGE(ped7, 35.0);
				SET_SENSE_RANGE(ped8, 35.0);
				SET_SENSE_RANGE(ped9, 35.0);
				SET_SENSE_RANGE(ped10, 35.0);
				SET_SENSE_RANGE(ped11, 35.0);
				SET_SENSE_RANGE(ped12, 35.0);
				SET_SENSE_RANGE(ped13, 35.0);
				SET_SENSE_RANGE(ped14, 35.0);
				SET_SENSE_RANGE(ped15, 35.0);
				SET_SENSE_RANGE(ped16, 95.0);
				SET_SENSE_RANGE(ped17, 35.0);
				SET_SENSE_RANGE(ped18, 35.0);
				SET_SENSE_RANGE(ped19, 35.0);
				SET_SENSE_RANGE(ped20, 35.0);

				SET_CHAR_WILL_USE_COVER(ped2, 1);
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
				SET_CHAR_WILL_USE_COVER(ped13, 1);
				SET_CHAR_WILL_USE_COVER(ped14, 1);
				SET_CHAR_WILL_USE_COVER(ped15, 1);
				SET_CHAR_WILL_USE_COVER(ped16, 1);
				SET_CHAR_WILL_USE_COVER(ped17, 1);
				SET_CHAR_WILL_USE_COVER(ped18, 1);
				SET_CHAR_WILL_USE_COVER(ped19, 1);
				SET_CHAR_WILL_USE_COVER(ped20, 1);

				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, FALSE);
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
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, FALSE);

				ADD_BLIP_FOR_CHAR(ped1, &diaz_ico);
				CHANGE_BLIP_SPRITE(diaz_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(diaz_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(diaz_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

				PRINT_STRING_IN_STRING("string", "KPM1_1", 5000, 1);//~g~Lance is being held at the junk yard, Go and rescue him!
				SetTime(1000);
				FREEZE_CHAR_POSITION(ped16, 1);
				SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped16, TRUE);

				SET_CHAR_COMPONENT_VARIATION(ped1, 1, 0, 0);
				SET_CHAR_COLLISION(ped1, 0);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stomach", "amb@hospital_idles_b", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				SetTime(1000);
				SET_CHAR_COORDINATES_NO_OFFSET(ped1, -877.801, 698.787, 6.5);// перемещаем игрока
				FREEZE_CHAR_POSITION(ped1, 1);

				//создаём пушку и аптечку
				CREATE_PICKUP_ROTATE(w_ak47, 3, 60, -737.191, 552.031, 5.861, -75.0, -80.0, 80.0, &sweap_1);// даём винтовку
				CREATE_PICKUP_ROTATE(w_uzi, 3, 60, -873.587, 697.847, 6.403, -90.0, 0.0, -70.0, &sweap_2);// даём винтовку
				CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -873.723, 695.923, 6.403, -90.0, 0.0, 0.0, &aid_1);//Аптека
				SET_MAX_WANTED_LEVEL(2);

				SETTIMERB( 0 );
				Health = 500;

				while (true)
				{
					WAIT( 0 );
					// Lance HUD
					DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
					DRAW_SPRITE( 0, 0.915054, 0.7838, 0.059166, 0.014, 0.0, 27, 89, 130, 255 );// рисуем фоновую текстуру.

					if (Health < 5)
					{
						carH1 = 0;
					}
					else
					{
						carH1 = Health-100;
					}
					carH2 = carHUD_w/500;
					carH3 = carH2*carH1;
					carHUD_y1 = carHUD_w-carH3;
					carHUD_y2 = carHUD_y1/2;
					carHUD_y3 = carHUD_x-carHUD_y2;
					DRAW_SPRITE( 0, carHUD_y3, 0.7838, carH3, 0.014, 0.0, 97, 194, 247, 255 );// рисуем фоновую текстуру.

					SET_TEXT_COLOUR(95, 195, 247, 255);
					SET_TEXT_SCALE(0.156, 0.267);
					SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
					DISPLAY_TEXT(0.78815097, 0.77731852, "KPM1_3"); //LANCE'S HEALTH:

					// тики тут
					if (TIMERB() > 700)
					{
						Health -= 1;
						SETTIMERB( 0 );
					}

					//игнор копов
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -799.441, 529.515, 3.0, -899.441, 729.515, 53.0, 0 )) && (hate == 0))
					{
						SET_MAX_WANTED_LEVEL(0);
						SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);
						hate = 1;
					}
					else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -799.441, 529.515, 3.0, -899.441, 729.515, 53.0, 0 )) && (hate == 1))
					{
						SET_MAX_WANTED_LEVEL(2);
						SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);
						hate = 0;
					}

					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты водитель лодки1 в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, PlayX, PlayY, PlayZ, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
						DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
						while(true)
						{
							WAIT(0);
							if (IS_SCREEN_FADED_OUT())
							{
								break;
							}
						}
						START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 3037, 0.0, 0.0, 0.0);
						START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car4, 3038, 0.0, 0.0, 0.0);
						PAUSE_PLAYBACK_RECORDED_CAR(car3);
						PAUSE_PLAYBACK_RECORDED_CAR(car4);

						// выгружаем из памяти педов
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

						// создаём новых мафиозников тут
						CREATE_CHAR_INSIDE_CAR(car3, 1, PedM1, &ped2);// Вуду за рулём Гаитянин
						CREATE_CHAR_INSIDE_CAR(car4, 1, PedM2, &ped3);// Вуду за рулём Гаитянин
						CREATE_CHAR_AS_PASSENGER(car3, 1, PedM2, 0, &ped4);// Вуду пассажир Гаитянин
						CREATE_CHAR_AS_PASSENGER(car4, 1, PedM2, 0, &ped5);// Вуду пассажир Гаитянин
						CREATE_CHAR_AS_PASSENGER(car3, 1, PedM2, 1, &ped6);// Вуду пассажир Гаитянин
						CREATE_CHAR_AS_PASSENGER(car4, 1, PedM1, 2, &ped7);// Вуду пассажир Гаитянин

						CREATE_CHAR_INSIDE_CAR(car5, 1, PedM2, &ped10);// Вуду за рулём Гаитянин
						CREATE_CHAR_INSIDE_CAR(car6, 1, PedM1, &ped11);// Вуду за рулём Гаитянин
						CREATE_CHAR_INSIDE_CAR(car7, 1, PedM1, &ped12);// Вуду за рулём Гаитянин
						CREATE_CHAR_AS_PASSENGER(car5, 1, PedM2, 0, &ped13);// Вуду пассажир Гаитянин
						CREATE_CHAR_AS_PASSENGER(car6, 1, PedM1, 0, &ped14);// Вуду пассажир Гаитянин
						CREATE_CHAR_AS_PASSENGER(car7, 1, PedM1, 0, &ped15);// Вуду пассажир Гаитянин
						CREATE_CHAR (26, PedM2, 280.231, -784.338, 5.134, &ped16, TRUE);// Сбитый прохожий
						CREATE_CHAR (26, PedM2, 282.531, -784.338, 5.134, &ped17, TRUE);// Сбитый прохожий
						CREATE_CHAR (26, PedM2, 284.837, -784.338, 5.134, &ped18, TRUE);// Сбитый прохожий
						CREATE_CHAR (26, PedM2, 287.141, -784.338, 5.134, &ped19, TRUE);// Сбитый прохожий
						CREATE_CHAR (26, PedM2, 289.444, -784.338, 5.134, &ped20, TRUE);// Сбитый прохожий
						CREATE_CHAR (26, PedM2, 291.844, -784.338, 5.134, &ped8, TRUE);// Сбитый прохожий
						CREATE_CHAR (26, PedM2, 294.144, -784.338, 5.134, &ped9, TRUE);// Сбитый прохожий

						// ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, -876.923, 698.383, 6.289); // куда смотрит камера
						SET_CAM_POS			( camera, -879.756, 705.374, 7.414 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						SET_CHAR_COORDINATES(GetPlayerPed(), -875.998, 698.787, 5.622);// перемещаем игрока
						SET_CHAR_HEADING(GetPlayerPed(), 85.0);

						SET_CHAR_COORDINATES(ped1, -877.062, 698.787, 5.74);// перемещаем игрока
						SET_CHAR_HEADING(ped1, -85.0);

						FREEZE_CHAR_POSITION(ped1, 0);
						SET_CHAR_COLLISION(ped1, 1);
						SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped1, 0);
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stomach", "amb@hospital_idles_b", 8.0, 1, 0, 0, 0, 10 );//Воиспроизвидение анимации на педе
						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана

						// воспроизводим звук
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R2_GC", "RESC_4", 0, 0);//There goes my careful planning blown to shit, thanks to you. You screwed up real good, Lance!
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 5000 );//Воиспроизвидение анимации на педе
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R2_GD", "RESC_5", 0, 0);//He killed my brother. What do you expect me to do, mow his lawns?
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 4000 );//Воиспроизвидение анимации на педе
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R2_HA", "RESC_6", 0, 0);//We're gonna have to take out that prick Diaz before he takes us out.
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_d", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 4500 );//Воиспроизвидение анимации на педе
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(3200);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R2_HB", "RESC_1", 0, 0);//You ok to use a gun?
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R2_HC", "RESC_2", 0, 0);//Sure...I guess...nice to see you, too.
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						UNPAUSE_PLAYBACK_RECORDED_CAR(car3);
						UNPAUSE_PLAYBACK_RECORDED_CAR(car4);
						SetTime(400);

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R2_HD", "RESC_3", 0, 0);//Let's get out of here.
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_d", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						// вооружаем
						UpdateWeaponOfPed(ped1, WEAPON_EPISODIC_13);
						UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_13);
						UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_13);
						UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_13);
						UpdateWeaponOfPed(ped5, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_13);
						UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_13);
						UpdateWeaponOfPed(ped10, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped11, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped12, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_13);
						UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_12);
						UpdateWeaponOfPed(ped15, WEAPON_EPISODIC_12);

						// агрим
						SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);

						SET_CHAR_RELATIONSHIP(ped2, 5, 0);
						SET_CHAR_RELATIONSHIP(ped3, 5, 0);
						SET_CHAR_RELATIONSHIP(ped4, 5, 0);
						SET_CHAR_RELATIONSHIP(ped5, 5, 0);
						SET_CHAR_RELATIONSHIP(ped6, 5, 0);
						SET_CHAR_RELATIONSHIP(ped7, 5, 0);
						SET_CHAR_RELATIONSHIP(ped10, 5, 0);
						SET_CHAR_RELATIONSHIP(ped11, 5, 0);
						SET_CHAR_RELATIONSHIP(ped12, 5, 0);
						SET_CHAR_RELATIONSHIP(ped13, 5, 0);
						SET_CHAR_RELATIONSHIP(ped14, 5, 0);
						SET_CHAR_RELATIONSHIP(ped15, 5, 0);

						SET_SENSE_RANGE(ped2, 25.0);
						SET_SENSE_RANGE(ped3, 25.0);
						SET_SENSE_RANGE(ped4, 25.0);
						SET_SENSE_RANGE(ped5, 25.0);
						SET_SENSE_RANGE(ped6, 25.0);
						SET_SENSE_RANGE(ped7, 25.0);
						SET_SENSE_RANGE(ped10, 250.0);
						SET_SENSE_RANGE(ped11, 250.0);
						SET_SENSE_RANGE(ped12, 250.0);
						SET_SENSE_RANGE(ped13, 250.0);
						SET_SENSE_RANGE(ped14, 250.0);
						SET_SENSE_RANGE(ped15, 250.0);

						SET_CHAR_WILL_USE_COVER(ped2, 1);
						SET_CHAR_WILL_USE_COVER(ped3, 1);
						SET_CHAR_WILL_USE_COVER(ped4, 1);
						SET_CHAR_WILL_USE_COVER(ped5, 1);
						SET_CHAR_WILL_USE_COVER(ped6, 1);
						SET_CHAR_WILL_USE_COVER(ped7, 1);
						SET_CHAR_WILL_USE_COVER(ped10, 1);
						SET_CHAR_WILL_USE_COVER(ped11, 1);
						SET_CHAR_WILL_USE_COVER(ped12, 1);
						SET_CHAR_WILL_USE_COVER(ped13, 1);
						SET_CHAR_WILL_USE_COVER(ped14, 1);
						SET_CHAR_WILL_USE_COVER(ped15, 1);

						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, 1);

						// приезжают ещё мафиозники
						SET_CAR_COORDINATES(car2, -808.543, 538.712, 6.024);
						SET_CAR_HEADING(car2, 50.0);
						SET_CAR_COORDINATES(car5, -723.865, 543.306, 6.007);// перемещаем игрока
						SET_CAR_HEADING(car5, 95.0);
						SET_CAR_COORDINATES(car6, -641.205, 556.361, 5.847);// перемещаем игрока
						SET_CAR_HEADING(car6, -175.0);
						SET_CAR_COORDINATES(car7, -633.097, 521.224, 5.853);// перемещаем игрока
						SET_CAR_HEADING(car7, 5.0);

						// меняем ракурс
						POINT_CAM_AT_COORD	( camera, -847.579, 659.682, 4.088); // куда смотрит камера
						SET_CAM_POS			( camera, -861.851, 693.179, 10.64 );//расположение камеры
						SetTime(1000);
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "KPM1_5", 5000, 1);//~g~Diaz's guys are after you! Get Lance to the hospital.
						SetTime(2000);

						// высаживаются тут
						STOP_PLAYBACK_RECORDED_CAR(car3);
						STOP_PLAYBACK_RECORDED_CAR(car4);
						TASK_GO_STRAIGHT_TO_COORD(ped2, -865.191, 684.245, 6.376, 3, -2);
						TASK_GO_STRAIGHT_TO_COORD(ped3, -869.152, 683.889, 6.376, 3, -2);
						TASK_GO_STRAIGHT_TO_COORD(ped4, -865.191, 684.245, 6.376, 3, -2);
						TASK_GO_STRAIGHT_TO_COORD(ped5, -869.152, 683.889, 6.376, 3, -2);
						TASK_GO_STRAIGHT_TO_COORD(ped6, -865.191, 684.245, 6.376, 3, -2);
						TASK_GO_STRAIGHT_TO_COORD(ped7, -869.152, 683.889, 6.376, 3, -2);
						SetTime(2500);

						// лояльность игроку
						SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
						SET_CHAR_RELATIONSHIP(ped1, 5, 24);

						//убираем камеру
						SetTime(500);
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
						SET_CHAR_HEALTH(ped1, 1500);

						del_car = 1;
						MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
						MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
						MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)

						ADD_BLIP_FOR_COORD(-388.097, 1695.986, 4.953, &diaz_ico);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(diaz_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
						CHANGE_BLIP_COLOUR(diaz_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(diaz_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "NE_POINT");//иконка на радаре называние в истории карты ""
						SetTime(2000);
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "KPM1_4", 5000, 1);//~g~Get Lance to the hospital!
						break;
					}
					else if ((IS_CHAR_DEAD(ped1)) || (Health < 101))
					{
						EXPLODE_CHAR_HEAD(ped1);
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
						skip = 1;
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// игрок мёртв/арестован
					{
						skip = 1;
						break;
					}
				}

				if (skip == 0)
				{
					TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
					stalking = 1;
					in_car = 0;
					while (true)
					{
						WAIT( 0 );
						// Ленс сталкирит за Томми
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+15, PedY+15, PedZ+15, PedX-15, PedY-15, PedZ-15, 0 ))
						{
							if (stalking == 0)
							{
								TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
								stalking = 1;
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
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car8);
								TASK_ENTER_CAR_AS_PASSENGER(ped1, car8, -1, 0);
								SETTIMERB( 0 );
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
								{
									in_car = 0;
									TASK_LEAVE_CAR(ped1, car8);
									MARK_CAR_AS_NO_LONGER_NEEDED(&car8);
									TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
									stalking = 1;
								}
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 1) && (TIMERB() > 15000))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car8, 0);
							}
						}
						else
						{
							if (stalking == 1)
							{
								stalking = 0;
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GEN3_23", 5000, 1);//~g~You've left Lance behind! Go and get him!
							}
						}
						
						//игнор копов
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -799.441, 529.515, 3.0, -899.441, 729.515, 53.0, 0 )) && (hate == 0))
						{
							SET_MAX_WANTED_LEVEL(0);
							SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);
							hate = 1;
						}
						else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -799.441, 529.515, 3.0, -899.441, 729.515, 53.0, 0 )) && (hate == 1))
						{
							SET_MAX_WANTED_LEVEL(2);
							SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);
							hate = 0;
						}

						DRAW_CHECKPOINT( -388.097, 1695.986, 4.953, 2.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -388.097, 1695.986, 4.953, &PedR);//проверка "игрок на координатах"
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -388.097, 1695.986, 4.953, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 2.0) && ( PedR < 2.0))
						{
							//
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -388.097, 1695.986, 5.961); // куда смотрит камера
							SET_CAM_POS			( camera, -397.775, 1692.438, 7.52 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

							// воспроизводим звук
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_LA", "RESC_7", 0, 0);//Get patched up and meet me on the bridge to Star Island, ok?
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_LB", "RESC_8", 0, 0);//Ok, I got you.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							WARP_CHAR_FROM_CAR_TO_COORD(ped1, -388.488, 1693.351, 5.156);//телепартируем из катера
							SET_CHAR_HEADING(ped1, 160.0);
							TASK_GO_STRAIGHT_TO_COORD(ped1, -389.176, 1684.607, 6.763, 2, -2);// идёт в двери

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, -388.488, 1693.351, 6.029); // куда смотрит камера
							SET_CAM_POS			( camera, -395.328, 1690.509, 5.97 );//расположение камеры
							SetTime(2000);

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							SET_CHAR_COORDINATES(ped1, -877.447, 698.787, 5.74);// перемещаем игрока

							skip = 2;
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// игрок мёртв/арестован
						{
							skip = 1;
							break;
						}
					}
				}

				// завершение миссии
				SET_MAX_WANTED_LEVEL(6);
				RELEASE_WEATHER();
				REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
				REMOVE_PICKUP(sweap_1);// выгружаем оружие
				REMOVE_PICKUP(sweap_2);// выгружаем оружие
				REMOVE_PICKUP(aid_1);// выгружаем оружие
				RELEASE_TEXTURE( fon );
				REMOVE_TXD( textur );

				REMOVE_CAR_RECORDING( 3037 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3038 ); // выгружаем пути транспорта

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа

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
				if (del_car == 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
					MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
					MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
				}
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car7);//выгружаем модель машины(в последствии машина изчезнет)

				if (car8 != 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car8);//выгружаем модель машины(в последствии машина изчезнет)
				}

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_KENT_1" );//Death Row
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(0, "missionpassed", "CASH");
					G_DIAZ = 8;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== Rub Out ======================================
		else if ((G_ONMISSION == 0) && (G_DIAZ == 8))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(172.483, 40.766, 4.996, &diaz_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DWAYNE);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(diaz_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "LG_05");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 172.483, 40.766, 4.996, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 172.483, 40.766, 4.996, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-288.2, -487.5, 9.8, 275.0);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
				blip_on = 0;
				skip = 0;
				PointN = 0;
				res = 0;
				hate = 0;
				play = 0;
				text1 = 0;
				stalking = 1;
				in_car = 0;
				play_Speech = 0;
				carHUD_x = 0.922156;
				carHUD_w = 0.0739583;
				G_DIAZ = 99; // открыть заднию дверь

				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20, ped21, ped22;
				Pickup sweap_1, aid_1;
				Car car1, car2;
				Cam camera;
				Texture fon;
				Blip lance_ico;

				uint PedM1 = MODEL_IG_LILJACOB;// Ланс
				uint PedM2 = MODEL_IG_BLEDAR;// Диаз
				uint PedM3 = MODEL_M_Y_GMAF_HI_01;// охрана 1
				uint PedM4 = MODEL_M_Y_GMAF_LO_02;// охрана 2
				uint CarM1 = MODEL_STALION;
				uint Diaz_hp, Lance_hp;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );

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

				FORCE_WEATHER_NOW(WEATHER_SUNNY);
				FORWARD_TO_TIME_OF_DAY(19, 30);//устанавливаем время
				RELEASE_WEATHER();

				SET_CHAR_COORDINATES(GetPlayerPed(), 169.921, 40.644, 5.385);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 5.0);

				// грузим модели
				REQUEST_MODEL(PedM1);// Ланс
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Диаз
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// охрана 1
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM4);// охрана 2
				while (!HAS_MODEL_LOADED(PedM4));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);

				// грузим пути
				REQUEST_CAR_RECORDING( 3039 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3039 )) WAIT(0);

				// грузим анимации
				REQUEST_ANIMS( "amb_sit_couch_m" );
				while (!HAVE_ANIMS_LOADED( "amb_sit_couch_m" )) WAIT(0);

				// создайм машину и Ланса в ней
				CREATE_CAR(CarM1, 75.654, -11.412, 7.35, &car1, TRUE);// Инфернус
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);// Вуду за рулём Гаитянин
				CLEAR_AREA( 172.483, 40.766, 4.996, 45.0, 1);//очещаем зону загрузки


				// создаём моделей педов
				CREATE_CHAR (26, PedM2, 49.176, -62.955, 20.605, &ped2, TRUE);// Диаз
				CREATE_CHAR (26, PedM3, 88.581, 1.5411, 9.4441, &ped3, TRUE);// охранник
				CREATE_CHAR (26, PedM4, 87.779, -9.641, 11.637, &ped4, TRUE);// охранник
				CREATE_CHAR (26, PedM4, 57.935, -20.11, 13.921, &ped5, TRUE);// охранник
				CREATE_CHAR (26, PedM3, 50.579, -20.11, 13.921, &ped6, TRUE);// охранник
				CREATE_CHAR (26, PedM3, 44.647, -4.735, 11.518, &ped7, TRUE);// охранник
				CREATE_CHAR (26, PedM4, 44.647, -3.187, 11.518, &ped8, TRUE);// охранник
				CREATE_CHAR (26, PedM3, 116.704, -27.488, 7.034, &ped9, TRUE);// охранник
				CREATE_CHAR (26, PedM4, 142.989, -30.812, 7.034, &ped10, TRUE);// охранник
				CREATE_CHAR (26, PedM3, 143.403, -56.902, 7.034, &ped11, TRUE);// охранник
				CREATE_CHAR (26, PedM4, 114.436, -64.933, 7.034, &ped12, TRUE);// охранник
				CREATE_CHAR (26, PedM3, 91.8561, -87.436, 7.034, &ped13, TRUE);// охранник
				CREATE_CHAR (26, PedM3, -14.858, -29.318, 7.034, &ped14, TRUE);// охранник
				CREATE_CHAR (26, PedM4, -16.798, -55.771, 7.034, &ped15, TRUE);// охранник
				CREATE_CHAR (26, PedM4, -36.821, -40.292, 7.034, &ped16, TRUE);// охранник
				CREATE_CHAR (26, PedM3, -42.248, -52.966, 7.034, &ped17, TRUE);// охранник
				CREATE_CHAR (26, PedM4, 16.8441, -90.387, 7.034, &ped18, TRUE);// охранник
				CREATE_CHAR (26, PedM3, 30.6181, -83.031, 7.034, &ped19, TRUE);// охранник
				CREATE_CHAR (26, PedM4, 62.9211, -65.775, 4.573, &ped20, TRUE);// охранник
				CREATE_CHAR (26, PedM4, 67.8221, -91.899, 4.737, &ped21, TRUE);// охранник
				CREATE_CHAR (26, PedM3, 27.2501, -54.622, 5.855, &ped22, TRUE);// охранник
				SET_CHAR_INVINCIBLE(ped2, 1);

				SET_CHAR_HEADING(ped2, 50.0);
				SET_CHAR_HEADING(ped8, -130.0);
				SET_CHAR_HEADING(ped9, -50.0);
				SET_CHAR_HEADING(ped10, 90.0);
				SET_CHAR_HEADING(ped11, 90.0);
				SET_CHAR_HEADING(ped12, -65.0);
				SET_CHAR_HEADING(ped14, 85.0);
				SET_CHAR_HEADING(ped15, -85.0);
				SET_CHAR_HEADING(ped16, 180.0);
				SET_CHAR_HEADING(ped17, 165.0);
				SET_CHAR_HEADING(ped19, -90.0);
				SET_CHAR_HEADING(ped20, 95.0);
				SET_CHAR_HEADING(ped22, 95.0);

				// ставим камеру
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, 162.309, 41.062, 6.396); // куда смотрит камера
				SET_CAM_POS			( camera, 182.717, 44.488, 6.448 );//расположение камеры
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_CAM_FOV( camera, 45.0 );
				SET_WIDESCREEN_BORDERS( 1 );

				// стартуем пути
				START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3039, 0.0, 0.0, 0.0);
				DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
				SetTime(5000);

				DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}
				
				// пути стоп
				STOP_PLAYBACK_RECORDED_CAR(car1);
				REMOVE_CAR_RECORDING( 3039 ); // выгружаем пути транспорта
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);

				// высаживаем Ленса
				WARP_CHAR_FROM_CAR_TO_COORD(ped1, 158.191, 34.033, 5.84);//телепартируем из катера
				SET_CHAR_HEADING(ped1, -180.0);
				SET_CHAR_COORDINATES(GetPlayerPed(), 157.288, 33.366, 5.841);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -180.0);

				// даём винтовку
				GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_M4, 30, FALSE);	
				SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_M4, TRUE);
				ADD_ARMOUR_TO_CHAR(GetPlayerPed(), 100);
				UpdateWeaponOfPed(ped1, WEAPON_M4);
				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_M4, TRUE);

				SET_CHAR_COLLISION(ped2, 0);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "sit_down_idle_01", "amb_sit_couch_m", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				SET_CHAR_COORDINATES_NO_OFFSET(ped2, 51.228, -63.21, 20.815);// перемещаем игрока
				FREEZE_CHAR_POSITION(ped2, 1);

				// меняем ракурс камеры
				POINT_CAM_AT_COORD	( camera, 49.229, -62.968, 21.094); // куда смотрит камера
				SET_CAM_POS			( camera, 57.033, -62.379, 20.633 );//расположение камеры

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "ASS_1", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("ass_1");
				while (!HAS_CUTSCENE_LOADED())
				{
					WAIT(0);
				}

				PRINT_BIG("ASS_1", 5000, 2);//Rub Out
				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED())
				{
					WAIT(0);
				}

				if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
				{
					DO_SCREEN_FADE_IN(0);
				}

				// меняем ракурс камеры
				POINT_CAM_AT_COORD	( camera, 49.246, -62.855, 21.229); // куда смотрит камера
				SET_CAM_POS			( camera, 55.855, -57.442, 22.821 );//расположение камеры
				SET_CHAR_COLLISION(ped2, 1);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "sit_down_idle_01", "amb_sit_couch_m", 8.0, 1, 0, 0, 0, 10 );//Воиспроизвидение анимации на педе
				SET_CHAR_COORDINATES_NO_OFFSET(ped2, 50.906, -62.993, 19.952);// перемещаем игрока
				FREEZE_CHAR_POSITION(ped2, 0);
				TASK_GO_STRAIGHT_TO_COORD(ped2, 49.126, -62.994, 19.952, 2, -2);// Диаз идёт к мониторам
				SetTime(4000);

				// создаём пикапы
				CREATE_PICKUP_ROTATE(w_mp5, 3, 60, 50.487, -60.02, 20.299, 90.0, -180.0, -50.0, &sweap_1);// даём винтовку
				CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 105.462, -42.917, 6.995, 0.0, 0.0, 90.0, &aid_1);//Аптека
				ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(sweap_1, "mansion_int");
				ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(aid_1, "mansion_int");

				// меняем ракурс камеры
				POINT_CAM_AT_COORD	( camera, 161.229, 25.492, 8.204); // куда смотрит камера
				SET_CAM_POS			( camera, 139.721, 27.711, 10.859 );//расположение камеры
				SET_CHAR_COORDINATES(ped2, 51.317, -62.526, 19.952);// перемещаем игрока
				SET_CHAR_HEADING(ped2, 5.0);
				// эффект видеозаписи тут
				TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 153.382, 8.826, 6.906, 3, -2);// Томми бежит по территории
				TASK_GO_STRAIGHT_TO_COORD(ped1, 153.038, 8.826, 6.905, 3, -2);// Ланс бедит по территории
				SetTime(3500);

				// меняем ракурс камеры
				POINT_CAM_AT_COORD	( camera, 51.635, -67.683, 21.761); // куда смотрит камера
				SET_CAM_POS			( camera, 50.696, -55.421, 20.402 );//расположение камеры
				TASK_GO_STRAIGHT_TO_COORD(ped2, 51.226, -60.046, 19.952, 2, -2);// Диаз идёт к столу с МР5
				SetTime(3500);

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

				SET_CHAR_COORDINATES(ped1, 153.382, 23.08, 6.906);// перемещаем игрока
				SET_CHAR_HEADING(ped1, 165.0);
				SET_CHAR_COORDINATES_NO_OFFSET(GetPlayerPed(), 153.038, 21.733, 7.179);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 0.0);

				// вооружаем тут;
				UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped15, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped16, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped17, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped18, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped19, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped20, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped21, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped22, WEAPON_EPISODIC_13);

				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped21, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped22, WEAPON_EPISODIC_13, TRUE);

				// агрим тут
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
				SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped16, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped17, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped18, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped19, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped20, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped21, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped22, 5);

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
				SET_CHAR_RELATIONSHIP(ped13, 5, 0);
				SET_CHAR_RELATIONSHIP(ped14, 5, 0);
				SET_CHAR_RELATIONSHIP(ped15, 5, 0);
				SET_CHAR_RELATIONSHIP(ped16, 5, 0);
				SET_CHAR_RELATIONSHIP(ped17, 5, 0);
				SET_CHAR_RELATIONSHIP(ped18, 5, 0);
				SET_CHAR_RELATIONSHIP(ped19, 5, 0);
				SET_CHAR_RELATIONSHIP(ped20, 5, 0);
				SET_CHAR_RELATIONSHIP(ped21, 5, 0);
				SET_CHAR_RELATIONSHIP(ped22, 5, 0);

				SET_SENSE_RANGE(ped3, 25.0);
				SET_SENSE_RANGE(ped4, 25.0);
				SET_SENSE_RANGE(ped5, 30.0);
				SET_SENSE_RANGE(ped6, 30.0);
				SET_SENSE_RANGE(ped7, 25.0);
				SET_SENSE_RANGE(ped8, 25.0);
				SET_SENSE_RANGE(ped9, 30.0);
				SET_SENSE_RANGE(ped10, 25.0);
				SET_SENSE_RANGE(ped11, 25.0);
				SET_SENSE_RANGE(ped12, 30.0);
				SET_SENSE_RANGE(ped13, 25.0);
				SET_SENSE_RANGE(ped14, 30.0);
				SET_SENSE_RANGE(ped15, 30.0);
				SET_SENSE_RANGE(ped16, 25.0);
				SET_SENSE_RANGE(ped17, 30.0);
				SET_SENSE_RANGE(ped18, 25.0);
				SET_SENSE_RANGE(ped19, 30.0);
				SET_SENSE_RANGE(ped20, 25.0);
				SET_SENSE_RANGE(ped21, 25.0);
				SET_SENSE_RANGE(ped22, 25.0);

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
				SET_CHAR_WILL_USE_COVER(ped13, 1);
				SET_CHAR_WILL_USE_COVER(ped14, 1);
				SET_CHAR_WILL_USE_COVER(ped15, 1);
				SET_CHAR_WILL_USE_COVER(ped16, 1);
				SET_CHAR_WILL_USE_COVER(ped17, 1);
				SET_CHAR_WILL_USE_COVER(ped18, 1);
				SET_CHAR_WILL_USE_COVER(ped19, 1);
				SET_CHAR_WILL_USE_COVER(ped20, 1);
				SET_CHAR_WILL_USE_COVER(ped21, 1);
				SET_CHAR_WILL_USE_COVER(ped22, 1);

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
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped21, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped22, FALSE);
				SetTime(500);

				DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
				SET_MAX_WANTED_LEVEL(0);
				SET_CHAR_INVINCIBLE(ped2, 0);
				SET_CHAR_HEALTH(ped2, 1000);
				SET_CHAR_COORDINATES(ped2, 54.242, -56.25, 19.59);// перемещаем игрока
				SET_CHAR_HEADING(ped2, 5.0);
				UpdateWeaponOfPed(ped2, WEAPON_MP5);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_MP5, TRUE);

				// лояльность игроку
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
				SET_CHAR_RELATIONSHIP(ped1, 5, 24);
				SET_CHAR_HEALTH(ped1, 500);
				TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );

				ADD_BLIP_FOR_CHAR(ped2, &diaz_ico);
				CHANGE_BLIP_SPRITE(diaz_ico, BLIP_DESTINATION);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(diaz_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(diaz_ico, "MO_TARGET");//иконка на радаре ""
				CHANGE_BLIP_SCALE(diaz_ico, 0.77999990); // масштаб иконки на радаре

				ADD_BLIP_FOR_CHAR(ped1, &lance_ico);
				CHANGE_BLIP_SPRITE(lance_ico, BLIP_DESTINATION);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(lance_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(lance_ico, "NE_LANCE");//иконка на радаре "Связной"
				CHANGE_BLIP_SCALE(lance_ico, 0.77999990); // масштаб иконки на радаре
				PRINT_STRING_IN_STRING("string", "ASS1_16", 5000, 1);//~g~Kill Diaz!
				play = 2;
				text1 = 1;
				time_sub = 3000;
				SETTIMERB( 0 );
				FREEZE_CHAR_POSITION(ped2, 1);

				while (true)
				{
					WAIT( 0 );

					// Диалог
					if (text1 == 1)
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R2_LC", "ASS1_1", 0, 0);//This place is going to be crawling with assholes...be careful...
						START_SCRIPT_CONVERSATION(1, 1);
						play_Speech = 1;
						text1 = 2;
					}
					else if (text1 == 2)
					{
						if (play_Speech == 0)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_LD", "ASS1_2", 0, 0);//Don't worry Tommy, I'll cover you.
							START_SCRIPT_CONVERSATION(1, 1);
							play_Speech = 1;
							text1 = 3;
						}
					}
					else if (text1 == 3)
					{
						if (play_Speech == 0)
						{
							if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 151.424, -93.871, 2.0, 91.424, -63.871, 10.0, 0 ))
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R2_LE", "ASS1_10", 0, 0);//Hey, this is a real nice herbaceous border.
								START_SCRIPT_CONVERSATION(1, 1);
								play_Speech = 1;
								text1 = 4;
							}
						}
					}
					else if ((text1 == 4) || (text1 == 3))
					{
						if (play_Speech == 0)
						{
							if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 68.589, -67.651, 2.0, 8.589, -37.651, 10.0, 0 ))
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R2_LF", "ASS1_4", 0, 0);//Diaz must be inside!
								START_SCRIPT_CONVERSATION(1, 1);
								play_Speech = 1;
								text1 = 5;
							}
						}
					}
					else if (text1 == 5)
					{
						if (play_Speech == 0)
						{
							if (IS_CHAR_IN_AREA_3D( ped1, 99.499, -38.318, 21.0, 94.499, -33.318, 27.0, 0 ))
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R2_LG", "ASS1_11", 0, 0);//Hey Tommy, can my room have a view of the bay?
								START_SCRIPT_CONVERSATION(1, 1);
								play_Speech = 1;
								text1 = 6;
								SETTIMERB( 0 );
							}
							else if (IS_CHAR_IN_AREA_3D( ped1, 99.499, -43.838, 13.0, 94.499, -38.838, 19.0, 0 ))
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R2_LH", "ASS1_12", 0, 0);//Beautiful high ceilings in here...
								START_SCRIPT_CONVERSATION(1, 1);
								play_Speech = 1;
								text1 = 6;
							}
						}
					}
					else if (text1 == 6)
					{
						if (play_Speech == 0)
						{
							if (Diaz_hp < 800)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R2_LI", "ASS1_7", 0, 0);//Eat this, you murdering bastards!!
								START_SCRIPT_CONVERSATION(1, 1);
								play_Speech = 1;
								text1 = 7;
							}
						}
					}

					if (play_Speech == 1)
					{
						if (!IS_SCRIPTED_CONVERSATION_ONGOING())
						{
							play_Speech = 0;
						}
					}

					GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//проверка "игрок на координатах"
					if ( PlayR > 75)
					{
						EXPLODE_CHAR_HEAD(ped1);
					}

					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 93.03, -46.721, 30.827, 87.03, -34.721, 35.827, 0 )) || (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 57.877, -21.441, 12.56, 51.877, -17.441, 18.56, 0 )))// проверка игрок в зоне
					{
						if (PointN == 0)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "ASS1_18", 5000, 1);//~g~The door is locked, try another route.
							PointN = 1;
						}
					}
					else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 72.006, -30.142, 13.111, 65.006, -23.142, 28.111, 0 )) && (hate == 0))
					{
						play = 0;
						FREEZE_CHAR_POSITION(ped2, 0);

						// камера сверху
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 54.577, -50.749, 20.865 ); // куда смотрит камера
						SET_CAM_POS			( camera, 56.814, -36.287, 19.631 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
						TASK_GO_STRAIGHT_TO_COORD(ped2, 54.242, -44.102, 19.59, 2, -2);// идёт в двери
						SetTime(2000);

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R2_LJ", "ASS1_13", 0, 0);//DIAZ?! I've come to take over your business!
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(4500);
						SetSpeech();

						// меняем ракурс
						POINT_CAM_AT_COORD	( camera, 70.478, -28.397, 19.202 ); // куда смотрит камера
						SET_CAM_POS			( camera, 42.129, -49.573, 23.115 );//расположение камеры

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R2_LK", "ASS1_14", 0, 0);//TOMMY! You betrayed me, you idiot! I'm gonna kill you real soon..
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(4500);
						SetSpeech();
						SetTime(1000);

						//убираем камеру
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

						// агрим Диаза
						SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
						SET_CHAR_RELATIONSHIP(ped2, 5, 0);
						SET_SENSE_RANGE(ped2, 25.0);
						SET_CHAR_WILL_USE_COVER(ped2, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, FALSE);
						SET_CHAR_SPHERE_DEFENSIVE_AREA(ped2, 54.242, -51.11, 19.59, 15.0);
						hate = 1;
						text1 = 6;
					}
					else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 104.918, -48.724, 4.998, 100.258, -43.408, 9.998, 0 )) && (res == 0))
					{
						res = 1;
						// респавн
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
						MARK_CHAR_AS_NO_LONGER_NEEDED(&ped21);//выгружаем модель педа(в последствии пед изчезнет
						MARK_CHAR_AS_NO_LONGER_NEEDED(&ped22);//выгружаем модель педа(в последствии пед изчезнет

						// создаём моделей педов
						CREATE_CHAR (26, PedM3, 167.981, -22.2, 7.01, &ped3, TRUE);// охранник
						CREATE_CHAR (26, PedM4, 167.981, -24.2, 7.01, &ped4, TRUE);// охранник
						CREATE_CHAR (26, PedM4, 167.981, -26.2, 7.01, &ped5, TRUE);// охранник
						CREATE_CHAR (26, PedM3, 167.981, -28.2, 7.01, &ped6, TRUE);// охранник
						CREATE_CHAR (26, PedM3, 167.981, -30.2, 7.01, &ped7, TRUE);// охранник
						CREATE_CHAR (26, PedM4, 167.981, -32.2, 7.01, &ped8, TRUE);// охранник
						CREATE_CHAR (26, PedM3, 167.981, -34.2, 7.01, &ped9, TRUE);// охранник
						CREATE_CHAR (26, PedM4, 167.981, -36.2, 7.01, &ped10, TRUE);// охранник
						CREATE_CHAR (26, PedM3, 167.981, -38.2, 7.01, &ped11, TRUE);// охранник
						CREATE_CHAR (26, PedM4, 167.981, -40.2, 7.01, &ped12, TRUE);// охранник
						CREATE_CHAR (26, PedM3, 167.981, -42.2, 7.01, &ped13, TRUE);// охранник
						CREATE_CHAR (26, PedM3, 167.981, -44.2, 7.01, &ped14, TRUE);// охранник
						CREATE_CHAR (26, PedM4, 167.981, -46.2, 7.01, &ped15, TRUE);// охранник
						CREATE_CHAR (26, PedM4, 167.981, -48.2, 7.01, &ped16, TRUE);// охранник
						CREATE_CHAR (26, PedM3, 167.981, -50.2, 7.01, &ped17, TRUE);// охранник
						CREATE_CHAR (26, PedM4, 167.981, -52.2, 7.01, &ped18, TRUE);// охранник
						CREATE_CHAR (26, PedM3, 167.981, -54.2, 7.01, &ped19, TRUE);// охранник
						CREATE_CHAR (26, PedM4, 167.981, -56.2, 7.01, &ped20, TRUE);// охранник
						CREATE_CHAR (26, PedM4, 167.981, -58.2, 7.01, &ped21, TRUE);// охранник
						CREATE_CHAR (26, PedM3, 167.981, -60.2, 7.01, &ped22, TRUE);// охранник
						SetTime(500);

						SET_CHAR_COORDINATES(ped3, 116.126, -49.704, 11.825);// перемещаем игрока
						SET_CHAR_COORDINATES(ped4, 106.418, -44.642, 13.865);// перемещаем игрока
						SET_CHAR_COORDINATES(ped5, 115.103, -40.408, 16.805);// перемещаем игрока
						SET_CHAR_COORDINATES(ped6, 107.395, -49.736, 21.885);// перемещаем игрока
						SET_CHAR_COORDINATES(ped7, 115.103, -41.019, 24.776);// перемещаем игрока
						SET_CHAR_COORDINATES(ped8, 96.261, -42.201, 21.927);// перемещаем игрока
						SET_CHAR_COORDINATES(ped9, 97.395, -33.025, 21.927);// перемещаем игрока
						SET_CHAR_COORDINATES(ped10, 87.475, -26.625, 21.927);// перемещаем игрока
						SET_CHAR_COORDINATES(ped11, 96.261, -42.201, 13.771);// перемещаем игрока
						SET_CHAR_COORDINATES(ped12, 97.395, -33.025, 13.771);// перемещаем игрока
						SET_CHAR_COORDINATES(ped13, 87.475, -26.625, 13.771);// перемещаем игрока
						SET_CHAR_COORDINATES(ped14, 60.915, -23.015, 21.832);// перемещаем игрока
						SET_CHAR_COORDINATES(ped15, 49.775, -27.361, 21.832);// перемещаем игрока
						SET_CHAR_COORDINATES(ped16, 41.422, -39.817, 19.535);// перемещаем игрока
						SET_CHAR_COORDINATES(ped17, 71.359, -45.963, 19.584);// перемещаем игрока
						SET_CHAR_COORDINATES(ped18, 57.144, -49.929, 19.584);// перемещаем игрока
						SET_CHAR_COORDINATES(ped19, 51.869, -49.812, 19.584);// перемещаем игрока
						SET_CHAR_COORDINATES(ped20, 58.639, -23.448, 13.818);// перемещаем игрока
						SET_CHAR_COORDINATES(ped21, 58.617, -30.433, 13.818);// перемещаем игрока
						SET_CHAR_COORDINATES(ped22, 49.859, -30.247, 13.818);// перемещаем игрока

						SET_CHAR_HEADING(ped4, -95.0);
						SET_CHAR_HEADING(ped5, 90.0);
						SET_CHAR_HEADING(ped7, 90.0);
						SET_CHAR_HEADING(ped8, -150.0);
						SET_CHAR_HEADING(ped9, 155.0);
						SET_CHAR_HEADING(ped10, -95.0);
						SET_CHAR_HEADING(ped11, -150.0);
						SET_CHAR_HEADING(ped12, 155.0);
						SET_CHAR_HEADING(ped13, -95.0);
						SET_CHAR_HEADING(ped14, -175.0);
						SET_CHAR_HEADING(ped15, -95.0);
						SET_CHAR_HEADING(ped16, -95.0);
						SET_CHAR_HEADING(ped17, 85.0);
						SET_CHAR_HEADING(ped20, 170.0);
						SET_CHAR_HEADING(ped22, -90.0);

						// вооружаем тут;
						UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_13);// 1
						UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_13);// 2
						UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_13);// 3
						UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_13);// 4
						UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_13);// 5
						UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_13);// 6
						UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_13);// 7
						UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_13);// 8
						UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_13);// 9
						UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_13);// 10
						UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_13);// 11
						UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_13);// 12
						UpdateWeaponOfPed(ped15, WEAPON_EPISODIC_12);// 13
						UpdateWeaponOfPed(ped16, WEAPON_EPISODIC_13);// 14
						UpdateWeaponOfPed(ped17, WEAPON_EPISODIC_13);// 15
						UpdateWeaponOfPed(ped18, WEAPON_EPISODIC_13);// 16
						UpdateWeaponOfPed(ped19, WEAPON_MP5);// 17
						UpdateWeaponOfPed(ped20, WEAPON_EPISODIC_13);// 18
						UpdateWeaponOfPed(ped21, WEAPON_EPISODIC_13);// 19
						UpdateWeaponOfPed(ped22, WEAPON_MP5);// 20

						SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_EPISODIC_12, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_MP5, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped21, WEAPON_EPISODIC_13, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped22, WEAPON_MP5, TRUE);

						// агрим тут
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
						SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped16, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped17, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped18, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped19, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped20, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped21, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped22, 5);

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
						SET_CHAR_RELATIONSHIP(ped13, 5, 0);
						SET_CHAR_RELATIONSHIP(ped14, 5, 0);
						SET_CHAR_RELATIONSHIP(ped15, 5, 0);
						SET_CHAR_RELATIONSHIP(ped16, 5, 0);
						SET_CHAR_RELATIONSHIP(ped17, 5, 0);
						SET_CHAR_RELATIONSHIP(ped18, 5, 0);
						SET_CHAR_RELATIONSHIP(ped19, 5, 0);
						SET_CHAR_RELATIONSHIP(ped20, 5, 0);
						SET_CHAR_RELATIONSHIP(ped21, 5, 0);
						SET_CHAR_RELATIONSHIP(ped22, 5, 0);

						SET_SENSE_RANGE(ped3, 15.0);
						SET_SENSE_RANGE(ped4, 15.0);
						SET_SENSE_RANGE(ped5, 10.0);
						SET_SENSE_RANGE(ped6, 10.0);
						SET_SENSE_RANGE(ped7, 15.0);
						SET_SENSE_RANGE(ped8, 15.0);
						SET_SENSE_RANGE(ped9, 10.0);
						SET_SENSE_RANGE(ped10, 15.0);
						SET_SENSE_RANGE(ped11, 15.0);
						SET_SENSE_RANGE(ped12, 10.0);
						SET_SENSE_RANGE(ped13, 15.0);
						SET_SENSE_RANGE(ped14, 10.0);
						SET_SENSE_RANGE(ped15, 10.0);
						SET_SENSE_RANGE(ped16, 15.0);
						SET_SENSE_RANGE(ped17, 10.0);
						SET_SENSE_RANGE(ped18, 15.0);
						SET_SENSE_RANGE(ped19, 10.0);
						SET_SENSE_RANGE(ped20, 15.0);
						SET_SENSE_RANGE(ped21, 15.0);
						SET_SENSE_RANGE(ped22, 15.0);

						SET_CHAR_ACCURACY(ped3, 30);
						SET_CHAR_ACCURACY(ped4, 10);
						SET_CHAR_ACCURACY(ped5, 10);
						SET_CHAR_ACCURACY(ped6, 10);
						SET_CHAR_ACCURACY(ped7, 10);
						SET_CHAR_ACCURACY(ped8, 20);
						SET_CHAR_ACCURACY(ped9, 10);
						SET_CHAR_ACCURACY(ped10, 10);
						SET_CHAR_ACCURACY(ped11, 10);
						SET_CHAR_ACCURACY(ped12, 20);
						SET_CHAR_ACCURACY(ped13, 10);
						SET_CHAR_ACCURACY(ped14, 15);
						SET_CHAR_ACCURACY(ped15, 10);
						SET_CHAR_ACCURACY(ped16, 10);
						SET_CHAR_ACCURACY(ped17, 10);
						SET_CHAR_ACCURACY(ped18, 10);
						SET_CHAR_ACCURACY(ped19, 15);
						SET_CHAR_ACCURACY(ped20, 10);
						SET_CHAR_ACCURACY(ped21, 10);
						SET_CHAR_ACCURACY(ped22, 15);

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
						SET_CHAR_WILL_USE_COVER(ped13, 1);
						SET_CHAR_WILL_USE_COVER(ped14, 1);
						SET_CHAR_WILL_USE_COVER(ped15, 1);
						SET_CHAR_WILL_USE_COVER(ped16, 1);
						SET_CHAR_WILL_USE_COVER(ped17, 1);
						SET_CHAR_WILL_USE_COVER(ped18, 1);
						SET_CHAR_WILL_USE_COVER(ped19, 1);
						SET_CHAR_WILL_USE_COVER(ped20, 1);
						SET_CHAR_WILL_USE_COVER(ped21, 1);
						SET_CHAR_WILL_USE_COVER(ped22, 1);

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
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped21, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped22, FALSE);
					}
					else
					{
						if (PointN == 1)
						{
							PointN = 0;
						}
					}

					// Ленс сталкирит за Томми
					if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+22, PedY+22, PedZ+15, PedX-22, PedY-22, PedZ-15, 0 ))
					{
						if (stalking == 0)
						{
							TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
							stalking = 1;
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
							GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car2);
							TASK_ENTER_CAR_AS_PASSENGER(ped1, car2, -1, 0);
							SETTIMERB( 0 );
						}
						else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
						{
							if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
							{
								in_car = 0;
								TASK_LEAVE_CAR(ped1, car2);
								MARK_CAR_AS_NO_LONGER_NEEDED(&car2);
								TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
								stalking = 1;
							}
						}
						else if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 1) && (TIMERB() > 15000))
						{
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car2, 0);
						}
					}
					else
					{
						if (stalking == 1)
						{
							stalking = 0;
							TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_23", 5000, 1);//~COL_NET_12~You've left Lance behind! Go and get him!
						}
					}

					GET_CHAR_HEALTH(ped1, &Lance_hp);
					GET_CHAR_HEALTH(ped2, &Diaz_hp);

					// Lance HUD
					DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
					DRAW_SPRITE( 0, 0.915054, 0.7838, 0.059166, 0.014, 0.0, 27, 89, 130, 255 );// рисуем фоновую текстуру.

					if (Lance_hp < 105)
					{
						carH1 = 0;
					}
					else
					{
						carH1 = Lance_hp-100;
					}
					carH2 = carHUD_w/500;
					carH3 = carH2*carH1;
					carHUD_y1 = carHUD_w-carH3;
					carHUD_y2 = carHUD_y1/2;
					carHUD_y3 = carHUD_x-carHUD_y2;
					DRAW_SPRITE( 0, carHUD_y3, 0.7838, carH3, 0.014, 0.0, 97, 194, 247, 255 );// рисуем фоновую текстуру.

					SET_TEXT_COLOUR(95, 195, 247, 255);
					SET_TEXT_SCALE(0.156, 0.267);
					SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
					DISPLAY_TEXT(0.78815097, 0.77731852, "KPM1_3"); //LANCE'S HEALTH:

					if ((Diaz_hp < 100) || (IS_CHAR_DEAD(ped2)))
					{
						EXPLODE_CHAR_HEAD(ped2);
						skip = 2;
						break;
					}
					else if ((Lance_hp < 100) || (IS_CHAR_DEAD(ped1)))
					{
						EXPLODE_CHAR_HEAD(ped1);
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
						skip = 1;
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// игрок мёртв/арестован
					{
						skip = 1;
						break;
					}
				}
				// завершение миссии
				G_DIAZ = 8;
				REMOVE_BLIP(lance_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
				SET_MAX_WANTED_LEVEL(6);
				REMOVE_PICKUP(sweap_1);
				REMOVE_PICKUP(aid_1);
				RELEASE_TEXTURE( fon );
				REMOVE_TXD( textur );

				
				if (skip == 2)
				{
					SET_CHAR_COORDINATES(ped1, 167.981, -18.2, 7.01);// перемещаем игрока
					/*/ прячим трупы
					SET_CHAR_COORDINATES(ped3, 167.981, -22.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped4, 167.981, -24.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped5, 167.981, -26.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped6, 167.981, -28.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped7, 167.981, -30.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped8, 167.981, -32.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped9, 167.981, -34.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped10, 167.981, -36.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped11, 167.981, -38.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped12, 167.981, -40.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped13, 167.981, -42.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped14, 167.981, -44.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped15, 167.981, -46.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped16, 167.981, -48.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped17, 167.981, -50.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped18, 167.981, -52.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped19, 167.981, -54.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped20, 167.981, -56.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped21, 167.981, -58.2, 7.01);// перемещаем игрока
					SET_CHAR_COORDINATES(ped22, 167.981, -60.2, 7.01);// перемещаем игрока
					//*/
				}
				

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель

				// выгружвем педов
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
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped21);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped22);//выгружаем модель педа(в последствии пед изчезнет
				CLEAR_AREA(55.5, -30.3, 14.1, 75.5, 0);//очещаем зону загрузки

				if (car2 != 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				}

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
					DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
					while(true)
					{
						WAIT(0);
						if (IS_SCREEN_FADED_OUT())
						{
							break;
						}
					}

					//------------ катсцена ----------------
					LOAD_ADDITIONAL_TEXT( "ASS_2", 6 ); // загружаем субтитры из *.GTX
					START_CUTSCENE_NOW("ass_2");
					while (!HAS_CUTSCENE_LOADED())
					{
						WAIT(0);
					}

					DO_SCREEN_FADE_IN(0);
					while (!HAS_CUTSCENE_FINISHED())
					{
					  if (GET_CUTSCENE_AUDIO_TIME_MS()>27280)
					  {
						DRAW_RECT(0.5, 0.5, 1.0, 1.0, 0, 0, 0, 255);
					  }
					}

					if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
					{
						DO_SCREEN_FADE_IN(0);
					}

					// камера сверху
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 55.544, -19.092, 16.294 ); // куда смотрит камера
					SET_CAM_POS			( camera, -5.072, 19.039, 24.72 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );


					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT(0.5, 0.45, "PROP_A");//PROPERTY ACQUIRED!

						WAIT( 0 );
						if ( TIMERA() > 4000 )
						{
							break;
						}
					}

					DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
					while(true)
					{
						WAIT(0);
						if (IS_SCREEN_FADED_OUT())
						{
							break;
						}
					}
					DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана

					//убираем камеру
					ACTIVATE_SCRIPTED_CAMS( 0, 0 );
					END_CAM_COMMANDS( &camera );
					SET_WIDESCREEN_BORDERS( 0 );
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_ASS_1" );//Rub Out
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(50000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +50000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 50000);
					REGISTER_SAVE_HOUSE(54.5077, -19.8106, 13.8069 - 0.26666, 0.0, "VercettiEstate", 15);
					ENABLE_SAVE_HOUSE(15, true);
					G_DIAZ = 9;
					G_PROTECT = 1;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
		else if ((G_ONMISSION == 0) && (G_DIAZ == 9))
		{
			break;
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(diaz_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}
	}
}
void main(void)
{
	//THIS_SCRIPT_SHOULD_BE_SAVED();
	if (G_DIAZ < 9)
	{
		baron_diaz();
	}
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
