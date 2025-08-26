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
float PlayX, PlayY, PlayZ, PlayR, blip_on, tovarX, tovarY, tovarZ, help_text1, all_tovar, go, sound, time_m, time_s, textur, skip, vVar4, rampaX, rampaY, rampaZ, rampaR, speed, bonus, camer;
float cameraX, cameraY, cameraZ, ricoX, ricoY, ricoZ, ricoR, start, text, get_car, explo_car, PedX, PedY, PedZ, stalking, in_car, stalkerR, trigger1, trigger2, trigger3, trigger4, trigger5, trigger6, trigger7;
float blip_off1, blip_off2, blip_off3, blip_off4, blip_off5, keys_UP1, keys_UP2, keys_UP3, tnt1, tnt2, tnt3, timer_on, in_zon, in_zavod, rrr_on, vorotaY, p_event, autosave;

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
void umberto(void)
{
	blip_on = 0;
	autosave = 0;
	Blip cuban_ico;
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
//============================== Stunt Boat Challenge ======================================
		if ((G_ONMISSION == 0) && (G_CUBAN == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-737.043, -74.3556, 5.6213, &cuban_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cuban_ico, BLIP_COMEDY_CLUB);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(cuban_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "LG_11");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( -737.043, -74.3556, 5.6213, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -737.043, -74.3556, 5.6213, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("CUB_1", 15000, CUTSCENE_CUBAN);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-1173.5, -599.6, 10.2, 277.1);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
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
				SET_CHAR_COORDINATES(GetPlayerPed(), 360.004, 621.999, 3.87638 );// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 115.0 );

				Cam camera;
				Car car1, car2;
				Ped ped1, ped2, ped3, ped4, ped5;
				Object rampa_1, rampa_2, rampa_3;
				Texture fon, timer;
				
				all_tovar = 1;
				go = 0;
				sound = 0;
				time_m = 5;
				time_s = 0;
				skip = 0;
				bonus = 0;
				camer = 0;
				start = 0;
				rampaX = 399.407;
				rampaY = 990.629;
				rampaZ = 0.8;
				cameraX = 425.557;
				cameraY = 995.622;
				cameraZ = 7.72758;

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				timer = GET_TEXTURE( textur, "timer_hud" );

				uint CarM1 = MODEL_DINGHY;// Катер 
				uint CarM2 = MODEL_HUNTLEY;// гольфкар 
				uint PedM1 = MODEL_M_Y_GLAT_HI_01;// Рикко
				uint PedM2 = MODEL_M_O_GRUS_HI_01;// Гольфмен
				uint PedM3 = MODEL_M_M_GRU2_HI_01;// Гольфмен 2
				uint ramp = waterjumpx2;
				uint checkpoint;

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);

				REQUEST_MODEL(PedM1);// Таксист
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Таксист
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// Таксист
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(ramp);
				while (!HAS_MODEL_LOADED(ramp)) WAIT(0);

				CREATE_CAR(CarM1, 349.322, 613.089 ,0.6436, &car1, TRUE);
				SET_CAR_HEADING(car1, 10.0);

				CREATE_CAR(CarM2, 406.634, 1025.04, 2.96648, &car2, TRUE);
				SET_CAR_HEADING(car2, -170.0);

				CREATE_CHAR (26, PedM1, 355.595, 618.756, 3.88806, &ped1, TRUE);// 
				SET_CHAR_HEADING(ped1, -55.0);
				SET_CHAR_COMPONENT_VARIATION(ped1, 1, 1, 0);

				CREATE_CHAR (26, PedM2, 411.097, 1022.49, 3.42637, &ped2, TRUE);// 
				CREATE_CHAR (26, PedM3, 411.345, 1024.04, 3.42637, &ped3, TRUE);// 
				CREATE_CHAR (26, PedM3, 412.331, 1022.23, 3.42637, &ped4, TRUE);// 
				CREATE_CHAR (26, PedM2, 412.578, 1023.77, 3.42637, &ped5, TRUE);// 
				SET_CHAR_HEADING(ped2, -110.0);
				SET_CHAR_HEADING(ped3, -150.0);
				SET_CHAR_HEADING(ped4, 75.0);
				SET_CHAR_HEADING(ped5, 100.0);

				//создаём рампы
				CREATE_OBJECT_NO_OFFSET(ramp, 399.407, 990.629, 0.8, &rampa_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(ramp, 758.003, 627.127, 0.8, &rampa_2, TRUE);
				CREATE_OBJECT_NO_OFFSET(ramp, 847.501, 453.201, 0.8, &rampa_3, TRUE);

				SET_OBJECT_HEADING(rampa_1, 343.60);
				SET_OBJECT_HEADING(rampa_2, 230.88);
				SET_OBJECT_HEADING(rampa_3, 184.9);

				SET_OBJECT_DYNAMIC(rampa_1, 0);
				SET_OBJECT_DYNAMIC(rampa_2, 0);
				SET_OBJECT_DYNAMIC(rampa_3, 0);

				SET_OBJECT_INVINCIBLE(rampa_1, 1);
				SET_OBJECT_INVINCIBLE(rampa_2, 1);
				SET_OBJECT_INVINCIBLE(rampa_3, 1);

				FREEZE_OBJECT_POSITION(rampa_1, 1);
				FREEZE_OBJECT_POSITION(rampa_2, 1);
				FREEZE_OBJECT_POSITION(rampa_3, 1);

				// грузим анимации
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				RELEASE_WEATHER();

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "CUB_1", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("cub_1");
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


				//камера
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, 357.058, 620.139, 4.45775 ); // куда смотрит камера
				SET_CAM_POS			( camera, 364.422, 616.007, 7.23219);//расположение камеры
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_CAM_FOV( camera, 45.0 );
				SET_WIDESCREEN_BORDERS( 1 );

				TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 356.581, 619.293, 3.62588, 2, -2);// идёт в двери
				SetTime(2000);

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R11_MB", "CUB1_01", 0, 0);//Hey, I'm Rico. You the man with the big cojones?
				START_SCRIPT_CONVERSATION(1, 1);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R4_GA", "GEN3_4", 0, 0);//Tommy Vercetti. Let's go...
				START_SCRIPT_CONVERSATION(1, 1);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R11_MC", "CUB1_02", 0, 0);//Ok man, treat her like a woman.
				START_SCRIPT_CONVERSATION(1, 1);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
				SetSpeech();

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

				WARP_CHAR_INTO_CAR(GetPlayerPed(), car1);
				WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car1, 2);
				DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

				checkpoint = CREATE_CHECKPOINT( 4, 330.0625, 704.7835, 0.6726999, 368.2528, 901.7051, 0.5050001, 1.20000000 );
				tovarX = 330.0625;
				tovarY = 704.7835;
				tovarZ = 0.6726999;

				ADD_BLIP_FOR_COORD(tovarX, tovarY, tovarZ, &cuban_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(cuban_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "CUB1_13", 5000, 1);//~COL_NET_12~You have five minutes to get round the course.

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
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				SETTIMERA(0);
				SETTIMERB(0);

				while (TRUE)
				{
					WAIT(0);
					if ((go == 0) || (go == 1))
					{
						if (go == 0)
						{
							PLAY_AUDIO_EVENT( "FRONTEND_GAME_PICKUP_CHECKPOINT" );
							go = 1;
						}

						SET_TEXT_FONT(4);
						SET_TEXT_COLOUR(235, 115, 18, 255);
						SET_TEXT_SCALE(0.5, 0.7);
						SET_TEXT_EDGE(2, 0, 0, 0, 255);
						SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
						SET_TEXT_CENTRE(1);
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "GO", 1);// 1
						if (TIMERB() > 900)
						{
							go = 2;
						}
					}
					//============================ HUD ============================
					// счётчик бомб 
					DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );
					//DRAW_SPRITE( tar, 0.8765625, 0.74213, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.
					SET_TEXT_COLOUR(95, 195, 247, 255);
					SET_TEXT_SCALE(0.156, 0.267);
					SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
					DISPLAY_TEXT(0.78815097, 0.73564852, "KICK1_9"); //CHECKPOINTS:

					SET_TEXT_COLOUR(95, 195, 247, 255);
					SET_TEXT_SCALE(0.26, 0.445);
					SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
					SET_TEXT_CENTRE(1);

					if ( all_tovar > 10 )
					{
						DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.72787074, "CP_TIME_NOZERO", all_tovar-1);// 
					}
					else
					{
						DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.72787074, "CP_TIME_ZERO", all_tovar-1);// 
					}
					SET_TEXT_COLOUR(95, 195, 247, 255);
					SET_TEXT_SCALE(0.26, 0.445);
					SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
					DISPLAY_TEXT_WITH_NUMBER(0.9203125, 0.72787074, "OUTOF_NUM", 27);// 

					// таймер тут
					if (TIMERA() > 1050)
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
						DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); // Время:

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
						DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); // Время:

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

					//турбобуст
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_CHAR_SPEED(GetPlayerPed(), &speed);

					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, rampaX, rampaY, rampaZ, &rampaR);//проверка "игрок на координатах"
					if ((IS_CHAR_IN_ANY_BOAT(GetPlayerPed())) && ( rampaR < 6.5 ) && (speed > 10) && (speed < 40))
					{
						vVar4 = GET_VEHICLE_ENGINE_REVS( car1 );
						vVar4 -= 0.6;
						vVar4 *= 0.25;
						APPLY_FORCE_TO_CAR( car1, 1, 0, vVar4, 0, 0, 0, 0, 1, 1, 1, 1 );

						if ((IS_CAR_IN_AIR_PROPER(car1)) && (camer == 0))
						{
							TASK_GO_STRAIGHT_TO_COORD(ped2, 16.757, 1013.62, 2.97067, 3, -2);
							TASK_GO_STRAIGHT_TO_COORD(ped3, 16.757, 1013.62, 2.97067, 3, -2);
							TASK_GO_STRAIGHT_TO_COORD(ped4, 16.757, 1013.62, 2.97067, 3, -2);
							TASK_GO_STRAIGHT_TO_COORD(ped5, 16.757, 1013.62, 2.97067, 3, -2);

							//камера
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, PlayX, PlayY, PlayZ ); // куда смотрит камера
							SET_CAM_POS			( camera, cameraX, cameraY, cameraZ);//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							SET_TIME_SCALE( 0.35 );
							SETTIMERC(0); //сбрасываем таймер 
							camer = 1;
						}
					}

					if (IS_CHAR_IN_CAR(GetPlayerPed(), car1))
					{
						if (start == 1)
						{
							REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_COORD(tovarX, tovarY, tovarZ, &cuban_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(cuban_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"
							CLEAR_PRINTS();
							start = 0;
						}
					}
					else
					{
						if (start == 0)
						{
							REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_CAR(car1, &cuban_ico);
							CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(cuban_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECOK3_R", 5000, 1);//~COL_NET_12~Return to the boat.
							start = 1;
						}
					}

					if (bonus == 0)
					{
						if (IS_CHAR_TOUCHING_CHAR(GetPlayerPed(), ped2))
						{
							EXPLODE_CHAR_HEAD(ped2);
							SETTIMERB( 0 );
							bonus = 1;
						}
						else if (IS_CHAR_TOUCHING_CHAR(GetPlayerPed(), ped3))
						{
							EXPLODE_CHAR_HEAD(ped3);
							SETTIMERB( 0 );
							bonus = 1;
						}
						else if (IS_CHAR_TOUCHING_CHAR(GetPlayerPed(), ped4))
						{
							EXPLODE_CHAR_HEAD(ped4);
							SETTIMERB( 0 );
							bonus = 1;
						}
						else if (IS_CHAR_TOUCHING_CHAR(GetPlayerPed(), ped5))
						{
							EXPLODE_CHAR_HEAD(ped5);
							SETTIMERB( 0 );
							bonus = 1;
						}
					}
					else if (bonus == 1)
					{
						if (TIMERB() < 3000)
						{
							SET_TEXT_COLOUR(255, 159, 255, 255); // задаём цвет текста
							SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
							SET_TEXT_EDGE(1, 0, 0, 0, 255); //
							SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
							SET_TEXT_CENTRE(1); // задаём центр текста
							DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "BONUS", 100);//BONUS $~1~
						}
						else
						{
							ADD_SCORE( GetPlayerIndex(), +100 );//даём игроку денег
							bonus = 2;
						}
					}

					if (camer == 1)
					{
						if ((!IS_CAR_IN_AIR_PROPER(car1)) || (TIMERC() > 2000))
						{
							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_TIME_SCALE( 1.0 );
							camer = 0;

							cameraX = 835.27;
							cameraY = 441.821;
							cameraZ = 8.93723;
						}
						else
						{
							SETTIMERA( TIMERA() );
							POINT_CAM_AT_COORD	( camera, PlayX, PlayY, PlayZ ); // куда смотрит камера
							SET_CAM_POS			( camera, cameraX, cameraY, cameraZ);//расположение камеры
						}
					}


					
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, tovarX, tovarY, tovarZ, &PlayR);//проверка "игрок на координатах"
					if ((IS_CHAR_IN_ANY_BOAT(GetPlayerPed())) && ( PlayR < 6.5 ))
					{
						all_tovar += 1;
						PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
						if (all_tovar == 2)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 368.2528, 901.7051, 0.5050001, 405.084, 1006.13, 11.0159, 1.20000000 );
							tovarX = 368.2528;
							tovarY = 901.7051;
							tovarZ = 0.5050001;
						}
						else if (all_tovar == 3)
						{
							//аудио тут
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_MD", "CUB1_05", 0, 0);//Amigo, you a man, man.
							START_SCRIPT_CONVERSATION(1, 1);

							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 405.084, 1006.13, 11.0159, 616.4692, 1147.984, 0.7676001, 1.20000000 );
							tovarX = 405.084;
							tovarY = 1006.13;
							tovarZ = 11.0159;
						}
						else if (all_tovar == 4)
						{
							rampaX = 758.003;
							rampaY = 627.127;
							rampaZ = 0.8;

							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 616.4692, 1147.984, 0.7676001, 672.9839, 955.9632, 0.9436998, 1.20000000 );
							tovarX = 616.4692;
							tovarY = 1147.984;
							tovarZ = 0.7676001;
						}
						else if (all_tovar == 5)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 672.9839, 955.9632, 0.9436998, 629.5818, 760.5221, 0.9738002, 1.20000000 );
							tovarX = 672.9839;
							tovarY = 955.9632;
							tovarZ = 0.9436998;
						}
						else if (all_tovar == 6)
						{
							//аудио тут
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_ME", "CUB1_06", 0, 0);//Call yourself a man, man?
							START_SCRIPT_CONVERSATION(1, 1);

							cameraX = 801.775;
							cameraY = 609.955;
							cameraZ = 3.14802;

							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 629.5818, 760.5221, 0.9738002, 769.4845, 616.632, 11.0888, 1.20000000 );
							tovarX = 629.5818;
							tovarY = 760.5221;
							tovarZ = 0.9738002;
						}
						else if (all_tovar == 7)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 769.4845, 616.632, 11.0888, 850.2411, 432.4598, 10.9255, 1.20000000 );
							tovarX = 769.4845;
							tovarY = 616.632;
							tovarZ = 11.0888;
						}
						else if (all_tovar == 8)
						{
							rampaX = 847.501;
							rampaY = 453.201;
							rampaZ = 0.8;

							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 850.2411, 432.4598, 10.9255, 835.8727, 232.3347, 0.7618999, 1.20000000 );
							tovarX = 850.2411;
							tovarY = 432.4598;
							tovarZ = 10.9255;
						}
						else if (all_tovar == 9)
						{
							

							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 835.8727, 232.3347, 0.7618999, 723.0335, 72.68039, 0.9769001, 1.20000000 );
							tovarX = 835.8727;
							tovarY = 232.3347;
							tovarZ = 0.7618999;
						}
						else if (all_tovar == 10)
						{
							//аудио тут
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_MF", "CUB1_07", 0, 0);//You a little scaredy kitten, baby boy, go cry to your mommy!
							START_SCRIPT_CONVERSATION(1, 1);

							camer = 99;

							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 723.0335, 72.68039, 0.9769001, 614.6709, -84.74768, 0.9920998, 1.20000000 );
							tovarX = 723.0335;
							tovarY = 72.68039;
							tovarZ = 0.9769001;
						}
						else if (all_tovar == 11)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 614.6709, -84.74768, 0.9920998, 428.3533, -161.4938, 0.8744002, 1.20000000 );
							tovarX = 614.6709;
							tovarY = -84.74768;
							tovarZ = 0.9920998;
						}
						else if (all_tovar == 12)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 428.3533, -161.4938, 0.8744002, 241.0374, -239.1127, 0.8744002, 1.20000000 );
							tovarX = 428.3533;
							tovarY = -161.4938;
							tovarZ = 0.8744002;
						}
						else if (all_tovar == 13)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 241.0374, -239.1127, 0.8744002, 97.53601, -377.51, 0.4899001, 1.20000000 );
							tovarX = 241.0374;
							tovarY = -239.1127;
							tovarZ = 0.8744002;
						}
						else if (all_tovar == 14)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 97.53601, -377.51, 0.4899001, 128.536, -455.51, 0.4899001, 1.20000000 );
							tovarX = 97.53601;
							tovarY = -377.51;
							tovarZ = 0.4899001;
						}
						else if (all_tovar == 15)
						{
							SET_OBJECT_COORDINATES(rampa_1, 728.2, 86.801, 0.7);
							SET_OBJECT_COORDINATES(rampa_2, 854.2, 420.33, 0.7);
							SET_OBJECT_COORDINATES(rampa_3, 8.2, 2.3, -15.7);
							SET_OBJECT_HEADING(rampa_1, 326.50);
							SET_OBJECT_HEADING(rampa_2, 356.88);

							rampaX = 728.2;
							rampaY = 86.801;
							rampaZ = 0.8;

							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 128.536, -455.51, 0.4899001, 188.536, -389.51, 0.4899001, 1.20000000 );
							tovarX = 128.536;
							tovarY = -455.51;
							tovarZ = 0.4899001;
						}
						else if (all_tovar == 16)
						{
							//аудио тут
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_MG", "CUB1_03", 0, 0);//Not bad, you're a real man.
							START_SCRIPT_CONVERSATION(1, 1);

							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 188.536, -389.51, 0.4899001, 288.221, -312.288, 1.0213, 1.20000000 );
							tovarX = 188.536;
							tovarY = -389.51;
							tovarZ = 0.4899001;
						}
						else if (all_tovar == 17)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 288.221, -312.288, 1.0213, 459.0794, -206.893, 1.0163, 1.20000000 );
							tovarX = 288.221;
							tovarY = -312.288;
							tovarZ = 1.0213;
						}
						else if (all_tovar == 18)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 459.0794, -206.893, 1.0163, 587.4145, -107.624, 0.3606, 1.20000000 );
							tovarX = 459.0794;
							tovarY = -206.893;
							tovarZ = 1.0163;
						}
						else if (all_tovar == 19)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 587.4145, -107.624, 0.3606, 737.531, 101.409, 11.0599, 1.20000000 );
							tovarX = 587.4145;
							tovarY = -107.624;
							tovarZ = 0.3606;
						}
						else if (all_tovar == 20)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 737.531, 101.409, 11.0599, 846.1745, 252.493, 0.9702001, 1.20000000 );
							tovarX = 737.531;
							tovarY = 101.409;
							tovarZ = 11.0599;
						}
						else if (all_tovar == 21)
						{
							rampaX =  854.2;
							rampaY = 420.33;
							rampaZ = 0.8;

							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 846.1745, 252.493, 0.9702001, 856.1779, 443.3159, 10.8592, 1.20000000 );
							tovarX = 846.1745;
							tovarY = 252.493;
							tovarZ = 0.9702001;
						}
						else if (all_tovar == 22)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 856.1779, 443.3159, 10.8592, 772.5622, 606.0977, 1.0374, 1.20000000 );
							tovarX = 856.1779;
							tovarY = 443.3159;
							tovarZ = 10.8592;
						}
						else if (all_tovar == 23)
						{
							//аудио тут
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_MG_QQQ1", "CUB1_09", 0, 0);//Man, you the man, man. I like you, man. I like you a lot.
							START_SCRIPT_CONVERSATION(1, 1);

							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 772.5622, 606.0977, 1.0374, 631.6795, 776.2925, 0.5461001, 1.20000000 );
							tovarX = 772.5622;
							tovarY = 606.0977;
							tovarZ = 1.0374;
						}
						else if (all_tovar == 24)
						{
							//аудио тут
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_MH", "CUB1_10", 0, 0);//Any time, man. 'cause you got cojones. And all my friends have big cojones.
							START_SCRIPT_CONVERSATION(1, 1);

							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 631.6795, 776.2925, 0.5461001, 508.6552, 934.3978, 0.6627998, 1.20000000 );
							tovarX = 631.6795;
							tovarY = 776.2925;
							tovarZ = 0.5461001;
						}
						else if (all_tovar == 25)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 508.6552, 934.3978, 0.6627998, 337.8989, 828.7862, 0.8772001, 1.20000000 );
							tovarX = 508.6552;
							tovarY = 934.3978;
							tovarZ = 0.6627998;
						}
						else if (all_tovar == 26)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 337.8989, 828.7862, 0.8772001, 346.6888, 628.7909, 0.6436, 1.20000000 );
							tovarX = 337.8989;
							tovarY = 828.7862;
							tovarZ = 0.8772001;
						}
						else if (all_tovar == 27)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 5, 346.6888, 628.7909, 0.6436, 346.6888, 628.7909, 0.6436, 1.20000000 );
							tovarX = 346.6888;
							tovarY = 628.7909;
							tovarZ = 0.6436;
						}
						else if (all_tovar == 28)
						{
							DELETE_CHECKPOINT(checkpoint);
							checkpoint = CREATE_CHECKPOINT( 4, 6.6888, 8.7909, 0.6, 6.6, 8.7, 0.6, 1.20000000 );
						}
						REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
						ADD_BLIP_FOR_COORD(tovarX, tovarY, tovarZ, &cuban_ico);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(cuban_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"
					}

					GET_CHAR_COORDINATES(ped1,  &ricoX, &ricoY, &ricoZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, ricoX, ricoY, ricoZ, &ricoR);//проверка "игрок на координатах"
					if (all_tovar > 27)
					{
						REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре

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
						SET_CAR_COORDINATES(car1, 349.322, 613.089, 0.6436);// телепортируем катер
						SET_CAR_HEADING(car1, -170.0);

						WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 353.904, 614.652, 3.88022);//телепартируем из катера
						SET_CHAR_HEADING(GetPlayerPed(), 100.0);
						WARP_CHAR_INTO_CAR(ped1, car1);// садим Рикко за руль

						DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

						//камера
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 348.052, 612.513, 0.6436 ); // куда смотрит камера
						SET_CAM_POS			( camera, 355.866, 617.851, 8.51077);//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );
						SetTime(600);

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_MI", "CUB1_04", 0, 0);//You got real big cojones, amigo.
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -11.77, -190.93, 1.5, 4, 90.0, 2, 5, 10);// пед едит на нужные координаты
						SetTime(2000);

						//убираем камеру
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// разморозить игрока

						skip = 2;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if (IS_CHAR_DEAD(ped1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "CUB1_11", 5000, 1);//~r~You Killed Rico!
						skip = 1;// переменная пропуска
						break;
					}
					else if (IS_CAR_DEAD(car1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COK3_7", 5000, 1);//~r~You destroyed the boat!
						skip = 1;// переменная пропуска
						break;
					}
					else if (ricoR > 50)
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "T4X4_F", 5000, 1);//~r~You bailed! Too tough for you?!
						skip = 1;// переменная пропуска
						break;
					}
					else if ((time_m == 0) && (time_s == 0))
					{
						REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре

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
						SET_CAR_COORDINATES(car1, 349.322, 613.089, 0.6436);// телепортируем катер
						SET_CAR_HEADING(car1, -170.0);

						WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), 353.904, 614.652, 3.88022);//телепартируем из катера
						SET_CHAR_HEADING(GetPlayerPed(), 100.0);
						WARP_CHAR_INTO_CAR(ped1, car1);// садим Рикко за руль

						DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

						//камера
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 348.052, 612.513, 0.6436 ); // куда смотрит камера
						SET_CAM_POS			( camera, 355.866, 617.851, 8.51077);//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );
						SetTime(600);

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R11_MJ", "CUB1_08", 0, 0);//You a big waste of space. Walk like a man, talk like a man, but you drive like an idiot.
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -11.77, -190.93, 1.5, 4, 90.0, 2, 5, 10);// пед едит на нужные координаты
						SetTime(2000);

						//убираем камеру
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// разморозить игрока

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "CUB1_15", 5000, 1);//~r~You are too slow, man.
						skip = 1;// переменная пропуска
						break;
					}
				}

				// чистим скрипт тут
				if (sound == 1)
				{
					STOP_STREAM();
					ENABLE_FRONTEND_RADIO();
				}

				REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
				DELETE_CHECKPOINT(checkpoint);

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( timer );
				REMOVE_TXD( textur );

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(ramp);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины

				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)

				DELETE_OBJECT(&rampa_1);
				DELETE_OBJECT(&rampa_2);
				DELETE_OBJECT(&rampa_3);

				MARK_OBJECT_AS_NO_LONGER_NEEDED(&rampa_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&rampa_2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&rampa_3);

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_CUB_1" );//Stunt Boat Challenge
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(1000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +1000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 1000);
					G_CUBAN = 2;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}

