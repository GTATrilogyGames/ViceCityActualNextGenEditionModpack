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
float PlayX, PlayY, PlayZ, PlayR, blip_on, skip, textur, time_m, time_s, sound, text, text2, volna_1, volna_2, autosave;
float attach_1, deton, PedX, PedY, PedZ, ico_1, ico_2, ico_3, ico_4, ico_5, ico_6, ico_7, ico_8, ico_9, ico_10, in_car, path_on, hel_set;

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
void voodoo(void)
{
	blip_on = 0;
	autosave = 0;
	Blip haiti_ico;
	uint cutscene_torso;
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
//============================== Juju Scramble ======================================
		if ((G_ONMISSION == 0) && (G_HAITI == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-529.349, 677.904, 3.32976, &haiti_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(haiti_ico, BLIP_RANSOM);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(haiti_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(haiti_ico, "LG_14");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( -529.349, 677.904, 3.32976, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -529.349, 677.904, 3.32976, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("HAT_1", 15000, CUTSCENE_HAITIAN);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-957.904, 122.843, 8.278, 356.948);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре
				blip_on = 0;

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замараживаем игрока
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
				SET_CHAR_COORDINATES(GetPlayerPed(), -529.452, 675.58, 3.45918 );// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 180.0 );
				// SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 0, 0);
				Cam camera;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9;
				Texture fon, timer;
				Pickup keys_1;

				skip = 0;
				time_m = 1;
				time_s = 0;
				sound = 0;
				text = 0;
				text2 = 0;

				uint PedM1 = MODEL_M_Y_NHELIPILOT;// SWAT

				REQUEST_MODEL(PedM1);// 
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				timer = GET_TEXTURE( textur, "timer_hud" );

				// педы
				CREATE_CHAR (26, PedM1, 290.970, -770.5, 4.6677, &ped1, TRUE);// SWAT
				CREATE_CHAR (26, PedM1, 290.971, -770.5, 4.6677, &ped2, TRUE);// SWAT
				CREATE_CHAR (26, PedM1, 290.972, -770.5, 4.6677, &ped3, TRUE);// SWAT
				CREATE_CHAR (26, PedM1, 290.973, -770.5, 4.6677, &ped4, TRUE);// SWAT
				CREATE_CHAR (26, PedM1, 290.974, -770.5, 4.6677, &ped5, TRUE);// SWAT
				CREATE_CHAR (26, PedM1, 290.975, -770.5, 4.6677, &ped6, TRUE);// SWAT
				CREATE_CHAR (26, PedM1, 290.976, -770.5, 4.6677, &ped7, TRUE);// SWAT
				CREATE_CHAR (26, PedM1, 290.977, -770.5, 4.6677, &ped8, TRUE);// SWAT
				CREATE_CHAR (26, PedM1, 290.978, -770.5, 4.6677, &ped9, TRUE);// SWAT

				uint hour, minute, weather;
				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 55);//устанавливаем время

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "HAT_1", 6 ); // загружаем субтитры из *.GTX
																	
							
				START_CUTSCENE_NOW("hat_1");
		
								   
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

				// вооружаем
				UpdateWeaponOfPed(ped1, WEAPON_MP5);
				UpdateWeaponOfPed(ped2, WEAPON_MP5);
				UpdateWeaponOfPed(ped3, WEAPON_MP5);
				UpdateWeaponOfPed(ped4, WEAPON_MP5);
				UpdateWeaponOfPed(ped5, WEAPON_MP5);
				UpdateWeaponOfPed(ped6, WEAPON_MP5);
				UpdateWeaponOfPed(ped7, WEAPON_SNIPERRIFLE);
				UpdateWeaponOfPed(ped8, WEAPON_MP5);
				UpdateWeaponOfPed(ped9, WEAPON_MP5);

				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_SNIPERRIFLE, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_MP5, TRUE);

				CREATE_PICKUP_ROTATE(mission_keis2, 22, 20, -731.569, 516.03, 10.8419, 0.0, 0.0, 0.0, &keys_1);

				ADD_BLIP_FOR_PICKUP(keys_1, &haiti_ico);
				CHANGE_BLIP_SPRITE(haiti_ico, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(haiti_ico, 5);   //цвет иконка на радаре (0=белая)
				CHANGE_BLIP_SCALE(haiti_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(haiti_ico, "MO_TARGET");//иконка на радаре "Товар"

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "HAM1_1", 5000, 1);//~g~The cops are closing in on our stashes. BE quick, and beat dem to it!

				//грузим анимацию
				REQUEST_ANIMS( "ne_missbank" );//загружаем файл с анимацией
				while (!HAVE_ANIMS_LOADED( "ne_missbank" )) WAIT(0);

				// поднять первый кейс
				while (TRUE)
				{
					WAIT(0);
					if (HAS_PICKUP_BEEN_COLLECTED( keys_1 ))
					{
						REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

						SET_CHAR_COORDINATES(ped1, -728.021, 502.665, 14.2908);
						SET_CHAR_COORDINATES(ped2, -721.543, 502.665, 14.2908);
						SET_CHAR_COORDINATES(ped3, -709.955, 516.404, 18.097);
						SET_CHAR_COORDINATES(ped4, -709.955, 522.881, 18.097);
						SET_CHAR_HEADING(ped1, 0.0);
						SET_CHAR_HEADING(ped2, 0.0);
						SET_CHAR_HEADING(ped3, 90.0);
						SET_CHAR_HEADING(ped4, 90.0);
						SetTime(500);

						// ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, -731.279, 514.042, 10.2528); // куда смотрит камера
						SET_CAM_POS			( camera, -726.811, 499.881, 17.7508 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						TASK_AIM_GUN_AT_CHAR(ped1, GetPlayerPed(), 3000);
					
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R8_VA", "HAT_1A", 0, 0);//~g~Don't move a muscle, chump!
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(1000);

						TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "armsup_loop", "ne_missbank", 8.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
						SetTime(2500);

						//убираем камеру
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

						SET_CHAR_COORDINATES(ped5, -534.981, 503.633, 5.25463);
						SET_CHAR_COORDINATES(ped6, -535.403, 487.612, 5.25463);
						SET_CHAR_COORDINATES(ped7, -534.808, 496.647, 8.20224);
						SET_CHAR_HEADING(ped5, 90.0);
						SET_CHAR_HEADING(ped6, 90.0);
						SET_CHAR_HEADING(ped7, 90.0);

						SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);

						SET_CHAR_RELATIONSHIP(ped1, 5, 0);
						SET_CHAR_RELATIONSHIP(ped2, 5, 0);
						SET_CHAR_RELATIONSHIP(ped3, 5, 0);
						SET_CHAR_RELATIONSHIP(ped4, 5, 0);
						SET_CHAR_RELATIONSHIP(ped5, 5, 0);
						SET_CHAR_RELATIONSHIP(ped6, 5, 0);
						SET_CHAR_RELATIONSHIP(ped7, 5, 0);

						SET_SENSE_RANGE(ped1, 85.0);
						SET_SENSE_RANGE(ped2, 85.0);
						SET_SENSE_RANGE(ped3, 85.0);
						SET_SENSE_RANGE(ped4, 85.0);
						SET_SENSE_RANGE(ped5, 85.0);
						SET_SENSE_RANGE(ped6, 85.0);
						SET_SENSE_RANGE(ped7, 85.0);

						SET_CHAR_WILL_USE_COVER(ped1, 1);
						SET_CHAR_WILL_USE_COVER(ped2, 1);
						SET_CHAR_WILL_USE_COVER(ped3, 1);
						SET_CHAR_WILL_USE_COVER(ped4, 1);
						SET_CHAR_WILL_USE_COVER(ped5, 1);
						SET_CHAR_WILL_USE_COVER(ped6, 1);
						SET_CHAR_WILL_USE_COVER(ped7, 1);

						CREATE_PICKUP_ROTATE(mission_keis2, 22, 20, -562.938, 514.365, 4.8622, 0.0, 0.0, -95.0, &keys_1);

						ADD_BLIP_FOR_PICKUP(keys_1, &haiti_ico);
						CHANGE_BLIP_SPRITE(haiti_ico, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(haiti_ico, 5);   //цвет иконка на радаре (0=белая)
						CHANGE_BLIP_SCALE(haiti_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(haiti_ico, "MO_TARGET");//иконка на радаре "Товар"

						ALTER_WANTED_LEVEL(GetPlayerIndex(), 2);
						APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "HAM1_4", 5000, 1);//~g~Good! Now get the next one!
						break;
					}
					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
				}
				// поднять второй кейс
				if (skip == 0)
				{
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

						if (HAS_PICKUP_BEEN_COLLECTED( keys_1 ))
						{
							REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре

							CREATE_PICKUP_ROTATE(mission_keis2, 22, 20, -483.234, 882.274, 5.42256, 0.0, 0.0, 80.0, &keys_1);

							ADD_BLIP_FOR_PICKUP(keys_1, &haiti_ico);
							CHANGE_BLIP_SPRITE(haiti_ico, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(haiti_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(haiti_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(haiti_ico, "MO_TARGET");//иконка на радаре "Товар"

							ALTER_WANTED_LEVEL(GetPlayerIndex(), 4);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());

							if (sound == 1)
							{
								STOP_STREAM();
								ENABLE_FRONTEND_RADIO();
							}

							time_m = 1;
							time_s = 0;
							sound = 0;

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "HAM1_4", 5000, 1);//~g~Good! Now get the next one!
							break;
						}
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((time_m == 0) && (time_s == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "HAM1_2", 5000, 1);//~r~The cops got to the stash first!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// поднять третий кейс
				if (skip == 0)
				{
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

						if (HAS_PICKUP_BEEN_COLLECTED( keys_1 ))
						{
							REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре

							ALTER_WANTED_LEVEL(GetPlayerIndex(), 5);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());

							SET_CHAR_COORDINATES(ped8, -469.458, 835.574, 5.57069);
							SET_CHAR_COORDINATES(ped9, -473.064, 835.095, 5.57069);
							SET_CHAR_HEADING(ped8, 5.0);
							SET_CHAR_HEADING(ped9, 5.0);

							SET_CHAR_RELATIONSHIP_GROUP(ped8, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped9, 3);
							SET_CHAR_RELATIONSHIP(ped8, 3, 0);
							SET_CHAR_RELATIONSHIP(ped9, 3, 0);
							SET_SENSE_RANGE(ped8, 85.0);
							SET_SENSE_RANGE(ped9, 85.0);
							SET_CHAR_WILL_USE_COVER(ped8, 1);
							SET_CHAR_WILL_USE_COVER(ped9, 1);
							TASK_COMBAT(ped8, GetPlayerPed());
							TASK_COMBAT(ped9, GetPlayerPed());

							if (sound == 1)
							{
								STOP_STREAM();
								ENABLE_FRONTEND_RADIO();
							}

							sound = 0;

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NEWANTED", 5000, 1);//~COL_NET_12~Shake the cops and lose your wanted level!
							break;
						}
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((time_m == 0) && (time_s == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "HAM1_2", 5000, 1);//~r~The cops got to the stash first!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// сдать кейсы
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (!IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0))
						{
							//DRAW_CHECKPOINT( -529.537, 675.639, 3.15269, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							//GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							//GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -529.537, 675.639, 3.15269, &PlayR);//проверка "игрок на координатах"
							//if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
							//{
								PRINT_STRING_IN_STRING("string", "HAM1_3", 5000, 1);//~g~Get this stuff back to the hideout!
								skip = 2;// переменная пропуска
								break;
							//}
						}
						if (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0))
						{
							if ( text == 0)
							{
								REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NEWANTED", 5000, 1);//~COL_NET_12~Shake the cops and lose your wanted level!
								text = 1;
							}
						}
						/*/else
						{
							if (text == 1)
							{
								ADD_BLIP_FOR_COORD(-529.537, 675.639, 3.15269, &haiti_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(haiti_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(haiti_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(haiti_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(haiti_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "HAM1_3", 5000, 1);//~g~Get this stuff back to the hideout!
								text = 0;
							}
						}
						//*/

						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
					}
				}

				REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( timer );
				REMOVE_TXD( textur );

				if (sound == 1)
				{
					STOP_STREAM();
					ENABLE_FRONTEND_RADIO();
				}

				REMOVE_PICKUP(keys_1);// выгружаем биту

				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа

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

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_HAT_1" );//Juju Scramble
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(1000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +1000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 1000);
					G_HAITI = 2;
					autosave = 1;
				}
				G_ONMISSION = 0;

			}
		}

