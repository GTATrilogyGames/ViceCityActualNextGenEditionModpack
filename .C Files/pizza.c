#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
#include "mission_passed.h"

#include "peds_hashes.h"	/*rebusx: чтобы случайно выбирать педов (получателей)*/


#define CONTROLLER_DPAD_UP	8


int picked_locations[10];	/*rebusx: для разбрасывания получателей по карте*/

bool pizza_flying = 0;
Object flying_pizza_object;
bool *current_cust_cr_flag;
Ped *current_cust;
Blip current_cust_blip;

uint ObjM1;
Car moped;
Object pizza_box_var;
Blip ped1_blip, ped2_blip, ped3_blip, ped4_blip, ped5_blip, ped6_blip, ped7_blip, ped8_blip, ped9_blip, ped10_blip, pizza_shop_blip, moped_blip;

int customer1_created, customer2_created, customer3_created, customer4_created, customer5_created, customer6_created, customer7_created, customer8_created, customer9_created, customer10_created;
Ped customer1, customer2, customer3, customer4, customer5, customer6, customer7, customer8, customer9, customer10;

int fon, textur;
int restaur_zone, mission_lvl, random_cord, random_heading, delivered_in_this_order, have_pizzas, time_m, time_s, random_speech, not_on_moped, pizza_throw_help1, pizza_throw_help2;
float PedX, PedY, PedZ, ped_coord_x, ped_coord_y, ped_coord_z, pizza_shopx, pizza_shopy, pizza_shopz;
float px, py, pz, pr;


void setup_draw_text(void)
{
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.156, 0.267);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
	return;
}

void setup_draw_value(void)
{
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.26, 0.445);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
	return;
}

void clear_all_customers()
{
	if (customer1 != INVALID_HANDLE)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&customer1);
	}
	if (customer2 != INVALID_HANDLE)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&customer2);
	}
	if (customer3 != INVALID_HANDLE)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&customer3);
	}
	if (customer4 != INVALID_HANDLE)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&customer4);
	}
	if (customer5 != INVALID_HANDLE)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&customer5);
	}
	if (customer6 != INVALID_HANDLE)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&customer6);
	}
	if (customer7 != INVALID_HANDLE)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&customer7);
	}
	if (customer8 != INVALID_HANDLE)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&customer8);
	}
	if (customer9 != INVALID_HANDLE)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&customer9);
	}
	if (customer10 != INVALID_HANDLE)
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&customer10);
	}
}

void mission_cleanup_pizza(void)
{
	clear_all_customers();
	SET_CAR_GENERATORS_ACTIVE_IN_AREA(pizza_shopx - 10, pizza_shopy - 10, pizza_shopz - 10, pizza_shopx + 10, pizza_shopy + 10, pizza_shopz + 10, 1);	/*rebusx: включить создание мопеда на точке*/
	WAIT(0);
	if (flying_pizza_object != INVALID_HANDLE)
	{
		MARK_OBJECT_AS_NO_LONGER_NEEDED(&flying_pizza_object);
	}
	REMOVE_BLIP(ped1_blip);
	REMOVE_BLIP(ped2_blip);
	REMOVE_BLIP(ped3_blip);
	REMOVE_BLIP(ped4_blip);
	REMOVE_BLIP(ped5_blip);
	REMOVE_BLIP(ped6_blip);
	REMOVE_BLIP(ped7_blip);
	REMOVE_BLIP(ped8_blip);
	REMOVE_BLIP(ped9_blip);
	REMOVE_BLIP(ped10_blip);
	REMOVE_BLIP(pizza_shop_blip);
	REMOVE_BLIP(moped_blip);
	MARK_CAR_AS_NO_LONGER_NEEDED(&moped);//выгружаем модель машины(в последствии машина изчезнет)
	MARK_MODEL_AS_NO_LONGER_NEEDED(ObjM1);
	SET_PLAYER_CAN_DO_DRIVE_BY(GetPlayerIndex(), 1);
	TERMINATE_THIS_SCRIPT();
}

void mission_failed_pizza(void)
{
	if (G_PIZZA == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
	}
	MissionFailed();
	mission_cleanup_pizza();
}

void text_ped_dead(void)
{
	PRINT_NOW("PIZ1_07", 5000, 1);	//You killed the customer! You're fired.
}

void help_text(void)
{
	if (pizza_throw_help2 == 0)
	{
		PRINT_HELP("PIZ1_96");	//Press the ~h~~k~~INPUT_ATTACK~ ~w~to throw pizza to the customer.
		pizza_throw_help2 = 1;
	}
	else if (pizza_throw_help2 == 1)
	{
		if ( TIMERA() > 5000 )
		{
			SETTIMERA(0); //сбрасываем таймер 
			pizza_throw_help2 = 0;
		}
	}
}

void create_new_pizza()
{
	CREATE_OBJECT_NO_OFFSET(pizza_box_1, 5.0, 5.0, -5.0, &pizza_box_var, 1);
	SET_OBJECT_COLLISION(pizza_box_var, 1);
	SET_OBJECT_DYNAMIC(pizza_box_var, 1);
}

