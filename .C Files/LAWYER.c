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
float PlayX, PlayY, PlayZ, PlayR, blip_on, skip, dialog, textID, help, car1_des, car2_des, car2_des2, autosave;
float PedX, PedY, PedZ, PedR, bike, in_car, in_cord, stelking, load_all, add_phone, locked;
float sound, soundID, riotID, riotON, skin, vorotaX;
float ped4_ID, ped5_ID, ped6_ID, ped7_ID, ped8_ID, ped9_ID, ped10_ID, ped11_ID, ped12_ID, ped13_ID;
float ped14_ID, ped15_ID, ped16_ID, ped17_ID, ped18_ID, ped19_ID, ped20_ID, ped21_ID, ped22_ID, ped23_ID, ped24_ID;
uint hour, minute, weather;


void SetTime(uint time)
{
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if (TIMERA() > time)
		{
			break;
		}
	}
}
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

void LAWYER_1(void)
{
	blip_on = 0;
	autosave = 0;
	Blip lawyer_ico, Party_ico, lance_car, jury_car1, jury_car2, Riot;	
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
//============================== The Party ======================================
		if ((G_ONMISSION == 0) && (G_LAWYER == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(552.217, -293.87, 4.356, &lawyer_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(lawyer_ico, BLIP_ROMAN);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(lawyer_ico, 0);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(lawyer_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(lawyer_ico, "NE_LAWYER");//иконка на радаре называние в истории карты "Адвокат"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 552.217, -293.87, 4.356, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 552.217, -293.87, 4.356, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				//--------------- СТАРТ МИССИИ ---------------
				start_scripted_cutscene("LAW_1", 15000, CUTSCENE_LAWYER);
				skip = 0; // переменная пропуска
				load_all = 0;
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(110.6, -824.2, 9.6, 327.9);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(lawyer_ico);//Удаляем иконку на радаре
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
				SET_CHAR_COORDINATES(GetPlayerPed(), 552.036, -293.714, 4.766);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 52.894);

				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "LAW_1A", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("law_1a");
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
				ADD_BLIP_FOR_COORD(527.259, -601.747, 4.341, &Party_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(Party_ico, BLIP_CLOTHES_SHOP);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(Party_ico, 0);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(Party_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_SHOP");//иконка на радаре называние в истории карты "Clothes shop"

				SetTime(1000);
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R14_VR", "", 0, 0);//
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				PRINT_STRING_IN_STRING("string", "LAW1_1", 5500, 1);//~g~Go get some new threads from Rafael's clothes shop.
				SetTime(2000);

				// мигиние радара
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(250);
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(250);
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(250);
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(3250);

				Car car1, car2, car3, car4, car5, car6;
				Ped ped1, ped2;
				Cam camera, camera2, camera3;

				uint PedM1 = MODEL_M_Y_DORK_02;// Байкер
				uint PedM2 = MODEL_IG_ANNA;// Мерседес
				uint CarM1 = MODEL_BOBBER;
				uint CarM2 = MODEL_BANSHEE;
				uint CarM3 = MODEL_SUPERGT;
				uint CarM4 = MODEL_INFERNUS;
				uint CarM5 = MODEL_STRETCH;

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

				REQUEST_MODEL(PedM1);// Байкер
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(PedM2);// Мерседес
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало

				// создаём байк и байкера
				CREATE_CAR(CarM1, 286.576, -788.199, 5.801, &car1, TRUE);
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//создаём педа за рулём автомобиля

				// создаём транспорт у яхты
				CREATE_CAR(CarM2, 196.987, -842.386, 2.732, &car2, TRUE);
				SET_CAR_HEADING(car2, 102.336);
				CREATE_CAR(CarM3, 195.982, -837.659, 2.732, &car3, TRUE);
				SET_CAR_HEADING(car3, -77.664);
				CREATE_CAR(CarM4, 191.256, -818.101, 2.732, &car4, TRUE);
				SET_CAR_HEADING(car4, 102.336);
				CREATE_CAR(CarM5, 191.191, -813.617, 2.732, &car5, TRUE);
				SET_CAR_HEADING(car5, 102.336);

				// создаём Мерседес
				CREATE_CHAR (26, PedM2, 281.145, -791.79, 5.445, &ped2, TRUE);// создаём педа
				SET_CHAR_COMPONENT_VARIATION(ped2, 1, 0, 0);

				// грузим пути байкера
				REQUEST_CAR_RECORDING( 2993 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 2993 )) WAIT(0);

				//------------------ Первая часть миссии ------------------
				while (TRUE)
				{
					WAIT(0);
					DRAW_CHECKPOINT( 527.259, -601.747, 4.341, 1.3, 246, 151, 255);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 527.259, -601.747, 4.341, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 1.3) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

						// камера сверху
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 530.273, -604.626, 4.197 ); // куда смотрит камера
						SET_CAM_POS			( camera, 522.552, -596.448, 16.414 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 529.623, -603.946, 4.766, 2, -2);// Томми идёт в двери
						SetTime(1000);

						DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
						while(true)
						{
							WAIT(0);
							if (IS_SCREEN_FADED_OUT())
							{
								break;
							}
						}
						// переодивание	
						SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 1, 0);

						SET_CHAR_COORDINATES(GetPlayerPed(), 528.664, -602.916, 4.766);// перемещаем игрока
						SET_CHAR_HEADING(GetPlayerPed(), 52.9);
						SetTime(200);
						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана

						// подём камеры
						CREATE_CAM( 3, &camera2 );
						CREATE_CAM( 14, &camera3 );
						POINT_CAM_AT_COORD	( camera, 528.442, -602.798, 4.56 ); // куда смотрит камера
						SET_CAM_POS			( camera, 527.141, -601.545, 5.08 );//расположение камеры
						POINT_CAM_AT_COORD	( camera3, 528.442, -602.798, 5.839 ); // куда смотрит камера
						SET_CAM_POS			( camera3, 527.141, -601.545, 5.08 );//расположение камеры
						SET_CAM_INTERP_STYLE_CORE( camera2, camera, camera3, 3500, 0 ); //перемещение камеры от игрока на точку указанную в координатах "SET_CAM_POS(camera, X, Y, Z)" 
						SET_CAM_ACTIVE( camera2, 1 );
						SET_CAM_PROPAGATE( camera2, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);

						SetTime(800);
						CLEAR_AREA(527.259, -601.747, 4.341, 80.5, 1);//очещаем зону загрузки
						START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 2993, 0.0, 0.0, 0.0);// подъезд мотоцыкла
						SetTime(3200);
						
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						DESTROY_CAM( camera2 );
						DESTROY_CAM( camera3 );

						// смена ракурса камеры
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 529.848, -602.708, 5.331 ); // куда смотрит камера
						SET_CAM_POS			( camera, 507.329, -603.689, 5.273 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SetTime(1000);

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R1_BE", "LAW1_12", 0, 0);//Hmmmm...nice bike.
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(2000);

						STOP_PLAYBACK_RECORDED_CAR(car1);
						TASK_LEAVE_CAR(ped1, car1);
						TASK_GO_STRAIGHT_TO_COORD(ped1, 508.057, -642.656, 12.069, 2, -2);
						SetTime(2500);

						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "LAW1_2", 5500, 1);//~g~Get to the Colonel's boat.

						ADD_BLIP_FOR_COORD(192.169, -827.01, 2.043, &Party_ico);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(Party_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(Party_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//иконка на радаре называние в истории карты ""

						bike = 0;
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
				}
				//------------------ Вторая часть миссии ------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						if ((!IS_CHAR_DEAD(ped1)) && (!IS_CHAR_INJURED(ped1)))//если игрок мёртв или аврестован
						{
							if ((IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (bike == 0))
							{
								bike = 1;
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R1_BE_XXX1", "LAW1_13", 0, 0);//No! My Bike!
								START_SCRIPT_CONVERSATION(1, 1);
								SETTIMERB( 0 );

								// тут анимация
								SET_CHAR_HEADING(ped1, -32.106);
								REQUEST_ANIMS( "amb@taxi_hail_m" );
								while (!HAVE_ANIMS_LOADED( "amb@taxi_hail_m" )) WAIT(0);
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "hail_left", "amb@taxi_hail_m", 1.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
							}
							if ((bike == 1) && (TIMERB() > 2000))
							{
								bike = 2;
								CLEAR_PRINTS();
								TASK_COMBAT(ped1, GetPlayerPed());
								PRINT_STRING_IN_STRING("string", "LAW1_2", 5500, 1);//~g~Get to the Colonel's boat.
							}
						}

						if ((load_all == 0) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 182.78, -847.079, 0.41, 210.881, -811.954, 17.658, 0 )))
						{
							load_all = 1;
							MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель машины
							MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
							MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
							MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель машины
							MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//выгружаем модель машины
							MARK_MODEL_AS_NO_LONGER_NEEDED(CarM5);//выгружаем модель машины

							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
							MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
							MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
							MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
							MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)
							REMOVE_CAR_RECORDING( 2993 ); // выгружаем пути транспорта
						}

						DRAW_CHECKPOINT( 192.169, -827.01, 2.043, 1.8, 246, 151, 255);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 192.169, -827.01, 2.043, &PlayR);//проверка "игрок на координатах"
						if ( PlayR < 1.3 )
						{
							REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							SET_WIDESCREEN_BORDERS(true);

							CREATE_CAM(14, &camera);
							SET_CAM_POS(camera, -229.438 + MAP_OFFSET_X, -1364.204 + MAP_OFFSET_Y, 12.607 + MAP_OFFSET_Z);
							POINT_CAM_AT_COORD(camera, -230.424 + MAP_OFFSET_X, -1364.068 + MAP_OFFSET_Y, 12.511 + MAP_OFFSET_Z); //View of boat
							SET_CAM_FOV(camera, 45.0);
							SET_CAM_ACTIVE(camera, 1);
							SET_CAM_PROPAGATE(camera, 1);
							ACTIVATE_SCRIPTED_CAMS(1, 1);

							WAIT(1000);

							DO_SCREEN_FADE_OUT(1500);// Затемняем экран

							mission_name = "LAW_1";
							mission_name_display_duration = 20000;
							#if !defined MISSION_NAME_COMPATIBILITY // Added workaround for PRINT_BIG disappearing after cutscene starts
							GET_GAME_TIMER(&mission_name_display_start_time);
							#endif
							PRINT_BIG("LAW_1", 20000, 2);

							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							// проверка игрок в машине
							if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car6);
								WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 189.069, -827.351, 2.732);// высаживаем игрока
								FIX_CAR(car6);
								SET_CAR_COORDINATES(car6, 194.114, -830.352, 2.732);
								SET_CAR_HEADING(car6, -77.664);
								MARK_CAR_AS_NO_LONGER_NEEDED(&car6);
							}
							SET_CHAR_COORDINATES(GetPlayerPed(), 189.069, -827.351, 2.732);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), -55.1);
							SET_CHAR_COORDINATES(ped2, 189.147, -825.867, 2.732);// перемещаем педа Мерседес
							SET_CHAR_HEADING(ped2, -175.0);

							//------------ катсцена ----------------
							LOAD_ADDITIONAL_TEXT( "LAW_1B", 6 ); // загружаем субтитры из *.GTX
							START_CUTSCENE_NOW("law_1b");
							while (!HAS_CUTSCENE_LOADED())
							{
								WAIT(0);
							}

							DO_SCREEN_FADE_IN(0);
							while (!HAS_CUTSCENE_FINISHED())
							{
								WAIT(0);
							}

							ACTIVATE_SCRIPTED_CAMS(0, 0);
							DESTROY_CAM(camera);
							SET_CAM_BEHIND_PED(GetPlayerPed());

							if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
							{
								DO_SCREEN_FADE_IN(0);
							}
							
							SET_WIDESCREEN_BORDERS(false);
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							ADD_BLIP_FOR_COORD(534.054, -946.33, 4.189, &Party_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(Party_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(Party_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//иконка на радаре называние в истории карты ""
							PRINT_STRING_IN_STRING("string", "LAW1_3", 5500, 1);//~g~Take the Colonel's daughter to the Pole Position club.
							in_car = 0;
							stelking = 0;
							dialog = 0;
							textID = 0;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				//------------------ Третья часть миссии ------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						// Мерседес сталкирит за Томми
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+15, PedY+15, PedZ+15, PedX-15, PedY-15, PedZ-15, 0 ))
						{
							if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (in_car == 0))
							{
								in_car = 1;
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car6);
								TASK_ENTER_CAR_AS_PASSENGER(ped2, car6, -1, 0);
								SETTIMERB( 0 );
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped2))
								{
									in_car = 0;
									TASK_LEAVE_CAR(ped2, car6);
									MARK_CAR_AS_NO_LONGER_NEEDED(&car6);
								}
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (in_car == 1) && (TIMERB() > 15000))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped2, car6, 0);
							}
							if (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
								if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+5, PedY+5, PedZ+5, PedX-5, PedY-5, PedZ-5, 0 ))
								{
									TASK_GO_STRAIGHT_TO_COORD(ped2, PlayX, PlayY, PlayZ, 4, -2);
								}
							}
							if (stelking == 1)
							{
								stelking = 0;
							}
						}
						else
						{
							if (stelking == 0)
							{
								stelking = 1;
								TASK_GO_STRAIGHT_TO_COORD(ped2, PedX, PedY, PedZ, 4, -2);
								PRINT_STRING_IN_STRING("string", "NE_LEFT", 5500, 1);//~g~You left the colonels daughter, come back for her.
							}
						}
						// Диалог в транспорте
						if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (dialog == 0))
						{
							if (IS_CHAR_ON_ANY_BIKE(GetPlayerPed())) // в мотоцикле
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R1_BE_XXX2", "NE_BIKE", 0, 0);//Wow, I like your motorcycle.
								START_SCRIPT_CONVERSATION(1, 1);
								dialog = 1;
								textID = 2;
							}
							else // в машине
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R1_BE_XXX3", "LAW1_5", 0, 0);//Will you be working for my father?
								START_SCRIPT_CONVERSATION(1, 1);
								dialog = 2;
								textID = 2;
							}
						}
						if (dialog == 1)
						{
							if (textID == 2)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BE_XXX3", "LAW1_5", 0, 0);//Will you be working for my father?
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 3;
								}
							}
							else if (textID == 3)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BF", "LAW1_6", 0, 0);//Maybe.
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 4;
								}
							}
							else if (textID == 4)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BF_XXX1", "LAW1_9", 0, 0);//It's so difficult having a rich and powerful father. Vamos.
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 5;
								}
							}
							else if (textID == 5)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									CLEAR_PRINTS();
									textID = 6;
								}
							}
						}
						else if (dialog == 2)
						{
							if (textID == 2)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BF", "LAW1_6", 0, 0);//Maybe.
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 3;
								}
							}
							else if (textID == 3)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BF_XXX2", "LAW1_7", 0, 0);//Do you mind me resting my hand in your lap?
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 4;
								}
							}
							else if (textID == 4)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BF", "LAW1_8", 0, 0);//Maybe.
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 5;
								}
							}
							else if (textID == 5)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BF_XXX1", "LAW1_9", 0, 0);//It's so difficult having a rich and powerful father. Vamos.
									START_SCRIPT_CONVERSATION(1, 1);
									textID = 6;
								}
							}
							else if (textID == 6)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									CLEAR_PRINTS();
									textID = 7;
								}
							}
						}

						DRAW_CHECKPOINT( 534.054, -946.33, 4.189, 1.3, 246, 151, 255);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 534.054, -946.33, 4.189, &PlayR);//проверка "игрок на координатах"
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 534.054, -946.33, 4.189, &PedR);//проверка "игрок на координатах"
						if (( PlayR < 1.5 ) && ( PedR < 1.5 ))
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							// затемнение
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
							DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							// Мерседесс идёт в двери
							if (IS_CHAR_SITTING_IN_ANY_CAR(ped2))
							{
								WARP_CHAR_FROM_CAR_TO_COORD(ped2, 533.717, -943.083, 4.834);// высаживаем педа
							}
							else
							{
								SET_CHAR_COORDINATES(ped2, 533.717, -943.083, 4.834);// перемещаем педа Мерседес
							}
							TASK_GO_STRAIGHT_TO_COORD(ped2, 524.137, -930.173, 4.834, 2, -2);

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 535.314, -937.212, 8.304); // куда смотрит камера
							SET_CAM_POS			( camera, 519.49, -951.657, 4.995 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							SetTime(200);
							DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
							SetTime(500);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BG", "LAW1_10", 0, 0);//See you around, handsome!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							CLEAR_PRINTS();

							// смена ракурса камеры
							POINT_CAM_AT_COORD	( camera, 524.911, -931.449, 6.039 ); // куда смотрит камера
							SET_CAM_POS			( camera, 533.056, -941.08, 4.889 );//расположение камеры
							
							{
								WAIT(500);
							}

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R1_BH", "LAW1_11", 0, 0);//I'm sure you will..
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
                            CLEAR_PRINTS();
							//убираем камеру
							SetTime(4000);
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							SET_CHAR_COORDINATES(ped2, 19.147, -5.867, 12.732);// перемещаем педа Мерседес
							skip = 2;// переменная пропуска
							CLEAR_PRINTS();
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_INJURED(ped2)))//если игрок мёртв или аврестован
						{
							ABORT_SCRIPTED_CONVERSATION( 0 );
							CLEAR_PRINTS();
							EXPLODE_CHAR_HEAD(ped2);
							PRINT_STRING_IN_STRING("string", "LAW1_4", 5500, 1);//~r~You killed the Colonel's daughter!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// чистим скрипт тут
				ABORT_SCRIPTED_CONVERSATION( 0 );
				REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
				if (load_all == 0)
				{
					MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель машины
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель машины
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//выгружаем модель машины
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM5);//выгружаем модель машины
					MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
					MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
					MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
					MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
					MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
					MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)
					REMOVE_CAR_RECORDING( 2993 ); // выгружаем пути транспорта
				}
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				RELEASE_WEATHER();
				if (car6 != 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//выгружаем модель машины(в последствии машина изчезнет)
				}
				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					PRINT_HELP("NECLOTH1"); //Soiree outfit delivered to Ocean View Hotel on Ocean Beach.
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_LAW_1" );//The Party
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(100, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +100 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);
					G_LAWYER = 2;

					autosave = 1;
				}

				G_ONMISSION = 0;
				blip_on = 0;
			}
		}