//============================== Cannon Fodder ======================================
		else if ((G_ONMISSION == 0) && (G_CUBAN == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-737.043, -74.3556, 5.6213, &cuban_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cuban_ico, BLIP_COMEDY_CLUB);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(cuban_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "LG_11");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( -737.043, -74.3556, 5.6213, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -737.043, -74.3556, 5.6213, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("CUB_2", 15000, CUTSCENE_CUBAN);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-1173.5, -599.6, 10.2, 277.1);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
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
				SET_CHAR_COORDINATES(GetPlayerPed(), -737.142, -73.7556, 5.9432 );// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 5.0 );

				Cam camera;
				Car car1, car2, car3, car4;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16;
				Blip ped1_ico, ped2_ico, ped3_ico, ped4_ico, ped5_ico;
				Pickup sweap_1;
				Object gunbox1, trubka_1;

				skip = 0;
				text = 1;
				get_car = 0;
				explo_car = 0;
				blip_off1 = 1;
				blip_off2 = 1;
				blip_off3 = 1;
				blip_off4 = 1;
				blip_off5 = 1;

				uint CarM1 = MODEL_TAXI;// Такси 
				uint CarM2 = MODEL_COQUETTE;// Стингер
				uint CarM3 = MODEL_PONY;// Пони
				uint PedM1 = MODEL_M_Y_GLAT_HI_01;// Кубинкц
				uint PedM2 = MODEL_M_M_GJAM_HI_01;// Гаитянин
				uint PedM3 = MODEL_M_M_TAXIDRIVER;// Таксист
				uint trubka = vc_mob_phone;
				uint gunboxM = ne_wood_gunbox;// GunBox
				uint pMax, car_HP, snuper_hp, ped1_hp, ped2_hp, ped3_hp, ped4_hp, ped5_hp, rico_hp;

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);
				REQUEST_MODEL(CarM3);
				while (!HAS_MODEL_LOADED(CarM3)) WAIT(100);

				REQUEST_MODEL(PedM1);// Таксист
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Таксист
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// Таксист
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(trubka);
				while (!HAS_MODEL_LOADED(trubka)) WAIT(0);
				REQUEST_MODEL(gunboxM);//
				while (!HAS_MODEL_LOADED(gunboxM)) WAIT(0);

				CREATE_CAR(CarM3, -727.783, 611.412, 5.70926, &car1, TRUE);// Пони
				SET_CAR_HEADING(car1, 90.0);
				CREATE_CAR(CarM2, -679.63 ,603.093, 5.84792, &car2, TRUE);// Стингер
				SET_CAR_HEADING(car2, -180.0);
				CREATE_CAR(CarM1, 299.551, -787.416, 5.44546, &car3, TRUE);// Такси 
				SET_CAR_HEADING(car3, 0.0);

				// кубинцы
				CREATE_CHAR (26, PedM1, -646.344, 607.2431, 5.6011, &ped1, TRUE);// Рико
				CREATE_CHAR (26, PedM1, -736.166, -77.1128, 5.9432, &ped2, TRUE);// Кубинкц
				CREATE_CHAR (26, PedM1, -736.931, -76.6788, 5.9432, &ped3, TRUE);// Кубинкц
				CREATE_CHAR (26, PedM1, -736.642, -77.7573, 5.9432, &ped4, TRUE);// Кубинкц
				CREATE_CHAR (26, PedM1, -646.531, 600.621, 5.60114, &ped5, TRUE);// Кубинкц
				CREATE_CHAR (26, PedM1, -646.152, 605.806, 5.60114, &ped6, TRUE);// Кубинкц
				SET_CHAR_COMPONENT_VARIATION(ped1, 1, 1, 0);
				SET_CHAR_COMPONENT_VARIATION(ped2, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped3, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped4, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped5, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped6, 1, 0, 0);
				SET_CHAR_HEADING(ped1, -80.0);
				SET_CHAR_HEADING(ped2, 100.0);
				SET_CHAR_HEADING(ped3, -125.0);
				SET_CHAR_HEADING(ped4, 0.0);
				SET_CHAR_HEADING(ped5, 75.0);
				SET_CHAR_HEADING(ped6, 115.0);
				SET_CHAR_HEALTH(ped1, 2000);

				// кубинцы в такси
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM1, 0, &ped7);// Кубинкц
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM1, 1, &ped8);// Кубинкц
				CREATE_CHAR_AS_PASSENGER(car3, 1, PedM1, 2, &ped9);// Кубинкц
				CREATE_CHAR_INSIDE_CAR(car3, 1, PedM3, &ped10);// Таксист
				SET_CHAR_COMPONENT_VARIATION(ped7, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped8, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped9, 1, 0, 0);

				// Гаитяни
				CREATE_CHAR (26, PedM2, -681.713, 603.338, 5.60114, &ped11, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -681.861, 600.719, 5.60114, &ped12, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -682.079, 605.765, 5.60114, &ped13, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -697.868, 600.982, 5.60114, &ped14, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -697.884, 608.741, 5.60114, &ped15, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, 302.672, -785.035, 5.05974, &ped16, TRUE);// Снайпер
				SET_CHAR_HEADING(ped11, -85.0);
				SET_CHAR_HEADING(ped12, -85.0);
				SET_CHAR_HEADING(ped13, -95.0);
				SET_CHAR_HEADING(ped14, -85.0);
				SET_CHAR_HEADING(ped15, -95.0);

				// грузим анимации
				REQUEST_ANIMS( "amb@taxi_hail_m" );
				while (!HAVE_ANIMS_LOADED( "amb@taxi_hail_m" )) WAIT(0);

				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				CREATE_OBJECT_NO_OFFSET(trubka, 1.1, 1.1, 1.1, &trubka_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(gunboxM, -659.77, 868.278, 5.71862, &gunbox1, TRUE);
				ATTACH_OBJECT_TO_CAR(gunbox1, car1, 0, 0.0, -0.05, 0.5, 11, 0.0, 22);

				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				RELEASE_WEATHER();

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "CUB_2", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("cub_2");
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

				ADD_BLIP_FOR_COORD(-734.82, -69.1976, 5.6909, &cuban_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(cuban_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"
				PRINT_STRING_IN_STRING("string", "CUB2_03", 5000, 1);//~g~Get a car and pick up the Cubans from outside Robina's Cafe.

				// вооружаем
				UpdateWeaponOfPed(ped1, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped15, WEAPON_EPISODIC_12);

				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_EPISODIC_12, TRUE);

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
				SET_CHAR_RELATIONSHIP_GROUP(ped7, 0);
				SET_CHAR_RELATIONSHIP(ped7, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped8, 0);
				SET_CHAR_RELATIONSHIP(ped8, 5, 24);
				SET_CHAR_RELATIONSHIP_GROUP(ped9, 0);
				SET_CHAR_RELATIONSHIP(ped9, 5, 24);

				CREATE_PICKUP_ROTATE(w_ak47, 3, 60, -646.834,606.579,5.61127, -87.532, -108.556, -1.476, &sweap_1);// даём винтовку

				// пригнать машину
				while (TRUE)
				{
					WAIT(0);
					DRAW_CHECKPOINT( -734.82, -69.1976, 5.6909, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -734.82, -69.1976, 5.6909, &PlayR);//проверка "игрок на координатах"
					if ( PlayR < 2.5 )
					{
						if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
						{
							if (get_car == 0)
							{
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car4);
								GET_MAXIMUM_NUMBER_OF_PASSENGERS(car4, &pMax);
								get_car = 1;
								if (pMax < 3)
								{
									if (text == 1)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R11_MK", "CUB2_01", 0, 0);//Not enough room, man, you need a bigger car.
										START_SCRIPT_CONVERSATION(1, 1);
										text = 0;
									}
								}
								else
								{
									SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
									SET_CAMERA_CONTROLS_DISABLED_WITH_PLAYER_CONTROLS( 0 );

									TASK_ENTER_CAR_AS_PASSENGER(ped2, car4, 10000, 0);
									TASK_ENTER_CAR_AS_PASSENGER(ped3, car4, 10000, 1);
									TASK_ENTER_CAR_AS_PASSENGER(ped4, car4, 10000, 2);
									SetTime(1000);

									SETTIMERA( 0 );
									while (TRUE)
									{
										WAIT(0);
										if ((IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (IS_CHAR_SITTING_IN_ANY_CAR(ped3)) && (IS_CHAR_SITTING_IN_ANY_CAR(ped4)))
										{
											break;
										}
										else if (TIMERA() > 9000)
										{
											WARP_CHAR_INTO_CAR_AS_PASSENGER(ped2, car4, 0);
											WARP_CHAR_INTO_CAR_AS_PASSENGER(ped3, car4, 1);
											WARP_CHAR_INTO_CAR_AS_PASSENGER(ped4, car4, 2);
											SHUT_CAR_DOOR(car4, 1);
											break;
										}
									}

									SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
									SET_CAMERA_CONTROLS_DISABLED_WITH_PLAYER_CONTROLS( 1 );

									REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
									ADD_BLIP_FOR_COORD(-641.682, 607.685, 5.0648, &cuban_ico);//создаем иконку на радаре
									CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cuban_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
									CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R11_ML", "CUB2_19", 0, 0);//We gonna fight like men!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();

									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "CUB2_04", 5000, 1);//~g~Go and drop the Cubans off at the fight.
									PRINT_STRING_IN_STRING("string", "CUB2_23", 5000, 1);//~g~ Little Haiti will be swarming with Haitians trying to even the score with the Cubans. Watch your back.
									text = 0;
									break;
								}
							}
						}
						else
						{
							if (text == 1)
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "CUB2_18", 5000, 1);// = ~g~Get a car and pick up the Cubans
								text = 0;
							}
						}
					}
					else
					{
						if (text == 0)
						{
							text = 1;
						}
						if (get_car == 1)
						{
							MARK_CAR_AS_NO_LONGER_NEEDED(&car4);
							get_car = 0;
						}
					}
					// провалы тут
					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)) || (IS_CHAR_FATALLY_INJURED(ped2)) || (IS_CHAR_FATALLY_INJURED(ped3)) || (IS_CHAR_FATALLY_INJURED(ped4)))//если пед мёртв или фатально ранен. 
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "CUB2_10", 5000, 1);//~r~You are supposed to be killing Haitians, not Cubans.
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_DEAD(ped5)) || (IS_CHAR_DEAD(ped6)) || (IS_CHAR_FATALLY_INJURED(ped1)) || (IS_CHAR_FATALLY_INJURED(ped5)) || (IS_CHAR_FATALLY_INJURED(ped6)))//если пед мёртв или фатально ранен. 
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "CUB2_10", 5000, 1);//~r~You are supposed to be killing Haitians, not Cubans.
						skip = 1;// переменная пропуска
						break;
					}
				}

				// привести на точку
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						DRAW_CHECKPOINT( -641.682, 607.685, 5.0648, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -641.682, 607.685, 5.0648, &PlayR);//проверка "игрок на координатах"
						if (IS_CHAR_IN_CAR(GetPlayerPed(), car4))
						{
							if ( PlayR < 2.0 )
							{
								// сценка тут
								REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
								CLEAR_AREA(-641.682, 607.685, 5.0648, 55.0, 1);//очещаем зону загрузки
								SET_MAX_WANTED_LEVEL(0);

								//ставим камеру
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, -641.682, 607.685, 6.50455 ); // куда смотрит камера
								SET_CAM_POS			( camera, -636.011, 617.043, 10.2113 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );

								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "hail_left", "amb@taxi_hail_m", 1.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе

								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(GetPlayerPed(), -645.18, 607.195, 5.3873, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, -644.576, 605.017, 5.3873, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped3, -644.609, 602.851, 5.3873, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped4, -645.054, 601.016, 5.3873, 3, -2, 1.5);// пед убегает
								SetTime(2000);

								// меняем ракурс
								POINT_CAM_AT_COORD	( camera, -646.671, 606.254, 5.85833 ); // куда смотрит камера
								SET_CAM_POS			( camera, -642.401, 611.122, 7.7852 );//расположение камеры
								CLEAR_AREA(-641.682, 607.685, 5.0648, 55.0, 1);//очещаем зону загрузки
								SetTime(3000);

								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 5500 );//Воиспроизвидение анимации на педе

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_MM", "CUB2_12", 0, 0);//Hey amigo! Good to see you could make it!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_MN", "CUB2_13", 0, 0);//Stinking nest of Haitians, we gonna kill 'em all!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								//убираем камеру
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								END_CAM_COMMANDS( &camera );
								SET_WIDESCREEN_BORDERS( 0 );
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R11_MO", "CUB2_14", 0, 0);//CHAAAAAARGE!
								START_SCRIPT_CONVERSATION(1, 1);

								//свой-чужой
								SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
								SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
								SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
								SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
								SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);

								SET_CHAR_RELATIONSHIP(ped11, 5, 0);
								SET_CHAR_RELATIONSHIP(ped12, 5, 0);
								SET_CHAR_RELATIONSHIP(ped13, 5, 0);
								SET_CHAR_RELATIONSHIP(ped14, 5, 0);
								SET_CHAR_RELATIONSHIP(ped15, 5, 0);

								SET_SENSE_RANGE(ped11, 45.0);
								SET_SENSE_RANGE(ped12, 45.0);
								SET_SENSE_RANGE(ped13, 45.0);
								SET_SENSE_RANGE(ped14, 45.0);
								SET_SENSE_RANGE(ped15, 45.0);

								SET_CHAR_WILL_USE_COVER(ped11, 1);
								SET_CHAR_WILL_USE_COVER(ped12, 1);
								SET_CHAR_WILL_USE_COVER(ped13, 1);
								SET_CHAR_WILL_USE_COVER(ped14, 1);
								SET_CHAR_WILL_USE_COVER(ped15, 1);

								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, FALSE);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, FALSE);
								
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
								SetSpeech();

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "CUB2_25", 5000, 1);//~COL_NET_12~KILL ALL THE HAITIANS!!
								break;
							}
							if (text == 1)
							{
								REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_COORD(-641.682, 607.685, 5.0648, &cuban_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(cuban_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "CUB2_04", 5000, 1);//~g~Go and drop the Cubans off at the fight.
								text = 0;
							}
						}
						else
						{
							if (text == 0)
							{
								REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CAR(car4, &cuban_ico);
								CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(cuban_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_CAR");//иконка на радаре называние в истории карты ""
								
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "IN_VEH", 5000, 1);//~g~Hey! Get back in the vehicle!
								text = 1;
							}
						}
						// провалы тут
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)) || (IS_CHAR_FATALLY_INJURED(ped2)) || (IS_CHAR_FATALLY_INJURED(ped3)) || (IS_CHAR_FATALLY_INJURED(ped4)))//если пед мёртв или фатально ранен. 
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB2_10", 5000, 1);//~r~You are supposed to be killing Haitians, not Cubans.
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_DEAD(ped5)) || (IS_CHAR_DEAD(ped6)) || (IS_CHAR_FATALLY_INJURED(ped1)) || (IS_CHAR_FATALLY_INJURED(ped5)) || (IS_CHAR_FATALLY_INJURED(ped6)))//если пед мёртв или фатально ранен. 
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB2_10", 5000, 1);//~r~You are supposed to be killing Haitians, not Cubans.
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// взорвать баррикаду
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						GET_CHAR_HEALTH(ped1, &rico_hp);
						GET_CHAR_HEALTH(ped11, &ped1_hp);
						GET_CHAR_HEALTH(ped12, &ped2_hp);
						GET_CHAR_HEALTH(ped13, &ped3_hp);
						GET_CHAR_HEALTH(ped14, &ped4_hp);
						GET_CHAR_HEALTH(ped15, &ped5_hp);

						// респавн педов тут
						if (!IS_CAR_DEAD(car2))
						{
							if (ped1_hp < 200)
							{
								DELETE_CHAR(&ped11);//выгружаем модель педа(в последствии пед изчезнет
								WAIT(10);
								CREATE_CHAR (26, PedM2, -681.772, 597.074, 5.60114, &ped11, TRUE);//
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped11, -681.713, 603.338, 5.60114, 3, -2, 1.5);// пед убегает

								REMOVE_BLIP(ped1_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CHAR(ped11, &ped1_ico);
								CHANGE_BLIP_SPRITE(ped1_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(ped1_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(ped1_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped1_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

								UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_13);
								SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_13, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
								SET_CHAR_RELATIONSHIP(ped11, 5, 0);
								SET_SENSE_RANGE(ped11, 45.0);
								SET_CHAR_WILL_USE_COVER(ped11, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
							}
							if (ped2_hp < 200)
							{
								DELETE_CHAR(&ped12);//выгружаем модель педа(в последствии пед изчезнет
								WAIT(10);
								CREATE_CHAR (26, PedM2, -681.772, 597.074, 5.60114, &ped12, TRUE);//
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped12, -681.861, 600.719, 5.60114, 3, -2, 1.5);// пед убегает

								REMOVE_BLIP(ped2_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CHAR(ped12, &ped2_ico);
								CHANGE_BLIP_SPRITE(ped2_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(ped2_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(ped2_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped2_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

								UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_13);
								SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_13, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
								SET_CHAR_RELATIONSHIP(ped12, 5, 0);
								SET_SENSE_RANGE(ped12, 45.0);
								SET_CHAR_WILL_USE_COVER(ped12, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
							}
							if (ped3_hp < 200)
							{
								DELETE_CHAR(&ped13);//выгружаем модель педа(в последствии пед изчезнет
								WAIT(10);
								CREATE_CHAR (26, PedM2, -682.067, 609.499, 5.60114, &ped13, TRUE);//
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped13, -682.079, 605.765, 5.60114, 3, -2, 1.5);// пед убегает

								REMOVE_BLIP(ped3_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CHAR(ped13, &ped3_ico);
								CHANGE_BLIP_SPRITE(ped3_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(ped3_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(ped3_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped3_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

								UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_13);
								SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_EPISODIC_13, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
								SET_CHAR_RELATIONSHIP(ped13, 5, 0);
								SET_SENSE_RANGE(ped13, 45.0);
								SET_CHAR_WILL_USE_COVER(ped13, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);
							}
							if (ped4_hp < 200)
							{
								DELETE_CHAR(&ped14);//выгружаем модель педа(в последствии пед изчезнет
								WAIT(10);
								CREATE_CHAR (26, PedM2, -705.939, 608.939, 5.60114, &ped14, TRUE);//
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped14, -697.868, 600.982, 5.60114, 3, -2, 1.5);// пед убегает

								REMOVE_BLIP(ped4_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CHAR(ped14, &ped4_ico);
								CHANGE_BLIP_SPRITE(ped4_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(ped4_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(ped4_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped4_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

								UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_13);
								SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_EPISODIC_13, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
								SET_CHAR_RELATIONSHIP(ped14, 5, 0);
								SET_SENSE_RANGE(ped14, 45.0);
								SET_CHAR_WILL_USE_COVER(ped14, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, FALSE);
							}
							if (ped5_hp < 200)
							{

								DELETE_CHAR(&ped15);//выгружаем модель педа(в последствии пед изчезнет
								WAIT(10);
								CREATE_CHAR (26, PedM2, -705.166, 599.978, 5.60114, &ped15, TRUE);//
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped15, -697.884, 608.74, 5.60114, 3, -2, 1.5);// пед убегает

								REMOVE_BLIP(ped5_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CHAR(ped15, &ped5_ico);
								CHANGE_BLIP_SPRITE(ped5_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(ped5_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(ped5_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped5_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

								UpdateWeaponOfPed(ped15, WEAPON_EPISODIC_13);
								SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_EPISODIC_13, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
								SET_CHAR_RELATIONSHIP(ped15, 5, 0);
								SET_SENSE_RANGE(ped15, 45.0);
								SET_CHAR_WILL_USE_COVER(ped15, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, FALSE);
							}
						}
						else
						{
							if ((ped1_hp < 200) && (blip_off1 == 1))
							{
								EXPLODE_CHAR_HEAD(ped11);
								REMOVE_BLIP(ped1_ico);//Удаляем иконку на радаре
								blip_off1 = 0;
							}
							if ((ped2_hp < 200) && (blip_off2 == 1))
							{
								EXPLODE_CHAR_HEAD(ped12);
								REMOVE_BLIP(ped2_ico);//Удаляем иконку на радаре
								blip_off2 = 0;
							}
							if ((ped3_hp < 200) && (blip_off3 == 1))
							{
								EXPLODE_CHAR_HEAD(ped13);
								REMOVE_BLIP(ped3_ico);//Удаляем иконку на радаре
								blip_off3 = 0;
							}
							if ((ped4_hp < 200) && (blip_off4 == 1))
							{
								EXPLODE_CHAR_HEAD(ped14);
								REMOVE_BLIP(ped4_ico);//Удаляем иконку на радаре
								blip_off4 = 0;
							}
							if ((ped5_hp < 200) && (blip_off5 == 1))
							{
								EXPLODE_CHAR_HEAD(ped15);
								REMOVE_BLIP(ped5_ico);//Удаляем иконку на радаре
								blip_off5 = 0;
							}
						}
						
						GET_CAR_HEALTH(car2, &car_HP);
						if ((car_HP < 500) && (explo_car == 0))
						{
							explo_car = 1;
							EXPLODE_CAR(car2, 1, 1);
						}

						if ((IS_CAR_DEAD(car2)) && (ped1_hp < 200) && (ped2_hp < 200) && (ped3_hp < 200) && (ped4_hp < 200) && (ped5_hp < 200))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_NAA", "CUB2_15", 0, 0);// Now, my brothers, CHAAARRRGGEE!!
							START_SCRIPT_CONVERSATION(1, 1);
							SetTime(2000);

							REMOVE_PICKUP(sweap_1);// выгружаем оружие
							CREATE_PICKUP_ROTATE(w_psg1, 3, 60, -698.246, 599.348, 5.61127, -87.532, -108.556, -1.476, &sweap_1);// даём винтовку

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							CLEAR_AREA(-681.713, 603.338, 5.60114, 55.0, 1);//очещаем зону загрузки
							SET_CAR_COORDINATES(car2, -675.496, 614.336, 5.84792);
							SET_CAR_HEADING(car2, -170.0);
							
							//ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -677.608, 603.093, 5.84792 ); // куда смотрит камера
							SET_CAM_POS			( camera, -635.969, 603.055, 7.74445 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							SET_CHAR_COORDINATES(ped1, -647.691, 603.177, 5.3873);
							SET_CHAR_COORDINATES(ped2, -661.086, 601.512, 5.3873);
							SET_CHAR_COORDINATES(ped3, -658.804, 601.542, 5.3873);
							SET_CHAR_COORDINATES(ped4, -662.328, 605.153, 5.3873);
							SET_CHAR_COORDINATES(ped5, -659.473, 605.531, 5.3873);
							SET_CHAR_COORDINATES(ped6, -662.564, 601.001, 5.3873);
							SET_CHAR_HEADING(ped1, 75.0);
							SET_CHAR_HEADING(ped2, 75.0);
							SET_CHAR_HEADING(ped3, 75.0);
							SET_CHAR_HEADING(ped4, 75.0);
							SET_CHAR_HEADING(ped5, 75.0);
							SET_CHAR_HEADING(ped6, 75.0);

							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(GetPlayerPed(), -657.274, 603.569, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped4, -718.916, 604.141, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped5, -717.438, 604.651, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped6, -715.156, 604.681, 5.3873, 3, -2, 1.5);// пед убегает
							SetTime(3000);

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, -698.407, 603.883, 4.36404 ); // куда смотрит камера
							SET_CAM_POS			( camera, -670.697, 603.593, 8.11014 );//расположение камеры

							SET_CHAR_COORDINATES(ped4, -678.069, 604.916, 5.0073);
							SET_CHAR_COORDINATES(ped5, -677.524, 603.151, 5.0073);
							SET_CHAR_COORDINATES(ped6, -678.503, 601.535, 5.0073);

							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped4, -718.916, 604.141, 5.3873, 3, -1, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped5, -717.438, 604.651, 5.3873, 3, -1, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped6, -715.156, 604.681, 5.3873, 3, -1, 1.5);// пед убегает
							SetTime(2000);

							SET_CHAR_COORDINATES(ped16, -743.086, 604.521, 18.122);
							SET_CHAR_HEADING(ped16, -85.0);
							UpdateWeaponOfPed(ped16, WEAPON_EPISODIC_15);
							SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_EPISODIC_15, TRUE);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped16, -740.548, 604.521, 18.122, 2, -2, 1.5);// пед убегает
							SetTime(2000);

							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped5, -717.438, 604.651, 5.3873, 3, -1, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped6, -715.156, 604.681, 5.3873, 3, -1, 1.5);// пед убегает
							TASK_SHOOT_AT_CHAR(ped16, ped4, 4500, 3);
							EXPLODE_CHAR_HEAD(ped4);
							SetTime(1500);

							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped6, -715.156, 604.681, 5.3873, 3, -1, 1.5);// пед убегает
							EXPLODE_CHAR_HEAD(ped5);
							SetTime(1500);

							EXPLODE_CHAR_HEAD(ped6);
							SetTime(1500);

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, -734.29, 604.285, 16.3152 ); // куда смотрит камера
							SET_CAM_POS			( camera, -743.52, 604.092, 20.9147 );//расположение камеры

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_NAB", "CUB2_09", 0, 0);//Sniper on the roof!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_NAC", "CUB2_07", 0, 0);//They fight like girls! Take cover!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							SET_CHAR_COORDINATES(GetPlayerPed(), -678.492, 599.888, 5.3873);
							SET_CHAR_COORDINATES(ped1, -679.745, 599.831, 5.3873);
							SET_CHAR_COORDINATES(ped2, -679.484, 598.718, 5.3873);
							SET_CHAR_COORDINATES(ped3, -679.792, 606.968, 5.3873);
							SET_CHAR_HEADING(GetPlayerPed(), 85.0);
							SET_CHAR_HEADING(ped1, -85.0);
							SET_CHAR_HEADING(ped2, -50.0);
							SET_CHAR_HEADING(ped3, -85.0);
							SetTime(1000);

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, -679.671, 602.763, 6.11582 ); // куда смотрит камера
							SET_CAM_POS			( camera, -677.624, 596.133, 7.30864 );//расположение камеры

							// анимация телефонного звонка
							ATTACH_OBJECT_TO_PED( trubka_1, ped1, 1232, 0.070, 0.052, 0.003, 3.30000000, 0.30000000, -0.45000000, 0 );
							REQUEST_ANIMS( "amb@payphone" );//загружаем файл с анимацией
							while (!HAVE_ANIMS_LOADED( "amb@payphone" )) WAIT(0);
							SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_UNARMED, TRUE);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "cellphone_talk", "amb@payphone", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе

							// RRR пути тут
							REQUEST_CAR_RECORDING( 3055 ); // полёт Основной
							while (!HAS_CAR_RECORDING_BEEN_LOADED( 3055 )) WAIT(0);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_NAD", "CUB2_02", 0, 0);//We need reinforcements from the cafe!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "put_down_phone", "amb@payphone", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе

							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 3055, 0.0, 0.0, 0.0);
							CLEAR_AREA(-678.535, 598.593, 5.3873, 55.0, 1);//очещаем зону загрузки
							CLEAR_AREA(-635.815, 603.068, 5.7759, 55.0, 1);//очещаем зону загрузки
							SETTIMERA( 0 );

							while(true)
							{
								WAIT(0);
								GET_CHAR_COORDINATES(ped10,  &rampaX, &rampaY, &rampaZ);//вписываем координаты игрока в переменную

								// меняем ракурс
								POINT_CAM_AT_COORD	( camera, rampaX, rampaY, rampaZ ); // куда смотрит камера
								SET_CAM_POS			( camera, -645.401, 606.3, 8.98409 );//расположение камеры
								if (TIMERA() > 4500)
								{
									break;
								}
							}
							// стоп RRR пути
							STOP_PLAYBACK_RECORDED_CAR(car3);
							REMOVE_CAR_RECORDING( 3055 ); // выгружаем пути транспорта

							DETACH_OBJECT( trubka_1, 1 );
							SET_OBJECT_COORDINATES(trubka_1, 1.0, 1.0, -1.0);

							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped7, -678.535, 598.593, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped8, -679.538, 607.747, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped9, -679.349, 608.606, 5.3873, 3, -2, 1.5);// пед убегает
							SetTime(1000);

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, -677.608, 603.093, 5.84792 ); // куда смотрит камера
							SET_CAM_POS			( camera, -635.969, 603.055, 7.74445 );//расположение камеры
							SetTime(3000);

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, -679.671, 602.763, 6.11582 ); // куда смотрит камера
							SET_CAM_POS			( camera, -677.624, 596.133, 7.30864 );//расположение камеры

							SET_CHAR_COORDINATES(ped7, -678.535, 598.593, 5.3873);
							SET_CHAR_COORDINATES(ped8, -679.538, 607.747, 5.3873);
							SET_CHAR_COORDINATES(ped9, -679.349, 608.606, 5.3873);

							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, -689.721, 609.203, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped7, -691.518, 611.267, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped9, -689.989, 612.472, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, -693.415, 599.095, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped8, -691.494, 597.932, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped3, -690.071, 599.496, 5.3873, 3, -2, 1.5);// пед убегает

							SET_CHAR_RELATIONSHIP_GROUP(ped16, 5);
							SET_CHAR_RELATIONSHIP(ped16, 5, 0);
							SET_SENSE_RANGE(ped16, 90.0);
							SET_CHAR_WILL_USE_COVER(ped16, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, FALSE);

							explo_car = 0;
							blip_off1 = 1;
							blip_off2 = 1;
							blip_off3 = 1;
							blip_off4 = 1;
							blip_off5 = 1;

							ADD_BLIP_FOR_CHAR(ped16, &cuban_ico);
							CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(cuban_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							FREEZE_CHAR_POSITION(ped16, 1);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_NAE", "CUB2_05", 0, 0);//Take out that cowardly sniper!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							break;
						}
						// провалы тут
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (rico_hp < 200)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB1_11", 5000, 1);//~r~You Killed Rico!
							skip = 1;// переменная пропуска
							break;
						}
						else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -591.529, 514.096, 2.163, -791.529, 714.096, 54.163, 0 ))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "T4X4_F", 5000, 1);//~r~You bailed! Too tough for you?!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// убить снайпера
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						GET_CHAR_HEALTH(ped1, &rico_hp);
						GET_CHAR_HEALTH(ped11, &ped1_hp);
						GET_CHAR_HEALTH(ped12, &ped2_hp);
						GET_CHAR_HEALTH(ped13, &ped3_hp);
						GET_CHAR_HEALTH(ped14, &ped4_hp);
						GET_CHAR_HEALTH(ped15, &ped5_hp);
						GET_CHAR_HEALTH(ped16, &snuper_hp);

						// респавн педов тут
						if (!IS_CHAR_DEAD(ped16))
						{
							if (ped1_hp < 200)
							{
								DELETE_CHAR(&ped11);//выгружаем модель педа(в последствии пед изчезнет
								WAIT(10);
								CREATE_CHAR (26, PedM2, -726.207, 609.126, 5.60114, &ped11, TRUE);//
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped11, -725.889, 604.384, 5.60114, 3, -2, 1.5);// пед убегает

								UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_12);
								SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_12, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
								SET_CHAR_RELATIONSHIP(ped11, 5, 0);
								SET_SENSE_RANGE(ped11, 45.0);
								SET_CHAR_WILL_USE_COVER(ped11, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
							}
							if (ped2_hp < 200)
							{
								DELETE_CHAR(&ped12);//выгружаем модель педа(в последствии пед изчезнет
								WAIT(10);
								CREATE_CHAR (26, PedM2, -725.91, 598.524, 5.60114, &ped12, TRUE);//
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped12, -725.362, 602.294, 5.60114, 3, -2, 1.5);// пед убегает

								UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_12);
								SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_12, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
								SET_CHAR_RELATIONSHIP(ped12, 5, 0);
								SET_SENSE_RANGE(ped12, 45.0);
								SET_CHAR_WILL_USE_COVER(ped12, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
							}
							if (ped3_hp < 200)
							{
								DELETE_CHAR(&ped13);//выгружаем модель педа(в последствии пед изчезнет
								WAIT(10);
								CREATE_CHAR (26, PedM2, -726.207, 609.126, 5.60114, &ped13, TRUE);//
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped13, -725.144, 606.652, 5.60114, 3, -2, 1.5);// пед убегает

								UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_13);
								SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_EPISODIC_13, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
								SET_CHAR_RELATIONSHIP(ped13, 5, 0);
								SET_SENSE_RANGE(ped13, 45.0);
								SET_CHAR_WILL_USE_COVER(ped13, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);
							}
							if (ped4_hp < 200)
							{
								DELETE_CHAR(&ped14);//выгружаем модель педа(в последствии пед изчезнет
								WAIT(10);
								CREATE_CHAR (26, PedM2, -707.027, 595.88, 5.60114, &ped14, TRUE);//
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped14,  -708.11, 602.17, 5.60114, 3, -2, 1.5);// пед убегает

								UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_12);
								SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_EPISODIC_12, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
								SET_CHAR_RELATIONSHIP(ped14, 5, 0);
								SET_SENSE_RANGE(ped14, 50.0);
								SET_CHAR_WILL_USE_COVER(ped14, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, FALSE);
							}
							if (ped5_hp < 200)
							{
								DELETE_CHAR(&ped15);//выгружаем модель педа(в последствии пед изчезнет
								WAIT(10);
								CREATE_CHAR (26, PedM2, -707.345, 613.941, 5.60114, &ped15, TRUE);//
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped15, -708.471, 607.007, 5.60114, 3, -2, 1.5);// пед убегает

								UpdateWeaponOfPed(ped15, WEAPON_EPISODIC_12);
								SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_EPISODIC_12, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
								SET_CHAR_RELATIONSHIP(ped15, 5, 0);
								SET_SENSE_RANGE(ped15, 45.0);
								SET_CHAR_WILL_USE_COVER(ped15, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, FALSE);
							}
						}
						else
						{
							if ((ped1_hp < 200) && (blip_off1 == 1))
							{
								EXPLODE_CHAR_HEAD(ped11);
								REMOVE_BLIP(ped1_ico);//Удаляем иконку на радаре
								blip_off1 = 0;
							}
							if ((ped2_hp < 200) && (blip_off2 == 1))
							{
								EXPLODE_CHAR_HEAD(ped12);
								REMOVE_BLIP(ped2_ico);//Удаляем иконку на радаре
								blip_off2 = 0;
							}
							if ((ped3_hp < 200) && (blip_off3 == 1))
							{
								EXPLODE_CHAR_HEAD(ped13);
								REMOVE_BLIP(ped3_ico);//Удаляем иконку на радаре
								blip_off3 = 0;
							}
							if ((ped4_hp < 200) && (blip_off4 == 1))
							{
								EXPLODE_CHAR_HEAD(ped14);
								REMOVE_BLIP(ped4_ico);//Удаляем иконку на радаре
								blip_off4 = 0;
							}
							if ((ped5_hp < 200) && (blip_off5 == 1))
							{
								EXPLODE_CHAR_HEAD(ped15);
								REMOVE_BLIP(ped5_ico);//Удаляем иконку на радаре
								blip_off5 = 0;
							}
						}
					
						if ((snuper_hp < 200) && (explo_car == 0))
						{
							if (!IS_CHAR_DEAD(ped11))
							{
								ADD_BLIP_FOR_CHAR(ped11, &ped1_ico);
								CHANGE_BLIP_SPRITE(ped1_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(ped1_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(ped1_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped1_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
							}
							if (!IS_CHAR_DEAD(ped12))
							{
								ADD_BLIP_FOR_CHAR(ped12, &ped2_ico);
								CHANGE_BLIP_SPRITE(ped2_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(ped2_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(ped2_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped2_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
							}
							if (!IS_CHAR_DEAD(ped13))
							{
								ADD_BLIP_FOR_CHAR(ped13, &ped3_ico);
								CHANGE_BLIP_SPRITE(ped3_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(ped3_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(ped3_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped3_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
							}
							if (!IS_CHAR_DEAD(ped14))
							{
								ADD_BLIP_FOR_CHAR(ped14, &ped4_ico);
								CHANGE_BLIP_SPRITE(ped4_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(ped4_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(ped4_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped4_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
							}
							if (!IS_CHAR_DEAD(ped15))
							{
								ADD_BLIP_FOR_CHAR(ped15, &ped5_ico);
								CHANGE_BLIP_SPRITE(ped5_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(ped5_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(ped5_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped5_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
							}

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB2_22", 5000, 1);//~g~ Finish off the rest of the Haitians so the Cubans can move forward.
							REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
							explo_car = 1;
							EXPLODE_CHAR_HEAD(ped16);
							FREEZE_CHAR_POSITION(ped16, 0);
						}
						if ((IS_CHAR_DEAD(ped16)) && (ped1_hp < 200) && (ped2_hp < 200) && (ped3_hp < 200) && (ped4_hp < 200) && (ped5_hp < 200))
						{
							// сценка тут
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							CLEAR_AREA(-715.156, 604.681, 5.3873, 55.0, 1);//очещаем зону загрузки

							//ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -719.979, 604.141, 5.79146 ); // куда смотрит камера
							SET_CAM_POS			( camera, -731.635, 604.463, 8.32183 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, -726.973, 606.031, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, -727.747, 602.939, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped3, -728.489, 604.944, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped7, -730.102, 602.198, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped8, -730.541, 606.052, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped9, -731.432, 602.913, 5.3873, 3, -2, 1.5);// пед убегает
							SetTime(2000);

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, -727.795, 604.124, 5.72238 ); // куда смотрит камера
							SET_CAM_POS			( camera, -716.811, 603.968, 7.70427 );//расположение камеры

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_NAF", "CUB2_21", 0, 0);//Fight like men with huge cojones!
							START_SCRIPT_CONVERSATION(1, 1);

							SET_CHAR_COORDINATES(ped1, -716.491, 605.233, 5.3873);
							SET_CHAR_COORDINATES(ped2, -716.441, 602.632, 5.3873);
							SET_CHAR_COORDINATES(ped3, -716.019, 602.632, 5.3873);
							
							TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, 10000, 0);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, -727.747, 602.939, 5.3873, 3, -2, 1.5);// пед убегает
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped3, -728.489, 604.944, 5.3873, 3, -2, 1.5);// пед убегает
							SetTime(2000);
							SetSpeech();

							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped10);//выгружаем модель педа(в последствии пед изчезнет
							WAIT(10);

							CREATE_CHAR (26, PedM2, -727.614, 619.995, 5.60114, &ped4, TRUE);//
							CREATE_CHAR (26, PedM2, -739.468, 634.276, 5.60114, &ped5, TRUE);//
							CREATE_CHAR (26, PedM2, -750.114, 625.911, 5.60114, &ped6, TRUE);//
							CREATE_CHAR (26, PedM2, -746.844, 635.373, 5.60114, &ped10, TRUE);//
							SET_CHAR_HEADING(ped4, -165.0);
							SET_CHAR_HEADING(ped5, -165.0);
							SET_CHAR_HEADING(ped6, -125.0);
							SET_CHAR_HEADING(ped10, -125.0);

							UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_12);
							SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_12, TRUE);
							SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
							SET_CHAR_RELATIONSHIP(ped4, 5, 0);
							SET_SENSE_RANGE(ped4, 45.0);
							SET_CHAR_WILL_USE_COVER(ped4, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);

							UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_12);
							SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_12, TRUE);
							SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
							SET_CHAR_RELATIONSHIP(ped5, 5, 0);
							SET_SENSE_RANGE(ped5, 45.0);
							SET_CHAR_WILL_USE_COVER(ped5, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);

							UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_12);
							SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_12, TRUE);
							SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
							SET_CHAR_RELATIONSHIP(ped6, 5, 0);
							SET_SENSE_RANGE(ped6, 45.0);
							SET_CHAR_WILL_USE_COVER(ped6, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);

							UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_12);
							SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_12, TRUE);
							SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
							SET_CHAR_RELATIONSHIP(ped10, 5, 0);
							SET_SENSE_RANGE(ped10, 45.0);
							SET_CHAR_WILL_USE_COVER(ped10, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped10, FALSE);

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							explo_car = 0;
							SetTime(1000);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_NA", "CUB2_16", 0, 0);//Tommy, we have proved our manful bravery!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_NB", "CUB2_17", 0, 0);//Let us steal the van full of drugs and make good our escape!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							SETTIMERA( 0 );
							while (TRUE)
							{
								WAIT(0);
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
								{
									break;
								}
								else if (TIMERA() > 10000)
								{
									WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car1, 0);
									SHUT_CAR_DOOR(car1, 1);
									break;
								}
							}

							ADD_BLIP_FOR_CAR(car1, &cuban_ico);
							CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(cuban_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_CAR");//иконка на радаре называние в истории карты ""
							text = 1;
							break;
						}
						// провалы тут
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (rico_hp < 200)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB1_11", 5000, 1);//~r~You Killed Rico!
							skip = 1;// переменная пропуска
							break;
						}
						else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -591.529, 514.096, 2.163, -791.529, 714.096, 54.163, 0 ))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "T4X4_F", 5000, 1);//~r~You bailed! Too tough for you?!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// забрать фургон
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						GET_CHAR_HEALTH(ped11, &ped1_hp);
						GET_CHAR_HEALTH(ped12, &ped2_hp);
						GET_CHAR_HEALTH(ped13, &ped3_hp);
						GET_CHAR_HEALTH(ped14, &ped4_hp);
						GET_CHAR_HEALTH(ped15, &ped5_hp);

						// респавн педов тут
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -719.0, 594.0, 3.0, -769.0, 644.0, 33.0, 0 )) && (explo_car == 0))
						{
							if (ped1_hp < 200)
							{
								if (TIMERC() > 2000)
								{
									DELETE_CHAR(&ped11);//выгружаем модель педа(в последствии пед изчезнет
									WAIT(10);
									CREATE_CHAR (26, PedM2, -753.97, 635.859, 5.1848, &ped11, TRUE);//
									TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped11, -731.76, 619.604, 5.60114, 3, -2, 1.5);// пед убегает

									UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_12);
									SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_12, TRUE);
									SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);
									SET_CHAR_RELATIONSHIP(ped11, 5, 0);
									SET_SENSE_RANGE(ped11, 45.0);
									SET_CHAR_WILL_USE_COVER(ped11, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped11, FALSE);
									SETTIMERC( 0 );
								}
							}
							if (ped2_hp < 200)
							{
								if (TIMERC() > 2000)
								{
									DELETE_CHAR(&ped12);//выгружаем модель педа(в последствии пед изчезнет
									WAIT(10);
									CREATE_CHAR (26, PedM2, -753.893, 625.645, 5.1848, &ped12, TRUE);//
									TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped12, -739.244, 613.635, 5.60114, 3, -2, 1.5);// пед убегает

									UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_12);
									SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_12, TRUE);
									SET_CHAR_RELATIONSHIP_GROUP(ped12, 5);
									SET_CHAR_RELATIONSHIP(ped12, 5, 0);
									SET_SENSE_RANGE(ped12, 45.0);
									SET_CHAR_WILL_USE_COVER(ped12, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped12, FALSE);
									SETTIMERC( 0 );
								}
							}
							if (ped3_hp < 200)
							{
								if (TIMERC() > 2000)
								{
									DELETE_CHAR(&ped13);//выгружаем модель педа(в последствии пед изчезнет
									WAIT(10);
									CREATE_CHAR (26, PedM2, -753.97, 635.859, 5.1848, &ped13, TRUE);//
									TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped13, -737.934, 622.338, 5.60114, 3, -2, 1.5);// пед убегает

									UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_12);
									SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_EPISODIC_12, TRUE);
									SET_CHAR_RELATIONSHIP_GROUP(ped13, 5);
									SET_CHAR_RELATIONSHIP(ped13, 5, 0);
									SET_SENSE_RANGE(ped13, 45.0);
									SET_CHAR_WILL_USE_COVER(ped13, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped13, FALSE);
									SETTIMERC( 0 );
								}
							}
							if (ped4_hp < 200)
							{
								if (TIMERC() > 2000)
								{
									DELETE_CHAR(&ped14);//выгружаем модель педа(в последствии пед изчезнет
									WAIT(10);
									CREATE_CHAR (26, PedM2, -753.893, 625.645, 5.1848, &ped14, TRUE);//
									TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped14,  -736.178, 617.103, 5.60114, 3, -2, 1.5);// пед убегает

									UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_12);
									SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_EPISODIC_12, TRUE);
									SET_CHAR_RELATIONSHIP_GROUP(ped14, 5);
									SET_CHAR_RELATIONSHIP(ped14, 5, 0);
									SET_SENSE_RANGE(ped14, 45.0);
									SET_CHAR_WILL_USE_COVER(ped14, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped14, FALSE);
									SETTIMERC( 0 );
								}
							}
							if (ped5_hp < 200)
							{
								if (TIMERC() > 2000)
								{
									DELETE_CHAR(&ped15);//выгружаем модель педа(в последствии пед изчезнет
									WAIT(10);
									CREATE_CHAR (26, PedM2, -753.97, 635.859, 5.1848, &ped15, TRUE);//
									TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped15, -734.338, 621.63, 5.60114, 3, -2, 1.5);// пед убегает

									UpdateWeaponOfPed(ped15, WEAPON_EPISODIC_12);
									SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_EPISODIC_12, TRUE);
									SET_CHAR_RELATIONSHIP_GROUP(ped15, 5);
									SET_CHAR_RELATIONSHIP(ped15, 5, 0);
									SET_SENSE_RANGE(ped15, 45.0);
									SET_CHAR_WILL_USE_COVER(ped15, 1);
									SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, FALSE);
									SETTIMERC( 0 );
								}
							}
						}
						else
						{
							if (explo_car == 0)
							{
								// баррикада тут
								SET_MAX_WANTED_LEVEL(6);
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет
								WAIT(10);
								CREATE_CHAR (26, PedM2, -682.079,605.765,5.60114, &ped4, TRUE);//
								CREATE_CHAR (26, PedM2, -681.713,603.338,5.60114, &ped5, TRUE);//
								CREATE_CHAR (26, PedM2, -681.861,600.719,5.60114, &ped6, TRUE);//
								SET_CHAR_HEADING(ped4, 85.0);
								SET_CHAR_HEADING(ped5, 90.0);
								SET_CHAR_HEADING(ped6, 110.0);

								UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_12);
								SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_12, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
								SET_CHAR_RELATIONSHIP(ped4, 5, 0);
								SET_SENSE_RANGE(ped4, 45.0);
								SET_CHAR_WILL_USE_COVER(ped4, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);

								UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_12);
								SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_12, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
								SET_CHAR_RELATIONSHIP(ped5, 5, 0);
								SET_SENSE_RANGE(ped5, 45.0);
								SET_CHAR_WILL_USE_COVER(ped5, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);

								UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_12);
								SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_12, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
								SET_CHAR_RELATIONSHIP(ped6, 5, 0);
								SET_SENSE_RANGE(ped6, 45.0);
								SET_CHAR_WILL_USE_COVER(ped6, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);

								ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
								APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
								explo_car = 1;
							}
						}

						if (IS_CHAR_IN_CAR(GetPlayerPed(), car1))
						{
							DRAW_CHECKPOINT( -729.157, -71.6485, 5.6909, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -729.157, -71.6485, 5.6909, &PlayR);//проверка "игрок на координатах"
							if ( PlayR < 2.0 )
							{
								skip = 2;
								break;
							}
							if (text == 1)
							{
								REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_COORD(-729.157, -71.6485, 5.6909, &cuban_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(cuban_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "CUB2_24", 5000, 1);//~g~Return to Robina's Cafe with the Van and park it round the back.
								text = 0;
							}
						}
						else
						{
							if (text == 0)
							{
								REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CAR(car1, &cuban_ico);
								CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(cuban_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_CAR");//иконка на радаре называние в истории карты ""

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "IN_VEH", 5000, 1);//~g~Hey! Get back in the vehicle!
								text = 1;
							}
						}
						// провалы тут
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CAR_DEAD(car1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB2_11", 5000, 1);//~r~You fool, we needed that car.
							skip = 1;// переменная пропуска
							break;
						}
					}
				}

				// чистим скрипт
				WAIT( 100 );
				REMOVE_PICKUP(sweap_1);// выгружаем оружие
				SET_MAX_WANTED_LEVEL(6);

				REMOVE_BLIP(ped1_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped2_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped3_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped4_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped5_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(trubka);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(gunboxM);//выгружаем модель

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель

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

				// выгружвем машину
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)

				DELETE_OBJECT(&gunbox1);
				DELETE_OBJECT( &trubka_1 );
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&trubka_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&gunbox1);

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_CUB_2" );//Cannon Fodder
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(2000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +2000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 2000);
					G_CUBAN = 3;
					autosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;

			}
		}
