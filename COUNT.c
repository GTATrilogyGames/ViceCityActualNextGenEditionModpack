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
float PlayX, PlayY, PlayZ, PlayR, PedX, PedY, PedZ, PedR, blip_on, blip_on2, skip, hate, PointN, Ped1_c, Ped4_c, Ped5_c, Ped6_c, Ped7_c, Ped8_c, Ped9_c, Ped10_c, Ped11_c, Ped12_c, taxi_cam, in_cord, siren, shoot;
float in_car1, in_car2, in_car3, keis, rrr_onV, rrr_on1, rrr_on2, rrr_on3, driver, text, text2, business, icon_on, collector, stop, sound, textur1, get_money, autosave;
float set_X, set_Y, set_Z, lance, Ped2X, Ped2Y, Ped2Z, Ped2R, Sonny, anim, animP1, animP2, animP3, animP4, alfa, move1, move2, set_page, set_cam, fon_black;
int money_ped, income, load_mashin, help;
int exp1,exp2, exp3, exp4;

void safe(float safeX, float safeY, float safeZ)
{
	GET_DISTANCE_BETWEEN_COORDS_3D( safeX, safeY, safeZ, 59.992, -63.3677, 19.2045, &PedR);//проверка "игрок на координатах"
	if (( PedR < 2.5) && (TIMERA() > 100))
	{
		ADD_SCORE( GetPlayerIndex(), -1 );//даём игроку денег
		SETTIMERA( 0 );
		if (anim == 0)
		{
			if ((animP1 == 0) && (animP2 == 0) && (animP3 == 0) && (animP4 == 0))
			{
				anim = 1;
			}
		}
	}

}
void set_cord(float cord)
{
	if ((cord == 1) || (cord == 5) || (cord == 9) || (cord == 13))
	{
		set_X = 63.4614;
		set_Y = -11.1707;
		set_Z = 11.3563;
	}
	else if ((cord == 2) || (cord == 6) || (cord == 10) || (cord == 14))
	{
		set_X = 45.8697;
		set_Y = -11.1707;
		set_Z = 11.3563;
	}
	else if ((cord == 3) || (cord == 7) || (cord == 11) || (cord == 15))
	{
		set_X = 82.4045;
		set_Y = -26.1977;
		set_Z = 21.9997;
	}
	else if ((cord == 4) || (cord == 8) || (cord == 12) || (cord == 16))
	{
		set_X = 82.4045;
		set_Y = -26.1977;
		set_Z = 13.6596;
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
void typography(void)
{
	blip_on = 0;
	get_money = 0;
	Blip count_ico;
	load_mashin = 0;
	help = 0;
	autosave = 0;
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
//============================== Spilling the Beans ======================================
		if ((G_ONMISSION == 0) && (G_COUNT == 1))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-629.403, 255.797, 5.95213, &count_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(count_ico, BLIP_DEAL);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(count_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(count_ico, "LG_20");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( -629.403, 255.797, 5.95213, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -629.403, 255.797, 5.95213, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("CNT_1", 15000, CUTSCENE_COUNTER);
				G_ONMISSION = 1;
				#if defined SHORT_CUT_TAXIS
				AddShortCutDropOffPointForMission(-1045.726, -292.454, 9.758, 97.607);
				#endif
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(count_ico);//Удаляем иконку на радаре
				blip_on = 0;
				skip = 0;
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
				taxi_cam = 0;
				in_cord = 0;
				siren = 0;
				shoot = 0;

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

				SET_CHAR_COORDINATES(GetPlayerPed(), -625.804, 246.421, 5.46582);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -90.0);

				uint hour, minute, weather;
				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW( WEATHER_EXTRA_SUNNY );//устанавливаем погода
				FORWARD_TO_TIME_OF_DAY(18, 20);//устанавливаем время
				RELEASE_WEATHER();
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "CNT_1A", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("cnt_1a");
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

				SetUpShortCut(-1047.664 + (433.0004434), -298.188 + (532.9998721), 11.0 + (-5.00017432), 266.280, 512.591 + (433.0004434), -74.900 + (532.9998721), 9.573 + (-5.00017432), 189.24);

				FORCE_WEATHER_NOW( weather );//устанавливаем погода
				RELEASE_WEATHER();
				FORWARD_TO_TIME_OF_DAY(hour, minute);//устанавливаем время

				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				Ped ped1, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20;
				Pickup sweap_1, aid_1;
				int dm, cdm;
				Cam camera;

				uint PedM2 = MODEL_M_M_SECURITYMAN;// охранник
				uint PedM3 = MODEL_M_M_PINDUS_01;// рабочий

				uint AudID1, AudID2, AudID3;

				LOAD_CHAR_DECISION_MAKER(2, &dm);
				LOAD_COMBAT_DECISION_MAKER(3, &cdm);

				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				//создаём пушку и аптечку
				CREATE_PICKUP_ROTATE(w_ak47, 3, 30, -264.091, -754.278, 5.80035, 90.0, -70.0, -90.0, &sweap_1);// даём винтовку
				CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -255.415, -719.711, 26.2279, 0.0, 0.0, 25.0, &aid_1);//Аптека

				REQUEST_MODEL(PedM2);
				REQUEST_MODEL(PedM3);

				while (!HAS_MODEL_LOADED(PedM2) || !HAS_MODEL_LOADED(PedM3))
				{
					WAIT(0);
				}

				#if !defined SHORT_CUT_TAXIS
				uint CarM1 = MODEL_CABBY;
				uint PedM1 = MODEL_M_M_TAXIDRIVER;

				REQUEST_MODEL(CarM1);
				REQUEST_MODEL(PedM1);

				while (!HAS_MODEL_LOADED(CarM1) || !HAS_MODEL_LOADED(PedM1))
				{
					WAIT(0);
				}

				Car car1;
				CREATE_CAR(CarM1, -615.798, 232.316, 5.42769, &car1, 1);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				SET_CAR_HEADING(car1, -90.0);//градус поворота машины

				Ped ped2;
				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped2);// Таксист

				Blip taxi_ico;
				ADD_BLIP_FOR_CAR(car1, &taxi_ico);
				CHANGE_BLIP_SPRITE(taxi_ico, BLIP_DESTINATION);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(taxi_ico, 19);   //цвет иконка на радаре (0=белая)
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(taxi_ico, "NE_CAR");//иконка на радаре называние в истории карты "ЛОДКА"
				#endif

				CREATE_CHAR (26, PedM2, -238.384, -718.947, 29.631, &ped1, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -249.586, -693.645, 17.9877, &ped4, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -254.233, -685.43, 10.6366, &ped5, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -189.372, -824.369, 10.6366, &ped6, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -197.987, -849.781, 10.6366, &ped7, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -219.979, -809.823, 10.6366, &ped8, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -248.227, -750.48, 10.6366, &ped9, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -177.185, -843.764, 10.6366, &ped10, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -193.177, -805.964, 10.6366, &ped11, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -213.925, -757.167, 10.6366, &ped12, TRUE);// создаём педа

				CREATE_CHAR (26, PedM2, -240.888, -753.75, 18.9012, &ped3, TRUE);// создаём педа
				CREATE_CHAR (26, PedM3, -272.918, -691.683, 10.6366, &ped13, TRUE);// создаём педа
				CREATE_CHAR (26, PedM3, -272.578, -692.573, 10.6366, &ped14, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -256.343, -707.959, 25.5601, &ped15, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -258.809, -723.476, 27.0691, &ped16, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -260.574, -690.121, 10.6275, &ped17, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -261.327, -712.455, 21.5172, &ped18, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -258.751, -693.182, 17.6979, &ped19, TRUE);// создаём педа
				CREATE_CHAR (26, PedM2, -206.736, -820.136, 18.9012, &ped20, TRUE);// создаём педа

				SET_CHAR_HEADING(ped1, 115.0);
				SET_CHAR_HEADING(ped3, 100.0);
				SET_CHAR_HEADING(ped4, 115.0);
				SET_CHAR_HEADING(ped5, 115.0);
				SET_CHAR_HEADING(ped6, 115.0);
				SET_CHAR_HEADING(ped7, 35.0);
				SET_CHAR_HEADING(ped8, 35.0);
				SET_CHAR_HEADING(ped9, 35.0);
				SET_CHAR_HEADING(ped10, 35.0);
				SET_CHAR_HEADING(ped11, 35.0);
				SET_CHAR_HEADING(ped12, 35.0);
				SET_CHAR_HEADING(ped13, 180.0);
				SET_CHAR_HEADING(ped14, 35.0);
				SET_CHAR_HEADING(ped15, 100.0);
				SET_CHAR_HEADING(ped16, 40.0);
				SET_CHAR_HEADING(ped17, 30.0);
				SET_CHAR_HEADING(ped18, 30.0);
				SET_CHAR_HEADING(ped19, 30.0);
				SET_CHAR_HEADING(ped20, 100.0);

				UpdateWeaponOfPed(ped1, WEAPON_AK47);
				UpdateWeaponOfPed(ped3, WEAPON_SNIPERRIFLE);
				UpdateWeaponOfPed(ped4, WEAPON_MP5);
				UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped6, WEAPON_AK47);
				UpdateWeaponOfPed(ped7, WEAPON_MP5);
				UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped9, WEAPON_MP5);
				UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped11, WEAPON_MP5);
				UpdateWeaponOfPed(ped12, WEAPON_AK47);
				UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_23);
				UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_23);
				UpdateWeaponOfPed(ped15, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped16, WEAPON_MP5);
				UpdateWeaponOfPed(ped17, WEAPON_AK47);
				UpdateWeaponOfPed(ped18, WEAPON_MP5);
				UpdateWeaponOfPed(ped19, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped20, WEAPON_AK47);

				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_SNIPERRIFLE, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_EPISODIC_23, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_EPISODIC_23, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_MP5, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_AK47, TRUE);

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
				SET_SENSE_RANGE(ped15, 35.0);
				SET_SENSE_RANGE(ped16, 35.0);
				SET_SENSE_RANGE(ped17, 35.0);
				SET_SENSE_RANGE(ped18, 35.0);
				SET_SENSE_RANGE(ped19, 35.0);
				SET_SENSE_RANGE(ped20, 35.0);

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
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped15, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped16, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped17, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped18, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped19, FALSE);
				SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped20, FALSE);

				ADD_BLIP_FOR_COORD(924.402, 455.03, 5.42028, &count_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(count_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(count_ico, 5);   //цвет иконка на радаре (0=белая)
				CHANGE_BLIP_SCALE(count_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(count_ico, "NE_POINT");//иконка на радаре называние в истории карты "ЛОДКА"

				//враги патрулирют лодочную мастерскую
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, -252.733, -725.676, 29.4787, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped4, -264.964, -700.598, 17.5642, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, -269.61, -692.383, 10.213, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, -202.497, -830.191, 10.213, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, -218.442, -813.021, 10.213, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped8, -244.133, -758.742, 10.213, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped9, -272.145, -697.477, 10.213, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped10, -187.127, -816.574, 10.213, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped11, -208.369, -769.892, 10.213, 2, -2, 3.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD(ped12, -237.382, -704.164, 10.213, 2, -2, 3.5);

				while (true)
				{
					WAIT( 0 );
					DRAW_CHECKPOINT( 924.402, 455.03, 5.42028, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 924.402, 455.03, 5.42028, &PlayR);//проверка "игрок на координатах"
					if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
					{
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замараживаем игрока
						REMOVE_BLIP(count_ico);//Удаляем иконку на радаре

						DO_SCREEN_FADE_OUT( 1000 );// Затемняем экран
						while(true)
						{
							WAIT(0);
							if (IS_SCREEN_FADED_OUT())
							{
								break;
							}
						}
						SET_CHAR_COORDINATES(GetPlayerPed(), 925.387, 454.108, 5.70609 );// перемещаем игрока
						SET_CHAR_HEADING(GetPlayerPed(), -130.0 );

						//------------ катсцена ----------------
						LOAD_ADDITIONAL_TEXT( "CNT_1B", 6 ); // загружаем субтитры из *.GTX
						START_CUTSCENE_NOW("cnt_1b");
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

						ADD_BLIP_FOR_COORD(-253.866, -711.997, 25.0507, &count_ico);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(count_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(count_ico, 5);   //цвет иконка на радаре (0=белая)
						CHANGE_BLIP_SCALE(count_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(count_ico, "NE_POINT");//иконка на радаре называние в истории карты "ЛОДКА"
						PRINT_STRING_IN_STRING("string", "CM1_1", 5000, 1);//~COL_NET_12~Go to the Chartered Libertine Lines boat at the docks.
						PRINT_STRING_IN_STRING("string", "CM1_2", 5000, 1);//~COL_NET_12~The Shipping Officer will have the information that is required.
						break;
					}
					else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
					if (taxi_cam == 0)
					{
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замараживаем игрока
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, -615.798, 232.316, 5.42769 ); // куда смотрит камера
						SET_CAM_POS			( camera, -607.207, 238.534, 8.28362 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );
						PRINT_STRING_IN_STRING("string", "TAXSHRT", 5000, 1);//~COL_NET_12~You can use this Kaufman Cab to take you to destinations instead of driving. It will cost you $9.
						SetTime(5000);

						//удяляем камеру тут
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
						taxi_cam = 1;
						PRINT_STRING_IN_STRING("string", "CM1_5", 5000, 1);//~COL_NET_12~Go and meet Kent Paul at the Malibu Club!
					}
					#if !defined SHORT_CUT_TAXIS
					else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -578.134, 219.109, 2.979, -634.071, 262.561, 12.979, 0 )) && (taxi_cam == 1))
					{
						taxi_cam = 2;
						SET_CAR_COORDINATES(car1, -642.313, 281.546, 6.19296 );// перемещаем
						REMOVE_BLIP(taxi_ico);//Удаляем иконку на радаре
					}

					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -612.798, 230.316, 4.264, -618.798, 234.316, 9.264, 0 )) && (taxi_cam == 1))
					{
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замараживаем игрока
						TASK_ENTER_CAR_AS_PASSENGER(GetPlayerPed(), car1, -1, 1);// пед содится к таксисту
						REMOVE_BLIP(taxi_ico);//Удаляем иконку на радаре
						SETTIMERB( 0 );

						while(true)
						{
							WAIT(0);
							if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
							{
								break;
							}
							else if (TIMERB() > 3000)
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(GetPlayerPed(), car1, 1);
								break;
							}
						}
						
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car1, 938.227, 450.946, 4.63323, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						SetTime(2000);

						DO_SCREEN_FADE_OUT( 2000 );// Затемняем экран
						while(true)
						{
							WAIT(0);
							if (IS_SCREEN_FADED_OUT())
							{
								break;
							}
						}
						SET_CAR_COORDINATES(car1, 942.743, 463.347, 4.63323 );// перемещаем
						SET_CAR_HEADING(car1, 180.0);
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car1, 938.227, 450.946, 4.63323, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						SetTime(1000);

						DO_SCREEN_FADE_IN( 2000 );// убирается затемнение экрана
						SetTime(3000);

						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car1, PlayX, PlayY, PlayZ, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						
						TASK_LEAVE_CAR(GetPlayerPed(), car1);
						SetTime(1500);
						TASK_CAR_DRIVE_WANDER(ped2, car1, 55.0, 2);// пед едит куда-то
						SetTime(1500);

						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
						ADD_SCORE( GetPlayerIndex(), -9 );//даём игроку денег
						INCREMENT_FLOAT_STAT(STAT_SPENT_ON_TAXIS, 9);
						taxi_cam = 2;
					}
					#endif
				}

				if (skip == 0)
				{
					while (true)
					{
						WAIT( 0 );
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -74.918, -983.077, -10.532, -374.918, -583.077, 89.468, 0 )) && (in_cord == 0))
						{
							//враги патрулирют лодочную мастерскую
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, -252.733, -725.676, 29.4787, 2, -2, 3.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped4, -264.964, -700.598, 17.5642, 2, -2, 3.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, -269.61, -692.383, 10.213, 2, -2, 3.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, -202.497, -830.191, 10.213, 2, -2, 3.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, -218.442, -813.021, 10.213, 2, -2, 3.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped8, -244.133, -758.742, 10.213, 2, -2, 3.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped9, -272.145, -697.477, 10.213, 2, -2, 3.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped10, -187.127, -816.574, 10.213, 2, -2, 3.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped11, -208.369, -769.892, 10.213, 2, -2, 3.5);
							TASK_FOLLOW_NAV_MESH_TO_COORD(ped12, -237.382, -704.164, 10.213, 2, -2, 3.5);
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
							in_cord = 1;
							SET_MAX_WANTED_LEVEL(2);
						}
						else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -74.918, -983.077, -10.532, -374.918, -583.077, 89.468, 0 )) && (in_cord == 1))
						{
							SET_MAX_WANTED_LEVEL(6);
							in_cord = 0;
						}
						// патрули
						if (Ped1_c == 0)
						{
							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -252.733, -725.676, 29.4787, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped1_c = 1;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, -238.384, -718.947, 29.631, 2, -2, 3.5);
							}
						}
						else if (Ped1_c == 1)
						{
							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -238.384, -718.947, 29.631, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped1_c = 0;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped1, -252.733, -725.676, 29.4787, 2, -2, 3.5);
							}
						}
						//------------------------
						if (Ped4_c == 0)
						{
							GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -264.964, -700.598, 17.5642, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped4_c = 1;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped4, -249.586, -693.645, 17.9877, 2, -2, 3.5);
							}
						}
						else if (Ped4_c == 1)
						{
							GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -249.586, -693.645, 17.9877, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped4_c = 0;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped4, -264.964, -700.598, 17.5642, 2, -2, 3.5);
							}
						}

						//------------------------
						if (Ped5_c == 0)
						{
							GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -269.61, -692.383, 10.213, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped5_c = 1;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, -254.233, -685.43, 10.6366, 2, -2, 3.5);
							}
						}
						else if (Ped5_c == 1)
						{
							GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -254.233, -685.43, 10.6366, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped5_c = 0;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, -269.61, -692.383, 10.213, 2, -2, 3.5);
							}
						}
						//------------------------
						if (Ped6_c == 0)
						{
							GET_CHAR_COORDINATES(ped6,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -202.497, -830.191, 10.213, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped6_c = 1;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, -189.372, -824.369, 10.6366, 2, -2, 3.5);
							}
						}
						else if (Ped6_c == 1)
						{
							GET_CHAR_COORDINATES(ped6,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -189.372, -824.369, 10.6366, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped6_c = 0;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped6, -202.497, -830.191, 10.213, 2, -2, 3.5);
							}
						}
						//------------------------
						if (Ped7_c == 0)
						{
							GET_CHAR_COORDINATES(ped7,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -218.442, -813.021, 10.213, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped7_c = 1;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, -197.987, -849.781, 10.6366, 2, -2, 3.5);
							}
						}
						else if (Ped7_c == 1)
						{
							GET_CHAR_COORDINATES(ped7,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -197.987, -849.781, 10.6366, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped7_c = 0;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped7, -218.442, -813.021, 10.213, 2, -2, 3.5);
							}
						}
						//------------------------
						if (Ped8_c == 0)
						{
							GET_CHAR_COORDINATES(ped8,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -244.133, -758.742, 10.213, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped8_c = 1;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped8, -219.979, -809.823, 10.6366, 2, -2, 3.5);
							}
						}
						else if (Ped8_c == 1)
						{
							GET_CHAR_COORDINATES(ped8,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -219.979, -809.823, 10.6366, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped8_c = 0;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped8, -244.133, -758.742, 10.213, 2, -2, 3.5);
							}
						}
						//------------------------
						if (Ped9_c == 0)
						{
							GET_CHAR_COORDINATES(ped9,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -272.145, -697.477, 10.213, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped9_c = 1;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped9, -248.227, -750.48, 10.6366, 2, -2, 3.5);
							}
						}
						else if (Ped9_c == 1)
						{
							GET_CHAR_COORDINATES(ped9,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -248.227, -750.48, 10.6366, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped9_c = 0;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped9, -272.145, -697.477, 10.213, 2, -2, 3.5);
							}
						}
						//------------------------
						if (Ped10_c == 0)
						{
							GET_CHAR_COORDINATES(ped10,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -187.127, -816.574, 10.213, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped10_c = 1;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped10, -177.185, -843.764, 10.6366, 2, -2, 3.5);
							}
						}
						else if (Ped10_c == 1)
						{
							GET_CHAR_COORDINATES(ped10,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -177.185, -843.764, 10.6366, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped10_c = 0;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped10, -187.127, -816.574, 10.213, 2, -2, 3.5);
							}
						}
						//------------------------
						if (Ped11_c == 0)
						{
							GET_CHAR_COORDINATES(ped11,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -208.369, -769.892, 10.213, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped11_c = 1;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped11, -193.177, -805.964, 10.6366, 2, -2, 3.5);
							}
						}
						else if (Ped11_c == 1)
						{
							GET_CHAR_COORDINATES(ped11,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -193.177, -805.964, 10.6366, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped11_c = 0;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped11, -208.369, -769.892, 10.213, 2, -2, 3.5);
							}
						}
						//------------------------
						if (Ped12_c == 0)
						{
							GET_CHAR_COORDINATES(ped12,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -237.382, -704.164, 10.213, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped12_c = 1;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped12, -213.925, -757.167, 10.6366, 2, -2, 3.5);
							}
						}
						else if (Ped12_c == 1)
						{
							GET_CHAR_COORDINATES(ped12,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -213.925, -757.167, 10.6366, &PedR);//проверка "игрок на координатах"
							if (PedR < 4.0)
							{
								Ped12_c = 0;
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped12, -237.382, -704.164, 10.213, 2, -2, 3.5);
							}
						}

						// Рабочие атакуют игрока тут
						if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -260.261, -721.971, 9.004, -273.482, -696.971, 15.104, 0 )) && (hate == 0))// релокация Ленса
						{
							// Рабочие атакуют игрока
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
							WAIT(25);
						}

						if (shoot == 0)
						{
							if ((IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), -228.194, -838.622, -178.194, -788.622, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped6, -228.194, -838.622, -178.194, -788.622, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped7, -228.194, -838.622, -178.194, -788.622, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped10, -228.194, -838.622, -178.194, -788.622, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped20, -228.194, -838.622, -178.194, -788.622, 0)))
							{
								SET_SENSE_RANGE(ped5, 0.01);
								SET_SENSE_RANGE(ped9, 0.01);
								SET_SENSE_RANGE(ped12, 0.01);
								SET_SENSE_RANGE(ped14, 0.01);
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, -232.755, -715.567, 10.213, 3, -2, 2.5);
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped9, -263.164, -717.779, 10.213, 3, -2, 2.5);
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped12, -232.755, -715.567, 10.213, 3, -2, 2.5);
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped14, -263.164, -717.779, 10.213, 3, -2, 2.5);
								shoot = 1;
							}
							else if ((IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), -261.521, -765.203, -211.521, -715.203, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped3, -261.521, -765.203, -211.521, -715.203, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped9, -261.521, -765.203, -211.521, -715.203, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped12, -261.521, -765.203, -211.521, -715.203, 0)))
							{
								SET_SENSE_RANGE(ped5, 0.01);
								SET_SENSE_RANGE(ped9, 0.01);
								SET_SENSE_RANGE(ped12, 0.01);
								SET_SENSE_RANGE(ped14, 0.01);
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped5, -232.755, -715.567, 10.213, 3, -2, 2.5);
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped9, -263.164, -717.779, 10.213, 3, -2, 2.5);
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped12, -232.755, -715.567, 10.213, 3, -2, 2.5);
								TASK_FOLLOW_NAV_MESH_TO_COORD(ped14, -263.164, -717.779, 10.213, 3, -2, 2.5);
								shoot = 1;
							}
						}
						else if (shoot == 1)
						{
							if ((IS_CHAR_IN_AREA_3D( ped9, -261.999, -719.229, 10.213, -266.739, -716.199, 14.213, 0 )) || (IS_CHAR_IN_AREA_3D( ped14, -261.999, -719.229, 10.213, -266.739, -716.199, 14.213, 0 )) || (IS_CHAR_IN_AREA_3D( ped5, -229.577, -716.926, 10.213, -234.317, -713.896, 14.213, 0 )) || (IS_CHAR_IN_AREA_3D( ped12, -229.577, -716.926, 10.213, -234.317, -713.896, 14.213, 0 )))
							{
								shoot = 2;
								SET_SENSE_RANGE(ped5, 55.01);
								SET_SENSE_RANGE(ped9, 55.01);
								SET_SENSE_RANGE(ped12, 55.01);
								SET_SENSE_RANGE(ped14, 55.01);

								// аудио тут
								while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/RB4_MUSEUM_PIECE" )))
								{
									 WAIT(3);
								}
								AudID1 = GET_SOUND_ID();
								PLAY_SOUND_FROM_POSITION(AudID1, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", -221.879, -794.003, 13.6525);
								AudID2 = GET_SOUND_ID();
								PLAY_SOUND_FROM_POSITION(AudID2, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", -257.369, -729.047, 13.6525);
								AudID3 = GET_SOUND_ID();
								PLAY_SOUND_FROM_POSITION(AudID3, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", -256.323, -698.055, 20.7516);

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "CM1_3", 5000, 1);//~COL_NET_12~You've been spotted!
								siren = 1;
								WAIT(25);
							}
						}

						//чекпойнт
						DRAW_CHECKPOINT( -253.866, -711.997, 25.0507, 0.8, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -253.866, -711.997, 25.0507, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							REMOVE_BLIP(count_ico);//Удаляем иконку на радаре
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замараживаем игрока

							//камера
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -253.866, -711.997, 25.8052 ); // куда смотрит камера
							SET_CAM_POS			( camera, -262.813, -713.136, 28.6468 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );

							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), -252.195, -715.306, 25.1412, 2, -2);// Пед идёт в двери
							SetTime(2000);

							// аудио тут
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R8_WA", "CNT1_1", 0, 0);//Who are you? Oooof! Aaiieee! Not the face! Not the face!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R8_XA", "CNT1_2", 0, 0);//Ok, I talk! I talk!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							SET_CHAR_COORDINATES(GetPlayerPed(), -252.638, -714.323, 25.3797);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 20.0);
							TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), -253.866, -711.997, 25.0507, 2, -2);// Пед идёт в двери
							SetTime(2000);

							//удяляем камеру тут
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока


							ADD_BLIP_FOR_COORD(-625.551, 246.349, 5.08937, &count_ico);//создаем иконку на радаре
							CHANGE_BLIP_SPRITE(count_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(count_ico, 5);   //цвет иконка на радаре (0=белая)
							CHANGE_BLIP_SCALE(count_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(count_ico, "NE_POINT");//иконка на радаре называние в истории карты
							PRINT_STRING_IN_STRING("string", "CM1_6", 5000, 1);//~COL_NET_12~Get the information back to the Print Works!

							// сигнализция тут
							if (siren == 0)
							{
								while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/RB4_MUSEUM_PIECE" )))
								{
									 WAIT(5);
								}
								AudID1 = GET_SOUND_ID();
								PLAY_SOUND_FROM_POSITION(AudID1, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", -221.879, -794.003, 13.6525);
								AudID2 = GET_SOUND_ID();
								PLAY_SOUND_FROM_POSITION(AudID2, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", -257.369, -729.047, 13.6525);
								AudID3 = GET_SOUND_ID();
								PLAY_SOUND_FROM_POSITION(AudID3, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", -256.323, -698.055, 20.7516);
								siren = 1;
								WAIT(25);
							}
							break;
						}
						if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
					}
				}

				if (skip == 0)
				{
					while (true)
					{
						WAIT( 0 );
						DRAW_CHECKPOINT( -625.551, 246.349, 5.08937, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -625.551, 246.349, 5.08937, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							skip = 2;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
						if ((IS_CHAR_DEAD(ped7)) || (IS_CHAR_INJURED(ped7)))
						{
							if (TIMERB() > 5000)
							{
								DELETE_CHAR(&ped7);//удаляем модель педа
								//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет
								CREATE_CHAR (26, PedM3, -256.183, -727.571, 10.5496, &ped7, TRUE);////ok
								SET_CHAR_HEADING(ped7, -165.0);
								UpdateWeaponOfPed(ped7, WEAPON_PISTOL);
								SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_PISTOL, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
								SET_CHAR_RELATIONSHIP(ped7, 5, 0);
								SET_SENSE_RANGE(ped7, 65.0);
								SET_CHAR_WILL_USE_COVER(ped7, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
								TASK_COMBAT(ped7, GetPlayerPed());
								SETTIMERB( 0 );
								WAIT(25);
							}
						}
						if ((IS_CHAR_DEAD(ped10)) || (IS_CHAR_INJURED(ped10)))
						{
							if (TIMERB() > 5000)
							{
								DELETE_CHAR(&ped10);//удаляем модель педа
								//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped10);//выгружаем модель педа(в последствии пед изчезнет
								CREATE_CHAR (26, PedM3, -255.926, -727.033, 10.5496, &ped10, TRUE);////ok
								SET_CHAR_HEADING(ped10, -165.0);
								UpdateWeaponOfPed(ped10, WEAPON_PISTOL);
								SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_PISTOL, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped10, 5);
								SET_CHAR_RELATIONSHIP(ped10, 5, 0);
								SET_SENSE_RANGE(ped10, 65.0);
								SET_CHAR_WILL_USE_COVER(ped10, 1);
								SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped6, FALSE);
								TASK_COMBAT(ped10, GetPlayerPed());
								SETTIMERB( 0 );
								WAIT(25);
							}
						}
					}
				}

				ClearShortCut();

				// завершение миссии
				REMOVE_BLIP(count_ico);//Удаляем иконку на радаре
				REMOVE_PICKUP(sweap_1);// выгружаем оружие
				REMOVE_PICKUP(aid_1);// выгружаем оружие
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
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа

				// выгружаем из памяти педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
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

				#if !defined SHORT_CUT_TAXIS
				REMOVE_BLIP(taxi_ico);

				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);

				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);
				#endif

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_CNT_1" );//Spilling the Beans
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(2000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +2000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 2000);
					G_COUNT = 2;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}

