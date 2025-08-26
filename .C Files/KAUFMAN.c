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
#include "cutscenes.h"
#include "fast_travel.h"
float PlayX, PlayY, PlayZ, PlayR, blip_on, skip, textur, text1, text2, time_m, time_s, sound, play, autosave;
float PedX, PedY, PedZ, PedR, taxi_1, taxi_2, taxi_3, touch1, touch2, touch3, engine, res_on, vorotaX, vorotaY;
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
void kaufman(void)
{
	blip_on = 0;
	autosave = 0;
	Blip cabs_ico;
	load_mashin = 0;
	help = 0;
	uint rId9;
	WAIT(1000);
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
//============================== V.I.P. ======================================
		if ((G_ONMISSION == 0) && (G_CABS == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-569.498, 738.454, 5.354, &cabs_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cabs_ico, BLIP_TAXI_RANK);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(cabs_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cabs_ico, "LG_18");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			//DRAW_CHECKPOINT( -569.498, 738.454, 5.354, 2.1, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_CABBY)) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -566.998, 733.454, 4.45, -571.998, 743.454, 12.45, 0 )))
			{
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-1020.8, 191.1, 10.5, 350.0);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(cabs_ico);//Удаляем иконку на радаре
				blip_on = 0;

				Ped ped1, ped2;
				Car car1, car2;
				Cam camera;
				Texture fon, timer;
				Blip ped_ico;

				skip = 0; // переменная пропуска
				text1 = 0;
				text2 = 0;
				time_m = 1;
				time_s = 30;
				sound = 0;
				play = 0;

				int dm, cdm;
				LOAD_CHAR_DECISION_MAKER(2, &dm); // 4
				LOAD_COMBAT_DECISION_MAKER(3, &cdm); // 3 10
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				timer = GET_TEXTURE( textur, "timer_hud" );

				uint CarM1 = MODEL_TAXI;// Такси
				uint PedM1 = MODEL_M_M_TAXIDRIVER;// Таксист
				uint PedM2 = MODEL_M_O_STREET_01;// Пассажир
				uint car_HP;

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(PedM1);// Таксист
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Пассажир
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало

				CREATE_CAR(CarM1, 286.232, -791.79, 5.445, &car1, TRUE);
				LOCK_CAR_DOORS(car1, 3); //блокируем двери автомобиля для игрока
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//создаём педа за рулём автомобиля
				SET_CHAR_COMPONENT_VARIATION(ped1, 1, 0, 0);
				CREATE_CHAR (26, PedM2, 291.032, -785.32, 5.06, &ped2, TRUE);// Пассажир
				SET_CHAR_DECISION_MAKER(ped2, dm);
				SET_COMBAT_DECISION_MAKER(ped2, cdm);

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
				CLEAR_WANTED_LEVEL(GetPlayerIndex());
				SetTime(600);

				// камера сверху
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, -570.081, 737.787, 5.891 ); // куда смотрит камера
				SET_CAM_POS			( camera, -562.707, 743.712, 10.922 );//расположение камеры
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_CAM_FOV( camera, 45.0 );
				SET_WIDESCREEN_BORDERS( 1 );
				SetTime(600);

				// брифинг
				PRINT_BIG("TAXI_1", 5000, 2);//V.I.P.
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R1_BV", "TAX1_1", 0, 0);//Ok, we got a high class fare needs picking up from Starfish island - any takers?
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R1_BV_XXX1", "TAX1_2", 0, 0);//Tommy here, I'll take it!
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				SetTime(500);
				CLEAR_PRINTS();

				//убираем камеру
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				END_CAM_COMMANDS( &camera );
				SET_WIDESCREEN_BORDERS( 0 );
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				SetTime(500);

				ADD_BLIP_FOR_COORD(-143.203, 52.906, 4.974, &cabs_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cabs_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(cabs_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(cabs_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cabs_ico, "NE_POINT");//иконка на радаре называние в истории карты ""
				PRINT_STRING_IN_STRING("string", "TAXW1_1", 5000, 1);//~g~Pick up the V.I.P. on Starfish Island.

				SETTIMERA( 0 );
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
						SET_TEXT_DROPSHADOW(1, 80, 0, 0, 255);;
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
					
					DRAW_CHECKPOINT( -143.203, 52.906, 4.974, 2.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -143.203, 52.906, 4.974, &PlayR);//проверка "игрок на координатах"
					if ( PlayR < 2.1)
					{
						if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_CABBY))
						{
							// посигнальте
							if (text1 == 0)
							{
								PRINT_HELP("NEHELP3");//Press ~INPUT_VEH_HORN~ button to sound horn.
								PRINT_STRING_IN_STRING("string", "HORN", 5000, 1);//~g~Sound the horn.
								text1 = 1;
							}
							if (IS_PLAYER_PRESSING_HORN(0))// проверка "игрок посигналил"
							{
								CLEAR_HELP(); // удаляем текст подсказки

								if (sound == 1)
								{
									STOP_STREAM();
									ENABLE_FRONTEND_RADIO();
								}

								// камера сверху
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, -133.389, 84.425, 9.72 ); // куда смотрит камера
								SET_CAM_POS			( camera, -151.251, 67.174, 6.0 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

								// идёт пассажир
								SET_CHAR_COORDINATES(ped2, -139.74, 86.059, 9.134);// перемещаем игрока
								SET_CHAR_HEADING(ped2, -90.0);
								TASK_GO_STRAIGHT_TO_COORD(ped2, -130.615, 86.059, 9.134, 2, -2);// Пед идёт
								SetTime(5000);

								// меняем ракурс камеры
								POINT_CAM_AT_COORD	( camera, -136.855, 52.543, 4.63 ); // куда смотрит камера
								SET_CAM_POS			( camera, -153.178, 63.934, 8.209 );//расположение камеры

								// идёт пассажир
								SET_CHAR_COORDINATES(ped2, -142.725, 65.634, 5.365);// перемещаем игрока
								SET_CHAR_HEADING(ped2, 180.0);
								TASK_GO_STRAIGHT_TO_COORD(ped2, -142.725, 60.487, 5.365, 2, -2);// Пед идёт

								// подъезжает таксист
								REQUEST_CAR_RECORDING( 3042 );
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3042 )) WAIT(0);
								CLEAR_AREA(-144.496, 58.904, 4.974, 25.0, 1);//очещаем зону загрузки
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3042, 0.0, 0.0, 0.0);
								SetTime(1500);

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R1_BV_XXX2", "TAX1_3", 0, 0);//This is my fare, back off asshole!
								START_SCRIPT_CONVERSATION(1, 1);
								SetTime(2800);
								STOP_PLAYBACK_RECORDED_CAR(car1);
								REMOVE_CAR_RECORDING( 3042 );

								TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, -1, 2);// пед содится к таксисту
								SETTIMERB( 0 );

								while(true)
								{
									WAIT(0);
									if (IS_CHAR_SITTING_IN_ANY_CAR(ped2))
									{
										break;
									}
									else if (TIMERB() > 3000)
									{
										WARP_CHAR_INTO_CAR_AS_PASSENGER(ped2, car1, 2);
										break;
									}
								}

								CLEAR_PRINTS();
								CLOSE_ALL_CAR_DOORS(car1);
								
								//убираем камеру
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								END_CAM_COMMANDS( &camera );
								SET_WIDESCREEN_BORDERS( 0 );
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
								PRINT_STRING_IN_STRING("string", "TAXW1_2", 5000, 1);//~g~Get the V.I.P back! Take the other car out!
								
								REMOVE_BLIP(cabs_ico);//Удаляем иконку на радаре
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -1021.249, -294.609, 8.418, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								
								ADD_BLIP_FOR_COORD(-1021.249, -294.609, 8.418, &cabs_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(cabs_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(cabs_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(cabs_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(cabs_ico, "NE_POINT");//иконка на радаре называние в истории карты ""

								ADD_BLIP_FOR_CHAR(ped2, &ped_ico);
								CHANGE_BLIP_SPRITE(ped_ico, BLIP_DESTINATION);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(ped_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(ped_ico, 0.77999990); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped_ico, "MO_TARGET");//иконка на радаре называние в истории карты

								break;
							}
							text2 = 0;
						}
						else
						{
							if (text2 == 0)
							{
								PRINT_STRING_IN_STRING("string", "TAXW1_5", 5000, 1);//~g~You need to be in a Kaufman cab!
								text2 = 1;
							}
						}
					}
					else
					{
						if (text1 == 1)
						{
							text1 = 0;
						}
						if (text2 == 1)
						{
							text2 = 0;
						}
					}

					// провал миссии
					if ((time_m == 0) && (time_s == 0))
					{
						PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
				}

				// часть 2
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						GET_CAR_HEALTH(car1, &car_HP);
						//DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", car_HP);// секунды

						if ((car_HP < 400) || (IS_CHAR_DEAD(ped1))) // VIP exits the rival taxi when the taxi is damaged enough or if the taxi driver is killed
						{
							GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, PedX, PedY, PedZ, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							TASK_LEAVE_CAR(ped2, car1);
						}
						if (!IS_CHAR_SITTING_IN_ANY_CAR(ped2))
						{
							text2 = 0;
							break;
						}
						// провал миссии
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -1021.249, -294.609, 8.418, &PedR);//проверка "игрок на координатах"
						if ( PedR < 2.1)
						{
							PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
							skip = 1;// переменная пропуска					
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска							PRINT_STRING_IN_STRING("string", "TAXW1_D", 5000, 1);//You scared the V.I.P. client
					
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_INJURED(ped2)))//если игрок мёртв или аврестован
						{
							PRINT_STRING_IN_STRING("string", "TAXW1_3", 5000, 1);//~r~The V.I.P. is dead!
							skip = 1;// переменная пропуска
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
						if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_CABBY))
						{
							GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car2);
							text2 = 0;
							TASK_ENTER_CAR_AS_PASSENGER(ped2, car2, -1, 2);// пед содится к игроку
							SETTIMERB( 0 );
							break;
						}
						else
						{
							if (text2 == 0)
							{
								PRINT_STRING_IN_STRING("string", "TAXW1_5", 5000, 1);//~g~You need to be in a Kaufman cab!
								text2 = 1;
							}
						}
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//???? ????? ???? ??? ??????????
						{
							skip = 1;// 							
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_INJURED(ped2)))//если игрок мёртв или аврестован
						{
							PRINT_STRING_IN_STRING("string", "TAXW1_3", 5000, 1);//~r~The V.I.P. is dead!
							skip = 1;// переменная пропуска
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
						if (play == 0)
						{
							// воспроизводим аудио
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BW", "TAX1_4", 0, 0);//Come on come on, Get in, quick!
							START_SCRIPT_CONVERSATION(1, 1);
							play = 1;
						}
						else if (play == 1)
						{
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								play = 2;
							}
						}

						if (!IS_CHAR_IN_CAR(ped2, car2))
						{
							if ((TIMERB() > 5000) && (!IS_CHAR_GETTING_IN_TO_A_CAR(ped2))) // VIP is tasked to enter the player cabby every 5 seconds, this check is skipped if VIP is mid-entering cabby to avoid the chance of the VIP exiting and failing the mission
							{
								GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
								TASK_GO_STRAIGHT_TO_COORD(ped2, PedX, PedY, PedZ, 2, -2);// Пед идёт
								TASK_ENTER_CAR_AS_PASSENGER(ped2, car2, -1, 2);// пед содится к игроку
								SETTIMERB( 0 );
							}
						}
						else
						{
							SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(ped2, false);
							if (play == 2)
							{
								// таксист атакует игрока
								SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
								SET_CHAR_RELATIONSHIP(ped1, 5, 0);
								SET_SENSE_RANGE(ped1, 2000.0);
								SET_CHAR_WILL_USE_COVER(ped1, 0);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, 1);
								TASK_COMBAT(ped1, GetPlayerPed());
								play = 0;
								break;
							}
						}
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))	  
						{
							skip = 1;							
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_INJURED(ped2)))//если игрок мёртв или аврестован
						{
							PRINT_STRING_IN_STRING("string", "TAXW1_3", 5000, 1);//~r~The V.I.P. is dead!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// часть 5
				if (skip == 0)
				{
					text2 = 0;
					while(true)
					{
						WAIT(0);
						if (play == 0)
						{
							// воспроизводим аудио
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R1_BW_XXX1", "TAX1_5", 0, 0);//Ok, ok! Just don't hurt me!
							START_SCRIPT_CONVERSATION(1, 1);
							REMOVE_BLIP(ped_ico);//Удаляем иконку на радаре
							play = 1;
						}
						else if (play == 1)
						{
							if (!IS_SCRIPTED_CONVERSATION_ONGOING())
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "TAXW1_6", 5000, 1);//~COL_NET_12~Take the V.I.P. to the airport!
								play = 2;
							}
						}

						DRAW_CHECKPOINT( -1021.249, -294.609, 8.418, 2.1, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -1021.249, -294.609, 8.418, &PedR);//проверка "игрок на координатах"
						if ( PedR < 2.0)
						{
							// камера сверху
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -1020.61, -296.039, 9.56 ); // куда смотрит камера
							SET_CAM_POS			( camera, -1039.026, -250.1, 12.843 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							SetTime(2000);

							// меняем ракурс
							WARP_CHAR_FROM_CAR_TO_COORD(ped2, -1028.089, -294.76, 9.075);//телепартируем из катера
							SET_CHAR_HEADING(ped2, 125.0);
							TASK_GO_STRAIGHT_TO_COORD(ped2, -1033.576, -300.022, 9.075, 2, -2);// Пед идёт

							POINT_CAM_AT_COORD	( camera, -1030.517, -297.303, 9.457 ); // куда смотрит камера
							SET_CAM_POS			( camera, -1038.524, -304.516, 12.678 );//расположение камеры
							SetTime(3000);

							// убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							skip = 2;// переменная пропуска
							break;
						}
						if (!IS_CHAR_IN_CAR(GetPlayerPed(), car2))
						{
							if (text2 == 0)
							{
								ADD_BLIP_FOR_CAR(car2, &ped_ico);
								CHANGE_BLIP_SPRITE(ped_ico, BLIP_DESTINATION);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(ped_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(ped_ico, 0.77999990); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped_ico, "NE_CAR");//иконка на радаре называние в истории карты
								PRINT_STRING_IN_STRING("string", "IN_VEH", 5000, 1);//~COL_NET_12~Hey! Get back in the vehicle!
								text2 = 1;
							}
						}
						else
						{
							if (text2 == 1)
							{
								PRINT_STRING_IN_STRING("string", "TAXW1_6", 5000, 1);//~COL_NET_12~Take the V.I.P. to the airport!
								REMOVE_BLIP(ped_ico);//Удаляем иконку на радаре
								text2 = 0;
							}
						}

						if (!IS_CHAR_IN_CAR(ped2, car2))
						{
							EXPLODE_CHAR_HEAD(ped2);
							PRINT_STRING_IN_STRING("string", "TAXW1_3", 5000, 1);//~r~The V.I.P. is dead!
							skip = 1;// переменная пропуска
							break;			 					
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_INJURED(ped2)))//если игрок мёртв или аврестован
						{
							PRINT_STRING_IN_STRING("string", "TAXW1_3", 5000, 1);//~r~The V.I.P. is dead!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// зачещаем скрипт
				WAIT(10);

				REMOVE_BLIP(ped_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(cabs_ico);//Удаляем иконку на радаре

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				
				// выгружаем из памяти транспорт
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				if (car2 != 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				}

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( timer );
				REMOVE_TXD( textur );

				if (sound == 1)
				{
					STOP_STREAM();
					ENABLE_FRONTEND_RADIO();
				}

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_TAXI_1" );//V.I.P.
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(1000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +1000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 1000);
					G_CABS = 2;
					autosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}

//============================== Friendly Rivalry ======================================
		else if ((G_ONMISSION == 0) && (G_CABS == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-569.498, 738.454, 5.354, &cabs_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cabs_ico, BLIP_TAXI_RANK);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(cabs_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cabs_ico, "LG_18");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_CABBY)) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -566.998, 733.454, 4.45, -571.998, 743.454, 12.45, 0 )))
			{
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-1020.8, 191.1, 10.5, 350.0);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(cabs_ico);//Удаляем иконку на радаре
				blip_on = 0;

				Ped ped1, ped2, ped3;
				Car car1, car2, car3;
				Cam camera;
				Pickup sweap_1;
				Blip car1_ico, car2_ico, car3_ico;

				skip = 0; // переменная пропуска
				taxi_1 = 1;
				taxi_2 = 1;
				taxi_3 = 1;
				touch1 = 0;
				touch2 = 0;
				touch3 = 0;

				uint CarM1 = MODEL_TAXI;// Такси
				uint PedM1 = MODEL_M_M_TAXIDRIVER;// Таксист
				uint checkpoint;

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(PedM1);// Таксист
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало

				GENERATE_RANDOM_INT_IN_RANGE( 1, 6, &checkpoint);
				if ((checkpoint == 1) || (checkpoint == 3) || (checkpoint == 5))
				{
					CREATE_CAR(CarM1, -570.21, 109.06, 5.49, &car1, TRUE);
					CREATE_CAR(CarM1, -1095.34, -222.32, 9.41, &car2, TRUE);
					CREATE_CAR(CarM1, -225.07, 1148.05, 5.62, &car3, TRUE);
				}
				else
				{
					CREATE_CAR(CarM1, -309.33, 608.46, 5.62, &car1, TRUE);
					CREATE_CAR(CarM1, 187.76, 83.71, 5.81, &car2, TRUE);
					CREATE_CAR(CarM1, -383.16, -932.21, 6.15, &car3, TRUE);
				}

				LOCK_CAR_DOORS(car1, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car2, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car3, 3); //блокируем двери автомобиля для игрока
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM1, &ped2);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM1, &ped3);//создаём педа за рулём автомобиля
				SET_CHAR_COMPONENT_VARIATION(ped1, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped2, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped3, 1, 0, 0);

				CREATE_PICKUP_ROTATE(w_mp5, 3, 60, -571.12, 721.369, 6.419, 90.0, 0.0, 140.0, &sweap_1);// даём винтовку
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
				CLEAR_WANTED_LEVEL(GetPlayerIndex());
				SetTime(600);

				// камера сверху
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, -570.081, 737.787, 5.891 ); // куда смотрит камера
				SET_CAM_POS			( camera, -562.707, 743.712, 10.922 );//расположение камеры
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_CAM_FOV( camera, 45.0 );
				SET_WIDESCREEN_BORDERS( 1 );
				SetTime(600);

				// брифинг
				PRINT_BIG("TAXI_2", 5000, 2);//Friendly Rivalry
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R1_BW_XXX2", "TAX2_1", 0, 0);//Calling all cars, we're losing fares all over town. What's with you guys?
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R1_BX", "TAX2_2", 0, 0);//VC Cabs keep beating us to it. They've just got too many cars - we can't compete!
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R1_CA", "TAX2_3", 0, 0);//Mr. Vercetti, if you're out there listening in, you gotta put some VC Cabs out of action before we go bust!
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				SetTime(500);
				CLEAR_PRINTS();

				//убираем камеру
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				END_CAM_COMMANDS( &camera );
				SET_WIDESCREEN_BORDERS( 0 );
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				SetTime(500);

				ADD_BLIP_FOR_CAR(car1, &car1_ico);
				CHANGE_BLIP_SPRITE(car1_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(car1_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(car1_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(car1_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				ADD_BLIP_FOR_CAR(car2, &car2_ico);
				CHANGE_BLIP_SPRITE(car2_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(car2_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(car2_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(car2_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				ADD_BLIP_FOR_CAR(car3, &car3_ico);
				CHANGE_BLIP_SPRITE(car3_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(car3_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(car3_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(car3_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				TASK_CAR_DRIVE_WANDER(ped1, car1, 20.0, 2);// пед едит куда-то
				TASK_CAR_DRIVE_WANDER(ped2, car2, 20.0, 2);// пед едит куда-то
				TASK_CAR_DRIVE_WANDER(ped3, car3, 20.0, 2);// пед едит куда-то

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "TAXW2_1", 5000, 1);//~g~Destroy 3 of the rival taxis!

				while(true)
				{
					WAIT(0);
					if ((IS_CHAR_TOUCHING_VEHICLE(GetPlayerPed(), car1)) && (touch1 == 0))
					{
						// таксист атакует игрока
						SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
						SET_CHAR_RELATIONSHIP(ped1, 5, 0);
						SET_SENSE_RANGE(ped1, 2000.0);
						SET_CHAR_WILL_USE_COVER(ped1, 0);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, 1);
						TASK_COMBAT(ped1, GetPlayerPed());
						touch1 = 1;
					}
					if ((IS_CHAR_TOUCHING_VEHICLE(GetPlayerPed(), car2)) && (touch2 == 0))
					{
						SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
						SET_CHAR_RELATIONSHIP(ped2, 5, 0);
						SET_SENSE_RANGE(ped2, 2000.0);
						SET_CHAR_WILL_USE_COVER(ped2, 0);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, 1);
						TASK_COMBAT(ped2, GetPlayerPed());
						touch2 = 1;
					}
					if ((IS_CHAR_TOUCHING_VEHICLE(GetPlayerPed(), car3)) && (touch3 == 0))
					{
						SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
						SET_CHAR_RELATIONSHIP(ped3, 5, 0);
						SET_SENSE_RANGE(ped3, 2000.0);
						SET_CHAR_WILL_USE_COVER(ped3, 0);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, 1);
						TASK_COMBAT(ped3, GetPlayerPed());
						touch3 = 1;
					}

					if (IS_CAR_DEAD(car1))
					{
						if (taxi_1 == 1)
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							REMOVE_BLIP(car1_ico);//Удаляем иконку на радаре
							taxi_1 = 0;
						}
					}
					if (IS_CAR_DEAD(car2))
					{
						if (taxi_2 == 1)
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							REMOVE_BLIP(car2_ico);//Удаляем иконку на радаре
							taxi_2 = 0;
						}
					}
					if (IS_CAR_DEAD(car3))
					{
						if (taxi_3 == 1)
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							REMOVE_BLIP(car3_ico);//Удаляем иконку на радаре
							taxi_3 = 0;
						}
					}
					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if ((taxi_1 == 0) && (taxi_2 == 0) && (taxi_3 == 0))
					{
						skip = 2;// переменная пропуска
						break;
					}
				}
				// зачещаем скрипт
				WAIT(10);
				REMOVE_BLIP(car1_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(car2_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(car3_ico);//Удаляем иконку на радаре
				REMOVE_PICKUP(sweap_1);// выгружаем биту

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет

				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_TAXI_2" );//Friendly Rivalry
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(2000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +2000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 2000);
					G_CABS = 3;
					autosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}
//============================== Cabmaggedon ======================================
		else if ((G_ONMISSION == 0) && (G_CABS == 3))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-569.498, 738.454, 5.354, &cabs_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cabs_ico, BLIP_TAXI_RANK);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(cabs_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cabs_ico, "LG_18");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_CABBY)) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -566.998, 733.454, 4.45, -571.998, 743.454, 12.45, 0 )))
			{
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-1020.8, 191.1, 10.5, 350.0);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(cabs_ico);//Удаляем иконку на радаре
				blip_on = 0;

				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7;
				Car car1, car2, car3, car4, car5, car6, car7, car8;
				Texture fon, timer;
				Cam camera;
				Blip car1_ico, car2_ico, car3_ico, car4_ico, car5_ico, car6_ico;
				Object vorota;

				skip = 0; // переменная пропуска
				text1 = 0;
				text2 = 0;
				time_m = 1;
				time_s = 0;
				sound = 0;
				engine = 1;
				res_on = 0;
				vorotaX = -556.453;
				vorotaY = -718.6;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				timer = GET_TEXTURE( textur, "timer_hud" );

				uint CarM1 = MODEL_TAXI;// Такси
				uint CarM2 = MODEL_ROM;// зебра
				uint PedM1 = MODEL_M_M_TAXIDRIVER;// Таксист
				uint vorotaM = vc_electricgate; //ворота
				uint car_HP, PTFX, PTFX2;

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);
				REQUEST_MODEL(PedM1);// Таксист
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(vorotaM);// ворота
				while (!HAS_MODEL_LOADED(vorotaM)) WAIT(0);

				CREATE_CAR(CarM1, 303.109, -787.416, 5.445, &car1, TRUE);
				CREATE_CAR(CarM1, 299.551, -787.416, 5.445, &car2, TRUE);
				CREATE_CAR(CarM1, 295.942, -787.416, 5.445, &car3, TRUE);
				CREATE_CAR(CarM1, 292.585, -787.416, 5.445, &car4, TRUE);
				CREATE_CAR(CarM1, 289.167, -787.416, 5.445, &car5, TRUE);
				CREATE_CAR(CarM1, 286.008, -787.416, 5.445, &car6, TRUE);
				CREATE_CAR(CarM2, 294.306, -779.725, 5.445, &car7, TRUE);

				LOCK_CAR_DOORS(car1, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car2, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car3, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car4, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car5, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car6, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car7, 3); //блокируем двери автомобиля для игрока

				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM1, &ped2);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM1, &ped3);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car4, 1, PedM1, &ped4);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car5, 1, PedM1, &ped5);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car6, 1, PedM1, &ped6);//создаём педа за рулём автомобиля
				CREATE_CHAR_INSIDE_CAR(car7, 1, PedM1, &ped7);//создаём педа за рулём автомобиля

				SET_CHAR_COMPONENT_VARIATION(ped1, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped2, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped3, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped4, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped5, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped6, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped7, 1, 0, 0);

				CREATE_OBJECT_NO_OFFSET(vorotaM, -559.584, -726.446, 5.338, &vorota, TRUE);
				SET_OBJECT_HEADING(vorota, 68.0);
				SET_OBJECT_DYNAMIC(vorota, 0);
				SET_OBJECT_INVINCIBLE(vorota, 1);
				FREEZE_OBJECT_POSITION(vorota, 1);

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
				CLEAR_WANTED_LEVEL(GetPlayerIndex());
				SetTime(600);

				// камера сверху
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, -570.081, 737.787, 5.891 ); // куда смотрит камера
				SET_CAM_POS			( camera, -562.707, 743.712, 10.922 );//расположение камеры
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_CAM_FOV( camera, 45.0 );
				SET_WIDESCREEN_BORDERS( 1 );
				SetTime(600);

				// брифинг
				PRINT_BIG("TAXI_3", 5000, 2);//Cabmaggedon
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R1_CB", "TAX3_1", 0, 0);//Car 13, We got a Miss Cortez, asked for you especially.
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R1_CC", "TAX3_2", 0, 0);//Ok, I got it. Car 13 out!
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				SetTime(500);
				CLEAR_PRINTS();

				//убираем камеру
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				END_CAM_COMMANDS( &camera );
				SET_WIDESCREEN_BORDERS( 0 );
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				SetTime(500);

				ADD_BLIP_FOR_COORD(-678.792, -756.889, 5.098, &cabs_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cabs_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(cabs_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(cabs_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cabs_ico, "NE_POINT");//иконка на радаре называние в истории карты ""
				PRINT_STRING_IN_STRING("string", "TAXW3_1", 5000, 1);//~g~Go and pick up Mercedes.

				while(true)
				{
					WAIT(0);
					DRAW_CHECKPOINT( -678.792, -756.889, 5.098, 2.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -678.792, -756.889, 5.098, &PlayR);//проверка "игрок на координатах"
					if ( PlayR < 2.1)
					{
						if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_CABBY))
						{
							// посигнальте
							if (text1 == 0)
							{
								PRINT_HELP("NEHELP3");//Press ~INPUT_VEH_HORN~ button to sound horn.
								PRINT_STRING_IN_STRING("string", "HORN", 5000, 1);//~COL_NET_12~Sound the horn.
								text1 = 1;
							}
							if (IS_PLAYER_PRESSING_HORN(0))// проверка "игрок посигналил"
							{
								SET_MAX_WANTED_LEVEL(0);
								CLEAR_HELP(); // удаляем текст подсказки
								REMOVE_BLIP(cabs_ico);//Удаляем иконку на радаре
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car8);
								//removed locking of door
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока


								// камера сверху
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, -675.899, -804.163, 7.433 ); // куда смотрит камера
								SET_CAM_POS			( camera, -676.856, -742.078, 7.916 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );
								SetTime(2000);

								// меняем ракурс
								POINT_CAM_AT_COORD	( camera, -650.254, -734.201, 5.541 ); // куда смотрит камера
								SET_CAM_POS			( camera, -688.891, -763.655, 8.102 );//расположение камеры
								SetTime(500);

								// аудио
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R1_CC_QQQ1", "TAX3_3", 0, 0);//Hmmmm, no sign of Mercedes...
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R1_FA", "TAXW3_C", 0, 0);//What's going on?
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								// выезд таксистов тут
								REQUEST_CAR_RECORDING( 3043 );
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3043 )) WAIT(0);
								REQUEST_CAR_RECORDING( 3044 );
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3044 )) WAIT(0);
								REQUEST_CAR_RECORDING( 3045 );
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3045 )) WAIT(0);
								REQUEST_CAR_RECORDING( 3046 );
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3046 )) WAIT(0);
								REQUEST_CAR_RECORDING( 3047 );
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3047 )) WAIT(0);
								REQUEST_CAR_RECORDING( 3048 );
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3048 )) WAIT(0);

								CLEAR_AREA(-539.753, -721.065, 5.823, 25.0, 1);//очещаем зону загрузки
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3043, 0.0, 0.0, 0.0);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 3044, 0.0, 0.0, 0.0);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 3045, 0.0, 0.0, 0.0);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car4, 3046, 0.0, 0.0, 0.0);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car5, 3047, 0.0, 0.0, 0.0);
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car6, 3048, 0.0, 0.0, 0.0);

								// меняем ракурс
								POINT_CAM_AT_COORD	( camera, -555.041, -729.485, 7.753 ); // куда смотрит камера
								SET_CAM_POS			( camera, -556.249, -700.029, 6.567 );//расположение камеры
								SetTime(1000);
								CLEAR_PRINTS();
								SetTime(2000);

								SET_PLAYBACK_SPEED(car1, 1.5);
								SET_PLAYBACK_SPEED(car2, 1.5);
								SET_PLAYBACK_SPEED(car3, 1.5);
								SET_PLAYBACK_SPEED(car4, 1.5);
								SET_PLAYBACK_SPEED(car5, 1.5);
								SET_PLAYBACK_SPEED(car6, 1.5);

								// меняем ракурс
								POINT_CAM_AT_COORD	( camera, -613.355, -700.484, 3.418 ); // куда смотрит камера
								SET_CAM_POS			( camera, -676.901, -750.855, 8.962 );//расположение камеры
								SetTime(7000);

								STOP_PLAYBACK_RECORDED_CAR(car1);
								STOP_PLAYBACK_RECORDED_CAR(car2);
								STOP_PLAYBACK_RECORDED_CAR(car3);
								STOP_PLAYBACK_RECORDED_CAR(car4);
								STOP_PLAYBACK_RECORDED_CAR(car5);
								STOP_PLAYBACK_RECORDED_CAR(car6);
								REMOVE_CAR_RECORDING( 3043 );
								REMOVE_CAR_RECORDING( 3044 );
								REMOVE_CAR_RECORDING( 3045 );
								REMOVE_CAR_RECORDING( 3046 );
								REMOVE_CAR_RECORDING( 3047 );
								REMOVE_CAR_RECORDING( 3048 );

								//убираем камеру
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								END_CAM_COMMANDS( &camera );
								SET_WIDESCREEN_BORDERS( 0 );
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
								SET_OBJECT_COORDINATES(vorota, -556.453, -718.6, 5.338);
								SetTime(500);

								//TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -616.451, -712.534, 5.758, 4, 40.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								//TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, -616.451, -712.534, 5.758, 4, 40.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								//TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, -616.451, -712.534, 5.758, 4, 40.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								//TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped4, car4, -616.451, -712.534, 5.758, 4, 40.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								//TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped5, car5, -616.451, -712.534, 5.758, 4, 40.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								//TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped6, car6, -616.451, -712.534, 5.758, 4, 40.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
								//SetTime(2000);

								// атака таксистов тут
								SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
								SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
								SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
								SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
								SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
								SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
								SET_CHAR_RELATIONSHIP(ped1, 5, 0);
								SET_CHAR_RELATIONSHIP(ped2, 5, 0);
								SET_CHAR_RELATIONSHIP(ped3, 5, 0);
								SET_CHAR_RELATIONSHIP(ped4, 5, 0);
								SET_CHAR_RELATIONSHIP(ped5, 5, 0);
								SET_CHAR_RELATIONSHIP(ped6, 5, 0);
								SET_SENSE_RANGE(ped1, 250.0);
								SET_SENSE_RANGE(ped2, 250.0);
								SET_SENSE_RANGE(ped3, 250.0);
								SET_SENSE_RANGE(ped4, 250.0);
								SET_SENSE_RANGE(ped5, 250.0);
								SET_SENSE_RANGE(ped6, 250.0);
								SET_CHAR_WILL_USE_COVER(ped1, 0);
								SET_CHAR_WILL_USE_COVER(ped2, 0);
								SET_CHAR_WILL_USE_COVER(ped3, 0);
								SET_CHAR_WILL_USE_COVER(ped4, 0);
								SET_CHAR_WILL_USE_COVER(ped5, 0);
								SET_CHAR_WILL_USE_COVER(ped6, 0);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, 1);
								TASK_COMBAT(ped1, GetPlayerPed());
								TASK_COMBAT(ped2, GetPlayerPed());
								TASK_COMBAT(ped3, GetPlayerPed());
								TASK_COMBAT(ped4, GetPlayerPed());
								TASK_COMBAT(ped5, GetPlayerPed());
								TASK_COMBAT(ped6, GetPlayerPed());

								ADD_BLIP_FOR_CHAR(ped1, &car1_ico);
								CHANGE_BLIP_SPRITE(car1_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(car1_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(car1_ico, 0.5); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(car1_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

								ADD_BLIP_FOR_CHAR(ped2, &car2_ico);
								CHANGE_BLIP_SPRITE(car2_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(car2_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(car2_ico, 0.5); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(car2_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

								ADD_BLIP_FOR_CHAR(ped3, &car3_ico);
								CHANGE_BLIP_SPRITE(car3_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(car3_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(car3_ico, 0.5); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(car3_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

								ADD_BLIP_FOR_CHAR(ped4, &car4_ico);
								CHANGE_BLIP_SPRITE(car4_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(car4_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(car4_ico, 0.5); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(car4_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

								ADD_BLIP_FOR_CHAR(ped5, &car5_ico);
								CHANGE_BLIP_SPRITE(car5_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(car5_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(car5_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(car5_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

								ADD_BLIP_FOR_CHAR(ped6, &car6_ico);
								CHANGE_BLIP_SPRITE(car6_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(car6_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(car6_ico, 0.5); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(car6_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "TAXW3_2", 5000, 1);//~g~Stay alive until the timer runs out.
								SETTIMERA( 0 );
								SETTIMERB( 10000 );
								engine = 1;
								break;
							}
							text2 = 0;
						}
						else
						{
							if (text2 == 0)
							{
								PRINT_STRING_IN_STRING("string", "TAXW1_5", 5000, 1);//~COL_NET_12~You need to be in a Kaufman cab!
								text2 = 1;
							}
						}
					}
					else
					{
						if (text1 == 1)
						{
							text1 = 0;
						}
						if (text2 == 1)
						{
							text2 = 0;
						}
					}

					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
				}
				// часть 2
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (engine == 1)
						{
							if (TIMERB() > 20000)
							{
								SET_CAR_ENGINE_ON(car8, 0, 1);
								SET_ENGINE_HEALTH(car8, 0);
								engine = 0;
							}
						}
						else if (engine == 0)
						{
							if (TIMERB() > 24000)
							{
								SET_ENGINE_HEALTH(car8, 250);
								SETTIMERB( 0 );
								engine = 1;
							}
						}
						if ((GET_ENGINE_HEALTH(car8) < 150) && (engine == 1))
						{
							SET_ENGINE_HEALTH(car8, 250);
						}

						if (!IS_CHAR_SITTING_IN_ANY_CAR(ped1))
						{
							WARP_CHAR_INTO_CAR(ped1, car1);
							SET_SENSE_RANGE(ped1, 2000.0);
							TASK_COMBAT(ped1, GetPlayerPed());
						}
						else if (!IS_CHAR_SITTING_IN_ANY_CAR(ped2))
						{
							WARP_CHAR_INTO_CAR(ped2, car2);
							SET_SENSE_RANGE(ped2, 2000.0);
							TASK_COMBAT(ped2, GetPlayerPed());
						}
						else if (!IS_CHAR_SITTING_IN_ANY_CAR(ped3))
						{
							WARP_CHAR_INTO_CAR(ped3, car3);
							SET_SENSE_RANGE(ped3, 2000.0);
							TASK_COMBAT(ped3, GetPlayerPed());
						}
						else if (!IS_CHAR_SITTING_IN_ANY_CAR(ped4))
						{
							WARP_CHAR_INTO_CAR(ped4, car4);
							SET_SENSE_RANGE(ped4, 2000.0);
							TASK_COMBAT(ped4, GetPlayerPed());
						}
						else if (!IS_CHAR_SITTING_IN_ANY_CAR(ped5))
						{
							WARP_CHAR_INTO_CAR(ped5, car5);
							SET_SENSE_RANGE(ped5, 2000.0);
							TASK_COMBAT(ped5, GetPlayerPed());
						}
						else if (!IS_CHAR_SITTING_IN_ANY_CAR(ped6))
						{
							WARP_CHAR_INTO_CAR(ped6, car6);
							SET_SENSE_RANGE(ped6, 2000.0);
							TASK_COMBAT(ped6, GetPlayerPed());
						}


						//============================ HUD ============================
						// таймер тут
						if (TIMERA() > 1250)
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
							DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); // TIME:

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
							DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); // TIME:

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
						// выполнение условия продержаться таймер
						if ((time_m == 0) && (time_s == 0))
						{
							if (sound == 1)
							{
								STOP_STREAM();
								ENABLE_FRONTEND_RADIO();
								sound = 1;
							}

							REMOVE_BLIP(car1_ico);//Удаляем иконку на радаре
							REMOVE_BLIP(car2_ico);//Удаляем иконку на радаре
							REMOVE_BLIP(car3_ico);//Удаляем иконку на радаре
							REMOVE_BLIP(car4_ico);//Удаляем иконку на радаре
							REMOVE_BLIP(car5_ico);//Удаляем иконку на радаре
							REMOVE_BLIP(car6_ico);//Удаляем иконку на радаре
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							// камера
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -555.041, -729.485, 7.753 ); // куда смотрит камера
							SET_CAM_POS			( camera, -556.249, -700.029, 6.567 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							// выезжает зебра тут
							SET_CHAR_COORDINATES(ped1, -5.883, -7.317, 5.823);// перемещаем игрока
							SET_CHAR_COORDINATES(ped2, -5.883, -6.317, 5.823);// перемещаем игрока
							SET_CHAR_COORDINATES(ped3, -5.883, -5.317, 5.823);// перемещаем игрока
							SET_CHAR_COORDINATES(ped4, -5.883, -4.317, 5.823);// перемещаем игрока
							SET_CHAR_COORDINATES(ped5, -5.883, -3.317, 5.823);// перемещаем игрока
							SET_CHAR_COORDINATES(ped6, -5.883, -2.317, 5.823);// перемещаем игрока
							SET_CHAR_COORDINATES(ped7, -551.883, -716.317, 5.823);// перемещаем игрока
							SET_CHAR_HEADING(ped7, 70.0);
							SetTime(1000);

							// открываем ворота
							while (true)
							{
								WAIT( 1 );
								vorotaX -= 0.0395;
								vorotaY -= 0.0985;
								SET_OBJECT_COORDINATES(vorota, vorotaX, vorotaY, 5.338);
								if (vorotaY < -726.446)
								{
									break;
								}
							}

							// аудио
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R2_AA", "TAX3_4", 0, 0);//It's time for Kaufman Cab's guardian angel to eat some fender!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped7, car7, -616.451, -712.534, 5.758, 4, 30.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							SetTime(2000);

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							SetTime(500);

							// нападает зебра тут
							SET_OBJECT_COORDINATES(vorota, -556.453, -718.6, 5.338);
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);
							SET_SENSE_RANGE(ped7, 2000.0);
							SET_CHAR_WILL_USE_COVER(ped7, 0);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, 1);
							TASK_COMBAT(ped7, GetPlayerPed());

							//WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car1, 0);
							//WARP_CHAR_INTO_CAR_AS_PASSENGER(ped2, car2, 0);
							//WARP_CHAR_INTO_CAR_AS_PASSENGER(ped3, car3, 0);
							//WARP_CHAR_INTO_CAR_AS_PASSENGER(ped4, car4, 0);
							//WARP_CHAR_INTO_CAR_AS_PASSENGER(ped5, car5, 0);
							//WARP_CHAR_INTO_CAR_AS_PASSENGER(ped6, car6, 0);
							//EXPLODE_CHAR_HEAD(ped1);
							//EXPLODE_CHAR_HEAD(ped2);
							//EXPLODE_CHAR_HEAD(ped3);
							//EXPLODE_CHAR_HEAD(ped4);
							//EXPLODE_CHAR_HEAD(ped5);
							//EXPLODE_CHAR_HEAD(ped6);

							ADD_BLIP_FOR_CHAR(ped7, &car1_ico);
							CHANGE_BLIP_SPRITE(car1_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(car1_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(car1_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(car1_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "TAXW3_3", 5000, 1);//~g~Take out the leader cab!

							SET_ENGINE_HEALTH(car8, 450);
							SETTIMERA( 0 );
							SETTIMERB( 0 );
							engine = 0;
							break;
						}

						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
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
						GET_CAR_HEALTH(car7, &car_HP);
						if ((IS_CHAR_TOUCHING_VEHICLE(GetPlayerPed(), car7)) && (engine == 0)) // если игрок поцарапал машину соперника
						{
							if (TIMERA() > 3000)
							{
								GET_CAR_HEALTH(car7, &car_HP);
								car_HP -=50;
								SET_CAR_HEALTH(car7, car_HP);
								SETTIMERA( 0 );
							}
						}
						if ((car_HP < 5) && (engine == 0))
						{
							//поджигаем автомобиль
							SETTIMERB(0);
							PTFX = START_PTFX_ON_VEH("fire_chopper_tail", car7, -1.035, -1.33, -0.35, 1, 1, 90, 0.36);
							PTFX2 = START_PTFX_ON_VEH("fire_chopper_tail", car7, 1.035, -1.33, -0.05, 1, 1, -90, 0.36);
							engine = 1;
							SETTIMERA( 0 );
						}
						if (engine == 1)
						{
							if (TIMERA() > 5000)
							{
								EXPLODE_CHAR_HEAD(ped7);
								EXPLODE_CAR(car7, 1, 1);
								engine = 2;
							}
						}

						if (GET_ENGINE_HEALTH(car8) < 150)
						{
							SET_ENGINE_HEALTH(car8, 250);
						}

						if (!IS_CHAR_SITTING_IN_ANY_CAR(ped7))
						{
							WARP_CHAR_INTO_CAR(ped7, car7);
						}

						if ((IS_CHAR_DEAD(ped7)) || (IS_CAR_DEAD(car7)))
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
							// камера
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -572.881, 723.549, 9.168 ); // куда смотрит камера
							SET_CAM_POS			( camera, -588.599, 753.044, 9.441 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

							SETTIMERA(0); //сбрасываем таймер 
							while (true)
							{
								SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
								SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
								SET_TEXT_EDGE(1, 0, 0, 0, 255); //
								SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
								SET_TEXT_CENTRE(1); // задаём центр текста
								DISPLAY_TEXT(0.5, 0.45, "TAX_AS1");//TAXI FIRM ASSET COMPLETED
								WAIT( 0 );
								if ( TIMERA() > 5000 )
								{
									break;
								}
							}

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, -565.734, 714.121, 6.778 ); // куда смотрит камера
							SET_CAM_POS			( camera, -560.881, 716.777, 7.953 );//расположение камеры
							PRINT_STRING_IN_STRING("string", "TAX_AS2", 5000, 1);//~g~Kaufman Cabs will now generate revenue up to a maximum of $5000. Make sure you collect it regularly.

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
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
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
				// зачещаем скрипт
				WAIT(10);
				SET_MAX_WANTED_LEVEL(6);
				REMOVE_BLIP(car1_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(car2_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(car3_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(car4_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(car5_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(car6_ico);//Удаляем иконку на радаре
				LOCK_CAR_DOORS(car7, 1); //разблокируем двери автомобиля для игрока

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(vorotaM);//выгружаем модель

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
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car7);//выгружаем модель машины(в последствии машина изчезнет)
				if (car8 != 0)
				{
					LOCK_CAR_DOORS(car8, 1); //блокируем двери автомобиля для игрока
					MARK_CAR_AS_NO_LONGER_NEEDED(&car8);//выгружаем модель машины(в последствии машина изчезнет)
				}
				DELETE_OBJECT(&vorota);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&vorota);

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( timer );
				REMOVE_TXD( textur );
				STOP_PTFX(PTFX);
				REMOVE_PTFX(PTFX);
				STOP_PTFX(PTFX2);
				REMOVE_PTFX(PTFX2);

				if (sound == 1)
				{
					STOP_STREAM();
					ENABLE_FRONTEND_RADIO();
				}

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_TAXI_3" );//Cabmaggedon
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(5000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +5000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 5000);
					G_CABS = 4;
					autosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}
		else if ((G_ONMISSION == 0) && (G_CABS == 4))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-569.498, 738.454, 5.354, &cabs_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cabs_ico, BLIP_TAXI_RANK);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(cabs_ico, 1.1); // масштаб иконки на радаре
				SET_BLIP_AS_SHORT_RANGE(cabs_ico, 1); // иконка пропадает если не в зоне радардиска
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cabs_ico, "LG_18");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(cabs_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}
		if (G_CABS == 4)
		{
			if ( TIMERC() > 576)// время фарма
			{
				if (income < 5000)// максимальный доход
				{
					income +=1;
				}
				SETTIMERC(0); //сбрасываем таймер 
			}
			if (G_COLLECTOR == 5)// ID Бизнеса
			{
				income = 0;
				G_COLLECTOR = 0;
			}

			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -558.695, 713.943, 5.301, -564.673, 721.777, 10.199, 0 ))
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
				if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -560.97, 714.555, -563.134, 717.373, 0))
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
	kaufman();
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