//============================== Naval Engagement ======================================
		else if ((G_ONMISSION == 0) && (G_CUBAN == 3))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-737.043, -74.3556, 5.6213, &cuban_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cuban_ico, BLIP_COMEDY_CLUB);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(cuban_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "LG_11");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( -737.043, -74.3556, 5.6213, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -737.043, -74.3556, 5.6213, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("CUB_3", 15000, CUTSCENE_CUBAN);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-1173.5, -599.6, 10.2, 277.1);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
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
				SET_CHAR_COORDINATES(GetPlayerPed(), -737.142, -73.7556, 5.9432 );// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 5.0 );

				Cam camera;
				Car car1, car2, car3, car4;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20;
				Blip keys1_ico, keys2_ico, keys3_ico;
				Pickup keys_1, keys_2, keys_3, aid_1;

				skip = 0;
				keys_UP1 = 0;
				keys_UP2 = 0;
				keys_UP3 = 0;
				tnt1 = 0;
				tnt2 = 0;
				tnt3 = 0;

				uint CarM1 = MODEL_JETMAX;// Лодка Рико 
				uint CarM2 = MODEL_TROPIC;// Трипик
				uint CarM3 = MODEL_VC_DINGHY;// Лодка Гаитян

				uint PedM1 = MODEL_M_Y_GLAT_HI_01;// Рико
				uint PedM2 = MODEL_M_M_GJAM_HI_01;// Гаитянин
				uint PedM3 = MODEL_M_Y_GIRI_LO_01;// Акула
				uint PedM4 = MODEL_M_Y_GIRI_LO_02;// Акула
				uint PedM5 = MODEL_M_Y_GIRI_LO_03;// Акула
				uint ped1_hp, ped2_hp, ped3_hp, ped4_hp, ped5_hp, ped6_hp, ped7_hp, ped8_hp, ped9_hp, rico_hp;

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);
				REQUEST_MODEL(CarM3);
				while (!HAS_MODEL_LOADED(CarM3)) WAIT(100);

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

				CREATE_CAR(CarM1, -286.661, -630.995, 0.58805, &car1, TRUE);// Лодка Рико 
				SET_CAR_HEADING(car1, 20.0);
				CREATE_CAR(CarM2, -215.809, 272.432, -2.0, &car2, TRUE);// Трипик
				SET_CAR_HEADING(car2, -50.0);
				CREATE_CAR(CarM2, -227.354, 263.014, -2.0, &car3, TRUE);// Трипик 
				SET_CAR_HEADING(car3, 130.0);
				CREATE_CAR(CarM3, -318.118, -603.255, 0.58805, &car4, TRUE);// Лодка Гаитян 

				CHANGE_CAR_COLOUR( car1, 39, 89 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car1, 127, 127 );//цвет отрожений машины

				// педы
				CREATE_CHAR (26, PedM1, -292.071, -634.141, 4.96902, &ped1, TRUE);// Рико
				CREATE_CHAR (26, PedM2, -217.111, 263.371, 3.83098, &ped2, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -216.913, 264.901, 3.83098, &ped3, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -218.574, 263.659, 3.83098, &ped4, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -216.945, 271.992, 4.50132, &ped5, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -218.759, 269.886, 2.04082, &ped6, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -219.287, 272.755, 2.74539, &ped7, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -226.085, 263.186, 4.50132, &ped8, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -227.497, 266.211, 2.74539, &ped9, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -224.211, 265.371, 2.04082, &ped10, TRUE);// Гаитянин
				SET_CHAR_COMPONENT_VARIATION(ped1, 1, 1, 0);
				SET_CHAR_HEALTH(ped1, 2000);

				SET_CHAR_HEADING(ped1, 110.0);
				SET_CHAR_HEADING(ped2, -145.0);
				SET_CHAR_HEADING(ped3, -165.0);
				SET_CHAR_HEADING(ped4, -125.0);

				// Акулы
				CREATE_CHAR (26, PedM4, -216.336, 262.408, 3.83098, &ped11, TRUE);// Акула
				CREATE_CHAR (26, PedM3, -214.872, 262.121, 3.83098, &ped12, TRUE);// Акула
				CREATE_CHAR (26, PedM5, -216.533, 260.879, 3.83098, &ped13, TRUE);// Акула
				CREATE_CHAR (26, PedM5, -175.311, 237.956, 6.28518, &ped14, TRUE);// Акула
				CREATE_CHAR (26, PedM4, -197.095, 232.627, 6.32339, &ped15, TRUE);// Акула
				CREATE_CHAR (26, PedM3, -212.972, 248.394, 4.04213, &ped16, TRUE);// Акула
				CREATE_CHAR (26, PedM3, -194.902, 222.981, 7.31697, &ped17, TRUE);// Акула
				CREATE_CHAR (26, PedM4, -200.362, 217.401, 7.31697, &ped18, TRUE);// Акула
				CREATE_CHAR (26, PedM5, -215.334, 205.893, 6.28518, &ped19, TRUE);// Акула
				CREATE_CHAR (26, PedM4, -188.995, 224.981, 21.1674, &ped20, TRUE);// Акула

				SET_CHAR_HEADING(ped11, 35.0);
				SET_CHAR_HEADING(ped12, 35.0);
				SET_CHAR_HEADING(ped13, 5.0);
				SET_CHAR_HEADING(ped14, 35.0);
				SET_CHAR_HEADING(ped15, 35.0);
				SET_CHAR_HEADING(ped16, 35.0);
				SET_CHAR_HEADING(ped17, 35.0);
				SET_CHAR_HEADING(ped18, 35.0);
				SET_CHAR_HEADING(ped19, 35.0);
				SET_CHAR_HEADING(ped20, 35.0);

				//таччим педов к машине
				ATTACH_PED_TO_CAR( ped5, car3, 0, -0.6836, -1.08221, 3.704, 0.0, 110, 1, 0 );
				ATTACH_PED_TO_CAR( ped6, car3, 0, -0.2142, -3.92239, 1.159, 0.0, 105, 1, 0 );
				ATTACH_PED_TO_CAR( ped7, car3, 0, 2.54061, -1.94455, 1.948, 0.0, 85, 1, 0 );
				ATTACH_PED_TO_CAR( ped8, car2, 0, -0.39317, -1.15265, 3.704, 0.0, -80, 1, 1 );
				ATTACH_PED_TO_CAR( ped9, car2, 0, -2.48369, -2.45645, 1.948, 0.0, -45, 1, 1 );
				ATTACH_PED_TO_CAR( ped10, car2, 0, 0.05384, -3.89645, 1.159, 0.0, -80, 1, 1 );

				FREEZE_CAR_POSITION(car2, 1);
				FREEZE_CAR_POSITION(car3, 1);


				// грузим анимации
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				REQUEST_ANIMS( "throw_grenade" );
				while (!HAVE_ANIMS_LOADED( "throw_grenade" )) WAIT(0);

				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				RELEASE_WEATHER();

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "CUB_4", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("cub_4");
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

				ADD_BLIP_FOR_COORD(-293.338, -634.651, 4.64145, &cuban_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(cuban_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"
				PRINT_STRING_IN_STRING("string", "CUB3_07", 5000, 1);//~g~ Go meet Rico. He'll drive you to the meet location.

				// вооружаем
				UpdateWeaponOfPed(ped1, WEAPON_MP5);

				UpdateWeaponOfPed(ped2, WEAPON_AK47);
				UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_13);

				UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped6, WEAPON_AK47);
				UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped8, WEAPON_AK47);
				UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_13);

				UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_13);

				UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_11);
				UpdateWeaponOfPed(ped15, WEAPON_AK47);
				UpdateWeaponOfPed(ped16, WEAPON_AK47);
				UpdateWeaponOfPed(ped17, WEAPON_AK47);
				UpdateWeaponOfPed(ped18, WEAPON_AK47);
				UpdateWeaponOfPed(ped19, WEAPON_EPISODIC_11);
				UpdateWeaponOfPed(ped20, WEAPON_SNIPERRIFLE);

				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_13, TRUE);

				SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_EPISODIC_11, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_EPISODIC_11, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_SNIPERRIFLE, TRUE);

				// лояльность игроку
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
				SET_CHAR_RELATIONSHIP(ped1, 5, 24);

				CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -205.665, 228.89, 7.24698, 90.0, 0.0, -40.0, &aid_1);//Аптека

				// Приехать на причал
				while (TRUE)
				{
					WAIT(0);
					GET_CHAR_HEALTH(ped1, &rico_hp);

					DRAW_CHECKPOINT( -293.338, -634.651, 4.64145, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -293.338, -634.651, 4.64145, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 2.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
						SET_CHAR_INVINCIBLE(ped1, 1);
						SET_CHAR_COORDINATES(GetPlayerPed(), -293.338, -634.651, 4.69394 );// перемещаем игрока
						SET_CHAR_HEADING(GetPlayerPed(), -70.0 );

						CREATE_PICKUP_ROTATE(mission_keis2, 22, 20, -216.792, 262.904, 3.689, 0.0, 0.0, 130.0, &keys_1);
						CREATE_PICKUP_ROTATE(mission_keis2, 22, 20, -198.144, 232.781, 6.201, 0.0, 0.0, 40.0, &keys_2);
						CREATE_PICKUP_ROTATE(mission_keis2, 22, 20, -198.939, 232.103, 6.201, 0.0, 0.0, 40.0, &keys_3);

						// ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, -292.829, -634.263, 5.68324 ); // куда смотрит камера
						SET_CAM_POS			( camera, -290.056, -637.498, 6.78833 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );
						SetTime(500);

						TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R8_RA", "CUB3_01", 0, 0);//Hey Rico. Nice boat, you ready?
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 4000 );//Воиспроизвидение анимации на педе
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R8_SA", "CUB3_05", 0, 0);//Si Tommy. Now you be a good shot today,
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						// меняем ракурс
						POINT_CAM_AT_COORD	( camera, -289.281, -630.785, 1.41952 ); // куда смотрит камера
						SET_CAM_POS			( camera, -271.799, -635.171, 6.94475 );//расположение камеры

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R8_TA", "CUB3_06", 0, 0);//My boat, she no good full of holes, ok?
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
						while(true)
						{
							WAIT(0);
							if (IS_SCREEN_FADED_OUT())
							{
								break;
							}
						}

						TASK_ENTER_CAR_AS_DRIVER(ped1, car1, TRUE);//
						WARP_CHAR_INTO_CAR_AS_PASSENGER(GetPlayerPed(), car1, 1);

						//Грузим пути
						REQUEST_CAR_RECORDING( 3056 ); // полёт Основной
						while (!HAS_CAR_RECORDING_BEEN_LOADED( 3056 )) WAIT(0);

						START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3056, 0.0, 0.0, 0.5);
						SET_PLAYBACK_SPEED(car1, 0.65);

						SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_MP5, TRUE);
						UpdateWeaponOfPed(GetPlayerPed(), WEAPON_AK47);
						SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_AK47, TRUE);

						DETACH_PED(ped5, 1);
						DETACH_PED(ped6, 1);
						DETACH_PED(ped7, 1);
						DETACH_PED(ped8, 1);
						DETACH_PED(ped9, 1);
						DETACH_PED(ped10, 1);
						SETTIMERA( 0 );

						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана

						// меняем ракурс
						while(true)
						{
							WAIT(0);
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							POINT_CAM_AT_COORD	( camera, PlayX, PlayY, PlayZ ); // куда смотрит камера
							SET_CAM_POS			( camera, -230.966, 305.548, 4.91723 );//расположение камеры

							if (TIMERA() > 6000)
							{
								break;
							}
						}

						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 5000 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped11, "stand_idle_d", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 5000 );//Воиспроизвидение анимации на педе

						// меняем ракурс
						POINT_CAM_AT_COORD	( camera, -217.696, 262.518, 4.36645 ); // куда смотрит камера
						SET_CAM_POS			( camera, -210.674, 264.025, 5.87273 );//расположение камеры
						SetTime(3000);

						STOP_PLAYBACK_RECORDED_CAR(car1);
						REMOVE_CAR_RECORDING( 3056 ); // выгружаем пути транспорта

						//удяляем камеру тут
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

						//свой-чужой
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

						SET_SENSE_RANGE(ped2, 45.0);
						SET_SENSE_RANGE(ped3, 45.0);
						SET_SENSE_RANGE(ped4, 45.0);
						SET_SENSE_RANGE(ped5, 45.0);
						SET_SENSE_RANGE(ped6, 45.0);
						SET_SENSE_RANGE(ped7, 45.0);
						SET_SENSE_RANGE(ped8, 45.0);
						SET_SENSE_RANGE(ped9, 45.0);
						SET_SENSE_RANGE(ped10, 45.0);
						SET_SENSE_RANGE(ped11, 45.0);
						SET_SENSE_RANGE(ped12, 45.0);
						SET_SENSE_RANGE(ped13, 45.0);
						SET_SENSE_RANGE(ped14, 45.0);
						SET_SENSE_RANGE(ped15, 45.0);
						SET_SENSE_RANGE(ped16, 45.0);
						SET_SENSE_RANGE(ped17, 45.0);
						SET_SENSE_RANGE(ped18, 45.0);
						SET_SENSE_RANGE(ped19, 45.0);
						SET_SENSE_RANGE(ped20, 45.0);

						SET_CHAR_WILL_USE_COVER(ped2, 1);
						SET_CHAR_WILL_USE_COVER(ped3, 1);
						SET_CHAR_WILL_USE_COVER(ped4, 1);
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

						SET_CHAR_SHOOT_RATE(ped2, 15);
						SET_CHAR_SHOOT_RATE(ped3, 15);
						SET_CHAR_SHOOT_RATE(ped4, 15);
						SET_CHAR_SHOOT_RATE(ped5, 15);
						SET_CHAR_SHOOT_RATE(ped6, 15);
						SET_CHAR_SHOOT_RATE(ped7, 15);
						SET_CHAR_SHOOT_RATE(ped8, 15);
						SET_CHAR_SHOOT_RATE(ped9, 15);
						SET_CHAR_SHOOT_RATE(ped10, 15);
						SET_CHAR_SHOOT_RATE(ped11, 15);
						SET_CHAR_SHOOT_RATE(ped12, 15);
						SET_CHAR_SHOOT_RATE(ped13, 15);

						SET_CHAR_FIRE_DAMAGE_MULTIPLIER( ped2, 0.20000000 );
						SET_CHAR_FIRE_DAMAGE_MULTIPLIER( ped3, 0.20000000 );
						SET_CHAR_FIRE_DAMAGE_MULTIPLIER( ped4, 0.20000000 );
						SET_CHAR_FIRE_DAMAGE_MULTIPLIER( ped5, 0.20000000 );
						SET_CHAR_FIRE_DAMAGE_MULTIPLIER( ped6, 0.20000000 );
						SET_CHAR_FIRE_DAMAGE_MULTIPLIER( ped7, 0.20000000 );
						SET_CHAR_FIRE_DAMAGE_MULTIPLIER( ped8, 0.20000000 );
						SET_CHAR_FIRE_DAMAGE_MULTIPLIER( ped9, 0.20000000 );
						SET_CHAR_FIRE_DAMAGE_MULTIPLIER( ped10, 0.20000000 );
						SET_CHAR_FIRE_DAMAGE_MULTIPLIER( ped11, 0.20000000 );
						SET_CHAR_FIRE_DAMAGE_MULTIPLIER( ped12, 0.20000000 );
						SET_CHAR_FIRE_DAMAGE_MULTIPLIER( ped13, 0.20000000 );

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped5, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R8_UA", "CUB3_08", 0, 0);//Uh oh.. Pack of Cubans. We under attack!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "CUB3_02", 5000, 1);//~g~KILL ALL THE HAITIANS ON THE BOATS!!
						break;
					}
					// провал миссии тут
					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if (IS_CAR_DEAD(car1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "COK3_7", 5000, 1);//r~You destroyed the boat!
						skip = 1;// переменная пропуска
						break;
					}
					else if (rico_hp < 100)
					{
						EXPLODE_CHAR_HEAD(ped1);
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "CUB1_11", 5000, 1);//~r~You Killed Rico!
						skip = 1;// переменная пропуска
						break;
					}
				}

				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						GET_CHAR_HEALTH(ped1, &rico_hp);
						GET_CHAR_HEALTH(ped2, &ped1_hp);
						GET_CHAR_HEALTH(ped3, &ped2_hp);
						GET_CHAR_HEALTH(ped4, &ped3_hp);
						GET_CHAR_HEALTH(ped5, &ped4_hp);
						GET_CHAR_HEALTH(ped6, &ped5_hp);
						GET_CHAR_HEALTH(ped7, &ped6_hp);
						GET_CHAR_HEALTH(ped8, &ped7_hp);
						GET_CHAR_HEALTH(ped9, &ped8_hp);
						GET_CHAR_HEALTH(ped10, &ped9_hp);

						if ((ped1_hp < 200) && (ped2_hp < 200) && (ped3_hp < 200) && (ped4_hp < 200) && (ped5_hp < 200) && (ped6_hp < 200) && (ped7_hp < 200) && (ped8_hp < 200) && (ped9_hp < 200))
						{

							//Грузим пути
							REQUEST_CAR_RECORDING( 3057 ); // полёт Основной
							while (!HAS_CAR_RECORDING_BEEN_LOADED( 3057 )) WAIT(0);

							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3057, 0.0, 0.0, 0.5);
							SET_PLAYBACK_SPEED(car1, 1.2);

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							// ставим камеру
							CREATE_CAM( 14, &camera );
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							SETTIMERA( 0 );

							// меняем ракурс
							while(true)
							{
								WAIT(0);
								GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
								POINT_CAM_AT_COORD	( camera, PlayX, PlayY, PlayZ ); // куда смотрит камера
								SET_CAM_POS			( camera, -201.132, 270.474, 7.81752 );//расположение камеры

								if (TIMERA() > 5000)
								{
									break;
								}
							}

							STOP_PLAYBACK_RECORDED_CAR(car1);
							REMOVE_CAR_RECORDING( 3057 ); // выгружаем пути транспорта

							DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
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

							GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_AK47, 30, FALSE);	
							WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), -184.541, 273.884, 4.69363);//телепартируем из катера
							SET_CHAR_HEADING(GetPlayerPed(), 130.0);
							FREEZE_CAR_POSITION(car1, 1);
							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB3_03", 5000, 1);//~g~Collect all the briefcases filled with the drugs and cash.

							ADD_BLIP_FOR_PICKUP(keys_1, &keys1_ico);
							CHANGE_BLIP_SPRITE(keys1_ico, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(keys1_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(keys1_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(keys1_ico, "MO_TARGET");//иконка на радаре "Товар"

							ADD_BLIP_FOR_PICKUP(keys_2, &keys2_ico);
							CHANGE_BLIP_SPRITE(keys2_ico, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(keys2_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(keys2_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(keys2_ico, "MO_TARGET");//иконка на радаре "Товар"

							ADD_BLIP_FOR_PICKUP(keys_3, &keys3_ico);
							CHANGE_BLIP_SPRITE(keys3_ico, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(keys3_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(keys3_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(keys3_ico, "MO_TARGET");//иконка на радаре "Товар"


							SET_CHAR_INVINCIBLE(ped1, 0);
							break;
						}

						// провал миссии тут
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CAR_DEAD(car1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "COK3_7", 5000, 1);//r~You destroyed the boat!
							skip = 1;// переменная пропуска
							break;
						}
						else if (rico_hp < 100)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB1_11", 5000, 1);//~r~You Killed Rico!
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
						if ((HAS_PICKUP_BEEN_COLLECTED( keys_1 )) && ( keys_UP1 == 0))
						{
							REMOVE_BLIP(keys1_ico);//Удаляем иконку на радаре
							keys_UP1 = 1;
						}
						if ((HAS_PICKUP_BEEN_COLLECTED( keys_2 )) && ( keys_UP2 == 0))
						{
							REMOVE_BLIP(keys2_ico);//Удаляем иконку на радаре
							keys_UP2 = 1;
						}
						if ((HAS_PICKUP_BEEN_COLLECTED( keys_3 )) && ( keys_UP3 == 0))
						{
							REMOVE_BLIP(keys3_ico);//Удаляем иконку на радаре
							keys_UP3 = 1;
						}

						if (( keys_UP1 == 1) && ( keys_UP2 == 1) && ( keys_UP3 == 1))
						{
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет
							CREATE_CHAR_INSIDE_CAR(car4, 1, PedM2, &ped2);// Гаитянин
							CREATE_CHAR (26, PedM2, -216.913, 264.901, 3.83098, &ped3, TRUE);// Гаитянин
							ATTACH_PED_TO_CAR( ped3, car4, 0, -0.112316, -0.66938, 0.945863, 0.0, 0, 1, 0 );

							UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped3, WEAPON_GRENADE);

							SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_GRENADE, TRUE);

							SET_CAR_COORDINATES(car4, -174.639, 295.999, 1.00084 );// перемещаем транспорт
							SET_CAR_HEADING(car4, -110.0 );

							FREEZE_CAR_POSITION(car1, 0);
							FREEZE_CAR_POSITION(car2, 0);
							FREEZE_CAR_POSITION(car3, 0);
							SetTime(500);

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -178.24, 286.227, 1.19084 ); // куда смотрит камера
							SET_CAM_POS			( camera, -199.606, 282.394, 7.87958 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							SetTime(1000);

							DETACH_PED(ped3, 1);
							SET_CHAR_HEADING(ped3, 170.0);

							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped3, "grenade_throw_short", "throw_grenade", 8.0, 1, 0, 0, 0, 1100 );//Воиспроизвидение анимации на педе
							SetTime(2000);
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped3, car4, 1);

							EXPLODE_CAR(car1, 1, 1);
							SetTime(2000);

							SET_CAR_COORDINATES(car4, -196.496, 271.283, 1.19084 );// перемещаем транспорт
							SET_CAR_HEADING(car4, 175.0 );

							WARP_CHAR_FROM_CAR_TO_COORD(ped2, -199.778, 269.321, 3.73762);//телепартируем из катера
							WARP_CHAR_FROM_CAR_TO_COORD(ped3, -198.367, 268.233, 3.73762);//телепартируем из катера
							SET_CHAR_HEADING(ped2, 170.0);
							SET_CHAR_HEADING(ped3, 170.0);

							//свой-чужой
							SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
							SET_CHAR_RELATIONSHIP(ped2, 5, 0);
							SET_CHAR_RELATIONSHIP(ped3, 5, 0);
							SET_SENSE_RANGE(ped2, 95.0);
							SET_SENSE_RANGE(ped3, 95.0);
							SET_CHAR_WILL_USE_COVER(ped2, 1);
							SET_CHAR_WILL_USE_COVER(ped3, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped2, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped3, FALSE);

							//удяляем камеру тут
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_13, TRUE);

							ADD_BLIP_FOR_COORD(-737.034, -74.3699, 5.56987, &cuban_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(cuban_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

							ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB3_04", 5000, 1);// ~g~Get the drugs and cash back to Umberto.
							break;
						}
						// провал миссии тут
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
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
						DRAW_CHECKPOINT( -737.034, -74.3699, 5.56987, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -737.034, -74.3699, 5.56987, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							// сценка тут
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -736.916, -74.6126, 7.60915 ); // куда смотрит камера
							SET_CAM_POS			( camera, -737.669, -62.7373, 10.9415 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), -735.814, -88.3123, 5.56987, 3, -2);// Томми бежит в двери
							SetTime(2500);
							SET_CHAR_COORDINATES(GetPlayerPed(), -728.587, -86.6162, 5.92349);// перемещаем
							SET_CHAR_HEADING(GetPlayerPed(), -90.0);
							SetTime(1000);

							ALTER_WANTED_LEVEL(GetPlayerIndex(), 0);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());

							//удяляем камеру тут
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							skip = 2;
							break;
						}
						// провал миссии тут
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
					}
				}

				// чистим скрипт тут
				REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(keys1_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(keys2_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(keys3_ico);//Удаляем иконку на радаре

				REMOVE_PICKUP(keys_1);
				REMOVE_PICKUP(keys_2);
				REMOVE_PICKUP(keys_3);
				REMOVE_PICKUP(aid_1);

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//выгружаем модель

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель

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
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_CUB_3" );//Naval Engagement
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(4000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +4000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 4000);
					G_CUBAN = 4;
					autosave = 1;
				}
				G_ONMISSION = 0;

			}
		}
