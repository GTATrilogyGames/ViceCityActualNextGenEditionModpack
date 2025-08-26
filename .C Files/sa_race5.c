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
Car car1, car2, car3;
Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11;
Texture fon, timer;
Blip Blip_r, Blip_r2, Blip_c1, Blip_c2, Blip_c3;
uint checkpoint;
float help_text;
float textur, skip, start_race, poziteon, time_m, time_s, zone;
float Blip_x, Blip_y, Blip_z, Blip_x2, Blip_y2, Blip_z2;
float PlayX, PlayY, PlayZ, PlayR, PlayH, play_cord, startX, startY, startZ, startH;
float Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, Ped1R, ped1_cord, SetSped1;
float Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, Ped2R, ped2_cord, SetSped2;
float Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, Ped3R, ped3_cord, SetSped3;
float water1X, water1Y, water1Z, water1R, water2X, water2Y, water2Z, water2R, water3X, water3Y, water3Z, water3R;
float sped_wall1, sped_wall2, sped_wall3, time_wall;

void position(void)
{
	//***************** позиция *****************
	GET_CHAR_COORDINATES(ped1,  &Ped1X, &Ped1Y, &Ped1Z);//вписываем координаты соперника в переменную
	GET_DISTANCE_BETWEEN_COORDS_3D( Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, &Ped1R);//проверка "игрок на координатах"
	GET_CHAR_COORDINATES(ped2,  &Ped2X, &Ped2Y, &Ped2Z);//вписываем координаты соперника в переменную
	GET_DISTANCE_BETWEEN_COORDS_3D( Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, &Ped2R);//проверка "игрок на координатах"
	GET_CHAR_COORDINATES(ped3,  &Ped3X, &Ped3Y, &Ped3Z);//вписываем координаты соперника в переменную
	GET_DISTANCE_BETWEEN_COORDS_3D( Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, &Ped3R);//проверка "игрок на координатах"
	GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
	GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, Blip_x, Blip_y, Blip_z, &PlayR);//проверка "игрок на координатах"

	if ((play_cord == ped1_cord) && (play_cord == ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			if (PlayR < Ped2R) //1
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 1;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 2;
				}
			}
			else if (PlayR > Ped2R)//0
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 2;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 3;
				}
			}
		}
		else if (PlayR > Ped1R)//0
		{
			if (PlayR < Ped2R) //1
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 2;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 3;
				}
			}
			else if (PlayR > Ped2R)//0
			{
				if (PlayR < Ped3R) //1
				{
					poziteon = 3;
				}
				else if (PlayR > Ped3R)//0
				{
					poziteon = 4;
				}
			}
		}
	}
	else if ((play_cord == ped1_cord) && (play_cord == ped2_cord) && (play_cord > ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			if (PlayR < Ped2R) //1
			{
				poziteon = 1;
			}
			else if (PlayR > Ped2R)//0
			{
				poziteon = 2;
			}
		}
		else if (PlayR > Ped1R) //0
		{
			if (PlayR < Ped2R) //1
			{
				poziteon = 2;
			}
			else if (PlayR > Ped2R)//0
			{
				poziteon = 3;
			}
		}
	}
	else if ((play_cord == ped1_cord) && (play_cord > ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 1;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 2;
			}
		}
		else if (PlayR > Ped1R) //0
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 2;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 3;
			}
		}
	}
	else if ((play_cord > ped1_cord) && (play_cord == ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped2R) //1
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 1;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 2;
			}
		}
		else if (PlayR > Ped2R) //0
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 2;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 3;
			}
		}
	}
	else if ((play_cord == ped1_cord) && (play_cord > ped2_cord) && (play_cord > ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			poziteon = 1;
		}
		else if (PlayR > Ped1R) //0
		{
			poziteon = 2;
		}
	}
	else if ((play_cord > ped1_cord) && (play_cord == ped2_cord) && (play_cord > ped3_cord))
	{
		if (PlayR < Ped2R) //1
		{
			poziteon = 1;
		}
		else if (PlayR > Ped2R) //0
		{
			poziteon = 2;
		}
	}
	else if ((play_cord > ped1_cord) && (play_cord > ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped3R) //1
		{
			poziteon = 1;
		}
		else if (PlayR > Ped3R) //0
		{
			poziteon = 2;
		}
	}
	else if ((play_cord > ped1_cord) && (play_cord > ped2_cord) && (play_cord > ped3_cord))
	{
		poziteon = 1;
	}
	else if ((play_cord == ped1_cord) && (play_cord == ped2_cord) && (play_cord < ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			if (PlayR < Ped2R) //1
			{
				poziteon = 2;
			}
			else if (PlayR > Ped2R)//0
			{
				poziteon = 3;
			}
		}
		else if (PlayR > Ped1R) //0
		{
			if (PlayR < Ped2R) //1
			{
				poziteon = 3;
			}
			else if (PlayR > Ped2R)//0
			{
			poziteon = 4;
			}
		}
	}
	else if ((play_cord == ped1_cord) && (play_cord < ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 2;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 3;
			}
		}
		else if (PlayR > Ped1R) //0
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 3;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 4;
			}
		}
	}
	else if ((play_cord < ped1_cord) && (play_cord == ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped2R) //1
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 2;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 3;
			}
		}
		else if (PlayR > Ped2R) //0
		{
			if (PlayR < Ped3R) //1
			{
				poziteon = 3;
			}
			else if (PlayR > Ped3R)//0
			{
				poziteon = 4;
			}
		}
	}
	else if ((play_cord == ped1_cord) && (play_cord < ped2_cord) && (play_cord < ped3_cord))
	{
		if (PlayR < Ped1R) //1
		{
			poziteon = 3;
		}
		else if (PlayR > Ped1R) //0
		{
			poziteon = 4;
		}
	}
	else if ((play_cord < ped1_cord) && (play_cord == ped2_cord) && (play_cord < ped3_cord))
	{
		if (PlayR < Ped2R) //1
		{
			poziteon = 3;
		}
		else if (PlayR > Ped2R) //0
		{
			poziteon = 4;
		}
	}
	else if ((play_cord < ped1_cord) && (play_cord < ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped3R) //1
		{
			poziteon = 3;
		}
		else if (PlayR > Ped3R) //0
		{
			poziteon = 4;
		}
	}
	else if ((play_cord < ped1_cord) && (play_cord < ped2_cord) && (play_cord < ped3_cord))
	{
		poziteon = 4;
	}
	//======
	else if ((play_cord > ped1_cord) && (play_cord < ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped3R) //1
		{
			poziteon = 2;
		}
		else //0
		{
			poziteon = 3;
		}
	}
	else if ((play_cord > ped1_cord) && (play_cord == ped2_cord) && (play_cord < ped3_cord))
	{
		if (PlayR < Ped2R) //1
		{
			poziteon = 2;
		}
		else //0
		{
			poziteon = 3;
		}
	}

	else if ((play_cord < ped1_cord) && (play_cord > ped2_cord) && (play_cord == ped3_cord))
	{
		if (PlayR < Ped3R) //1
		{
			poziteon = 2;
		}
		else //0
		{
			poziteon = 3;
		}
	}
	else if ((play_cord < ped1_cord) && (play_cord == ped2_cord) && (play_cord > ped3_cord))
	{
		if (PlayR < Ped2R) //1
		{
			poziteon = 2;
		}
		else //0
		{
			poziteon = 3;
		}
	}
	else if ((play_cord > ped1_cord) && (play_cord < ped2_cord) && (play_cord < ped3_cord))
	{
		poziteon = 3;
	}
	else if ((play_cord > ped1_cord) && (play_cord > ped2_cord) && (play_cord < ped3_cord))
	{
		poziteon = 2;
	}
	else if ((play_cord > ped1_cord) && (play_cord < ped2_cord) && (play_cord > ped3_cord))
	{
		poziteon = 2;
	}

	else if ((play_cord < ped1_cord) && (play_cord > ped2_cord) && (play_cord > ped3_cord))
	{
		poziteon = 2;
	}
	else if ((play_cord < ped1_cord) && (play_cord > ped2_cord) && (play_cord < ped3_cord))
	{
		poziteon = 3;
	}
	else if ((play_cord < ped1_cord) && (play_cord > ped2_cord) && (play_cord < ped3_cord))
	{
		poziteon = 3;
	}
	return;
}
void setup_draw_text(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.156, 0.267);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
	return;
}