//============================== Back Alley Brawl ======================================
		else if ((G_ONMISSION == 0) && (G_LAWYER == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(552.217, -293.87, 4.356, &lawyer_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(lawyer_ico, BLIP_ROMAN);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(lawyer_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(lawyer_ico, "NE_LAWYER");//иконка на радаре называние в истории карты "Адвокат"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 552.217, -293.87, 4.356, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 552.217, -293.87, 4.356, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				//--------------- СТАРТ МИССИИ ---------------
				start_scripted_cutscene("LAW_2", 15000, CUTSCENE_LAWYER);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(110.6, -824.2, 9.6, 327.9);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				skip = 0;// переменная пропуска
				add_phone = 0;
				in_cord = 0;
				textID = 0;
				in_car = 0;
				help = 0;
				locked = 1;
				REMOVE_BLIP(lawyer_ico);//Удаляем иконку на радаре
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

				SET_CHAR_COORDINATES(GetPlayerPed(), 552.036, -293.714, 4.766);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 52.894);
				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 40);//устанавливаем время
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "LAW_2A", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("law_2a");
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

				ADD_BLIP_FOR_COORD(925.599, 453.827, 5.389, &Party_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(Party_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(Party_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//иконка на радаре называние в истории карты "Телефонный звонок"
				PRINT_STRING_IN_STRING("string", "LAW2_6", 5500, 1);//~g~Go to the Malibu Club and find Kent Paul.

				Car car1;
				Pickup mob_phone;
				Ped ped1, ped2, ped3, ped4, ped5;
				Cam camera, camera2, camera3;
				Object trubka_1;
				int dm, cdm;

				uint PedM1 = MODEL_M_M_KOREACOOK_01;// Повор - босс 
				uint PedM2 = MODEL_M_M_SHORTORDER;// повор m_m_koreacook_01 
				uint PedM3 = MODEL_IG_LILJACOB;// Ланс
				uint CarM1 = MODEL_INFERNUS;
				uint trubka = vc_mob_phone;

				LOAD_CHAR_DECISION_MAKER(2, &dm);
				LOAD_COMBAT_DECISION_MAKER(3, &cdm);

				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				REQUEST_MODEL(PedM1);// Повор - босс
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// повор
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// Ланс
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало

				// создаём педов
				CREATE_CHAR (26, PedM1, 281.145, -791.79, 5.445, &ped1, TRUE);// создаём повора босса
				CREATE_CHAR (26, PedM2, 281.145, -791.79, 5.445, &ped2, TRUE);// создаём повора 1
				CREATE_CHAR (26, PedM2, 281.145, -791.79, 5.445, &ped3, TRUE);// создаём повора 2
				CREATE_CHAR (26, PedM2, 281.145, -791.79, 5.445, &ped4, TRUE);// создаём повора 3
				CREATE_CHAR (26, PedM3, 281.145, -791.79, 5.445, &ped5, TRUE);// // создаём Ланса

				//создаём машину Ланса
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				CREATE_CAR(CarM1, 196.987, -842.386, 2.732, &car1, TRUE);
				SET_CAR_HEADING(car1, 102.336);
				LOCK_CAR_DOORS(car1, 3); //блокируем двери автомобиля для игрока
				CHANGE_CAR_COLOUR( car1, 112, 112 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car1, 112, 112 );//цвет отрожений машины

				// грузим пути
				REQUEST_CAR_RECORDING( 2994 );// грузим пути ланса подъезд
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 2994 )) WAIT(0);
				REQUEST_CAR_RECORDING( 2995 );// грузим пути ланса уезд
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 2995 )) WAIT(0);

				// грузим телефон
				REQUEST_MODEL(trubka);
				while (!HAS_MODEL_LOADED(trubka)) WAIT(0);
				CREATE_OBJECT_NO_OFFSET(trubka, 1.1, 1.1, -1.1, &trubka_1, TRUE);

				//------------------ Первая часть миссии ------------------
				while (TRUE)
				{
					// клуб молибу
					WAIT(0);
					DRAW_CHECKPOINT( 925.599, 453.827, 5.389, 1.3, 246, 151, 255);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 925.599, 453.827, 5.389, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 1.3) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

						// ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 923.279, 454.929, 6.108); // куда смотрит камера
						SET_CAM_POS			( camera, 936.918, 437.017, 6.893 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 921.141, 457.901, 5.688, 2, -2);//игрок идёт в клуб

						// затемнение
						REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
						DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
						while(true)
						{
							WAIT(0);
							if (IS_SCREEN_FADED_OUT())
							{
								break;
							}
						}
						SetTime(200);
						SET_CHAR_COORDINATES(GetPlayerPed(), 925.06, 453.041, 5.763);// перемещаем игрока
						SET_CHAR_HEADING(GetPlayerPed(), -128.321);

						//убираем камеру
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );

						//------------ катсцена тут ----------------
						LOAD_ADDITIONAL_TEXT( "LAW_2B", 6 ); // загружаем субтитры из *.GTX
						START_CUTSCENE_NOW("law_2b");
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

						ADD_BLIP_FOR_COORD(869.546, -37.984, 5.566, &Party_ico);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
						CHANGE_BLIP_COLOUR(Party_ico, 19);  //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(Party_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//иконка на радаре называние в истории карты "Телефонный звонок"
						PRINT_STRING_IN_STRING("string", "LAW2_7", 5500, 1);//~g~Go and find the chef on Ocean Drive.

						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
						SET_CHAR_COORDINATES(ped1, 869.546, -37.984, 4.853);// перемещаем повора-босса
						SET_CHAR_HEADING(ped1, 56.323);

						// анимация разговора по телефону
						ATTACH_OBJECT_TO_PED( trubka_1, ped1, 1232, 0.070, 0.052, 0.003, 3.30000000, 0.30000000, -0.45000000, 0 );
						REQUEST_ANIMS( "amb@payphone" );//загружаем файл с анимацией
						while (!HAVE_ANIMS_LOADED( "amb@payphone" )) WAIT(0);
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "cellphone_talk", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
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
				//------------------ Вторая часть миссии ------------------
					while (TRUE)
					{
						// драка в переулке
						WAIT(0);
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 869.546, -37.984, 5.566, &PlayR);//проверка "игрок на координатах"
						if ( PlayR < 15.3)
						{
							REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 868.909, -38.109, 5.991); // куда смотрит камера
							SET_CAM_POS			( camera, 871.836, -37.408, 6.237 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
								SET_CHAR_COORDINATES(GetPlayerPed(), 879.131, -26.629, 5.39);// перемещаем игрока
								SET_CHAR_HEADING(GetPlayerPed(), 156.233);
								WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 872.062, -31.654, 4.918);// высаживаем игрока
							}
							else
							{
								SET_CHAR_COORDINATES(GetPlayerPed(), 872.062, -31.654, 4.918);// перемещаем игрока
								SET_CHAR_HEADING(GetPlayerPed(), 154.994);
							}

							SetTime(800);
							SET_CHAR_HEADING(ped1, -15.994);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "cellphone_out", "amb@payphone", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
							SetTime(1000);
							DETACH_OBJECT( trubka_1, 1 );
							SET_OBJECT_COORDINATES(trubka_1, 1.1, 1.1, -1.1);

							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 870.175, -36.652, 4.918, 2, -2);//игрок идёт к повору - боссу
							SetTime(200);

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, 870.603, -38.014, 4.678); // куда смотрит камера
							SET_CAM_POS			( camera, 867.869, -25.671, 8.817 );//расположение камеры

							// диалог тут
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R1_BH_XXX2", "LAW2_1", 0, 0);//Hey, whatchoo lookin' at?
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

// анимация разговора тут

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BI", "LAW2_2", 0, 0);//You better start talking..
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