//============================== Trojan Voodoo ======================================
		else if ((G_ONMISSION == 0) && (G_CUBAN == 4) && (G_HAITI >= 5))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-737.043, -74.3556, 5.6213, &cuban_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(cuban_ico, BLIP_COMEDY_CLUB);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(cuban_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "LG_11");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( -737.043, -74.3556, 5.6213, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -737.043, -74.3556, 5.6213, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("CUB_4", 15000, CUTSCENE_CUBAN);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-1173.5, -599.6, 10.2, 277.1);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
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
				SET_CHAR_COORDINATES(GetPlayerPed(), -737.142, -73.7556, 5.9432 );// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 5.0 );

				Cam camera;
				Car car1, car2, car3;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20;
				Blip tnt1_ico, tnt2_ico, tnt3_ico;
				Object tnt_1, tnt_2, tnt_3, vorota;
				Texture fon, timer;

				skip = 0;
				start = 1;
				timer_on = 0;
				stalking = 0;
				in_car = 0;
				in_zon = 0;
				in_zavod = 0;
				rrr_on = 1;
				vorotaY = 607.411;
				time_m = 1;
				time_s = 30;
				sound = 0;
				p_event = 0;
				trigger1 = 0;
				trigger2 = 0;
				trigger3 = 0;
				trigger4 = 0;
				trigger5 = 0;
				trigger6 = 0;
				trigger7 = 0;
				tnt1 = 0;
				tnt2 = 0;
				tnt3 = 0;

				uint CarM1 = MODEL_VOODOO;// Voodoo
				uint PedM1 = MODEL_M_Y_GLAT_HI_01;// Кубинец
				uint PedM2 = MODEL_M_M_GJAM_HI_01;// Гаитянин
				uint dynamite_1 = dynamite;// динамит
				uint vorotaM = vc_electricgate; //ворота
				uint rico_hp, car_HP;

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);

				REQUEST_MODEL(PedM1);// 
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// 
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(dynamite_1);// динамит
				while (!HAS_MODEL_LOADED(dynamite_1)) WAIT(0);
				REQUEST_MODEL(vorotaM);// ворота
				while (!HAS_MODEL_LOADED(vorotaM)) WAIT(0);

				CREATE_CAR(CarM1, -612.301, 705.289, 5.85357, &car1, TRUE);// Voodoo 
				SET_CAR_HEADING(car1, -175.0);
				CREATE_CAR(CarM1, -608.904, 708.173, 5.85357, &car2, TRUE);// Voodoo
				SET_CAR_HEADING(car2, -175.0);
				LOCK_CAR_DOORS(car1, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car2, 3); //блокируем двери автомобиля для игрока

				// педы
				CREATE_CHAR (26, PedM1, -735.919, -74.1093, 5.92349, &ped1, TRUE);// Рико
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped2);// Кубинец
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM1, &ped3);// Кубинец
				CREATE_CHAR_AS_PASSENGER(car1, 1, PedM1, 0, &ped4);// Кубинец
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM1, 0, &ped5);// Кубинец

				CREATE_CHAR (26, PedM2, -682.235, 607.707, 5.92349, &ped6, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -704.865, 600.751, 5.92349, &ped7, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -705.448, 610.131, 5.92349, &ped8, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -707.101, 610.095, 5.92349, &ped9, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -725.794, 608.262, 5.92349, &ped10, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -733.523, 641.775, 5.92349, &ped11, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -734.912, 641.561, 5.92349, &ped12, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -757.481, 636.052, 5.92349, &ped13, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -755.649, 616.688, 5.92349, &ped14, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -763.191, 615.354, 5.92349, &ped15, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -759.549, 604.395, 5.92349, &ped16, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -747.439, 612.458, 5.92349, &ped17, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -749.721, 600.055, 14.0724, &ped18, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -754.285, 620.572, 14.0724, &ped19, TRUE);// Гаитянин
				CREATE_CHAR (26, PedM2, -740.772, 605.086, 18.2701, &ped20, TRUE);// Гаитянин

				SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped13, TRUE);
				SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped14, TRUE);
				SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped15, TRUE);
				SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped16, TRUE);
				SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped17, TRUE);
				SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped18, TRUE);
				SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped19, TRUE);

				SET_CHAR_COMPONENT_VARIATION(ped1, 1, 1, 0);
				SET_CHAR_HEALTH(ped1, 2000);

				SET_CHAR_HEADING(ped1, 30.0);
				SET_CHAR_HEADING(ped6, -175.0);
				SET_CHAR_HEADING(ped7, 85.0);
				SET_CHAR_HEADING(ped8, 170.0);
				SET_CHAR_HEADING(ped9, -170.0);
				SET_CHAR_HEADING(ped10, 105.0);
				SET_CHAR_HEADING(ped11, 105.0);
				SET_CHAR_HEADING(ped12, -110.0);
				SET_CHAR_HEADING(ped13, -155.0);
				SET_CHAR_HEADING(ped14, 30.0);
				SET_CHAR_HEADING(ped15, -35.0);
				SET_CHAR_HEADING(ped16, 5.0);
				SET_CHAR_HEADING(ped17, 95.0);
				SET_CHAR_HEADING(ped18, 30.0);
				SET_CHAR_HEADING(ped19, 90.0);
				SET_CHAR_HEADING(ped20, -90.0);

				// создаём ворота
				CREATE_OBJECT_NO_OFFSET(vorotaM, -681.281, 607.411, 5.23681, &vorota, TRUE);
				SET_OBJECT_HEADING(vorota, -90.0);
				SET_OBJECT_DYNAMIC(vorota, 0);
				SET_OBJECT_INVINCIBLE(vorota, 1);
				FREEZE_OBJECT_POSITION(vorota, 1);

				CREATE_OBJECT_NO_OFFSET(dynamite_1, 872.146, 864.587, 5.441, &tnt_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(dynamite_1, 875.146, 864.587, 5.441, &tnt_2, TRUE);
				CREATE_OBJECT_NO_OFFSET(dynamite_1, 877.146, 864.587, 5.441, &tnt_3, TRUE);

				// грузим анимации
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				REQUEST_ANIMS( "amb@atm" );//загружаем файл с анимацией
				while (!HAVE_ANIMS_LOADED( "amb@atm" )) WAIT(0);

				//------------ загрузка путей ----------------
				REQUEST_CAR_RECORDING( 3058 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3058 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3059 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3059 )) WAIT(0);

				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				RELEASE_WEATHER();

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "CUB_3", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("cub_3");
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

				// вооружаем
				UpdateWeaponOfPed(ped1, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped7, WEAPON_PISTOL);
				UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_11);
				UpdateWeaponOfPed(ped15, WEAPON_AK47);
				UpdateWeaponOfPed(ped16, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped17, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped18, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped19, WEAPON_EPISODIC_11);
				UpdateWeaponOfPed(ped20, WEAPON_AK47);


				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_PISTOL, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_EPISODIC_11, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_EPISODIC_11, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_AK47, TRUE);

				// лояльность игроку
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 0);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 0);
				SET_CHAR_RELATIONSHIP_GROUP(ped4, 0);
				SET_CHAR_RELATIONSHIP_GROUP(ped5, 0);
				SET_CHAR_RELATIONSHIP(ped1, 5, 24);
				SET_CHAR_RELATIONSHIP(ped2, 5, 24);
				SET_CHAR_RELATIONSHIP(ped3, 5, 24);
				SET_CHAR_RELATIONSHIP(ped4, 5, 24);
				SET_CHAR_RELATIONSHIP(ped5, 5, 24);

				START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3058, 0.0, 0.0, 0.0);
				PAUSE_PLAYBACK_RECORDED_CAR(car1);
				START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 3059, 0.0, 0.0, 0.0);
				PAUSE_PLAYBACK_RECORDED_CAR(car2);

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				timer = GET_TEXTURE( textur, "timer_hud" );

				SetTime(1000);
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R14_XG", "", 0, 0);//
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "CUB4_26", 5000, 1);//~g~Take Pepe, head North into Little Haiti and steal a Voodoo car.

				// Найти Вуду
				while (TRUE)
				{
					WAIT(0);
					GET_CHAR_HEALTH(ped1, &rico_hp);

					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -526.375, 18.403, 2.128, -676.375, 218.403, 52.128, 0 )) && ( trigger1 == 0))
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R11_NE", "CUB4_18", 0, 0);//Man, this a nice part of town...
						START_SCRIPT_CONVERSATION(1, 1);
						trigger1 = 1;
					}
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -676.375, -10.738, 2.128, -790.375, 114.262, 52.128, 0 )) && ( trigger2 == 0))
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_NF", "CUB4_20", 0, 0);//I had a beautiful woman... lived around this neighborhood.
						START_SCRIPT_CONVERSATION(1, 1);
						trigger2 = 1;
					}
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -368.908, 279.625, 2.128, -827.908, 429.625, 52.128, 0 )) && ( trigger3 == 0))
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_NG", "CUB4_19", 0, 0);//This place is a dump, man.
						START_SCRIPT_CONVERSATION(1, 1);
						trigger3 = 1;
					}
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -612.53, 587.112, 2.128, -662.53, 637.112, 35.128, 0 )) && ( trigger4 == 0))
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_NG_QQQ1", "CUB4_21", 0, 0);//You know, they do nice pizzas here.
						START_SCRIPT_CONVERSATION(1, 1);
						trigger4 = 1;
					}
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -168.248, 934.492, 2.128, -764.948, 1084.492, 52.128, 0 )) && ( trigger5 == 0))
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_NH", "CUB4_23", 0, 0);//You lost, man?
						START_SCRIPT_CONVERSATION(1, 1);
						trigger5 = 1;
					}

					DRAW_CHECKPOINT( -605.383, 710.026, 5.17858, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -605.383, 710.026, 5.17858, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 1.5) && (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_VOODOO)))
					{
						if (trigger7 == 0)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_NC", "CUB4_12", 0, 0);//Hey, we need a Haitian gang car!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							trigger7 = 1;
						}
					}
					else
					{
						if (trigger7 == 1)
						{
							trigger7 = 0;
						}
					}
					
					// Рико сталкирит за Томми
					GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
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
							GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car3);
							TASK_ENTER_CAR_AS_PASSENGER(ped1, car3, -1, 0);
							SETTIMERB( 0 );
						}
						else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
						{
							if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
							{
								in_car = 0;
								TASK_LEAVE_CAR(ped1, car3);
								MARK_CAR_AS_NO_LONGER_NEEDED(&car3);
								TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
								stalking = 1;
							}
						}
						else if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 1) && (TIMERB() > 15000))
						{
							WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car3, 0);
						}
					}
					else
					{
						if (stalking == 1)
						{
							stalking = 0;
							TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB4_24", 5000, 1);//You've left Pepe behind, go and get him.
						}
					}

					if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_VOODOO)) && (IS_CHAR_IN_MODEL(ped1, MODEL_VOODOO)))
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R11_ND", "CUB4_13", 0, 0);//Oye, let's go find our muchachos!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "CUB4_27", 5000, 1);//~g~Go and meet up with Rico and the other Cubans.
						start = 1;
						break;
					}
					// провал миссии тут
					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(ped1)) || (rico_hp < 100))
					{
						EXPLODE_CHAR_HEAD(ped1);
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "CUB2_10", 5000, 1);//~r~You are supposed to be killing Haitians, not Cubans.
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)) || (IS_CHAR_DEAD(ped5)))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "CUB2_10", 5000, 1);//~r~You are supposed to be killing Haitians, not Cubans.
						skip = 1;// переменная пропуска
						break;
					}
				}
				// Приехать на сходку
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						GET_CHAR_HEALTH(ped1, &rico_hp);
						GET_CAR_HEALTH(car3, &car_HP);

						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -526.375, 18.403, 2.128, -676.375, 218.403, 52.128, 0 )) && ( trigger1 == 0))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_NE", "CUB4_18", 0, 0);//Man, this a nice part of town...
							START_SCRIPT_CONVERSATION(1, 1);
							trigger1 = 1;
						}
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -676.375, -10.738, 2.128, -790.375, 114.262, 52.128, 0 )) && ( trigger2 == 0))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_NF", "CUB4_20", 0, 0);//I had a beautiful woman... lived around this neighborhood.
							START_SCRIPT_CONVERSATION(1, 1);
							trigger2 = 1;
						}
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -368.908, 279.625, 2.128, -827.908, 429.625, 52.128, 0 )) && ( trigger3 == 0))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_NG", "CUB4_19", 0, 0);//This place is a dump, man.
							START_SCRIPT_CONVERSATION(1, 1);
							trigger3 = 1;
						}
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -612.53, 587.112, 2.128, -662.53, 637.112, 35.128, 0 )) && ( trigger4 == 0))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_NG_QQQ1", "CUB4_21", 0, 0);//You know, they do nice pizzas here.
							START_SCRIPT_CONVERSATION(1, 1);
							trigger4 = 1;
						}
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -168.248, 934.492, 2.128, -764.948, 1084.492, 52.128, 0 )) && ( trigger5 == 0))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_NH", "CUB4_23", 0, 0);//You lost, man?
							START_SCRIPT_CONVERSATION(1, 1);
							trigger5 = 1;
						}
						if ((car_HP < 600) && (trigger6 == 0))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_NI", "CUB4_22", 0, 0);//Whoah, man. You drive like a crazy bitch!
							START_SCRIPT_CONVERSATION(1, 1);
							trigger6 = 1;
						}

						DRAW_CHECKPOINT( -605.383, 710.026, 5.17858, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -605.383, 710.026, 5.17858, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							SetSpeech();
							// сценка тут
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							SET_CAR_DENSITY_MULTIPLIER(0);// отключаем пути
							CLEAR_AREA(-625.475, 664.914, 5.17858, 85.0, 1);//очещаем зону загрузки

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -610.569, 709.178, 5.85356 ); // куда смотрит камера
							SET_CAM_POS			( camera, -600.314, 700.914, 9.42846 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_NJ", "CUB4_08", 0, 0);//Hola, amigos.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_NK", "CUB4_07", 0, 0);//Oy - the solvent is round the back, amigo.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_NL", "CUB4_09", 0, 0);//Bueno. Haitian Putas. Muerte.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_NM", "CUB4_10", 0, 0);//Vamos.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_NN", "CUB4_11", 0, 0);//Vamos indeed.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// воспроизводим RRR пути
							UNPAUSE_PLAYBACK_RECORDED_CAR(car1);
							UNPAUSE_PLAYBACK_RECORDED_CAR(car2);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_NO", "CUB4_14", 0, 0);//Follow my compadres.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							SetTime(2000);

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_CAR(car2, &cuban_ico);
							CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(cuban_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_CAR");//иконка на радаре называние в истории карты ""

							start = 1;
							break;
						}

						if (IS_CHAR_IN_CAR(GetPlayerPed(), car3))
						{
							if (start == 1)
							{
								REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_COORD(-605.383, 710.026, 5.17858, &cuban_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(cuban_ico, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "CUB4_27", 5000, 1);//~g~Go and meet up with Rico and the other Cubans.
								start = 0;
							}
						}
						else
						{
							if (start == 0)
							{
								REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CAR(car3, &cuban_ico);
								CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(cuban_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_CAR");//иконка на радаре называние в истории карты ""

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "IN_VEH", 5000, 1);//~COL_NET_12~Hey! Get back in the vehicle!
								start = 1;
							}
						}
						// провал миссии тут
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (rico_hp < 100))
						{
							EXPLODE_CHAR_HEAD(ped1);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB2_10", 5000, 1);//~r~You are supposed to be killing Haitians, not Cubans.
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)) || (IS_CHAR_DEAD(ped5)))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB2_10", 5000, 1);//~r~You are supposed to be killing Haitians, not Cubans.
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// доехать до до завода
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						GET_CHAR_HEALTH(ped1, &rico_hp);

						//отключаем трафик
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -546.884, 547.347, 2.128, -696.884, 747.347, 52.128, 0 )) && ( in_zon == 0))
						{
							in_zon = 1;
							SET_CAR_DENSITY_MULTIPLIER(0);// отключаем пути
						}
						else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -546.884, 547.347, 2.128, -696.884, 747.347, 52.128, 0 )) && ( in_zon == 1))
						{
							in_zon = 0;
							SET_CAR_DENSITY_MULTIPLIER(1);// включаем пути
						}

						if ((IS_CHAR_IN_AREA_3D( ped2, -673.838, 601.201, 4.988, -677.338, 605.201, 8.988, 0 )) && ( in_zavod == 0))
						{
							// пауза путей
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB4_28", 5000, 1);//~g~Join the other Cubans at the Haitian Drugs Factory.

							SetTime(1500);
							PAUSE_PLAYBACK_RECORDED_CAR(car1);
							PAUSE_PLAYBACK_RECORDED_CAR(car2);
							start = 1;
							in_zavod = 1;
						}

						if (in_zavod == 1)
						{
							DRAW_CHECKPOINT( -655.833, 603.265, 5.17858, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -655.833, 603.265, 5.17858, &PlayR);//проверка "игрок на координатах"
							if (( PlayR < 1.5) && (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "CUB4_03", 5000, 1);//~g~Stay in the car until safely parked inside the compound.

								TASK_GO_STRAIGHT_TO_COORD(ped6, -682.235, 605.133, 5.04067, 2, -2);// Пед идёт в двери
								SetTime(1500);

								REQUEST_ANIMS( "amb@taxi_hail_m" );
								while (!HAVE_ANIMS_LOADED( "amb@taxi_hail_m" )) WAIT(0);
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "hail_left", "amb@taxi_hail_m", 1.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе
								SetTime(2000);

								TASK_GO_STRAIGHT_TO_COORD(ped6, -682.235, 607.707, 5.92349, 2, -2);// Томми идёт в двери
								SetTime(1000);

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_NP", "CUB4_15", 0, 0);//Ok, in you go...
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								// открываем ворота
								while (true)
								{
									WAIT( 0 );
									vorotaY += 0.06;
									SET_OBJECT_COORDINATES(vorota, -681.281, vorotaY, 5.23681);
									if (vorotaY > 614.435)
									{
										break;
									}
								}

								SET_CAR_DENSITY_MULTIPLIER(1);// включаем пути

								// воспроизводим RRR пути
								UNPAUSE_PLAYBACK_RECORDED_CAR(car1);
								UNPAUSE_PLAYBACK_RECORDED_CAR(car2);
								SetTime(2000);

								REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_COORD(-739.801, 615.565, 5.05374, &cuban_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(cuban_ico, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "CUB4_32", 5000, 1);//~g~Park the car at the blip and get out.
								start = 1;
								break;
							}
						}

						if (IS_CHAR_IN_CAR(GetPlayerPed(), car3))
						{
							if (in_zavod == 1)
							{
								if (start == 1)
								{
									REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
									ADD_BLIP_FOR_COORD(-655.833, 603.265, 5.17858, &cuban_ico);//создаем иконку на радаре
									CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cuban_ico, 5);   //цвет иконка на радаре (0=белая)
									CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"

									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "CUB4_28", 5000, 1);//~g~Join the other Cubans at the Haitian Drugs Factory.
									start = 0;
								}
							}
							else
							{
								if (start == 1)
								{
									REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
									ADD_BLIP_FOR_CAR(car2, &cuban_ico);
									CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
									CHANGE_BLIP_COLOUR(cuban_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
									CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
									CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_CAR");//иконка на радаре называние в истории карты ""

									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "CUB4_14", 5000, 1);//Follow my compadres.
									start = 0;
								}
							}
						}
						else
						{
							if (start == 0)
							{
								REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_CAR(car3, &cuban_ico);
								CHANGE_BLIP_SPRITE(cuban_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(cuban_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(cuban_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(cuban_ico, "NE_CAR");//иконка на радаре называние в истории карты ""

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "IN_VEH", 5000, 1);//~COL_NET_12~Hey! Get back in the vehicle!
								start = 1;
							}
						}
						// провал миссии тут
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), -546.884, 547.347, -696.884, 747.347, 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB4_04", 5000, 1);//~r~You've alerted the base, there is no way we will get in now!
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (rico_hp < 100))
						{
							EXPLODE_CHAR_HEAD(ped1);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB2_10", 5000, 1);//~r~You are supposed to be killing Haitians, not Cubans.
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)) || (IS_CHAR_DEAD(ped5)))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB2_10", 5000, 1);//~r~You are supposed to be killing Haitians, not Cubans.
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// припорковаться на территории завода
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						GET_CHAR_HEALTH(ped1, &rico_hp);

						DRAW_CHECKPOINT( -739.801, 615.565, 5.05374, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -739.801, 615.565, 5.05374, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
							SET_OBJECT_COORDINATES(vorota, -681.281, 607.411, 5.23681);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_NQ", "CUB4_16", 0, 0);//I'm going to plant the bomb, cover me!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							STOP_PLAYBACK_RECORDED_CAR(car1);
							STOP_PLAYBACK_RECORDED_CAR(car2);
							REMOVE_CAR_RECORDING( 3058 ); // выгружаем пути транспорта
							REMOVE_CAR_RECORDING( 3059 ); // выгружаем пути транспорта
							rrr_on = 0;

							TASK_LEAVE_CAR(ped1, car3);
							TASK_LEAVE_CAR(ped2, car1);
							TASK_LEAVE_CAR(ped3, car2);
							TASK_LEAVE_CAR(ped4, car1);
							TASK_LEAVE_CAR(ped5, car2);

							UpdateWeaponOfPed(ped20, WEAPON_EPISODIC_13);
							SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_EPISODIC_13, TRUE);
							SET_CHAR_COORDINATES(ped20, -682.169, 599.709, 5.92349);// перемещаем игрока
							SET_CHAR_HEADING(ped20, 90.0);

							ADD_BLIP_FOR_COORD(-754.194, 636.405, 5.12495, &tnt1_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(tnt1_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(tnt1_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(tnt1_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt1_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"

							ADD_BLIP_FOR_COORD(-748.368, 614.555, 5.12495, &tnt2_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(tnt2_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(tnt2_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(tnt2_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt2_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"

							ADD_BLIP_FOR_COORD(-740.792, 603.311, 11.8548, &tnt3_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(tnt3_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(tnt3_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(tnt3_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(tnt3_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"
							SetTime(2000);

							//свой-чужой
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

							SET_SENSE_RANGE(ped6, 45.0);
							SET_SENSE_RANGE(ped7, 45.0);
							SET_SENSE_RANGE(ped8, 45.0);
							SET_SENSE_RANGE(ped9, 45.0);
							SET_SENSE_RANGE(ped10, 45.0);
							SET_SENSE_RANGE(ped11, 45.0);
							SET_SENSE_RANGE(ped12, 45.0);
							SET_SENSE_RANGE(ped13, 35.0);
							SET_SENSE_RANGE(ped14, 35.0);
							SET_SENSE_RANGE(ped15, 35.0);
							SET_SENSE_RANGE(ped16, 35.0);
							SET_SENSE_RANGE(ped17, 35.0);
							SET_SENSE_RANGE(ped18, 35.0);
							SET_SENSE_RANGE(ped19, 35.0);
							SET_SENSE_RANGE(ped20, 35.0);

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

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB4_29", 4000, 1);//~g~Walk into each of the markers to plant a bomb at that location.
							PRINT_STRING_IN_STRING("string", "CUB4_02", 4000, 1);//~g~The bombs will be set with a 70 second timer.
							PRINT_STRING_IN_STRING("string", "CUB4_30", 4000, 1);//~g~After all three bombs are planted, get clear of the factory before it blows.
							break;
						}
						// провал миссии тут
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (rico_hp < 100))
						{
							EXPLODE_CHAR_HEAD(ped1);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB2_10", 5000, 1);//~r~You are supposed to be killing Haitians, not Cubans.
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_DEAD(ped3)) || (IS_CHAR_DEAD(ped4)) || (IS_CHAR_DEAD(ped5)))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB2_10", 5000, 1);//~r~You are supposed to be killing Haitians, not Cubans.
							skip = 1;// переменная пропуска
							break;
						}
						else if ((!IS_CHAR_IN_CAR(GetPlayerPed(), car3)) || (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), -546.884, 547.347, -696.884, 747.347, 0)))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB4_04", 5000, 1);//~r~You've alerted the base, there is no way we will get in now!
							skip = 1;
							break;
						}
					}
				}
				// Расставить динамит
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						if (timer_on == 1)
						{
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
						}

						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную

						if (tnt1 == 0)
						{
							DRAW_CHECKPOINT( -754.194, 636.405, 5.12495, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -754.194, 636.405, 5.12495, &PlayR);//проверка "игрок на координатах"
							if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (tnt1 == 0))
							{
								tnt1 = 1;
								timer_on = 1;
								REMOVE_BLIP(tnt1_ico);//Удаляем иконку на радаре
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "f_insertcard", "amb@atm", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								SETTIMERB( 0 );
								p_event = 1;
							}
						}
						if (tnt2 == 0)
						{
							DRAW_CHECKPOINT( -748.368, 614.555, 5.12495, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -748.368, 614.555, 5.12495, &PlayR);//проверка "игрок на координатах"
							if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (tnt2 == 0))
							{
								tnt2 = 1;
								timer_on = 1;
								REMOVE_BLIP(tnt2_ico);//Удаляем иконку на радаре
								// аримация тут
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "f_insertcard", "amb@atm", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								SETTIMERB( 0 );
								p_event = 1;
							}
						}
						if (tnt3 == 0)
						{
							DRAW_CHECKPOINT( -740.792, 603.311, 11.8548, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -740.792, 603.311, 11.8548, &PlayR);//проверка "игрок на координатах"
							if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (tnt3 == 0))
							{
								tnt3 = 1;
								timer_on = 1;
								REMOVE_BLIP(tnt3_ico);//Удаляем иконку на радаре
								// аримация тут
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "f_insertcard", "amb@atm", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								SETTIMERB( 0 );
								p_event = 1;
							}
						}

						if ( p_event == 1 )
						{
							if (TIMERB() > 999)
							{
								PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
								if (tnt1 == 1)
								{
									SET_OBJECT_COORDINATES(tnt_1, -754.285, 637.031, 6.44356);
									tnt1 = 2;
								}
								if (tnt2 == 1)
								{
									SET_OBJECT_COORDINATES(tnt_2, -748.393, 615.169, 6.44915);
									tnt2 = 2;
								}
								if (tnt3 == 1)
								{
									SET_OBJECT_COORDINATES(tnt_3, -740.951, 603.945, 13.2457);
									tnt3 = 2;
								}
								p_event = 0;
							}
						}

						if ((tnt1 == 2) && (tnt2 == 2) && (tnt3 == 2))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_NQ_QQQ1", "CUB4_17", 0, 0);//RUN!!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB4_31", 5000, 1);//~g~Get clear of the factory!!

							// педы убегают с завада
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, -694.352, 567.472, 12.1556, 3, -2, 2.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, -694.352, 567.472, 12.1556, 3, -2, 2.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped3, -694.352, 567.472, 12.1556, 3, -2, 2.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped4, -694.352, 567.472, 12.1556, 3, -2, 2.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped5, -694.352, 567.472, 12.1556, 3, -2, 2.5);
							break;
						}
						// провал миссии тут
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((time_m == 0) && (time_s == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB4_06", 5000, 1);//~r~You did not get far enough away from the base and we had to abort the explosion!
							skip = 1;// переменная пропуска
							break;
						}
						
					}
				}
				// Покинуть территорию завода
				if (skip == 0)
				{
					while (TRUE)
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

						if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -678.299, 574.74, 1.532, -783.579, 660.315, 51.532, 0 ))
						{
							if (sound == 1)
							{
								STOP_STREAM();
								ENABLE_FRONTEND_RADIO();
								sound = 0;
							}

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замараживаем игрока
							SET_OBJECT_COORDINATES(tnt_1, -748.393, 615.169, -12.441);
							SET_OBJECT_COORDINATES(tnt_2, -744.393, 615.169, -12.441);

							skip = 2;
							break;
						}
						// провал миссии тут
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((time_m == 0) && (time_s == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CUB4_06", 5000, 1);//~r~You did not get far enough away from the base and we had to abort the explosion!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}

				// чистим скрипт тут
				if (rrr_on == 1)
				{
					STOP_PLAYBACK_RECORDED_CAR(car1);
					STOP_PLAYBACK_RECORDED_CAR(car2);
					REMOVE_CAR_RECORDING( 3058 ); // выгружаем пути транспорта
					REMOVE_CAR_RECORDING( 3059 ); // выгружаем пути транспорта
				}

				REMOVE_BLIP(tnt1_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(tnt2_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(tnt3_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( timer );
				REMOVE_TXD( textur );

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(dynamite_1);//выгружаем модель
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

				// выгружвем машину
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)

				// удаляем объекты
				DELETE_OBJECT(&tnt_1);
				DELETE_OBJECT(&tnt_2);
				DELETE_OBJECT(&tnt_3);
				DELETE_OBJECT(&vorota);

				// выгружаем бочки и ворота
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&tnt_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&tnt_2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&tnt_3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&vorota);

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
					G_CUBAN = 99;
					//------------ катсцена ----------------
					SETTIMERA(0); //сбрасываем таймер 
					int boom_skip = 0;
					START_CUTSCENE_NOW("destr2");
					while (!HAS_CUTSCENE_LOADED())
					{
						WAIT(0);
						if ( TIMERA() > 5000 )
						{
							boom_skip = 1;
							break;
						}
					}
					if (boom_skip == 0)
					{
						DO_SCREEN_FADE_IN(0);
						while (!HAS_CUTSCENE_FINISHED())
						{
							WAIT(0);
						}

						if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
						{
							DO_SCREEN_FADE_IN(0);
						}
					}
					else
					{
						DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					}

					G_CUBAN = 6;

					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_CUB_4" );//Trojan Voodoo
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(10000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +10000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 10000);
					autosave = 1;
				}
				G_ONMISSION = 0;

			}
		}
		else if ((G_ONMISSION == 0) && (G_CUBAN == 6))
		{
			break;
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(cuban_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}
	}
}
void main(void)
{
	//THIS_SCRIPT_SHOULD_BE_SAVED();
	if (G_CUBAN < 6)
	{
		umberto();
	}
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