void setup_draw_value(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.26, 0.445);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
	return;
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
void sa_race(void)
{
	if (!IS_BIT_SET(G_SA_RACE, 4))
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}

	uint Ped_hp4, Ped_hp5, Ped_hp6, Ped_hp7, Ped_hp8, Ped_hp9, Ped_hp10, Ped_hp11;
	
	help_text = 0;
	skip = 0;
	zone = 1;
	start_race = 0;
	time_m = 0;
	time_s = 0;

	startX = 633.631;
	startY = 168.35;
	startZ = 4.46113;
	startH = 345.0;

	Blip_x = 654.582;
	Blip_y = 243.813;
	Blip_z = 6.361;
	Blip_x2 = 686.71;
	Blip_y2 = 309.064;
	Blip_z2 = 4.8523;
	play_cord = 1;

	ped1B_x = 654.582;
	ped1B_y = 243.813;
	ped1B_z = 6.361;
	SetSped1 = 0;
	ped1_cord = 1;

	ped2B_x = 654.582;
	ped2B_y = 243.813;
	ped2B_z = 6.361;
	SetSped2 = 0;
	ped2_cord = 1;

	ped3B_x = 654.582;
	ped3B_y = 243.813;
	ped3B_z = 6.361;
	SetSped3 = 0;
	ped3_cord = 1;

	SWITCH_ROADS_OFF( 715.988, 109.372, -1.286, 602.218, 333.631, 80.0 );// ОТКЛЮЧАЕМ ПУТИ ТРАФИКА
	//SET_CAR_DENSITY_MULTIPLIER(0.4);// отключаем пути

	ADD_BLIP_FOR_COORD(startX, startY, startZ, &Blip_r);//создаем иконку на радаре
	CHANGE_BLIP_SPRITE(Blip_r, BLIP_OBJECTIVE);//текстура иконки на радаре "BLIP_FINISH_LINE"
	CHANGE_BLIP_COLOUR(Blip_r, 5);   //цвет иконка на радаре (0=белая 5=розовый 19=жёлтый)
	CHANGE_BLIP_SCALE(Blip_r, 0.6); // масштаб иконки на радаре
	CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_r, "NE_POINT");//иконка на радаре называние в истории карты ""

	textur = LOAD_TXD( "sunshine_race" );
	fon = GET_TEXTURE( textur, "fon_hud" );
	timer = GET_TEXTURE( textur, "timer_hud" );

	uint CarM1 = MODEL_INFERNUS;//Переменная "Car2" = модели машины
	uint CarM2 = MODEL_BANSHEE;//Переменная "Car2" = модели машины
	uint CarM3 = MODEL_SUPERGT;//Переменная "Car2" = модели машины
	uint PedM1 = MODEL_F_Y_CDRESS_01;////Переменная "Ped1" = модели нужного педа
	uint PedM2 = MODEL_M_Y_BOHO_01;////Переменная "Ped1" = модели нужного педа
	uint PedM3 = MODEL_M_Y_GIRI_LO_01;////Переменная "Ped1" = модели нужного педа

	uint PedM4 = MODEL_F_Y_PMANHAT_02;////Переменная "Ped1" = модели нужного педа
	uint PedM5 = MODEL_F_Y_PVILLBO_02;////Переменная "Ped1" = модели нужного педа
	uint PedM6 = MODEL_M_Y_MODO;////Переменная "Ped1" = модели нужного педа
	uint PedM7 = MODEL_M_Y_PCOOL_02;////Переменная "Ped1" = модели нужного педа

	// загружаем анимации
	REQUEST_ANIMS( "vcNE_race_funs" );//загружаем файл с анимацией
	while (!HAVE_ANIMS_LOADED( "vcNE_race_funs" )) WAIT(0);

	REQUEST_MODEL(CarM1);//загрузка модели машины из переменной
	while (!HAS_MODEL_LOADED(CarM1));//проверка "машина загрузилась" если нет то начанаем с начало
	CREATE_CAR(CarM1, (-4*COS((1-startH))+0*SIN((1-startH)))+startX, (0*COS((1-startH))-(-4*SIN((1-startH))))+startY, startZ, &car1, TRUE);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
	SET_CAR_HEADING(car1, startH);//градус поворота машины

	REQUEST_MODEL(CarM2);//загрузка модели машины из переменной
	while (!HAS_MODEL_LOADED(CarM2));//проверка "машина загрузилась" если нет то начанаем с начало
	CREATE_CAR(CarM2, (-4*COS((1-startH))+6*SIN((1-startH)))+startX, (6*COS((1-startH))-(-4*SIN((1-startH))))+startY, startZ, &car2, TRUE);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
	SET_CAR_HEADING(car2, startH);//градус поворота машины

	REQUEST_MODEL(CarM3);//загрузка модели машины из переменной
	while (!HAS_MODEL_LOADED(CarM3));//проверка "машина загрузилась" если нет то начанаем с начало
	CREATE_CAR(CarM3, (0*COS((1-startH))+6*SIN((1-startH)))+startX, (6*COS((1-startH))-(0*SIN((1-startH))))+startY, startZ, &car3, TRUE);// создаём машину,(Модель в переменной"Car2"),("&a2"переменная в корорую вписона загрузка машины) на нужных координатах
	SET_CAR_HEADING(car3, startH);//градус поворота машины

	REQUEST_MODEL(PedM1);//загрузка модели любого педа из переменной
	while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
	CREATE_CHAR_INSIDE_CAR(car1, 1, PedM1, &ped1);//создаём педа за рулём автомобиля

	REQUEST_MODEL(PedM2);//загрузка модели любого педа из переменной
	while (!HAS_MODEL_LOADED(PedM2));////проверка "пед загрузился" если нет то начанаем с начало
	CREATE_CHAR_INSIDE_CAR(car2, 1, PedM2, &ped2);//создаём педа за рулём автомобиля

	REQUEST_MODEL(PedM3);//загрузка модели любого педа из переменной
	while (!HAS_MODEL_LOADED(PedM3));////проверка "пед загрузился" если нет то начанаем с начало
	CREATE_CHAR_INSIDE_CAR(car3, 1, PedM3, &ped3);//создаём педа за рулём автомобиля

	REQUEST_MODEL(PedM4);//загрузка модели любого педа из переменной
	while (!HAS_MODEL_LOADED(PedM4));////проверка "пед загрузился" если нет то начанаем с начало

	REQUEST_MODEL(PedM5);//загрузка модели любого педа из переменной
	while (!HAS_MODEL_LOADED(PedM5));////проверка "пед загрузился" если нет то начанаем с начало

	REQUEST_MODEL(PedM6);//загрузка модели любого педа из переменной
	while (!HAS_MODEL_LOADED(PedM6));////проверка "пед загрузился" если нет то начанаем с начало

	REQUEST_MODEL(PedM7);//загрузка модели любого педа из переменной
	while (!HAS_MODEL_LOADED(PedM7));////проверка "пед загрузился" если нет то начанаем с начало

	CREATE_CHAR (26, PedM1, (3.5*COS((1-startH))+5.1*SIN((1-startH)))+startX, (5.1*COS((1-startH))-(3.5*SIN((1-startH))))+startY, startZ, &ped4, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах
	CREATE_CHAR (26, PedM2, (3.7*COS((1-startH))+3.7*SIN((1-startH)))+startX, (3.7*COS((1-startH))-(3.7*SIN((1-startH))))+startY, startZ, &ped5, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах
	CREATE_CHAR (26, PedM3, (3.4*COS((1-startH))+2.0*SIN((1-startH)))+startX, (2.0*COS((1-startH))-(3.4*SIN((1-startH))))+startY, startZ, &ped6, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах
	CREATE_CHAR (26, PedM4, (-7.8*COS((1-startH))+5.8*SIN((1-startH)))+startX, (5.8*COS((1-startH))-(-7.8*SIN((1-startH))))+startY, startZ, &ped7, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах
	CREATE_CHAR (26, PedM5, (-8.9*COS((1-startH))+3.8*SIN((1-startH)))+startX, (3.8*COS((1-startH))-(-8.9*SIN((1-startH))))+startY, startZ, &ped8, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах
	CREATE_CHAR (26, PedM6, (-7.6*COS((1-startH))+3.4*SIN((1-startH)))+startX, (3.4*COS((1-startH))-(-7.6*SIN((1-startH))))+startY, startZ, &ped9, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах
	CREATE_CHAR (26, PedM7, (-8.3*COS((1-startH))+1.8*SIN((1-startH)))+startX, (1.8*COS((1-startH))-(-8.3*SIN((1-startH))))+startY, startZ, &ped10, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах
	CREATE_CHAR (26, PedM1, (-7.7*COS((1-startH))+0.2*SIN((1-startH)))+startX, (0.2*COS((1-startH))-(-7.7*SIN((1-startH))))+startY, startZ, &ped11, TRUE);// создаём педа,(Модель в переменной"Ped1"),("&p1"переменная в корорую вписона загрузка педа) на нужных координатах

	SET_CHAR_PROOFS(ped1, TRUE, TRUE, TRUE, TRUE, TRUE);//делает педа бесмертным
	SET_CHAR_PROOFS(ped2, TRUE, TRUE, TRUE, TRUE, TRUE);//делает педа бесмертным
	SET_CHAR_PROOFS(ped3, TRUE, TRUE, TRUE, TRUE, TRUE);//делает педа бесмертным
	SET_CAR_PROOFS(car1, TRUE, TRUE, TRUE, TRUE, TRUE);//делает машину бесмертной
	SET_CAR_PROOFS(car2, TRUE, TRUE, TRUE, TRUE, TRUE);//делает машину бесмертной
	SET_CAR_PROOFS(car3, TRUE, TRUE, TRUE, TRUE, TRUE);//делает машину бесмертной
	SET_CAN_BURST_CAR_TYRES(car1, 0); // шины автомобиля нельзя повредить
	SET_CAN_BURST_CAR_TYRES(car2, 0); // шины автомобиля нельзя повредить
	SET_CAN_BURST_CAR_TYRES(car3, 0); // шины автомобиля нельзя повредить
	LOCK_CAR_DOORS(car1, 3); //блокируем двери автомобиля для игрока
	LOCK_CAR_DOORS(car2, 3); //блокируем двери автомобиля для игрока
	LOCK_CAR_DOORS(car3, 3); //блокируем двери автомобиля для игрока

	SET_CHAR_HEADING(ped4, 75.0+startH);
	SET_CHAR_HEADING(ped5, 95.0+startH);
	SET_CHAR_HEADING(ped6, 85.0+startH);
	SET_CHAR_HEADING(ped7, -95.0+startH);
	SET_CHAR_HEADING(ped8, -95.0+startH);
	SET_CHAR_HEADING(ped9, -80.0+startH);
	SET_CHAR_HEADING(ped10, -110.0+startH);
	SET_CHAR_HEADING(ped11, -90.0+startH);

	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped4, "crowd_excited_a", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "crowd_excited_b", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "crowd_negative", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "stactic_celeb_a", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped8, "crowd_positive", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped9, "crowd_negative", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped10, "crowd_excited_b", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
	TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped11, "crowd_excited_a", "vcNE_race_funs", 1.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе

	CLEAR_AREA( startX, startY, startZ, 65.0, 1);//очещаем зону загрузки
	GET_CAR_HEADING(car1, &startH); //получаем угол поворота игрока
	while(true)
	{
		WAIT(0);
		DRAW_CHECKPOINT( startX, startY, startZ, 2, 160, 116, 209);//создание чекпойнт на координатах и его цвет
		GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
		GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, startX, startY, startZ, &PlayR);//проверка "игрок на координатах"
		if ( PlayR < 2.0)
		{
			if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) //проверяем "игрок в машине"
			{
				GET_CHAR_HEADING(GetPlayerPed(), &PlayH); //получаем угол поворота игрока
				if ((PlayH > (startH-20)) && (PlayH < (startH+20))) //проверяем "угол игрока в допустимых диапазонах"
				{
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
					break;
				}
				else
				{
					if (help_text == 0)
					{
						PRINT_STRING_IN_STRING("string", "VC2_RACE_TEXT6", 350, 1);//Выводим на экран сообщение "Выровняйте машину"
						help_text = 1;
					}
				}
			}
			else
			{
				if (help_text == 0)
				{
					PRINT_STRING_IN_STRING("string", "VC2_RACE_TEXT7", 350, 1);//Выводим на экран сообщение "Найдите подходящую машину"
					help_text = 1;
				}
			}
		}
		else
		{
			if (help_text == 1)
			{
				help_text = 0;
			}
		}
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (IS_CHAR_TOUCHING_VEHICLE(GetPlayerPed(), car1))) // если игрок поцарапал машину соперника
		{
			start_race = 1; //переменная с пропуском заморозки игрока
			break;
		}
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (IS_CHAR_TOUCHING_VEHICLE(GetPlayerPed(), car2))) // если игрок поцарапал машину соперника
		{
			start_race = 1; //переменная с пропуском заморозки игрока
			break;
		}
		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (IS_CHAR_TOUCHING_VEHICLE(GetPlayerPed(), car3))) // если игрок поцарапал машину соперника
		{
			start_race = 1; //переменная с пропуском заморозки игрока
			break;
		}
		
		//получаем здоровье статистов
		GET_CHAR_HEALTH(ped4, &Ped_hp4);
		GET_CHAR_HEALTH(ped5, &Ped_hp5);
		GET_CHAR_HEALTH(ped6, &Ped_hp6);
		GET_CHAR_HEALTH(ped7, &Ped_hp7);
		GET_CHAR_HEALTH(ped8, &Ped_hp8);
		GET_CHAR_HEALTH(ped9, &Ped_hp9);
		GET_CHAR_HEALTH(ped10, &Ped_hp10);
		GET_CHAR_HEALTH(ped11, &Ped_hp11);
		if (IS_CHAR_SHOOTING_IN_AREA(GetPlayerPed(), startX-25, startY-25, startX+25, startY+25, 0))//проверка Игрок начал пальбу на старте
		{
			PRINT_STRING_IN_STRING("string", "VC2_RACE_TEXT8", 3500, 1);//Выводим на экран сообщение "Кто-то открыл стрельбу,гонка отменина"
			skip = 1;
			PANIC_SCREAM(ped4);
			PANIC_SCREAM(ped5);
			PANIC_SCREAM(ped6);
			PANIC_SCREAM(ped7);
			PANIC_SCREAM(ped8);
			PANIC_SCREAM(ped9);
			PANIC_SCREAM(ped10);
			PANIC_SCREAM(ped11);
			break;
		}
		else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
		{
			skip = 1;
			break;
		}
		else if ((IS_CHAR_IN_AREA_2D( GetPlayerPed(), startX-30, startY-30, startX+30, startY+30, 0 )) && (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0)))
		{
			PRINT_STRING_IN_STRING("string", "VC2_RACE_TEXT12", 3500, 1);//Выводим на экран сообщение "Ты притащил на гонку копов, они разогнали всех участников."
			skip = 1;
			PANIC_SCREAM(ped4);
			PANIC_SCREAM(ped5);
			PANIC_SCREAM(ped6);
			PANIC_SCREAM(ped7);
			PANIC_SCREAM(ped8);
			PANIC_SCREAM(ped9);
			PANIC_SCREAM(ped10);
			PANIC_SCREAM(ped11);
			break;
		}
		else if (( Ped_hp4 < 195 ) || ( Ped_hp5 < 195 ) || ( Ped_hp6 < 195 ) || ( Ped_hp7 < 195 ) || ( Ped_hp8 < 195 ) || ( Ped_hp9 < 195 ) || ( Ped_hp10 < 195 ) || ( Ped_hp11 < 195 ))
		{
			PRINT_STRING_IN_STRING("string", "VC2_RACE_TEXT9", 3500, 1);//Выводим на экран сообщение "человек из толпы пострадал. Гонка отменина"
			skip = 1;
			PANIC_SCREAM(ped4);
			PANIC_SCREAM(ped5);
			PANIC_SCREAM(ped6);
			PANIC_SCREAM(ped7);
			PANIC_SCREAM(ped8);
			PANIC_SCREAM(ped9);
			PANIC_SCREAM(ped10);
			PANIC_SCREAM(ped11);
			break;
		}
	}
	// сама гонка тут
	if (skip == 0)
	{
		REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
		ADD_BLIP_FOR_CHAR(ped1, &Blip_c1);
		CHANGE_BLIP_SPRITE(Blip_c1, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(Blip_c1, 12);   //цвет иконка на радаре (0=белая)
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_c1, "NE_RACE1");//иконка на радаре "Blip01" называние в истории карты
		CHANGE_BLIP_SCALE(Blip_c1, 0.77999990); // масштаб иконки на радаре

		ADD_BLIP_FOR_CHAR(ped2, &Blip_c2);
		CHANGE_BLIP_SPRITE(Blip_c2, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(Blip_c2, 8);   //цвет иконка на радаре (0=белая)
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_c2, "NE_RACE1");//иконка на радаре "Blip01" называние в истории карты
		CHANGE_BLIP_SCALE(Blip_c2, 0.77999990); // масштаб иконки на радаре

		ADD_BLIP_FOR_CHAR(ped3, &Blip_c3);
		CHANGE_BLIP_SPRITE(Blip_c3, BLIP_DESTINATION);//иконка на радаре "Blip01" равна "BLIP_FINISH_LINE"
		CHANGE_BLIP_COLOUR(Blip_c3, 19);   //цвет иконка на радаре (0=белая)
		CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip_c3, "NE_RACE1");//иконка на радаре "Blip01" называние в истории карты
		CHANGE_BLIP_SCALE(Blip_c3, 0.77999990); // масштаб иконки на радаре

		SETTIMERA( 0 );
		SETTIMERB( 0 );
		while(true)
		{
			WAIT(0);
			if (start_race == 0)
			{
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
					if (TIMERA() > 999)
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
					if (TIMERA() > 999)
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
					if (TIMERA() > 999)
					{
						break;
					}
					WAIT(0);
				}
				start_race = 2;
			}

			// гонка тут
			if (start_race == 1)
			{
				if (TIMERA() < 900)
				{
					SET_TEXT_FONT(4);
					SET_TEXT_COLOUR(235, 115, 18, 255);
					SET_TEXT_SCALE(0.5, 0.7);
					SET_TEXT_EDGE(2, 0, 0, 0, 255);
					SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
					SET_TEXT_CENTRE(1);
					DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "VC2_RACE_TEXT11", 1); // пишем "3...2...1... GO"
				}
				else
				{
					start_race = 3;
				}
			}
			else if (start_race == 2)
			{
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
					start_race = 3;
				}
			}
			else if (start_race == 3)
			{
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// Размораживаем игрока
				SET_CAR_DENSITY_MULTIPLIER(0.6);// отключаем пути
				PLAY_AUDIO_EVENT( "FRONTEND_GAME_PICKUP_CHECKPOINT" );
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)

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
				start_race = 99;
			}
			//прячим толпу
			if (zone == 1)
			{
				if (!IS_CHAR_IN_AREA_2D( GetPlayerPed(), startX-50, startY-50, startX+50, startY+50, 0 ))
				{
					SET_CHAR_COORDINATES(ped4, -925, -402, 10.);// убераем педа из кадра
					SET_CHAR_COORDINATES(ped5, -926, -402, 10.);// убераем педа из кадра
					SET_CHAR_COORDINATES(ped6, -927, -402, 10.);// убераем педа из кадра
					SET_CHAR_COORDINATES(ped7, -926, -401, 10.);// убераем педа из кадра
					SET_CHAR_COORDINATES(ped8, -926, -402, 10.);// убераем педа из кадра
					SET_CHAR_COORDINATES(ped9, -926, -403, 10.);// убераем педа из кадра
					SET_CHAR_COORDINATES(ped10, -925, -401, 10.);// убераем педа из кадра
					SET_CHAR_COORDINATES(ped11, -927, -403, 10.);// убераем педа из кадра
					zone = 0;
				}
			}
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
					Blip_x2 = 728.899;
					Blip_y2 = 398.234;
					Blip_z2 = 6.1339;
				}
				else if (play_cord == 3)
				{
					Blip_x2 = 762.479;
					Blip_y2 = 515.3703;
					Blip_z2 = 5.3388;
				}
				else if (play_cord == 4)
				{
					Blip_x2 = 821.747;
					Blip_y2 = 553.8195;
					Blip_z2 = 9.1745;
				}
				else if (play_cord == 5)
				{
					Blip_x2 = 877.209;
					Blip_y2 = 622.5439;
					Blip_z2 = 4.9166;
				}
				else if (play_cord == 6)
				{
					Blip_x2 = 831.9408;
					Blip_y2 = 746.423;
					Blip_z2 = 4.85;
				}
				else if (play_cord == 7)
				{
					Blip_x2 = 862.3534;
					Blip_y2 = 798.3797;
					Blip_z2 = 5.4397;
				}
				else if (play_cord == 8)
				{
					Blip_x2 = 877.635;
					Blip_y2 = 941.029;
					Blip_z2 = 5.4397;
				}
				else if (play_cord == 9)
				{
					Blip_x2 = 903.734;
					Blip_y2 = 1037.302;
					Blip_z2 = 5.483;
				}
				else if (play_cord == 10)
				{
					Blip_x2 = 929.0539;
					Blip_y2 = 1189.219;
					Blip_z2 = 4.8803;
				}
				else if (play_cord == 11)
				{
					Blip_x2 = 980.899;
					Blip_y2 = 1284.469;
					Blip_z2 = 5.180801;
				}
				else if (play_cord == 12)
				{
					Blip_x2 = 989.338;
					Blip_y2 = 1424.329;
					Blip_z2 = 8.5641;
				}
				else if (play_cord == 13)
				{
					Blip_x2 = 945.934;
					Blip_y2 = 1537.66;
					Blip_z2 = 11.9283;
				}
				else if (play_cord == 14)
				{
					Blip_x2 = 933.877;
					Blip_y2 = 1654.62;
					Blip_z2 = 10.2929;
				}
				else if (play_cord == 15)
				{
					Blip_x2 = 955.579;
					Blip_y2 = 1765.54;
					Blip_z2 = 10.2502;
				}
				else if (play_cord == 16)
				{
					Blip_x2 = 865.152;
					Blip_y2 = 1814.97;
					Blip_z2 = 11.0003;
				}
				else if (play_cord == 17)
				{
					Blip_x2 = 749.406;
					Blip_y2 = 1814.97;
					Blip_z2 = 11.1761;
				}
				else if (play_cord == 18)
				{
					Blip_x2 = 652.951;
					Blip_y2 = 1776.39;
					Blip_z2 = 11.18;
				}
				else if (play_cord == 19)
				{
					Blip_x2 = 716.852;
					Blip_y2 = 1731.78;
					Blip_z2 = 11.7968;
				}
				else if (play_cord == 20)
				{
					Blip_x2 = 703.59;
					Blip_y2 = 1654.62;
					Blip_z2 = 13.3989;
				}
				else if (play_cord == 21)
				{
					Blip_x2 = 740.966;
					Blip_y2 = 1556.95;
					Blip_z2 = 6.9725;
				}
				else if (play_cord == 22)
				{
					Blip_x2 = 753.023;
					Blip_y2 = 1446.031;
					Blip_z2 = 4.8582;
				}
				else if (play_cord == 23)
				{
					Blip_x2 = 727.703;
					Blip_y2 = 1333.902;
					Blip_z2 = 4.849;
				}
				else if (play_cord == 24)
				{
					Blip_x2 = 652.951;
					Blip_y2 = 1254.326;
					Blip_z2 = 4.849;
				}
				else if (play_cord == 25)
				{
					Blip_x2 = 610.7509;
					Blip_y2 = 1204.893;
					Blip_z2 = 4.849;
				}
				else if (play_cord == 26)
				{
					Blip_x2 = 679.476;
					Blip_y2 = 1200.07;
					Blip_z2 = 4.8548;
				}
				else if (play_cord == 27)
				{
					Blip_x2 = 767.4909;
					Blip_y2 = 1203.687;
					Blip_z2 = 4.8524;
				}
				else if (play_cord == 28)
				{
					Blip_x2 = 813.307;
					Blip_y2 = 1177.162;
					Blip_z2 = 5.0442;
				}
				else if (play_cord == 29)
				{
					Blip_x2 = 816.925;
					Blip_y2 = 1090.352;
					Blip_z2 = 5.3795;
				}
				else if (play_cord == 30)
				{
					Blip_x2 = 813.307;
					Blip_y2 = 1020.422;
					Blip_z2 = 5.6054;
				}
				else if (play_cord == 31)
				{
					Blip_x2 = 919.408;
					Blip_y2 = 1013.188;
					Blip_z2 = 5.4553;
				}
				else if (play_cord == 32)
				{
					Blip_x2 = 961.9505;
					Blip_y2 = 990.4267;
					Blip_z2 = 4.8644;
				}
				else if (play_cord == 33)
				{
					Blip_x2 = 942.109;
					Blip_y2 = 886.4781;
					Blip_z2 = 4.8673;
				}
				else if (play_cord == 34)
				{
					Blip_x2 = 927.3036;
					Blip_y2 = 778.078;
					Blip_z2 = 4.901301;
				}
				else if (play_cord == 35)
				{
					Blip_x2 = 931.7009;
					Blip_y2 = 671.977;
					Blip_z2 = 4.866;
				}
				else if (play_cord == 36)
				{
					Blip_x2 = 910.969;
					Blip_y2 = 627.3666;
					Blip_z2 = 5.1941;
				}
				else if (play_cord == 37)
				{
					Blip_x2 = 827.776;
					Blip_y2 = 558.6422;
					Blip_z2 = 9.535401;
				}
				else if (play_cord == 38)
				{
					Blip_x2 = 760.6492;
					Blip_y2 = 500.9478;
					Blip_z2 = 4.8861;
				}
				else if (play_cord == 39)
				{
					Blip_x2 = 733.732;
					Blip_y2 = 405.519;
					Blip_z2 = 5.776;
				}
				else if (play_cord == 40)
				{
					Blip_x2 = 722.881;
					Blip_y2 = 350.057;
					Blip_z2 = 5.4278;
				}
				else if (play_cord == 41)
				{
					Blip_x2 = 799.4901;
					Blip_y2 = 310.27;
					Blip_z2 = 5.7668;
				}
				else if (play_cord == 42)
				{
					Blip_x2 = 789.6779;
					Blip_y2 = 230.9841;
					Blip_z2 = 5.8559;
				}
				else if (play_cord == 43)
				{
					Blip_x2 = 716.852;
					Blip_y2 = 171.8796;
					Blip_z2 = 5.7751;
				}
				else if (play_cord == 44)
				{
					Blip_x2 = 664.6887;
					Blip_y2 = 108.0546;
					Blip_z2 = 5.7829;
				}
				else if (play_cord == 45)
				{
					Blip_x2 = 648.8611;
					Blip_y2 = 14.875;
					Blip_z2 = 5.7829;
				}
				else if (play_cord == 46)
				{
					Blip_x2 = 611.8346;
					Blip_y2 = 6.434998;
					Blip_z2 = 5.5379;
				}
				else if (play_cord == 47)
				{
					Blip_x2 = 615.3787;
					Blip_y2 = 90.23642;
					Blip_z2 = 4.8402;
				}
				else if (play_cord == 48)
				{
					Blip_x2 = 629.7757;
					Blip_y2 = 161.97;
					Blip_z2 = 4.5263;
				}
				else if (play_cord == 49)
				{
					Blip_x2 = Blip_x2; 
					Blip_y2 = Blip_y2;
					Blip_z2 = Blip_z2;
				}
				else if (play_cord == 50)
				{
					skip = 2;
					break;
				}
				if (play_cord < 49)
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
					if (play_cord < 48)
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

