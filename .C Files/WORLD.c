/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"

#define SPAWN_STATE_DISABLED				0		/*rebusx*/
#define SPAWN_STATE_DISABLED_FROM_START		1
#define SPAWN_STATE_ENABLED					2




float swap, swap2, sebal, angle, spawn_car, spawnT, spawnL, spawnS1, spawnS2, spawnS3, spawnS4, spawnS5, spawnH, spawnF, spawnM, spawn_blood, spawn_inf, cop_on, run_on, arm_on, heal_on;
//float fire_on;
float PlayX, PlayY, PlayZ, PlayR, PedX, PedY, PedZ, PedR, in_taxi, in_voodoo;
float x, y, set_money, siren, check_X, check_Y, check_Z, James, Pizza, Tools, Ammunition, add_check, trigger, open_D_door, open_D_door2, open_pron, open_star1, open_star2;

uint time_fireproof_check = 0;	/*rebusx*/


void i_need_tools(void)
{
	Cam camera;
	Cam camera2;
	Cam camera3;
	int money_ped, buy_1, buy_2, buy_3, buy_4, buy_5, all_cam;
	int add_ammo1, add_ammo2, add_ammo3, add_ammo4, add_ammo5;
	float set_cam, cam_on, cam_Z, help;
	float cam1_X1, cam1_Y1, cam1_X2, cam1_Y2;
	float cam2_X1, cam2_Y1, cam2_X2, cam2_Y2;
	float cam3_X1, cam3_Y1, cam3_X2, cam3_Y2;
	float cam4_X1, cam4_Y1, cam4_X2, cam4_Y2;
	float cam5_X1, cam5_Y1, cam5_X2, cam5_Y2;
	float cam6_X1, cam6_Y1, cam6_X2, cam6_Y2;
	Weapon set_weap_1, set_weap_2, set_weap_3, set_weap_4, set_weap_5, set_weap_6;

	cam_on = 0;
	set_cam = 1;
	help = 0;
	all_cam = 4;
	add_ammo1 = 1;
	add_ammo2 = 1;
	add_ammo3 = 1;
	add_ammo4 = 1;
	add_ammo5 = 1;

	if (Tools == 1)
	{
		cam1_X1 = -529.389;
		cam1_Y1 = -156.113;
		cam1_X2 = -528.158;
		cam1_Y2 = -155.962;

		cam2_X1 = -529.168;
		cam2_Y1 = -157.721;
		cam2_X2 = -527.937;
		cam2_Y2 = -157.571;

		cam3_X1 = -528.965;
		cam3_Y1 = -159.338;
		cam3_X2 = -527.734;
		cam3_Y2 = -159.188;

		cam4_X1 = -528.779;
		cam4_Y1 = -160.764;
		cam4_X2 = -527.548;
		cam4_Y2 = -160.614;

		cam_Z = 8.45652;

		buy_1 = 20;
		buy_2 = 50;
		buy_3 = 90;
		buy_4 = 500;
		set_weap_1 = WEAPON_EPISODIC_23;//молоток - w_hammer
		set_weap_2 = WEAPON_EPISODIC_8;//тисак - w_cleaver
		set_weap_3 = WEAPON_BASEBALLBAT;
		set_weap_4 = WEAPON_EPISODIC_1;//бензопила - w_chnsaw
	}
	else if (Tools == 2)
	{
		cam1_X1 = 634.954;
		cam1_Y1 = 62.6022;
		cam1_X2 = 634.977;
		cam1_Y2 = 63.8419;

		cam2_X1 = 636.577;
		cam2_Y1 = 62.5971;
		cam2_X2 = 636.599;
		cam2_Y2 = 63.8368;

		cam3_X1 = 638.231;
		cam3_Y1 = 62.5733;
		cam3_X2 = 638.253;
		cam3_Y2 = 63.8129;

		cam4_X1 = 639.836;
		cam4_Y1 = 62.5788;
		cam4_X2 = 639.859;
		cam4_Y2 = 63.8185;

		cam_Z = 9.13504;

		buy_1 = 20;
		buy_2 = 50;
		buy_3 = 90;
		buy_4 = 90;

		set_weap_1 = WEAPON_EPISODIC_23;//молоток - w_hammer
		set_weap_2 = WEAPON_EPISODIC_8;//тисак - w_cleaver
		set_weap_3 = WEAPON_KNIFE;
		set_weap_4 = WEAPON_EPISODIC_4;
	}
	else if (Tools == 3)
	{
		cam1_X1 = 799.603;
		cam1_Y1 = 1606.82;
		cam1_X2 = 799.581;
		cam1_Y2 = 1605.58;

		cam2_X1 = 797.981;
		cam2_Y1 = 1606.82;
		cam2_X2 = 797.958;
		cam2_Y2 = 1605.58;

		cam3_X1 = 796.326;
		cam3_Y1 = 1606.85;
		cam3_X2 = 796.304;
		cam3_Y2 = 1605.61;

		cam4_X1 = 794.721;
		cam4_Y1 = 1606.84;
		cam4_X2 = 794.699;
		cam4_Y2 = 1605.61;

		cam_Z = 15.9605;

		buy_1 = 20;
		buy_2 = 50;
		buy_3 = 90;
		buy_4 = 90;

		set_weap_1 = WEAPON_EPISODIC_23;//молоток - w_hammer
		set_weap_2 = WEAPON_EPISODIC_3;//тисак - w_cleaver
		set_weap_3 = WEAPON_BASEBALLBAT;
		set_weap_4 = WEAPON_KNIFE;
	}
	else if (Ammunition == 1)
	{
		all_cam = 5;
		cam1_X1 = 371.851;
		cam1_Y1 = -954.272;
		cam1_X2 = 371.741;
		cam1_Y2 = -955.505;

		cam2_X1 = 370.753;
		cam2_Y1 = -954.164;
		cam2_X2 = 370.623;
		cam2_Y2 = -955.397;

		cam3_X1 = 369.088;
		cam3_Y1 = -954.016;
		cam3_X2 = 368.991;
		cam3_Y2 = -955.249;

		cam4_X1 = 367.619;
		cam4_Y1 = -953.896;
		cam4_X2 = 367.503;
		cam4_Y2 = -955.129;

		cam5_X1 = 366.123;
		cam5_Y1 = -953.742;
		cam5_X2 = 366.002;
		cam5_Y2 = -954.975;

		cam_Z = 7.50674;

		buy_1 = 100;
		buy_2 = 300;
		buy_3 = 500;
		buy_4 = 1000;
		buy_5 = 200;

		add_ammo1 = 17;
		add_ammo2 = 50;
		add_ammo3 = 8;
		add_ammo4 = 30;

		set_weap_1 = WEAPON_PISTOL;
		set_weap_2 = WEAPON_MICRO_UZI;
		set_weap_3 = WEAPON_SHOTGUN;
		set_weap_4 = WEAPON_AK47;
		set_weap_5 = 0;
	}
	else if (Ammunition == 2)
	{
		all_cam = 6;
		cam1_X1 = -249.533;
		cam1_Y1 = 1734.16;
		cam1_X2 = -250.773;
		cam1_Y2 = 1734.16;

		cam2_X1 = -249.551;
		cam2_Y1 = 1735.53;
		cam2_X2 = -250.789;
		cam2_Y2 = 1735.54;

		cam3_X1 = -249.546;
		cam3_Y1 = 1736.82;
		cam3_X2 = -250.785;
		cam3_Y2 = 1736.83;

		cam4_X1 = -249.535;
		cam4_Y1 = 1738.21;
		cam4_X2 = -250.774;
		cam4_Y2 = 1738.21;

		cam5_X1 = -249.563;
		cam5_Y1 = 1739.54;
		cam5_X2 = -250.803;
		cam5_Y2 = 1739.55;

		cam6_X1 = -249.553;
		cam6_Y1 = 1740.77;
		cam6_X2 = -250.793;
		cam6_Y2 = 1740.76;

		cam_Z = 8.10639;

		buy_1 = 2000;
		buy_2 = 3000;
		buy_3 = 4000;
		buy_4 = 5000;
		buy_5 = 6000;

		add_ammo1 = 6;
		add_ammo2 = 30;
		add_ammo3 = 10;
		add_ammo4 = 30;
		add_ammo5 = 10;

		set_weap_1 = WEAPON_DEAGLE;
		set_weap_2 = WEAPON_MP5;
		set_weap_3 = WEAPON_BARETTA;
		set_weap_4 = WEAPON_M4;
		set_weap_5 = WEAPON_SNIPERRIFLE;
	}
	else if (Ammunition == 3)
	{
		all_cam = 6;
		cam1_X1 = 800.896;
		cam1_Y1 = 1583.57;
		cam1_X2 = 800.894;
		cam1_Y2 = 1582.33;

		cam2_X1 = 800.016;
		cam2_Y1 = 1583.55;
		cam2_X2 = 800.008;
		cam2_Y2 = 1582.31;

		cam3_X1 = 798.606;
		cam3_Y1 = 1583.57;
		cam3_X2 = 798.603;
		cam3_Y2 = 1582.33;

		cam4_X1 = 796.819;
		cam4_Y1 = 1583.58;
		cam4_X2 = 796.821;
		cam4_Y2 = 1582.34;

		cam5_X1 = 795.684;
		cam5_Y1 = 1583.57;
		cam5_X2 = 795.674;
		cam5_Y2 = 1582.33;

		cam6_X1 = 794.675;
		cam6_Y1 = 1583.58;
		cam6_X2 = 794.679;
		cam6_Y2 = 1582.34;

		cam_Z = 16.1771;

		buy_1 = 100;
		buy_2 = 300;
		buy_3 = 500;
		buy_4 = 6000;
		buy_5 = 300;

		add_ammo1 = 17;
		add_ammo2 = 50;
		add_ammo3 = 8;
		add_ammo4 = 10;
		add_ammo5 = 1;

		set_weap_1 = WEAPON_PISTOL;
		set_weap_2 = WEAPON_EPISODIC_13;
		set_weap_3 = WEAPON_EPISODIC_11;
		set_weap_4 = WEAPON_EPISODIC_15;
		set_weap_5 = WEAPON_GRENADE;
	}

	CLEAR_HELP(); // удаляем текст подсказки
	PRINT_HELP_FOREVER("NE_NAVIG"); // навигация
	SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока

	CREATE_CAM( 14, &camera );
	POINT_CAM_AT_COORD	( camera, cam1_X2, cam1_Y2, cam_Z ); // куда смотрит камера
	SET_CAM_POS			( camera, cam1_X1, cam1_Y1, cam_Z );//расположение камеры
	SET_CAM_ACTIVE( camera, 1 );
	SET_CAM_PROPAGATE( camera, 0 );
	ACTIVATE_SCRIPTED_CAMS(1, 1);

	GET_GAME_CAM(&camera3);
	CREATE_CAM( 3, &camera2 );
	SET_CAM_INTERP_STYLE_DETAILED( camera2, 1, 1, 1, 1 );
	SET_CAM_INTERP_STYLE_CORE( camera2, camera3, camera, 500, 0 ); //перемещение камеры от игрока на точку указанную в координатах "SET_CAM_POS(camera, X, Y, Z)" 
	SET_CAM_ACTIVE( camera2, 1 );
	SET_CAM_PROPAGATE( camera2, 1 );
	ACTIVATE_SCRIPTED_CAMS(1, 1);

	uint time_before_shopping;
	GET_GAME_TIMER(&time_before_shopping);

	while (true)
	{
		WAIT(0);
		DISPLAY_CASH(true);
		if (help == 1)
		{
			if (TIMERB() > 1000)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP_FOREVER("NE_NAVIG"); // навигация
				help = 0;
			}
		}
		if ((IS_BUTTON_PRESSED( 0, 11 )) || (IS_GAME_KEYBOARD_NAV_RIGHT_PRESSED( 1 ))) //нажато вправо
		{
			SETTIMERA(0);
			while (true)
			{
				WAIT(0);
				if ((IS_BUTTON_PRESSED( 0, 11 )) || (IS_GAME_KEYBOARD_NAV_RIGHT_PRESSED( 1 ))) //нажато вправо
				{
					if (TIMERA() > 600)
					{
						break;
					}
				}
				else if ((!IS_BUTTON_PRESSED( 0, 11 )) || (!IS_GAME_KEYBOARD_NAV_RIGHT_PRESSED( 1 ))) //нажато вправо
				{
					break;
				}
			}
			if (set_cam < all_cam)
			{
				cam_on = 1;
				set_cam += 1;
			}
		}
		else if ((IS_BUTTON_PRESSED( 0, 10 )) || (IS_GAME_KEYBOARD_NAV_LEFT_PRESSED( 1 ))) //нажато влево
		{
			SETTIMERA(0);
			while (true)
			{
				WAIT(0);
				if ((IS_BUTTON_PRESSED( 0, 10 )) || (IS_GAME_KEYBOARD_NAV_LEFT_PRESSED( 1 ))) //нажато влево
				{
					if (TIMERA() > 600)
					{
						break;
					}
				}
				else if ((!IS_BUTTON_PRESSED( 0, 10 )) || (!IS_GAME_KEYBOARD_NAV_LEFT_PRESSED( 1 ))) //нажато влево
				{
					break;
				}
			}
			if (set_cam >= 2)
			{
				cam_on = 1;
				set_cam -= 1;
			}
		}
		else if ((IS_BUTTON_PRESSED( 0, 17 )) || ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER()))) // BACKSPACE
		{
			break;
		}
		else if ((IS_BUTTON_PRESSED( 0, 16 )) || ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()))) //клавиатура ENTER
		{
			STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
			if (set_cam == 1)
			{
				if (money_ped >= buy_1)
				{
					ADD_SCORE( GetPlayerIndex(), -buy_1 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_SPENT_IN_GUN_SHOP, buy_1);
					GIVE_WEAPON_TO_CHAR(GetPlayerPed(), set_weap_1, add_ammo1, FALSE);	
					SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), set_weap_1, TRUE);
				}
				else
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NE_NOTMONEY"); // пишем недостаточно средств
					help = 1;
				}
			}
			else if (set_cam == 2)
			{
				if (money_ped >= buy_2)
				{
					ADD_SCORE( GetPlayerIndex(), -buy_2 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_SPENT_IN_GUN_SHOP, buy_2);
					GIVE_WEAPON_TO_CHAR(GetPlayerPed(), set_weap_2, add_ammo2, FALSE);	
					SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), set_weap_2, TRUE);
				}
				else
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NE_NOTMONEY"); // пишем недостаточно средств
					help = 1;
				}
			}
			else if (set_cam == 3)
			{
				if (money_ped >= buy_3)
				{
					ADD_SCORE( GetPlayerIndex(), -buy_3 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_SPENT_IN_GUN_SHOP, buy_3);
					GIVE_WEAPON_TO_CHAR(GetPlayerPed(), set_weap_3, add_ammo3, FALSE);		
					SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), set_weap_3, TRUE);
				}
				else
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NE_NOTMONEY"); // пишем недостаточно средств
					help = 1;
				}
			}
			else if (set_cam == 4)
			{
				if (money_ped >= buy_4)
				{
					ADD_SCORE( GetPlayerIndex(), -buy_4 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_SPENT_IN_GUN_SHOP, buy_4);
					GIVE_WEAPON_TO_CHAR(GetPlayerPed(), set_weap_4, add_ammo4, FALSE);	
					SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), set_weap_4, TRUE);
				}
				else
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NE_NOTMONEY"); // пишем недостаточно средств
					help = 1;
				}
			}
			else if (set_cam == 5)
			{
				if (money_ped >= buy_5)
				{
					ADD_SCORE( GetPlayerIndex(), -buy_5 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_SPENT_IN_GUN_SHOP, buy_5);
					if (set_weap_5 == 0)
					{
						ADD_ARMOUR_TO_CHAR(GetPlayerPed(), 100);
					}
					else
					{
						GIVE_WEAPON_TO_CHAR(GetPlayerPed(), set_weap_5, add_ammo5, FALSE);	
						SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), set_weap_5, TRUE);
					}
				}
				else
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NE_NOTMONEY"); // пишем недостаточно средств
					help = 1;
				}
			}
			else if (set_cam == 6)
			{
				if (money_ped >= 200)
				{
					ADD_SCORE( GetPlayerIndex(), -200 );//даём игроку денег
					INCREMENT_FLOAT_STAT(STAT_SPENT_IN_GUN_SHOP, 200);
					ADD_ARMOUR_TO_CHAR(GetPlayerPed(), 100);
				}
				else
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NE_NOTMONEY"); // пишем недостаточно средств
					help = 1;
				}
			}
			while (true)
			{
				WAIT(0);
				if ((!IS_CONTROL_PRESSED( 2, 181 )) && (!IS_USING_CONTROLLER())) //клавиатура ENTER
				{
					if (!IS_BUTTON_PRESSED( 0, 16 ))
					{
						SETTIMERB(0);
						break;
					}
				}
				else if ((!IS_CONTROL_PRESSED( 2, 181 )) && (IS_USING_CONTROLLER())) //клавиатура ENTER
				{
					if (!IS_BUTTON_PRESSED( 0, 16 ))
					{
						SETTIMERB(0);
						break;
					}
				}
			}
		}
		if (cam_on == 1)
		{
			if (set_cam == 1)
			{
				POINT_CAM_AT_COORD	( camera, cam1_X2, cam1_Y2, cam_Z ); // куда смотрит камера
				SET_CAM_POS			( camera, cam1_X1, cam1_Y1, cam_Z );//расположение камеры
			}
			else if (set_cam == 2)
			{
				POINT_CAM_AT_COORD	( camera, cam2_X2, cam2_Y2, cam_Z ); // куда смотрит камера
				SET_CAM_POS			( camera, cam2_X1, cam2_Y1, cam_Z );//расположение камеры
			}
			else if (set_cam == 3)
			{
				POINT_CAM_AT_COORD	( camera, cam3_X2, cam3_Y2, cam_Z ); // куда смотрит камера
				SET_CAM_POS			( camera, cam3_X1, cam3_Y1, cam_Z );//расположение камеры
			}
			else if (set_cam == 4)
			{
				POINT_CAM_AT_COORD	( camera, cam4_X2, cam4_Y2, cam_Z ); // куда смотрит камера
				SET_CAM_POS			( camera, cam4_X1, cam4_Y1, cam_Z );//расположение камеры
			}
			else if (set_cam == 5)
			{
				POINT_CAM_AT_COORD	( camera, cam5_X2, cam5_Y2, cam_Z ); // куда смотрит камера
				SET_CAM_POS			( camera, cam5_X1, cam5_Y1, cam_Z );//расположение камеры
			}
			else if (set_cam == 6)
			{
				POINT_CAM_AT_COORD	( camera, cam6_X2, cam6_Y2, cam_Z ); // куда смотрит камера
				SET_CAM_POS			( camera, cam6_X1, cam6_Y1, cam_Z );//расположение камеры
			}
			SET_CAM_INTERP_STYLE_CORE( camera2, camera2, camera, 500, 0 ); //перемещение камеры от игрока на точку указанную в координатах "SET_CAM_POS(camera, X, Y, Z)" 
			cam_on = 0;
		}
	}
	ACTIVATE_SCRIPTED_CAMS( 0, 0 );
	DESTROY_CAM( camera );
	DESTROY_CAM( camera2 );
	CLEAR_HELP(); // удаляем текст подсказки
	DISPLAY_CASH(false);
	SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
	uint time_after_shopping;
	GET_GAME_TIMER(&time_after_shopping);
	INCREMENT_INT_STAT(STAT_TIME_SPENT_SHOPPING, time_after_shopping - time_before_shopping);
}



