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
float PlayX, PlayY, PlayZ, PlayR, PedX, PedY, PedZ, PedR, PedX2, PedY2, PedZ2, PedR2, blip_on, skip, ped_res, stalking, stalkerR, in_car, del_car, girl_b1, girl_b2, no_kill, autosave;
float textur, Health, carH1, carH2, carH3, carHUD_x, carHUD_w, carHUD_y1, carHUD_y2, carHUD_y3, blips_on, point_1, point_2, point_3, point_4, point_5, point_6, all_point, hud_on, del_chek, set_chek, text;
float Ped5_c, Ped6_c, Ped7_c, snimok, set_model, HealG_1, HealG_2, HealG_3, glassON_1, glassON_2, glassON_3, in_hotel, in_aria;
float Blip_x, Blip_y, Blip_z, Blip_x2, Blip_y2, Blip_z2, play_cord, check_on, res_point, door1Y, door2Y, light_z;
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
void studio(void)
{
	blip_on = 0;
	autosave = 0;
	Blip pron_ico;
	load_mashin = 0;
	help = 0;
	uint rId9;
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
//============================== Recruitment Drive ======================================
		if ((G_ONMISSION == 0) && (G_PRON == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(365.19, 1463.24, 4.84835, &pron_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(pron_ico, BLIP_INTERNET);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(pron_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "LG_12");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 365.19, 1463.24, 4.84835, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 365.19, 1463.24, 4.84835, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("PORN_1", 15000, CUTSCENE_PORN);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(21.489, 966.28, 9.5, 172.7);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
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
				SET_CHAR_COORDINATES(GetPlayerPed(), 365.628, 1465.67, 5.2528);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -90.0);

				int dm, cdm;
				Car car1, car2, car3, car4;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7;
				Blip girl_1, girl_2;
				Cam camera;

				skip = 0;
				ped_res = 0;
				stalking = 0;
				in_car = 0;
				del_car = 0;
				girl_b1 = 0;
				girl_b2 = 0;
				no_kill = 1;

				uint CarM1 = MODEL_STRETCH;// Лимузин
				uint CarM2 = MODEL_SENTINEL;// Сентинейл
				
				uint PedM1 = MODEL_IG_SARAH;// Кенди
				uint PedM2 = MODEL_IG_ANNA;// Мерседес
				uint PedM3 = MODEL_M_Y_DOWNTOWN_02;// Водила лимузина
				uint PedM4 = MODEL_M_Y_PHARLEM_01;// Менеджер
				uint PedM5 = MODEL_M_Y_DRUG_01;// Охранник

				LOAD_CHAR_DECISION_MAKER(2, &dm);
				LOAD_COMBAT_DECISION_MAKER(3, &cdm);

				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(10);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(10);

				REQUEST_MODEL(PedM1);// Приспешник 1
				while (!HAS_MODEL_LOADED(PedM1)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Приспешник 2
				while (!HAS_MODEL_LOADED(PedM2)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// Охрана
				while (!HAS_MODEL_LOADED(PedM3)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM4);// // Бизнесмен
				while (!HAS_MODEL_LOADED(PedM4)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM5);// // Бизнесмен
				while (!HAS_MODEL_LOADED(PedM5)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало

				CREATE_CAR(CarM1, 299.551, -779.725, 5.44546, &car4, TRUE);// Лимузин
				CREATE_CAR(CarM2, 295.942, -779.725, 5.44546, &car2, TRUE);// Сентинейл
				CREATE_CAR(CarM2, 292.585, -779.725, 5.44546, &car3, TRUE);// Сентинейл 2

				CHANGE_CAR_COLOUR( car4, 110, 110 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car4, 132, 132 );//цвет отрожений машины
				LOCK_CAR_DOORS(car2, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car3, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car4, 3); //блокируем двери автомобиля для игрока

				CREATE_CHAR (26, PedM2, 289.762, -777.475, 5.05974, &ped2, TRUE);// Мерседес
				CREATE_CHAR_INSIDE_CAR(car4, 1, PedM3, &ped7);// 
				CREATE_CHAR_INSIDE_CAR(car2, 1, PedM4, &ped3);// Менеджер

				CREATE_CHAR_AS_PASSENGER(car4, 1, PedM1, 2, &ped1);// Кенди
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM5, 0, &ped4);// 
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM5, 1, &ped5);// 
				CREATE_CHAR_AS_PASSENGER(car2, 1, PedM5, 2, &ped6);// 

				SET_CHAR_RELATIONSHIP_GROUP(ped1, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 3);
				SET_CHAR_COMPONENT_VARIATION(ped2, 1, 1, 0);

				SET_CHAR_DECISION_MAKER(ped1, dm);
				SET_CHAR_DECISION_MAKER(ped2, dm);
				SET_CHAR_DECISION_MAKER(ped3, dm);
				SET_COMBAT_DECISION_MAKER(ped1, cdm);
				SET_COMBAT_DECISION_MAKER(ped2, cdm);
				SET_COMBAT_DECISION_MAKER(ped3, cdm);

				uint hour, minute, weather;
				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 0);//устанавливаем время

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "PORN_1", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("porn_1");
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

				// создаём блипы
				ADD_BLIP_FOR_COORD(-15.3837, 1859.44, 5.68604, &pron_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(pron_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(pron_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "NE_POINT");//иконка на радаре называние в истории карты ""

				SetTime(1000);
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
				ADD_LINE_TO_CONVERSATION(0, "R14_VT", "", 0, 0);//
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				PRINT_STRING_IN_STRING("string", "POR1_01", 5000, 1);//~g~Candy Suxxx would be perfect for a starring role!
				SetTime(3000);
				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "POR1_23", 5000, 1);//~g~Candy will be taking care of business ~h~Downtown~g~.

				// грузим анимации
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);


				// часть 1 встать на маркер
				while(true)
				{
					WAIT(0);
					DRAW_CHECKPOINT( -15.3837, 1859.44, 5.68604, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -15.3837, 1859.44, 5.68604, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
						CLEAR_AREA(-36.8277, 1870.99, 6.13243, 20.0, 1);//очещаем зону загрузки
						CLEAR_AREA(-78.072, 1870.6, 5.31231, 60.0, 1);//очещаем зону загрузки
						SET_CAR_DENSITY_MULTIPLIER(0);// выключаем пути
						SET_CHAR_INVINCIBLE(ped3, 1);

						// лимузыт едит тут
						SET_CAR_COORDINATES(car4, -36.8277, 1870.99, 6.13243);// перемещаем игрока
						SET_CAR_HEADING(car4, -85.0);
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped7, car4, -19.1025, 1872.55, 6.27189, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

						// ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, -19.085, 1871.301, 6.361 ); // куда смотрит камера
						SET_CAM_POS			( camera, -13.592, 1856.211, 7.85958 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR1_26", 5000, 1);//~g~Here's Candy, looks like she has been with Congressman Shrub again.
						SetTime(3000);
						SETTIMERB( 0 );

						while(true)
						{
							WAIT(0);
							if (IS_CAR_STOPPED(car4))
							{
								break;
							}
							else if (TIMERB() > 5000)
							{
								WARP_CHAR_FROM_CAR_TO_COORD(ped1, -17.9991, 1870.75, 5.64813);//телепартируем из транспорта
								break;
							}
						}

						// Кэнди выходит и идёт
						TASK_GO_STRAIGHT_TO_COORD(ped1, -16.0962, 1864.32, 5.64813, 2, -2);// пед идёт к ...
						SetTime(1000);

						// смена ракурса камеры
						POINT_CAM_AT_COORD	( camera, -16.9414, 1871.37, 6.361 ); // куда смотрит камера
						SET_CAM_POS			( camera, -14.7926, 1861.98, 8.05112 );//расположение камеры
						SetTime(1000);
						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), -16.0962, 1864.32, 5.64813, 2, -2);// пед идёт к ...

						// Лимузин кзежает
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped7, car4, 299.551, -779.725, 5.44546, 4, 60.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

						// Подъезжает менеджер
						CLEAR_AREA(-36.8277, 1870.99, 6.13243, 20.0, 1);//очещаем зону загрузки
						CLEAR_AREA(-78.072, 1870.6, 5.31231, 60.0, 1);//очещаем зону загрузки
						SET_CAR_COORDINATES(car2, -36.8277, 1870.99, 6.13243);// перемещаем игрока
						SET_CAR_HEADING(car2, -85.0);
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car2, -19.1025, 1872.55, 6.27189, 4, 40.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						SetTime(4000);

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R7_FA", "POR1_04", 0, 0);//Yo, Candy. I'm looking for movie talent - you interested?
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
						START_SCRIPT_CONVERSATION(1, 1);

						SET_CAR_COORDINATES(car4, 299.551, -779.725, 5.44546);// перемещаем игрока
						SET_CAR_HEADING(car4, 0.0);
						SetTime(3650);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R7_FB", "POR1_05", 0, 0);//Sure! But, you'd have to talk to my agent...
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
						START_SCRIPT_CONVERSATION(1, 1);

						// Менеджер выходит
						TASK_LEAVE_CAR(ped3, car2);
						SetTime(4500);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped3, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R7_FC", "POR1_06", 0, 0);//The HELL are you doin'?
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(1730);
						SetSpeech();

						TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), -15.1479, 1865.75, 5.64813, 2, -2);// пед идёт к ...
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R7_FD", "POR1_07", 0, 0);//You should have stayed at home today!
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(2380);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped3, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R7_FE", "POR1_7B", 0, 0);//Can you believe this asshole?
						START_SCRIPT_CONVERSATION(1, 1);
						SetTime(2000);
						SetSpeech();

						// Менеджер садится
						TASK_ENTER_CAR_AS_DRIVER(ped3, car2, -1);
						TASK_GO_STRAIGHT_TO_COORD(ped1, -15.4191, 1857.65, 5.97518, 2, -2);// пед идёт к ...

						// Выходит охрна 
						TASK_LEAVE_CAR(ped4, car2);
						TASK_LEAVE_CAR(ped5, car2);
						TASK_LEAVE_CAR(ped6, car2);
						SetTime(1000);

						// Охрана нападает на Томми
						UpdateWeaponOfPed(ped4, WEAPON_BASEBALLBAT);
						UpdateWeaponOfPed(ped5, WEAPON_BASEBALLBAT);
						UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_12);
						SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_BASEBALLBAT, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_BASEBALLBAT, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_12, TRUE);
						SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
						SET_CHAR_RELATIONSHIP(ped4, 5, 0);
						SET_CHAR_RELATIONSHIP(ped5, 5, 0);
						SET_CHAR_RELATIONSHIP(ped6, 5, 0);
						SET_SENSE_RANGE(ped4, 80.0);
						SET_SENSE_RANGE(ped5, 80.0);
						SET_SENSE_RANGE(ped6, 80.0);
						SET_CHAR_WILL_USE_COVER(ped4, 0);
						SET_CHAR_WILL_USE_COVER(ped5, 0);
						SET_CHAR_WILL_USE_COVER(ped6, 1);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);
						SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
						SET_CHAR_DECISION_MAKER(ped4, dm);
						SET_COMBAT_DECISION_MAKER(ped4, cdm);
						SET_CHAR_DECISION_MAKER(ped5, dm);
						SET_COMBAT_DECISION_MAKER(ped5, cdm);
						SET_CHAR_KEEP_TASK(ped4, 1);
						SET_CHAR_KEEP_TASK(ped5, 1);
						SET_CHAR_KEEP_TASK(ped6, 1);

						// менеджер уезжает
						TASK_CAR_DRIVE_WANDER(ped3, car2, 40.0, 2);// пед едит куда-то
						SetTime(2000);
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR1_02", 5000, 1);//~g~ Go and take out Candy's pimp, then return and pick up Candy.
						
						// создаём блипы
						ADD_BLIP_FOR_CHAR(ped3, &pron_ico);
						CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(pron_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(pron_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

						//убираем камеру
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
						SET_CAR_DENSITY_MULTIPLIER(1);// включаем пути
						SetTime(500);

						TASK_COMBAT(ped4, GetPlayerPed());
						TASK_COMBAT(ped5, GetPlayerPed());
						TASK_COMBAT(ped6, GetPlayerPed());
						
						SETTIMERB( 0 );
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
				}

				// часть 2 разобраться с менеджером
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if ((TIMERB() > 3000) && (no_kill == 1))
						{
							SET_CHAR_INVINCIBLE(ped3, 0);
							//EXPLODE_CHAR_HEAD(ped3);
							no_kill = 0;
						}

						// респавн охраны тут
						if (IS_CHAR_SITTING_IN_ANY_CAR(ped3))
						{
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							GET_CHAR_COORDINATES(ped3,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &PlayR);//проверка "игрок на координатах"
							if ( PlayR < 18.5)
							{
								if (TIMERB() > 9000)
								{
									if (ped_res == 0)
									{
										TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car2, PedX, PedY, PedZ, 4, 2.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
										
										// респавн охраны тут
										if (IS_CHAR_SITTING_IN_ANY_CAR(ped4)) 
										{
											WARP_CHAR_FROM_CAR_TO_COORD(ped4, 58.38, -122.03, 2.5);//телепартируем из катера
										}
										if (IS_CHAR_SITTING_IN_ANY_CAR(ped5)) 
										{
											WARP_CHAR_FROM_CAR_TO_COORD(ped5, 55.38, -122.03, 2.5);//телепартируем из катера
										}
										if (IS_CHAR_SITTING_IN_ANY_CAR(ped6)) 
										{
											WARP_CHAR_FROM_CAR_TO_COORD(ped6, 52.38, -122.03, 2.5);//телепартируем из катера
										}

										MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
										MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
										MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет
										CREATE_CHAR_AS_PASSENGER(car2, 1, PedM5, 0, &ped4);// 
										CREATE_CHAR_AS_PASSENGER(car2, 1, PedM5, 1, &ped5);// 
										CREATE_CHAR_AS_PASSENGER(car2, 1, PedM5, 2, &ped6);// 

										ped_res = 1;
									}

									if ((!IS_CAR_STOPPED(car2)) && (ped_res == 1))
									{
										TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car2, PedX, PedY, PedZ, 4, 2.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
									}


									if ((IS_CAR_STOPPED(car2)) && (ped_res == 1))
									{
										TASK_LEAVE_CAR(ped4, car2);
										TASK_LEAVE_CAR(ped5, car2);
										TASK_LEAVE_CAR(ped6, car2);

										// Охрана нападает на Томми
										UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_12);
										UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_12);
										UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_12);
										SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_12, TRUE);
										SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_12, TRUE);
										SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_12, TRUE);
										SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
										SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
										SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
										SET_CHAR_RELATIONSHIP(ped4, 5, 0);
										SET_CHAR_RELATIONSHIP(ped5, 5, 0);
										SET_CHAR_RELATIONSHIP(ped6, 5, 0);
										SET_SENSE_RANGE(ped4, 80.0);
										SET_SENSE_RANGE(ped5, 80.0);
										SET_SENSE_RANGE(ped6, 80.0);
										SET_CHAR_WILL_USE_COVER(ped4, 0);
										SET_CHAR_WILL_USE_COVER(ped5, 0);
										SET_CHAR_WILL_USE_COVER(ped6, 1);
										SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);
										SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);
										SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
										SET_CHAR_KEEP_TASK(ped4, 1);
										SET_CHAR_KEEP_TASK(ped5, 1);
										SET_CHAR_KEEP_TASK(ped6, 1);
										TASK_COMBAT(ped4, GetPlayerPed());
										TASK_COMBAT(ped5, GetPlayerPed());
										TASK_COMBAT(ped6, GetPlayerPed());
										TASK_CAR_DRIVE_WANDER(ped3, car2, 40.0, 2);// пед едит куда-то
										SETTIMERB( 0 );
										ped_res = 0;
									}
								}
							}
						}

						if ((IS_CHAR_DEAD(ped3)) || (IS_CHAR_FATALLY_INJURED(ped3)))//если пед мёртв или фатально ранен.
						{
							REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре

							ADD_BLIP_FOR_COORD(-15.3837, 1859.44, 5.68604, &pron_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(pron_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(pron_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

							SET_CHAR_COORDINATES(ped1, -15.4191, 1857.65, 5.97518);// перемещаем игрока
							SET_CHAR_HEADING(ped1, 0.0);

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR1_24", 5000, 1);//~g~Go back and collect Candy.
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR1_03", 5000, 1);//~r~Candy is dead!
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

				// часть 3 вернуться в Кэнди
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						DRAW_CHECKPOINT( -15.3837, 1859.44, 5.68604, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -15.3837, 1859.44, 5.68604, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							// ставим Мерседес
							SET_CHAR_COORDINATES(ped2, -469.997, 1331.96, 5.80247);// перемещаем игрока
							SET_CHAR_HEADING(ped2, 55.0);

							// ставим машину
							SET_CAR_COORDINATES(car3, -427.292, 1328.17, 5.65142);// перемещаем игрока
							SET_CAR_HEADING(car3, -25.0);

							REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_COORD(-468.068, 1329.49, 5.32595, &pron_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(pron_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(pron_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_FF", "POR1_27", 0, 0);//Come on, let's go.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							SetTime(1000);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR1_12", 5000, 1);//~g~Take Candy with you to meet up with Mercedes.
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR1_03", 5000, 1);//~r~Candy is dead!
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
				// часть 4 забрать Мерседес
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						
						// Кэнди сталкирит за Томми
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
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R7_TA", "POR1_25", 0, 0);//~g~You have left Candy behind, go and get her.
								START_SCRIPT_CONVERSATION(1, 1);
								PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "Tommy where are you going? Get back here!", 8000, 4);// Текст "Ты оставил Кэнди, вернись за ней."
							}
						}

						DRAW_CHECKPOINT( -468.068, 1329.49, 5.32595, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -468.068, 1329.49, 5.32595, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -469.633, 1331.48, 6.95868 ); // куда смотрит камера
							SET_CAM_POS			( camera, -462.331, 1332.92, 7.61611 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R7_FK", "POR1_08", 0, 0);//Hey Mercedes!
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 1000 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetTime(1000);

							TASK_GO_STRAIGHT_TO_COORD(ped2, -468.615, 1330.14, 5.32595, 2, -2);// пед идёт к ...
							SetTime(2000);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R7_FL", "POR1_09", 0, 0);//Hey Tommy! You wanna party?
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_FM", "POR1_10", 0, 0);//Not now sweets. You interested in doing some movies?
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_GA", "POR1_11", 0, 0);//Of course. As long as it's cheap and sleazy.
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_GB", "POR1_14", 0, 0);//Heh heh - you're hired!
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							SetTime(1000);

							REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_COORD(372.253, 1469.16, 4.82587, &pron_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(pron_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(pron_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR1_13", 5000, 1);//~g~Take the girls back to the Studio to meet Steve.

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							LOCK_CAR_DOORS(car3, 1); //блокируем двери автомобиля для игрока
							MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
							del_car = 1;
							stalking = 0;
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR1_03", 5000, 1);//~r~Candy is dead!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_FATALLY_INJURED(ped2)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "RBM1_8", 5000, 1);//~r~Mercedes is dead!
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

				// часть 5 отвези на студию
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
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
								TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, -1, 1);
								TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, -1, 0);
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1)) // Adding checks for both girls, originally only ped1 was checked, which could potentially prevent the script and stop the girls re-entering the player car
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
								in_car = 0; // Adding this, as in_car = 1 can be set if player goes out of range of the girls, and never gets set back to 0. The girls will only attempt to get into the car if in_car = 0.
								TASK_GO_STRAIGHT_TO_COORD(ped1, PedX, PedY, PedZ, 4, -2);
								TASK_GO_STRAIGHT_TO_COORD(ped2, PedX2, PedY2, PedZ2, 4, -2);
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NEPOR1_B", 5000, 1);//You left the girl behind! Go and get her!
							}
						}

						DRAW_CHECKPOINT( 372.253, 1469.16, 4.82587, 2.1, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(ped2,  &PedX2, &PedY2, &PedZ2);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 372.253, 1469.16, 4.82587, &PedR);//проверка "игрок на координатах"
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX2, PedY2, PedZ2, 372.253, 1469.16, 4.82587, &PedR2);//проверка "игрок на координатах"
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 372.253, 1469.16, 4.82587, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 2.1 ) && ( PedR < 2.5 ) && ( PedR2 < 2.5 ))
						{
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 366.924, 1479.72, 7.47809 ); // куда смотрит камера
							SET_CAM_POS			( camera, 373.337, 1454.92, 5.24965 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R7_GC", "POR1_15", 0, 0);//Tommy, you coming in for a warm-up?
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_GD", "POR1_16", 0, 0);//Maybe later, babe...
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, 352.194, 1465.011, 2.34472 ); // куда смотрит камера
							SET_CAM_POS			( camera, 372.899, 1466.501, 9.29127 );//расположение камеры

							// педы уходят
							if (IS_CHAR_SITTING_IN_ANY_CAR(ped1))
							{
								WARP_CHAR_FROM_CAR_TO_COORD(ped1, 366.888, 1465.98, 4.82587);//телепартируем из катера
							}
							else
							{
								SET_CHAR_COORDINATES(ped1, 366.888, 1465.98, 4.82587);// перемещаем игрока
							}
							if (IS_CHAR_SITTING_IN_ANY_CAR(ped2))
							{
								WARP_CHAR_FROM_CAR_TO_COORD(ped2, 366.933, 1464.49, 4.82587);//телепартируем из катера
							}
							else
							{
								SET_CHAR_COORDINATES(ped2, 366.933, 1464.49, 4.82587);// перемещаем игрока
							}

							TASK_GO_STRAIGHT_TO_COORD(ped1, 352.317, 1463.77, 4.82587, 2, -2);// пед идёт к ...
							TASK_GO_STRAIGHT_TO_COORD(ped2, 352.317, 1463.77, 4.82587, 2, -2);// пед идёт к ...
							SetTime(6100);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_GE", "POR1_17", 0, 0);//Whoa, cool shark!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							SET_CHAR_COORDINATES(ped1, 286.008, -779.725, 5.44546);// перемещаем игрока
							SET_CHAR_COORDINATES(ped2, 282.008, -779.725, 5.44546);// перемещаем игрока

							skip = 2;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR1_03", 5000, 1);//~r~Candy is dead!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_FATALLY_INJURED(ped2)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "RBM1_8", 5000, 1);//~r~Mercedes is dead!
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

				// чистим скрипт тут
				WAIT(100);
				REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре

				SET_CHAR_COORDINATES(ped1, -469.997, 1331.96, 5.80247);// перемещаем игрока
				SET_CHAR_COORDINATES(ped2, -469.997, 1331.96, 5.80247);// перемещаем игрока

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины

				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//выгружаем модель педа

				if (car1 != 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				}
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				if (del_car == 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				}
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)

				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_PORN_1" );//Recruitment Drive
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(1000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +1000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 1000);
					G_PRON = 2;
					autosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;

			}
		}