//============================== соперник 1 ==============================
			GET_CHAR_COORDINATES(ped1,  &Ped1X, &Ped1Y, &Ped1Z);//вписываем координаты соперника в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( Ped1X, Ped1Y, Ped1Z, ped1B_x, ped1B_y, ped1B_z, &Ped1R);//проверка "игрок на координатах"
			if ( Ped1R < 55.0)
			{
				if (SetSped1 == 0)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 95.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				}
				if (SetSped1 == 1)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				}
				if (SetSped1 == 2)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 12.5, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				}
			}
			if ( Ped1R < 10.0)
			{
				ped1_cord += 1;
				water1X = ped1B_x;
				water1Y = ped1B_y;
				water1Z = ped1B_z;
				GET_CAR_HEADING(car1, &water1R);

				if (ped1_cord == 2)
				{
					ped1B_x = 686.71;
					ped1B_y = 309.064;
					ped1B_z = 4.8523;
					SetSped1 = 0;
				}
				else if (ped1_cord == 3)
				{
					ped1B_x = 728.899;
					ped1B_y = 398.234;
					ped1B_z = 6.1339;
					SetSped1 = 0;
				}
				else if (ped1_cord == 4)
				{
					ped1B_x = 762.479;
					ped1B_y = 515.3703;
					ped1B_z = 5.3388;
					SetSped1 = 1;
				}
				else if (ped1_cord == 5)
				{
					ped1B_x = 821.747;
					ped1B_y = 553.8195;
					ped1B_z = 9.1745;
					SetSped1 = 0;
				}
				else if (ped1_cord == 6)
				{
					ped1B_x = 876.495;
					ped1B_y = 601.993;
					ped1B_z = 4.9166;
					SetSped1 = 1;
				}
				else if (ped1_cord == 7)
				{
					ped1B_x = 833.618;
					ped1B_y = 755.384;
					ped1B_z = 4.85;
					SetSped1 = 1;
				}
				else if (ped1_cord == 8)
				{
					ped1B_x = 861.483;
					ped1B_y = 820.662;
					ped1B_z = 5.4397;
					SetSped1 = 0;
				}
				else if (ped1_cord == 9)
				{
					ped1B_x = 877.635;
					ped1B_y = 941.029;
					ped1B_z = 5.4397;
					SetSped1 = 0;
				}
				else if (ped1_cord == 10)
				{
					ped1B_x = 903.734;
					ped1B_y = 1037.302;
					ped1B_z = 5.483;
					SetSped1 = 0;
				}
				else if (ped1_cord == 11)
				{
					ped1B_x = 902.363;
					ped1B_y = 1175.82;
					ped1B_z = 4.8803;
					SetSped1 = 2;
				}
				else if (ped1_cord == 12)
				{
					ped1B_x = 980.899;
					ped1B_y = 1284.469;
					ped1B_z = 5.180801;
					SetSped1 = 0;
				}
				else if (ped1_cord == 13)
				{
					ped1B_x = 989.338;
					ped1B_y = 1424.329;
					ped1B_z = 8.5641;
					SetSped1 = 0;
				}
				else if (ped1_cord == 14)
				{
					ped1B_x = 945.934;
					ped1B_y = 1537.66;
					ped1B_z = 11.9283;
					SetSped1 = 0;
				}
				else if (ped1_cord == 15)
				{
					ped1B_x = 933.877;
					ped1B_y = 1654.62;
					ped1B_z = 10.2929;
					SetSped1 = 0;
				}
				else if (ped1_cord == 16)
				{
					ped1B_x = 955.579;
					ped1B_y = 1765.54;
					ped1B_z = 10.2502;
					SetSped1 = 2;
				}
				else if (ped1_cord == 17)
				{
					ped1B_x = 865.152;
					ped1B_y = 1814.97;
					ped1B_z = 11.0003;
					SetSped1 = 0;
				}
				else if (ped1_cord == 18)
				{
					ped1B_x = 749.406;
					ped1B_y = 1814.97;
					ped1B_z = 11.1761;
					SetSped1 = 0;
				}
				else if (ped1_cord == 19)
				{
					ped1B_x = 652.951;
					ped1B_y = 1776.39;
					ped1B_z = 11.18;
					SetSped1 = 1;
				}
				else if (ped1_cord == 20)
				{
					ped1B_x = 716.852;
					ped1B_y = 1731.78;
					ped1B_z = 11.7968;
					SetSped1 = 0;
				}
				else if (ped1_cord == 21)
				{
					ped1B_x = 703.59;
					ped1B_y = 1654.62;
					ped1B_z = 13.3989;
					SetSped1 = 0;
				}
				else if (ped1_cord == 22)
				{
					ped1B_x = 740.966;
					ped1B_y = 1556.95;
					ped1B_z = 6.9725;
					SetSped1 = 0;
				}
				else if (ped1_cord == 23)
				{
					ped1B_x = 753.023;
					ped1B_y = 1446.031;
					ped1B_z = 4.8582;
					SetSped1 = 0;
				}
				else if (ped1_cord == 24)
				{
					ped1B_x = 727.703;
					ped1B_y = 1333.902;
					ped1B_z = 4.849;
					SetSped1 = 0;
				}
				else if (ped1_cord == 25)
				{
					ped1B_x = 652.951;
					ped1B_y = 1254.326;
					ped1B_z = 4.849;
					SetSped1 = 0;
				}
				else if (ped1_cord == 26)
				{
					ped1B_x = 610.7509;
					ped1B_y = 1204.893;
					ped1B_z = 4.849;
					SetSped1 = 1;
				}
				else if (ped1_cord == 27)
				{
					ped1B_x = 679.476;
					ped1B_y = 1200.07;
					ped1B_z = 4.8548;
					SetSped1 = 0;
				}
				else if (ped1_cord == 28)
				{
					ped1B_x = 767.4909;
					ped1B_y = 1203.687;
					ped1B_z = 4.8524;
					SetSped1 = 1;
				}
				else if (ped1_cord == 29)
				{
					ped1B_x = 813.307;
					ped1B_y = 1177.162;
					ped1B_z = 5.0442;
					SetSped1 = 0;
				}
				else if (ped1_cord == 30)
				{
					ped1B_x = 816.925;
					ped1B_y = 1090.352;
					ped1B_z = 5.3795;
					SetSped1 = 0;
				}
				else if (ped1_cord == 31)
				{
					ped1B_x = 813.307;
					ped1B_y = 1020.422;
					ped1B_z = 5.6054;
					SetSped1 = 0;
				}
				else if (ped1_cord == 32)
				{
					ped1B_x = 919.408;
					ped1B_y = 1013.188;
					ped1B_z = 5.4553;
					SetSped1 = 0;
				}
				else if (ped1_cord == 33)
				{
					ped1B_x = 966.952;
					ped1B_y = 1009.52;
					ped1B_z = 4.8644;
					SetSped1 = 1;
				}
				else if (ped1_cord == 34)
				{
					ped1B_x = 942.109;
					ped1B_y = 886.4781;
					ped1B_z = 4.8673;
					SetSped1 = 0;
				}
				else if (ped1_cord == 35)
				{
					ped1B_x = 927.3036;
					ped1B_y = 778.078;
					ped1B_z = 4.901301;
					SetSped1 = 0;
				}
				else if (ped1_cord == 36)
				{
					ped1B_x = 931.7009;
					ped1B_y = 671.977;
					ped1B_z = 4.866;
					SetSped1 = 0;
				}
				else if (ped1_cord == 37)
				{
					ped1B_x = 919.644;
					ped1B_y = 626.556;
					ped1B_z = 5.1941;
					SetSped1 = 1;
				}
				else if (ped1_cord == 38)
				{
					ped1B_x = 827.776;
					ped1B_y = 558.6422;
					ped1B_z = 9.535401;
					SetSped1 = 0;
				}
				else if (ped1_cord == 39)
				{
					ped1B_x = 757.852;
					ped1B_y = 507.827;
					ped1B_z = 4.8861;
					SetSped1 = 0;
				}
				else if (ped1_cord == 40)
				{
					ped1B_x = 733.732;
					ped1B_y = 405.519;
					ped1B_z = 5.776;
					SetSped1 = 1;
				}
				else if (ped1_cord == 41)
				{
					ped1B_x = 722.881;
					ped1B_y = 350.057;
					ped1B_z = 5.4278;
					SetSped1 = 0;
				}
				else if (ped1_cord == 42)
				{
					ped1B_x = 799.4901;
					ped1B_y = 310.27;
					ped1B_z = 5.7668;
					SetSped1 = 0;
				}
				else if (ped1_cord == 43)
				{
					ped1B_x = 789.6779;
					ped1B_y = 230.9841;
					ped1B_z = 5.8559;
					SetSped1 = 0;
				}
				else if (ped1_cord == 44)
				{
					ped1B_x = 716.852;
					ped1B_y = 171.8796;
					ped1B_z = 5.7751;
					SetSped1 = 0;
				}
				else if (ped1_cord == 45)
				{
					ped1B_x = 664.6887;
					ped1B_y = 108.0546;
					ped1B_z = 5.7829;
					SetSped1 = 0;
				}
				else if (ped1_cord == 46)
				{
					ped1B_x = 648.8611;
					ped1B_y = 14.875;
					ped1B_z = 5.7829;
					SetSped1 = 1;
				}
				else if (ped1_cord == 47)
				{
					ped1B_x = 611.8346;
					ped1B_y = 6.434998;
					ped1B_z = 5.5379;
					SetSped1 = 0;
				}
				else if (ped1_cord == 48)
				{
					ped1B_x = 615.3787;
					ped1B_y = 90.23642;
					ped1B_z = 4.8402;
					SetSped1 = 0;
				}
				else if (ped1_cord == 49)
				{
					ped1B_x = 629.7757;
					ped1B_y = 161.97;
					ped1B_z = 4.5263;
					SetSped1 = 0;
				}
				else if (ped1_cord == 50)
				{
					ped1B_x = ped1B_x; 
					ped1B_y = ped1B_y;
					ped1B_z = ped1B_z;
					SetSped1 = 0;
					skip = 1;
					PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
					break;
				}
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 90.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
			}