// анимация разговора тут

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BI_XXX1", "LAW2_3", 0, 0);//Hey, make me, you prick!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							//убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							// над повором загорается стрелка
							ADD_BLIP_FOR_CHAR(ped1, &Party_ico);
							CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
							CHANGE_BLIP_COLOUR(Party_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "MO_TARGET");//иконка на радаре "Связной"
							CHANGE_BLIP_SCALE(Party_ico, 0.6); // масштаб иконки на радаре

							// повор атакует игрока
							SetTime(200);
							CLEAR_PRINTS();
							SET_SENSE_RANGE(ped1, 50.0);
							SET_CHAR_DECISION_MAKER(ped1, dm);
							SET_COMBAT_DECISION_MAKER(ped1, cdm);
							SET_CHAR_HEALTH(ped1, 200);
							SET_CHAR_KEEP_TASK(ped1, 1);
							TASK_COMBAT(ped1, GetPlayerPed());
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, 0);
							SetTime(3000);

							while (TRUE)
							{
								WAIT(0);
								if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_INJURED(ped1)))//если пед мёртв или ранен
								{
									EXPLODE_CHAR_HEAD(ped1);
									REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре

									// из педа выподает телефон
									PRINT_STRING_IN_STRING("string", "LAW2_11", 5500, 1);//~g~Pick up his cell phone.
									GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
									GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &PedZ);
									CREATE_PICKUP( vc_phone_pick_up, 22, PedX+0.2, PedY+0.2, PedZ+0.2, &mob_phone, 0 );// телефон

									ADD_BLIP_FOR_PICKUP(mob_phone, &Party_ico);
									CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
									CHANGE_BLIP_COLOUR(Party_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
									CHANGE_BLIP_SCALE(Party_ico, 0.6); // масштаб иконки на радаре
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "MO_TARGET");//иконка на радаре называние в истории карты "Телефонный звонок"
									add_phone = 1;
									break;
								}
								GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
								if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+20, PedY+20, PedZ+20, PedX-20, PedY-20, PedZ-20, 0 ))// если игрок убежал от повора
								{
									PRINT_STRING_IN_STRING("string", "NE_FIGHT", 5500, 1);//~r~Are you afraid of a fight?
									skip = 1;// переменная пропуска
									break;
								}
								else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
								{
									skip = 1;// переменная пропуска
									break;
								}
							}
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_INJURED(ped1)))//если игрок мёртв или аврестован
						{
							EXPLODE_CHAR_HEAD(ped1);
							DETACH_OBJECT( trubka_1, 1 );
							SET_OBJECT_COORDINATES(trubka_1, 1.1, 1.1, -1.1);

							REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
							if (add_phone == 0)
							{
								// из педа выподает телефон
								PRINT_STRING_IN_STRING("string", "LAW2_11", 5500, 1);//~g~Pick up his cell phone.
								GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
								GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &PedZ);
								CREATE_PICKUP( vc_phone_pick_up, 22, PedX+0.2, PedY+0.2, PedZ+0.2, &mob_phone, 0 );// телефон

								ADD_BLIP_FOR_PICKUP(mob_phone, &Party_ico);
								CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
								CHANGE_BLIP_COLOUR(Party_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(Party_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "MO_TARGET");//иконка на радаре называние в истории карты "Телефонный звонок"
								add_phone = 1;
							}
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				//------------------ Третья часть миссии ------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						// поднять телефон
						WAIT(0);
						if (HAS_PICKUP_BEEN_COLLECTED( mob_phone ))
						{
							REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							PRINT_HELP_FOREVER("LAW2_12"); //Cell phone acquired! You can now receive phone calls.
							SetTime(1000);

							DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							CLEAR_HELP(); // удаляем текст подсказки

							// раздаём оружие
							GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_PISTOL, 14, FALSE);
							SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_PISTOL, TRUE);

							UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_3);
							UpdateWeaponOfPed(ped3, WEAPON_KNIFE);
							UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_3);
							UpdateWeaponOfPed(ped5, WEAPON_PISTOL);
							SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_EPISODIC_3, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_KNIFE, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_3, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_PISTOL, TRUE);

							// телепортируем Игрока
							SET_CHAR_COORDINATES(GetPlayerPed(), 867.67, -38.887, 4.918);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), -21.819);

							// телепортируем Ланса
							SET_CHAR_COORDINATES(ped5, 867.607, -41.114, 4.918);// перемещаем Ланса
							SET_CHAR_HEADING(ped5, 154.994);

							// телепортируем автомобиль Ланса
							SET_CAR_COORDINATES(car1, 867.521, -116.042, 5.519);// перемещаем автомобиль Ланса
							SET_CAR_HEADING(car1, 156.233);
							FREEZE_CAR_POSITION(car1, 1);

							// телепортируем поворов
							SET_CHAR_COORDINATES(ped2, 871.851, -33.606, 4.918);// перемещаем повора1
							SET_CHAR_HEADING(ped2, 154.994);

							SET_CHAR_COORDINATES(ped3, 870.694, -32.833, 4.918);// перемещаем повора2
							SET_CHAR_HEADING(ped3, 154.994);

							SET_CHAR_COORDINATES(ped4, 869.312, -32.151, 4.918);// перемещаем повора3
							SET_CHAR_HEADING(ped4, 154.994);
							SetTime(500);

							ADD_BLIP_FOR_CHAR(ped5, &Party_ico);
							CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
							CHANGE_BLIP_COLOUR(Party_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_LANCE");//иконка на радаре "Связной"
							CHANGE_BLIP_SCALE(Party_ico, 0.6); // масштаб иконки на радаре

							ADD_BLIP_FOR_CAR(car1, &lance_car);
							CHANGE_BLIP_SPRITE(lance_car, BLIP_OBJECTIVE);//текстура иконки на радаре
							CHANGE_BLIP_COLOUR(lance_car, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(lance_car, "NE_CAR");//иконка на радаре "Связной"
							CHANGE_BLIP_SCALE(lance_car, 0.6); // масштаб иконки на радаре

							//------------ катсцена тут ----------------
							LOAD_ADDITIONAL_TEXT( "LAW_2C", 6 ); // загружаем субтитры из *.GTX
							START_CUTSCENE_NOW("law_2c");
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

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 870.993, -32.916, 5.651 ); // куда смотрит камера
							SET_CAM_POS			( camera, 864.445, -44.067, 6.119 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							SetTime(2000);

							// смена ракурса
							POINT_CAM_AT_COORD	( camera, 864.085, -44.291, 5.505 ); // куда смотрит камера
							SET_CAM_POS			( camera, 869.913, -35.165, 5.837 );//расположение камеры

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BI_XXX2", "LAW2_4", 0, 0);//This way!
							START_SCRIPT_CONVERSATION(1, 1);
							TASK_GO_STRAIGHT_TO_COORD(ped5, 838.004, -103.263, 4.918, 4, -2);//Ланс бежит в первый пойнт
							SetSpeech();

							//убираем камеру
							SetTime(500);
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							SET_SENSE_RANGE(ped2, 50.0);
							SET_CHAR_DECISION_MAKER(ped2, dm);
							SET_COMBAT_DECISION_MAKER(ped2, cdm);
							SET_CHAR_HEALTH(ped2, 200);
							SET_CHAR_KEEP_TASK(ped2, 1);
							TASK_COMBAT(ped2, GetPlayerPed());
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, 0);

							SET_SENSE_RANGE(ped3, 50.0);
							SET_CHAR_DECISION_MAKER(ped3, dm);
							SET_COMBAT_DECISION_MAKER(ped3, cdm);
							SET_CHAR_HEALTH(ped3, 200);
							SET_CHAR_KEEP_TASK(ped3, 1);
							TASK_COMBAT(ped3, GetPlayerPed());
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, 0);

							SET_SENSE_RANGE(ped4, 50.0);
							SET_CHAR_DECISION_MAKER(ped4, dm);
							SET_COMBAT_DECISION_MAKER(ped4, cdm);
							SET_CHAR_HEALTH(ped4, 200);
							SET_CHAR_KEEP_TASK(ped4, 1);
							TASK_COMBAT(ped4, GetPlayerPed());
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, 0);
							CLEAR_PRINTS();
							SetTime(6000);
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				//------------------ Четвёртая часть миссии ------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						// сесть в иашину
						WAIT(0);
						GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//вписываем координаты педа в переменную
						if (in_cord == 0)
						{
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 838.004, -103.263, 4.918, &PedR);//проверка "пед на координатах"
							if ( PedR < 1.3)
							{
								TASK_GO_STRAIGHT_TO_COORD(ped5, 867.269, -115.923, 5.519, 4, -2);//Ланс бежит во второй пойнт
								in_cord = 1;
							}
						}
						else if (in_cord == 1)
						{
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 867.269, -115.923, 5.519, &PedR);//проверка "пед на координатах"
							if ( PedR < 5.3)
							{
								TASK_ENTER_CAR_AS_PASSENGER(ped5, car1, -1, 0);
								in_cord = 2;
								SETTIMERB(0); //сбрасываем таймер 
							}
						}

						if (locked == 1)
						{
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 868.855, -116.292, 5.08047, &PlayR);//проверка "игрок на координатах"
							if ( PlayR < 1.5)
							{
								FREEZE_CAR_POSITION(car1, 0);
								LOCK_CAR_DOORS(car1, 1); //разблокируем двери автомобиля для игрока
								locked = 0;
							}
						}

						if ((IS_CHAR_SITTING_IN_ANY_CAR(ped5)) && (in_cord == 2))
						{
							PRINT_STRING_IN_STRING("string", "NE_IN_CAR", 5500, 1);//~g~Get in the car.
							REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
							in_cord = 3;
						}
						else if (( TIMERB() > 10000 ) && (in_cord == 2) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped5)))
						{
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped5, car1, 0);
						}

						if ((IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (IS_CHAR_SITTING_IN_ANY_CAR(ped5)))
						{
							REMOVE_BLIP(lance_car);//Удаляем иконку на радаре
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped5)) || (IS_CHAR_INJURED(ped5)))//если Ланс мёртв
						{
							skip = 1;// переменная пропуска
							PRINT_STRING_IN_STRING("string", "COK2_26", 5500, 1);//~r~You killed Lance!
							EXPLODE_CHAR_HEAD(ped5);
							break;
						}
					}
				}
				//------------------ Первая часть миссии ------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						// оружейный магазин
						WAIT(0);
						if ((IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (textID == 0))
						{
							// диалог тут
							SetTime(2000);
							CLOSE_ALL_CAR_DOORS(car1);
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BI_XXX3", "LAW2_16", 0, 0);//One thing you gotta realize about this town. You gotta pack some heat.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BJ", "LAW2_17", 0, 0);//C'mon, the local gun shop's a couple of blocks away.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// создаём блип оружейки
							SetTime(1000);
							ADD_BLIP_FOR_COORD(369.825, -949.315, 4.43197, &Party_ico);
							CHANGE_BLIP_SPRITE(Party_ico, BLIP_WEAPONS);//текстура иконки на радаре
							CHANGE_BLIP_SCALE(Party_ico, 1.1); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//иконка на радаре называние в истории карты "Ammu-Nation"
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "LAW2_15", 5500, 1);//~g~Go to Ammu-Nation.
							textID = 1;
						}

						if ((!IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (textID == 1) && (in_car == 0))
						{
							in_car = 1;
							// вернись в машину
							PRINT_STRING_IN_STRING("string", "IN_VEH", 5500, 1);//~g~Hey! Get back in the vehicle!
							REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_CAR(car1, &lance_car);
							CHANGE_BLIP_SPRITE(lance_car, BLIP_OBJECTIVE);//текстура иконки на радаре
							CHANGE_BLIP_COLOUR(lance_car, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(lance_car, "NE_CAR");//иконка на радаре "Связной"
							CHANGE_BLIP_SCALE(lance_car, 0.6); // масштаб иконки на радаре
						}
						else if ((IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (textID == 1) && (in_car == 1))
						{
							in_car = 0;
							// езжай в оружейный магазин
							PRINT_STRING_IN_STRING("string", "LAW2_15", 5500, 1);//~g~Go to Ammu-Nation.
							REMOVE_BLIP(lance_car);//Удаляем иконку на радаре
							ADD_BLIP_FOR_COORD(369.825, -949.315, 4.43197, &Party_ico);
							CHANGE_BLIP_SPRITE(Party_ico, BLIP_WEAPONS);//текстура иконки на радаре
							CHANGE_BLIP_SCALE(Party_ico, 1.1); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//иконка на радаре называние в истории карты "Ammu-Nation"
						}

						if (IS_CHAR_IN_CAR(GetPlayerPed(), car1))
						{
							DRAW_CHECKPOINT( 379.082, -948.858, 4.217, 2.5, 246, 151, 255);//создание чекпойнт на координатах и его цвет
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 379.082, -948.858, 4.217, &PlayR);//проверка "игрок на координатах"
							if (( PlayR < 2.1) && (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
							{
								ABORT_SCRIPTED_CONVERSATION( 0 );
								//подсказки Ammu-Nation
								REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
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
								POINT_CAM_AT_COORD	( camera, 369.507, -948.653, 5.431); // куда смотрит камера
								SET_CAM_POS			( camera, 379.696, -946.602, 6.501 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );
								DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
								SETTIMERA( 0 );
								help = 0;
								// текстс подсказки 1
								PRINT_HELP_FOREVER("LAW3_11"); //Stand in the ~q~pink marker~w~ to view the weapons on offer.

								while(true)
								{
									WAIT(0);
									if ((IS_GAME_KEYBOARD_KEY_PRESSED(GAME_KEY_ESC)) || (help == 69) || (IS_GAME_KEYBOARD_KEY_PRESSED(57)) || (IS_GAME_KEYBOARD_KEY_PRESSED(42)) || (IS_GAME_KEYBOARD_KEY_PRESSED(54)) ||(IS_GAME_KEYBOARD_KEY_PRESSED(28)))
									{

										help = 99;
										break;
									}
									if ((TIMERA() > 3500) && (help == 0))
									{
										// текстс подсказки 2
										PRINT_HELP_FOREVER("LAW3_12"); //You can select weapons by pressing ~h~left~w~ or ~h~right~w~ on the ~h~directional button.
										POINT_CAM_AT_COORD	( camera, 369.387, -955.835, 7.097); // куда смотрит камера
										SET_CAM_POS			( camera, 370.659, -945.036, 7.113 );//расположение камеры
										SETTIMERA( 0 );
										help = 1;
									}
									else if ((TIMERA() > 3500) && (help == 1))
									{
										// текстс подсказки 3
										PRINT_HELP_FOREVER("LAW3_13"); //If you have enough cash you can buy weapons by pressing the ~h~~k~~PED_SPRINT~ ~w~button.
										POINT_CAM_AT_COORD	( camera, 367.628, -956.467, 7.645); // куда смотрит камера
										SET_CAM_POS			( camera, 372.485, -945.471, 6.522 );//расположение камеры
										SETTIMERA( 0 );
										help = 2;
									}
									else if ((TIMERA() > 3500) && (help == 2))
									{
										// текстс подсказки 4
										PRINT_HELP_FOREVER("LAW3_14"); //You can exit the shop by pressing the ~h~~k~~VEHICLE_ENTER_EXIT~ ~w~button.
										POINT_CAM_AT_COORD	( camera, 372.263, -950.477, 4.784); // куда смотрит камера
										SET_CAM_POS			( camera, 366.303, -942.803, 7.469 );//расположение камеры
										SETTIMERA( 0 );
										help = 3;
									}
									else if ((TIMERA() > 3500) && (help == 3))
									{
										// текстс подсказки 5
										PRINT_HELP_FOREVER("HELP46"); //There are eight different types of weapon.
										POINT_CAM_AT_COORD	( camera, 369.387, -955.835, 7.097); // куда смотрит камера
										SET_CAM_POS			( camera, 370.659, -945.036, 7.113 );//расположение камеры
										SETTIMERA( 0 );
										help = 4;
									}
									else if ((TIMERA() > 3500) && (help == 4))
									{
										// текстс подсказки 6
										PRINT_HELP_FOREVER("HELP47"); //You can carry one of each type of weapon at a time - one type of pistol, one type of shotgun.
										POINT_CAM_AT_COORD	( camera, 367.628, -956.467, 7.645); // куда смотрит камера
										SET_CAM_POS			( camera, 372.485, -945.471, 6.522 );//расположение камеры
										SETTIMERA( 0 );
										help = 5;
									}
									else if ((TIMERA() > 3500) && (help == 5))
									{
										help = 69;
									}
								}
								//убираем камеру
								DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
								while(true)
								{
									WAIT(0);
									if (IS_SCREEN_FADED_OUT())
									{
										break;
									}
								}
								CLEAR_HELP(); // удаляем текст подсказки
								SET_CAM_BEHIND_PED( GetPlayerPed() );
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								DESTROY_CAM( camera );
								SET_WIDESCREEN_BORDERS( 0 );
								DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

								PRINT_STRING_IN_STRING("string", "LAW2_10", 5500, 1);//~g~Drive back to the hotel.
								REMOVE_BLIP(lance_car);//Удаляем иконку на радаре
								ADD_BLIP_FOR_COORD(671.379, -747.318, 4.727, &Party_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
								CHANGE_BLIP_COLOUR(Party_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(Party_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//иконка на радаре называние в истории карты "hotel"

								in_car = 0;
								break;
							}
						}

						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (!IS_CHAR_SITTING_IN_ANY_CAR(ped5))//если Ланс вышел из машины то убиваем его
						{
							skip = 1;// переменная пропуска
							PRINT_STRING_IN_STRING("string", "COK2_26", 5500, 1);//~r~You killed Lance!
							EXPLODE_CHAR_HEAD(ped5);
							break;
						}
						else if ((IS_CHAR_DEAD(ped5)) || (IS_CHAR_INJURED(ped5)))//если Ланс мёртв
						{
							skip = 1;// переменная пропуска
							PRINT_STRING_IN_STRING("string", "COK2_26", 5500, 1);//~r~You killed Lance!
							EXPLODE_CHAR_HEAD(ped5);
							break;
						}
					}
				}
				//------------------ шестая часть миссии ------------------
				if (skip == 0)
				{
					while (TRUE)
					{
						// отель
						WAIT(0);
						if ((!IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (textID == 1) && (in_car == 0))
						{
							in_car = 1;
							// вернись в машину
							PRINT_STRING_IN_STRING("string", "IN_VEH", 5500, 1);//~g~Hey! Get back in the vehicle!
							REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_CAR(car1, &lance_car);
							CHANGE_BLIP_SPRITE(lance_car, BLIP_OBJECTIVE);//текстура иконки на радаре
							CHANGE_BLIP_COLOUR(lance_car, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(lance_car, "NE_CAR");//иконка на радаре "Связной"
							CHANGE_BLIP_SCALE(lance_car, 0.6); // масштаб иконки на радаре
						}
						else if ((IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (textID == 1) && (in_car == 1))
						{
							in_car = 0;
							// езжай в оружейный магазин
							PRINT_STRING_IN_STRING("string", "LAW2_10", 5500, 1);//~g~Drive back to the hotel.
							REMOVE_BLIP(lance_car);//Удаляем иконку на радаре
							ADD_BLIP_FOR_COORD(671.379, -747.318, 4.727, &Party_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(Party_ico, BLIP_OBJECTIVE);//текстура иконки на радаре
							CHANGE_BLIP_COLOUR(Party_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(Party_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_POINT");//иконка на радаре называние в истории карты "hotel"
						}

						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 653.863, -795.02, 1.962, 703.863, -695.02, 26.962, 0 )) && (IS_CHAR_IN_CAR(GetPlayerPed(), car1)))
						{
							// затемнение
							REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
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
							SET_CAR_DENSITY_MULTIPLIER(0);// отключаем пути
							CLEAR_AREA_OF_CARS( 680.758, -755.964, 1.154, 100.0 );

							// запускаем пути приезда
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 2994, 0.0, 0.008, -0.128);// запускаем пути приезда

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 674.017, -740.841, 6.473); // куда смотрит камера
							SET_CAM_POS			( camera, 670.527, -752.394, 5.354 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
							CLEAR_AREA(674.2433, -750.8853, 4.501233, 6.5, 0);//очещаем зону загрузки


							SetTime(3000);
							TASK_LEAVE_CAR(GetPlayerPed(), car1);// высаживаем Томми
							SetTime(3000);

							// смена ракурса камеры
							POINT_CAM_AT_COORD	( camera, 675.293, -747.194, 5.183 ); // куда смотрит камера
							SET_CAM_POS			( camera, 673.211, -737.637, 8.129 );//расположение камеры

							// анимация пересадки Ланса
							REQUEST_ANIMS( "veh@low" );//загружаем файл с анимацией
							while (!HAVE_ANIMS_LOADED( "veh@low" )) WAIT(0);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "shuffle_seat_ps", "veh@low", 1.0, 0, 0, 0, 1, -1 );//Воиспроизвидение анимации на педе
							SetTime(1500);

							// проигрываем диалог
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R1_BK", "LAW2_5", 0, 0);//I'm going to go see what I can dig up. I'll be watching you, Tommy.
							START_SCRIPT_CONVERSATION(1, 1);
							SetTime(4200);

							// смена ракурса камеры
							CLEAR_PRINTS();
							POINT_CAM_AT_COORD	( camera, 676.609, -746.077, 4.005 ); // куда смотрит камера
							SET_CAM_POS			( camera, 674.922, -722.211, 7.108 );//расположение камеры

							// запускаем пути уезда
							STOP_PLAYBACK_RECORDED_CAR(car1);
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 2995, 0.0, 0.008, -0.128);// запускаем пути уезда
							SetTime(5800);
							STOP_PLAYBACK_RECORDED_CAR(car1);
							SET_CHAR_COORDINATES(ped5, 19.147, -5.867, 12.732);// перемещаем педа

							//убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							SET_CAR_DENSITY_MULTIPLIER(1);// активируем пути

							skip = 2;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							break;
						}
						else if (!IS_CHAR_SITTING_IN_ANY_CAR(ped5))//если Ланс вышел из машины то убиваем его
						{
							PRINT_STRING_IN_STRING("string", "COK2_26", 5500, 1);//~r~You killed Lance!
							EXPLODE_CHAR_HEAD(ped5);
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped5)) || (IS_CHAR_INJURED(ped5)))//если Ланс мёртв
						{
							PRINT_STRING_IN_STRING("string", "COK2_26", 5500, 1);//~r~You killed Lance!
							EXPLODE_CHAR_HEAD(ped5);
							skip = 1;
							break;
						}
					}
				}


				ABORT_SCRIPTED_CONVERSATION( 0 );
				REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(lance_car);//Удаляем иконку на радаре

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(trubka);

				// выгружвем педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет

				// выгружвем машину
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&trubka_1);

				// выгружвем модепутили
				REMOVE_CAR_RECORDING( 2994 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 2995 ); // выгружаем пути транспорта

				//удаляем мобыльный телефон тут
				REMOVE_PICKUP(mob_phone);
				DELETE_OBJECT( &trubka_1 );

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_LAW_2" );//Back Alley Brawl
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(200, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +200 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 200);
					G_LAWYER = 3;
					G_MAIN_CALL = 1;
					autosave = 1;
				}
				G_ONMISSION = 0;
				blip_on = 0;
			}
		}