//============================== Bombs Away! ======================================
		else if ((G_ONMISSION == 0) && (G_HAITI == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-529.349, 677.904, 3.32976, &haiti_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(haiti_ico, BLIP_RANSOM);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(haiti_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(haiti_ico, "LG_14");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( -529.349, 677.904, 3.32976, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -529.349, 677.904, 3.32976, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("HAT_2", 15000, CUTSCENE_HAITIAN);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-957.904, 122.843, 8.278, 356.948);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре
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

				SET_CHAR_COORDINATES(GetPlayerPed(), -529.452, 675.58, 3.45918 );// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 180.0 );
				
				uint hour, minute, weather;
				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 55);//устанавливаем время
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "HAT_2", 6 ); // загружаем субтитры из *.GTX
																	
							
				START_CUTSCENE_NOW("hat_2");
		
								   
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

				Car car1, car2, car3, car4, car5, car6;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9;
				Object tnt_1;
				Blip ped1_ico, ped2_ico, ped3_ico, ped4_ico, ped5_ico, ped6_ico, ped7_ico, ped8_ico, ped9_ico;
				Cam camera;
				Texture fon, hel;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				hel = GET_TEXTURE( textur, "rc_hel_hud" );

				uint PedM1 = MODEL_M_Y_GLAT_HI_01;// Кубинец
				uint CarM1 = MODEL_SPEEDO;// фургон
				uint CarM2 = MODEL_TOURMAV;// вертолёт
				uint CarM3 = MODEL_COASTG;// Лодка 1
				uint CarM4 = MODEL_JETMAX;// Лодка 2
				uint CarM5 = MODEL_DINGHY;// Лодка 3
				uint CarM6 = MODEL_DUKES;// Гермес
				uint dynamite_1 = vc_rc_bomb;// Бомба
				uint ped1_hp, ped2_hp, ped3_hp, ped4_hp, ped5_hp, ped6_hp, ped7_hp, ped8_hp, ped9_hp;

				skip = 0;
				attach_1 = 1;
				ico_1 = 1;
				ico_2 = 1;
				ico_3 = 1;
				ico_4 = 1;
				ico_5 = 1;
				ico_6 = 1;
				ico_7 = 1;
				ico_8 = 1;
				ico_9 = 1;
				in_car = 0;
				path_on = 0;
				hel_set = 3;

				// загрузаем автомобиль
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);

				// загружаем вертолётик
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);

				// загружаем Лодка 1
				REQUEST_MODEL(CarM3);
				while (!HAS_MODEL_LOADED(CarM3)) WAIT(100);

				// загружаем Лодка 2
				REQUEST_MODEL(CarM4);
				while (!HAS_MODEL_LOADED(CarM4)) WAIT(100);

				// загружаем пЛодка 3
				REQUEST_MODEL(CarM5);
				while (!HAS_MODEL_LOADED(CarM5)) WAIT(100);

				// загружаем Гермес
				REQUEST_MODEL(CarM6);
				while (!HAS_MODEL_LOADED(CarM6)) WAIT(100);

				// загружаем Кубинец
				REQUEST_MODEL(PedM1);// Кубинец
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало

				// загружаем динамит
				REQUEST_MODEL(dynamite_1);// бочки
				while (!HAS_MODEL_LOADED(dynamite_1)) WAIT(0);

				// создаём фургон
				CREATE_CAR(CarM1, -374.205, 377.547, 5.65768, &car1, TRUE);
				SET_CAR_HEADING(car1, 0.0);

				// создаём верталёт
				CREATE_CAR(CarM2, 277.635, -797.568, 4.80212, &car2, TRUE);

				// создаём автомобиль
				CREATE_CAR(CarM3, -29.6848, 283.813, 1.0, &car3, TRUE);// Лодка 1
				CREATE_CAR(CarM4, -22.7851, 283.813, 1.0, &car4, TRUE);// Лодка 2
				CREATE_CAR(CarM5, -15.8854, 283.813, 1.0, &car5, TRUE);// Лодка 3
				CREATE_CAR(CarM6, 282.497, -797.568, 4.80212, &car6, TRUE);// Гермес

				// создаём динамит
				CREATE_OBJECT_NO_OFFSET(dynamite_1, 294.8487, -798.9435, 5.445457, &tnt_1, TRUE);
			
				// педы
				CREATE_CHAR (26, PedM1, 290.970, -770.5, 4.6677, &ped1, TRUE);// 
				CREATE_CHAR (26, PedM1, 290.971, -770.5, 4.6677, &ped2, TRUE);// 
				CREATE_CHAR (26, PedM1, 290.972, -770.5, 4.6677, &ped3, TRUE);// 
				CREATE_CHAR (26, PedM1, 290.973, -770.5, 4.6677, &ped4, TRUE);// 
				CREATE_CHAR (26, PedM1, 290.974, -770.5, 4.6677, &ped5, TRUE);// 
				CREATE_CHAR (26, PedM1, 290.975, -770.5, 4.6677, &ped6, TRUE);// 
				CREATE_CHAR (26, PedM1, 290.976, -770.5, 4.6677, &ped7, TRUE);// 
				CREATE_CHAR (26, PedM1, 290.977, -770.5, 4.6677, &ped8, TRUE);// 
				CREATE_CHAR (26, PedM1, 290.978, -770.5, 4.6677, &ped9, TRUE);//

				// маркер на автомобиле
				ADD_BLIP_FOR_CAR(car1, &haiti_ico);
				CHANGE_BLIP_SPRITE(haiti_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(haiti_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(haiti_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(haiti_ico, "NE_CAR");//иконка на радаре называние в истории карты "Фургон ТОПФАН"

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "HAT2_B1", 5000, 1);//~g~Get to the van that contains the flying bombs.

				// грузим анимации
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				REQUEST_ANIMS( "amb@atm" );//загружаем файл с анимацией
				while (!HAVE_ANIMS_LOADED( "amb@atm" )) WAIT(0);

				REQUEST_ANIMS( "ne_topfun" );//загружаем файл с анимацией
				while (!HAVE_ANIMS_LOADED( "ne_topfun" )) WAIT(0);
				SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, TRUE);

				while (true)
				{
					WAIT( 0 );
					if (IS_CHAR_IN_CAR(GetPlayerPed(), car1))
					{
						REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре
						SetTime(1000);
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

						// вооружаем
						UpdateWeaponOfPed(ped1, WEAPON_MP5);
						UpdateWeaponOfPed(ped2, WEAPON_MP5);
						UpdateWeaponOfPed(ped3, WEAPON_MP5);
						UpdateWeaponOfPed(ped4, WEAPON_MP5);
						UpdateWeaponOfPed(ped5, WEAPON_MP5);
						UpdateWeaponOfPed(ped6, WEAPON_MP5);
						UpdateWeaponOfPed(ped7, WEAPON_MP5);
						UpdateWeaponOfPed(ped8, WEAPON_MP5);
						UpdateWeaponOfPed(ped9, WEAPON_MP5);

						SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_MP5, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_MP5, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_MP5, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_MP5, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_MP5, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_MP5, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_MP5, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_MP5, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_MP5, TRUE);

						TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "topfun_out", "ne_topfun", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						SetTime(2000);

						DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
						while(true)
						{
							WAIT(0);
							if (IS_SCREEN_FADED_OUT())
							{
								break;
							}
						}

						SET_CAR_COORDINATES(car1, -374.205, 377.547, 5.65768 );
						SET_CAR_HEADING(car1, 0.0);
						SET_CAR_COORDINATES(car2, -375.769, 369.225, 5.65768);
						SET_CAR_HEADING(car2, 180.0);
						SET_CAR_LIVERY(car2, 2);
						SET_CAR_HEALTH(car2, 3000);
						SET_ENGINE_HEALTH(car2, 3000);
						SET_PETROL_TANK_HEALTH(car2, 3000);

						SET_CHAR_VISIBLE(GetPlayerPed(), 0); //прозрачный игрок
						TASK_ENTER_CAR_AS_DRIVER(GetPlayerPed(), car2, TRUE);//садим игрока в верталёт

						SET_CHAR_COORDINATES(ped1, -98.1484,281.855,4.77167);// перемещаем игрока
						SET_CHAR_COORDINATES(ped2, -75.7422,296.294,2.4526);// перемещаем игрока
						SET_CHAR_COORDINATES(ped3, -95.5094,294.563,2.4526);// перемещаем игрока
						SET_CHAR_COORDINATES(ped4, -95.0721,296.614,2.4526);// перемещаем игрока
						SET_CHAR_COORDINATES(ped5, -96.9814,295.639,2.4526);// перемещаем игрока
						SET_CHAR_COORDINATES(ped6, -103.829,296.98,2.4526);// перемещаем игрока
						SET_CHAR_COORDINATES(ped7, -84.1499,288.359,4.77167);// перемещаем игрока
						SET_CHAR_COORDINATES(ped8, -84.5231,289.671,4.77167);// перемещаем игрока
						SET_CHAR_COORDINATES(ped9, -85.532,288.178,4.77167);// перемещаем игрока
						SET_CHAR_HEADING(ped1, -170.0);
						SET_CHAR_HEADING(ped2, 0.0);
						SET_CHAR_HEADING(ped3, -5.0);
						SET_CHAR_HEADING(ped4, 170.0);
						SET_CHAR_HEADING(ped5, -95.0);
						SET_CHAR_HEADING(ped6, 0.0);
						SET_CHAR_HEADING(ped7, 55.0);
						SET_CHAR_HEADING(ped8, -170.0);
						SET_CHAR_HEADING(ped9, -60.0);

						SET_CAR_COORDINATES(car3, -82.0904, 306.128, 1.01);
						SET_CAR_COORDINATES(car4, -91.4206, 306.785, 1.01);
						SET_CAR_COORDINATES(car5, -99.4425, 306.564, 1.01);
						SET_CAR_COORDINATES(car6, -97.8436, 279.273, 5.11);
						SET_CAR_HEADING(car3, -70.0);
						SET_CAR_HEADING(car4, 0.0);
						SET_CAR_HEADING(car5, 45.0);
						SET_CAR_HEADING(car6, -175.0);

						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "f_insertcard", "amb@atm", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped3, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped4, "stand_idle_d", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "f_insertcard", "amb@atm", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "stand_idle_d", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped8, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped9, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						SetTime(500);

						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана

						// ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, -86.0409, 295.163, -1.7832 ); // куда смотрит камера
						SET_CAM_POS			( camera, -114.335, 310.239, 11.8853 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "HAT2_B2", 5000, 1);//Kill the Cubans...
						SetTime(4000);

						// Меняем ракурс
						POINT_CAM_AT_COORD	( camera, -100.478 ,299.158, 2.4526 ); // куда смотрит камера
						SET_CAM_POS			( camera, -108.127, 294.953, 5.6447 );//расположение камеры

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "HAT2_B4", 5000, 1);//...and destroy their boats!
						SetTime(4000);

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

						PRINT_HELP("BOLLOX"); //Press the ~h~~INPUT_PHONE_ACCEPT~ ~w~button to drop a bomb. Press the ~h~~INPUT_ENTER~ ~w~button to cancel.

						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
						SET_FOLLOW_VEHICLE_CAM_SUBMODE(2);
						ATTACH_OBJECT_TO_CAR(tnt_1, car2, 0, 0, 0, -0.5, 0, 0, 0);

						ADD_BLIP_FOR_COORD(-95.0721, 296.614, 2.4526, &haiti_ico);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(haiti_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(haiti_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(haiti_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(haiti_ico, "NE_POINT");//иконка на радаре называние в истории карты "Фургон ТОПФАН"
						break;
					}
					// провал миссии
					if (IS_CAR_DEAD(car1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "TEX3_31", 5000, 1);//~r~You destroyed the TOPFUN van that contained the bombs and RC helicopter!
						skip = 3;// переменная пропуска
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
					while (true)
					{
						WAIT( 0 );
						// худ
						DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
						DRAW_SPRITE( hel, 0.8720625, 0.80925926, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.80729167, 0.80277778, "HAT2_B9"); //RC HELICOPTERS:

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.795, "CP_TIME_ZERO", hel_set-1);

						SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// игрок бессмертный
						if ((IS_BUTTON_PRESSED( 0, 16 )) || ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()))) //клавиатура ENTER
						{
							if (attach_1 == 1)
							{
								DETACH_OBJECT(tnt_1, 1);
								APPLY_FORCE_TO_OBJECT(tnt_1, 1, 0.0, 1.0, -3.0, 0, 0, 0, 1, 1, 1, 1);
								PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
								SETTIMERB( 0 );
								attach_1 = 0;
							}
						}
						if (attach_1 == 0)
						{
							GET_OBJECT_COORDINATES(tnt_1,  &PedX, &PedY, &PedZ);//вписываем координаты модели в переменную
							GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &deton);
							if ((PedZ < deton+0.25) || (IS_OBJECT_IN_WATER(tnt_1)) || (TIMERB() > 5000))
							{
								ADD_EXPLOSION( PedX, PedY, PedZ, 0, 5.5, 1, 0, 0.1 );
								ATTACH_OBJECT_TO_CAR(tnt_1, car2, 0, 0, 0, -0.5, 0, 0, 0);
								attach_1 = 1;
							}
							else if ((IS_VEHICLE_TOUCHING_OBJECT(car3, tnt_1)) || (IS_VEHICLE_TOUCHING_OBJECT(car4, tnt_1)) || (IS_VEHICLE_TOUCHING_OBJECT(car5, tnt_1)) || (IS_VEHICLE_TOUCHING_OBJECT(car6, tnt_1)))
							{
								ADD_EXPLOSION( PedX, PedY, PedZ, 0, 5.5, 1, 0, 0.1 );
								ATTACH_OBJECT_TO_CAR(tnt_1, car2, 0, 0, 0, -0.5, 0, 0, 0);
								attach_1 = 1;
							} 
						}

						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -48.02, 263.384, -1.951, -134.821, 350.186, 58.049, 0 ))
						{
							REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре

							ADD_BLIP_FOR_CHAR(ped1, &ped1_ico);
							CHANGE_BLIP_SPRITE(ped1_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped1_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped1_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped1_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_CHAR(ped2, &ped2_ico);
							CHANGE_BLIP_SPRITE(ped2_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped2_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped2_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped2_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_CHAR(ped3, &ped3_ico);
							CHANGE_BLIP_SPRITE(ped3_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped3_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped3_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped3_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_CHAR(ped4, &ped4_ico);
							CHANGE_BLIP_SPRITE(ped4_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped4_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped4_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped4_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_CHAR(ped5, &ped5_ico);
							CHANGE_BLIP_SPRITE(ped5_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped5_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped5_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped5_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_CHAR(ped6, &ped6_ico);
							CHANGE_BLIP_SPRITE(ped6_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped6_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped6_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped6_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_CHAR(ped7, &ped7_ico);
							CHANGE_BLIP_SPRITE(ped7_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped7_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped7_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped7_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_CHAR(ped8, &ped8_ico);
							CHANGE_BLIP_SPRITE(ped8_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped8_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped8_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped8_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_CHAR(ped9, &ped9_ico);
							CHANGE_BLIP_SPRITE(ped9_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped9_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped9_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped9_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							TASK_GO_STRAIGHT_TO_COORD(ped2, -82.4629, 300.063, 2.18294, 3, -2);// пед бежит
							TASK_GO_STRAIGHT_TO_COORD(ped9, -82.4629, 300.063, 2.18294, 3, -2);// пед бежит
							TASK_GO_STRAIGHT_TO_COORD(ped3, -90.7263, 300.063, 2.18294, 3, -2);// пед бежит
							TASK_GO_STRAIGHT_TO_COORD(ped4, -90.7263, 300.063, 2.18294, 3, -2);// пед бежит
							TASK_GO_STRAIGHT_TO_COORD(ped8, -90.7263, 300.063, 2.18294, 3, -2);// пед бежит
							TASK_GO_STRAIGHT_TO_COORD(ped5, -98.9897, 300.063, 2.18294, 3, -2);// пед бежит
							TASK_GO_STRAIGHT_TO_COORD(ped6, -98.9897, 300.063, 2.18294, 3, -2);// пед бежит

							TASK_ENTER_CAR_AS_PASSENGER(ped7, car6, -1, 0);
							TASK_ENTER_CAR_AS_DRIVER(ped1, car6, TRUE);//садим игрока в верталёт

							ATTACH_OBJECT_TO_CAR(tnt_1, car2, 0, 0, 0, -0.5, 0, 0, 0);
							attach_1 = 1;
							SETTIMERC( 0 );
							break;
						}

						if (((IS_CAR_DEAD(car2)) && (hel_set > 0)) || ((GET_ENGINE_HEALTH(car2) < 200) && (hel_set > 0)) || ((IS_CAR_IN_WATER(car2)) && (hel_set > 0)))
						{
							if (hel_set > 1)
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
								SET_CAR_COORDINATES(car2, 0.01, 0.01, -10.01);
								MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)

								CREATE_CAR(CarM2, -375.769, 369.225, 5.65768, &car2, TRUE);
								SET_CAR_HEADING(car2, 180.0);
								SET_CAR_LIVERY(car2, 2);
								SET_CAR_HEALTH(car2, 3000);
								SET_ENGINE_HEALTH(car2, 3000);
								SET_PETROL_TANK_HEALTH(car2, 3000);
								TASK_ENTER_CAR_AS_DRIVER(GetPlayerPed(), car2, TRUE);//садим игрока в верталёт
							
								DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

								DETACH_OBJECT(tnt_1, 1);
								ADD_EXPLOSION( PedX, PedY, PedZ, 0, 5.5, 1, 0, 0.1 );
								ATTACH_OBJECT_TO_CAR(tnt_1, car2, 0, 0, 0, -0.5, 0, 0, 0);
								attach_1 = 1;
							}
							hel_set -= 1;
						}

						// провал миссии
						if (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))//если игрок покинул или унечтожел вертолёт, тогда провал миссии
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NERCCANX", 5000, 1);//~r~RC helicopter cancelled.
							EXPLODE_CAR(car2, 1, 1);
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CAR_DEAD(car1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "TEX3_31", 5500, 1);//~r~You destroyed the TOPFUN van that contained the bombs and RC helicopter!
							SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);
							skip = 1;// переменная пропуска
							EXPLODE_CHAR_HEAD(GetPlayerPed());
							break;
						}
						else if (hel_set  == 0)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NEHAT2_B8", 5000, 1);//~r~You have no RC helicopters left!
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
						GET_CHAR_HEALTH(ped1, &ped1_hp);
						GET_CHAR_HEALTH(ped2, &ped2_hp);
						GET_CHAR_HEALTH(ped3, &ped3_hp);
						GET_CHAR_HEALTH(ped4, &ped4_hp);
						GET_CHAR_HEALTH(ped5, &ped5_hp);
						GET_CHAR_HEALTH(ped6, &ped6_hp);
						GET_CHAR_HEALTH(ped7, &ped7_hp);
						GET_CHAR_HEALTH(ped8, &ped8_hp);
						GET_CHAR_HEALTH(ped9, &ped9_hp);

						// худ
						DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
						DRAW_SPRITE( hel, 0.8720625, 0.80925926, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.80729167, 0.80277778, "HAT2_B9"); //RC HELICOPTERS:

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.795, "CP_TIME_ZERO", hel_set-1);

						if (((IS_CAR_DEAD(car2)) && (hel_set > 0)) || ((GET_ENGINE_HEALTH(car2) < 200) && (hel_set > 0)) || ((IS_CAR_IN_WATER(car2)) && (hel_set > 0)))
						{
							if (hel_set > 1)
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

								SET_CAR_COORDINATES(car2, 0.01, 0.01, -10.01);
								MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)

								CREATE_CAR(CarM2, -375.769, 369.225, 5.65768, &car2, TRUE);
								SET_CAR_HEADING(car2, 180.0);
								SET_CAR_LIVERY(car2, 2);
								SET_CAR_HEALTH(car2, 3000);
								SET_ENGINE_HEALTH(car2, 3000);
								SET_PETROL_TANK_HEALTH(car2, 3000);
								TASK_ENTER_CAR_AS_DRIVER(GetPlayerPed(), car2, TRUE);//садим игрока в верталёт
							
								DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

								DETACH_OBJECT(tnt_1, 1);
								ADD_EXPLOSION( PedX, PedY, PedZ, 0, 5.5, 1, 0, 0.1 );
								ATTACH_OBJECT_TO_CAR(tnt_1, car2, 0, 0, 0, -0.5, 0, 0, 0);
								attach_1 = 1;
							}
							hel_set -= 1;
						}

						if ((in_car == 0) && (TIMERC() > 4000))
						{
							WARP_CHAR_INTO_CAR(ped2, car3);
							WARP_CHAR_INTO_CAR(ped4, car4);
							WARP_CHAR_INTO_CAR(ped5, car5);
							WARP_CHAR_INTO_CAR(ped1, car6);
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped6, car5, 0);
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped3, car4, 0);
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped8, car4, 1);
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped9, car3, 0);
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped7, car6, 0);

							TASK_CAR_DRIVE_WANDER(ped2, car3, 20.0, 2);// пед едит куда-то
							TASK_CAR_DRIVE_WANDER(ped4, car4, 20.0, 2);// пед едит куда-то
							TASK_CAR_DRIVE_WANDER(ped5, car5, 20.0, 2);// пед едит куда-то

							//------------ загрузка путей ----------------
							REQUEST_CAR_RECORDING( 3060 );
							while (!HAS_CAR_RECORDING_BEEN_LOADED( 3060 )) WAIT(0);
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car6, 3060, 0.0, 0.0, 0.0);
							path_on = 1;

							SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);

							SET_CHAR_RELATIONSHIP(ped3, 5, 0);
							SET_CHAR_RELATIONSHIP(ped6, 5, 0);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);
							SET_CHAR_RELATIONSHIP(ped8, 5, 0);
							SET_CHAR_RELATIONSHIP(ped9, 5, 0);

							SET_SENSE_RANGE(ped3, 80.0);
							SET_SENSE_RANGE(ped6, 80.0);
							SET_SENSE_RANGE(ped7, 80.0);
							SET_SENSE_RANGE(ped8, 80.0);
							SET_SENSE_RANGE(ped9, 80.0);

							SET_CHAR_WILL_USE_COVER(ped3, 1);
							SET_CHAR_WILL_USE_COVER(ped6, 1);
							SET_CHAR_WILL_USE_COVER(ped7, 1);
							SET_CHAR_WILL_USE_COVER(ped8, 1);
							SET_CHAR_WILL_USE_COVER(ped9, 1);
							in_car = 1;

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "HAT2_B5", 5000, 1);//~g~The Cubans are making a run for it. Don't let them get away!

							SETTIMERC( 0 );
						}
						else if ((in_car == 1) && (TIMERC() > 15000))
						{
							STOP_PLAYBACK_RECORDED_CAR(car6);
							REMOVE_CAR_RECORDING( 3060 ); // выгружаем пути транспорта

							TASK_CAR_DRIVE_WANDER(ped1, car6, 20.0, 2);// пед едит куда-то

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "HAT2_B7", 5000, 1);//~g~One of the Cubans in escaping in a car. Don't leave any witnesses!

							path_on = 0;
							in_car = 2;
						}

						SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 1);// игрок бессмертный
						if ((IS_BUTTON_PRESSED( 0, 16 )) || ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()))) //клавиатура ENTER
						{
							if (attach_1 == 1)
							{
								DETACH_OBJECT(tnt_1, 1);
								APPLY_FORCE_TO_OBJECT(tnt_1, 1, 0.0, 1.0, -2.5, 0, 0, 0, 1, 1, 1, 1);
								PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
								SETTIMERB( 0 );
								attach_1 = 0;
							}
						}
						if (attach_1 == 0)
						{
							GET_OBJECT_COORDINATES(tnt_1,  &PedX, &PedY, &PedZ);//вписываем координаты модели в переменную
							GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &deton);
							if ((PedZ < deton+0.25) || (IS_OBJECT_IN_WATER(tnt_1)) || (TIMERB() > 5000))
							{
								ADD_EXPLOSION( PedX, PedY, PedZ, 0, 5.5, 1, 0, 0.1 );
								ATTACH_OBJECT_TO_CAR(tnt_1, car2, 0, 0, 0, -0.5, 0, 0, 0);
								attach_1 = 1;
							}
							else if ((IS_VEHICLE_TOUCHING_OBJECT(car3, tnt_1)) || (IS_VEHICLE_TOUCHING_OBJECT(car4, tnt_1)) || (IS_VEHICLE_TOUCHING_OBJECT(car5, tnt_1)) || (IS_VEHICLE_TOUCHING_OBJECT(car6, tnt_1)))
							{
								ADD_EXPLOSION( PedX, PedY, PedZ, 0, 5.5, 1, 0, 0.1 );
								ATTACH_OBJECT_TO_CAR(tnt_1, car2, 0, 0, 0, -0.5, 0, 0, 0);
								attach_1 = 1;
							} 
						}

						if ((ped1_hp < 100) && (ico_1 == 1))
						{
							REMOVE_BLIP(ped1_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped1);
							ico_1 = 0;
						}
						if ((ped2_hp < 100) && (ico_2 == 1))
						{
							REMOVE_BLIP(ped2_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped2);
							ico_2 = 0;
						}
						if ((ped3_hp < 100) && (ico_3 == 1))
						{
							REMOVE_BLIP(ped3_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped3);
							ico_3 = 0;
						}
						if ((ped4_hp < 100) && (ico_4 == 1))
						{
							REMOVE_BLIP(ped4_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped4);
							ico_4 = 0;
						}
						if ((ped5_hp < 100) && (ico_5 == 1))
						{
							REMOVE_BLIP(ped5_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped5);
							ico_5 = 0;
						}
						if ((ped6_hp < 100) && (ico_6 == 1))
						{
							REMOVE_BLIP(ped6_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped6);
							ico_6 = 0;
						}
						if ((ped7_hp < 100) && (ico_7 == 1))
						{
							REMOVE_BLIP(ped7_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped7);
							ico_7 = 0;
						}
						if ((ped8_hp < 100) && (ico_8 == 1))
						{
							REMOVE_BLIP(ped8_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped8);
							ico_8 = 0;
						}
						if ((ped9_hp < 100) && (ico_9 == 1))
						{
							REMOVE_BLIP(ped9_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped9);
							ico_9 = 0;
						}

						if ((ico_1 == 0) && (ico_2 == 0) && (ico_3 == 0) && (ico_4 == 0) && (ico_5 == 0) && (ico_6 == 0) && (ico_7 == 0) && (ico_8 == 0) && (ico_9 == 0))
						{
							skip = 2;// переменная пропуска
							//TASK_ENTER_CAR_AS_PASSENGER(GetPlayerIndex(), car1, -1, 1);
							break;
						}
						// провал миссии
						if (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NERCCANX", 5000, 1);//~r~RC helicopter cancelled.
							EXPLODE_CAR(car2, 1, 1);
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CAR_DEAD(car1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "TEX3_31", 5500, 1);//~r~You destroyed the TOPFUN van that contained the bombs and RC helicopter!
							SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0);
							skip = 1;// переменная пропуска
							EXPLODE_CHAR_HEAD(GetPlayerPed());
							break;
						}
						else if (hel_set  == 0)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NEHAT2_B8", 5000, 1);//~r~You have no RC helicopters left!
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
				/// чистим скрипт тут

				if ((skip == 1) || (skip == 2))
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

					WARP_CHAR_INTO_CAR(GetPlayerPed(), car1);
					DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
					WAIT(100);
					SET_PLAYER_INVINCIBLE(GetPlayerIndex(), 0); // смертный
					SET_CHAR_VISIBLE(GetPlayerPed(), 1); // видимый игрок

					if ((!IS_CHAR_DEAD(GetPlayerPed())) && (!HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "topfun_in", "ne_topfun", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						SetTime(1500);
					}
				}

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				SET_CAR_COORDINATES(car2, 0.01, 0.01, -10.01);

				if (path_on == 1)
				{
					STOP_PLAYBACK_RECORDED_CAR(car6);
					REMOVE_CAR_RECORDING( 3060 ); // выгружаем пути транспорта
				}

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( hel );
				REMOVE_TXD( textur );

				REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped1_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped2_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped3_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped4_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped5_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped6_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped7_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped8_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped9_ico);//Удаляем иконку на радаре

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM5);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM6);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(dynamite_1);//выгружаем модель

				// выгружвем машину
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car6);//выгружаем модель машины(в последствии машина изчезнет)

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


				// удаляем объекты
				DELETE_OBJECT(&tnt_1);

				// выгружаем динамит
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&tnt_1);

				if ((skip == 1) || (skip == 3))
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_HAT_2" );//Bombs Away!
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(2000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +2000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 2000);
					G_HAITI = 3;
					autosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}