//============================== соперник 2 ==============================
			GET_CHAR_COORDINATES(ped2,  &Ped2X, &Ped2Y, &Ped2Z);//вписываем координаты соперника в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, &Ped2R);//проверка "игрок на координатах"
			if ( Ped2R < 55.0)
			{
				if (SetSped2 == 0)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 95.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				}
				if (SetSped2 == 1)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				}
				if (SetSped2 == 2)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 12.5, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				}
			}
			if ( Ped2R < 10.0)
			{
				ped2_cord += 1;
				water2X = ped2B_x;
				water2Y = ped2B_y;
				water2Z = ped2B_z;
				GET_CAR_HEADING(car2, &water2R);

				if (ped2_cord == 2)
				{
					ped2B_x = 686.71;
					ped2B_y = 309.064;
					ped2B_z = 4.8523;
					SetSped2 = 0;
				}
				else if (ped2_cord == 3)
				{
					ped2B_x = 728.899;
					ped2B_y = 398.234;
					ped2B_z = 6.1339;
					SetSped2 = 0;
				}
				else if (ped2_cord == 4)
				{
					ped2B_x = 762.479;
					ped2B_y = 515.3703;
					ped2B_z = 5.3388;
					SetSped2 = 1;
				}
				else if (ped2_cord == 5)
				{
					ped2B_x = 821.747;
					ped2B_y = 553.8195;
					ped2B_z = 9.1745;
					SetSped2 = 0;
				}
				else if (ped2_cord == 6)
				{
					ped2B_x = 876.495;
					ped2B_y = 601.993;
					ped2B_z = 4.9166;
					SetSped2 = 1;
				}
				else if (ped2_cord == 7)
				{
					ped2B_x = 833.618;
					ped2B_y = 755.384;
					ped2B_z = 4.85;
					SetSped2 = 1;
				}
				else if (ped2_cord == 8)
				{
					ped2B_x = 861.483;
					ped2B_y = 820.662;
					ped2B_z = 5.4397;
					SetSped2 = 0;
				}
				else if (ped2_cord == 9)
				{
					ped2B_x = 877.635;
					ped2B_y = 941.029;
					ped2B_z = 5.4397;
					SetSped2 = 0;
				}
				else if (ped2_cord == 10)
				{
					ped2B_x = 903.734;
					ped2B_y = 1037.302;
					ped2B_z = 5.483;
					SetSped2 = 0;
				}
				else if (ped2_cord == 11)
				{
					ped2B_x = 902.363;
					ped2B_y = 1175.82;
					ped2B_z = 4.8803;
					SetSped2 = 2;
				}
				else if (ped2_cord == 12)
				{
					ped2B_x = 980.899;
					ped2B_y = 1284.469;
					ped2B_z = 5.180801;
					SetSped2 = 0;
				}
				else if (ped2_cord == 13)
				{
					ped2B_x = 989.338;
					ped2B_y = 1424.329;
					ped2B_z = 8.5641;
					SetSped2 = 0;
				}
				else if (ped2_cord == 14)
				{
					ped2B_x = 945.934;
					ped2B_y = 1537.66;
					ped2B_z = 11.9283;
					SetSped2 = 0;
				}
				else if (ped2_cord == 15)
				{
					ped2B_x = 933.877;
					ped2B_y = 1654.62;
					ped2B_z = 10.2929;
					SetSped2 = 0;
				}
				else if (ped2_cord == 16)
				{
					ped2B_x = 955.579;
					ped2B_y = 1765.54;
					ped2B_z = 10.2502;
					SetSped2 = 2;
				}
				else if (ped2_cord == 17)
				{
					ped2B_x = 865.152;
					ped2B_y = 1814.97;
					ped2B_z = 11.0003;
					SetSped2 = 0;
				}
				else if (ped2_cord == 18)
				{
					ped2B_x = 749.406;
					ped2B_y = 1814.97;
					ped2B_z = 11.1761;
					SetSped2 = 0;
				}
				else if (ped2_cord == 19)
				{
					ped2B_x = 652.951;
					ped2B_y = 1776.39;
					ped2B_z = 11.18;
					SetSped2 = 1;
				}
				else if (ped2_cord == 20)
				{
					ped2B_x = 716.852;
					ped2B_y = 1731.78;
					ped2B_z = 11.7968;
					SetSped2 = 0;
				}
				else if (ped2_cord == 21)
				{
					ped2B_x = 703.59;
					ped2B_y = 1654.62;
					ped2B_z = 13.3989;
					SetSped2 = 0;
				}
				else if (ped2_cord == 22)
				{
					ped2B_x = 740.966;
					ped2B_y = 1556.95;
					ped2B_z = 6.9725;
					SetSped2 = 0;
				}
				else if (ped2_cord == 23)
				{
					ped2B_x = 753.023;
					ped2B_y = 1446.031;
					ped2B_z = 4.8582;
					SetSped2 = 0;
				}
				else if (ped2_cord == 24)
				{
					ped2B_x = 727.703;
					ped2B_y = 1333.902;
					ped2B_z = 4.849;
					SetSped2 = 0;
				}
				else if (ped2_cord == 25)
				{
					ped2B_x = 652.951;
					ped2B_y = 1254.326;
					ped2B_z = 4.849;
					SetSped2 = 0;
				}
				else if (ped2_cord == 26)
				{
					ped2B_x = 610.7509;
					ped2B_y = 1204.893;
					ped2B_z = 4.849;
					SetSped2 = 1;
				}
				else if (ped2_cord == 27)
				{
					ped2B_x = 679.476;
					ped2B_y = 1200.07;
					ped2B_z = 4.8548;
					SetSped2 = 0;
				}
				else if (ped2_cord == 28)
				{
					ped2B_x = 767.4909;
					ped2B_y = 1203.687;
					ped2B_z = 4.8524;
					SetSped2 = 1;
				}
				else if (ped2_cord == 29)
				{
					ped2B_x = 813.307;
					ped2B_y = 1177.162;
					ped2B_z = 5.0442;
					SetSped2 = 0;
				}
				else if (ped2_cord == 30)
				{
					ped2B_x = 816.925;
					ped2B_y = 1090.352;
					ped2B_z = 5.3795;
					SetSped2 = 0;
				}
				else if (ped2_cord == 31)
				{
					ped2B_x = 813.307;
					ped2B_y = 1020.422;
					ped2B_z = 5.6054;
					SetSped2 = 0;
				}
				else if (ped2_cord == 32)
				{
					ped2B_x = 919.408;
					ped2B_y = 1013.188;
					ped2B_z = 5.4553;
					SetSped2 = 0;
				}
				else if (ped2_cord == 33)
				{
					ped2B_x = 966.952;
					ped2B_y = 1009.52;
					ped2B_z = 4.8644;
					SetSped2 = 1;
				}
				else if (ped2_cord == 34)
				{
					ped2B_x = 942.109;
					ped2B_y = 886.4781;
					ped2B_z = 4.8673;
					SetSped2 = 0;
				}
				else if (ped2_cord == 35)
				{
					ped2B_x = 927.3036;
					ped2B_y = 778.078;
					ped2B_z = 4.901301;
					SetSped2 = 0;
				}
				else if (ped2_cord == 36)
				{
					ped2B_x = 931.7009;
					ped2B_y = 671.977;
					ped2B_z = 4.866;
					SetSped2 = 0;
				}
				else if (ped2_cord == 37)
				{
					ped2B_x = 919.644;
					ped2B_y = 626.556;
					ped2B_z = 5.1941;
					SetSped2 = 1;
				}
				else if (ped2_cord == 38)
				{
					ped2B_x = 827.776;
					ped2B_y = 558.6422;
					ped2B_z = 9.535401;
					SetSped2 = 0;
				}
				else if (ped2_cord == 39)
				{
					ped2B_x = 757.852;
					ped2B_y = 507.827;
					ped2B_z = 4.8861;
					SetSped2 = 0;
				}
				else if (ped2_cord == 40)
				{
					ped2B_x = 733.732;
					ped2B_y = 405.519;
					ped2B_z = 5.776;
					SetSped2 = 1;
				}
				else if (ped2_cord == 41)
				{
					ped2B_x = 722.881;
					ped2B_y = 350.057;
					ped2B_z = 5.4278;
					SetSped2 = 0;
				}
				else if (ped2_cord == 42)
				{
					ped2B_x = 799.4901;
					ped2B_y = 310.27;
					ped2B_z = 5.7668;
					SetSped2 = 0;
				}
				else if (ped2_cord == 43)
				{
					ped2B_x = 789.6779;
					ped2B_y = 230.9841;
					ped2B_z = 5.8559;
					SetSped2 = 0;
				}
				else if (ped2_cord == 44)
				{
					ped2B_x = 716.852;
					ped2B_y = 171.8796;
					ped2B_z = 5.7751;
					SetSped2 = 0;
				}
				else if (ped2_cord == 45)
				{
					ped2B_x = 664.6887;
					ped2B_y = 108.0546;
					ped2B_z = 5.7829;
					SetSped2 = 0;
				}
				else if (ped2_cord == 46)
				{
					ped2B_x = 648.8611;
					ped2B_y = 14.875;
					ped2B_z = 5.7829;
					SetSped2 = 1;
				}
				else if (ped2_cord == 47)
				{
					ped2B_x = 611.8346;
					ped2B_y = 6.434998;
					ped2B_z = 5.5379;
					SetSped2 = 0;
				}
				else if (ped2_cord == 48)
				{
					ped2B_x = 615.3787;
					ped2B_y = 90.23642;
					ped2B_z = 4.8402;
					SetSped2 = 0;
				}
				else if (ped2_cord == 49)
				{
					ped2B_x = 629.7757;
					ped2B_y = 161.97;
					ped2B_z = 4.5263;
					SetSped2 = 0;
				}
				else if (ped2_cord == 50)
				{
					ped2B_x = ped2B_x; 
					ped2B_y = ped2B_y;
					ped2B_z = ped2B_z;
					SetSped2 = 0;
					skip = 1;
					PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
					break;
				}
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 90.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
			}