//============================== Jury Fury ======================================
		else if ((G_ONMISSION == 0) && (G_LAWYER == 3))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(552.217, -293.87, 4.356, &lawyer_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(lawyer_ico, BLIP_ROMAN);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(lawyer_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(lawyer_ico, "NE_LAWYER");//иконка на радаре называние в истории карты "Адвокат"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 552.217, -293.87, 4.356, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 552.217, -293.87, 4.356, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("LAW_3", 15000, CUTSCENE_LAWYER);
				skip = 0; // переменная пропуска
				help = 0;
				car1_des = 0;
				car2_des = 0;
				car2_des2 = 0;
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(110.6, -824.2, 9.6, 327.9);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(lawyer_ico);//Удаляем иконку на радаре
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

				SET_CHAR_COORDINATES(GetPlayerPed(), 552.036, -293.714, 4.766);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 52.894);
				Car car1, car2, car3, car4;
				Ped ped1, ped2, ped3, ped4, ped5, ped6;
				Pickup sweap_1, sweap_2;
				uint car1_HP, car2_HP, ped2_HP, ped3_HP;
				uint dialogID;
				Cam camera;

				uint PedM1 = MODEL_M_M_GTRI_HI_01;// Присяжный 1
				uint PedM2 = MODEL_M_M_BUSINESS_03;// Присяжный 2
				uint PedM3 = MODEL_F_M_PJERSEY_01;// Собиседник Присяжныого 2
				uint PedM4 = MODEL_M_M_SWEEPER;// Сбитый прохожий
				uint PedM5 = MODEL_M_M_GRU2_HI_02;// Водитель драндулета
				uint PedM6 = MODEL_IG_TUNA;// Водитель грузовика

				uint CarM1 = MODEL_SENTINEL;// Сентинейл
				uint CarM2 = MODEL_ADMIRAL;// Адмирал
				uint CarM3 = MODEL_MARBELLA;// Драндулет
				uint CarM4 = MODEL_FXT;// Грузовик

				// грузим модели
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);

				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);

				REQUEST_MODEL(CarM3);
				while (!HAS_MODEL_LOADED(CarM3)) WAIT(100);

				REQUEST_MODEL(CarM4);
				while (!HAS_MODEL_LOADED(CarM4)) WAIT(100);

				REQUEST_MODEL(PedM1);// Присяжный 1
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(PedM2);// Присяжный 2
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(PedM3);// Собиседник Присяжныого 2
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(PedM4);// Сбитый прохожий
				while (!HAS_MODEL_LOADED(PedM4));////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(PedM5);// Водитель драндулета
				while (!HAS_MODEL_LOADED(PedM5));////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(PedM6);// Водитель грузовика
				while (!HAS_MODEL_LOADED(PedM6));////проверка "пед загрузился" если нет то начанаем с начало

				// создаём авто
				CREATE_CAR(CarM1, 968.689, 749.632, 9.099, &car1, TRUE);// Сентинейл
				CREATE_CAR(CarM2, 618.481, -500.791, 5.058, &car2, TRUE);// Адмирал
				CREATE_CAR(CarM3, 297.061, -779.882, 5.019, &car3, TRUE);// Драндулет
				CREATE_CAR(CarM4, 283.846, -780.803, 5.019, &car4, TRUE);// Грузовик
				SET_CAR_HEADING(car1, -91.702);
				SET_CAR_HEADING(car2, 261.36);

				// закрываем машины для игрока
				LOCK_CAR_DOORS(car1, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car2, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car4, 3); //блокируем двери автомобиля для игрока

				// создаём Педов
				CREATE_CHAR (26, PedM1, 290.473, -785.685, 5.19, &ped1, TRUE);// Присяжный 1
				CREATE_CHAR (26, PedM2, 623.574, -493.928, 5.386, &ped2, TRUE);// Присяжный 2
				CREATE_CHAR (26, PedM3, 623.574, -493.021, 5.386, &ped3, TRUE);// Cобиседник Присяжныого 2
				CREATE_CHAR (26, PedM4, 549.677, -288.081, 4.686, &ped4, TRUE);// Сбитый прохожий
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM5, &ped5);// Водитель драндулета
				CREATE_CHAR_INSIDE_CAR(car4, 1, PedM6, &ped6);// Водитель грузовика
				SET_CHAR_HEADING(ped3, 172.928);
				SET_CHAR_HEADING(ped4, 43.279);
				SET_CHAR_HEALTH(ped2, 1000);
				SET_CHAR_HEALTH(ped3, 1000);

				SET_CHAR_RELATIONSHIP_GROUP(ped2, 0);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 0);
				SET_CHAR_RELATIONSHIP(ped2, 5, 24);
				SET_CHAR_RELATIONSHIP(ped3, 5, 24);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped4, 1);

				// грузим пути драндулета
				REQUEST_CAR_RECORDING( 2996 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 2996 )) WAIT(0);

				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 40);//устанавливаем время

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "LAW_3", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("law_3");
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

				// камера на сбитие прохожего
				CLEAR_AREA(549.677, -288.081, 4.686, 80.5, 1);//очещаем зону загрузки
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, 550.738, -288.656, 5.308); // куда смотрит камера
				SET_CAM_POS			( camera, 540.301, -286.913, 7.878 );//расположение камеры
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_CAM_FOV( camera, 45.0 );
				SET_WIDESCREEN_BORDERS( 1 );

				SetTime(1000);
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R14_XF", "", 0, 0);//
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				// проигрвыаем пути
				SetTime(1000);
				START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 2996, 0.0, 0.0, 0.0);
				SetTime(1000);
				SETTIMERA( 0 );

				// машина сбивает педа
				while (TRUE)
				{
					WAIT(0);
					if ((TIMERA() > 3000) || (IS_CHAR_TOUCHING_VEHICLE(ped4, car3))) //или если машина задела педа
					{
						EXPLODE_CHAR_HEAD(ped4);
						STOP_PLAYBACK_RECORDED_CAR(car3);
						break;
					}
				}
				// получаем координаты педа
				GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
				GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &PedZ);
				CREATE_PICKUP_ROTATE(w_hammer, 3, 1, PedX, PedY, PedZ, -87.532, -108.556, 8.524, &sweap_1);// создаём биту 
				CREATE_PICKUP_ROTATE(w_bat, 3, 1, 625.035, -491.01, 5.062, 169.82, -14.625, 4.35, &sweap_2);// создаём биту 

				SetTime(2000);
				// меняем ракурс на биту
				POINT_CAM_AT_COORD	( camera, 551.371, -288.083, 4.596); // куда смотрит камера
				SET_CAM_POS			( camera, 543.173, -296.107, 6.183 );//расположение камеры
				PRINT_STRING_IN_STRING("string", "LAW3_24", 5500, 1);//~g~That hammer would be useful.
				SetTime(4000);

				//убираем камеру
				SET_CAM_BEHIND_PED( GetPlayerPed() );
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				DESTROY_CAM( camera );
				SET_WIDESCREEN_BORDERS( 0 );
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				TASK_LEAVE_CAR(ped5, car3);// пед выходит из драндулета

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//выгружаем модель машины
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель машины

				// выгружаем пути драндулета
				REMOVE_CAR_RECORDING( 2996 ); // выгружаем пути транспорта

				// создаём меркеры над машиной
				ADD_BLIP_FOR_CAR(car1, &jury_car1);
				CHANGE_BLIP_SPRITE(jury_car1, BLIP_OBJECTIVE);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(jury_car1, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(jury_car1, "NE_CAR");//иконка на радаре "Связной"
				CHANGE_BLIP_SCALE(jury_car1, 0.6); // масштаб иконки на радаре

				// создаём меркеры над педом
				ADD_BLIP_FOR_CHAR(ped2, &jury_car2);
				CHANGE_BLIP_SPRITE(jury_car2, BLIP_OBJECTIVE);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(jury_car2, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(jury_car2, "NE_CAR");//иконка на радаре "Связной"
				CHANGE_BLIP_SCALE(jury_car2, 0.6); // масштаб иконки на радаре

				// проигрываем монолог
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R1_BL", "LAW3_7", 0, 0);//~g~Go and intimidate the two jurors, but DON'T kill them!
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();
				//SET_CURRENT_MOVIE( "audio/law3_24" );


				// мигиние радара
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(250);
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(250);
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(250);
				DISPLAY_RADAR(0);
				SetTime(250);
				DISPLAY_RADAR(1);
				SetTime(1250);

				//------------------ Первая часть миссии ------------------
				while (TRUE)
				{
					WAIT(0);
					GET_CAR_HEALTH(car1, &car1_HP);
					GET_CAR_HEALTH(car2, &car2_HP);
					GET_CHAR_HEALTH(ped2, &ped2_HP);
					GET_CHAR_HEALTH(ped3, &ped3_HP);

					// если игрок на координатах пишем "разбейте машину"
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 951.636, 711.794, 6.106, 986.436, 771.794, 21.106, 0 )) && (help == 0))
					{
						PRINT_STRING_IN_STRING("string", "LAW3_20", 5500, 1);//~g~Smash up the Juror's car!
						help = 1;
					}

					// если машина 1 разбита
					if ((car1_HP < 400) && (car1_des == 0))
					{

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
						REMOVE_BLIP(jury_car1);//Удаляем иконку на радаре
						SET_CHAR_COORDINATES(ped1, 984.8, 727.5, 8.539);// перемещаем педа
						SET_CHAR_HEADING(ped1, 46.4);

						// камера тут
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 984.691, 727.433, 10.274); // куда смотрит камера
						SET_CAM_POS			( camera, 986.126, 723.922, 10.789 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						// проверка игрок в машине
						if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
						{
							SET_CHAR_COORDINATES(GetPlayerPed(), 958.737, 745.489, 9.099);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), -15.013);
							WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 975.0, 740.8, 8.539);// высаживаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), -148.514);
						}
						else
						{
							SET_CHAR_COORDINATES(GetPlayerPed(), 975.0, 740.8, 8.539);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), -148.514);
						}

						// игрок идёт к педу
						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 978.492, 736.038, 9.391, 2, -2);//Игрок идёт в пойнт
						SetTime(250);

						// проигрывается диалог
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R1_BM", "LAW3_21", 0, 0);//I can't believe this is happening!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						GENERATE_RANDOM_INT_IN_RANGE( 1, 12, &dialogID);
						if ((dialogID == 1) || (dialogID == 7))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BM_XXX1", "LAW3_1", 0, 0);//Giorgio sends his regards.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
						}
						else if ((dialogID == 2) || (dialogID == 8))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BM_XXX2", "LAW3_2", 0, 0);//Remember, guilty is a dirty word.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
						}
						else if ((dialogID == 3) || (dialogID == 9))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BN", "LAW3_3", 0, 0);//Innocent until I say otherwise.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
						}
						else if ((dialogID == 4) || (dialogID == 10))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BN_XXX1", "LAW3_4", 0, 0);//You know he's not guilty.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
						}
						else if ((dialogID == 5) || (dialogID == 11))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BN_XXX2", "LAW3_5", 0, 0);//You remember Giorgio? You remember he's innocent.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
						}
						else if ((dialogID == 6) || (dialogID == 12))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BO", "LAW3_6", 0, 0);//Not guilty, understand? Good.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
						}

						// меняем ракурс
						POINT_CAM_AT_COORD	( camera, 980.528, 733.934, 10.859); // куда смотрит камера
						SET_CAM_POS			( camera, 981.683, 736.051, 10.808 );//расположение камеры

						// пед убегает
						TASK_GO_STRAIGHT_TO_COORD(ped1, 968.7, 710.3, 9.391, 4, -2);//Присяжный бежит
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R1_BP", " ", 0, 0);//Кричит
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();
						//SetTime(2500);

						//убираем камеру
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

						// убераем педа
						SET_CHAR_COORDINATES(ped1, 290.473, -785.685, 5.19);// перемещаем педа
						TASK_GO_STRAIGHT_TO_COORD(ped1, 290.473, -785.685, 5.19, 4, -2);//Присяжный бежит
						car1_des = 1;
					}

					// если машина 2 разбита
					if ((car2_HP < 400) && (car2_des == 0))
					{
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
						REMOVE_BLIP(jury_car2);//Удаляем иконку на радаре
						SET_CHAR_COORDINATES(ped2, 634.284, -489.079, 4.451);// перемещаем педа
						SET_CHAR_HEADING(ped2, 155.144);

						// камера тут
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 631.786, -494.704, 5.021); // куда смотрит камера
						SET_CAM_POS			( camera, 636.534, -487.072, 6.687 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						// проверка игрок в машине
						if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
						{
							SET_CHAR_COORDINATES(GetPlayerPed(), 626.771, -498.732, 5.058);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 105.498);
							WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 631.758, -496.799, 4.451);// высаживаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), -7.47);
						}
						else
						{
							SET_CHAR_COORDINATES(GetPlayerPed(), 631.758, -496.799, 4.451);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), -7.47);
						}

						// игрок идёт к педу
						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 632.752, -493.506, 5.386, 2, -2);//Игрок идёт в пойнт
						SetTime(250);

						// запускаем диалог
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R1_BQ", "NE_LAW3_1", 0, 0);//Man. my car!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R1_BN", "LAW3_3", 0, 0);//Innocent until I say otherwise.
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						// меняем ракурс
						POINT_CAM_AT_COORD	( camera, 632.427, -490.956, 5.862); // куда смотрит камера
						SET_CAM_POS			( camera, 632.131, -491.902, 5.988 );//расположение камеры

						// пед убегает
						TASK_GO_STRAIGHT_TO_COORD(ped2, 638.477, -471.28, 5.386, 4, -2);//Присяжный бежит
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R1_BQ_XXX1", " ", 0, 0);//Кричит
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();
						//SetTime(3000);

						//убираем камеру
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

						// убераем педа
						SET_CHAR_COORDINATES(ped2, 292.473, -783.685, 5.19);// перемещаем педа
						TASK_GO_STRAIGHT_TO_COORD(ped2, 292.473, -783.685, 5.19, 4, -2);//Присяжный бежит
						car2_des = 1;
					}

					// если пед 1 или пед 2 пострадали 
					if (((ped2_HP < 990) && (car2_des == 0)) || ((ped3_HP < 990) && (car2_des == 0)))
					{
						if (IS_CAR_IN_AREA_3D(car2, 615.574, -502.26, 3.946, 621.074, -499.26, 6.946, 0))
						{
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
							SET_CHAR_COORDINATES(ped2, 620.943, -497.315, 4.451);// перемещаем педа
							SET_CHAR_HEADING(ped2, 166.505);
							SET_CAR_HEALTH(car2, 1000);
							SET_CHAR_COORDINATES(GetPlayerPed(), 626.771, -498.732, 5.058);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 105.498);

							SET_CAR_COORDINATES(car2, 618.48, -500.79, 5.058);// перемещаем машину
							SET_CAR_HEADING(car2, 261.36);

							// грузим пути
							REQUEST_CAR_RECORDING( 2997 );// грузим пути адмирала
							while (!HAS_CAR_RECORDING_BEEN_LOADED( 2997 )) WAIT(0);
							REQUEST_CAR_RECORDING( 2998 );// грузим пути грузовика
							while (!HAS_CAR_RECORDING_BEEN_LOADED( 2998 )) WAIT(0);

							REQUEST_ANIMS( "ped" );//загружаем файл с анимацией
							while (!HAVE_ANIMS_LOADED( "ped" )) WAIT(0);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped3, "duck_cower", "ped", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
							PANIC_SCREAM(ped3);
							TASK_ENTER_CAR_AS_DRIVER(ped2, car2, -1);// пед садится в машину

							// камера тут
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 618.985, -503.321, 5.338); // куда смотрит камера
							SET_CAM_POS			( camera, 625.491, -496.804, 7.461 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана

							// пед бежит к машине
							SETTIMERA( 0 );
							while(true)
							{
								WAIT(0);
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped2))
								{
									SetTime(1000);
									break;
								}
								else if (TIMERA() > 3000)
								{
									WARP_CHAR_INTO_CAR(ped2, car2);// телепартируем педа за руль
									break;
								}
							}
							// очещаем зону
							CLEAR_AREA(640.931, -483.029, 4.07, 5.5, 1);//очещаем зону загрузки
							CLEAR_AREA(639.585, -489.304, 4.07, 5.5, 1);//очещаем зону загрузки
							CLEAR_AREA(638.272, -495.001, 4.07, 5.5, 1);//очещаем зону загрузки
							CLEAR_AREA(636.958, -500.699, 4.07, 5.5, 1);//очещаем зону загрузки
							CLEAR_AREA(635.644, -506.396, 4.07, 5.5, 1);//очещаем зону загрузки
							CLEAR_AREA(634.367, -512.435, 4.07, 5.5, 1);//очещаем зону загрузки

							// запускаем пути
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 2997, 0.0, 0.374, -0.164);
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car4, 2998, 0.0, 0.142, -0.693);

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, 626.665, -503.788, 4.24); // куда смотрит камера
							SET_CAM_POS			( camera, 611.616, -498.071, 6.533 );//расположение камеры
							CLOSE_ALL_CAR_DOORS(car2);// закрываем двери
							SetTime(4000);

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, 633.956, -505.002, 5.19); // куда смотрит камера
							SET_CAM_POS			( camera, 633.633, -496.148, 8.663 );//расположение камеры
							SetTime(4000);

							// убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							PRINT_STRING_IN_STRING("string", "LAW3_9", 5500, 1);//~g~Smash up the Juror's car to get him out!

							//останавливаем пути
							STOP_PLAYBACK_RECORDED_CAR(car2);
							STOP_PLAYBACK_RECORDED_CAR(car4);
							REMOVE_CAR_RECORDING( 2997 ); // выгружаем пути транспорта
							REMOVE_CAR_RECORDING( 2998 ); // выгружаем пути транспорта
							EXTINGUISH_CAR_FIRE(car2);
							EXTINGUISH_CAR_FIRE(car4);
							SET_CAR_HEALTH(car2, 1000);

							// запускаем цыкл разбития машины
							while(true)
							{
								WAIT(0);
								GET_CAR_HEALTH(car2, &car2_HP);
								//DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.9, "CP_TIME_NOZERO", car2_HP);
								if ((car2_HP < 900) && (car2_des2 == 0))
								{
									// проигрываем монолог педа
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R1_BQ_XXX2", "NE_LAW3_2", 0, 0);//Hey man, my car! Leave my damn car alone, man!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									SET_CAR_HEALTH(car2, 900);
									car2_des2 = 1;
								}
								else if ((car2_HP < 700) && (car2_des2 == 1))
								{
									// проигрываем монолог педа
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R1_BR", "NE_LAW3_3", 0, 0);//Oh, please God! Someone help me!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									SET_CAR_HEALTH(car2, 700);
									car2_des2 = 2;
								}
								else if ((car2_HP < 600) && (car2_des2 == 2))
								{
									// проигрываем монолог педа
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BS", "NE_LAW3_4", 0, 0);//Yo man, I still got payment to make on this!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									SET_CAR_HEALTH(car2, 600);
									car2_des2 = 3;
								}
								else if ((car2_HP < 500) && (car2_des2 == 3))
								{
									// проигрываем монолог педа
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R1_BS_XXX1", "NE_LAW3_5", 0, 0);//Okay, okay, man! I get the message!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									SET_CAR_HEALTH(car2, 1);
									car2_des2 = 4;
								}
								else if (((car2_HP < 5) && (car2_des2 == 4)) || (!IS_CHAR_SITTING_IN_ANY_CAR(ped2)))
								{
									if (IS_CHAR_SITTING_IN_ANY_CAR(ped2))
									{
										TASK_LEAVE_CAR(ped2, car2);// пед выходит из машины
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
									SetTime(1000);
									if (IS_CHAR_SITTING_IN_ANY_CAR(ped2))
									{
										WARP_CHAR_FROM_CAR_TO_COORD(ped2, 633.551, -503.916, 4.451);// высаживаем педа
										SET_CHAR_HEADING(ped2, -168.322);
									}
									else
									{
										SET_CHAR_COORDINATES(ped2, 633.551, -503.916, 4.451);// перемещаем педа
										SET_CHAR_HEADING(ped2, -168.322);
									}
									SET_CAR_COORDINATES(car2, 632.11, -505.21, 5.058);// перемещаем машину
									SET_CAR_HEADING(car2, 209.23);

									// проверка игрок в машине
									if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
									{
										SET_CHAR_COORDINATES(GetPlayerPed(), 626.771, -498.732, 5.058);// перемещаем игрока
										SET_CHAR_HEADING(GetPlayerPed(), 105.498);
										WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 633.158, -507.921, 4.304);// высаживаем игрока
										SET_CHAR_HEADING(GetPlayerPed(), -11.288);
									}
									else
									{
										SET_CHAR_COORDINATES(GetPlayerPed(), 633.158, -507.921, 4.304);// перемещаем игрока
										SET_CHAR_HEADING(GetPlayerPed(), -11.288);
									}

									SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
									REMOVE_BLIP(jury_car2);//Удаляем иконку на радаре

									// ставим камеру
									CREATE_CAM( 14, &camera );
									POINT_CAM_AT_COORD	( camera, 631.877, -506.294, 4.671); // куда смотрит камера
									SET_CAM_POS			( camera, 634.686, -497.097, 6.668 );//расположение камеры
									SET_CAM_ACTIVE( camera, 1 );
									SET_CAM_PROPAGATE( camera, 1 );
									ACTIVATE_SCRIPTED_CAMS(1, 1);
									SET_CAM_FOV( camera, 45.0 );
									SET_WIDESCREEN_BORDERS( 1 );
									DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
									SetTime(250);

									// проигрывается диалог
									REMOVE_BLIP(jury_car2);//Удаляем иконку на радаре
									GENERATE_RANDOM_INT_IN_RANGE( 1, 12, &dialogID);
									if ((dialogID == 1) || (dialogID == 7))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R1_BM_XXX1", "LAW3_1", 0, 0);//Giorgio sends his regards.
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
									}
									else if ((dialogID == 2) || (dialogID == 8))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R1_BM_XXX2", "LAW3_2", 0, 0);//Remember, guilty is a dirty word.
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
									}
									else if ((dialogID == 3) || (dialogID == 9))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R1_BN", "LAW3_3", 0, 0);//Innocent until I say otherwise.
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
									}
									else if ((dialogID == 4) || (dialogID == 10))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R1_BN_XXX1", "LAW3_4", 0, 0);//You know he's not guilty.
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
									}
									else if ((dialogID == 5) || (dialogID == 11))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R1_BN_XXX2", "LAW3_5", 0, 0);//You remember Giorgio? You remember he's innocent.
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
									}
									else if ((dialogID == 6) || (dialogID == 12))
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R1_BO", "LAW3_6", 0, 0);//Not guilty, understand? Good.
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
									}

									// меняем ракурс
									POINT_CAM_AT_COORD	( camera, 632.427, -490.956, 5.862); // куда смотрит камера
									SET_CAM_POS			( camera, 632.131, -491.902, 5.988 );//расположение камеры
									SET_CHAR_COORDINATES(ped2, 634.284, -489.079, 4.451);// перемещаем педа
									SET_CHAR_HEADING(ped2, -28.13);

									// пед убегает
									TASK_GO_STRAIGHT_TO_COORD(ped2, 638.477, -471.28, 5.386, 4, -2);//Присяжный бежит
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R1_BQ_XXX1", " ", 0, 0);//Кричит
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									//SetTime(2500);

									//убираем камеру
									SET_CAM_BEHIND_PED( GetPlayerPed() );
									ACTIVATE_SCRIPTED_CAMS( 0, 0 );
									DESTROY_CAM( camera );
									SET_WIDESCREEN_BORDERS( 0 );
									SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

									// убераем педа
									SET_CHAR_COORDINATES(ped2, 292.473, -783.685, 5.19);// перемещаем педа
									TASK_GO_STRAIGHT_TO_COORD(ped2, 292.473, -783.685, 5.19, 4, -2);//Присяжный бежит
									car2_des2 = 5;
									car2_des = 1;
									break;
								}
								else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_INJURED(ped1)) || (IS_CHAR_DEAD(ped2)) || (IS_CHAR_INJURED(ped2)))//если Присяжный мёртв
								{
									EXPLODE_CHAR_HEAD(ped1);
									EXPLODE_CHAR_HEAD(ped2);
									break;
								}
								else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 581.95, -543.68, 1.652, 671.95, -453.68, 25.1, 0 ))// если игрок покинул заону
								{
									skip = 1;
									break;
								}
							}
							SetTime(2500);
						}
						else
						{
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
							REMOVE_BLIP(jury_car2);//Удаляем иконку на радаре
							SET_CHAR_COORDINATES(ped2, 624.583, -494.482, 4.451);// перемещаем педа
							SET_CHAR_HEADING(ped2, -111.38);

							REQUEST_ANIMS( "ped" );//загружаем файл с анимацией
							while (!HAVE_ANIMS_LOADED( "ped" )) WAIT(0);

							// камера тут
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 630.144, -495.907, 4.983); // куда смотрит камера
							SET_CAM_POS			( camera, 622.264, -492.284, 6.136 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							// проверка игрок в машине
							if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
								SET_CHAR_COORDINATES(GetPlayerPed(), 626.771, -498.732, 5.058);// перемещаем игрока
								SET_CHAR_HEADING(GetPlayerPed(), 105.498);
								WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 628.82, -495.402, 4.451);// высаживаем игрока
								SET_CHAR_HEADING(GetPlayerPed(), 68.201);
							}
							else
							{
								SET_CHAR_COORDINATES(GetPlayerPed(), 628.82, -495.402, 4.451);// перемещаем игрока
								SET_CHAR_HEADING(GetPlayerPed(), 68.201);
							}

							// игрок идёт к педу
							DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped3, "duck_cower", "ped", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
							PANIC_SCREAM(ped3);
							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 626.697, -494.893, 5.386, 2, -2);//Игрок идёт в пойнт
							SetTime(250);

							// запускаем диалог
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BN", "LAW3_3", 0, 0);//Innocent until I say otherwise.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BS_XXX1", "NE_LAW3_5", 0, 0);//Okay, okay, man! I get the message!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, 632.427, -490.956, 5.862); // куда смотрит камера
							SET_CAM_POS			( camera, 632.131, -491.902, 5.988 );//расположение камеры
							SET_CHAR_COORDINATES(ped2, 634.284, -489.079, 4.451);// перемещаем педа
							SET_CHAR_HEADING(ped2, -15.774);

							// пед убегает
							TASK_GO_STRAIGHT_TO_COORD(ped2, 638.477, -471.28, 5.386, 4, -2);//Присяжный бежит
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R1_BQ_XXX1", " ", 0, 0);//Кричит
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							//SetTime(3000);

							//убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							// убераем педа
							SET_CHAR_COORDINATES(ped2, 292.473, -783.685, 5.19);// перемещаем педа
							TASK_GO_STRAIGHT_TO_COORD(ped2, 292.473, -783.685, 5.19, 4, -2);//Присяжный бежит
						}
						car2_des = 1;
					}

					if ((car1_des == 1) && (car2_des == 1))// если машина 1 и 2 разбиты
					{
						skip = 2;
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;
						break;
					}
					else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_INJURED(ped1)) || (IS_CHAR_DEAD(ped2)) || (IS_CHAR_INJURED(ped2)))//если Присяжный мёртв
					{
						skip = 1;
						PRINT_STRING_IN_STRING("string", "LAW3_8", 5500, 1);//~r~You killed a Juror!
						EXPLODE_CHAR_HEAD(ped1);
						EXPLODE_CHAR_HEAD(ped2);
						break;
					}
					else if (skip == 1)
					{
						PRINT_STRING_IN_STRING("string", "NE_LAW3_6", 5500, 1);//~r~The Juror called the police!
						break;
					}
				}

				ABORT_SCRIPTED_CONVERSATION( 0 );
				REMOVE_BLIP(jury_car1);//Удаляем иконку на радаре
				REMOVE_BLIP(jury_car2);//Удаляем иконку на радаре
				REMOVE_PICKUP(sweap_1);// выгружаем биту
				REMOVE_PICKUP(sweap_2);// выгружаем биту

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM6);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//выгружаем модель машины

				// выгружвем педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет

				// выгружвем машину
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_LAW_3" );//Jury Fury
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(400, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +400 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 400);
					G_LAWYER = 4;
					autosave = 1;
				}

				G_ONMISSION = 0;
				blip_on = 0;
			}
		}