void pizza_throw()
{
	GET_CHAR_COORDINATES(GetPlayerPed(), &px, &py, &pz);
	SET_OBJECT_COORDINATES(pizza_box_var, px, py, pz + 1.0);
	WAIT(0);	/*rebusx: обязательно*/
	/*GET_CHAR_HEADING(GetPlayerPed(), &pr);
	pr -= 90.0;
	px += COS(pr) * 0.7;
	py += SIN(pr) * 0.7;
	GET_GROUND_Z_FOR_3D_COORD(px, py, pz, &pz);*/
	float vectX = PedX - px;
	float vectY = PedY - py;
	APPLY_FORCE_TO_OBJECT(pizza_box_var, 1, vectX * 2, vectY * 2, 1.0, 0.0, 0.0, 0.0, 1, 0, 1, 1);
	flying_pizza_object = pizza_box_var;
	create_new_pizza();
}

int check_pizza_end_flying()
{
	float veloc_x, veloc_y, veloc_z;
	GET_OBJECT_VELOCITY(flying_pizza_object, &veloc_x, &veloc_y, &veloc_z);
	veloc_x = ABSF(veloc_x);
	veloc_y = ABSF(veloc_y);
	veloc_z = ABSF(veloc_z);
	if (veloc_x < 0.3 && veloc_y < 0.3 && veloc_z < 0.3)
	{
		GET_OBJECT_COORDINATES(flying_pizza_object, &px, &py, &pz);
		MARK_OBJECT_AS_NO_LONGER_NEEDED(&flying_pizza_object);
		pizza_flying = 0;
		return 1;
	}
	return 0;
}

void play_speech(char *str1, char *line)
{
	NEW_SCRIPTED_CONVERSATION();
	ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
	ADD_LINE_TO_CONVERSATION(0, str1, line, 0, 0);
	START_SCRIPT_CONVERSATION(1, 1);
}

void set_random_speech(void)
{
	GENERATE_RANDOM_INT_IN_RANGE(1, 19, &random_speech);
	if (random_speech == 1)
	{
		play_speech("B2_CB", "PIZ1_13");
	}
	else if (random_speech == 2)
	{
		play_speech("B2_CF", "PIZ1_14");
	}
	else if (random_speech == 3)
	{
		play_speech("B2_CG", "PIZ1_15");
	}	
	else if (random_speech == 4)
	{
		play_speech("B2_CL", "PIZ1_16");
	}
	else if (random_speech == 5)
	{
		play_speech("B2_CO", "PIZ1_17");
	}
	else if (random_speech == 6)
	{
		play_speech("B2_CT", "PIZ1_18");
	}
	else if (random_speech == 7)
	{
		play_speech("B2_CV", "PIZ1_19");
	}
	else if (random_speech == 8)
	{
		play_speech("B2_CW", "PIZ1_20");
	}
	else if (random_speech == 9)
	{
		play_speech("B2_DB", "PIZ1_21");
	}
	else if (random_speech == 10)
	{
		play_speech("B2_DE", "PIZ1_22");
	}
	else if (random_speech == 11)
	{
		play_speech("B2_DK", "PIZ1_23");
	}
	else if (random_speech == 12)
	{
		play_speech("B2_DL", "PIZ1_24");
	}
	else if (random_speech == 13)
	{
		play_speech("B2_DM", "PIZ1_25");
	}
	else if (random_speech == 14)
	{
		play_speech("B2_DQ", "PIZ1_26");
	}
	else if (random_speech == 15)
	{
		play_speech("B2_DX", "PIZ1_27");
	}
	else if (random_speech == 16)
	{
		play_speech("B2_FA", "PIZ1_28");
	}
	else if (random_speech == 17)
	{
		play_speech("B2_FG", "PIZ1_29");
	}
	else if (random_speech == 18)
	{
		play_speech("B2_FH", "PIZ1_30");
	}
	else if (random_speech == 19)
	{
		play_speech("B2_FL", "PIZ1_31");
	}
}


void dead_ped(void)
{
	if (customer1_created == 1)
	{
		if (IS_CHAR_DEAD(customer1))
		{
			text_ped_dead();
			mission_failed_pizza();
		}
	}
	if (customer2_created == 1)
	{
		if (IS_CHAR_DEAD(customer2))
		{
			text_ped_dead();
			mission_failed_pizza();
		}
	}
	if (customer3_created == 1)
	{
		if (IS_CHAR_DEAD(customer3))
		{
			text_ped_dead();
			mission_failed_pizza();
		}
	}
	if (customer4_created == 1)
	{
		if (IS_CHAR_DEAD(customer4))
		{
			text_ped_dead();
			mission_failed_pizza();
		}
	}
	if (customer5_created == 1)
	{
		if (IS_CHAR_DEAD(customer5))
		{
			text_ped_dead();
			mission_failed_pizza();
		}
	}
	if (customer6_created == 1)
	{
		if (IS_CHAR_DEAD(customer6))
		{
			text_ped_dead();
			mission_failed_pizza();
		}
	}
	if (customer7_created == 1)
	{
		if (IS_CHAR_DEAD(customer7))
		{
			text_ped_dead();
			mission_failed_pizza();
		}
	}
	if (customer8_created == 1)
	{
		if (IS_CHAR_DEAD(customer8))
		{
			text_ped_dead();
			mission_failed_pizza();
		}
	}
	if (customer9_created == 1)
	{
		if (IS_CHAR_DEAD(customer9))
		{
			text_ped_dead();
			mission_failed_pizza();
		}
	}
	if (customer10_created == 1)
	{
		if (IS_CHAR_DEAD(customer10))
		{
			text_ped_dead();
			mission_failed_pizza();
		}
	}
	return;
}