void i_need_hiling(void)
{
	WAIT(0);
	int money_ped;
	uint ranspeech;
	STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
	if ( money_ped >= 5)
	{
		REQUEST_ANIMS( "amb@hotdogcart" );//загружаем файл с анимацией
		while (!HAVE_ANIMS_LOADED( "amb@hotdogcart" )) WAIT(0);

		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R4_IA", "", 0, 0);//
		START_SCRIPT_CONVERSATION(1, 1);
		SETTIMERA( 0 );
		while(true)
		{
			WAIT(0);
			if (!IS_SCRIPTED_CONVERSATION_ONGOING())
			{
				break;
			}
			else if (TIMERA() > 8000)
			{
				break;
			}
		}
		GENERATE_RANDOM_INT_IN_RANGE(1, 9, &ranspeech);
		if ((ranspeech == 1) || (ranspeech == 4) || (ranspeech == 7))
		{
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "R8_A_LA", "", 0, 0);//
			START_SCRIPT_CONVERSATION(1, 1);
		}
		else if ((ranspeech == 2) || (ranspeech == 5) || (ranspeech == 8))
		{
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "R8_A_MA", "", 0, 0);//
			START_SCRIPT_CONVERSATION(1, 1);
		}
		else if ((ranspeech == 3) || (ranspeech == 6) || (ranspeech == 9))
		{
			NEW_SCRIPTED_CONVERSATION();
			ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
			ADD_LINE_TO_CONVERSATION(0, "R8_A_NA", "", 0, 0);//
			START_SCRIPT_CONVERSATION(1, 1);
		}
		TASK_PLAY_ANIM_SECONDARY_UPPER_BODY( GetPlayerPed(), "eat_hotdog_plyr", "amb@hotdogcart", 8.0, 1, 0, 0, 0, 3500 );//Воиспроизвидение анимации на педе
		SETTIMERA( 0 );
		while(true)
		{
			WAIT(0);
			if (TIMERA() > 4000)
			{
				break;
			}
		}
		ADD_SCORE( GetPlayerIndex(), -5 );//даём игроку денег
		INCREMENT_FLOAT_STAT(STAT_SPENT_ON_FOOD, 5);
		INCREMENT_INT_STAT(STAT_MEALS_EATEN, 1);
		SET_CHAR_HEALTH(GetPlayerPed(), 200);
	}
}



void ammu_nation(void)
{
	Ped ped1;
	int dm, cdm;
	int intHash;
	uint AudID1, PedM1;
	add_check = 0;
	GET_INTERIOR_FROM_CHAR(GetPlayerPed(), &intHash);

	LOAD_CHAR_DECISION_MAKER(2, &dm); // 4
	LOAD_COMBAT_DECISION_MAKER(3, &cdm); // 3 10
	SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
	SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);
	PedM1 = MODEL_M_Y_FRENCHTOM;//

	REQUEST_MODEL(PedM1);
	while (!HAS_MODEL_LOADED(PedM1)) WAIT(0);

	x = -0.484924;
	y = 2.02809;
	set_money = 0;
	siren = 0;
	check_X = PedX;
	check_Y = PedY;
	check_Z = PedZ;

	PedX = (x*COS((y-PedR))+y*SIN((y-PedR)))+PedX;
	PedY = (y*COS((y-PedR))-(x*SIN((y-PedR))))+PedY;

	CREATE_CHAR (26, PedM1, 527.002, -870.002, 4.64608, &ped1, TRUE);//  создать педа
	SET_CHAR_COORDINATES(ped1, PedX, PedY, PedZ+0.2);
	SET_CHAR_HEADING(ped1, PedR+180.0);

	if ( intHash == 258 ) // интрерьер Молл
	{
		SET_ROOM_FOR_CHAR_BY_NAME(ped1, "mall_mloroom");
	}

	SET_CHAR_DECISION_MAKER(ped1, dm);
	SET_COMBAT_DECISION_MAKER(ped1, cdm);
	UpdateWeaponOfPed(ped1, WEAPON_DEAGLE);
	
	while(true)
	{
		WAIT(0);
		if (set_money == 0)
		{
			DRAW_CHECKPOINT( check_X, check_Y, check_Z, 0.8, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, check_X, check_Y, check_Z, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				if (add_check == 0)
				{
					add_check = 1;
					i_need_tools();
				}
			}
			else
			{
				if (add_check == 1)
				{
					add_check = 0;
				}
			}
		}
		if (trigger == 3)
		{
			if (!IS_CHAR_IN_AREA_2D(GetPlayerPed(), 828.036, 1537.16, 788.138, 1602.397, 0))
			{
				break;
			}
		}
		else
		{
			if (!IS_CHAR_IN_AREA_2D(GetPlayerPed(), check_X+37, check_Y+37, check_X-37, check_Y-37, 0))
			{
				break;
			}
		}
		if ((IS_PLAYER_FREE_AIMING_AT_CHAR(GetPlayerIndex(), ped1)) || (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PedX-10, PedY-10, PedX+10, PedY+10, 0)))//проверка Игрок начал пальбу на старте
		{
			if (set_money == 0)
			{
				while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/RB4_MUSEUM_PIECE" )))
				{
					 WAIT(0);
				}
				AudID1 = GET_SOUND_ID();
				PLAY_SOUND_FROM_POSITION(AudID1, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", PedX, PedY, PedZ+3.2);
				siren = 1;
				ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
				APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
				SET_SENSE_RANGE(ped1, 100.0);
				TASK_COMBAT(ped1, GetPlayerPed());// агрим педа
				set_money = 1;
			}
		}
	}
	//очистить метод
	if (siren == 1)
	{
		while(true)
		{
			WAIT(0);
			if (!IS_CHAR_IN_AREA_2D(GetPlayerPed(), check_X+220, check_Y+220, check_X-220, check_Y-220, 0))
			{
				break;
			}
		}
		STOP_SOUND(AudID1);
		RELEASE_SOUND_ID(AudID1);
		AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED();
	}
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
	trigger = 0;
	Ammunition = 0;
}



