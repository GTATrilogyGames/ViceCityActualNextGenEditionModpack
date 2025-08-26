/***********************************************************************
					Fully stripped main script
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
#include "cutscenes.h"
#include "mission_passed.h"

int model1_on, model2_on, model3_on, model4_on, model5_on, model6_on, model7_on, model8_on, model9_on, model10_on, model11_on, model12_on, model13_on, model14_on, model15_on;
int help, help2, money_ped, cam_res;

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
void business(void)
{
	Blip unused_blip, property_blip[16], ammun1_ico, ammun2_ico, ammun3_ico, tools1_ico, tools2_ico, tools3_ico, paint1_ico, paint2_ico, paint3_ico, paint4_ico;
					 
	cam_res = 0;
	help = 0;
	help2 = 0;
	model1_on = 0;
	model2_on = 0;
	model3_on = 0;
	model4_on = 0;
	model5_on = 0;
	model6_on = 0;
	model7_on = 0;
	model8_on = 0;
	model9_on = 0;
	model10_on = 0;
	model11_on = 0;
	model12_on = 0;
	model13_on = 0;
	model14_on = 0;
	model15_on = 0;

	uint stendM;
	uint stendM_off = stend_prodano2; // скоро в продаже
	uint stendM_no = stend_prodano; // можно покупать
	Object stend;
	Cam camera;

	REQUEST_MODEL(stendM_off);
	REQUEST_MODEL(stendM_no);
	while ((!HAS_MODEL_LOADED(stendM_off)) || (!HAS_MODEL_LOADED(stendM_no))) WAIT(0);

//************************************************************* МЕТКИ НА КАРТЕ *************************************************************
	// Doughnut Shop (Havana)
	ADD_BLIP_FOR_COORD(-425.312, -101.683, 5.36331, &unused_blip);
	CHANGE_BLIP_SPRITE(unused_blip, BLIP_RESTAURANT);
	CHANGE_BLIP_SCALE(unused_blip, 1.1);
	SET_BLIP_AS_SHORT_RANGE(unused_blip, 1);

	// Cafe Robina (Havana)
	ADD_BLIP_FOR_COORD(-736.09, -84.6355, 5.78244, &unused_blip);
	CHANGE_BLIP_SPRITE(unused_blip, BLIP_RESTAURANT);
	CHANGE_BLIP_SCALE(unused_blip, 1.1);
	SET_BLIP_AS_SHORT_RANGE(unused_blip, 1);

	// Pizza #1 (Vice Point)
	ADD_BLIP_FOR_COORD(852.456, 620.24, 5.16551, &unused_blip);
	CHANGE_BLIP_SPRITE(unused_blip, BLIP_RESTAURANT);
	CHANGE_BLIP_SCALE(unused_blip, 1.1);
	SET_BLIP_AS_SHORT_RANGE(unused_blip, 1);

	// Pizza #2 (Haiti)
	ADD_BLIP_FOR_COORD(-608.372, 615.234, 5.5641, &unused_blip);
	CHANGE_BLIP_SPRITE(unused_blip, BLIP_RESTAURANT);
	CHANGE_BLIP_SCALE(unused_blip, 1.1);
	SET_BLIP_AS_SHORT_RANGE(unused_blip, 1);
	
	// Pizza #3 (Downtown)
	ADD_BLIP_FOR_COORD(-469.844, 1331.57, 5.35378, &unused_blip);
	CHANGE_BLIP_SPRITE(unused_blip, BLIP_RESTAURANT);
	CHANGE_BLIP_SCALE(unused_blip, 1.1);
	SET_BLIP_AS_SHORT_RANGE(unused_blip, 1);

	// HotDog #1 (Mall)
	ADD_BLIP_FOR_COORD(869.753, 1638.69, 13.21, &unused_blip);
	CHANGE_BLIP_SPRITE(unused_blip, BLIP_RESTAURANT);
	CHANGE_BLIP_SCALE(unused_blip, 1.1);
	SET_BLIP_AS_SHORT_RANGE(unused_blip, 1);

	// HotDog #2 (Mall)
	ADD_BLIP_FOR_COORD(871.064, 1675.66, 13.165, &unused_blip);
	CHANGE_BLIP_SPRITE(unused_blip, BLIP_RESTAURANT);
	CHANGE_BLIP_SCALE(unused_blip, 1.1);
	SET_BLIP_AS_SHORT_RANGE(unused_blip, 1);

	// HotDog #3 (Mall)
	ADD_BLIP_FOR_COORD(810.264, 1680.68, 13.5298, &unused_blip);
	CHANGE_BLIP_SPRITE(unused_blip, BLIP_RESTAURANT);
	CHANGE_BLIP_SCALE(unused_blip, 1.1);
	SET_BLIP_AS_SHORT_RANGE(unused_blip, 1);

	// Ammu-Nation#1 (Washington Beach)
	ADD_BLIP_FOR_COORD(369.825, -949.315, 4.43197, &ammun1_ico);//создаем иконку на радаре
	CHANGE_BLIP_SPRITE(ammun1_ico, BLIP_WEAPONS);//текстура иконки на радаре
	CHANGE_BLIP_SCALE(ammun1_ico, 1.1); // масштаб иконки на радаре
	SET_BLIP_AS_SHORT_RANGE(ammun1_ico, 1); // иконка пропадает если не в зоне радардиска
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(ammun1_ico, "LG_13");//иконка на радаре называние в истории карты ""

	// Ammu-Nation#2 (Downtown)
	ADD_BLIP_FOR_COORD(-244.787, 1737.22, 5.01206, &ammun2_ico);//создаем иконку на радаре
	CHANGE_BLIP_SPRITE(ammun2_ico, BLIP_WEAPONS);//текстура иконки на радаре
	CHANGE_BLIP_SCALE(ammun2_ico, 1.1); // масштаб иконки на радаре
	SET_BLIP_AS_SHORT_RANGE(ammun2_ico, 1); // иконка пропадает если не в зоне радардиска
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(ammun2_ico, "LG_13");//иконка на радаре называние в истории карты ""

	// Ammu-Nation#3 (Mall)
	ADD_BLIP_FOR_COORD(798.101, 1588.29, 13.1281, &ammun3_ico);//создаем иконку на радаре
	CHANGE_BLIP_SPRITE(ammun3_ico, BLIP_WEAPONS);//текстура иконки на радаре
	CHANGE_BLIP_SCALE(ammun3_ico, 1.1); // масштаб иконки на радаре
	SET_BLIP_AS_SHORT_RANGE(ammun3_ico, 1); // иконка пропадает если не в зоне радардиска
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(ammun3_ico, "LG_13");//иконка на радаре называние в истории карты ""

	// Screw This (Havana)
	ADD_BLIP_FOR_COORD(-533.581, -160.29, 5.26489, &tools1_ico);//создаем иконку на радаре
	CHANGE_BLIP_SPRITE(tools1_ico, BLIP_REVENGE);//текстура иконки на радаре
	CHANGE_BLIP_SCALE(tools1_ico, 1.1); // масштаб иконки на радаре
	SET_BLIP_AS_SHORT_RANGE(tools1_ico, 1); // иконка пропадает если не в зоне радардиска
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(tools1_ico, "LG_15");//иконка на радаре называние в истории карты ""

	// Bunch of Tools (Washington Beach)
	ADD_BLIP_FOR_COORD(636.332, 59.2133, 4.97102, &tools2_ico);//создаем иконку на радаре
	CHANGE_BLIP_SPRITE(tools2_ico, BLIP_REVENGE);//текстура иконки на радаре
	CHANGE_BLIP_SCALE(tools2_ico, 1.1); // масштаб иконки на радаре
	SET_BLIP_AS_SHORT_RANGE(tools2_ico, 1); // иконка пропадает если не в зоне радардиска
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(tools2_ico, "LG_15");//иконка на радаре называние в истории карты ""

	// Hardware Store (Mall)
	ADD_BLIP_FOR_COORD(796.299, 1610.4, 13.0615, &tools3_ico);//создаем иконку на радаре
	CHANGE_BLIP_SPRITE(tools3_ico, BLIP_REVENGE);//текстура иконки на радаре
	CHANGE_BLIP_SCALE(tools3_ico, 1.1); // масштаб иконки на радаре
	SET_BLIP_AS_SHORT_RANGE(tools3_ico, 1); // иконка пропадает если не в зоне радардиска
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(tools3_ico, "LG_15");//иконка на радаре называние в истории карты ""

	// Pay 'n' Spray (Docks)
	ADD_BLIP_FOR_COORD(-473.14, -722.05, 6.68, &paint1_ico);//создаем иконку на радаре
	CHANGE_BLIP_SPRITE(paint1_ico, BLIP_PAY_N_SPRAY);//текстура иконки на радаре
	CHANGE_BLIP_SCALE(paint1_ico, 1.1); // масштаб иконки на радаре
	SET_BLIP_AS_SHORT_RANGE(paint1_ico, 1); // иконка пропадает если не в зоне радардиска
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(paint1_ico, "LG_22");//иконка на радаре называние в истории карты ""

	// Pay 'n' Spray (Haiti)
	ADD_BLIP_FOR_COORD(-447.7, 419.3, 6.07, &paint2_ico);//создаем иконку на радаре
	CHANGE_BLIP_SPRITE(paint2_ico, BLIP_PAY_N_SPRAY);//текстура иконки на радаре
	CHANGE_BLIP_SCALE(paint2_ico, 1.1); // масштаб иконки на радаре
	SET_BLIP_AS_SHORT_RANGE(paint2_ico, 1); // иконка пропадает если не в зоне радардиска
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(paint2_ico, "LG_22");//иконка на радаре называние в истории карты ""

	// Pay 'n' Spray (Washington Beach)
	ADD_BLIP_FOR_COORD(426.69, -725.55, 5.43, &paint3_ico);//создаем иконку на радаре
	CHANGE_BLIP_SPRITE(paint3_ico, BLIP_PAY_N_SPRAY);//текстура иконки на радаре
	CHANGE_BLIP_SCALE(paint3_ico, 1.1); // масштаб иконки на радаре
	SET_BLIP_AS_SHORT_RANGE(paint3_ico, 1); // иконка пропадает если не в зоне радардиска
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(paint3_ico, "LG_22");//иконка на радаре называние в истории карты ""

	// Pay 'n' Spray (Vice Point)
	ADD_BLIP_FOR_COORD(752.2, 965.8, 6.21, &paint4_ico);//создаем иконку на радаре
	CHANGE_BLIP_SPRITE(paint4_ico, BLIP_PAY_N_SPRAY);//текстура иконки на радаре
	CHANGE_BLIP_SCALE(paint4_ico, 1.1); // масштаб иконки на радаре
	SET_BLIP_AS_SHORT_RANGE(paint4_ico, 1); // иконка пропадает если не в зоне радардиска
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(paint4_ico, "LG_22");//иконка на радаре называние в истории карты ""

	while (TRUE) 
	{
		WAIT(0);
//************************************************************* Fix камеры покрасочной  *************************************************************
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -568.004, -324.765, 1.159, -581.655, -308.657, 6.149, 0 )))
		{
			if (cam_res == 0)
			{
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, -574.829, -316.711, 1.15926 ); // куда смотрит камера
				SET_CAM_POS			( camera, -574.936, -292.296, 8.12582 );//расположение камеры
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_WIDESCREEN_BORDERS( 1 );
				cam_res = 1;
			}
		}
		else
		{
			if (cam_res == 1)
			{
				SET_CAM_BEHIND_PED( GetPlayerPed() );
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				END_CAM_COMMANDS( &camera );
				SET_WIDESCREEN_BORDERS( 0 );
				cam_res = 0;
			}
		}
//************************************************************* СТЕНДЫ ПОКУПКИ *************************************************************

		// -----------------------------------  Стенд покупки "Printworks" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -553.505, 189.527, -642.972, 291.936, 0)) && (G_COUNT == 0))//
		{
			if (model1_on == 0)
			{
				if (G_SALE_NO == 1)
				{
					stendM = stendM_no;
				}
				else
				{
					stendM = stendM_off;
				}
				CREATE_OBJECT_NO_OFFSET(stendM, -625.976, 249.794, 5.16228, &stend, TRUE);
				SET_OBJECT_HEADING(stend, 90.0);
				model1_on = 1;
			}
		}
		else
		{
			if (model1_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model1_on = 0;
			}
		}
		// -----------------------------------  Стенд покупки "Sunshine Autos" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -511.774, -421.269, -661.774, -271.269, 0)) && (G_BUSINES_SA == 0))//
		{
			if (model2_on == 0)
			{
				if (G_SALE_NO == 1)
				{
					stendM = stendM_no;
				}
				else
				{
					stendM = stendM_off;
				}
				CREATE_OBJECT_NO_OFFSET(stendM, -586.774, -346.269, 7.00958, &stend, TRUE);
				model2_on = 1;
			}
		}
		else
		{
			if (model2_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model2_on = 0;
			}
		}
		// -----------------------------------  Стенд покупки "Interglobal Films" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 524.207, 1425.438, 374.207, 1575.438, 0)) && (G_PRON == 0))//
		{
			if (model3_on == 0)
			{
				if (G_SALE_NO == 1)
				{
					stendM = stendM_no;
				}
				else
				{
					stendM = stendM_off;
				}
				CREATE_OBJECT_NO_OFFSET(stendM, 449.207, 1500.44, 4.89943, &stend, TRUE);
				SET_OBJECT_HEADING(stend, 85.0);
				model3_on = 1;
			}
		}
		else
		{
			if (model3_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model3_on = 0;
			}
		}
		// -----------------------------------  Стенд покупки "Cherry Popper Icecreams" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -355.017, -109.166, -505.017, 40.834, 0)) && (G_ICECREAM == 0))//
		{
			if (model4_on == 0)
			{
				if (G_SALE_NO == 1)
				{
					stendM = stendM_no;
				}
				else
				{
					stendM = stendM_off;
				}
				CREATE_OBJECT_NO_OFFSET(stendM, -430.356, -45.9763, 4.95301, &stend, TRUE);
				SET_OBJECT_HEADING(stend, 95.0);
				model4_on = 1;
			}
		}
		else
		{
			if (model4_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model4_on = 0;
			}
		}
		// -----------------------------------  Стенд покупки "Kaufman Cabs" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -506.749, 652.2, -656.749, 802.2, 0)) && (G_CABS == 0))//
		{
			if (model5_on == 0)
			{
				if (G_SALE_NO == 1)
				{
					stendM = stendM_no;
				}
				else
				{
					stendM = stendM_off;
				}
				CREATE_OBJECT_NO_OFFSET(stendM, -579.761, 725.212, 5.17992, &stend, TRUE);
				SET_OBJECT_HEADING(stend, 85.0);
				model5_on = 1;
			}
		}
		else
		{
			if (model5_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model5_on = 0;
			}
		}
		// -----------------------------------  Стенд покупки "Malibu Club" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 1015.69, 351.669, 865.69, 501.669, 0)) && (G_CLUB == 0))//
		{
			if (model6_on == 0)
			{
				if (G_SALE_NO == 1)
				{
					stendM = stendM_no;
				}
				else
				{
					stendM = stendM_off;
				}
				CREATE_OBJECT_NO_OFFSET(stendM, 917.176, 443.684, 5.438, &stend, TRUE);
				SET_OBJECT_HEADING(stend, 0.0);
				model6_on = 1;
			}
		}
		else
		{
			if (model6_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model6_on = 0;
			}
		}
		// -----------------------------------  Стенд покупки "The Boatyard" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -213.936, -999.331, -363.936, -849.331, 0)) && (G_COKERUN == 0))//
		{
			if (model7_on == 0)
			{
				if (G_SALE_NO == 1)
				{
					stendM = stendM_no;
				}
				else
				{
					stendM = stendM_off;
				}
				CREATE_OBJECT_NO_OFFSET(stendM, -253.92, -952.214, 6.20324, &stend, TRUE);
				SET_OBJECT_HEADING(stend, 70.0);
				model7_on = 1;
			}
		}
		else
		{
			if (model7_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model7_on = 0;
			}
		}
		// -----------------------------------  Стенд покупки "Pole Position Club" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 609.163, -1011.184, 490.722, -861.184, 0)) && (G_STRIP == 0))//
		{
			if (model8_on == 0)
			{
				if (G_SALE_NO == 1)
				{
					stendM = stendM_no;
				}
				else
				{
					stendM = stendM_off;
				}
				CREATE_OBJECT_NO_OFFSET(stendM, 532.888, -938.744, 4.34977, &stend, TRUE);
				SET_OBJECT_HEADING(stend, 70.0);
				model8_on = 1;
			}
		}
		else
		{
			if (model8_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model8_on = 0;
			}
		}
		// -----------------------------------  Стенд покупки "El Swanko Casa" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 938.646, 1109.436, 788.646, 1259.436, 0)) && (G_SWANKO == 0))//
		{
			if (model9_on == 0)
			{
				CREATE_OBJECT_NO_OFFSET(stendM_no, 863.646, 1184.44, 5.13381, &stend, TRUE);
				SET_OBJECT_HEADING(stend, 175.0);
				model9_on = 1;
			}
		}
		else
		{
			if (model9_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model9_on = 0;
			}
		}

		// -----------------------------------  Стенд покупки "Links View Apartment" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 818.354, 848.015, 655.851, 984.37, 0)) && (G_LINKS == 0))//
		{
			if (model10_on == 0)
			{
				CREATE_OBJECT_NO_OFFSET(stendM_no, 737.102, 905.26, 7.16889, &stend, TRUE);
				SET_OBJECT_HEADING(stend, -90.0);
				model10_on = 1;
			}
		}
		else
		{
			if (model10_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model10_on = 0;
			}
		}
		// -----------------------------------  Стенд покупки "Hyman Condo" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -329.521, 1762.531, -479.521, 1912.531, 0)) && (G_CONDO == 0))//
		{
			if (model11_on == 0)
			{
				CREATE_OBJECT_NO_OFFSET(stendM_no, -405.751, 1837.61, 5.45809, &stend, TRUE);
				SET_OBJECT_HEADING(stend, 20.0);
				model11_on = 1;
			}
		}
		else
		{
			if (model11_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model11_on = 0;
			}
		}
		// -----------------------------------  Стенд покупки "Ocean Heighs Aprt." -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 490.16, -1011.184, 371.718, -861.184, 0)) && (G_HEIGHS == 0))//
		{
			if (model12_on == 0)
			{
				CREATE_OBJECT_NO_OFFSET(stendM_no, 450.95, -952.567, 4.37774, &stend, TRUE);
				SET_OBJECT_HEADING(stend, -7.5);
				model12_on = 1;
			}
		}
		else
		{
			if (model12_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model12_on = 0;
			}
		}
		// -----------------------------------  Стенд покупки "1102 Washington Street" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 606.06, -341.152, 456.06, -191.152, 0)) && (G_WS_1102 == 0))//
		{
			if (model13_on == 0)
			{
				CREATE_OBJECT_NO_OFFSET(stendM_no, 531.06, -266.152, 4.3935, &stend, TRUE);
				SET_OBJECT_HEADING(stend, -120.0);
				model13_on = 1;
			}
		}
		else
		{
			if (model13_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model13_on = 0;
			}
		}
		// -----------------------------------  Стенд покупки "Vice Point" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 1040.874, 1722.849, 890.874, 1872.849, 0)) && (G_VP_3321 == 0))//
		{
			if (model14_on == 0)
			{
				CREATE_OBJECT_NO_OFFSET(stendM_no, 965.874,1797.85,10.3284, &stend, TRUE);
				SET_OBJECT_HEADING(stend, 130.0);
				model14_on = 1;
			}
		}
		else
		{
			if (model14_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model14_on = 0;
			}
		}
		// -----------------------------------  Стенд покупки "Skumole Shack" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -30.384, 1156.068, -180.384, 1306.068, 0)) && (G_SHACK == 0))//
		{
			if (model15_on == 0)
			{
				CREATE_OBJECT_NO_OFFSET(stendM_no, -105.384, 1231.07, 14.4595, &stend, TRUE);
				SET_OBJECT_HEADING(stend, -170.0);
				model15_on = 1;
			}
		}
		else
		{
			if (model15_on == 1)
			{
				DELETE_OBJECT(&stend);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&stend);
				model15_on = 0;
			}
		}
//===================================================================================================================================
//************************************************************* ПОКУПКА *************************************************************

		// -----------------------------------  ПОКУПКА "Printworks" -----------------------------------
		if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -624.476, 249.443, -627.476, 252.443, 0)) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_COUNT == 0))//
		{
			if (help == 0)
			{
				if  (G_SALE_NO == 0)
				{
					PRINT_HELP("PRNT_NO"); //You cannot buy the Print Works at this time, come back later.
					help = 1;
				}
				else if  (G_SALE_NO == 1)
				{
					PRINT_HELP_FOREVER_WITH_NUMBER("PRNT_L", 70000); //Press the ~INPUT_PHONE_ACCEPT~ button to purchase the Print Works for ~g~$~1~
					help = 1;
				}
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) && (G_SALE_NO == 1) || (IS_BUTTON_PRESSED( 0, 16 )) && (G_SALE_NO == 1))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 70000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 70000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -70000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(-645.084, 246.738, 6.27582 - 0.22332, -5.0, "PrintWorks", 0);
					ENABLE_SAVE_HOUSE(0, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_COUNT = 1;
					REMOVE_BLIP(property_blip[0]);
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
					SET_CHAR_COORDINATES(GetPlayerPed(), -627.057, 246.12, 5.39574);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), -90.0);
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, -644.978, 264.365, 8.10603 ); // куда смотрит камера
					SET_CAM_POS			( camera, -593.396, 234.504, 16.1353 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "CNTBUY1", 70000); //Printworks purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 5000 )
						{
							break;
						}
					}
					//Камера на диван
					POINT_CAM_AT_COORD	( camera, -645.223, 244.068, 6.51072 ); // куда смотрит камера
					SET_CAM_POS			( camera, -643.529, 249.673, 8.48956 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEHELP1"); //Sleeping on the bed will save the game and advance time by six hours.
					SetTime(5000);

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
					G_ONMISSION = 0;

					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}

		// -----------------------------------  ПОКУПКА "Sunshine Autos" -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -584.126, -347.769, -587.126, -344.769, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_BUSINES_SA == 0))//
		{
			if (help == 0)
			{
				if  (G_SALE_NO == 0)
				{
					PRINT_HELP("CAR_NO"); //You cannot buy the Car Showroom at this time, come back later.
					help = 1;
				}
				else if  (G_SALE_NO == 1)
				{
					PRINT_HELP_FOREVER_WITH_NUMBER("CAR_L", 50000); //Press the ~INPUT_PHONE_ACCEPT~ button to purchase the Car Showroom for ~g~$~1~
					help = 1;
				}
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) && (G_SALE_NO == 1) || (IS_BUTTON_PRESSED( 0, 16 )) && (G_SALE_NO == 1))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 50000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 50000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -50000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(-595.363, -318.285, 7.53234 - 0.48149, -150.0, "SunshineAutos", 1);
					ENABLE_SAVE_HOUSE(1, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_BUSINES_SA = 1;
					REMOVE_BLIP(property_blip[1]);
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
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);
					SET_CHAR_COORDINATES(GetPlayerPed(), -588.85, -325.996, 7.17353);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), -105.0);
					FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
					RELEASE_WEATHER();

					LOAD_ADDITIONAL_TEXT( "CAR_1", 6 ); // загружаем субтитры из *.GTX
				  
		
					START_CUTSCENE_NOW("car_1");
   
		 
					while (!HAS_CUTSCENE_LOADED())
					{
						WAIT(0);
					}
					DO_SCREEN_FADE_IN(0);
					while (!HAS_CUTSCENE_FINISHED())
					{
						WAIT(0);
					}

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, -583.188, -334.591, 12.646); // куда смотрит камера
					SET_CAM_POS			( camera, -587.596, -389.758, 14.336); //расположение камеры	
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "CARBUY", 50000); //Car Showroom purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 5000 )
						{
							break;
						}
					}
					//Камера на диван
					POINT_CAM_AT_COORD	( camera, -596.941, -315.536, 7.53233 ); // куда смотрит камера
					SET_CAM_POS			( camera, -596.425, -319.508, 9.06065 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEHELP1"); //Sleeping on the bed will save the game and advance time by six hours.
					SetTime(5000);

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
					DO_SCREEN_FADE_IN(500);

					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
					G_ONMISSION = 0;
					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}

		// -----------------------------------  ПОКУПКА "Interglobal Films" -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 450.707, 1500.086, 447.707, 1503.086, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_PRON == 0))//
		{
			if (help == 0)
			{
				if  (G_SALE_NO == 0)
				{
					PRINT_HELP("PORN_NO"); //You cannot buy the Film Studio at this time, come back later.
					help = 1;
				}
				else if  (G_SALE_NO == 1)
				{
					PRINT_HELP_FOREVER_WITH_NUMBER("PORN_L", 60000); //Press the ~INPUT_PHONE_ACCEPT~ ~button to purchase the Film Studios for ~g~$~1~
					help = 1;
				}
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) && (G_SALE_NO == 1) || (IS_BUTTON_PRESSED( 0, 16 )) && (G_SALE_NO == 1))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 60000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 60000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -60000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(349.932, 1461.77, 5.1074 - 0.33669, -105.0, "InterGlobalStudios", 2);
					ENABLE_SAVE_HOUSE(2, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_PRON = 1;
					REMOVE_BLIP(property_blip[2]);
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
					SET_CHAR_COORDINATES(GetPlayerPed(), 426.072,1493.69,5.22053);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), -70.0);
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 428.048, 1500.59, 9.42667 ); // куда смотрит камера
					SET_CAM_POS			( camera, 476.677, 1475.27, 15.8669 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "PORNBUY", 60000); //Film Studio purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 5000 )
						{
							break;
						}
					}
					//Камера на диван
					POINT_CAM_AT_COORD	( camera, 348.119, 1466.341, 5.10739 ); // куда смотрит камера
					SET_CAM_POS			( camera, 347.723, 1461.501, 6.42478 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEHELP1"); //Sleeping on the bed will save the game and advance time by six hours.
					SetTime(5000);

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
					G_ONMISSION = 0;

					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}
		// -----------------------------------  ПОКУПКА "Cherry Popper Icecreams" -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -428.856, -46.328, -431.856, -43.328, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_ICECREAM == 0))//
		{
			if (help == 0)
			{
				if  (G_SALE_NO == 0)
				{
					PRINT_HELP("ICE_NO"); // You cannot buy the Ice Cream Factory at this time, come back later.
					help = 1;
				}
				else if  (G_SALE_NO == 1)
				{
					PRINT_HELP_FOREVER_WITH_NUMBER("ICE_L", 20000); //Press the ~INPUT_PHONE_ACCEPT~ button to purchase the Ice Cream Factory for ~g~$~1~
					help = 1;
				}
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) && (G_SALE_NO == 1) || (IS_BUTTON_PRESSED( 0, 16 )) && (G_SALE_NO == 1))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 20000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 20000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -20000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(-444.516, -45.5149, 5.47654 - 0.23604, -80.0, "CherryPopperIceCreamFactory", 3);
					ENABLE_SAVE_HOUSE(3, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_ICECREAM = 1;
					REMOVE_BLIP(property_blip[3]);
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
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);
					SET_CHAR_COORDINATES(GetPlayerPed(), -442.448, -35.7613, 5.47654);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), -125.0);

					uint hour, minute, weather;
					GET_TIME_OF_DAY(&hour, &minute);
					GET_CURRENT_WEATHER(&weather);
					FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
					FORWARD_TO_TIME_OF_DAY(18, 25);//устанавливаем время

					LOAD_ADDITIONAL_TEXT( "ICE_1", 6 ); // загружаем субтитры из *.GTX
																	 
							 
					START_CUTSCENE_NOW("ice_1");
		 
									
					while (!HAS_CUTSCENE_LOADED())
					{
						WAIT(0);
					}
					DO_SCREEN_FADE_IN(0);
					while (!HAS_CUTSCENE_FINISHED())
					{
						WAIT(0);
					}

					FORCE_WEATHER_NOW( weather );//устанавливаем погода
					RELEASE_WEATHER();
					FORWARD_TO_TIME_OF_DAY(hour, minute);//устанавливаем время

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, -504.002, -10.755, 6.353 ); // куда смотрит камера
					SET_CAM_POS			( camera, -399.236, -60.687, 18.444 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "ICEBUY", 20000); //Ice Cream Factory purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 5000 )
						{
							break;
						}
					}
					//Камера на диван
					POINT_CAM_AT_COORD	( camera, -446.558, -45.5251, 5.69816 ); // куда смотрит камера
					SET_CAM_POS			( camera, -443.155, -48.0858, 6.07822 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEHELP1"); //Sleeping on the bed will save the game and advance time by six hours.
					SetTime(5000);

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
					DO_SCREEN_FADE_IN(500);

					SetTime(1000);
					NEW_SCRIPTED_CONVERSATION();
					ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
					ADD_LINE_TO_CONVERSATION(0, "R14_VV", "", 0, 0);//
					START_SCRIPT_CONVERSATION(1, 1);

					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
					G_ONMISSION = 0;
					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}
		// -----------------------------------  ПОКУПКА "Kaufman Cabs" -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -578.261, 724.86, -581.261, 727.86, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_CABS == 0))//
		{
			if (help == 0)
			{
				if  (G_SALE_NO == 0)
				{
					PRINT_HELP("TAXI_NO"); //You cannot buy the Taxi Company at this time, come back later.
					help = 1;
				}
				else if  (G_SALE_NO == 1)
				{
					PRINT_HELP_FOREVER_WITH_NUMBER("TAXI_L", 40000); //Press the ~INPUT_PHONE_ACCEPT~ button to purchase the Taxi Company for ~g~$~1~
					help = 1;
				}
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) && (G_SALE_NO == 1) || (IS_BUTTON_PRESSED( 0, 16 )) && (G_SALE_NO == 1))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 40000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 40000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -40000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(-567.321, 720.751, 5.67434 - 0.26589, 60.0, "KaufmanCabs", 4);
					ENABLE_SAVE_HOUSE(4, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_CABS = 1;
					REMOVE_BLIP(property_blip[4]);
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
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);
					SET_CHAR_COORDINATES(GetPlayerPed(), -565.688, 724.969, 5.67434);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), 60.0);

					uint hour, minute, weather;
					GET_TIME_OF_DAY(&hour, &minute);
					GET_CURRENT_WEATHER(&weather);
					FORCE_WEATHER_NOW(WEATHER_EXTRA_SUNNY);
					FORWARD_TO_TIME_OF_DAY(18, 30);//устанавливаем время
					

					LOAD_ADDITIONAL_TEXT( "TAX_1", 6 ); // загружаем субтитры из *.GTX
																	 
							 
					START_CUTSCENE_NOW("tax_1");
		 
									
					while (!HAS_CUTSCENE_LOADED())
					{
						WAIT(0);
					}
					DO_SCREEN_FADE_IN(0);
					while (!HAS_CUTSCENE_FINISHED())
					{
						WAIT(0);
					}

					FORCE_WEATHER_NOW( weather );//устанавливаем погода
					RELEASE_WEATHER();
					FORWARD_TO_TIME_OF_DAY(hour, minute);//устанавливаем время

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, -572.881, 723.549, 9.168 ); // куда смотрит камера
					SET_CAM_POS			( camera, -588.599, 753.044, 9.441 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "TAXIBUY", 40000); //Taxi Firm purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 5000 )
						{
							break;
						}
					}
					//Камера на диван
					POINT_CAM_AT_COORD	( camera, -565.577, 720.491, 5.86685 ); // куда смотрит камера
					SET_CAM_POS			( camera, -567.029, 724.304, 6.30875 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEHELP1"); //Sleeping on the bed will save the game and advance time by six hours.
					SetTime(5000);

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
					DO_SCREEN_FADE_IN(500);

					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
					G_ONMISSION = 0;
					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}
		// -----------------------------------  ПОКУПКА "Malibu Club" -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 919.765, 442.644, 916.765, 445.644, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_CLUB == 0))//
		{
			if (help == 0)
			{
				if  (G_SALE_NO == 0)
				{
					PRINT_HELP("BANK_NO"); //You cannot buy The Malibu at this time, come back later.
					help = 1;
				}
				else if  (G_SALE_NO == 1)
				{
					PRINT_HELP_FOREVER_WITH_NUMBER("BANK_L", 120000); // = Press the ~INPUT_PHONE_ACCEPT~ button to purchase The Malibu for ~g~$~1~
					help = 1;
				}
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) && (G_SALE_NO == 1) || (IS_BUTTON_PRESSED( 0, 16 )) && (G_SALE_NO == 1))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 120000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 120000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -120000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(924.395, 454.833, 5.73708 - 0.27817, -130.0, "MalibuClub", 5);
					ENABLE_SAVE_HOUSE(5, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_CLUB = 1;
					REMOVE_BLIP(property_blip[5]);
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
					SET_CHAR_COORDINATES(GetPlayerPed(), 924.827,454.729,5.73708);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), -130.0);
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 914.084, 464.584, 5.83583 ); // куда смотрит камера
					SET_CAM_POS			( camera, 946.271, 430.582, 11.1684 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "BANKBUY", 120000); //The Malibu purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 5000 )
						{
							break;
						}
					}
					//Камера на диван
					POINT_CAM_AT_COORD	( camera, 896.968, 481.86, 10.0952 ); // куда смотрит камера
					SET_CAM_POS			( camera, 896.723, 478.72, 11.6229 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEHELP1"); //Sleeping on the bed will save the game and advance time by six hours.
					SetTime(5000);

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
					G_ONMISSION = 0;

					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}
		// -----------------------------------  ПОКУПКА "The Boatyard" -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -252.07, -952.45, -255.07, -949.45, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_COKERUN == 0))//
		{
			if (help == 0)
			{
				if  (G_SALE_NO == 0)
				{
					PRINT_HELP("BOAT_NO"); //You cannot buy the Boatyard at this time, come back later.
					help = 1;
				}
				else if  (G_SALE_NO == 1)
				{
					PRINT_HELP_FOREVER_WITH_NUMBER("BOAT_L", 10000); //Press the ~INPUT_PHONE_ACCEPT~ button to purchase the Boatyard for ~g~$~1~
					help = 1;
				}
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) && (G_SALE_NO == 1) || (IS_BUTTON_PRESSED( 0, 16 )) && (G_SALE_NO == 1))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 10000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 10000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -10000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(-235.225, -949.423, 8.07865 - 0.33167, -25.0, "Boatyard", 6);
					ENABLE_SAVE_HOUSE(6, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_COKERUN = 1;
					REMOVE_BLIP(property_blip[6]);
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
					uint reefM = dk_reef;
					REQUEST_MODEL(reefM);
					while (!HAS_MODEL_LOADED(reefM));
					uint cutObj;
					CREATE_OBJECT_NO_OFFSET(reefM, -218.0, -948.21, 11.647, &cutObj, 1);

					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);
					SET_CHAR_COORDINATES(GetPlayerPed(), -209.378, -952.158, 8.07865);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), -115.0);
					FORCE_WEATHER_NOW(WEATHER_SUNNY);


					LOAD_ADDITIONAL_TEXT( "DRUG_1", 6 ); // загружаем субтитры из *.GTX
																	 
							 
					START_CUTSCENE_NOW("drug_1");
		 
									 
					while (!HAS_CUTSCENE_LOADED())
					{
						WAIT(0);
					}
					DO_SCREEN_FADE_IN(0);
					while (!HAS_CUTSCENE_FINISHED())
					{
						WAIT(0);
					}

					RELEASE_WEATHER();
					DELETE_OBJECT(&cutObj);
					MARK_MODEL_AS_NO_LONGER_NEEDED(reefM);

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, -132.401, -966.641, 14.598 ); // куда смотрит камера
					SET_CAM_POS			( camera, -117.879, -968.923, 16.259 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "BOATBUY", 10000); //Boatyard purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 5000 )
						{
							break;
						}
					}
					//Камера на диван
					POINT_CAM_AT_COORD	( camera, -235.751, -951.261, 8.20742 ); // куда смотрит камера
					SET_CAM_POS			( camera, -231.451, -950.318, 9.67795 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEHELP1"); //Sleeping on the bed will save the game and advance time by six hours.
					SetTime(5000);

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
					DO_SCREEN_FADE_IN(500);

					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
					G_ONMISSION = 0;
					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}
		// -----------------------------------  ПОКУПКА "Pole Position Club" -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 534.661, -939.063, 531.661, -936.063, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_STRIP == 0))//
		{
			if (help == 0)
			{
				if  (G_SALE_NO == 0)
				{
					PRINT_HELP("STRP_NO"); //You cannot buy the Stripclub at this time, come back later.
					help = 1;
				}
				else if  (G_SALE_NO == 1)
				{
					PRINT_HELP_FOREVER_WITH_NUMBER("STRP_L", 30000); //Press the ~INPUT_PHONE_ACCEPT~ button to purchase the Pole Position Club for ~g~$~1~
					help = 1;
				}
			}
			if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()) && (G_SALE_NO == 1) || (IS_BUTTON_PRESSED( 0, 16 )) && (G_SALE_NO == 1))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 30000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 30000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -30000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(529.641, -937.62, 4.65521 - 0.2571, -150.0, "ThePolePositionClub", 7);
					ENABLE_SAVE_HOUSE(7, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_STRIP = 1;
					REMOVE_BLIP(property_blip[7]);
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
					SET_CHAR_COORDINATES(GetPlayerPed(), 529.927, -938.109, 4.66887);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), -145.0);
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 530.951, -939.898, 10.2194 ); // куда смотрит камера
					SET_CAM_POS			( camera, 538.559, -954.132, 13.486 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "STRPBUY", 30000); //Pole Position Club purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 5000 )
						{
							break;
						}
					}
					//Камера на диван
					POINT_CAM_AT_COORD	( camera, 499.998, -921.742, 5.56992 ); // куда смотрит камера
					SET_CAM_POS			( camera, 500.307, -919.739, 4.72875 );//расположение камеры
					SetTime(10);
					POINT_CAM_AT_COORD	( camera, 506.755, -916.366, 4.9338 ); // куда смотрит камера
					SET_CAM_POS			( camera, 509.832, -918.184, 6.3462 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEHELP1"); //Sleeping on the bed will save the game and advance time by six hours.
					SetTime(5000);

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
					G_ONMISSION = 0;
					PRINT_HELP("NECLOTH8"); //Mr Vercetti outfit delivered to Pole Position Club on Ocean Beach and on Vercetti Mansion.
					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}
		// -----------------------------------  ПОКУПКА "El Swanko Casa" -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 863.997, 1182.936, 860.997, 1185.936, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_SWANKO == 0))//
		{
			if (help == 0)
			{
				PRINT_HELP_FOREVER_WITH_NUMBER("NBMN_L", 8000); //Press the ~INPUT_PHONE_ACCEPT~ button to purchase El Swanko Casa for ~g~$~1~
				help = 1;
			}
			if (((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER())) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 8000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 8000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -8000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(861.53, 1139.81, 6.99313 - 0.31587, 0.0, "ElSwankoCasa", 8);
					ENABLE_SAVE_HOUSE(8, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_SWANKO = 1;
					CHANGE_BLIP_SPRITE(property_blip[8], BLIP_SAFEHOUSE);
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
					SET_CHAR_COORDINATES(GetPlayerPed(), 878.706, 1157.56, 5.64922);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), 0.0);
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 861.472, 1137.301, 13.1984 ); // куда смотрит камера
					SET_CAM_POS			( camera, 862.098, 1169.891, 6.12214 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "NBMNBUY", 8000); //El Swanko Casa purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 6000 )
						{
							break;
						}
					}
					//Камера на двери
					//NEHELP1
					POINT_CAM_AT_COORD	( camera, 859.646, 1136.19, 6.70153 ); // куда смотрит камера
					SET_CAM_POS			( camera, 870.455, 1148.84, 13.3133 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEBUYSAVE"); //You can now save your game here when not on a mission. To do this, walk through the doors of your property.
					SetTime(5000);

					//камера на гараж
					OPEN_GARAGE("gdoor10");
					POINT_CAM_AT_COORD	( camera, 886.138, 1171.57, 6.75008 ); // куда смотрит камера
					SET_CAM_POS			( camera, 871.395, 1179.61, 11.849 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("BUYGARG"); //You can also store vehicles in this garage.
					SetTime(5000);

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
					G_ONMISSION = 0;

					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}
		// -----------------------------------  ПОКУПКА "Links View Apartment" -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 738.602, 902.612, 735.602, 905.612, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_LINKS == 0))//
		{
			if (help == 0)
			{
				PRINT_HELP_FOREVER_WITH_NUMBER("LNKV_L", 6000); //Press the ~INPUT_PHONE_ACCEPT~ button to purchase Links View Apartment for ~g~$~1~
				help = 1;
			}
			if (((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER())) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 6000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 6000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -6000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(737.991, 909.371, 7.45291 - 0.26794, -85.0, "LinksViewApartment", 9);
					ENABLE_SAVE_HOUSE(9, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_LINKS = 1;
					CHANGE_BLIP_SPRITE(property_blip[9], BLIP_SAFEHOUSE);
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
					SET_CHAR_COORDINATES(GetPlayerPed(), 739.479, 917.924, 7.4594);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), -90.0);
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 729.957, 901.667, 23.3689 ); // куда смотрит камера
					SET_CAM_POS			( camera, 785.507, 955.337, 22.0341 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "LNKVBUY", 6000); //Links View Apartment purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 6000 )
						{
							break;
						}
					}
					//Камера на двери
					POINT_CAM_AT_COORD	( camera, 735.808, 908.971, 8.72206 ); // куда смотрит камера
					SET_CAM_POS			( camera, 745.684, 912.931, 13.9169 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEBUYSAVE"); //You can now save your game here when not on a mission. To do this, walk through the doors of your property.
					SetTime(5000);

					//камера на гараж
					OPEN_GARAGE("gdoor11");
					POINT_CAM_AT_COORD	( camera, 735.575, 938.531, 6.27094 ); // куда смотрит камера
					SET_CAM_POS			( camera, 749.416, 919.618, 16.9161 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("BUYGARG"); //You can also store vehicles in this garage.
					SetTime(5000);

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
					G_ONMISSION = 0;

					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}
		// -----------------------------------  ПОКУПКА "Hyman Condo" -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -403.136, 1836.783, -406.136, 1839.783, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_CONDO == 0))//
		{
			if (help == 0)
			{
				PRINT_HELP_FOREVER_WITH_NUMBER("HYCO_L", 14000); //Press the ~INPUT_PHONE_ACCEPT~ button to purchase Hyman Condo for ~g~$~1~
				help = 1;
			}
			if (((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER())) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 14000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 14000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -14000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(-401.593, 1839.58, 5.7949 - 0.29537, -165.0, "HymanCondo", 10);
					ENABLE_SAVE_HOUSE(10, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_CONDO = 1;
					CHANGE_BLIP_SPRITE(property_blip[10], BLIP_SAFEHOUSE);
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
					SET_CHAR_COORDINATES(GetPlayerPed(), -398.812, 1839.41, 5.75065);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), -165.0);
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, -392.419, 1867.27, 48.0627 ); // куда смотрит камера
					SET_CAM_POS			( camera, -488.811, 1900.47, 33.3734 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "HYCOBUY", 14000); //Hyman Condo purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 6000 )
						{
							break;
						}
					}
					//Камера на двери
					POINT_CAM_AT_COORD	( camera, -402.008, 1841.04, 6.70257 ); // куда смотрит камера
					SET_CAM_POS			( camera, -404.554, 1834.86, 8.30057 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEBUYSAVE"); //You can now save your game here when not on a mission. To do this, walk through the doors of your property.
					SetTime(5000);

					/*/камера на гараж
					POINT_CAM_AT_COORD	( camera, -398.571, 1844.99, 8.5453 ); // куда смотрит камера
					SET_CAM_POS			( camera, -417.093, 1828.67, 7.1639 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("BUYGARG"); //You can also store vehicles in this garage.
					OPEN_GARAGE("gdoor5");
					SetTime(500);
					OPEN_GARAGE("gdoor6");
					SetTime(500);
					OPEN_GARAGE("gdoor7");
					SetTime(4000);
					//*/

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
					//убираем камеру
					ACTIVATE_SCRIPTED_CAMS( 0, 0 );
					END_CAM_COMMANDS( &camera );
					SET_WIDESCREEN_BORDERS( 0 );
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					G_ONMISSION = 0;
					PRINT_HELP("CLOTH2"); //Street outfit delivered to Safehouses.

					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}
		// -----------------------------------  ПОКУПКА "Ocean Heighs Aprt." -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 453.598, -954.067, 450.598, -951.067, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_HEIGHS == 0))//
		{
			if (help == 0)
			{
				PRINT_HELP_FOREVER_WITH_NUMBER("OCHE_L", 7000); //Press the ~INPUT_PHONE_ACCEPT~ button to purchase Ocean Heights Apartment for ~g~$~1~
				help = 1;
			}
			if (((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER())) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 7000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 7000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -7000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(451.255, -967.217, 7.52892 - 0.31428, -5.0, "OceanHeightsApartment", 11);
					ENABLE_SAVE_HOUSE(11, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_HEIGHS = 1;
					CHANGE_BLIP_SPRITE(property_blip[11], BLIP_SAFEHOUSE);
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
					SET_CHAR_COORDINATES(GetPlayerPed(), 450.872, -963.737, 7.49369);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), -10.0);
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 453.427, -987.233, 20.8432 ); // куда смотрит камера
					SET_CAM_POS			( camera, 424.561, -940.881, 6.93499 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "OCHEBUY", 7000); //Ocean Heights Apartment purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 6000 )
						{
							break;
						}
					}
					//Камера на двери
					POINT_CAM_AT_COORD	( camera, 450.069, -969.381, 8.00377 ); // куда смотрит камера
					SET_CAM_POS			( camera, 452.951, -962.111, 9.85656 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEBUYSAVE"); //You can now save your game here when not on a mission. To do this, walk through the doors of your property.
					SetTime(5000);

					//камера на гараж
					OPEN_GARAGE("gdoor9");
					POINT_CAM_AT_COORD	( camera, 457.097, -954.075, 4.37774 ); // куда смотрит камера
					SET_CAM_POS			( camera, 449.727, -939.958, 11.2557 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("BUYGARG"); //You can also store vehicles in this garage.
					SetTime(5000);

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
					G_ONMISSION = 0;

					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}
		// -----------------------------------  ПОКУПКА "1102 Washington Street" -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 531.897, -268.394, 528.897, -265.394, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_WS_1102 == 0))//
		{
			if (help == 0)
			{
				PRINT_HELP_FOREVER_WITH_NUMBER("WASH_L", 3000); //Press the ~INPUT_PHONE_ACCEPT~ button to purchase 1102 Washington Street for ~g~$~1~
				help = 1;
			}
			if (((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER())) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 3000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 3000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -3000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(522.489, -272.164, 6.00446 - 0.30502, -120.0, "1102WashingtonStreet", 12);
					ENABLE_SAVE_HOUSE(12, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_WS_1102 = 1;
					CHANGE_BLIP_SPRITE(property_blip[12], BLIP_SAFEHOUSE);
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
					SET_CHAR_COORDINATES(GetPlayerPed(), 527.872, -269.953, 4.77075);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), -120.0);
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 514.368, -262.556, 31.1287 ); // куда смотрит камера
					SET_CAM_POS			( camera, 511.906, -342.815, 10.1779 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "WASHBUY", 3000); //1102 Washington Street purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 6000 )
						{
							break;
						}
					}
					//Камера на двери
					POINT_CAM_AT_COORD	( camera, 520.104, -269.722, 5.70883 ); // куда смотрит камера
					SET_CAM_POS			( camera, 522.505, -280.804, 9.75918 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEBUYSAVE"); //You can now save your game here when not on a mission. To do this, walk through the doors of your property.
					SetTime(5000);

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
					G_ONMISSION = 0;

					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}
		// -----------------------------------  ПОКУПКА "Vice Point" -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), 966.884, 1797.39, 963.884, 1800.39, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_VP_3321 == 0))//
		{
			if (help == 0)
			{
				PRINT_HELP_FOREVER_WITH_NUMBER("VCPT_L", 2500); //Press the ~INPUT_PHONE_ACCEPT~ button to purchase 3321 Vice Point for ~g~$~1~
				help = 1;
			}
			if (((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER())) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 2500)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 2500) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -2500 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(963.529, 1805.22, 12.0903 - 0.27704, 130.0, "3321VicePoint", 13);
					ENABLE_SAVE_HOUSE(13, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_VP_3321 = 1;
					CHANGE_BLIP_SPRITE(property_blip[13], BLIP_SAFEHOUSE);
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
					SET_CHAR_COORDINATES(GetPlayerPed(), 962.848, 1802, 10.7663);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), 140.0);
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, 982.386, 1819.441, 23.2439 ); // куда смотрит камера
					SET_CAM_POS			( camera, 963.204, 1763.401, 17.104 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "VCPTBUY", 2500); //3321 Vice Point purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 6000 )
						{
							break;
						}
					}
					//Камера на двери
					POINT_CAM_AT_COORD	( camera, 966.469, 1807.381, 13.9696 ); // куда смотрит камера
					SET_CAM_POS			( camera, 963.064, 1799.901, 16.8672 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEBUYSAVE"); //You can now save your game here when not on a mission. To do this, walk through the doors of your property.
					SetTime(5000);

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
					G_ONMISSION = 0;

					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}
		// -----------------------------------  ПОКУПКА "Skumole Shack" -----------------------------------
		else if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -105.138, 1230.052, -108.138, 1233.052, 0)) &&  (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_SHACK == 0))//
		{
			if (help == 0)
			{
				PRINT_HELP_FOREVER_WITH_NUMBER("SKUM_L", 1000); //Press the ~INPUT_PHONE_ACCEPT~ button to purchase Skumole Shack for ~g~$~1~
				help = 1;
			}
			if (((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER())) || (IS_BUTTON_PRESSED( 0, 16 )))//проверка нажата-ли клавиша "Для покупки".
			{
				STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
				if (G_ONMISSION == 1)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_MISSION_NO"); //You cannot buy property while on a mission.
						help2 = 1;
					}
				}
				else if (money_ped < 1000)
				{
					if (help2 == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NE_NO_BUY"); //You don't have enough cash for this property.
						help2 = 1;
					}
				}
				else if ((money_ped >= 1000) && (G_ONMISSION == 0))
				{
					G_ONMISSION = 1;
					ADD_SCORE( GetPlayerIndex(), -1000 );// отнимаем у игрока сумму
					REGISTER_SAVE_HOUSE(-127.19, 1236.19, 14.8111 - 0.32943, 0.0, "SkumoleShack", 14);
					ENABLE_SAVE_HOUSE(14, true);
					CLEAR_HELP(); // удаляем текст подсказки
					G_SHACK = 1;
					CHANGE_BLIP_SPRITE(property_blip[14], BLIP_SAFEHOUSE);
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
					SET_CHAR_COORDINATES(GetPlayerPed(), -120.805, 1237.01, 14.7873);// перемещаем игрока
					SET_CHAR_HEADING(GetPlayerPed(), -110.0);
					SET_OBJECT_COORDINATES(stend, 5.9, 6.8, 2.6);

					// камера
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, -128.662, 1232.28, 14.7873 ); // куда смотрит камера
					SET_CAM_POS			( camera, -146.885, 1240.61, 21.0725 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_CAM_FOV( camera, 45.0 );
					SET_WIDESCREEN_BORDERS( 1 );

					DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
					play_mission_complete_tune();
					SETTIMERA(0); //сбрасываем таймер 
					while (true)
					{
						SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
						SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
						SET_TEXT_EDGE(1, 0, 0, 0, 255); //
						SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
						SET_TEXT_CENTRE(1); // задаём центр текста
						DISPLAY_TEXT_WITH_NUMBER(0.5, 0.45, "SKUMBUY", 1000); //Skumole Shack purchased: $~1~
						WAIT( 0 );
						if ( TIMERA() > 6000 )
						{
							break;
						}
					}
					//Камера на двери
					POINT_CAM_AT_COORD	( camera, -127.331, 1234.95, 15.8352 ); // куда смотрит камера
					SET_CAM_POS			( camera, -128.922, 1240.21, 18.1244 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEBUYSAVE"); //You can now save your game here when not on a mission. To do this, walk through the doors of your property.
					SetTime(5000);

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
					G_ONMISSION = 0;

					help = 0;
					help2 = 0;
					G_GAME_PROGRESS += 1;
					SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
				}
			}
		}
		else
		{
			if ((help == 1) || (help2 == 1))
			{
				CLEAR_HELP(); // удаляем текст подсказки
				help = 0;
				help2 = 0;
			}
		}