int deliver(bool *creation_flag, Ped *cust_var)
{
	if (*creation_flag == 0)
	{
		return 0;
	}
	GET_CHAR_COORDINATES(*cust_var,  &PedX, &PedY, &PedZ);
	if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), PedX, PedY, PedZ, 6.0, 6.0, 2.0, 1))
	{
		help_text();
		if (IS_CONTROL_PRESSED(2, 4))
		{
			if (have_pizzas)
			{
				pizza_throw();
				pizza_flying = 1;
				return 1;
			}
			else
			{
				//PRINT_NOW("PIZ1_33", 5000, 1);	//Return to the restaurant for more orders.
				PRINT_NOW("PIZ1_02", 5000, 1);	//~g~You have thrown all your pizzas, go back and get some more.
			}
		}
	}
	return 0;
}

void customer_get_pizza(bool *cust_creation_flag, Ped *cust_var, Blip cust_blip)
{
	TASK_GO_STRAIGHT_TO_COORD(*cust_var, px, py, pz, 4, -1);
	TASK_WANDER_STANDARD(*cust_var);
	REMOVE_BLIP(cust_blip);
	//MARK_CHAR_AS_NO_LONGER_NEEDED(cust_var);	/*rebusx: очистка сразу всех в конце уровня*/
	*cust_creation_flag = 0;
}


void check_not_on_moped()
{
	if (!IS_CHAR_IN_CAR(GetPlayerPed(), moped))
	{
		if (not_on_moped == 0)
		{
			ADD_BLIP_FOR_CAR(moped, &moped_blip);
			CHANGE_BLIP_SPRITE(moped_blip, BLIP_OBJECTIVE);
			CHANGE_BLIP_COLOUR(moped_blip, 19);
			CHANGE_BLIP_SCALE(moped_blip, 0.6);
			PRINT_NOW("PIZ1_11", 5000, 1);	//Hey! Get back on the bike! You have pizzas to deliver!
			not_on_moped = 1;
		}
	}
	else
	{
		if (not_on_moped == 1)
		{
			REMOVE_BLIP(moped_blip);
			not_on_moped = 0;
		}
	}
}


void timer()
{
	if (TIMERB() > 1000)
	{
		time_s -= 1;
		SETTIMERB( 0 );
	}
	if (time_s < 0)
	{
		time_m -= 1;
		time_s = 59;
	}
}


void draw_hud_and_checkp()
{
	DRAW_CHECKPOINT( pizza_shopx, pizza_shopy, pizza_shopz, 4.0, 160, 116, 209);//создание чекпойнт на координатах и его цвет
	DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
	DRAW_SPRITE( fon, 0.8765625, 0.7838, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.

	setup_draw_text();
	DISPLAY_TEXT(0.78815097, 0.73564852, "PIZ1_12");
	setup_draw_value();
	SET_TEXT_CENTRE(1);
	DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.72916666, "CP_TIME_ZERO", have_pizzas);

	setup_draw_text();
	DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
	setup_draw_value();
	SET_TEXT_CENTRE(1);
	if (time_m > 9)
	{
		DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_NOZERO", time_m);// минуты
	}
	else
	{
		DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", time_m);// минуты
	}
	setup_draw_value();
	DISPLAY_TEXT(0.9203125, 0.76954074, "CP_TIME_SEP");

	setup_draw_value();
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


void fail_states()
{
	dead_ped();
	if (IS_CAR_DEAD(moped))
	{
		CLEAR_PRINTS();
		PRINT_NOW("PIZ1_09", 5000, 1);	//~r~You destroyed our bike! You're fired.
		mission_failed_pizza();
	}
	else if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER())))
	{
		CLEAR_PRINTS();
		PRINT_NOW("PIZ1_32", 5000, 1);	//~r~Pizza's too hot to handle?
		mission_failed_pizza();
	}
	else if ((time_m == 0) && (time_s < 1))
	{
		CLEAR_PRINTS();
		PRINT_NOW("PIZ1_08", 5000, 1);	//~r~You are out of time. You're fired.
		mission_failed_pizza();
	}
	else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// игрок мёртв/арестован
	{
		CLEAR_PRINTS();
		mission_failed_pizza();
	}
}