//============================== Hit the Courier ======================================
		else if ((G_ONMISSION == 0) && (G_COUNT == 2))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-629.403, 255.797, 5.95213, &count_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(count_ico, BLIP_DEAL);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(count_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(count_ico, "LG_20");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( -629.403, 255.797, 5.95213, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -629.403, 255.797, 5.95213, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("CNT_2", 15000, CUTSCENE_COUNTER);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-1045.726, -292.454, 9.758, 97.607);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(count_ico);//Удаляем иконку на радаре
				blip_on = 0;
				skip = 0;
				shoot = 0;
				in_car1 = 0;
				in_car2 = 99;
				in_car3 = 99;
				keis = 0;
				rrr_onV = 1;
				rrr_on1 = 0;
				rrr_on2 = 0;
				rrr_on3 = 0;
				driver = 0;
				text = 0;
				text2 = 0;

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

				SET_CHAR_COORDINATES(GetPlayerPed(), -625.804, 246.421, 5.46582);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -90.0);

				uint hour, minute, weather;
				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW( WEATHER_EXTRA_SUNNY );//устанавливаем погода
				FORWARD_TO_TIME_OF_DAY(18, 20);//устанавливаем время
				RELEASE_WEATHER();
				
				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "CNT_2", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("cnt_2");
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

				Car car1, car2, car3, car4;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15, ped16, ped17, ped18, ped19, ped20;
				Pickup sweap_1, aid_1, bag;
				Cam camera;
				Blip hel_ico;

				uint CarM1 = MODEL_MAVERICK; // вертолёт
				uint CarM2 = MODEL_SENTINEL; // машина

				uint PedM1 = MODEL_F_Y_NURSE;// 
				uint PedM2 = MODEL_F_Y_DOCTOR_01;// 
				uint PedM3 = MODEL_F_Y_PCOOL_01;// 
				uint PedM4 = MODEL_F_M_PMANHAT_01;// 

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(CarM2);
				while (!HAS_MODEL_LOADED(CarM2)) WAIT(100);

				REQUEST_MODEL(PedM1);// 
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// 
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// 
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM4);// 
				while (!HAS_MODEL_LOADED(PedM4));////проверка "пед загрузился" если нет то начанаем с начало

				//загрузка путей
				REQUEST_CAR_RECORDING( 3062 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3062 )) WAIT(0);

				REQUEST_CAR_RECORDING( 3063 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3063 )) WAIT(0);

				REQUEST_CAR_RECORDING( 3064 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3064 )) WAIT(0);

				REQUEST_CAR_RECORDING( 3065 );
				while (!HAS_CAR_RECORDING_BEEN_LOADED( 3065 )) WAIT(0);

				CREATE_CAR(CarM1, -326.769, -1007.17, 16.5912, &car1, TRUE);
				SET_CAR_HEADING(car1, 0.0);

				CREATE_CAR(CarM2, -263.622, -1019.88, 6.75169, &car2, TRUE);
				SET_CAR_HEADING(car2, 70.0);

				CREATE_CAR(CarM2, -265.113, -1023.66, 6.75169, &car3, TRUE);
				SET_CAR_HEADING(car3, 70.0);

				CREATE_CAR(CarM2, -266.601, -1027.39, 6.75169, &car4, TRUE);
				SET_CAR_HEADING(car4, 70.0);

				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped2);// пилот вертолёта
				CREATE_CHAR_AS_PASSENGER(car1, 1, PedM2, 0, &ped1);// пассажир вертолёта

				CREATE_CHAR (26, PedM2, -263.508, -959.648, 5.81226, &ped3, TRUE);// 
				CREATE_CHAR (26, PedM1, -287.874, -967.161, 5.79409, &ped4, TRUE);// 
				CREATE_CHAR (26, PedM3, -266.161, -986.677, 6.75169, &ped5, TRUE);//
				CREATE_CHAR (26, PedM1, -283.661, -1005.54, 6.75169, &ped6, TRUE);//
				CREATE_CHAR (26, PedM2, -284.149, -1004.42, 6.75169, &ped7, TRUE);//
				CREATE_CHAR (26, PedM4, -286.179, -997.373, 6.75169, &ped8, TRUE);//
				CREATE_CHAR (26, PedM2, -289.171, -994.926, 11.1557, &ped9, TRUE);//
				CREATE_CHAR (26, PedM3, -290.838, -1013.17, 9.21439, &ped10, TRUE);//
				CREATE_CHAR (26, PedM3, -290.606, -1022.15, 6.75169, &ped11, TRUE);//
				CREATE_CHAR (26, PedM4, -284.737, -1027.73, 9.21439, &ped12, TRUE);//
				CREATE_CHAR (26, PedM2, -292.029, -1024.89, 9.21439, &ped13, TRUE);//
				CREATE_CHAR (26, PedM1, -295.611, -1019.71, 17.2508, &ped14, TRUE);//
				CREATE_CHAR (26, PedM4, -276.891, -1011.24, 6.75169, &ped15, TRUE);//
				CREATE_CHAR (26, PedM3, -270.479, -1039.93, 10.8058, &ped16, TRUE);//
				CREATE_CHAR (26, PedM4, -239.399, -1021.12, 17.9301, &ped17, TRUE);//
				CREATE_CHAR (26, PedM3, -241.103, -1003.61, 6.75169, &ped18, TRUE);//
				CREATE_CHAR (26, PedM1, -251.534, -1022.07, 6.75169, &ped19, TRUE);//
				CREATE_CHAR (26, PedM4, -251.651, -1021.25, 6.75169, &ped20, TRUE);//

				SET_CHAR_HEADING(ped5, 65.0);
				SET_CHAR_HEADING(ped6, 30.0);
				SET_CHAR_HEADING(ped7, -150.0);
				SET_CHAR_HEADING(ped8, -35.0);
				SET_CHAR_HEADING(ped9, -35.0);
				SET_CHAR_HEADING(ped10, -120.0);
				SET_CHAR_HEADING(ped11, -55.0);
				SET_CHAR_HEADING(ped13, -30.0);
				SET_CHAR_HEADING(ped14, -80.0);
				SET_CHAR_HEADING(ped15, 70.0);
				SET_CHAR_HEADING(ped16, -75.0);
				SET_CHAR_HEADING(ped17, 120.0);
				SET_CHAR_HEADING(ped18, -100.0);
				SET_CHAR_HEADING(ped20, -170.0);