//=========================================================================================================================================
//************************************************************* МЕТКИ НА КАРТЕ *************************************************************
		if (!G_ONMISSION)
		{
			if (G_COUNT == 0 && !DOES_BLIP_EXIST(property_blip[0]))
			{
				ADD_BLIP_FOR_COORD(-629.403, 255.797, 5.95213, &property_blip[0]);
				CHANGE_BLIP_SPRITE(property_blip[0], BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[0], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[0], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[0], "LG_20");
				CHANGE_BLIP_PRIORITY(property_blip[0], 0);
			}

			if (G_BUSINES_SA == 0 && !DOES_BLIP_EXIST(property_blip[1]))
			{
				ADD_BLIP_FOR_COORD(-584.339, -331.17, 6.98854, &property_blip[1]);
				CHANGE_BLIP_SPRITE(property_blip[1], BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[1], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[1], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[1], "LG_36");
				CHANGE_BLIP_PRIORITY(property_blip[1], 0);
			}

			if (G_PRON == 0 && !DOES_BLIP_EXIST(property_blip[2]))
			{
				ADD_BLIP_FOR_COORD(365.19, 1463.24, 4.84835, &property_blip[2]);
				CHANGE_BLIP_SPRITE(property_blip[2], BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[2], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[2], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[2], "LG_12");
				CHANGE_BLIP_PRIORITY(property_blip[2], 0);
			}

			if (G_ICECREAM == 0 && !DOES_BLIP_EXIST(property_blip[3]))
			{
				ADD_BLIP_FOR_COORD(-443.132, -37.314, 5.065, &property_blip[3]);
				CHANGE_BLIP_SPRITE(property_blip[3], BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[3], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[3], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[3], "LG_17");
				CHANGE_BLIP_PRIORITY(property_blip[3], 0);
			}

			if (G_CABS == 0 && !DOES_BLIP_EXIST(property_blip[4]))
			{
				ADD_BLIP_FOR_COORD(-569.498, 738.454, 5.354, &property_blip[4]);
				CHANGE_BLIP_SPRITE(property_blip[4], BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[4], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[4], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[4], "LG_18");
				CHANGE_BLIP_PRIORITY(property_blip[4], 0);
			}

			if (G_CLUB == 0 && !DOES_BLIP_EXIST(property_blip[5]))
			{
				ADD_BLIP_FOR_COORD(896.966, 472.341, 5.394, &property_blip[5]);
				CHANGE_BLIP_SPRITE(property_blip[5], BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[5], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[5], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[5], "LG_10");
				CHANGE_BLIP_PRIORITY(property_blip[5], 0);
			}

			if (G_COKERUN == 0 && !DOES_BLIP_EXIST(property_blip[6]))
			{
				ADD_BLIP_FOR_COORD(-224.504, -946.921, 7.458, &property_blip[6]);
				CHANGE_BLIP_SPRITE(property_blip[6], BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[6], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[6], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[6], "LG_09");
				CHANGE_BLIP_PRIORITY(property_blip[6], 0);
			}

			if (G_STRIP == 0 && !DOES_BLIP_EXIST(property_blip[7]))
			{
				ADD_BLIP_FOR_COORD(526.212, -932.28, 4.34719, &property_blip[7]);
				CHANGE_BLIP_SPRITE(property_blip[7], BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[7], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[7], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[7], "LG_37");
				CHANGE_BLIP_PRIORITY(property_blip[7], 0);
			}
		
			if (!DOES_BLIP_EXIST(property_blip[8]))
			{
				ADD_BLIP_FOR_COORD(860.838, 1140.87, 6.71937, &property_blip[8]);
				CHANGE_BLIP_SPRITE(property_blip[8], (G_SWANKO == 1) ? BLIP_SAFEHOUSE : BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[8], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[8], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[8], "LG_16");
				CHANGE_BLIP_PRIORITY(property_blip[8], 0);
			}

			if (!DOES_BLIP_EXIST(property_blip[9]))
			{
				ADD_BLIP_FOR_COORD(737.099, 909.333, 7.20204, &property_blip[9]);
				CHANGE_BLIP_SPRITE(property_blip[9], (G_LINKS == 1) ? BLIP_SAFEHOUSE : BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[9], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[9], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[9], "LG_16");
				CHANGE_BLIP_PRIORITY(property_blip[9], 0);
			}

			if (!DOES_BLIP_EXIST(property_blip[10]))
			{
				ADD_BLIP_FOR_COORD(-401.992, 1840.67, 5.63224, &property_blip[10]);
				CHANGE_BLIP_SPRITE(property_blip[10], (G_CONDO == 1) ? BLIP_SAFEHOUSE : BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[10], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[10], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[10], "LG_16");
				CHANGE_BLIP_PRIORITY(property_blip[10], 0);
			}

			if (!DOES_BLIP_EXIST(property_blip[11]))
			{
				ADD_BLIP_FOR_COORD(451.062, -968.568, 7.27016, &property_blip[11]);
				CHANGE_BLIP_SPRITE(property_blip[11], (G_HEIGHS == 1) ? BLIP_SAFEHOUSE : BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[11], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[11], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[11], "LG_16");
				CHANGE_BLIP_PRIORITY(property_blip[11], 0);
			}
				
			if (!DOES_BLIP_EXIST(property_blip[12]))
			{
				ADD_BLIP_FOR_COORD(520.688, -271.45, 5.74085, &property_blip[12]);
				CHANGE_BLIP_SPRITE(property_blip[12], (G_WS_1102 == 1) ? BLIP_SAFEHOUSE : BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[12], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[12], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[12], "LG_16");
				CHANGE_BLIP_PRIORITY(property_blip[12], 0);
			}
				
			if (!DOES_BLIP_EXIST(property_blip[13]))
			{
				ADD_BLIP_FOR_COORD(964.902, 1807.76, 12.1611, &property_blip[13]);
				CHANGE_BLIP_SPRITE(property_blip[13], (G_VP_3321 == 1) ? BLIP_SAFEHOUSE : BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[13], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[13], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[13], "LG_16");
				CHANGE_BLIP_PRIORITY(property_blip[13], 0);
			}

			if (!DOES_BLIP_EXIST(property_blip[14]))
			{
				ADD_BLIP_FOR_COORD(-127.205, 1235.3, 14.451, &property_blip[14]);
				CHANGE_BLIP_SPRITE(property_blip[14], (G_SHACK == 1) ? BLIP_SAFEHOUSE : BLIP_DARTS);
				CHANGE_BLIP_SCALE(property_blip[14], 1.1);
				SET_BLIP_AS_SHORT_RANGE(property_blip[14], 1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[14], "LG_16");
				CHANGE_BLIP_PRIORITY(property_blip[14], 0);
			}

			if (!DOES_BLIP_EXIST(property_blip[15]))
			{
				ADD_BLIP_FOR_COORD(661.2, -730.39, 15.59, &property_blip[15]);
				CHANGE_BLIP_SPRITE(property_blip[15], BLIP_SAFEHOUSE);
				CHANGE_BLIP_SCALE(property_blip[15], 1.1);
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(property_blip[15], "LG_16");
				CHANGE_BLIP_PRIORITY(property_blip[15], 0);
			}
		}
		else
		{
			int i;

			for (i = 0; i < 16; i++)
			{
				if (DOES_BLIP_EXIST(property_blip[i]))
				{
					REMOVE_BLIP(property_blip[i]);
				}
			}
		}