void set_random_cord(void)//рандономайзер координат
{
	/*GENERATE_RANDOM_INT_IN_RANGE(1, 33, &random_cord);*/		/*rebusx: перенёс в "spawn_clients()"*/
	if (restaur_zone == 1)
	{
		if (random_cord == 1) ped_coord_x = 887.532, ped_coord_y = 761.333, ped_coord_z = 5.39392;
		else if (random_cord == 2) ped_coord_x = 917.407, ped_coord_y = 544.382, ped_coord_z = 5.07748;
		else if (random_cord == 3) ped_coord_x = 750.961, ped_coord_y = 422.827, ped_coord_z = 5.09734;
		else if (random_cord == 4) ped_coord_x = 923.361, ped_coord_y = 127.123, ped_coord_z = 5.06151;
		else if (random_cord == 5) ped_coord_x = 969.679, ped_coord_y = 937.108, ped_coord_z = 5.10474;
		else if (random_cord == 6) ped_coord_x = 826.375, ped_coord_y = 1189.05, ped_coord_z = 5.07446;
		else if (random_cord == 7) ped_coord_x = 707.429, ped_coord_y = 544.642, ped_coord_z = 5.15235;
		else if (random_cord == 8) ped_coord_x = 948.045, ped_coord_y = 1201.28, ped_coord_z = 5.281;
		else if (random_cord == 9) ped_coord_x = 734.799, ped_coord_y = -7.8874, ped_coord_z = 4.07915;
		else if (random_cord == 10) ped_coord_x = 790.101, ped_coord_y = -150.005, ped_coord_z = 4.27534;
		else if (random_cord == 11) ped_coord_x = 926.043, ped_coord_y = 369.475, ped_coord_z = 4.13004;
		else if (random_cord == 12) ped_coord_x = 640.047, ped_coord_y = 169.969, ped_coord_z = 4.73574;
		else if (random_cord == 13) ped_coord_x = 948.495, ped_coord_y = 676.721, ped_coord_z = 5.08392;
		else if (random_cord == 14) ped_coord_x = 907.889, ped_coord_y = 433.181, ped_coord_z = 4.76095;
		else if (random_cord == 15) ped_coord_x = 758.766, ped_coord_y = 939.491, ped_coord_z = 5.32192;
		else if (random_cord == 16) ped_coord_x = 910.553, ped_coord_y = 1099.17, ped_coord_z = 5.79144;
		else if (random_cord == 17) ped_coord_x = 955.893, ped_coord_y = 872.177, ped_coord_z = 5.08358;
		else if (random_cord == 18) ped_coord_x = 824.059, ped_coord_y = 75.3093, ped_coord_z = 4.1206;
		else if (random_cord == 19) ped_coord_x = 662.026, ped_coord_y = -151.119, ped_coord_z = 4.40624;
		else if (random_cord == 20) ped_coord_x = 901.715, ped_coord_y = -33.218, ped_coord_z = 5.03978;
		else if (random_cord == 21) ped_coord_x = 606.891, ped_coord_y = 47.2347, ped_coord_z = 5.12773;
		else if (random_cord == 22) ped_coord_x = 761.084, ped_coord_y = 782.761, ped_coord_z = 5.71017;
		else if (random_cord == 23) ped_coord_x = 803.391, ped_coord_y = 1069.51, ped_coord_z = 5.6672;
		else if (random_cord == 24) ped_coord_x = 866.363, ped_coord_y = 880.867, ped_coord_z = 5.69295;
		else if (random_cord == 25) ped_coord_x = 700.626, ped_coord_y = -32.195, ped_coord_z = 4.15679;
		else if (random_cord == 26) ped_coord_x = 720.978, ped_coord_y = 344.573, ped_coord_z = 5.62406;
		else if (random_cord == 27) ped_coord_x = 958.858, ped_coord_y = 487.593, ped_coord_z = 5.00521;
		else if (random_cord == 28) ped_coord_x = 747.093, ped_coord_y = 534.776, ped_coord_z = 5.06633;
		else if (random_cord == 29) ped_coord_x = 632.831, ped_coord_y = 39.5213, ped_coord_z = 5.54685;
		else if (random_cord == 30) ped_coord_x = 863.372, ped_coord_y = 1008.88, ped_coord_z = 5.73865;
		else if (random_cord == 31) ped_coord_x = 856.656, ped_coord_y = 100.624, ped_coord_z = 4.18156;
		else if (random_cord == 32) ped_coord_x = 745.488, ped_coord_y = 750.524, ped_coord_z = 5.35247;
		else if (random_cord == 33) ped_coord_x = 775.878, ped_coord_y = 205.896, ped_coord_z = 6.69808;
	}
	else if (restaur_zone == 2)
	{
		if (random_cord == 1) ped_coord_x = -563.515, ped_coord_y = 544.382, -14.598, ped_coord_z = 544.382, 5.16179;
		else if (random_cord == 2) ped_coord_x = -604.768, ped_coord_y = 544.382, 221.181, ped_coord_z = 544.382, 4.91013;
		else if (random_cord == 3) ped_coord_x = -580.889, ped_coord_y = 544.382, 738.401, ped_coord_z = 544.382, 5.32323;
		else if (random_cord == 4) ped_coord_x = -287.342, ped_coord_y = 544.382, 848.556, ped_coord_z = 544.382, 5.10759;
		else if (random_cord == 5) ped_coord_x = -301.879, ped_coord_y = 544.382, 777.216, ped_coord_z = 544.382, 5.29473;
		else if (random_cord == 6) ped_coord_x = -761.324, ped_coord_y = 544.382, 339.401, ped_coord_z = 544.382, 5.46329;
		else if (random_cord == 7) ped_coord_x = -557.771, ped_coord_y = 544.382, 435.381, ped_coord_z = 544.382, 4.71664;
		else if (random_cord == 8) ped_coord_x = -626.646, ped_coord_y = 544.382, 443.363, ped_coord_z = 544.382, 5.45495;
		else if (random_cord == 9) ped_coord_x = -325.131, ped_coord_y = 544.382, 661.935, ped_coord_z = 544.382, 5.16518;
		else if (random_cord == 10) ped_coord_x = -618.851, ped_coord_y = 544.382, 400.099, ped_coord_z = 544.382, 5.38091;
		else if (random_cord == 11) ped_coord_x = -542.317, ped_coord_y = 544.382, 286.871, ped_coord_z = 544.382, 4.7919;
		else if (random_cord == 12) ped_coord_x = -437.623, ped_coord_y = 544.382, 213.443, ped_coord_z = 544.382, 5.1851;
		else if (random_cord == 13) ped_coord_x = -587.044, ped_coord_y = 544.382, 179.984, ped_coord_z = 544.382, 5.04386;
		else if (random_cord == 14) ped_coord_x = -661.381, ped_coord_y = 544.382, -140.553, ped_coord_z = 544.382, 5.82063;
		else if (random_cord == 15) ped_coord_x = -562.755, ped_coord_y = 544.382, 101.579, ped_coord_z = 544.382, 5.05164;
		else if (random_cord == 16) ped_coord_x = -481.266, ped_coord_y = 544.382, 860.109, ped_coord_z = 544.382, 5.28982;
		else if (random_cord == 17) ped_coord_x = -629.171, ped_coord_y = 544.382, 517.616, ped_coord_z = 544.382, 5.42825;
		else if (random_cord == 18) ped_coord_x = -421.213, ped_coord_y = 544.382, -7.708, ped_coord_z = 544.382, 5.1047;
		else if (random_cord == 19) ped_coord_x = -777.752, ped_coord_y = 544.382, 119.431, ped_coord_z = 544.382, 4.92004;
		else if (random_cord == 20) ped_coord_x = -715.262, ped_coord_y = 544.382, -67.8823, ped_coord_z = 544.382, 5.50791;
		else if (random_cord == 21) ped_coord_x = -435.438, ped_coord_y = 544.382, 67.802, ped_coord_z = 544.382, 5.1326;
		else if (random_cord == 22) ped_coord_x = -512.526, ped_coord_y = 544.382, 652.409, ped_coord_z = 544.382, 3.44966;
		else if (random_cord == 23) ped_coord_x = -753.932, ped_coord_y = 544.382, -133.422, ped_coord_z = 544.382, 5.73674;
		else if (random_cord == 24) ped_coord_x = -446.734, ped_coord_y = 544.382, -112.935, ped_coord_z = 544.382, 5.38707;
		else if (random_cord == 25) ped_coord_x = -747.337, ped_coord_y = 544.382, 425.051, ped_coord_z = 544.382, 5.44635;
		else if (random_cord == 26) ped_coord_x = -504.452, ped_coord_y = 544.382, 615.02, ped_coord_z = 544.382, 3.92488;
		else if (random_cord == 27) ped_coord_x = -568.232, ped_coord_y = 544.382, -143.257, ped_coord_z = 544.382, 5.82969;
		else if (random_cord == 28) ped_coord_x = -681.451, ped_coord_y = 544.382, 159.137, ped_coord_z = 544.382, 5.01216;
		else if (random_cord == 29) ped_coord_x = -747.214, ped_coord_y = 544.382, 311.81, ped_coord_z = 544.382, 5.45036;
		else if (random_cord == 30) ped_coord_x = -541.271, ped_coord_y = 544.382, 572.427, ped_coord_z = 544.382, 4.76289;
		else if (random_cord == 31) ped_coord_x = -682.584, ped_coord_y = 544.382, 47.2127, ped_coord_z = 544.382, 5.01989;
		else if (random_cord == 32) ped_coord_x = -757.611, ped_coord_y = 544.382, 82.2386, ped_coord_z = 544.382, 5.00629;
		else if (random_cord == 33) ped_coord_x = -542.099, ped_coord_y = 544.382, 476.675, ped_coord_z = 544.382, 4.85845;
	}
	else if (restaur_zone == 3)
	{
		if (random_cord == 1) ped_coord_x = -247.424, ped_coord_y = 1263.22, ped_coord_z = 5.09121;
		else if (random_cord == 2) ped_coord_x = -616.936, ped_coord_y = 1778.63, ped_coord_z = 2.7557;
		else if (random_cord == 3) ped_coord_x = -148.147, ped_coord_y = 1659.05, ped_coord_z = 5.09701;
		else if (random_cord == 4) ped_coord_x = -238.346, ped_coord_y = 1988.15, ped_coord_z = 6.13007;
		else if (random_cord == 5) ped_coord_x = -258.52, ped_coord_y = 1641.68, ped_coord_z = 5.58668;
		else if (random_cord == 6) ped_coord_x = -327.158, ped_coord_y = 1294.39, ped_coord_z = 5.22404;
		else if (random_cord == 7) ped_coord_x = -360.104, ped_coord_y = 1104.95, ped_coord_z = 5.2138;
		else if (random_cord == 8) ped_coord_x = -329.328, ped_coord_y = 2005.75, ped_coord_z = 6.31973;
		else if (random_cord == 9) ped_coord_x = -413.345, ped_coord_y = 1582.97, ped_coord_z = 9.95649;
		else if (random_cord == 10) ped_coord_x = -238.087, ped_coord_y = 1514.41, ped_coord_z = 5.51341;
		else if (random_cord == 11) ped_coord_x = -171.743, ped_coord_y = 1187.77, ped_coord_z = 5.26635;
		else if (random_cord == 12) ped_coord_x = -385.593, ped_coord_y = 1695.78, ped_coord_z = 5.13744;
		else if (random_cord == 13) ped_coord_x = -198.053, ped_coord_y = 1866.96, ped_coord_z = 5.81208;
		else if (random_cord == 14) ped_coord_x = -362.008, ped_coord_y = 1920.32, ped_coord_z = 5.60745;
		else if (random_cord == 15) ped_coord_x = -578.239, ped_coord_y = 1863.16, ped_coord_z = 3.84059;
		else if (random_cord == 16) ped_coord_x = -71.4308, ped_coord_y = 1283.46, ped_coord_z = 4.81623;
		else if (random_cord == 17) ped_coord_x = -243.892, ped_coord_y = 1630.03, ped_coord_z = 5.51745;
		else if (random_cord == 18) ped_coord_x = -288.417, ped_coord_y = 1087.08, ped_coord_z = 5.22028;
		else if (random_cord == 19) ped_coord_x = -300.335, ped_coord_y = 1701.38, ped_coord_z = 5.22123;
		else if (random_cord == 20) ped_coord_x = -247.074, ped_coord_y = 1290.06, ped_coord_z = 5.13072;
		else if (random_cord == 21) ped_coord_x = -442.607, ped_coord_y = 1518.75, ped_coord_z = 5.14163;
		else if (random_cord == 22) ped_coord_x = -235.576, ped_coord_y = 1925.52, ped_coord_z = 5.98404;
		else if (random_cord == 23) ped_coord_x = -84.1095, ped_coord_y = 1260.39, ped_coord_z = 5.21499;
		else if (random_cord == 24) ped_coord_x = -136.804, ped_coord_y = 1207.66, ped_coord_z = 5.15906;
		else if (random_cord == 25) ped_coord_x = -246.131, ped_coord_y = 1473.1, ped_coord_z = 5.43976;
		else if (random_cord == 26) ped_coord_x = -330.165, ped_coord_y = 1853.27, ped_coord_z = 5.85905;
		else if (random_cord == 27) ped_coord_x = -228.939, ped_coord_y = 1290.08, ped_coord_z = 5.12999;
		else if (random_cord == 28) ped_coord_x = -435.128, ped_coord_y = 1671.96, ped_coord_z = 4.9982;
		else if (random_cord == 29) ped_coord_x = -310.277, ped_coord_y = 1727.85, ped_coord_z = 5.14213;
		else if (random_cord == 30) ped_coord_x = -450.338, ped_coord_y = 1844.12, ped_coord_z = 5.44753;
		else if (random_cord == 31) ped_coord_x = -454.034, ped_coord_y = 1896.8, ped_coord_z = 5.6254;
		else if (random_cord == 32) ped_coord_x = -140.712, ped_coord_y = 1685.4, ped_coord_z = 5.15328;
		else if (random_cord == 33) ped_coord_x = -37.0007, ped_coord_y = 1639.02, ped_coord_z = 5.3199;
	}
	GENERATE_RANDOM_INT_IN_RANGE(1, 360, &random_heading);
}