void create_shops(void)
{
	Ped ped1;
	int dm, cdm;
	int intHash;
	Pickup money1, money2, money3, money4;
	uint AudID1, PedM1;
	Object cashbox;
	add_check = 0;
	GET_INTERIOR_FROM_CHAR(GetPlayerPed(), &intHash);

	if (James == 1)
	{
		LOAD_CHAR_DECISION_MAKER(2, &dm); // 4
		LOAD_COMBAT_DECISION_MAKER(3, &cdm); // 3 10
		SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(dm, 50);
		SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(cdm, 50);
		PedM1 = MODEL_IG_JOHNNYBIKER;// James
	}
	else if (Pizza == 1)
	{
		PedM1 = MODEL_M_Y_FF_WSPIZZA_R;//
	}
	else
	{
		PedM1 = MODEL_M_Y_BOWL_01;//
	}
	REQUEST_MODEL(PedM1);
	while (!HAS_MODEL_LOADED(PedM1)) WAIT(0);

	uint ObjM1 = vc_cashreg; // касса
	REQUEST_MODEL(ObjM1);
	while (!HAS_MODEL_LOADED(ObjM1)) WAIT(0);

	x = -0.484924;
	y = 2.02809;
	set_money = 0;
	siren = 0;
	check_X = PedX;
	check_Y = PedY;
	check_Z = PedZ;

	PedX = (x*COS((y-PedR))+y*SIN((y-PedR)))+PedX;
	PedY = (y*COS((y-PedR))-(x*SIN((y-PedR))))+PedY;

	CREATE_CHAR (26, PedM1, 527.002, -870.002, 4.64608, &ped1, TRUE);//  создать педа
	SET_CHAR_COORDINATES(ped1, PedX, PedY, PedZ+0.2);
	SET_CHAR_HEADING(ped1, PedR+180.0);

	if ( intHash == 258 ) // интрерьер Молл
	{
		SET_ROOM_FOR_CHAR_BY_NAME(ped1, "mall_mloroom");
	}

	if (James == 1)
	{
		SET_CHAR_DECISION_MAKER(ped1, dm);
		SET_COMBAT_DECISION_MAKER(ped1, cdm);
		UpdateWeaponOfPed(ped1, WEAPON_KNIFE);
	}
	// касса
	x = -0.1;
	y = 1.26;
	PedX = (x*COS((y-PedR))+y*SIN((y-PedR)))+check_X;
	PedY = (y*COS((y-PedR))-(x*SIN((y-PedR))))+check_Y;
	GET_GROUND_Z_FOR_3D_COORD(PedX, PedY, PedZ+2.5, &PedZ);

	CREATE_OBJECT_NO_OFFSET(ObjM1, PedX, PedY, PedZ, &cashbox, TRUE);
	SET_OBJECT_HEADING(cashbox, PedR);

	if ( intHash == 258 ) // интрерьер Молл
	{
		ADD_OBJECT_TO_INTERIOR_ROOM_BY_NAME(cashbox, "mall_mloroom");
	}

	//грузим анимацию
	REQUEST_ANIMS( "ne_missbank" );//загружаем файл с анимацией
	while (!HAVE_ANIMS_LOADED( "ne_missbank" )) WAIT(0);
	while(true)
	{
		WAIT(0);
		if (((Pizza == 1) && (set_money == 0)) || ((Tools > 0) && (set_money == 0)))
		{
			DRAW_CHECKPOINT( check_X, check_Y, check_Z, 0.8, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, check_X, check_Y, check_Z, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				if (add_check == 0)
				{
					add_check = 1;
					if (Pizza == 1)
					{
						i_need_hiling();
					}
					else if (Tools > 0)
					{
						i_need_tools();
					}
				}
			}
			else
			{
				if (add_check == 1)
				{
					add_check = 0;
				}
			}
		}
		if (trigger == 1)
		{
			if (!IS_CHAR_IN_AREA_2D(GetPlayerPed(), check_X+20, check_Y+30, check_X-20, check_Y-30, 0))
			{
				break;
			}
		}
		else if (trigger == 2)
		{
			if (!IS_CHAR_IN_AREA_2D(GetPlayerPed(), 839.019, 1601.49, 792.267, 1647.401, 0))
			{
				break;
			}
		}
		else
		{
			if (!IS_CHAR_IN_AREA_2D(GetPlayerPed(), check_X+37, check_Y+37, check_X-37, check_Y-37, 0))
			{
				break;
			}
		}
		if ((IS_PLAYER_FREE_AIMING_AT_CHAR(GetPlayerIndex(), ped1)) || (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), PedX-10, PedY-10, PedX+10, PedY+10, 0)))//проверка Игрок начал пальбу на старте
		{
			if (set_money == 0)
			{
				SETTIMERA( 0 );
				set_money = 1;
				if (James != 1)
				{
					TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "armsup_loop", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				}
			}
			if ((TIMERA() > 5000) && (set_money > 0) && (set_money < 5))
			{
				GET_OBJECT_COORDINATES(cashbox, &PedX, &PedY, &PedZ);
				if (set_money == 1)
				{
					CREATE_MONEY_PICKUP(((x-0.4)*COS((y-PedR))+y*SIN((y-PedR)))+check_X, (y*COS((y-PedR))-((x-0.4)*SIN((y-PedR))))+check_Y, PedZ+0.1, 100, 1, &money1);
					if ( intHash == 258 ) // интрерьер Молл
					{
						ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(money1, "mall_mloroom");
					}
					SETTIMERA( 0 );
				}
				if (set_money == 2)
				{
					CREATE_MONEY_PICKUP(((x-0.6)*COS((y-PedR))+y*SIN((y-PedR)))+check_X, (y*COS((y-PedR))-((x-0.6)*SIN((y-PedR))))+check_Y, PedZ+0.1, 100, 1, &money2);
					if ( intHash == 258 ) // интрерьер Молл
					{
						ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(money2, "mall_mloroom");
					}
					ALTER_WANTED_LEVEL(GetPlayerIndex(), 1);
					APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
					SETTIMERA( 0 );
				}
				if (set_money == 3)
				{
					CREATE_MONEY_PICKUP(((x-0.8)*COS((y-PedR))+y*SIN((y-PedR)))+check_X, (y*COS((y-PedR))-((x-0.8)*SIN((y-PedR))))+check_Y, PedZ+0.1, 100, 1, &money3);
					if ( intHash == 258 ) // интрерьер Молл
					{
						ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(money3, "mall_mloroom");
					}
					ALTER_WANTED_LEVEL(GetPlayerIndex(), 2);
					APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
					SETTIMERA( 0 );
				}
				if (set_money == 4)
				{
					CREATE_MONEY_PICKUP(((x-1.0)*COS((y-PedR))+y*SIN((y-PedR)))+check_X, (y*COS((y-PedR))-((x-1.0)*SIN((y-PedR))))+check_Y, PedZ+0.1, 100, 1, &money4);
					if ( intHash == 258 ) // интрерьер Молл
					{
						ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(money4, "mall_mloroom");
					}
					ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
					APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
					SETTIMERA( 0 );
				}
				set_money += 1;
			}
		}
		else
		{
			if ((set_money > 0) && (set_money < 10))
			{
				// сигналка тут
				if ((!IS_CHAR_DEAD(ped1)) && (James != 1))
				{
					while (!(REQUEST_AMBIENT_AUDIO_BANK( "SCRIPT_MISSION/RB4_MUSEUM_PIECE" )))
					{
						 WAIT(0);
					}
					AudID1 = GET_SOUND_ID();
					PLAY_SOUND_FROM_POSITION(AudID1, "SCRIPT_MISSION_RB4_MUSEUM_PIECE_ALARM_LOOP", PedX, PedY, PedZ+3.2);
					siren = 1;
					TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "duck_cower", "ne_missbank", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
					ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
					APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
				}
				set_money = 99;
			}
		}
	}
	//очистить метод
	if (siren == 1)
	{
		while(true)
		{
			WAIT(0);
			if (!IS_CHAR_IN_AREA_2D(GetPlayerPed(), check_X+220, check_Y+220, check_X-220, check_Y-220, 0))
			{
				break;
			}
		}
		STOP_SOUND(AudID1);
		RELEASE_SOUND_ID(AudID1);
		AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED();
	}
	REMOVE_PICKUP(money1);
	REMOVE_PICKUP(money2);
	REMOVE_PICKUP(money3);
	REMOVE_PICKUP(money4);
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
	MARK_MODEL_AS_NO_LONGER_NEEDED(ObjM1);//выгружаем модель
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
	DELETE_OBJECT(&cashbox);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cashbox);
	Pizza = 0;
	Tools = 0;
	Ammunition = 0;
	James = 0;
	trigger = 0;

}



