/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "features.h"
#include "map_offset.h"
#include "globals.h"
#include "cutscenes.h"
#include "mission_passed.h"
#include "fast_travel.h"
float PlayX, PlayY, PlayZ, PlayR, PedX, PedY, PedZ, PedR, blip_on, skip, help_1, help_2, text, play, stalking, in_car, del_car, wave, gogogo, textur, in_zon, hate, clear_ped, autosave;
float pedHUD_x, pedHUD_w, LanceH1, LanceH2, LanceH3, LanceHUD_y1, LanceHUD_y2, LanceHUD_y3, DiazH1, DiazH2, DiazH3, DiazHUD_y1, DiazHUD_y2, DiazHUD_y3, Speech, explo_1;
float convoy_x, convoy_y, passenger, point, speed, speed2, speed3, speed4, terpenie, PedX2, PedY2, PedZ2, PedR2, convoy_x2, convoy_y2, car_blip, delta, hud_on, boom, garage, in_garage;

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
void cortez(void)
{
	blip_on = 0;
	autosave = 0;
	Blip cortez_ico, vert_ico;
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
//============================== Treacherous Swine ======================================
		if ((G_ONMISSION == 0) && (G_CORTEZ == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(189.427, -827.564, 2.028, &cortez_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_GAMBETTI);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(cortez_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "LG_04");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 189.427, -827.564, 2.028, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 189.427, -827.564, 2.028, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("COL_1", 15000, CUTSCENE_GENERAL);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-163.0, -1439.4, 9.0, 201.5);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
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

				SET_CHAR_COORDINATES(GetPlayerPed(), 189.427, -827.564, 2.028);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -85.0);
				FORCE_WEATHER_NOW(WEATHER_SUNNY);
				RELEASE_WEATHER();
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "COL_1", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("col_1");
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
				ADD_BLIP_FOR_COORD(908.828, 563.354, 5.941, &cortez_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(cortez_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(cortez_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//иконка на радаре называние в истории карты ""
				PRINT_STRING_IN_STRING("string", "GEN1_05", 5000, 1);//~g~Go and kill Gonzalez!

				// даём бензопилу
				SetTime(2000);
				UpdateWeaponOfPed(GetPlayerPed(), WEAPON_FTHROWER);

				Ped ped1, ped2, ped3;
				Cam camera;
				int money_plaer;
				help_1 = 0;
				help_2 = 0;
				play = 0;
				text = 0;

				uint PedM1 = MODEL_IG_ANTHONY;// Гонзалис
				uint PedM2 = MODEL_M_Y_GMAF_HI_01;// охрана

				// грузим модели
				REQUEST_MODEL(PedM1);// Гольфмен
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// охрана
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало

				// создаём моделей педов
				CREATE_CHAR (26, PedM1, 895.752, 571.529, 27.553, &ped1, TRUE);// Гонзалис
				CREATE_CHAR (26, PedM2, 895.823, 572.708, 27.553, &ped2, TRUE);// охранник
				CREATE_CHAR (26, PedM2, 895.106, 576.637, 27.553, &ped3, TRUE);// охранник
				SET_CHAR_HEADING(ped1, -25.0);
				SET_CHAR_HEADING(ped2, -170.0);
				SET_CHAR_HEADING(ped3, -5.0);

				// грузим анимации
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				SetTime(2000);
				SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_FTHROWER, TRUE);

				while (TRUE)
				{
					WAIT(0);
					DRAW_CHECKPOINT( 908.828, 563.354, 5.941, 1.3, 246, 151, 255);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 908.828, 563.354, 5.941, &PlayR);//проверка "игрок на координатах"
					if ((( PlayR < 1.3) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))) || (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 910.591, 547.901, 23.0, 881.21, 578.805, 33.5, 0 )))
					{
						REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
						SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_FTHROWER, TRUE);

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
						SET_CHAR_COORDINATES(GetPlayerPed(), 887.29, 562.852, 29.284);// перемещаем игрока
						SET_CHAR_HEADING(GetPlayerPed(), -95.0);

						// ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 886.461, 556.552, 29.904); // куда смотрит камера
						SET_CAM_POS			( camera, 900.625, 576.546, 28.014 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						SetTime(200);
						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 892.86, 561.146, 29.284, 2, -2);// Томми идёт в двери
						// анимации разговора педов
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_idle_b", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе

						SetTime(3000);
						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 893.19, 562.085, 29.284, 2, -2);// Томми идёт в двери
						SetTime(1000);
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 1500 );//Воиспроизвидение анимации на педе

						// воспроизводим аудио
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_AD", "GEN1_10", 0, 0);//I'm going to shut that big mouth of yours!
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(2000);
						SetSpeech();

						// смена ракурса камеры
						POINT_CAM_AT_COORD	( camera, 895.755, 578.788, 28.006 ); // куда смотрит камера
						SET_CAM_POS			( camera, 895.242, 551.305, 32.388 );//расположение камеры

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_A_AA", "GEN1_06", 0, 0);//Eh! He's got a blade!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 893.944, 563.112, 24.916, 3, -1, 1.5);// Гонзалис бежит к выходу
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R4_A_AB", "GEN1_11", 0, 0);//Stop running you fat slimeball!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						//убираем камеру
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

						// маркер над целью.
						ADD_BLIP_FOR_CHAR(ped1, &cortez_ico);
						CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//текстура иконки на радаре
						CHANGE_BLIP_COLOUR(cortez_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//иконка на радаре ""
						CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // масштаб иконки на радаре

						// агрим педов
						SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
						SET_CHAR_RELATIONSHIP(ped2, 5, 0);
						SET_CHAR_RELATIONSHIP(ped3, 5, 0);
						SET_SENSE_RANGE(ped2, 20.0);
						SET_SENSE_RANGE(ped3, 20.0);
						SET_CHAR_WILL_USE_COVER(ped2, 1);
						SET_CHAR_WILL_USE_COVER(ped3, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, FALSE);
						SetTime(1000);
						PANIC_SCREAM(ped1);
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if (IS_CHAR_DEAD(ped1))
					{
						break;
					}
				}

				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						DRAW_CHECKPOINT( 908.828, 563.354, 5.941, 1.3, 246, 151, 255);//создание чекпойнт на координатах и его цвет
						DRAW_CHECKPOINT( 885.286, 563.279, 28.781, 1.3, 246, 151, 255);//создание чекпойнт на координатах и его цвет
						DRAW_CHECKPOINT( 893.944, 563.112, 24.916, 1.3, 246, 151, 255);//создание чекпойнт на координатах и его цвет

						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ,  885.286, 563.279, 28.781, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.3 ) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							DO_SCREEN_FADE_OUT( 400 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							SET_CHAR_COORDINATES(GetPlayerPed(), 910.986, 563.28, 6.1);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), -95.0);
							DO_SCREEN_FADE_IN( 400 );// убирается затемнение экрана
						}
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 893.944, 563.112, 24.916, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.3 ) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							DO_SCREEN_FADE_OUT( 400 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							SET_CHAR_COORDINATES(GetPlayerPed(), 910.986, 563.28, 6.1);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), -95.0);
							DO_SCREEN_FADE_IN( 400 );// убирается затемнение экрана
						}
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 908.828, 563.354, 5.941, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.3) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							DO_SCREEN_FADE_OUT( 400 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							SET_CHAR_COORDINATES(GetPlayerPed(), 887.29, 562.852, 29.284);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), -95.0);
							DO_SCREEN_FADE_IN( 400 );// убирается затемнение экрана
						}
						if ((IS_CHAR_DEAD(ped1)) && (help_2 == 0))
						{
							// маркер на выход
							REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_COORD(885.286, 563.279, 28.781, &cortez_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
							CHANGE_BLIP_COLOUR(cortez_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(cortez_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//иконка на радаре называние в истории карты ""

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN1_23", 5000, 1);//~g~Go back through the doors to return to the ground floor.
							help_2 = 1;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						else
						{
							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 893.944, 563.112, 24.916, &PedR);//проверка "игрок на координатах"
							if ( PedR < 2.0 )
							{
								PANIC_SCREAM(ped1);
								SET_CHAR_COORDINATES(ped1, 910.986, 563.28, 6.1);// перемещаем игрока
								SET_CHAR_HEADING(ped1, -95.0);
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 828.377, 59.035, 6.753, 3, -1, 1.5);// Гонзалис бежит к копам

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GEN1_23", 5000, 1);//~g~Go back through the doors to return to the ground floor.
								text = 1;
								SETTIMERB( 0 );
							}
						}
						if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 910.591, 547.901, 23.0, 881.21, 578.805, 33.5, 0 )) && (!IS_CHAR_IN_AREA_3D( ped1, 910.591, 547.901, 23.0, 881.21, 578.805, 33.5, 0 )))
						{
							break;
						}
						else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 910.591, 547.901, 23.0, 881.21, 578.805, 33.5, 0 )) && (IS_CHAR_DEAD(ped1)))
						{
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
					}
				}

				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (IS_CHAR_DEAD(ped1))
						{
							REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 2);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
							STORE_SCORE(GetPlayerIndex(), &money_plaer);// записываем средства игрока в переменную
							if ( money_plaer < 100 )
							{
								ADD_SCORE( GetPlayerIndex(), +100 );//даём игроку денег
							}
							// маркер на покрасочную
							ADD_BLIP_FOR_COORD(754.079, 965.605, 5.128, &cortez_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
							CHANGE_BLIP_COLOUR(cortez_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(cortez_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//иконка на радаре называние в истории карты "магазин одежды"

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NE_GEN1", 5000, 1);//The Vice City Police are on to you! Get to the Pay 'N' Spray in Vice Point.								 
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						else
						{
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//проверка "игрок на координатах"
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 828.377, 59.035, 6.753, &PedR);//проверка "игрок на координатах"
							if (( PlayR > 200.0) || ( PedR < 2.5 ))
							{
								ALTER_WANTED_LEVEL(GetPlayerIndex(), 4);
								APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GEN1_18", 5000, 1);//~r~Gonzalez has made it safely to the Police Station!
								skip = 1;// переменная пропуска
								break;
							}
							else
							{
								if (TIMERB() > 8000)
								{
									TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 828.377, 59.035, 6.753, 3, -1, 1.5);// Гонзалис бежит к копам
									SETTIMERB( 0 );
									if (text == 1)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R4_A_DA", "GEN1_07", 0, 0);//Go away from me, you cheap bastard!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									else if (text == 2)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R4_A_AB", "GEN1_11", 0, 0);//Stop running you fat slimeball!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									else if (text == 3)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R4_A_EA", "GEN1_08", 0, 0);//Oh sweet Jesus, I've wasted my life and my looks!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									else if (text == 4)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R4_A_FA", "GEN1_12", 0, 0);//Stand still and I'll make it quick!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									else if (text == 5)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R4_A_GA", "GEN1_09", 0, 0);//I pay you double, Tommy, DOUBLE!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									else if (text == 6)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R4_A_GB", "GEN1_13", 0, 0);//Quit your squealing, no one cares, fatso!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									else
									{
										PANIC_SCREAM(ped1);
									}
									text += 1;
								}
							}
						}
					}
				}


				if (skip == 0)
				{
					if (play == 1)
					{
						play = 0;
					}
					while(true)
					{
						WAIT(0);
						// маркер на покрасочную
						DRAW_CHECKPOINT( 754.079, 965.605, 5.128, 2.1, 246, 151, 255);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ,  754.079, 965.605, 5.128, &PlayR);//проверка "игрок на координатах"
						if ( PlayR < 2.0 )
						{
							if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
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
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
								ALTER_WANTED_LEVEL(GetPlayerIndex(), 0);
								APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
								SetTime(2000);
								DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
								skip = 2;// переменная пропуска
								break;
							}
							else
							{
								if (help_1 == 0)
								{
									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "GEN1_20", 5000, 1);//~g~Get into a vehicle.
									help_1 = 1;
								}
							}
						}
						else
						{
							if (help_1 == 1)
							{
								help_1 = 0;
							}
						}
						if (!IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0))
						{
							skip = 2;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				

				REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					PRINT_HELP("CLOTH7"); //Casual outfit delivered to Gash in The North Point Mall.
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_COL_1" );//Treacherous Swine
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(250, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +250 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 250);
					G_CORTEZ = 2;
					autosave = 1;
				}

				G_ONMISSION = 0;
			}
		}