void spawn_1_client(Ped *cust_var, Blip *cust_blip)
{
	set_random_cord();
	//CREATE_RANDOM_CHAR( ped_coord_x, ped_coord_y, ped_coord_z, cust_var);	/*rebusx*/
	int randint;
	GENERATE_RANDOM_INT_IN_RANGE(PED_HASHES_MIN_INDEX, PED_HASHES_MAX_INDEX, &randint);
	REQUEST_MODEL(peds_hashes[randint]);
	while ( !HAS_MODEL_LOADED(peds_hashes[randint]) )
	{
		WAIT(0);
	}
	CREATE_CHAR(PED_TYPE_CIV_MALE, peds_hashes[randint], ped_coord_x, ped_coord_y, ped_coord_z, cust_var, 1);
	MARK_MODEL_AS_NO_LONGER_NEEDED(peds_hashes[randint]);
	SET_CHAR_HEADING(*cust_var, random_heading);
	ADD_BLIP_FOR_CHAR(*cust_var, cust_blip);
	CHANGE_BLIP_COLOUR(*cust_blip, 19);
	CHANGE_BLIP_SCALE(*cust_blip, 0.77999990);
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(*cust_blip, "PIZ_BL");
}

int location_already_picked(int index_with_cur_loc)
{
	int i;
	for (i = 0; i < index_with_cur_loc; ++i)
	{
		if (random_cord == picked_locations[i])
		{
			return 1;
		}
	}
	return 0;
}