//
				UpdateWeaponOfPed(ped1, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped2, WEAPON_EPISODIC_13);
				UpdateWeaponOfPed(ped3, WEAPON_AK47);
				UpdateWeaponOfPed(ped4, WEAPON_SHOTGUN);
				UpdateWeaponOfPed(ped5, WEAPON_SHOTGUN);
				UpdateWeaponOfPed(ped6, WEAPON_AK47);
				UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped8, WEAPON_AK47);
				UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_15);
				UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped11, WEAPON_AK47);
				UpdateWeaponOfPed(ped12, WEAPON_SHOTGUN);
				UpdateWeaponOfPed(ped13, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped14, WEAPON_EPISODIC_15);
				UpdateWeaponOfPed(ped15, WEAPON_SHOTGUN);
				UpdateWeaponOfPed(ped16, WEAPON_EPISODIC_15);
				UpdateWeaponOfPed(ped17, WEAPON_EPISODIC_15);
				UpdateWeaponOfPed(ped18, WEAPON_SHOTGUN);
				UpdateWeaponOfPed(ped19, WEAPON_AK47);
				UpdateWeaponOfPed(ped20, WEAPON_EPISODIC_13);

				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_EPISODIC_13, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_SHOTGUN, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_SHOTGUN, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_15, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_SHOTGUN, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped13, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped14, WEAPON_EPISODIC_15, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped15, WEAPON_SHOTGUN, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped16, WEAPON_EPISODIC_15, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped17, WEAPON_EPISODIC_15, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped18, WEAPON_SHOTGUN, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped19, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped20, WEAPON_EPISODIC_13, TRUE);

				SET_CHAR_RELATIONSHIP_GROUP(ped1, 18);
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

				SET_SENSE_RANGE(ped3, 25.0);
				SET_SENSE_RANGE(ped4, 35.0);
				SET_SENSE_RANGE(ped5, 25.0);
				SET_SENSE_RANGE(ped6, 25.0);
				SET_SENSE_RANGE(ped7, 15.0);
				SET_SENSE_RANGE(ped8, 15.0);
				SET_SENSE_RANGE(ped9, 55.0);
				SET_SENSE_RANGE(ped10, 15.0);
				SET_SENSE_RANGE(ped11, 25.0);
				SET_SENSE_RANGE(ped12, 25.0);
				SET_SENSE_RANGE(ped13, 15.0);
				SET_SENSE_RANGE(ped14, 55.0);
				SET_SENSE_RANGE(ped15, 25.0);
				SET_SENSE_RANGE(ped16, 55.0);
				SET_SENSE_RANGE(ped17, 55.0);
				SET_SENSE_RANGE(ped18, 15.0);
				SET_SENSE_RANGE(ped19, 25.0);
				SET_SENSE_RANGE(ped20, 15.0);

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

				ADD_BLIP_FOR_COORD(-250.171, -1032.97, 6.75169, &count_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(count_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(count_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(count_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(count_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

				ADD_BLIP_FOR_CHAR(ped1, &hel_ico);
				CHANGE_BLIP_SPRITE(hel_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(hel_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(hel_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(hel_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "CNT2_01", 5000, 1);//~g~The counterfeit plates ~y~courier~g~ is arriving at the ~r~docks~g~ in a helicopter any second now.

				//создаём пушку и аптечку
				CREATE_PICKUP_ROTATE(w_ak47, 3, 30, -277.438, -935.46, 5.76597, 90.0, -70.0, 175.0, &sweap_1);// даём винтовку
				CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -273.885, -1030.93, 7.92273, 5.0, 15.0, 25.0, &aid_1);//Аптека

				START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car1, 3065, 0.0, 0.0, 0.0);

				while (TRUE)
				{
					WAIT(0);
					GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -245.69, -1034.77, 7.875, &PedR);//проверка "игрок на координатах"
					if ( PedR < 1.5)
					{
						REMOVE_BLIP(count_ico);//Удаляем иконку на радаре

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "CNT2_08", 5000, 1);//~g~The ~y~courier~g~ with the plates has arrived at the docks.
						WARP_CHAR_INTO_CAR_AS_PASSENGER(ped2, car1, 1);
						SetTime(2500);

						STOP_PLAYBACK_RECORDED_CAR(car1);
						rrr_onV = 0;

						//TASK_LEAVE_CAR(ped1, car1);
						//TASK_LEAVE_CAR(ped2, car1);

						// педы бегут по автомбилям тут
						TASK_ENTER_CAR_AS_DRIVER(ped7, car2, -1);// 
						TASK_ENTER_CAR_AS_PASSENGER(ped18, car2, -1, 0);// пед содится
						TASK_ENTER_CAR_AS_PASSENGER(ped19, car2, -1, 1);// пед содится 
						TASK_ENTER_CAR_AS_PASSENGER(ped20, car2, -1, 2);// пед содится

						TASK_ENTER_CAR_AS_DRIVER(ped2, car3, -1);// 
						TASK_ENTER_CAR_AS_PASSENGER(ped15, car3, -1, 0);// пед содится
						TASK_ENTER_CAR_AS_PASSENGER(ped1, car3, -1, 1);// пед содится
						TASK_ENTER_CAR_AS_PASSENGER(ped11, car3, -1, 2);// пед содится

						TASK_ENTER_CAR_AS_DRIVER(ped6, car4, -1);// 
						TASK_ENTER_CAR_AS_PASSENGER(ped10, car4, -1, 0);// пед содится
						TASK_ENTER_CAR_AS_PASSENGER(ped12, car4, -1, 1);// пед содится
						TASK_ENTER_CAR_AS_PASSENGER(ped13, car4, -1, 2);// пед содится

						if (IS_CHAR_DEAD(ped2))// проверка пед мёртв
						{
							TASK_ENTER_CAR_AS_DRIVER(ped1, car3, -1);//
							driver = 1;
						}

						if (IS_CHAR_DEAD(ped6))// проверка пед мёртв
						{
							TASK_COMBAT(ped10, GetPlayerPed());
							TASK_COMBAT(ped12, GetPlayerPed());
							TASK_COMBAT(ped13, GetPlayerPed());
						}
						if (IS_CHAR_DEAD(ped7))// проверка пед мёртв
						{
							TASK_COMBAT(ped18, GetPlayerPed());
							TASK_COMBAT(ped19, GetPlayerPed());
							TASK_COMBAT(ped20, GetPlayerPed());
						}
						break;
					}

					if ((IS_CHAR_SHOOTING_IN_AREA(ped3, -251.008, -972.148, -276.008, -947.148, 0)) && (text == 0))
					{
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped3, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_NR", "CNT2_4", 0, 0);//Private business. You're not welcome!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped3, "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R11_NS", "CNT2_1", 0, 0);//Kill him!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						text = 1;
					}

					// провел миссии тут
					if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -236.356, -1052.455, 4.508, -291.356, -997.455, 24.163, 0 )) && (IS_CHAR_IN_AREA_3D( ped1, -186.442, -1095.474, 4.508, -291.356, -997.455, 70.163, 0 )))
					{
						if ((IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), -236.356, -1052.455, -291.356, -997.455, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped16, -236.356, -1052.455, -291.356, -997.455, 0)))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CNT2_02", 5000, 1);//~r~The plates courier has fled in the helicopter.
							STOP_PLAYBACK_RECORDED_CAR(car1);
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car1, -50.723, 84.868, 25.80757, 4, 35.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							rrr_onV = 0;
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_SHOOTING_IN_AREA(ped19, -236.356, -1052.455, -291.356, -997.455, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped15, -236.356, -1052.455, -291.356, -997.455, 0)))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CNT2_02", 5000, 1);//~r~The plates courier has fled in the helicopter.
							STOP_PLAYBACK_RECORDED_CAR(car1);
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car1, -50.723, 84.868, 25.80757, 4, 35.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							rrr_onV = 0;
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_SHOOTING_IN_AREA(ped13, -236.356, -1052.455, -291.356, -997.455, 0)) || (IS_CHAR_SHOOTING_IN_AREA(ped14, -236.356, -1052.455, -291.356, -997.455, 0)))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CNT2_02", 5000, 1);//~r~The plates courier has fled in the helicopter.
							STOP_PLAYBACK_RECORDED_CAR(car1);
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car1, -50.723, 84.868, 25.80757, 4, 35.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							rrr_onV = 0;
							skip = 1;// переменная пропуска
							break;
						}
					}
					if (((IS_CHAR_SITTING_IN_CAR(ped1, car1)) && (IS_CHAR_DEAD(ped1)) && (IS_CAR_DEAD(car1))) || (IS_CHAR_ON_FIRE(ped1)))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "CNT2_04", 5000, 1);//~r~You destroyed the plates in the explosion!
						skip = 1;// переменная пропуска
						break;
					}
					else if (IS_CHAR_IN_WATER(ped1))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "CNT2_11", 5000, 1);//~r~The plates are at the bottom of the sea!
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
					while (TRUE)
					{
						WAIT(0);
						// старт RRR путей
						if (in_car1 == 0)
						{
							if (!IS_CHAR_DEAD(ped2))
							{
								if ((IS_CHAR_SITTING_IN_CAR(ped1, car3)) && (IS_CHAR_SITTING_IN_CAR(ped2, car3)))
								{
									//старт петей 1
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 3062, 0.0, 0.0, 0.0);
									rrr_on1 = 1;
									in_car1 = 1;
									in_car2 = 0;
									in_car3 = 0;
								}
							}
							else
							{
								if ((!IS_CHAR_DEAD(ped1)) && (IS_CHAR_SITTING_IN_CAR(ped1, car3)))
								{
									//старт петей 1
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car3, 3062, 0.0, 0.0, 0.0);
									rrr_on1 = 0;
									in_car1 = 1;
								}
							}
						}
						else if (in_car1 == 1)
						{
							if (!IS_CHAR_DEAD(ped11))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped11, car3, 2);
							}
							if (!IS_CHAR_DEAD(ped15))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped15, car3, 0);
							}
							in_car1 = 2;
						}

						if (in_car2 == 0)
						{
							if (!IS_CHAR_DEAD(ped6))// проверка пед мёртв
							{
								if (IS_CHAR_SITTING_IN_CAR(ped6, car4))
								{
									//старт петей 2
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car4, 3064, 0.0, 0.0, 0.0);
									in_car2 = 1;
									rrr_on2 = 1;
								}
							}
							else
							{
								TASK_COMBAT(ped10, GetPlayerPed());
								TASK_COMBAT(ped11, GetPlayerPed());
								TASK_COMBAT(ped13, GetPlayerPed());
								in_car2 = 2;
							}
						}
						else if (in_car2 == 1)
						{
							if (!IS_CHAR_DEAD(ped10))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped10, car4, 0);
							}
							if (!IS_CHAR_DEAD(ped12))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped12, car4, 1);
							}
							if (!IS_CHAR_DEAD(ped13))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped13, car4, 2);
							}
							in_car2 = 2;
						}

						if (in_car3 == 0)
						{
							if (!IS_CHAR_DEAD(ped7))// проверка пед мёртв
							{
								if (IS_CHAR_SITTING_IN_CAR(ped7, car2))
								{
									//старт петей 3
									START_PLAYBACK_RECORDED_CAR_WITH_OFFSET(car2, 3063, 0.0, 0.0, 0.0);
									in_car3 = 1;
									rrr_on3 = 1;
								}
							}
							else
							{
								TASK_COMBAT(ped18, GetPlayerPed());
								TASK_COMBAT(ped19, GetPlayerPed());
								TASK_COMBAT(ped20, GetPlayerPed());
								in_car3 = 2;
							}
						}
						else if (in_car3 == 1)
						{
							if (!IS_CHAR_DEAD(ped18))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped18, car2, 0);
							}
							if (!IS_CHAR_DEAD(ped19))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped19, car2, 1);
							}
							if (!IS_CHAR_DEAD(ped20))
							{
								WARP_CHAR_INTO_CAR_AS_PASSENGER(ped20, car2, 2);
							}
							in_car3 = 2;
						}
						//-------------------------

						if (((IS_CHAR_IN_AREA_3D( ped1, -267.649, -965.102, 3.646, -287.649, -945.102, 13.646, 0 )) && (in_car1 == 2)) || ((IS_CHAR_DEAD(ped1)) && (driver == 1)) || ((IS_CHAR_DEAD(ped2)) && (driver == 0)))
						{
							// пути стоп
							if (rrr_on1 == 1)
							{
								STOP_PLAYBACK_RECORDED_CAR(car3);
								rrr_on1 = 0;
							}
							if (!IS_CHAR_DEAD(ped2))
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car3, -540.723, 854.868, 5.80757, 4, 15.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
							else
							{
								TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car3, -540.723, 854.868, 5.80757, 4, 15.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							}
							driver = 99;
							in_car1 = 3;
						}

						if (((IS_CHAR_IN_AREA_3D( ped6, -267.649, -965.102, 3.646, -296.155, -945.102, 13.646, 0 )) && (in_car2 == 2)) || ((IS_CHAR_DEAD(ped6)) && (in_car2 == 2)))
						{
							if (rrr_on2 == 1)
							{
								STOP_PLAYBACK_RECORDED_CAR(car4);
								rrr_on2 = 0;
							}
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped6, car4, -540.723, 854.868, 5.80757, 4, 15.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							in_car2 = 3;
							
						}
						if (((IS_CHAR_IN_AREA_3D( ped7, -267.649, -965.102, 3.646, -296.155, -945.102, 13.646, 0 )) && (in_car3 == 2)) || ((IS_CHAR_DEAD(ped7)) && (in_car3 == 2)))
						{
							if (rrr_on3 == 1)
							{
								STOP_PLAYBACK_RECORDED_CAR(car2);
								rrr_on3 = 0;
							}
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped7, car2, -540.723, 854.868, 5.80757, 4, 15.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							in_car3 = 3;
						}

						if (in_car1 == 3)
						{
							if (IS_CHAR_IN_AREA_3D( ped1, -534.078, 848.917, 4.287, -549.078, 863.917, 14.287, 0 ))
							{
								TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, -545.612, 799.39, 2.59469, 4, -2, 2.5);
								in_car1 = 4;
							}
						}
						if (in_car2 == 3)
						{
							if (IS_CHAR_IN_AREA_3D( ped6, -534.078, 848.917, 4.287, -549.078, 863.917, 14.287, 0 ))
							{
								TASK_LEAVE_CAR(ped6, car4);
								TASK_LEAVE_CAR(ped10, car4);
								TASK_LEAVE_CAR(ped12, car4);
								TASK_LEAVE_CAR(ped13, car4);
								TASK_COMBAT(ped6, GetPlayerPed());
								TASK_COMBAT(ped10, GetPlayerPed());
								TASK_COMBAT(ped12, GetPlayerPed());
								TASK_COMBAT(ped13, GetPlayerPed());
								in_car2 = 4;
							}
						}
						if (in_car3 == 3)
						{
							if (IS_CHAR_IN_AREA_3D( ped7, -534.078, 848.917, 4.287, -549.078, 863.917, 14.287, 0 ))
							{
								TASK_LEAVE_CAR(ped7, car2);
								TASK_LEAVE_CAR(ped18, car2);
								TASK_LEAVE_CAR(ped19, car2);
								TASK_LEAVE_CAR(ped20, car2);
								TASK_COMBAT(ped7, GetPlayerPed());
								TASK_COMBAT(ped18, GetPlayerPed());
								TASK_COMBAT(ped19, GetPlayerPed());
								TASK_COMBAT(ped20, GetPlayerPed());
								in_car3 = 4;
							}
						}

						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						if ((IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PedX+25, PedY+25, PedX-25, PedY-25, 0)) && (text2 == 0))
						{
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R11_NT", "CNT2_3", 0, 0);//Protect the courier!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();
							text2 = 1;
						}

						// провел миссии тут
						if (((IS_CHAR_SITTING_IN_CAR(ped1, car3)) && (IS_CHAR_DEAD(ped1)) && (IS_CAR_DEAD(car3))) || (IS_CHAR_ON_FIRE(ped1)))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CNT2_04", 5000, 1);//~r~You destroyed the plates in the explosion!
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_IN_WATER(ped1))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CNT2_11", 5000, 1);//~r~The plates are at the bottom of the sea!
							skip = 1;// переменная пропуска
							break;
						}
						else if (IS_CHAR_IN_AREA_3D( ped1, -543.112, 796.89, 2.595, -548.112, 801.89, 7.595, 0 ))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CNT2_03", 5000, 1);//~r~The courier has arrived at his destination safely, you're too late!
							skip = 1;// переменная пропуска
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;// переменная пропуска
							break;
						}

						if ((IS_CHAR_DEAD(ped1)) && (keis == 0))
						{
							REMOVE_BLIP(hel_ico);//Удаляем иконку на радаре

							TASK_LEAVE_CAR(ped1, car3);
							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ, &PedZ);
							CREATE_PICKUP( mission_keis, 22, PedX+0.2, PedY+0.2, PedZ+0.2, &bag, 0 );// сумка

							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
							ADD_LINE_TO_CONVERSATION(0, "R11_NU", "CNT2_2", 0, 0);//Get the plates!
							START_SCRIPT_CONVERSATION(1, 1);
							SetSpeech();

							ADD_BLIP_FOR_PICKUP(bag, &hel_ico);
							CHANGE_BLIP_SPRITE(hel_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(hel_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(hel_ico, 0.6); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(hel_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CNT2_06", 5000, 1);//~g~The courier has died and dropped the plates, get to them before anyone else.

							keis = 1;
						}

						if (keis == 1)
						{
							if (HAS_PICKUP_BEEN_COLLECTED( bag ))
							{
								REMOVE_BLIP(hel_ico);//Удаляем иконку на радаре

								ADD_BLIP_FOR_COORD(-625.551, 246.349, 5.08937, &hel_ico);//создаем иконку на радаре
								CHANGE_BLIP_SPRITE(hel_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
								CHANGE_BLIP_COLOUR(hel_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
								CHANGE_BLIP_SCALE(hel_ico, 0.6); // масштаб иконки на радаре
								CHANGE_BLIP_NAME_FROM_TEXT_FILE(hel_ico, "NE_POINT");//иконка на радаре называние в истории карты "витрина"

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "CNT2_05", 5000, 1);//~g~You have the counterfeit plates. Take them to the print works.
								break;
							}
						}
					}
				}
				if (skip == 0)
				{
					while(true)
					{
						WAIT(0);
						DRAW_CHECKPOINT( -625.551, 246.349, 5.08937, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
						GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -625.551, 246.349, 5.08937, &PlayR);//проверка "игрок на координатах"
						if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
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
							POINT_CAM_AT_COORD	( camera, -644.978, 264.365, 8.10603 ); // куда смотрит камера
							SET_CAM_POS			( camera, -593.396, 234.504, 16.1353 );//расположение камеры
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
								DISPLAY_TEXT(0.5, 0.45, "CNT2_09");//PRINT WORKS ASSET COMPLETED
								WAIT( 0 );
								if ( TIMERA() > 5000 )
								{
									break;
								}
							}

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, -648.068, 257.938, 7.48352 ); // куда смотрит камера
							SET_CAM_POS			( camera, -647.136, 255.391, 8.43172 ); // расположение камеры

							PRINT_STRING_IN_STRING("string", "CNT2_10", 5000, 1);// = ~g~The print works will now generate revenue up to a maximum of $8000. Make sure you collect it regularly.

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
							skip = 2;
							break;
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
						{
							skip = 1;
							break;
						}
					}
				}

				// чистим скрипт тут
				WAIT( 100 );
				REMOVE_BLIP(count_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(hel_ico);//Удаляем иконку на радаре

				REMOVE_PICKUP(sweap_1);
				REMOVE_PICKUP(bag);
				REMOVE_PICKUP(aid_1);

				if (rrr_onV == 1)
				{
					STOP_PLAYBACK_RECORDED_CAR(car1);
				}
				if (rrr_on1 == 1)
				{
					STOP_PLAYBACK_RECORDED_CAR(car3);
				}
				if (rrr_on2 == 1)
				{
					STOP_PLAYBACK_RECORDED_CAR(car2);
				}
				if (rrr_on3 == 1)
				{
					STOP_PLAYBACK_RECORDED_CAR(car4);
				}
				REMOVE_CAR_RECORDING( 3062 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3063 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3064 ); // выгружаем пути транспорта
				REMOVE_CAR_RECORDING( 3065 ); // выгружаем пути транспорта

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель

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
					REGISTER_MISSION_PASSED( "S_CNT_2" );//Hit the Courier
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(5000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +5000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 5000);
					G_COUNT = 3;
					autosave = 1;
				}
				G_ONMISSION = 0;
			}
		}
