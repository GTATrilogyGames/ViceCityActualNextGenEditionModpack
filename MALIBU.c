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
#include "map_offset.h"
#include "cutscenes.h"
#include "mission_passed.h"
#include "fast_travel.h"
float PlayX, PlayY, PlayZ, PlayR, blip_on, skip, text, in_area, cop_on, PedX, PedY, PedZ, PedR, stalking, stalkerR, in_car, del_car, vorotaX, vorotaY, siren, autosave, round_skip;
float Ramka1_y, Ramka2_y, Ramka3_y, mishen1_y, mishen2_y, mishen3_y, mishen4_y, mishen5_y, mishen6_y, fix_1_1, fix_1_2, fix_1_3, fix_1_4, fix_1_5, fix_2_1, fix_2_2, fix_2_3, fix_2_4, fix_2_5, fix_3_1, fix_3_2, fix_3_3, fix_3_4, fix_3_5;
float Ramka1_LR, Ramka2_LR, Ramka3_LR, Heal_1_1, Heal_1_2, Heal_1_3, Heal_1_4, Heal_1_5, Heal_2_1, Heal_2_2, Heal_2_3, Heal_2_4, Heal_2_5, Heal_3_1, Heal_3_2, Heal_3_3, Heal_3_4, Heal_3_5, score1, score2, score3, score_all;
float mishen1_x,  mishen2_x,  mishen3_x,  mishen4_x,  mishen5_x,  mishen6_x, Ramka4_LR, Ramka5_LR, Ramka6_LR, sound, audio, textur1, time_s, time_m;
float start, Blip_x, Blip_y, Blip_z, Blip_x2, Blip_y2, Blip_z2, play_cord, poziteon, ugol, wanted, water1X, water1Y, water1Z, water1R;
float Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, Ped1R, SetSped1, ped1_cord, sped_wall1, sped_wall2, sped_wall3;
float ofice, PedX2, PedY2, PedZ2, add_cash, road_spech, hp_car, speech_hp, smoke_on;
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
void club(void)
{
	blip_on = 0;
	autosave = 0;
	Blip malibu_ico;
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
//============================== No Escape? ======================================
		if ((G_ONMISSION == 0) && (G_CLUB == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(896.966, 472.341, 5.394, &malibu_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(malibu_ico, BLIP_CLUB);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(malibu_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "LG_10");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 896.966, 472.341, 5.394, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 896.966, 472.341, 5.394, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("BANK_1", 15000, CUTSCENE_BANKJOB);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(512.591, -74.900, 9.573, 189.24);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
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
				SET_CHAR_COORDINATES(GetPlayerPed(), 898.68, 474.04, 6.45);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 287.0);
				MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 1 );
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "BANK_1", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("bank_1");
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
				MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 0 );
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				Car car1, car2;
				Cam camera;
				Blip card_ico;
				Pickup aid_1, card;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12;
				Object vorota;
				int dm, cdm;

				skip = 0;
				round_skip = 0;
				text = 0;
				in_area = 0;
				cop_on = 0;
				del_car = 0;
				in_car = 0;
				stalking = 0;
				siren = 0;
				vorotaX = 816.722;
				vorotaY = 26.8835;

				LOAD_CHAR_DECISION_MAKER(2, &dm);
				LOAD_COMBAT_DECISION_MAKER(3, &cdm);

				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				uint CarM1 = MODEL_SENTINEL;// Сентинейл
				uint PedM1 = MODEL_IG_DARDAN;// Кэм
				uint PedM2 = MODEL_M_Y_COP;// Коп
				uint vorotaM = od_celldoor3; //ворота
				uint AudID1, AudID2, AudID3;

				REQUEST_MODEL(CarM1);// Сентинейл
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(10);
				REQUEST_MODEL(PedM1);// Кэм
				while (!HAS_MODEL_LOADED(PedM1)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Коп
				while (!HAS_MODEL_LOADED(PedM2)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(vorotaM);// ворота
				while (!HAS_MODEL_LOADED(vorotaM)) WAIT(0);

				// грузим анимации
				REQUEST_ANIMS( "amb@hang_str_idls" );
				while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

				REQUEST_ANIMS( "amb@atm" );//загружаем файл с анимацией
				while (!HAVE_ANIMS_LOADED( "amb@atm" )) WAIT(0);

				REQUEST_ANIMS( "missttkill" );
				while (!HAVE_ANIMS_LOADED( "missttkill" )) WAIT(0);

				REQUEST_ANIMS( "amb_sit_wall_m" );
				while (!HAVE_ANIMS_LOADED( "amb_sit_wall_m" )) WAIT(0);

				REQUEST_ANIMS( "amb@wall_read_idl_f" );
				while (!HAVE_ANIMS_LOADED( "amb@wall_read_idl_f" )) WAIT(0);

				// создаём машины
				CREATE_CAR(CarM1, 299.551, -788.604, 5.44546, &car1, TRUE);// Сентинейл

				// создаём педов
				CREATE_CHAR (26, PedM1, 302.252, -785.078, 5.05974, &ped1, TRUE);// Джонс
				CREATE_CHAR (26, PedM2, 300.252, -785.078, 5.05974, &ped2, TRUE);// коп
				CREATE_CHAR (26, PedM2, 298.252, -785.078, 5.05974, &ped3, TRUE);// коп
				CREATE_CHAR (26, PedM2, 296.252, -785.078, 5.05974, &ped4, TRUE);// коп
				CREATE_CHAR (26, PedM2, 294.252, -785.078, 5.05974, &ped5, TRUE);// коп
				CREATE_CHAR (26, PedM2, 292.252, -785.078, 5.05974, &ped6, TRUE);// коп
				CREATE_CHAR (26, PedM2, 290.252, -785.078, 5.05974, &ped7, TRUE);// коп
				CREATE_CHAR (26, PedM2, 288.252, -785.078, 5.05974, &ped8, TRUE);// коп
				CREATE_CHAR (26, PedM2, 286.252, -785.078, 5.05974, &ped9, TRUE);// коп
				CREATE_CHAR (26, PedM2, 284.252, -785.078, 5.05974, &ped10, TRUE);// коп
				CREATE_CHAR (26, PedM2, 282.252, -785.078, 5.05974, &ped11, TRUE);// коп
				CREATE_CHAR (26, PedM2, 280.252, -785.078, 5.05974, &ped12, TRUE);// коп
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 18);
				SET_CHAR_RELATIONSHIP(ped1, 5, 24);
				SET_SENSE_RANGE(ped1, 0.01);
				SET_CHAR_COMPONENT_VARIATION(ped1, 1, 0, 0);

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

				CREATE_OBJECT_NO_OFFSET(vorotaM, 816.722, 26.8835, 4.68022, &vorota, TRUE);
				SET_OBJECT_DYNAMIC(vorota, 0);
				SET_OBJECT_INVINCIBLE(vorota, 1);
				FREEZE_OBJECT_POSITION(vorota, 1);
				ADD_OBJECT_TO_INTERIOR_ROOM_BY_NAME(vorota, "cop_mloroom");

				CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 800.412, 37.9893, 8.592, -90.0, 0.0, 0.0, &aid_1);//Аптека
				CREATE_PICKUP( vc_keycard, 22, 799.772, 62.4925, 8.55801, &card, 0 );// ключ-карта
				ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(aid_1, "cop_int");
				ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(card, "cop_int");

				// создаём блипы
				ADD_BLIP_FOR_COORD(813.281, 27.6732, 3.54226, &malibu_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

				PRINT_STRING_IN_STRING("string", "BJM1_1", 5000, 1);//~g~Break Cam Jones out of police custody!
				// часть 1 войти в полицейский участок
				while (true)
				{
					WAIT( 0 );
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 831.844, 51.777, 5.354, 825.844, 57.777, 11.354, 0 )) || (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 829.643, 53.671, 5.354, 823.643, 60.199, 11.354, 0 )) || (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 827.442, 55.566, 5.354, 821.442, 61.566, 11.354, 0 )))
					{
						if (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0))
						{
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
						}
						else
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM1_3", 5000, 1);//~g~You will find something useful in the station's locker room.
						}
						// телепартируем педов тут
						CLEAR_AREA(818.966, 60.3302, 6.737, 5.0, 1);//очещаем зону загрузки
						CLEAR_AREA(832.226, 39.4608, 5.284, 5.0, 1);//очещаем зону загрузки
						CLEAR_AREA(804.777, 42.0494, 8.239, 5.0, 1);//очещаем зону загрузки
						CLEAR_AREA(803.956, 51.3054, 8.239, 5.0, 1);//очещаем зону загрузки
						CLEAR_AREA(805.887, 55.1141, 8.239, 5.0, 1);//очещаем зону загрузки
						CLEAR_AREA(802.008, 55.7254, 8.239, 5.0, 1);//очещаем зону загрузки
						CLEAR_AREA(796.713, 57.2504, 8.239, 5.0, 1);//очещаем зону загрузки
						CLEAR_AREA(793.295, 45.3329, 8.239, 5.0, 1);//очещаем зону загрузки

						SET_CHAR_COORDINATES(ped1, 813.281, 27.6732, 3.54226);// ссыт
						SET_CHAR_COORDINATES(ped2, 833.354, 39.8861, 5.28409);// сидит
						SET_CHAR_COORDINATES(ped3, 820.546, 59.1127, 6.737);// стоит
						SET_CHAR_COORDINATES(ped4, 818.804, 63.7868, 6.35038);// шкаф
						SET_CHAR_COORDINATES(ped5, 815.602, 58.6608, 6.737);// стоит
						SET_CHAR_COORDINATES(ped6, 804.777, 42.0494, 8.239);// шкаф
						SET_CHAR_COORDINATES(ped7, 803.956, 51.3054, 8.239);// шкаф
						SET_CHAR_COORDINATES(ped8, 807.083, 55.1958, 8.2391);// сидит
						SET_CHAR_COORDINATES(ped9, 800.989, 55.4021, 8.2391);// сидит
						SET_CHAR_COORDINATES(ped10, 794.783,54.6292,8.2391);// шкаф
						SET_CHAR_COORDINATES(ped11, 793.884, 44.7743, 8.2391);// стоит
						SET_CHAR_COORDINATES(ped12, 795.337, 46.4029, 8.2391);// стоит

						SET_CHAR_HEADING(ped1, 80.0);
						SET_CHAR_HEADING(ped2, 54.0);
						SET_CHAR_HEADING(ped3, -126.0);
						SET_CHAR_HEADING(ped4, 46.0);
						SET_CHAR_HEADING(ped5, 144.0);
						SET_CHAR_HEADING(ped6, -129.0);
						SET_CHAR_HEADING(ped7, 51.0);
						SET_CHAR_HEADING(ped8, 146.0);
						SET_CHAR_HEADING(ped9, -129.0);
						SET_CHAR_HEADING(ped10, 146.0);
						SET_CHAR_HEADING(ped11, -52.0);
						SET_CHAR_HEADING(ped12, 133.0);

						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "piss_loop", "missttkill", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "sit_down_idle_01", "amb_sit_wall_m", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped4, "f_takecash", "amb@atm", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "f_takecash", "amb@atm", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "f_takecash", "amb@atm", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped8, "turn_page", "amb@wall_read_idl_f", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped9, "sit_down_idle_01", "amb_sit_wall_m", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped10, "f_takecash", "amb@atm", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе

						UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_13);
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

						// создаём блипы
						REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
						ADD_BLIP_FOR_CHAR(ped1, &malibu_ico);
						CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

						break;
					}
					if (IS_CHAR_INJURED(ped1))
					{
						EXPLODE_CHAR_HEAD(ped1);
					}
					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if (IS_CHAR_DEAD(ped1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "BJM1_2", 5000, 1);//~r~You were supposed to bust Cam out, not get him killed!
						skip = 1;// переменная пропуска
						break;
					}
				}
				// часть 2 переодеться
				if(skip == 0)
				{
					while (true)
					{
						WAIT( 0 );
						DRAW_CHECKPOINT( 840.727,46.4067,6.17163, 1.1, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 840.727,46.4067,6.17163, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 840.784, 46.407, 6.956 ); // куда смотрит камера
							SET_CAM_POS			( camera, 831.199, 47.402, 8.655 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 842.515, 48.5359, 6.17163, 2, -2);// // Томми уходит в душевую
							SetTime(2000);
							SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 5, 0);// меняем одежду
							SET_CHAR_HEADING(GetPlayerPed(), 139.0);
							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 839.903, 45.4487, 6.17163, 2, -2);// // Томми выходит
							SetTime(3000);

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							// создаём блипы
							ADD_BLIP_FOR_PICKUP(card, &card_ico);
							CHANGE_BLIP_SPRITE(card_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(card_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(card_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(card_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM1_21", 5000, 1);//~g~The key card to the cells can be found upstairs in the station.
							break;
						}
						else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 823.221, 38.803, 5.354, 813.221, 52.803, 11.354, 0 ))
						{
							// воспроизводим аудио
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R7_GK", "BJM1_5", 0, 0);//Only authorized personnel beyond this point!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM1_21", 5000, 1);//~g~The key card to the cells can be found upstairs in the station.

							while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/RB4_MUSEUM_PIECE" )))
							{
								 WAIT(0);
							}
							AudID1 = GET_SOUND_ID();
							PLAY_SOUND_FROM_POSITION(AudID1, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", 821.13, 52.31, 7.31);
							AudID2 = GET_SOUND_ID();
							PLAY_SOUND_FROM_POSITION(AudID2, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", 809.09, 45.51, 8.78);
							AudID3 = GET_SOUND_ID();
							PLAY_SOUND_FROM_POSITION(AudID3, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", 827.86, 35.43, 5.83);
							siren = 1;

							SET_SENSE_RANGE(ped2, 250.0);
							SET_SENSE_RANGE(ped4, 250.0);
							SET_SENSE_RANGE(ped6, 250.0);
							SET_SENSE_RANGE(ped8, 250.0);
							SET_SENSE_RANGE(ped10, 250.0);
							SET_SENSE_RANGE(ped12, 250.0);
							TASK_COMBAT(ped2, GetPlayerPed());// агрим охраника
							TASK_COMBAT(ped4, GetPlayerPed());// агрим охраника
							TASK_COMBAT(ped6, GetPlayerPed());// агрим охраника
							TASK_COMBAT(ped8, GetPlayerPed());// агрим охраника
							TASK_COMBAT(ped10, GetPlayerPed());// агрим охраника
							TASK_COMBAT(ped12, GetPlayerPed());// агрим охраника
							break;
						}
						else if (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0))
						{
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM1_21", 5000, 1);//~g~The key card to the cells can be found upstairs in the station.
							break;
						}
						if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM1_2", 5000, 1);//~r~You were supposed to bust Cam out, not get him killed!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// часть 3 Взять ключ-карту
				if(skip == 0)
				{
					while (true)
					{
						WAIT( 0 );
						DRAW_CHECKPOINT( 817.92, 23.2714, 3.30849, 1.1, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 817.92, 23.2714, 3.30849, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (text == 0))
						{
							if (text == 0)
							{
								// создаём блипы
								REMOVE_BLIP(card_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_PICKUP(card, &card_ico);
								CHANGE_BLIP_SPRITE(card_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(card_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(card_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(card_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "BJM1_23", 5000, 1);//~g~You need to get the key card first!
								text = 1;
							}
						}
						else if (( PlayR > 1.6) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (text == 1))
						{
							text = 0;
						}
						if (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0))
						{
							if (cop_on == 0)
							{
								cop_on = 1;
								ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
								APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
							}
						}
						if (HAS_PICKUP_BEEN_COLLECTED( card ))
						{
							REMOVE_BLIP(card_ico);//Удаляем иконку на радаре
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NE_BJM1_R", 5000, 1);//~g~Release Cam Johnson.
							break;
						}
						if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM1_2", 5000, 1);//~r~You were supposed to bust Cam out, not get him killed!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// часть 4 выпустить заключенного
				if(skip == 0)
				{
					while (true)
					{
						WAIT( 0 );
						DRAW_CHECKPOINT( 817.92, 23.2714, 3.30849, 1.1, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 817.92, 23.2714, 3.30849, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							SET_CHAR_COORDINATES(GetPlayerPed(), 817.718, 23.311, 3.45236);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 170.0);

							// лояльность к игроку тут
							SET_CHAR_RELATIONSHIP_GROUP(ped1, 18);
							SET_CHAR_DECISION_MAKER(ped1, dm);
							SET_COMBAT_DECISION_MAKER(ped1, cdm);
							SET_CHAR_HEALTH(ped1, 800);
							SET_CHAR_WILL_USE_COVER(ped1, 1);
							SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, FALSE);
							SET_SENSE_RANGE(ped1, 0.01);
							SET_MAX_WANTED_LEVEL(3);

							// даём педу оружие
							//UpdateWeaponOfPed(ped1, WEAPON_MICRO_UZI);
							//SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_MICRO_UZI, TRUE);

							// ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, 818.014, 23.5824, 4.5652); // куда смотрит камера
							SET_CAM_POS			( camera, 820.505, 28.8662, 4.53316 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "f_insertcard", "amb@atm", 8.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе
							SetTime(2000);

							// смена ракурса камеры
							POINT_CAM_AT_COORD	( camera, 813.964, 27.564, 4.444 ); // куда смотрит камера
							SET_CAM_POS			( camera, 820.649, 26.059, 4.002 );//расположение камеры

							// анисация открытия двери
							while (true)
							{
								WAIT( 1 );
								vorotaX -= 0.008;
								vorotaY -= 0.0095;
								SET_OBJECT_COORDINATES(vorota, vorotaX, vorotaY, 4.68022);
								if (vorotaY < 25.817)
								{
									break;
								}
							}

							// педы идут
							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 817.523, 26.0563, 3.30849, 2, -2);// Томми идёт в двери
							TASK_GO_STRAIGHT_TO_COORD(ped1, 815.979, 27.1949, 3.30849, 2, -2);// Кэм идёт в двери
							SetTime(3000);
							SET_CHAR_HEADING(GetPlayerPed(), 40.0);

							// разговор тут
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_GL", "BNK1_7", 0, 0);//Cam Jones?
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 1500 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_HA", "BNK1_10", 0, 0);//Yeah, that's me..
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 1500 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_HB", "BNK1_8", 0, 0);//I'm busting you out!
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 1500 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R7_IA", "BNK1_11", 0, 0);//Whatever you say!
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 1500 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// смена ракурса камеры
							POINT_CAM_AT_COORD	( camera, 816.333, 23.334, 4.597 ); // куда смотрит камера
							SET_CAM_POS			( camera, 821.841, 29.998, 4.056 );//расположение камеры

							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 819.207, 27.1564, 3.30849, 2, -2);// Томми идёт в двери
							TASK_GO_STRAIGHT_TO_COORD(ped1, 818.612, 26.3146, 3.30849, 2, -2);// Кэм идёт в двери
							SetTime(3000);

							//убираем камеру
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
							text = 0;

							// разговор тут
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R7_IB", "BNK1_12", 0, 0);//Lose the heat and get me back to my place!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							SET_SENSE_RANGE(ped2, 250.0);
							SET_SENSE_RANGE(ped4, 250.0);
							SET_SENSE_RANGE(ped6, 250.0);
							SET_SENSE_RANGE(ped8, 250.0);
							SET_SENSE_RANGE(ped10, 250.0);
							SET_SENSE_RANGE(ped12, 250.0);
							TASK_COMBAT(ped2, GetPlayerPed());// агрим охраника
							TASK_COMBAT(ped4, GetPlayerPed());// агрим охраника
							TASK_COMBAT(ped6, GetPlayerPed());// агрим охраника
							TASK_COMBAT(ped8, GetPlayerPed());// агрим охраника
							TASK_COMBAT(ped10, GetPlayerPed());// агрим охраника
							TASK_COMBAT(ped12, GetPlayerPed());// агрим охраника

							if (siren == 0)
							{
								while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/RB4_MUSEUM_PIECE" )))
								{
									 WAIT(0);
								}
								AudID1 = GET_SOUND_ID();
								PLAY_SOUND_FROM_POSITION(AudID1, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", 821.13, 52.31, 7.31);
								AudID2 = GET_SOUND_ID();
								PLAY_SOUND_FROM_POSITION(AudID2, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", 809.09, 45.51, 8.78);
								AudID3 = GET_SOUND_ID();
								PLAY_SOUND_FROM_POSITION(AudID3, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", 827.86, 35.43, 5.83);
								siren = 1;
							}
							break;
						}
						if (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0))
						{
							if (cop_on == 0)
							{
								cop_on = 1;
								ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
								APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
							}
						}
						if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM1_2", 5000, 1);//~r~You were supposed to bust Cam out, not get him killed!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// часть 5
				if(skip == 0)
				{
					while (true)
					{
						WAIT( 0 );
						if (in_area == 0)
						{
							if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 829.643, 53.671, 5.354, 823.643, 60.199, 11.354, 0 )))
							{
								in_area = 1;
							}
						}
						else if (in_area == 1)
						{
							if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 829.643, 53.671, 5.354, 823.643, 60.199, 11.354, 0 ))
							{
								// переносим автомобиль
								SET_CAR_COORDINATES(car1, 810.219, 83.953, 4.701);// перемещаем игрока
								SET_CAR_HEADING(car1, 115.0);

								MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
								MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NEWANTED", 5000, 1);//~g~Shake the cops and lose your wanted level!
								SET_MAX_WANTED_LEVEL(6);
								in_area = 2;
								del_car = 1;
							}
						}
						if (!IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0))
						{
							if (text == 0)
							{
								ADD_BLIP_FOR_COORD(-396.853, -366.469, 4.82963, &malibu_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "BJM1_22", 5000, 1);//~g~Get Cam back to his house!
								text = 1;
							}
							DRAW_CHECKPOINT( -396.853, -366.469, 4.82963, 2.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -396.853, -366.469, 4.82963, &PlayR);//проверка "игрок на координатах"
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -396.853, -366.469, 4.82963, &PedR);//проверка "игрок на координатах"
							if (( PlayR < 1.5) && (PedR < 2.5))
							{
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

								// ставим камеру
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, -396.281, -365.604, 5.44972 ); // куда смотрит камера
								SET_CAM_POS			( camera, -400.289, -371.423, 8.03588 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );

								// разговор тут
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R7_JA", "BNK1_13", 0, 0);//I'm gonna be doing a job and you're my safe cracker.
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R7_KA", "BNK1_14", 0, 0);//Beats losing my ass in a cell!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								// смена ракурса камеры
								POINT_CAM_AT_COORD	( camera, -396.955, -362.708, 4.5538 ); // куда смотрит камера
								SET_CAM_POS			( camera, -400.137, -381.606, 9.4254 );//расположение камеры
								TASK_GO_STRAIGHT_TO_COORD(ped1, -400.245, -372.539, 5.45929, 2, -2);// Кэм идёт в двери
								SetTime(6000);

								//убираем камеру
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								END_CAM_COMMANDS( &camera );
								SET_WIDESCREEN_BORDERS( 0 );
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
								SET_CHAR_COORDINATES(ped1, 8.29, 5.852, 29.284);// перемещаем игрока
								skip = 2;// переменная пропуска
								break;
							}
						}
						else
						{
							if (text == 1)
							{
								REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
								text = 0;
							}
						}
						if (IS_CHAR_INJURED(ped1))
						{
							EXPLODE_CHAR_HEAD(ped1);
						}
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_DEAD(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM1_2", 5000, 1);//~r~You were supposed to bust Cam out, not get him killed!
							skip = 1;// переменная пропуска
							break;
						}
						// Кэм сталкерит за Томми тут
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
								PRINT_STRING_IN_STRING("string", "HEY", 5000, 1);//~COL_NET_12~Don't go solo, keep your posse together!
							}
						}
					}
				}
				// зачищаем скрипт
				WAIT( 100 );
				REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(card_ico);//Удаляем иконку на радаре
				REMOVE_PICKUP(aid_1);
				REMOVE_PICKUP(card);
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

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(vorotaM);//выгружаем модель

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

				DELETE_OBJECT(&vorota);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&vorota);

				// выгружаем из памяти транспорт
				if (del_car == 0)
				{
					MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
					MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				}
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
					PRINT_HELP("CLOTH6"); //Cop outfit delivered to Police Station on Washington Beach.
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_BANK_1" );//No Escape?
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(1000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +1000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 1000);
					G_CLUB = 3;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== The Shootist ======================================
		else if ((G_ONMISSION == 0) && (G_CLUB == 3))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(896.966, 472.341, 5.394, &malibu_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(malibu_ico, BLIP_CLUB);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(malibu_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "LG_10");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 896.966, 472.341, 5.394, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 896.966, 472.341, 5.394, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("BANK_2", 15000, CUTSCENE_BANKJOB);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(512.591, -74.900, 9.573, 189.24);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
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
				SET_CHAR_COORDINATES(GetPlayerPed(), 898.68, 474.04, 6.45);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 90.0);
				MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 1 );
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "BANK_2A", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("bank_2a");
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

				MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 0 );
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				Cam camera;
				Ped ped1;
				Object frame1, frame2, frame3, head1, head2, head3, shoulder_R1, shoulder_R2, shoulder_R3, shoulder_L1, shoulder_L2, shoulder_L3, torso_R1, torso_R2, torso_R3, torso_L1, torso_L2, torso_L3;

				Weapon pWeapon, MaxAmmo;
				Texture fon, tar;

				uint Weap1, Ammo1_1, Ammo1_2;
				uint Weap2, Ammo2_1, Ammo2_2;
				uint Weap3, Ammo3_1, Ammo3_2;
				uint Weap4, Ammo4_1, Ammo4_2;
				uint Weap5, Ammo5_1, Ammo5_2;
				uint Weap6, Ammo6_1, Ammo6_2;
				uint Weap7, Ammo7_1, Ammo7_2;
				uint Weap8, Ammo8_1, Ammo8_2;
				uint Weap9, Ammo9_1, Ammo9_2;
				uint Weap0, Ammo0_1, Ammo0_2;
				uint AudID;

				uint PedM1 = MODEL_IG_BRUCIE;// Фил
				uint frameM = tar_frame;// Рамка
				uint headM = tar_top;// Голова
				uint shoulderMR = tar_upright;// Правое плечо
				uint shoulderML = tar_upleft;// Левое плечо
				uint torsoMR = tar_downright;// Правый торс
				uint torsoML = tar_downleft;// Левый торс

				uint targM1 = tar_civ1;// мишень 1
				uint targM2 = tar_civ2;// мишень 2
				uint targM3 = tar_gun1;// мишень 3
				uint targM4 = tar_gun2;// мишень 4

				textur1 = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur1, "fon_hud" );
				tar = GET_TEXTURE( textur1, "tar_hud" );

				skip = 0;
				round_skip = 0;
				siren = 0;
				fix_1_1 = 0;
				fix_1_2 = 0;
				fix_1_3 = 0;
				fix_1_4 = 0;
				fix_1_5 = 0;

				fix_2_1 = 0;
				fix_2_2 = 0;
				fix_2_3 = 0;
				fix_2_4 = 0;
				fix_2_5 = 0;

				fix_3_1 = 0;
				fix_3_2 = 0;
				fix_3_3 = 0;
				fix_3_4 = 0;
				fix_3_5 = 0;

				Ramka1_y = 1780.0;
				Ramka2_y = 1780.0;
				Ramka3_y = 1780.0;
				mishen1_y = 0;
				mishen2_y = 0;
				mishen3_y = 0;
				mishen4_y = 0;
				mishen5_y = 0;
				mishen6_y = 0;

				Ramka1_LR = 0;
				Ramka2_LR = 0;
				Ramka3_LR = 0;

				score1 = 0;
				score2 = 0;
				score3 = 0;
				score_all = 0;
				sound = 0;
				audio = 0;
				time_m = 2;
				time_s = 0;

				ADD_BLIP_FOR_COORD(-234.946, 1744.91, 4.99193, &malibu_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_POINT");//иконка на радаре называние в истории карты ""

				PRINT_STRING_IN_STRING("string", "BJM2_1", 5000, 1);//~g~Go to Ammu-Nation in Downtown and talk to Phil Cassidy.

				// грузим модели
				REQUEST_MODEL(PedM1);// Фил
				while (!HAS_MODEL_LOADED(PedM1)) WAIT(0);

				REQUEST_MODEL(frameM);// 
				while (!HAS_MODEL_LOADED(frameM)) WAIT(0);
				
				REQUEST_MODEL(headM);// 
				while (!HAS_MODEL_LOADED(headM)) WAIT(0);
				REQUEST_MODEL(shoulderMR);// 
				while (!HAS_MODEL_LOADED(shoulderMR)) WAIT(0);
				REQUEST_MODEL(shoulderML);// 
				while (!HAS_MODEL_LOADED(shoulderML)) WAIT(0);
				REQUEST_MODEL(torsoMR);// 
				while (!HAS_MODEL_LOADED(torsoMR)) WAIT(0);
				REQUEST_MODEL(torsoML);// 
				while (!HAS_MODEL_LOADED(torsoML)) WAIT(0);

				REQUEST_MODEL(targM1);// 
				while (!HAS_MODEL_LOADED(targM1)) WAIT(0);
				REQUEST_MODEL(targM2);// 
				while (!HAS_MODEL_LOADED(targM2)) WAIT(0);
				REQUEST_MODEL(targM3);// 
				while (!HAS_MODEL_LOADED(targM3)) WAIT(0);
				REQUEST_MODEL(targM4);// 
				while (!HAS_MODEL_LOADED(targM4)) WAIT(0);

				CREATE_CHAR (26, PedM1, -233.262, 1767.24, 5.22361, &ped1, TRUE);// Фил
				SET_CHAR_COMPONENT_VARIATION(ped1, 1, 0, 0);
				SET_CHAR_HEADING(ped1, 90.0);
				SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);

				CREATE_OBJECT_NO_OFFSET(frameM, -240.0, 1780.0, 7.5, &frame1, TRUE);
				CREATE_OBJECT_NO_OFFSET(frameM, -240.0, 1780.0, 7.5, &frame2, TRUE);
				CREATE_OBJECT_NO_OFFSET(frameM, -240.0, 1780.0, 7.5, &frame3, TRUE);
				CREATE_OBJECT_NO_OFFSET(headM, -240.0, 1780.0, 7.5, &head1, TRUE);
				CREATE_OBJECT_NO_OFFSET(headM, -240.0, 1780.0, 7.5, &head2, TRUE);
				CREATE_OBJECT_NO_OFFSET(headM, -240.0, 1780.0, 7.5, &head3, TRUE);
				CREATE_OBJECT_NO_OFFSET(shoulderMR, -240.0, 1780.0, 7.5, &shoulder_R1, TRUE);
				CREATE_OBJECT_NO_OFFSET(shoulderMR, -240.0, 1780.0, 7.5, &shoulder_R2, TRUE);
				CREATE_OBJECT_NO_OFFSET(shoulderMR, -240.0, 1780.0, 7.5, &shoulder_R3, TRUE);
				CREATE_OBJECT_NO_OFFSET(shoulderML, -240.0, 1780.0, 7.5, &shoulder_L1, TRUE);
				CREATE_OBJECT_NO_OFFSET(shoulderML, -240.0, 1780.0, 7.5, &shoulder_L2, TRUE);
				CREATE_OBJECT_NO_OFFSET(shoulderML, -240.0, 1780.0, 7.5, &shoulder_L3, TRUE);
				CREATE_OBJECT_NO_OFFSET(torsoMR, -240.0, 1780.0, 7.5, &torso_R1, TRUE);
				CREATE_OBJECT_NO_OFFSET(torsoMR, -240.0, 1780.0, 7.5, &torso_R2, TRUE);
				CREATE_OBJECT_NO_OFFSET(torsoMR, -240.0, 1780.0, 7.5, &torso_R3, TRUE);
				CREATE_OBJECT_NO_OFFSET(torsoML, -240.0, 1780.0, 7.5, &torso_L1, TRUE);
				CREATE_OBJECT_NO_OFFSET(torsoML, -240.0, 1780.0, 7.5, &torso_L2, TRUE);
				CREATE_OBJECT_NO_OFFSET(torsoML, -240.0, 1780.0, 7.5, &torso_L3, TRUE);

				SET_OBJECT_DYNAMIC(frame1, 0);
				SET_OBJECT_DYNAMIC(frame2, 0);
				SET_OBJECT_DYNAMIC(frame3, 0);

				SET_OBJECT_INVINCIBLE(frame1, 1);
				SET_OBJECT_INVINCIBLE(frame2, 1);
				SET_OBJECT_INVINCIBLE(frame3, 1);

				FREEZE_OBJECT_POSITION(frame1, 1);
				FREEZE_OBJECT_POSITION(frame2, 1);
				FREEZE_OBJECT_POSITION(frame3, 1);
				

				while (TRUE)
				{
					WAIT(0);
					DRAW_CHECKPOINT( -234.946, 1744.91, 4.99193, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -234.946, 1744.91, 4.99193, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
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

						SET_OBJECT_HEADING( frame1, 90.0 );
						SET_OBJECT_HEADING( frame2, 90.0 );
						SET_OBJECT_HEADING( frame3, 90.0 );
						SET_OBJECT_HEADING( head1, 90.0 );
						SET_OBJECT_HEADING( head2, 90.0 );
						SET_OBJECT_HEADING( head3, 90.0 );
						SET_OBJECT_HEADING( shoulder_R1, 90.0 );
						SET_OBJECT_HEADING( shoulder_R2, 90.0 );
						SET_OBJECT_HEADING( shoulder_R3, 90.0 );
						SET_OBJECT_HEADING( shoulder_L1, 90.0 );
						SET_OBJECT_HEADING( shoulder_L2, 90.0 );
						SET_OBJECT_HEADING( shoulder_L3, 90.0 );
						SET_OBJECT_HEADING( torso_R1, 90.0 );
						SET_OBJECT_HEADING( torso_R2, 90.0 );
						SET_OBJECT_HEADING( torso_R3, 90.0 );
						SET_OBJECT_HEADING( torso_L1, 90.0 );
						SET_OBJECT_HEADING( torso_L2, 90.0 );
						SET_OBJECT_HEADING( torso_L3, 90.0 );

						SET_OBJECT_COORDINATES( frame1, -240.25, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( head1, -240.25, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( shoulder_R1, -240.25, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( shoulder_L1, -240.25, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( torso_R1, -240.25, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( torso_L1, -240.25, 1771.3, 6.5 );

						SET_OBJECT_COORDINATES( frame2, -243.15, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( head2, -243.15, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( shoulder_R2, -243.15, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( shoulder_L2, -243.15, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( torso_R2, -243.15, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( torso_L2, -243.15, 1771.3, 6.5 );

						SET_OBJECT_COORDINATES( frame3, -246, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( head3, -246, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( shoulder_R3, -246, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( shoulder_L3, -246, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( torso_R3, -246, 1771.3, 6.5 );
						SET_OBJECT_COORDINATES( torso_L3, -246, 1771.3, 6.5 );

						SET_CHAR_COORDINATES(GetPlayerPed(), -233.554, 1764.69, 5.22361);// перемещаем игрока
						SET_CHAR_HEADING(GetPlayerPed(), 90.0);

						//получить оружие
						GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 1, &Weap1, &Ammo1_1, &Ammo1_2);
						GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 2, &Weap2, &Ammo2_1, &Ammo2_2);
						GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 3, &Weap3, &Ammo3_1, &Ammo3_2);
						GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 4, &Weap4, &Ammo4_1, &Ammo4_2);
						GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 5, &Weap5, &Ammo5_1, &Ammo5_2);
						GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 6, &Weap6, &Ammo6_1, &Ammo6_2);
						GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 7, &Weap7, &Ammo7_1, &Ammo7_2);
						GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 8, &Weap8, &Ammo8_1, &Ammo8_2);
						GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 9, &Weap9, &Ammo9_1, &Ammo9_2);
						GET_CHAR_WEAPON_IN_SLOT(GetPlayerPed(), 0, &Weap0, &Ammo0_1, &Ammo0_2);
						siren = 1;
						FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
						FORWARD_TO_TIME_OF_DAY(19, 30);//устанавливаем время
						SET_PED_DENSITY_MULTIPLIER(0.0); // отключаем людской траффик
						CLEAR_AREA(-243.28, 1733.15, 4.98655, 60.0, 1);//очещаем зону загрузки

						//------------ катсцена ----------------
						LOAD_ADDITIONAL_TEXT( "BANK_2B", 6 ); // загружаем субтитры из *.GTX
						START_CUTSCENE_NOW("bank_2b");
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

						// даём пистолет
						UpdateWeaponOfPed(GetPlayerPed(), WEAPON_PISTOL);
						SET_CHAR_AMMO(GetPlayerPed(), 7, 100);

						SET_CAMERA_CONTROLS_DISABLED_WITH_PLAYER_CONTROLS( 0 );
						SET_PLAYER_FORCED_AIM( GetPlayerIndex(), 1 );

						// обяснения тут
						PRINT_STRING_IN_STRING("string", "BJM2_19", 4000, 1);//~g~Hit as many targets as you can in the time limit!
						SetTime(4000);
						PRINT_STRING_IN_STRING("string", "BJM2_20", 4000, 1);//~g~When you run out of ~w~time ~g~or ~w~ammunition ~g~the round is over!
						SetTime(4000);
						PRINT_STRING_IN_STRING("string", "BJM2_24", 4000, 1);//~g~The closest target is worth one point.
						SetTime(4000);
						PRINT_STRING_IN_STRING("string", "BJM2_25", 4000, 1);//~g~The middle target is worth two points.
						SetTime(4000);
						PRINT_STRING_IN_STRING("string", "BJM2_26", 4000, 1);//~g~The far target is worth three points.
						SetTime(4000);
						PRINT_STRING_IN_STRING("string", "BJM2_2", 4000, 1);//~g~To exit the round press the ~h~~INPUT_PHONE_CANCEL~ ~g~button.
						SetTime(4000);
						PRINT_STRING_IN_STRING("string", "BJM2_23", 4000, 1);//~g~If you leave the shooting range during the competition, you will fail the mission.
						SetTime(4000);

						// Пригодная амуниция
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R8_BA", "BNK2_1", 0, 0);//LIVE AMMUNITION
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();
						CLEAR_PRINTS();

						// Целься 3...2...1...Огонь!
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R8_BB", "BNK2_2", 0, 0);//AIM 3-2-1 FIRE!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();
						CLEAR_PRINTS();

						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
						SET_MAX_WANTED_LEVEL(0);

						
						FREEZE_CHAR_POSITION(GetPlayerPed(), 1);

						// воспроизводим звук
						while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_AMBIENT/TOLLBOOTH" )))
						{
							 WAIT(0);
						}
						AudID = GET_SOUND_ID();
						PLAY_SOUND_FROM_POSITION(AudID, "SCRIPT_AMBIENT_TOLLBOOTH_ARM_LOOP", -237.876, 1765.32, 8.27772);
						audio = 1;
						SETTIMERB( 0 );
						break;
					}

					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "BJM2_11", 5000, 1);//~r~Phil's dead!
						skip = 1;// переменная пропуска
						break;
					}
				}
				// мишени 1
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						//============================ HUD ============================
						// таймер тут
						if (TIMERB() > 999)
						{
							time_s -= 1;
							SETTIMERB( 0 );
						}

						if (time_s < 0)
						{
							time_m -= 1;
							time_s = 59;
						}

						// таймер
						DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78305097, 0.77731852, "RACES"); //TIME:

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


						// счётчик 
						DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );
						DRAW_SPRITE( tar, 0.8270625, 0.74213, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.
						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78305097, 0.73564852, "BJM2_18"); //SCORE TO BEAT:

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						if ( score_all > 9 )
						{
							if ( score_all > 99 )
							{
								DISPLAY_TEXT_WITH_NUMBER(0.9083334, 0.72787074, "CP_TIME_NOZERO", score_all);// 
							}
							else
							{
								DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.72787074, "CP_TIME_NOZERO", score_all);// 
							}
						}
						else
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.72787074, "CP_TIME_ZERO", score_all);// 
						}
						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT_WITH_NUMBER(0.9203125, 0.72787074, "OUTOF_NUM", 60);// 

						if (sound == 0)
						{
							if ((time_m == 0) && (time_s < 59))
							{
								if (score_all >= 20)
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R8_FA", "BNK2_4", 0, 0);//Hoooeee!
									START_SCRIPT_CONVERSATION(1, 1);
									sound = 1;
								}
								else if (score_all < 20)
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R8_GA", "BNK2_5", 0, 0);//Couldn't hit a barn door!
									START_SCRIPT_CONVERSATION(1, 1);
									sound = 1;
								}
							}
						}
						else if (sound == 1)
						{
							if ((time_m == 0) && (time_s < 29) && (score_all >= 35))
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R8_HA", "NEBNK2_L", 0, 0);//This guy is a lunatic.
								START_SCRIPT_CONVERSATION(1, 1);
								sound = 2;
							}
						}
						
						// Движение мишений
						if (Ramka1_LR == 0)
						{
							if ((fix_1_1 == 1) && (fix_1_2 == 1) && (fix_1_3 == 1) && (fix_1_4 == 1) && (fix_1_5 == 1))
							{
								Ramka1_y = Ramka1_y-0.09;
							}
							else
							{
								Ramka1_y = Ramka1_y-0.03;
							}
						}
						else if (Ramka1_LR == 1)
						{
							if ((fix_1_1 == 1) && (fix_1_2 == 1) && (fix_1_3 == 1) && (fix_1_4 == 1) && (fix_1_5 == 1))
							{
								Ramka1_y = Ramka1_y+0.09;
							}
							else
							{
								Ramka1_y = Ramka1_y+0.03;
							}
						}

						if (Ramka2_LR == 0)
						{
							if ((fix_2_1 == 1) && (fix_2_2 == 1) && (fix_2_3 == 1) && (fix_2_4 == 1) && (fix_2_5 == 1))
							{
								Ramka2_y = Ramka2_y-0.09;
							}
							else
							{
								Ramka2_y = Ramka2_y-0.05;
							}
						}
						else if (Ramka2_LR == 1)
						{
							if ((fix_2_1 == 1) && (fix_2_2 == 1) && (fix_2_3 == 1) && (fix_2_4 == 1) && (fix_2_5 == 1))
							{
								Ramka2_y = Ramka2_y+0.09;
							}
							else
							{
								Ramka2_y = Ramka2_y+0.05;
							}
						}

						if (Ramka3_LR == 0)
						{
							if ((fix_3_1 == 1) && (fix_3_2 == 1) && (fix_3_3 == 1) && (fix_3_4 == 1) && (fix_3_5 == 1))
							{
								Ramka3_y = Ramka3_y-0.09;
							}
							else
							{
								Ramka3_y = Ramka3_y-0.075;
							}
						}
						else if (Ramka3_LR == 1)
						{
							if ((fix_3_1 == 1) && (fix_3_2 == 1) && (fix_3_3 == 1) && (fix_3_4 == 1) && (fix_3_5 == 1))
							{
								Ramka3_y = Ramka3_y+0.09;
							}
							else
							{
								Ramka3_y = Ramka3_y+0.075;
							}
						}

						SET_OBJECT_COORDINATES( frame1, -240.25, Ramka1_y, 6.5 );
						SET_OBJECT_COORDINATES( head1, -240.25, Ramka1_y, 6.5 );
						SET_OBJECT_COORDINATES( shoulder_R1, -240.25, Ramka1_y, 6.5 );
						SET_OBJECT_COORDINATES( shoulder_L1, -240.25, Ramka1_y, 6.5 );
						SET_OBJECT_COORDINATES( torso_R1, -240.25, Ramka1_y, 6.5 );
						SET_OBJECT_COORDINATES( torso_L1, -240.25, Ramka1_y, 6.5 );

						SET_OBJECT_COORDINATES( frame2, -243.15, Ramka2_y, 6.5 );
						SET_OBJECT_COORDINATES( head2, -243.15, Ramka2_y, 6.5 );
						SET_OBJECT_COORDINATES( shoulder_R2, -243.15, Ramka2_y, 6.5 );
						SET_OBJECT_COORDINATES( shoulder_L2, -243.15, Ramka2_y, 6.5 );
						SET_OBJECT_COORDINATES( torso_R2, -243.15, Ramka2_y, 6.5 );
						SET_OBJECT_COORDINATES( torso_L2, -243.15, Ramka2_y, 6.5 );

						SET_OBJECT_COORDINATES( frame3, -246, Ramka3_y, 6.5 );
						SET_OBJECT_COORDINATES( head3, -246, Ramka3_y, 6.5 );
						SET_OBJECT_COORDINATES( shoulder_R3, -246, Ramka3_y, 6.5 );
						SET_OBJECT_COORDINATES( shoulder_L3, -246, Ramka3_y, 6.5 );
						SET_OBJECT_COORDINATES( torso_R3, -246, Ramka3_y, 6.5 );
						SET_OBJECT_COORDINATES( torso_L3, -246, Ramka3_y, 6.5 );

						// Реверс мишений и фикс моделей
						if (Ramka1_y < 1759.7)
						{
							if ((fix_1_1 == 1) && (fix_1_2 == 1) && (fix_1_3 == 1) && (fix_1_4 == 1) && (fix_1_5 == 1))
							{
								DELETE_OBJECT(&head1);
								DELETE_OBJECT(&shoulder_R1);
								DELETE_OBJECT(&shoulder_L1);
								DELETE_OBJECT(&torso_R1);
								DELETE_OBJECT(&torso_L1);
								
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&head1);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_R1);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_L1);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R1);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L1);

								CREATE_OBJECT_NO_OFFSET(headM, -240.0, 1780.0, 7.5, &head1, TRUE);
								CREATE_OBJECT_NO_OFFSET(shoulderMR, -240.0, 1780.0, 7.5, &shoulder_R1, TRUE);
								CREATE_OBJECT_NO_OFFSET(shoulderML, -240.0, 1780.0, 7.5, &shoulder_L1, TRUE);
								CREATE_OBJECT_NO_OFFSET(torsoMR, -240.0, 1780.0, 7.5, &torso_R1, TRUE);
								CREATE_OBJECT_NO_OFFSET(torsoML, -240.0, 1780.0, 7.5, &torso_L1, TRUE);

								SET_OBJECT_HEADING( head1, 90.0 );
								SET_OBJECT_HEADING( shoulder_R1, 90.0 );
								SET_OBJECT_HEADING( shoulder_L1, 90.0 );
								SET_OBJECT_HEADING( torso_R1, 90.0 );
								SET_OBJECT_HEADING( torso_L1, 90.0 );

								fix_1_1 = 0;
								fix_1_2 = 0;
								fix_1_3 = 0;
								fix_1_4 = 0;
								fix_1_5 = 0;
							}
							if (Ramka1_LR == 0)
							{
								Ramka1_LR = 1;
							}
						}
						else if (Ramka1_y > 1771.3)
						{
							if ((fix_1_1 == 1) && (fix_1_2 == 1) && (fix_1_3 == 1) && (fix_1_4 == 1) && (fix_1_5 == 1))
							{
								DELETE_OBJECT(&head1);
								DELETE_OBJECT(&shoulder_R1);
								DELETE_OBJECT(&shoulder_L1);
								DELETE_OBJECT(&torso_R1);
								DELETE_OBJECT(&torso_L1);
								
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&head1);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_R1);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_L1);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R1);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L1);

								CREATE_OBJECT_NO_OFFSET(headM, -240.0, 1780.0, 7.5, &head1, TRUE);
								CREATE_OBJECT_NO_OFFSET(shoulderMR, -240.0, 1780.0, 7.5, &shoulder_R1, TRUE);
								CREATE_OBJECT_NO_OFFSET(shoulderML, -240.0, 1780.0, 7.5, &shoulder_L1, TRUE);
								CREATE_OBJECT_NO_OFFSET(torsoMR, -240.0, 1780.0, 7.5, &torso_R1, TRUE);
								CREATE_OBJECT_NO_OFFSET(torsoML, -240.0, 1780.0, 7.5, &torso_L1, TRUE);

								SET_OBJECT_HEADING( head1, 90.0 );
								SET_OBJECT_HEADING( shoulder_R1, 90.0 );
								SET_OBJECT_HEADING( shoulder_L1, 90.0 );
								SET_OBJECT_HEADING( torso_R1, 90.0 );
								SET_OBJECT_HEADING( torso_L1, 90.0 );

								fix_1_1 = 0;
								fix_1_2 = 0;
								fix_1_3 = 0;
								fix_1_4 = 0;
								fix_1_5 = 0;
							}
							if (Ramka1_LR == 1)
							{
								Ramka1_LR = 0;
							}
						}

						if (Ramka2_y < 1759.7)
						{
							if ((fix_2_1 == 1) && (fix_2_2 == 1) && (fix_2_3 == 1) && (fix_2_4 == 1) && (fix_2_5 == 1))
							{
								DELETE_OBJECT(&head2);
								DELETE_OBJECT(&shoulder_R2);
								DELETE_OBJECT(&shoulder_L2);
								DELETE_OBJECT(&torso_R2);
								DELETE_OBJECT(&torso_L2);
								
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&head2);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_R2);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_L2);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R2);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L2);

								CREATE_OBJECT_NO_OFFSET(headM, -240.0, 1780.0, 7.5, &head2, TRUE);
								CREATE_OBJECT_NO_OFFSET(shoulderMR, -240.0, 1780.0, 7.5, &shoulder_R2, TRUE);
								CREATE_OBJECT_NO_OFFSET(shoulderML, -240.0, 1780.0, 7.5, &shoulder_L2, TRUE);
								CREATE_OBJECT_NO_OFFSET(torsoMR, -240.0, 1780.0, 7.5, &torso_R2, TRUE);
								CREATE_OBJECT_NO_OFFSET(torsoML, -240.0, 1780.0, 7.5, &torso_L2, TRUE);

								SET_OBJECT_HEADING( head2, 90.0 );
								SET_OBJECT_HEADING( shoulder_R2, 90.0 );
								SET_OBJECT_HEADING( shoulder_L2, 90.0 );
								SET_OBJECT_HEADING( torso_R2, 90.0 );
								SET_OBJECT_HEADING( torso_L2, 90.0 );

								fix_2_1 = 0;
								fix_2_2 = 0;
								fix_2_3 = 0;
								fix_2_4 = 0;
								fix_2_5 = 0;
							}
							if (Ramka2_LR == 0)
							{
								Ramka2_LR = 1;
							}
						}
						else if (Ramka2_y > 1771.3)
						{
							if ((fix_2_1 == 1) && (fix_2_2 == 1) && (fix_2_3 == 1) && (fix_2_4 == 1) && (fix_2_5 == 1))
							{
								DELETE_OBJECT(&head2);
								DELETE_OBJECT(&shoulder_R2);
								DELETE_OBJECT(&shoulder_L2);
								DELETE_OBJECT(&torso_R2);
								DELETE_OBJECT(&torso_L2);
								
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&head2);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_R2);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_L2);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R2);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L2);

								CREATE_OBJECT_NO_OFFSET(headM, -240.0, 1780.0, 7.5, &head2, TRUE);
								CREATE_OBJECT_NO_OFFSET(shoulderMR, -240.0, 1780.0, 7.5, &shoulder_R2, TRUE);
								CREATE_OBJECT_NO_OFFSET(shoulderML, -240.0, 1780.0, 7.5, &shoulder_L2, TRUE);
								CREATE_OBJECT_NO_OFFSET(torsoMR, -240.0, 1780.0, 7.5, &torso_R2, TRUE);
								CREATE_OBJECT_NO_OFFSET(torsoML, -240.0, 1780.0, 7.5, &torso_L2, TRUE);

								SET_OBJECT_HEADING( head2, 90.0 );
								SET_OBJECT_HEADING( shoulder_R2, 90.0 );
								SET_OBJECT_HEADING( shoulder_L2, 90.0 );
								SET_OBJECT_HEADING( torso_R2, 90.0 );
								SET_OBJECT_HEADING( torso_L2, 90.0 );

								fix_2_1 = 0;
								fix_2_2 = 0;
								fix_2_3 = 0;
								fix_2_4 = 0;
								fix_2_5 = 0;
							}
							if (Ramka2_LR == 1)
							{
								Ramka2_LR = 0;
							}
						}

						if (Ramka3_y < 1759.7)
						{
							if ((fix_3_1 == 1) && (fix_3_2 == 1) && (fix_3_3 == 1) && (fix_3_4 == 1) && (fix_3_5 == 1))
							{
								DELETE_OBJECT(&head3);
								DELETE_OBJECT(&shoulder_R3);
								DELETE_OBJECT(&shoulder_L3);
								DELETE_OBJECT(&torso_R3);
								DELETE_OBJECT(&torso_L3);
								
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&head3);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_R3);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_L3);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R3);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L3);

								CREATE_OBJECT_NO_OFFSET(headM, -240.0, 1780.0, 7.5, &head3, TRUE);
								CREATE_OBJECT_NO_OFFSET(shoulderMR, -240.0, 1780.0, 7.5, &shoulder_R3, TRUE);
								CREATE_OBJECT_NO_OFFSET(shoulderML, -240.0, 1780.0, 7.5, &shoulder_L3, TRUE);
								CREATE_OBJECT_NO_OFFSET(torsoMR, -240.0, 1780.0, 7.5, &torso_R3, TRUE);
								CREATE_OBJECT_NO_OFFSET(torsoML, -240.0, 1780.0, 7.5, &torso_L3, TRUE);

								SET_OBJECT_HEADING( head3, 90.0 );
								SET_OBJECT_HEADING( shoulder_R3, 90.0 );
								SET_OBJECT_HEADING( shoulder_L3, 90.0 );
								SET_OBJECT_HEADING( torso_R3, 90.0 );
								SET_OBJECT_HEADING( torso_L3, 90.0 );

								fix_3_1 = 0;
								fix_3_2 = 0;
								fix_3_3 = 0;
								fix_3_4 = 0;
								fix_3_5 = 0;
							}
							if (Ramka3_LR == 0)
							{
								Ramka3_LR = 1;
							}
						}
						else if (Ramka3_y > 1771.3)
						{
							if ((fix_3_1 == 1) && (fix_3_2 == 1) && (fix_3_3 == 1) && (fix_3_4 == 1) && (fix_3_5 == 1))
							{
								DELETE_OBJECT(&head3);
								DELETE_OBJECT(&shoulder_R3);
								DELETE_OBJECT(&shoulder_L3);
								DELETE_OBJECT(&torso_R3);
								DELETE_OBJECT(&torso_L3);
								
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&head3);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_R3);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_L3);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R3);
								MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L3);

								CREATE_OBJECT_NO_OFFSET(headM, -240.0, 1780.0, 7.5, &head3, TRUE);
								CREATE_OBJECT_NO_OFFSET(shoulderMR, -240.0, 1780.0, 7.5, &shoulder_R3, TRUE);
								CREATE_OBJECT_NO_OFFSET(shoulderML, -240.0, 1780.0, 7.5, &shoulder_L3, TRUE);
								CREATE_OBJECT_NO_OFFSET(torsoMR, -240.0, 1780.0, 7.5, &torso_R3, TRUE);
								CREATE_OBJECT_NO_OFFSET(torsoML, -240.0, 1780.0, 7.5, &torso_L3, TRUE);

								SET_OBJECT_HEADING( head3, 90.0 );
								SET_OBJECT_HEADING( shoulder_R3, 90.0 );
								SET_OBJECT_HEADING( shoulder_L3, 90.0 );
								SET_OBJECT_HEADING( torso_R3, 90.0 );
								SET_OBJECT_HEADING( torso_L3, 90.0 );

								fix_3_1 = 0;
								fix_3_2 = 0;
								fix_3_3 = 0;
								fix_3_4 = 0;
								fix_3_5 = 0;
							}
							if (Ramka3_LR == 1)
							{
								Ramka3_LR = 0;
							}
						}
						// получаем повреждения тут
						GET_OBJECT_HEALTH(head1, &Heal_1_1);
						GET_OBJECT_HEALTH(shoulder_R1, &Heal_1_2);
						GET_OBJECT_HEALTH(shoulder_L1, &Heal_1_3);
						GET_OBJECT_HEALTH(torso_R1, &Heal_1_4);
						GET_OBJECT_HEALTH(torso_L1, &Heal_1_5);

						GET_OBJECT_HEALTH(head2, &Heal_2_1);
						GET_OBJECT_HEALTH(shoulder_R2, &Heal_2_2);
						GET_OBJECT_HEALTH(shoulder_L2, &Heal_2_3);
						GET_OBJECT_HEALTH(torso_R2, &Heal_2_4);
						GET_OBJECT_HEALTH(torso_L2, &Heal_2_5);

						GET_OBJECT_HEALTH(head3, &Heal_3_1);
						GET_OBJECT_HEALTH(shoulder_R3, &Heal_3_2);
						GET_OBJECT_HEALTH(shoulder_L3, &Heal_3_3);
						GET_OBJECT_HEALTH(torso_R3, &Heal_3_4);
						GET_OBJECT_HEALTH(torso_L3, &Heal_3_5);

						if (score1 == 5)
						{
							score1 = 0;
							score_all += 1;
						}
						if (score2 == 5)
						{
							score2 = 0;
							score_all += 2;
						}
						if (score3 == 5)
						{
							score3 = 0;
							score_all += 3;
						}

						if ((Heal_1_1 < 995) && (fix_1_1 == 0))
						{
							score1 += 1;
							fix_1_1 = 1;
						}
						if ((Heal_1_2 < 995) && (fix_1_2 == 0))
						{
							score1 += 1;
							fix_1_2 = 1;
						}
						if ((Heal_1_3 < 995) && (fix_1_3 == 0))
						{
							score1 += 1;
							fix_1_3 = 1;
						}
						if ((Heal_1_4 < 995) && (fix_1_4 == 0))
						{
							score1 += 1;
							fix_1_4 = 1;
						}
						if ((Heal_1_5 < 995) && (fix_1_5 == 0))
						{
							score1 += 1;
							fix_1_5 = 1;
						}

						if ((Heal_2_1 < 995) && (fix_2_1 == 0))
						{
							score2 += 1;
							fix_2_1 = 1;
						}
						if ((Heal_2_2 < 995) && (fix_2_2 == 0))
						{
							score2 += 1;
							fix_2_2 = 1;
						}
						if ((Heal_2_3 < 995) && (fix_2_3 == 0))
						{
							score2 += 1;
							fix_2_3 = 1;
						}
						if ((Heal_2_4 < 995) && (fix_2_4 == 0))
						{
							score2 += 1;
							fix_2_4 = 1;
						}
						if ((Heal_2_5 < 995) && (fix_2_5 == 0))
						{
							score2 += 1;
							fix_2_5 = 1;
						}

						if ((Heal_3_1 < 995) && (fix_3_1 == 0))
						{
							score3 += 1;
							fix_3_1 = 1;
						}
						if ((Heal_3_2 < 995) && (fix_3_2 == 0))
						{
							score3 += 1;
							fix_3_2 = 1;
						}
						if ((Heal_3_3 < 995) && (fix_3_3 == 0))
						{
							score3 += 1;
							fix_3_3 = 1;
						}
						if ((Heal_3_4 < 995) && (fix_3_4 == 0))
						{
							score3 += 1;
							fix_3_4 = 1;
						}
						if ((Heal_3_5 < 995) && (fix_3_5 == 0))
						{
							score3 += 1;
							fix_3_5 = 1;
						}

						GET_CURRENT_CHAR_WEAPON(GetPlayerPed(), &pWeapon);//!!!___2(вписываем в переменную "pWeapon" оружие в руках игрока) 
						GET_AMMO_IN_CHAR_WEAPON(GetPlayerPed(), pWeapon, &MaxAmmo);

						// проверка количества поторонов тут
						if (((time_m == 0) && (time_s < 1)) || (MaxAmmo < 1) || (round_skip > 0))
						{
							CLEAR_PRINTS();
							SET_PLAYER_FORCED_AIM( GetPlayerIndex(), 0 );
							FREEZE_CHAR_POSITION(GetPlayerPed(), 0);
							REMOVE_ALL_CHAR_WEAPONS(GetPlayerPed());

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R8_IA", "BNK2_3", 0, 0);// AREA CLEAR!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							

							ADD_BLIP_FOR_COORD(-236.702, 1803.67, 4.99193, &malibu_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_POINT");//иконка на радаре называние в истории карты ""

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM2_9", 5000, 1);//~g~Get to round two's starting point.

							STOP_SOUND(AudID);
							RELEASE_SOUND_ID(AudID);
							AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED();
							audio = 0;
							round_skip = 0;
							SETTIMERA(0); //сбрасываем таймер 
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM2_11", 5000, 1);//~r~Phil's dead!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_BUTTON_PRESSED( 0, 17 )) || ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER()))) // BACKSPACE
						{
							CLEAR_PRINTS();

							round_skip = 1;

						}
					}
				}
				// Пойнт 2
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						if ( TIMERA() < 4000 )
						{
							SET_TEXT_COLOUR(255, 159, 255, 255); // задаём цвет текста
							SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
							SET_TEXT_EDGE(1, 0, 0, 0, 255); //
							SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
							SET_TEXT_CENTRE(1); // задаём центр текста
							DISPLAY_TEXT(0.5, 0.45, "BJM2_7");//TOTAL SCORE FOR SHOOT:

							SET_TEXT_COLOUR(255, 159, 255, 255); // задаём цвет текста
							SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
							SET_TEXT_EDGE(1, 0, 0, 0, 255); //
							SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
							SET_TEXT_CENTRE(1); // задаём центр текста
							DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", score_all);//
						}

						DRAW_CHECKPOINT( -236.702, 1803.67, 4.99193, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -236.702, 1803.67, 4.99193, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							// обучение тут
							SET_OBJECT_COORDINATES( frame1, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( head1, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( shoulder_R1, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( shoulder_L1, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_R1, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_L1, -238.229, 1782.66, 7.31169 );

							SET_OBJECT_COORDINATES( frame2, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( head2, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( shoulder_R2, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( shoulder_L2, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_R2, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_L2, -238.229, 1782.66, 7.31169 );

							SET_OBJECT_COORDINATES( frame3, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( head3, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( shoulder_R3, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( shoulder_L3, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_R3, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_L3, -238.229, 1782.66, 7.31169 );

							DELETE_OBJECT(&torso_R1);
							DELETE_OBJECT(&torso_R2);
							DELETE_OBJECT(&torso_R3);
							DELETE_OBJECT(&torso_L1);
							DELETE_OBJECT(&torso_L2);
							DELETE_OBJECT(&torso_L3);
							
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R1);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R2);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R3);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L1);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L2);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L3);

							CREATE_OBJECT_NO_OFFSET(tar_civ1, -249.822, 1801.39, 4.82258, &torso_R1, TRUE);
							CREATE_OBJECT_NO_OFFSET(tar_civ2, -249.822, 1805.23, 4.82258, &torso_R2, TRUE);
							CREATE_OBJECT_NO_OFFSET(tar_gun1, -249.822, 1811.41, 4.82258, &torso_R3, TRUE);
							CREATE_OBJECT_NO_OFFSET(tar_gun1, -253.327, 1806.63, 7.29204, &torso_L1, TRUE);
							CREATE_OBJECT_NO_OFFSET(tar_civ1, -253.971, 1810.34, 7.29204, &torso_L2, TRUE);
							CREATE_OBJECT_NO_OFFSET(tar_civ2, -249.822, 1811.71, 7.29204, &torso_L3, TRUE);

							SET_OBJECT_HEADING( torso_R1, -90.0 );
							SET_OBJECT_HEADING( torso_R2, -90.0 );
							SET_OBJECT_HEADING( torso_R3, -90.0 );
							SET_OBJECT_HEADING( torso_L1, -90.0 );
							SET_OBJECT_HEADING( torso_L2, -90.0 );
							SET_OBJECT_HEADING( torso_L3, -90.0 );

							mishen1_y = 1801.39;
							mishen2_y = 1805.23;
							mishen3_y = 1811.41;
							mishen4_y = 1802.74;
							mishen5_y = 1807.96;
							mishen6_y = 1811.71;

							mishen1_x = -249.822;
							mishen2_x = -249.822;
							mishen3_x = -249.822;
							mishen4_x = -249.822;
							mishen5_x = -249.822;
							mishen6_x = -249.822;

							Ramka1_LR = 1;
							Ramka2_LR = 1;
							Ramka3_LR = 0;
							Ramka4_LR = 0;
							Ramka5_LR = 0;
							Ramka6_LR = 1;

							WAIT(100);
							UpdateWeaponOfPed(GetPlayerPed(), WEAPON_PISTOL);
							SET_CHAR_AMMO(GetPlayerPed(), 7, 50);

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							SET_CAMERA_CONTROLS_DISABLED_WITH_PLAYER_CONTROLS( 0 );
							SET_PLAYER_FORCED_AIM( GetPlayerIndex(), 1 );

							SET_CHAR_COORDINATES(GetPlayerPed(), -236.702, 1803.67, 4.99193);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 90.0);
							REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре

							// обяснения тут
							PRINT_STRING_IN_STRING("string", "BJM2_19", 5000, 1);//~g~Hit as many targets as you can in the time limit!
							SetTime(5000);
							PRINT_STRING_IN_STRING("string", "BJM2_20", 5000, 1);//~g~When you run out of ~w~time ~g~or ~w~ammunition ~g~the round is over!
							SetTime(5000);
							PRINT_STRING_IN_STRING("string", "BJM2_27", 5000, 1);//~g~All targets this round are worth one point.
							SetTime(5000);
							CLEAR_PRINTS();

							// Целься 3...2...1...Огонь!
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R8_BB", "BNK2_2", 0, 0);//AIM 3-2-1 FIRE!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							FREEZE_CHAR_POSITION(GetPlayerPed(), 1);
							SETTIMERB( 0 );

							// воспроизводим звук
							while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_AMBIENT/TOLLBOOTH" )))
							{
								 WAIT(0);
							}
							AudID = GET_SOUND_ID();
							PLAY_SOUND_FROM_POSITION(AudID, "SCRIPT_AMBIENT_TOLLBOOTH_ARM_LOOP", -241.138, 1803.92, 8.27772);
							audio = 1;
							time_m = 1;
							time_s = 0;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM2_11", 5000, 1);//~r~Phil's dead!
							skip = 1;// переменная пропуска
							break;
						}
						else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -207.201, 1744.357, 1.895, -263.896, 1835.861, 24.875, 0 ))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM2_22", 5000, 1);//~r~You have left the shooting range!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// мишени 2
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						//============================ HUD ============================
						// таймер тут
						if (TIMERB() > 999)
						{
							time_s -= 1;
							SETTIMERB( 0 );
						}

						if (time_s < 0)
						{
							time_m -= 1;
							time_s = 59;
						}

						// таймер
						DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78305097, 0.77731852, "RACES"); //TIME:

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

						// счётчик бомб 
						DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );
						DRAW_SPRITE( tar, 0.8270625, 0.74213, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.
						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78305097, 0.73564852, "BJM2_18"); //SCORE TO BEAT:

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						if ( score_all > 9 )
						{
							if ( score_all > 99 )
							{
								DISPLAY_TEXT_WITH_NUMBER(0.9083334, 0.72787074, "CP_TIME_NOZERO", score_all);// 
							}
							else
							{
								DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.72787074, "CP_TIME_NOZERO", score_all);// 
							}
						}
						else
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.72787074, "CP_TIME_ZERO", score_all);// 
						}
						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT_WITH_NUMBER(0.9203125, 0.72787074, "OUTOF_NUM", 60);// 

						// Движение мишений
						if (Ramka1_LR == 0)
						{
							mishen1_y = mishen1_y-0.03;
						}
						else if (Ramka1_LR == 1)
						{
							mishen1_y = mishen1_y+0.03;
						}

						if (Ramka2_LR == 0)
						{
							mishen2_y = mishen2_y-0.03;
						}
						else if (Ramka2_LR == 1)
						{
							mishen2_y = mishen2_y+0.03;
						}

						if (Ramka3_LR == 0)
						{
							mishen3_y = mishen3_y-0.03;
						}
						else if (Ramka3_LR == 1)
						{
							mishen3_y = mishen3_y+0.03;
						}
						if (Ramka4_LR == 0)
						{
							mishen4_y = mishen4_y-0.03;
						}
						else if (Ramka4_LR == 1)
						{
							mishen4_y = mishen4_y+0.03;
						}

						if (Ramka5_LR == 0)
						{
							mishen5_y = mishen5_y-0.03;
						}
						else if (Ramka5_LR == 1)
						{
							mishen5_y = mishen5_y+0.03;
						}

						if (Ramka6_LR == 0)
						{
							mishen6_y = mishen6_y-0.03;
						}
						else if (Ramka6_LR == 1)
						{
							mishen6_y = mishen6_y+0.03;
						}

						SET_OBJECT_COORDINATES( torso_R1, mishen1_x, mishen1_y, 4.82258 );
						SET_OBJECT_COORDINATES( torso_R2, mishen2_x, mishen2_y, 4.82258 );
						SET_OBJECT_COORDINATES( torso_R3, mishen3_x, mishen3_y, 4.82258 );
						SET_OBJECT_COORDINATES( torso_L1, mishen4_x, mishen4_y, 7.29204 );
						SET_OBJECT_COORDINATES( torso_L2, mishen5_x, mishen5_y, 7.29204 );
						SET_OBJECT_COORDINATES( torso_L3, mishen6_x, mishen6_y, 7.29204 );

						if ((Ramka1_LR == 1) && (mishen1_y > 1802.331))
						{
							mishen1_x = -249.822;
						}
						if ((Ramka2_LR == 1) && (mishen2_y > 1805.275))
						{
							mishen2_x = -249.822;
						}
						if ((Ramka3_LR == 0) && (mishen3_y < 1810.997))
						{
							mishen3_x = -249.822;
						}
						if ((Ramka4_LR == 0) && (mishen4_y < 1805.112))
						{
							mishen4_x = -249.822;
						}
						if ((Ramka5_LR == 0) && (mishen5_y < 1807.94))
						{
							mishen5_x = -249.822;
						}
						if ((Ramka6_LR == 1) && (mishen6_y > 1810.997))
						{
							mishen6_x = -249.822;
						}

						if (mishen1_y > 1805.17)
						{
							Ramka1_LR = 0;
						}
						else if (mishen1_y < 1802.53)
						{
							Ramka1_LR = 1;
						}

						if (mishen2_y > 1807.963)
						{
							Ramka2_LR = 0;
						}
						else if (mishen2_y < 1805.275)
						{
							Ramka2_LR = 1;
						}
						if (mishen3_y < 1807.963)
						{
							Ramka3_LR = 1;
						}
						else if (mishen3_y > 1810.997)
						{
							Ramka3_LR = 0;
						}
						if (mishen4_y < 1802.535)
						{
							Ramka4_LR = 1;
						}
						else if (mishen4_y > 1805.112)
						{
							Ramka4_LR = 0;
						}
						if (mishen5_y < 1805.219)
						{
							Ramka5_LR = 1;
						}
						else if (mishen5_y > 1807.94)
						{
							Ramka5_LR = 0;
						}
						if (mishen6_y < 1807.963)
						{
							Ramka6_LR = 1;
						}
						else if (mishen6_y > 1810.997)
						{
							Ramka6_LR = 0;
						}
						
						GET_OBJECT_HEALTH(torso_R1, &Heal_1_1);
						GET_OBJECT_HEALTH(torso_R2, &Heal_1_2);
						GET_OBJECT_HEALTH(torso_R3, &Heal_1_3);
						GET_OBJECT_HEALTH(torso_L1, &Heal_1_4);
						GET_OBJECT_HEALTH(torso_L2, &Heal_1_5);
						GET_OBJECT_HEALTH(torso_L3, &Heal_2_1);

						if (Heal_1_1 < 995)
						{
							DELETE_OBJECT(&torso_R1);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R1);
							CREATE_OBJECT_NO_OFFSET(tar_civ1, -253.956, 1798.44, 4.82258, &torso_R1, TRUE);
							SET_OBJECT_HEADING( torso_R1, -90.0 );
							mishen1_x = -253.956;
							mishen1_y = 1798.44;
							Ramka1_LR = 1;
							score_all += 1;
						}
						if (Heal_1_2 < 995)
						{
							DELETE_OBJECT(&torso_R2);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R2);
							CREATE_OBJECT_NO_OFFSET(tar_civ2, -253.956, 1802.73, 4.82258, &torso_R2, TRUE);
							SET_OBJECT_HEADING( torso_R2, -90.0 );
							mishen2_x = -253.956;
							mishen2_y = 1802.73;
							Ramka2_LR = 1;
							score_all += 1;
						}
						if (Heal_1_3 < 995)
						{
							DELETE_OBJECT(&torso_R3);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R3);
							CREATE_OBJECT_NO_OFFSET(tar_gun1, -253.956, 1813.51, 4.82258, &torso_R3, TRUE);
							SET_OBJECT_HEADING( torso_R3, -90.0 );
							mishen3_x = -253.956;
							mishen3_y = 1813.51;
							Ramka3_LR = 0;
							score_all += 1;
						}
						if (Heal_1_4 < 995)
						{
							DELETE_OBJECT(&torso_L1);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L1);
							CREATE_OBJECT_NO_OFFSET(tar_gun1, -253.327, 1806.63, 7.29204, &torso_L1, TRUE);
							SET_OBJECT_HEADING( torso_L1, -90.0 );
							mishen4_x = -253.327;
							mishen4_y = 1806.63;
							Ramka4_LR = 0;
							score_all += 1;
						}
						if (Heal_1_5 < 995)
						{
							DELETE_OBJECT(&torso_L2);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L2);
							CREATE_OBJECT_NO_OFFSET(tar_civ1, -253.971, 1810.34, 7.29204, &torso_L2, TRUE);
							SET_OBJECT_HEADING( torso_L2, -90.0 );
							mishen5_x = -253.971;
							mishen5_y = 1810.34;
							Ramka5_LR = 0;
							score_all += 1;
						}
						if (Heal_2_1 < 995)
						{
							DELETE_OBJECT(&torso_L3);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L3);
							CREATE_OBJECT_NO_OFFSET(tar_civ2, -253.956, 1813.51, 4.82258, &torso_L3, TRUE);
							SET_OBJECT_HEADING( torso_L3, -90.0 );
							mishen6_x = -253.956;
							mishen6_y = 1813.51;
							Ramka6_LR = 1;
							score_all += 1;
						}

						GET_CURRENT_CHAR_WEAPON(GetPlayerPed(), &pWeapon);//!!!___2(вписываем в переменную "pWeapon" оружие в руках игрока) 
						GET_AMMO_IN_CHAR_WEAPON(GetPlayerPed(), pWeapon, &MaxAmmo);

						// проверка количества поторонов тут
						if (((time_m == 0) && (time_s < 1)) || (MaxAmmo < 1) || (round_skip > 0))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R8_IA", "BNK2_3", 0, 0);// AREA CLEAR!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							SET_PLAYER_FORCED_AIM( GetPlayerIndex(), 0 );
							FREEZE_CHAR_POSITION(GetPlayerPed(), 0);
							REMOVE_ALL_CHAR_WEAPONS(GetPlayerPed());

							ADD_BLIP_FOR_COORD(-245.585, 1808.23, 4.99193, &malibu_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_POINT");//иконка на радаре называние в истории карты ""

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM2_14", 5000, 1);//~g~Move on to the next area!

							STOP_SOUND(AudID);
							RELEASE_SOUND_ID(AudID);
							AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED();
							audio = 0;
							round_skip = 0;

							SETTIMERA(0); //сбрасываем таймер 
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM2_11", 5000, 1);//~r~Phil's dead!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_BUTTON_PRESSED( 0, 17 )) || ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER()))) // BACKSPACE
						{
							CLEAR_PRINTS();
							round_skip = 1;
						
			 
						}
					}
				}
				// Пойнт 3
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						if ( TIMERA() < 4000 )
						{
							SET_TEXT_COLOUR(255, 159, 255, 255); // задаём цвет текста
							SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
							SET_TEXT_EDGE(1, 0, 0, 0, 255); //
							SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
							SET_TEXT_CENTRE(1); // задаём центр текста
							DISPLAY_TEXT(0.5, 0.45, "BJM2_7");//TOTAL SCORE FOR SHOOT:

							SET_TEXT_COLOUR(255, 159, 255, 255); // задаём цвет текста
							SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
							SET_TEXT_EDGE(1, 0, 0, 0, 255); //
							SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
							SET_TEXT_CENTRE(1); // задаём центр текста
							DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", score_all);//
						}

						DRAW_CHECKPOINT( -245.585, 1808.23, 4.99193, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -245.585, 1808.23, 4.99193, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							// обучение тут
							REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре

							SET_OBJECT_COORDINATES( torso_R1, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_L1, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_R2, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_L2, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_R3, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_L3, -238.229, 1782.66, 7.31169 );

							DELETE_OBJECT(&torso_R1);
							DELETE_OBJECT(&torso_R2);
							DELETE_OBJECT(&torso_R3);
							DELETE_OBJECT(&torso_L1);
							DELETE_OBJECT(&torso_L2);
							DELETE_OBJECT(&torso_L3);
							
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R1);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R2);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R3);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L1);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L2);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L3);

							CREATE_OBJECT_NO_OFFSET(tar_civ1, -253.573, 1807.73, 7.29204, &torso_R1, TRUE);
							CREATE_OBJECT_NO_OFFSET(tar_civ2, -241.459, 1823.71, 7.29204, &torso_R2, TRUE);
							CREATE_OBJECT_NO_OFFSET(tar_gun1, -245.316, 1825.05, 0.25, &torso_R3, TRUE);
							CREATE_OBJECT_NO_OFFSET(tar_gun1, -254.939, 1821.96, 4.76985, &torso_L1, TRUE);
							CREATE_OBJECT_NO_OFFSET(tar_civ1, -236.597, 1820.73, 4.76985, &torso_L2, TRUE);
							CREATE_OBJECT_NO_OFFSET(tar_civ2, -236.146, 1812.04, 4.76985, &torso_L3, TRUE);

							SET_OBJECT_HEADING( torso_R1, -90.0 );
							SET_OBJECT_HEADING( torso_R2, -90.0 );
							SET_OBJECT_HEADING( torso_R3, 0.0 );
							SET_OBJECT_HEADING( torso_L1, 0.0 );
							SET_OBJECT_HEADING( torso_L2, 0.0 );
							SET_OBJECT_HEADING( torso_L3, 0.0 );

							mishen1_x = -253.573;
							mishen2_x = -241.459;
							mishen3_x = 0.25;
							mishen4_x = -254.939;
							mishen5_x = -236.597;
							mishen6_x = -236.146;

							mishen1_y = 1807.73;
							mishen2_y = 1823.71;
							mishen3_y = 1825.05;
							mishen4_y = 1821.96;
							mishen5_y = 1820.73;
							mishen6_y = 1812.04;

							Ramka1_LR = 1;
							Ramka2_LR = 0;
							Ramka3_LR = 1;
							Ramka4_LR = 0;
							Ramka5_LR = 0;
							Ramka6_LR = 0;

							WAIT(100);
							UpdateWeaponOfPed(GetPlayerPed(), WEAPON_PISTOL);
							SET_CHAR_AMMO(GetPlayerPed(), 7, 20);

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							SET_CAMERA_CONTROLS_DISABLED_WITH_PLAYER_CONTROLS( 0 );
							SET_PLAYER_FORCED_AIM( GetPlayerIndex(), 1 );

							SET_CHAR_COORDINATES(GetPlayerPed(), -245.585, 1808.23, 4.99193);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 0.0);

							// обяснения тут
							PRINT_STRING_IN_STRING("string", "BJM2_19", 5000, 1);//~g~Hit as many targets as you can in the time limit!
							SetTime(5000);
							PRINT_STRING_IN_STRING("string", "BJM2_20", 5000, 1);//~g~When you run out of ~w~time ~g~or ~w~ammunition ~g~the round is over!
							SetTime(5000);
							PRINT_STRING_IN_STRING("string", "BJM2_27", 5000, 1);//~g~All targets this round are worth one point.
							SetTime(5000);
							CLEAR_PRINTS();

							// Целься 3...2...1...Огонь!
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R8_BB", "BNK2_2", 0, 0);//AIM 3-2-1 FIRE!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							FREEZE_CHAR_POSITION(GetPlayerPed(), 1);
							SETTIMERB( 0 );

							// воспроизводим звук
							while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_AMBIENT/TOLLBOOTH" )))
							{
								 WAIT(0);
							}
							AudID = GET_SOUND_ID();
							PLAY_SOUND_FROM_POSITION(AudID, "SCRIPT_AMBIENT_TOLLBOOTH_ARM_LOOP", -245.34, 1811.49, 8.27772);
							audio = 1;
							time_m = 1;
							time_s = 0;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM2_11", 5000, 1);//~r~Phil's dead!
							skip = 1;// переменная пропуска
							break;
						}
						else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -207.201, 1744.357, 1.895, -263.896, 1835.861, 24.875, 0 ))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM2_22", 5000, 1);//~r~You have left the shooting range!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}
				// мишени 3
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						//============================ HUD ============================
						// таймер тут
						if (TIMERB() > 999)
						{
							time_s -= 1;
							SETTIMERB( 0 );
						}

						if (time_s < 0)
						{
							time_m -= 1;
							time_s = 59;
						}

						// таймер
						DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78305097, 0.77731852, "RACES"); //TIME:

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

						// счётчик бомб 
						DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );
						DRAW_SPRITE( tar, 0.8270625, 0.74213, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.
						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.78305097, 0.73564852, "BJM2_18"); //SCORE TO BEAT:

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						if ( score_all > 9 )
						{
							if ( score_all > 99 )
							{
								DISPLAY_TEXT_WITH_NUMBER(0.9083334, 0.72787074, "CP_TIME_NOZERO", score_all);// 
							}
							else
							{
								DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.72787074, "CP_TIME_NOZERO", score_all);// 
							}
						}
						else
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.72787074, "CP_TIME_ZERO", score_all);// 
						}
						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT_WITH_NUMBER(0.9203125, 0.72787074, "OUTOF_NUM", 60);// 

						// Движение мишений
						if (Ramka1_LR == 0)
						{
							mishen1_y = mishen1_y-0.03;
						}
						else if (Ramka1_LR == 1)
						{
							mishen1_y = mishen1_y+0.03;
						}
						if (Ramka2_LR == 0)
						{
							mishen2_y = mishen2_y-0.03;
						}
						else if (Ramka2_LR == 1)
						{
							mishen2_y = mishen2_y+0.03;
						}
						if (Ramka3_LR == 0)
						{
							mishen3_x = mishen3_x-0.03;
						}
						else if (Ramka3_LR == 1)
						{
							mishen3_x = mishen3_x+0.03;
						}
						if (Ramka4_LR == 0)
						{
							mishen4_x = mishen4_x-0.03;
						}
						else if (Ramka4_LR == 1)
						{
							mishen4_x = mishen4_x+0.03;
						}
						if (Ramka5_LR == 0)
						{
							mishen5_x = mishen5_x-0.03;
						}
						else if (Ramka5_LR == 1)
						{
							mishen5_x = mishen5_x+0.03;
						}
						if (Ramka6_LR == 0)
						{
							mishen6_x = mishen6_x-0.03;
						}
						else if (Ramka6_LR == 1)
						{
							mishen6_x = mishen6_x+0.03;
						}

						SET_OBJECT_COORDINATES( torso_R1, mishen1_x, mishen1_y, 7.29204 );
						SET_OBJECT_COORDINATES( torso_R2, mishen2_x, mishen2_y, 7.29204 );
						SET_OBJECT_COORDINATES( torso_R3, -245.316, mishen3_y, mishen3_x );
						SET_OBJECT_COORDINATES( torso_L1, mishen4_x, mishen4_y, 4.77 );
						SET_OBJECT_COORDINATES( torso_L2, mishen5_x, mishen5_y, 4.77 );
						SET_OBJECT_COORDINATES( torso_L3, mishen6_x, mishen6_y, 4.77 );

						if ((Ramka1_LR == 1) && (mishen1_y > 1812.532))
						{
							mishen1_x = -249.08;
						}
						else if ((Ramka1_LR == 0) && (mishen1_y < 1812.532))
						{
							mishen1_x = -253.573;
						}

						if (mishen1_y > 1815.465)
						{
							Ramka1_LR = 0;
						}
						else if (mishen1_y < 1807.734)
						{
							Ramka1_LR = 1;
						}
						if (mishen2_y > 1823.698)
						{
							Ramka2_LR = 0;
						}
						else if (mishen2_y < 1808.045)
						{
							Ramka2_LR = 1;
						}
						if (mishen3_x < 0.25)
						{
							Ramka3_LR = 1;
						}
						else if (mishen3_x > 9.766)
						{
							Ramka3_LR = 0;
						}
						if (mishen4_x < -254.939)
						{
							Ramka4_LR = 1;
						}
						else if (mishen4_x > -248.653)
						{
							Ramka4_LR = 0;
						}
						if (mishen5_x < -244.084)
						{
							Ramka5_LR = 1;
						}
						else if (mishen5_x > -236.597)
						{
							Ramka5_LR = 0;
						}
						if (mishen6_x < -242.414)
						{
							Ramka6_LR = 1;
						}
						else if (mishen6_x > -236.146)
						{
							Ramka6_LR = 0;
						}
						
						GET_OBJECT_HEALTH(torso_R1, &Heal_1_1);
						GET_OBJECT_HEALTH(torso_R2, &Heal_1_2);
						GET_OBJECT_HEALTH(torso_R3, &Heal_1_3);
						GET_OBJECT_HEALTH(torso_L1, &Heal_1_4);
						GET_OBJECT_HEALTH(torso_L2, &Heal_1_5);
						GET_OBJECT_HEALTH(torso_L3, &Heal_2_1);

						if (Heal_1_1 < 995)
						{
							DELETE_OBJECT(&torso_R1);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R1);
							CREATE_OBJECT_NO_OFFSET(tar_civ1, -253.573, 1807.73, 7.29204, &torso_R1, TRUE);
							SET_OBJECT_HEADING( torso_R1, -90.0 );
							mishen1_x = -253.573;
							mishen1_y = 1807.73;
							Ramka1_LR = 1;
							score_all += 1;
						}
						if (Heal_1_2 < 995)
						{
							DELETE_OBJECT(&torso_R2);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R2);
							CREATE_OBJECT_NO_OFFSET(tar_civ2, -241.459, 1823.71, 7.29204, &torso_R2, TRUE);
							SET_OBJECT_HEADING( torso_R2, -90.0 );
							mishen2_x = -241.459;
							mishen2_y = 1823.71;
							Ramka2_LR = 0;
							score_all += 1;
						}
						if (Heal_1_3 < 995)
						{
							DELETE_OBJECT(&torso_R3);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R3);
							CREATE_OBJECT_NO_OFFSET(tar_gun1, -245.316, 1825.05, 0.25, &torso_R3, TRUE);
							SET_OBJECT_HEADING( torso_R3, 0.0 );
							mishen3_x = 0.25;
							mishen3_y = 1825.05;
							Ramka3_LR = 1;
							score_all += 1;
						}
						if (Heal_1_4 < 995)
						{
							DELETE_OBJECT(&torso_L1);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L1);
							CREATE_OBJECT_NO_OFFSET(tar_gun1, -254.939, 1821.96, 4.76985, &torso_L1, TRUE);
							SET_OBJECT_HEADING( torso_L1, 0.0 );
							mishen4_x = -254.939;
							mishen4_y = 1821.96;
							Ramka4_LR = 0;
							score_all += 1;
						}
						if (Heal_1_5 < 995)
						{
							DELETE_OBJECT(&torso_L2);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L2);
							CREATE_OBJECT_NO_OFFSET(tar_civ1, -236.597, 1820.73, 4.76985, &torso_L2, TRUE);
							SET_OBJECT_HEADING( torso_L2, 0.0 );
							mishen5_x = -236.597;
							mishen5_y = 1820.73;
							Ramka5_LR = 0;
							score_all += 1;
						}
						if (Heal_2_1 < 995)
						{
							DELETE_OBJECT(&torso_L3);
							MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L3);
							CREATE_OBJECT_NO_OFFSET(tar_civ2, -236.146, 1812.04, 4.76985, &torso_L3, TRUE);
							SET_OBJECT_HEADING( torso_L3, 0.0 );
							mishen6_x = -236.146;
							mishen6_y = 1812.04;
							Ramka6_LR = 0;
							score_all += 1;
						}

						GET_CURRENT_CHAR_WEAPON(GetPlayerPed(), &pWeapon);//!!!___2(вписываем в переменную "pWeapon" оружие в руках игрока) 
						GET_AMMO_IN_CHAR_WEAPON(GetPlayerPed(), pWeapon, &MaxAmmo);

						// проверка количества поторонов тут
						if (((time_m == 0) && (time_s < 1)) || (MaxAmmo < 1) || (round_skip > 0))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R8_IA", "BNK2_3", 0, 0);// AREA CLEAR!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							SET_PLAYER_FORCED_AIM( GetPlayerIndex(), 0 );
							FREEZE_CHAR_POSITION(GetPlayerPed(), 0);
							REMOVE_ALL_CHAR_WEAPONS(GetPlayerPed());

							ADD_BLIP_FOR_CHAR(ped1, &malibu_ico);
							CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_POINT");//иконка на радаре называние в истории карты ""

							SET_OBJECT_COORDINATES( torso_R1, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_L1, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_R2, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_L2, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_R3, -238.229, 1782.66, 7.31169 );
							SET_OBJECT_COORDINATES( torso_L3, -238.229, 1782.66, 7.31169 );

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM2_17", 5000, 1);//~g~Go and talk to Phil.
							
							STOP_SOUND(AudID);
							RELEASE_SOUND_ID(AudID);
							AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED();
							audio = 0;
							round_skip = 0;
							SETTIMERA(0); //сбрасываем таймер 
                            break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM2_11", 5000, 1);//~r~Phil's dead!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_BUTTON_PRESSED( 0, 17 )) || ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER()))) // BACKSPACE
						{
							CLEAR_PRINTS();
							round_skip = 1;
														
			 
						}
					}
				}
				// Пойнт 4
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						if ( TIMERA() < 4000 )
						{
							SET_TEXT_COLOUR(255, 159, 255, 255); // задаём цвет текста
							SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
							SET_TEXT_EDGE(1, 0, 0, 0, 255); //
							SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
							SET_TEXT_CENTRE(1); // задаём центр текста
							DISPLAY_TEXT(0.5, 0.45, "BJM2_7");//TOTAL SCORE FOR SHOOT:

							SET_TEXT_COLOUR(255, 159, 255, 255); // задаём цвет текста
							SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
							SET_TEXT_EDGE(1, 0, 0, 0, 255); //
							SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
							SET_TEXT_CENTRE(1); // задаём центр текста
							DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "CP_TIME_NOZERO", score_all);//
						}

						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -216.406, 1789.85, 4.99193, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 8.0) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							// грузим анимации
							REQUEST_ANIMS( "amb@hang_str_idls" );
							while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);

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

							SET_CHAR_COORDINATES(ped1, -233.262, 1767.24, 5.22361);// перемещаем
							SET_CHAR_HEADING(ped1, -90.0);

							SET_CHAR_COORDINATES(GetPlayerPed(), -231.646, 1767.2, 5.22361);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 90.0);
							SetTime(1000);

							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -233.724, 1769.41, 6.79401 ); // куда смотрит камера
							SET_CAM_POS			( camera, -229.302, 1761.84, 5.37918 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
							SetTime(1000);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R8_JA", "BNK2_7", 0, 0);//So you wanna do me a favor, and help me put together a job?
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2000 );//Воиспроизвидение анимации на педе
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							if (score_all <= 60)
							{
								// диалог тут
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R8_LA", "BNK2_9A", 0, 0);// Son, you better get your fancy talking and big ideas and shove 'em where there ain't no sun. You can't shoot nothin'!
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();
								skip = 1;// переменная пропуска
							}
							else
							{
								// диалог тут
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R8_KA", "BNK2_8", 0, 0);//Son, after shooting like that, if you asked me to be your wife, I'd say yes.
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();
								skip = 2;// переменная пропуска
							}
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
							//удяляем камеру тут
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							SET_CHAR_COORDINATES(ped1, -23.262, 177.24, 5.22361);// перемещаем
							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM2_11", 5000, 1);//~r~Phil's dead!
							skip = 1;// переменная пропуска
							break;
						}
						else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -207.201, 1744.357, 1.895, -263.896, 1835.861, 24.875, 0 ))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BJM2_22", 5000, 1);//~r~You have left the shooting range!
							skip = 1;// переменная пропуска
							break;
						}
					}
				}

				// зачищаем скрипт
				if (audio == 1)
				{
					STOP_SOUND(AudID);
					RELEASE_SOUND_ID(AudID);
					AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED();
				}
				SET_PLAYER_FORCED_AIM( GetPlayerIndex(), 0 );
				FREEZE_CHAR_POSITION(GetPlayerPed(), 0);

				SET_MAX_WANTED_LEVEL(6);
				SET_PED_DENSITY_MULTIPLIER(1.0); // отключаем людской траффик
				REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
				RELEASE_WEATHER();

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( tar );
				REMOVE_TXD( textur1 );

				//задать оружие
				if (siren == 1)
				{
					REMOVE_ALL_CHAR_WEAPONS(GetPlayerPed());
					WAIT(100);

					UpdateWeaponOfPed(GetPlayerPed(), Weap1);
					UpdateWeaponOfPed(GetPlayerPed(), Weap2);
					UpdateWeaponOfPed(GetPlayerPed(), Weap3);
					UpdateWeaponOfPed(GetPlayerPed(), Weap4);
					UpdateWeaponOfPed(GetPlayerPed(), Weap5);
					UpdateWeaponOfPed(GetPlayerPed(), Weap6);
					UpdateWeaponOfPed(GetPlayerPed(), Weap7);
					UpdateWeaponOfPed(GetPlayerPed(), Weap8);
					UpdateWeaponOfPed(GetPlayerPed(), Weap9);
					UpdateWeaponOfPed(GetPlayerPed(), Weap0);
					SET_CHAR_AMMO(GetPlayerPed(), Weap1, Ammo1_1);
					SET_CHAR_AMMO(GetPlayerPed(), Weap2, Ammo2_1);
					SET_CHAR_AMMO(GetPlayerPed(), Weap3, Ammo3_1);
					SET_CHAR_AMMO(GetPlayerPed(), Weap4, Ammo4_1);
					SET_CHAR_AMMO(GetPlayerPed(), Weap5, Ammo5_1);
					SET_CHAR_AMMO(GetPlayerPed(), Weap6, Ammo6_1);
					SET_CHAR_AMMO(GetPlayerPed(), Weap7, Ammo7_1);
					SET_CHAR_AMMO(GetPlayerPed(), Weap8, Ammo8_1);
					SET_CHAR_AMMO(GetPlayerPed(), Weap9, Ammo9_1);
					SET_CHAR_AMMO(GetPlayerPed(), Weap0, Ammo0_1);
				}

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(frameM);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(headM);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(shoulderMR);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(shoulderML);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(torsoMR);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(torsoML);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(targM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(targM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(targM3);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(targM4);//выгружаем модель

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет

				DELETE_OBJECT(&frame1);
				DELETE_OBJECT(&frame2);
				DELETE_OBJECT(&frame3);
				DELETE_OBJECT(&head1);
				DELETE_OBJECT(&head2);
				DELETE_OBJECT(&head3);
				DELETE_OBJECT(&shoulder_R1);
				DELETE_OBJECT(&shoulder_R2);
				DELETE_OBJECT(&shoulder_R3);
				DELETE_OBJECT(&shoulder_L1);
				DELETE_OBJECT(&shoulder_L2);
				DELETE_OBJECT(&shoulder_L3);
				DELETE_OBJECT(&torso_R1);
				DELETE_OBJECT(&torso_R2);
				DELETE_OBJECT(&torso_R3);
				DELETE_OBJECT(&torso_L1);
				DELETE_OBJECT(&torso_L2);
				DELETE_OBJECT(&torso_L3);

				MARK_OBJECT_AS_NO_LONGER_NEEDED(&frame1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&frame2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&frame3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&head1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&head2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&head3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_R1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_R2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_R3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_L1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_L2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&shoulder_L3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_R3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&torso_L3);

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_BANK_2" );//The Shootist
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(1000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +1000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 1000);
					G_CLUB = 4;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== The Driver ======================================
		else if ((G_ONMISSION == 0) && (G_CLUB == 4))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(896.966, 472.341, 5.394, &malibu_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(malibu_ico, BLIP_CLUB);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(malibu_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "LG_10");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 896.966, 472.341, 5.394, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 896.966, 472.341, 5.394, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("BANK_3", 15000, CUTSCENE_BANKJOB);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(512.591, -74.900, 9.573, 189.24);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
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

				Car car1, car2;
				Ped ped1;
				Cam camera;
				Texture fon, timer;
				Blip Blip_r, Blip_r2, Blip_c1;
				uint checkpoint, car_heal;
				
				skip = 0;
				time_m = 0;
				time_s = 0;
				start = 0;
				
				Blip_x = 912.06;
				Blip_y = 358.32;
				Blip_z = 3.7;
				Blip_x2 = 910.68;
				Blip_y2 = 319.71;
				Blip_z2 = 5.47;
				play_cord = 1;

				ped1B_x = Blip_x;
				ped1B_y = Blip_y;
				ped1B_z = Blip_z;
				SetSped1 = 0;
				ped1_cord = 1;
				wanted = 0;


				textur1 = LOAD_TXD( "sunshine_race" );
				fon = GET_TEXTURE( textur1, "fon_hud" );
				timer = GET_TEXTURE( textur1, "timer_hud" );

				//uint CarM1 = MODEL_COMET;
				uint CarM1 = MODEL_SABREGT;// Sabre Turbo
				uint CarM2 = MODEL_SENTINEL;// Sentinel
				uint PedM1 = MODEL_IG_BULGARIN;// Хилари

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);

				REQUEST_MODEL(PedM1);// Хилари
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало

				CREATE_CAR(CarM1, 912.947, 383.023, 4.53957, &car1, TRUE);
				CREATE_CAR(CarM2, 916.777, 383.124, 4.53957, &car2, TRUE);

				SET_CAR_HEADING(car1, 180.0);
				SET_CAR_HEADING(car2, 180.0);
				SET_CAN_BURST_CAR_TYRES(car1, 0); // шины автомобиля нельзя повредить
				SET_CAN_BURST_CAR_TYRES(car2, 0); // шины автомобиля нельзя повредить
				SET_CAR_ENGINE_ON(car2, 1, 1);

				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//создаём педа за рулём автомобиля
				//SET_CHAR_PROOFS(ped1, TRUE, TRUE, TRUE, TRUE, TRUE);//делает педа бесмертным
				SET_CHAR_COMPONENT_VARIATION(ped1, 1, 0, 0);

				TASK_ENTER_CAR_AS_DRIVER(GetPlayerPed(), car2, TRUE);//садим игрока в верталёт
				MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 1 );

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "BANK_3A", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("bank_3a");
				while (!HAS_CUTSCENE_LOADED())
				{
					WAIT(0);
				}

				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED())
				{
					WAIT(0);
				}
				FORCE_WEATHER_NOW(WEATHER_SUNNY);
				FORWARD_TO_TIME_OF_DAY(19, 20);//устанавливаем время
				MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 0 );

				LOAD_ADDITIONAL_TEXT( "BANK_3B", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("bank_3b");
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

				RELEASE_WEATHER();
				CLEAR_AREA( 912.947, 383.023, 4.53957, 65.0, 1);//очещаем зону загрузки
				SET_CAR_DENSITY_MULTIPLIER(0);// отключаем пути

				SetTime(1000);
				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R14_XD", "", 0, 0);//
				START_SCRIPT_CONVERSATION(1, 1);
				SetSpeech();

				NEW_SCRIPTED_CONVERSATION();
				ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
				ADD_LINE_TO_CONVERSATION(0, "R8_MA", " ", 0, 0);//
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

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				SETTIMERA( 0 );
				SETTIMERB( 0 );

				// сама гонка тут
				ADD_BLIP_FOR_CHAR(ped1, &Blip_c1);
				CHANGE_BLIP_SPRITE(Blip_c1, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(Blip_c1, 12);   //цвет иконка на радаре (0=белая)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_c1, "NE_RACE1");//иконка на радаре "Blip01" называние в истории карты
				CHANGE_BLIP_SCALE(Blip_c1, 0.77999990); // масштаб иконки на радаре

				while(true)
				{
					WAIT(0);
					if ((start == 0) || (start == 1))
					{
						if (start == 0)
						{
							PLAY_AUDIO_EVENT( "FRONTEND_GAME_PICKUP_CHECKPOINT" );
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							
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
							start = 1;
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
					
					if ((wanted == 0) && (play_cord > 4))
					{
						// АУДИО ТУТ!!!
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R8_OA", "BNK3_3A", 0, 0);//Illegal street race in progress at Vice Point.
						START_SCRIPT_CONVERSATION(1, 1);

						ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
						APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
						wanted = 1;
					}
					if (wanted == 1)
					{
						if (!IS_SCRIPTED_CONVERSATION_ONGOING())
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R8_PA", "BNK3_3B", 0, 0);//Calling all officers.
							START_SCRIPT_CONVERSATION(1, 1);
							wanted = 2;
						}
					}
					else if (wanted == 2)
					{
						if (!IS_SCRIPTED_CONVERSATION_ONGOING())
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R8_QA", "BNK3_3C", 0, 0);//Street racers, this is illegal and forbidden!
							START_SCRIPT_CONVERSATION(1, 1);
							wanted = 3;
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
							Blip_x2 = 891.74;
							Blip_y2 = 217.25;
							Blip_z2 = 3.78;
						}
						else if (play_cord == 3)
						{
							Blip_x2 = 851.92; 
							Blip_y2 = 135.73;
							Blip_z2 = 3.65;
						}
						else if (play_cord == 4)
						{
							Blip_x2 = 663.78; 
							Blip_y2 = -164.36;
							Blip_z2 = 3.98;
						}
						else if (play_cord == 5)
						{
							Blip_x2 = 504.23; 
							Blip_y2 = -473.72;
							Blip_z2 = 4.01;
						}
						else if (play_cord == 6)
						{
							Blip_x2 = 515.352;
							Blip_y2 = -623.916;
							Blip_z2 = 3.98;
						}
						else if (play_cord == 7)
						{
							Blip_x2 = 477.835;
							Blip_y2 = -833.969;
							Blip_z2 = 3.98;
						}
						else if (play_cord == 8)
						{
							Blip_x2 = 418.641;
							Blip_y2 = -1036.19;
							Blip_z2 = 4.01;
						}
						else if (play_cord == 9)
						{
							Blip_x2 = 359.948;
							Blip_y2 = -1023.07;
							Blip_z2 = 3.98;
						}
						else if (play_cord == 10)
						{
							Blip_x2 = 282.592;
							Blip_y2 = -904.553;
							Blip_z2 = 3.98;
						}
						else if (play_cord == 11)
						{
							Blip_x2 = 242.823;
							Blip_y2 = -743.515;
							Blip_z2 = 3.98;
						}
						else if (play_cord == 12)
						{
							Blip_x2 = 388.573; 
							Blip_y2 = -738.543;
							Blip_z2 = 3.98;
						}
						else if (play_cord == 13)
						{
							Blip_x2 = 337.872; 
							Blip_y2 = -360.779;
							Blip_z2 = 3.98;
						}
						else if (play_cord == 14)
						{
							Blip_x2 = 557.88; 
							Blip_y2 = -267.59;
							Blip_z2 = 4.01;
						}
						else if (play_cord == 15)
						{
							Blip_x2 = 616.11; 
							Blip_y2 = 36.51;
							Blip_z2 = 4.6;
						}
						else if (play_cord == 16)
						{
							Blip_x2 = 710.36; 
							Blip_y2 = 356.36;
							Blip_z2 = 5.01;
						}
						else if (play_cord == 17)
						{
							Blip_x2 = 879.8; 
							Blip_y2 = 601.27;
							Blip_z2 = 4.86;
						}
						else if (play_cord == 18)
						{
							Blip_x2 = 922.63; 
							Blip_y2 = 600.13;
							Blip_z2 = 4.7;
						}
						else if (play_cord == 19)
						{
							Blip_x2 = 950.55; 
							Blip_y2 = 458.22;
							Blip_z2 = 4.29;
						}
						else if (play_cord == 20)
						{
							Blip_x2 = Blip_x2; 
							Blip_y2 = Blip_y2;
							Blip_z2 = Blip_z2;
						}
						else if (play_cord == 21)
						{
							skip = 2;
							break;
						}
						if (play_cord < 20)
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
							if (play_cord < 19)
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
					}

					//============================== соперник ==============================
					GET_CHAR_COORDINATES(ped1,  &Ped1X, &Ped1Y, &Ped1Z);//вписываем координаты соперника в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, &Ped1R);//проверка "игрок на координатах"
					if ( Ped1R < 55.0)
					{
						if (SetSped1 == 0)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						}
						if (SetSped1 == 1)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 30.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						}
						if (SetSped1 == 2)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 15.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						}
					}
					if ( Ped1R < 15.0)
					{
						water1X = ped1B_x;
						water1Y = ped1B_y;
						water1Z = ped1B_z;
						GET_CAR_HEADING(car1, &water1R);
						ped1_cord += 1;

						if (ped1_cord == 3)
						{
							ped1B_x = 891.74;
							ped1B_y = 217.25;
							ped1B_z = 3.78;
							SetSped1 = 0;
						}
						else if (ped1_cord == 4)
						{
							ped1B_x = 851.92; 
							ped1B_y = 135.73;
							ped1B_z = 3.65;
							SetSped1 = 1;
						}
						else if (ped1_cord == 5)
						{
							ped1B_x = 663.78; 
							ped1B_y = -164.36;
							ped1B_z = 3.98;
							SetSped1 = 0;
							SET_CAR_DENSITY_MULTIPLIER(1);// отключаем\включаем пути
						}
						else if (ped1_cord == 6)
						{
							ped1B_x = 504.23; 
							ped1B_y = -473.72;
							ped1B_z = 4.01;
							SetSped1 = 1;
							SET_CAR_DENSITY_MULTIPLIER(0);// отключаем\включаем пути
						}
						else if (ped1_cord == 7)
						{
							ped1B_x = 515.352;
							ped1B_y = -623.916;
							ped1B_z = 3.98;
							SetSped1 = 0;
						}
						else if (ped1_cord == 8)
						{
							ped1B_x = 477.835;
							ped1B_y = -833.969;
							ped1B_z = 3.98;
							SetSped1 = 1;
						}
						else if (ped1_cord == 9)
						{
							ped1B_x = 418.641;
							ped1B_y = -1036.19;
							ped1B_z = 4.01;
							SetSped1 = 2;
						}
						else if (ped1_cord == 10)
						{
							ped1B_x = 359.948;
							ped1B_y = -1023.07;
							ped1B_z = 3.98;
							SetSped1 = 1;
							SET_CAR_DENSITY_MULTIPLIER(1);// отключаем\включаем пути
						}

						else if (ped1_cord == 11)
						{
							ped1B_x = 282.592;
							ped1B_y = -904.553;
							ped1B_z = 3.98;
							SetSped1 = 1;
							SET_CAR_DENSITY_MULTIPLIER(0);// отключаем\включаем пути
						}
						else if (ped1_cord == 12)
						{
							ped1B_x = 242.823;
							ped1B_y = -743.515;
							ped1B_z = 3.98;
							SetSped1 = 2;
						}
						else if (ped1_cord == 13)
						{
							ped1B_x = 388.573; 
							ped1B_y = -738.543;
							ped1B_z = 3.98;
							SetSped1 = 2;
							SET_CAR_DENSITY_MULTIPLIER(1);// отключаем\включаем пути
						}
						else if (ped1_cord == 14)
						{
							ped1B_x = 337.872; 
							ped1B_y = -360.779;
							ped1B_z = 3.98;
							SetSped1 = 2;
							SET_CAR_DENSITY_MULTIPLIER(0);// отключаем\включаем пути
						}
						else if (ped1_cord == 15)
						{
							ped1B_x = 557.88; 
							ped1B_y = -267.59;
							ped1B_z = 4.01;
							SetSped1 = 0;
						}
						else if (ped1_cord == 16)
						{
							ped1B_x = 616.11; 
							ped1B_y = 36.51;
							ped1B_z = 4.6;
							SetSped1 = 1;
							SET_CAR_DENSITY_MULTIPLIER(1);// отключаем\включаем пути
						}
						else if (ped1_cord == 17)
						{
							ped1B_x = 710.36; 
							ped1B_y = 356.36;
							ped1B_z = 5.01;
							SetSped1 = 1;
							SET_CAR_DENSITY_MULTIPLIER(0);// отключаем\включаем пути
						}
						else if (ped1_cord == 18)
						{
							ped1B_x = 879.8; 
							ped1B_y = 601.27;
							ped1B_z = 4.86;
							SetSped1 = 1;
						}
						else if (ped1_cord == 19)
						{
							ped1B_x = 922.63; 
							ped1B_y = 600.13;
							ped1B_z = 4.7;
							SetSped1 = 1;
							SET_CAR_DENSITY_MULTIPLIER(1);// отключаем\включаем пути
						}
						else if (ped1_cord == 20)
						{
							ped1B_x = 950.55; 
							ped1B_y = 458.22;
							ped1B_z = 4.29;
							SetSped1 = 0;
						}
						else if (ped1_cord == 21)
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

					if ((IS_CHAR_DEAD(ped1)) || (IS_CHAR_FATALLY_INJURED(ped1)))//если пед мёртв или фатально ранен. 
					{
						skip = 1;
						PRINT_STRING_IN_STRING("string", "BJM3_2", 5000, 1);//~r~Hilary is dead!
						break;
					}

					//***************** позиция *****************
					GET_CHAR_COORDINATES(ped1,  &Ped1X, &Ped1Y, &Ped1Z);//вписываем координаты соперника в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, &Ped1R);//проверка "игрок на координатах"
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, Blip_x, Blip_y, Blip_z, &PlayR);//проверка "игрок на координатах"

					if (play_cord == ped1_cord)
					{
						if (PlayR < Ped1R) //1
						{
							poziteon = 1;
						}
						else
						{
							poziteon = 2;
						}
					}
					else if (play_cord > ped1_cord)
					{
						poziteon = 1;
					}
					else if (play_cord < ped1_cord)
					{
						poziteon = 2;
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

					//==================== фиксы переворота соперников ====================
					if (!IS_CHAR_SITTING_IN_ANY_CAR( ped1 ))
					{
						SETTIMERB(0);
						GET_CAR_COORDINATES(car1, &Ped1X, &Ped1Y, &Ped1Z);
						SET_CAR_COORDINATES(car1, Ped1X, Ped1Y, Ped1Z+1);
						GET_CAR_HEADING(car1, &Ped1R);
						SET_CAR_HEADING(car1, Ped1R);//градус поворота машины
						FIX_CAR(car1);
						WARP_CHAR_INTO_CAR(ped1, car1);
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
					}
					if (IS_CAR_IN_WATER(car1))
					{
						SETTIMERB(0);
						FIX_CAR(car1);
						SET_CAR_COORDINATES(car1, water1X, water1Y, water1Z);
						SET_CAR_HEADING(car1, water1R);//градус поворота машины
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
					}
					//==================== фиксы соперника в стене ====================
					GET_CHAR_SPEED(ped1, &sped_wall1);
					if (sped_wall1 < 2)
					{
						if (TIMERB() > 3000)
						{
							FIX_CAR(car1);
							SET_CAR_COORDINATES(car1, water1X, water1Y, water1Z);
							SET_CAR_HEADING(car1, water1R);//градус поворота машины
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							SETTIMERB(0);
						}
					}
					if (sped_wall1 > 4)
					{
						SETTIMERB(0);
					}
					//==================== фиксы разбитой тачки ====================
					GET_CAR_HEALTH(car1, &car_heal);
					if (car_heal < 500)
					{
						FIX_CAR(car1);
					}
				}

				// чистим скрипт тут
				WAIT(100);
				REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
				REMOVE_BLIP(Blip_r2);//Удаляем иконку на радаре
				REMOVE_BLIP(Blip_c1);//Удаляем иконку на радаре
				DELETE_CHECKPOINT(checkpoint);
				SET_CAR_DENSITY_MULTIPLIER(1);// отключаем\включаем пути

				if (skip == 2)
				{
					// сценка тут
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
					CLEAR_AREA( 952.11, 463.735, 5.15046, 65.0, 1);//очещаем зону загрузки

					SET_CHAR_COORDINATES(GetPlayerPed(), 952.11, 463.735, 5.15046);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), 180.0);

					FIX_CAR(car1);
					SET_CHAR_COORDINATES(ped1, 948.28, 463.634, 5.15046);// перемещаем игрока
					SET_CHAR_HEADING(ped1, 180.0);
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, 948.28, 463.634, 5.15046, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 949.899, 463.616, 5.15046 ); // куда смотрит камера
					SET_CAM_POS			( camera, 950.337, 452.762, 8.39867 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );
					DO_SCREEN_FADE_IN( 800 );// убирается затемнение экрана
					SetTime(1000);

					NEW_SCRIPTED_CONVERSATION();
					ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
					ADD_LINE_TO_CONVERSATION(0, "R8_NA", "BNK3_1", 0, 0);//Ok. I'll drive for you, but please, treat me bad.
					START_SCRIPT_CONVERSATION(1, 1);
					SetSpeech();
					SetTime(500);
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, 912.06, 358.32, 3.7, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
					SetTime(2000);

					DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
					while(true)
					{
						WAIT(0);
						if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
						{
							break;
						}
					}
					SET_CHAR_COORDINATES(ped1, 94.28, 46.634, 5.15046);// перемещаем игрока
					
					//удяляем камеру тут
					SET_CAM_BEHIND_PED( GetPlayerPed() );
					ACTIVATE_SCRIPTED_CAMS( 0, 0 );
					END_CAM_COMMANDS( &camera );
					SET_WIDESCREEN_BORDERS( 0 );
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

					DO_SCREEN_FADE_IN( 800 );// убирается затемнение экрана
				}

				// выгружаем из памяти модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет

				// выгружаем из памяти транспорт
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)

				RELEASE_TEXTURE( fon );
				RELEASE_TEXTURE( timer );
				REMOVE_TXD( textur1 );

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}

				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_BANK_3" );//The Driver
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(3000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +3000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 3000);
					G_CLUB = 5;
					autosave = 1;
				}
				G_ONMISSION = 0;

			}
		}