void global_world(void)
{
	int hours_s, minutes_s;
	trigger = 0;
	siren = 0;
	Pizza = 0;
	Tools = 0;
	Ammunition = 0;
	James = 0;
	swap = 0;
	swap2 = 0;
	sebal = 0;
	angle = 0;
	cop_on = 1;
	spawn_car = 0;
	spawnT = 0;
	spawnL = 0;
	spawn_blood = 0;
	spawn_inf = 0;
	open_D_door = 0;
	open_D_door2 = 0;
	open_pron = 0;
	open_star1 = 0;
	open_star2 = 0;
	run_on = 0;
	arm_on = 0;
	//fire_on = 0;
	heal_on = 0;
	spawnS1 = SPAWN_STATE_DISABLED_FROM_START;
	spawnS2 = SPAWN_STATE_DISABLED_FROM_START;
	spawnS3 = SPAWN_STATE_DISABLED_FROM_START;
	spawnS4 = SPAWN_STATE_DISABLED_FROM_START;
	spawnS5 = 0;
	spawnH = 0;
	spawnF = 0;
	spawnM = 0;
	in_taxi = 0;
	in_voodoo = 0;

	// ОТКЛЮЧАЕМ ПУТИ ТРАФИКА
	SWITCH_ROADS_OFF( 390.773, 1523.602, -1.286, -240.193, 1741.047, 80.0 );// Остров криветок <> Даунтаун
	SWITCH_ROADS_OFF( 318.472, -433.547, 0.0, -360.321, -349.814, 54.909 );// Вашингтон <> Доки
	SWITCH_ROADS_OFF( 722.177, 593.187, 0.0, 368.373, 805.895, 50.0 );//  Гольф <> клуб Гаити 1
	SWITCH_ROADS_OFF( 368.373, 546.309, 0.0, 379.467, 659.573, 50.0 );//  Гольф <> клуб Гаити 2
	SWITCH_ROADS_OFF( -379.467, 568.191, 0.0, 490.939, 624.621, 50.0 );// Гольф <> клуб Гаити 3
	SWITCH_ROADS_OFF( 606.697, 34.711, 0.0, 192.455, 125.665, 50.0 );// Вице Пойнт <> Остров Морской Звезды
	SWITCH_ROADS_OFF( -211.183, -9.076, 0.0, -384.859, 63.049, 50.0 );// Остров Морской Звезды <> Гавана

	// ЯХТА
	Car car1, carhidra;
	Car love, carCab, carSA, Sparrow, boat, maver;
	uint CarM1 = MODEL_TUGA;// Яхта Котеса

	REQUEST_MODEL(CarM1);// 
	while (!HAS_MODEL_LOADED(CarM1));////проверка "пед загрузился" если нет то начанаем с начало

	CREATE_CAR(CarM1, 54.0, -789.9, -3.0, &car1, TRUE);// Яхта Котеса
	SET_CAR_HEADING(car1, 360.0);
	TURN_OFF_VEHICLE_EXTRA(car1, 1, 0);
	FREEZE_CAR_POSITION(car1, 1); 
	SET_CAR_IN_CUTSCENE(car1, 1);

	// СТРОЙКА
	Object str1, str2, str3;
	uint strM1 = bldngst2meshcol; //Несущий каркас здания
	uint strM2 = buildingsite2col; //Обшивка здания
	uint strM3 = buildingsite2_damcol; //Несущий каркас здания

	REQUEST_MODEL(strM1);// Несущий каркас здания
	while (!HAS_MODEL_LOADED(strM1)) WAIT(0);
	REQUEST_MODEL(strM2);// Обшивка здания
	while (!HAS_MODEL_LOADED(strM2)) WAIT(0);
	REQUEST_MODEL(strM3);// Несущий каркас здания
	while (!HAS_MODEL_LOADED(strM3)) WAIT(0);

	CREATE_OBJECT_NO_OFFSET(strM1, 547.9089, 166.84, 902.630675, &str1, TRUE);
	SET_OBJECT_DYNAMIC(str1, 0);
	SET_OBJECT_INVINCIBLE(str1, 1);
	FREEZE_OBJECT_POSITION(str1, 1);

	CREATE_OBJECT_NO_OFFSET(strM2, 547.9089, 166.84, 902.630675, &str2, TRUE);
	SET_OBJECT_DYNAMIC(str2, 0);
	SET_OBJECT_INVINCIBLE(str2, 1);
	FREEZE_OBJECT_POSITION(str2, 1);

	CREATE_OBJECT_NO_OFFSET(strM3, 547.9089, 166.84, 902.630675, &str3, TRUE);
	SET_OBJECT_DYNAMIC(str3, 0);
	SET_OBJECT_INVINCIBLE(str3, 1);
	FREEZE_OBJECT_POSITION(str3, 1);

	// ЗАВОД
	Object fac1, fac2;
	uint facM1 = build1_col; //Завод
	uint facM2 = buildblown_col; //Разрушенный завод

	REQUEST_MODEL(facM1);//
	while (!HAS_MODEL_LOADED(facM1)) WAIT(0);
	REQUEST_MODEL(facM2);//
	while (!HAS_MODEL_LOADED(facM2)) WAIT(0);

	CREATE_OBJECT_NO_OFFSET(facM1, -732.4966, 617.8056, 912.58214, &fac1, TRUE);
	SET_OBJECT_DYNAMIC(fac1, 0);
	SET_OBJECT_INVINCIBLE(fac1, 1);
	FREEZE_OBJECT_POSITION(fac1, 1);

	CREATE_OBJECT_NO_OFFSET(facM2, -732.4966, 617.8056, 912.58214, &fac2, TRUE);
	SET_OBJECT_DYNAMIC(fac2, 0);
	SET_OBJECT_INVINCIBLE(fac2, 1);
	FREEZE_OBJECT_POSITION(fac2, 1);

	// ОСТРОВ МОРСКОЙ ЗВЕЗДЫ
	Object star_door1, star_door2, star_door3, star_door4;
	uint starM1 = comgate2closed; //Ворота на остров САРФИШ Закрыто
	uint starM2 = comgate2open; //Ворота на остров САРФИШ открыто
	uint starM3 = comgate1closed; //Ворота на второй остров Закрыто
	uint starM4 = comgate1open; //Ворота на второй остров открыто

	REQUEST_MODEL(starM1);//
	REQUEST_MODEL(starM2);//
	REQUEST_MODEL(starM3);//
	REQUEST_MODEL(starM4);//
	while ((!HAS_MODEL_LOADED(starM1)) || (!HAS_MODEL_LOADED(starM2)) || (!HAS_MODEL_LOADED(starM3)) || (!HAS_MODEL_LOADED(starM4))) WAIT(0);

	CREATE_OBJECT_NO_OFFSET(starM1, 251.549, 60.39, 6.31316, &star_door1, TRUE);
	SET_OBJECT_HEADING(star_door1, 102.0);
	SET_OBJECT_DYNAMIC(star_door1, 0);
	FREEZE_OBJECT_POSITION(star_door1, 1);

	CREATE_OBJECT_NO_OFFSET(starM2, 249.176, 59.777, -7.52204, &star_door2, TRUE);
	SET_OBJECT_DYNAMIC(star_door2, 0);
	FREEZE_OBJECT_POSITION(star_door2, 1);

	CREATE_OBJECT_NO_OFFSET(starM3, -282.082, 43.311, 7.68508, &star_door3, TRUE);
	SET_OBJECT_DYNAMIC(star_door3, 0);
	FREEZE_OBJECT_POSITION(star_door3, 1);

	CREATE_OBJECT_NO_OFFSET(starM4, -279.524, 43.572, -7.68508, &star_door4, TRUE);
	SET_OBJECT_DYNAMIC(star_door4, 0);
	FREEZE_OBJECT_POSITION(star_door4, 1);

	// МОСТЫ
	Object bridge1, bridge2, bridge3;
	uint bridgeM1 = wsh_roadblock; // Баррикады Ванингтон
	uint bridgeM2 = nt_roadblockGF; // Баррикады Гольф клуб
	uint bridgeM3 = nt_roadblockCI; // Баррикады Остров креветок

	REQUEST_MODEL(bridgeM1);//
	REQUEST_MODEL(bridgeM2);//
	REQUEST_MODEL(bridgeM3);//
	while ((!HAS_MODEL_LOADED(bridgeM1)) || (!HAS_MODEL_LOADED(bridgeM2)) || (!HAS_MODEL_LOADED(bridgeM3))) WAIT(0);

	CREATE_OBJECT_NO_OFFSET(bridgeM1, 190.329, -402.929, 11.1891, &bridge1, TRUE);
	SET_OBJECT_DYNAMIC(bridge1, 0);
	FREEZE_OBJECT_POSITION(bridge1, 1);

	CREATE_OBJECT_NO_OFFSET(bridgeM2, 351.54, 614.358, 16.0669, &bridge2, TRUE);
	SET_OBJECT_DYNAMIC(bridge2, 0);
	FREEZE_OBJECT_POSITION(bridge2, 1);

	CREATE_OBJECT_NO_OFFSET(bridgeM3, 335.7, 1594.8, 6.70011, &bridge3, TRUE);
	SET_OBJECT_DYNAMIC(bridge3, 0);
	FREEZE_OBJECT_POSITION(bridge3, 1);

	// ОСОБНЯК
	Object diaz_door1, diaz_door2, diaz_door3;
	uint diazM1 = vc_star_door1; //Парадная
	uint diazM2 = vc_star_door2; //Крышка
	uint diazM3 = vc_star_door3; //Задняя дверь

	REQUEST_MODEL(diazM1);//
	REQUEST_MODEL(diazM2);//
	REQUEST_MODEL(diazM3);//
	while ((!HAS_MODEL_LOADED(diazM1)) || (!HAS_MODEL_LOADED(diazM2)) || (!HAS_MODEL_LOADED(diazM3))) WAIT(0);

	CREATE_OBJECT_NO_OFFSET(diazM1, 54.5462, -21.5325, 16.9252, &diaz_door1, TRUE);
	SET_OBJECT_DYNAMIC(diaz_door1, 0);
	FREEZE_OBJECT_POSITION(diaz_door1, 1);

	CREATE_OBJECT_NO_OFFSET(diazM2, 92.815, -40.7402, 32.3637, &diaz_door2, TRUE);
	SET_OBJECT_DYNAMIC(diaz_door2, 0);
	FREEZE_OBJECT_POSITION(diaz_door2, 1);

	CREATE_OBJECT_NO_OFFSET(diazM3, 86.7328, -45.8009, 7.1464, &diaz_door3, TRUE);
	SET_OBJECT_DYNAMIC(diaz_door3, 0);
	FREEZE_OBJECT_POSITION(diaz_door3, 1);

	//КИНОСТУДИЯ
	Object pron_door1, pron_door2, pron_door3, pron_door4, pron_door5;
	uint pronM1 = ci_gatesclosed; //Гл. Ворота закрыто
	uint pronM2 = ci_gatesopen; //Гл. Ворота открыто
	uint pronM3 = ci_backgateclose; //вторые вотора закрыто
	uint pronM4 = ci_backgateopen; //вторые вотора открыто
	uint pronM5 = ci_jetygatesopen; //Задние ворота

	REQUEST_MODEL(pronM1);//
	REQUEST_MODEL(pronM2);//
	REQUEST_MODEL(pronM3);//
	REQUEST_MODEL(pronM4);//
	REQUEST_MODEL(pronM5);//
	while ((!HAS_MODEL_LOADED(pronM1)) || (!HAS_MODEL_LOADED(pronM2)) || (!HAS_MODEL_LOADED(pronM3)) || (!HAS_MODEL_LOADED(pronM4)) || (!HAS_MODEL_LOADED(pronM5))) WAIT(0);

	CREATE_OBJECT_NO_OFFSET(pronM1, 444.697 ,1496.18, 7.128, &pron_door1, TRUE);
	SET_OBJECT_DYNAMIC(pron_door1, 0);
	FREEZE_OBJECT_POSITION(pron_door1, 1);

	CREATE_OBJECT_NO_OFFSET(pronM2, 443.273, 1496.31, -7.128, &pron_door2, TRUE);
	SET_OBJECT_DYNAMIC(pron_door2, 0);
	FREEZE_OBJECT_POSITION(pron_door2, 1);

	CREATE_OBJECT_NO_OFFSET(pronM3, 421.147, 1417.06, 8.40003, &pron_door3, TRUE);
	SET_OBJECT_DYNAMIC(pron_door3, 0);
	FREEZE_OBJECT_POSITION(pron_door3, 1);

	CREATE_OBJECT_NO_OFFSET(pronM4, 418.619, 1417.12, -8.40003, &pron_door4, TRUE);
	SET_OBJECT_DYNAMIC(pron_door4, 0);
	FREEZE_OBJECT_POSITION(pron_door4, 1);

	CREATE_OBJECT_NO_OFFSET(pronM5, 317.171, 1560.77, 6.353, &pron_door5, TRUE);
	SET_OBJECT_HEADING(pron_door5, -86.3);
	SET_OBJECT_DYNAMIC(pron_door5, 0);
	FREEZE_OBJECT_POSITION(pron_door5, 1);

	// ПРОЖЕКТОР
	Object progektor, light, lest_1, lest_2, lest_3, lest_4;
	uint lest_a_M = dt_gspot_stairs_b; //лестница вверх
	uint lest_b_M = dt_gspot_stairs; //лестница вниз
	uint light_a_M = dts_spot_a; //прожектор
	uint light_b_M = dts_spot_b; //свет прожектора

	REQUEST_MODEL(lest_a_M);// лестница вверх
	while (!HAS_MODEL_LOADED(lest_a_M)) WAIT(0);
	REQUEST_MODEL(lest_b_M);// лестница вниз
	while (!HAS_MODEL_LOADED(lest_b_M)) WAIT(0);
	REQUEST_MODEL(light_a_M);// прожектор
	while (!HAS_MODEL_LOADED(light_a_M)) WAIT(0);
	REQUEST_MODEL(light_b_M);// свет прожектора
	while (!HAS_MODEL_LOADED(light_b_M)) WAIT(0);

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
	SET_OBJECT_DYNAMIC(lest_1, 0);
	SET_OBJECT_DYNAMIC(lest_2, 0);
	SET_OBJECT_DYNAMIC(lest_3, 0);
	SET_OBJECT_DYNAMIC(lest_4, 0);
	SET_OBJECT_DYNAMIC(progektor, 0);
	SET_OBJECT_DYNAMIC(light, 0);
	SET_OBJECT_INVINCIBLE(lest_1, 1);
	SET_OBJECT_INVINCIBLE(lest_2, 1);
	SET_OBJECT_INVINCIBLE(lest_3, 1);
	SET_OBJECT_INVINCIBLE(lest_4, 1);
	SET_OBJECT_INVINCIBLE(progektor, 1);
	SET_OBJECT_INVINCIBLE(light, 1);
	FREEZE_OBJECT_POSITION(lest_1, 1);
	FREEZE_OBJECT_POSITION(lest_2, 1);
	FREEZE_OBJECT_POSITION(lest_3, 1);
	FREEZE_OBJECT_POSITION(lest_4, 1);
	FREEZE_OBJECT_POSITION(progektor, 1);
	FREEZE_OBJECT_POSITION(light, 1);

	while (TRUE)
	{
		WAIT(0);
		// ----------------------------------- ТЕЛЕПОРТЫ -----------------------------------
		if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 25.04, 1651.798, 4.93, 20.04, 1656.798, 9.93, 0 ))// телепорт на крушу "Vice City News"
		{
			DO_SCREEN_FADE_OUT(1000);
			while (IS_SCREEN_FADING())
			{
				WAIT(0);
			}
			SET_CHAR_COORDINATES(GetPlayerPed(), -14.9423, 1661.15, 50.7111);
			SET_CHAR_HEADING(GetPlayerPed(), -95.0);
			WAIT(500);
			DO_SCREEN_FADE_IN(1000);
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -16.199, 1657.671, 50.138, -21.199, 1662.671, 55.138, 0 ))// телепорт с круши "Vice City News"
		{
			DO_SCREEN_FADE_OUT(1000);
			while (IS_SCREEN_FADING())
			{
				WAIT(0);
			}
			SET_CHAR_COORDINATES(GetPlayerPed(), 22.54, 1650.92, 5.29218);
			SET_CHAR_HEADING(GetPlayerPed(), 175.0);
			WAIT(500);
			DO_SCREEN_FADE_IN(1000);
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -395.249, 1842.97, 4.499, -400.249, 1847.97, 9.499, 0 ))// телепорт на крушу "Hyman Condo"
		{
			DO_SCREEN_FADE_OUT(1000);
			while (IS_SCREEN_FADING())
			{
				WAIT(0);
			}
			SET_CHAR_COORDINATES(GetPlayerPed(), -382.115, 1887.5, 60.672);
			SET_CHAR_HEADING(GetPlayerPed(), 90.0);
			WAIT(500);
			DO_SCREEN_FADE_IN(1000);
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -375.722, 1884.996, 60.141, -380.722, 1889.996, 65.141, 0 ))// телепорт с круши "Hyman Condo"
		{
			DO_SCREEN_FADE_OUT(1000);
			while (IS_SCREEN_FADING())
			{
				WAIT(0);
			}
			SET_CHAR_COORDINATES(GetPlayerPed(), -396.592, 1841.62, 5.70449);
			SET_CHAR_HEADING(GetPlayerPed(), -170.0);
			WAIT(500);
			DO_SCREEN_FADE_IN(1000);
		}
		// ----------------------------------- ЯХТА -----------------------------------
		if (G_CORTEZ > 7)
		{
			if ((sebal == 0) || (sebal == 1))
			{
				SET_CAR_COORDINATES(car1, 512.0, 4096.0, -3.0);// перемещаем игрока
				sebal = 2;
			}
		}
		else
		{
			if ((sebal == 0) || (sebal == 2))
			{
				SET_CAR_COORDINATES(car1, 54.0, -789.9, -3.0);// перемещаем игрока
				sebal = 1;
			}
		}
		// --------------------------------- СТРОЙКА ----------------------------------
		if (G_AVERY < 3)// стройка стоит целая
		{
			if (swap == 0)
			{
				SET_OBJECT_COORDINATES(str1, 547.9089, 166.84, 2.630675);
				SET_OBJECT_COORDINATES(str2, 547.9089, 166.84, 2.630675);
				SET_OBJECT_COORDINATES(str3, 547.9089, 166.84, 902.630675);
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(547.9089, 166.84, -5.0, 0.05000000, GET_HASH_KEY("buildingsite2_dam"), 0); // сделать невидимой разруш. модель из wpl
				swap = 1;
			}

		}
		else if ((G_AVERY > 2) && (G_AVERY < 10)) // стройка взорвона переменная "G_AVERY = 3"
		{
			if ((swap == 0) || (swap == 1))
			{
				SET_OBJECT_COORDINATES(str1, 547.9089, 166.84, 902.630675);
				SET_OBJECT_COORDINATES(str2, 547.9089, 166.84, 902.630675);
				SET_OBJECT_COORDINATES(str3, 547.9089, 166.84, 2.630675);

				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(547.9089, 166.84, 2.630675, 0.05000000, GET_HASH_KEY("buildingsite2"), 0);  // удаляем коллизию и убираем целое здание для катсцены
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(547.9089, 166.84, 2.630675, 0.05000000, GET_HASH_KEY("bldngst2mesh"), 0);
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(547.9089, 166.84, -5.0, 0.05000000, GET_HASH_KEY("buildingsite2_dam"), 1); // создание разруш. модели
				swap = 2;
			}
		}
		else if (G_AVERY == 99) // происходит катсцена
		{
			if (swap == 1)
			{
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(547.9089, 166.84, 2.630675, 0.05000000, GET_HASH_KEY("buildingsite2"), 0);  // удаляем коллизию и убираем целое здание для катсцены
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(547.9089, 166.84, 2.630675, 0.05000000, GET_HASH_KEY("bldngst2mesh"), 0);
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(547.9089, 166.84, -5.0, 0.05000000, GET_HASH_KEY("buildingsite2_dam"), 0); // создание разруш. модели
				swap = 0;
			}
		}
		// --------------------------------- ЗАВОД ----------------------------------
		if (G_CUBAN <= 5)// завод стоит целый
		{
			if (swap2 == 0)
			{
				SET_OBJECT_COORDINATES(fac1, -732.4966, 617.8056, 12.58214);
				SET_OBJECT_COORDINATES(fac2, -732.4966, 617.8056, 912.58214);//Разрушенный завод
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(-732.4966, 617.8056, 12.58214, 1.0, GET_HASH_KEY("buildblown"), 0);
				swap2 = 1;
			}

		}
		else if ((G_CUBAN > 5) && (G_CUBAN < 15)) // завод взорван переменная "G_CUBAN = 6"
		{
			if ((swap2 == 0) || (swap2 == 1))
			{
				SET_OBJECT_COORDINATES(fac1, -732.4966, 617.8056, 912.58214);
				SET_OBJECT_COORDINATES(fac2, -732.4966, 617.8056, 12.58214);//Разрушенный завод

				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(-732.4966, 617.8056, 12.58214, 1.0, GET_HASH_KEY("build1"), 0);
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(-753.0992, 618.2167, 11.30857, 1.0, GET_HASH_KEY("hdrugfactoryint"), 0);
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(-753.0992, 618.2167, 11.30857, 1.0, GET_HASH_KEY("hdrugfactoryintb"), 0);
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(-732.4966, 617.8056, 12.58214, 1.0, GET_HASH_KEY("buildblown"), 1);
				swap2 = 2;
			}
		}
		else if (G_CUBAN == 99) // происходит катсцена
		{
			if (swap2 == 1)
			{
				CLEAR_AREA(-732.4966, 617.8056, 12.58214, 85.0, 1);//очещаем зону загрузки
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(-732.4966, 617.8056, 12.58214, 1.0, GET_HASH_KEY("build1"), 0);
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(-753.0992, 618.2167, 11.30857, 1.0, GET_HASH_KEY("hdrugfactoryint"), 0);
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(-753.0992, 618.2167, 11.30857, 1.0, GET_HASH_KEY("hdrugfactoryintb"), 0);
				SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(-732.4966, 617.8056, 12.58214, 1.0, GET_HASH_KEY("buildblown"), 0);
				swap2 = 0;
			}
		}
		// --------------------------------- ОСТРОВ МОРСКОЙ ЗВЕЗДЫ И МОСТЫ---------------------------------
		if (G_DIAZ > 0)
		{
			if (open_star1 == 0)
			{
				SET_INT_STAT(STAT_ISLANDS_UNLOCKED, 3);
				SET_OBJECT_COORDINATES(star_door1, 251.549, 60.39, -6.31316);
				SET_OBJECT_COORDINATES(star_door2, 249.176, 59.777, 7.52204);
				SWITCH_ROADS_BACK_TO_ORIGINAL( 606.697, 34.711, 0.0, 192.455, 125.665, 50.0 );// Вице Пойнт <> Остров Морской Звезды
				open_star1 = 1;
			}
		}
		if (G_DIAZ > 2)
		{
			if (open_star2 == 0)
			{
				SET_INT_STAT(STAT_ISLANDS_UNLOCKED, 4);
				SET_OBJECT_COORDINATES(star_door3, -282.082, 43.311, -7.68508);
				SET_OBJECT_COORDINATES(star_door4, -279.524, 43.572, 7.68508);
				SET_OBJECT_COORDINATES(bridge1, 190.329, -402.929, -11.1891);
				SET_OBJECT_COORDINATES(bridge2, 351.54, 614.358, -16.0669);
				SET_OBJECT_COORDINATES(bridge3, 335.7, 1594.8, -16.70011);
				SWITCH_ROADS_BACK_TO_ORIGINAL( 390.773, 1523.602, -1.286, -240.193, 1741.047, 80.0 );// Остров криветок <> Даунтаун
				SWITCH_ROADS_BACK_TO_ORIGINAL( 318.472, -433.547, 0.0, -360.321, -349.814, 54.909 );// Вашингтон <> Доки
				SWITCH_ROADS_BACK_TO_ORIGINAL( 722.177, 593.187, 0.0, 368.373, 805.895, 50.0 );//  Гольф <> клуб Гаити 1
				SWITCH_ROADS_BACK_TO_ORIGINAL( 368.373, 546.309, 0.0, 379.467, 659.573, 50.0 );//  Гольф <> клуб Гаити 2
				SWITCH_ROADS_BACK_TO_ORIGINAL( -379.467, 568.191, 0.0, 490.939, 624.621, 50.0 );// Гольф <> клуб Гаити 3
				SWITCH_ROADS_BACK_TO_ORIGINAL( -211.183, -9.076, 0.0, -384.859, 63.049, 50.0 );//  Остров Морской Звезды <> Гавана
				open_star2 = 1;
			}
		}

		// --------------------------------- ОСОБНЯК ---------------------------------
		if (G_DIAZ == 99)
		{
			if (open_D_door == 0)
			{
				SET_OBJECT_COORDINATES(diaz_door3, 86.7328, -45.8009, -1.146);
				open_D_door = 1;
			}
		}
		else if (G_DIAZ >= 9)
		{
			if (open_D_door2 == 0)
			{
				SET_OBJECT_COORDINATES(diaz_door1, 86.7328, -45.8009, -2.146);
				SET_OBJECT_COORDINATES(diaz_door2, 86.7328, -45.8009, -2.146);
				SET_OBJECT_COORDINATES(diaz_door3, 86.7328, -45.8009, -2.146);
				open_D_door2 = 1;
			}
		}
		else
		{
			if (open_D_door == 1)
			{
				SET_OBJECT_COORDINATES(diaz_door3, 86.7328, -45.8009, 7.1464);
				open_D_door = 0;
			}
		}
		// --------------------------------- КИНОСТУДИЯ ---------------------------------
		if (G_PRON > 0)
		{
			if (open_pron == 0)
			{
				SET_OBJECT_COORDINATES(pron_door1, 444.697 ,1496.18, -7.128);
				SET_OBJECT_COORDINATES(pron_door2, 443.273, 1496.31, 7.128);
				SET_OBJECT_COORDINATES(pron_door3, 421.147, 1417.06, -8.40003);
				SET_OBJECT_COORDINATES(pron_door4, 418.619, 1417.12, 8.40003);
				SET_OBJECT_COORDINATES(pron_door5, 318.118, 1561.62, 6.35027);
				SET_OBJECT_HEADING(pron_door5, 0.0);
				open_pron = 1;
			}
		}
		// --------------------------------- ПРОЖЕКТОР ---------------------------------
		if (G_PRON < 5) // прожектор смотрит в море
		{
			if (angle == 0)
			{
				SET_OBJECT_COORDINATES(progektor, 78.5022, 1522.89, 39.7106);
				SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);
				SET_OBJECT_HEADING(progektor, 125.0);
				SET_OBJECT_HEADING(light, 125.0);

				SET_OBJECT_COORDINATES(lest_1, -140.934, 1907.22, 10.6474);
				SET_OBJECT_COORDINATES(lest_2, -103.961, 1891.43, 10.6474);
				SET_OBJECT_COORDINATES(lest_3, 65.9711, 1446.13, 11.0396);
				SET_OBJECT_COORDINATES(lest_4, 53.3428, 1481.54, 11.0396);

				angle = 1;
			}
		}
		else if ((G_PRON >= 5) && (G_PRON < 15)) // прожектор смотрит на здание
		{
			if ((angle == 0) || (angle == 1))
			{
				SET_OBJECT_COORDINATES(progektor, 78.5022, 1522.89, 39.7106);
				SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 39.7106);
				SET_OBJECT_HEADING(progektor, 13.0);
				SET_OBJECT_HEADING(light, 13.0);

				SET_OBJECT_COORDINATES(lest_2, -140.934, 1907.22, 10.6474);
				SET_OBJECT_COORDINATES(lest_1, -103.961, 1891.43, 10.6474);
				SET_OBJECT_COORDINATES(lest_4, 65.9711, 1446.13, 11.0396);
				SET_OBJECT_COORDINATES(lest_3, 53.3428, 1481.54, 11.0396);

				angle = 2;
			}
		}
		else if (G_PRON == 99) // отключаем прожектор
		{
			if (angle == 1)
			{
				SET_OBJECT_COORDINATES(progektor, 78.5022, 1522.89, 1239.7106);
				SET_OBJECT_COORDINATES(light, 78.5022, 1522.89, 1239.7106);
				SET_OBJECT_COORDINATES(lest_1, -103.961, 1891.43, 10.6474);
				SET_OBJECT_COORDINATES(lest_2, -103.961, 1891.43, 10.6474);
				SET_OBJECT_COORDINATES(lest_3, 53.3428, 1481.54, 11.0396);
				SET_OBJECT_COORDINATES(lest_4, 53.3428, 1481.54, 11.0396);
				angle = 0;
			}
		}
		// --------------------------------- Sunshine Autos ---------------------------------
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -675.318, -448.524, -0.96, -485.318, -258.524, 89.04, 0 )) && (G_BUSINES_SA > 1) && (spawn_car == 0))//проверка игрок в зоне загрузки автомобиля
		{
			if (G_BUSINES_SA > 1)
			{
				uint CarM1 = MODEL_FUTO;// Deluxo
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				CREATE_CAR(CarM1, -589.355, -333.968, 7.66709, &carSA, TRUE);
				SET_CAR_HEADING(carSA, 160.0);
				SET_VEHICLE_DIRT_LEVEL(carSA, 0);
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
				MARK_CAR_AS_NO_LONGER_NEEDED(&carSA);
				WAIT( 250 );
			}
			if (G_BUSINES_SA > 2)
			{
				uint CarM1 = MODEL_SABREGT;// Sabre Turbo
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				CREATE_CAR(CarM1, -580.991, -335.121, 7.66709, &carSA, TRUE);
				SET_CAR_HEADING(carSA, -170.0);
				SET_VEHICLE_DIRT_LEVEL(carSA, 0);
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
				MARK_CAR_AS_NO_LONGER_NEEDED(&carSA);
				WAIT( 250 );
			}
			if (G_BUSINES_SA > 3)
			{
				uint CarM1 = MODEL_CAVALCADE;// Sandking
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				CREATE_CAR(CarM1, -580.991, -335.121, 12.5935, &carSA, TRUE);
				SET_CAR_HEADING(carSA, -170.0);
				SET_VEHICLE_DIRT_LEVEL(carSA, 0);
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
				MARK_CAR_AS_NO_LONGER_NEEDED(&carSA);
				WAIT( 250 );
			}
			if (G_BUSINES_SA > 4)
			{
				uint CarM1 = MODEL_FELTZER;// Hotring Racer
				REQUEST_MODEL(CarM1);
				while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
				CREATE_CAR(CarM1, -589.355, -333.968, 12.5935, &carSA, TRUE);
				SET_CAR_HEADING(carSA, 160.0);
				SET_VEHICLE_DIRT_LEVEL(carSA, 0);
				MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
				MARK_CAR_AS_NO_LONGER_NEEDED(&carSA);
				WAIT( 250 );
			}
			spawn_car = 1;
		}
		else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -675.318, -448.524, -0.96, -485.318, -258.524, 89.04, 0 )) && (spawn_car == 1))//проверка игрок в зоне загрузки автомобиля
		{
			spawn_car = 0;
		}
		//============================== Спавн такси на координатах ======================================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -555.283, 697.072, 1.737, -605.283, 747.072, 16.737, 0 )) && (spawnT == 0))
		{
			if (G_CABS == 4)
			{
				uint CabM = MODEL_ROM;// такси Зебра
				REQUEST_MODEL(CabM);
				while (!HAS_MODEL_LOADED(CabM)) WAIT(0);
				CREATE_CAR(CabM, -569.498, 738.454, 5.965, &carCab, TRUE);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				SET_CAR_HEADING(carCab, 175.0);//градус поворота машины
				WAIT(10);
				MARK_MODEL_AS_NO_LONGER_NEEDED(CabM);//выгружаем модель
				MARK_CAR_AS_NO_LONGER_NEEDED(&carCab);//выгружаем модель машины(в последствии машина изчезнет)
			}
			else
			{
				uint CabM = MODEL_CABBY;// обычное такси
				REQUEST_MODEL(CabM);
				while (!HAS_MODEL_LOADED(CabM)) WAIT(0);
				CREATE_CAR(CabM, -569.498, 738.454, 5.965, &carCab, TRUE);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
				SET_CAR_HEADING(carCab, 175.0);//градус поворота машины
				WAIT(10);
				MARK_MODEL_AS_NO_LONGER_NEEDED(CabM);//выгружаем модель
				MARK_CAR_AS_NO_LONGER_NEEDED(&carCab);//выгружаем модель машины(в последствии машина изчезнет)
			}
			spawnT = 1;
		}
		else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -555.283, 697.072, 1.737, -605.283, 747.072, 16.737, 0 )) && (spawnT == 1))
		{
			spawnT = 0;
		}
		//============================== Спавн лимузина на координатах ======================================
		if (G_ROCK >= 5)
		{
			if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -382.122, 1618.784, 2.0, -452.122, 1743.784, 22.0, 0 )) && (spawnL == 0))
			{
				uint LoveM = MODEL_COGNOSCENTI;// Лимузин
				REQUEST_MODEL(LoveM);
				while (!HAS_MODEL_LOADED(LoveM)) WAIT(0);
				CREATE_CAR(LoveM, -433.092, 1681.284, 5.453, &love, TRUE);
				SET_CAR_HEADING(love, 180.0);
				WAIT(10);
				MARK_MODEL_AS_NO_LONGER_NEEDED(LoveM);//выгружаем модель
				MARK_CAR_AS_NO_LONGER_NEEDED(&love);//выгружаем модель машины(в последствии машина изчезнет)
				spawnL = 1;
			}
			else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -382.122, 1618.784, 2.0, -452.122, 1743.784, 22.0, 0 )) && (spawnL == 1))
			{
				spawnL = 0;
			}
		}
		//============================== Спавн инфернуса в молле ======================================
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 868.81, 1706.189, 8.0, 799.201, 1790.643, 35.0, 0 )) && (spawn_inf == 0))
		{
			uint inferM = MODEL_INFERNUS;// Инфернус
			REQUEST_MODEL(inferM);
			while (!HAS_MODEL_LOADED(inferM)) WAIT(0);
			CREATE_CAR(inferM, 818.5, 1760.0, 15.0, &love, TRUE);
			SET_CAR_HEADING(love, 90.0);
			SET_VEHICLE_DIRT_LEVEL(love, 0);
			SET_ROOM_FOR_CAR_BY_NAME(love, "mall_mloroom");
			WAIT(10);
			MARK_MODEL_AS_NO_LONGER_NEEDED(inferM);//выгружаем модель
			MARK_CAR_AS_NO_LONGER_NEEDED(&love);//выгружаем модель машины(в последствии машина изчезнет)
			spawn_inf = 1;
		}
		else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 868.81, 1706.189, 8.0, 799.201, 1790.643, 35.0, 0 )) && (spawn_inf == 1))
		{
			spawn_inf = 0;
		}
		// --------------------------------- Спавн блодринг у стадиона ---------------------------------
		if (G_BLOODRING > 0)
		{
			if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -621.291, 1735.546, 1.0, -721.291, 1811.662, 50.04, 0 )) && (spawn_blood == 0))//проверка игрок в зоне загрузки автомобиля
			{
				uint BloobM1 = MODEL_PEYOTE;// Bloodra
				REQUEST_MODEL(BloobM1);
				while (!HAS_MODEL_LOADED(BloobM1)) WAIT(100);
				CREATE_CAR(BloobM1, -691.905, 1784.17, 3.32399, &carSA, TRUE);
				SET_CAR_HEADING(carSA, -120.0);
				WAIT( 10 );
				MARK_MODEL_AS_NO_LONGER_NEEDED(BloobM1);
				MARK_CAR_AS_NO_LONGER_NEEDED(&carSA);
				WAIT( 200 );

				uint BloobM2 = MODEL_WILLARD;// Bloodrb
				REQUEST_MODEL(BloobM2);
				while (!HAS_MODEL_LOADED(BloobM2)) WAIT(100);
				CREATE_CAR(BloobM2, -694.948, 1779.36, 3.324, &carSA, TRUE);
				SET_CAR_HEADING(carSA, -120.0);
				WAIT( 10 );
				MARK_MODEL_AS_NO_LONGER_NEEDED(BloobM2);
				MARK_CAR_AS_NO_LONGER_NEEDED(&carSA);
				spawn_blood = 1;
			}
			else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -621.291, 1735.546, 1.0, -721.291, 1811.662, 50.04, 0 )) && (spawn_blood == 1))//проверка игрок в зоне загрузки автомобиля
			{
				spawn_blood = 0;
			}
		}
		//============================== Спавн самой быстрой лодки ======================================
		if (G_COKERUN > 0)
		{
			if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -88.241, -1031.361, -2.0, -213.241, -931.361, 52.0, 0 )) && (spawnF == 0))
			{
				uint BoatM = MODEL_SQUALO;// самая быстрая лодка
				REQUEST_MODEL(BoatM);
				while (!HAS_MODEL_LOADED(BoatM)) WAIT(0);
				CREATE_CAR(BoatM, -150.741, -981.361, 1.685, &boat, TRUE);
				SET_CAR_HEADING(boat, -112.96);
				WAIT(10);
				MARK_MODEL_AS_NO_LONGER_NEEDED(BoatM);//выгружаем модель
				MARK_CAR_AS_NO_LONGER_NEEDED(&boat);//выгружаем модель машины(в последствии машина изчезнет)
				spawnF = 1;
			}
			else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -88.241, -1031.361, -2.0, -213.241, -931.361, 52.0, 0 )) && (spawnF == 1))
			{
				spawnF = 0;
			}
		}
		//============================== Спавн вертолёта Макерик на особняке ======================================
		if (G_PROTECT > 0)
		{
			if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 119.484, -90.103, 27.921, -30.516, 9.897, 77.921, 0 )) && (spawnM == 0))
			{
				uint heliM2 = MODEL_MAVERICK;// Макерик
				REQUEST_MODEL(heliM2);
				while (!HAS_MODEL_LOADED(heliM2)) WAIT(0);
				CREATE_CAR(heliM2, 41.5106, -40.103, 34.6007, &maver, TRUE);
				SET_CAR_HEADING(maver, 0.0);
				WAIT(10);
				MARK_MODEL_AS_NO_LONGER_NEEDED(heliM2);//выгружаем модель
				MARK_CAR_AS_NO_LONGER_NEEDED(&maver);//выгружаем модель машины(в последствии машина изчезнет)
				spawnM = 1;
			}
			else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 119.484, -90.103, 27.921, -30.516, 9.897, 77.921, 0 )) && (spawnM == 1))
			{
				spawnM = 0;
			}
		}
		//============================== Спавн вертолётов Sparrow  ======================================
		
		/*rebusx: переделал здесь. Порождение вертолётов теперь прописано в .wpl-файлах, как обычного транспорта на карте*/
		
		float sparr1_x = 461.4463;
		float sparr1_y = -778.7614;
		float sparr1_z = 11.4712;
		float sparr2_x = 808.8450;
		float sparr2_y = 865.9194;
		float sparr2_z = 6.5155;
		float sparr3_x = -453.5938;
		float sparr3_y = 769.5693;
		float sparr3_z = 8.9773;
		if (G_DIAZ >= 9)
		{
			if (spawnS1 == SPAWN_STATE_DISABLED || spawnS1 == SPAWN_STATE_DISABLED_FROM_START)
			{
				SET_CAR_GENERATORS_ACTIVE_IN_AREA(sparr1_x - 10, sparr1_y - 10, sparr1_z - 10, sparr1_x + 10, sparr1_y + 10, sparr1_z + 10, 1);
				WAIT(0);
				spawnS1 = SPAWN_STATE_ENABLED;
			}
			if (spawnS2 == SPAWN_STATE_DISABLED || spawnS2 == SPAWN_STATE_DISABLED_FROM_START)
			{
				SET_CAR_GENERATORS_ACTIVE_IN_AREA(sparr2_x - 10, sparr2_y - 10, sparr2_z - 10, sparr2_x + 10, sparr2_y + 10, sparr2_z + 10, 1);
				WAIT(0);
				spawnS2 = SPAWN_STATE_ENABLED;
			}
			if (spawnS3 == SPAWN_STATE_DISABLED || spawnS3 == SPAWN_STATE_DISABLED_FROM_START)
			{
				SET_CAR_GENERATORS_ACTIVE_IN_AREA(sparr3_x - 10, sparr3_y - 10, sparr3_z - 10, sparr3_x + 10, sparr3_y + 10, sparr3_z + 10, 1);
				WAIT(0);
				spawnS3 = SPAWN_STATE_ENABLED;
			}
		}
		else
		{
			if (spawnS1 == SPAWN_STATE_DISABLED_FROM_START || spawnS1 == SPAWN_STATE_ENABLED)
			{
				SET_CAR_GENERATORS_ACTIVE_IN_AREA(sparr1_x - 10, sparr1_y - 10, sparr1_z - 10, sparr1_x + 10, sparr1_y + 10, sparr1_z + 10, 0);
				REMOVE_CARS_FROM_GENERATORS_IN_AREA(sparr1_x - 10, sparr1_y - 10, sparr1_z - 10, sparr1_x + 10, sparr1_y + 10, sparr1_z + 10);
				WAIT(0);
				spawnS1 = SPAWN_STATE_DISABLED;
			}
			if (spawnS2 == SPAWN_STATE_DISABLED_FROM_START || spawnS2 == SPAWN_STATE_ENABLED)
			{
				SET_CAR_GENERATORS_ACTIVE_IN_AREA(sparr2_x - 10, sparr2_y - 10, sparr2_z - 10, sparr2_x + 10, sparr2_y + 10, sparr2_z + 10, 0);
				REMOVE_CARS_FROM_GENERATORS_IN_AREA(sparr2_x - 10, sparr2_y - 10, sparr2_z - 10, sparr2_x + 10, sparr2_y + 10, sparr2_z + 10);
				WAIT(0);
				spawnS2 = SPAWN_STATE_DISABLED;
			}
			if (spawnS3 == SPAWN_STATE_DISABLED_FROM_START || spawnS3 == SPAWN_STATE_ENABLED)
			{
				SET_CAR_GENERATORS_ACTIVE_IN_AREA(sparr3_x - 10, sparr3_y - 10, sparr3_z - 10, sparr3_x + 10, sparr3_y + 10, sparr3_z + 10, 0);
				REMOVE_CARS_FROM_GENERATORS_IN_AREA(sparr3_x - 10, sparr3_y - 10, sparr3_z - 10, sparr3_x + 10, sparr3_y + 10, sparr3_z + 10);
				WAIT(0);
				spawnS3 = SPAWN_STATE_DISABLED;
			}
		}
		
		float sparr4_x = -136.1451;
		float sparr4_y = 1384.0923;
		float sparr4_z = 17.8402;
		if (G_PRON >= 5)
		{
			if (spawnS4 == SPAWN_STATE_DISABLED || spawnS4 == SPAWN_STATE_DISABLED_FROM_START)
			{
				SET_CAR_GENERATORS_ACTIVE_IN_AREA(sparr4_x - 10, sparr4_y - 10, sparr4_z - 10, sparr4_x + 10, sparr4_y + 10, sparr4_z + 10, 1);
				WAIT(0);
				spawnS4 = SPAWN_STATE_ENABLED;
			}
		}
		else
		{
			if (spawnS4 == SPAWN_STATE_DISABLED_FROM_START || spawnS4 == SPAWN_STATE_ENABLED)
			{
				SET_CAR_GENERATORS_ACTIVE_IN_AREA(sparr4_x - 10, sparr4_y - 10, sparr4_z - 10, sparr4_x + 10, sparr4_y + 10, sparr4_z + 10, 0);
				REMOVE_CARS_FROM_GENERATORS_IN_AREA(sparr4_x - 10, sparr4_y - 10, sparr4_z - 10, sparr4_x + 10, sparr4_y + 10, sparr4_z + 10);
				WAIT(0);
				spawnS4 = SPAWN_STATE_DISABLED;
			}
		}

		//============================== Спавн бонусов за пакеты  ======================================
		if (G_PACKET >= 8)// спавн Спероу у осабняка
		{
			if ((IS_CHAR_IN_AREA_2D( GetPlayerPed(), 114.383, -152.474, -5.617, -62.474, 0 )) && (spawnS5 == 0))
			{
				uint heliM = MODEL_SEASPARROW;// Вертолёт Sparrow
				REQUEST_MODEL(heliM);
				while (!HAS_MODEL_LOADED(heliM)) WAIT(0);
				CREATE_CAR(heliM, 54.3835, -99.0029, 4.90576, &Sparrow, TRUE);
				SET_CAR_HEADING(Sparrow, 0.0);
				WAIT(10);
				MARK_MODEL_AS_NO_LONGER_NEEDED(heliM);//выгружаем модель
				MARK_CAR_AS_NO_LONGER_NEEDED(&Sparrow);//выгружаем модель машины(в последствии машина изчезнет)
				spawnS5 = 1;
			}
			else if ((!IS_CHAR_IN_AREA_2D( GetPlayerPed(), 114.383, -152.474, -5.617, -62.474, 0 )) && (spawnS5 == 1))
			{
				spawnS5 = 0;
			}
		}
		if (G_PACKET >= 10)// спавн Хантер в Вашингтоне
		{
			if ((IS_CHAR_IN_AREA_2D( GetPlayerPed(), 420.336, -1114.135, 320.336, -1014.135, 0 )) && (spawnH == 0))
			{
				uint heliM = MODEL_BUZZARD;// Вертолёт Хантер
				REQUEST_MODEL(heliM);
				while (!HAS_MODEL_LOADED(heliM)) WAIT(0);
				CREATE_CAR(heliM, 362.736, -1074.04, 6.80173, &Sparrow, TRUE);
				SET_CAR_HEADING(Sparrow, 0.0);
				WAIT(10);
				MARK_MODEL_AS_NO_LONGER_NEEDED(heliM);//выгружаем модель
				MARK_CAR_AS_NO_LONGER_NEEDED(&Sparrow);//выгружаем модель машины(в последствии машина изчезнет)
				spawnH = 1;
			}
			else if ((!IS_CHAR_IN_AREA_2D( GetPlayerPed(), 420.336, -1114.135, 320.336, -1014.135, 0 )) && (spawnH == 1))
			{
				spawnH = 0;
			}
		}

		//--- копы игнорят в зоне службы доставки
		if ((cop_on == 1) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 775.386, 172.246, 2.743, 695.386, 268.246, 37.743, 0 )))
		{
			SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 1);
			cop_on = 0;
		}
		else if ((cop_on == 0) && (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 775.386, 172.246, 2.743, 695.386, 268.246, 37.743, 0 )))
		{
			SET_POLICE_IGNORE_PLAYER(GetPlayerIndex(), 0);
			cop_on = 1;
		}
		// ----------------------------------- БОНУСЫ -----------------------------------
        while ((G_MEDIC == 1) && (run_on == 0)) // бесконечный бег
	    {
		    SET_PLAYER_NEVER_GETS_TIRED(GetPlayerIndex(), 1);
			run_on = 1;
			//G_MEDIC = 2;
		}
		while ((G_COPCAR == 1) && (arm_on == 0)) // 150 брони
	    {
			INCREASE_PLAYER_MAX_ARMOUR(GetPlayerIndex(), 50);
		    arm_on = 1;
		    //G_COPCAR = 2;
	    }			
		uint timer_value;
		GET_GAME_TIMER(&timer_value);
		//if ((G_FIRE == 1) && (fire_on == 0)) // Iaiaoii?iinou
		if (G_FIRE == 1 && timer_value > time_fireproof_check) // Iaiaoii?iinou
		{
			//MAKE_PLAYER_FIRE_PROOF(GetPlayerIndex(), 1);
			SET_CHAR_PROOFS(GetPlayerPed(), 0, 1, 0, 0, 0);	/*rebusx: oae ?aaioaao*/
			time_fireproof_check = timer_value + 5000;
			//fire_on = 1;
			//G_FIRE = 2;
		}
	    while ((G_PIZZA == 1) && (heal_on == 0)) // 150 Здоровья
		{
			INCREASE_PLAYER_MAX_HEALTH(GetPlayerIndex(), 50);
			heal_on = 1;
		    //G_PIZZA = 2;
		}			
		//===================== гидвавлика тут =====================
		if (G_TAXI == 1) // Гидравлика на такси
		{
			if ((IS_CHAR_IN_TAXI(GetPlayerPed())) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_ROM)))
			{
				if (in_taxi == 0)
				{
					STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &carhidra);
					in_taxi = 1;
				}
				if (IS_PLAYER_PRESSING_HORN(0))// проверка "игрок посигналил"
				{
					if (IS_VEHICLE_ON_ALL_WHEELS(carhidra))
					{
						APPLY_FORCE_TO_CAR( carhidra, 1, 0, 0, 4.301, 0.0, 0.0, 0.0, 1, 1, 1, 1 );
					}
				}
			}
			else
			{
				if (in_taxi == 1)
				{
					in_taxi = 0;
				}
			}
		}
		if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_VOODOO))
		{
			if (in_voodoo == 0)
			{
				STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &carhidra);
				in_voodoo = 1;
			}
			if (IS_VEHICLE_ON_ALL_WHEELS(carhidra))
			{
				if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(72)) // если нажата "nam8"
				{
					APPLY_FORCE_TO_CAR( carhidra, 1, 0, 0, 1.801, 0.0, 1.801, 0.0, 1, 1, 1, 1 );
				}
				else if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(80)) // если нажата "nam2"
				{
					APPLY_FORCE_TO_CAR( carhidra, 1, 0, 0, 1.801, 0.0, -1.801, 0.0, 1, 1, 1, 1 );
				}
				else if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(77))// если нажата "nam6"
				{
					APPLY_FORCE_TO_CAR( carhidra, 1, 0, 0, 1.301, 1.801, 0.0, 1.801, 1, 1, 1, 1 );
				}
				else if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(75)) // если нажата "nam4"
				{
					APPLY_FORCE_TO_CAR( carhidra, 1, 0, 0, 1.301, -1.301, 0.0, -1.301, 1, 1, 1, 1 );
				}
				else if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(76)) // если нажата "nam5"
				{
					APPLY_FORCE_TO_CAR( carhidra, 1, 0, 0, 3.301, 0.0, 0.0, 0.0, 1, 1, 1, 1 );
				}
			}
		}
		else
		{
			if (in_voodoo == 1)
			{
				in_voodoo = 0;
			}
		}

		// ----------------------------------- МАГАЗИНЫ -----------------------------------
		if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -390.224, -135.368, -440.224, -85.368, 0)) //Doughnut Shop (Havana)
		{
			PedX = -425.312;
			PedY = -101.683;
			PedZ = 5.36331;
			PedR = 0.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -716.185, -105.635, -766.185, -55.635, 0)) //Cafe Robina (Havana)
		{
			PedX = -736.09;
			PedY = -84.6355;
			PedZ = 5.78244;
			PedR = -85.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -725.737, 179.159, -775.737, 229.159, 0)) //Laundromat (Havana)
		{
			PedX = -762.125;
			PedY = 208.565;
			PedZ = 4.88992;
			PedR = -85.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -725.737, 179.159, -775.737, 229.159, 0)) //Laundromat (Havana)
		{
			PedX = -762.125;
			PedY = 208.565;
			PedZ = 4.88992;
			PedR = -85.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -394.499, 423.496, -444.499, 473.496, 0)) //Ryton Aide Pharmacy (Haiti)
		{
			PedX = -414.661;
			PedY = 458.586;
			PedZ = 5.49698;
			PedR = -40.0;
			GET_TIME_OF_DAY(&hours_s, &minutes_s);
			if (hours_s < 5)
			{
				James = 1;
			}
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -377.666, 1258.43, -427.666, 1308.43, 0)) //Pharmacy (Downtown)
		{
			PedX = -399.394;
			PedY = 1273.61;
			PedZ = 5.22946;
			PedR = -90.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -406.95, 1358.411, -456.95, 1408.411, 0)) //Jewelry Store#3 (Downtown)
		{
			PedX = -423.353;
			PedY = 1380.43;
			PedZ = 5.32183;
			PedR = -90.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), 847.987, 716.072, 797.987, 766.072, 0)) //Jewelry Store#1 (Vice Point)
		{
			PedX = 814.79;
			PedY = 740.053;
			PedZ = 5.32183;
			PedR = 85.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), 832.881, 1262.734, 782.881, 1312.734, 0)) //Dispensary Plus (Vice Point)
		{
			PedX = 817.386;
			PedY = 1290.32;
			PedZ = 5.6715;
			PedR = 0.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), 906.426, 1293.375, 856.426, 1343.375, 0)) //Corner Store (Vice Point)
		{
			PedX = 882.698;
			PedY = 1317.71;
			PedZ = 6.90617;
			PedR = 180.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 817.163, 1627.627, 18.425, 778.675, 1671.675, 24.705, 0 )) //Music Store (Vice Point)
		{
			PedX = 785.558;
			PedY = 1647.52;
			PedZ = 19.3279;
			PedR = 145.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 875.982, 1548.667, 12.127, 828.268, 1601.061, 18.406, 0 )) //Gash "floor 1" (Vice Point)
		{
			PedX = 855.131;
			PedY = 1570.7;
			PedZ = 12.9082;
			PedR = -55.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 875.982, 1548.667, 18.466, 828.268, 1601.061, 24.705, 0 )) //Gash "floor 2" (Vice Point)
		{
			PedX = 855.131;
			PedY = 1570.7;
			PedZ = 19.2472;
			PedR = -55.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), 917.595, 1715.72, 867.595, 1765.72, 0)) //Jewelry Store#2 (Vice Point)
		{
			PedX = 900.888;
			PedY = 1741.61;
			PedZ = 12.9487;
			PedR = -135.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), 887.671, 584.821, 837.671, 634.821, 0)) //Pizza #1 (Vice Point)
		{
			Pizza = 1;
			PedX = 852.456;
			PedY = 620.24;
			PedZ = 5.16551;
			PedR = 35.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -593.688, 590.265, -643.688, 640.265, 0)) //Pizza #2 (Haiti)
		{
			Pizza = 1;
			PedX = -608.372;
			PedY = 615.234;
			PedZ = 5.5641;
			PedR = -90.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -434.69, 1304.743, -484.69, 1354.743, 0)) //Pizza #3 (Downtown)
		{
			Pizza = 1;
			PedX = -469.844;
			PedY = 1331.57;
			PedZ = 5.35378;
			PedR = 80.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 897.988, 1620.541, 12.127, 842.516, 1655.051, 18.406, 0 )) //HotDog #1 (Mall)
		{
			trigger = 1;
			Pizza = 1;
			PedX = 869.753;
			PedY = 1638.69;
			PedZ = 13.21;
			PedR = 135.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 897.981, 1659.243, 12.127, 847.606, 1694.092, 18.406, 0 )) //HotDog #2 (Mall)
		{
			trigger = 1;
			Pizza = 1;
			PedX = 871.064;
			PedY = 1675.66;
			PedZ = 13.165;
			PedR = 45.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 833.619, 1663.809, 12.127, 782.647, 1698.658, 18.406, 0 )) //HotDog #3 (Mall)
		{
			trigger = 1;
			Pizza = 1;
			PedX = 810.264;
			PedY = 1680.68;
			PedZ = 13.5298;
			PedR = -5.0;
			create_shops();
		}

		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -511.656, -175.374, -561.656, -125.374, 0)) //Screw This (Havana)
		{
			Tools = 1;
			PedX = -533.581;
			PedY = -160.29;
			PedZ = 5.26489;
			PedR = -85.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), 659.673, 24.831, 609.673, 74.831, 0)) //Bunch of Tools (Washington Beach)
		{
			Tools = 2;
			PedX = 636.332;
			PedY = 59.2133;
			PedZ = 4.97102;
			PedR = 0.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 829.477, 1602.7, 12.127, 791.078, 1644.194, 18.406, 0 )) //Hardware Store (Mall)
		{
			trigger = 2;
			Tools = 3;
			PedX = 796.299;
			PedY = 1610.4;
			PedZ = 13.0615;
			PedR = 179.0;
			create_shops();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), 404.044, -982.104, 354.044, -916.243, 0)) //Ammu-Nation#1 (Washington Beach)
		{
			Ammunition = 1;
			PedX = 369.825;
			PedY = -949.315;
			PedZ = 4.43197;
			PedR = 175.0;
			ammu_nation();
		}
		else if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -217.805, 1703.571, -267.805, 1753.571, 0)) //Ammu-Nation#2 (Downtown)
		{
			Ammunition = 2;
			PedX = -244.787;
			PedY = 1737.22;
			PedZ = 5.01206;
			PedR = 90.0;
			ammu_nation();
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 827.01, 1563.613, 12.127, 792.244, 1601.332, 18.406, 0 )) //Ammu-Nation#3 (Mall)
		{
			trigger = 3;
			Ammunition = 3;
			PedX = 798.101;
			PedY = 1588.29;
			PedZ = 13.1281;
			PedR = 180.0;
			ammu_nation();
		}
	}
}