void gener_unique_location(int index)
{
	while(1)
	{
		GENERATE_RANDOM_INT_IN_RANGE(1, 33, &random_cord);
		picked_locations[index] = random_cord;
		if (location_already_picked(index))
		{
			continue;
		}
		break;
	}
}

void spawn_clients(void)//создание клиентов
{
	int i;
	for (i = 0; i < 10; ++i)	/*rebusx: очистить массив запомненных положений*/
	{
		picked_locations[i] = -1;
	}
	i = 0;
	if ((customer1_created == 0) && (mission_lvl >= 1))
	{
		GENERATE_RANDOM_INT_IN_RANGE(1, 33, &random_cord);
		picked_locations[i] = random_cord;
		i++;
		spawn_1_client(&customer1, &ped1_blip);
		customer1_created = 1;
	}
	if ((customer2_created == 0) && (mission_lvl >= 2))
	{
		gener_unique_location(i);
		i++;
		spawn_1_client(&customer2, &ped2_blip);
		customer2_created = 1;
	}
	if ((customer3_created == 0) && (mission_lvl >= 3))
	{
		gener_unique_location(i);
		i++;
		spawn_1_client(&customer3, &ped3_blip);
		customer3_created = 1;
	}
	if ((customer4_created == 0) && (mission_lvl >= 4))
	{
		gener_unique_location(i);
		i++;
		spawn_1_client(&customer4, &ped4_blip);
		customer4_created = 1;
	}
	if ((customer5_created == 0) && (mission_lvl >= 5))
	{
		gener_unique_location(i);
		i++;
		spawn_1_client(&customer5, &ped5_blip);
		customer5_created = 1;
	}
	if ((customer6_created == 0) && (mission_lvl >= 6))
	{
		gener_unique_location(i);
		i++;
		spawn_1_client(&customer6, &ped6_blip);
		customer6_created = 1;
	}
	if ((customer7_created == 0) && (mission_lvl >= 7))
	{
		gener_unique_location(i);
		i++;
		spawn_1_client(&customer7, &ped7_blip);
		customer7_created = 1;
	}
	if ((customer8_created == 0) && (mission_lvl >= 8))
	{
		gener_unique_location(i);
		i++;
		spawn_1_client(&customer8, &ped8_blip);
		customer8_created = 1;
	}
	if ((customer9_created == 0) && (mission_lvl >= 9))
	{
		gener_unique_location(i);
		i++;
		spawn_1_client(&customer9, &ped9_blip);
		customer9_created = 1;
	}
	if ((customer10_created == 0) && (mission_lvl == 10))
	{
		gener_unique_location(i);
		i++;
		spawn_1_client(&customer10, &ped10_blip);
		customer10_created = 1;
	}
}