//============================== Cap the Collector ======================================
		else if ((G_ONMISSION == 0) && (G_COUNT == 4))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-629.403, 255.797, 5.95213, &count_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(count_ico, BLIP_DEAL);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(count_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(count_ico, "LG_20");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			DRAW_CHECKPOINT( -629.403, 255.797, 5.95213, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -629.403, 255.797, 5.95213, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				start_scripted_cutscene("CAP_1", 15000, CUTSCENE_COUNTER);
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-1045.726, -292.454, 9.758, 97.607);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(count_ico);//Удаляем иконку на радаре
				blip_on = 0;
				skip = 0;
				in_cord = 0;
				business = 1;
				icon_on = 0;
				stop = 0;
				collector = 0;
				text = 1;
				text2 = 1;

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

				SET_CHAR_COORDINATES(GetPlayerPed(), -625.804, 246.421, 5.46582);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), -90.0);

				uint hour, minute, weather;
				GET_TIME_OF_DAY(&hour, &minute);
				GET_CURRENT_WEATHER(&weather);
				FORCE_WEATHER_NOW( WEATHER_EXTRA_SUNNY );//устанавливаем погода
				FORWARD_TO_TIME_OF_DAY(18, 20);//устанавливаем время
				RELEASE_WEATHER();
				
				Car car1, car2, car3;
				Ped ped1, ped2, ped3, ped4, ped5, ped6;
				Cam camera;
				Blip bus1_ico, bus2_ico, bus3_ico, bus4_ico, bus5_ico, bus6_ico;

				uint CarM1 = MODEL_SANCHEZ; //
				uint PedM1 = MODEL_IG_DARKO;// 
				uint PedM2 = MODEL_IG_DERRICK_MC;//
				uint ped1_hp, ped2_hp;

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);

				REQUEST_MODEL(PedM1);// 
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// 
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				
				CREATE_CAR(CarM1, -430.237, 109.167, 5.46784, &car1, TRUE);
				SET_CAR_HEADING(car1, -175.0);

				CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);// пилот
				CREATE_CHAR_AS_PASSENGER(car1, 1, PedM2, 0, &ped2);// пассажир
				SET_CHAR_COMPONENT_VARIATION(ped1, 1, 0, 1);
				SET_CHAR_COMPONENT_VARIATION(ped2, 1, 0, 1);