//============================== соперник 3 ==============================
			GET_CHAR_COORDINATES(ped3,  &Ped3X, &Ped3Y, &Ped3Z);//вписываем координаты соперника в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, &Ped3R);//проверка "игрок на координатах"
			if ( Ped3R < 55.0)
			{
				if (SetSped3 == 0)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 95.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				}
				if (SetSped3 == 1)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 20.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				}
				if (SetSped3 == 2)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 12.5, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
				}
			}
			if ( Ped3R < 10.0)
			{
				ped3_cord += 1;
				water3X = ped3B_x;
				water3Y = ped3B_y;
				water3Z = ped3B_z;
				GET_CAR_HEADING(car3, &water3R);

				if (ped3_cord == 2)
				{
					ped3B_x = 686.71;
					ped3B_y = 309.064;
					ped3B_z = 4.8523;
					SetSped3 = 0;
				}
				else if (ped3_cord == 3)
				{
					ped3B_x = 728.899;
					ped3B_y = 398.234;
					ped3B_z = 6.1339;
					SetSped3 = 0;
				}
				else if (ped3_cord == 4)
				{
					ped3B_x = 762.479;
					ped3B_y = 515.3703;
					ped3B_z = 5.3388;
					SetSped3 = 1;
				}
				else if (ped3_cord == 5)
				{
					ped3B_x = 821.747;
					ped3B_y = 553.8195;
					ped3B_z = 9.1745;
					SetSped3 = 0;
				}
				else if (ped3_cord == 6)
				{
					ped3B_x = 876.495;
					ped3B_y = 601.993;
					ped3B_z = 4.9166;
					SetSped3 = 1;
				}
				else if (ped3_cord == 7)
				{
					ped3B_x = 833.618;
					ped3B_y = 755.384;
					ped3B_z = 4.85;
					SetSped3 = 1;
				}
				else if (ped3_cord == 8)
				{
					ped3B_x = 861.483;
					ped3B_y = 820.662;
					ped3B_z = 5.4397;
					SetSped3 = 0;
				}
				else if (ped3_cord == 9)
				{
					ped3B_x = 877.635;
					ped3B_y = 941.029;
					ped3B_z = 5.4397;
					SetSped3 = 0;
				}
				else if (ped3_cord == 10)
				{
					ped3B_x = 903.734;
					ped3B_y = 1037.302;
					ped3B_z = 5.483;
					SetSped3 = 0;
				}
				else if (ped3_cord == 11)
				{
					ped3B_x = 902.363;
					ped3B_y = 1175.82;
					ped3B_z = 4.8803;
					SetSped3 = 2;
				}
				else if (ped3_cord == 12)
				{
					ped3B_x = 980.899;
					ped3B_y = 1284.469;
					ped3B_z = 5.180801;
					SetSped3 = 0;
				}
				else if (ped3_cord == 13)
				{
					ped3B_x = 989.338;
					ped3B_y = 1424.329;
					ped3B_z = 8.5641;
					SetSped3 = 0;
				}
				else if (ped3_cord == 14)
				{
					ped3B_x = 945.934;
					ped3B_y = 1537.66;
					ped3B_z = 11.9283;
					SetSped3 = 0;
				}
				else if (ped3_cord == 15)
				{
					ped3B_x = 933.877;
					ped3B_y = 1654.62;
					ped3B_z = 10.2929;
					SetSped3 = 0;
				}
				else if (ped3_cord == 16)
				{
					ped3B_x = 955.579;
					ped3B_y = 1765.54;
					ped3B_z = 10.2502;
					SetSped3 = 2;
				}
				else if (ped3_cord == 17)
				{
					ped3B_x = 865.152;
					ped3B_y = 1814.97;
					ped3B_z = 11.0003;
					SetSped3 = 0;
				}
				else if (ped3_cord == 18)
				{
					ped3B_x = 749.406;
					ped3B_y = 1814.97;
					ped3B_z = 11.1761;
					SetSped3 = 0;
				}
				else if (ped3_cord == 19)
				{
					ped3B_x = 652.951;
					ped3B_y = 1776.39;
					ped3B_z = 11.18;
					SetSped3 = 1;
				}
				else if (ped3_cord == 20)
				{
					ped3B_x = 716.852;
					ped3B_y = 1731.78;
					ped3B_z = 11.7968;
					SetSped3 = 0;
				}
				else if (ped3_cord == 21)
				{
					ped3B_x = 703.59;
					ped3B_y = 1654.62;
					ped3B_z = 13.3989;
					SetSped3 = 0;
				}
				else if (ped3_cord == 22)
				{
					ped3B_x = 740.966;
					ped3B_y = 1556.95;
					ped3B_z = 6.9725;
					SetSped3 = 0;
				}
				else if (ped3_cord == 23)
				{
					ped3B_x = 753.023;
					ped3B_y = 1446.031;
					ped3B_z = 4.8582;
					SetSped3 = 0;
				}
				else if (ped3_cord == 24)
				{
					ped3B_x = 727.703;
					ped3B_y = 1333.902;
					ped3B_z = 4.849;
					SetSped3 = 0;
				}
				else if (ped3_cord == 25)
				{
					ped3B_x = 652.951;
					ped3B_y = 1254.326;
					ped3B_z = 4.849;
					SetSped3 = 0;
				}
				else if (ped3_cord == 26)
				{
					ped3B_x = 610.7509;
					ped3B_y = 1204.893;
					ped3B_z = 4.849;
					SetSped3 = 1;
				}
				else if (ped3_cord == 27)
				{
					ped3B_x = 679.476;
					ped3B_y = 1200.07;
					ped3B_z = 4.8548;
					SetSped3 = 0;
				}
				else if (ped3_cord == 28)
				{
					ped3B_x = 767.4909;
					ped3B_y = 1203.687;
					ped3B_z = 4.8524;
					SetSped3 = 1;
				}
				else if (ped3_cord == 29)
				{
					ped3B_x = 813.307;
					ped3B_y = 1177.162;
					ped3B_z = 5.0442;
					SetSped3 = 0;
				}
				else if (ped3_cord == 30)
				{
					ped3B_x = 816.925;
					ped3B_y = 1090.352;
					ped3B_z = 5.3795;
					SetSped3 = 0;
				}
				else if (ped3_cord == 31)
				{
					ped3B_x = 813.307;
					ped3B_y = 1020.422;
					ped3B_z = 5.6054;
					SetSped3 = 0;
				}
				else if (ped3_cord == 32)
				{
					ped3B_x = 919.408;
					ped3B_y = 1013.188;
					ped3B_z = 5.4553;
					SetSped3 = 0;
				}
				else if (ped3_cord == 33)
				{
					ped3B_x = 966.952;
					ped3B_y = 1009.52;
					ped3B_z = 4.8644;
					SetSped3 = 1;
				}
				else if (ped3_cord == 34)
				{
					ped3B_x = 942.109;
					ped3B_y = 886.4781;
					ped3B_z = 4.8673;
					SetSped3 = 0;
				}
				else if (ped3_cord == 35)
				{
					ped3B_x = 927.3036;
					ped3B_y = 778.078;
					ped3B_z = 4.901301;
					SetSped3 = 0;
				}
				else if (ped3_cord == 36)
				{
					ped3B_x = 931.7009;
					ped3B_y = 671.977;
					ped3B_z = 4.866;
					SetSped3 = 0;
				}
				else if (ped3_cord == 37)
				{
					ped3B_x = 919.644;
					ped3B_y = 626.556;
					ped3B_z = 5.1941;
					SetSped3 = 1;
				}
				else if (ped3_cord == 38)
				{
					ped3B_x = 827.776;
					ped3B_y = 558.6422;
					ped3B_z = 9.535401;
					SetSped3 = 0;
				}
				else if (ped3_cord == 39)
				{
					ped3B_x = 757.852;
					ped3B_y = 507.827;
					ped3B_z = 4.8861;
					SetSped3 = 0;
				}
				else if (ped3_cord == 40)
				{
					ped3B_x = 733.732;
					ped3B_y = 405.519;
					ped3B_z = 5.776;
					SetSped3 = 1;
				}
				else if (ped3_cord == 41)
				{
					ped3B_x = 722.881;
					ped3B_y = 350.057;
					ped3B_z = 5.4278;
					SetSped3 = 0;
				}
				else if (ped3_cord == 42)
				{
					ped3B_x = 799.4901;
					ped3B_y = 310.27;
					ped3B_z = 5.7668;
					SetSped3 = 0;
				}
				else if (ped3_cord == 43)
				{
					ped3B_x = 789.6779;
					ped3B_y = 230.9841;
					ped3B_z = 5.8559;
					SetSped3 = 0;
				}
				else if (ped3_cord == 44)
				{
					ped3B_x = 716.852;
					ped3B_y = 171.8796;
					ped3B_z = 5.7751;
					SetSped3 = 0;
				}
				else if (ped3_cord == 45)
				{
					ped3B_x = 664.6887;
					ped3B_y = 108.0546;
					ped3B_z = 5.7829;
					SetSped3 = 0;
				}
				else if (ped3_cord == 46)
				{
					ped3B_x = 648.8611;
					ped3B_y = 14.875;
					ped3B_z = 5.7829;
					SetSped3 = 1;
				}
				else if (ped3_cord == 47)
				{
					ped3B_x = 611.8346;
					ped3B_y = 6.434998;
					ped3B_z = 5.5379;
					SetSped3 = 0;
				}
				else if (ped3_cord == 48)
				{
					ped3B_x = 615.3787;
					ped3B_y = 90.23642;
					ped3B_z = 4.8402;
					SetSped3 = 0;
				}
				else if (ped3_cord == 49)
				{
					ped3B_x = 629.7757;
					ped3B_y = 161.97;
					ped3B_z = 4.5263;
					SetSped3 = 0;
				}
				else if (ped3_cord == 50)
				{
					ped3B_x = ped3B_x; 
					ped3B_y = ped3B_y;
					ped3B_z = ped3B_z;
					SetSped3 = 0;
					skip = 1;
					PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
					break;
				}
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 90.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
			}
			
			//получаем здоровье статистов
			GET_CHAR_HEALTH(ped4, &Ped_hp4);
			GET_CHAR_HEALTH(ped5, &Ped_hp5);
			GET_CHAR_HEALTH(ped6, &Ped_hp6);
			GET_CHAR_HEALTH(ped7, &Ped_hp7);
			GET_CHAR_HEALTH(ped8, &Ped_hp8);
			GET_CHAR_HEALTH(ped9, &Ped_hp9);
			GET_CHAR_HEALTH(ped10, &Ped_hp10);
			GET_CHAR_HEALTH(ped11, &Ped_hp11);

			if (( Ped_hp4 < 195 ) || ( Ped_hp5 < 195 ) || ( Ped_hp6 < 195 ) || ( Ped_hp7 < 195 ) || ( Ped_hp8 < 195 ) || ( Ped_hp9 < 195 ) || ( Ped_hp10 < 195 ) || ( Ped_hp11 < 195 ))
			{
				PRINT_STRING_IN_STRING("string", "VC2_RACE_TEXT9", 3500, 1);//Выводим на экран сообщение "человек из толпы пострадал. Гонка отменина"
				PANIC_SCREAM(ped4);
				PANIC_SCREAM(ped5);
				PANIC_SCREAM(ped6);
				PANIC_SCREAM(ped7);
				PANIC_SCREAM(ped8);
				PANIC_SCREAM(ped9);
				PANIC_SCREAM(ped10);
				PANIC_SCREAM(ped11);
				skip = 1;
				break;
			}
			else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
			{
				skip = 1;
				break;
			}
			position();

			// HUD позицыя игрока 
			DRAW_SPRITE( fon, 0.8765625, 0.74213, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );

			setup_draw_text();
			DISPLAY_TEXT(0.78815097, 0.73564852, "NE_RACE5"); //POSITION:

			SET_TEXT_COLOUR(95, 195, 247, 255);
			SET_TEXT_SCALE(0.312, 0.534);
			SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
			DISPLAY_TEXT_WITH_NUMBER(0.920052, 0.725462962, "CP_TIME_NOZERO", poziteon);

			setup_draw_text();
			if (poziteon == 1)
			{
				DISPLAY_TEXT(0.93099, 0.72916666, "ST");
			}
			else if (poziteon == 2)
			{
				DISPLAY_TEXT(0.93099, 0.72916666, "ND");
			}
			else if (poziteon == 3)
			{
				DISPLAY_TEXT(0.93099, 0.72916666, "RD");
			}
			else if (poziteon == 4)
			{
				DISPLAY_TEXT(0.93099, 0.72916666, "TH");
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

			setup_draw_text();
			DISPLAY_TEXT(0.78815097, 0.77731852, "RACES"); //TIME:

			setup_draw_value();
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.9088542, 0.76954074, "CP_TIME_ZERO", time_m);// минуты

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

			/*/================ режим MW ================
			if ( best_time_s == cop_on )
			{
				GENERATE_RANDOM_INT_IN_RANGE( 1, 6, &cop_on);
				if (cop_on < 3)
				{
					cop_on = 95;
				}
				else
				{
					ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
					APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
					cop_on = 85;
				}
			}
			if ((IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0)) && (cop_on == 85)) //проверка розыска.
			{
				cop_on = 90;
				ALTER_WANTED_LEVEL(GetPlayerIndex(), 3);
				APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
				if (IS_CHAR_IN_ZONE(GetPlayerPed(), "FRANI"))
				{
					while (!(PRELOAD_STREAM("CUTSCENES_RPBAD1")));
					PRELOAD_STREAM("CUTSCENES_RPBAD1");  // имя берется из sounds.dat15, также можно проиграть музыку из радио
					//Airport
				}
				else if ((IS_CHAR_IN_ZONE(GetPlayerPed(), "PORTU")) || (IS_CHAR_IN_ZONE(GetPlayerPed(), "BRALG")))
				{
					while (!(PRELOAD_STREAM("CUTSCENES_RPED1")));
					PRELOAD_STREAM("CUTSCENES_RPED1");  // имя берется из sounds.dat15, также можно проиграть музыку из радио
					//PORT
				}
				else if (IS_CHAR_IN_ZONE(GetPlayerPed(), "STHBO"))
				{
					while (!(PRELOAD_STREAM("CUTSCENES_RPED2")));
					PRELOAD_STREAM("CUTSCENES_RPED2");  // имя берется из sounds.dat15, также можно проиграть музыку из радио
					//HAVANA
				}
				else if (IS_CHAR_IN_ZONE(GetPlayerPed(), "WILLI"))
				{
					while (!(PRELOAD_STREAM("CUTSCENES_RPEXG1")));
					PRELOAD_STREAM("CUTSCENES_RPEXG1");  // имя берется из sounds.dat15, также можно проиграть музыку из радио
					//HAITI
				}
				//=================== остальные зоны тут ===================
				else
				{
					while (!(PRELOAD_STREAM("CUTSCENES_RPBRI1")));
					PRELOAD_STREAM("CUTSCENES_RPBRI1");  // имя берется из sounds.dat15, также можно проиграть музыку из радио
					//прочие зоны
				}
				DISABLE_FRONTEND_RADIO();
				PLAY_STREAM_FRONTEND();
				SETTIMERC(0);
			}
			if (cop_on == 90)
			{
				radio = TIMERC();
				if (radio > 10000)
				{
					//radio_off
					STOP_STREAM();
					ENABLE_FRONTEND_RADIO();
					cop_on = 95;
				}
			}
			if (cop_on == 95)
			{
				if (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0)) //проверка розыска.
				{
					cop_on = 95;
				}
				else
				{
					cop_on = 85;
				}
			}
			//================ режим MW ================*/
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
			if (!IS_CHAR_SITTING_IN_ANY_CAR( ped2 ))
			{
				SETTIMERB(0);
				GET_CAR_COORDINATES(car2, &Ped2X, &Ped2Y, &Ped2Z);
				SET_CAR_COORDINATES(car2, Ped2X, Ped2Y, Ped2Z+1);
				GET_CAR_HEADING(car2, &Ped2R);
				SET_CAR_HEADING(car2, Ped2R);//градус поворота машины
				FIX_CAR(car2);
				WARP_CHAR_INTO_CAR(ped2, car2);
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
			}
			if (!IS_CHAR_SITTING_IN_ANY_CAR( ped3 ))
			{
				SETTIMERB(0);
				GET_CAR_COORDINATES(car3, &Ped3X, &Ped3Y, &Ped3Z);
				SET_CAR_COORDINATES(car3, Ped3X, Ped3Y, Ped3Z+1);
				GET_CAR_HEADING(car3, &Ped3R);
				SET_CAR_HEADING(car3, Ped3R);//градус поворота машины
				FIX_CAR(car3);
				WARP_CHAR_INTO_CAR(ped3, car3);
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
			}
			//==================== фиксы соперника-водалаза ====================
			if (IS_CAR_IN_WATER(car1))
			{
				SETTIMERB(0);
				FIX_CAR(car1);
				SET_CAR_COORDINATES(car1, water1X, water1Y, water1Z);
				SET_CAR_HEADING(car1, water1R);//градус поворота машины
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
			}
			if (IS_CAR_IN_WATER(car2))
			{
				SETTIMERB(0);
				FIX_CAR(car2);
				SET_CAR_COORDINATES(car2, water2X, water2Y, water2Z);
				SET_CAR_HEADING(car2, water2R);//градус поворота машины
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
			}
			if (IS_CAR_IN_WATER(car3))
			{
				SETTIMERB(0);
				FIX_CAR(car3);
				SET_CAR_COORDINATES(car3, water3X, water3Y, water3Z);
				SET_CAR_HEADING(car3, water3R);//градус поворота машины
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
			}
			//==================== фиксы соперника в стене ====================
			GET_CHAR_SPEED(ped1, &sped_wall1);
			GET_CHAR_SPEED(ped2, &sped_wall2);
			GET_CHAR_SPEED(ped3, &sped_wall3);
			if (sped_wall1 < 2)
			{
				time_wall = TIMERB();
				if (time_wall > 5000)
				{
					FIX_CAR(car1);
					SET_CAR_COORDINATES(car1, water1X, water1Y, water1Z);
					SET_CAR_HEADING(car1, water1R);//градус поворота машины
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
					SETTIMERB(0);
				}
			}
			if (sped_wall2 < 2)
			{
				time_wall = TIMERB();
				if (time_wall > 5000)
				{
					FIX_CAR(car2);
					SET_CAR_COORDINATES(car2, water2X, water2Y, water2Z);
					SET_CAR_HEADING(car2, water2R);//градус поворота машины
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
					SETTIMERB(0);
				}
			}
			if (sped_wall3 < 2)
			{
				time_wall = TIMERB();
				if (time_wall > 5000)
				{
					FIX_CAR(car3);
					SET_CAR_COORDINATES(car3, water3X, water3Y, water3Z);
					SET_CAR_HEADING(car3, water3R);//градус поворота машины
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 120.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
					SETTIMERB(0);
				}
			}
			if ((sped_wall1 > 2) && (sped_wall2 > 2) && (sped_wall3 > 2))
			{
				SETTIMERB(0);
			}



		}
	}
	// чистим скрипт тут
	WAIT(100);
	SET_CAR_DENSITY_MULTIPLIER(1);// отключаем пути
	SWITCH_ROADS_BACK_TO_ORIGINAL( 715.988, 109.372, -1.286, 602.218, 333.631, 80.0 );//  АКТИВИРУЕМ ТРАФИКА
	REMOVE_BLIP(Blip_r);//Удаляем иконку на радаре
	REMOVE_BLIP(Blip_r2);//Удаляем иконку на радаре
	REMOVE_BLIP(Blip_c1);//Удаляем иконку на радаре
	REMOVE_BLIP(Blip_c2);//Удаляем иконку на радаре
	REMOVE_BLIP(Blip_c3);//Удаляем иконку на радаре
	DELETE_CHECKPOINT(checkpoint);

	// выгружаем из памяти модели
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
	MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель машины
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель педа
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель педа
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель педа
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель педа
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//выгружаем модель педа
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM6);//выгружаем модель педа
	MARK_MODEL_AS_NO_LONGER_NEEDED(PedM7);//выгружаем модель педа

	// выгружаем из памяти педов
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped5);//выгружаем модель педа(в последствии пед изчезнет)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped6);//выгружаем модель педа(в последствии пед изчезнет)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped7);//выгружаем модель педа(в последствии пед изчезнет)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped8);//выгружаем модель педа(в последствии пед изчезнет)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped9);//выгружаем модель педа(в последствии пед изчезнет)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped10);//выгружаем модель педа(в последствии пед изчезнет)
	MARK_CHAR_AS_NO_LONGER_NEEDED(&ped11);//выгружаем модель педа(в последствии пед изчезнет)

	// выгружаем из памяти транспорт
	MARK_CAR_AS_NO_LONGER_NEEDED(&car1);//выгружаем модель машины(в последствии машина изчезнет)
	MARK_CAR_AS_NO_LONGER_NEEDED(&car2);//выгружаем модель машины(в последствии машина изчезнет)
	MARK_CAR_AS_NO_LONGER_NEEDED(&car3);//выгружаем модель машины(в последствии машина изчезнет)

	RELEASE_TEXTURE( fon );
	RELEASE_TEXTURE( timer );
	REMOVE_TXD( textur );

	if (skip == 1)
	{
		if (!IS_BIT_SET(G_SA_RACE, 4))
		{
			INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
		}
		MissionFailed();
	}
	else if (skip == 2)
	{
		SETTIMERA(0); //сбрасываем таймер 
		play_mission_complete_tune();
		MissionPassed(20000, "youhavewon", "CASH");
		ADD_SCORE( GetPlayerIndex(), +20000 );//даём игроку денег
		INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 20000);
		if (!IS_BIT_SET(G_SA_RACE, 4))
		{
			SET_BIT(&G_SA_RACE, 4);
			INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
			G_GAME_PROGRESS += 1;
			SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
		}
	}
}
void main(void)
{
	WAIT(500);
	sa_race();
	TERMINATE_THIS_SCRIPT();
}