void get_new_order(int enable_speech)
{
	have_pizzas = 6;
	if (enable_speech)
	{
		set_random_speech();
	}
	time_m = 5;
	time_s = 0;
	delivered_in_this_order = 0;
	spawn_clients();
}


void main(void)
{
	WAIT(100);
	if (G_PIZZA == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);	
	}
	init_ped_hashes();	/*rebusx*/
	not_on_moped = 0;
	pizza_throw_help1 = 0;
	pizza_throw_help2 = 0;
	
	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT(0.5, 0.45, "PIZ1_A");//

		WAIT( 0 );
		if ( TIMERA() > 3000 )
		{
			break;
		}
	}
	LOAD_ADDITIONAL_TEXT("PIZZA", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	
	ObjM1 = pizza_box_1; // коробка пиццы
	REQUEST_MODEL(ObjM1);
	while (!HAS_MODEL_LOADED(ObjM1)) WAIT(0);
	create_new_pizza();

	if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STARJ"))
	{
		pizza_shopx = 844.6;
		pizza_shopy = 630.8;
		pizza_shopz = 5.4;
		restaur_zone = 1;
	}
	else if (IS_CHAR_IN_ZONE(GetPlayerPed(), "WILLI"))
	{
		pizza_shopx = -595.9; 
		pizza_shopy = 615.7;
		pizza_shopz = 5.7;
		restaur_zone = 2;
	}
	else if (IS_CHAR_IN_ZONE(GetPlayerPed(), "LTBAY"))
	{
		pizza_shopx = -475.0; 
		pizza_shopy = 1342.3;
		pizza_shopz = 5.5;	
		restaur_zone = 3;
	}
	ADD_BLIP_FOR_COORD(pizza_shopx, pizza_shopy, pizza_shopz, &pizza_shop_blip);//создаем иконку на радаре
	CHANGE_BLIP_SPRITE(pizza_shop_blip, BLIP_OBJECTIVE);
	CHANGE_BLIP_COLOUR(pizza_shop_blip, 5);
	CHANGE_BLIP_SCALE(pizza_shop_blip, 0.6);
	
	SET_CAR_GENERATORS_ACTIVE_IN_AREA(pizza_shopx - 10, pizza_shopy - 10, pizza_shopz - 10, pizza_shopx + 10, pizza_shopy + 10, pizza_shopz + 10, 0);	/*rebusx: отключить создание мопеда на точке*/

	PRINT("PIZ1_01", 7000, 1);
	PRINT("PIZ1_05", 7000, 1);
	PRINT_HELP("PIZ1_06");	//Press the ~h~~k~~PAD_LB~ ~w~when on the bike to cancel the mission.
	SETTIMERA(0); //сбрасываем таймер 
	SETTIMERB(0);

	SET_PLAYER_CAN_DO_DRIVE_BY(GetPlayerIndex(), 0);
	GET_CAR_CHAR_IS_USING(GetPlayerPed(), &moped);
	
	mission_lvl = 1;
	get_new_order(0);	/*rebusx: без озвучки*/
	
	bool this_order_done = 0;
	
	while (1)
	{
		WAIT(0);
		timer();
		draw_hud_and_checkp();
		check_not_on_moped();
		fail_states();
		
		if (pizza_throw_help1 == 0)
		{
			if ( TIMERA() > 5000 )
			{
				PRINT_HELP("PIZ1_96");	//Press the ~h~~k~~INPUT_ATTACK~ ~w~to throw pizza to the customer.
				pizza_throw_help1 = 1;
			}
		}
		
		if (pizza_flying)
		{
			if ( check_pizza_end_flying() )
			{
				customer_get_pizza(current_cust_cr_flag, current_cust, current_cust_blip);
				PLAY_AUDIO_EVENT( "FRONTEND_OTHER_RACE_321" );
				ADD_SCORE(GetPlayerIndex(), 10);
				INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 10);
				have_pizzas -= 1;
				delivered_in_this_order += 1;
				//if (mission_lvl == delivered_in_this_order)
				if (delivered_in_this_order >= mission_lvl)
				{
					//PRINT_NOW("PIZ1_02", 5000, 1);	//~g~You have thrown all your pizzas, go back and get some more.
					PRINT_NOW("PIZ1_33", 5000, 1);	//Return to the restaurant for more orders.
					this_order_done = 1;
				}
				else
				{	
					if (have_pizzas)
					{
						PRINT_NOW("PIZ1_34", 5000, 1);	//~g~Pizza delivered, here's your cash.
					}
					else
					{
						PRINT_NOW("PIZ1_02", 5000, 1);	//~g~You have thrown all your pizzas, go back and get some more.
					}
				}
			}
			else
			{
				continue;
			}
		}
		
		if (!this_order_done && IS_CHAR_IN_CAR(GetPlayerPed(), moped))
		{
			if (deliver(&customer1_created, &customer1))
			{
				current_cust_cr_flag = &customer1_created;
				current_cust = &customer1;
				current_cust_blip = ped1_blip;
				continue;
			}
			if (deliver(&customer2_created, &customer2))
			{
				current_cust_cr_flag = &customer2_created;
				current_cust = &customer2;
				current_cust_blip = ped2_blip;
				continue;
			}
			if (deliver(&customer3_created, &customer3))
			{
				current_cust_cr_flag = &customer3_created;
				current_cust = &customer3;
				current_cust_blip = ped3_blip;
				continue;
			}
			if (deliver(&customer4_created, &customer4))
			{
				current_cust_cr_flag = &customer4_created;
				current_cust = &customer4;
				current_cust_blip = ped4_blip;
				continue;
			}
			if (deliver(&customer5_created, &customer5))
			{
				current_cust_cr_flag = &customer5_created;
				current_cust = &customer5;
				current_cust_blip = ped5_blip;
				continue;
			}
			if (deliver(&customer6_created, &customer6))
			{
				current_cust_cr_flag = &customer6_created;
				current_cust = &customer6;
				current_cust_blip = ped6_blip;
				continue;
			}
			if (deliver(&customer7_created, &customer7))
			{
				current_cust_cr_flag = &customer7_created;
				current_cust = &customer7;
				current_cust_blip = ped7_blip;
				continue;
			}
			if (deliver(&customer8_created, &customer8))
			{
				current_cust_cr_flag = &customer8_created;
				current_cust = &customer8;
				current_cust_blip = ped8_blip;
				continue;
			}
			if (deliver(&customer9_created, &customer9))
			{
				current_cust_cr_flag = &customer9_created;
				current_cust = &customer9;
				current_cust_blip = ped9_blip;
				continue;
			}
			if (deliver(&customer10_created, &customer10))
			{
				current_cust_cr_flag = &customer10_created;
				current_cust = &customer10;
				current_cust_blip = ped10_blip;
				continue;
			}
		}
		
		float moped_speed;
		GET_CAR_SPEED(moped, &moped_speed);
		if ( LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), pizza_shopx, pizza_shopy, pizza_shopz, 5.0, 5.0, 5.0, 1) && (moped_speed < 0.3) )	/*rebusx: быстрая реакция на остановку мопеда */
		{
			if (delivered_in_this_order >= mission_lvl)
			{
				clear_all_customers();
				mission_lvl++;
				if (mission_lvl > 10)
				{
					break;
				}
				get_new_order(1);	/*rebusx: с озвучкой*/
				this_order_done = 0;
			}
			else
			{
				if (have_pizzas < 6)
				{
					have_pizzas = 6;
					set_random_speech();
				}
			}
		}
	}
	CLEAR_PRINTS();
	CLEAR_WANTED_LEVEL(GetPlayerIndex());
	play_mission_complete_tune();
	MissionPassed(5000, "missionpassed", "P_PASS");
	ADD_SCORE(GetPlayerIndex(), 5000);
	INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 5000);
	if (G_PIZZA == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
		G_GAME_PROGRESS += 1;
		SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
		PRINT_HELP("PIZ1_WON");	//Pizza Mission Complete. Your max Health increased to 150.
		G_PIZZA = 1;
	}
	mission_cleanup_pizza();
}