//============================== Mall Shootout ======================================
		else if ((G_ONMISSION == 0) && (G_CORTEZ == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(189.427, -827.564, 2.028, &cortez_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_GAMBETTI);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(cortez_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "LG_04");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 189.427, -827.564, 2.028, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 189.427, -827.564, 2.028, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("COL_2", 15000, CUTSCENE_GENERAL);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-163.0, -1439.4, 9.0, 201.5);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
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

				SET_CHAR_COORDINATES(GetPlayerPed(), 189.427, -827.564, 2.028);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -85.0);
				FORCE_WEATHER_NOW(WEATHER_SUNNY);
				RELEASE_WEATHER();
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "COL_2", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("col_2");
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

				// меняем погоду
				FORCE_WEATHER_NOW(WEATHER_RAINING);
				RELEASE_WEATHER();
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				Car car1, car2;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7;
				Cam camera;
				Pickup bag;
				skip = 0;

				uint PedM1 = MODEL_IG_DMITRI;// Француз
				uint PedM2 = MODEL_M_Y_NHELIPILOT;// SWAT
				uint CarM1 = MODEL_PCJ;// PCJ

				// грузим модели
				REQUEST_MODEL(PedM1);// Гольфмен
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// охрана
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM1);// охрана
				while (!HAS_MODEL_LOADED(CarM1));////проверка "пед загрузился" если нет то начанаем с начало

				// создаём моделей педов
				CREATE_CHAR (26, PedM1, 439.097, -403.801, 10.9, &ped1, TRUE);// Француз
				CREATE_CHAR (26, PedM2, 286.386, -785.672, 5.06, &ped2, TRUE);// SWAT
				CREATE_CHAR (26, PedM2, 289.619, -785.672, 5.06, &ped3, TRUE);// SWAT
				CREATE_CHAR (26, PedM2, 292.961, -785.672, 5.06, &ped4, TRUE);// SWAT
				CREATE_CHAR (26, PedM2, 296.473, -785.672, 5.06, &ped5, TRUE);// SWAT
				CREATE_CHAR (26, PedM2, 299.976, -785.672, 5.06, &ped6, TRUE);// SWAT
				CREATE_CHAR (26, PedM2, 286.775, -783.209, 5.06, &ped7, TRUE);// SWAT

				SET_CHAR_HEADING(ped1, -95.0);
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
				SET_CHAR_RELATIONSHIP(ped1, 5, 24);

				CREATE_CAR(CarM1, 286.232, -791.79, 5.445, &car1, TRUE);
				CREATE_CAR(CarM1, 289.629, -791.79, 5.445, &car2, TRUE);

				// грузим анимации
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				REQUEST_ANIMS( "gun@ak47" );
				while (!HAVE_ANIMS_LOADED( "gun@ak47" )) WAIT(0);

				ADD_BLIP_FOR_CHAR(ped1, &cortez_ico);
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(cortez_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(cortez_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//иконка на радаре называние в истории карты "магазин одежды"
				PRINT_STRING_IN_STRING("string", "COL2_B1", 5000, 1);//~g~Meet the courier at the mall.
				SetTime(2000);

				while(true)
				{
					WAIT(0);
					if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 439.897, -407.509, 9.982, 435.397, -403.509, 13.982, 0 ))// если игрок в зоне
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

						REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
						ADD_BLIP_FOR_CHAR(ped1, &cortez_ico);
						CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//текстура иконки на радаре
						CHANGE_BLIP_COLOUR(cortez_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

						// ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 433.081, -407.492, 10.705); // куда смотрит камера
						SET_CAM_POS			( camera, 442.991, -403.101, 12.374 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );
						
						SET_CHAR_COORDINATES(GetPlayerPed(), 436.942, -405.857, 10.2);// перемещаем игрока
						SET_CHAR_HEADING(GetPlayerPed(), -50.0);
						TASK_GO_STRAIGHT_TO_COORD(ped1, 437.601, -404.651, 10.5, 2, -1);// Францез идёт к Томми
						SetTime(200);

						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
						SetTime(1500);

						SET_CHAR_HEADING(ped1, 150.0);
						SetTime(2000);

						// диалог
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_A_GC", "COL2_1", 0, 0);//Ze rain, she is tres wet zis time of the year...
						START_SCRIPT_CONVERSATION(1, 1);

						// анимация диалога
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 9000 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 9000 );//Воиспроизвидение анимации на педе
						SetTime(1000);

						// раставляем swat
						SET_CHAR_COORDINATES(ped2, 439.325, -417.789, 16.121);// перемещаем игрока
						SET_CHAR_COORDINATES(ped3, 435.535, -417.789, 16.121);// перемещаем игрока
						SET_CHAR_HEADING(ped2, 5.0);
						SET_CHAR_HEADING(ped3, 5.0);
						SET_CHAR_COORDINATES(ped4, 416.164, -404.718, 4.883);// перемещаем игрока
						SET_CHAR_COORDINATES(ped5, 416.164, -407.192, 4.883);// перемещаем игрока
						SET_CHAR_HEADING(ped4, -95.0);
						SET_CHAR_HEADING(ped5, -95.0);
						SET_CHAR_COORDINATES(ped6, 434.698, -405.802, 4.883);// перемещаем игрока
						SET_CHAR_COORDINATES(ped7, 438.483, -404.522, 4.883);// перемещаем игрока

						// расставляем мопЭды
						SET_CAR_COORDINATES(car1, 472.664, -364.41, 4.861);// перемещаем игрока
						SET_CAR_COORDINATES(car2, 475.702, -364.41, 4.861);// перемещаем игрока
						SET_CAR_HEADING(car1, -45.0);
						SET_CAR_HEADING(car2, -45.0);
						SET_CAR_ENGINE_ON(car2, 1, 1);

						// вооружаем swat
						UpdateWeaponOfPed(ped2, WEAPON_MP5);
						UpdateWeaponOfPed(ped3, WEAPON_MP5);
						UpdateWeaponOfPed(ped4, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped5, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped6, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped7, WEAPON_PISTOL);
						SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_MP5, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_MP5, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_PISTOL, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_PISTOL, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_PISTOL, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_PISTOL, TRUE);
						SetTime(2340);
						SetSpeech();

						// swat идёт к перилам
						TASK_GO_STRAIGHT_TO_COORD(ped2, 438.338, -414.568, 16.121, 2, -2);// swat идёт к перилам
						TASK_GO_STRAIGHT_TO_COORD(ped3, 436.234, -414.568, 16.121, 2, -2);// swat идёт к перилам

						// смена ракурса камеры
						POINT_CAM_AT_COORD	( camera, 437.323, -407.423, 12.515 ); // куда смотрит камера
						SET_CAM_POS			( camera, 437.323, -394.819, 10.936 );//расположение камеры

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R4_A_HA", "COL2_2", 0, 0);//What?
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_EB_QQQ1", "COL2_3", 0, 0);//Ah, comment?
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_EC", "COL2_4", 0, 0);//Look, Cortez sent me. Just give me the damn chips.
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R4_A_ZA", "COL2_5", 0, 0);//Oh...d'accord.
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						// анимация прицеливания
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "holster_2_aim", "gun@ak47", 1.0, 0, 0, 0, 1, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped3, "holster_2_aim", "gun@ak47", 1.0, 0, 0, 0, 1, -1 );//Воиспроизвидение анимации на педе

						// смена ракурса камеры
						POINT_CAM_AT_COORD	( camera, 437.146, -405.239, 9.128 ); // куда смотрит камера
						SET_CAM_POS			( camera, 437.146, -418.711, 20.242 );//расположение камеры
						SetTime(500);

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R4_EA", "COL2_6A", 0, 0);//Freeze, imperialist American pig! Zat iz propertay of ze government Francais. 'And eet over!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_EB", "COL2_9", 0, 0);//You American idiot! They followed you here!
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(1000);

						TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 422.178, -400.601, 4.883, 3, -1, 1.5);// францез бежит к выходу
						SetTime(1800);

						// переставляем сват с крыши
						UpdateWeaponOfPed(ped2, WEAPON_PISTOL);
						UpdateWeaponOfPed(ped3, WEAPON_PISTOL);
						SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_PISTOL, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_PISTOL, TRUE);
						SET_CHAR_COORDINATES(ped2, 424.877, -397.139, 10.9);// перемещаем игрока
						SET_CHAR_COORDINATES(ped3, 424.877, -415.179, 10.9);// перемещаем игрока
						SET_CHAR_HEADING(ped2, 5.0);
						SET_CHAR_HEADING(ped3, 5.0);

						// смена ракурса камеры
						POINT_CAM_AT_COORD	( camera, 437.387, -400.745, 8.703 ); // куда смотрит камера
						SET_CAM_POS			( camera, 414.856, -410.971, 4.811 );//расположение камеры
						SetTime(3000);

						//убираем камеру
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COL2_B2", 5000, 1);//~g~The courier is fleeing with the guidance chips! Don't let him get away!

						// телепортируем француза
						SET_CHAR_COORDINATES(ped1, 443.712, -372.927, 4.883);// телепортируем француза
						TASK_CAR_DRIVE_WANDER(ped1, car1, 55.0, 2);// пед едит куда-то

						// агрим swat
						SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
						SET_CHAR_RELATIONSHIP(ped2, 5, 0);
						SET_CHAR_RELATIONSHIP(ped3, 5, 0);
						SET_CHAR_RELATIONSHIP(ped4, 5, 0);
						SET_CHAR_RELATIONSHIP(ped5, 5, 0);
						SET_CHAR_RELATIONSHIP(ped6, 5, 0);
						SET_CHAR_RELATIONSHIP(ped7, 5, 0);
						SET_SENSE_RANGE(ped2, 20.0);
						SET_SENSE_RANGE(ped3, 20.0);
						SET_SENSE_RANGE(ped4, 20.0);
						SET_SENSE_RANGE(ped5, 20.0);
						SET_SENSE_RANGE(ped6, 20.0);
						SET_SENSE_RANGE(ped7, 20.0);
						SET_CHAR_WILL_USE_COVER(ped2, 1);
						SET_CHAR_WILL_USE_COVER(ped3, 1);
						SET_CHAR_WILL_USE_COVER(ped4, 1);
						SET_CHAR_WILL_USE_COVER(ped5, 1);
						SET_CHAR_WILL_USE_COVER(ped6, 1);
						SET_CHAR_WILL_USE_COVER(ped7, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
						TASK_COMBAT(ped2, GetPlayerPed());
						TASK_COMBAT(ped3, GetPlayerPed());
						TASK_COMBAT(ped4, GetPlayerPed());
						TASK_COMBAT(ped5, GetPlayerPed());
						TASK_COMBAT(ped6, GetPlayerPed());
						TASK_COMBAT(ped7, GetPlayerPed());
						SET_CHAR_SHOOT_RATE(ped2, 25);
						SET_CHAR_SHOOT_RATE(ped3, 25);
						SET_CHAR_SHOOT_RATE(ped4, 25);
						SET_CHAR_SHOOT_RATE(ped5, 25);
						SET_CHAR_SHOOT_RATE(ped6, 25);
						SET_CHAR_SHOOT_RATE(ped7, 25);
						break;
					}

					else if (IS_CHAR_DEAD(ped1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COL2_F1", 5000, 1);//~r~You killed the contact!
						skip = 1;// переменная пропуска
						break;
					}
					
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
				}

				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (IS_CHAR_DEAD(ped1))
						{
							// из педа выпадает кейс
							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &PedZ);
							CREATE_PICKUP( mission_keis, 22, PedX+0.2, PedY+0.2, PedZ+0.2, &bag, 0 );// сумка

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL2_F2", 5000, 1);//~g~The courier is dead. Grab the guidance chips.

							REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_PICKUP(bag, &cortez_ico);
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(cortez_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//иконка на радаре "Товар"
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}

						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//проверка "игрок на координатах"
						if ( PlayR > 250.5)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL2_F4", 5000, 1);//~r~The courier has escaped! You failed to get the guidance chips.
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_IN_WATER(ped1))//если пед в воде
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL2_F3", 5000, 1);//~r~The guidance chips are at the bottom of the sea.
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
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (HAS_PICKUP_BEEN_COLLECTED( bag ))
						{
							REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL2_B3", 5000, 1);//~g~Take the guidance chips back to the Colonel.
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 2);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());

							ADD_BLIP_FOR_COORD(189.427, -827.564, 2.028, &cortez_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(cortez_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(cortez_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//иконка на радаре называние в истории карты "Телефонный звонок"
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						DRAW_CHECKPOINT( 189.427, -827.564, 2.028, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 189.427, -827.564, 2.028, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
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
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 0);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
							SET_CHAR_COORDINATES(GetPlayerPed(), 191.565, -827.564, 2.028);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), -85.0);
							SetTime(1000);
							DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							skip = 2;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
				REMOVE_PICKUP(bag);// выгружаем оружие

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет

				// выгружаем из памяти транспорт
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_COL_2" );//Mall Shootout
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(500, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +500 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 500);
					G_CORTEZ = 3;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== Guardian Angels ======================================
		else if ((G_ONMISSION == 0) && (G_CORTEZ == 3))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(189.427, -827.564, 2.028, &cortez_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_GAMBETTI);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(cortez_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "LG_04");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 189.427, -827.564, 2.028, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 189.427, -827.564, 2.028, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("COL_3", 15000, CUTSCENE_GENERAL);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-163.0, -1439.4, 9.0, 201.5);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
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

				SET_CHAR_COORDINATES(GetPlayerPed(), 189.427, -827.564, 2.028);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -85.0);
				FORCE_WEATHER_NOW(WEATHER_SUNNY);
				RELEASE_WEATHER();
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "COL_3A", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("col_3a");
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

				Car car1, car2, car3, car4, car5, car6, car7, car8, car9, car10, car11;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20, ped21, ped22;
				Cam camera;
				Object keis;
				Pickup sweap_1, bag;
				int pic_cord1, pic_cord2;
				Texture fon;
				bool area_check;
				skip = 0;
				stalking = 0;
				in_car = 0;
				del_car = 0;
				gogogo = 0;
				text = 0;
				clear_ped = 0;
				area_check = false;

				uint PedM1 = MODEL_IG_LILJACOB;// Ленс
				uint PedM2 = MODEL_IG_BLEDAR;// Диас
				uint PedM3 = MODEL_M_Y_GMAF_HI_01;// Охранник Диаса 1
				uint PedM4 = MODEL_M_Y_GMAF_LO_01;// Охранник Диаса 2
				uint PedM5 = MODEL_M_Y_GLAT_HI_01;// Кубинец 1
				uint PedM6 = MODEL_M_Y_GLAT_HI_02;// Кубинец 2
				uint PedM7 = MODEL_M_M_GJAM_HI_01;// Гаитянин

				uint CarM1 = MODEL_INFERNUS;// Инфернус
				uint CarM2 = MODEL_ADMIRAL;// Адмирал
				uint CarM3 = MODEL_DUKES;// Кубан Гермес
				uint CarM4 = MODEL_VOODOO;// Вуду
				uint CarM5 = MODEL_BURRITO;// Буритто
				uint CarM6 = MODEL_SANCHEZ;// Санцез

				uint keisM = mission_keis2;// кейс
				uint Diaz_hp, Lance_hp;

				// грузим модели
				REQUEST_MODEL(PedM1);// 
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// 
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// 
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM4);// 
				while (!HAS_MODEL_LOADED(PedM4));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM5);// 
				while (!HAS_MODEL_LOADED(PedM5));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM6);// 
				while (!HAS_MODEL_LOADED(PedM6));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM7);// 
				while (!HAS_MODEL_LOADED(PedM7));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(keisM);// бочки
				while (!HAS_MODEL_LOADED(keisM)) WAIT(0);;

				REQUEST_MODEL(CarM1);// 
				while (!HAS_MODEL_LOADED(CarM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM2);// 
				while (!HAS_MODEL_LOADED(CarM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM3);// 
				while (!HAS_MODEL_LOADED(CarM3));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM4);// 
				while (!HAS_MODEL_LOADED(CarM4));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM5);// 
				while (!HAS_MODEL_LOADED(CarM5));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM6);// 
				while (!HAS_MODEL_LOADED(CarM6));////проверка "пед загрузился" если нет то начанаем с начало

				CREATE_OBJECT_NO_OFFSET(keisM, 0.8, 0.9, -2.4, &keis, TRUE);

				// создаём транспорт
				CREATE_CAR(CarM1, 299.551, -779.725, 5.445, &car1, TRUE);// Инфернус
				CREATE_CAR(CarM2, 295.942, -779.725, 5.445, &car2, TRUE);// Адмирал
				CREATE_CAR(CarM3, 292.585, -779.725, 5.445, &car3, TRUE);// Кубан Гермес
				CREATE_CAR(CarM4, 289.167, -779.725, 5.445, &car4, TRUE);// Вуду
				CREATE_CAR(CarM4, 286.008, -779.725, 5.445, &car5, TRUE);// Вуду
				CREATE_CAR(CarM5, 299.551, -787.416, 5.445, &car6, TRUE);// Буритто
				CREATE_CAR(CarM5, 295.942, -787.416, 5.445, &car7, TRUE);// Буритто
				CREATE_CAR(CarM4, 292.585, -787.416, 5.445, &car8, TRUE);// Вуду
				CREATE_CAR(CarM6, 289.167, -787.416, 5.445, &car9, TRUE);// Санцез
				CREATE_CAR(CarM6, 286.008, -787.416, 5.445, &car10, TRUE);// Санцез
				LOCK_CAR_DOORS(car2, 3); // запераем автомобиль
				LOCK_CAR_DOORS(car10, 3); // запераем автомобиль

				CHANGE_CAR_COLOUR( car1, 112, 112 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car1, 112, 112 );//цвет отрожений машины
				CHANGE_CAR_COLOUR( car9, 89, 89 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car9, 27, 27 );//цвет отрожений машины
				CHANGE_CAR_COLOUR( car10, 89, 89 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car10, 27, 27 );//цвет отрожений машины

				// создаём педов за рулёп
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);// Инфернус за рулём Ленс
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM2, &ped2);// Адмирал за рулём Диас
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM5, &ped5);// Кубан Гермес за рулём Кубинец 1
				CREATE_CHAR_INSIDE_CAR(car4, 1, PedM7, &ped7);// Вуду за рулём Гаитянин
				CREATE_CHAR_INSIDE_CAR(car5, 1, PedM7, &ped9);// Вуду за рулём Гаитянин
				CREATE_CHAR_INSIDE_CAR(car6, 1, PedM7, &ped11);// Буритто за рулём Гаитянин
				CREATE_CHAR_INSIDE_CAR(car7, 1, PedM7, &ped15);// Буритто за рулём Гаитянин
				CREATE_CHAR_INSIDE_CAR(car8, 1, PedM7, &ped19);// Вуду за рулём Гаитянин
				CREATE_CHAR_INSIDE_CAR(car9, 1, PedM7, &ped21);// Санцез за рулём Гаитянин
				CREATE_CHAR_INSIDE_CAR(car10, 1, PedM7, &ped22);// Санцез за рулём Гаитянин

				// создаём педов пассажиров
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM3, 1, &ped3);// Адмирал пассажир Охранник Диаса 1
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM4, 0, &ped4);// Адмирал пассажир Охранник Диаса 2
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM6, 0, &ped6);// Кубан Гермес пассажир Кубинец 2
				CREATE_CHAR_AS_PASSENGER(car4, 1, PedM7, 0, &ped8);// Вуду пассажир Гаитянин
				CREATE_CHAR_AS_PASSENGER(car5, 1, PedM7, 0, &ped10);// Вуду пассажир Гаитянин
				CREATE_CHAR_AS_PASSENGER(car6, 1, PedM7, 0, &ped12);// Буритто пассажир Гаитянин
				CREATE_CHAR_AS_PASSENGER(car6, 1, PedM7, 1, &ped13);// Буритто пассажир Гаитянин
				CREATE_CHAR_AS_PASSENGER(car6, 1, PedM7, 2, &ped14);// Буритто пассажир Гаитянин
				CREATE_CHAR_AS_PASSENGER(car7, 1, PedM7, 0, &ped16);// Буритто пассажир Гаитянин
				CREATE_CHAR_AS_PASSENGER(car7, 1, PedM7, 1, &ped17);// Буритто пассажир Гаитянин
				CREATE_CHAR_AS_PASSENGER(car7, 1, PedM7, 2, &ped18);// Буритто пассажир Гаитянин
				CREATE_CHAR_AS_PASSENGER(car8, 1, PedM7, 0, &ped20);// Вуду пассажир Гаитянин

				// грузим анимации
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				// грузим пути
				REQUEST_CAR_RECORDING( 2999 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 2999 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3000 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3000 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3001 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3001 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3002 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3002 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3003 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3003 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3004 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3004 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3005 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3005 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3006 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3006 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3007 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3007 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3008 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3008 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3009 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3009 )) WAIT(0);

				CREATE_PICKUP_ROTATE(w_ak47, 3, 120, 591.236, -657.675, 12.279, 92.468, -71.444, -1.476, &sweap_1);// даём винтовку
				ADD_BLIP_FOR_PICKUP(sweap_1, &cortez_ico);
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(cortez_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(cortez_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//иконка на радаре называние в истории карты "магазин одежды"
				GET_BLIP_COORDS(cortez_ico, &pic_cord1);// дебаг

				SetTime(1000);
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R14_WC", "", 0, 0);//
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				PRINT_STRING_IN_STRING("string", "GEN3_20", 5000, 1);//~g~The Colonel has arranged some firepower for you at the multistory carpark.
				SetTime(1000);

				// лояльность игроку
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
				SET_CHAR_RELATIONSHIP(ped1, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 0);
				SET_CHAR_RELATIONSHIP(ped2, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 0);
				SET_CHAR_RELATIONSHIP(ped3, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped4, 0);
				SET_CHAR_RELATIONSHIP(ped4, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped5, 0);
				SET_CHAR_RELATIONSHIP(ped5, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped6, 0);
				SET_CHAR_RELATIONSHIP(ped6, 5, 24);

				while(true)
				{
					GET_BLIP_COORDS(cortez_ico, &pic_cord2);// дебаг
					WAIT(0);
					if ((HAS_PLAYER_COLLECTED_PICKUP(GetPlayerIndex(), sweap_1)) || (pic_cord2 != pic_cord1))// дебаг
					{
						REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
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

						// ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 568.505, -669.958, 10.557); // куда смотрит камера
						SET_CAM_POS			( camera, 589.701, -661.164, 13.531 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						CLEAR_AREA(565.183, -677.905, 9.607, 10.0, 1);//очещаем зону загрузки
						CLEAR_AREA(582.581, -663.427, 11.426, 15.0, 1);//очещаем зону загрузки
						SET_CHAR_COORDINATES(GetPlayerPed(), 589.384, -660.17, 12.036);// перемещаем игрока
						SET_CHAR_HEADING(GetPlayerPed(), 120.0);
						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
						START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 2999, 0.0, 0.0, 0.0);// подъезд Ленса
						SetTime(7000);
					
						// меняем ракурс
						POINT_CAM_AT_COORD	( camera, 585.171, -661.506, 12.827); // куда смотрит камера
						SET_CAM_POS			( camera, 588.315, -668.298, 12.885 );//расположение камеры

						STOP_PLAYBACK_RECORDED_CAR(car1);
						TASK_GO_STRAIGHT_TO_COORD(ped1, 585.034, -662.539, 12.33, 2, -1);// Томми идёт к Лансу
						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 585.981, -661.875, 12.33, 2, -1);// Ленс идёт к Томми
						SetTime(1000);

						// воспроизводим звук
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_ED", "GEN3_1", 0, 0);//Hogging all the action, I see...
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_FA", "GEN3_2", 0, 0);//Look, you wanna do something other than just shadowing me everywhere? Why don't you come along and show me if you're any use.
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(5000);
						SetSpeech();

						// анимации разговора педов
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_FB", "GEN3_3", 0, 0);//I might just do that. The name's Lance, by the way.
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_GA", "GEN3_4", 0, 0);//Tommy Vercetti. Let's go...
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						//убираем камеру
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

						del_car = 1;
						MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
						MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)

						ADD_BLIP_FOR_COORD(891.904, 26.789, 4.831, &cortez_ico);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
						CHANGE_BLIP_COLOUR(cortez_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(cortez_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//иконка на радаре называние в истории карты "магазин одежды"
						PRINT_STRING_IN_STRING("string", "GEN3_44", 5000, 1);//~g~Go with Lance to the drop off and watch over Diaz.
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
				}

				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						// Ленс сталкирит за Томми
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+15, PedY+15, PedZ+15, PedX-15, PedY-15, PedZ-15, 0 ))
						{
							if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 0))
							{
								in_car = 1;
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car11);
								TASK_ENTER_CAR_AS_PASSENGER(ped1, car11, -1, 0);
								SETTIMERB( 0 );
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
								{
									in_car = 0;
									TASK_LEAVE_CAR(ped1, car11);
									MARK_CAR_AS_NO_LONGER_NEEDED(&car11);
								}
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 1) && (TIMERB() > 15000))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car11, 0);
							}
							if (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
								if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+5, PedY+5, PedZ+5, PedX-5, PedY-5, PedZ-5, 0 ))
								{
									TASK_GO_STRAIGHT_TO_COORD(ped1, PlayX, PlayY, PlayZ, 4, -2);
								}
							}
							if (stalking == 1)
							{
								stalking = 0;
							}
						}
						else
						{
							if (stalking == 0)
							{
								stalking = 1;
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GEN3_23", 5000, 1);//~g~You've left Lance behind! Go and get him!
							}
						}


						DRAW_CHECKPOINT( 891.904, 26.789, 4.831, 2.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 891.904, 26.789, 4.831, &PedR);//проверка "игрок на координатах"
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 891.904, 26.789, 4.831, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 2.0) && ( PedR < 2.0))
						{
							REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре

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

							if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
								{
									TASK_LEAVE_CAR(ped1, car11);
								}
								TASK_LEAVE_CAR(GetPlayerPed(), car11);
								MARK_CAR_AS_NO_LONGER_NEEDED(&car11);
							}

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 891.904, 26.789, 5.403); // куда смотрит камера
							SET_CAM_POS			( camera, 886.86, 3.537, 15.38 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							CLEAR_AREA(894.659, 54.979, 4.954, 15.0, 1);//очещаем зону загрузки
							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 3000, 0.0, 0.0, 0.0);// подъезд Диаса
							SetTime(3000);
						
							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, 894.318, 44.199, 5.192); // куда смотрит камера
							SET_CAM_POS			( camera, 893.822, 34.996, 6.659 );//расположение камеры

							STOP_PLAYBACK_RECORDED_CAR(car2);
							TASK_GO_STRAIGHT_TO_COORD(ped2, 894.208, 38.563, 5.231, 2, -1);// Диас идёт в точку
							SetTime(500);
							TASK_GO_STRAIGHT_TO_COORD(ped3, 895.002, 39.167, 5.231, 2, -1);// охранник_1 идёт в точку
							SetTime(500);
							TASK_GO_STRAIGHT_TO_COORD(ped4, 893.113, 39.177, 5.231, 2, -1);// охранник_2 идёт в точку
							SetTime(5000);

							CLEAR_AREA(891.904, 26.789, 4.831, 15.0, 1);//очещаем зону загрузки
							SET_CHAR_COORDINATES(GetPlayerPed(), 893.265, 35.292, 5.276);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 0.0);
							SET_CHAR_COORDINATES(ped1, 894.673, 35.153, 5.276);// перемещаем Ланса
							SET_CHAR_HEADING(ped1, 5.0);
							SetTime(2000);

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, 896.823, 35.329, 4.878); // куда смотрит камера
							SET_CAM_POS			( camera, 888.071, 41.434, 7.708 );//расположение камеры
							SetTime(3000);
							
							// воспроизводим звук
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_GB", "GEN3_5", 0, 0);//You must be Cortez's new gun.
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_GC", "GEN3_6", 0, 0);//Until more gainful opportunities arise.
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, 893.955, 34.872, 5.658); // куда смотрит камера
							SET_CAM_POS			( camera, 896.875, 40.563, 6.79 );//расположение камеры

							SET_CHAR_HEADING(ped1, 65.0);
							SET_CHAR_HEADING(GetPlayerPed(), -90.0);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_GD", "GEN3_7", 0, 0);//They'll be here any minute - we both better get a good vantage point...
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_GE", "GEN3_8", 0, 0);// OK! I'll take the balcony, you get the roof across the yard.
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							// даём оружие
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 894.78, 14.377, 12.23, 3, -1, 1.5);// Ленс бежит на болкон
							UpdateWeaponOfPed(ped1, WEAPON_AK47);
							UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_13);
							SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_AK47, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_13, TRUE);
							SET_SENSE_RANGE(ped1, 80.0);

							ADD_BLIP_FOR_COORD(887.101, 28.852, 11.917, &cortez_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
							CHANGE_BLIP_COLOUR(cortez_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(cortez_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//иконка на радаре называние в истории карты "магазин одежды"
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NEGEN3_P", 5000, 1);//Take an observation point.
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
					}
				}

				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						DRAW_CHECKPOINT( 887.101, 28.852, 11.917, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 887.101, 28.852, 11.917, &PlayR);//проверка "игрок на координатах"
						if ( PlayR < 1.5)
						{
							REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
							SET_CHAR_HEALTH(ped1, 500);
							SET_CHAR_HEALTH(ped2, 500);
							SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);
							SET_MAX_WANTED_LEVEL(0);

							CLEAR_AREA(891.904, 26.789, 4.831, 15.0, 1);//очещаем зону загрузки
							CLEAR_AREA(877.868, 7.5111, 3.854, 15.0, 1);//очещаем зону загрузки
							SET_CHAR_COORDINATES(ped1, 894.78, 14.377, 12.23);// перемещаем Ланса
							SET_CHAR_HEADING(ped1, 60.0);
							FREEZE_CHAR_POSITION(ped1, 1);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped1, TRUE);

							SET_CHAR_COORDINATES(ped2, 894.208, 38.563, 5.108);// перемещаем Ланса
							SET_CHAR_HEADING(ped2, 180.0);

							// ставим камеру
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_37", 5000, 1);//~g~Here come the Cubans. Watch over the deal making sure Diaz and Lance are safe.
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 893.401, 35.232, 9.185); // куда смотрит камера
							SET_CAM_POS			( camera, 893.585, 64.332, 15.034 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							// сценка приезда Кубинцев
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 3001, 0.0, 0.0, 0.0);// подъезд Кубинцев
							SetTime(5000);

							STOP_PLAYBACK_RECORDED_CAR(car3);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped5, 893.226, 36.905, 5.967, 2, -1, 0.7);// Кубинец_1 идёт в точку
							SetTime(500);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped6, 894.634, 36.767, 5.967, 2, -1, 0.7);// Кубинец_2 идёт в точку
							SetTime(5000);	

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							SET_CHAR_COORDINATES(ped5, 893.226, 36.905, 5.074);// перемещаем Кубинец_1
							SET_CHAR_HEADING(ped5, -30.0);

							UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_12);
							UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_12);
							SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_12, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_12, TRUE);
							SETTIMERB( 0 );
							wave = 0;
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_DEAD(ped2))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_38", 5000, 1);//~r~Diaz died! You failed to protect him!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						else if (IS_CHAR_INJURED(ped2))
						{
							EXPLODE_CHAR_HEAD(ped2);
						}
					}
				}

				if (skip == 0)
				{
					textur = LOAD_TXD( "sunshine_race" );
					fon = GET_TEXTURE( textur, "fon_hud" );

					while(true)
					{
						WAIT(0);
						// HUD здоровья Диаса и Ленса
						GET_CHAR_HEALTH(ped1, &Lance_hp);
						GET_CHAR_HEALTH(ped2, &Diaz_hp);
						pedHUD_x = 0.922156;
						pedHUD_w = 0.0739583;

						// -------------------------- Diaz HUD --------------------------
						DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );
						DRAW_SPRITE( 0, 0.915054, 0.74213, 0.059166, 0.014, 0.0, 27, 89, 130, 255 );// рисуем фоновую текстуру.
						if (Diaz_hp < 105)
						{
							DiazH1 = 0;
						}
						else
						{
							DiazH1 = Diaz_hp-100;
						}
						DiazH2 = pedHUD_w/500;
						DiazH3 = DiazH2*DiazH1;
						DiazHUD_y1 = pedHUD_w-DiazH3;
						DiazHUD_y2 = DiazHUD_y1/2;
						DiazHUD_y3 = pedHUD_x-DiazHUD_y2;
						DRAW_SPRITE( 0, DiazHUD_y3, 0.74213, DiazH3, 0.014, 0.0, 97, 194, 247, 255 );// рисуем фоновую текстуру.

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78815097, 0.73564852, "GEN3_22"); //DIAZ'S HEALTH:

						// -------------------------- Lance HUD --------------------------
						DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
						DRAW_SPRITE( 0, 0.915054, 0.7838, 0.059166, 0.014, 0.0, 27, 89, 130, 255 );// рисуем фоновую текстуру.
						if (Lance_hp < 105)
						{
							LanceH1 = 0;
						}
						else
						{
							LanceH1 = Lance_hp-100;
						}
						LanceH2 = pedHUD_w/500;
						LanceH3 = LanceH2*LanceH1;
						LanceHUD_y1 = pedHUD_w-LanceH3;
						LanceHUD_y2 = LanceHUD_y1/2;
						LanceHUD_y3 = pedHUD_x-LanceHUD_y2;
						DRAW_SPRITE( 0, LanceHUD_y3, 0.7838, LanceH3, 0.014, 0.0, 97, 194, 247, 255 );// рисуем фоновую текстуру.

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78815097, 0.77731852, "GEN3_49"); //LANCE'S HEALTH:

						if (wave == 0)
						{
							if ((IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)))// проверка люди Диаса мертвы
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GEN3_33", 5000, 1);//~r~Check your fire!! You're supposed to be watching over Diaz and his men, not shooting them!
								skip = 1;// переменная пропуска
								break;
							}
							else if ((IS_CHAR_DEAD(ped5)) || (IS_CHAR_DEAD(ped6)))// проверка Кубинцы мертвы
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GEN3_34", 5000, 1);//~r~There ain't gonna be a deal if you shoot the Cubans!
								skip = 1;// переменная пропуска
								break;
							}
						}
						
						if (TIMERB() > 10000)
						{
							if (wave == 0)
							{
								SET_OBJECT_COORDINATES(keis, 893.853, 37.61, 5.061);// ставим кейс
								SETTIMERB( 0 );
								wave = 1;
							}
							else if (wave == 1)
							{
								if (gogogo == 0)
								{
									ADD_BLIP_FOR_CHAR(ped7, &cortez_ico);
									CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cortez_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
									CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // масштаб иконки на радаре
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

									CLEAR_AREA(891.904, 26.789, 4.831, 15.0, 1);//очещаем зону загрузки
									CLEAR_AREA(877.868, 7.5111, 3.854, 15.0, 1);//очещаем зону загрузки
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car4, 3002, 0.0, 0.0, 0.0);// подъезд вуду1
									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "GEN3_19", 5000, 1);//~g~Haitians! They're busting the deal! Protect Diaz!
                                    gogogo = 1;
									area_check = true;
								}
								if (TIMERB() > 21000)
								{
									// агрим
									UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_12);
									UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_12);
									SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_12, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_12, TRUE);

									SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
									SET_CHAR_RELATIONSHIP(ped7, 5, 0);
									SET_CHAR_RELATIONSHIP(ped8, 5, 0);
									SET_SENSE_RANGE(ped7, 80.0);
									SET_SENSE_RANGE(ped8, 80.0);
									SET_CHAR_WILL_USE_COVER(ped7, 1);
									SET_CHAR_WILL_USE_COVER(ped8, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, FALSE);
									SET_CHAR_SHOOT_RATE(ped7, 45);
									SET_CHAR_SHOOT_RATE(ped8, 35);
									STOP_PLAYBACK_RECORDED_CAR(car4);
									REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре

									SETTIMERB( 0 );
									gogogo = 0;
									wave = 2;
								}
							}
							else if (wave == 2)
							{
								if (gogogo == 0)
								{
									ADD_BLIP_FOR_CHAR(ped9, &cortez_ico);
									CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cortez_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
									CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // масштаб иконки на радаре
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//иконка на радаре называние в истории карты "магазин одежды"

									CLEAR_AREA(891.904, 26.789, 4.831, 15.0, 1);//очещаем зону загрузки
									CLEAR_AREA(877.868, 7.5111, 3.854, 15.0, 1);//очещаем зону загрузки
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car5, 3003, 0.0, 0.0, 0.0);// подъезд вуду2
									gogogo = 1;
								}
								if (TIMERB() > 20000)
								{
									// агрим
									UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_12);
									UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_12);
									SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_12, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_12, TRUE);

									SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
									SET_CHAR_RELATIONSHIP(ped9, 5, 0);
									SET_CHAR_RELATIONSHIP(ped10, 5, 0);
									SET_SENSE_RANGE(ped9, 80.0);
									SET_SENSE_RANGE(ped10, 80.0);
									SET_CHAR_WILL_USE_COVER(ped9, 1);
									SET_CHAR_WILL_USE_COVER(ped10, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, FALSE);
									SET_CHAR_SHOOT_RATE(ped9, 55);
									SET_CHAR_SHOOT_RATE(ped10, 35);
									STOP_PLAYBACK_RECORDED_CAR(car5);
									REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре

									SETTIMERB( 0 );
									gogogo = 0;
									wave = 3;
								}
							}
							else if (wave == 3)
							{
								if (gogogo == 0)
								{
									ADD_BLIP_FOR_CHAR(ped11, &cortez_ico);
									CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cortez_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
									CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // масштаб иконки на радаре
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//иконка на радаре называние в истории карты "магазин одежды"

									CLEAR_AREA(891.904, 26.789, 4.831, 15.0, 1);//очещаем зону загрузки
									CLEAR_AREA(877.868, 7.5111, 3.854, 15.0, 1);//очещаем зону загрузки
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car6, 3004, 0.0, 0.0, 0.0);// подъезд буритто1
									gogogo = 1;
								}
								if (TIMERB() > 13000)
								{
									// агрим
									UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_12);
									UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_12);
									UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_12);
									UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_12);
									SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_12, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_12, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_EPISODIC_12, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_EPISODIC_12, TRUE);
									SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
									SET_CHAR_RELATIONSHIP(ped11, 5, 0);
									SET_CHAR_RELATIONSHIP(ped12, 5, 0);
									SET_CHAR_RELATIONSHIP(ped13, 5, 0);
									SET_CHAR_RELATIONSHIP(ped14, 5, 0);
									SET_SENSE_RANGE(ped11, 80.0);
									SET_SENSE_RANGE(ped12, 80.0);
									SET_SENSE_RANGE(ped13, 80.0);
									SET_SENSE_RANGE(ped14, 80.0);
									SET_CHAR_WILL_USE_COVER(ped11, 1);
									SET_CHAR_WILL_USE_COVER(ped12, 1);
									SET_CHAR_WILL_USE_COVER(ped13, 1);
									SET_CHAR_WILL_USE_COVER(ped14, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, FALSE);
									SET_CHAR_SHOOT_RATE(ped11, 25);
									SET_CHAR_SHOOT_RATE(ped12, 45);
									SET_CHAR_SHOOT_RATE(ped13, 35);
									SET_CHAR_SHOOT_RATE(ped14, 25);
									STOP_PLAYBACK_RECORDED_CAR(car6);
									REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре

									SETTIMERB( 0 );
									gogogo = 0;
									wave = 4;
								}
							}
							else if (wave == 4)
							{
								if (gogogo == 0)
								{
									ADD_BLIP_FOR_CHAR(ped15, &cortez_ico);
									CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cortez_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
									CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // масштаб иконки на радаре
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//иконка на радаре называние в истории карты "магазин одежды"

									CLEAR_AREA(894.659, 54.979, 4.831, 15.0, 1);//очещаем зону загрузки
									CLEAR_AREA(897.339, 83.125, 3.854, 15.0, 1);//очещаем зону загрузки
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car7, 3006, 0.0, 0.0, 0.0);// подъезд буритто2
									gogogo = 1;
								}
								if (TIMERB() > 19000)
								{
									// агрим
									UpdateWeaponOfPed(ped15, WEAPON_EPISODIC_12);
									UpdateWeaponOfPed(ped16, WEAPON_EPISODIC_12);
									UpdateWeaponOfPed(ped17, WEAPON_EPISODIC_12);
									UpdateWeaponOfPed(ped18, WEAPON_EPISODIC_12);
									SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_EPISODIC_12, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_EPISODIC_12, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_EPISODIC_12, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_EPISODIC_12, TRUE);
									SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped16, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped17, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped18, 5);
									SET_CHAR_RELATIONSHIP(ped15, 5, 0);
									SET_CHAR_RELATIONSHIP(ped16, 5, 0);
									SET_CHAR_RELATIONSHIP(ped17, 5, 0);
									SET_CHAR_RELATIONSHIP(ped18, 5, 0);
									SET_SENSE_RANGE(ped15, 80.0);
									SET_SENSE_RANGE(ped16, 80.0);
									SET_SENSE_RANGE(ped17, 80.0);
									SET_SENSE_RANGE(ped18, 80.0);
									SET_CHAR_WILL_USE_COVER(ped15, 1);
									SET_CHAR_WILL_USE_COVER(ped16, 1);
									SET_CHAR_WILL_USE_COVER(ped17, 1);
									SET_CHAR_WILL_USE_COVER(ped18, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, FALSE);
									SET_CHAR_SHOOT_RATE(ped15, 35);
									SET_CHAR_SHOOT_RATE(ped16, 25);
									SET_CHAR_SHOOT_RATE(ped17, 65);
									SET_CHAR_SHOOT_RATE(ped18, 25);
									STOP_PLAYBACK_RECORDED_CAR(car7);
									REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре

									SETTIMERB( 0 );
									gogogo = 0;
									wave = 5;
                                    area_check = false;
								}
							}
							else if (wave == 5)
							{
								if (gogogo == 0)
								{
									ADD_BLIP_FOR_CHAR(ped19, &cortez_ico);
									CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cortez_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
									CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // масштаб иконки на радаре
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//иконка на радаре называние в истории карты "магазин одежды"

									CLEAR_AREA(891.904, 26.789, 4.831, 15.0, 1);//очещаем зону загрузки
									CLEAR_AREA(877.868, 7.5111, 3.854, 15.0, 1);//очещаем зону загрузки
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car8, 3005, 0.0, 0.0, 0.0);// подъезд вуду3
									gogogo = 1;
								}
								if (TIMERB() > 17000)
								{
									// агрим
									UpdateWeaponOfPed(ped19, WEAPON_EPISODIC_12);
									UpdateWeaponOfPed(ped20, WEAPON_EPISODIC_12);
									UpdateWeaponOfPed(ped21, WEAPON_EPISODIC_13);
									UpdateWeaponOfPed(ped22, WEAPON_EPISODIC_13);
									SET_CURRENT_CHAR_WEAPON(ped21, WEAPON_EPISODIC_13, TRUE);
									SET_CURRENT_CHAR_WEAPON(ped22, WEAPON_EPISODIC_13, TRUE);
									SET_CHAR_RELATIONSHIP_GROUP(ped19, 5);
									SET_CHAR_RELATIONSHIP_GROUP(ped20, 5);
									SET_CHAR_RELATIONSHIP(ped19, 5, 0);
									SET_CHAR_RELATIONSHIP(ped20, 5, 0);
									SET_SENSE_RANGE(ped19, 80.0);
									SET_SENSE_RANGE(ped20, 80.0);
									SET_CHAR_WILL_USE_COVER(ped19, 1);
									SET_CHAR_WILL_USE_COVER(ped20, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, FALSE);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, FALSE);
									SET_CHAR_SHOOT_RATE(ped19, 45);
									SET_CHAR_SHOOT_RATE(ped20, 55);
									STOP_PLAYBACK_RECORDED_CAR(car8);
									REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре

									SETTIMERB( 0 );
									gogogo = 0;
									wave = 6;
								}
							}
							else if (wave == 6)
							{
								if (gogogo == 0 &&
									IS_CHAR_INJURED(ped7) &&
									IS_CHAR_INJURED(ped8) &&
									IS_CHAR_INJURED(ped9) &&
									IS_CHAR_INJURED(ped10) &&
									IS_CHAR_INJURED(ped11) &&
									IS_CHAR_INJURED(ped12) &&
									IS_CHAR_INJURED(ped13) &&
									IS_CHAR_INJURED(ped14) &&
									IS_CHAR_INJURED(ped15) &&
									IS_CHAR_INJURED(ped16) &&
									IS_CHAR_INJURED(ped17) &&
									IS_CHAR_INJURED(ped18) &&
									IS_CHAR_INJURED(ped19) &&
									IS_CHAR_INJURED(ped20))
								{
									// Aaeoyia aaoo									
									SET_CHAR_COORDINATES_NO_OFFSET(ped2, 893.469, 43.037, 5.108);// ia?aiauaai 
									SET_CHAR_HEADING(ped2, -160.0);

									CLEAR_AREA(897.339, 83.125, 4.951, 15.0, 1);//очещаем зону загрузки
									CLEAR_AREA(894.659, 54.979, 4.951, 15.0, 1);//очещаем зону загрузки
									CLEAR_AREA(884.946, 5.731, 3.854, 20.0, 1);//очещаем зону загрузки
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car9, 3008, 0.0, 0.0, 0.0);// подъезд Санцез 1
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car10, 3007, 0.0, 0.0, 0.0);// подъезд Санцез 2
									
									// ставим камеру
									GET_CHAR_COORDINATES(ped21,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
									SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
									CREATE_CAM( 14, &camera );
									POINT_CAM_AT_COORD	( camera, PedX+0.617, PedY-2.174, PedZ+0.457); // куда смотрит камера
									SET_CAM_POS			( camera, PedX+0.617, PedY+3.544, PedZ+0.505 );//расположение камеры
									SET_CAM_ACTIVE( camera, 1 );
									SET_CAM_PROPAGATE( camera, 1 );
									ACTIVATE_SCRIPTED_CAMS(1, 1);
									SET_CAM_FOV( camera, 45.0 );
									SET_WIDESCREEN_BORDERS( 1 );

									SET_CAR_COORDINATES(car2, 893.78, 46.3, 5.445);// перемещаем игрока
									SET_CAR_COORDINATES(car7, 295.942, -787.416, 5.445);// перемещаем игрока
									SET_CAR_COORDINATES(car8, 292.585, -787.416, 5.445);// перемещаем игрока
									SET_CAR_HEADING(car2, 176.41);
									SET_CAR_HEADING(car7, 0.0);
									SET_CAR_HEADING(car8, 0.0);
									SETTIMERB( 0 );
									text = 0;
									

									while(true)
									{
										WAIT(0);
										if (text == 0)
										{
											// камера 1
											GET_CHAR_COORDINATES(ped21,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
											POINT_CAM_AT_COORD	( camera, PedX+0.617, PedY-2.174, PedZ+0.457); // куда смотрит камера
											SET_CAM_POS			( camera, PedX+0.617, PedY+3.544, PedZ+0.505 );//расположение камеры
										}
										else
										{
											// камера 2
											GET_CHAR_COORDINATES(ped22,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
											POINT_CAM_AT_COORD	( camera, PedX, PedY, PedZ); // куда смотрит камера
											SET_CAM_POS			( camera, 888.129, 27.327, 10.96 );//расположение камеры
										}

										if (((IS_CHAR_IN_AREA_3D( ped22, 898.26, 32.856, 4.897, 888.26, 44.702, 14.897, 0 )) && (text == 0)) || ((TIMERB() > 20000) && (text == 0)))
										{
											SETTIMERB( 0 );
											text = 1;
										}
										if ((text == 1) && (TIMERB() > 500))
										{
											NEW_SCRIPTED_CONVERSATION();
											ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
											ADD_LINE_TO_CONVERSATION(0, "R4_GF", "GEN3_53", 0, 0);// MY MONEY!
											START_SCRIPT_CONVERSATION(1, 1);
											SET_OBJECT_COORDINATES(keis, 0.853, 0.61, -5.061);// прячим кейс
											SETTIMERB( 0 );
											text = 2;
										}
										if ((text == 2) && (TIMERB() > 1600))
										{
											SetSpeech();
											NEW_SCRIPTED_CONVERSATION();
											ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
											ADD_LINE_TO_CONVERSATION(0, "R4_GG", "", 0, 0);// выстрел
											START_SCRIPT_CONVERSATION(1, 1);

											EXPLODE_CHAR_HEAD(ped21);
											STOP_PLAYBACK_RECORDED_CAR(car9);
											SetSpeech();
											break;
										}

									}
									SetTime(2000);	

									// удаляем камеру
									ACTIVATE_SCRIPTED_CAMS( 0, 0 );
									DESTROY_CAM( camera );
									SET_WIDESCREEN_BORDERS( 0 );
									SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R4_GH", "GEN3_54", 0, 0);//Don't just stand there, you pricks, chase that Haitian dickhead down!
									START_SCRIPT_CONVERSATION(1, 1);

									SET_CAR_COORDINATES(car9, 884.92, -11.548, 5.445);// перемещаем игрока
									SET_CAR_HEADING(car9, 160.00);

									ADD_BLIP_FOR_CHAR(ped22, &cortez_ico);
									CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cortez_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
									CHANGE_BLIP_SCALE(cortez_ico, 0.77999990); // масштаб иконки на радаре
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//иконка на радаре называние в истории карты "магазин одежды"
									SetTime(2000);
									SetSpeech();

									STOP_PLAYBACK_RECORDED_CAR(car10);
									TASK_CAR_DRIVE_WANDER(ped22, car10, 20.0, 2);// пед едит куда-то
									SetTime(2000);
									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "GEN3_36", 5000, 1);//~g~Grab the bike, chase him down and get Diaz's money back!

									SETTIMERB( 0 );
									SETTIMERC( 0 );
									SET_PED_FALL_OFF_BIKES_WHEN_SHOT(ped22, false);
									gogogo = 0;
									wave = 7;
									break;
								}
							}
						}
						if (area_check && !IS_CHAR_IN_AREA_2D(GetPlayerPed(), 474.124 + MAP_OFFSET_X, -461.5191 + MAP_OFFSET_Y, 441.1417 + MAP_OFFSET_X, -531.2878 + MAP_OFFSET_Y, false) && !IS_CHAR_DEAD(ped2) && !IS_CHAR_ON_SCREEN(ped2))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_56", 5000, 1);//~r~Diaz was ambushed and died! Next time keep him in your sights!
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_DEAD(ped2))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_38", 5000, 1);//~r~Diaz died! You failed to protect him!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (Lance_hp < 100)
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						else if (Diaz_hp < 100)
						{
							EXPLODE_CHAR_HEAD(ped2);
						}
					}
				}

				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (IS_CHAR_DEAD(ped22))
						{
							REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
							GET_CHAR_COORDINATES(ped22,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &PedZ);

							CREATE_PICKUP( mission_keis, 22, PedX+0.2, PedY+0.2, PedZ+0.2, &bag, 0 );// сумка
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_29", 5000, 1);//~g~Collect the briefcase and take it back to Diaz.

							ADD_BLIP_FOR_PICKUP(bag, &cortez_ico);
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(cortez_ico, 19);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//иконка на радаре "Товар"
							break;
						}

						if ((TIMERB() > 6000) && (gogogo == 0) && (!IS_CHAR_DEAD(ped22)))
						{
							TASK_CAR_DRIVE_WANDER(ped22, car10, 40.0, 2);// пед едит куда-то
							gogogo = 1;
						}

						GET_CHAR_COORDINATES(ped22,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//проверка "игрок на координатах"
						if ( PlayR > 250.5)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_30", 5000, 1);//~r~He got away with the money! Diaz will have your balls for this!
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_DEAD(ped2))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GEN3_38", 5000, 1);//~r~Diaz died! You failed to protect him!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						else if (IS_CHAR_INJURED(ped2))
						{
							EXPLODE_CHAR_HEAD(ped2);
						}
					}
				}
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (HAS_PICKUP_BEEN_COLLECTED( bag ))
						{
							FIX_CAR(car2);// чиним машину диаса
							FIX_CAR(car3);// чиним машину 
							FIX_CAR(car4);// чиним машину 
							SET_CHAR_HEALTH(ped1, 400);
							SET_CHAR_HEALTH(ped2, 400);
							WAIT(500);


							SET_CAR_COORDINATES(car2, 894.18, 42.15, 5.73);// перемещаем игрока
							SET_CAR_HEADING(car2, 175.0);
							TASK_ENTER_CAR_AS_DRIVER(ped2, car2, TRUE);// садим Диаса в машину
							WAIT(500);
						
							// прячим Педов
							SET_CHAR_COORDINATES(ped1, 291.135, -767.684, 5.06);// перемещаем 
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
							CLEAR_AREA(888.8, 11.1, 5.5, 75.5, 0);//очещаем зону загрузки
							clear_ped = 1;

							/*/ прячим Педов
							SET_CHAR_COORDINATES(ped3, 292.135, -767.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped4, 293.135, -767.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped5, 294.135, -767.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped6, 295.135, -767.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped7, 291.135, -766.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped8, 292.135, -766.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped9, 293.135, -766.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped10, 294.135, -766.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped11, 295.135, -766.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped12, 291.135, -765.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped13, 292.135, -765.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped14, 293.135, -765.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped15, 294.135, -765.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped16, 295.135, -765.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped17, 291.135, -764.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped18, 292.135, -764.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped19, 293.135, -764.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped20, 294.135, -764.684, 5.06);// перемещаем 
							SET_CHAR_COORDINATES(ped21, 295.135, -764.684, 5.06);// перемещаем 
							WAIT(500);
							//*/

							// прячем машины вагов
							SET_CAR_COORDINATES(car3, 899.157, 37.433, 5.065);// перемещаем игрока
							SET_CAR_COORDINATES(car4, 896.312, 30.915, 5.065);// перемещаем игрока
							SET_CAR_COORDINATES(car5, 286.008, -779.725, 5.445);// перемещаем игрока
							SET_CAR_COORDINATES(car6, 299.551, -787.416, 5.445);// перемещаем игрока
							SET_CAR_COORDINATES(car7, 295.942, -787.416, 5.445);// перемещаем игрока
							SET_CAR_COORDINATES(car8, 292.585, -787.416, 5.445);// перемещаем игрока
							SET_CAR_HEADING(car3, -15.0);
							SET_CAR_HEADING(car4, -25.0);
							SET_CAR_HEADING(car5, 0.0);
							SET_CAR_HEADING(car6, 0.0);
							SET_CAR_HEADING(car7, 0.0);
							SET_CAR_HEADING(car8, 0.0);
							WAIT(500);

							REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_COORD(895.972, 42.967, 4.954, &cortez_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
							CHANGE_BLIP_COLOUR(cortez_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(cortez_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//иконка на радаре называние в истории карты ""
							PRINT_STRING_IN_STRING("string", "GEN3_28", 5000, 1);//~g~Take the briefcase back to Diaz.
							WAIT(500);
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							PRINT_STRING_IN_STRING("string", "NECOK2_D", 5000, 1);//~r~Lance is dead.
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_DEAD(ped2))
						{
							PRINT_STRING_IN_STRING("string", "GEN3_38", 5000, 1);//~r~Diaz died! You failed to protect him!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						else if (IS_CHAR_INJURED(ped2))
						{
							EXPLODE_CHAR_HEAD(ped2);
						}
					}
				}
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						DRAW_CHECKPOINT( 895.972, 42.967, 4.954, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 895.972, 42.967, 4.954, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							FIX_CAR(car2);// чиним машину 
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 3009, 0.0, 0.0, 0.0);
							PAUSE_PLAYBACK_RECORDED_CAR(car2);
							SET_CHAR_COORDINATES(GetPlayerPed(), 895.662, 41.629, 5.156);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 80.0);

							// ставим камеру
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 895.585, 42.791, 5.664); // куда смотрит камера
							SET_CAM_POS			( camera, 891.361, 38.441, 6.598 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							// воспроизводим аудио.
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_HA", "GEN3_9", 0, 0);//I live! Dickheads! And it's all down to you! What is your name?
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();	

							// смена ракурса
							POINT_CAM_AT_COORD	( camera, 892.826, 40.272, 5.193); // куда смотрит камера
							SET_CAM_POS			( camera, 897.216, 46.511, 6.773 );//расположение камеры

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_HB", "GEN3_10", 0, 0);//Tommy.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();


							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_HC", "GEN3_11", 0, 0);//I see you soon, amigo, I think!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							UNPAUSE_PLAYBACK_RECORDED_CAR(car2);
							SetTime(3000);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_HD", "GEN3_12", 0, 0);//Shit. Where's that guy Lance?
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// удаляем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							SET_CAR_COORDINATES(car10, 289.167, -787.416, 5.445);// перемещаем игрока
							SET_CAR_HEADING(car10, 0.0);
							FIX_CAR(car9);// чиним машину 
							SET_CAR_COORDINATES(car9, 895.007, 25.38, 5.445);// перемещаем игрока
							SET_CAR_HEADING(car9, -15.0);

							STOP_PLAYBACK_RECORDED_CAR(car2);
							SET_CAR_COORDINATES(car2, 295.942, -779.725, 5.445);// перемещаем игрока
							SET_CAR_HEADING(car2, 0.0);
							skip = 2;// переменная пропуска
							break;
						}
						else if (IS_CHAR_DEAD(ped2))
						{
							PRINT_STRING_IN_STRING("string", "GEN3_38", 5000, 1);//~r~Diaz died! You failed to protect him!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_INJURED(ped2))
						{
							EXPLODE_CHAR_HEAD(ped2);
						}
					}
				}

				REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
				REMOVE_PICKUP(sweap_1);// выгружаем оружие
				REMOVE_PICKUP(bag);// выгружаем кейс
				SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);
				SET_MAX_WANTED_LEVEL(6);

				RELEASE_TEXTURE( fon );
				REMOVE_TXD( textur );

				STOP_PLAYBACK_RECORDED_CAR(car1);
				STOP_PLAYBACK_RECORDED_CAR(car2);
				STOP_PLAYBACK_RECORDED_CAR(car3);
				STOP_PLAYBACK_RECORDED_CAR(car4);
				STOP_PLAYBACK_RECORDED_CAR(car5);
				STOP_PLAYBACK_RECORDED_CAR(car6);
				STOP_PLAYBACK_RECORDED_CAR(car7);
				STOP_PLAYBACK_RECORDED_CAR(car8);
				STOP_PLAYBACK_RECORDED_CAR(car9);
				STOP_PLAYBACK_RECORDED_CAR(car10);

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM6);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM7);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM5);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM6);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(keisM);//выгружаем модель

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				if (clear_ped == 0)
				{
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
				}


				if (del_car == 0)
				{
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
					MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				}

				// выгружаем из памяти транспорт
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car7);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car8);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car9);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car10);//выгружаем модель машины(в последствии машина изчезнет)

				// выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 2999 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3000 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3001 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3002 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3003 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3004 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3005 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3006 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3007 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3008 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3009 ); // выгружаем пути транспорта

				DELETE_OBJECT(&keis);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&keis);
				if (car11 != 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car11);//выгружаем модель машины(в последствии машина изчезнет)
				}

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_COL_3" );//Guardian Angels
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(1000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +1000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 1000);
					G_CORTEZ = 4;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== Sir, Yes Sir! ======================================
		else if ((G_ONMISSION == 0) && (G_CORTEZ == 5))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(189.427, -827.564, 2.028, &cortez_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_GAMBETTI);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(cortez_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "LG_04");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 189.427, -827.564, 2.028, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 189.427, -827.564, 2.028, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("COL_4", 15000, CUTSCENE_GENERAL);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-163.0, -1439.4, 9.0, 201.5);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
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

				SET_CHAR_COORDINATES(GetPlayerPed(), 189.427, -827.564, 2.028);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -85.0);
				FORCE_WEATHER_NOW(WEATHER_SUNNY);
				RELEASE_WEATHER();
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "COL_4A", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("col_4a");
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

				Car car1, car2, car3, car4, car5;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20, ped21, ped22;
				Texture fon;

				uint PedM1 = MODEL_M_Y_GBIK_LO_02;// Солдат
				uint CarM1 = MODEL_PATRIOT;// Патриот
				uint CarM2 = MODEL_BIFF;// Грузовик
				uint CarM3 = MODEL_APC;// Танк
				
				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );

				ADD_ARMOUR_TO_CHAR(GetPlayerPed(), 100);
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				in_zon = 0;
				hate = 0;
				help_1 = 0;
				help_2 = 0;
				play = 0;
				in_car = 0;
				del_car = 0;
				passenger = 0;
				point = 1;
				terpenie = 0;
				car_blip = 0;
				delta = 0;
				hud_on = 0;
				boom = 0;
				garage = 0;
				in_garage = 0;
				Speech = 0;
				pedHUD_x = 0.9088541;
				pedHUD_w = 0.0739583;

				// грузим модели
				REQUEST_MODEL(PedM1);// 
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM1);// 
				while (!HAS_MODEL_LOADED(CarM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM2);// 
				while (!HAS_MODEL_LOADED(CarM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM3);// 
				while (!HAS_MODEL_LOADED(CarM3));////проверка "пед загрузился" если нет то начанаем с начало

				// создаём транспорт
				CREATE_CAR(CarM1, -423.002, 369.767, 5.417, &car1, TRUE);// Патриот
				CREATE_CAR(CarM2, -423.002, 378.171, 5.417, &car2, TRUE);// Грузовик
				CREATE_CAR(CarM3, -423.002, 386.576, 5.417, &car3, TRUE);// Танк
				CREATE_CAR(CarM2, -423.002, 394.981, 5.417, &car4, TRUE);// Грузовик
				CREATE_CAR(CarM1, 286.008, -779.725, 5.445, &car5, TRUE);// Вуду
				SET_CAR_HEADING(car1, 180.0);
				SET_CAR_HEADING(car2, 180.0);
				SET_CAR_HEADING(car3, 180.0);
				SET_CAR_HEADING(car4, 180.0);

				LOCK_CAR_DOORS(car1, 3); // запераем автомобиль
				LOCK_CAR_DOORS(car2, 3); // запераем автомобиль
				LOCK_CAR_DOORS(car3, 3); // запераем автомобиль
				LOCK_CAR_DOORS(car4, 3); // запераем автомобиль
				TURN_OFF_VEHICLE_EXTRA( car2, 2, 1 );
				TURN_OFF_VEHICLE_EXTRA( car4, 2, 1 );

				CHANGE_CAR_COLOUR( car1, 96, 96 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car1, 112, 112 );//цвет отрожений машины
				CHANGE_CAR_COLOUR( car2, 112, 112 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car2, 112, 112 );//цвет отрожений машины
				CHANGE_CAR_COLOUR( car3, 112, 112 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car3, 112, 112 );//цвет отрожений машины
				CHANGE_CAR_COLOUR( car4, 112, 112 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car4, 112, 112 );//цвет отрожений машины

				// создаём педов за рулёп
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);// Патриот за рулём Солдат
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM1, &ped2);// Грузовик за рулём Солдат
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM1, &ped3);// Танк за рулём Солдат
				CREATE_CHAR_INSIDE_CAR(car4, 1, PedM1, &ped4);// Грузовик за рулём Солдат

				// создаём педов пассажиров
				CREATE_CHAR_AS_PASSENGER(car1, 1, PedM1, 0, &ped5);// Патриот пассажир Солдат
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM1, 0, &ped6);// Грузовик пассажир Солдат
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM1, 0, &ped7);// Танк пассажир Солдат
				CREATE_CHAR_AS_PASSENGER(car4, 1, PedM1, 0, &ped8);// Грузовик пассажир Солдат

				// создаём педов
				CREATE_CHAR (26, PedM1, -426.583, 377.662, 5.094, &ped9, TRUE);// конвоир 1
				CREATE_CHAR (26, PedM1, -419.908, 377.662, 5.094, &ped10, TRUE);// конвоир 1
				CREATE_CHAR (26, PedM1, -426.583, 379.739, 5.094, &ped11, TRUE);// конвоир 1
				CREATE_CHAR (26, PedM1, -419.908, 379.739, 5.094, &ped12, TRUE);// конвоир 1
				CREATE_CHAR (26, PedM1, -425.881, 393.487, 5.094, &ped13, TRUE);// конвоир 1
				CREATE_CHAR (26, PedM1, -419.781, 393.487, 5.094, &ped14, TRUE);// конвоир 1
				CREATE_CHAR (26, PedM1, -425.881, 395.564, 5.094, &ped15, TRUE);// конвоир 1
				CREATE_CHAR (26, PedM1, -419.781, 395.564, 5.094, &ped16, TRUE);// конвоир 1

				CREATE_CHAR (26, PedM1, -426.002, 383.576, 5.094, &ped17, TRUE);// конвоир 1
				CREATE_CHAR (26, PedM1, -426.002, 386.576, 5.094, &ped18, TRUE);// конвоир 2
				CREATE_CHAR (26, PedM1, -426.002, 389.576, 5.094, &ped19, TRUE);// конвоир 3
				CREATE_CHAR (26, PedM1, -420.002, 383.576, 5.094, &ped20, TRUE);// конвоир 1
				CREATE_CHAR (26, PedM1, -420.002, 386.576, 5.094, &ped21, TRUE);// конвоир 2
				CREATE_CHAR (26, PedM1, -420.002, 389.576, 5.094, &ped22, TRUE);// конвоир 3

				SET_CHAR_HEADING(ped17, 180.0);
				SET_CHAR_HEADING(ped18, 180.0);
				SET_CHAR_HEADING(ped19, 180.0);
				SET_CHAR_HEADING(ped20, 180.0);
				SET_CHAR_HEADING(ped21, 180.0);
				SET_CHAR_HEADING(ped22, 180.0);

				// вооружаем
				UpdateWeaponOfPed(ped1, WEAPON_AK47);
				UpdateWeaponOfPed(ped2, WEAPON_AK47);
				UpdateWeaponOfPed(ped3, WEAPON_PISTOL);
				UpdateWeaponOfPed(ped4, WEAPON_AK47);
				UpdateWeaponOfPed(ped5, WEAPON_PISTOL);
				UpdateWeaponOfPed(ped6, WEAPON_AK47);
				UpdateWeaponOfPed(ped7, WEAPON_PISTOL);
				UpdateWeaponOfPed(ped8, WEAPON_AK47);
				UpdateWeaponOfPed(ped9, WEAPON_AK47);
				UpdateWeaponOfPed(ped10, WEAPON_AK47);
				UpdateWeaponOfPed(ped11, WEAPON_AK47);
				UpdateWeaponOfPed(ped12, WEAPON_AK47);
				UpdateWeaponOfPed(ped13, WEAPON_AK47);
				UpdateWeaponOfPed(ped14, WEAPON_AK47);
				UpdateWeaponOfPed(ped15, WEAPON_AK47);
				UpdateWeaponOfPed(ped16, WEAPON_AK47);
				UpdateWeaponOfPed(ped17, WEAPON_AK47);
				UpdateWeaponOfPed(ped18, WEAPON_AK47);
				UpdateWeaponOfPed(ped19, WEAPON_AK47);
				UpdateWeaponOfPed(ped20, WEAPON_AK47);
				UpdateWeaponOfPed(ped21, WEAPON_AK47);
				UpdateWeaponOfPed(ped22, WEAPON_AK47);

				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_PISTOL, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_PISTOL, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_PISTOL, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped21, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped22, WEAPON_AK47, TRUE);

				SET_CHAR_HEALTH(ped1, 200);
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
				SET_CHAR_HEALTH(ped15, 200);
				SET_CHAR_HEALTH(ped16, 200);
				SET_CHAR_HEALTH(ped17, 200);
				SET_CHAR_HEALTH(ped18, 200);
				SET_CHAR_HEALTH(ped19, 200);
				SET_CHAR_HEALTH(ped20, 200);
				SET_CHAR_HEALTH(ped21, 200);
				SET_CHAR_HEALTH(ped22, 200);

				//таччим педов к машине
				ATTACH_PED_TO_CAR( ped9, car2, 0, -0.75, -0.934, 1.864, 3.0, 90, 1, 1 );
				ATTACH_PED_TO_CAR( ped10, car2, 0, -0.75, -3.441, 1.864, 3.0, 90, 1, 1 );
				ATTACH_PED_TO_CAR( ped11, car2, 0, 0.646, -0.934, 1.864, 0.0, 0, 1, 0 );
				ATTACH_PED_TO_CAR( ped12, car2, 0, 0.646, -3.441, 1.864, 0.0, 270, 0, 1 );

				ATTACH_PED_TO_CAR( ped13, car4, 0, -0.75, -0.934, 1.864, 3.0, 90, 1, 1 );
				ATTACH_PED_TO_CAR( ped14, car4, 0, -0.75, -3.441, 1.864, 3.0, 90, 1, 1 );
				ATTACH_PED_TO_CAR( ped15, car4, 0, 0.646, -0.934, 1.864, 0.0, 0, 1, 1 );
				ATTACH_PED_TO_CAR( ped16, car4, 0, 0.646, -3.441, 1.864, 0.0, 270, 0, 0 );

				FREEZE_CHAR_POSITION(ped9, 1);
				FREEZE_CHAR_POSITION(ped10, 1);
				FREEZE_CHAR_POSITION(ped11, 1);
				FREEZE_CHAR_POSITION(ped12, 1);
				FREEZE_CHAR_POSITION(ped13, 1);
				FREEZE_CHAR_POSITION(ped14, 1);
				FREEZE_CHAR_POSITION(ped15, 1);
				FREEZE_CHAR_POSITION(ped16, 1);


				ADD_BLIP_FOR_CAR(car3, &cortez_ico);
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(cortez_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(cortez_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

				PRINT_STRING_IN_STRING("string", "COL4_B1", 5000, 1);//~g~Go and acquire the piece of military hardware that is being taken through town.
				SetTime(8000);

				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -398.104, -116.811, 5.48731, 4, 3.5, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -398.837, -108.438, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -399.569, -100.065, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -400.302, -91.6919, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

				while(true)
				{
					WAIT(0);
					// получаем автомобиль игрока
					if (in_car == 0)
					{
						if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
						{
							if (IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), car5))
							{
								in_car = 1;
							}
							else
							{
								if (!IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), car3))
								{
									MARK_CAR_AS_NO_LONGER_NEEDED(&car5);
									GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car5);
								}
							}
						}
					}
					else if (in_car == 1) 
					{
						if (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
						{
							in_car = 0;
						}
					}

					// Отойди от танка
					GET_CHAR_COORDINATES(ped3,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 5.5) && (help_1 == 0))
					{
						help_1 = 1;
						SETTIMERC(0); //сбрасываем таймер 
						if (play == 0)
						{
							// отойди от танка!
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped7, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_HD_QQQ1", "COL4_7", 0, 0);//Civilian, move away from the tank!
							START_SCRIPT_CONVERSATION(1, 1);
							SETTIMERA(0); //сбрасываем таймер 
							play = 1;
						}
					}
					else if (help_1 == 1)
					{
						if ( TIMERC() > 3000 )
						{
							help_1 = 2;
						}
					}
					else if (help_1 == 2)
					{
						if ( TIMERC() > 8000 )
						{
							help_1 = 0;
						}
					}

					// Вояка отгоняет автомобиль/педа
					GET_CHAR_SPEED(ped1, &speed);
					GET_CHAR_SPEED(ped2, &speed2);
					GET_CHAR_SPEED(ped3, &speed3);
					GET_CHAR_SPEED(ped4, &speed4);

					if ((speed < 0.5) && (del_car == 0))
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_HEADING(ped1, &PedR); //получаем угол поворота игрока
						convoy_x = (0*COS((0-PedR))+(4*SIN((0-PedR))))+PedX;
						convoy_y = (4*COS((0-PedR))-(0*SIN((0-PedR))))+PedY;
						del_car = 5;
					}
					else if ((speed2 < 0.5) && (del_car == 0))
					{
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_HEADING(ped2, &PedR); //получаем угол поворота игрока
						convoy_x = (0*COS((0-PedR))+(4*SIN((0-PedR))))+PedX;
						convoy_y = (4*COS((0-PedR))-(0*SIN((0-PedR))))+PedY;
						del_car = 5;
					}
					else if ((speed3 < 0.5) && (del_car == 0))
					{
						GET_CHAR_COORDINATES(ped3,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_HEADING(ped3, &PedR); //получаем угол поворота игрока
						convoy_x = (0*COS((0-PedR))+(4*SIN((0-PedR))))+PedX;
						convoy_y = (4*COS((0-PedR))-(0*SIN((0-PedR))))+PedY;
						del_car = 5;
					}
					else if ((speed4 < 0.5) && (del_car == 0))
					{
						GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_HEADING(ped4, &PedR); //получаем угол поворота игрока
						convoy_x = (0*COS((0-PedR))+(4*SIN((0-PedR))))+PedX;
						convoy_y = (4*COS((0-PedR))-(0*SIN((0-PedR))))+PedY;
						del_car = 5;
					}
					if (del_car == 5)
					{
						del_car = 1;
						SETTIMERB(0); //сбрасываем таймер 
						GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, PedX, PedY, PedZ, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						GET_CHAR_COORDINATES(ped3,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, PedX, PedY, PedZ, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, PedX, PedY, PedZ, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, PedX, PedY, PedZ, 4, 3.5, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

						if (IS_CAR_IN_AREA_3D(car5, convoy_x+3, convoy_y+5, PedZ-2, convoy_x-3, convoy_y-5, PedZ+2, 0))
						{
							if (play == 0)
							{
								//Уберите эту гражданскую машину с нашего пути!
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_HE", "COL4_3", 0, 0);//CONVOY HALT!
								START_SCRIPT_CONVERSATION(1, 1);

								SETTIMERA(0); //сбрасываем таймер
								Speech = 1;
								play = 1;
							}
							terpenie += 1;
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped5, car5, PedX-12, PedY-12, PedZ, 4, 80.0, 2, 5, 10);// пед едит на нужные координаты
							while (true)
							{
								WAIT( 0 );
								if ((!IS_CAR_IN_AREA_3D(car5, convoy_x+6, convoy_y+8, PedZ-2, convoy_x-6, convoy_y-8, PedZ+2, 0)) && (passenger == 0))
								{
									TASK_ENTER_CAR_AS_PASSENGER(ped5, car1, 10000, 3);
									SETTIMERC(0); //сбрасываем таймер 
									passenger = 1;
								}
								GET_CHAR_COORDINATES(ped3,  &PedX2, &PedY2, &PedZ2);//вписываем координаты игрока в переменную
								if ((IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), car3)) || (terpenie > 4) || (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PedX2+45, PedY2+45, PedX2-45, PedY2-45, 0)))
								{
									hate = 1;
									break;
								}
								else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_DEAD(ped2)) || (IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)) || (IS_CHAR_DEAD(ped5)) || (IS_CHAR_DEAD(ped6)) || (IS_CHAR_DEAD(ped7)) || (IS_CHAR_DEAD(ped8)) || (IS_CHAR_DEAD(ped9)) || (IS_CHAR_DEAD(ped10)) || (IS_CHAR_DEAD(ped11)) || (IS_CHAR_DEAD(ped12)) || (IS_CHAR_DEAD(ped13)) || (IS_CHAR_DEAD(ped14)) || (IS_CHAR_DEAD(ped15)) || (IS_CHAR_DEAD(ped16)) || (IS_CHAR_DEAD(ped17)) || (IS_CHAR_DEAD(ped18)) || (IS_CHAR_DEAD(ped19)) || (IS_CHAR_DEAD(ped20)) || (IS_CHAR_DEAD(ped21)) || (IS_CHAR_DEAD(ped22)))
								{
									hate = 1;
									break;
								}
								else if ((IS_CHAR_INJURED(ped1)) || (IS_CHAR_INJURED(ped2)) || (IS_CHAR_INJURED(ped3)) || (IS_CHAR_INJURED(ped4)) || (IS_CHAR_INJURED(ped5)) || (IS_CHAR_INJURED(ped6)) || (IS_CHAR_INJURED(ped7)) || (IS_CHAR_INJURED(ped8)) || (IS_CHAR_INJURED(ped9)) || (IS_CHAR_INJURED(ped10)) || (IS_CHAR_INJURED(ped11)) || (IS_CHAR_INJURED(ped12)) || (IS_CHAR_INJURED(ped13)) || (IS_CHAR_INJURED(ped14)) || (IS_CHAR_INJURED(ped15)) || (IS_CHAR_INJURED(ped16)) || (IS_CHAR_INJURED(ped17)) || (IS_CHAR_INJURED(ped18)) || (IS_CHAR_INJURED(ped19)) || (IS_CHAR_INJURED(ped20)) || (IS_CHAR_INJURED(ped21)) || (IS_CHAR_INJURED(ped22)))
								{
									hate = 1;
									break;
								}
								if (passenger == 1)
								{
									if (IS_CHAR_SITTING_IN_CAR(ped5, car1))
									{
										if (point == 1)
										{
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -398.104, -116.811, 5.48731, 4, 3.5, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -398.837, -108.438, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -399.569, -100.065, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -400.302, -91.6919, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
										}
										else if (point == 3)
										{
											// Доки
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -389.988, -951.072, 5.978, 4, 3.5, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -387.114, -943.174, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -384.239, -935.276, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -381.364, -927.378, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги
										}
										passenger = 0;
										break;
									}
									else if ( TIMERC() > 15000 )
									{
										if (point == 1)
										{
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -398.104, -116.811, 5.48731, 4, 3.5, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -398.837, -108.438, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -399.569, -100.065, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -400.302, -91.6919, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
										}
										else if (point == 3)
										{
											// Доки
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -389.988, -951.072, 5.978, 4, 3.5, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -387.114, -943.174, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -384.239, -935.276, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -381.364, -927.378, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги
										}
										terpenie -= 1;
										WARP_CHAR_INTO_CAR_AS_PASSENGER(ped5, car1, 0);
										passenger = 0;
										break;
									}
								}
								if (play == 1)
								{
									if (!IS_SCRIPTED_CONVERSATION_ONGOING())
									{
										if (Speech == 1)
										{
											// Уберите эту гражданскую машину с нашего пути!
											NEW_SCRIPTED_CONVERSATION();
											ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
											ADD_LINE_TO_CONVERSATION(0, "R4_HF", "COL4_15", 0, 0);//Get that civilian vehicle out of our way! - Sir! Moving vehicle Sir!
											START_SCRIPT_CONVERSATION(1, 1);
											SETTIMERA(0); //сбрасываем таймер 
											Speech = 0;
										}
									}
									if ( TIMERA() > 5000 )
									{
										play = 0;
									}
								}
							}
						}
						// ---- Tommi
						else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), convoy_x+3, convoy_y+5, PedZ-2, convoy_x-3, convoy_y-5, PedZ+2, 0 ))
						{
							if (play == 0)
							{
								//Уберите этого гражданского с нашего пути!
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_HE", "COL4_3", 0, 0);//CONVOY HALT!
								START_SCRIPT_CONVERSATION(1, 1);

								SETTIMERA(0); //сбрасываем таймер 
								Speech = 2;
								play = 1;
							}
							TASK_LEAVE_CAR(ped5, car1);
							SET_CHAR_RELATIONSHIP_GROUP(ped5, 3);
							SET_CHAR_RELATIONSHIP(ped5, 3, 0);
							SET_SENSE_RANGE(ped5, 15.0);
							SET_CHAR_WILL_USE_COVER(ped5, 0);
							SET_CHAR_HEALTH(ped5, 200);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);
							TASK_COMBAT(ped5, GetPlayerPed());
							terpenie += 1;
							while (true)
							{
								WAIT( 0 );
								if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), convoy_x+3, convoy_y+5, PedZ-2, convoy_x-3, convoy_y-5, PedZ+2, 0 )) && (passenger == 0))
								{
									SET_SENSE_RANGE(ped5, 0.01);
									TASK_ENTER_CAR_AS_PASSENGER(ped5, car1, 10000, 3);
									SETTIMERC(0); //сбрасываем таймер 
									passenger = 1;
								}
								GET_CHAR_COORDINATES(ped3,  &PedX2, &PedY2, &PedZ2);//вписываем координаты игрока в переменную
								if ((IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), car3)) || (terpenie > 4) || (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PedX2+45, PedY2+45, PedX2-45, PedY2-45, 0)))
								{
									hate = 1;
									break;
								}
								else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_DEAD(ped2)) || (IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)) || (IS_CHAR_DEAD(ped5)) || (IS_CHAR_DEAD(ped6)) || (IS_CHAR_DEAD(ped7)) || (IS_CHAR_DEAD(ped8)) || (IS_CHAR_DEAD(ped9)) || (IS_CHAR_DEAD(ped10)) || (IS_CHAR_DEAD(ped11)) || (IS_CHAR_DEAD(ped12)) || (IS_CHAR_DEAD(ped13)) || (IS_CHAR_DEAD(ped14)) || (IS_CHAR_DEAD(ped15)) || (IS_CHAR_DEAD(ped16)) || (IS_CHAR_DEAD(ped17)) || (IS_CHAR_DEAD(ped18)) || (IS_CHAR_DEAD(ped19)) || (IS_CHAR_DEAD(ped20)) || (IS_CHAR_DEAD(ped21)) || (IS_CHAR_DEAD(ped22)))
								{
									hate = 1;
									break;
								}
								else if ((IS_CHAR_INJURED(ped1)) || (IS_CHAR_INJURED(ped2)) || (IS_CHAR_INJURED(ped3)) || (IS_CHAR_INJURED(ped4)) || (IS_CHAR_INJURED(ped5)) || (IS_CHAR_INJURED(ped6)) || (IS_CHAR_INJURED(ped7)) || (IS_CHAR_INJURED(ped8)) || (IS_CHAR_INJURED(ped9)) || (IS_CHAR_INJURED(ped10)) || (IS_CHAR_INJURED(ped11)) || (IS_CHAR_INJURED(ped12)) || (IS_CHAR_INJURED(ped13)) || (IS_CHAR_INJURED(ped14)) || (IS_CHAR_INJURED(ped15)) || (IS_CHAR_INJURED(ped16)) || (IS_CHAR_INJURED(ped17)) || (IS_CHAR_INJURED(ped18)) || (IS_CHAR_INJURED(ped19)) || (IS_CHAR_INJURED(ped20)) || (IS_CHAR_INJURED(ped21)) || (IS_CHAR_INJURED(ped22)))
								{
									hate = 1;
									break;
								}
								if (passenger == 1)
								{
									if (IS_CHAR_SITTING_IN_CAR(ped5, car1))
									{
										if (point == 1)
										{
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -398.104, -116.811, 5.48731, 4, 3.5, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -398.837, -108.438, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -399.569, -100.065, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -400.302, -91.6919, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
										}
										else
										{
											// Доки
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -389.988, -951.072, 5.978, 4, 3.5, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -387.114, -943.174, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -384.239, -935.276, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -381.364, -927.378, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги
										}
										passenger = 0;
										break;
									}
									else if ( TIMERC() > 15000 )
									{
										if (point == 1)
										{
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -398.104, -116.811, 5.48731, 4, 3.5, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -398.837, -108.438, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -399.569, -100.065, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -400.302, -91.6919, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
										}
										else if (point == 3)
										{
											// Доки
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -389.988, -951.072, 5.978, 4, 3.5, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -387.114, -943.174, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -384.239, -935.276, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
											TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -381.364, -927.378, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги
										}
										terpenie -= 1;
										SET_SENSE_RANGE(ped5, 0.1);
										WARP_CHAR_INTO_CAR_AS_PASSENGER(ped5, car1, 0);
										passenger = 0;
										break;
									}
								}
								if (play == 1)
								{
									if (!IS_SCRIPTED_CONVERSATION_ONGOING())
									{
										if (Speech == 2)
										{
											// Уберите этого гражданского с нашего пути!
											NEW_SCRIPTED_CONVERSATION();
											ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
											ADD_LINE_TO_CONVERSATION(0, "R4_HG", "COL4_11", 0, 0);//Get that civilian out of our way soldier! - Sir, Yes Sir!
											START_SCRIPT_CONVERSATION(1, 1);
											SETTIMERA(0); //сбрасываем таймер 
											Speech = 0;
										}
									}
									if ( TIMERA() > 5000 )
									{
										play = 0;
									}
								}
							}
						}
						else
						{
							del_car = 0;
							if (point == 1)
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -398.104, -116.811, 5.48731, 4, 3.5, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -398.837, -108.438, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -399.569, -100.065, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -400.302, -91.6919, 5.48731, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
							else if (point == 3)
							{
								// Доки
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -389.988, -951.072, 5.978, 4, 3.5, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -387.114, -943.174, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -384.239, -935.276, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -381.364, -927.378, 5.978, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги
							}
						}
					}
					else if ((speed > 2) && (del_car == 1))
					{
						if (play == 0)
						{
							// Хорошо, ВЗВОД, ВЫДВИГАЙТЕСЬ!
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_JA", "COL4_17", 0, 0);//Ok, PLATOON MOVE IT OUT!
							START_SCRIPT_CONVERSATION(1, 1);

							SETTIMERA(0); //сбрасываем таймер 
							play = 1;
						}
						del_car = 0;
					}
					else if ((speed < 1) && (del_car == 1))
					{
						if ( TIMERB() > 15000 )
						{
							del_car = 0;
						}
					}
					//DRAW_CHECKPOINT( convoy_x, convoy_y, PedZ, 4.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					//DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.66954074, "CP_TIME_NOZERO", del_car);// секунды
					//DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", speed*10);// секунды
					//DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.66954074, "CP_TIME_NOZERO", terpenie);// секунды

					//----------------------------------------------

					// аудио стоп
					if (play == 1)
					{
						if ((point == 1) || (point == 3))
						{
							if ( TIMERA() > 5000 )
							{
								play = 0;
							}
						}
						else if (point == 5)
						{
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								if (Speech == 3)
								{
									//Иди принеси пончиков, солдат!
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped7, "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R4_KA", "COL4_19", 0, 0);//Go get some doughnuts, soldier! - Sir, Yes Sir!
									START_SCRIPT_CONVERSATION(1, 1);
									SETTIMERA(0); //сбрасываем таймер 
									Speech = 0;
								}
							}
						
							if ( TIMERA() > 5000 )
							{
								SETTIMERA(0); //сбрасываем таймер 
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped7, -419.942, -101.064, 5.762, 3, -2, 2.5);// солдат бежит в магазин
								play = 0;
								point = 4;
							}
						}
					}
					//----------------------------------------------

					// Вояки покупают жратву тут
					if (point == 4)
					{
						if ( TIMERA() > 9000 )
						{
							SETTIMERA(0); //сбрасываем таймер 
							TASK_ENTER_CAR_AS_PASSENGER(ped7, car3, 10000, 3);
							point = 2;
						}
					}
					else if (point == 2)
					{
						if ( TIMERA() > 11000 )
						{
							// Хорошо, ВЗВОД, ВЫДВИГАЙТЕСЬ!
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped7, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_JA", "COL4_17", 0, 0);//Ok, PLATOON MOVE IT OUT!
							START_SCRIPT_CONVERSATION(1, 1);

							SETTIMERA(0); //сбрасываем таймер 
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped7, car3, 0);
							play = 1;
							point = 3;
						}
					}

					GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -398.104, -116.811, 5.48731, &PedR);//проверка "игрок на координатах"
					if (( PedR < 2.5 ) && (point == 1))
					{
						ABORT_SCRIPTED_CONVERSATION( 0 );
						play = 0;

						GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, PedX, PedY, PedZ, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						GET_CHAR_COORDINATES(ped3,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, PedX, PedY, PedZ, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, PedX, PedY, PedZ, 4, 4.0, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, PedX, PedY, PedZ, 4, 3.5, 4, 2, 2);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

						// Иди принеси пончиков, солдат!
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped7, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_HE", "COL4_3", 0, 0);//CONVOY HALT!
						START_SCRIPT_CONVERSATION(1, 1);

						SETTIMERA(0); //сбрасываем таймер 
						play = 1;
						point = 5;
						Speech = 3;
						LOCK_CAR_DOORS(car3, 1); // запераем автомобиль
					}
					//----------------------------------------------

					// фикс бегунов
					GET_CHAR_COORDINATES(ped3,  &PedX2, &PedY2, &PedZ2);//вписываем координаты игрока в переменную
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX2+65, PedY2+65, PedZ2-5, PedX2-65, PedY2-65, PedZ2+20, 0 )) && ( help_2 == 0))
					{
						GET_CHAR_COORDINATES(ped3,  &PedX2, &PedY2, &PedZ2);//вписываем координаты игрока в переменную
						GET_CHAR_HEADING(ped3, &PedR2); //получаем угол поворота игрока

						convoy_x2 = (3*COS((0-PedR2))+(3.5*SIN((0-PedR2))))+PedX2;
						convoy_y2 = (3.5*COS((0-PedR2))-(3*SIN((0-PedR2))))+PedY2;
						SET_CHAR_COORDINATES(ped17, convoy_x2, convoy_y2, PedZ2);// перемещаем игрока

						convoy_x2 = (3*COS((0-PedR2))+(-1*SIN((0-PedR2))))+PedX2;
						convoy_y2 = (-1*COS((0-PedR2))-(3*SIN((0-PedR2))))+PedY2;
						SET_CHAR_COORDINATES(ped18, convoy_x2, convoy_y2, PedZ2);// перемещаем игрока

						convoy_x2 = (3*COS((0-PedR2))+(-3.5*SIN((0-PedR2))))+PedX2;
						convoy_y2 = (-3.5*COS((0-PedR2))-(3*SIN((0-PedR2))))+PedY2;
						SET_CHAR_COORDINATES(ped19, convoy_x2, convoy_y2, PedZ2);// перемещаем игрока

						convoy_x2 = (-3*COS((0-PedR2))+(3*SIN((0-PedR2))))+PedX2;
						convoy_y2 = (3*COS((0-PedR2))-(-3*SIN((0-PedR2))))+PedY2;
						SET_CHAR_COORDINATES(ped20, convoy_x2, convoy_y2, PedZ2);// перемещаем игрока

						convoy_x2 = (-3*COS((0-PedR2))+(0*SIN((0-PedR2))))+PedX2;
						convoy_y2 = (0*COS((0-PedR2))-(-3*SIN((0-PedR2))))+PedY2;
						SET_CHAR_COORDINATES(ped21, convoy_x2, convoy_y2, PedZ2);// перемещаем игрока;

						convoy_x2 = (-3*COS((0-PedR2))+(-3*SIN((0-PedR2))))+PedX2;
						convoy_y2 = (-3*COS((0-PedR2))-(-3*SIN((0-PedR2))))+PedY2;
						SET_CHAR_COORDINATES(ped22, convoy_x2, convoy_y2, PedZ2);// перемещаем игрока
						help_2 = 1;
					}
					else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX2+65, PedY2+65, PedZ2-5, PedX2-65, PedY2-65, PedZ2+20, 0 )) && ( help_2 == 2))
					{
						help_2 = 0;
					}
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX2+20, PedY2+20, PedZ2-5, PedX2-20, PedY2-20, PedZ2+10, 0 )) && ( help_2 == 1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COL4_B6", 5000, 1);//~g~Find a way to steal the tank!
						help_2 = 2;
					}
					//----------------------------------------------

					// агрим вояк
					if ((IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), car3)) || (terpenie > 4) || (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PedX2+45, PedY2+45, PedX2-45, PedY2-45, 0)))
					{
						hate = 1;
					}
					else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_DEAD(ped2)) || (IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)) || (IS_CHAR_DEAD(ped5)) || (IS_CHAR_DEAD(ped6)) || (IS_CHAR_DEAD(ped7)) || (IS_CHAR_DEAD(ped8)) || (IS_CHAR_DEAD(ped9)) || (IS_CHAR_DEAD(ped10)) || (IS_CHAR_DEAD(ped11)) || (IS_CHAR_DEAD(ped12)) || (IS_CHAR_DEAD(ped13)) || (IS_CHAR_DEAD(ped14)) || (IS_CHAR_DEAD(ped15)) || (IS_CHAR_DEAD(ped16)) || (IS_CHAR_DEAD(ped17)) || (IS_CHAR_DEAD(ped18)) || (IS_CHAR_DEAD(ped19)) || (IS_CHAR_DEAD(ped20)) || (IS_CHAR_DEAD(ped21)) || (IS_CHAR_DEAD(ped22)))
					{
						hate = 1;
					}
					else if ((IS_CHAR_INJURED(ped1)) || (IS_CHAR_INJURED(ped2)) || (IS_CHAR_INJURED(ped3)) || (IS_CHAR_INJURED(ped4)) || (IS_CHAR_INJURED(ped5)) || (IS_CHAR_INJURED(ped6)) || (IS_CHAR_INJURED(ped7)) || (IS_CHAR_INJURED(ped8)) || (IS_CHAR_INJURED(ped9)) || (IS_CHAR_INJURED(ped10)) || (IS_CHAR_INJURED(ped11)) || (IS_CHAR_INJURED(ped12)) || (IS_CHAR_INJURED(ped13)) || (IS_CHAR_INJURED(ped14)) || (IS_CHAR_INJURED(ped15)) || (IS_CHAR_INJURED(ped16)) || (IS_CHAR_INJURED(ped17)) || (IS_CHAR_INJURED(ped18)) || (IS_CHAR_INJURED(ped19)) || (IS_CHAR_INJURED(ped20)) || (IS_CHAR_INJURED(ped21)) || (IS_CHAR_INJURED(ped22)))
					{
						hate = 1;
					}
					if (hate == 1)
					{
						ABORT_SCRIPTED_CONVERSATION( 0 );
						WAIT(50);

						//МЫ ПРИНИМАЕМ ВРАЖСКИЙ ОГОНЬ!
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R4_LA", "COL4_6", 0, 0);//WE'RE TAKING ENEMY FIRE!
						START_SCRIPT_CONVERSATION(1, 1);
						Speech = 4;
						play = 1;

						SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped3, 4);
						SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped7, 4);
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

						SET_CHAR_RELATIONSHIP(ped1, 5, 0);
						SET_CHAR_RELATIONSHIP(ped2, 5, 0);
						SET_CHAR_RELATIONSHIP(ped3, 4, 0);
						SET_CHAR_RELATIONSHIP(ped4, 5, 0);
						SET_CHAR_RELATIONSHIP(ped5, 5, 0);
						SET_CHAR_RELATIONSHIP(ped6, 5, 0);
						SET_CHAR_RELATIONSHIP(ped7, 4, 0);
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

						SET_SENSE_RANGE(ped1, 25.0);
						SET_SENSE_RANGE(ped2, 25.0);
						SET_SENSE_RANGE(ped3, 0.01);
						SET_SENSE_RANGE(ped4, 25.0);
						SET_SENSE_RANGE(ped5, 25.0);
						SET_SENSE_RANGE(ped6, 25.0);
						SET_SENSE_RANGE(ped7, 0.01);
						SET_SENSE_RANGE(ped8, 25.0);
						SET_SENSE_RANGE(ped9, 25.0);
						SET_SENSE_RANGE(ped10, 25.0);
						SET_SENSE_RANGE(ped11, 25.0);
						SET_SENSE_RANGE(ped12, 25.0);
						SET_SENSE_RANGE(ped13, 25.0);
						SET_SENSE_RANGE(ped14, 25.0);
						SET_SENSE_RANGE(ped15, 25.0);
						SET_SENSE_RANGE(ped16, 25.0);
						SET_SENSE_RANGE(ped17, 25.0);
						SET_SENSE_RANGE(ped18, 25.0);
						SET_SENSE_RANGE(ped19, 25.0);
						SET_SENSE_RANGE(ped20, 25.0);
						SET_SENSE_RANGE(ped21, 25.0);
						SET_SENSE_RANGE(ped22, 25.0);

						SET_CHAR_WILL_USE_COVER(ped1, 1);
						SET_CHAR_WILL_USE_COVER(ped2, 1);
						SET_CHAR_WILL_USE_COVER(ped4, 1);
						SET_CHAR_WILL_USE_COVER(ped5, 1);
						SET_CHAR_WILL_USE_COVER(ped6, 1);
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

						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped21, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped22, 1);

						// отклеиваем
						DETACH_PED(ped9, 1);
						DETACH_PED(ped10, 1);
						DETACH_PED(ped11, 1);
						DETACH_PED(ped12, 1);
						DETACH_PED(ped13, 1);
						DETACH_PED(ped14, 1);
						DETACH_PED(ped15, 1);
						DETACH_PED(ped16, 1);
						FREEZE_CHAR_POSITION(ped9, 0);
						FREEZE_CHAR_POSITION(ped10, 0);
						FREEZE_CHAR_POSITION(ped11, 0);
						FREEZE_CHAR_POSITION(ped12, 0);
						FREEZE_CHAR_POSITION(ped13, 0);
						FREEZE_CHAR_POSITION(ped14, 0);
						FREEZE_CHAR_POSITION(ped15, 0);
						FREEZE_CHAR_POSITION(ped16, 0);

						// педы выпрыгивают из грузовика тут

						TASK_COMBAT(ped1, GetPlayerPed());
						TASK_COMBAT(ped2, GetPlayerPed());
						TASK_COMBAT(ped4, GetPlayerPed());
						TASK_COMBAT(ped5, GetPlayerPed());
						TASK_COMBAT(ped6, GetPlayerPed());
						TASK_COMBAT(ped8, GetPlayerPed());
						TASK_COMBAT(ped9, GetPlayerPed());
						TASK_COMBAT(ped10, GetPlayerPed());
						TASK_COMBAT(ped11, GetPlayerPed());
						TASK_COMBAT(ped12, GetPlayerPed());
						TASK_COMBAT(ped13, GetPlayerPed());
						TASK_COMBAT(ped14, GetPlayerPed());
						TASK_COMBAT(ped15, GetPlayerPed());
						TASK_COMBAT(ped16, GetPlayerPed());
						TASK_COMBAT(ped17, GetPlayerPed());
						TASK_COMBAT(ped18, GetPlayerPed());
						TASK_COMBAT(ped19, GetPlayerPed());
						TASK_COMBAT(ped20, GetPlayerPed());
						TASK_COMBAT(ped21, GetPlayerPed());
						TASK_COMBAT(ped22, GetPlayerPed());

						if (point > 1)
						{
							SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
							
							SET_CHAR_RELATIONSHIP(ped3, 5, 0);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);

							SET_SENSE_RANGE(ped3, 25.0);
							SET_SENSE_RANGE(ped7, 25.0);

							SET_CHAR_WILL_USE_COVER(ped3, 1);
							SET_CHAR_WILL_USE_COVER(ped7, 1);

							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, 1);
						}
						WAIT(50);
						SETTIMERA(0); //сбрасываем таймер 
						SETTIMERB(0); //сбрасываем таймер
						SET_CAR_DENSITY_MULTIPLIER(1);// включаем пути
						hate = 2;
						break;
					}
					//----------------------------------------------


					// педы бегут
					GET_CHAR_COORDINATES(ped3,  &PedX2, &PedY2, &PedZ2);//вписываем координаты игрока в переменную
					GET_CHAR_HEADING(ped3, &PedR2); //получаем угол поворота игрока

					convoy_x2 = (3*COS((0-PedR2))+(3.5*SIN((0-PedR2))))+PedX2;
					convoy_y2 = (3.5*COS((0-PedR2))-(3*SIN((0-PedR2))))+PedY2;
					TASK_GO_STRAIGHT_TO_COORD(ped17, convoy_x2, convoy_y2, PedZ2, 3, -2);

					convoy_x2 = (3*COS((0-PedR2))+(-1*SIN((0-PedR2))))+PedX2;
					convoy_y2 = (-1*COS((0-PedR2))-(3*SIN((0-PedR2))))+PedY2;
					TASK_GO_STRAIGHT_TO_COORD(ped18, convoy_x2, convoy_y2, PedZ2, 3, -2);

					convoy_x2 = (3*COS((0-PedR2))+(-3.5*SIN((0-PedR2))))+PedX2;
					convoy_y2 = (-3.5*COS((0-PedR2))-(3*SIN((0-PedR2))))+PedY2;
					TASK_GO_STRAIGHT_TO_COORD(ped19, convoy_x2, convoy_y2, PedZ2, 3, -2);

					convoy_x2 = (-3*COS((0-PedR2))+(3*SIN((0-PedR2))))+PedX2;
					convoy_y2 = (3*COS((0-PedR2))-(-3*SIN((0-PedR2))))+PedY2;
					TASK_GO_STRAIGHT_TO_COORD(ped20, convoy_x2, convoy_y2, PedZ2, 3, -2);

					convoy_x2 = (-3*COS((0-PedR2))+(0*SIN((0-PedR2))))+PedX2;
					convoy_y2 = (0*COS((0-PedR2))-(-3*SIN((0-PedR2))))+PedY2;
					TASK_GO_STRAIGHT_TO_COORD(ped21, convoy_x2, convoy_y2, PedZ2, 3, -2);

					convoy_x2 = (-3*COS((0-PedR2))+(-3*SIN((0-PedR2))))+PedX2;
					convoy_y2 = (-3*COS((0-PedR2))-(-3*SIN((0-PedR2))))+PedY2;
					TASK_GO_STRAIGHT_TO_COORD(ped22, convoy_x2, convoy_y2, PedZ2, 3, -2);
					//----------------------------------------------

					// отключаем трафик
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -288.417, -983.924, -10.0, -484.687, 516.076, 60.0, 0 )) && ( in_zon == 0))
					{
						in_zon = 1;
						SET_CAR_DENSITY_MULTIPLIER(0);// отключаем пути
					}
					else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -288.417, -983.924, -10.0, -484.687, 516.076, 60.0, 0 )) && ( in_zon == 1))
					{
						in_zon = 0;
						SET_CAR_DENSITY_MULTIPLIER(1);// включаем пути
					}
					//----------------------------------------------

					// провал миссии
					GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -384.239, -935.276, 5.978, &PedR);//проверка "игрок на координатах"
					if ( PedR < 2.5 )
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COL4_B2", 5000, 1);//~r~The tank arrived at its destination safely!
						skip = 1;// переменная пропуска
						break;
					}
					else if (IS_CAR_DEAD(car3))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COL4_B5", 5000, 1);//~r~The tank has been destroyed!
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					//----------------------------------------------
				}

				if ((skip == 0) && (point == 1))
				{
					while (true)
					{
						WAIT( 0 );
						if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped3)) || (!IS_CHAR_SITTING_IN_ANY_CAR(ped7)) || (TIMERA() > 10000))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOL4_T", 5000, 1);//~g~Get in the tank.
							LOCK_CAR_DOORS(car3, 1); // отпираем автомобиль
							SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
							
							SET_CHAR_RELATIONSHIP(ped3, 5, 0);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);

							SET_SENSE_RANGE(ped3, 25.0);
							SET_SENSE_RANGE(ped7, 25.0);

							SET_CHAR_WILL_USE_COVER(ped3, 1);
							SET_CHAR_WILL_USE_COVER(ped7, 1);

							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, 1);
							SETTIMERB(0); //сбрасываем таймер
							SETTIMERA(0); //сбрасываем таймер
							break;
						}

						// аудио стоп
						if (play == 1)
						{
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								if (Speech == 4)
								{
									//ОБОРОНИТЕЛЬНЫЕ ПОЗИЦИИ!"
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R4_MA", "COL4_9", 0, 0);//DEFENSIVE POSITIONS!
									START_SCRIPT_CONVERSATION(1, 1);
									SETTIMERA(0); //сбрасываем таймер
									Speech = 0;
								}
							}
							if ( TIMERA() > 5000 )
							{
								play = 0;
							}
						}

						// провал миссии
						if (IS_CAR_DEAD(car3))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL4_B5", 5000, 1);//~r~The tank has been destroyed!
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

				if (skip == 0)
				{
					while (true)
					{
						WAIT( 0 );

						// аудио стоп
						if (play == 1)
						{
							if ( TIMERA() > 5000 )
							{
								WAIT(10);
								play = 0;
							}
						}

						if (IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), car3))
						{
							if (car_blip == 0)
							{
								REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_COORD(-613.883, 55.733, 4.186, &cortez_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
								CHANGE_BLIP_COLOUR(cortez_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(cortez_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "NE_POINT");//иконка на радаре называние в истории карты ""
								car_blip = 1;
							}
							if (car_blip == 1)
							{
								DRAW_CHECKPOINT( -613.883, 55.733, 4.186, 4.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							}

							if ((delta == 0) && (play == 0))
							{
								WAIT(50);
								ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
								APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());

								//протокол альфа дельта запущен бла-бла-бла
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_MB", "COL4_24", 0, 0);//Security protocol Delta India Echo triggered! Vehicle self destruct initiated!
								START_SCRIPT_CONVERSATION(1, 1);

								SETTIMERA(0); //сбрасываем таймер
								SETTIMERB(0); //сбрасываем таймер
								play = 1;
								delta = 1;
							}

							if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -600.939, 30.766, 4.186, -645.592, 78.711, 15.632, 0 )) && (garage == 0))
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "COL4_B7", 5000, 1);//~g~Drive the tank into the garage.
								OPEN_GARAGE("tank_g");
								garage = 1;
							}
							else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -600.939, 30.766, 4.186, -645.592, 78.711, 15.632, 0 )) && (garage == 1))
							{
								CLOSE_GARAGE("tank_g");
								garage = 0;
							}
						}
						else
						{
							if (car_blip == 1)
							{
								REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CAR(car3, &cortez_ico);
								CHANGE_BLIP_SPRITE(cortez_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
								CHANGE_BLIP_COLOUR(cortez_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(cortez_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "MO_TARGET");//иконка на радаре называние в истории карты "магазин одежды"
								
								if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -603.975, 49.006, 4.186, -623.065, 62.218, 10.299, 0 ))
								{
									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "NECOL4_T2", 5000, 1);//~g~Get back in the tank!
								}
								car_blip = 0;
							}
						}
						
						if (IS_CAR_IN_AREA_3D(car3, -603.975, 49.006, 4.186, -620.684, 62.218, 10.299, 0))
						{
							if ( in_garage == 0 )
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "COL4_B8", 5000, 1);//~g~Get out of the tank and walk out of the garage.
								in_garage = 1;
							}
								if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -626.496, 46.79855, 4.966417, -603.6121, 65.062, 10.26642, 0 ))
							{
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
								//SetTime(1000);
								CLOSE_GARAGE("tank_g");
								SetTime(2000);
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
								skip = 2;// переменная пропуска
								break;
							}
						}
						else if ((!IS_CAR_IN_AREA_3D(car3, -603.975, 49.006, 4.186, -620.684, 62.218, 10.299, 0)) && ( in_garage == 1))
						{
							in_garage = 0;
						}
						

						// протокол Альфа-Дельта
						if (delta == 1)
						{
							if ((TIMERB() > 5000) && (hud_on == 0))
							{
								SETTIMERB(0); //сбрасываем таймер
								hud_on = 1;
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "COL4_B3", 5000, 1);//~g~Drop the tank off in the Colonels lockup before it self destructs.
							}
							if (hud_on == 1)
							{
								if (TIMERB() > 100)
								{
									boom += 1;
									SETTIMERB(0); //сбрасываем таймер
								}
								// ----------------- HUD -----------------
								//DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", boom);// секунды

								SET_TEXT_COLOUR(95, 195, 247, 255);
								SET_TEXT_SCALE(0.156, 0.267);
								SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
								DISPLAY_TEXT(0.78815097, 0.80277778, "RBM3_6"); //DETONATION:

								DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
								DRAW_SPRITE( 0, 0.9088541, 0.80925926, 0.0739583, 0.014, 0.0, 27, 89, 130, 255 );// рисуем фоновую текстуру.

								DiazH1 = boom;
								DiazH2 = pedHUD_w/1000;
								DiazH3 = DiazH2*DiazH1;
								DiazHUD_y1 = pedHUD_w-DiazH3;
								DiazHUD_y2 = DiazHUD_y1/2;
								DiazHUD_y3 = pedHUD_x-DiazHUD_y2;
								DRAW_SPRITE( 0, DiazHUD_y3, 0.80925926, DiazH3, 0.014, 0.0, 97, 194, 247, 255 );// рисуем фоновую текстуру.

							}
						}

						// провал миссии
						if (boom > 1000)
						{
							EXPLODE_CAR(car3, 1, 1);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL4_B5", 5000, 1);//~r~The tank has been destroyed!
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CAR_DEAD(car3))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL4_B5", 5000, 1);//~r~The tank has been destroyed!
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

				ABORT_SCRIPTED_CONVERSATION( 0 );

				REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
				SET_CAR_DENSITY_MULTIPLIER(1);// включаем пути

				RELEASE_TEXTURE( fon );
				REMOVE_TXD( textur );

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель машины

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
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped21);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped22);//выгружаем модель педа(в последствии пед изчезнет

				// выгружаем из памяти транспорт
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_COL_4" );//Sir, Yes Sir!
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(2000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +2000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 2000);
					G_CORTEZ = 6;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== All Hands On Deck! ======================================
		else if ((G_ONMISSION == 0) && (G_CORTEZ == 7))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(189.427, -827.564, 2.028, &cortez_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cortez_ico, BLIP_GAMBETTI);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(cortez_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cortez_ico, "LG_04");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 189.427, -827.564, 2.028, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 189.427, -827.564, 2.028, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("COL_5", 15000, CUTSCENE_GENERAL);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-163.0, -1439.4, 9.0, 201.5);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				SET_MAX_WANTED_LEVEL(0);
				REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
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

				Car car1, car2, car3, car4, car5, car6, car7, car8, car9, car10, car11, car12, car13;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20, ped21, ped22, ped23, ped24, ped25;
				Pickup sweap_1, aid_1;
				Cam camera;

				uint PedM1 = MODEL_IG_FAUSTIN;// Кортес
				uint PedM2 = MODEL_IG_FRENCH_TOM;// Матрос
				uint PedM3 = MODEL_M_M_LAWYER_02;// Француз в костюме

				uint CarM1 = MODEL_TUGA;// Яхта Котеса
				uint CarM2 = MODEL_WASHINGTON;// Машина (Washington)
				uint CarM3 = MODEL_DINGHY;// катер (Speedre)
				uint CarM4 = MODEL_TROPIC;// яхта (Tripic)
				uint CarM5 = MODEL_MARQUIS;// яхта (Marquis)
				uint CarM6 = MODEL_REEFER;// катер (Reefer)
				uint CarM7 = MODEL_MAVERICK;// вертолёт (Maverick)
				uint CarM8 = MODEL_BUZZARD;// вертолёт (Hunter)
				uint Cortes_hp, car_hp1, car_hp2, car_hp3;
				speed = 0;
				speed2 = 0;
				speed3 = 0;
				speed4 = 0;
				play = 0;

				// грузим модели
				REQUEST_MODEL(PedM1);// 
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// 
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// 
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM1);// 
				while (!HAS_MODEL_LOADED(CarM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM2);// 
				while (!HAS_MODEL_LOADED(CarM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM3);// 
				while (!HAS_MODEL_LOADED(CarM3));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM4);// 
				while (!HAS_MODEL_LOADED(CarM4));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM5);// 
				while (!HAS_MODEL_LOADED(CarM5));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM6);// 
				while (!HAS_MODEL_LOADED(CarM6));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM7);// 
				while (!HAS_MODEL_LOADED(CarM7));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(CarM8);// 
				while (!HAS_MODEL_LOADED(CarM8));////проверка "пед загрузился" если нет то начанаем с начало

				// Грузим пути тут
				REQUEST_CAR_RECORDING( 3010 );// Машина (Washington)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3010 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3011 );// Машина (Washington)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3011 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3012 );// Яхта Котеса
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3012 )) WAIT(0);

				REQUEST_CAR_RECORDING( 3014 );// вертолёт (Maverick)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3014 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3015 );// вертолёт (Maverick)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3015 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3016 );// вертолёт (Hunter)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3016 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3017 );// вертолёт (Hunter)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3017 )) WAIT(0);

				FORCE_WEATHER_NOW(WEATHER_SUNNY);
				RELEASE_WEATHER();
				FORWARD_TO_TIME_OF_DAY(6, 0);//устанавливаем время

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "COL_5A", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("col_5a");
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
				G_CORTEZ = 99;

				CREATE_CAR(CarM1, 54.0, -789.9, -3.0, &car1, TRUE);// Яхта Котеса
				TURN_OFF_VEHICLE_EXTRA(car1, 1, 0);
				CREATE_CAR(CarM2, 247.149, -907.476, 3.468, &car2, TRUE);// Машина (Washington)
				CHANGE_CAR_COLOUR( car2, 0, 0 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car2, 0, 0 );//цвет отрожений машины
				CREATE_CAR(CarM2, 251.749, -906.255, 4.103, &car3, TRUE);// Машина (Washington)
				CHANGE_CAR_COLOUR( car3, 0, 0 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car3, 0, 0 );//цвет отрожений машины
				CREATE_CAR(CarM3, 100.991, -690.089, 1.587, &car4, TRUE);// катер (Speedre)
				SET_CAR_HEADING(car4, 90.0);
				CREATE_CAR(CarM4, 101.697, -699.992, 1.587, &car5, TRUE);// яхта (Tripic)
				SET_CAR_HEADING(car5, 90.0);
				CREATE_CAR(CarM5, 104.164, -674.854, 1.587, &car6, TRUE);// яхта (Marquis)
				SET_CAR_HEADING(car6, 90.0);
				CREATE_CAR(CarM6, 120.866, -674.887, 1.587, &car7, TRUE);// катер (Reefer)
				SET_CAR_HEADING(car7, 90.0);
				CREATE_CAR(CarM5, 624.929, 1483.241, 1.587, &car8, TRUE);// яхта (Marquis)
				SET_CAR_HEADING(car8, 75.0);
				CREATE_CAR(CarM4, 647.332, 1474.099, 1.587, &car9, TRUE);// яхта (Tripic)
				SET_CAR_HEADING(car9, 75.0);
				CREATE_CAR(CarM7, 742.157, 1642.026, 11.823, &car10, TRUE);// вертолёт (Maverick)
				SET_CAR_HEADING(car10, 90.0);
				CREATE_CAR(CarM7, 742.157, 1664.559, 12.523, &car11, TRUE);// вертолёт (Maverick)
				SET_CAR_HEADING(car11, 90.0);
				CREATE_CAR(CarM8, 757.386, 1653.161, 12.323, &car12, TRUE);// вертолёт (Hunter)
				SET_CAR_HEADING(car12, 90.0);
				CREATE_CAR(CarM3, 120.173, -733.062, 1.587, &car13, TRUE);// катер (Speedre)
				SET_CAR_HEADING(car13, 180.0);
				CHANGE_CAR_COLOUR( car13, 30, 4 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car13, 0, 0 );//цвет отрожений машины

				// создаём педов
				CREATE_CHAR (26, PedM1, 41.17, -821.214, 2.606, &ped1, TRUE);// Кортес
				CREATE_CHAR (26, PedM2, 41.17, -819.721, 2.606, &ped2, TRUE);// Матрос
				CREATE_CHAR (26, PedM2, 41.17, -818.226, 2.606, &ped3, TRUE);// Матрос
				CREATE_CHAR (26, PedM2, 41.17, -816.733, 2.606, &ped4, TRUE);// Матрос
				CREATE_CHAR (26, PedM2, 41.17, -815.239, 2.606, &ped5, TRUE);// Матрос

				CREATE_CHAR (26, PedM3, 281.581, -792.161, 5.423, &ped19, TRUE);// Француз в костюме
				CREATE_CHAR (26, PedM3, 283.395, -792.161, 5.423, &ped20, TRUE);// Француз в костюме
				CREATE_CHAR (26, PedM3, 285.208, -792.161, 5.423, &ped21, TRUE);// Француз в костюме
				CREATE_CHAR (26, PedM3, 287.021, -792.161, 5.423, &ped22, TRUE);// Француз в костюме
				CREATE_CHAR (26, PedM3, 281.581, -790.448, 5.423, &ped23, TRUE);// Француз в костюме
				CREATE_CHAR (26, PedM3, 283.395, -790.448, 5.423, &ped24, TRUE);// Француз в костюме
				CREATE_CHAR (26, PedM3, 285.208, -790.448, 5.423, &ped25, TRUE);// Француз в костюме

				SET_CHAR_HEADING(ped19, 90.0);
				SET_CHAR_HEADING(ped20, 90.0);
				SET_CHAR_HEADING(ped21, 90.0);
				SET_CHAR_HEADING(ped22, 90.0);

				// создаём педов за рулёп
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM3, &ped6);// Француз в костюме
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM3, &ped7);// Француз в костюме
				CREATE_CHAR_INSIDE_CAR(car10, 1, PedM3, &ped14);// Француз в костюме
				CREATE_CHAR_INSIDE_CAR(car11, 1, PedM3, &ped15);// Француз в костюме
				CREATE_CHAR_INSIDE_CAR(car12, 1, PedM3, &ped16);// Француз в костюме

				// создаём педов пассажиров
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM3, 0, &ped8);// Француз в костюме
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM3, 1, &ped9);// Француз в костюме
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM3, 2, &ped10);// Француз в костюме

				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM3, 0, &ped11);// Француз в костюме
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM3, 1, &ped12);// Француз в костюме
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM3, 2, &ped13);// Француз в костюме
				CREATE_CHAR_AS_PASSENGER(car10, 1, PedM3, 2, &ped17);// Француз в костюме
				CREATE_CHAR_AS_PASSENGER(car11, 1, PedM3, 1, &ped18);// Француз в костюме

				//таччим педов к машине
				ATTACH_PED_TO_CAR( GetPlayerPed(), car1, 0, 0.141, -16.323, 8.131, 0.0, 0, 1, 1 );
				ATTACH_PED_TO_CAR( ped1, car1, 0, -2.948, -2.538, 8.131, 0.0, 0, 1, 1 );
				ATTACH_PED_TO_CAR( ped2, car1, 0, -4.221, -5.591, 8.131, 3.0, 90, 1, 1 );
				ATTACH_PED_TO_CAR( ped3, car1, 0, 4.2311, -5.591, 8.131, 3.0, 90, 1, 1 );
				ATTACH_PED_TO_CAR( ped4, car1, 0, -4.231, -13.185, 8.131, 0.0, 0, 1, 0 );
				ATTACH_PED_TO_CAR( ped5, car1, 0, 4.2311, -13.185, 8.131, 0.0, 270, 0, 1 );

				FREEZE_CHAR_POSITION(GetPlayerPed(), 1);
				FREEZE_CHAR_POSITION(ped1, 1);
				FREEZE_CHAR_POSITION(ped2, 1);
				FREEZE_CHAR_POSITION(ped3, 1);
				FREEZE_CHAR_POSITION(ped4, 1);
				FREEZE_CHAR_POSITION(ped5, 1);

				SET_CAR_DENSITY_MULTIPLIER(0);// выключаем пути

				// старт путей
				START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3012, 0.0, 0.0, 0.0);// Яхта Котеса
				START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 3010, 0.0, 0.0, 0.0);// Машина (Washington)
				START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 3011, 0.0, 0.0, 0.0);// Машина (Washington)
				PAUSE_PLAYBACK_RECORDED_CAR(car2);
				PAUSE_PLAYBACK_RECORDED_CAR(car3);

				// ставим камеру
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, 53.217, -783.811, 9.597); // куда смотрит камера
				SET_CAM_POS			( camera, 33.126, -743.569, 4.93 );//расположение камеры
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_CAM_FOV( camera, 45.0 );
				SET_WIDESCREEN_BORDERS( 1 );
				DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
				SetTime(5000);
				UNPAUSE_PLAYBACK_RECORDED_CAR(car2);
				UNPAUSE_PLAYBACK_RECORDED_CAR(car3);

				// меняем ракурс
				POINT_CAM_AT_COORD	( camera, 53.588, -742.778, 7.715); // куда смотрит камера
				SET_CAM_POS			( camera, 42.605, -849.751, 8.827 );//расположение камеры
				SetTime(5500);

				// меняем ракурс
				POINT_CAM_AT_COORD	( camera, 188.281, -748.055, 2.386); // куда смотрит камера
				SET_CAM_POS			( camera, 185.821, -658.835, 6.594 );//расположение камеры
				SetTime(5500);

				STOP_PLAYBACK_RECORDED_CAR(car2);
				STOP_PLAYBACK_RECORDED_CAR(car3);
				REMOVE_CAR_RECORDING( 3010 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3011 ); // выгружаем пути транспорта

				// меняем ракурс
				POINT_CAM_AT_COORD	( camera, 176.847, -678.321, 4.518); // куда смотрит камера
				SET_CAM_POS			( camera, 198.709, -688.142, 4.591 );//расположение камеры

				// педы бегут к яхтам
				TASK_GO_STRAIGHT_TO_COORD(ped6, 103.184, -679.364, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped7, 120.505, -679.278, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped8, 109.659, -682.302, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped9, 109.659, -681.011, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped10, 103.184, -679.364, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped11, 120.505, -679.278, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped12, 109.659, -682.302, 2.606, 3, -2);
				TASK_GO_STRAIGHT_TO_COORD(ped13, 109.659, -681.011, 2.606, 3, -2);
				SetTime(3000);
				
				// меняем ракурс
				POINT_CAM_AT_COORD	( camera, 90.848, -683.712, 7.504); // куда смотрит камера
				SET_CAM_POS			( camera, 158.721, -686.547, 3.787 );//расположение камеры

				// телепортируем педов тут
				SET_CHAR_COORDINATES(ped6, 159.45, -679.962, 2.171);// перемещаем игрока
				SET_CHAR_COORDINATES(ped7, 159.45, -681.38, 2.171);// перемещаем игрока
				SET_CHAR_COORDINATES(ped8, 159.45, -682.799, 2.171);// перемещаем игрока
				SET_CHAR_COORDINATES(ped9, 158.632, -680.674, 2.171);// перемещаем игрока
				SET_CHAR_COORDINATES(ped10, 158.632, -682.194, 2.171);// перемещаем игрока
				SET_CHAR_COORDINATES(ped11, 157.634, -679.833, 2.171);// перемещаем игрока
				SET_CHAR_COORDINATES(ped12, 157.634, -681.337, 2.171);// перемещаем игрока
				SET_CHAR_COORDINATES(ped13, 157.634, -682.841, 2.171);// перемещаем игрока
				SetTime(3000);

				// меняем ракурс
				POINT_CAM_AT_COORD	( camera, 116.05, -681.641, 0.167); // куда смотрит камера
				SET_CAM_POS			( camera, 67.945, -716.863, 24.279 );//расположение камеры
				SetTime(3500);

				DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}

				// рассаживаем педов по катерам тут
				WARP_CHAR_INTO_CAR(ped6, car4);
				WARP_CHAR_INTO_CAR(ped7, car5);
				WARP_CHAR_INTO_CAR(ped8, car6);
				WARP_CHAR_INTO_CAR(ped9, car7);
				
				SET_CHAR_COORDINATES(ped10, 103.184, -679.364, 2.606);// перемещаем игрока
				SET_CHAR_COORDINATES(ped11, 120.505, -679.278, 2.606);// перемещаем игрока
				SET_CHAR_COORDINATES(ped12, 109.659, -682.302, 2.606);// перемещаем игрока
				SET_CHAR_COORDINATES(ped13, 109.659, -681.011, 2.606);// перемещаем игрока
				SetTime(250);

				ATTACH_PED_TO_CAR( ped10, car4, 0, -0.157, -0.359, 1.052, 0.0, 0, 1, 1 );// катер (Speedre)
				ATTACH_PED_TO_CAR( ped11, car5, 0, -0.245, 7.989, 2.339, 3.0, 90, 1, 1 );// яхта (Tripic)
				ATTACH_PED_TO_CAR( ped12, car6, 0, -0.184, 6.023, 1.815, 3.0, 90, 1, 0 );// яхта (Marquis)
				ATTACH_PED_TO_CAR( ped13, car7, 0, 1.0, 3.0, 1.816, 0.0, 270, 0, 1 );// катер (Reefer)

				FREEZE_CHAR_POSITION(ped10, 1);
				FREEZE_CHAR_POSITION(ped11, 1);
				FREEZE_CHAR_POSITION(ped12, 1);
				FREEZE_CHAR_POSITION(ped13, 1);

				// катера-яхты плывут тут
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped6, car4, -39.386, -484.829, 1.1, 4, 16.0, 1, 5, 10 );// катер (Speedre)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped7, car5, -20.679, -477.399, 1.1, 4, 16.0, 1, 5, 10 );// яхта (Tripic)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped8, car6, -32.641, -510.701, 1.1, 4, 16.0, 1, 5, 10 );// яхта (Marquis)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped9, car7, -13.131, -504.776, 1.1, 4, 16.0, 1, 5, 10 );// катер (Reefer)

				STOP_PLAYBACK_RECORDED_CAR(car1);
				REMOVE_CAR_RECORDING( 3012 ); // Яхта Котеса

				SET_CAR_COORDINATES(car1, -26.928, -491.821, -3.5);
				SET_CAR_HEADING(car1, 15.0);
				FREEZE_CAR_POSITION(car1, 1);

				//убираем камеру
				SetTime(250);
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				DESTROY_CAM( camera );
				SET_WIDESCREEN_BORDERS( 0 );
				DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

				//деттаччим педов от машины
				DETACH_PED(GetPlayerPed(), 1);
				DETACH_PED(ped1, 1);
				DETACH_PED(ped2, 1);
				DETACH_PED(ped3, 1);
				DETACH_PED(ped4, 1);
				DETACH_PED(ped5, 1);

				FREEZE_CHAR_POSITION(GetPlayerPed(), 0);
				FREEZE_CHAR_POSITION(ped1, 1);
				SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped1, TRUE);
				FREEZE_CHAR_POSITION(ped2, 0);
				FREEZE_CHAR_POSITION(ped3, 0);
				FREEZE_CHAR_POSITION(ped4, 0);
				FREEZE_CHAR_POSITION(ped5, 0);
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				// вооружаем педов
				UpdateWeaponOfPed(ped1, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped2, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped3, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped4, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped5, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped7, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_M4, TRUE);
				UpdateWeaponOfPed(ped8, WEAPON_M4);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped10, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped11, WEAPON_AK47);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_AK47, TRUE);
				UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_13);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_13, TRUE);
				UpdateWeaponOfPed(ped13, WEAPON_M4);
				SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_M4, TRUE);

				// лояльность к игроку
				SET_CHAR_HEALTH(ped1, 250);
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
				SET_CHAR_RELATIONSHIP(ped1, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 0);
				SET_CHAR_RELATIONSHIP(ped2, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 0);
				SET_CHAR_RELATIONSHIP(ped3, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped4, 0);
				SET_CHAR_RELATIONSHIP(ped4, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped5, 0);
				SET_CHAR_RELATIONSHIP(ped5, 5, 24);
				SET_CHAR_SHOOT_RATE(ped1, 15);
				SET_CHAR_SHOOT_RATE(ped2, 15);
				SET_CHAR_SHOOT_RATE(ped3, 15);
				SET_CHAR_SHOOT_RATE(ped4, 15);
				SET_CHAR_SHOOT_RATE(ped5, 15);

				// агрим тут
				SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);

				SET_CHAR_RELATIONSHIP(ped10, 5, 0);
				SET_CHAR_RELATIONSHIP(ped11, 5, 0);
				SET_CHAR_RELATIONSHIP(ped12, 5, 0);
				SET_CHAR_RELATIONSHIP(ped13, 5, 0);

				SET_SENSE_RANGE(ped10, 30.0);
				SET_SENSE_RANGE(ped11, 30.0);
				SET_SENSE_RANGE(ped12, 30.0);
				SET_SENSE_RANGE(ped13, 30.0);

				SET_CHAR_WILL_USE_COVER(ped10, 1);
				SET_CHAR_WILL_USE_COVER(ped11, 1);
				SET_CHAR_WILL_USE_COVER(ped12, 1);
				SET_CHAR_WILL_USE_COVER(ped13, 1);

				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);

				SET_CHAR_SHOOT_RATE(ped10, 35);
				SET_CHAR_SHOOT_RATE(ped11, 35);
				SET_CHAR_SHOOT_RATE(ped12, 35);
				SET_CHAR_SHOOT_RATE(ped13, 35);

				PRINT_STRING_IN_STRING("string", "COL5_B1", 5000, 1);//~g~Defend the Colonel and his yacht at all costs.

				SETTIMERB( 0 );
				SETTIMERC( 0 );
				SET_CHAR_HEALTH(ped1, 500);
				CREATE_PICKUP_ROTATE(w_ak47, 3, 90, -27.256, -496.16, 9.268, -75.0, -80.0, 0.0, &sweap_1);// даём винтовку
				CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -27.148, -495.558, 9.268, 0.0, 0.0, 105.0, &aid_1);//Аптека

				while(true)
				{
					WAIT(0);
					
					if (TIMERC() > 65000)
					{
						FIX_CAR(car1);//чиним машину
						REMOVE_PICKUP(sweap_1);
						REMOVE_PICKUP(aid_1);
						CREATE_PICKUP_ROTATE(w_ak47, 3, 90, -27.256, -496.16, 9.268, -75.0, -80.0, 0.0, &sweap_1);// даём винтовку
						CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -27.148, -495.558, 9.268, 0.0, 0.0, 105.0, &aid_1);//Аптека
						SETTIMERC( 0 );
					}
					if ((IS_CHAR_IN_AREA_3D( ped6, -35.386, -480.829, -1.1, -44.386, -488.829, 5.1, 0 )) && (speed == 0))// если игрок в зоне
					{
						// катер (Speedre)
						if (!IS_CHAR_DEAD(ped6))
						{
							WARP_CHAR_FROM_CAR_TO_COORD(ped6, -34.576, -484.78, 3.604);// высаживаем игрока
							SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
							SET_CHAR_RELATIONSHIP(ped6, 5, 0);
							SET_SENSE_RANGE(ped6, 30.0);
							SET_CHAR_WILL_USE_COVER(ped6, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
							SET_CHAR_SHOOT_RATE(ped6, 45);
						}
						if (!IS_CHAR_DEAD(ped10))
						{
							DETACH_PED(ped10, 1);
							FREEZE_CHAR_POSITION(ped10, 0);
							SET_CHAR_COORDINATES(ped10, -34.277, -485.926, 3.604);// перемещаем игрока
						}
						if (!IS_SCRIPTED_CONVERSATION_ONGOING())
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_NA", "COL5_1", 0, 0);//Port side! Port side!
							START_SCRIPT_CONVERSATION(1, 1);
						}
						speed = 1;
					}
					if ((IS_CHAR_IN_AREA_3D( ped7, -16.679, -473.399, -1.1, -24.679, -481.399, 5.1, 0 )) && (speed2 == 0))// если игрок в зоне
					{
						// яхта (Tripic)
						if (!IS_CHAR_DEAD(ped7))
						{
							WARP_CHAR_FROM_CAR_TO_COORD(ped7, -25.713, -476.612, 3.604);// высаживаем игрока
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);
							SET_SENSE_RANGE(ped7, 30.0);
							SET_CHAR_WILL_USE_COVER(ped7, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
							SET_CHAR_SHOOT_RATE(ped7, 45);
						}
						if (!IS_CHAR_DEAD(ped11))
						{
							DETACH_PED(ped11, 1);
							FREEZE_CHAR_POSITION(ped11, 0);
							SET_CHAR_COORDINATES(ped11, -25.414, -477.758, 3.604);// перемещаем игрока
						}
						if (!IS_SCRIPTED_CONVERSATION_ONGOING())
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_OA", "COL5_2", 0, 0);//They're attacking from starboard!
							START_SCRIPT_CONVERSATION(1, 1);
						}
						speed2 = 1;
					}
					if ((IS_CHAR_IN_AREA_3D( ped8, -28.641, -506.701, -1.1, -36.641, -514.701, 5.1, 0 )) && (speed3 == 0))// если игрок в зоне
					{
						// яхта (Marquis)
						if (!IS_CHAR_DEAD(ped8))
						{
							WARP_CHAR_FROM_CAR_TO_COORD(ped8, -29.969, -499.865, 3.604);// высаживаем игрока
							SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
							SET_CHAR_RELATIONSHIP(ped8, 5, 0);
							SET_SENSE_RANGE(ped8, 30.0);
							SET_CHAR_WILL_USE_COVER(ped8, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, FALSE);
							SET_CHAR_SHOOT_RATE(ped8, 45);
						}
						if (!IS_CHAR_DEAD(ped12))
						{
							DETACH_PED(ped12, 1);
							FREEZE_CHAR_POSITION(ped12, 0);
							SET_CHAR_COORDINATES(ped12, -30.267, -498.719, 3.604);// перемещаем игрока
						}
						if (!IS_SCRIPTED_CONVERSATION_ONGOING())
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_NA", "COL5_1", 0, 0);//Port side! Port side!
							START_SCRIPT_CONVERSATION(1, 1);
						}
						speed3 = 1;
					}
					if ((IS_CHAR_IN_AREA_3D( ped9, -9.131, -500.776, -1.1, -17.131, -508.776, 5.1, 0 )) && (speed4 == 0))// если игрок в зоне
					{
						// катер (Reefer)
						if (!IS_CHAR_DEAD(ped9))
						{
							WARP_CHAR_FROM_CAR_TO_COORD(ped9, -19.498, -499.133, 3.604);// высаживаем игрока
							SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
							SET_CHAR_RELATIONSHIP(ped9, 5, 0);
							SET_SENSE_RANGE(ped9, 30.0);
							SET_CHAR_WILL_USE_COVER(ped9, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, FALSE);
							SET_CHAR_SHOOT_RATE(ped9, 45);
						}
						if (!IS_CHAR_DEAD(ped13))
						{
							DETACH_PED(ped13, 1);
							FREEZE_CHAR_POSITION(ped13, 0);
							SET_CHAR_COORDINATES(ped13, -19.797, -497.987, 3.604);// перемещаем игрока
						}
						if (!IS_SCRIPTED_CONVERSATION_ONGOING())
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_OA", "COL5_2", 0, 0);//They're attacking from starboard!
							START_SCRIPT_CONVERSATION(1, 1);
						}
						speed4 = 1;
					}
			
					if (((IS_CHAR_DEAD(ped6)) || (IS_CHAR_INJURED(ped6))) && ((IS_CHAR_DEAD(ped7)) || (IS_CHAR_INJURED(ped7))) && ((IS_CHAR_DEAD(ped8)) || (IS_CHAR_INJURED(ped8))) && ((IS_CHAR_DEAD(ped9)) || (IS_CHAR_INJURED(ped9))) && ((IS_CHAR_DEAD(ped10)) || (IS_CHAR_INJURED(ped10))) && ((IS_CHAR_DEAD(ped11)) || (IS_CHAR_INJURED(ped11))) && ((IS_CHAR_DEAD(ped12)) || (IS_CHAR_INJURED(ped12))) && ((IS_CHAR_DEAD(ped13)) || (IS_CHAR_INJURED(ped13))))
					{
						break;
					}

					if (TIMERB() > 120000)
					{
						EXPLODE_CHAR_HEAD(ped6);
						EXPLODE_CHAR_HEAD(ped7);
						EXPLODE_CHAR_HEAD(ped8);
						EXPLODE_CHAR_HEAD(ped9);
						EXPLODE_CHAR_HEAD(ped10);
						EXPLODE_CHAR_HEAD(ped11);
						EXPLODE_CHAR_HEAD(ped12);
						EXPLODE_CHAR_HEAD(ped13);
					}

					GET_CHAR_HEALTH(ped1, &Cortes_hp);
					if (IS_CHAR_DEAD(ped1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COL5_B3", 5000, 1);//~r~The Colonel is dead!
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if ((Cortes_hp < 50) || (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 3.072, -536.821, -5.0, -56.928, -446.821, 25.0, 0 )))// если игрок в зоне
					{
						EXPLODE_CHAR_HEAD(ped1);
					}
				}

				// вторая часть миссии 
				if (skip == 0)
				{
					// затемнение экрана
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
					REMOVE_PICKUP(sweap_1);
					REMOVE_PICKUP(aid_1);
					FIX_CAR(car1);//чиним машину

					// выгружаем из памяти педов
					DELETE_CHAR(&ped2);//удаляем модель педа
					DELETE_CHAR(&ped3);//удаляем модель педа
					DELETE_CHAR(&ped4);//удаляем модель педа
					DELETE_CHAR(&ped5);//удаляем модель педа
					DELETE_CHAR(&ped6);//удаляем модель педа
					DELETE_CHAR(&ped7);//удаляем модель педа
					DELETE_CHAR(&ped8);//удаляем модель педа
					DELETE_CHAR(&ped9);//удаляем модель педа
					DELETE_CHAR(&ped10);//удаляем модель педа
					DELETE_CHAR(&ped11);//удаляем модель педа
					DELETE_CHAR(&ped12);//удаляем модель педа
					DELETE_CHAR(&ped13);//удаляем модель педа
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//выгружаем модель педа(в последствии пед изчезнет
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped9);//выгружаем модель педа(в последствии пед изчезнет
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped10);//выгружаем модель педа(в последствии пед изчезнет
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped11);//выгружаем модель педа(в последствии пед изчезнет
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped12);//выгружаем модель педа(в последствии пед изчезнет
					//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped13);//выгружаем модель педа(в последствии пед изчезнет

					// выгружаем из памяти транспорт
					DELETE_CAR(&car2);//удаляем модель педа
					DELETE_CAR(&car3);//удаляем модель педа
					DELETE_CAR(&car4);//удаляем модель педа
					DELETE_CAR(&car5);//удаляем модель педа
					DELETE_CAR(&car6);//удаляем модель педа
					DELETE_CAR(&car7);//удаляем модель педа
					//MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
					//MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
					//MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
					//MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)
					//MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//выгружаем модель машины(в последствии машина изчезнет)
					//MARK_CAR_AS_NO_LONGER_NEEDED(&car7);//выгружаем модель машины(в последствии машина изчезнет)

					// создаём новых педов
					CREATE_CHAR (26, PedM2, 41.17, -819.721, 2.606, &ped2, TRUE);// Матрос
					CREATE_CHAR (26, PedM2, 41.17, -818.226, 2.606, &ped3, TRUE);// Матрос
					CREATE_CHAR (26, PedM2, 41.17, -816.733, 2.606, &ped4, TRUE);// Матрос
					CREATE_CHAR (26, PedM2, 41.17, -815.239, 2.606, &ped5, TRUE);// Матрос

					//таччим педов к машине
					ATTACH_PED_TO_CAR( GetPlayerPed(), car1, 0, 0.141, -16.323, 8.131, 0.0, 0, 1, 1 );
					ATTACH_PED_TO_CAR( ped1, car1, 0, -2.948, -2.538, 8.131, 0.0, 0, 1, 1 );
					ATTACH_PED_TO_CAR( ped2, car1, 0, -4.221, -5.591, 8.131, 3.0, 90, 1, 1 );
					ATTACH_PED_TO_CAR( ped3, car1, 0, 4.2311, -5.591, 8.131, 3.0, 90, 1, 1 );
					ATTACH_PED_TO_CAR( ped4, car1, 0, -4.231, -13.185, 8.131, 0.0, 0, 1, 0 );
					ATTACH_PED_TO_CAR( ped5, car1, 0, 4.2311, -13.185, 8.131, 0.0, 270, 0, 1 );

					FREEZE_CHAR_POSITION(GetPlayerPed(), 1);
					FREEZE_CHAR_POSITION(ped1, 1);
					FREEZE_CHAR_POSITION(ped2, 1);
					FREEZE_CHAR_POSITION(ped3, 1);
					FREEZE_CHAR_POSITION(ped4, 1);
					FREEZE_CHAR_POSITION(ped5, 1);

					// лояльность к игроку
					SET_CHAR_RELATIONSHIP_GROUP(ped2, 0);
					SET_CHAR_RELATIONSHIP(ped2, 5, 24);
					SET_CHAR_RELATIONSHIP_GROUP(ped3, 0);
					SET_CHAR_RELATIONSHIP(ped3, 5, 24);
					SET_CHAR_RELATIONSHIP_GROUP(ped4, 0);
					SET_CHAR_RELATIONSHIP(ped4, 5, 24);
					SET_CHAR_RELATIONSHIP_GROUP(ped5, 0);
					SET_CHAR_RELATIONSHIP(ped5, 5, 24);
					SET_CHAR_SHOOT_RATE(ped2, 15);
					SET_CHAR_SHOOT_RATE(ped3, 15);
					SET_CHAR_SHOOT_RATE(ped4, 15);
					SET_CHAR_SHOOT_RATE(ped5, 15);

					// запускаем пути приплытия
					REQUEST_CAR_RECORDING( 3013 );// Яхта Котеса
					while (!HAS_CAR_RECORDING_BEEN_LOADED( 3013 )) WAIT(0);
					START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3013, 0.0, 0.0, 0.0);// Яхта Котеса

					// создаём новый транспорт тут
					CREATE_CAR(CarM6, 606.748, 1489.45, 1.587, &car2, TRUE);// катер (Reefer)
					SET_CAR_HEADING(car2, -105.0);
					CREATE_CAR(CarM6, 663.787, 1467.786, 1.587, &car3, TRUE);// катер (Reefer)
					SET_CAR_HEADING(car3, 90.0);
					CREATE_CAR(CarM3, 591.783, 1491.737, 0.3, &car4, TRUE);// катер (Speedre)
					SET_CAR_HEADING(car4, -140.0);
					CREATE_CAR(CarM3, 681.423, 1463.657, 0.3, &car5, TRUE);// катер (Speedre)
					SET_CAR_HEADING(car5, 120.0);
					CREATE_CAR(CarM3, 486.127, 1336.15, 0.3, &car6, TRUE);// катер (Speedre)
					SET_CAR_HEADING(car6, -55.0);
					CREATE_CAR(CarM3, 575.811, 1287.265, 0.3, &car7, TRUE);// катер (Speedre)
					SET_CAR_HEADING(car7, -20.0);

					// создаём педов на катерах
					CREATE_CHAR_INSIDE_CAR(car4, 1, PedM3, &ped6);// Француз в костюме
					CREATE_CHAR_INSIDE_CAR(car5, 1, PedM3, &ped7);// Француз в костюме
					CREATE_CHAR_INSIDE_CAR(car6, 1, PedM3, &ped8);// Француз в костюме
					CREATE_CHAR_INSIDE_CAR(car7, 1, PedM3, &ped9);// Француз в костюме

					// создаём новых педов
					CREATE_CHAR (26, PedM3, 41.17, -819.721, 2.606, &ped10, TRUE);// Француз в костюме
					CREATE_CHAR (26, PedM3, 41.17, -818.226, 2.606, &ped11, TRUE);// Француз в костюме
					CREATE_CHAR (26, PedM3, 41.17, -816.733, 2.606, &ped12, TRUE);// Француз в костюме
					CREATE_CHAR (26, PedM3, 41.17, -815.239, 2.606, &ped13, TRUE);// Француз в костюме

					ATTACH_PED_TO_CAR( ped10, car4, 0, -0.157, -0.359, 1.052, 0.0, 0, 1, 1 );// катер (Speedre)
					ATTACH_PED_TO_CAR( ped11, car5, 0, -0.157, -0.359, 1.052, 0.0, 0, 1, 1 );// катер (Speedre)
					ATTACH_PED_TO_CAR( ped12, car6, 0, -0.157, -0.359, 1.052, 0.0, 0, 1, 1 );// катер (Speedre)
					ATTACH_PED_TO_CAR( ped13, car7, 0, -0.157, -0.359, 1.052, 0.0, 0, 1, 1 );// катер (Speedre)

					ATTACH_PED_TO_CAR( ped19, car8, 0, -0.184, 6.023, 1.815, 90.0, 90, 1, 1 );// яхта (Marquis)
					ATTACH_PED_TO_CAR( ped20, car8, 0, -1.719, -3.01, 1.613, 90.0, 90, 1, 1 );// яхта (Marquis)
					ATTACH_PED_TO_CAR( ped21, car9, 0, -1.879, 5.899, 2.097, 90.0, 90, 1, 1 );// яхта (Tripic)
					ATTACH_PED_TO_CAR( ped22, car9, 0, -2.41, -1.704, 1.961, 90.0, 90, 1, 1 );// яхта (Tripic)
					ATTACH_PED_TO_CAR( ped23, car3, 0, -1.221, 3.243, 1.816, 90.0, 90, 1, 1 );// катер (Reefer)
					ATTACH_PED_TO_CAR( ped24, car8, 0, -1.719, 1.059, 1.613, 90.0, 90, 1, 1 );// яхта (Marquis)
					ATTACH_PED_TO_CAR( ped25, car12, 0, 0.015, 2.933, -1.039, 0.0, 0, 1, 1 );// вертолёт (Hunter)

					FREEZE_CHAR_POSITION(ped10, 1);
					FREEZE_CHAR_POSITION(ped11, 1);
					FREEZE_CHAR_POSITION(ped12, 1);
					FREEZE_CHAR_POSITION(ped13, 1);

					DETACH_PED(ped19, 1);
					DETACH_PED(ped20, 1);
					DETACH_PED(ped21, 1);
					DETACH_PED(ped22, 1);
					DETACH_PED(ped23, 1);
					DETACH_PED(ped24, 1);

					FREEZE_CHAR_POSITION(ped25, 1);
					SET_CHAR_COLLISION(ped25, 0);
					SET_CHAR_INVINCIBLE(ped25, 1);
					SET_CHAR_VISIBLE(ped25, 0);

					// ставим камеру
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 605.018, 1379.022, 9.764); // куда смотрит камера
					SET_CAM_POS			( camera, 616.156, 1448.337, 5.113 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );
					DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
					SetTime(4000);

					// меняем ракурс
					POINT_CAM_AT_COORD	( camera, 631.069, 1443.263, 6.032); // куда смотрит камера
					SET_CAM_POS			( camera, 581.424, 1377.638, 15.011 );//расположение камеры
					SetTime(3000);

					DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
					while(true)
					{
						WAIT(0);
						if (IS_SCREEN_FADED_OUT())
						{
							break;
						}
					}
					
					// переносим карабль
					STOP_PLAYBACK_RECORDED_CAR(car1);
					REMOVE_CAR_RECORDING( 3013 ); // выгружаем пути транспорта
					SET_CAR_COORDINATES(car1, 617.177, 1418.828, -3.5);
					SET_CAR_HEADING(car1, -20.0);
					FREEZE_CAR_POSITION(car1, 1);

					//убираем камеру
					ACTIVATE_SCRIPTED_CAMS( 0, 0 );
					DESTROY_CAM( camera );
					SET_WIDESCREEN_BORDERS( 0 );
					
					//деттаччим педов от машины
					SetTime(250);
					DETACH_PED(GetPlayerPed(), 1);
					DETACH_PED(ped1, 1);
					DETACH_PED(ped2, 1);
					DETACH_PED(ped3, 1);
					DETACH_PED(ped4, 1);
					DETACH_PED(ped5, 1);

					FREEZE_CHAR_POSITION(GetPlayerPed(), 0);
					FREEZE_CHAR_POSITION(ped1, 1);
					SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped1, TRUE);
					FREEZE_CHAR_POSITION(ped2, 0);
					FREEZE_CHAR_POSITION(ped3, 0);
					FREEZE_CHAR_POSITION(ped4, 0);
					FREEZE_CHAR_POSITION(ped5, 0);

					// вооружаем педов
					UpdateWeaponOfPed(ped2, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped3, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped4, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped5, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_13);
					SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_13, TRUE);
					UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_12);
					SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_12, TRUE);
					UpdateWeaponOfPed(ped8, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped9, WEAPON_PISTOL);
					SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_PISTOL, TRUE);
					UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_12);
					SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_12, TRUE);
					UpdateWeaponOfPed(ped11, WEAPON_PISTOL);
					SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_PISTOL, TRUE);
					UpdateWeaponOfPed(ped12, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_12, TRUE);
					UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_12);
					SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_EPISODIC_12, TRUE);
					UpdateWeaponOfPed(ped17, WEAPON_M4);
					SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_M4, TRUE);
					UpdateWeaponOfPed(ped18, WEAPON_M4);
					SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_M4, TRUE);
					UpdateWeaponOfPed(ped19, WEAPON_EPISODIC_13);
					SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_EPISODIC_13, TRUE);
					UpdateWeaponOfPed(ped20, WEAPON_EPISODIC_13);
					SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_EPISODIC_13, TRUE);
					UpdateWeaponOfPed(ped21, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped21, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped22, WEAPON_EPISODIC_13);
					SET_CURRENT_CHAR_WEAPON(ped22, WEAPON_EPISODIC_13, TRUE);
					UpdateWeaponOfPed(ped23, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped23, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped24, WEAPON_AK47);
					SET_CURRENT_CHAR_WEAPON(ped24, WEAPON_AK47, TRUE);
					UpdateWeaponOfPed(ped25, WEAPON_M4);
					SET_CURRENT_CHAR_WEAPON(ped25, WEAPON_M4, TRUE);

					CREATE_PICKUP_ROTATE(w_ak47, 3, 90, 614.419, 1415.461, 9.268, -75.0, -80.0, -35.0, &sweap_1);// даём винтовку
					CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 614.852, 1415.893, 9.268, 0.0, 0.0, 70.0, &aid_1);//Аптека
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

					// агрим тут
					SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped17, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped18, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped19, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped20, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped21, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped22, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped23, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped24, 5);
					SET_CHAR_RELATIONSHIP_GROUP(ped25, 5);

					SET_CHAR_RELATIONSHIP(ped10, 5, 0);
					SET_CHAR_RELATIONSHIP(ped11, 5, 0);
					SET_CHAR_RELATIONSHIP(ped12, 5, 0);
					SET_CHAR_RELATIONSHIP(ped13, 5, 0);
					SET_CHAR_RELATIONSHIP(ped14, 5, 0);
					SET_CHAR_RELATIONSHIP(ped15, 5, 0);
					SET_CHAR_RELATIONSHIP(ped17, 5, 0);
					SET_CHAR_RELATIONSHIP(ped18, 5, 0);
					SET_CHAR_RELATIONSHIP(ped19, 5, 0);
					SET_CHAR_RELATIONSHIP(ped20, 5, 0);
					SET_CHAR_RELATIONSHIP(ped21, 5, 0);
					SET_CHAR_RELATIONSHIP(ped22, 5, 0);
					SET_CHAR_RELATIONSHIP(ped23, 5, 0);
					SET_CHAR_RELATIONSHIP(ped24, 5, 0);
					SET_CHAR_RELATIONSHIP(ped25, 5, 0);

					SET_SENSE_RANGE(ped10, 30.0);
					SET_SENSE_RANGE(ped11, 30.0);
					SET_SENSE_RANGE(ped12, 30.0);
					SET_SENSE_RANGE(ped13, 30.0);
					SET_SENSE_RANGE(ped14, 30.0);
					SET_SENSE_RANGE(ped15, 30.0);
					SET_SENSE_RANGE(ped17, 30.0);
					SET_SENSE_RANGE(ped18, 30.0);
					SET_SENSE_RANGE(ped19, 90.0);
					SET_SENSE_RANGE(ped20, 90.0);
					SET_SENSE_RANGE(ped21, 90.0);
					SET_SENSE_RANGE(ped22, 90.0);
					SET_SENSE_RANGE(ped23, 90.0);
					SET_SENSE_RANGE(ped24, 90.0);
					SET_SENSE_RANGE(ped25, 95.0);

					SET_CHAR_WILL_USE_COVER(ped10, 1);
					SET_CHAR_WILL_USE_COVER(ped11, 1);
					SET_CHAR_WILL_USE_COVER(ped12, 1);
					SET_CHAR_WILL_USE_COVER(ped13, 1);
					SET_CHAR_WILL_USE_COVER(ped14, 1);
					SET_CHAR_WILL_USE_COVER(ped15, 1);
					SET_CHAR_WILL_USE_COVER(ped17, 1);
					SET_CHAR_WILL_USE_COVER(ped18, 1);
					SET_CHAR_WILL_USE_COVER(ped19, 1);
					SET_CHAR_WILL_USE_COVER(ped20, 1);
					SET_CHAR_WILL_USE_COVER(ped21, 1);
					SET_CHAR_WILL_USE_COVER(ped22, 1);
					SET_CHAR_WILL_USE_COVER(ped23, 1);
					SET_CHAR_WILL_USE_COVER(ped24, 1);

					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, 1);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, 1);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, 1);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, 1);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped21, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped22, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped23, FALSE);
					SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped24, FALSE);

					SET_CHAR_SHOOT_RATE(ped10, 35);
					SET_CHAR_SHOOT_RATE(ped11, 35);
					SET_CHAR_SHOOT_RATE(ped12, 35);
					SET_CHAR_SHOOT_RATE(ped13, 35);
					SET_CHAR_SHOOT_RATE(ped17, 35);
					SET_CHAR_SHOOT_RATE(ped18, 35);
					SET_CHAR_SHOOT_RATE(ped19, 35);
					SET_CHAR_SHOOT_RATE(ped20, 35);
					SET_CHAR_SHOOT_RATE(ped21, 35);
					SET_CHAR_SHOOT_RATE(ped22, 35);
					SET_CHAR_SHOOT_RATE(ped23, 35);
					SET_CHAR_SHOOT_RATE(ped24, 35);

					SET_CHAR_HEALTH(ped1, 1000);
					SET_CHAR_HEALTH(ped14, 1000);
					SET_CHAR_HEALTH(ped15, 1000);
					SET_CHAR_HEALTH(ped16, 1500);
					SET_CHAR_HEALTH(ped17, 1500);
					SET_CHAR_HEALTH(ped18, 1500);

					SETTIMERB( 0 );
					SETTIMERC( 0 );
					gogogo = 0;
					speed = 0;
					speed2 = 0;
					speed3 = 0;
					speed4 = 0;
					in_zon = 0;
					in_car = 0;
					LanceH1 = 0;
					LanceH2 = 0;
					LanceH3 = 0;
					play = 0;
					explo_1 = 0;

					while(true)
					{
						WAIT(5);
						if (TIMERC() > 65000)
						{
							explo_1 += 1;
							FIX_CAR(car1);//чиним машину
							REMOVE_PICKUP(sweap_1);
							REMOVE_PICKUP(aid_1);
							CREATE_PICKUP_ROTATE(w_ak47, 3, 60, 614.419, 1415.461, 9.268, -75.0, -80.0, -35.0, &sweap_1);// даём винтовку
							CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 614.852, 1415.893, 9.268, 0.0, 0.0, 70.0, &aid_1);//Аптека
							SETTIMERC( 0 );
						}
						if (explo_1 == 1)
						{
							if (TIMERC() > 30000)
							{
								explo_1 = 2;
							}
						}

						if ((TIMERB() > 2000) && (gogogo == 0))
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_PA", "COL5_3", 0, 0);//The bridge up ahead!
							START_SCRIPT_CONVERSATION(1, 1);
							SETTIMERA( 1500 );
							play = 1;

							// катера-яхты плывут тут
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped6, car4, 610.982, 1431.7, 1.1, 4, 16.0, 1, 5, 10 );// катер (Speedre)
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped7, car5, 630.567, 1427.057, 1.1, 4, 16.0, 1, 5, 10 );// катер (Speedre)
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped8, car6, 601.667, 1406.639, 1.1, 4, 16.0, 1, 5, 10 );// катер (Speedre)
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped9, car7, 621.048, 1400.301, 1.1, 4, 16.0, 1, 5, 10 );// катер (Speedre)
							gogogo = 1;
							SETTIMERB( 0 );
						}

						// верталёты тут
						if ((TIMERB() > 35000) && (gogogo == 1))
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_TA", "COL5_17", 0, 0);//Oh my god they've got a helicopter!
							START_SCRIPT_CONVERSATION(1, 1);
							SETTIMERA( 0 );
							play = 1;

							// стартуем пути верталёта 1
							ADD_BLIP_FOR_CAR(car10, &vert_ico);
							CHANGE_BLIP_SPRITE(vert_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
							CHANGE_BLIP_COLOUR(vert_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(vert_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(vert_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""
						
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car10, 3014, 0.0, 0.0, 0.0);// верталёт 1
							WAIT(500);
							in_zon = 0;
							gogogo = 2;
							in_car = 1;
							SETTIMERB( 0 );
						}
						if ((TIMERB() > 5000) && (gogogo == 2))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL5_B5", 5000, 1);//~g~Shoot down the helicopters, do not endanger the yacht.
							gogogo = 3;
						}

						if (in_car == 1)
						{
							if ((IS_CHAR_IN_AREA_3D( ped14,  769.5, 1509.5, 1.5,  724.5, 1554.5, 21.5, 0 )) && (in_zon == 1))// если игрок в зоне
							{
								// обнуляем пути верталёта
								STOP_PLAYBACK_RECORDED_CAR(car10);
								REMOVE_CAR_RECORDING( 3014 ); // выгружаем пути транспорта
								REQUEST_CAR_RECORDING( 3014 );// вертолёт (Maverick)
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3014 )) WAIT(0);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car10, 3014, 0.0, 0.0, 0.0);// верталёт 1

								// обновляем пассажира
								//DELETE_CAR(&ped17);//удаляем модель педа
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped17);//выгружаем модель педа(в последствии пед изчезнет
								CREATE_CHAR_AS_PASSENGER(car10, 1, PedM3, 2, &ped17);// Француз в костюме Верталёт 1
								UpdateWeaponOfPed(ped17, WEAPON_M4);
								SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_M4, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped17, 5);
								SET_CHAR_RELATIONSHIP(ped17, 5, 0);
								SET_SENSE_RANGE(ped17, 30.0);
								SET_CHAR_WILL_USE_COVER(ped17, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, 1);
								SET_CHAR_SHOOT_RATE(ped17, 35);
								SET_CHAR_HEALTH(ped17, 1500);
								in_zon = 0;
							}
							else if ((!IS_CHAR_IN_AREA_3D( ped14,  769.5, 1509.5, 1.5,  724.5, 1554.5, 21.5, 0 )) && (in_zon == 0))// если игрок в зоне
							{
								in_zon = 1;
							}
						}
						else if (in_car == 2)
						{
							if ((IS_CHAR_IN_AREA_3D( ped15,  872.5, 1409.5, 1.2,  827.5, 1454.5, 21.2, 0 )) && (in_zon == 1))// если игрок в зоне
							{
								// обнуляем пути верталёта
								STOP_PLAYBACK_RECORDED_CAR(car11);
								REMOVE_CAR_RECORDING( 3015 ); // выгружаем пути транспорта
								REQUEST_CAR_RECORDING( 3015 );// вертолёт (Maverick)
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3015 )) WAIT(0);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car11, 3015, 0.0, 0.0, 0.0);// верталёт 2

								// обновляем пассажира
								//DELETE_CAR(&ped18);//удаляем модель педа
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped18);//выгружаем модель педа(в последствии пед изчезнет
								CREATE_CHAR_AS_PASSENGER(car11, 1, PedM3, 1, &ped18);// Француз в костюме Верталёт 2
								UpdateWeaponOfPed(ped18, WEAPON_M4);
								SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_M4, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped18, 5);
								SET_CHAR_RELATIONSHIP(ped18, 5, 0);
								SET_SENSE_RANGE(ped18, 30.0);
								SET_CHAR_WILL_USE_COVER(ped18, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, 1);
								SET_CHAR_SHOOT_RATE(ped18, 35);
								SET_CHAR_HEALTH(ped18, 1500);
								in_zon = 0;
							}
							else if ((!IS_CHAR_IN_AREA_3D( ped15,  872.5, 1409.5, 1.2,  827.5, 1454.5, 21.2, 0 )) && (in_zon == 0))// если игрок в зоне
							{
								in_zon = 1;
							}
						}
						else if (in_car == 3)
						{
							if ((IS_CHAR_IN_AREA_3D( ped16,  382.5, 1537.5, 2.0, 337.5, 1582.5, 22.0, 0 )) && (in_zon == 1))// если игрок в зоне
							{
								// обнуляем пути верталёта
								STOP_PLAYBACK_RECORDED_CAR(car12);
								REMOVE_CAR_RECORDING( 3016 ); // выгружаем пути транспорта
								REQUEST_CAR_RECORDING( 3016 );// вертолёт (Maverick)
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3016 )) WAIT(0);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car12, 3016, 0.0, 0.0, 0.0);// верталёт 3
								in_zon = 0;

								if (play == 0)
								{
									if (!IS_SCRIPTED_CONVERSATION_ONGOING())
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R4_SA", "COL5_20", 0, 0);//He's coming again! Blow that chopper!
										START_SCRIPT_CONVERSATION(1, 1);
									}
									SETTIMERA( 0 );
									play = 1;
								}	
							}
							else if ((!IS_CHAR_IN_AREA_3D( ped16,  382.5, 1537.5, 2.0, 337.5, 1582.5, 22.0, 0 )) && (in_zon == 0))// если игрок в зоне
							{
								in_zon = 1;
							}
						}

						if ( ((IS_CHAR_DEAD(ped14)) && (in_car == 1)) || ((IS_CAR_DEAD(car10)) && (in_car == 1)))
						{
							// стартуем пути верталёта 2
							REMOVE_BLIP(vert_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_CAR(car11, &vert_ico);
							CHANGE_BLIP_SPRITE(vert_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
							CHANGE_BLIP_COLOUR(vert_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(vert_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(vert_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

							STOP_PLAYBACK_RECORDED_CAR(car10);
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car11, 3015, 0.0, 0.0, 0.0);// верталёт 2
							WAIT(500);
							in_zon = 0;
							in_car = 2;
						}
						if ( ((IS_CHAR_DEAD(ped15)) && (in_car == 2)) || ((IS_CAR_DEAD(car11)) && (in_car == 2)))
						{
							// стартуем пути верталёта 3
							REMOVE_BLIP(vert_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_CAR(car12, &vert_ico);
							CHANGE_BLIP_SPRITE(vert_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
							CHANGE_BLIP_COLOUR(vert_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(vert_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(vert_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""
							STOP_PLAYBACK_RECORDED_CAR(car11);
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car12, 3017, 0.0, 0.0, 0.0);// верталёт 3

							// камера на вертолёт
							ABORT_SCRIPTED_CONVERSATION( 0 );
							DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
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
							POINT_CAM_AT_COORD	( camera, 456.011, 1262.081, 18.311); // куда смотрит камера
							SET_CAM_POS			( camera, 619.327, 1413.817, 14.956 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
							SetTime(4500);

							DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
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
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL5_B4", 5000, 1);//~g~Shoot the attacking helicopter out of the sky.
							WAIT(500);
							in_zon = 0;
							in_car = 3;

						}
						if ((IS_CAR_DEAD(car12)) && (in_car == 3))
						{
							REMOVE_BLIP(vert_ico);//Удаляем иконку на радаре
							STOP_PLAYBACK_RECORDED_CAR(car12);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL5_B2", 5000, 1);//~g~Get up front and clear the route for the Colonel's yacht.
							in_car = 4;
							WAIT( 25 );
						}

						// абордаж
						if ((IS_CHAR_IN_AREA_3D( ped6,  614.982, 1435.7, -1.1,  606.982, 1427.7, 5.1, 0 )) && (speed == 0))// если игрок в зоне
						{
							// катер (car4)
							if (!IS_CHAR_DEAD(ped6))
							{
								WARP_CHAR_FROM_CAR_TO_COORD(ped6, 614.951, 1428.982, 3.604);// высаживаем игрока
								SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
								SET_CHAR_RELATIONSHIP(ped6, 5, 0);
								SET_SENSE_RANGE(ped6, 30.0);
								SET_CHAR_WILL_USE_COVER(ped6, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
								SET_CHAR_SHOOT_RATE(ped6, 45);
							}
							if (!IS_CHAR_DEAD(ped10))
							{
								DETACH_PED(ped10, 1);
								FREEZE_CHAR_POSITION(ped10, 0);
								SET_CHAR_COORDINATES(ped10, 614.538, 1427.872, 3.604);// перемещаем игрока
							}

							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_NA", "COL5_1", 0, 0);//Port side! Port side!
								START_SCRIPT_CONVERSATION(1, 1);
							}		
							speed = 1;
						}
						if ((IS_CHAR_IN_AREA_3D( ped7, 634.567, 1431.057, -1.1, 626.567, 1423.057, 5.1, 0 )) && (speed2 == 0))// если игрок в зоне
						{
							// яхта (car5)
							if (!IS_CHAR_DEAD(ped7))
							{
								WARP_CHAR_FROM_CAR_TO_COORD(ped7, 626.895, 1430.59, 3.604);// высаживаем игрока
								SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
								SET_CHAR_RELATIONSHIP(ped7, 5, 0);
								SET_SENSE_RANGE(ped7, 30.0);
								SET_CHAR_WILL_USE_COVER(ped7, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
								SET_CHAR_SHOOT_RATE(ped7, 45);
							}
							if (!IS_CHAR_DEAD(ped11))
							{
								DETACH_PED(ped11, 1);
								FREEZE_CHAR_POSITION(ped11, 0);
								SET_CHAR_COORDINATES(ped11, 626.483, 1429.479, 3.604);// перемещаем игрока
							}
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_OA", "COL5_2", 0, 0);//They're attacking from starboard!
								START_SCRIPT_CONVERSATION(1, 1);
							}		
							speed2 = 1;
						}
						if ((IS_CHAR_IN_AREA_3D( ped8, 605.667, 1410.639, -1.1, 597.667, 1402.639, 5.1, 0 )) && (speed3 == 0))// если игрок в зоне
						{
							// яхта (car6)
							if (!IS_CHAR_DEAD(ped8))
							{
								WARP_CHAR_FROM_CAR_TO_COORD(ped8, 610.485, 1415.093, 3.604);// высаживаем игрока
								SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
								SET_CHAR_RELATIONSHIP(ped8, 5, 0);
								SET_SENSE_RANGE(ped8, 30.0);
								SET_CHAR_WILL_USE_COVER(ped8, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, FALSE);
								SET_CHAR_SHOOT_RATE(ped8, 45);
							}
							if (!IS_CHAR_DEAD(ped12))
							{
								DETACH_PED(ped12, 1);
								FREEZE_CHAR_POSITION(ped12, 0);
								SET_CHAR_COORDINATES(ped12, 610.072, 1413.983, 3.604);// перемещаем игрока
							}
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_NA", "COL5_1", 0, 0);//Port side! Port side!
								START_SCRIPT_CONVERSATION(1, 1);
							}			
							speed3 = 1;
						}
						if ((IS_CHAR_IN_AREA_3D( ped9, 625.048, 1404.301, -1.1, 617.048, 1396.301, 6.1, 0 )) && (speed4 == 0))// если игрок в зоне
						{
							// катер (car7)
							if (!IS_CHAR_DEAD(ped9))
							{
								WARP_CHAR_FROM_CAR_TO_COORD(ped9, 619.481, 1409.687, 3.604);// высаживаем игрока
								SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
								SET_CHAR_RELATIONSHIP(ped9, 5, 0);
								SET_SENSE_RANGE(ped9, 30.0);
								SET_CHAR_WILL_USE_COVER(ped9, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, FALSE);
								SET_CHAR_SHOOT_RATE(ped9, 45);
							}
							if (!IS_CHAR_DEAD(ped13))
							{
								DETACH_PED(ped13, 1);
								FREEZE_CHAR_POSITION(ped13, 0);
								SET_CHAR_COORDINATES(ped13, 619.069, 1408.577, 3.604);// перемещаем игрока
							}
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R4_OA", "COL5_2", 0, 0);//They're attacking from starboard!
								START_SCRIPT_CONVERSATION(1, 1);
							}	
							speed4 = 1;
						}

						// стоп айдио
						if ((TIMERA() > 3500) && (play == 1))
						{
							play = 0;
						}

						// прохождение миссии
						if ((IS_CAR_DEAD(car8)) && (IS_CAR_DEAD(car9)) && (IS_CAR_DEAD(car12)))
						{
							skip = 2;// переменная пропуска
							break;
						}

						if (LanceH1 == 0)
						{
							GET_CAR_HEALTH(car8, &car_hp1);
						}
						if (LanceH2 == 0)
						{
							GET_CAR_HEALTH(car9, &car_hp2);
						}
						if (LanceH3 == 0)
						{
							GET_CAR_HEALTH(car12, &car_hp3);
						}


						if (((car_hp1 < 600) && (LanceH1 == 0)) || ((explo_1 == 2) && (LanceH1 == 0)))
						{
							EXPLODE_CAR(car8, 1, 1);
							LanceH1 = 1;
							WAIT( 250 );
						}
						if (((car_hp2 < 600) && (LanceH2 == 0)) || ((explo_1 == 3) && (LanceH2 == 0)))
						{
							EXPLODE_CAR(car9, 1, 1);
							LanceH2 = 1;
							WAIT( 250 );
						}
						if (((!IS_CHAR_SITTING_IN_ANY_CAR(ped16)) && (LanceH3 == 0)) || ((car_hp3 < 500) && (LanceH3 == 0)) || ((explo_1 == 5) && (LanceH3 == 0)))
						{
							EXPLODE_CAR(car12, 1, 1);
							LanceH3 = 1;
							WAIT( 50 );
						}

						GET_CHAR_HEALTH(ped1, &Cortes_hp);
						if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COL5_B3", 5000, 1);//~r~The Colonel is dead!					
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((Cortes_hp < 50) || (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 657.177, 1373.828, -5.0, 577.177, 1463.828, 25.0, 0 )))// если игрок в зоне
						{
							EXPLODE_CHAR_HEAD(ped1);
							WAIT( 25 );
						}
					}
				}

				// завершение миссии
				REMOVE_BLIP(vert_ico);//Удаляем иконку на радаре
				REMOVE_PICKUP(sweap_1);
				REMOVE_PICKUP(aid_1);
				G_CORTEZ = 7;

				if (skip == 1)
				{
					if (IS_CHAR_DEAD(GetPlayerPed()))
					{
						while (true)
						{
							WAIT( 0 );
							if (!IS_CHAR_DEAD(GetPlayerPed()))
							{
								break;
							}
						}
					}
					else
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
						SET_CHAR_COORDINATES(GetPlayerPed(), 193.919, -827.131, 2.028);// перемещаем игрока
						SET_CHAR_HEADING(GetPlayerPed(), -85.0);
						WAIT( 500 );
						DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					}
				}
				else if (skip == 2)
				{
					// камера уплытия тут
					SetTime(2500);
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
					SET_CHAR_COORDINATES(ped1, 41.0, -818.0, 2.604);// перемещаем игрока

					// запускаем пути приплытия
					REQUEST_CAR_RECORDING( 3013 );// Яхта Котеса
					while (!HAS_CAR_RECORDING_BEEN_LOADED( 3013 )) WAIT(0);
					START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3013, -10.0, 70.0, 0.0);// Яхта Котеса

					SET_CAR_COORDINATES(car13, 587.045, 1686.647, 1.587);// перемещаем катер
					SET_CAR_HEADING(car13, 130.0);
					WARP_CHAR_INTO_CAR(GetPlayerPed(), car13);// садим игрока в катер

					// ставим камеру
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 634.947, 1475.841, 2.741); // куда смотрит камера
					SET_CAM_POS			( camera, 629.109, 1583.829, 5.083 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );
					DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
					SetTime(4000);

					// меняем ракурс
					POINT_CAM_AT_COORD	( camera, 628.874, 1506.061, 10.863); // куда смотрит камера
					SET_CAM_POS			( camera, 634.541, 1342.408, 13.411 );//расположение камеры
					SetTime(4000);

					DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
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
					DESTROY_CAM( camera );
					SET_WIDESCREEN_BORDERS( 0 );

					STOP_PLAYBACK_RECORDED_CAR(car1);
					REMOVE_CAR_RECORDING( 3013 ); // выгружаем пути транспорта

					SET_CAR_COORDINATES(car1, 606.133, 1486.415, -3.9454);// перемещаем яхту
					SET_CAR_HEADING(car1, 360.0);
					TURN_OFF_VEHICLE_EXTRA(car1, 1, 0);
					FREEZE_CAR_POSITION(car1, 1); 
					SET_CAR_IN_CUTSCENE(car1, 1);

					FORCE_WEATHER_NOW(WEATHER_SUNNY);
					RELEASE_WEATHER();

					//------------ катсцена ----------------
					LOAD_ADDITIONAL_TEXT( "COL_5B", 6 ); // загружаем субтитры из *.GTX
					START_CUTSCENE_NOW("col_5b");
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

					SET_CAR_COORDINATES(car1, -26.928, -491.821, 1.587);// перемещаем яхту
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				}
				
				SET_MAX_WANTED_LEVEL(6);
				SET_CAR_DENSITY_MULTIPLIER(1);// включаем пути

				STOP_PLAYBACK_RECORDED_CAR(car10); // вертолёт (Maverick)
				STOP_PLAYBACK_RECORDED_CAR(car11); // вертолёт (Maverick)
				STOP_PLAYBACK_RECORDED_CAR(car12); // вертолёт (Hunter)
				REMOVE_CAR_RECORDING( 3014 ); // вертолёт (Maverick)
				REMOVE_CAR_RECORDING( 3015 ); // вертолёт (Maverick)
				REMOVE_CAR_RECORDING( 3016 ); // вертолёт (Hunter)

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM5);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM6);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM7);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM8);//выгружаем модель машины

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
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped21);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped22);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped23);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped24);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped25);//выгружаем модель педа(в последствии пед изчезнет

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
				MARK_CAR_AS_NO_LONGER_NEEDED(&car10);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car11);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car12);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car13);//выгружаем модель машины(в последствии машина изчезнет)

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_COL_5" );//All Hands On Deck!
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(5000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +5000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 5000);
					G_CORTEZ = 8;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
		else if ((G_ONMISSION == 0) && (G_CORTEZ == 8))
		{
			break;
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(cortez_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}
	}
}
void main(void)
{
	//THIS_SCRIPT_SHOULD_BE_SAVED();
	if (G_CORTEZ < 8)
	{
		cortez();
	}
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