//============================== Dirty Lickin's ======================================
		else if ((G_ONMISSION == 0) && (G_HAITI == 3))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-529.349, 677.904, 3.32976, &haiti_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(haiti_ico, BLIP_RANSOM);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(haiti_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(haiti_ico, "LG_14");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( -529.349, 677.904, 3.32976, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -529.349, 677.904, 3.32976, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("HAT_3", 15000, CUTSCENE_HAITIAN);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-957.904, 122.843, 8.278, 356.948);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре
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

				SET_CHAR_COORDINATES(GetPlayerPed(), -529.452, 675.58, 3.45918 );// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 180.0 );
				
				uint hour, minute, weather;
				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 55);//устанавливаем время
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "HAT_3", 6 ); // загружаем субтитры из *.GTX
																	
							
				START_CUTSCENE_NOW("hat_3");
		
								   
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

				Car car1;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20;
				Blip ped1_ico, ped2_ico, ped3_ico, ped4_ico, ped5_ico, ped6_ico, ped7_ico, ped8_ico, ped9_ico, ped10_ico;
				int dm, cdm;

				uint PedM1 = MODEL_M_M_GJAM_HI_01;// Гаитянин
				uint PedM2 = MODEL_M_Y_GLAT_HI_01;// Кубинец
				uint CarM1 = MODEL_BURRITO;// фургон

				uint ped1_hp, ped2_hp, ped3_hp, ped4_hp, ped5_hp, ped6_hp, ped7_hp, ped8_hp, ped9_hp, ped10_hp;
				uint ped11_hp, ped12_hp, ped13_hp, ped14_hp, ped15_hp, ped16_hp, ped17_hp, ped18_hp, ped19_hp, ped20_hp;
			
				skip = 0;
				ico_1 = 1;
				ico_2 = 1;
				ico_3 = 1;
				ico_4 = 1;
				ico_5 = 1;
				ico_6 = 1;
				ico_7 = 1;
				ico_8 = 1;
				ico_9 = 1;
				ico_10 = 1;
				volna_1 = 0;
				volna_2 = 0;
				in_car = 1;
				text = 0;

				// загрузаем автомобиль
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);

				REQUEST_MODEL(PedM1);// 
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// 
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало

				CREATE_CHAR (26, PedM1, -446.221, 573.818, 4.47146, &ped1, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM1, -449.742, 576.932, 4.09862, &ped2, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM1, -455.343, 576.791, 4.47146, &ped3, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM1, -458.604, 581.879, 3.96489, &ped4, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM1, -461.851, 575.531, 4.47146, &ped5, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM1, -462.547, 579.456, 4.47146, &ped6, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM1, -466.388, 576.574, 4.47146, &ped7, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM1, -465.051, 584.207, 3.80116, &ped8, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM1, -471.211, 578.552, 4.47146, &ped9, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM1, -469.951, 582.437, 4.47146, &ped10, TRUE);// Гаитянин

				SET_CHAR_HEADING(ped1, 50.0);
				SET_CHAR_HEADING(ped2, 50.0);
				SET_CHAR_HEADING(ped3, 50.0);
				SET_CHAR_HEADING(ped4, 50.0);
				SET_CHAR_HEADING(ped5, 50.0);
				SET_CHAR_HEADING(ped6, 50.0);
				SET_CHAR_HEADING(ped7, 50.0);
				SET_CHAR_HEADING(ped8, 50.0);
				SET_CHAR_HEADING(ped9, 50.0);
				SET_CHAR_HEADING(ped10, 50.0);

				CREATE_CHAR (26, PedM2, -447.087, 574.221, 4.47146, &ped11, TRUE);// Кубинец
				CREATE_CHAR (26, PedM2, -450.608, 577.334, 4.09862, &ped12, TRUE);// Кубинец
				CREATE_CHAR (26, PedM2, -456.211, 577.192, 4.47146, &ped13, TRUE);// Кубинец
				CREATE_CHAR (26, PedM2, -462.717, 575.933, 4.47146, &ped14, TRUE);// Кубинец
				CREATE_CHAR (26, PedM2, -459.471, 582.281, 3.96489, &ped15, TRUE);// Кубинец
				CREATE_CHAR (26, PedM2, -463.413, 579.858, 4.47146, &ped16, TRUE);// Кубинец
				CREATE_CHAR (26, PedM2, -467.254, 576.976, 4.47146, &ped17, TRUE);// Кубинец
				CREATE_CHAR (26, PedM2, -465.916, 584.611, 3.80116, &ped18, TRUE);// Кубинец
				CREATE_CHAR (26, PedM2, -472.076, 578.954, 4.47146, &ped19, TRUE);// Кубинец
				CREATE_CHAR (26, PedM2, -470.817, 582.839, 4.47146, &ped20, TRUE);// Кубинец
				SET_CHAR_HEADING(ped11, 120.0);
				SET_CHAR_HEADING(ped12, 120.0);
				SET_CHAR_HEADING(ped13, 120.0);
				SET_CHAR_HEADING(ped14, 120.0);
				SET_CHAR_HEADING(ped15, 120.0);
				SET_CHAR_HEADING(ped16, 120.0);
				SET_CHAR_HEADING(ped17, 120.0);
				SET_CHAR_HEADING(ped18, 120.0);
				SET_CHAR_HEADING(ped19, 120.0);
				SET_CHAR_HEADING(ped20, 120.0);

				CREATE_CAR(CarM1, 299.551, -787.416, 5.44546, &car1, TRUE);// Фургон 

				LOAD_CHAR_DECISION_MAKER(2, &dm);
				LOAD_COMBAT_DECISION_MAKER(3, &cdm);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				// лояльность игроку
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 18);
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 18);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 18);
				SET_CHAR_RELATIONSHIP_GROUP(ped4, 18);
				SET_CHAR_RELATIONSHIP_GROUP(ped5, 18);
				SET_CHAR_RELATIONSHIP_GROUP(ped6, 18);
				SET_CHAR_RELATIONSHIP_GROUP(ped7, 18);
				SET_CHAR_RELATIONSHIP_GROUP(ped8, 18);
				SET_CHAR_RELATIONSHIP_GROUP(ped9, 18);
				SET_CHAR_RELATIONSHIP_GROUP(ped10, 18);

				SET_CHAR_RELATIONSHIP(ped1, 5, 17);
				SET_CHAR_RELATIONSHIP(ped2, 5, 17);
				SET_CHAR_RELATIONSHIP(ped3, 5, 17);
				SET_CHAR_RELATIONSHIP(ped4, 5, 17);
				SET_CHAR_RELATIONSHIP(ped5, 5, 17);
				SET_CHAR_RELATIONSHIP(ped6, 5, 17);
				SET_CHAR_RELATIONSHIP(ped7, 5, 17);
				SET_CHAR_RELATIONSHIP(ped8, 5, 17);
				SET_CHAR_RELATIONSHIP(ped9, 5, 17);
				SET_CHAR_RELATIONSHIP(ped10, 5, 17);
				
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

				//Агрим педов
				SET_CHAR_RELATIONSHIP_GROUP(ped11, 17);
				SET_CHAR_RELATIONSHIP_GROUP(ped12, 17);
				SET_CHAR_RELATIONSHIP_GROUP(ped13, 17);
				SET_CHAR_RELATIONSHIP_GROUP(ped14, 17);
				SET_CHAR_RELATIONSHIP_GROUP(ped15, 17);
				SET_CHAR_RELATIONSHIP_GROUP(ped16, 17);
				SET_CHAR_RELATIONSHIP_GROUP(ped17, 17);
				SET_CHAR_RELATIONSHIP_GROUP(ped18, 17);
				SET_CHAR_RELATIONSHIP_GROUP(ped19, 17);
				SET_CHAR_RELATIONSHIP_GROUP(ped20, 17);

				SET_CHAR_RELATIONSHIP(ped11, 5, 18);
				SET_CHAR_RELATIONSHIP(ped12, 5, 18);
				SET_CHAR_RELATIONSHIP(ped13, 5, 18);
				SET_CHAR_RELATIONSHIP(ped14, 5, 18);
				SET_CHAR_RELATIONSHIP(ped15, 5, 18);
				SET_CHAR_RELATIONSHIP(ped16, 5, 18);
				SET_CHAR_RELATIONSHIP(ped17, 5, 18);
				SET_CHAR_RELATIONSHIP(ped18, 5, 18);
				SET_CHAR_RELATIONSHIP(ped19, 5, 18);
				SET_CHAR_RELATIONSHIP(ped20, 5, 18);

				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, FALSE);
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

				ADD_BLIP_FOR_CHAR(ped11, &ped1_ico);
				CHANGE_BLIP_SPRITE(ped1_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(ped1_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(ped1_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped1_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				ADD_BLIP_FOR_CHAR(ped12, &ped2_ico);
				CHANGE_BLIP_SPRITE(ped2_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(ped2_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(ped2_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped2_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				ADD_BLIP_FOR_CHAR(ped13, &ped3_ico);
				CHANGE_BLIP_SPRITE(ped3_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(ped3_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(ped3_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped3_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				ADD_BLIP_FOR_CHAR(ped14, &ped4_ico);
				CHANGE_BLIP_SPRITE(ped4_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(ped4_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(ped4_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped4_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				ADD_BLIP_FOR_CHAR(ped15, &ped5_ico);
				CHANGE_BLIP_SPRITE(ped5_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(ped5_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(ped5_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped5_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				ADD_BLIP_FOR_CHAR(ped16, &ped6_ico);
				CHANGE_BLIP_SPRITE(ped6_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(ped6_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(ped6_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped6_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				ADD_BLIP_FOR_CHAR(ped17, &ped7_ico);
				CHANGE_BLIP_SPRITE(ped7_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(ped7_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(ped7_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped7_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				ADD_BLIP_FOR_CHAR(ped18, &ped8_ico);
				CHANGE_BLIP_SPRITE(ped8_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(ped8_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(ped8_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped8_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				ADD_BLIP_FOR_CHAR(ped19, &ped9_ico);
				CHANGE_BLIP_SPRITE(ped9_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(ped9_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(ped9_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped9_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				ADD_BLIP_FOR_CHAR(ped20, &ped10_ico);
				CHANGE_BLIP_SPRITE(ped10_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(ped10_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(ped10_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped10_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				ADD_BLIP_FOR_COORD(-462.814, 610.598, 9.89533, &haiti_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(haiti_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(haiti_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(haiti_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(haiti_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

				GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_EPISODIC_15, 35, FALSE);
				SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_EPISODIC_15, TRUE);

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "HAM3_1", 5000, 1);//~g~We must win this battle. If all the Haitians die we lose.
				PRINT_STRING_IN_STRING("string", "HAM3_5", 5000, 1);//~g~You must kill the Cubans from a distance. You must not be seen.


				while (TRUE)
				{
					WAIT(0);
					DRAW_CHECKPOINT( -462.814, 610.598, 9.89533, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -462.814, 610.598, 9.89533, &PlayR);//проверка "игрок на координатах"
					if ( PlayR < 2.5 )
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "HAM3_3", 5000, 1);//~g~I expect the Cubans to cheat so be on your guard.

						REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре
						SET_MAX_WANTED_LEVEL(0);
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -432.665, 547.768, 2.627, -502.665, 597.768, 12.627, 0 )) ||  (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), -321.538, 428.19, -621.538, 728.19, 0)))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "HAM3_4", 5000, 1);//~r~You have been spotted! The mission is a failure!
						skip = 1;// переменная пропуска
						break;
					}
				}

				//
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						GET_CHAR_HEALTH(ped1, &ped1_hp);
						GET_CHAR_HEALTH(ped2, &ped2_hp);
						GET_CHAR_HEALTH(ped3, &ped3_hp);
						GET_CHAR_HEALTH(ped4, &ped4_hp);
						GET_CHAR_HEALTH(ped5, &ped5_hp);
						GET_CHAR_HEALTH(ped6, &ped6_hp);
						GET_CHAR_HEALTH(ped7, &ped7_hp);
						GET_CHAR_HEALTH(ped8, &ped8_hp);
						GET_CHAR_HEALTH(ped9, &ped9_hp);
						GET_CHAR_HEALTH(ped10, &ped10_hp);

						GET_CHAR_HEALTH(ped11, &ped11_hp);
						GET_CHAR_HEALTH(ped12, &ped12_hp);
						GET_CHAR_HEALTH(ped13, &ped13_hp);
						GET_CHAR_HEALTH(ped14, &ped14_hp);
						GET_CHAR_HEALTH(ped15, &ped15_hp);
						GET_CHAR_HEALTH(ped16, &ped16_hp);
						GET_CHAR_HEALTH(ped17, &ped17_hp);
						GET_CHAR_HEALTH(ped18, &ped18_hp);
						GET_CHAR_HEALTH(ped19, &ped19_hp);
						GET_CHAR_HEALTH(ped20, &ped20_hp);

						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную

						if ((ped11_hp < 100) && (ico_1 == 1))
						{
							REMOVE_BLIP(ped1_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped11);
							ico_1 = 0;
							volna_1 +=1;
						}
						if ((ped12_hp < 100) && (ico_2 == 1))
						{
							REMOVE_BLIP(ped2_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped12);
							ico_2 = 0;
							volna_1 +=1;
						}
						if ((ped13_hp < 100) && (ico_3 == 1))
						{
							REMOVE_BLIP(ped3_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped13);
							ico_3 = 0;
							volna_1 +=1;
						}
						if ((ped14_hp < 100) && (ico_4 == 1))
						{
							REMOVE_BLIP(ped4_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped14);
							ico_4 = 0;
							volna_1 +=1;
						}

						if ((ped15_hp < 100) && (ico_5 == 1))
						{
							REMOVE_BLIP(ped5_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped15);
							ico_5 = 0;
							volna_2 +=1;
						}
						if ((ped16_hp < 100) && (ico_6 == 1))
						{
							REMOVE_BLIP(ped6_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped16);
							ico_6 = 0;
							volna_2 +=1;
						}
						if ((ped17_hp < 100) && (ico_7 == 1))
						{
							REMOVE_BLIP(ped7_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped17);
							ico_7 = 0;
							volna_2 +=1;
						}
						if ((ped18_hp < 100) && (ico_8 == 1))
						{
							REMOVE_BLIP(ped8_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped18);
							ico_8 = 0;
							volna_2 +=1;
						}
						if ((ped19_hp < 100) && (ico_9 == 1))
						{
							REMOVE_BLIP(ped9_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped19);
							ico_9 = 0;
							volna_2 +=1;
						}
						if ((ped20_hp < 100) && (ico_10 == 1))
						{
							REMOVE_BLIP(ped10_ico);//Удаляем иконку на радаре
							EXPLODE_CHAR_HEAD(ped20);
							ico_10 = 0;
							volna_2 +=1;
						}


						if (volna_1 == 4)
						{
							// Пды на фургоне тут
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "HAM3_7", 5000, 1);//~g~Look Out! The Cubans have brought reinforcements. Kill them all!!

							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped11);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped12);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped13);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped14);//выгружаем модель педа(в последствии пед изчезнет
							WAIT(100);
							CLEAR_AREA(-452.428, 572.987, 1.64151, 45.0, 1);//очещаем зону загрузки

							CREATE_CHAR_AS_PASSENGER(car1, 1, PedM2, 0, &ped11);// Кубинкц
							CREATE_CHAR_AS_PASSENGER(car1, 1, PedM2, 1, &ped12);// Кубинкц
							CREATE_CHAR_AS_PASSENGER(car1, 1, PedM2, 2, &ped13);// Кубинкц
							CREATE_CHAR_INSIDE_CAR(car1, 1, PedM2, &ped14);// Кубинкц

							CLEAR_AREA(-493.221, 565.447, 5.33107, 15.0, 1);//очещаем зону загрузки
							
							REQUEST_CAR_RECORDING( 3061 ); // полёт Основной
							while (!HAS_CAR_RECORDING_BEEN_LOADED( 3061 )) WAIT(0);
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3061, 0.0, 0.0, 0.0);
							SETTIMERA( 0 );

							ADD_BLIP_FOR_CHAR(ped11, &ped1_ico);
							CHANGE_BLIP_SPRITE(ped1_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped1_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped1_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped1_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_CHAR(ped12, &ped2_ico);
							CHANGE_BLIP_SPRITE(ped2_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped2_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped2_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped2_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_CHAR(ped13, &ped3_ico);
							CHANGE_BLIP_SPRITE(ped3_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped3_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped3_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped3_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_CHAR(ped14, &ped4_ico);
							CHANGE_BLIP_SPRITE(ped4_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped4_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped4_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped4_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ico_1 = 1;
							ico_2 = 1;
							ico_3 = 1;
							ico_4 = 1;
							in_car = 2;
							volna_1 = 99;
						}

						if (in_car == 2)
						{
							if (TIMERA() > 5500)
							{
								STOP_PLAYBACK_RECORDED_CAR(car1);
								REMOVE_CAR_RECORDING( 3061 ); // выгружаем пути транспорта

								TASK_GO_STRAIGHT_TO_COORD(ped11, -462.547, 579.456, 4.47146, 3, -2);// Томми бежит в двери
								TASK_GO_STRAIGHT_TO_COORD(ped12, -462.547, 579.456, 4.47146, 3, -2);// Томми бежит в двери
								TASK_GO_STRAIGHT_TO_COORD(ped13, -462.547, 579.456, 4.47146, 3, -2);// Томми бежит в двери
								TASK_GO_STRAIGHT_TO_COORD(ped14, -462.547, 579.456, 4.47146, 3, -2);// Томми бежит в двери

								/*TASK_LEAVE_CAR(ped11, car1);
								TASK_LEAVE_CAR(ped12, car1);
								TASK_LEAVE_CAR(ped13, car1);
								TASK_LEAVE_CAR(ped14, car1);*/

								SET_CHAR_RELATIONSHIP_GROUP(ped11, 17);
								SET_CHAR_RELATIONSHIP_GROUP(ped12, 17);
								SET_CHAR_RELATIONSHIP_GROUP(ped13, 17);
								SET_CHAR_RELATIONSHIP_GROUP(ped14, 17);

								SET_CHAR_RELATIONSHIP(ped11, 5, 18);
								SET_CHAR_RELATIONSHIP(ped12, 5, 18);
								SET_CHAR_RELATIONSHIP(ped13, 5, 18);
								SET_CHAR_RELATIONSHIP(ped14, 5, 18);

								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, FALSE);

								SET_CHAR_DECISION_MAKER(ped11, dm);
								SET_CHAR_DECISION_MAKER(ped12, dm);
								SET_CHAR_DECISION_MAKER(ped13, dm);
								SET_CHAR_DECISION_MAKER(ped14, dm);

								SET_COMBAT_DECISION_MAKER(ped11, cdm);
								SET_COMBAT_DECISION_MAKER(ped12, cdm);
								SET_COMBAT_DECISION_MAKER(ped13, cdm);
								SET_COMBAT_DECISION_MAKER(ped14, cdm);

								in_car = 0;
							}
						}

						//
						if ( volna_2 == 6)
						{
							// Педы из переулка
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "HAM3_7", 5000, 1);//~g~Look Out! The Cubans have brought reinforcements. Kill them all!!

							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped15);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped16);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped17);//выгружаем модель педа(в последствии пед изчезнет
							//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped18);//выгружаем модель педа(в последствии пед изчезнет
							//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped19);//выгружаем модель педа(в последствии пед изчезнет
							//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped20);//выгружаем модель педа(в последствии пед изчезнет
							WAIT(250);
							CLEAR_AREA(-452.428, 572.987, 1.64151, 45.0, 1);//очещаем зону загрузки

							CREATE_CHAR (26, PedM2, -439.793, 598.086, 3.96489, &ped15, TRUE);// Кубинец
							CREATE_CHAR (26, PedM2, -439.569, 598.815, 3.68376, &ped16, TRUE);// Кубинец
							CREATE_CHAR (26, PedM2, -439.609, 599.902, 3.68376, &ped17, TRUE);// Кубинец
							//CREATE_CHAR (26, PedM2, -439.571, 600.885, 3.68376, &ped18, TRUE);// Кубинец
							//CREATE_CHAR (26, PedM2, -439.361, 601.755, 3.68376, &ped19, TRUE);// Кубинец
							//CREATE_CHAR (26, PedM2, -439.061, 602.696, 3.68376, &ped20, TRUE);// Кубинец

							SET_CHAR_HEADING(ped15, 165.0);
							SET_CHAR_HEADING(ped16, 165.0);
							SET_CHAR_HEADING(ped17, 165.0);
							//SET_CHAR_HEADING(ped18, 165.0);
							//SET_CHAR_HEADING(ped19, 165.0);
							//SET_CHAR_HEADING(ped20, 165.0);

							TASK_GO_STRAIGHT_TO_COORD(ped15, -462.547, 579.456, 4.47146, 3, -2);// Томми бежит в двери
							TASK_GO_STRAIGHT_TO_COORD(ped16, -462.547, 579.456, 4.47146, 3, -2);// Томми бежит в двери
							TASK_GO_STRAIGHT_TO_COORD(ped17, -462.547, 579.456, 4.47146, 3, -2);// Томми бежит в двери
							//TASK_GO_STRAIGHT_TO_COORD(ped18, -462.547, 579.456, 4.47146, 3, -2);// Томми бежит в двери
							//TASK_GO_STRAIGHT_TO_COORD(ped19, -462.547, 579.456, 4.47146, 3, -2);// Томми бежит в двери
							//TASK_GO_STRAIGHT_TO_COORD(ped20, -462.547, 579.456, 4.47146, 3, -2);// Томми бежит в двери

							SET_CHAR_RELATIONSHIP_GROUP(ped15, 17);
							SET_CHAR_RELATIONSHIP_GROUP(ped16, 17);
							SET_CHAR_RELATIONSHIP_GROUP(ped17, 17);
							//SET_CHAR_RELATIONSHIP_GROUP(ped18, 17);
							//SET_CHAR_RELATIONSHIP_GROUP(ped19, 17);
							//SET_CHAR_RELATIONSHIP_GROUP(ped20, 17);

							SET_CHAR_RELATIONSHIP(ped15, 5, 18);
							SET_CHAR_RELATIONSHIP(ped16, 5, 18);
							SET_CHAR_RELATIONSHIP(ped17, 5, 18);
							//SET_CHAR_RELATIONSHIP(ped18, 5, 18);
							//SET_CHAR_RELATIONSHIP(ped19, 5, 18);
							//SET_CHAR_RELATIONSHIP(ped20, 5, 18);

							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, FALSE);
							//SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, FALSE);
							//SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, FALSE);
							//SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, FALSE);

							SET_CHAR_DECISION_MAKER(ped15, dm);
							SET_CHAR_DECISION_MAKER(ped16, dm);
							SET_CHAR_DECISION_MAKER(ped17, dm);
							//SET_CHAR_DECISION_MAKER(ped18, dm);
							//SET_CHAR_DECISION_MAKER(ped19, dm);
							//SET_CHAR_DECISION_MAKER(ped20, dm);

							SET_COMBAT_DECISION_MAKER(ped15, cdm);
							SET_COMBAT_DECISION_MAKER(ped16, cdm);
							SET_COMBAT_DECISION_MAKER(ped17, cdm);
							//SET_COMBAT_DECISION_MAKER(ped18, cdm);
							//SET_COMBAT_DECISION_MAKER(ped19, cdm);
							//SET_COMBAT_DECISION_MAKER(ped20, cdm);

							ADD_BLIP_FOR_CHAR(ped15, &ped5_ico);
							CHANGE_BLIP_SPRITE(ped5_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped5_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped5_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped5_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_CHAR(ped16, &ped6_ico);
							CHANGE_BLIP_SPRITE(ped6_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped6_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped6_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped6_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_CHAR(ped17, &ped7_ico);
							CHANGE_BLIP_SPRITE(ped7_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(ped7_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(ped7_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped7_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							//ADD_BLIP_FOR_CHAR(ped18, &ped8_ico);
							//CHANGE_BLIP_SPRITE(ped8_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							//CHANGE_BLIP_COLOUR(ped8_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							//CHANGE_BLIP_SCALE(ped8_ico, 0.6); // масштаб иконки на радаре
							//CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped8_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							//ADD_BLIP_FOR_CHAR(ped19, &ped9_ico);
							//CHANGE_BLIP_SPRITE(ped9_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							//CHANGE_BLIP_COLOUR(ped9_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							//CHANGE_BLIP_SCALE(ped9_ico, 0.6); // масштаб иконки на радаре
							//CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped9_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							//ADD_BLIP_FOR_CHAR(ped20, &ped10_ico);
							//CHANGE_BLIP_SPRITE(ped10_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							//CHANGE_BLIP_COLOUR(ped10_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							//CHANGE_BLIP_SCALE(ped10_ico, 0.6); // масштаб иконки на радаре
							//CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped10_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							UpdateWeaponOfPed(ped15, WEAPON_EPISODIC_4);
							SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_EPISODIC_4, TRUE);

							ico_5 = 1;
							ico_6 = 1;
							ico_7 = 1;
							//ico_8 = 1;
							//ico_9 = 1;
							//ico_10 = 1;
							volna_2 = 99;
						}
						//*/
						if ((ped1_hp < 100) && (ped2_hp < 100) && (ped3_hp < 100) && (ped8_hp < 100) && (ped10_hp < 100) && (text == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "HAM3_8", 5000, 1);//~g~Haitians are dying! Improve your aim.
							text = 1;
						}

						if ((ped1_hp < 100) && (ped2_hp < 100) && (ped3_hp < 100) && (ped4_hp < 100) && (ped5_hp < 100) && (ped6_hp < 100) && (ped7_hp < 100) && (ped8_hp < 100) && (ped9_hp < 100) && (ped10_hp < 100))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "HAM3_2", 5000, 1);//~r~The Haitians have died!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (PlayZ < 8.5)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "HAM3_4", 5000, 1);//~r~You have been spotted! The mission is a failure!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((ped11_hp < 100) && (ped12_hp < 100) && (ped13_hp < 100) && (ped14_hp < 100) && (ped15_hp < 100) && (ped16_hp < 100) && (ped17_hp < 100) && (ped18_hp < 100) && (ped19_hp < 100) && (ped20_hp < 100))
						{
							skip = 2;// переменная пропуска
							break;
						}
					}
				}

				// чистим скрипт тут
				REMOVE_BLIP(ped1_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped2_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped3_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped4_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped5_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped6_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped7_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped8_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped9_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped10_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре

				SET_MAX_WANTED_LEVEL(6);

				if (in_car == 2)
				{
					STOP_PLAYBACK_RECORDED_CAR(car1);
					REMOVE_CAR_RECORDING( 3061 ); // выгружаем пути транспорта
				}

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель

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

				// выгружвем машину
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_HAT_3" );//Dirty Lickin's
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(5000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +5000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 5000);
					G_HAITI = 4;
					autosave = 1;
				}
				G_ONMISSION = 0;
				
			}
		}
		else if ((G_ONMISSION == 0) && (G_HAITI == 4) && (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -209.925, 216.375, -35.491, -917.502, 952.896, 150.0, 0 )))
		{
			G_HAITI = 5;
		}
		else if ((G_ONMISSION == 0) && (G_HAITI == 5))
		{
			break;
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(haiti_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}
	}
}
void main(void)
{
	//THIS_SCRIPT_SHOULD_BE_SAVED();
	if (G_HAITI < 5)
	{
		voodoo();
	}
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