//
				UpdateWeaponOfPed(ped1, WEAPON_M4);
				UpdateWeaponOfPed(ped2, WEAPON_MP5);

				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_M4, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_MP5, TRUE);

				SET_CHAR_RELATIONSHIP_GROUP(ped1, 18);
				SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);

				//SET_CHAR_RELATIONSHIP(ped1, 5, 0);
				SET_CHAR_RELATIONSHIP(ped2, 5, 0);

				SET_SENSE_RANGE(ped1, 25.0);
				SET_SENSE_RANGE(ped2, 35.0);

				SET_CHAR_WILL_USE_COVER(ped1, 1);
				SET_CHAR_WILL_USE_COVER(ped2, 1);
				SET_CHAR_HEALTH(ped1, 1000);
				SET_CHAR_HEALTH(ped2, 1000);

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT( "CAP_1", 6 ); // загружаем субтитры из *.GTX
				START_CUTSCENE_NOW("cap_1");
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

				CLEAR_AREA(-430.237, 109.167, 5.46784, 50.0, 1);//очещаем зону загрузки
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -265.881, -950.416, 2.94725, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную

				// камера
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, PedX, PedY, PedZ ); // куда смотрит камера
				SET_CAM_POS			( camera, -443.338, 66.3797, 6.58122 );//расположение камеры
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_CAM_FOV( camera, 45.0 );
				SET_WIDESCREEN_BORDERS( 1 );
				SETTIMERA( 0 );

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "CAP1_B1", 15000, 1);//~g~The Mafia is taxing your businesses. Find them and kill them.

				while(true)
				{
					WAIT(0);
					GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					if (TIMERA() > 5000)
					{
						break;
					}

					POINT_CAM_AT_COORD	( camera, PedX, PedY, PedZ ); // куда смотрит камера
					SET_CAM_POS			( camera, -443.338, 66.3797, 6.58122 );//расположение камеры
				}
				SETTIMERA( 0 );

				while(true)
				{
					WAIT(0);
					GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					if (TIMERA() > 5000)
					{
						break;
					}

					POINT_CAM_AT_COORD	( camera, PedX, PedY, PedZ ); // куда смотрит камера
					SET_CAM_POS			( camera, -416.202, -57.5433, 20.3719 );//расположение камеры
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

				//убираем камеру
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				END_CAM_COMMANDS( &camera );
				SET_WIDESCREEN_BORDERS( 0 );
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

				ADD_BLIP_FOR_CHAR(ped1, &count_ico);
				CHANGE_BLIP_SPRITE(count_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
				CHANGE_BLIP_COLOUR(count_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
				CHANGE_BLIP_SCALE(count_ico, 0.6); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(count_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

				ADD_BLIP_FOR_COORD(-224.504, -946.921, 7.458, &bus1_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(bus1_ico, BLIP_BOAT_TOUR);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(bus1_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(bus1_ico, "LG_09");//иконка на радаре называние в истории карты ""

				ADD_BLIP_FOR_COORD(-584.339, -331.17, 6.98854, &bus2_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(bus2_ico, BLIP_GARAGE);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(bus2_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(bus2_ico, "LG_36");//иконка на радаре называние в истории карты ""

				ADD_BLIP_FOR_COORD(-443.132, -37.314, 5.065, &bus3_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(bus3_ico, BLIP_BAR);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(bus3_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(bus3_ico, "LG_17");//иконка на радаре называние в истории карты ""

				ADD_BLIP_FOR_COORD(-569.498, 738.454, 5.354, &bus4_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(bus4_ico, BLIP_TAXI_RANK);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(bus4_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(bus4_ico, "LG_18");//иконка на радаре называние в истории карты ""

				ADD_BLIP_FOR_COORD(363.606, 1465.63, 4.82587, &bus5_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(bus5_ico, BLIP_INTERNET);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(bus5_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(bus5_ico, "LG_12");//иконка на радаре называние в истории карты ""

				ADD_BLIP_FOR_COORD(896.841, 474.251, 5.389, &bus6_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(bus6_ico, BLIP_CLUB);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(bus6_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(bus6_ico, "LG_10");//иконка на радаре называние в истории карты "Боярский"

				while (TRUE)
				{
					WAIT(0);
					GET_CHAR_HEALTH(ped1, &ped1_hp);
					GET_CHAR_HEALTH(ped2, &ped2_hp);
					if (ped1_hp < 100)
					{
						EXPLODE_CHAR_HEAD(ped1);
					}
					if (ped2_hp < 100)
					{
						EXPLODE_CHAR_HEAD(ped2);
					}

					if ((IS_CHAR_DEAD(ped1)) && (!IS_CHAR_DEAD(ped2)) && (icon_on == 0))
					{
						icon_on = 1;
						REMOVE_BLIP(count_ico);//Удаляем иконку на радаре
						ADD_BLIP_FOR_CHAR(ped2, &count_ico);
						CHANGE_BLIP_SPRITE(count_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(count_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(count_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(count_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""
					}

					// боевые фразы тут
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_CHAR_COORDINATES(ped2,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					if (IS_CHAR_SHOOTING_IN_AREA(ped2, PlayX+15, PlayY+15, PlayX-15, PlayY-15, 0))
					{
						if ((text == 1) && (TIMERB() > 7000))
						{
							SetSpeech();
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R8_A_OA", "", 0, 0);//
							START_SCRIPT_CONVERSATION(1, 1);
							SETTIMERB( 0 );
							text = 2;
							text2 = 1;
						}
						else if ((text == 2) && (TIMERB() > 7000))
						{
							SetSpeech();
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R8_A_QA", "", 0, 0);//
							START_SCRIPT_CONVERSATION(1, 1);
							SETTIMERB( 0 );
							text = 1;
							text2 = 1;
						}
					}
					else if (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PedX+15, PedY+15, PedX-15, PedY-15, 0))
					{
						if ((text2 == 1) && (TIMERB() > 7000))
						{
							SetSpeech();
							NEW_SCRIPTED_CONVERSATION();
							ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
							ADD_LINE_TO_CONVERSATION(0, "R8_A_RA", "", 0, 0);//
							START_SCRIPT_CONVERSATION(1, 1);
							SETTIMERB( 0 );
							text2 = 2;
						}
					}

					if (business == 1) // Лодочная мастерская
					{
						if ((IS_CHAR_IN_AREA_3D( ped1, -258.381, -957.916, 2.947, -273.381, -942.916, 17.947, 0 )) && (in_cord == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CAP1_C2", 5000, 1);//~g~The Mafia has arrived at the Boatyard!

							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, PedX, PedY, PedZ, 4, 5.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

							// педы бигут за данью
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, -211.005, -951.826, 2.94725, 4, -2, 2.5);
							SetTime(1000);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, -211.005, -951.826, 2.94725, 4, -2, 2.5);
							in_cord = 1;
							SETTIMERA( 0 );
						}
						else if ((IS_CHAR_IN_AREA_3D( ped1, -203.505, -959.326, 2.947, -218.505, -944.326, 17.947, 0 )) && (in_cord == 1))
						{
							REMOVE_BLIP(bus1_ico);//Удаляем иконку на радаре
							CLEAR_PRINTS();
							G_COLLECTOR = 7;// бандос забирает деньги бизнеса.
							PRINT_STRING_IN_STRING("string", "CAP1_B2", 5000, 1);//~g~The Mafia has taxed the Boatyard!
							PRINT_STRING_IN_STRING("string", "CAP1_D2", 5000, 1);//~g~The Mafia is leaving the Boatyard!

							// сесть на байк
							TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, 10000, 0);// пед содится
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -589.857, -376.725, 4.73406, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							in_cord = 0;
							stop = 0;
							business = 2;
						}
						else if ((TIMERA() > 45000) && (in_cord == 1))
						{
							REMOVE_BLIP(bus1_ico);//Удаляем иконку на радаре
							CLEAR_PRINTS();
							G_COLLECTOR = 7;// бандос забирает деньги бизнеса.
							PRINT_STRING_IN_STRING("string", "CAP1_B2", 5000, 1);//~g~The Mafia has taxed the Boatyard!
							PRINT_STRING_IN_STRING("string", "CAP1_D2", 5000, 1);//~g~The Mafia is leaving the Boatyard!

							// сесть на байк
							TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, 10000, 0);// пед содится
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -589.857, -376.725, 4.73406, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							in_cord = 0;
							stop = 0;
							business = 2;
						}
					}
					else if (business == 2) // Автосалон
					{
						if ((IS_CHAR_IN_AREA_3D( ped1, -581.01, -389.694, 4.734, -609.033, -361.672, 19.734, 0 )) && (in_cord == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CAP1_C4", 5000, 1);//~g~The Mafia has arrived at the Car Showroom!

							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, PedX, PedY, PedZ, 4, 5.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

							// педы бигут за данью
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, -578.18, -332.647, 6.08898, 4, -2, 2.5);
							SetTime(1000);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, -578.18, -332.647, 6.08898, 4, -2, 2.5);
							in_cord = 1;
							SETTIMERA( 0 );
						}
						else if ((IS_CHAR_IN_AREA_3D( ped1, -575.68, -335.147, 6.089, -580.68, -330.147, 11.089, 0 )) && (in_cord == 1))
						{
							REMOVE_BLIP(bus2_ico);//Удаляем иконку на радаре
							CLEAR_PRINTS();
							G_COLLECTOR = 2;// бандос забирает деньги бизнеса.
							PRINT_STRING_IN_STRING("string", "CAP1_B4", 5000, 1);//~g~The Mafia has taxed the Car Showroom!
							PRINT_STRING_IN_STRING("string", "CAP1_D4", 5000, 1);//~g~The Mafia is leaving the Car Showroom!
							
							// сесть на байк
							TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, 10000, 0);// пед содится
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -417.169, -35.5722, 2.94725, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							in_cord = 0;
							stop = 0;
							business = 3;
						}
						else if ((TIMERA() > 45000) && (in_cord == 1))
						{
							REMOVE_BLIP(bus2_ico);//Удаляем иконку на радаре
							CLEAR_PRINTS();
							G_COLLECTOR = 2;// бандос забирает деньги бизнеса.
							PRINT_STRING_IN_STRING("string", "CAP1_B4", 5000, 1);//~g~The Mafia has taxed the Car Showroom!
							PRINT_STRING_IN_STRING("string", "CAP1_D4", 5000, 1);//~g~The Mafia is leaving the Car Showroom!
							
							// сесть на байк
							TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, 10000, 0);// пед содится
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -417.169, -35.5722, 2.94725, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							in_cord = 0;
							stop = 0;
							business = 3;
						}
					}
					else if (business == 3) // Фабрика мороженого
					{
						if ((IS_CHAR_IN_AREA_3D( ped1, -400.939, -52.233, 2.947, -433.981, -19.191, 17.947, 0 )) && (in_cord == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CAP1_C3", 5000, 1);//~g~The Mafia has arrived at the Ice Cream Factory!

							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, PedX, PedY, PedZ, 4, 5.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

							// педы бигут за данью
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, -443.446, -41.0813, 4.70368, 4, -2, 2.5);
							SetTime(1000);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, -443.446, -41.0813, 4.70368, 4, -2, 2.5);
							in_cord = 1;
							SETTIMERA( 0 );
						}
						else if ((IS_CHAR_IN_AREA_3D( ped1, -440.946, -43.581, 4.704, -445.946, -38.581, 9.704, 0 )) && (in_cord == 1))
						{
							REMOVE_BLIP(bus3_ico);//Удаляем иконку на радаре
							CLEAR_PRINTS();
							G_COLLECTOR = 4;// бандос забирает деньги бизнеса.
							PRINT_STRING_IN_STRING("string", "CAP1_B3", 5000, 1);//~g~The Mafia has taxed the Ice Cream Factory!
							PRINT_STRING_IN_STRING("string", "CAP1_D3", 5000, 1);//~g~The Mafia is leaving the Ice Cream Factory!
					
							// сесть на байк
							TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, 10000, 0);// пед содится
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -586.722, 733.262, 4.86954, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							in_cord = 0;
							stop = 0;
							business = 4;
						}
						else if ((TIMERA() > 45000) && (in_cord == 1))
						{
							REMOVE_BLIP(bus3_ico);//Удаляем иконку на радаре
							CLEAR_PRINTS();
							G_COLLECTOR = 4;// бандос забирает деньги бизнеса.
							PRINT_STRING_IN_STRING("string", "CAP1_B3", 5000, 1);//~g~The Mafia has taxed the Ice Cream Factory!
							PRINT_STRING_IN_STRING("string", "CAP1_D3", 5000, 1);//~g~The Mafia is leaving the Ice Cream Factory!
					
							// сесть на байк
							TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, 10000, 0);// пед содится
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -586.722, 733.262, 4.86954, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							in_cord = 0;
							stop = 0;
							business = 4;
						}
					}
					else if (business == 4) // Таксопарк
					{
						if ((IS_CHAR_IN_AREA_3D( ped1, -570.474, 717.406, 2.947, -601.344, 748.275, 17.947, 0 )) && (in_cord == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CAP1_C5", 5000, 1);//~g~The Mafia has arrived at the Taxi Firm!

							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, PedX, PedY, PedZ, 4, 5.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

							// педы бигут за данью
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, -561.819, 724.629, 5.06957, 4, -2, 2.5);
							SetTime(1000);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, -561.819, 724.629, 5.06957, 4, -2, 2.5);
							in_cord = 1;
							SETTIMERA( 0 );
						}
						else if ((IS_CHAR_IN_AREA_3D( ped1, -559.319, 722.129, 5.07, -564.319, 727.129, 10.07, 0 )) && (in_cord == 1))
						{
							REMOVE_BLIP(bus4_ico);//Удаляем иконку на радаре
							CLEAR_PRINTS();
							G_COLLECTOR = 5;// бандос забирает деньги бизнеса.
							PRINT_STRING_IN_STRING("string", "CAP1_B5", 5000, 1);//~g~The Mafia has taxed the Taxi Firm!
							PRINT_STRING_IN_STRING("string", "CAP1_D5", 5000, 1);//~g~The Mafia is leaving the Taxi Firm!
							
							// сесть на байк
							TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, 10000, 0);// пед содится
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -565.705,853.455, 4.76485, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							in_cord = 0;
							stop = 0;
							business = 5;
						}
						else if ((TIMERA() > 45000) && (in_cord == 1))
						{
							REMOVE_BLIP(bus4_ico);//Удаляем иконку на радаре
							CLEAR_PRINTS();
							G_COLLECTOR = 5;// бандос забирает деньги бизнеса.
							PRINT_STRING_IN_STRING("string", "CAP1_B5", 5000, 1);//~g~The Mafia has taxed the Taxi Firm!
							PRINT_STRING_IN_STRING("string", "CAP1_D5", 5000, 1);//~g~The Mafia is leaving the Taxi Firm!
							
							// сесть на байк
							TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, 10000, 0);// пед содится
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -565.705,853.455, 4.76485, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							in_cord = 0;
							stop = 0;
							business = 5;
						}
					}
					else if (business == 5) // Киностудия
					{
						if ((IS_CHAR_IN_AREA_3D( ped1, 478.322, 1470.84, 2.947, 427.142, 1522.02, 17.947, 0 )) && (in_cord == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CAP1_C0", 5000, 1);//~g~The Mafia has arrived at the film studio!

							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, PedX, PedY, PedZ, 4, 5.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

							// педы бигут за данью
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, 432.593, 1491.95, 4.50785, 4, -2, 2.5);
							SetTime(1000);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 432.593, 1491.95, 4.50785, 4, -2, 2.5);
							in_cord = 1;
							SETTIMERA( 0 );
						}
						else if ((IS_CHAR_IN_AREA_3D( ped1, 435.093, 435.093, 4.508, 430.093, 1494.453, 9.508, 0 )) && (in_cord == 1))
						{
							REMOVE_BLIP(bus5_ico);//Удаляем иконку на радаре
							CLEAR_PRINTS();
							G_COLLECTOR = 3;// бандос забирает деньги бизнеса.
							PRINT_STRING_IN_STRING("string", "CAP1_B0", 5000, 1);//~g~The mafia has taxed the film studio!
							PRINT_STRING_IN_STRING("string", "CAP1_D0", 5000, 1);//~g~The Mafia is leaving the film studio!
							
							// сесть на байк
							SET_CAR_COORDINATES(car1, 452.267, 1494.87, 5.37265);// перемещаем
							SET_CAR_HEADING(car1, -15.0);
							TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, 10000, 0);// пед содится
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, 939.516, 451.099, 2.94725, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							in_cord = 0;
							stop = 0;
							business = 6;
						}
						else if ((TIMERA() > 45000) && (in_cord == 1))
						{
							REMOVE_BLIP(bus5_ico);//Удаляем иконку на радаре
							CLEAR_PRINTS();
							G_COLLECTOR = 3;// бандос забирает деньги бизнеса.
							PRINT_STRING_IN_STRING("string", "CAP1_B0", 5000, 1);//~g~The mafia has taxed the film studio!
							PRINT_STRING_IN_STRING("string", "CAP1_D0", 5000, 1);//~g~The Mafia is leaving the film studio!
							
							// сесть на байк
							SET_CAR_COORDINATES(car1, 452.267, 1494.87, 5.37265);// перемещаем
							SET_CAR_HEADING(car1, -15.0);
							TASK_ENTER_CAR_AS_PASSENGER(ped2, car1, 10000, 0);// пед содится
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, 939.516, 451.099, 2.94725, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							in_cord = 0;
							stop = 0;
							business = 6;
						}
					}
					else if (business == 6) // Клуб «Малибу»
					{
						if ((IS_CHAR_IN_AREA_3D( ped1, 955.004, 435.61, 2.947, 924.027, 466.587, 17.947, 0 )) && (in_cord == 0))
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CAP1_C9", 5000, 1);//~g~The Mafia has arrived at The Malibu!

							GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, PedX, PedY, PedZ, 4, 5.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

							// педы бигут за данью
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, 920.749, 458.672, 5.10549, 4, -2, 2.5);
							SetTime(1000);
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 920.749, 458.672, 5.10549, 4, -2, 2.5);
							in_cord = 1;
							SETTIMERA( 0 );
						}
						else if ((IS_CHAR_IN_AREA_3D( ped1, 923.249, 456.172, 5.105, 918.249, 461.172, 10.105, 0 )) && (in_cord == 1))
						{
							REMOVE_BLIP(bus6_ico);//Удаляем иконку на радаре
							CLEAR_PRINTS();
							G_COLLECTOR = 6;// бандос забирает деньги бизнеса.
							PRINT_STRING_IN_STRING("string", "CAP1_B9", 5000, 1);//~g~The mafia has taxed The Malibu!
							SetTime(3000);

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CAP1_B8", 5000, 1);//~r~The collector has taxed all of your businesses.
							skip = 1;// переменная пропуска
							break;
						}
						else if ((TIMERA() > 45000) && (in_cord == 1))
						{
							REMOVE_BLIP(bus6_ico);//Удаляем иконку на радаре
							CLEAR_PRINTS();
							G_COLLECTOR = 6;// бандос забирает деньги бизнеса.
							PRINT_STRING_IN_STRING("string", "CAP1_B9", 5000, 1);//~g~The mafia has taxed The Malibu!
							SetTime(3000);

							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CAP1_B8", 5000, 1);//~r~The collector has taxed all of your businesses.
							skip = 1;// переменная пропуска
							break;
						}
					}
					//-----------------
					if ((business == 1) && (stop == 0)) // Лодочная мастерская
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -265.881, -950.416, 2.94725, &PedR);//проверка "игрок на координатах"
						if ( PedR < 50.5)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -265.881, -950.416, 2.94725, 4, 10.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							stop = 1;
						}
					}
					else if ((business == 2) && (stop == 0)) // Автосалон
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -589.857, -376.725, 4.73406, &PedR);//проверка "игрок на координатах"
						if ( PedR < 50.5)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -589.857, -376.725, 4.73406, 4, 10.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							stop = 1;
						}
					}
					else if ((business == 3) && (stop == 0)) // Фабрика мороженого
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -417.169, -35.5722, 2.94725, &PedR);//проверка "игрок на координатах"
						if ( PedR < 50.5)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -417.169, -35.5722, 2.94725, 4, 10.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							stop = 1;
						}
					}
					else if ((business == 4) && (stop == 0)) // Таксопарк
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -586.722, 733.262, 4.86954, &PedR);//проверка "игрок на координатах"
						if ( PedR < 50.5)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -586.722, 733.262, 4.86954, 4, 10.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							stop = 1;
						}
					}
					else if ((business == 5) && (stop == 0)) // Киностудия пойнт 1
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -565.705, 853.455, 4.76485, &PedR);//проверка "игрок на координатах"
						if ( PedR < 25.5)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -266.152, 824.817, 3.9066, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							stop = 1;
						}
					}
					else if ((business == 5) && (stop == 1)) // Киностудия пойнт 2
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -266.152, 824.817, 3.9066, &PedR);//проверка "игрок на координатах"
						if ( PedR < 25.5)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -239.803, 1284.79, 3.9066, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							stop = 2;
						}
					}
					else if ((business == 5) && (stop == 2)) // Киностудия пойнт 3
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -239.803, 1284.79, 3.9066, &PedR);//проверка "игрок на координатах"
						if ( PedR < 25.5)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -253.418, 1716.61, 3.9066, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							stop = 3;
						}
					}
					else if ((business == 5) && (stop == 3)) // Киностудия пойнт 4
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -253.418, 1716.61, 3.9066, &PedR);//проверка "игрок на координатах"
						if ( PedR < 65.5)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -253.418, 1716.61, 3.9066, 4, 10.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							stop = 4;
						}
					}
					else if ((business == 5) && (stop == 4)) // Киностудия пойнт 4.5
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, -253.418, 1716.61, 3.9066, &PedR);//проверка "игрок на координатах"
						if ( PedR < 25.5)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, 452.732, 1496.43, 2.94725, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							stop = 5;
						}
					}
					else if ((business == 5) && (stop == 5)) // Киностудия пойнт 5
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 452.732, 1496.43, 2.94725, &PedR);//проверка "игрок на координатах"
						if ( PedR < 50.5)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, 452.732, 1496.43, 2.94725, 4, 10.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							stop = 6;
						}
					}
					else if ((business == 6) && (stop == 0)) // Клуб «Малибу»
					{
						GET_CHAR_COORDINATES(ped1,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
						GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, 939.516, 451.099, 2.94725, &PedR);//проверка "игрок на координатах"
						if ( PedR < 50.5)
						{
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, 939.516, 451.099, 2.94725, 4, 10.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
							stop = 1;
						}
					}

					if ((IS_CHAR_DEAD(ped1)) && (IS_CHAR_DEAD(ped2)))
					{
						stop = 0;
						in_cord = 0;
						icon_on = 0;
						collector += 1;
						if (business < 6)
						{
							business += 1;
						}

						REMOVE_BLIP(count_ico);//Удаляем иконку на радаре
						MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
						MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
						MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
						CREATE_CAR(CarM1, -575.307, -314.17, 1.3906, &car1, TRUE);

						CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);// пилот
						CREATE_CHAR_AS_PASSENGER(car1, 1, PedM2, 0, &ped2);// пассажир

						UpdateWeaponOfPed(ped1, WEAPON_M4);
						UpdateWeaponOfPed(ped2, WEAPON_MP5);

						SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_M4, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_MP5, TRUE);

						SET_CHAR_RELATIONSHIP_GROUP(ped1, 18);
						SET_CHAR_RELATIONSHIP_GROUP(ped2, 5);

						SET_CHAR_RELATIONSHIP(ped2, 5, 0);

						SET_SENSE_RANGE(ped1, 25.0);
						SET_SENSE_RANGE(ped2, 35.0);

						SET_CHAR_WILL_USE_COVER(ped1, 1);
						SET_CHAR_WILL_USE_COVER(ped2, 1);

						SET_CHAR_WILL_USE_COVER(ped1, 1);
						SET_CHAR_WILL_USE_COVER(ped2, 1);
						SET_CHAR_HEALTH(ped1, 1000);
						SET_CHAR_HEALTH(ped2, 1000);

						if (business == 2)
						{
							SET_CAR_COORDINATES(car1, -430.237, 109.167, 5.46784);// перемещаем игрока
							SET_CAR_HEADING(car1, -175.0);
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -584.936, -370.159, 4.73406, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						}
						else if (business == 3)
						{
							SET_CAR_COORDINATES(car1, -404.874, 440.351, 5.44965);// перемещаем игрока
							SET_CAR_HEADING(car1, 150.0);
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -423.202, -35.262, 2.94725, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						}
						else if (business == 4)
						{
							SET_CAR_COORDINATES(car1, -408.128, 434.495, 5.44965);// перемещаем игрока
							SET_CAR_HEADING(car1, -25.0);
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -578.062, 730.896, 2.94725, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						}
						else if (business == 5)
						{
							stop = 2;
							SET_CAR_COORDINATES(car1, -244.243, 1150.6, 5.56032);// перемещаем игрока
							SET_CAR_HEADING(car1, -5.0);
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, -239.803, 1284.79, 3.9066, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						}
						else if (business == 6)
						{
							SET_CAR_COORDINATES(car1, 784.174, 1478.24, 13.2269);// перемещаем игрока
							SET_CAR_HEADING(car1, -100.0);
							TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, 939.516, 451.099, 2.94725, 4, 25.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
						}

						ADD_BLIP_FOR_CHAR(ped1, &count_ico);
						CHANGE_BLIP_SPRITE(count_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(count_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(count_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(count_ico, "MO_TARGET");//иконка на радаре называние в истории карты ""

						if (collector < 3)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "CAP1B10", 5000, 1);//You've capped the Collectors. More are on their way.
                        }   
                    }
					if (collector == 3)
					{
						skip = 2;// переменная пропуска
						break;
					}

					//провал миссии 
					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
					{
						skip = 1;// переменная пропуска
						break;
					}
				}

				// чистим скрипт
				WAIT( 100 );
				REMOVE_BLIP(count_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(bus1_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(bus2_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(bus3_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(bus4_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(bus5_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(bus6_ico);//Удаляем иконку на радаре

				

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель

				// выгружвем педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет

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
					REGISTER_MISSION_PASSED( "S_CAP_1" );//Cap the Collector
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(30000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +30000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 30000);
					G_COUNT = 5;
					autosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}
//============================== Keep your Friends Close... ======================================
		else if ((G_ONMISSION == 0) && (G_COUNT == 6))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(54.6656, -43.6248, 19.2045, &count_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(count_ico, BLIP_VLAD);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(count_ico, 1.1); // масштаб иконки на радаре
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(count_ico, "LG_24");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 56.6656, -41.6248, 19.2045, 52.6656, -45.6248, 27.2045, 0 )) && (get_money == 0))
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				get_money = 1;
				if (money_ped >= 1000)
				{
					get_money = 2;
				}
				else
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP_FOREVER("FIN_B6"); //You do not have enough money to start this mission.
					get_money = 3;
				}
			}
			else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 56.6656, -41.6248, 19.2045, 52.6656, -45.6248, 27.2045, 0 )) && (get_money > 0)) 
			{
				CLEAR_HELP(); // удаляем текст подсказки
				get_money = 0;
			}
			DRAW_CHECKPOINT( 54.6656, -43.6248, 19.2045, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, 54.6656, -43.6248, 19.2045, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (get_money == 2))
			{
				G_ONMISSION = 1;
				AddShortCutDropOffPointForMission(-288.2, -487.5, 9.8, 275.0);
				INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
				REMOVE_BLIP(count_ico);//Удаляем иконку на радаре
				blip_on = 0;
				skip = 0;
				in_cord = 0;
				lance = 99;
				hate = 0;
				Sonny = 0;
				anim = 0;
				animP1 = 0;
				animP2 = 0;
				animP3 = 0;
				animP4 = 0;
				blip_on2 = 0;
				sound = 0;

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

				SET_CHAR_COORDINATES(GetPlayerPed(), 54.6656, -59.1096, 20.13);// перемещаем игрока
				SET_CHAR_HEADING(GetPlayerPed(), 0.0);
				SET_MAX_WANTED_LEVEL(0);
				SET_CHAR_HEALTH(GetPlayerPed(), 200);
				ADD_ARMOUR_TO_CHAR(GetPlayerPed(), 100);
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока

				Car car1, car2, car3;
				Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12;
				Object barrel_1, barrel_2, barrel_3, barrel_4, barrel_5, barrel_6, barrel_7, barrel_8, barrel_9, barrel_10, barrel_11, barrel_12;
				Object kaska_1;
				Pickup sweap_1, sweap_2, aid_1, aid_2;
				Cam camera;
				int dm, cdm;
				Blip ped_ico, heal_ico, safe_ico;
				Texture page_1, page_2;

				textur1 = LOAD_TXD( "final_credits" );
				page_1 = GET_TEXTURE( textur1, "page_1" );
				page_2 = GET_TEXTURE( textur1, "page_2" );

				uint CarM1 = MODEL_STRETCH; // лимузин
				uint PedM1 = MODEL_IG_LILJACOB;// Ленс
				uint PedM2 = MODEL_IG_VLAD;// Сонни
				uint PedM3 = MODEL_IG_DARKO;// Приспешник 1
				uint PedM4 = MODEL_IG_DERRICK_MC;// Приспешник 2
				uint barrel = barrel1;// бочка
				uint barre2 = barrel4;// бочка
				uint kaska = headshot_off;
				uint random, random2, ped1_hp, ped2_hp, ped3_hp, ped4_hp, ped5_hp, ped6_hp, ped7_hp, ped8_hp, ped9_hp, playHP;
				uint hour, minute, weather, AudID;

				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				REQUEST_MODEL(PedM1);// 
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM2);// 
				while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM3);// 
				while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(PedM4);// 
				while (!HAS_MODEL_LOADED(PedM4));////проверка "пед загрузился" если нет то начанаем с начало
				REQUEST_MODEL(barrel);// бочки
				while (!HAS_MODEL_LOADED(barrel)) WAIT(0);
				REQUEST_MODEL(barre2);// бочки
				while (!HAS_MODEL_LOADED(barre2)) WAIT(0);
				REQUEST_MODEL(kaska);
				while (!HAS_MODEL_LOADED(kaska)) WAIT(0);

				//------------ катсцена ----------------
				LOAD_ADDITIONAL_TEXT("fin", 0);
				int state = 0;
				START_CUTSCENE_NOW("fin");
				while (!HAS_CUTSCENE_LOADED()) {
					WAIT(0);
				}
				PRINT_BIG("FIN_1", 5000, 2);//Keep your Friends Close...
				DO_SCREEN_FADE_IN(0);
				while (!HAS_CUTSCENE_FINISHED()) {
					WAIT(0);
					if ((state == 0) && (GET_CUTSCENE_AUDIO_TIME_MS() > 57100)) {
						DO_SCREEN_FADE_OUT(5000);
						state++;
					} else if ((state == 1) && (GET_CUTSCENE_AUDIO_TIME_MS() > 62500)) {
						DO_SCREEN_FADE_IN(2000);
						state++;
					} else if ((state == 2) && (GET_CUTSCENE_AUDIO_TIME_MS() > 150350)) {
						SET_SPRITES_DRAW_BEFORE_FADE(1);
						DRAW_RECT(0.5, 0.5, 1.0, 1.0, 0, 0, 0, 255);
					}
				}
				if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT())) {
					if (GET_CUTSCENE_AUDIO_TIME_MS() > 150350) {
						SET_SPRITES_DRAW_BEFORE_FADE(1);
						DRAW_RECT(0.5, 0.5, 1.0, 1.0, 0, 0, 0, 255);
					}
					DO_SCREEN_FADE_IN(0);
				}

				//LOAD_ADDITIONAL_TEXT( "FIN", 6 ); // загружаем субтитры из *.GTX
				//START_CUTSCENE_NOW("fin");
				//while (!HAS_CUTSCENE_LOADED())
				//{
				//	WAIT(0);
				//}

				//DO_SCREEN_FADE_IN(0);
				//while (!HAS_CUTSCENE_FINISHED())
				//{
				//	WAIT(0);
				//}
				//LOAD_ADDITIONAL_TEXT( "FIN_2", 6 ); // загружаем субтитры из *.GTX
				//FORWARD_TO_TIME_OF_DAY(6, 0);//устанавливаем время
				//START_CUTSCENE_NOW("fin_2");
				//while (!HAS_CUTSCENE_LOADED())
				//{
				//	WAIT(0);
				//}

				//DO_SCREEN_FADE_IN(0);
				//while (!HAS_CUTSCENE_FINISHED())
				//{
				//	WAIT(0);
				//}

				//if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
				//{
				//	DO_SCREEN_FADE_IN(0);
				//}

				LOAD_CHAR_DECISION_MAKER(2, &dm);
				LOAD_COMBAT_DECISION_MAKER(3, &cdm);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
				SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);

				// создаём бочки
				CREATE_OBJECT_NO_OFFSET(barrel, 72.246, -48.146, 31.3786, &barrel_1, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 72.517, -47.252, 31.3786, &barrel_2, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 72.123, -46.425, 31.3786, &barrel_3, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 72.171, -40.395, 31.3786, &barrel_4, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 72.007, -39.515, 31.3786, &barrel_5, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 72.171, -38.658, 31.3786, &barrel_6, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 71.941, -37.831, 31.3786, &barrel_7, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 89.617, -42.322, 31.3786, &barrel_8, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 89.453, -41.441, 31.3786, &barrel_9, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 89.617, -40.585, 31.3786, &barrel_10, TRUE);
				CREATE_OBJECT_NO_OFFSET(barrel, 89.385, -39.756, 31.3786, &barrel_11, TRUE);
				CREATE_OBJECT_NO_OFFSET(barre2, 67.613, -48.496, 31.3786, &barrel_12, TRUE);
				CREATE_OBJECT_NO_OFFSET(kaska, 1.1, 1.1, 1.1, &kaska_1, TRUE);
				SET_OBJECT_HEALTH(kaska_1, 1000);

				// грузим анимации
				REQUEST_ANIMS( "missbankjob" );
				while (!HAVE_ANIMS_LOADED( "missbankjob" )) WAIT(0);

				CREATE_CAR(CarM1, 41.3687, 16.9731, 7.34593, &car1, TRUE);
				SET_CAR_HEADING(car1, 105.0);
				CREATE_CAR(CarM1, 54.0494, 17.7102, 7.34593, &car2, TRUE);
				SET_CAR_HEADING(car2, 90.0);
				CREATE_CAR(CarM1, 67.7153, 16.8315, 7.34593, &car3, TRUE);
				SET_CAR_HEADING(car3, 80.0);

				CHANGE_CAR_COLOUR( car1, 112, 112 );//цвет машины
				CHANGE_CAR_COLOUR( car2, 112, 112 );//цвет машины
				CHANGE_CAR_COLOUR( car3, 112, 112 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car1, 112, 112 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car2, 112, 112 );//цвет машины
				SET_EXTRA_CAR_COLOURS( car3, 112, 112 );//цвет машины

				CREATE_CHAR (26, PedM1, 290.493, -783.023, 4.63619, &ped1, TRUE);// Ленс
				CREATE_CHAR (26, PedM2, 288.569, -783.023, 4.63619, &ped2, TRUE);// Сонни
				CREATE_CHAR (26, PedM3, 296.021, -778.305, 4.63619, &ped3, TRUE);// 
				CREATE_CHAR (26, PedM4, 294.021, -778.305, 4.63619, &ped4, TRUE);// 
				CREATE_CHAR (26, PedM3, 292.021, -778.305, 4.63619, &ped5, TRUE);//
				CREATE_CHAR (26, PedM4, 290.021, -778.305, 4.63619, &ped6, TRUE);//
				CREATE_CHAR (26, PedM3, 288.021, -778.305, 4.63619, &ped7, TRUE);//
				CREATE_CHAR (26, PedM4, 286.021, -778.305, 4.63619, &ped8, TRUE);//
				CREATE_CHAR (26, PedM3, 284.021, -778.305, 4.63619, &ped9, TRUE);//
				CREATE_CHAR (26, PedM3, 282.021, -778.305, 4.63619, &ped10, TRUE);//
				CREATE_CHAR (26, PedM3, 280.021, -778.305, 4.63619, &ped11, TRUE);//
				CREATE_CHAR (26, PedM3, 278.021, -778.305, 4.63619, &ped12, TRUE);//
				SET_CHAR_HEALTH(ped1, 500);
				SET_CHAR_HEALTH(ped2, 500);

				UpdateWeaponOfPed(ped1, WEAPON_AK47);
				UpdateWeaponOfPed(ped2, WEAPON_M4);
				UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped10, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped11, WEAPON_EPISODIC_12);
				UpdateWeaponOfPed(ped12, WEAPON_EPISODIC_12);

				SET_CURRENT_CHAR_WEAPON(ped1, WEAPON_AK47, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped2, WEAPON_M4, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped10, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped11, WEAPON_EPISODIC_12, TRUE);
				SET_CURRENT_CHAR_WEAPON(ped12, WEAPON_EPISODIC_12, TRUE);

				SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
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

				SET_CHAR_RELATIONSHIP(ped1, 5, 0);
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

				SET_SENSE_RANGE(ped1, 25.0);
				SET_SENSE_RANGE(ped2, 0.05);
				SET_SENSE_RANGE(ped3, 25.0);
				SET_SENSE_RANGE(ped4, 25.0);
				SET_SENSE_RANGE(ped5, 25.0);
				SET_SENSE_RANGE(ped6, 25.0);
				SET_SENSE_RANGE(ped7, 0.05);
				SET_SENSE_RANGE(ped8, 0.05);
				SET_SENSE_RANGE(ped9, 0.05);
				SET_SENSE_RANGE(ped10, 80.0);
				SET_SENSE_RANGE(ped11, 80.0);
				SET_SENSE_RANGE(ped12, 80.0);

				SET_CHAR_WILL_USE_COVER(ped1, 1);
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

				set_cord(1);
				SET_CHAR_COORDINATES(ped3, set_X, set_Y, set_Z);// перемещаем игрока
				set_cord(2);
				SET_CHAR_COORDINATES(ped4, set_X, set_Y, set_Z);// перемещаем игрока
				set_cord(2);
				SET_CHAR_COORDINATES(ped5, set_X, set_Y, set_Z);// перемещаем игрока
				set_cord(3);
				SET_CHAR_COORDINATES(ped6, set_X, set_Y, set_Z);// перемещаем игрока

				TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped3, 59.992, -63.3677, 19.2045, 4, -2, 2.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped4, 59.992, -63.3677, 19.2045, 4, -2, 2.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped5, 59.992, -63.3677, 19.2045, 4, -2, 2.5);
				TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped6, 59.992, -63.3677, 19.2045, 4, -2, 2.5);

				CLEAR_PRINTS();
				PRINT_STRING_IN_STRING("string", "FIN_B3", 5000, 1);//~g~The Mafia are trying to steal your money. Defend the safe.

				//создаём пушку и аптечку
				CREATE_PICKUP_ROTATE(w_eagle, 3, 24, 59.4046, -59.4459, 20.2107, -90.0, 180.0, 80.0, &sweap_1);// даём винтовку
				CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 61.2166, -58.4282, 20.5471, 90.0, 0.0, -140.0, &aid_1);//Аптека
				ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(sweap_1, "mansion_int");
				ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(aid_1, "mansion_int");
				SETTIMERC( 0 );

				while (TRUE)
				{
					WAIT(5);
					//DISPLAY_TEXT_WITH_NUMBER(0.9203125, 0.68787074, "CP_TIME_NOZERO", ped1_hp);// 
					//DISPLAY_TEXT_WITH_NUMBER(0.9203125, 0.65787074, "CP_TIME_NOZERO", playHP);// 

					GET_CHAR_HEALTH(ped1, &ped1_hp);
					GET_CHAR_HEALTH(ped2, &ped2_hp);
					GET_CHAR_HEALTH(ped3, &ped3_hp);
					GET_CHAR_HEALTH(ped4, &ped4_hp);
					GET_CHAR_HEALTH(ped5, &ped5_hp);
					GET_CHAR_HEALTH(ped6, &ped6_hp);
					GET_CHAR_HEALTH(ped7, &ped7_hp);
					GET_CHAR_HEALTH(ped8, &ped8_hp);
					GET_CHAR_HEALTH(ped9, &ped9_hp);
					GET_CHAR_HEALTH(GetPlayerPed(), &playHP);
					
					STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную

					if ((ped3_hp < 100) && (exp1 == 0))
					{
						//SETTIMERB( 0 );
						EXPLODE_CHAR_HEAD(ped3);
						exp1 = 1;
						WAIT(25);
					}
					if ((ped4_hp < 100) && (exp2 == 0))
					{
						//SETTIMERB( 0 );
						EXPLODE_CHAR_HEAD(ped4);
						exp2 = 1;
						WAIT(25);
					}
					if ((ped5_hp < 100) && (exp3 == 0))
					{
						//SETTIMERB( 0 );
						EXPLODE_CHAR_HEAD(ped5);
						exp3 = 1;
						WAIT(25);
					}
					if ((ped6_hp < 100) && (exp4 == 0))
					{
						//SETTIMERB( 0 );
						EXPLODE_CHAR_HEAD(ped6);
						exp4 = 1;
						WAIT(25);
					}
					if (ped7_hp < 100)
					{
						EXPLODE_CHAR_HEAD(ped7);
						WAIT(25);
					}
					if (ped8_hp < 100)
					{
						EXPLODE_CHAR_HEAD(ped8);
						WAIT(25);
					}
					if (ped9_hp < 100)
					{
						EXPLODE_CHAR_HEAD(ped9);
						WAIT(25);
					}

					GENERATE_RANDOM_INT_IN_RANGE( 1, 16, &random);

					// сегмент с сэйфом
					if (IS_CHAR_DEAD(ped3))
					{
						if (TIMERB() > 4000)
						{
							DELETE_CHAR(&ped3);//удаляем модель педа
							//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет
							CREATE_CHAR (26, PedM3, 296.021, -778.305, 4.63619, &ped3, TRUE);// 
							SET_CHAR_DECISION_MAKER(ped3, dm);
							SET_COMBAT_DECISION_MAKER(ped3, cdm);

							GENERATE_RANDOM_INT_IN_RANGE( 1, 10, &random2);
							if ((random2 == 1) || (random2 == 5) || (random2 == 9))
							{
								UpdateWeaponOfPed(ped3, WEAPON_EPISODIC_12);
								SET_CURRENT_CHAR_WEAPON(ped3, WEAPON_EPISODIC_12, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped3, 5);
								SET_CHAR_RELATIONSHIP(ped3, 5, 0);
								SET_SENSE_RANGE(ped3, 25.0);
								SET_CHAR_WILL_USE_COVER(ped3, 1);
							}
							else
							{
								SET_CHAR_RELATIONSHIP_GROUP(ped3, 17);
							}

							set_cord(random);
							SET_CHAR_COORDINATES(ped3, set_X, set_Y, set_Z);// перемещаем игрока
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped3, 59.992, -63.3677, 19.2045, 4, -2, 2.5);
							SETTIMERB( 0 );
							anim = 0;
							animP1 = 0;
							exp1 = 0;
							WAIT(25);
						}
					}
					else if (IS_CHAR_DEAD(ped4))
					{
						if (TIMERB() > 4000)
						{
							DELETE_CHAR(&ped4);//удаляем модель педа
							//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет
							CREATE_CHAR (26, PedM4, 296.021, -778.305, 4.63619, &ped4, TRUE);//
							SET_CHAR_DECISION_MAKER(ped4, dm);
							SET_COMBAT_DECISION_MAKER(ped4, cdm);
							

							GENERATE_RANDOM_INT_IN_RANGE( 1, 10, &random2);
							if ((random2 == 1) || (random2 == 5) || (random2 == 9) || (Sonny == 2))
							{
								UpdateWeaponOfPed(ped4, WEAPON_EPISODIC_12);
								SET_CURRENT_CHAR_WEAPON(ped4, WEAPON_EPISODIC_12, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped4, 5);
								SET_CHAR_RELATIONSHIP(ped4, 5, 0);
								SET_SENSE_RANGE(ped4, 25.0);
								SET_CHAR_WILL_USE_COVER(ped4, 1);
							}
							else
							{
								SET_CHAR_RELATIONSHIP_GROUP(ped4, 17);
							}

							set_cord(random);
							SET_CHAR_COORDINATES(ped4, set_X, set_Y, set_Z);// перемещаем игрока
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped4, 59.992, -63.3677, 19.2045, 4, -2, 2.5);
							SETTIMERB( 0 );
							anim = 0;
							animP2 = 0;
							exp2 = 0;
							WAIT(25);
						}
					}
					else if (IS_CHAR_DEAD(ped5))
					{
						if (TIMERB() > 4000)
						{
							DELETE_CHAR(&ped5);//удаляем модель педа
							//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет
							CREATE_CHAR (26, PedM3, 296.021, -778.305, 4.63619, &ped5, TRUE);//
							SET_CHAR_DECISION_MAKER(ped5, dm);
							SET_COMBAT_DECISION_MAKER(ped5, cdm);
							

							GENERATE_RANDOM_INT_IN_RANGE( 1, 10, &random2);
							if ((random2 == 1) || (random2 == 5) || (random2 == 9) || (Sonny == 2))
							{
								UpdateWeaponOfPed(ped5, WEAPON_EPISODIC_12);
								SET_CURRENT_CHAR_WEAPON(ped5, WEAPON_EPISODIC_12, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped5, 5);
								SET_CHAR_RELATIONSHIP(ped5, 5, 0);
								SET_SENSE_RANGE(ped5, 25.0);
								SET_CHAR_WILL_USE_COVER(ped5, 1);
							}
							else
							{
								SET_CHAR_RELATIONSHIP_GROUP(ped5, 17);
							}

							set_cord(random);
							SET_CHAR_COORDINATES(ped5, set_X, set_Y, set_Z);// перемещаем игрока
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped5, 59.992, -63.3677, 19.2045, 4, -2, 2.5);
							SETTIMERB( 0 );
							anim = 0;
							animP3 = 0;
							exp3 = 0;
							WAIT(25);
						}
					}
					else if (IS_CHAR_DEAD(ped6))
					{
						if (TIMERB() > 4000)
						{
							DELETE_CHAR(&ped6);//удаляем модель педа
							//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет
							CREATE_CHAR (26, PedM4, 296.021, -778.305, 4.63619, &ped6, TRUE);// 
							SET_CHAR_DECISION_MAKER(ped6, dm);
							SET_COMBAT_DECISION_MAKER(ped6, cdm);
							
							GENERATE_RANDOM_INT_IN_RANGE( 1, 10, &random2);
							if ((random2 == 1) || (random2 == 5) || (random2 == 9) || (Sonny == 2))
							{
								UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_12);
								SET_CURRENT_CHAR_WEAPON(ped6, WEAPON_EPISODIC_12, TRUE);
								SET_CHAR_RELATIONSHIP_GROUP(ped6, 5);
								SET_CHAR_RELATIONSHIP(ped6, 5, 0);
								SET_SENSE_RANGE(ped6, 25.0);
								SET_CHAR_WILL_USE_COVER(ped6, 1);
							}
							else
							{
								SET_CHAR_RELATIONSHIP_GROUP(ped6, 17);
							}

							set_cord(random);
							SET_CHAR_COORDINATES(ped6, set_X, set_Y, set_Z);// перемещаем игрока
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped6, 59.992, -63.3677, 19.2045, 4, -2, 2.5);
							SETTIMERB( 0 );
							anim = 0;
							animP4 = 0;
							exp4 = 0;
							WAIT(25);
						}
					}

					GET_CHAR_COORDINATES(ped3,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					safe(PedX, PedY, PedZ);
					if ((anim == 1) && (animP1 == 0))
					{
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped3, "searchped_loop", "missbankjob", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						anim = 2;
						animP1 = 1;
						blip_on2 = 1;
						WAIT(25);
					}
					GET_CHAR_COORDINATES(ped4,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					safe(PedX, PedY, PedZ);
					if ((anim == 1) && (animP2 == 0))
					{
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped4, "searchped_loop", "missbankjob", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						anim = 2;
						animP2 = 1;
						blip_on2 = 1;
						WAIT(25);
					}
					GET_CHAR_COORDINATES(ped5,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					safe(PedX, PedY, PedZ);
					if ((anim == 1) && (animP3 == 0))
					{
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "searchped_loop", "missbankjob", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						anim = 2;
						animP3 = 1;
						blip_on2 = 1;
						WAIT(25);
					}
					GET_CHAR_COORDINATES(ped6,  &PedX, &PedY, &PedZ);//вписываем координаты игрока в переменную
					safe(PedX, PedY, PedZ);
					if ((anim == 1) && (animP4 == 0))
					{
						TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "searchped_loop", "missbankjob", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
						anim = 2;
						animP4 = 1;
						blip_on2 = 1;
						WAIT(25);
					}

					if (blip_on2 == 1)
					{
						REMOVE_BLIP(safe_ico);//Удаляем иконку на радаре
						ADD_BLIP_FOR_COORD(59.992, -63.3677, 19.2045, &safe_ico);//создаем иконку на радаре
						CHANGE_BLIP_SPRITE(safe_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(safe_ico, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(safe_ico, 0.6); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(safe_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

						PRINT_STRING_IN_STRING("string", "FIN_B5", 5000, 1);//~g~The Mafia is stealing your money, defend the ~c~safe
						blip_on2 = 2;
						WAIT(25);
					}
					else if ((blip_on2 == 2) && (animP1 == 0) && (animP2 == 0) && (animP3 == 0) && (animP4 == 0))
					{
						REMOVE_BLIP(safe_ico);//Удаляем иконку на радаре
						blip_on2 = 0;
					}

					// сегмент Ленса
					if ((TIMERC() > 60000) && (lance == 99))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "FIN_B1", 5000, 1);//~g~Go and kill ~y~Lance Vance ~g~the backstabber.
						lance = 0;
						WAIT(25);
					}
					else if ((lance == 0) && (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 62.918, -67.055, 19.141, 45.918, -50.555, 27.141, 0 )))
					{
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
						SET_CHAR_COORDINATES(GetPlayerPed(), 54.7593, -49.7201, 19.285);// перемещаем игрока
						SET_CHAR_HEADING(GetPlayerPed(), -25.0);

						SET_CHAR_COORDINATES(ped1, 74.3155, -26.7665, 21.7509);// перемещаем игрока
						SET_CHAR_COORDINATES(ped7, 74.3155, -26.1776, 21.7509);// перемещаем игрока
						SET_CHAR_COORDINATES(ped8, 75.3155, -26.1776, 21.7509);// перемещаем игрока
						SET_CHAR_COORDINATES(ped9, 76.3155, -26.1776, 21.7509);// перемещаем игрока
						SET_CHAR_HEADING(ped1, 80.0);
						SET_CHAR_HEADING(ped7, 80.0);
						SET_CHAR_HEADING(ped8, 80.0);
						SET_CHAR_HEADING(ped9, 80.0);
						WAIT(25);

						TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 68.8139, -26.7665, 21.7509, 4, -2, 1.8);
						TASK_GO_STRAIGHT_TO_COORD(ped7, 47.7729, -27.3967, 21.8199, 4, -2);//Ланс бежит во второй пойнт
						TASK_GO_STRAIGHT_TO_COORD(ped8, 55.7881, -27.3967, 21.8199, 4, -2);//Ланс бежит во второй пойнт
						TASK_GO_STRAIGHT_TO_COORD(ped9, 61.5962, -27.3967, 21.8199, 4, -2);//Ланс бежит во второй пойнт

						//ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 68.8139, -26.766, 21.9868 ); // куда смотрит камера
						SET_CAM_POS			( camera, 53.5861, -50.632, 20.7116 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );
						SetTime(3000);

						TASK_AIM_GUN_AT_CHAR(ped1, GetPlayerPed(), 6000);

						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_NV", "FIN_3", 0, 0);//No one to cover your ass now, eh Tommy?
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();
						TASK_AIM_GUN_AT_CHAR(GetPlayerPed(), ped1, 4000);
						
						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_NV_QQQ1", "FIN_1B", 0, 0);//You're going down, you back stabbing prick!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						//меняем рукурс тут
						POINT_CAM_AT_COORD	( camera, 68.0346, -28.0357, 23.0244 ); // куда смотрит камера
						SET_CAM_POS			( camera, 69.3445, -24.0564, 23.2337 );//расположение камеры

						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R11_NX", "FIN_2B", 0, 0);//Oh you think so!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						// убираем камеру
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
						SET_CHAR_HEALTH(GetPlayerPed(), 200);
						ADD_ARMOUR_TO_CHAR(GetPlayerPed(), 100);

						SET_SENSE_RANGE(ped7, 25.05);
						SET_SENSE_RANGE(ped8, 25.05);
						SET_SENSE_RANGE(ped9, 25.05);
						
						ADD_BLIP_FOR_CHAR(ped1, &ped_ico);
						CHANGE_BLIP_SPRITE(ped_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(ped_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(ped_ico, 0.77999990); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"
						lance = 1;
						hate = 1;
						WAIT(25);
					}

					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
					GET_CHAR_COORDINATES(ped1,  &Ped2X, &Ped2Y, &Ped2Z);//вписываем координаты игрока в переменную
					GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, Ped2X, Ped2Y, Ped2Z, &PlayR);//проверка "игрок на координатах"
					if ((( PlayR < 15.0) && (lance == 1)) || ((IS_BULLET_IN_AREA(Ped2X, Ped2Y, Ped2Z, 2.5, 1)) && (lance == 1)))
					{
						SET_CHAR_RELATIONSHIP_GROUP(ped1, 17);
						SET_SENSE_RANGE(ped1, 0.05);
						SET_CHAR_KEEP_TASK(ped1, TRUE);
						TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 96.7647, -26.3826, 21.3318, 4, -2, 2.5);
						SET_CHAR_KEEP_TASK(ped1, TRUE);
						lance = 2;
					}
					else if (lance == 2)
					{
						if (IS_PED_IN_COMBAT(ped1))
						{
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 96.7647, -26.3826, 21.3318, 4, -2, 2.5);
						}
						GET_DISTANCE_BETWEEN_COORDS_3D( Ped2X, Ped2Y, Ped2Z, 96.7647, -26.3826, 21.3318, &Ped2R);//проверка "игрок на координатах"
						if (Ped2R < 2.0)
						{
							SET_CHAR_HEADING(ped1, 100.0);
							SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
							SET_CHAR_RELATIONSHIP(ped1, 5, 0);
							SET_SENSE_RANGE(ped1, 55.05);
							lance = 3;
						}
					}
					else if ((( PlayR < 15.0) && (lance == 3)) || ((IS_BULLET_IN_AREA(Ped2X, Ped2Y, Ped2Z, 2.5, 1)) && (lance == 3)))
					{
						SET_CHAR_RELATIONSHIP_GROUP(ped1, 17);
						SET_SENSE_RANGE(ped1, 0.05);
						TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 96.7647, -46.0808, 21.3318, 4, -2, 2.5);
						lance = 4;
					}
					else if (lance == 4)
					{
						if (IS_PED_IN_COMBAT(ped1))
						{
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 96.7647, -46.0808, 21.3318, 4, -2, 2.5);
						}
						GET_DISTANCE_BETWEEN_COORDS_3D( Ped2X, Ped2Y, Ped2Z, 96.7647, -46.0808, 21.3318, &Ped2R);//проверка "игрок на координатах"
						if (Ped2R < 2.0)
						{
							SET_CHAR_HEADING(ped1, 0.0);
							SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
							SET_CHAR_RELATIONSHIP(ped1, 5, 0);
							SET_SENSE_RANGE(ped1, 55.05);
							lance = 5;
						}
					}
					else if ((( PlayR < 15.0) && (lance == 5)) || ((IS_BULLET_IN_AREA(Ped2X, Ped2Y, Ped2Z, 2.5, 1)) && (lance == 5)))
					{
						SET_CHAR_RELATIONSHIP_GROUP(ped1, 17);
						SET_SENSE_RANGE(ped1, 0.05);
						TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 115.776, -49.7099, 27.6808, 4, -2, 2.5);
						lance = 6;
					}
					else if (lance == 6)
					{
						if (IS_PED_IN_COMBAT(ped1))
						{
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 115.776, -49.7099, 27.6808, 4, -2, 2.5);
						}
						GET_DISTANCE_BETWEEN_COORDS_3D( Ped2X, Ped2Y, Ped2Z, 115.776, -49.7099, 27.6808, &Ped2R);//проверка "игрок на координатах"
						if (Ped2R < 2.0)
						{
							SET_CHAR_HEADING(ped1, 40.0);
							SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
							SET_CHAR_RELATIONSHIP(ped1, 5, 0);
							SET_SENSE_RANGE(ped1, 55.05);
							lance = 7;
						}
					}
					else if ((( PlayR < 8.0) && (lance == 7)) || ((IS_BULLET_IN_AREA(Ped2X, Ped2Y, Ped2Z, 2.5, 1)) && (lance == 7)))
					{
						SET_CHAR_RELATIONSHIP_GROUP(ped1, 17);
						SET_SENSE_RANGE(ped1, 0.05);
						TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 102.901, -49.5906, 29.5005, 4, -2, 2.5);
						lance = 8;
					}
					else if (lance == 8)
					{
						if (IS_PED_IN_COMBAT(ped1))
						{
							TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped1, 102.901, -49.5906, 29.5005, 4, -2, 2.5);
						}
						GET_DISTANCE_BETWEEN_COORDS_3D( Ped2X, Ped2Y, Ped2Z, 102.901, -49.5906, 29.5005, &Ped2R);//проверка "игрок на координатах"
						if (Ped2R < 2.0)
						{
							SET_CHAR_COORDINATES(ped1, 70.2237, -38.7204, 30.9176);// перемещаем игрока
							SET_CHAR_HEADING(ped1, -90.0);
							SET_CHAR_RELATIONSHIP_GROUP(ped1, 5);
							SET_CHAR_RELATIONSHIP(ped1, 5, 0);
							SET_SENSE_RANGE(ped1, 50.05);
							SET_CHAR_PROOFS(ped1, 0, 1, 0, 1, 1);

							SET_CHAR_COORDINATES(ped10, 75.3179, -52.3612, 30.9176);// перемещаем игрока
							SET_CHAR_COORDINATES(ped11, 70.6166, -47.2464, 30.9176);// перемещаем игрока
							SET_CHAR_COORDINATES(ped12, 70.2676, -43.2274, 30.9176);// перемещаем игрока
							SET_CHAR_HEADING(ped10, -90.0);
							SET_CHAR_HEADING(ped11, -90.0);
							SET_CHAR_HEADING(ped12, -90.0);
							WAIT(25);

							DELETE_CHAR(&ped7);//удаляем модель педа
							DELETE_CHAR(&ped8);//удаляем модель педа
							DELETE_CHAR(&ped9);//удаляем модель педа
							//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет
							//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//выгружаем модель педа(в последствии пед изчезнет
							//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped9);//выгружаем модель педа(в последствии пед изчезнет
							WAIT(25);

							CREATE_CHAR (26, PedM3, 70.8567, -40.2056, 30.9176, &ped7, TRUE);// 
							CREATE_CHAR (26, PedM4, 70.7708, -37.3693, 30.9176, &ped8, TRUE);// 
							CREATE_CHAR (26, PedM3, 72.9255, -33.2938, 30.9176, &ped9, TRUE);// 
							SET_CHAR_HEADING(ped7, -90.0);
							SET_CHAR_HEADING(ped8, -90.0);
							SET_CHAR_HEADING(ped9, -90.0);

							UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_12);
							UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_12);
							UpdateWeaponOfPed(ped9, WEAPON_EPISODIC_12);

							SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_12, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_12, TRUE);
							SET_CURRENT_CHAR_WEAPON(ped9, WEAPON_EPISODIC_12, TRUE);

							SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
							SET_CHAR_RELATIONSHIP_GROUP(ped9, 5);

							SET_CHAR_RELATIONSHIP(ped7, 5, 0);
							SET_CHAR_RELATIONSHIP(ped8, 5, 0);
							SET_CHAR_RELATIONSHIP(ped9, 5, 0);
							SET_SENSE_RANGE(ped7, 25.0);
							SET_SENSE_RANGE(ped8, 25.0);
							SET_SENSE_RANGE(ped9, 25.0);
							SET_CHAR_WILL_USE_COVER(ped7, 1);
							SET_CHAR_WILL_USE_COVER(ped8, 1);
							SET_CHAR_WILL_USE_COVER(ped9, 1);
							lance = 9;
							WAIT(25);
						}
					}

					if ((ped1_hp < 100) && (Sonny == 0))
					{
						EXPLODE_CHAR_HEAD(ped1);
						REMOVE_BLIP(ped_ico);//Удаляем иконку на радаре
						hate = 5;

						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R12_A_BD", "FIN_5", 0, 0);// = You picked the wrong side, Lance...
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "DEFSAFE", 5000, 1);//~g~Get back to the safe and defend it.

						CREATE_PICKUP_ROTATE(w_pumpshot, 3, 24, 56.2016, -60.2295, 20.1242, -80.0, -110.0, 0.0, &sweap_2);// даём винтовку
						ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(sweap_2, "mansion_int");
						if (playHP < 150)
						{
							CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 105.462, -42.917, 6.995, 0.0, 0.0, 90.0, &aid_2);//Аптека
							ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(aid_2, "mansion_int");

							ADD_BLIP_FOR_PICKUP(aid_2, &heal_ico);
							CHANGE_BLIP_SPRITE(heal_ico, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
							CHANGE_BLIP_COLOUR(heal_ico, 0);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
							CHANGE_BLIP_SCALE(heal_ico, 0.45); // масштаб иконки на радаре
							CHANGE_BLIP_NAME_FROM_TEXT_FILE(heal_ico, "BLIP_19");//иконка на радаре называние в истории карты "витрина"

							PRINT_STRING_IN_STRING("string", "FIN_B4", 5000, 1);//~g~You are close to death, get some ~w~health ~g~from downstairs.
						}
						SETTIMERC( 0 );
						Sonny = 1;
						hate = 99;
						WAIT(25);
					}
					if ((ped2_hp < 100) && (Sonny == 2))
					{
						EXPLODE_CHAR_HEAD(ped2);
						WAIT(25);

						//SET_CHAR_COORDINATES(ped2, 288.569, -783.023, 4.63619);// перемещаем игрока
						//SET_CHAR_COORDINATES(ped3, 296.021, -778.305, 4.63619);// перемещаем игрока
						//SET_CHAR_COORDINATES(ped4, 294.021, -778.305, 4.63619);// перемещаем игрока
						//SET_CHAR_COORDINATES(ped5, 292.021, -778.305, 4.63619);// перемещаем игрока
						//SET_CHAR_COORDINATES(ped6, 290.021, -778.305, 4.63619);// перемещаем игрока
						//SET_CHAR_COORDINATES(ped7, 288.021, -778.305, 4.63619);// перемещаем игрока
						//SET_CHAR_COORDINATES(ped8, 286.021, -778.305, 4.63619);// перемещаем игрока
						CLEAR_AREA(54.531, -27.615, 14.515, 50.0, 1);//очещаем зону загрузки

						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
						GET_TIME_OF_DAY(&hour, &minute);
						GET_CURRENT_WEATHER(&weather);
						Sonny = 3;

						//------------ катсцена ----------------
						while (!(PRELOAD_STREAM("CUTSCENES_FINALE")));
						PRELOAD_STREAM("CUTSCENES_FINALE");  // имя берется из sounds.dat15, также можно проиграть музыку из радио

						LOAD_ADDITIONAL_TEXT( "FINALE", 6 ); // загружаем субтитры из *.GTX
						START_CUTSCENE_NOW("finale");
						while (!HAS_CUTSCENE_LOADED())
						{
							WAIT(0);
						}
						DO_SCREEN_FADE_IN(0);

						PLAY_STREAM_FRONTEND();
						SETTIMERC( 0 );
						sound = 1;

						while (!HAS_CUTSCENE_FINISHED())
						{
							WAIT(0);
						}

						if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
						{
							DO_SCREEN_FADE_IN(0);
						}
						break;
					}

					//диалоги погони
					if ((hate == 1) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 99.273, -46.691, 21.224, 73.353, -24.032, 26.712, 0 )))
					{
						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R12_AB", "FIN_1A", 0, 0);//Come here you double-crossing piece of shit!
						START_SCRIPT_CONVERSATION(1, 1);
						//SetSpeech();
						hate = 2;
					}
					else if ((hate == 2) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 99.273, -29.518, 11.125, 93.932, -24.032, 28.254, 0 )))
					{
						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R12_A_BA", "FIN_4", 0, 0);//You're history, Tommy, history
						START_SCRIPT_CONVERSATION(1, 1);
						//SetSpeech();
						hate = 3;
					}
					else if ((hate == 3) && (lance == 9) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 92.861, -47.383, 30.466, 88.801, -33.703, 34.777, 0 )))
					{
						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
						ADD_LINE_TO_CONVERSATION(0, "R12_A_BB", "FIN_1C", 0, 0);//This is the last dance for lance vance!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();
						hate = 4;
					}
					else if ((hate == 4) && (!IS_CHAR_DEAD(ped1)))
					{
						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped1, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R12_A_BC", "FIN_2C", 0, 0);//I said I had enough of that at school!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();
						hate = 5;
					}

					// сегмент Сонни
					if ((TIMERC() > 60000) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 62.918, -67.055, 19.141, 45.918, -50.555, 27.141, 0 )) && (Sonny == 1))
					{
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
						SET_CHAR_COORDINATES(GetPlayerPed(), 54.6753, -46.7048, 19.293);// перемещаем игрока
						SET_CHAR_HEADING(GetPlayerPed(), 0.0);

						SET_CHAR_COORDINATES(ped3, 4.6753, -460.7048, 1.293);// перемещаем игрока
						SET_CHAR_COORDINATES(ped4, 4.6753, -465.7048, 1.293);// перемещаем игрока
						SET_CHAR_COORDINATES(ped5, 4.6753, -470.7048, 1.293);// перемещаем игрока
						SET_CHAR_COORDINATES(ped6, 4.6753, -475.7048, 1.293);// перемещаем игрока
						EXPLODE_CHAR_HEAD(ped3);
						EXPLODE_CHAR_HEAD(ped4);
						EXPLODE_CHAR_HEAD(ped5);
						EXPLODE_CHAR_HEAD(ped6);

						SET_CHAR_COORDINATES(ped2, 54.5139, -23.2074, 13.544);// перемещаем
						SET_CHAR_HEADING(ped2, 180.0);
						ATTACH_OBJECT_TO_PED( kaska_1, ped2, 1205, 0.03, 0.0, 0.0, 0.0, 0.0, 0.0, 0 );
						SET_CHAR_PROOFS(ped2, 0, 1, 0, 1, 1);

						DELETE_CHAR(&ped7);//удаляем модель педа
						DELETE_CHAR(&ped8);//удаляем модель педа
						//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет
						//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//выгружаем модель педа(в последствии пед изчезнет
						WAIT(25);

						CREATE_CHAR (26, PedM3, 288.021, -778.305, 4.63619, &ped7, TRUE);//
						CREATE_CHAR (26, PedM4, 286.021, -778.305, 4.63619, &ped8, TRUE);//

						UpdateWeaponOfPed(ped7, WEAPON_EPISODIC_12);
						UpdateWeaponOfPed(ped8, WEAPON_EPISODIC_12);
						SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_EPISODIC_12, TRUE);
						SET_CURRENT_CHAR_WEAPON(ped8, WEAPON_EPISODIC_12, TRUE);
						SET_CHAR_COORDINATES(ped7, 52.6993, -24.0832, 13.544);// перемещаем игрока
						SET_CHAR_COORDINATES(ped8, 56.0334, -24.0832, 13.544);// перемещаем игрока
						SET_CHAR_HEADING(ped7, 145.0);
						SET_CHAR_HEADING(ped8, 145.0);

						//ставим камеру
						CREATE_CAM( 14, &camera );
						POINT_CAM_AT_COORD	( camera, 54.605, -24.7195, 14.8736 ); // куда смотрит камера
						SET_CAM_POS			( camera, 53.267, -46.5512, 21.6791 );//расположение камеры
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_CAM_FOV( camera, 45.0 );
						SET_WIDESCREEN_BORDERS( 1 );
						SetTime(2000);
						
						TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(GetPlayerPed(), 54.6753, -43.5971, 19.293, 2, -2, 1.8);
						TASK_GO_STRAIGHT_TO_COORD(ped7, 50.7719, -30.4683, 13.5441, 3, -2);// бежит во второй пойнт
						TASK_GO_STRAIGHT_TO_COORD(ped8, 57.1227, -28.3331, 13.5441, 3, -2);// бежит во второй пойнт
						SetTime(2000);

						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_NY", "FIN_11A", 0, 0);//You took fifteen years from me Sonny...
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						TASK_AIM_GUN_AT_CHAR(ped7, GetPlayerPed(), 6000);
						TASK_AIM_GUN_AT_CHAR(GetPlayerPed(), ped2, 4000);

						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_NY_QQQ1", "FIN_11B", 0, 0);//And now I'm gonna make you pay!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						//меняем рукурс тут
						POINT_CAM_AT_COORD	( camera, 54.813, -24.7767, 14.3612 ); // куда смотрит камера
						SET_CAM_POS			( camera, 50.226, -28.1531, 15.4656 );//расположение камеры

						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_NZ", "FIN_12A", 0, 0);//You still don't get it do you!
						START_SCRIPT_CONVERSATION(1, 1);
						TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(ped2, 54.531, -27.615, 14.515, 2, -2, 1.8);
						SetSpeech();

						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_OA", "FIN_12B", 0, 0);//I OWN you, Tommy.
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						//меняем рукурс тут
						POINT_CAM_AT_COORD	( camera, 61.5256, -42.986, 19.681 ); // куда смотрит камера
						SET_CAM_POS			( camera, 51.9815, -23.929, 14.557 );//расположение камеры

						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_XYA", "FIN_12C", 0, 0);//Those fifteen years were mine to spend!
						START_SCRIPT_CONVERSATION(1, 1);
						SetSpeech();

						// аудио тут
						NEW_SCRIPTED_CONVERSATION();
						ADD_NEW_CONVERSATION_SPEAKER(0, ped2, "ROMAN");
						ADD_LINE_TO_CONVERSATION(0, "R11_XYB", "FIN_13", 0, 0);//Get him boys, he never understood a thing.
						START_SCRIPT_CONVERSATION(1, 1);

						// убираем камеру
						SET_CAM_BEHIND_PED( GetPlayerPed() );
						ACTIVATE_SCRIPTED_CAMS( 0, 0 );
						END_CAM_COMMANDS( &camera );
						SET_WIDESCREEN_BORDERS( 0 );
						SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
						SET_CHAR_HEALTH(GetPlayerPed(), 200);
						ADD_ARMOUR_TO_CHAR(GetPlayerPed(), 100);

						SET_SENSE_RANGE(ped7, 25.05);
						SET_SENSE_RANGE(ped8, 25.05);
						SET_SENSE_RANGE(ped9, 25.05);

						SET_CHAR_RELATIONSHIP_GROUP(ped7, 5);
						SET_CHAR_RELATIONSHIP_GROUP(ped8, 5);
						SET_CHAR_RELATIONSHIP(ped7, 5, 0);
						SET_CHAR_RELATIONSHIP(ped8, 5, 0);
						SET_SENSE_RANGE(ped2, 25.0);
						SET_SENSE_RANGE(ped7, 25.0);
						SET_SENSE_RANGE(ped8, 25.0);
						SET_CHAR_WILL_USE_COVER(ped7, 1);
						SET_CHAR_WILL_USE_COVER(ped8, 1);

						TASK_COMBAT(ped2, GetPlayerPed());// агрим
						TASK_COMBAT(ped7, GetPlayerPed());// агрим
						TASK_COMBAT(ped8, GetPlayerPed());// агрим

						ADD_BLIP_FOR_CHAR(ped2, &ped_ico);
						CHANGE_BLIP_SPRITE(ped_ico, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
						CHANGE_BLIP_COLOUR(ped_ico, 19);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
						CHANGE_BLIP_SCALE(ped_ico, 0.77999990); // масштаб иконки на радаре
						CHANGE_BLIP_NAME_FROM_TEXT_FILE(ped_ico, "MO_TARGET");//иконка на радаре называние в истории карты "витрина"

						SetSpeech();
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "FIN_B2", 5000, 1);//~g~Kill ~p~Sonny ~g~and finish this once and for all.
						Sonny = 2;
						WAIT(25);
					}

					// провал миссии тут
					if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован, если лодка унечтожена
					{
						skip = 1;
						break;
					}
					else if (money_ped < 1)
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "FIN_B7", 5000, 1);//~r~The mafia has stolen all your money.
						skip = 1;
						break;
					}
					else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 127.627, -88.09, -3.425, -22.373, 11.91, 46.575, 0 )) 
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NEFIN_L1", 5000, 1);//~r~You left the mansion, now Sonny is the boss in Vice City.
						skip = 1;
						break;
					}
					if ((IS_CHAR_IN_AREA_3D( ped3, 61.721, -64.944, 19.582, 58.721, -61.944, 24.582, 0 )) && (IS_CHAR_ON_FIRE(ped3)))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NEFIN_S1", 5000, 1);//NEFIN_S1 = ~r~You were supposed to protect the safe, not destroy it!
						EXPLODE_CHAR_HEAD(ped3);
						skip = 1;
						break;
					}
					else if ((IS_CHAR_IN_AREA_3D( ped4, 61.721, -64.944, 19.582, 58.721, -61.944, 24.582, 0 )) && (IS_CHAR_ON_FIRE(ped4)))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NEFIN_S1", 5000, 1);//NEFIN_S1 = ~r~You were supposed to protect the safe, not destroy it!
						EXPLODE_CHAR_HEAD(ped4);
						skip = 1;
						break;
					}
					else if ((IS_CHAR_IN_AREA_3D( ped5, 61.721, -64.944, 19.582, 58.721, -61.944, 24.582, 0 )) && (IS_CHAR_ON_FIRE(ped5)))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NEFIN_S1", 5000, 1);//NEFIN_S1 = ~r~You were supposed to protect the safe, not destroy it!
						EXPLODE_CHAR_HEAD(ped5);
						skip = 1;
						break;
					}
					else if ((IS_CHAR_IN_AREA_3D( ped6, 61.721, -64.944, 19.582, 58.721, -61.944, 24.582, 0 )) && (IS_CHAR_ON_FIRE(ped6)))
					{
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NEFIN_S1", 5000, 1);//NEFIN_S1 = ~r~You were supposed to protect the safe, not destroy it!
						EXPLODE_CHAR_HEAD(ped6);
						skip = 1;
						break;
					}
				}

				// финальные титры тут
				if (skip == 0)
				{
					if (TIMERC() < 104000)
					{
						STOP_STREAM();
						while (!(PRELOAD_STREAM_WITH_START_OFFSET("CUTSCENES_FINALE", 105000)));
						PRELOAD_STREAM_WITH_START_OFFSET("CUTSCENES_FINALE", 105000);  // имя берется из sounds.dat15, также можно проиграть музыку из радио
						PLAY_STREAM_FRONTEND();
					}

					SETTIMERA( 0 );
					SETTIMERB( 0 );
					SETTIMERC( 0 );

					alfa = 255;
					move1 = 1.5;
					move2 = 2.5;
					fon_black = 1;
					set_page = 2;
					set_cam = 1;
					skip = 2;

					//ставим камеру
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 748.8044, -72.4032, 5.1004 ); // куда смотрит камера
					SET_CAM_POS			( camera, 748.4413, -73.3295, 4.9994 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// Размораживаем игрока
					FORCE_WEATHER_NOW(WEATHER_SUNNY);
					FORWARD_TO_TIME_OF_DAY(18, 0);//устанавливаем время
					SET_CHAR_COORDINATES(GetPlayerPed(), 775.07, -44.41, 5.08);// перемещаем игрока
					MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 1 );

					while (TRUE)
					{
						WAIT(0);
						DISABLE_PAUSE_MENU(1);
						DRAW_SPRITE( 0, 0.5, 0.5, 1.0, 1.0, 0.0, 0, 0, 0, alfa );// чёрный фон

						// сами титры тут
						DRAW_SPRITE( page_1, 0.5, move1, 0.5, 1.0, 0.0, 255, 255, 255, 255 );// лист 1
						DRAW_SPRITE( page_2, 0.5, move2, 0.5, 1.0, 0.0, 255, 255, 255, 255 );// лист 2
						
						//Затемнение/осветление
						if (TIMERB() > 23000)
						{
							if ((fon_black == 1) && (set_cam < 8))
							{
								fon_black = 0; // осветляем экран
								// камеры тут
								if (set_cam == 1)
								{
									set_cam = 2;
								}
								else if (set_cam == 2)
								{
									POINT_CAM_AT_COORD	( camera, 375.8786, -1045.4846, 5.765 ); // куда смотрит камера
									SET_CAM_POS			( camera, 375.9911, -1046.4728, 5.6604 );//расположение камеры
									FORWARD_TO_TIME_OF_DAY(14, 0);//устанавливаем время
									SET_CHAR_COORDINATES(GetPlayerPed(), 358.05, -992.14, 5.42);// перемещаем игрока
									set_cam = 3;
								}
								else if (set_cam == 3)
								{
									POINT_CAM_AT_COORD	( camera, 402.5186, -409.2845, 5.4088 ); // куда смотрит камера
									SET_CAM_POS			( camera, 401.5523, -409.5128, 5.2897 );//расположение камеры
									FORWARD_TO_TIME_OF_DAY(15, 0);//устанавливаем время
									SET_CHAR_COORDINATES(GetPlayerPed(), 430.59, -405.92, 5.61);// перемещаем игрока
									set_cam = 4;
								}
								else if (set_cam == 4)
								{
									POINT_CAM_AT_COORD	( camera, 959.1959, -568.6124, 6.4088 ); // куда смотрит камера
									SET_CAM_POS			( camera, 960.1948, -568.6581, 6.3979 );//расположение камеры
									FORWARD_TO_TIME_OF_DAY(12, 0);//устанавливаем время
									SET_CHAR_COORDINATES(GetPlayerPed(), 965.1948, -568.6581, 6.04);// перемещаем игрока
									set_cam = 5;
								}
								else if (set_cam == 5)
								{
									POINT_CAM_AT_COORD	( camera, 762.5483, -589.4576, 23.4027 ); // куда смотрит камера
									SET_CAM_POS			( camera, 762.8244, -590.4187, 23.418 );//расположение камеры
									FORWARD_TO_TIME_OF_DAY(2, 0);//устанавливаем время
									SET_CHAR_COORDINATES(GetPlayerPed(), 702.43, -519.15, 6.05);// перемещаем игрока
									set_cam = 6;
								}
								else if (set_cam == 6)
								{
									POINT_CAM_AT_COORD	( camera, 853.3214, 354.2665, 6.193 ); // куда смотрит камера
									SET_CAM_POS			( camera, 853.3749, 353.2681, 6.2077 );//расположение камеры
									FORWARD_TO_TIME_OF_DAY(11, 0);//устанавливаем время
									SET_CHAR_COORDINATES(GetPlayerPed(), 802.46, 437.45, 6.71);// перемещаем игрока
									set_cam = 7;
								}
								else if (set_cam == 7)
								{
									POINT_CAM_AT_COORD	( camera, 36.4549, 556.4814, 41.7505 ); // куда смотрит камера
									SET_CAM_POS			( camera, 35.6175, 555.9746, 41.9553 );//расположение камеры
									FORWARD_TO_TIME_OF_DAY(5, 45);//устанавливаем время
									SET_CHAR_COORDINATES(GetPlayerPed(), 105.62, 575.12, 2.61);// перемещаем игрока
									set_cam = 99;
								}
							}
							else if (fon_black == 0)
							{
								fon_black = 1; // затемняем экран
							}
							SETTIMERB( 0 );
						}

						// тики
						if (TIMERA() > 12) 
						{
							if ((fon_black == 1) && (alfa < 255)) // затемняем экран
							{
								alfa +=1;
							}
							else if ((fon_black == 0) && (alfa > 1)) // осветляем экран
							{
								alfa -=1;
							}
							// движение титров тут
							if (move1 < -0.5)
							{
								move1 = 1.5;
								RELEASE_TEXTURE( page_1 );
								if (set_page == 2)
								{
									page_1 = GET_TEXTURE( textur1, "page_3" );
									set_page = 3;
								}
								else if (set_page == 4)
								{
									page_1 = GET_TEXTURE( textur1, "page_5" );
									set_page = 5;
								}
								else if (set_page == 6)
								{
									page_1 = GET_TEXTURE( textur1, "page_7" );
									set_page = 7;
								}
								else if (set_page == 8)
								{
									page_1 = GET_TEXTURE( textur1, "page_9" );
									set_page = 9;
								}
								else if (set_page == 10)
								{
									page_1 = GET_TEXTURE( textur1, "page_11" );
									set_page = 11;
								}
								else if (set_page == 12)
								{
									page_1 = GET_TEXTURE( textur1, "page_13" );
									set_page = 13;
								}
								else if (set_page == 14)
								{
									page_1 = GET_TEXTURE( textur1, "page_15" );
									set_page = 15;
								}
								else if (set_page == 16)
								{
									page_1 = GET_TEXTURE( textur1, "page_17" );
									set_page = 17;
								}
								else if (set_page == 18)
								{
									page_1 = GET_TEXTURE( textur1, "page_19" );
									set_page = 19;
								}
								else if (set_page == 20)
								{
									page_1 = GET_TEXTURE( textur1, "page_21" );
									set_page = 21;
								}
								else if (set_page == 22)
								{
									page_1 = GET_TEXTURE( textur1, "page_21" );
									move1 = 2.5;
								}
							}
							if (move2 < -0.5)
							{
								move2 = 1.5;
								RELEASE_TEXTURE( page_2 );
								if (set_page == 3)
								{
									page_2 = GET_TEXTURE( textur1, "page_4" );
									set_page = 4;
								}
								else if (set_page == 5)
								{
									page_2 = GET_TEXTURE( textur1, "page_6" );
									set_page = 6;
								}
								else if (set_page == 7)
								{
									page_2 = GET_TEXTURE( textur1, "page_8" );
									set_page = 8;
								}
								else if (set_page == 9)
								{
									page_2 = GET_TEXTURE( textur1, "page_10" );
									set_page = 10;
								}
								else if (set_page == 11)
								{
									page_2 = GET_TEXTURE( textur1, "page_12" );
									set_page = 12;
								}
								else if (set_page == 13)
								{
									page_2 = GET_TEXTURE( textur1, "page_14" );
									set_page = 14;
								}
								else if (set_page == 15)
								{
									page_2 = GET_TEXTURE( textur1, "page_16" );
									set_page = 16;
								}
								else if (set_page == 17)
								{
									page_2 = GET_TEXTURE( textur1, "page_18" );
									set_page = 18;
								}
								else if (set_page == 19)
								{
									page_2 = GET_TEXTURE( textur1, "page_20" );
									set_page = 20;
								}
								else if (set_page == 21)
								{
									page_2 = GET_TEXTURE( textur1, "page_22" );
									set_page = 22;
								}
							}
							move1 -= 0.001;
							move2 -= 0.001;
							SETTIMERA( 0 );
						}

						//DISPLAY_TEXT_WITH_NUMBER(0.9203125, 0.65787074, "CP_TIME_NOZERO", TIMERC());// 
						if (TIMERC() > 346000)
						{
							// убираем камеру
							SET_CAM_BEHIND_PED( GetPlayerPed() );
							ACTIVATE_SCRIPTED_CAMS( 0, 0 );
							END_CAM_COMMANDS( &camera );
							SET_WIDESCREEN_BORDERS( 0 );
							FORCE_WEATHER_NOW( weather );//устанавливаем погода
							RELEASE_WEATHER();
							FORWARD_TO_TIME_OF_DAY(hour, minute);//устанавливаем время

							SET_CHAR_COORDINATES(GetPlayerPed(), 54.5139, -20.4137, 13.5738);// перемещаем игрока
							SET_CHAR_HEADING(GetPlayerPed(), 0.0);
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
							MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 0 );
							break;
						}
					}
				}

				// чистим скрипт
				WAIT(100);
				SET_MAX_WANTED_LEVEL(6);
				DISABLE_PAUSE_MENU(0);

				RELEASE_TEXTURE( page_1 );
				RELEASE_TEXTURE( page_2 );
				REMOVE_TXD( textur1 );

				REMOVE_BLIP(safe_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(ped_ico);//Удаляем иконку на радаре
				REMOVE_BLIP(heal_ico);//Удаляем иконку на радаре

				REMOVE_PICKUP(sweap_1);// выгружаем оружие
				REMOVE_PICKUP(sweap_2);// выгружаем оружие
				REMOVE_PICKUP(aid_1);// выгружаем оружие
				REMOVE_PICKUP(aid_2);// выгружаем оружие

				if (sound == 1)
				{
					STOP_STREAM();
				}

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(barrel);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(barre2);//выгружаем модель
				MARK_MODEL_AS_NO_LONGER_NEEDED(kaska);//выгружаем модель

				DELETE_CHAR(&ped1);//удаляем модель педа
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

				//MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
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

				// выгружвем машину
				MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
				MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)

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
				DELETE_OBJECT(&barrel_11);
				DELETE_OBJECT(&barrel_12);
				DELETE_OBJECT(&kaska_1);

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
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_11);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&barrel_12);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&kaska_1);

				if (skip == 1)
				{
					INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
					MissionFailed();
				}
				else if (skip == 2)
				{
					PRINT_HELP("NECLOTH11"); //'This is business' & 'An old friend outfit' outfit delivered to Vercetti Mansion.
					SETTIMERA(0); //сбрасываем таймер 
					REGISTER_MISSION_PASSED( "S_FIN_1" );//Keep your Friends Close...
					INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
					play_mission_complete_tune();
					MissionPassed(30000, "missionpassed", "CASH");
					ADD_SCORE( GetPlayerIndex(), +30000 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 30000);
					G_COUNT = 7;
					autosave = 1;
				}
				blip_on = 0;
				G_ONMISSION = 0;
			}
		}
		else if (((G_ONMISSION == 0) && (G_COUNT == 3)) || ((G_ONMISSION == 0) && (G_COUNT >= 7)))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-629.403, 255.797, 5.95213, &count_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(count_ico, BLIP_DEAL);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(count_ico, 1.1); // масштаб иконки на радаре
				SET_BLIP_AS_SHORT_RANGE(count_ico, 1); // иконка пропадает если не в зоне радардиска
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(count_ico, "LG_20");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(count_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}

		if ((G_COUNT == 3) || (G_COUNT >= 7))
		{
			if ( TIMERC() > 360)// время фарма
			{
				if (income < 8000)// максимальный доход
				{
					income +=1;
				}
				SETTIMERC(0); //сбрасываем таймер 
			}

			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -642.463, 252.566, 5.686, -650.009, 260.059, 10.851, 0 ))
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
				if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -646.323, 256.013, -649.323, 259.013, 0))
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
	typography();
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