//============================== Dildo Dodo ======================================
		else if ((G_ONMISSION == 0) && (G_PRON == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(365.19, 1463.24, 4.84835, &pron_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(pron_ico, BLIP_INTERNET);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(pron_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "LG_12");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 365.19, 1463.24, 4.84835, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 365.19, 1463.24, 4.84835, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("PORN_2", 15000, CUTSCENE_PORN);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(21.489, 966.28, 9.5, 172.7);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
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
				
				SET_CHAR_COORDINATES(GetPlayerPed(), 365.628, 1465.67, 5.2528);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -90.0);

				Car car1;
				Blip chek_1, chek_2, chek_3, chek_4, chek_5, chek_6, chek_f;
				Cam camera;
				Texture fon, timer;
				Object soplo, extra9;

				skip = 0;
				carHUD_x = 0.922156;
				carHUD_w = 0.0739583;
				Health = 500;
				in_car = 0;
				hud_on = 0;
				blips_on = 0;
				del_chek = 0;
				set_chek = 0;
				text = 0;

				point_1 = 1;
				point_2 = 1;
				point_3 = 1;
				point_4 = 1;
				point_5 = 1;
				point_6 = 1;
				all_point = 0;

				uint checkpoint1, checkpoint2, checkpoint3, checkpoint4, checkpoint5, checkpoint6, checkpointF;

				uint CarM1 = MODEL_SPARROW;// модель вертолёта (имя в ...\inc\consts.h)
				uint soploM = vert_saplo;
				uint extraM = vert_box;

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(10);

				REQUEST_MODEL(soploM);
				while (!HAS_MODEL_LOADED(soploM)) WAIT(0);
				REQUEST_MODEL(extraM);
				while (!HAS_MODEL_LOADED(extraM)) WAIT(0);

				CREATE_OBJECT_NO_OFFSET(soploM, 0.1, 0.1, -90.1, &soplo, TRUE);
				CREATE_OBJECT_NO_OFFSET(extraM, 0.1, 0.1, -90.1, &extra9, TRUE);

				// координаты спавна вертолёта
				CREATE_CAR(CarM1, 358.3892, 1551.992, 5.538, &car1, TRUE);// Вертолёт
				SET_CAR_HEADING(car1, 170.0);

				ATTACH_OBJECT_TO_CAR(soplo, car1, 0, 0, 0, 0.5, 0, 0, 0);
				ATTACH_OBJECT_TO_CAR(extra9, car1, 0, 0, 0, 0.0, 0, 0, 0);

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				timer = GET_TEXTURE( textur, "timer_hud" );

				uint hour, minute, weather;
				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 0);//устанавливаем время

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "PORN_2", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("porn_2");
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

				// создаём блипы
				ADD_BLIP_FOR_CAR(car1, &pron_ico);
				CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(pron_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(pron_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				PRINT_STRING_IN_STRING("string", "NEPOR2_01", 5000, 1);//~g~There is a helicopter that was used as a prop in some old indie film round the back of the studios.
				SetTime(3000);
				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "POR2_05", 5000, 1);//~g~Use it to distribute the flyers around town.

				SETTIMERA( 0 );
				SETTIMERB( 0 );
				SETTIMERC( 0 );
				while(true)
				{
					WAIT(0);
					if (text == 1)
					{
						if (TIMERA() > 3000)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR2_02", 5000, 1);//~g~Pick one of the checkpoints to start dropping the flyers from.
							SETTIMERA( 0 );
							text = 2;
						}
					}
					else if (text == 2)
					{
						if (TIMERA() > 3000)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR2_03", 5000, 1);//~g~Drop the flyers all the way to the end checkpoint.
							SETTIMERA( 0 );
							text = 3;
						}
					}
					if ((IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (hud_on == 0))
					{
						REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
						in_car = 1;
						hud_on = 1;
						text = 1;
						SETTIMERA( 0 );
					}

					if (hud_on == 1)
					{
						// -------------------------- HUD --------------------------
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
						DISPLAY_TEXT(0.78815097, 0.77731852, "NEDILDO"); //FUEL:

						// тики тут ( Увеличить значение 650 для увеличения количества топлива )
						if (TIMERB() > 650)
						{
							Health -= 1;
							SETTIMERB( 0 );
						}
					}

					//--------------- пойнты -------------------
					if ((blips_on == 0) && (hud_on == 1))
					{
						// создаём блипы тут
						if (point_1 == 1)
						{
							ADD_BLIP_FOR_COORD(-167.877, 1192.81, 38.0127, &chek_1);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(chek_1, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(chek_1, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(chek_1, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(chek_1, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
							checkpoint1 = CREATE_CHECKPOINT( 8, -167.877, 1192.81, 38.0127, -167.877, 1192.81, 38.0127, 1.20000000 );
						}
						if (point_2 == 1)
						{
							ADD_BLIP_FOR_COORD(-31.0775, 1992.11, 34.0127, &chek_2);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(chek_2, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(chek_2, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(chek_2, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(chek_2, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
							checkpoint2 = CREATE_CHECKPOINT( 8, -31.0775, 1992.11, 34.0127, -31.0775, 1992.11, 34.0127, 1.20000000 );
						}
						if (point_3 == 1)
						{
							ADD_BLIP_FOR_COORD(-439.677, 1338.61, 29.0127, &chek_3);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(chek_3, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(chek_3, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(chek_3, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(chek_3, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
							checkpoint3 = CREATE_CHECKPOINT( 8, -439.677, 1338.61, 29.0127, -439.677, 1338.61, 29.0127, 1.20000000 );
						}
						if (point_4 == 1)
						{
							ADD_BLIP_FOR_COORD(-697.077, 350.109, 30.0127, &chek_4);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(chek_4, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(chek_4, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(chek_4, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(chek_4, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
							checkpoint4 = CREATE_CHECKPOINT( 8, -697.077, 350.109, 30.0127, -697.077, 350.109, 30.0127, 1.20000000 );
						}
						if (point_5 == 1)
						{
							ADD_BLIP_FOR_COORD(-269.877, -963.191, 39.0127, &chek_5);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(chek_5, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(chek_5, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(chek_5, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(chek_5, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
							checkpoint5 = CREATE_CHECKPOINT( 8, -269.877, -963.191, 39.0127, -269.877, -963.191, 39.0127, 1.20000000 );
						}
						if (point_6 == 1)
						{
							ADD_BLIP_FOR_COORD(-434.278, 189.609, 34.0127, &chek_6);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(chek_6, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(chek_6, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(chek_6, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(chek_6, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
							checkpoint6 = CREATE_CHECKPOINT( 8, -434.278, 189.609, 34.0127, -434.278, 189.609, 34.0127, 1.20000000 );
						}
						blips_on = 1;
					}
					// подбор начала броса листовок ( Для увеличения точности пролёта увеличите значения PlayR < 4.5)
					if (blips_on == 1)
					{																															  
						if (LOCATE_CAR_3D(car1, -167.877, 1192.81, 38.0127, 8.5, 8.5, 10.0, 0))
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							ATTACH_OBJECT_TO_CAR(soplo, car1, 0, 0, 0, 0.0, 0, 0, 0);
							PedX = 79.1416;
							PedY = 1621.51;
							PedZ = 40.8803;
							set_chek = 1;
							blips_on = 2;
							del_chek = 1;
						}
						if (LOCATE_CAR_3D(car1, -31.0775, 1992.11, 34.0127, 8.5, 8.5, 10.0, 0))
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							ATTACH_OBJECT_TO_CAR(soplo, car1, 0, 0, 0, 0.0, 0, 0, 0);
							PedX = -427.743;
							PedY = 1617.56;
							PedZ = 49.098;
							set_chek = 1;
							blips_on = 2;
							del_chek = 1;
						}
						if (LOCATE_CAR_3D(car1, -439.677, 1338.61, 29.0127, 8.5, 8.5, 10.0, 0))
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							ATTACH_OBJECT_TO_CAR(soplo, car1, 0, 0, 0, 0.0, 0, 0, 0);
							PedX = -637.143;
							PedY = 620.762;
							PedZ = 29.598;
							set_chek = 1;
							blips_on = 2;
							del_chek = 1;
						}
						if (LOCATE_CAR_3D(car1, -697.077, 350.109, 30.0127, 8.5, 8.5, 10.0, 0))
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							ATTACH_OBJECT_TO_CAR(soplo, car1, 0, 0, 0, 0.0, 0, 0, 0);
							PedX = -1000.14;
							PedY = -274.338;
							PedZ = 40.098;
							set_chek = 1;
							blips_on = 2;
							del_chek = 1;
						}
						if (LOCATE_CAR_3D(car1, -269.877, -963.191, 39.0127, 8.5, 8.5, 10.0, 0))
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							ATTACH_OBJECT_TO_CAR(soplo, car1, 0, 0, 0, 0.0, 0, 0, 0);
							PedX = -438.343;
							PedY = -41.238;
							PedZ = 49.598;
							set_chek = 1;
							blips_on = 2;
							del_chek = 1;
						}
						if (LOCATE_CAR_3D(car1, -434.278, 189.609, 34.0127, 8.5, 8.5, 10.0, 0))
					   
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							ATTACH_OBJECT_TO_CAR(soplo, car1, 0, 0, 0, 0.0, 0, 0, 0);
							PedX = -338.243;
							PedY = 837.362;
							PedZ = 44.698;
							set_chek = 1;
							blips_on = 2;
							del_chek = 1;
						}
					}
					// подбор конца броса листовок ( Для увеличения точности пролёта увеличите значения PlayR < 4.5)
					if (blips_on == 2)
					{
						if (LOCATE_CAR_3D(car1, 79.1416 ,1621.51, 40.8803, 8.5, 8.5, 10.0, 0))
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							ATTACH_OBJECT_TO_CAR(soplo, car1, 0, 0, 0, 0.5, 0, 0, 0);
							REMOVE_BLIP(chek_f);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpointF);
							blips_on = 0;
							point_1 = 0;
							all_point += 1;
						}
						if (LOCATE_CAR_3D(car1, -427.743, 1617.56, 49.098, 8.5, 8.5, 10.0, 0))
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							ATTACH_OBJECT_TO_CAR(soplo, car1, 0, 0, 0, 0.5, 0, 0, 0);
							REMOVE_BLIP(chek_f);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpointF);
							blips_on = 0;
							point_2 = 0;
							all_point += 1;
						}
						if (LOCATE_CAR_3D(car1, -637.143, 620.762, 29.598, 8.5, 8.5, 10.0, 0))
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							ATTACH_OBJECT_TO_CAR(soplo, car1, 0, 0, 0, 0.5, 0, 0, 0);
							REMOVE_BLIP(chek_f);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpointF);
							blips_on = 0;
							point_3 = 0;
							all_point += 1;
						}
						if (LOCATE_CAR_3D(car1, -1000.14, -274.338, 40.098, 8.5, 8.5, 10.0, 0))
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							ATTACH_OBJECT_TO_CAR(soplo, car1, 0, 0, 0, 0.5, 0, 0, 0);
							REMOVE_BLIP(chek_f);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpointF);
							blips_on = 0;
							point_4 = 0;
							all_point += 1;
						}
						if (LOCATE_CAR_3D(car1, -438.343, -41.238, 49.598, 8.5, 8.5, 10.0, 0))
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							ATTACH_OBJECT_TO_CAR(soplo, car1, 0, 0, 0, 0.5, 0, 0, 0);
							REMOVE_BLIP(chek_f);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpointF);
							blips_on = 0;
							point_5 = 0;
							all_point += 1;
						}
						if (LOCATE_CAR_3D(car1, -338.243, 837.362, 44.698, 8.5, 8.5, 10.0, 0))
						{
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							ATTACH_OBJECT_TO_CAR(soplo, car1, 0, 0, 0, 0.5, 0, 0, 0);
							REMOVE_BLIP(chek_f);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpointF);
							blips_on = 0;
							point_6 = 0;
							all_point += 1;
						}
					}

					// 2dfx
					if ((IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (blips_on == 2))
					{
						if (TIMERC() > 100)
						{
							//wind_debris_paper
							//col_bin_household_paper
							//col_dumpsters_paper
							//col_newspaper_bundle
							//dest_newspaper_bundle
							//imp_bullet_paper
							TRIGGER_PTFX_ON_VEH( "dest_newspaper_bundle", car1, 0.955, -0.913, -0.657, 1, 1, 90, 2.5);
							TRIGGER_PTFX_ON_VEH( "dest_newspaper_bundle", car1, -0.955, -0.913, -0.657, 1, 1, 90, 2.5);
							SETTIMERC( 0 );
						}
					}

					if ((!IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (in_car == 1))
					{
						if (blips_on == 1)
						{
							del_chek = 1;
						}
						else if (blips_on == 2)
						{
							REMOVE_BLIP(chek_f);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpointF);
							blips_on = 3;
						}

						// создаём блипы
						ADD_BLIP_FOR_CAR(car1, &pron_ico);
						CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(pron_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(pron_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NEPOR2_H", 5000, 1);//~g~Get back in the Helicopter!
						text = 99;
						in_car = 0;
					}
					else if ((IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (in_car == 0))
					{
						REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
						if (blips_on == 1)
						{
							blips_on = 0;
						}
						else if (blips_on == 3)
						{
							set_chek = 1;
							blips_on = 2;
						}
						in_car = 1;
					}

					if (set_chek == 1)
					{
						ADD_BLIP_FOR_COORD(PedX, PedY, PedZ, &chek_f);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(chek_f, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(chek_f, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(chek_f, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(chek_f, "MO_TARGET");//иконка на радаре называние в истории карты ""
						checkpointF = CREATE_CHECKPOINT( 8, PedX, PedY, PedZ, PedX, PedY, PedZ, 1.20000000 );
						set_chek = 0;
					}
					if (del_chek == 1)
					{
						if (point_1 == 1)
						{
							REMOVE_BLIP(chek_1);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpoint1);
						}
						if (point_2 == 1)
						{
							REMOVE_BLIP(chek_2);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpoint2);
						}
						if (point_3 == 1)
						{
							REMOVE_BLIP(chek_3);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpoint3);
						}
						if (point_4 == 1)
						{
							REMOVE_BLIP(chek_4);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpoint4);
						}
						if (point_5 == 1)
						{
							REMOVE_BLIP(chek_5);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpoint5);
						}
						if (point_6 == 1)
						{
							REMOVE_BLIP(chek_6);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpoint6);
						}
						del_chek = 0;
					}

					// провал\прохождение миссии тут
					if (all_point == 6)
					{
						skip = 2;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if (IS_CAR_DEAD(car1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NEPOR2_D", 5000, 1);//~r~The Helicopter has been destroyed!
						skip = 1;// переменная пропуска
						break;
					}
					else if (Health < 100)
					{
						SET_CAR_ENGINE_ON(car1, 0, 1);
						SET_ENGINE_HEALTH(car1, 0);
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR2_04", 5000, 1);//~r~LOW FUEL!!!
						skip = 1;// переменная пропуска
						break;
					}
				}

				// чистим скрипт тут
				WAIT(100);
				REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( timer );
				REMOVE_TXD( textur );

				if (blips_on == 1)
				{
					if (point_1 == 1)
					{
						REMOVE_BLIP(chek_1);//Удаляем иконку на радаре
						DELETE_CHECKPOINT(checkpoint1);
					}
					if (point_2 == 1)
					{
						REMOVE_BLIP(chek_2);//Удаляем иконку на радаре
						DELETE_CHECKPOINT(checkpoint2);
					}
					if (point_3 == 1)
					{
						REMOVE_BLIP(chek_3);//Удаляем иконку на радаре
						DELETE_CHECKPOINT(checkpoint3);
					}
					if (point_4 == 1)
					{
						REMOVE_BLIP(chek_4);//Удаляем иконку на радаре
						DELETE_CHECKPOINT(checkpoint4);
					}
					if (point_5 == 1)
					{
						REMOVE_BLIP(chek_5);//Удаляем иконку на радаре
						DELETE_CHECKPOINT(checkpoint5);
					}
					if (point_6 == 1)
					{
						REMOVE_BLIP(chek_6);//Удаляем иконку на радаре
						DELETE_CHECKPOINT(checkpoint6);
					}
				}
				else if (blips_on == 2)
				{
					if (all_point <= 5)
					{
						REMOVE_BLIP(chek_f);//Удаляем иконку на радаре
						DELETE_CHECKPOINT(checkpointF);
					}
				}

				DETACH_OBJECT(soplo, 1);
				DETACH_OBJECT(extra9, 1);
				DELETE_OBJECT(&soplo);
				DELETE_OBJECT(&extra9);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&soplo);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&extra9);

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(soploM);
				MARK_MODEL_AS_NO_LONGER_NEEDED(extraM);

				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_PORN_2" );//Dildo Dodo
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(2000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +2000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 2000);
					G_PRON = 3;
					autosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}
//============================== Martha's Mug Shot ======================================
		else if ((G_ONMISSION == 0) && (G_PRON == 3))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(365.19, 1463.24, 4.84835, &pron_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(pron_ico, BLIP_INTERNET);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(pron_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "LG_12");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 365.19, 1463.24, 4.84835, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 365.19, 1463.24, 4.84835, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("PORN_3", 15000, CUTSCENE_PORN);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(21.489, 966.28, 9.5, 172.7);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
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
				SET_CHAR_COORDINATES(GetPlayerPed(), 365.628, 1465.67, 5.2528);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -90.0);

				UpdateWeaponOfPed(GetPlayerPed(), WEAPON_CAMERA);
				SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_CAMERA, TRUE);
				SET_CHAR_AMMO(GetPlayerPed(), 45, 10);

				int dm, cdm;
				Car car1, car2, car3, car4, car5;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8;
				Object shot_1, shot_2, shot_3;
				Weapon pWeapon, MaxAmmo;
				uint Weap1, Ammo1_1, Ammo1_2;
				Texture fon, photos;
				Blip vert_ico;
				Cam camera;

				skip = 0;
				ped_res = 0;
				in_car = 0;
				snimok = 0;
				set_model = 0;
				Ped5_c = 0;
				Ped6_c = 0;
				Ped7_c = 0;
				glassON_1 = 1;
				glassON_2 = 1;
				glassON_3 = 1;
				in_hotel = 0;
				in_aria = 1;
				text = 0;

				uint CarM1 = MODEL_STRETCH;// Лимузин
				uint CarM2 = MODEL_SPARROW;// Верталёт
				uint CarM3 = MODEL_RANCHER;// Ренчер
				uint WinM1 = vc_photo;

				uint PedM1 = MODEL_IG_SARAH;// Кенди
				uint PedM2 = MODEL_IG_CHARLIEUC;// Конгресмен
				uint PedM3 = MODEL_M_Y_DOWNTOWN_02;// Водила лимузина
				uint PedM4 = MODEL_M_M_SECURITYMAN;// Охранник
				uint PedM5 = MODEL_M_M_FBI;// FBI

				LOAD_CHAR_DECISION_MAKER(2, &dm);
				LOAD_COMBAT_DECISION_MAKER(3, &cdm);

				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(10);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(10);
				REQUEST_MODEL(CarM3);
				while (!HAS_MODEL_LOADED(CarM3)) WAIT(10);

				REQUEST_MODEL(PedM1);// Приспешник 1
				while (!HAS_MODEL_LOADED(PedM1)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Приспешник 2
				while (!HAS_MODEL_LOADED(PedM2)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// Охрана
				while (!HAS_MODEL_LOADED(PedM3)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM4);// // Бизнесмен
				while (!HAS_MODEL_LOADED(PedM4)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM5);// // Бизнесмен
				while (!HAS_MODEL_LOADED(PedM5)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(WinM1);
				while (!HAS_MODEL_LOADED(WinM1)) WAIT(100);

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				photos = GET_TEXTURE( textur, "photo_hud" );

				CREATE_OBJECT_NO_OFFSET(WinM1, 1.818, 1.925, -25.8765, &shot_1, TRUE); // магазин 5 (одежда)
				CREATE_OBJECT_NO_OFFSET(WinM1, 1.217, 2.925, -25.8765, &shot_2, TRUE); // магазин 5 (одежда)
				CREATE_OBJECT_NO_OFFSET(WinM1, 1.615, 3.925, -25.8765, &shot_3, TRUE); // магазин 5 (одежда)

				CREATE_CAR(CarM1, 451.311, 1495.811, 5.3735, &car1, TRUE);// Лимузин
				CREATE_CAR(CarM2, 358.389, 1551.992, 5.5381, &car2, TRUE);// Вертолёт
				CREATE_CAR(CarM3, 299.551, -779.725, 5.4454, &car3, TRUE);// Ренчер
				CREATE_CAR(CarM3, 295.942, -779.725, 5.4454, &car4, TRUE);// Ренчер
				CREATE_CAR(CarM3, 292.585, -779.725, 5.4454, &car5, TRUE);// Ренчер
				SET_CAR_HEADING(car1, -10.0);
				SET_CAR_HEADING(car2, 170.0);

				CHANGE_CAR_COLOUR( car1, 110, 110 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car1, 132, 132 );//цвет отрожений машины
				LOCK_CAR_DOORS(car1, 3); //блокируем двери автомобиля для игрока

				CREATE_CHAR (26, PedM1, 396.052, 1485.11, 5.05974, &ped1, TRUE);// Кенди
				CREATE_CHAR (26, PedM2, 902.386, 560.993, 24.0311, &ped2, TRUE);// Конгресмен
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM3, &ped3);// Водила лимузина
				CREATE_CHAR (26, PedM4, 908.381, 560.792, 6.2609, &ped4, TRUE);// Охранник

				//FBI
				CREATE_CHAR (26, PedM5, 904.359,550.657,27.3021, &ped5, TRUE);// FBI 1
				CREATE_CHAR (26, PedM5, 903.471,575.913,27.4257, &ped6, TRUE);// FBI 2
				CREATE_CHAR (26, PedM5, 889.295,569.233,29.1751, &ped7, TRUE);// FBI 3
				CREATE_CHAR (26, PedM5, 910.532,563.393,25.1613, &ped8, TRUE);// FBI 4

				SET_CHAR_HEADING(ped1, -50.0);
				SET_CHAR_HEADING(ped2, 60.0);
				SET_CHAR_HEADING(ped4, -35.0);// Охранник
				SET_CHAR_HEADING(ped5, 90.0);//  FBI 1
				SET_CHAR_HEADING(ped6, 90.0);//  FBI 2
				SET_CHAR_HEADING(ped7, 180.0);// FBI 3
				SET_CHAR_HEADING(ped8, -90.0);// FBI 4

				SET_CHAR_RELATIONSHIP_GROUP(ped1, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped4, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped5, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped6, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped7, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped8, 3);

				SET_CHAR_DECISION_MAKER(ped1, dm);
				SET_CHAR_DECISION_MAKER(ped2, dm);
				SET_CHAR_DECISION_MAKER(ped3, dm);
				SET_CHAR_DECISION_MAKER(ped4, dm);
				SET_CHAR_DECISION_MAKER(ped5, dm);
				SET_CHAR_DECISION_MAKER(ped6, dm);
				SET_CHAR_DECISION_MAKER(ped7, dm);
				SET_CHAR_DECISION_MAKER(ped8, dm);
				SET_COMBAT_DECISION_MAKER(ped1, cdm);
				SET_COMBAT_DECISION_MAKER(ped2, cdm);
				SET_COMBAT_DECISION_MAKER(ped3, cdm);
				SET_COMBAT_DECISION_MAKER(ped4, cdm);
				SET_COMBAT_DECISION_MAKER(ped5, cdm);
				SET_COMBAT_DECISION_MAKER(ped6, cdm);
				SET_COMBAT_DECISION_MAKER(ped7, cdm);
				SET_COMBAT_DECISION_MAKER(ped8, cdm);

				uint hour, minute, weather;
				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 0);//устанавливаем время

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "PORN_3", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("porn_3");
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

				// создаём блипы
				ADD_BLIP_FOR_CHAR(ped1, &pron_ico);
				CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(pron_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(pron_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				// создаём блипы
				ADD_BLIP_FOR_CAR(car2, &vert_ico);
				CHANGE_BLIP_SPRITE(vert_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(vert_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(vert_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(vert_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

				// грузим анимации
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, 891.317, 550.628, 27.3021, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, 891.519, 575.913, 27.4257, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, 889.295, 556.023, 29.1751, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, 419.734, 1500.38, 4.82587, 2, -2, 1.5);

				UpdateWeaponOfPed(ped4, WEAPON_PISTOL);
				UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_13);

				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_PISTOL, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_13, TRUE);

				PRINT_STRING_IN_STRING("string", "POR3_01", 5000, 1);//~g~Follow Candy's ~h~Stretch~g~.
				SetTime(5000);
				PRINT_STRING_IN_STRING("string", "POR3_20", 5000, 1);//~g~If you need transport, use the ~h~Sparrow~g~ round the back.

				// часть 1 проследить
				while(true)
				{
					WAIT(0);
					// патрули
					if (Ped5_c == 0)
					{
						GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 891.317, 550.628, 27.3021, &PedR);//проверка "игрок на координатах"
						if (PedR < 3.0)
						{
							Ped5_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, 905.611, 550.657, 27.3021, 2, -2, 3.5);
						}
					}
					else if (Ped5_c == 1)
					{
						GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 905.611, 550.657, 27.3021, &PedR);//проверка "игрок на координатах"
						if (PedR < 3.0)
						{
							Ped5_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, 891.317, 550.628, 27.3021, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped6_c == 0)
					{
						GET_CHAR_COORDINATES(ped6,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 891.519, 575.913, 27.4257, &PedR);//проверка "игрок на координатах"
						if (PedR < 3.0)
						{
							Ped6_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, 905.918, 575.913, 27.4257, 2, -2, 3.5);
						}
					}
					else if (Ped6_c == 1)
					{
						GET_CHAR_COORDINATES(ped6,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 905.918, 575.913, 27.4257, &PedR);//проверка "игрок на координатах"
						if (PedR < 3.0)
						{
							Ped6_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, 891.519, 575.913, 27.4257, 2, -2, 3.5);
						}
					}
					//------------------------
					if (Ped7_c == 0)
					{
						GET_CHAR_COORDINATES(ped7,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 889.295, 556.023, 29.1751, &PedR);//проверка "игрок на координатах"
						if (PedR < 3.0)
						{
							Ped7_c = 1;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, 889.295, 570.058, 29.1751, 2, -2, 3.5);
						}
					}
					else if (Ped7_c == 1)
					{
						GET_CHAR_COORDINATES(ped7,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 889.295, 570.058, 29.1751, &PedR);//проверка "игрок на координатах"
						if (PedR < 3.0)
						{
							Ped7_c = 0;
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, 889.295, 556.023, 29.1751, 2, -2, 3.5);
						}
					}
					//------------------------

					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_CHAR_COORDINATES(ped1,  &PedX2, &PedY2, &PedZ2);//вписываем координаты игрока в переменную
					if (in_car == 0)
					{
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX2, PedY2, PedZ2, 419.734, 1500.38, 4.82587, &PedR2);//проверка "игрок на координатах"
						if (PedR2 < 3.0)
						{
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, 449.016, 1494.79, 4.82587, 2, -2, 1.5);
							in_car = 1;
						}
					}
					if (in_car == 1)
					{
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX2, PedY2, PedZ2, 449.016, 1494.79, 4.82587, &PedR2);//проверка "игрок на координатах"
						if (PedR2 < 3.0)
						{
							TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, -1, 1);
							in_car = 2;
						}
					}
					else if (in_car == 2)
					{
						if (IS_CHAR_IN_CAR(ped1, car1))
						{
							in_car = 3;
						}
					}
					else if (in_car == 3)
					{
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car1, 920.071, 572.644, 5.44832, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						in_car = 4;
					}

					if ((ped_res == 0) && (IS_CHAR_IN_CAR(GetPlayerPed(), car2)))
					{
						REMOVE_BLIP(vert_ico);//Удаляем иконку на радаре
						ped_res = 1;
					}
					// получение плёнки
					GET_CURRENT_CHAR_WEAPON(GetPlayerPed(), &pWeapon);//!!!___2(вписываем в переменную "pWeapon" оружие в руках игрока) 
					GET_AMMO_IN_CHAR_WEAPON(GetPlayerPed(), pWeapon, &MaxAmmo);
					GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 6, &Weap1, &Ammo1_1, &Ammo1_2);

					// выполнение/провел миссии
					GET_DISTANCE_BETWEEN_COORDS_3D( PedX2, PedY2, PedZ2, 920.071, 572.644, 5.44832, &PedR2);//проверка "игрок на координатах"
					if (PedR2 < 15.0)
					{
						REMOVE_BLIP(vert_ico);//Удаляем иконку на радаре
						REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре

						// сценка тут
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
						WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car1, 2);
						SET_CAR_COORDINATES(car1, 918.811, 563.875, 5.44832);//
						SET_CAR_HEADING(car1, -175.0);
						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана

						// ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 917.467, 564.746, 5.44832); // куда смотрит камера
						SET_CAM_POS			( camera, 906.938, 560.237, 8.00289 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, 905.667, 563.265, 6.18015, 2, -2, 2.5);
						SetTime(3000);
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car1, 934.144, 546.451, 4.66242, 4, 10.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						SetTime(3000);

						// смена ракурса камеры
						POINT_CAM_AT_COORD	( camera, 892.565, 564.483, 25.5009 ); // куда смотрит камера
						SET_CAM_POS			( camera, 905.356, 558.901, 25.376 );//расположение камеры

						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car1, 277.673, -779.725, 5.44546, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						SET_CAR_COORDINATES(car1, 277.673, -779.725, 5.44546);//
						SET_CAR_HEADING(car1, 0.0);

						SET_CHAR_COORDINATES(ped1, 893.005, 564.576, 24.9766);// перемещаем игрока
						SET_CHAR_HEADING(ped1, -100.0);
						TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, 896.514, 564.576, 24.9766, 2, -2, 1.5);
						SetTime(2000);
						TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, 902.386, 560.993, 24.6975, 2, -2, 2.5);

						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R7_GF", "POR1_19", 0, 0);//Hey!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R7_GG", "POR3_04", 0, 0);//Uh, Candy, could you call me Martha?
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 4000 );//Воиспроизвидение анимации на педе
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R7_GH", "POR3_05", 0, 0);//Oh Alex - I mean Martha. Whatever you say...
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 4000 );//Воиспроизвидение анимации на педе
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();
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

						SET_CHAR_COORDINATES(ped1, 896.184, 561.554, 25.3169);// перемещаем игрока
						SET_CHAR_COORDINATES(ped2, 896.359, 562.617, 25.3169);// перемещаем игрока
						SET_CHAR_HEADING(ped1, 10.0);
						SET_CHAR_HEADING(ped2, 180.0);
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе

						//убираем камеру
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

						ADD_BLIP_FOR_COORD(896.359, 562.617, 25.3169, &pron_ico);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(pron_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(pron_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

						ADD_BLIP_FOR_COORD(991.054, 550.567, 46.884, &vert_ico);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(vert_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(vert_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(vert_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(vert_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR3_16", 5000, 1);//~g~You need three good blackmail photographs of Alex Shrub with Candy.
						SETTIMERA( 0 );
						text = 1;

						DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
						break;
					}

					GET_DISTANCE_BETWEEN_COORDS_3D( PedX2, PedY2, PedZ2, PlayX, PlayY, PlayZ, &PedR2);//проверка "игрок на координатах"
					if ((PedR2 > 250.0) && (in_car == 4))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR3_21", 5000, 1);//~g~You lost Candy's Stretch!
						skip = 1;// переменная пропуска
						break;
					}
					else if (IS_CAR_DEAD(car1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR3_15", 5000, 1);//~r~You trashed Candy's Stretch!
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR1_03", 5000, 1);//~r~Candy is dead!
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_FATALLY_INJURED(ped2)))//если пед мёртв или фатально ранен.
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR3_02", 5000, 1);//~r~You've killed the Congressman! There's no way you can blackmail him now.
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(ped3)) || (IS_CHAR_FATALLY_INJURED(ped3)))//если пед мёртв или фатально ранен.
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR3_15", 5000, 1);//~r~You trashed Candy's Stretch!
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), 931.359, 527.617, 861.359, 597.617, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped4, 931.359, 527.617, 861.359, 597.617, 0)))//проверка Игрок начал пальбу на старте
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR3_03", 5000, 1);//~r~You've alerted the Congressman's protection, they will get him out of there immediately.
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_SHOOTING_IN_AREA(ped5, 931.359, 527.617, 861.359, 597.617, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped6, 931.359, 527.617, 861.359, 597.617, 0)))//проверка Игрок начал пальбу на старте
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR3_03", 5000, 1);//~r~You've alerted the Congressman's protection, they will get him out of there immediately.
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_SHOOTING_IN_AREA(ped7, 931.359, 527.617, 861.359, 597.617, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped8, 931.359, 527.617, 861.359, 597.617, 0)))//проверка Игрок начал пальбу на старте
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR3_03", 5000, 1);//~r~You've alerted the Congressman's protection, they will get him out of there immediately.
						skip = 1;// переменная пропуска
						break;
					}
					else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 922.293, 537.391, 22.0, 872.293, 872.293, 42.0, 0 ))
					{
						SET_CHAR_RELATIONSHIP_GROUP(ped4, 3);
						SET_CHAR_RELATIONSHIP_GROUP(ped5, 3);
						SET_CHAR_RELATIONSHIP_GROUP(ped6, 3);
						SET_CHAR_RELATIONSHIP_GROUP(ped7, 3);
						SET_CHAR_RELATIONSHIP_GROUP(ped8, 3);

						SET_CHAR_RELATIONSHIP(ped4, 5, 0);
						SET_CHAR_RELATIONSHIP(ped5, 5, 0);
						SET_CHAR_RELATIONSHIP(ped6, 5, 0);
						SET_CHAR_RELATIONSHIP(ped7, 5, 0);
						SET_CHAR_RELATIONSHIP(ped8, 5, 0);

						TASK_COMBAT(ped4, GetPlayerPed());
						TASK_COMBAT(ped5, GetPlayerPed());
						TASK_COMBAT(ped6, GetPlayerPed());
						TASK_COMBAT(ped7, GetPlayerPed());
						TASK_COMBAT(ped8, GetPlayerPed());

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR3_03", 5000, 1);//~r~You've alerted the Congressman's protection, they will get him out of there immediately.
						skip = 1;// переменная пропуска
						break;
					}
					else if ((pWeapon == 45) && (MaxAmmo < 2) && (snimok < 2))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR3_19", 5000, 1);//~r~You ran out of film!
						skip = 1;// переменная пропуска
						break;
					}
					else if (Weap1 != 45)
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NEPOR3_L", 5000, 1);//~r~You lost camera
						skip = 1;// переменная пропуска
						break;
					}
				}
				// часть 2 сфотографировать
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						if (text == 1)
						{
							if (TIMERA() > 3000)
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "POR3_22", 5000, 1);//~g~The WK Chariot Hotel across from his balcony should provide an ideal photo-grabbing location.
								SETTIMERA( 0 );
								text = 2;
							}
						}
						else if (text == 2)
						{
							if (TIMERA() > 3000)
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "POR3_23", 5000, 1);//~g~There is a side door that will allow you access to the hotel.
								SETTIMERA( 0 );
								text = 3;
							}
						}

						// ХУД тут
						//1779/1920=0,9265625
						DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
						DRAW_SPRITE( photos, 0.8555625, 0.80925926, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.80729167, 0.80277778, "POR3_24"); //PHOTOS TAKEN:

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						DISPLAY_TEXT_WITH_NUMBER(0.9340625, 0.795, "CP_TIME_NOZERO", snimok);

						// патрули
						if (Ped5_c == 0)
						{
							GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 891.317, 550.628, 27.3021, &PedR);//проверка "игрок на координатах"
							if (PedR < 3.0)
							{
								Ped5_c = 1;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, 905.611, 550.657, 27.3021, 2, -2, 3.5);
							}
						}
						else if (Ped5_c == 1)
						{
							GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 905.611, 550.657, 27.3021, &PedR);//проверка "игрок на координатах"
							if (PedR < 3.0)
							{
								Ped5_c = 0;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, 891.317, 550.628, 27.3021, 2, -2, 3.5);
							}
						}
						//------------------------
						if (Ped6_c == 0)
						{
							GET_CHAR_COORDINATES(ped6,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 891.519, 575.913, 27.4257, &PedR);//проверка "игрок на координатах"
							if (PedR < 3.0)
							{
								Ped6_c = 1;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, 905.918, 575.913, 27.4257, 2, -2, 3.5);
							}
						}
						else if (Ped6_c == 1)
						{
							GET_CHAR_COORDINATES(ped6,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 905.918, 575.913, 27.4257, &PedR);//проверка "игрок на координатах"
							if (PedR < 3.0)
							{
								Ped6_c = 0;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, 891.519, 575.913, 27.4257, 2, -2, 3.5);
							}
						}
						//------------------------
						if (Ped7_c == 0)
						{
							GET_CHAR_COORDINATES(ped7,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 889.295, 556.023, 29.1751, &PedR);//проверка "игрок на координатах"
							if (PedR < 3.0)
							{
								Ped7_c = 1;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, 889.295, 570.058, 29.1751, 2, -2, 3.5);
							}
						}
						else if (Ped7_c == 1)
						{
							GET_CHAR_COORDINATES(ped7,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 889.295, 570.058, 29.1751, &PedR);//проверка "игрок на координатах"
							if (PedR < 3.0)
							{
								Ped7_c = 0;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, 889.295, 556.023, 29.1751, 2, -2, 3.5);
							}
						}
						//------------------------

						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 993.554, 548.067, 45.897, 988.554, 553.067, 50.897, 0 )) && (in_hotel == 0))
						{
							REMOVE_BLIP(vert_ico);//Удаляем иконку на радаре
							in_hotel = 1;
						}

						// получаем снимки
						GET_OBJECT_HEALTH(shot_1, &HealG_1);
						GET_OBJECT_HEALTH(shot_2, &HealG_2);
						GET_OBJECT_HEALTH(shot_3, &HealG_3);
						
						// получение плёнки
						GET_CURRENT_CHAR_WEAPON(GetPlayerPed(), &pWeapon);//!!!___2(вписываем в переменную "pWeapon" оружие в руках игрока) 
						GET_AMMO_IN_CHAR_WEAPON(GetPlayerPed(), pWeapon, &MaxAmmo);
						GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 6, &Weap1, &Ammo1_1, &Ammo1_2);

						if ((HealG_1 < 999) && (glassON_1 == 1))
						{
							DRAW_SPRITE( 0, 0.5, 0.5, 1.0, 1.0, 0.0, 255, 255, 255, 255 );
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							glassON_1 = 0;
							snimok += 1;
						}
						if ((HealG_2 < 999) && (glassON_2 == 1))
						{
							DRAW_SPRITE( 0, 0.5, 0.5, 1.0, 1.0, 0.0, 255, 255, 255, 255 );
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							glassON_2 = 0;
							snimok += 1;
						}
						if ((HealG_3 < 999) && (glassON_3 == 1))
						{
							DRAW_SPRITE( 0, 0.5, 0.5, 1.0, 1.0, 0.0, 255, 255, 255, 255 );
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
							glassON_3 = 0;
							snimok += 1;
						}

						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1067.5, 465.0, 1.0, 972.5, 645.0, 61.0, 0 ))
						{
							if (pWeapon == 45)
							{
								if (set_model == 0)
								{
									SET_MAX_WANTED_LEVEL(0);
									// ставим модели
									if (glassON_1 == 1)
									{
										SET_OBJECT_COORDINATES(shot_1, 901.771, 563.239, 27.0096);
									}
									if (glassON_2 == 1)
									{
										SET_OBJECT_COORDINATES(shot_2, 901.838, 563.667, 26.8563);
									}
									if (glassON_3 == 1)
									{
										SET_OBJECT_COORDINATES(shot_3, 901.698, 563.365, 26.9478);
									}
									set_model = 1;
								}
							}
							else
							{
								if (set_model == 1)
								{
									SET_MAX_WANTED_LEVEL(6);
									// убираем модели
									SET_OBJECT_COORDINATES(shot_1, 1.818, 1.925, -25.8765);
									SET_OBJECT_COORDINATES(shot_2, 1.818, 2.925, -25.8765);
									SET_OBJECT_COORDINATES(shot_3, 1.818, 3.925, -25.8765);
									set_model = 0;
								}
							}
						}
						else
						{
							if (set_model == 1)
							{
								SET_MAX_WANTED_LEVEL(6);
								// убираем модели
								SET_OBJECT_COORDINATES(shot_1, 1.818, 1.925, -25.8765);
								SET_OBJECT_COORDINATES(shot_2, 1.818, 2.925, -25.8765);
								SET_OBJECT_COORDINATES(shot_3, 1.818, 3.925, -25.8765);
								set_model = 0;
							}
						}

						// прохождение
						if (snimok == 3)
						{
							// создаём блип на киностудии
							REMOVE_BLIP(vert_ico);//Удаляем иконку на радаре
							REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре

							ADD_BLIP_FOR_COORD(368.342, 1467.11, 4.82587, &pron_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(pron_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(pron_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

							// розыск тут
							SET_MAX_WANTED_LEVEL(5);
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 5);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
							SET_CHAR_AMMO(GetPlayerPed(), Weap1, 0);

							// аудио тут
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_GI", "POR3_06", 0, 0);//Martha, someone's watching.. how kinky.
							START_SCRIPT_CONVERSATION(1, 1);

							SETTIMERA( 0 );
							text = 4;
							break;
						}

						// провал
						if ((IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), 1067.5, 465.0, 972.5, 645.0, 0)) && (pWeapon != 45))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR3_03", 5000, 1);//~r~You've alerted the Congressman's protection, they will get him out of there immediately.
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR1_03", 5000, 1);//~r~Candy is dead!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_FATALLY_INJURED(ped2)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR3_02", 5000, 1);//~r~You've killed the Congressman! There's no way you can blackmail him now.
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 922.293, 537.391, 22.0, 872.293, 872.293, 42.0, 0 ))
						{
							SET_CHAR_RELATIONSHIP_GROUP(ped4, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped5, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped6, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped8, 3);

							SET_CHAR_RELATIONSHIP(ped4, 5, 0);
							SET_CHAR_RELATIONSHIP(ped5, 5, 0);
							SET_CHAR_RELATIONSHIP(ped6, 5, 0);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);
							SET_CHAR_RELATIONSHIP(ped8, 5, 0);

							TASK_COMBAT(ped4, GetPlayerPed());
							TASK_COMBAT(ped5, GetPlayerPed());
							TASK_COMBAT(ped6, GetPlayerPed());
							TASK_COMBAT(ped7, GetPlayerPed());
							TASK_COMBAT(ped8, GetPlayerPed());

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR3_03", 5000, 1);//~r~You've alerted the Congressman's protection, they will get him out of there immediately.
							skip = 1;// переменная пропуска
							break;
						}
						else if ((pWeapon == 45) && (MaxAmmo < 2) && (snimok < 2))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR3_19", 5000, 1);//~r~You ran out of film!
							skip = 1;// переменная пропуска
							break;
						}
						else if (Weap1 != 45)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NEPOR3_L", 5000, 1);//~r~You lost camera
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// часть 3 скрыться
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);

						if (text == 4)
						{
							if (TIMERA() > 4440)
							{
								if (!IS_SCRIPTED_CONVERSATION_ONGOING())
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R7_GJ", "POR3_07", 0, 0);// You! Give me that camera!
									START_SCRIPT_CONVERSATION(1, 1);
									SETTIMERA( 0 );
									text = 5;
								}
							}
						}
						else if (text == 5)
						{
							if (TIMERA() > 2000)
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "POR3_17", 5000, 1);//~g~Get back to the Porn Studios with the film.
								SETTIMERA( 0 );
								text = 6;
							}
						}

						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1003.18, 559.277, 21.069, 998.18, 564.277, 30.97, 0 )) && (in_hotel == 1))
						{
							// прячим педов
							SET_CHAR_COORDINATES(ped1, 289.762, -777.475, 5.05974);// перемещаем игрока
							SET_CHAR_COORDINATES(ped2, 288.738, -777.447, 5.05974);// перемещаем игрока

							// охрана на лестнице
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//выгружаем модель педа(в последствии пед изчезнет

							CREATE_CHAR (26, PedM4, 1002.86, 582.532, 8.45938, &ped4, TRUE);// Охранник
							CREATE_CHAR (26, PedM5, 1005.94, 559.654, 6.7417, &ped5, TRUE);// FBI 1
							CREATE_CHAR (26, PedM5, 1005.63, 557.219, 6.7417, &ped6, TRUE);// FBI 2
							CREATE_CHAR (26, PedM5, 995.571, 557.564, 11.9089, &ped7, TRUE);// FBI 3
							CREATE_CHAR (26, PedM5, 994.623, 559.828, 11.9089, &ped8, TRUE);// FBI 4

							SET_CHAR_HEADING(ped4, -170.0);
							SET_CHAR_HEADING(ped5, 115.0);
							SET_CHAR_HEADING(ped6, 80.0);
							SET_CHAR_HEADING(ped7, -35.0);
							SET_CHAR_HEADING(ped8, -70.0);

							UpdateWeaponOfPed(ped4, WEAPON_PISTOL);
							UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_13);

							SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_PISTOL, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_13, TRUE);

							SET_CHAR_RELATIONSHIP_GROUP(ped4, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped5, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped6, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped8, 3);

							SET_CHAR_RELATIONSHIP(ped4, 5, 0);
							SET_CHAR_RELATIONSHIP(ped5, 5, 0);
							SET_CHAR_RELATIONSHIP(ped6, 5, 0);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);
							SET_CHAR_RELATIONSHIP(ped8, 5, 0);

							SET_SENSE_RANGE(ped4, 35.0);
							SET_SENSE_RANGE(ped5, 35.0);
							SET_SENSE_RANGE(ped6, 35.0);
							SET_SENSE_RANGE(ped7, 35.0);
							SET_SENSE_RANGE(ped8, 35.0);

							SET_CHAR_WILL_USE_COVER(ped4, 1);
							SET_CHAR_WILL_USE_COVER(ped5, 1);
							SET_CHAR_WILL_USE_COVER(ped6, 1);
							SET_CHAR_WILL_USE_COVER(ped7, 1);
							SET_CHAR_WILL_USE_COVER(ped8, 1);

							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, FALSE);
							in_hotel = 2;
						}

						if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 1255.107, 268.722, 0.0, 655.107, 868.722, 150.0, 0 )) && (in_aria == 1))
						{
							// прячим педов
							SET_CHAR_COORDINATES(ped1, 289.762, -777.475, 5.05974);// перемещаем игрока
							SET_CHAR_COORDINATES(ped2, 288.738, -777.447, 5.05974);// перемещаем игрока

							// переносим машины
							SET_CAR_COORDINATES(car3, 447.314, 1496.02, 5.53165);//
							SET_CAR_COORDINATES(car4, 424.118, 1418.97, 5.40512);//
							SET_CAR_COORDINATES(car5, 421.365, 1412.77, 5.40512);//
							SET_CAR_HEADING(car3, -10.0);
							SET_CAR_HEADING(car4, 155.0);
							SET_CAR_HEADING(car5, 165.0);

							// создаём блокпосты
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//выгружаем модель педа(в последствии пед изчезнет

							CREATE_CHAR (26, PedM4, 442.545, 1500.14, 5.05974, &ped4, TRUE);// Охранник
							CREATE_CHAR (26, PedM5, 444.711, 1494.64, 5.05974, &ped5, TRUE);// FBI 1
							CREATE_CHAR (26, PedM5, 422.419, 1422.34, 5.05974, &ped6, TRUE);// FBI 2
							CREATE_CHAR (26, PedM5, 420.586, 1418.17, 5.05974, &ped7, TRUE);// FBI 3
							CREATE_CHAR (26, PedM5, 418.289, 1412.33, 5.05974, &ped8, TRUE);// FBI 4

							SET_CHAR_HEADING(ped4, 175.0);
							SET_CHAR_HEADING(ped5, -105.0);
							SET_CHAR_HEADING(ped6, -105.0);
							SET_CHAR_HEADING(ped7, -105.0);
							SET_CHAR_HEADING(ped8, -95.0);

							UpdateWeaponOfPed(ped4, WEAPON_PISTOL);
							UpdateWeaponOfPed(ped5, WEAPON_M4);
							UpdateWeaponOfPed(ped6, WEAPON_M4);
							UpdateWeaponOfPed(ped7, WEAPON_MP5);
							UpdateWeaponOfPed(ped8, WEAPON_M4);

							SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_PISTOL, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_M4, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_M4, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_MP5, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_M4, TRUE);

							SET_CHAR_RELATIONSHIP_GROUP(ped4, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped5, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped6, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped7, 3);
							SET_CHAR_RELATIONSHIP_GROUP(ped8, 3);

							SET_CHAR_RELATIONSHIP(ped4, 5, 0);
							SET_CHAR_RELATIONSHIP(ped5, 5, 0);
							SET_CHAR_RELATIONSHIP(ped6, 5, 0);
							SET_CHAR_RELATIONSHIP(ped7, 5, 0);
							SET_CHAR_RELATIONSHIP(ped8, 5, 0);

							SET_SENSE_RANGE(ped4, 35.0);
							SET_SENSE_RANGE(ped5, 35.0);
							SET_SENSE_RANGE(ped6, 35.0);
							SET_SENSE_RANGE(ped7, 35.0);
							SET_SENSE_RANGE(ped8, 35.0);

							SET_CHAR_WILL_USE_COVER(ped4, 1);
							SET_CHAR_WILL_USE_COVER(ped5, 1);
							SET_CHAR_WILL_USE_COVER(ped6, 1);
							SET_CHAR_WILL_USE_COVER(ped7, 1);
							SET_CHAR_WILL_USE_COVER(ped8, 1);

							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped4, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped5, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped7, FALSE);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped8, FALSE);
							in_aria = 0;
						}
						DRAW_CHECKPOINT( 368.342, 1467.11, 4.82587, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 368.342, 1467.11, 4.82587, &PlayR);//проверка "игрок на координатах"
						if ( PlayR < 1.5 )
						{
							skip = 2;// переменная пропуска
							break;
						}
						
						// провал
						if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR1_03", 5000, 1);//~r~Candy is dead!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_FATALLY_INJURED(ped2)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR3_02", 5000, 1);//~r~You've killed the Congressman! There's no way you can blackmail him now.
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

				// чистим скрипт тут
				WAIT(100);
				REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(vert_ico);//Удаляем иконку на радаре
				SET_MAX_WANTED_LEVEL(6);

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( photos );
				REMOVE_TXD( textur );

				GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 6, &Weap1, &Ammo1_1, &Ammo1_2);
				if (Weap1 == 45)
				{
					SET_CHAR_AMMO(GetPlayerPed(), Weap1, 0);
				}

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(WinM1);//выгружаем модель

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//выгружаем модель педа(в последствии пед изчезнет

				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car4);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car5);//выгружаем модель машины(в последствии машина изчезнет)

				DELETE_OBJECT(&shot_1);
				DELETE_OBJECT(&shot_2);
				DELETE_OBJECT(&shot_3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&shot_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&shot_2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&shot_3);

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_PORN_3" );//Martha's Mug Shot
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(4000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +4000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 4000);
					G_PRON = 4;
					autosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}