//==================================================================================================================================
//************************************************************* ГАРАЖИ *************************************************************

		// -----------------------------------  ГАРАЖ "Sunshine Autos" -----------------------------------
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -547.969, -298.255, 0.756, -558.294, -268.255, 6.3, 0 )) && (G_BUSINES_SA > 0))
		{
			OPEN_GARAGE("gdoor1");
			while (true)
			{
				if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -547.969, -298.255, 0.756, -558.294, -268.255, 6.3, 0 )) 
				{
					break;
				}
				WAIT(0);
			}
		}
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -558.917, -298.255, 0.756, -569.241, -268.255, 6.3, 0 )) && (G_BUSINES_SA > 0))
		{
			OPEN_GARAGE("gdoor2");
			while (true)
			{
				if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -558.917, -298.255, 0.756, -569.241, -268.255, 6.3, 0 ))
				{
					break;
				}
				WAIT(0);
			}
		}
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -570.586, -298.255, 0.756, -580.91, -268.255, 6.3, 0 )) && (G_BUSINES_SA > 0))
		{
			OPEN_GARAGE("gdoor3");
			while (true)
			{
				if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -570.586, -298.255, 0.756, -580.91, -268.255, 6.3, 0 )) 
				{
					break;
				}
				WAIT(0);
			}
		}
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -582.38, -298.255, 0.756, -592.704, -268.255, 6.3, 0 )) && (G_BUSINES_SA > 0))
		{
			OPEN_GARAGE("gdoor4");
			while (true)
			{
				if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -582.38, -298.255, 0.756, -592.704, -268.255, 6.3, 0 )) 
				{
					break;
				}
				WAIT(0);
			}
		}
		
		// -----------------------------------  ГАРАЖ "El Swanko Casa" -----------------------------------
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 891.239, 1168.599, 4.885, 877.344, 1174.218, 9.136, 0 )) && (G_SWANKO > 0))
		{
			OPEN_GARAGE("gdoor10");
			while (true)
			{
				if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 891.239, 1168.599, 4.885, 877.344, 1174.218, 9.136, 0 ))
				{
					break;
				}
				WAIT(0);
			}
		}
		// -----------------------------------  ГАРАЖ "Links View Apartment" -----------------------------------
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 739.701, 928.352, 6.802, 731.076, 942.836, 11.053, 0 )) && (G_LINKS > 0))
		{
			OPEN_GARAGE("gdoor11");
			while (true)
			{
				if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 739.701, 928.352, 6.802, 731.076, 942.836, 11.053, 0 ))
				{
					break;
				}
				WAIT(0);
			}
		}
		// -----------------------------------  ГАРАЖ "Hyman Condo" -----------------------------------
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -405.892, 1830.202, 4.844, -419.322, 1855.273, 10.931, 0 )) && (G_CONDO > 0))
		{
			OPEN_GARAGE("gdoor5");
			while (true)
			{
				if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -405.892, 1830.202, 4.844, -419.322, 1855.273, 10.931, 0 ))
				{
					break;
				}
				WAIT(0);
			}
		}
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -375.193, 1837.447, 4.844, -394.384, 1859.513, 10.931, 0 )) && (G_CONDO > 0))
		{
			OPEN_GARAGE("gdoor6");
			OPEN_GARAGE("gdoor7");
			while (true)
			{
				if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -375.193, 1837.447, 4.844, -394.384, 1859.513, 10.931, 0 ))
				{
					break;
				}
				WAIT(0);
			}
		}
		// -----------------------------------  ГАРАЖ "Ocean Heighs Aprt." -----------------------------------
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 461.113, -958.618, 4.129, 454.283, -943.668, 9.32, 0 )) && (G_HEIGHS > 0))
		{
			OPEN_GARAGE("gdoor9");
			while (true)
			{
				if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 461.113, -958.618, 4.129, 454.283, -943.668, 9.32, 0 ))
				{
					break;
				}
				WAIT(0);
			}
		}
		// -----------------------------------  ГАРАЖ "Vercetti Mansion" -----------------------------------
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 80.008, -18.195, 6.586, 69.992, 0.179, 10.322, 0 )) && (G_PROTECT > 0))
		{
			OPEN_GARAGE("gdoor8");
			while (true)
			{
				if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 80.008, -18.195, 6.586, 69.992, 0.179, 10.322, 0 ))
				{
					break;
				}
				WAIT(0);
			}
		}
	}
}
void main(void)
{
	business();
	while (TRUE) 
	{
		WAIT(0);
	}

}