void hide_unused_stats(void)
{
	// GENERAL
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_REPLAYS_USED);

	// VEHICLES
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_MILES_BY_TRAIN);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_MILES_AS_TAXI_PASSENGER);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_HELICOPTER_TOURS_TAKEN);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_TAXIS_HAILED);

	// MONEY
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SPENT_BUYING_CLOTHES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SPENT_IN_BARS_AND_CLUBS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SPENT_ON_PROSTITUTES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_GIVEN_TO_TRAMPS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SPENT_ON_VENDORS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SPENT_ON_BINOCULARS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SPENT_ON_DATES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_MOST_SPENT_ON_A_DATE);

	// PLAYER
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_TIMES_GOT_DRUNK);

	// SCORE
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_POOL_WINS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_POOL_DEFEATS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_POOL_PLAYED_TIME);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_POOL_CLEARANCES_FROM_BREAK);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_DARTS_WINS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_DARTS_DEFEATS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_DARTS_180S_HIT);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_DARTS_BULLSEYE);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_DARTS_SHORTEST_CHECK_OUT);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_DARTS_TIME_PLAYED);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_BOWLING_HIGH_SCORE);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_BOWLING_WINS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_BOWLING_DRAWS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_BOWLING_DEFEATS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_BOWLING_SPARES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_BOWLING_PERFECTS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_BOWLING_STRIKES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_BOWLING_TIME_PLAYED);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SOUTH_BROKER_WINS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SOUTH_BROKER_RACES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SOUTH_BROKER_RECORD);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_AIRPORT_RUN_WINS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_AIRPORT_RUN_RACES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_AIRPORT_RUN_RECORD);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_DUKES_BOULEVARD_WINS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_DUKES_BOULEVARD_RACES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_DUKES_BOULEVARD_RECORD);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SOUTH_ALGONQUIN_WINS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SOUTH_ALGONQUIN_RACES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SOUTH_ALGONQUIN_RECORD);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_STAR_JUNCTION_WINS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_STAR_JUNCTION_RACES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_STAR_JUNCTION_RECORD);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_ROAD_TO_BOHAN_WINS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_ROAD_TO_BOHAN_RACES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_ROAD_TO_BOHAN_RECORD);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_NORTH_ALDERNEY_WINS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_NORTH_ALDERNEY_RACES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_NORTH_ALDERNEY_RECORD);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_ELEVATED_WINS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_ELEVATED_RACES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_ELEVATED_RECORD);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SOUTH_ALDERNEY_WINS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SOUTH_ALDERNEY_RACES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SOUTH_ALDERNEY_RECORD);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_QUB3D_HIGH_SCORE);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_MOST_WANTED_COMPLETED);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_PIGEONS_EXTERMINATED);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_DRUG_PACKAGES_DELIVERED);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_RANDOM_CHARACTERS_MET);

	// MISC
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_TIME_SPENT_ON_INTERNET);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_EMAILS_RECEIVED);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_EMAILS_SENT);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_CALLS_MADE_FROM_PHONE);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_TEXTS_RECEIVED);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_PHOTOS_TAKEN);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_TOTAL_DATES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SUCCESSFUL_DATES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_BAD_DATES);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SCORED_WITH_GIRL);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_GIRLS_DUMPED);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_PROSTITUTE_VISITS);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_TRAMPS_GIVEN_MONEY_TO);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_HOTDOGS_EATEN);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_BURGERS_EATEN);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_NUTS_EATEN);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_BINOCULARS_USED);
	SET_STAT_FRONTEND_NEVER_VISIBLE(STAT_SODA_DRUNK);
}

void main(void)
{
	hide_unused_stats();
	global_world();
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