//============================== G-spotlight ======================================
		else if ((G_ONMISSION == 0) && (G_PRON == 4))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(365.19, 1463.24, 4.84835, &pron_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(pron_ico, BLIP_INTERNET);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(pron_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "LG_12");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 365.19, 1463.24, 4.84835, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 365.19, 1463.24, 4.84835, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("PORN_4", 15000, CUTSCENE_PORN);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(21.489, 966.28, 9.5, 172.7);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
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
				SET_CHAR_COORDINATES(GetPlayerPed(), 365.628, 1465.67, 5.2528);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -90.0);

				Car car1;
				Ped ped1, ped2, ped3;
				Blip Blip_r, Blip_r2;
				Texture fon, timer;
				Object door_1, door_2, progektor, light, lest_1, lest_2, lest_3, lest_4;
				Cam camera;
				
				skip = 0;
				check_on = 0;
				play_cord = 1;
				res_point = 1;
				Blip_x = -95.4149;
				Blip_y = 1307.89;
				Blip_z = 91.4345;
				Blip_x2 = -93.5626;
				Blip_y2 = 1421.82;
				Blip_z2 = 62.2432;
				G_PRON = 99;

				uint CarM1 = MODEL_PCJ;// Лимузин
				uint PedM1 = MODEL_M_O_STREET_01;// 
				uint PedM2 = MODEL_F_O_PJERSEY_01;// 
				uint PedM3 = MODEL_M_Y_PJERSEY_01;// 
				uint doorM = office_door; //двери лифта
				uint hour, min, minute, weather;
				uint checkpoint;

				uint lest_a_M = dt_gspot_stairs_b; //лестница вверх
				uint lest_b_M = dt_gspot_stairs; //лестница вниз
				uint light_a_M = dts_spot_a; //прожектор
				uint light_b_M = dts_spot_b; //свет прожектора

				textur = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur, "fon_hud" );
				timer = GET_TEXTURE( textur, "timer_hud" );

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(10);

				REQUEST_MODEL(PedM1);// Приспешник 1
				while (!HAS_MODEL_LOADED(PedM1)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Приспешник 2
				while (!HAS_MODEL_LOADED(PedM2)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// Приспешник 2
				while (!HAS_MODEL_LOADED(PedM3)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало

				REQUEST_MODEL(doorM);// двери лифта
				while (!HAS_MODEL_LOADED(doorM)) WAIT(0);
				REQUEST_MODEL(lest_a_M);// лестница вверх
				while (!HAS_MODEL_LOADED(lest_a_M)) WAIT(0);
				REQUEST_MODEL(lest_b_M);// лестница вниз
				while (!HAS_MODEL_LOADED(lest_b_M)) WAIT(0);
				REQUEST_MODEL(light_a_M);// прожектор
				while (!HAS_MODEL_LOADED(light_a_M)) WAIT(0);
				REQUEST_MODEL(light_b_M);// свет прожектора
				while (!HAS_MODEL_LOADED(light_b_M)) WAIT(0);


				CREATE_CAR(CarM1, 421.713, 1489.76, 5.53541, &car1, TRUE);//
				CHANGE_CAR_COLOUR( car1, 132, 132 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car1, 131, 131 );//цвет отрожений машины

				CREATE_CHAR (26, PedM1, 289.762, -777.475, 5.05974, &ped1, TRUE);// 
				CREATE_CHAR (26, PedM2, 288.738, -777.447, 5.05974, &ped2, TRUE);// 
				CREATE_CHAR (26, PedM3, 286.533, -777.448, 5.05974, &ped3, TRUE);// 

				CREATE_OBJECT_NO_OFFSET(doorM, -126.469, 1316.2, 18.3393, &door_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(doorM, -126.469, 1314.2, 18.3393, &door_2, TRUE);

				CREATE_OBJECT_NO_OFFSET(lest_a_M, -140.934, 1907.22, 10.6474, &lest_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(lest_b_M, -103.961, 1891.43, 10.6474, &lest_2, TRUE);
				CREATE_OBJECT_NO_OFFSET(lest_a_M, 65.9711, 1446.13, 11.0396, &lest_3, TRUE);
				CREATE_OBJECT_NO_OFFSET(lest_b_M, 53.3428, 1481.54, 11.0396, &lest_4, TRUE);
				CREATE_OBJECT_NO_OFFSET(light_a_M, 78.5022, 1522.89, 39.7106, &progektor, TRUE);
				CREATE_OBJECT_NO_OFFSET(light_b_M, 78.5022, 1522.89, 39.7106, &light, TRUE);
				SET_OBJECT_HEADING(lest_3, 157.1);
				SET_OBJECT_HEADING(lest_4, 157.1);
				SET_OBJECT_HEADING(progektor, 125.0);
				SET_OBJECT_HEADING(light, 125.0);

				SET_OBJECT_DYNAMIC(door_1, 0);
				SET_OBJECT_DYNAMIC(door_2, 0);
				SET_OBJECT_DYNAMIC(lest_1, 0);
				SET_OBJECT_DYNAMIC(lest_2, 0);
				SET_OBJECT_DYNAMIC(lest_3, 0);
				SET_OBJECT_DYNAMIC(lest_4, 0);
				SET_OBJECT_DYNAMIC(progektor, 0);
				SET_OBJECT_DYNAMIC(light, 0);
				SET_OBJECT_INVINCIBLE(door_1, 1);
				SET_OBJECT_INVINCIBLE(door_2, 1);
				SET_OBJECT_INVINCIBLE(lest_1, 1);
				SET_OBJECT_INVINCIBLE(lest_2, 1);
				SET_OBJECT_INVINCIBLE(lest_3, 1);
				SET_OBJECT_INVINCIBLE(lest_4, 1);
				SET_OBJECT_INVINCIBLE(progektor, 1);
				SET_OBJECT_INVINCIBLE(light, 1);
				FREEZE_OBJECT_POSITION(door_1, 1);
				FREEZE_OBJECT_POSITION(door_2, 1);
				FREEZE_OBJECT_POSITION(lest_1, 1);
				FREEZE_OBJECT_POSITION(lest_2, 1);
				FREEZE_OBJECT_POSITION(lest_3, 1);
				FREEZE_OBJECT_POSITION(lest_4, 1);
				FREEZE_OBJECT_POSITION(progektor, 1);
				FREEZE_OBJECT_POSITION(light, 1);

				// грузим анимации
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				// Грузим пути тут
				REQUEST_CAR_RECORDING( 3050 );// Машина (Washington)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3050 )) WAIT(0);
				REQUEST_CAR_RECORDING( 3051 );// Машина (Washington)
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3051 )) WAIT(0);

				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
				FORWARD_TO_TIME_OF_DAY(18, 0);//устанавливаем время

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "PORN_4", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("porn_4");
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
				FORWARD_TO_TIME_OF_DAY(18, 0);//устанавливаем время
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				// создаём блипы
				ADD_BLIP_FOR_COORD(-54.7404, 1371.15, 5.42921, &pron_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(pron_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(pron_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "POR4_01", 5000, 1);//~g~Go ~h~Downtown ~g~and adjust the spotlight on top of the building.
				SetTime(5000);
				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "POR4_02", 5000, 1);//~g~A fast bike will be needed to jump from roof to roof. The Security Guard usually drives a ~h~PCJ 600~g~ to work...
				SetTime(5000);
				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "POR4_03", 5000, 1);//~g~You will need to get onto the roofs of the buildings. There should be a lift into one of the upper offices...

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)

				// часть 1 добраться до лестници
				while (TRUE)
				{
					WAIT(0);
					GET_TIME_OF_DAY(&hour, &min);
					DRAW_CHECKPOINT( -54.7404, 1371.15, 5.42921, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -54.7404, 1371.15, 5.42921, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 1.5) && (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

						// ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, -64.836, 1370.39, 6.43355); // куда смотрит камера
						SET_CAM_POS			( camera, -22.837, 1381.42, 16.8284 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR4_05", 5000, 1);//~g~These stairs will lead round to a lower office.
						SetTime(4000);

						//убираем камеру
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

						// создаём блипы
						ADD_BLIP_FOR_COORD(-128.407, 1314.88, 16.7565, &pron_ico);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(pron_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(pron_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if (hour == 5)
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "POR4_10", 5000, 1);//~r~It's too light to get up there unseen.
						skip = 1;// переменная пропуска
						break;
					}

				}
				
				// часть 2 лифт
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						GET_TIME_OF_DAY(&hour, &min);
						DRAW_CHECKPOINT( -128.407, 1314.88, 16.7565, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -128.407, 1314.88, 16.7565, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							// создаём блипы
							ADD_BLIP_FOR_COORD(-128.407, 1314.88, 16.7565, &pron_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(pron_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(pron_ico, 0.5); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							ADD_BLIP_FOR_COORD(Blip_x, Blip_y, Blip_z, &Blip_r);//создаем иконку на радаре в переменной "Blip01"
							CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(Blip_r, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_RACE2");//иконка на радаре "Blip01" называние в истории карты
							CHANGE_BLIP_SCALE(Blip_r, 0.77999990); // масштаб иконки на радаре
							checkpoint = CREATE_CHECKPOINT( 6, Blip_x, Blip_y, (Blip_z+1.5), Blip_x2, Blip_y2, Blip_z2, 0.60000000 );
							check_on = 1;
							
							ADD_BLIP_FOR_COORD(Blip_x2, Blip_y2, Blip_z2, &Blip_r2);//создаем иконку на радаре в переменной "Blip01"
							CHANGE_BLIP_SPRITE(Blip_r2, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(Blip_r2, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//иконка на радаре "Blip01" называние в истории карты
							CHANGE_BLIP_SCALE(Blip_r2, (0.77999990 / 1.50000000)); // масштаб иконки на радаре
							CHANGE_BLIP_ALPHA(Blip_r2, 125);

							// телепорт педов тут
							GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car1);
							SET_CHAR_COORDINATES(ped1, -123.191, 1315.801, 16.9909);// перемещаем игрока
							SET_CHAR_COORDINATES(ped2, -123.146, 1314.311, 16.9909);// перемещаем игрока
							SET_CHAR_COORDINATES(ped3, -96.6115, 1360.631, 91.6931);// перемещаем игрока
							SET_CHAR_HEADING(ped1, 180.0);
							SET_CHAR_HEADING(ped2, 0.0);
							SET_CHAR_HEADING(ped3, 0.0);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_VA", "", 0, 0);//
							START_SCRIPT_CONVERSATION(1, 1);

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -124.516, 1314.99, 17.9011); // куда смотрит камера
							SET_CAM_POS			( camera, -136.167, 1314.89, 19.8444 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							// RRR пули 1 тут
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3050, 0.0, 0.0, 0.0);//
							PAUSE_PLAYBACK_RECORDED_CAR(car1);
							SetTime(2100);

							door1Y = 1316.2;
							door2Y = 1314.2;
							// открываем двери лифта
							while (true)
							{
								WAIT( 0 );
								door1Y += 0.03;
								door2Y -= 0.03;
								SET_OBJECT_COORDINATES(door_1, -126.469, door1Y, 18.3393);
								SET_OBJECT_COORDINATES(door_2, -126.469, door2Y, 18.3393);
								if (door1Y > 1317.9)
								{
									break;
								}
							}
							UNPAUSE_PLAYBACK_RECORDED_CAR(car1);

							SetTime(1500);
							SET_CHAR_HEADING(ped1, 90.0);
							SET_CHAR_HEADING(ped2, 90.0);
							STOP_PLAYBACK_RECORDED_CAR(car1);

							// закрываем лифт тут
							while (true)
							{
								WAIT( 0 );
								door1Y -= 0.03;
								door2Y += 0.03;
								SET_OBJECT_COORDINATES(door_1, -126.469, door1Y, 18.3393);
								SET_OBJECT_COORDINATES(door_2, -126.469, door2Y, 18.3393);
								if (door1Y < 1316.17)
								{
									break;
								}
							}
							SetTime(1000);

							ABORT_SCRIPTED_CONVERSATION( 0 );
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_YA", "", 0, 0);//
							START_SCRIPT_CONVERSATION(1, 1);

							// смена ракурса камеры
							POINT_CAM_AT_COORD	( camera, -122.831, 1316.54, 16.9947 ); // куда смотрит камера
							SET_CAM_POS			( camera, -126.006, 1313.32, 20.1873 );//расположение камеры
							SetTime(3500);

							// смена ракурса камеры
							POINT_CAM_AT_COORD	( camera, -117.895, 1321.01, 93.7552 ); // куда смотрит камера
							SET_CAM_POS			( camera, -129.546, 1321.02, 95.6986 );//расположение камеры

							ABORT_SCRIPTED_CONVERSATION( 0 );
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_VA", "", 0, 0);//
							START_SCRIPT_CONVERSATION(1, 1);

							// RRR пули 2 тут
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3051, 0.0, 0.0, 0.0);//
							PAUSE_PLAYBACK_RECORDED_CAR(car1);

							SET_CHAR_COORDINATES(ped1, -117.063, 1321.73, 91.7413);// перемещаем игрока
							SET_CHAR_COORDINATES(ped2, -117.018, 1320.24, 91.7413);// перемещаем игрока
							SET_CHAR_HEADING(ped1, 90.0);
							SET_CHAR_HEADING(ped2, 90.0);

							// переносим створки лифта тут
							SET_OBJECT_COORDINATES(door_1, -120.632, 1321.98, 92.9898);
							SET_OBJECT_COORDINATES(door_2, -120.632, 1319.98, 92.9898);
							SetTime(2100);

							door1Y = 1321.98;
							door2Y = 1319.98;
							// открываем двери лифта
							while (true)
							{
								WAIT( 0 );
								door1Y += 0.03;
								door2Y -= 0.03;
								SET_OBJECT_COORDINATES(door_1, -120.632, door1Y, 92.9898);
								SET_OBJECT_COORDINATES(door_2, -120.632, door2Y, 92.9898);
								if (door1Y > 1323.7)
								{
									break;
								}
							}

							SetTime(500);
							UNPAUSE_PLAYBACK_RECORDED_CAR(car1);
							SetTime(1500);

							// закрываем лифт тут
							while (true)
							{
								WAIT( 0 );
								door1Y -= 0.03;
								door2Y += 0.03;
								SET_OBJECT_COORDINATES(door_1, -120.632, door1Y, 92.9898);
								SET_OBJECT_COORDINATES(door_2, -120.632, door2Y, 92.9898);
								if (door1Y < 1322.01)
								{
									break;
								}
							}
							SetTime(1000);

							STOP_PLAYBACK_RECORDED_CAR(car1);
							SET_CHAR_COORDINATES(GetPlayerPed(), -125.588, 1319.13, 92.1071);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 180.0);

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							MARK_CAR_AS_NO_LONGER_NEEDED(&car1);

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR4_06", 5000, 1);//~g~Return to the lower office if you need access to the rooftops again.
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (hour == 5)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR4_10", 5000, 1);//~r~It's too light to get up there unseen.
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				//*/
				// часть 3 окно
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						GET_TIME_OF_DAY(&hour, &min);
						DRAW_CHECKPOINT( -128.407, 1314.88, 16.7565, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -128.407, 1314.88, 16.7565, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
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
							SET_CHAR_COORDINATES(GetPlayerPed(), -125.588, 1319.13, 92.1071);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 180.0);
							DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
						}

						DRAW_SPHERE(Blip_x, Blip_y, (Blip_z-4.5), 7.0);
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, Blip_x, Blip_y, Blip_z, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 8.5) && (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
							REMOVE_BLIP(Blip_r2);//Удаляем иконку на радаре
							DELETE_CHECKPOINT(checkpoint);
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							play_cord = 2;
							Blip_x = -93.5626;
							Blip_y = 1421.82;
							Blip_z = 62.2432;
							Blip_x2 = -113.274;
							Blip_y2 = 1610.59;
							Blip_z2 = 46.4839;

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

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -99.6834, 1360.02, 93.0695); // куда смотрит камера
							SET_CAM_POS			( camera, -99.6774, 1345.89, 94.1329 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR4_08", 5000, 1);//~g~Smash through the window to start the course. You have until 05:00 before it gets too light to get up there unseen.
							SetTime(3000);

							// смена ракурса камеры
							POINT_CAM_AT_COORD	( camera, -94.0956, 1418.761, 64.9372 ); // куда смотрит камера
							SET_CAM_POS			( camera, -100.112, 1356.501, 94.6805 );//расположение камеры

							SET_CHAR_COORDINATES(GetPlayerPed(), -97.0126, 1306.1, 92.1071);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 0.0);

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR4_09", 5000, 1);//~g~The pickups will show you which building to jump to next.

							// демонстрация чекпойнта
							SETTIMERA(0); //сбрасываем таймер 
							while (TRUE)
							{
								WAIT(0);
								DRAW_SPHERE(Blip_x, Blip_y, (Blip_z-4.5), 7.0);
								if ( TIMERA() > 4000 )
								{
									break;
								}
							}

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							SET_CHAR_COORDINATES(ped1, 289.762, -777.475, 5.05974);// перемещаем игрока
							SET_CHAR_COORDINATES(ped2, 288.738, -777.447, 5.05974);// перемещаем игрока
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (hour == 5)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR4_10", 5000, 1);//~r~It's too light to get up there unseen.
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				
				// часть 4 маршрут
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						if (res_point == 1) // лифт
						{
							DRAW_CHECKPOINT( -128.407, 1314.88, 16.7565, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -128.407, 1314.88, 16.7565, &PlayR);//проверка "игрок на координатах"
							if (( PlayR < 1.5) && (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
							{
								play_cord = 2;
								Blip_x = -93.5626;
								Blip_y = 1421.82;
								Blip_z = 62.2432;
								Blip_x2 = -113.274;
								Blip_y2 = 1610.59;
								Blip_z2 = 46.4839;

								REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
								REMOVE_BLIP(Blip_r2);//Удаляем иконку на радаре
								DELETE_CHECKPOINT(checkpoint);

								ADD_BLIP_FOR_COORD(Blip_x, Blip_y, (Blip_z + 0.1), &Blip_r);//создаем иконку на радаре в переменной "Blip01"
								CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(Blip_r, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_RACE2");//иконка на радаре "Blip01" называние в истории карты
								CHANGE_BLIP_SCALE(Blip_r, 0.77999990); // масштаб иконки на радаре
								checkpoint = CREATE_CHECKPOINT( 6, Blip_x, Blip_y, (Blip_z+1.5), Blip_x2, Blip_y2, Blip_z2, 0.50000000 );

								ADD_BLIP_FOR_COORD(Blip_x2, Blip_y2, (Blip_z2 + 0.1), &Blip_r2);//создаем иконку на радаре в переменной "Blip01"
								CHANGE_BLIP_SPRITE(Blip_r2, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(Blip_r2, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//иконка на радаре "Blip01" называние в истории карты
								CHANGE_BLIP_SCALE(Blip_r2, (0.77999990 / 1.50000000)); // масштаб иконки на радаре
								CHANGE_BLIP_ALPHA(Blip_r2, 125);
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
								SET_CHAR_COORDINATES(GetPlayerPed(), -125.588, 1319.13, 92.1071);// перемещаем игрока
								SET_CHAR_HEADING(GetPlayerPed(), 180.0);
								DO_SCREEN_FADE_IN( 1000 );// убирается затемнение экрана
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							}
						}
						else if (res_point == 2) // крыша
						{
							if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -132.393, 1887.155, 8.199, -147.393, 1907.155, 18.199, 0 )) && (play_cord > 12))// релокация Ленса
							{
								play_cord = 12;
								Blip_x = -56.5504; 
								Blip_y = 1889.09;
								Blip_z = 19.1836;
								Blip_x2 = 26.2289; 
								Blip_y2 = 1898.7;
								Blip_z2 = 23.6123;

								REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
								REMOVE_BLIP(Blip_r2);//Удаляем иконку на радаре
								DELETE_CHECKPOINT(checkpoint);

								ADD_BLIP_FOR_COORD(Blip_x, Blip_y, (Blip_z + 0.1), &Blip_r);//создаем иконку на радаре в переменной "Blip01"
								CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(Blip_r, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_RACE2");//иконка на радаре "Blip01" называние в истории карты
								CHANGE_BLIP_SCALE(Blip_r, 0.77999990); // масштаб иконки на радаре
								checkpoint = CREATE_CHECKPOINT( 6, Blip_x, Blip_y, (Blip_z+1.5), Blip_x2, Blip_y2, Blip_z2, 0.50000000 );

								ADD_BLIP_FOR_COORD(Blip_x2, Blip_y2, (Blip_z2 + 0.1), &Blip_r2);//создаем иконку на радаре в переменной "Blip01"
								CHANGE_BLIP_SPRITE(Blip_r2, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(Blip_r2, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//иконка на радаре "Blip01" называние в истории карты
								CHANGE_BLIP_SCALE(Blip_r2, (0.77999990 / 1.50000000)); // масштаб иконки на радаре
								CHANGE_BLIP_ALPHA(Blip_r2, 125);
							}
						}
						
						DRAW_SPHERE(Blip_x, Blip_y, (Blip_z-4.5), 7.0);
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, Blip_x, Blip_y, Blip_z, &PlayR);//проверка "игрок на координатах"
						if ( PlayR < 8.5 )
						{
							play_cord += 1;
							Blip_x = Blip_x2; 
							Blip_y = Blip_y2;
							Blip_z = Blip_z2;
							PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );

							if (play_cord == 3)
							{
								Blip_x2 = -167.518; 
								Blip_y2 = 1644.58;
								Blip_z2 = 26.5091;
							}
							else if (play_cord == 4)
							{
								Blip_x2 = -275.736; 
								Blip_y2 = 1672.69;
								Blip_z2 = 26.9549;
							}
							else if (play_cord == 5)
							{
								Blip_x2 = -366.585; 
								Blip_y2 = 1678.85;
								Blip_z2 = 19.2333;
							}
							else if (play_cord == 6)
							{
								Blip_x2 = -404.123;
								Blip_y2 = 1739.53;
								Blip_z2 = 10.4662;
							}
							else if (play_cord == 7)
							{
								Blip_x2 = -357.386;
								Blip_y2 = 1831.83;
								Blip_z2 = 21.9557;
							}
							else if (play_cord == 8)
							{
								Blip_x2 = -308.431;
								Blip_y2 = 1832.07;
								Blip_z2 = 14.9601;
							}
							else if (play_cord == 9)
							{
								Blip_x2 = -248.553;
								Blip_y2 = 1877.98;
								Blip_z2 = 16.3595;
							}
							else if (play_cord == 10)
							{
								Blip_x2 = -139.798;
								Blip_y2 = 1898.46;
								Blip_z2 = 10.282;
							}
							else if (play_cord == 11)
							{
								Blip_x2 = -56.5504; 
								Blip_y2 = 1889.09;
								Blip_z2 = 19.1836;
							}
							else if (play_cord == 12)
							{
								REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

								// скускаем лестницу тут
								SET_OBJECT_COORDINATES(lest_1, -101.672, 1899.62, 4.84822);
								SET_OBJECT_COORDINATES(lest_2, -140.934, 1907.22, 10.6474);

								// ставим камеру
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, -138.811, 1902.58, 11.7479); // куда смотрит камера
								SET_CAM_POS			( camera, -174.452, 1907.42, 31.086 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "POR4_11", 5000, 1);//~g~Return to the ladder if you need access to the rooftops again.
								SetTime(3000);

								//убираем камеру
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								END_CAM_COMMANDS( &camera );
								SET_WIDESCREEN_BORDERS( 0 );
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

								// создаём блипы
								ADD_BLIP_FOR_COORD(-140.96, 1906.52, 10.282, &pron_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(pron_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(pron_ico, 0.5); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "NE_POINT");//иконка на радаре называние в истории карты ""

								res_point = 2;
								Blip_x2 = 26.2289; 
								Blip_y2 = 1898.7;
								Blip_z2 = 23.6123;
							}
							else if (play_cord == 13)
							{
								Blip_x2 = 70.4563; 
								Blip_y2 = 1919.7;
								Blip_z2 = 21.1601;
							}
							else if (play_cord == 14)
							{
								Blip_x2 = 136.457; 
								Blip_y2 = 1933.94;
								Blip_z2 = 20.9484;
							}
							else if (play_cord == 15)
							{
								Blip_x2 = 152.857; 
								Blip_y2 = 1873.23;
								Blip_z2 = 21.13;
							}
							else if (play_cord == 16)
							{
								Blip_x2 = 154.597; 
								Blip_y2 = 1812.46;
								Blip_z2 = 21.7429;
							}
							else if (play_cord == 17)
							{
								Blip_x2 = 155.023; 
								Blip_y2 = 1737.7;
								Blip_z2 = 35.6598;
							}
							else if (play_cord == 18)
							{
								Blip_x2 = 100.915; 
								Blip_y2 = 1589.07;
								Blip_z2 = 32.3309;
							}
							else if (play_cord == 19)
							{
								Blip_x2 = Blip_x2; 
								Blip_y2 = Blip_y2;
								Blip_z2 = Blip_z2;
							}
							else if (play_cord == 20)
							{
								// скускаем лестницу тут
								SET_OBJECT_COORDINATES(lest_3, 53.3428, 1481.54, 11.0396);
								SET_OBJECT_COORDINATES(lest_4, 65.9711, 1446.13, 11.0396);
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

								// ставим камеру
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, 63.5209, 1469.18, 16.2917); // куда смотрит камера
								SET_CAM_POS			( camera, 118.974, 1367.83, 29.1514 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );
								SetTime(3000);

								// смена ракурса
								POINT_CAM_AT_COORD	( camera, 61.6074, 1438.74, 6.88951); // куда смотрит камера
								SET_CAM_POS			( camera, 93.8511, 1443.69, 25.5205 );//расположение камеры
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "POR4_11", 5000, 1);//~g~Return to the ladder if you need access to the rooftops again.
								SetTime(3000);

								//убираем камеру
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								END_CAM_COMMANDS( &camera );
								SET_WIDESCREEN_BORDERS( 0 );
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

								REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
								REMOVE_BLIP(Blip_r2);//Удаляем иконку на радаре
								REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
								DELETE_CHECKPOINT(checkpoint);
								check_on = 0;
								
								// создаём блип
								ADD_BLIP_FOR_COORD(76.9871, 1523.56, 39.3627, &pron_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(pron_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(pron_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(pron_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
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

								ADD_BLIP_FOR_COORD(Blip_x2, Blip_y2, (Blip_z2 + 0.1), &Blip_r2);//создаем иконку на радаре в переменной "Blip01"
								CHANGE_BLIP_SPRITE(Blip_r2, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(Blip_r2, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r2, "NE_RACE3");//иконка на радаре "Blip01" называние в истории карты
								CHANGE_BLIP_SCALE(Blip_r2, (0.77999990 / 1.50000000)); // масштаб иконки на радаре
								CHANGE_BLIP_ALPHA(Blip_r2, 125);
							}
							else
							{
								REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
								REMOVE_BLIP(Blip_r2);//Удаляем иконку на радаре
								DELETE_CHECKPOINT(checkpoint);
								ADD_BLIP_FOR_COORD(Blip_x, Blip_y, (Blip_z + 0.1), &Blip_r);//создаем иконку на радаре в переменной "Blip01"
								CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(Blip_r, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "MO_TARGET");//иконка на радаре "Blip01" называние в истории карты
								CHANGE_BLIP_SCALE(Blip_r, 0.77999990); // масштаб иконки на радаре
								checkpoint = CREATE_CHECKPOINT( 6, Blip_x, Blip_y, (Blip_z+1.5), Blip_x, Blip_y, (Blip_z-1.5), 0.50000000 );
							}
						}
						
						// HUD время
						GET_TIME_OF_DAY(&hour, &min);
						DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						if ( hour > 9 )
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_NOZERO", hour);// минуты
						}
						else
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", hour);// минуты
						}

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						if ( min > 9 )
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", min);// секунды
						}
						else
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_ZERO", min);// секунды
						}

						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (hour == 5)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR4_10", 5000, 1);//~r~It's too light to get up there unseen.
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				
				// часть 5 прожектор
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						// HUD время
						GET_TIME_OF_DAY(&hour, &min);
						DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						if ( hour > 9 )
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_NOZERO", hour);// минуты
						}
						else
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", hour);// минуты
						}

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						if ( min > 9 )
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_NOZERO", min);// секунды
						}
						else
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.76954074, "CP_TIME_ZERO", min);// секунды
						}
						DRAW_CHECKPOINT( 76.9871, 1523.56, 39.3627, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 76.9871, 1523.56, 39.3627, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);

							// камера
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 77.5939, 1523.47, 40.4273 ); // куда смотрит камера
							SET_CAM_POS			( camera, 78.0524, 1528.79, 42.951 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R4_ZA", "", 0, 0);//
							START_SCRIPT_CONVERSATION(1, 1);
							
							//анимация тут
							SET_CHAR_COORDINATES(GetPlayerPed(), 77.4213, 1523.94, 39.6316);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), -125.0);
							REQUEST_ANIMS( "amb@atm" );//загружаем файл с анимацией
							while (!HAVE_ANIMS_LOADED( "amb@atm" )) WAIT(0);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "f_insertcard", "amb@atm", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе

							SetTime(2000);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 390.7106);
							SetTime(500);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);
							SetTime(500);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 390.7106);
							SetTime(500);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);
							SetTime(300);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 390.7106);
							SetTime(200);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);
							SetTime(100);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 390.7106);
							SetTime(50);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);
							SetTime(10);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 390.7106);
							SetTime(10);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);
							SetTime(10);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 390.7106);
							SetTime(500);

							// смена ракурса
							POINT_CAM_AT_COORD	( camera, -73.8506, 1481.72, 165.916 ); // куда смотрит камера
							SET_CAM_POS			( camera, 82.3065, 1524.01, 40.0194 );//расположение камеры
							SET_CHAR_COORDINATES(GetPlayerPed(), 86.5624, 1525.14, 39.4721);// перемещаем игрока

							// поворот прожектора тут
							light_z = 125.0;
							while (true)
							{
								WAIT( 0 );

								light_z -= 0.25;
								SET_OBJECT_HEADING(progektor, light_z);
								if (light_z < 13.0)
								{
									break;
								}
							}

							SetTime(500);
							SET_OBJECT_HEADING(light, 13.0);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);
							SetTime(10);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 390.7106);
							SetTime(10);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);
							SetTime(10);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 390.7106);
							SetTime(50);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);
							SetTime(100);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 390.7106);
							SetTime(200);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);
							SetTime(300);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 390.7106);
							SetTime(500);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);
							SetTime(500);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 390.7106);
							SetTime(500);
							SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);
							SetTime(5000);

							ABORT_SCRIPTED_CONVERSATION( 0 );

							//-------------------------
							DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())
								{
									break;
								}
							}
							// смена ракурса
							POINT_CAM_AT_COORD	( camera, 428.048, 1500.59, 9.42667 ); // куда смотрит камера
							SET_CAM_POS			( camera, 476.677, 1475.27, 15.8669 );//расположение камеры
							SET_CHAR_COORDINATES(GetPlayerPed(), 79.4098, 1528.11, 39.4721);// перемещаем игрока

							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

							SETTIMERA(0); //сбрасываем таймер 
							while (true)
							{
								SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
								SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
								SET_TEXT_EDGE(1, 0, 0, 0, 255); //
								SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
								SET_TEXT_CENTRE(1); // задаём центр текста
								DISPLAY_TEXT(0.5, 0.45, "POR_AS1");//FILM STUDIO ASSET COMPLETED
								WAIT( 0 );
								if ( TIMERA() > 5000 )
								{
									break;
								}
							}

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, 435.441, 1491.101, 6.07797 ); // куда смотрит камера
							SET_CAM_POS			( camera, 432.529, 1489.461, 7.16788 );//расположение камеры

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR_AS2", 5000, 1);//~g~Inter Global Films will now generate revenue up to a maximum of $7000. Make sure you collect it regularly.
							
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
						else if (hour == 5)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "POR4_10", 5000, 1);//~r~It's too light to get up there unseen.
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				

				// чистим скрипт тут
				WAIT(100);
				REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
				REMOVE_BLIP(Blip_r2);//Удаляем иконку на радаре
				REMOVE_CAR_RECORDING( 3050 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3051 ); // выгружаем пути транспорта
				G_PRON = 4;

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( timer );
				REMOVE_TXD( textur );

				if (check_on == 1)
				{
					DELETE_CHECKPOINT(checkpoint);
				}
								
				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(doorM);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(lest_a_M);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(lest_b_M);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(light_a_M);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(light_b_M);//выгружаем модель

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет

				DELETE_OBJECT(&door_1);
				DELETE_OBJECT(&door_2);
				DELETE_OBJECT(&lest_1);
				DELETE_OBJECT(&lest_2);
				DELETE_OBJECT(&lest_3);
				DELETE_OBJECT(&lest_4);
				DELETE_OBJECT(&progektor);
				DELETE_OBJECT(&light);

				MARK_OBJECT_AS_NO_LONGER_NEEDED(&door_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&door_2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&lest_1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&lest_2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&lest_3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&lest_4);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&progektor);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&light);

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					G_PRON = 5;
					autosave = 1;
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_PORN_4" );//G-spotlight
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(8000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +8000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 8000);
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}
		else if ((G_ONMISSION == 0) && (G_PRON >= 5))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(434.754, 1490.9, 5.88433, &pron_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(pron_ico, BLIP_INTERNET);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(pron_ico, 1.1); // масштаб иконки на радаре
				SET_BLIP_AS_SHORT_RANGE(pron_ico, 1); // иконка пропадает если не в зоне радардиска
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(pron_ico, "LG_12");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(pron_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}
		if (G_PRON >= 5)
		{
			if ( TIMERC() > 411)// время фарма
			{
				if (income < 7000)// максимальный доход
				{
					income +=1;
				}
				SETTIMERC(0); //сбрасываем таймер 
			}
			if (G_COLLECTOR == 3)// ID Бизнеса
			{
				income = 0;
				G_COLLECTOR = 0;
			}
			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 441.11, 1482.908, 4.651, 424.819, 1499.303, 9.587, 0 ))
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
				if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), 435.883, 1488.756, 432.883, 1491.756, 0))
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

			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -121.554, 1312.835, 16.297, -126.554, 1317.835, 23.297, 0 ))// телепорт в офис
			{
				DO_SCREEN_FADE_OUT(1000);
				while (IS_SCREEN_FADING())
				{
					WAIT(0);
				}
				SET_CHAR_COORDINATES(GetPlayerPed(), -121.924, 1321.19, 91.723);
				SET_CHAR_HEADING(GetPlayerPed(), 90.0);
				WAIT(500);
				DO_SCREEN_FADE_IN(1000);
			}
			else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -115.692, 1318.518, 90.377, -120.692, 1323.518, 97.377, 0 ))// телепорт из офиса
			{
				DO_SCREEN_FADE_OUT(1000);
				while (IS_SCREEN_FADING())
				{
					WAIT(0);
				}
				SET_CHAR_COORDINATES(GetPlayerPed(), -127.984, 1315.33, 17.1524);
				SET_CHAR_HEADING(GetPlayerPed(), 90.0);
				WAIT(500);
				DO_SCREEN_FADE_IN(1000);
			}
		}
	}
}
void main(void)
{
	THIS_SCRIPT_SHOULD_BE_SAVED();
	studio();
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