//============================== The Job ======================================
		else if ((G_ONMISSION == 0) && (G_CLUB == 5))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(896.966, 472.341, 5.394, &malibu_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(malibu_ico, BLIP_CLUB);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(malibu_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "LG_10");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
			DRAW_CHECKPOINT( 896.966, 472.341, 5.394, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 896.966, 472.341, 5.394, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("BANK_4", 15000, CUTSCENE_BANKJOB);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(512.591, -74.900, 9.573, 189.24);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
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
				FORWARD_TO_TIME_OF_DAY(6, 0);//устанавливаем время
				SET_CHAR_COORDINATES(GetPlayerPed(), 898.68, 474.04, 6.45);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 287.0);
				ALTER_WANTED_LEVEL(GetPlayerIndex(), 0);
				APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
				MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 1 );

				Car car1, car2, car3;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20;
				Cam camera;
				Object wire1, wire2, wire3, wire4, wire5, wire6;
				Pickup arm_1, aid_1;
				int dm, cdm;

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "BANK_4", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("bank_4");
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

				skip = 0;
				start = 1;
				in_car = 0;
				stalking = 0;
				ofice = 0;
				text = 0;
				del_car = 0;
				road_spech = 1;
				wanted = 0;
				speech_hp = 0;
				siren = 0;
				smoke_on = 0;

				uint Phil_hp, Cam_hp, Manager_hp;
				uint AudID1, AudID2, AudID3;
				uint PTFX, PTFX2, PTFX3, PTFX4;

				uint CarM1 = MODEL_TAXI;// Фургон
				uint CarM2 = MODEL_NSTOCKADE;// Фургон SWAT
				uint PedM1 = MODEL_IG_BRUCIE;// Фил
				uint PedM2 = MODEL_IG_DARDAN;// Кэм
				uint PedM3 = MODEL_IG_BULGARIN;// Хилари
				uint PedM4 = MODEL_M_M_SECURITYMAN;// Охрана
				uint PedM5 = MODEL_F_M_PMANHAT_02;// Сотрудник 1 Ж
				uint PedM6 = MODEL_M_M_PBUSINESS_01;// Сотрудник 2 М
				uint PedM7 = MODEL_M_Y_NHELIPILOT;// SWAT
				uint wireM = swat_wire; //верёвка

				LOAD_CHAR_DECISION_MAKER(2, &dm);
				LOAD_COMBAT_DECISION_MAKER(3, &cdm);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);

				REQUEST_MODEL(PedM1);// Фил
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// Кэм
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// Хилари
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM4);// Охрана
				while (!HAS_MODEL_LOADED(PedM4));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM5);// Сотрудник 1 М
				while (!HAS_MODEL_LOADED(PedM5));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM6);// Сотрудник 2 Ж
				while (!HAS_MODEL_LOADED(PedM6));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM7);// SWAT
				while (!HAS_MODEL_LOADED(PedM7));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(wireM);// верёвка
				while (!HAS_MODEL_LOADED(wireM));////проверка "пед загрузился" если нет то начанаем с начало

				CREATE_CAR(CarM1, 496.5 + MAP_OFFSET_X, -84.0 + MAP_OFFSET_Y, 9.8 + MAP_OFFSET_Z, &car1, TRUE);
							   
															   
																   
				SET_CAR_HEADING(car1, 137.0);

				CREATE_CAR(CarM2, 309.359, -762.952, 5.04796, &car2, TRUE);
				CREATE_CAR(CarM2, 306.277, -762.952, 5.04796, &car3, TRUE);
				LOCK_CAR_DOORS(car2, 3); //блокируем двери автомобиля для игрока
				LOCK_CAR_DOORS(car3, 3); //блокируем двери автомобиля для игрока

				// подельники
				CREATE_CHAR (26, PedM1, 300.081, -785.078, 5.05974, &ped1, TRUE);// Фил
				CREATE_CHAR (26, PedM2, 298.777, -785.033, 5.05974, &ped2, TRUE);// Кэм
				CREATE_CHAR (26, PedM3, 297.471, -785.033, 5.05974, &ped3, TRUE);// Хилари
				SET_CHAR_COMPONENT_VARIATION(ped1, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped2, 1, 0, 0);
				SET_CHAR_COMPONENT_VARIATION(ped3, 1, 0, 0);
				// SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 0, 0);
				SET_CHAR_HEALTH(ped1, 600);
				SET_CHAR_HEALTH(ped2, 600);

				// охрана
				CREATE_CHAR (26, PedM4, 293.628, -781.535, 5.05974, &ped4, TRUE);// Охрана
				CREATE_CHAR (26, PedM4, 294.873, -781.535, 5.05974, &ped5, TRUE);// Охрана
				CREATE_CHAR (26, PedM4, 296.119, -781.535, 5.05974, &ped6, TRUE);// Охрана
				CREATE_CHAR (26, PedM4, 297.365, -781.535, 5.05974, &ped7, TRUE);// Охрана
				CREATE_CHAR (26, PedM4, 298.611, -781.535, 5.05974, &ped8, TRUE);// Охрана
				CREATE_CHAR (26, PedM4, 299.856, -781.535, 5.05974, &ped9, TRUE);// Охрана
				CREATE_CHAR (26, PedM4, 301.101, -781.535, 5.05974, &ped10, TRUE);// Охрана
				CREATE_CHAR (26, PedM4, 302.347, -781.535, 5.05974, &ped11, TRUE);// Охрана

				// сотрудники банка
				CREATE_CHAR (26, PedM5, 293.628, -779.729, 5.05974, &ped12, TRUE);// Сотрудник 1 Ж
				CREATE_CHAR (26, PedM5, 294.873, -779.729, 5.05974, &ped13, TRUE);// Сотрудник 1 Ж
				CREATE_CHAR (26, PedM5, 296.119, -779.729, 5.05974, &ped14, TRUE);// Сотрудник 1 Ж
				CREATE_CHAR (26, PedM5, 297.365, -779.729, 5.05974, &ped15, TRUE);// Сотрудник 1 Ж
				CREATE_CHAR (26, PedM5, 298.611, -779.729, 5.05974, &ped16, TRUE);// Сотрудник 1 Ж
				CREATE_CHAR (26, PedM5, 299.856, -779.729, 5.05974, &ped17, TRUE);// Сотрудник 1 Ж
				CREATE_CHAR (26, PedM5, 301.101, -779.729, 5.05974, &ped18, TRUE);// Сотрудник 1 Ж
				CREATE_CHAR (26, PedM6, 302.347, -779.729, 5.05974, &ped19, TRUE);// Сотрудник 2 М
				CREATE_CHAR (26, PedM6, 303.424, -779.729, 5.05974, &ped20, TRUE);// Менеджер

				CREATE_OBJECT_NO_OFFSET(wireM, -497.446, 196.269, 14.8121, &wire1, TRUE);
				CREATE_OBJECT_NO_OFFSET(wireM, -497.446, 196.269, 14.8121, &wire2, TRUE);
				CREATE_OBJECT_NO_OFFSET(wireM, -497.446, 196.269, 14.8121, &wire3, TRUE);
				CREATE_OBJECT_NO_OFFSET(wireM, -497.446, 196.269, 14.8121, &wire4, TRUE);
				CREATE_OBJECT_NO_OFFSET(wireM, -497.446, 196.269, 14.8121, &wire5, TRUE);
				CREATE_OBJECT_NO_OFFSET(wireM, -497.446, 196.269, 14.8121, &wire6, TRUE);

				SET_OBJECT_DYNAMIC(wire1, 0);
				SET_OBJECT_DYNAMIC(wire2, 0);
				SET_OBJECT_DYNAMIC(wire3, 0);
				SET_OBJECT_DYNAMIC(wire4, 0);
				SET_OBJECT_DYNAMIC(wire5, 0);
				SET_OBJECT_DYNAMIC(wire6, 0);

				SET_OBJECT_INVINCIBLE(wire1, 1);
				SET_OBJECT_INVINCIBLE(wire2, 1);
				SET_OBJECT_INVINCIBLE(wire3, 1);
				SET_OBJECT_INVINCIBLE(wire4, 1);
				SET_OBJECT_INVINCIBLE(wire5, 1);
				SET_OBJECT_INVINCIBLE(wire6, 1);

				FREEZE_OBJECT_POSITION(wire1, 1);
				FREEZE_OBJECT_POSITION(wire2, 1);
				FREEZE_OBJECT_POSITION(wire3, 1);
				FREEZE_OBJECT_POSITION(wire4, 1);
				FREEZE_OBJECT_POSITION(wire5, 1);
				FREEZE_OBJECT_POSITION(wire6, 1);

				ADD_OBJECT_TO_INTERIOR_ROOM_BY_NAME(wire1, "bank_mloroom");
				ADD_OBJECT_TO_INTERIOR_ROOM_BY_NAME(wire2, "bank_mloroom");
				ADD_OBJECT_TO_INTERIOR_ROOM_BY_NAME(wire3, "bank_mloroom");
				ADD_OBJECT_TO_INTERIOR_ROOM_BY_NAME(wire4, "bank_mloroom");
				ADD_OBJECT_TO_INTERIOR_ROOM_BY_NAME(wire5, "bank_mloroom");
				ADD_OBJECT_TO_INTERIOR_ROOM_BY_NAME(wire6, "bank_mloroom");

				// вооружаем педов
				UpdateWeaponOfPed(ped7, WEAPON_MP5);
				UpdateWeaponOfPed(ped8, WEAPON_MP5);
				UpdateWeaponOfPed(ped9, WEAPON_MP5);
				UpdateWeaponOfPed(ped10, WEAPON_MP5);
				UpdateWeaponOfPed(ped11, WEAPON_MP5);

				// свой-чужой
				SET_CHAR_RELATIONSHIP_GROUP(ped4, 17);
				SET_CHAR_RELATIONSHIP_GROUP(ped5, 17);
				SET_CHAR_RELATIONSHIP_GROUP(ped6, 17);
				SET_CHAR_RELATIONSHIP_GROUP(ped7, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped8, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped9, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped10, 3);
				SET_CHAR_RELATIONSHIP_GROUP(ped11, 0);

				SET_SENSE_RANGE(ped7, 10.0);
				SET_SENSE_RANGE(ped8, 10.0);
				SET_SENSE_RANGE(ped9, 20.0);
				SET_SENSE_RANGE(ped10, 10.0);
				SET_SENSE_RANGE(ped11, 10.0);

				SET_CHAR_WILL_USE_COVER(ped7, 1);
				SET_CHAR_WILL_USE_COVER(ped8, 1);
				SET_CHAR_WILL_USE_COVER(ped9, 1);
				SET_CHAR_WILL_USE_COVER(ped10, 1);
				SET_CHAR_WILL_USE_COVER(ped11, 1);
				
				SET_CHAR_SPHERE_DEFENSIVE_AREA(ped7, -520.786, 194.368, 10.4802, 15.0);
				SET_CHAR_SPHERE_DEFENSIVE_AREA(ped8, -526.678, 199.865, 10.4802, 15.0);
				SET_CHAR_SPHERE_DEFENSIVE_AREA(ped9, -485.638, 178.734, 12.7778, 15.0);
				SET_CHAR_SPHERE_DEFENSIVE_AREA(ped10, -494.781, 185.333, 12.7636, 15.0);

				// настройка падельников
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

				SET_CHAR_RELATIONSHIP_GROUP(ped1, 0);
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 0);
				SET_CHAR_RELATIONSHIP_GROUP(ped3, 0);
				SET_CHAR_RELATIONSHIP(ped1, 5, 24);
				SET_CHAR_RELATIONSHIP(ped2, 5, 24);
				SET_CHAR_RELATIONSHIP(ped3, 5, 24);

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 0 );
				
				// билип тут
				ADD_BLIP_FOR_CAR(car1, &malibu_ico);
				CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(malibu_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_CAR");//иконка на радаре называние в истории карты ""

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "GETCAR", 5000, 1);//~g~Get in the getaway car to do the bank job!

				CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -528.916, 197.563, 10.4561, -90.0, 0.0, -40.0, &aid_1);//Аптека
				CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, -524.597, 194.829, 9.5785, -10.0, 0.0, 90.0, &arm_1);
				ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(aid_1, "bank_int");
				ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(arm_1, "bank_int");

				//грузим анимацию
				REQUEST_ANIMS( "ne_missbank" );//загружаем файл с анимацией
				while (!HAVE_ANIMS_LOADED( "ne_missbank" )) WAIT(0);

				// временно
				//WARP_CHAR_INTO_CAR(GetPlayerPed(), car1);
				//SET_CHAR_COORDINATES(GetPlayerPed(), 929.599, 448.432, 4.95018);// перемещаем игрока

				// часть 1 (пригнать машину)
				while (TRUE)
				{
					WAIT(0);
					if (IS_CHAR_IN_CAR(GetPlayerPed(), car1))
					{
						if (start == 1)
						{
							REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
																												 
																														  
																									
																						   
																																								
					  
																												   
							start = 0;
						}
						// ?????? ???
																																						
																																						 
																   
	   
							 
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							SET_CHAR_COORDINATES(ped1, 921.363, 457.332, 5.59428);// подельник
							SET_CHAR_COORDINATES(ped2, 921.704, 458.027, 5.59428);// подельник
							SET_CHAR_COORDINATES(ped3, 920.871, 458.109, 5.59428);// подельник
							SET_CHAR_HEADING(ped1, -145.0);
							SET_CHAR_HEADING(ped2, -145.0);
							SET_CHAR_HEADING(ped3, -145.0);

							TASK_ENTER_CAR_AS_PASSENGER(ped3, car1, 10000, 0);
							TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, 10000, 1);
							TASK_ENTER_CAR_AS_PASSENGER(ped1, car1, 10000, 2);
							SetTime(1500);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_CA", "BNK4_1", 0, 0);//I'll drive.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							SetTime(1000);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped3, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_CB", "BNK4_2", 0, 0);//Great. A passenger. Wait 'til I tell the group about this.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							SETTIMERA( 0 );
							while (TRUE)
						{
							WAIT(0);
							if ((IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (IS_CHAR_SITTING_IN_ANY_CAR(ped3)))
							{
				
																														   
		 
								//SET_CHAR_COORDINATES(GetPlayerPed(), -446.454, 192.487, 5.5746);// ?????????? ??????
								SETTIMERB( 0 );
			   
		 
								 
		 
														
														
														
								
						
								break;
		 
							}
							else if (TIMERA() > 8000)
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped1, car1, 2);
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped2, car1, 1);
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped3, car1, 0);
								SHUT_CAR_DOOR(car1, 1);
								SETTIMERB( 0 );
								break;
							}
						}

						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//????????????? ??????
						start = 1;
                        break;			
					}
					else
					{
						if (start == 0)
						{
							REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_CAR(car1, &malibu_ico);
							CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(malibu_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_CAR");//иконка на радаре называние в истории карты ""
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "GETCAR", 5000, 1);//~g~Get in the getaway car to do the bank job!
							start = 1;
						}
					}
					if (IS_CAR_DEAD(car1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "TRASHED", 5000, 1);//~r~YOU TRASHED THE GETAWAY CAR!!
						skip = 1;
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
				}
				// часть 2 ( добраться до банка)
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						hp_car = GET_ENGINE_HEALTH(car1);

						if (IS_CHAR_IN_CAR(GetPlayerPed(), car1))
						{
							if (start == 1)
							{
								REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
								ADD_BLIP_FOR_COORD(-446.716, 192.29, 5.01873, &malibu_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NEBNK4_P", 5000, 1);//~g~Go to the Vice City Bank.
								start = 0;
							}

							
							if (TIMERB() > 35000)
							{
								if (road_spech == 1)
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R11_DB", "BNK4_3B", 0, 0);//Tommy, Hilary's taking up too much room!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									road_spech = 2;
									SET_CHAR_COMPONENT_VARIATION(ped3, 1, 1, 0);
								}
								else if (road_spech == 2)
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped3, "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R11_DB_QQQ1", "BNK4_3C", 0, 0);//I am not!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									road_spech = 3;
								}
								else if (road_spech == 3)
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R11_DD", "BNK4_3D", 0, 0);//Are too!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									road_spech = 4;
								}
								else if (road_spech == 4)
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R11_DF", "BNK4_3E", 0, 0);//Hey, shut up you two, or you can get out and walk.
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									road_spech = 5;
								}
								else if (road_spech == 5)
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R11_EA", "BNK4_3F", 0, 0);//Yeah - HILARY.
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									road_spech = 7;
									SET_CHAR_COMPONENT_VARIATION(ped2, 1, 1, 0);
									SETTIMERB( 0 );
								}
							}

							if (road_spech > 6)
							{
								if (TIMERB() > 15000)
								{
									if (road_spech == 7)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
										ADD_LINE_TO_CONVERSATION(0, "R11_EB", "BNK4_3I", 0, 0);//For god's sake, Phil, stop waving that thing around!
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
										road_spech = 8;
										SET_CHAR_COMPONENT_VARIATION(ped1, 1, 1, 0);
									}
									else if (road_spech == 8)
									{
										NEW_SCRIPTED_CONVERSATION();
										ADD_NEW_CONVERSATION_SPEAKER(0, ped3, "ROMAN");
										ADD_LINE_TO_CONVERSATION(0, "R11_EC", "BNK4_3J", 0, 0);//Yeah, you'll have somebody's eye out!
										START_SCRIPT_CONVERSATION(1, 1);
										SetSpeech();
										road_spech = 9;
									}
								}
							}

							if (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0))
							{
								if( wanted == 0)
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R11_ED", "NEBNK4_W", 0, 0);//Crap. Now the cops are on to us.
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									SetTime(1000);

									CLEAR_PRINTS();
									PRINT_STRING_IN_STRING("string", "NEWANTED", 5000, 1);//~COL_NET_12~Shake the cops and lose your wanted level!
									wanted = 1;
									REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
								}
							}
							else
							{
								if( wanted == 1)
								{
									start = 1;
									wanted = 0;
								}
							}

							if (hp_car < 150)
							{
								SET_ENGINE_HEALTH(car1, 0 );
								SET_CAR_ENGINE_ON(car1, 0, 1);
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped3, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_EE", "BNK4_3M", 0, 0);//The car's ruined. RUINED!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();
								SetTime(1000);

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "TRASHED", 5000, 1);//~r~YOU TRASHED THE GETAWAY CAR!!
								skip = 1;
								break;
							}
							else if (hp_car < 550)
							{
								if (speech_hp == 0)
								{
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, ped3, "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R11_EG", "BNK4_3A", 0, 0);//Hey, watch the wheels, Tommy!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									speech_hp = 1;
								}
							}

							DRAW_CHECKPOINT( -446.716, 192.29, 5.01873, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -446.716, 192.29, 5.01873, &PlayR);//проверка "игрок на координатах"
							if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -430.272, 180.002, 3.554, -455.272, 205.002, 18.554, 0 )) && (IS_CHAR_IN_CAR(GetPlayerPed(), car1)) && (!IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0)))
							{
								SET_MAX_WANTED_LEVEL(0);

								// охрана
								SET_CHAR_COORDINATES(ped4, -486.867, 181.723, 8.27248);// Охрана
								SET_CHAR_COORDINATES(ped5, -476.339, 185.799, 8.27248);// Охрана
								SET_CHAR_COORDINATES(ped6, -484.554, 193.398, 8.27248);// Охрана
								SET_CHAR_COORDINATES(ped7, -520.786, 194.368, 10.4802);// Охрана
								SET_CHAR_COORDINATES(ped8, -526.678, 199.865, 10.4802);// Охрана
								SET_CHAR_COORDINATES(ped9, -485.638, 178.734, 12.7778);// Охрана
								SET_CHAR_COORDINATES(ped10, -494.781, 185.333, 12.7636);// Охрана
								SET_CHAR_COORDINATES(ped11, -509.465, 189.534, 1.7156);// Охрана

								SET_CHAR_HEADING(ped4, -48.0);
								SET_CHAR_HEADING(ped5, -30.0);
								SET_CHAR_HEADING(ped6, -125.0);
								SET_CHAR_HEADING(ped7, 0.0);
								SET_CHAR_HEADING(ped8, 0.0);
								SET_CHAR_HEADING(ped9, 0.0);
								SET_CHAR_HEADING(ped10, -95.0);
								SET_CHAR_HEADING(ped11, -90.0);

								// сотрудники банка
								SET_CHAR_COORDINATES(ped12, -477.531, 179.094, 8.27248);// Сотрудник 1 Ж
								SET_CHAR_COORDINATES(ped13, -485.428, 179.011, 8.27248);// Сотрудник 1 Ж
								SET_CHAR_COORDINATES(ped14, -486.772, 197.346, 8.27248);// Сотрудник 1 Ж
								SET_CHAR_COORDINATES(ped15, -486.723, 202.124, 8.27248);// Сотрудник 1 Ж
								SET_CHAR_COORDINATES(ped16, -478.113, 204.516, 8.27248);// Сотрудник 1 Ж
								SET_CHAR_COORDINATES(ped17, -476.603, 204.516, 8.27248);// Сотрудник 1 Ж
								SET_CHAR_COORDINATES(ped18, -488.239, 185.975, 8.27248);// Сотрудник 1 Ж
								SET_CHAR_COORDINATES(ped19, -489.093, 187.751, 8.27248);// Сотрудник 2 М
								SET_CHAR_COORDINATES(ped20, -531.369, 196.225, 10.4802);// Менеджер

								SET_CHAR_HEADING(ped12, 0.0);
								SET_CHAR_HEADING(ped13, 0.0);
								SET_CHAR_HEADING(ped14, -140.0);
								SET_CHAR_HEADING(ped15, -90.0);
								SET_CHAR_HEADING(ped16, 180.0);
								SET_CHAR_HEADING(ped17, 180.0);
								SET_CHAR_HEADING(ped18, -30.0);
								SET_CHAR_HEADING(ped19, -140.0);
								SET_CHAR_HEADING(ped20, 0.0);

								REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре

								// сценка тут
								DO_SCREEN_FADE_OUT( 100 );// Затемняем экран
								while(true)
								{
									WAIT(0);
									if (IS_SCREEN_FADED_OUT())//если игрок мёртв или аврестован, если лодка унечтожена
									{
										break;
									}
								}
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

								// переодивание	
								SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, 6, 0);
								SET_CHAR_COMPONENT_VARIATION(ped1, 1, 1, 0);
								SET_CHAR_COMPONENT_VARIATION(ped2, 1, 1, 0);
								SET_CHAR_COMPONENT_VARIATION(ped3, 1, 1, 0);

								REQUEST_ANIMS( "veh@low" );//загружаем файл с анимацией
								while (!HAVE_ANIMS_LOADED( "veh@low" )) WAIT(0);

								//Грузим пути
								REQUEST_CAR_RECORDING( 3052 ); // полёт Основной
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3052 )) WAIT(0);
								REQUEST_CAR_RECORDING( 3053 ); // релокация Ленса
								while (!HAS_CAR_RECORDING_BEEN_LOADED( 3053 )) WAIT(0);

								// вооружаем тут
								UpdateWeaponOfPed(ped2, WEAPON_MP5);
								GIVE_WEAPON_TO_CHAR(GetPlayerPed(), WEAPON_DEAGLE, 12, FALSE);

								// заускаем RRR пути тут
								CLEAR_AREA(-439.298, 188.959, 5.5746, 25.0, 1);//очещаем зону загрузки
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3052, 0.0, 0.0, 0.0);
								SET_PLAYBACK_SPEED(car1, 1.25);

								//ставим камеру
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, -445.908, 192.571, 6.0251 ); // куда смотрит камера
								SET_CAM_POS			( camera, -455.771, 193.901, 8.0049 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );
								DO_SCREEN_FADE_IN( 100 );// убирается затемнение экрана

								SetTime(4000);
								STOP_PLAYBACK_RECORDED_CAR(car1);
								REMOVE_CAR_RECORDING( 3052 ); // выгружаем пути транспорта

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R11_EH", "BNK4_4A", 0, 0);//Keep driving around the block, OK?
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped3, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_EI", "BNK4_5", 0, 0);//Okay, Tommy, Okay.
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								TASK_LEAVE_ANY_CAR(GetPlayerPed());
								TASK_LEAVE_ANY_CAR(ped1);
								TASK_LEAVE_ANY_CAR(ped2);
								SetTime(2500);

								SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_MP5, TRUE);
								SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_DEAGLE, TRUE);

								// анимация пересаживание Хилари тут
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped3, "shuffle_seat_ps", "veh@low", 1.0, 0, 0, 0, 1, -1 );//Воиспроизвидение анимации на педе
								SetTime(1000);

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_EJ", "BNK4_94", 0, 0);//Ok, guys. Nice an easy just as we planned.
								START_SCRIPT_CONVERSATION(1, 1);

								//меняем рукурс тут
								POINT_CAM_AT_COORD	( camera, -453.597, 192.487, 5.9259 ); // куда смотрит камера
								SET_CAM_POS			( camera, -435.562, 184.875, 9.8366 );//расположение камеры

								UpdateWeaponOfPed(ped1, WEAPON_M4);
								SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_M4, TRUE);

								// заускаем RRR пути 2 тут
								START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3053, 0.0, 0.0, 0.0);

								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(GetPlayerPed(), -476.111, 192.207, 7.5746, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, -474.414, 193.046, 7.5367, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, -474.603, 190.854, 7.5367, 3, -2, 1.5);// пед убегает
								SetTime(3000);
								SetSpeech();

								DO_SCREEN_FADE_OUT( 100 );// Затемняем экран
								while(true)
								{
									WAIT(0);
									if (IS_SCREEN_FADED_OUT())//если игрок мёртв или аврестован, если лодка унечтожена
									{
										break;
									}
								}

								STOP_PLAYBACK_RECORDED_CAR(car1);
								REMOVE_CAR_RECORDING( 3053 ); // выгружаем пути транспорта

								SET_CHAR_COORDINATES(ped1, -474.414, 193.046, 7.5367);// подельник
								SET_CHAR_COORDINATES(ped2, -474.603, 190.854, 7.5367);// подельник
								SET_CHAR_COORDINATES(GetPlayerPed(), -476.111, 192.207, 7.5746);// 
								SET_CHAR_HEADING(ped1, 30.0);
								SET_CHAR_HEADING(ped2, 140.0);
								SET_CHAR_HEADING(GetPlayerPed(), 85.0);

								//меняем рукурс тут
								POINT_CAM_AT_COORD	( camera, -473.514, 191.958, 9.04192 ); // куда смотрит камера
								SET_CAM_POS			( camera, -480.223, 193.948, 7.56871 );//расположение камеры
								DO_SCREEN_FADE_IN( 100 );// убирается затемнение экрана

								// анимации прицеливания тут
								TASK_AIM_GUN_AT_CHAR(GetPlayerPed(), ped6, 25000);
								SetTime(150);

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_EJ_QQQ1", "BNK4_6", 0, 0);//THIS IS A RAID!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								TASK_AIM_GUN_AT_COORD(ped1, -481.831, 204.516, 8.27248, 25000);
								TASK_AIM_GUN_AT_COORD(ped2, -485.428, 179.011, 8.27248, 25000);

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_EK", "BNK4_7", 0, 0);//NOBODY MOVE!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								// прячем Холари тут
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped3, "shuffle_seat_ps", "veh@low", 1.0, 0, 0, 0, 1, 1 );//Воиспроизвидение анимации на педе
								WARP_CHAR_INTO_CAR(ped3, car1);
								SET_CAR_COORDINATES(car1, -450.949, 216.518, 5.5746);//
								SET_CAR_HEADING(car1, 0.0);

								//меняем рукурс тут
								POINT_CAM_AT_COORD	( camera, -481.662, 195.237, 8.33039 ); // куда смотрит камера
								SET_CAM_POS			( camera, -469.993, 188.801, 9.75076 );//расположение камеры

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R11_EL", "BNK4_8", 0, 0);//EVERYBODY UP AGAINST THAT WALL!
								START_SCRIPT_CONVERSATION(1, 1);
								SetTime(3000);
								SetSpeech();

								DO_SCREEN_FADE_OUT( 100 );// Затемняем экран
								while(true)
								{
									WAIT(0);
									if (IS_SCREEN_FADED_OUT())//если игрок мёртв или аврестован, если лодка унечтожена
									{
										break;
									}
								}

								//меняем рукурс тут
								POINT_CAM_AT_COORD	( camera, -487.231, 195.046, 7.36434 ); // куда смотрит камера
								SET_CAM_POS			( camera, -472.451, 180.688, 9.56999 );//расположение камеры

								// ставим педов в ряд тут
								SET_CHAR_COORDINATES(ped12, -485.846, 186.601, 7.45208);//
								SET_CHAR_COORDINATES(ped13, -485.274, 187.437, 7.45208);//
								SET_CHAR_COORDINATES(ped14, -485.498, 188.362, 7.45208);//
								SET_CHAR_COORDINATES(ped19, -485.487, 189.271, 7.45208);//
								SET_CHAR_COORDINATES(ped15, -485.162, 190.212, 7.45208);//
								SET_CHAR_COORDINATES(ped16, -490.716, 197.451, 7.45208);//
								SET_CHAR_COORDINATES(ped17, -490.547, 196.481, 7.45208);//
								SET_CHAR_COORDINATES(ped18, -490.706, 195.477, 7.45208);//
								SET_CHAR_COORDINATES(ped4, -490.672, 192.595, 7.45208);//
								SET_CHAR_COORDINATES(ped5, -490.405, 193.572, 7.45208);//
								SET_CHAR_COORDINATES(ped6, -490.636, 194.561, 7.45208);//

								SET_CHAR_HEADING(ped4, 90.0);
								SET_CHAR_HEADING(ped5, 90.0);
								SET_CHAR_HEADING(ped6, 90.0);
								SET_CHAR_HEADING(ped12, 90.0);
								SET_CHAR_HEADING(ped13, 90.0);
								SET_CHAR_HEADING(ped14, 90.0);
								SET_CHAR_HEADING(ped15, 90.0);
								SET_CHAR_HEADING(ped16, 90.0);
								SET_CHAR_HEADING(ped17, 90.0);
								SET_CHAR_HEADING(ped18, 90.0);
								SET_CHAR_HEADING(ped19, 90.0);

								SET_CHAR_COORDINATES(ped1, -486.617, 196.802, 7.45208);//
								SET_CHAR_COORDINATES(ped2, -485.347, 193.884, 7.45208);//
								SET_CHAR_COORDINATES(GetPlayerPed(), -486.106, 195.6, 8.50807);//
								SET_CHAR_HEADING(ped1, 90.0);
								SET_CHAR_HEADING(ped2, 155.0);
								SET_CHAR_HEADING(GetPlayerPed(), 90.0);

								TASK_AIM_GUN_AT_COORD(GetPlayerPed(), -490.706, 195.477, 7.45208, 1);
								TASK_AIM_GUN_AT_COORD(ped1, -490.547, 196.48, 8.34914, 15000);

								//анимация поднятых рук тут
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped4, "armsup_loop", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "idle", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "armsup_loop", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped12, "armsup_loop", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped13, "idle", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped14, "armsup_loop", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped15, "idle", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped16, "armsup_loop", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped17, "idle", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped18, "idle", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped19, "armsup_loop", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped20, "duck_cower", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								SetTime(300);

								DO_SCREEN_FADE_IN( 100 );// убирается затемнение экрана
								SetTime(3000);

								//меняем рукурс тут
								POINT_CAM_AT_COORD	( camera, -487.419, 194.709, 9.25713 ); // куда смотрит камера
								SET_CAM_POS			( camera, -482.358, 202.035, 11.3139 );//расположение камеры

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_EM", "BNK4_9", 0, 0);//Phil, hold down the fort!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_FA", "BNK4_10", 0, 0);//Wilco roger that!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_FB", "BNK4_11", 0, 0);//Come on Cam, the vault's upstairs...
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								// убираем камеру
								SET_CAM_BEHIND_PED( GetPlayerPed() );
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								END_CAM_COMMANDS( &camera );
								SET_WIDESCREEN_BORDERS( 0 );

								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

								SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_MP5, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_MP5, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_MP5, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_MP5, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_MP5, TRUE);

								SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
								SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
								SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);
								SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
								SET_CHAR_RELATIONSHIP_GROUP(ped11, 5);

								SET_CHAR_RELATIONSHIP(ped7, 5, 0);
								SET_CHAR_RELATIONSHIP(ped8, 5, 0);
								SET_CHAR_RELATIONSHIP(ped9, 5, 0);
								SET_CHAR_RELATIONSHIP(ped10, 5, 0);
								SET_CHAR_RELATIONSHIP(ped11, 5, 0);

								SET_SENSE_RANGE(ped7, 10.0);
								SET_SENSE_RANGE(ped8, 10.0);
								SET_SENSE_RANGE(ped9, 10.0);
								SET_SENSE_RANGE(ped10, 10.0);
								SET_SENSE_RANGE(ped11, 10.0);

								SET_CHAR_WILL_USE_COVER(ped7, 1);
								SET_CHAR_WILL_USE_COVER(ped8, 1);
								SET_CHAR_WILL_USE_COVER(ped9, 1);
								SET_CHAR_WILL_USE_COVER(ped10, 1);
								SET_CHAR_WILL_USE_COVER(ped11, 1);

								TASK_AIM_GUN_AT_COORD(ped2, -490.706, 195.477, 7.45208, 1);

								ADD_BLIP_FOR_COORD(-505.972 ,181.342, 11.6755, &malibu_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"
								break;
							}
						}
						else
						{
							if (start == 0)
							{
								REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped3, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_EF", "BNK4_3V", 0, 0);//Hey Tommy, why have we stopped?
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();
								SetTime(1000);
								
								ADD_BLIP_FOR_CAR(car1, &malibu_ico);
								CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(malibu_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_CAR");//иконка на радаре называние в истории карты ""
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "GETCAR", 5000, 1);//~g~Get in the getaway car to do the bank job!
								start = 1;
							}
						}

						GET_CHAR_HEALTH(ped1, &Phil_hp);
						GET_CHAR_HEALTH(ped2, &Cam_hp);
						GET_CHAR_HEALTH(ped20, &Manager_hp);
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						else if (Phil_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped1);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "P_DEAD", 5000, 1);//~r~Phil's dead!!
							skip = 1;
							break;
						}
						else if (Cam_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped2);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "C_DEAD", 5000, 1);//~r~Cam's dead!!
							skip = 1;
							break;
						}
						else if (Manager_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped20);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BM_DEAD", 5000, 1);//~r~You needed the bank manager alive!!
							skip = 1;
							break;
						}
						else if ((IS_CHAR_DEAD(ped3)) || (IS_CHAR_FATALLY_INJURED(ped3)))//если пед мёртв или фатально ранен.
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "H_DEAD", 5000, 1);//~r~Hilary's dead!!
							skip = 1;
							break;
						}
					}
				}

				// часть 3 (войти в подвал)
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						// Кэм сталкерит за Томми тут
						GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+15, PedY+15, PedZ+15, PedX-15, PedY-15, PedZ-15, 0 ))
						{
							if (stalking == 0)
							{
								TASK_GO_TO_CHAR( ped2, GetPlayerPed(), -1, 13.50000000 );
								stalking = 1;
							}

							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &stalkerR);//проверка "игрок на координатах"
							if ((stalkerR < 1.2) && (stalking == 1) && (in_car == 0))
							{
								stalking = 2;
								TASK_GO_STRAIGHT_TO_COORD(ped2, PedX, PedY, PedZ, 4, -2);
							}
							else if ((stalkerR > 3.0) && (stalking == 2) && (in_car == 0))
							{
								stalking = 0;
							}

							if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (in_car == 0))
							{
								in_car = 1;
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car1);
								TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, -1, 0);
								SETTIMERB( 0 );
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped2))
								{
									in_car = 0;
									TASK_LEAVE_CAR(ped2, car1);
									MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
									TASK_GO_TO_CHAR( ped2, GetPlayerPed(), -1, 13.50000000 );
									stalking = 1;
								}
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped2)) && (in_car == 1) && (TIMERB() > 15000))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped2, car1, 0);
							}
						}
						else
						{
							if (stalking == 1)
							{
								stalking = 0;
								TASK_GO_STRAIGHT_TO_COORD(ped2, PedX, PedY, PedZ, 4, -2);
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "HEY", 5000, 1);//~COL_NET_12~Don't go solo, keep your posse together!
							}
						}

						DRAW_CHECKPOINT( -505.972 ,181.342, 11.6755, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -505.972 ,181.342, 11.6755, &PlayR);//проверка "игрок на координатах"
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -505.972 ,181.342, 11.6755, &PedR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && ( PedR < 2.0) &&(!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							// телепорт в подвал тут
							DO_SCREEN_FADE_OUT( 100 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())//если игрок мёртв или аврестован, если лодка унечтожена
								{
									break;
								}
							}
							SET_CHAR_COORDINATES(GetPlayerPed(), -505.624, 181.022, 1.396);//
							SET_CHAR_COORDINATES(ped2, -506.501, 181.473, 1.396);//
							SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_UNARMED, TRUE);
							
							SET_CHAR_HEADING(GetPlayerPed(), -90.0);
							SET_CHAR_HEADING(ped2, -90.0);
							SET_CHAR_RELATIONSHIP_GROUP(ped11, 3);
							SetTime(500);
							DO_SCREEN_FADE_IN( 100 );// убирается затемнение экрана

							REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_COORD(-511.607, 190.587, 1.1637, &malibu_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"

						}

						DRAW_CHECKPOINT( -511.607, 190.587, 1.1637, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -511.607, 190.587, 1.1637, &PlayR);//проверка "игрок на координатах"
						if ( PlayR < 1.5)
						{
							// сценка с сейфон тут
							REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_UNARMED, TRUE);

							//ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -512.911, 189.714, 2.58847 ); // куда смотрит камера
							SET_CAM_POS			( camera, -509.338, 188.727, 3.05347 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							SET_CHAR_COORDINATES(GetPlayerPed(), -512.043, 191.002, 1.34873);//
							SET_CHAR_HEADING(GetPlayerPed(), 155.0);

							SET_CHAR_COORDINATES(ped2, -505.712, 189.148, 1.7156);//
							SET_CHAR_HEADING(ped2, 90.0);
							
							TASK_GO_STRAIGHT_TO_COORD(ped2, -511.942, 189.187, 1.7156, 4, -2);

							REQUEST_ANIMS( "amb@atm" );//загружаем файл с анимацией
							while (!HAVE_ANIMS_LOADED( "amb@atm" )) WAIT(0);

							REQUEST_ANIMS( "amb@hang_str_idls" );
							while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);
							SetTime(2000);

							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "m_takecash", "amb@atm", 1.0, 0, 0, 0, 1, 5000 );//Воиспроизвидение анимации на педе
							SetTime(3000);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_FC", "BK4_12A", 0, 0);//Damn! It's a Flange 9000!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
		
							SET_CHAR_HEADING(ped2, -15.0);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 4000 );//Воиспроизвидение анимации на педе
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_FD", "BK4_12B", 0, 0);//This could take hours to crack,
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_FE", "BK4_12C", 0, 0);//Or five minutes if you could find the manager.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 2500 );//Воиспроизвидение анимации на педе
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_FF", "BNK4_13", 0, 0);//I'll go find where he's holed up.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );

							ofice = 0;
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							break;
						}

						GET_CHAR_HEALTH(ped1, &Phil_hp);
						GET_CHAR_HEALTH(ped2, &Cam_hp);
						GET_CHAR_HEALTH(ped20, &Manager_hp);
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						else if (Phil_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped1);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "P_DEAD", 5000, 1);//~r~Phil's dead!!
							skip = 1;
							break;
						}
						else if (Cam_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped2);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "C_DEAD", 5000, 1);//~r~Cam's dead!!
							skip = 1;
							break;
						}
						else if (Manager_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped20);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BM_DEAD", 5000, 1);//~r~You needed the bank manager alive!!
							skip = 1;
							break;
						}
						else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -460.464, 189.008, 7.117, -464.092, 194.982, 10.864, 0 ))
						{
							EXPLODE_CHAR_HEAD(ped20);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "IDIOT", 5000, 1);//~r~ That's right, just wander about dressed like a lunatic and draw attention to yourself, IDIOT!
							skip = 1;
							break;
						}
					}
				}
				// часть 4 (найти Менеджера)
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						DRAW_CHECKPOINT( -506.259, 181.417, 1.1637, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -506.259, 181.417, 1.1637, &PlayR);//проверка "игрок на координатах"
						if ( PlayR < 1.5 )
						{
							// телепорт из подвала тут
							SET_CHAR_COORDINATES(ped1, -486.617, 196.802, 7.45208);//
							SET_CHAR_HEADING(ped1, 90.0);

							DO_SCREEN_FADE_OUT( 100 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())//если игрок мёртв или аврестован, если лодка унечтожена
								{
									break;
								}
							}

							SET_CHAR_COORDINATES(GetPlayerPed(), -505.972, 181.342, 11.8297);//
							SET_CHAR_HEADING(GetPlayerPed(), -95.0);
							
							SetTime(500);
							DO_SCREEN_FADE_IN( 100 );// убирается затемнение экрана

							in_car = 0;
							stalking = 0;
						}

						// диалог с филом тут
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -485.816, 185.576, 10.977, -492.374, 196.418, 16.256, 0 )) && (text == 0))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_FG", "BK4_14A", 0, 0);//Phil, things still sweet?
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							text = 1;
						}
						if (text == 1)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_FH", "BNK4_15", 0, 0);//Sure. Everything's reeaal quiet.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							text = 5;
						}

						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -529.721, 193.812, 9.267, -534.721, 198.812, 13.267, 0 )) && (ofice == 0))
						{
							// сценка тут
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							//ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -531.318, 196.715, 10.8963 ); // куда смотрит камера
							SET_CAM_POS			( camera, -529.515, 201.811, 11.3144 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							TASK_AIM_GUN_AT_CHAR(GetPlayerPed(), ped20, 4000);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped20, "armsup_loop", "ne_missbank", 1.0, 1, 0, 0, 0, 3000 );//Воиспроизвидение анимации на педе

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_FI", "BNK4_16", 0, 0);//You - you're coming with me!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped20, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_FJ", "BNK4_17", 0, 0);//Ok! Ok! Just don't shoot!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							ADD_BLIP_FOR_COORD(-505.972 ,181.342, 11.6755, &malibu_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"
							SET_CHAR_RELATIONSHIP_GROUP(ped20, 0);
							ofice = 1;
							break;
						}
						GET_CHAR_HEALTH(ped1, &Phil_hp);
						GET_CHAR_HEALTH(ped2, &Cam_hp);
						GET_CHAR_HEALTH(ped20, &Manager_hp);
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						else if (Phil_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped1);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "P_DEAD", 5000, 1);//~r~Phil's dead!!
							skip = 1;
							break;
						}
						else if (Cam_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped2);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "C_DEAD", 5000, 1);//~r~Cam's dead!!
							skip = 1;
							break;
						}
						else if (Manager_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped20);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BM_DEAD", 5000, 1);//r~You needed the bank manager alive!!
							skip = 1;
							break;
						}
						else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -460.464, 189.008, 7.117, -464.092, 194.982, 10.864, 0 ))
						{
							EXPLODE_CHAR_HEAD(ped20);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "IDIOT", 5000, 1);//~r~ That's right, just wander about dressed like a lunatic and draw attention to yourself, IDIOT!
							skip = 1;
							break;
						}
					}
				}
				// часть 5 (Менеджер)
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						// Менеджер сталкерит за Томми тут
						GET_CHAR_COORDINATES(ped20,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), PedX+15, PedY+15, PedZ+15, PedX-15, PedY-15, PedZ-15, 0 ))
						{
							if (stalking == 0)
							{
								TASK_GO_TO_CHAR( ped20, GetPlayerPed(), -1, 13.50000000 );
								stalking = 1;
							}

							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, PedX, PedY, PedZ, &stalkerR);//проверка "игрок на координатах"
							if ((stalkerR < 1.2) && (stalking == 1) && (in_car == 0))
							{
								stalking = 2;
								TASK_GO_STRAIGHT_TO_COORD(ped20, PedX, PedY, PedZ, 4, -2);
							}
							else if ((stalkerR > 3.0) && (stalking == 2) && (in_car == 0))
							{
								stalking = 0;
							}

							if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_SITTING_IN_ANY_CAR(ped20)) && (in_car == 0))
							{
								in_car = 1;
								GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car1);
								TASK_ENTER_CAR_AS_PASSENGER(ped20, car1, -1, 0);
								SETTIMERB( 0 );
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (in_car == 1))
							{
								if (IS_CHAR_SITTING_IN_ANY_CAR(ped20))
								{
									in_car = 0;
									TASK_LEAVE_CAR(ped20, car1);
									MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
									TASK_GO_TO_CHAR( ped20, GetPlayerPed(), -1, 13.50000000 );
									stalking = 1;
								}
							}
							else if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped20)) && (in_car == 1) && (TIMERB() > 15000))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped20, car1, 0);
							}
						}
						else
						{
							if (stalking == 1)
							{
								stalking = 0;
								TASK_GO_STRAIGHT_TO_COORD(ped20, PedX, PedY, PedZ, 4, -2);
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "HEY", 5000, 1);//~COL_NET_12~Don't go solo, keep your posse together!
							}
						}

						// диалог с филом 2 тут
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -485.816, 185.576, 10.977, -492.374, 196.418, 16.256, 0 )) && (text == 5))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_FJ_QQQ1", "BNK4_18", 0, 0);//I SAID NOBODY MOVE!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							text = 6;
						}

						DRAW_CHECKPOINT( -505.972 ,181.342, 11.6755, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -505.972 ,181.342, 11.6755, &PlayR);//проверка "игрок на координатах"
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -505.972 ,181.342, 11.6755, &PedR);//проверка "игрок на координатах"
						if (( PlayR < 1.5 ) && ( PedR < 2.0 ))
						{
							// телепорт в подвал тут
							DO_SCREEN_FADE_OUT( 100 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())//если игрок мёртв или аврестован, если лодка унечтожена
								{
									break;
								}
							}

							SET_CHAR_COORDINATES(GetPlayerPed(), -505.624, 181.022, 1.396);//
							SET_CHAR_COORDINATES(ped20, -506.501, 181.473, 1.396);//
							
							SET_CHAR_HEADING(GetPlayerPed(), -90.0);
							SET_CHAR_HEADING(ped20, -90.0);
							SetTime(500);
							DO_SCREEN_FADE_IN( 100 );// убирается затемнение экрана

							SET_CHAR_COORDINATES(ped2, -512.238, 189.766, 2.15844);//
							SET_CHAR_HEADING(ped2, 90.0);

							// анимация тут
							SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_UNARMED, TRUE);
							REQUEST_ANIMS( "amb@telescope_idles" );
							while (!HAVE_ANIMS_LOADED( "amb@telescope_idles" )) WAIT(0);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_focus", "amb@telescope_idles", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе

							REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_COORD(-511.607, 190.587, 1.1637, &malibu_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"
						}

						DRAW_CHECKPOINT( -511.607, 190.587, 1.1637, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -511.607, 190.587, 1.1637, &PlayR);//проверка "игрок на координатах"
						if ( PlayR < 1.5)
						{
							// сценка с менеджером и Кэмом тут
							REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							//ставим камеру
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -512.911, 189.714, 2.58847 ); // куда смотрит камера
							SET_CAM_POS			( camera, -509.338, 188.727, 3.05347 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							SET_CHAR_COORDINATES(GetPlayerPed(), -512.043, 191.002, 1.34873);//
							SET_CHAR_HEADING(GetPlayerPed(), 155.0);

							SET_CHAR_COORDINATES(ped20, -505.712, 189.148, 1.7156);//
							SET_CHAR_HEADING(ped20, 90.0);
							TASK_AIM_GUN_AT_CHAR(GetPlayerPed(), ped20, 15000);

							TASK_GO_STRAIGHT_TO_COORD(ped20, -511.599, 189.165, 1.7156, 4, -2);

							REQUEST_ANIMS( "amb@hang_str_idls" );
							while (!HAVE_ANIMS_LOADED( "amb@hang_str_idls" )) WAIT(0);
							SetTime(2000);

							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped20, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 4000 );//Воиспроизвидение анимации на педе
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped20, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_FK", "BK4_19A", 0, 0);//It's on a time lock,
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped20, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_FL", "BK4_19B", 0, 0);//You might as well give up now!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// меняем рукурс тут
							POINT_CAM_AT_COORD	( camera, -512.116, 189.801, 2.58513 ); // куда смотрит камера
							SET_CAM_POS			( camera, -509.971, 191.126, 2.93867 );//расположение камеры
							SET_CHAR_HEADING(ped2, -110.0);

							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_idle_a", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 4500 );//Воиспроизвидение анимации на педе
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_FM", "BK4_20A", 0, 0);//Hell, I can bypass the time lock,
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_FN", "BK4_20B", 0, 0);//Then we just need your key code and we're good!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// меняем рукурс тут
							POINT_CAM_AT_COORD	( camera, -511.617, 190.426, 2.5707 ); // куда смотрит камера
							SET_CAM_POS			( camera, -510.123, 188.832, 3.19552 );//расположение камеры

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_FO", "BNK4_21", 0, 0);//Stay here. You try anything and you're dead.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_GA", "BK4_24A", 0, 0);//I'm gonna check on Phil, I'll be right back.
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );

							ofice = 0;
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

							REMOVE_PICKUP(aid_1);
							REMOVE_PICKUP(arm_1);
							CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -528.916, 197.563, 10.4561, -90.0, 0.0, -40.0, &aid_1);//Аптека
							CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, -524.597, 194.829, 9.5785, -10.0, 0.0, 90.0, &arm_1);
							ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(aid_1, "bank_int");
							ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(arm_1, "bank_int");
							break;
						}
						GET_CHAR_HEALTH(ped1, &Phil_hp);
						GET_CHAR_HEALTH(ped2, &Cam_hp);
						GET_CHAR_HEALTH(ped20, &Manager_hp);
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						else if (Phil_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped1);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "P_DEAD", 5000, 1);//~r~Phil's dead!!
							skip = 1;
							break;
						}
						else if (Cam_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped2);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "C_DEAD", 5000, 1);//~r~Cam's dead!!
							skip = 1;
							break;
						}
						else if (Manager_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped20);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BM_DEAD", 5000, 1);//~r~You needed the bank manager alive!!
							skip = 1;
							break;
						}
						else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -460.464, 189.008, 7.117, -464.092, 194.982, 10.864, 0 ))
						{
							EXPLODE_CHAR_HEAD(ped20);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "IDIOT", 5000, 1);//~r~ That's right, just wander about dressed like a lunatic and draw attention to yourself, IDIOT!
							skip = 1;
							break;
						}
					}
				}
				// часть 6 (Сигнализвция тут)
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						DRAW_CHECKPOINT( -506.259, 181.417, 1.1637, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -506.259, 181.417, 1.1637, &PlayR);//проверка "игрок на координатах"
						if ( PlayR < 1.5 )
						{
							// телепорт из подвала тут
							SET_CHAR_COORDINATES(ped1, -486.617, 196.802, 7.45208);//
							SET_CHAR_HEADING(ped1, 90.0);

							DO_SCREEN_FADE_OUT( 100 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if (IS_SCREEN_FADED_OUT())//если игрок мёртв или аврестован, если лодка унечтожена
								{
									break;
								}
							}

							SET_CHAR_COORDINATES(GetPlayerPed(), -505.972, 181.342, 11.8297);//
							SET_CHAR_HEADING(GetPlayerPed(), -95.0);
							
							SetTime(500);
							DO_SCREEN_FADE_IN( 100 );// убирается затемнение экрана
						}

						// активация сирены
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -487.357, 182.336, 10.977, -493.914, 193.178, 16.256, 0 )) && (text == 6))
						{
							while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/RB4_MUSEUM_PIECE" )))
							{
								 WAIT(0);
							}
							AudID1 = GET_SOUND_ID();
							PLAY_SOUND_FROM_POSITION(AudID1, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", -486.557, 191.661, 11.5546);
							AudID2 = GET_SOUND_ID();
							PLAY_SOUND_FROM_POSITION(AudID2, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", -468.608, 192.402, 11.5546);
							AudID3 = GET_SOUND_ID();
							PLAY_SOUND_FROM_POSITION(AudID3, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", -503.277, 196.638, 13.2252);
							siren = 1;

							TASK_SHOOT_AT_CHAR(ped1, ped5, 2000, 3);
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_GB", "BK4_24B", 0, 0);//I told you not to touch that alarm!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							text = 7;
						}

						if (text == 7)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_GC", "BNK4_25", 0, 0);//The SWAT team will be here any minute!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							text = 8;
						}
						else if (text == 8)
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_GD", "BNK4_27", 0, 0);//I could do with some help here, Tommy!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
							ADD_BLIP_FOR_COORD(-475.711, 186.124, 7.27132, &malibu_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"
							text = 11;
						}
						else if (text == 11)
						{
							DRAW_CHECKPOINT( -475.711, 186.124, 7.27132, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
							GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -475.711, 186.124, 7.27132, &PlayR);//проверка "игрок на координатах"
							if ( PlayR < 1.5 )
							{
								//сценка свата тут
								REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

								//ставим камеру
								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, -473.393, 188.707, 8.06266 ); // куда смотрит камера
								SET_CAM_POS			( camera, -481.303 ,184.286, 9.44313 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );

								SET_CHAR_COORDINATES(ped1, -485.882, 196.765, 8.27248);//
								SET_CHAR_COORDINATES(ped2, -487.619, 190.331, 12.7619);//
								SET_CHAR_HEADING(ped1, -105.0);
								SET_CHAR_HEADING(ped2, -95.0);

								// анимация сидит тут
								TASK_AIM_GUN_AT_COORD(ped1, -467.162, 192.066, 7.96181, 35000);
								TASK_AIM_GUN_AT_COORD(GetPlayerPed(), -467.162, 192.066, 7.96181, 35000);

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_HA", "BNK4_28", 0, 0);//Vice City S.W.A.T! You are completely surrounded!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								//смена ракурса
								POINT_CAM_AT_COORD	( camera, -486.376, 196.099, 8.27248 ); // куда смотрит камера
								SET_CAM_POS			( camera, -482.862, 200.307, 8.71806 );//расположение камеры

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_HB", "BNK4_29", 0, 0);//Surrounded? HA HA HA HAAAAAaaa!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R11_HC", "BNK4_30", 0, 0);//They're crapping themselves, corrupt bastards!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								//смена ракурса
								POINT_CAM_AT_COORD	( camera, -488.342, 189.787, 12.9145 ); // куда смотрит камера
								SET_CAM_POS			( camera, -483.745, 193.284, 13.9819 );//расположение камеры

								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "stand_idle_k", "amb@hang_str_idls", 8.0, 1, 0, 0, 0, 4000 );//Воиспроизвидение анимации на педе
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_HD", "BK4_31A", 0, 0);//Tommy! The vault's open!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();
								
								//смена ракурса
								POINT_CAM_AT_COORD	( camera, -475.975, 186.265, 8.92755 ); // куда смотрит камера
								SET_CAM_POS			( camera, -473.094, 187.357, 8.62006 );//расположение камеры

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_IA", "BK4_34A", 0, 0);//Ok, we got the SWAT retirement fund. Let's get out of here!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								//смена ракурса
								POINT_CAM_AT_COORD	( camera, -473.393, 188.707, 8.06266 ); // куда смотрит камера
								SET_CAM_POS			( camera, -481.303 ,184.286, 9.44313 );//расположение камеры


								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_IB", "BK4_34B", 0, 0);//Ok, you asked for it! You've had your last chance!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								//смена ракурса
								POINT_CAM_AT_COORD	( camera, -486.376, 196.099, 8.27248 ); // куда смотрит камера
								SET_CAM_POS			( camera, -482.862, 200.307, 8.71806 );//расположение камеры
								
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R11_IC", "BK4_35A", 0, 0);//They're storming the place!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_ID", "BK4_35B", 0, 0);//Take cover!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								// убираем камеру
								SET_CAM_BEHIND_PED( GetPlayerPed() );
								ACTIVATE_SCRIPTED_CAMS( 0, 0 );
								END_CAM_COMMANDS( &camera );
								SET_WIDESCREEN_BORDERS( 0 );

								TASK_AIM_GUN_AT_COORD(ped1, -467.162, 192.066, 7.96181, 1);
								TASK_AIM_GUN_AT_COORD(GetPlayerPed(), -467.162, 192.066, 7.96181, 1);
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

								// перезапись педов тут
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//выгружаем модель педа(в последствии пед изчезнет
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped9);//выгружаем модель педа(в последствии пед изчезнет
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped10);//выгружаем модель педа(в последствии пед изчезнет
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped11);//выгружаем модель педа(в последствии пед изчезнет
								MARK_CHAR_AS_NO_LONGER_NEEDED(&ped20);//выгружаем модель педа(в последствии пед изчезнет

								CREATE_CHAR (26, PedM7, 297.365, -781.535, 5.05974, &ped7, TRUE);// SWAT
								CREATE_CHAR (26, PedM7, 298.611, -781.535, 5.05974, &ped8, TRUE);// SWAT
								CREATE_CHAR (26, PedM7, 299.856, -781.535, 5.05974, &ped9, TRUE);// SWAT
								CREATE_CHAR (26, PedM7, 301.101, -781.535, 5.05974, &ped10, TRUE);// SWAT
								CREATE_CHAR (26, PedM7, 302.347, -781.535, 5.05974, &ped11, TRUE);// SWAT
								CREATE_CHAR (26, PedM7, 303.424, -779.729, 5.05974, &ped20, TRUE);// SWAT

								SET_CHAR_COORDINATES(ped7, -482.714, 196.396, 19.6456);//
								SET_CHAR_COORDINATES(ped8, -482.714, 187.498, 19.6456);//
								SET_CHAR_COORDINATES(ped9, -474.621, 196.396, 19.6456);//
								SET_CHAR_COORDINATES(ped10, -474.621, 187.498, 19.6456);//
								SET_CHAR_COORDINATES(ped11, -466.528, 199.344, 16.8553);//
								SET_CHAR_COORDINATES(ped20, -466.528, 184.535, 16.8553);//

								SET_CHAR_VISIBLE(ped7, 0);
								SET_CHAR_VISIBLE(ped8, 0);
								SET_CHAR_VISIBLE(ped9, 0);
								SET_CHAR_VISIBLE(ped10, 0);
								SET_CHAR_VISIBLE(ped11, 0);
								SET_CHAR_VISIBLE(ped20, 0);

								// дымовые шашки тут
								PTFX = START_PTFX( "smoke_vault_lingers", -482.714, 187.498, 7.36482, 0.0, 0.0, 0.0, 1065353216 );
								PTFX2 = START_PTFX( "smoke_vault_lingers", -482.714, 196.396, 7.36482, 0.0, 0.0, 0.0, 1065353216 );
								PTFX3 = START_PTFX( "smoke_vault_lingers", -474.621, 187.498, 7.36482, 0.0, 0.0, 0.0, 1065353216 );
								PTFX4 = START_PTFX( "smoke_vault_lingers", -474.621, 196.396, 7.36482, 0.0, 0.0, 0.0, 1065353216 );
								smoke_on = 1;
								SetTime(700);

								// анимация свата тут
								SET_CHAR_COORDINATES(ped7, -516.673, 185.588, 1.28735);//
								SET_CHAR_COORDINATES(ped8, -516.673, 186.354, 1.28735);//
								SET_CHAR_COORDINATES(ped9, -516.673, 187.121, 1.28735);//
								SET_CHAR_COORDINATES(ped10, -516.673, 187.885, 1.28735);//
								SET_CHAR_COORDINATES(ped11, -516.673, 188.651, 1.28735);//
								SET_CHAR_COORDINATES(ped20, -516.673, 189.417, 1.28735);//
								SetTime(1500);

								SET_CHAR_COORDINATES(ped7, -482.714, 196.396, 7.36482);//
								SET_CHAR_COORDINATES(ped8, -482.714, 187.498, 7.36482);//
								SET_CHAR_COORDINATES(ped9, -474.621, 196.396, 7.36482);//
								SET_CHAR_COORDINATES(ped10, -474.621, 187.498, 7.36482);//
								SET_CHAR_COORDINATES(ped11, -466.528, 199.344, 11.7358);//
								SET_CHAR_COORDINATES(ped20, -466.528, 184.535, 11.7358);//

								// верёвки тут
								SET_OBJECT_COORDINATES(wire1, -466.688, 199.385, 19.2636);
								SET_OBJECT_COORDINATES(wire2, -466.688, 184.576, 19.2636);
								SET_OBJECT_COORDINATES(wire3, -474.781, 196.437, 14.8121);
								SET_OBJECT_COORDINATES(wire4, -474.781, 187.539, 14.8121);
								SET_OBJECT_COORDINATES(wire5, -482.874, 196.437, 14.8121);
								SET_OBJECT_COORDINATES(wire6, -482.874, 187.539, 14.8121);

								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "bank_swat_rope", "ne_missbank", 100.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped8, "bank_swat_rope", "ne_missbank", 100.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped9, "bank_swat_rope", "ne_missbank", 100.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped10, "bank_swat_rope", "ne_missbank", 100.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped11, "bank_swat_rope", "ne_missbank", 100.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped20, "bank_swat_rope", "ne_missbank", 100.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
								SetTime(100);

								SET_CHAR_VISIBLE(ped7, 1);
								SET_CHAR_VISIBLE(ped8, 1);
								SET_CHAR_VISIBLE(ped9, 1);
								SET_CHAR_VISIBLE(ped10, 1);
								SET_CHAR_VISIBLE(ped11, 1);
								SET_CHAR_VISIBLE(ped20, 1);
								SetTime(2500);

								UpdateWeaponOfPed(ped7, WEAPON_MP5);
								UpdateWeaponOfPed(ped8, WEAPON_MP5);
								UpdateWeaponOfPed(ped9, WEAPON_MP5);
								UpdateWeaponOfPed(ped10, WEAPON_MP5);
								UpdateWeaponOfPed(ped11, WEAPON_MP5);
								UpdateWeaponOfPed(ped20, WEAPON_MP5);

								SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_MP5, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_MP5, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_MP5, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_MP5, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_MP5, TRUE);
								SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_MP5, TRUE);

								SET_CHAR_WILL_USE_COVER(ped7, 1);
								SET_CHAR_WILL_USE_COVER(ped8, 1);
								SET_CHAR_WILL_USE_COVER(ped9, 1);
								SET_CHAR_WILL_USE_COVER(ped10, 1);
								SET_CHAR_WILL_USE_COVER(ped11, 1);
								SET_CHAR_WILL_USE_COVER(ped20, 1);

								SET_CHAR_SHOOT_RATE(ped7, 25);
								SET_CHAR_SHOOT_RATE(ped8, 25);
								SET_CHAR_SHOOT_RATE(ped9, 25);
								SET_CHAR_SHOOT_RATE(ped10, 25);
								SET_CHAR_SHOOT_RATE(ped11, 25);
								SET_CHAR_SHOOT_RATE(ped20, 25);

								TASK_COMBAT(ped7, GetPlayerPed());
								TASK_COMBAT(ped8, GetPlayerPed());
								TASK_COMBAT(ped9, GetPlayerPed());
								TASK_COMBAT(ped10, GetPlayerPed());
								TASK_COMBAT(ped11, GetPlayerPed());
								TASK_COMBAT(ped20, GetPlayerPed());

								PANIC_SCREAM(ped4);
								PANIC_SCREAM(ped5);
								PANIC_SCREAM(ped6);
								PANIC_SCREAM(ped12);
								PANIC_SCREAM(ped13);
								PANIC_SCREAM(ped14);
								PANIC_SCREAM(ped15);
								PANIC_SCREAM(ped16);
								PANIC_SCREAM(ped17);
								PANIC_SCREAM(ped18);
								PANIC_SCREAM(ped19);

								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped4, -438.752, 203.373, 5.10573, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped5, -496.498, 190.509, 11.9341, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped6, -474.414, 193.046, 7.5367, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped12, -521.891, 193.618, 9.79606, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped13, -527.531, 197.377, 9.79606, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped14, -527.531, 197.377, 9.79606, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped15, -496.498, 190.509, 11.9341, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped16, -438.752, 203.373, 5.10573, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped17, -438.752, 203.373, 5.10573, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped18, -496.498, 190.509, 11.9341, 3, -2, 1.5);// пед убегает
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped19, -438.752, 203.373, 5.10573, 3, -2, 1.5);// пед убегает
								text = 11;
								break;
							}
						}
						GET_CHAR_HEALTH(ped1, &Phil_hp);
						GET_CHAR_HEALTH(ped2, &Cam_hp);
						GET_CHAR_HEALTH(ped20, &Manager_hp);
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						else if (Phil_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped1);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "P_DEAD", 5000, 1);//~r~Phil's dead!!
							skip = 1;
							break;
						}
						else if (Cam_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped2);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "C_DEAD", 5000, 1);//~r~Cam's dead!!
							skip = 1;
							break;
						}
						else if (Manager_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped20);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "BM_DEAD", 5000, 1);//~r~You needed the bank manager alive!!
							skip = 1;
							break;
						}
						else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -460.464, 189.008, 7.117, -464.092, 194.982, 10.864, 0 ))
						{
							EXPLODE_CHAR_HEAD(ped20);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "IDIOT", 5000, 1);//~r~ That's right, just wander about dressed like a lunatic and draw attention to yourself, IDIOT!
							skip = 1;
							break;
						}
					}
				}
				// часть 7 (отбится от свата)
				if (skip == 0)
				{
					while (TRUE)
					{
						WAIT(0);
						if ((IS_CHAR_INJURED(ped7)) && (IS_CHAR_INJURED(ped8)) && (IS_CHAR_INJURED(ped9)) && (IS_CHAR_INJURED(ped10)) && (IS_CHAR_INJURED(ped11)) && (IS_CHAR_INJURED(ped20)))
						{
							if (text == 11)
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
								ADD_LINE_TO_CONVERSATION(0, "R11_IE", "BNK4_38", 0, 0);//That's the last of them. GO! GO! GO!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();
								TASK_GO_TO_CHAR( ped1, GetPlayerPed(), -1, 13.50000000 );
								TASK_GO_TO_CHAR( ped2, GetPlayerPed(), -1, 13.50000000 );
								text = 12;
							}
						}
						if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -460.464, 189.008, 7.117, -464.092, 194.982, 10.864, 0 ))
						{
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

							// сценка тут
							DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
							while(true)
							{
								WAIT(0);
								if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
								{
									break;
								}
							}

							//Грузим пути
							REQUEST_CAR_RECORDING( 3054 ); // полёт Основной
							while (!HAS_CAR_RECORDING_BEEN_LOADED( 3054 )) WAIT(0);

							// перезапись педов тут
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped9);//выгружаем модель педа(в последствии пед изчезнет
							MARK_CHAR_AS_NO_LONGER_NEEDED(&ped10);//выгружаем модель педа(в последствии пед изчезнет

							CREATE_CHAR (26, PedM7, -443.603, 185.213, 5.78294, &ped7, TRUE);// SWAT
							CREATE_CHAR (26, PedM7, -442.771, 198.861, 5.77261, &ped8, TRUE);// SWAT
							CREATE_CHAR (26, PedM7, -440.211, 191.641, 5.77261, &ped9, TRUE);// SWAT
							CREATE_CHAR (26, PedM7, -440.043, 192.477, 5.77261, &ped10, TRUE);// SWAT

							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped7, TRUE);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped8, TRUE);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped9, TRUE);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped10, TRUE);

							SET_CHAR_HEADING(ped7, 85.0);
							SET_CHAR_HEADING(ped8, 105.0);
							SET_CHAR_HEADING(ped9, 90.0);
							SET_CHAR_HEADING(ped10, 105.0);

							UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_13);
							UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_13);
														
							SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_13, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_13, TRUE);

							SET_CHAR_WILL_USE_COVER(ped7, 1);
							SET_CHAR_WILL_USE_COVER(ped8, 1);
							SET_CHAR_WILL_USE_COVER(ped9, 1);
							SET_CHAR_WILL_USE_COVER(ped10, 1);
							CLEAR_AREA(-439.298, 188.959, 5.5746, 25.0, 1);//очещаем зону загрузки

							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped9, "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе

							SET_CAR_COORDINATES(car2, -437.483, 187.569, 5.5746);//
							SET_CAR_COORDINATES(car3, -436.818, 196.805, 5.5746);//
							SET_CAR_HEADING(car2, 140.0);
							SET_CAR_HEADING(car3, 40.0);

							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -460.648, 184.102, 8.00638 ); // куда смотрит камера
							SET_CAM_POS			( camera, -456.774, 190.551, 9.63376 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							if (!IS_CHAR_DEAD(ped2))//если пед мёртв или фатально ранен.
							{
								SET_CHAR_COORDINATES(ped2, -461.179, 186.504, 7.70699);//
								SET_CHAR_HEADING(ped2, -75.0);
								TASK_GO_STRAIGHT_TO_COORD(ped2, -461.179, 186.504, 7.70699, 4, -2);
								TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
							}
							SetTime(250);

							SET_CHAR_COORDINATES(GetPlayerPed(), -458.924, 185.701, 7.95951);//
							SET_CHAR_COORDINATES(ped1, -461.234, 185.565, 7.70699);//
							SET_CHAR_HEADING(GetPlayerPed(), -30.0);
							SET_CHAR_HEADING(ped1, -75.0);
							TASK_GO_STRAIGHT_TO_COORD(ped1, -461.234, 185.565, 7.70699, 4, -2);
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
							SetTime(250);

							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped8, "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped10, "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе

							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
							SetTime(1000);

							if ((IS_CHAR_DEAD(ped2)) || (IS_CHAR_FATALLY_INJURED(ped2)))//если пед мёртв или фатально ранен.
							{
								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_KA", "BNK4_36", 0, 0);//Where's Cam?
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_KB", "BNK4_37", 0, 0);//History...
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();
							}

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_KC", "BNK_39", 0, 0);//Shit! Where's Hilary?
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// смена ракурса
							POINT_CAM_AT_COORD	( camera, -437.441, 192.311, 5.5746 ); // куда смотрит камера
							SET_CAM_POS			( camera, -458.979, 189.351, 13.2093 );//расположение камеры

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_KD", "BK4_40A", 0, 0);//I'll give him abandonment issues!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							// смена ракурса
							POINT_CAM_AT_COORD	( camera, -453.735, 194.054, 4.56173 ); // куда смотрит камера
							SET_CAM_POS			( camera, -435.722, 182.469, 10.2316 );//расположение камеры

							// заускаем RRR пути тут
							START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3054, 0.0, 0.0, 0.0);
							SET_PLAYBACK_SPEED(car1, 1.15);
							SetTime(2000);
							STOP_PLAYBACK_RECORDED_CAR(car1);
							REMOVE_CAR_RECORDING( 3054 ); // выгружаем пути транспорта
							TASK_LEAVE_CAR(ped3, car1);
							SetTime(1000);

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped3, "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_KE", "BNK4_42", 0, 0);//Hey guys! Get in! I got you covered!
							START_SCRIPT_CONVERSATION(1, 1);
							SetTime(1000);

							// смена ракурса
							POINT_CAM_AT_COORD	( camera, -452.554, 194.579, 6.3003 ); // куда смотрит камера
							SET_CAM_POS			( camera, -446.359, 188.088, 5.38462 );//расположение камеры
							
							TASK_SHOOT_AT_CHAR(ped3, ped10, 2000, 3);
							SetTime(1500);
							SetSpeech();

							SetTime(500);
							TASK_SHOOT_AT_CHAR(ped3, ped10, 1000, 3);
							SetTime(1000);

							TASK_SHOOT_AT_CHAR(ped7, ped3, 1000, 3);
							TASK_SHOOT_AT_CHAR(ped8, ped3, 1000, 3);
							SetTime(1500);

							EXPLODE_CHAR_HEAD(ped3);
							SetTime(1500);

							// убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );

							TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, 1 );//Воиспроизвидение анимации на педе
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, 1 );//Воиспроизвидение анимации на педе
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, 1 );//Воиспроизвидение анимации на педе

							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, 1 );//Воиспроизвидение анимации на педе
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped8, "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, 1 );//Воиспроизвидение анимации на педе
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped9, "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, 1 );//Воиспроизвидение анимации на педе
							TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped10, "swat_idle", "ne_missbank", 8.0, 1, 0, 0, 0, 1 );//Воиспроизвидение анимации на педе

							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// разморозить игрока

							SET_MAX_WANTED_LEVEL(6);
							ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
							APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());

							TASK_COMBAT(ped7, GetPlayerPed());
							TASK_COMBAT(ped8, GetPlayerPed());
							TASK_COMBAT(ped9, GetPlayerPed());
							TASK_COMBAT(ped10, GetPlayerPed());

							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped7, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped8, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped9, 0);
							SET_CHAR_MOVEMENT_ANIMS_BLOCKED(ped10, 0);

							MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
							del_car = 1;
							in_car = 0;
							stalking = 0;
							cop_on = 0;
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NEWANTED", 5000, 1);//~COL_NET_12~Shake the cops and lose your wanted level!
							break;
						}
						GET_CHAR_HEALTH(ped1, &Phil_hp);
						GET_CHAR_HEALTH(ped2, &Cam_hp);
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						else if (Phil_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped1);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "P_DEAD", 5000, 1);//~r~Phil's dead!!
							skip = 1;
							break;
						}
						else if (Cam_hp < 105)
						{
							if (!IS_CHAR_DEAD(ped2))
							{
								EXPLODE_CHAR_HEAD(ped2);
							}
						}
					}
				}
				// часть 8 ( убежище)
				if (skip == 0)
				{
					while (TRUE)
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
								else if ((!IS_CHAR_SITTING_IN_ANY_CAR(ped1)) && (in_car == 1))
								{
									in_car = 0;
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
						
						if (!IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0))
						{
							if (cop_on == 0)
							{
								ADD_BLIP_FOR_COORD(-412.747, -368.869, 4.94332, &malibu_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(malibu_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(malibu_ico, 5);   //цвет иконка на радаре (0=белая)
								CHANGE_BLIP_SCALE(malibu_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "NE_POINT");//иконка на радаре называние в истории карты "Особняк"
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NEBNK4_H", 5000, 1);//~g~Go to the hideout.
								cop_on = 1;
							}

							DRAW_CHECKPOINT( -412.747, -368.869, 4.94332, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет

							if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -392.541, -373.328, 4.324, -402.541, -363.328, 14.324, 0 ))
							{
								if (IS_GARAGE_CLOSED("camscan"))
								{
									OPEN_GARAGE("camscan");
								}
							}
							if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -408.116, -374.853, 4.985, -418.116, -364.853, 9.985, 0 )) && (IS_CHAR_IN_AREA_3D( ped1, -408.116, -374.853, 4.985, -418.116, -364.853, 9.985, 0 )))
							{
								// сценка тут
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
								CLOSE_GARAGE("camscan");

								DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
								while(true)
								{
									WAIT(0);
									if (IS_SCREEN_FADED_OUT())
									{
										break;
									}
								}

								CREATE_CAM( 14, &camera );
								POINT_CAM_AT_COORD	( camera, -411.427, -374.904, 5.49129 ); // куда смотрит камера
								SET_CAM_POS			( camera, -383.808, -354.336, 15.6692 );//расположение камеры
								SET_CAM_ACTIVE( camera, 1 );
								SET_CAM_PROPAGATE( camera, 1 );
								ACTIVATE_SCRIPTED_CAMS(1, 1);
								SET_CAM_FOV( camera, 45.0 );
								SET_WIDESCREEN_BORDERS( 1 );
								SetTime(500);
								DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
								SetTime(1000);

								NEW_SCRIPTED_CONVERSATION();
								ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
								ADD_LINE_TO_CONVERSATION(0, "R11_KF", "BNK4_44", 0, 0);//We made it! We're rich! RICH!
								START_SCRIPT_CONVERSATION(1, 1);
								SetSpeech();

								if (IS_CHAR_DEAD(ped2))
								{
									// диалог 1
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R11_KG", "BNK4_45", 0, 0);//Shame Cam didn't make it, he was a good guy!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();

									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R11_KH", "BNK4_46", 0, 0);//Yeah. Still... more for us!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();

									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R11_KI", "BNK4_47", 0, 0);//Damned straight! YEEEEHAAAH!
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();
									add_cash = 50000;
								}
								else
								{
									// диалог 2
									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R11_KJ", "BNK4_48", 0, 0);//Tommy, would you like a massage?
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();

									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
									ADD_LINE_TO_CONVERSATION(0, "R11_KK", "BNK4_49", 0, 0);//Well, Hi there, Mercedes! Yeah, I'm a little tense...
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();

									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R11_KL", "BNK450A", 0, 0);//What'd I tell you Tommy? What'd I tell you? Bent SWAT better watch out when Kent Paul is in town.
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();

									NEW_SCRIPTED_CONVERSATION();
									ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
									ADD_LINE_TO_CONVERSATION(0, "R11_KM", "BNK450B", 0, 0);//Come on, gimme a bigger slice, mate, c'mon. I gotta get some new threads.
									START_SCRIPT_CONVERSATION(1, 1);
									SetSpeech();

									add_cash = 35000;
								}

								DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
								while(true)
								{
									WAIT(0);
									if (IS_SCREEN_FADED_OUT())
									{
										break;
									}
								}

								POINT_CAM_AT_COORD	( camera, 914.084, 464.584, 5.83583 ); // куда смотрит камера
								SET_CAM_POS			( camera, 946.271, 430.582, 11.1684 );//расположение камеры

								SetTime(500);
								DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
								CLEAR_PRINTS();

								SETTIMERA(0); //сбрасываем таймер 
								while (true)
								{
									SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
									SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
									SET_TEXT_EDGE(1, 0, 0, 0, 255); //
									SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
									SET_TEXT_CENTRE(1); // задаём центр текста
									DISPLAY_TEXT(0.5, 0.45, "ASSET_A");//BANK HEIST ASSET COMPLETED!
									WAIT( 0 );
									if ( TIMERA() > 5000 )
									{
										break;
									}
								}

								if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
								{
									WARP_CHAR_FROM_CAR_TO_COORD(GetPlayerPed(), -400.771, -375.696, 6.59763);//телепартируем из катера
									SET_CHAR_HEADING(GetPlayerPed(), 0.0);
								}
								else
								{
									SET_CHAR_COORDINATES(GetPlayerPed(), -400.771, -375.696, 6.59763);//
									SET_CHAR_HEADING(GetPlayerPed(), 0.0);
								}
								SET_CHAR_COORDINATES(ped1, -40.771, -35.696, 6.59763);//
								SET_CHAR_COORDINATES(ped2, -40.771, -35.696, 6.59763);//

								POINT_CAM_AT_COORD	( camera, 901.547, 480.051, 11.1095 ); // куда смотрит камера
								SET_CAM_POS			( camera, 899.004, 480.846, 11.7199 );//расположение камеры

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "ASSET_B", 5000, 1);//~g~The Malibu Club will now generate revenue up to a maximum of $10000 per day. Pick up your cash regularly!
								
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

						}
						else
						{
							if (cop_on == 1)
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NEWANTED", 5000, 1);//~COL_NET_12~Shake the cops and lose your wanted level!
								REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
								cop_on = 0;
							}
						}
						GET_CHAR_HEALTH(ped1, &Phil_hp);
						GET_CHAR_HEALTH(ped2, &Cam_hp);
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						else if (Phil_hp < 105)
						{
							EXPLODE_CHAR_HEAD(ped1);
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "P_DEAD", 5000, 1);//~r~Phil's dead!!
							skip = 1;
							break;
						}
						else if (Cam_hp < 105)
						{
							if (!IS_CHAR_DEAD(ped2))
							{
								EXPLODE_CHAR_HEAD(ped2);
							}
						}
					}
				}

				// чистим скрипт тут
				REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
				SET_MAX_WANTED_LEVEL(6);
				REMOVE_PICKUP(aid_1);
				REMOVE_PICKUP(arm_1);

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
				if (smoke_on == 1)
				{
					STOP_PTFX(PTFX);
					REMOVE_PTFX(PTFX);
					STOP_PTFX(PTFX2);
					REMOVE_PTFX(PTFX2);
					STOP_PTFX(PTFX3);
					REMOVE_PTFX(PTFX3);
					STOP_PTFX(PTFX4);
					REMOVE_PTFX(PTFX4);
				}

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины

				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM6);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM7);//выгружаем модель педа

				MARK_MODEL_AS_NO_LONGER_NEEDED(wireM);//выгружаем модель

				if (del_car == 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				}

				if (car1 != 0)
				{
					MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				}
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)

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

				DELETE_OBJECT(&wire1);
				DELETE_OBJECT(&wire2);
				DELETE_OBJECT(&wire3);
				DELETE_OBJECT(&wire4);
				DELETE_OBJECT(&wire5);
				DELETE_OBJECT(&wire6);

				MARK_OBJECT_AS_NO_LONGER_NEEDED(&wire1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&wire2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&wire3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&wire4);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&wire5);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&wire6);

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					PRINT_HELP("CLOTH10"); //Bank Job outfit delivered to Malibu Club in Vice Point.
					G_CLUB = 6;
					autosave = 1;
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_BANK_4" );//The Job
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(add_cash, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +add_cash );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, add_cash);
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}
		else if ((G_ONMISSION == 0) && (G_CLUB == 6))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(896.966, 472.341, 5.394, &malibu_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(malibu_ico, BLIP_CLUB);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(malibu_ico, 1.1); // масштаб иконки на радаре
				SET_BLIP_AS_SHORT_RANGE(malibu_ico, 1); // иконка пропадает если не в зоне радардиска
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(malibu_ico, "LG_10");//иконка на радаре называние в истории карты "Боярский"
				blip_on = 1;
			}
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(malibu_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}
		if (G_CLUB == 6)
		{
			if ( TIMERC() > 288)// время фарма
			{
				if (income < 10000)// максимальный доход
				{
					income +=1;
				}
				SETTIMERC(0); //сбрасываем таймер 
			}
			if (G_COLLECTOR == 6)// ID Бизнеса
			{
				income = 0;
				G_COLLECTOR = 0;
			}

			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 904.356, 476.795, 9.563, 898.356, 483.795, 13.563, 0 ))
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
				if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), 902.761, 479.165, 900.373, 481.551, 0))
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
	club();
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