//============================== Riot ======================================
		else if ((G_ONMISSION == 0) && (G_LAWYER == 4))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(552.217, -293.87, 4.356, &lawyer_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(lawyer_ico, BLIP_ROMAN);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(lawyer_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(lawyer_ico, "NE_LAWYER");//иконка на радаре называние в истории карты "Адвокат"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 552.217, -293.87, 4.356, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 552.217, -293.87, 4.356, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("LAW_4", 15000, CUTSCENE_LAWYER);
				skip = 0; // переменная пропуска
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(110.6, -824.2, 9.6, 327.9);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(lawyer_ico);//Удаляем иконку на радаре
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

				SET_CHAR_COORDINATES(GetPlayerPed(), 552.036, -293.714, 4.766);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 52.894);
				// SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 1, 0);
				SET_MAX_WANTED_LEVEL(0);

				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 40);//устанавливаем время
				
				//------------ катсцена тут ----------------
				LOAD_ADDITIONAL_TEXT( "LAW_4", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("law_4");
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

				// иконка бунта
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				ADD_BLIP_FOR_COORD(731.166, 210.147, 6.354, &Riot);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(Riot, BLIP_OBJECTIVE);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(Riot, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(Riot, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Riot, "NE_POINT");//иконка на радаре называние в истории карты ""

				// иконка магазина одежды
				ADD_BLIP_FOR_COORD(527.259, -601.747, 4.341, &Party_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(Party_ico, BLIP_CLOTHES_SHOP);//текстура иконки на радаре
				CHANGE_BLIP_COLOUR(Party_ico, 0);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(Party_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Party_ico, "NE_SHOP");//иконка на радаре называние в истории карты ""

				SetTime(1000);
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R14_WB", "", 0, 0);//mono_8
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				PRINT_STRING_IN_STRING("string", "LAW1_1", 5500, 1);//~g~Go get some new threads from Rafael's clothes shop.
				SetTime(1000);

				Car car1, car2, car3;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20, ped21, ped22, ped23, ped24;
				Object barrel_1, barrel_2, barrel_3, vorota;
				Cam camera, camera2, camera3;

				// запрашиваем модели грузовиков
				uint PedM1 = MODEL_M_M_SECURITYMAN;// Охранник
				uint PedM2 = MODEL_IG_TUNA;// Рабочий 1
				uint PedM3 = MODEL_IG_VINNY_SPAZ;// Рабочий 2
				uint CarM1 = MODEL_FXT;// Грузовик
				uint barrel = barrel4;// бочка
				uint vorotaM = vc_electricgate; //ворота
				uint ped4_HP, ped5_HP, ped6_HP, ped7_HP, ped8_HP, ped9_HP, ped10_HP, ped11_HP, ped12_HP, ped13_HP;
				uint ped14_HP, ped15_HP, ped16_HP, ped17_HP, ped18_HP, ped19_HP, ped20_HP, ped21_HP, ped22_HP, ped23_HP, ped24_HP;
				uint AudID;

				// загружаем модели
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);

				REQUEST_MODEL(PedM1);// Охранник
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(PedM2);// Рабочий 1
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(PedM3);// Рабочий 2
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(barrel);// бочки
				while (!HAS_MODEL_LOADED(barrel)) WAIT(0);
				
				REQUEST_MODEL(vorotaM);// ворота
				while (!HAS_MODEL_LOADED(vorotaM)) WAIT(0);

				// создаём ворота
				CREATE_OBJECT_NO_OFFSET(vorotaM, 731.196, 219.32, 6.078, &vorota, TRUE);
				SET_OBJECT_DYNAMIC(vorota, 0);
				SET_OBJECT_INVINCIBLE(vorota, 1);
				FREEZE_OBJECT_POSITION(vorota, 1);

				// создаём бочки
				CREATE_OBJECT_NO_OFFSET(barrel, 716.957, 222.311, 6.386, &barrel_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 747.284, 231.978, 6.386, &barrel_2, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 744.208, 221.089, 6.386, &barrel_3, TRUE);

				// создаём машины
				CREATE_CAR(CarM1, 744.774, 223.702, 6.354, &car1, TRUE);
				SET_CAR_HEADING(car1, 89.421);
				CREATE_CAR(CarM1, 744.774, 229.793, 6.354, &car2, TRUE);
				SET_CAR_HEADING(car2, 89.421);
				CREATE_CAR(CarM1, 719.85, 230.833, 6.354, &car3, TRUE);
				SET_CAR_HEADING(car3, -90.579);

				// создаём Охранников
				CREATE_CHAR (26, PedM1, 737.717, 234.072, 6.354, &ped1, TRUE);// создаём педа
				CREATE_CHAR (26, PedM1, 731.529, 221.274, 6.354, &ped2, TRUE);// создаём педа
				CREATE_CHAR (26, PedM1, 735.911, 221.376, 6.354, &ped3, TRUE);// создаём педа

				// создаём Рабочих 1
				CREATE_CHAR (26, PedM2, 726.113, 216.401, 6.354, &ped4, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, 737.019, 211.426, 6.354, &ped5, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, 740.795, 216.692, 6.354, &ped6, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, 731.361, 214.974, 6.354, &ped7, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, 726.873, 210.934, 6.354, &ped8, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, 735.413, 214.706, 6.354, &ped9, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, 741.986, 213.132, 6.354, &ped10, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, 739.796, 209.501, 6.354, &ped11, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, 730.041, 212.085, 6.354, &ped12, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, 736.509, 217.536, 6.354, &ped13, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, 731.682, 209.003, 6.354, &ped14, TRUE);// создаём педа

				// создаём Рабочих 2
				CREATE_CHAR (26, PedM3, 723.234, 212.966, 6.354, &ped15, TRUE);// создаём педа
				CREATE_CHAR (26, PedM3, 728.926, 208.093, 6.354, &ped16, TRUE);// создаём педа
				CREATE_CHAR (26, PedM3, 726.826, 213.711, 6.354, &ped17, TRUE);// создаём педа
				CREATE_CHAR (26, PedM3, 729.155, 216.309, 6.354, &ped18, TRUE);// создаём педа
				CREATE_CHAR (26, PedM3, 732.908, 217.047, 6.354, &ped19, TRUE);// создаём педа
				CREATE_CHAR (26, PedM3, 733.013, 212.894, 6.354, &ped20, TRUE);// создаём педа
				CREATE_CHAR (26, PedM3, 734.284, 210.596, 6.354, &ped21, TRUE);// создаём педа
				CREATE_CHAR (26, PedM3, 736.751, 207.754, 6.354, &ped22, TRUE);// создаём педа
				CREATE_CHAR (26, PedM3, 738.673, 215.755, 6.354, &ped23, TRUE);// создаём педа
				CREATE_CHAR (26, PedM3, 741.959, 210.859, 6.354, &ped24, TRUE);// создаём педа

				// поворачиваем педов
				SET_CHAR_HEADING(ped1, -175.01);
				SET_CHAR_HEADING(ped2, -170.01);
				SET_CHAR_HEADING(ped3, 175.01);

				SET_CHAR_HEADING(ped4, -40.0);
				SET_CHAR_HEADING(ped5, -10.0);
				SET_CHAR_HEADING(ped6, 0.01);
				SET_CHAR_HEADING(ped7, 0.01);
				SET_CHAR_HEADING(ped8, 0.01);
				SET_CHAR_HEADING(ped9, 15.0);
				SET_CHAR_HEADING(ped10, 15.0);
				SET_CHAR_HEADING(ped11, 15.0);
				SET_CHAR_HEADING(ped12, -20.0);
				SET_CHAR_HEADING(ped13, 10.0);
				SET_CHAR_HEADING(ped14, -30.0);

				SET_CHAR_HEADING(ped15, -20.0);
				SET_CHAR_HEADING(ped16, -15.0);
				SET_CHAR_HEADING(ped17, -30.0);
				SET_CHAR_HEADING(ped18, -20.0);
				SET_CHAR_HEADING(ped19, -15.0);
				SET_CHAR_HEADING(ped20, 0.01);
				SET_CHAR_HEADING(ped21, 0.01);
				SET_CHAR_HEADING(ped22, 0.01);
				SET_CHAR_HEADING(ped23, 0.01);
				SET_CHAR_HEADING(ped24, 0.01);

				// настройки "Свой-чужой" тут
				int dm, cdm;
				LOAD_CHAR_DECISION_MAKER(2, &dm); // 4
				LOAD_COMBAT_DECISION_MAKER(3, &cdm); // 3 10
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				SET_SENSE_RANGE(ped1, 0.01);
				SET_SENSE_RANGE(ped2, 0.01);
				SET_SENSE_RANGE(ped3, 0.01);
				SET_SENSE_RANGE(ped4, 0.01);
				SET_SENSE_RANGE(ped5, 0.01);
				SET_SENSE_RANGE(ped6, 0.01);
				SET_SENSE_RANGE(ped7, 0.01);
				SET_SENSE_RANGE(ped8, 0.01);
				SET_SENSE_RANGE(ped9, 0.01);
				SET_SENSE_RANGE(ped10, 0.01);
				SET_SENSE_RANGE(ped11, 0.01);
				SET_SENSE_RANGE(ped12, 0.01);
				SET_SENSE_RANGE(ped13, 0.01);
				SET_SENSE_RANGE(ped14, 0.01);
				SET_SENSE_RANGE(ped15, 0.01);
				SET_SENSE_RANGE(ped16, 0.01);
				SET_SENSE_RANGE(ped17, 0.01);
				SET_SENSE_RANGE(ped18, 0.01);
				SET_SENSE_RANGE(ped19, 0.01);
				SET_SENSE_RANGE(ped20, 0.01);
				SET_SENSE_RANGE(ped21, 0.01);
				SET_SENSE_RANGE(ped22, 0.01);
				SET_SENSE_RANGE(ped23, 0.01);
				SET_SENSE_RANGE(ped24, 0.01);

				SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
				SET_CHAR_RELATIONSHIP_GROUP(ped4, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped5, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped6, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped7, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped8, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped9, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped10, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped11, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped12, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped13, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped14, 6);
				SET_CHAR_RELATIONSHIP_GROUP(ped15, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped16, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped17, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped18, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped19, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped20, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped21, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped22, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped23, 7);
				SET_CHAR_RELATIONSHIP_GROUP(ped24, 7);

				SET_CHAR_DECISION_MAKER(ped1, dm);
				SET_CHAR_DECISION_MAKER(ped2, dm);
				SET_CHAR_DECISION_MAKER(ped3, dm);
				SET_CHAR_DECISION_MAKER(ped4, dm);
				SET_CHAR_DECISION_MAKER(ped5, dm);
				SET_CHAR_DECISION_MAKER(ped6, dm);
				SET_CHAR_DECISION_MAKER(ped7, dm);
				SET_CHAR_DECISION_MAKER(ped8, dm);
				SET_CHAR_DECISION_MAKER(ped9, dm);
				SET_CHAR_DECISION_MAKER(ped10, dm);
				SET_CHAR_DECISION_MAKER(ped11, dm);
				SET_CHAR_DECISION_MAKER(ped12, dm);
				SET_CHAR_DECISION_MAKER(ped13, dm);
				SET_CHAR_DECISION_MAKER(ped14, dm);
				SET_CHAR_DECISION_MAKER(ped15, dm);
				SET_CHAR_DECISION_MAKER(ped16, dm);
				SET_CHAR_DECISION_MAKER(ped17, dm);
				SET_CHAR_DECISION_MAKER(ped18, dm);
				SET_CHAR_DECISION_MAKER(ped19, dm);
				SET_CHAR_DECISION_MAKER(ped20, dm);
				SET_CHAR_DECISION_MAKER(ped21, dm);
				SET_CHAR_DECISION_MAKER(ped22, dm);
				SET_CHAR_DECISION_MAKER(ped23, dm);
				SET_CHAR_DECISION_MAKER(ped24, dm);

				SET_COMBAT_DECISION_MAKER(ped1, cdm);
				SET_COMBAT_DECISION_MAKER(ped2, cdm);
				SET_COMBAT_DECISION_MAKER(ped3, cdm);
				SET_COMBAT_DECISION_MAKER(ped4, cdm);
				SET_COMBAT_DECISION_MAKER(ped5, cdm);
				SET_COMBAT_DECISION_MAKER(ped6, cdm);
				SET_COMBAT_DECISION_MAKER(ped7, cdm);
				SET_COMBAT_DECISION_MAKER(ped8, cdm);
				SET_COMBAT_DECISION_MAKER(ped9, cdm);
				SET_COMBAT_DECISION_MAKER(ped10, cdm);
				SET_COMBAT_DECISION_MAKER(ped11, cdm);
				SET_COMBAT_DECISION_MAKER(ped12, cdm);
				SET_COMBAT_DECISION_MAKER(ped13, cdm);
				SET_COMBAT_DECISION_MAKER(ped14, cdm);
				SET_COMBAT_DECISION_MAKER(ped15, cdm);
				SET_COMBAT_DECISION_MAKER(ped16, cdm);
				SET_COMBAT_DECISION_MAKER(ped17, cdm);
				SET_COMBAT_DECISION_MAKER(ped18, cdm);
				SET_COMBAT_DECISION_MAKER(ped19, cdm);
				SET_COMBAT_DECISION_MAKER(ped20, cdm);
				SET_COMBAT_DECISION_MAKER(ped21, cdm);
				SET_COMBAT_DECISION_MAKER(ped22, cdm);
				SET_COMBAT_DECISION_MAKER(ped23, cdm);
				SET_COMBAT_DECISION_MAKER(ped24, cdm);

				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped9, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped21, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped22, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped23, 0);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped24, 0);

				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped1, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped2, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped3, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped4, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped5, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped6, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped7, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped8, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped9, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped10, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped11, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped12, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped13, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped14, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped15, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped16, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped17, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped18, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped19, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped20, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped21, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped22, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped23, 1);
				SET_PED_PATH_MAY_USE_CLIMBOVERS(ped24, 1);

				SET_PED_DONT_DO_EVASIVE_DIVES(ped1, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped2, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped3, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped4, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped5, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped6, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped7, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped8, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped9, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped10, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped11, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped12, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped13, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped14, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped15, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped16, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped17, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped18, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped19, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped20, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped21, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped22, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped23, 1);
				SET_PED_DONT_DO_EVASIVE_DIVES(ped24, 1);

				SET_CHAR_WILL_USE_COVER(ped1, 0);
				SET_CHAR_WILL_USE_COVER(ped2, 0);
				SET_CHAR_WILL_USE_COVER(ped3, 0);
				SET_CHAR_WILL_USE_COVER(ped4, 0);
				SET_CHAR_WILL_USE_COVER(ped5, 0);
				SET_CHAR_WILL_USE_COVER(ped6, 0);
				SET_CHAR_WILL_USE_COVER(ped7, 0);
				SET_CHAR_WILL_USE_COVER(ped8, 0);
				SET_CHAR_WILL_USE_COVER(ped9, 0);
				SET_CHAR_WILL_USE_COVER(ped10, 0);
				SET_CHAR_WILL_USE_COVER(ped11, 0);
				SET_CHAR_WILL_USE_COVER(ped12, 0);
				SET_CHAR_WILL_USE_COVER(ped13, 0);
				SET_CHAR_WILL_USE_COVER(ped14, 0);
				SET_CHAR_WILL_USE_COVER(ped15, 0);
				SET_CHAR_WILL_USE_COVER(ped16, 0);
				SET_CHAR_WILL_USE_COVER(ped17, 0);
				SET_CHAR_WILL_USE_COVER(ped18, 0);
				SET_CHAR_WILL_USE_COVER(ped19, 0);
				SET_CHAR_WILL_USE_COVER(ped20, 0);
				SET_CHAR_WILL_USE_COVER(ped21, 0);
				SET_CHAR_WILL_USE_COVER(ped22, 0);
				SET_CHAR_WILL_USE_COVER(ped23, 0);
				SET_CHAR_WILL_USE_COVER(ped24, 0);

				UpdateWeaponOfPed(ped1, WEAPON_PISTOL);
				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_PISTOL, TRUE);
				UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_24);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_EPISODIC_24, TRUE);
				UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_24);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_24, TRUE);

				// загружаем анимацию
				REQUEST_ANIMS( "amb@bum_a" );//загружаем файл с анимацией
				while (!HAVE_ANIMS_LOADED( "amb@bum_a" ));//если файл с анимацией не загружен начанаем с начало
				REQUEST_ANIMS( "amb@nightclub_ext" );//загружаем файл с анимацией
				while (!HAVE_ANIMS_LOADED( "amb@nightclub_ext" ));//если файл с анимацией не загружен начанаем с начало
				REQUEST_ANIMS( "amb@payphone" );//загружаем файл с анимацией
				while (!HAVE_ANIMS_LOADED( "amb@payphone" ));//если файл с анимацией не загружен начанаем с начало
				REQUEST_ANIMS( "ped" );//загружаем файл с анимацией
				while (!HAVE_ANIMS_LOADED( "ped" ));//если файл с анимацией не загружен начанаем с начало

				// воспроизводим анимацию
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "stand_rant_b", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped8, "stand_rant_a", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped13, "angryman", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped20, "street_argue_a", "amb@nightclub_ext", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				WAIT(200);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped4, "street_argue_a", "amb@nightclub_ext", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped17, "stand_rant_b", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped21, "angryman", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped15, "stand_rant_a", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				WAIT(200);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped9, "stand_rant_b", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped23, "stand_rant_a", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped18, "angryman", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped24, "street_argue_a", "amb@nightclub_ext", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				WAIT(200);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "stand_rant_a", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped22, "stand_rant_b", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped12, "street_argue_a", "amb@nightclub_ext", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "angryman", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				WAIT(200);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped10, "angryman", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped11, "street_argue_a", "amb@nightclub_ext", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped14, "stand_rant_b", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped16, "stand_rant_a", "amb@bum_a", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				WAIT(200);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped19, "street_argue_a", "amb@nightclub_ext", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе

				sound = 0;
				soundID = 1;
				help = 0;
				riotID = 0;
				ped4_ID = 0;
				ped5_ID = 0;
				ped6_ID = 0;
				ped7_ID = 0;
				ped8_ID = 0;
				ped9_ID = 0;
				ped10_ID = 0;
				ped11_ID = 0;
				ped12_ID = 0;
				ped13_ID = 0;
				ped14_ID = 0;
				ped15_ID = 0;
				ped16_ID = 0;
				ped17_ID = 0;
				ped18_ID = 0;
				ped19_ID = 0;
				ped20_ID = 0;
				ped21_ID = 0;
				ped22_ID = 0;
				ped23_ID = 0;
				ped24_ID = 0;
				riotON = 0;
				skin = 0;
				textID = 0;
				car1_des = 0;
				car2_des = 0;
				car2_des2 = 0;
				vorotaX = 731.196;

				// воспроизводим звук
				while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/M1_FIRST_DATE" )))
				{
					 WAIT(0);
				}
				AudID = GET_SOUND_ID();
				PLAY_SOUND_FROM_POSITION(AudID, "SCRIPT_MISSION_M1_FIRST_DATE_LAUGHTER_01", 731.166, 210.147, 6.354);

				while (TRUE)
				{
					WAIT(0);

					// чекпойнт смены одежды
					if (skin == 0)
					{
						DRAW_CHECKPOINT( 527.259, -601.747, 4.341, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 527.259, -601.747, 4.341, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							skin = 1;
							REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							// камера сверху
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 530.273, -604.626, 4.197 ); // куда смотрит камера
							SET_CAM_POS			( camera, 522.552, -596.448, 16.414 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 529.623, -603.946, 4.766, 2, -2);// Томми идёт в двери
							SetTime(1000);

							DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							// переодивание	
							SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 2, 0);// куртка

							SET_CHAR_COORDINATES(GetPlayerPed(), 528.664, -602.916, 4.766);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 52.9);
							SetTime(200);
							DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана

							// подём камеры
							CREATE_CAM( 3, &camera2 );
							CREATE_CAM( 14, &camera3 );
							POINT_CAM_AT_COORD	( camera, 528.442, -602.798, 4.56 ); // куда смотрит камера
							SET_CAM_POS			( camera, 527.141, -601.545, 5.08 );//расположение камеры
							POINT_CAM_AT_COORD	( camera3, 528.442, -602.798, 5.839 ); // куда смотрит камера
							SET_CAM_POS			( camera3, 527.141, -601.545, 5.08 );//расположение камеры
							SET_CAM_INTERP_STYLE_CORE( camera2, camera, camera3, 3500, 0 ); //перемещение камеры от игрока на точку указанную в координатах "SET_CAM_POS(camera, X, Y, Z)" 
							SET_CAM_ACTIVE( camera2, 1 );
							SET_CAM_PROPAGATE( camera2, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_WIDESCREEN_BORDERS( 1 ); //отключаем инетрфейс
							SetTime(5000);

							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							DESTROY_CAM( camera2 );
							DESTROY_CAM( camera3 );
							SET_WIDESCREEN_BORDERS( 0 ); //возвращаем инетрфейс
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							PRINT_STRING_IN_STRING("string", "NE_LAW4_1", 5500, 1);//~g~Drive to the site of the workers' strike.
						}
					}

					GET_CHAR_HEALTH(ped4, &ped4_HP);
					GET_CHAR_HEALTH(ped5, &ped5_HP);
					GET_CHAR_HEALTH(ped6, &ped6_HP);
					GET_CHAR_HEALTH(ped7, &ped7_HP);
					GET_CHAR_HEALTH(ped8, &ped8_HP);
					GET_CHAR_HEALTH(ped9, &ped9_HP);
					GET_CHAR_HEALTH(ped10, &ped10_HP);
					GET_CHAR_HEALTH(ped11, &ped11_HP);
					GET_CHAR_HEALTH(ped12, &ped12_HP);
					GET_CHAR_HEALTH(ped13, &ped13_HP);
					GET_CHAR_HEALTH(ped14, &ped14_HP);
					GET_CHAR_HEALTH(ped15, &ped15_HP);
					GET_CHAR_HEALTH(ped16, &ped16_HP);
					GET_CHAR_HEALTH(ped17, &ped17_HP);
					GET_CHAR_HEALTH(ped18, &ped18_HP);
					GET_CHAR_HEALTH(ped19, &ped19_HP);
					GET_CHAR_HEALTH(ped20, &ped20_HP);
					GET_CHAR_HEALTH(ped21, &ped21_HP);
					GET_CHAR_HEALTH(ped22, &ped22_HP);
					GET_CHAR_HEALTH(ped23, &ped23_HP);
					GET_CHAR_HEALTH(ped24, &ped24_HP);

					// чекпойнт бунта
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 731.166, 210.147, 6.354, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 40.0) && (sound == 0))
					{
						SETTIMERB( 0 );
						sound = 1;
					}
					else if (( PlayR > 40.0) && (sound == 1))
					{
						ABORT_SCRIPTED_CONVERSATION( 0 );
						sound = 0;
					}
					if (sound == 1)
					{
						if (soundID == 1)
						{
							if (TIMERB() > 7000)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R1_DA", " ", 0, 0);//
								START_SCRIPT_CONVERSATION(1, 1);
								SETTIMERB( 0 );
								soundID = 2;
							}
						}
						else if (soundID == 2)
						{
							if (TIMERB() > 7000)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R1_EA", " ", 0, 0);//
								START_SCRIPT_CONVERSATION(1, 1);
								SETTIMERB( 0 );
								soundID = 1;
							}
						}
					}
					if (( PlayR < 25.0) && (textID == 0))
					{
						// начните драку с несколькими рабочими
						PRINT_STRING_IN_STRING("string", "LAW4_13", 5500, 1);//~g~Start fighting with at least 4 workers to get a riot started.
						textID = 1;
					}

					if ((ped4_HP < 195) && (ped4_ID == 0)) ped4_ID = 1, riotID += 1;
					else if ((ped5_HP < 195) && (ped5_ID == 0)) ped5_ID = 1, riotID += 1;
					else if ((ped6_HP < 195) && (ped6_ID == 0)) ped6_ID = 1, riotID += 1;
					else if ((ped7_HP < 195) && (ped7_ID == 0)) ped7_ID = 1, riotID += 1;
					else if ((ped8_HP < 195) && (ped8_ID == 0)) ped8_ID = 1, riotID += 1;
					else if ((ped9_HP < 195) && (ped9_ID == 0)) ped9_ID = 1, riotID += 1;
					else if ((ped10_HP < 195) && (ped10_ID == 0)) ped10_ID = 1, riotID += 1;
					else if ((ped11_HP < 195) && (ped11_ID == 0)) ped11_ID = 1, riotID += 1;
					else if ((ped12_HP < 195) && (ped12_ID == 0)) ped12_ID = 1, riotID += 1;
					else if ((ped13_HP < 195) && (ped13_ID == 0)) ped13_ID = 1, riotID += 1;
					else if ((ped14_HP < 195) && (ped14_ID == 0)) ped14_ID = 1, riotID += 1;
					else if ((ped15_HP < 195) && (ped15_ID == 0)) ped15_ID = 1, riotID += 1;
					else if ((ped16_HP < 195) && (ped16_ID == 0)) ped16_ID = 1, riotID += 1;
					else if ((ped17_HP < 195) && (ped17_ID == 0)) ped17_ID = 1, riotID += 1;
					else if ((ped18_HP < 195) && (ped18_ID == 0)) ped18_ID = 1, riotID += 1;
					else if ((ped19_HP < 195) && (ped19_ID == 0)) ped19_ID = 1, riotID += 1;
					else if ((ped20_HP < 195) && (ped20_ID == 0)) ped20_ID = 1, riotID += 1;
					else if ((ped21_HP < 195) && (ped21_ID == 0)) ped21_ID = 1, riotID += 1;
					else if ((ped22_HP < 195) && (ped22_ID == 0)) ped22_ID = 1, riotID += 1;
					else if ((ped23_HP < 195) && (ped23_ID == 0)) ped23_ID = 1, riotID += 1;
					else if ((ped24_HP < 195) && (ped24_ID == 0)) ped24_ID = 1, riotID += 1;

					if (((riotID > 3) && (riotON == 0)) || ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 716.176, 219.828, 5.218, 748.176, 235.758, 15.218, 0 )) && (riotON == 0)))
					{
						riotON = 1;
						REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
						REMOVE_BLIP(Riot);//Удаляем иконку на радаре

						if (riotID > 3)
						{
							// камера на ворота
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 733.589, 220.041, 6.696 ); // куда смотрит камера
							SET_CAM_POS			( camera, 728.927, 224.124, 7.243);//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);

							ABORT_SCRIPTED_CONVERSATION( 0 );
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BS_XXX2", "LAW4_5", 0, 0);//Sticks out, boys! Let's crack some commie skulls!
							START_SCRIPT_CONVERSATION(1, 1);
							soundID = 3;

							// открываем ворота
							while (true)
							{
								WAIT( 0 );
								vorotaX += 0.06;
								SET_OBJECT_COORDINATES(vorota, vorotaX, 219.32, 6.078);
								if (vorotaX > 737.4)
								{
									break;
								}
							}
							SetSpeech();

							TASK_GO_STRAIGHT_TO_COORD(ped2, 732.049, 218.421, 6.354, 2, -2);// Пед идёт в пойнт
							TASK_GO_STRAIGHT_TO_COORD(ped3, 736.048, 218.378, 6.354, 2, -2);// Пед идёт в пойнт
							SetTime(2000);

							// убираем камиру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							DESTROY_CAM( camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
						}

						SET_OBJECT_COORDINATES(vorota, 737.8, 219.32, 6.078);
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped4, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped8, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped9, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped10, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped11, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped12, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped13, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped14, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped15, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped16, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped17, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped18, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped19, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped20, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped21, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped22, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped23, "nm_melee", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped24, "fuck_u", "ped", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе

						// бунт тут
						SET_SENSE_RANGE(ped1, 15.01);
						SET_SENSE_RANGE(ped2, 10.01);
						SET_SENSE_RANGE(ped3, 10.01);
						SET_SENSE_RANGE(ped4, 6.01);
						SET_SENSE_RANGE(ped5, 6.01);
						SET_SENSE_RANGE(ped6, 6.01);
						SET_SENSE_RANGE(ped7, 6.01);
						SET_SENSE_RANGE(ped8, 6.01);
						SET_SENSE_RANGE(ped9, 6.01);
						SET_SENSE_RANGE(ped10, 6.01);
						SET_SENSE_RANGE(ped11, 6.01);
						SET_SENSE_RANGE(ped12, 6.01);
						SET_SENSE_RANGE(ped13, 6.01);
						SET_SENSE_RANGE(ped14, 6.01);
						SET_SENSE_RANGE(ped15, 6.01);
						SET_SENSE_RANGE(ped16, 6.01);
						SET_SENSE_RANGE(ped17, 6.01);
						SET_SENSE_RANGE(ped18, 6.01);
						SET_SENSE_RANGE(ped19, 6.01);
						SET_SENSE_RANGE(ped20, 6.01);
						SET_SENSE_RANGE(ped21, 6.01);
						SET_SENSE_RANGE(ped22, 6.01);
						SET_SENSE_RANGE(ped23, 6.01);
						SET_SENSE_RANGE(ped24, 6.01);

						if (skin == 1)
						{
							SET_CHAR_RELATIONSHIP_GROUP(ped15, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped16, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped17, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped18, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped19, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped20, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped21, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped22, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped23, 0);
							SET_CHAR_RELATIONSHIP_GROUP(ped24, 0);
						}
						TASK_COMBAT(ped2, ped7);
						TASK_COMBAT(ped3, ped19);
						TASK_COMBAT(ped4, ped15);
						TASK_COMBAT(ped5, ped16);
						TASK_COMBAT(ped6, ped17);
						TASK_COMBAT(ped7, ped18);
						TASK_COMBAT(ped15, ped4);
						TASK_COMBAT(ped16, ped5);
						TASK_COMBAT(ped17, ped6);
						TASK_COMBAT(ped18, ped7);
						TASK_COMBAT(ped1, GetPlayerPed());
						TASK_COMBAT(ped2, ped7);
						TASK_COMBAT(ped3, ped19);
						PRINT_STRING_IN_STRING("string", "LAW4_14", 5500, 1);//~g~Destroy the vans in the compound!

						ADD_BLIP_FOR_CAR(car1, &lance_car);
						CHANGE_BLIP_SPRITE(lance_car, BLIP_OBJECTIVE);//текстура иконки на радаре
						CHANGE_BLIP_COLOUR(lance_car, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(lance_car, "MO_TARGET");//иконка на радаре "Связной"
						CHANGE_BLIP_SCALE(lance_car, 0.6); // масштаб иконки на радаре

						ADD_BLIP_FOR_CAR(car2, &jury_car1);
						CHANGE_BLIP_SPRITE(jury_car1, BLIP_OBJECTIVE);//текстура иконки на радареjury_car1
						CHANGE_BLIP_COLOUR(jury_car1, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(jury_car1, "MO_TARGET");//иконка на радаре "Связной"
						CHANGE_BLIP_SCALE(jury_car1, 0.6); // масштаб иконки на радаре

						ADD_BLIP_FOR_CAR(car3, &jury_car2);
						CHANGE_BLIP_SPRITE(jury_car2, BLIP_OBJECTIVE);//текстура иконки на радареjury_car1
						CHANGE_BLIP_COLOUR(jury_car2, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(jury_car2, "MO_TARGET");//иконка на радаре "Связной"
						CHANGE_BLIP_SCALE(jury_car2, 0.6); // масштаб иконки на радаре
						skin = 1;
					}

					if ((riotON == 1) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 716.176, 219.828, 5.218, 748.176, 235.758, 15.218, 0 )))
					{
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 737.311, 233.431, 6.871 ); // куда смотрит камера
						SET_CAM_POS			( camera, 730.188, 225.704, 9.987 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SetTime(4000);

						// меняем ракурс
						POINT_CAM_AT_COORD	( camera, 748.657, 232.445, 5.295 ); // куда смотрит камера
						SET_CAM_POS			( camera, 732.313, 232.226, 8.498 );//расположение камеры
						SetTime(4000);

						// убираем камиру
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						DESTROY_CAM( camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

						TASK_COMBAT(ped1, GetPlayerPed());
						TASK_COMBAT(ped2, ped7);
						TASK_COMBAT(ped3, ped19);
						TASK_COMBAT(ped4, ped15);
						TASK_COMBAT(ped5, ped16);
						TASK_COMBAT(ped6, ped17);
						TASK_COMBAT(ped7, ped18);
						TASK_COMBAT(ped15, ped4);
						TASK_COMBAT(ped16, ped5);
						TASK_COMBAT(ped17, ped6);
						TASK_COMBAT(ped18, ped7);
						riotON = 2;
					}
					
					if ((IS_CAR_DEAD(car1)) && (car1_des == 0))
					{
						REMOVE_BLIP(lance_car);//Удаляем иконку на радаре
						car1_des = 1;
					}
					if ((IS_CAR_DEAD(car2)) && (car2_des == 0))
					{
						REMOVE_BLIP(jury_car1);//Удаляем иконку на радаре
						car2_des = 1;
					}
					if ((IS_CAR_DEAD(car3)) && (car2_des2 == 0))
					{
						REMOVE_BLIP(jury_car2);//Удаляем иконку на радаре
						car2_des2 = 1;
					}

					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;
						break;
					}
					else if ((car1_des == 1) && (car2_des == 1) && (car2_des2 == 1))
					{
						WAIT( 500 );
						if ((!IS_CHAR_DEAD(GetPlayerPed())) && (!HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 2;
							break;
						}
						else
						{
							skip = 1;
							break;
						}
					}
				}

				// удаляем звук
				STOP_SOUND(AudID);
				RELEASE_SOUND_ID(AudID);
				AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED();
				SET_MAX_WANTED_LEVEL(6);

				REMOVE_BLIP(Party_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(Riot);//Удаляем иконку на радаре
				REMOVE_BLIP(lance_car);//Удаляем иконку на радаре
				REMOVE_BLIP(jury_car1);//Удаляем иконку на радаре
				REMOVE_BLIP(jury_car2);//Удаляем иконку на радаре

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(barrel);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(vorotaM);//выгружаем модель

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
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped23);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped24);//выгружаем модель педа(в последствии пед изчезнет

				// выгружвем машину
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)

				// удаляем объекты
				DELETE_OBJECT(&barrel_1);
				DELETE_OBJECT(&barrel_2);
				DELETE_OBJECT(&barrel_3);
				DELETE_OBJECT(&vorota);

				// выгружаем бочки и ворота
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&vorota);

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					PRINT_HELP("CLOTH3"); //Coveralls outfit delivered to Tooled Up in The North Point Mall.
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_LAW_4" );//Riot
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(1000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +1000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 1000);
					G_LAWYER = 5;
					G_AVERY = 1;
					autosave = 1;
				}

				G_ONMISSION = 0;
				blip_on = 0;
			}
		}
		else if ((G_ONMISSION == 0) && (G_LAWYER == 5))
		{
			break;
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(lawyer_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}
	}					
}
void main(void)
{
	//THIS_SCRIPT_SHOULD_BE_SAVED();
	if (G_LAWYER < 5)
	{
		LAWYER_1();
	}
	WAIT(200);
	while (TRUE)
	{
		WAIT(10);
	}
	return;
}
