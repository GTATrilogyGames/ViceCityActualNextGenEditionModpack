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
	if (!IS_BIT_SET(G_SA_RACE, 5))
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

	startX = -572.187;
	startY = -406.217;
	startZ = 8.60515;
	startH = 225.0;

	Blip_x = -496.153;
	Blip_y = -496.48;
	Blip_z = 8.6592;
	Blip_x2 = -454.966;
	Blip_y2 = -540.35;
	Blip_z2 = 8.647801;
	play_cord = 1;

	ped1B_x = -496.153;
	ped1B_y = -496.48;
	ped1B_z = 8.6592;
	SetSped1 = 1;
	ped1_cord = 1;

	ped2B_x = -496.153;
	ped2B_y = -496.48;
	ped2B_z = 8.6592;
	SetSped2 = 1;
	ped2_cord = 1;

	ped3B_x = -496.153;
	ped3B_y = -496.48;
	ped3B_z = 8.6592;
	SetSped3 = 1;
	ped3_cord = 1;

	SWITCH_ROADS_OFF( -465.473, -529.89, -1.286, -759.523, -169.158, 80.0 );// ОТКЛЮЧАЕМ ПУТИ ТРАФИКА
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
					Blip_x2 = -391.396;
					Blip_y2 = -507.23;
					Blip_z2 = 4.8895;
				}
				else if (play_cord == 3)
				{
					Blip_x2 = -390.5;
					Blip_y2 = -413.213;
					Blip_z2 = 4.8871;
				}
				else if (play_cord == 4)
				{
					Blip_x2 = -331.407;
					Blip_y2 = -392.62;
					Blip_z2 = 4.457501;
				}
				else if (play_cord == 5)
				{
					Blip_x2 = -244.557;
					Blip_y2 = -397.992;
					Blip_z2 = 8.6473;
				}
				else if (play_cord == 6)
				{
					Blip_x2 = -155.022;
					Blip_y2 = -399.782;
					Blip_z2 = 15.4283;
				}
				else if (play_cord == 7)
				{
					Blip_x2 = -59.219;
					Blip_y2 = -399.782;
					Blip_z2 = 20.0643;
				}
				else if (play_cord == 8)
				{
					Blip_x2 = 36.58499;
					Blip_y2 = -402.468;
					Blip_z2 = 17.5963;
				}
				else if (play_cord == 9)
				{
					Blip_x2 = 137.76;
					Blip_y2 = -406.05;
					Blip_z2 = 11.4214;
				}
				else if (play_cord == 10)
				{
					Blip_x2 = 243.412;
					Blip_y2 = -397.096;
					Blip_z2 = 6.0187;
				}
				else if (play_cord == 11)
				{
					Blip_x2 = 328.471;
					Blip_y2 = -362.177;
					Blip_z2 = 4.2782;
				}
				else if (play_cord == 12)
				{
					Blip_x2 = 410.8439;
					Blip_y2 = -337.107;
					Blip_z2 = 4.2782;
				}
				else if (play_cord == 13)
				{
					Blip_x2 = 506.6471;
					Blip_y2 = -325.468;
					Blip_z2 = 4.278;
				}
				else if (play_cord == 14)
				{
					Blip_x2 = 564.845;
					Blip_y2 = -254.734;
					Blip_z2 = 4.278;
				}
				else if (play_cord == 15)
				{
					Blip_x2 = 596.183;
					Blip_y2 = -173.257;
					Blip_z2 = 4.278;
				}
				else if (play_cord == 16)
				{
					Blip_x2 = 606.032;
					Blip_y2 = -113.268;
					Blip_z2 = 10.1956;
				}
				else if (play_cord == 17)
				{
					Blip_x2 = 611.404;
					Blip_y2 = -16.57001;
					Blip_z2 = 5.689999;
				}
				else if (play_cord == 18)
				{
					Blip_x2 = 617.671;
					Blip_y2 = 80.129;
					Blip_z2 = 4.8402;
				}
				else if (play_cord == 19)
				{
					Blip_x2 = 632.8919;
					Blip_y2 = 167.874;
					Blip_z2 = 4.465;
				}
				else if (play_cord == 20)
				{
					Blip_x2 = 657.9621;
					Blip_y2 = 257.41;
					Blip_z2 = 5.9105;
				}
				else if (play_cord == 21)
				{
					Blip_x2 = 701.835;
					Blip_y2 = 334.41;
					Blip_z2 = 4.8572;
				}
				else if (play_cord == 22)
				{
					Blip_x2 = 741.231;
					Blip_y2 = 417.678;
					Blip_z2 = 4.8605;
				}
				else if (play_cord == 23)
				{
					Blip_x2 = 760.9279;
					Blip_y2 = 502.7374;
					Blip_z2 = 4.9096;
				}
				else if (play_cord == 24)
				{
					Blip_x2 = 822.708;
					Blip_y2 = 553.7727;
					Blip_z2 = 9.2094;
				}
				else if (play_cord == 25)
				{
					Blip_x2 = 880.011;
					Blip_y2 = 619.1337;
					Blip_z2 = 4.8733;
				}
				else if (play_cord == 26)
				{
					Blip_x2 = 832.557;
					Blip_y2 = 705.983;
					Blip_z2 = 4.847;
				}
				else if (play_cord == 27)
				{
					Blip_x2 = 824.499;
					Blip_y2 = 770.449;
					Blip_z2 = 4.3895;
				}
				else if (play_cord == 28)
				{
					Blip_x2 = 773.463;
					Blip_y2 = 786.565;
					Blip_z2 = 5.1255;
				}
				else if (play_cord == 29)
				{
					Blip_x2 = 767.1961;
					Blip_y2 = 885.055;
					Blip_z2 = 5.4291;
				}
				else if (play_cord == 30)
				{
					Blip_x2 = 782.417;
					Blip_y2 = 977.276;
					Blip_z2 = 5.4235;
				}
				else if (play_cord == 31)
				{
					Blip_x2 = 811.068;
					Blip_y2 = 1064.126;
					Blip_z2 = 5.4235;
				}
				else if (play_cord == 32)
				{
					Blip_x2 = 815.545;
					Blip_y2 = 1140.231;
					Blip_z2 = 5.4235;
				}
				else if (play_cord == 33)
				{
					Blip_x2 = 795.847;
					Blip_y2 = 1201.116;
					Blip_z2 = 4.894;
				}
				else if (play_cord == 34)
				{
					Blip_x2 = 697.358;
					Blip_y2 = 1202.906;
					Blip_z2 = 4.8524;
				}
				else if (play_cord == 35)
				{
					Blip_x2 = 640.055;
					Blip_y2 = 1190.371;
					Blip_z2 = 4.849;
				}
				else if (play_cord == 36)
				{
					Blip_x2 = 611.404;
					Blip_y2 = 1203.802;
					Blip_z2 = 4.849;
				}
				else if (play_cord == 37)
				{
					Blip_x2 = 629.311;
					Blip_y2 = 1240.511;
					Blip_z2 = 4.849;
				}
				else if (play_cord == 38)
				{
					Blip_x2 = 705.416;
					Blip_y2 = 1298.71;
					Blip_z2 = 4.8514;
				}
				else if (play_cord == 39)
				{
					Blip_x2 = 744.812;
					Blip_y2 = 1390.036;
					Blip_z2 = 4.8551;
				}
				else if (play_cord == 40)
				{
					Blip_x2 = 751.975;
					Blip_y2 = 1507.328;
					Blip_z2 = 5.6569;
				}
				else if (play_cord == 41)
				{
					Blip_x2 = 726.905;
					Blip_y2 = 1600.44;
					Blip_z2 = 7.0802;
				}
				else if (play_cord == 42)
				{
					Blip_x2 = 706.312;
					Blip_y2 = 1672.07;
					Blip_z2 = 15.0402;
				}
				else if (play_cord == 43)
				{
					Blip_x2 = 716.161;
					Blip_y2 = 1733.85;
					Blip_z2 = 11.7887;
				}
				else if (play_cord == 44)
				{
					Blip_x2 = 655.276;
					Blip_y2 = 1767.88;
					Blip_z2 = 11.18;
				}
				else if (play_cord == 45)
				{
					Blip_x2 = 716.161;
					Blip_y2 = 1814.44;
					Blip_z2 = 11.1801;
				}
				else if (play_cord == 46)
				{
					Blip_x2 = 816.4411;
					Blip_y2 = 1814.44;
					Blip_z2 = 11.1761;
				}
				else if (play_cord == 47)
				{
					Blip_x2 = 905.976;
					Blip_y2 = 1811.75;
					Blip_z2 = 11.5197;
				}
				else if (play_cord == 48)
				{
					Blip_x2 = 951.639;
					Blip_y2 = 1791.16;
					Blip_z2 = 10.5517;
				}
				else if (play_cord == 49)
				{
					Blip_x2 = 941.7901;
					Blip_y2 = 1697.14;
					Blip_z2 = 11.0812;
				}
				else if (play_cord == 50)
				{
					Blip_x2 = 932.837;
					Blip_y2 = 1607.61;
					Blip_z2 = 11.7323;
				}
				else if (play_cord == 51)
				{
					Blip_x2 = 952.535;
					Blip_y2 = 1515.386;
					Blip_z2 = 11.9283;
				}
				else if (play_cord == 52)
				{
					Blip_x2 = 985.878;
					Blip_y2 = 1434.804;
					Blip_z2 = 8.8502;
				}
				else if (play_cord == 53)
				{
					Blip_x2 = 992.826;
					Blip_y2 = 1353.326;
					Blip_z2 = 6.2706;
				}
				else if (play_cord == 54)
				{
					Blip_x2 = 977.605;
					Blip_y2 = 1259.314;
					Blip_z2 = 4.9648;
				}
				else if (play_cord == 55)
				{
					Blip_x2 = 955.221;
					Blip_y2 = 1188.581;
					Blip_z2 = 4.9354;
				}
				else if (play_cord == 56)
				{
					Blip_x2 = 852.255;
					Blip_y2 = 1213.651;
					Blip_z2 = 5.2006;
				}
				else if (play_cord == 57)
				{
					Blip_x2 = 854.045;
					Blip_y2 = 1316.617;
					Blip_z2 = 5.2006;
				}
				else if (play_cord == 58)
				{
					Blip_x2 = 857.627;
					Blip_y2 = 1404.362;
					Blip_z2 = 5.1785;
				}
				else if (play_cord == 59)
				{
					Blip_x2 = 837.9289;
					Blip_y2 = 1474.2;
					Blip_z2 = 6.4493;
				}
				else if (play_cord == 60)
				{
					Blip_x2 = 736.754;
					Blip_y2 = 1483.153;
					Blip_z2 = 15.4129;
				}
				else if (play_cord == 61)
				{
					Blip_x2 = 623.939;
					Blip_y2 = 1508.223;
					Blip_z2 = 18.2634;
				}
				else if (play_cord == 62)
				{
					Blip_x2 = 527.2402;
					Blip_y2 = 1520.758;
					Blip_z2 = 4.8228;
				}
				else if (play_cord == 63)
				{
					Blip_x2 = 529.268;
					Blip_y2 = 1441.967;
					Blip_z2 = 4.7065;
				}
				else if (play_cord == 64)
				{
					Blip_x2 = 478.1894;
					Blip_y2 = 1398.236;
					Blip_z2 = 4.7037;
				}
				else if (play_cord == 65)
				{
					Blip_x2 = 443.972;
					Blip_y2 = 1428.536;
					Blip_z2 = 4.7136;
				}
				else if (play_cord == 66)
				{
					Blip_x2 = 463.9647;
					Blip_y2 = 1519.482;
					Blip_z2 = 4.7345;
					play_cord = 69;
				}
				else if (play_cord == 67)
				{
					Blip_x2 = 464.2384;
					Blip_y2 = 1591.027;
					Blip_z2 = 4.8576;
				}
				else if (play_cord == 68)
				{
					Blip_x2 = 447.1929;
					Blip_y2 = 1642.57;
					Blip_z2 = 10.5335;
				}
				else if (play_cord == 69)
				{
					Blip_x2 = 395.7428;
					Blip_y2 = 1580.943;
					Blip_z2 = 4.8058;
				}
				else if (play_cord == 70)
				{
					Blip_x2 = 294.447;
					Blip_y2 = 1608.5;
					Blip_z2 = 6.180101;
				}
				else if (play_cord == 71)
				{
					Blip_x2 = 205.807;
					Blip_y2 = 1616.56;
					Blip_z2 = 14.3942;
				}
				else if (play_cord == 72)
				{
					Blip_x2 = 118.062;
					Blip_y2 = 1617.46;
					Blip_z2 = 16.0711;
				}
				else if (play_cord == 73)
				{
					Blip_x2 = 18.67801;
					Blip_y2 = 1618.35;
					Blip_z2 = 5.4061;
				}
				else if (play_cord == 74)
				{
					Blip_x2 = -72.64899;
					Blip_y2 = 1632.68;
					Blip_z2 = 4.8647;
				}
				else if (play_cord == 75)
				{
					Blip_x2 = -155.022;
					Blip_y2 = 1678.34;
					Blip_z2 = 4.872501;
				}
				else if (play_cord == 76)
				{
					Blip_x2 = -238.29;
					Blip_y2 = 1714.16;
					Blip_z2 = 4.872501;
				}
				else if (play_cord == 77)
				{
					Blip_x2 = -339.465;
					Blip_y2 = 1709.68;
					Blip_z2 = 4.8647;
				}
				else if (play_cord == 78)
				{
					Blip_x2 = -425.2143;
					Blip_y2 = 1688.099;
					Blip_z2 = 4.7009;
				}
				else if (play_cord == 79)
				{
					Blip_x2 = -433.4924;
					Blip_y2 = 1597.211;
					Blip_z2 = 4.8699;
				}
				else if (play_cord == 80)
				{
					Blip_x2 = -436.2254;
					Blip_y2 = 1501.277;
					Blip_z2 = 4.8699;
				}
				else if (play_cord == 81)
				{
					Blip_x2 = -438.7631;
					Blip_y2 = 1395.701;
					Blip_z2 = 4.8816;
				}
				else if (play_cord == 82)
				{
					Blip_x2 = -437.408;
					Blip_y2 = 1311.439;
					Blip_z2 = 4.8816;
				}
				else if (play_cord == 83)
				{
					Blip_x2 = -322.6299;
					Blip_y2 = 1286.177;
					Blip_z2 = 4.8816;
				}
				else if (play_cord == 84)
				{
					Blip_x2 = -240.0354;
					Blip_y2 = 1267.206;
					Blip_z2 = 4.9913;
				}
				else if (play_cord == 85)
				{
					Blip_x2 = -244.4168;
					Blip_y2 = 1167.997;
					Blip_z2 = 4.8813;
				}
				else if (play_cord == 86)
				{
					Blip_x2 = -253.957;
					Blip_y2 = 1072.407;
					Blip_z2 = 4.8847;
				}
				else if (play_cord == 87)
				{
					Blip_x2 = -264.2693;
					Blip_y2 = 981.9677;
					Blip_z2 = 4.8925;
					play_cord = 88;
				}
				else if (play_cord == 88)
				{
					Blip_x2 = -272.3832;
					Blip_y2 = 889.7058;
					Blip_z2 = 4.8679;
				}
				else if (play_cord == 89)
				{
					Blip_x2 = -295.8838;
					Blip_y2 = 826.4709;
					Blip_z2 = 4.9507;
				}
				else if (play_cord == 90)
				{
					Blip_x2 = -365.431;
					Blip_y2 = 839.391;
					Blip_z2 = 5.2203;
				}
				else if (play_cord == 91)
				{
					Blip_x2 = -458.548;
					Blip_y2 = 850.136;
					Blip_z2 = 5.2165;
				}
				else if (play_cord == 92)
				{
					Blip_x2 = -543.1764;
					Blip_y2 = 857.2659;
					Blip_z2 = 5.1999;
				}
				else if (play_cord == 93)
				{
					Blip_x2 = -583.0317;
					Blip_y2 = 777.374;
					Blip_z2 = 5.1766;
				}
				else if (play_cord == 94)
				{
					Blip_x2 = -621.1567;
					Blip_y2 = 684.0111;
					Blip_z2 = 5.2094;
				}
				else if (play_cord == 95)
				{
					Blip_x2 = -636.8751;
					Blip_y2 = 581.2972;
					Blip_z2 = 5.2116;
				}
				else if (play_cord == 96)
				{
					Blip_x2 = -636.2772;
					Blip_y2 = 516.8642;
					Blip_z2 = 5.2118;
				}
				else if (play_cord == 97)
				{
					Blip_x2 = -648.8364;
					Blip_y2 = 464.6268;
					Blip_z2 = 5.3946;
				}
				else if (play_cord == 98)
				{
					Blip_x2 = -716.8814;
					Blip_y2 = 455.9111;
					Blip_z2 = 5.3912;
				}
				else if (play_cord == 99)
				{
					Blip_x2 = -751.4313;
					Blip_y2 = 384.294;
					Blip_z2 = 5.3799;
				}
				else if (play_cord == 100)
				{
					Blip_x2 = -752.5255;
					Blip_y2 = 281.0686;
					Blip_z2 = 5.3807;
				}
				else if (play_cord == 101)
				{
					Blip_x2 = -749.1074;
					Blip_y2 = 182.7831;
					Blip_z2 = 4.7105;
				}
				else if (play_cord == 102)
				{
					Blip_x2 = -765.843;
					Blip_y2 = 83.67506;
					Blip_z2 = 4.7421;
				}
				else if (play_cord == 103)
				{
					Blip_x2 = -721.182;
					Blip_y2 = 33.6928;
					Blip_z2 = 4.7692;
				}
				else if (play_cord == 104)
				{
					Blip_x2 = -659.649;
					Blip_y2 = 42.2182;
					Blip_z2 = 5.1038;
				}
				else if (play_cord == 105)
				{
					Blip_x2 = -632.6763;
					Blip_y2 = -49.21457;
					Blip_z2 = 4.9241;
				}
				else if (play_cord == 106)
				{
					Blip_x2 = -552.5643;
					Blip_y2 = -50.53316;
					Blip_z2 = 5.2854;
				}
				else if (play_cord == 107)
				{
					Blip_x2 = -549.1974;
					Blip_y2 = -134.2322;
					Blip_z2 = 5.5705;
				}
				else if (play_cord == 108)
				{
					Blip_x2 = -623.8671;
					Blip_y2 = -143.9434;
					Blip_z2 = 5.5966;
				}
				else if (play_cord == 109)
				{
					Blip_x2 = -694.3903;
					Blip_y2 = -154.4668;
					Blip_z2 = 5.5742;
				}
				else if (play_cord == 110)
				{
					Blip_x2 = -678.81;
					Blip_y2 = -256.525;
					Blip_z2 = 5.6719;
				}
				else if (play_cord == 111)
				{
					Blip_x2 = -638.51;
					Blip_y2 = -332.631;
					Blip_z2 = 6.3928;
				}
				else if (play_cord == 112)
				{
					Blip_x2 = -562.409;
					Blip_y2 = -413.213;
					Blip_z2 = 8.658201;
				}
				else if (play_cord == 113)
				{
					Blip_x2 = Blip_x2; 
					Blip_y2 = Blip_y2;
					Blip_z2 = Blip_z2;
				}
				else if (play_cord == 114)
				{
					skip = 2;
					break;
				}
				if (play_cord < 113)
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
					if (play_cord < 112)
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
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped1, car1, ped1B_x, ped1B_y, ped1B_z, 4, 65.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
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
					ped1B_x = -454.966;
					ped1B_y = -540.35;
					ped1B_z = 8.647801;
					SetSped1 = 0;
				}
				else if (ped1_cord == 3)
				{
					ped1B_x = -391.396;
					ped1B_y = -507.23;
					ped1B_z = 4.8895;
					SetSped1 = 0;
				}
				else if (ped1_cord == 4)
				{
					ped1B_x = -390.5;
					ped1B_y = -413.213;
					ped1B_z = 4.8871;
					SetSped1 = 0;
				}
				else if (ped1_cord == 5)
				{
					ped1B_x = -331.407;
					ped1B_y = -392.62;
					ped1B_z = 4.457501;
					SetSped1 = 1;
				}
				else if (ped1_cord == 6)
				{
					ped1B_x = -244.557;
					ped1B_y = -397.992;
					ped1B_z = 8.6473;
					SetSped1 = 0;
				}
				else if (ped1_cord == 7)
				{
					ped1B_x = -155.022;
					ped1B_y = -399.782;
					ped1B_z = 15.4283;
					SetSped1 = 0;
				}
				else if (ped1_cord == 8)
				{
					ped1B_x = -59.219;
					ped1B_y = -399.782;
					ped1B_z = 20.0643;
					SetSped1 = 1;
				}
				else if (ped1_cord == 9)
				{
					ped1B_x = 36.58499;
					ped1B_y = -402.468;
					ped1B_z = 17.5963;
					SetSped1 = 0;
				}
				else if (ped1_cord == 10)
				{
					ped1B_x = 137.76;
					ped1B_y = -406.05;
					ped1B_z = 11.4214;
					SetSped1 = 0;
				}
				else if (ped1_cord == 11)
				{
					ped1B_x = 243.412;
					ped1B_y = -397.096;
					ped1B_z = 6.0187;
					SetSped1 = 0;
				}
				else if (ped1_cord == 12)
				{
					ped1B_x = 328.471;
					ped1B_y = -362.177;
					ped1B_z = 4.2782;
					SetSped1 = 0;
				}
				else if (ped1_cord == 13)
				{
					ped1B_x = 410.8439;
					ped1B_y = -337.107;
					ped1B_z = 4.2782;
					SetSped1 = 0;
				}
				else if (ped1_cord == 14)
				{
					ped1B_x = 506.6471;
					ped1B_y = -325.468;
					ped1B_z = 4.278;
					SetSped1 = 1;
				}
				else if (ped1_cord == 15)
				{
					ped1B_x = 564.845;
					ped1B_y = -254.734;
					ped1B_z = 4.278;
					SetSped1 = 0;
				}
				else if (ped1_cord == 16)
				{
					ped1B_x = 596.183;
					ped1B_y = -173.257;
					ped1B_z = 4.278;
					SetSped1 = 0;
				}
				else if (ped1_cord == 17)
				{
					ped1B_x = 606.032;
					ped1B_y = -113.268;
					ped1B_z = 10.1956;
					SetSped1 = 0;
				}
				else if (ped1_cord == 18)
				{
					ped1B_x = 611.404;
					ped1B_y = -16.57001;
					ped1B_z = 5.689999;
					SetSped1 = 0;
				}
				else if (ped1_cord == 19)
				{
					ped1B_x = 617.671;
					ped1B_y = 80.129;
					ped1B_z = 4.8402;
					SetSped1 = 0;
				}
				else if (ped1_cord == 20)
				{
					ped1B_x = 632.8919;
					ped1B_y = 167.874;
					ped1B_z = 4.465;
					SetSped1 = 0;
				}
				else if (ped1_cord == 21)
				{
					ped1B_x = 657.9621;
					ped1B_y = 257.41;
					ped1B_z = 5.9105;
					SetSped1 = 0;
				}
				else if (ped1_cord == 22)
				{
					ped1B_x = 701.835;
					ped1B_y = 334.41;
					ped1B_z = 4.8572;
					SetSped1 = 1;
				}
				else if (ped1_cord == 23)
				{
					ped1B_x = 741.231;
					ped1B_y = 417.678;
					ped1B_z = 4.8605;
					SetSped1 = 1;
				}
				else if (ped1_cord == 24)
				{
					ped1B_x = 760.9279;
					ped1B_y = 502.7374;
					ped1B_z = 4.9096;
					SetSped1 = 1;
				}
				else if (ped1_cord == 25)
				{
					ped1B_x = 822.708;
					ped1B_y = 553.7727;
					ped1B_z = 9.2094;
					SetSped1 = 0;
				}
				else if (ped1_cord == 26)
				{
					ped1B_x = 880.011;
					ped1B_y = 619.1337;
					ped1B_z = 4.8733;
					SetSped1 = 0;
				}
				else if (ped1_cord == 27)
				{
					ped1B_x = 832.557;
					ped1B_y = 705.983;
					ped1B_z = 4.847;
					SetSped1 = 0;
				}
				else if (ped1_cord == 28)
				{
					ped1B_x = 824.499;
					ped1B_y = 770.449;
					ped1B_z = 4.3895;
					SetSped1 = 0;
				}
				else if (ped1_cord == 29)
				{
					ped1B_x = 773.463;
					ped1B_y = 786.565;
					ped1B_z = 5.1255;
					SetSped1 = 0;
				}
				else if (ped1_cord == 30)
				{
					ped1B_x = 767.1961;
					ped1B_y = 885.055;
					ped1B_z = 5.4291;
					SetSped1 = 0;
				}
				else if (ped1_cord == 31)
				{
					ped1B_x = 782.417;
					ped1B_y = 977.276;
					ped1B_z = 5.4235;
					SetSped1 = 0;
				}
				else if (ped1_cord == 32)
				{
					ped1B_x = 811.068;
					ped1B_y = 1064.126;
					ped1B_z = 5.4235;
					SetSped1 = 0;
				}
				else if (ped1_cord == 33)
				{
					ped1B_x = 815.545;
					ped1B_y = 1140.231;
					ped1B_z = 5.4235;
					SetSped1 = 1;
				}
				else if (ped1_cord == 34)
				{
					ped1B_x = 795.847;
					ped1B_y = 1201.116;
					ped1B_z = 4.894;
					SetSped1 = 0;
				}
				else if (ped1_cord == 35)
				{
					ped1B_x = 697.358;
					ped1B_y = 1202.906;
					ped1B_z = 4.8524;
					SetSped1 = 0;
				}
				else if (ped1_cord == 36)
				{
					ped1B_x = 640.055;
					ped1B_y = 1190.371;
					ped1B_z = 4.849;
					SetSped1 = 1;
				}
				else if (ped1_cord == 37)
				{
					ped1B_x = 611.404;
					ped1B_y = 1203.802;
					ped1B_z = 4.849;
					SetSped1 = 0;
				}
				else if (ped1_cord == 38)
				{
					ped1B_x = 629.311;
					ped1B_y = 1240.511;
					ped1B_z = 4.849;
					SetSped1 = 0;
				}
				else if (ped1_cord == 39)
				{
					ped1B_x = 705.416;
					ped1B_y = 1298.71;
					ped1B_z = 4.8514;
					SetSped1 = 0;
				}
				else if (ped1_cord == 40)
				{
					ped1B_x = 744.812;
					ped1B_y = 1390.036;
					ped1B_z = 4.8551;
					SetSped1 = 0;
				}
				else if (ped1_cord == 41)
				{
					ped1B_x = 751.975;
					ped1B_y = 1507.328;
					ped1B_z = 5.6569;
					SetSped1 = 0;
				}
				else if (ped1_cord == 42)
				{
					ped1B_x = 726.905;
					ped1B_y = 1600.44;
					ped1B_z = 7.0802;
					SetSped1 = 0;
				}
				else if (ped1_cord == 43)
				{
					ped1B_x = 706.312;
					ped1B_y = 1672.07;
					ped1B_z = 15.0402;
					SetSped1 = 1;
				}
				else if (ped1_cord == 44)
				{
					ped1B_x = 716.161;
					ped1B_y = 1733.85;
					ped1B_z = 11.7887;
					SetSped1 = 1;
				}
				else if (ped1_cord == 45)
				{
					ped1B_x = 655.276;
					ped1B_y = 1767.88;
					ped1B_z = 11.18;
					SetSped1 = 0;
				}
				else if (ped1_cord == 46)
				{
					ped1B_x = 716.161;
					ped1B_y = 1814.44;
					ped1B_z = 11.1801;
					SetSped1 = 0;
				}
				else if (ped1_cord == 47)
				{
					ped1B_x = 816.4411;
					ped1B_y = 1814.44;
					ped1B_z = 11.1761;
					SetSped1 = 0;
				}
				else if (ped1_cord == 48)
				{
					ped1B_x = 905.976;
					ped1B_y = 1811.75;
					ped1B_z = 11.5197;
					SetSped1 = 1;
				}
				else if (ped1_cord == 49)
				{
					ped1B_x = 951.639;
					ped1B_y = 1791.16;
					ped1B_z = 10.5517;
					SetSped1 = 0;
				}
				else if (ped1_cord == 50)
				{
					ped1B_x = 941.7901;
					ped1B_y = 1697.14;
					ped1B_z = 11.0812;
					SetSped1 = 0;
				}
				else if (ped1_cord == 51)
				{
					ped1B_x = 932.837;
					ped1B_y = 1607.61;
					ped1B_z = 11.7323;
					SetSped1 = 0;
				}
				else if (ped1_cord == 52)
				{
					ped1B_x = 952.535;
					ped1B_y = 1515.386;
					ped1B_z = 11.9283;
					SetSped1 = 0;
				}
				else if (ped1_cord == 53)
				{
					ped1B_x = 985.878;
					ped1B_y = 1434.804;
					ped1B_z = 8.8502;
					SetSped1 = 0;
				}
				else if (ped1_cord == 54)
				{
					ped1B_x = 992.826;
					ped1B_y = 1353.326;
					ped1B_z = 6.2706;
					SetSped1 = 0;
				}
				else if (ped1_cord == 55)
				{
					ped1B_x = 977.605;
					ped1B_y = 1259.314;
					ped1B_z = 4.9648;
					SetSped1 = 1;
				}
				else if (ped1_cord == 56)
				{
					ped1B_x = 955.221;
					ped1B_y = 1188.581;
					ped1B_z = 4.9354;
					SetSped1 = 0;
				}
				else if (ped1_cord == 57)
				{
					ped1B_x = 852.255;
					ped1B_y = 1213.651;
					ped1B_z = 5.2006;
					SetSped1 = 0;
				}
				else if (ped1_cord == 58)
				{
					ped1B_x = 854.045;
					ped1B_y = 1316.617;
					ped1B_z = 5.2006;
					SetSped1 = 0;
				}
				else if (ped1_cord == 59)
				{
					ped1B_x = 857.627;
					ped1B_y = 1404.362;
					ped1B_z = 5.1785;
					SetSped1 = 0;
				}
				else if (ped1_cord == 60)
				{
					ped1B_x = 837.9289;
					ped1B_y = 1474.2;
					ped1B_z = 6.4493;
					SetSped1 = 1;
				}
				else if (ped1_cord == 61)
				{
					ped1B_x = 736.754;
					ped1B_y = 1483.153;
					ped1B_z = 15.4129;
					SetSped1 = 0;
				}
				else if (ped1_cord == 62)
				{
					ped1B_x = 623.939;
					ped1B_y = 1508.223;
					ped1B_z = 18.2634;
					SetSped1 = 1;
				}
				else if (ped1_cord == 63)
				{
					ped1B_x = 544.339;
					ped1B_y = 1536.54;
					ped1B_z = 4.8228;
					SetSped1 = 2;
				}
				else if (ped1_cord == 64)
				{
					ped1B_x = 529.268;
					ped1B_y = 1441.967;
					ped1B_z = 4.7065;
					SetSped1 = 0;
				}
				else if (ped1_cord == 65)
				{
					ped1B_x = 478.1894;
					ped1B_y = 1398.236;
					ped1B_z = 4.7037;
					SetSped1 = 1;
				}
				else if (ped1_cord == 66)
				{
					ped1B_x = 443.972;
					ped1B_y = 1428.536;
					ped1B_z = 4.7136;
					SetSped1 = 0;
				}
				else if (ped1_cord == 67)
				{
					ped1B_x = 463.9647;
					ped1B_y = 1519.482;
					ped1B_z = 4.7345;
					SetSped1 = 1;
					ped1_cord = 70;
				}
				else if (ped1_cord == 68)
				{
					ped1B_x = 464.2384;
					ped1B_y = 1591.027;
					ped1B_z = 4.8576;
					SetSped1 = 0;
				}
				else if (ped1_cord == 69)
				{
					ped1B_x = 428.572;
					ped1B_y = 1634.68;
					ped1B_z = 10.5335;
					SetSped1 = 1;
				}
				else if (ped1_cord == 70)
				{
					ped1B_x = 352.107;
					ped1B_y = 1594.31;
					ped1B_z = 4.8058;
					SetSped1 = 0;
				}
				else if (ped1_cord == 71)
				{
					ped1B_x = 294.447;
					ped1B_y = 1608.5;
					ped1B_z = 6.180101;
					SetSped1 = 0;
				}
				else if (ped1_cord == 72)
				{
					ped1B_x = 205.807;
					ped1B_y = 1616.56;
					ped1B_z = 14.3942;
					SetSped1 = 0;
				}
				else if (ped1_cord == 73)
				{
					ped1B_x = 118.062;
					ped1B_y = 1617.46;
					ped1B_z = 16.0711;
					SetSped1 = 0;
				}
				else if (ped1_cord == 74)
				{
					ped1B_x = 18.67801;
					ped1B_y = 1618.35;
					ped1B_z = 5.4061;
					SetSped1 = 1;
				}
				else if (ped1_cord == 75)
				{
					ped1B_x = -72.64899;
					ped1B_y = 1632.68;
					ped1B_z = 4.8647;
					SetSped1 = 0;
				}
				else if (ped1_cord == 76)
				{
					ped1B_x = -155.022;
					ped1B_y = 1678.34;
					ped1B_z = 4.872501;
					SetSped1 = 0;
				}
				else if (ped1_cord == 77)
				{
					ped1B_x = -238.29;
					ped1B_y = 1714.16;
					ped1B_z = 4.872501;
					SetSped1 = 0;
				}
				else if (ped1_cord == 78)
				{
					ped1B_x = -339.465;
					ped1B_y = 1709.68;
					ped1B_z = 4.8647;
					SetSped1 = 1;
				}
				else if (ped1_cord == 79)
				{
					ped1B_x = -425.2143;
					ped1B_y = 1688.099;
					ped1B_z = 4.7009;
					SetSped1 = 1;
				}
				else if (ped1_cord == 80)
				{
					ped1B_x = -433.4924;
					ped1B_y = 1597.211;
					ped1B_z = 4.8699;
					SetSped1 = 0;
				}
				else if (ped1_cord == 81)
				{
					ped1B_x = -436.2254;
					ped1B_y = 1501.277;
					ped1B_z = 4.8699;
					SetSped1 = 0;
				}
				else if (ped1_cord == 82)
				{
					ped1B_x = -438.7631;
					ped1B_y = 1395.701;
					ped1B_z = 4.8816;
					SetSped1 = 0;
				}
				else if (ped1_cord == 83)
				{
					ped1B_x = -437.408;
					ped1B_y = 1311.439;
					ped1B_z = 4.8816;
					SetSped1 = 1;
				}
				else if (ped1_cord == 84)
				{
					ped1B_x = -274.465;
					ped1B_y = 1284.54;
					ped1B_z = 4.8816;
					SetSped1 = 1;
				}
				else if (ped1_cord == 85)
				{
					ped1B_x = -240.0354;
					ped1B_y = 1267.206;
					ped1B_z = 4.9913;
					SetSped1 = 2;
				}
				else if (ped1_cord == 86)
				{
					ped1B_x = -244.4168;
					ped1B_y = 1167.997;
					ped1B_z = 4.8813;
					SetSped1 = 0;
				}
				else if (ped1_cord == 87)
				{
					ped1B_x = -253.957;
					ped1B_y = 1072.407;
					ped1B_z = 4.8847;
					SetSped1 = 0;
				}
				else if (ped1_cord == 88)
				{
					ped1B_x = -264.2693;
					ped1B_y = 981.9677;
					ped1B_z = 4.8925;
					SetSped1 = 1;
					ped1_cord = 89;
				}
				else if (ped1_cord == 89)
				{
					ped1B_x = -272.3832;
					ped1B_y = 889.7058;
					ped1B_z = 4.8679;
					SetSped1 = 1;
				}
				else if (ped1_cord == 90)
				{
					ped1B_x = -295.8838;
					ped1B_y = 826.4709;
					ped1B_z = 4.9507;
					SetSped1 = 2;
				}
				else if (ped1_cord == 91)
				{
					ped1B_x = -365.431;
					ped1B_y = 839.391;
					ped1B_z = 5.2203;
					SetSped1 = 0;
				}
				else if (ped1_cord == 92)
				{
					ped1B_x = -458.548;
					ped1B_y = 850.136;
					ped1B_z = 5.2165;
					SetSped1 = 0;
				}
				else if (ped1_cord == 93)
				{
					ped1B_x = -543.1764;
					ped1B_y = 857.2659;
					ped1B_z = 5.1999;
					SetSped1 = 1;
				}
				else if (ped1_cord == 94)
				{
					ped1B_x = -583.0317;
					ped1B_y = 777.374;
					ped1B_z = 5.1766;
					SetSped1 = 0;
				}
				else if (ped1_cord == 95)
				{
					ped1B_x = -621.1567;
					ped1B_y = 684.0111;
					ped1B_z = 5.2094;
					SetSped1 = 0;
				}
				else if (ped1_cord == 96)
				{
					ped1B_x = -636.8751;
					ped1B_y = 581.2972;
					ped1B_z = 5.2116;
					SetSped1 = 0;
				}
				else if (ped1_cord == 97)
				{
					ped1B_x = -634.963;
					ped1B_y = 478.759;
					ped1B_z = 5.2118;
					SetSped1 = 1;
				}
				else if (ped1_cord == 98)
				{
					ped1B_x = -677.264;
					ped1B_y = 464.626;
					ped1B_z = 5.3946;
					SetSped1 = 0;
				}
				else if (ped1_cord == 99)
				{
					ped1B_x = -716.8814;
					ped1B_y = 455.9111;
					ped1B_z = 5.3912;
					SetSped1 = 0;
				}
				else if (ped1_cord == 100)
				{
					ped1B_x = -751.4313;
					ped1B_y = 384.294;
					ped1B_z = 5.3799;
					SetSped1 = 0;
				}
				else if (ped1_cord == 101)
				{
					ped1B_x = -752.5255;
					ped1B_y = 281.0686;
					ped1B_z = 5.3807;
					SetSped1 = 0;
				}
				else if (ped1_cord == 102)
				{
					ped1B_x = -749.1074;
					ped1B_y = 182.7831;
					ped1B_z = 4.7105;
					SetSped1 = 1;
				}
				else if (ped1_cord == 103)
				{
					ped1B_x = -765.843;
					ped1B_y = 83.67506;
					ped1B_z = 4.7421;
					SetSped1 = 1;
				}
				else if (ped1_cord == 104)
				{
					ped1B_x = -721.182;
					ped1B_y = 33.6928;
					ped1B_z = 4.7692;
					SetSped1 = 0;
				}
				else if (ped1_cord == 105)
				{
					ped1B_x = -659.649;
					ped1B_y = 42.2182;
					ped1B_z = 5.1038;
					SetSped1 = 2;
				}
				else if (ped1_cord == 106)
				{
					ped1B_x = -632.6763;
					ped1B_y = -49.21457;
					ped1B_z = 4.9241;
					SetSped1 = 0;
				}
				else if (ped1_cord == 107)
				{
					ped1B_x = -552.5643;
					ped1B_y = -50.53316;
					ped1B_z = 5.2854;
					SetSped1 = 0;
				}
				else if (ped1_cord == 108)
				{
					ped1B_x = -549.1974;
					ped1B_y = -134.2322;
					ped1B_z = 5.5705;
					SetSped1 = 0;
				}
				else if (ped1_cord == 109)
				{
					ped1B_x = -623.8671;
					ped1B_y = -143.9434;
					ped1B_z = 5.5966;
					SetSped1 = 0;
				}
				else if (ped1_cord == 110)
				{
					ped1B_x = -694.3903;
					ped1B_y = -154.4668;
					ped1B_z = 5.5742;
					SetSped1 = 1;
				}
				else if (ped1_cord == 111)
				{
					ped1B_x = -678.81;
					ped1B_y = -256.525;
					ped1B_z = 5.6719;
					SetSped1 = 0;
				}
				else if (ped1_cord == 112)
				{
					ped1B_x = -638.51;
					ped1B_y = -332.631;
					ped1B_z = 6.3928;
					SetSped1 = 0;
				}
				else if (ped1_cord == 113)
				{
					ped1B_x = -562.409;
					ped1B_y = -413.213;
					ped1B_z = 8.658201;
					SetSped1 = 0;
				}
				else if (ped1_cord == 114)
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

//============================== соперник 2 ==============================
			GET_CHAR_COORDINATES(ped2,  &Ped2X, &Ped2Y, &Ped2Z);//вписываем координаты соперника в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( Ped2X, Ped2Y, Ped2Z, ped2B_x, ped2B_y, ped2B_z, &Ped2R);//проверка "игрок на координатах"
			if ( Ped2R < 55.0)
			{
				if (SetSped2 == 0)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 65.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
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
					ped2B_x = -454.966;
					ped2B_y = -540.35;
					ped2B_z = 8.647801;
					SetSped2 = 0;
				}
				else if (ped2_cord == 3)
				{
					ped2B_x = -391.396;
					ped2B_y = -507.23;
					ped2B_z = 4.8895;
					SetSped2 = 0;
				}
				else if (ped2_cord == 4)
				{
					ped2B_x = -390.5;
					ped2B_y = -413.213;
					ped2B_z = 4.8871;
					SetSped2 = 0;
				}
				else if (ped2_cord == 5)
				{
					ped2B_x = -331.407;
					ped2B_y = -392.62;
					ped2B_z = 4.457501;
					SetSped2 = 1;
				}
				else if (ped2_cord == 6)
				{
					ped2B_x = -244.557;
					ped2B_y = -397.992;
					ped2B_z = 8.6473;
					SetSped2 = 0;
				}
				else if (ped2_cord == 7)
				{
					ped2B_x = -155.022;
					ped2B_y = -399.782;
					ped2B_z = 15.4283;
					SetSped2 = 0;
				}
				else if (ped2_cord == 8)
				{
					ped2B_x = -59.219;
					ped2B_y = -399.782;
					ped2B_z = 20.0643;
					SetSped2 = 1;
				}
				else if (ped2_cord == 9)
				{
					ped2B_x = 36.58499;
					ped2B_y = -402.468;
					ped2B_z = 17.5963;
					SetSped2 = 0;
				}
				else if (ped2_cord == 10)
				{
					ped2B_x = 137.76;
					ped2B_y = -406.05;
					ped2B_z = 11.4214;
					SetSped2 = 0;
				}
				else if (ped2_cord == 11)
				{
					ped2B_x = 243.412;
					ped2B_y = -397.096;
					ped2B_z = 6.0187;
					SetSped2 = 0;
				}
				else if (ped2_cord == 12)
				{
					ped2B_x = 328.471;
					ped2B_y = -362.177;
					ped2B_z = 4.2782;
					SetSped2 = 0;
				}
				else if (ped2_cord == 13)
				{
					ped2B_x = 410.8439;
					ped2B_y = -337.107;
					ped2B_z = 4.2782;
					SetSped2 = 0;
				}
				else if (ped2_cord == 14)
				{
					ped2B_x = 506.6471;
					ped2B_y = -325.468;
					ped2B_z = 4.278;
					SetSped2 = 1;
				}
				else if (ped2_cord == 15)
				{
					ped2B_x = 564.845;
					ped2B_y = -254.734;
					ped2B_z = 4.278;
					SetSped2 = 0;
				}
				else if (ped2_cord == 16)
				{
					ped2B_x = 596.183;
					ped2B_y = -173.257;
					ped2B_z = 4.278;
					SetSped2 = 0;
				}
				else if (ped2_cord == 17)
				{
					ped2B_x = 606.032;
					ped2B_y = -113.268;
					ped2B_z = 10.1956;
					SetSped2 = 0;
				}
				else if (ped2_cord == 18)
				{
					ped2B_x = 611.404;
					ped2B_y = -16.57001;
					ped2B_z = 5.689999;
					SetSped2 = 0;
				}
				else if (ped2_cord == 19)
				{
					ped2B_x = 617.671;
					ped2B_y = 80.129;
					ped2B_z = 4.8402;
					SetSped2 = 0;
				}
				else if (ped2_cord == 20)
				{
					ped2B_x = 632.8919;
					ped2B_y = 167.874;
					ped2B_z = 4.465;
					SetSped2 = 0;
				}
				else if (ped2_cord == 21)
				{
					ped2B_x = 657.9621;
					ped2B_y = 257.41;
					ped2B_z = 5.9105;
					SetSped2 = 0;
				}
				else if (ped2_cord == 22)
				{
					ped2B_x = 701.835;
					ped2B_y = 334.41;
					ped2B_z = 4.8572;
					SetSped2 = 1;
				}
				else if (ped2_cord == 23)
				{
					ped2B_x = 741.231;
					ped2B_y = 417.678;
					ped2B_z = 4.8605;
					SetSped2 = 1;
				}
				else if (ped2_cord == 24)
				{
					ped2B_x = 760.9279;
					ped2B_y = 502.7374;
					ped2B_z = 4.9096;
					SetSped2 = 1;
				}
				else if (ped2_cord == 25)
				{
					ped2B_x = 822.708;
					ped2B_y = 553.7727;
					ped2B_z = 9.2094;
					SetSped2 = 0;
				}
				else if (ped2_cord == 26)
				{
					ped2B_x = 880.011;
					ped2B_y = 619.1337;
					ped2B_z = 4.8733;
					SetSped2 = 0;
				}
				else if (ped2_cord == 27)
				{
					ped2B_x = 832.557;
					ped2B_y = 705.983;
					ped2B_z = 4.847;
					SetSped2 = 0;
				}
				else if (ped2_cord == 28)
				{
					ped2B_x = 824.499;
					ped2B_y = 770.449;
					ped2B_z = 4.3895;
					SetSped2 = 0;
				}
				else if (ped2_cord == 29)
				{
					ped2B_x = 773.463;
					ped2B_y = 786.565;
					ped2B_z = 5.1255;
					SetSped2 = 0;
				}
				else if (ped2_cord == 30)
				{
					ped2B_x = 767.1961;
					ped2B_y = 885.055;
					ped2B_z = 5.4291;
					SetSped2 = 0;
				}
				else if (ped2_cord == 31)
				{
					ped2B_x = 782.417;
					ped2B_y = 977.276;
					ped2B_z = 5.4235;
					SetSped2 = 0;
				}
				else if (ped2_cord == 32)
				{
					ped2B_x = 811.068;
					ped2B_y = 1064.126;
					ped2B_z = 5.4235;
					SetSped2 = 0;
				}
				else if (ped2_cord == 33)
				{
					ped2B_x = 815.545;
					ped2B_y = 1140.231;
					ped2B_z = 5.4235;
					SetSped2 = 1;
				}
				else if (ped2_cord == 34)
				{
					ped2B_x = 795.847;
					ped2B_y = 1201.116;
					ped2B_z = 4.894;
					SetSped2 = 0;
				}
				else if (ped2_cord == 35)
				{
					ped2B_x = 697.358;
					ped2B_y = 1202.906;
					ped2B_z = 4.8524;
					SetSped2 = 0;
				}
				else if (ped2_cord == 36)
				{
					ped2B_x = 640.055;
					ped2B_y = 1190.371;
					ped2B_z = 4.849;
					SetSped2 = 1;
				}
				else if (ped2_cord == 37)
				{
					ped2B_x = 611.404;
					ped2B_y = 1203.802;
					ped2B_z = 4.849;
					SetSped2 = 0;
				}
				else if (ped2_cord == 38)
				{
					ped2B_x = 629.311;
					ped2B_y = 1240.511;
					ped2B_z = 4.849;
					SetSped2 = 0;
				}
				else if (ped2_cord == 39)
				{
					ped2B_x = 705.416;
					ped2B_y = 1298.71;
					ped2B_z = 4.8514;
					SetSped2 = 0;
				}
				else if (ped2_cord == 40)
				{
					ped2B_x = 744.812;
					ped2B_y = 1390.036;
					ped2B_z = 4.8551;
					SetSped2 = 0;
				}
				else if (ped2_cord == 41)
				{
					ped2B_x = 751.975;
					ped2B_y = 1507.328;
					ped2B_z = 5.6569;
					SetSped2 = 0;
				}
				else if (ped2_cord == 42)
				{
					ped2B_x = 726.905;
					ped2B_y = 1600.44;
					ped2B_z = 7.0802;
					SetSped2 = 0;
				}
				else if (ped2_cord == 43)
				{
					ped2B_x = 706.312;
					ped2B_y = 1672.07;
					ped2B_z = 15.0402;
					SetSped2 = 1;
				}
				else if (ped2_cord == 44)
				{
					ped2B_x = 716.161;
					ped2B_y = 1733.85;
					ped2B_z = 11.7887;
					SetSped2 = 1;
				}
				else if (ped2_cord == 45)
				{
					ped2B_x = 655.276;
					ped2B_y = 1767.88;
					ped2B_z = 11.18;
					SetSped2 = 0;
				}
				else if (ped2_cord == 46)
				{
					ped2B_x = 716.161;
					ped2B_y = 1814.44;
					ped2B_z = 11.1801;
					SetSped2 = 0;
				}
				else if (ped2_cord == 47)
				{
					ped2B_x = 816.4411;
					ped2B_y = 1814.44;
					ped2B_z = 11.1761;
					SetSped2 = 0;
				}
				else if (ped2_cord == 48)
				{
					ped2B_x = 905.976;
					ped2B_y = 1811.75;
					ped2B_z = 11.5197;
					SetSped2 = 1;
				}
				else if (ped2_cord == 49)
				{
					ped2B_x = 951.639;
					ped2B_y = 1791.16;
					ped2B_z = 10.5517;
					SetSped2 = 0;
				}
				else if (ped2_cord == 50)
				{
					ped2B_x = 941.7901;
					ped2B_y = 1697.14;
					ped2B_z = 11.0812;
					SetSped2 = 0;
				}
				else if (ped2_cord == 51)
				{
					ped2B_x = 932.837;
					ped2B_y = 1607.61;
					ped2B_z = 11.7323;
					SetSped2 = 0;
				}
				else if (ped2_cord == 52)
				{
					ped2B_x = 952.535;
					ped2B_y = 1515.386;
					ped2B_z = 11.9283;
					SetSped2 = 0;
				}
				else if (ped2_cord == 53)
				{
					ped2B_x = 985.878;
					ped2B_y = 1434.804;
					ped2B_z = 8.8502;
					SetSped2 = 0;
				}
				else if (ped2_cord == 54)
				{
					ped2B_x = 992.826;
					ped2B_y = 1353.326;
					ped2B_z = 6.2706;
					SetSped2 = 0;
				}
				else if (ped2_cord == 55)
				{
					ped2B_x = 977.605;
					ped2B_y = 1259.314;
					ped2B_z = 4.9648;
					SetSped2 = 1;
				}
				else if (ped2_cord == 56)
				{
					ped2B_x = 955.221;
					ped2B_y = 1188.581;
					ped2B_z = 4.9354;
					SetSped2 = 0;
				}
				else if (ped2_cord == 57)
				{
					ped2B_x = 852.255;
					ped2B_y = 1213.651;
					ped2B_z = 5.2006;
					SetSped2 = 0;
				}
				else if (ped2_cord == 58)
				{
					ped2B_x = 854.045;
					ped2B_y = 1316.617;
					ped2B_z = 5.2006;
					SetSped2 = 0;
				}
				else if (ped2_cord == 59)
				{
					ped2B_x = 857.627;
					ped2B_y = 1404.362;
					ped2B_z = 5.1785;
					SetSped2 = 0;
				}
				else if (ped2_cord == 60)
				{
					ped2B_x = 837.9289;
					ped2B_y = 1474.2;
					ped2B_z = 6.4493;
					SetSped2 = 1;
				}
				else if (ped2_cord == 61)
				{
					ped2B_x = 736.754;
					ped2B_y = 1483.153;
					ped2B_z = 15.4129;
					SetSped2 = 0;
				}
				else if (ped2_cord == 62)
				{
					ped2B_x = 623.939;
					ped2B_y = 1508.223;
					ped2B_z = 18.2634;
					SetSped2 = 1;
				}
				else if (ped2_cord == 63)
				{
					ped2B_x = 544.339;
					ped2B_y = 1536.54;
					ped2B_z = 4.8228;
					SetSped2 = 2;
				}
				else if (ped2_cord == 64)
				{
					ped2B_x = 529.268;
					ped2B_y = 1441.967;
					ped2B_z = 4.7065;
					SetSped2 = 0;
				}
				else if (ped2_cord == 65)
				{
					ped2B_x = 478.1894;
					ped2B_y = 1398.236;
					ped2B_z = 4.7037;
					SetSped2 = 1;
				}
				else if (ped2_cord == 66)
				{
					ped2B_x = 443.972;
					ped2B_y = 1428.536;
					ped2B_z = 4.7136;
					SetSped2 = 0;
				}
				else if (ped2_cord == 67)
				{
					ped2B_x = 463.9647;
					ped2B_y = 1519.482;
					ped2B_z = 4.7345;
					SetSped2 = 1;
					ped2_cord = 70;
				}
				else if (ped2_cord == 68)
				{
					ped2B_x = 464.2384;
					ped2B_y = 1591.027;
					ped2B_z = 4.8576;
					SetSped2 = 0;
				}
				else if (ped2_cord == 69)
				{
					ped2B_x = 428.572;
					ped2B_y = 1634.68;
					ped2B_z = 10.5335;
					SetSped2 = 1;
				}
				else if (ped2_cord == 70)
				{
					ped2B_x = 352.107;
					ped2B_y = 1594.31;
					ped2B_z = 4.8058;
					SetSped2 = 0;
				}
				else if (ped2_cord == 71)
				{
					ped2B_x = 294.447;
					ped2B_y = 1608.5;
					ped2B_z = 6.180101;
					SetSped2 = 0;
				}
				else if (ped2_cord == 72)
				{
					ped2B_x = 205.807;
					ped2B_y = 1616.56;
					ped2B_z = 14.3942;
					SetSped2 = 0;
				}
				else if (ped2_cord == 73)
				{
					ped2B_x = 118.062;
					ped2B_y = 1617.46;
					ped2B_z = 16.0711;
					SetSped2 = 0;
				}
				else if (ped2_cord == 74)
				{
					ped2B_x = 18.67801;
					ped2B_y = 1618.35;
					ped2B_z = 5.4061;
					SetSped2 = 1;
				}
				else if (ped2_cord == 75)
				{
					ped2B_x = -72.64899;
					ped2B_y = 1632.68;
					ped2B_z = 4.8647;
					SetSped2 = 0;
				}
				else if (ped2_cord == 76)
				{
					ped2B_x = -155.022;
					ped2B_y = 1678.34;
					ped2B_z = 4.872501;
					SetSped2 = 0;
				}
				else if (ped2_cord == 77)
				{
					ped2B_x = -238.29;
					ped2B_y = 1714.16;
					ped2B_z = 4.872501;
					SetSped2 = 0;
				}
				else if (ped2_cord == 78)
				{
					ped2B_x = -339.465;
					ped2B_y = 1709.68;
					ped2B_z = 4.8647;
					SetSped2 = 1;
				}
				else if (ped2_cord == 79)
				{
					ped2B_x = -425.2143;
					ped2B_y = 1688.099;
					ped2B_z = 4.7009;
					SetSped2 = 1;
				}
				else if (ped2_cord == 80)
				{
					ped2B_x = -433.4924;
					ped2B_y = 1597.211;
					ped2B_z = 4.8699;
					SetSped2 = 0;
				}
				else if (ped2_cord == 81)
				{
					ped2B_x = -436.2254;
					ped2B_y = 1501.277;
					ped2B_z = 4.8699;
					SetSped2 = 0;
				}
				else if (ped2_cord == 82)
				{
					ped2B_x = -438.7631;
					ped2B_y = 1395.701;
					ped2B_z = 4.8816;
					SetSped2 = 0;
				}
				else if (ped2_cord == 83)
				{
					ped2B_x = -437.408;
					ped2B_y = 1311.439;
					ped2B_z = 4.8816;
					SetSped2 = 1;
				}
				else if (ped2_cord == 84)
				{
					ped2B_x = -274.465;
					ped2B_y = 1284.54;
					ped2B_z = 4.8816;
					SetSped2 = 1;
				}
				else if (ped2_cord == 85)
				{
					ped2B_x = -240.0354;
					ped2B_y = 1267.206;
					ped2B_z = 4.9913;
					SetSped2 = 2;
				}
				else if (ped2_cord == 86)
				{
					ped2B_x = -244.4168;
					ped2B_y = 1167.997;
					ped2B_z = 4.8813;
					SetSped2 = 0;
				}
				else if (ped2_cord == 87)
				{
					ped2B_x = -253.957;
					ped2B_y = 1072.407;
					ped2B_z = 4.8847;
					SetSped2 = 0;
				}
				else if (ped2_cord == 88)
				{
					ped2B_x = -264.2693;
					ped2B_y = 981.9677;
					ped2B_z = 4.8925;
					SetSped2 = 1;
					ped2_cord = 89;
				}
				else if (ped2_cord == 89)
				{
					ped2B_x = -272.3832;
					ped2B_y = 889.7058;
					ped2B_z = 4.8679;
					SetSped2 = 1;
				}
				else if (ped2_cord == 90)
				{
					ped2B_x = -295.8838;
					ped2B_y = 826.4709;
					ped2B_z = 4.9507;
					SetSped2 = 2;
				}
				else if (ped2_cord == 91)
				{
					ped2B_x = -365.431;
					ped2B_y = 839.391;
					ped2B_z = 5.2203;
					SetSped2 = 0;
				}
				else if (ped2_cord == 92)
				{
					ped2B_x = -458.548;
					ped2B_y = 850.136;
					ped2B_z = 5.2165;
					SetSped2 = 0;
				}
				else if (ped2_cord == 93)
				{
					ped2B_x = -543.1764;
					ped2B_y = 857.2659;
					ped2B_z = 5.1999;
					SetSped2 = 1;
				}
				else if (ped2_cord == 94)
				{
					ped2B_x = -583.0317;
					ped2B_y = 777.374;
					ped2B_z = 5.1766;
					SetSped2 = 0;
				}
				else if (ped2_cord == 95)
				{
					ped2B_x = -621.1567;
					ped2B_y = 684.0111;
					ped2B_z = 5.2094;
					SetSped2 = 0;
				}
				else if (ped2_cord == 96)
				{
					ped2B_x = -636.8751;
					ped2B_y = 581.2972;
					ped2B_z = 5.2116;
					SetSped2 = 0;
				}
				else if (ped2_cord == 97)
				{
					ped2B_x = -634.963;
					ped2B_y = 478.759;
					ped2B_z = 5.2118;
					SetSped2 = 1;
				}
				else if (ped2_cord == 98)
				{
					ped2B_x = -677.264;
					ped2B_y = 464.626;
					ped2B_z = 5.3946;
					SetSped2 = 0;
				}
				else if (ped2_cord == 99)
				{
					ped2B_x = -716.8814;
					ped2B_y = 455.9111;
					ped2B_z = 5.3912;
					SetSped2 = 0;
				}
				else if (ped2_cord == 100)
				{
					ped2B_x = -751.4313;
					ped2B_y = 384.294;
					ped2B_z = 5.3799;
					SetSped2 = 0;
				}
				else if (ped2_cord == 101)
				{
					ped2B_x = -752.5255;
					ped2B_y = 281.0686;
					ped2B_z = 5.3807;
					SetSped2 = 0;
				}
				else if (ped2_cord == 102)
				{
					ped2B_x = -749.1074;
					ped2B_y = 182.7831;
					ped2B_z = 4.7105;
					SetSped2 = 1;
				}
				else if (ped2_cord == 103)
				{
					ped2B_x = -765.843;
					ped2B_y = 83.67506;
					ped2B_z = 4.7421;
					SetSped2 = 1;
				}
				else if (ped2_cord == 104)
				{
					ped2B_x = -721.182;
					ped2B_y = 33.6928;
					ped2B_z = 4.7692;
					SetSped2 = 0;
				}
				else if (ped2_cord == 105)
				{
					ped2B_x = -659.649;
					ped2B_y = 42.2182;
					ped2B_z = 5.1038;
					SetSped2 = 2;
				}
				else if (ped2_cord == 106)
				{
					ped2B_x = -632.6763;
					ped2B_y = -49.21457;
					ped2B_z = 4.9241;
					SetSped2 = 0;
				}
				else if (ped2_cord == 107)
				{
					ped2B_x = -552.5643;
					ped2B_y = -50.53316;
					ped2B_z = 5.2854;
					SetSped2 = 0;
				}
				else if (ped2_cord == 108)
				{
					ped2B_x = -549.1974;
					ped2B_y = -134.2322;
					ped2B_z = 5.5705;
					SetSped2 = 0;
				}
				else if (ped2_cord == 109)
				{
					ped2B_x = -623.8671;
					ped2B_y = -143.9434;
					ped2B_z = 5.5966;
					SetSped2 = 0;
				}
				else if (ped2_cord == 110)
				{
					ped2B_x = -694.3903;
					ped2B_y = -154.4668;
					ped2B_z = 5.5742;
					SetSped2 = 1;
				}
				else if (ped2_cord == 111)
				{
					ped2B_x = -678.81;
					ped2B_y = -256.525;
					ped2B_z = 5.6719;
					SetSped2 = 0;
				}
				else if (ped2_cord == 112)
				{
					ped2B_x = -638.51;
					ped2B_y = -332.631;
					ped2B_z = 6.3928;
					SetSped2 = 0;
				}
				else if (ped2_cord == 113)
				{
					ped2B_x = -562.409;
					ped2B_y = -413.213;
					ped2B_z = 8.658201;
					SetSped2 = 0;
				}
				else if (ped2_cord == 114)
				{
					ped2B_x = ped2B_x; 
					ped2B_y = ped2B_y;
					ped2B_z = ped2B_z;
					SetSped2 = 0;
					skip = 1;
					PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
					break;
				}
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped2, car2, ped2B_x, ped2B_y, ped2B_z, 4, 60.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
			}

//============================== соперник 3 ==============================
			GET_CHAR_COORDINATES(ped3,  &Ped3X, &Ped3Y, &Ped3Z);//вписываем координаты соперника в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( Ped3X, Ped3Y, Ped3Z, ped3B_x, ped3B_y, ped3B_z, &Ped3R);//проверка "игрок на координатах"
			if ( Ped3R < 55.0)
			{
				if (SetSped3 == 0)
				{
					TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 65.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
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
					ped3B_x = -454.966;
					ped3B_y = -540.35;
					ped3B_z = 8.647801;
					SetSped3 = 0;
				}
				else if (ped3_cord == 3)
				{
					ped3B_x = -391.396;
					ped3B_y = -507.23;
					ped3B_z = 4.8895;
					SetSped3 = 0;
				}
				else if (ped3_cord == 4)
				{
					ped3B_x = -390.5;
					ped3B_y = -413.213;
					ped3B_z = 4.8871;
					SetSped3 = 0;
				}
				else if (ped3_cord == 5)
				{
					ped3B_x = -331.407;
					ped3B_y = -392.62;
					ped3B_z = 4.457501;
					SetSped3 = 1;
				}
				else if (ped3_cord == 6)
				{
					ped3B_x = -244.557;
					ped3B_y = -397.992;
					ped3B_z = 8.6473;
					SetSped3 = 0;
				}
				else if (ped3_cord == 7)
				{
					ped3B_x = -155.022;
					ped3B_y = -399.782;
					ped3B_z = 15.4283;
					SetSped3 = 0;
				}
				else if (ped3_cord == 8)
				{
					ped3B_x = -59.219;
					ped3B_y = -399.782;
					ped3B_z = 20.0643;
					SetSped3 = 1;
				}
				else if (ped3_cord == 9)
				{
					ped3B_x = 36.58499;
					ped3B_y = -402.468;
					ped3B_z = 17.5963;
					SetSped3 = 0;
				}
				else if (ped3_cord == 10)
				{
					ped3B_x = 137.76;
					ped3B_y = -406.05;
					ped3B_z = 11.4214;
					SetSped3 = 0;
				}
				else if (ped3_cord == 11)
				{
					ped3B_x = 243.412;
					ped3B_y = -397.096;
					ped3B_z = 6.0187;
					SetSped3 = 0;
				}
				else if (ped3_cord == 12)
				{
					ped3B_x = 328.471;
					ped3B_y = -362.177;
					ped3B_z = 4.2782;
					SetSped3 = 0;
				}
				else if (ped3_cord == 13)
				{
					ped3B_x = 410.8439;
					ped3B_y = -337.107;
					ped3B_z = 4.2782;
					SetSped3 = 0;
				}
				else if (ped3_cord == 14)
				{
					ped3B_x = 506.6471;
					ped3B_y = -325.468;
					ped3B_z = 4.278;
					SetSped3 = 1;
				}
				else if (ped3_cord == 15)
				{
					ped3B_x = 564.845;
					ped3B_y = -254.734;
					ped3B_z = 4.278;
					SetSped3 = 0;
				}
				else if (ped3_cord == 16)
				{
					ped3B_x = 596.183;
					ped3B_y = -173.257;
					ped3B_z = 4.278;
					SetSped3 = 0;
				}
				else if (ped3_cord == 17)
				{
					ped3B_x = 606.032;
					ped3B_y = -113.268;
					ped3B_z = 10.1956;
					SetSped3 = 0;
				}
				else if (ped3_cord == 18)
				{
					ped3B_x = 611.404;
					ped3B_y = -16.57001;
					ped3B_z = 5.689999;
					SetSped3 = 0;
				}
				else if (ped3_cord == 19)
				{
					ped3B_x = 617.671;
					ped3B_y = 80.129;
					ped3B_z = 4.8402;
					SetSped3 = 0;
				}
				else if (ped3_cord == 20)
				{
					ped3B_x = 632.8919;
					ped3B_y = 167.874;
					ped3B_z = 4.465;
					SetSped3 = 0;
				}
				else if (ped3_cord == 21)
				{
					ped3B_x = 657.9621;
					ped3B_y = 257.41;
					ped3B_z = 5.9105;
					SetSped3 = 0;
				}
				else if (ped3_cord == 22)
				{
					ped3B_x = 701.835;
					ped3B_y = 334.41;
					ped3B_z = 4.8572;
					SetSped3 = 1;
				}
				else if (ped3_cord == 23)
				{
					ped3B_x = 741.231;
					ped3B_y = 417.678;
					ped3B_z = 4.8605;
					SetSped3 = 1;
				}
				else if (ped3_cord == 24)
				{
					ped3B_x = 760.9279;
					ped3B_y = 502.7374;
					ped3B_z = 4.9096;
					SetSped3 = 1;
				}
				else if (ped3_cord == 25)
				{
					ped3B_x = 822.708;
					ped3B_y = 553.7727;
					ped3B_z = 9.2094;
					SetSped3 = 0;
				}
				else if (ped3_cord == 26)
				{
					ped3B_x = 880.011;
					ped3B_y = 619.1337;
					ped3B_z = 4.8733;
					SetSped3 = 0;
				}
				else if (ped3_cord == 27)
				{
					ped3B_x = 832.557;
					ped3B_y = 705.983;
					ped3B_z = 4.847;
					SetSped3 = 0;
				}
				else if (ped3_cord == 28)
				{
					ped3B_x = 824.499;
					ped3B_y = 770.449;
					ped3B_z = 4.3895;
					SetSped3 = 0;
				}
				else if (ped3_cord == 29)
				{
					ped3B_x = 773.463;
					ped3B_y = 786.565;
					ped3B_z = 5.1255;
					SetSped3 = 0;
				}
				else if (ped3_cord == 30)
				{
					ped3B_x = 767.1961;
					ped3B_y = 885.055;
					ped3B_z = 5.4291;
					SetSped3 = 0;
				}
				else if (ped3_cord == 31)
				{
					ped3B_x = 782.417;
					ped3B_y = 977.276;
					ped3B_z = 5.4235;
					SetSped3 = 0;
				}
				else if (ped3_cord == 32)
				{
					ped3B_x = 811.068;
					ped3B_y = 1064.126;
					ped3B_z = 5.4235;
					SetSped3 = 0;
				}
				else if (ped3_cord == 33)
				{
					ped3B_x = 815.545;
					ped3B_y = 1140.231;
					ped3B_z = 5.4235;
					SetSped3 = 1;
				}
				else if (ped3_cord == 34)
				{
					ped3B_x = 795.847;
					ped3B_y = 1201.116;
					ped3B_z = 4.894;
					SetSped3 = 0;
				}
				else if (ped3_cord == 35)
				{
					ped3B_x = 697.358;
					ped3B_y = 1202.906;
					ped3B_z = 4.8524;
					SetSped3 = 0;
				}
				else if (ped3_cord == 36)
				{
					ped3B_x = 640.055;
					ped3B_y = 1190.371;
					ped3B_z = 4.849;
					SetSped3 = 1;
				}
				else if (ped3_cord == 37)
				{
					ped3B_x = 611.404;
					ped3B_y = 1203.802;
					ped3B_z = 4.849;
					SetSped3 = 0;
				}
				else if (ped3_cord == 38)
				{
					ped3B_x = 629.311;
					ped3B_y = 1240.511;
					ped3B_z = 4.849;
					SetSped3 = 0;
				}
				else if (ped3_cord == 39)
				{
					ped3B_x = 705.416;
					ped3B_y = 1298.71;
					ped3B_z = 4.8514;
					SetSped3 = 0;
				}
				else if (ped3_cord == 40)
				{
					ped3B_x = 744.812;
					ped3B_y = 1390.036;
					ped3B_z = 4.8551;
					SetSped3 = 0;
				}
				else if (ped3_cord == 41)
				{
					ped3B_x = 751.975;
					ped3B_y = 1507.328;
					ped3B_z = 5.6569;
					SetSped3 = 0;
				}
				else if (ped3_cord == 42)
				{
					ped3B_x = 726.905;
					ped3B_y = 1600.44;
					ped3B_z = 7.0802;
					SetSped3 = 0;
				}
				else if (ped3_cord == 43)
				{
					ped3B_x = 706.312;
					ped3B_y = 1672.07;
					ped3B_z = 15.0402;
					SetSped3 = 1;
				}
				else if (ped3_cord == 44)
				{
					ped3B_x = 716.161;
					ped3B_y = 1733.85;
					ped3B_z = 11.7887;
					SetSped3 = 1;
				}
				else if (ped3_cord == 45)
				{
					ped3B_x = 655.276;
					ped3B_y = 1767.88;
					ped3B_z = 11.18;
					SetSped3 = 0;
				}
				else if (ped3_cord == 46)
				{
					ped3B_x = 716.161;
					ped3B_y = 1814.44;
					ped3B_z = 11.1801;
					SetSped3 = 0;
				}
				else if (ped3_cord == 47)
				{
					ped3B_x = 816.4411;
					ped3B_y = 1814.44;
					ped3B_z = 11.1761;
					SetSped3 = 0;
				}
				else if (ped3_cord == 48)
				{
					ped3B_x = 905.976;
					ped3B_y = 1811.75;
					ped3B_z = 11.5197;
					SetSped3 = 1;
				}
				else if (ped3_cord == 49)
				{
					ped3B_x = 951.639;
					ped3B_y = 1791.16;
					ped3B_z = 10.5517;
					SetSped3 = 0;
				}
				else if (ped3_cord == 50)
				{
					ped3B_x = 941.7901;
					ped3B_y = 1697.14;
					ped3B_z = 11.0812;
					SetSped3 = 0;
				}
				else if (ped3_cord == 51)
				{
					ped3B_x = 932.837;
					ped3B_y = 1607.61;
					ped3B_z = 11.7323;
					SetSped3 = 0;
				}
				else if (ped3_cord == 52)
				{
					ped3B_x = 952.535;
					ped3B_y = 1515.386;
					ped3B_z = 11.9283;
					SetSped3 = 0;
				}
				else if (ped3_cord == 53)
				{
					ped3B_x = 985.878;
					ped3B_y = 1434.804;
					ped3B_z = 8.8502;
					SetSped3 = 0;
				}
				else if (ped3_cord == 54)
				{
					ped3B_x = 992.826;
					ped3B_y = 1353.326;
					ped3B_z = 6.2706;
					SetSped3 = 0;
				}
				else if (ped3_cord == 55)
				{
					ped3B_x = 977.605;
					ped3B_y = 1259.314;
					ped3B_z = 4.9648;
					SetSped3 = 1;
				}
				else if (ped3_cord == 56)
				{
					ped3B_x = 955.221;
					ped3B_y = 1188.581;
					ped3B_z = 4.9354;
					SetSped3 = 0;
				}
				else if (ped3_cord == 57)
				{
					ped3B_x = 852.255;
					ped3B_y = 1213.651;
					ped3B_z = 5.2006;
					SetSped3 = 0;
				}
				else if (ped3_cord == 58)
				{
					ped3B_x = 854.045;
					ped3B_y = 1316.617;
					ped3B_z = 5.2006;
					SetSped3 = 0;
				}
				else if (ped3_cord == 59)
				{
					ped3B_x = 857.627;
					ped3B_y = 1404.362;
					ped3B_z = 5.1785;
					SetSped3 = 0;
				}
				else if (ped3_cord == 60)
				{
					ped3B_x = 837.9289;
					ped3B_y = 1474.2;
					ped3B_z = 6.4493;
					SetSped3 = 1;
				}
				else if (ped3_cord == 61)
				{
					ped3B_x = 736.754;
					ped3B_y = 1483.153;
					ped3B_z = 15.4129;
					SetSped3 = 0;
				}
				else if (ped3_cord == 62)
				{
					ped3B_x = 623.939;
					ped3B_y = 1508.223;
					ped3B_z = 18.2634;
					SetSped3 = 1;
				}
				else if (ped3_cord == 63)
				{
					ped3B_x = 544.339;
					ped3B_y = 1536.54;
					ped3B_z = 4.8228;
					SetSped3 = 2;
				}
				else if (ped3_cord == 64)
				{
					ped3B_x = 529.268;
					ped3B_y = 1441.967;
					ped3B_z = 4.7065;
					SetSped3 = 0;
				}
				else if (ped3_cord == 65)
				{
					ped3B_x = 478.1894;
					ped3B_y = 1398.236;
					ped3B_z = 4.7037;
					SetSped3 = 1;
				}
				else if (ped3_cord == 66)
				{
					ped3B_x = 443.972;
					ped3B_y = 1428.536;
					ped3B_z = 4.7136;
					SetSped3 = 0;
				}
				else if (ped3_cord == 67)
				{
					ped3B_x = 463.9647;
					ped3B_y = 1519.482;
					ped3B_z = 4.7345;
					SetSped3 = 1;
					ped3_cord = 70;
				}
				else if (ped3_cord == 68)
				{
					ped3B_x = 464.2384;
					ped3B_y = 1591.027;
					ped3B_z = 4.8576;
					SetSped3 = 0;
				}
				else if (ped3_cord == 69)
				{
					ped3B_x = 428.572;
					ped3B_y = 1634.68;
					ped3B_z = 10.5335;
					SetSped3 = 1;
				}
				else if (ped3_cord == 70)
				{
					ped3B_x = 352.107;
					ped3B_y = 1594.31;
					ped3B_z = 4.8058;
					SetSped3 = 0;
				}
				else if (ped3_cord == 71)
				{
					ped3B_x = 294.447;
					ped3B_y = 1608.5;
					ped3B_z = 6.180101;
					SetSped3 = 0;
				}
				else if (ped3_cord == 72)
				{
					ped3B_x = 205.807;
					ped3B_y = 1616.56;
					ped3B_z = 14.3942;
					SetSped3 = 0;
				}
				else if (ped3_cord == 73)
				{
					ped3B_x = 118.062;
					ped3B_y = 1617.46;
					ped3B_z = 16.0711;
					SetSped3 = 0;
				}
				else if (ped3_cord == 74)
				{
					ped3B_x = 18.67801;
					ped3B_y = 1618.35;
					ped3B_z = 5.4061;
					SetSped3 = 1;
				}
				else if (ped3_cord == 75)
				{
					ped3B_x = -72.64899;
					ped3B_y = 1632.68;
					ped3B_z = 4.8647;
					SetSped3 = 0;
				}
				else if (ped3_cord == 76)
				{
					ped3B_x = -155.022;
					ped3B_y = 1678.34;
					ped3B_z = 4.872501;
					SetSped3 = 0;
				}
				else if (ped3_cord == 77)
				{
					ped3B_x = -238.29;
					ped3B_y = 1714.16;
					ped3B_z = 4.872501;
					SetSped3 = 0;
				}
				else if (ped3_cord == 78)
				{
					ped3B_x = -339.465;
					ped3B_y = 1709.68;
					ped3B_z = 4.8647;
					SetSped3 = 1;
				}
				else if (ped3_cord == 79)
				{
					ped3B_x = -425.2143;
					ped3B_y = 1688.099;
					ped3B_z = 4.7009;
					SetSped3 = 1;
				}
				else if (ped3_cord == 80)
				{
					ped3B_x = -433.4924;
					ped3B_y = 1597.211;
					ped3B_z = 4.8699;
					SetSped3 = 0;
				}
				else if (ped3_cord == 81)
				{
					ped3B_x = -436.2254;
					ped3B_y = 1501.277;
					ped3B_z = 4.8699;
					SetSped3 = 0;
				}
				else if (ped3_cord == 82)
				{
					ped3B_x = -438.7631;
					ped3B_y = 1395.701;
					ped3B_z = 4.8816;
					SetSped3 = 0;
				}
				else if (ped3_cord == 83)
				{
					ped3B_x = -437.408;
					ped3B_y = 1311.439;
					ped3B_z = 4.8816;
					SetSped3 = 1;
				}
				else if (ped3_cord == 84)
				{
					ped3B_x = -274.465;
					ped3B_y = 1284.54;
					ped3B_z = 4.8816;
					SetSped3 = 1;
				}
				else if (ped3_cord == 85)
				{
					ped3B_x = -240.0354;
					ped3B_y = 1267.206;
					ped3B_z = 4.9913;
					SetSped3 = 2;
				}
				else if (ped3_cord == 86)
				{
					ped3B_x = -244.4168;
					ped3B_y = 1167.997;
					ped3B_z = 4.8813;
					SetSped3 = 0;
				}
				else if (ped3_cord == 87)
				{
					ped3B_x = -253.957;
					ped3B_y = 1072.407;
					ped3B_z = 4.8847;
					SetSped3 = 0;
				}
				else if (ped3_cord == 88)
				{
					ped3B_x = -264.2693;
					ped3B_y = 981.9677;
					ped3B_z = 4.8925;
					SetSped3 = 1;
					ped3_cord = 89;
				}
				else if (ped3_cord == 89)
				{
					ped3B_x = -272.3832;
					ped3B_y = 889.7058;
					ped3B_z = 4.8679;
					SetSped3 = 1;
				}
				else if (ped3_cord == 90)
				{
					ped3B_x = -295.8838;
					ped3B_y = 826.4709;
					ped3B_z = 4.9507;
					SetSped3 = 2;
				}
				else if (ped3_cord == 91)
				{
					ped3B_x = -365.431;
					ped3B_y = 839.391;
					ped3B_z = 5.2203;
					SetSped3 = 0;
				}
				else if (ped3_cord == 92)
				{
					ped3B_x = -458.548;
					ped3B_y = 850.136;
					ped3B_z = 5.2165;
					SetSped3 = 0;
				}
				else if (ped3_cord == 93)
				{
					ped3B_x = -543.1764;
					ped3B_y = 857.2659;
					ped3B_z = 5.1999;
					SetSped3 = 1;
				}
				else if (ped3_cord == 94)
				{
					ped3B_x = -583.0317;
					ped3B_y = 777.374;
					ped3B_z = 5.1766;
					SetSped3 = 0;
				}
				else if (ped3_cord == 95)
				{
					ped3B_x = -621.1567;
					ped3B_y = 684.0111;
					ped3B_z = 5.2094;
					SetSped3 = 0;
				}
				else if (ped3_cord == 96)
				{
					ped3B_x = -636.8751;
					ped3B_y = 581.2972;
					ped3B_z = 5.2116;
					SetSped3 = 0;
				}
				else if (ped3_cord == 97)
				{
					ped3B_x = -634.963;
					ped3B_y = 478.759;
					ped3B_z = 5.2118;
					SetSped3 = 1;
				}
				else if (ped3_cord == 98)
				{
					ped3B_x = -677.264;
					ped3B_y = 464.626;
					ped3B_z = 5.3946;
					SetSped3 = 0;
				}
				else if (ped3_cord == 99)
				{
					ped3B_x = -716.8814;
					ped3B_y = 455.9111;
					ped3B_z = 5.3912;
					SetSped3 = 0;
				}
				else if (ped3_cord == 100)
				{
					ped3B_x = -751.4313;
					ped3B_y = 384.294;
					ped3B_z = 5.3799;
					SetSped3 = 0;
				}
				else if (ped3_cord == 101)
				{
					ped3B_x = -752.5255;
					ped3B_y = 281.0686;
					ped3B_z = 5.3807;
					SetSped3 = 0;
				}
				else if (ped3_cord == 102)
				{
					ped3B_x = -749.1074;
					ped3B_y = 182.7831;
					ped3B_z = 4.7105;
					SetSped3 = 1;
				}
				else if (ped3_cord == 103)
				{
					ped3B_x = -765.843;
					ped3B_y = 83.67506;
					ped3B_z = 4.7421;
					SetSped3 = 1;
				}
				else if (ped3_cord == 104)
				{
					ped3B_x = -721.182;
					ped3B_y = 33.6928;
					ped3B_z = 4.7692;
					SetSped3 = 0;
				}
				else if (ped3_cord == 105)
				{
					ped3B_x = -659.649;
					ped3B_y = 42.2182;
					ped3B_z = 5.1038;
					SetSped3 = 2;
				}
				else if (ped3_cord == 106)
				{
					ped3B_x = -632.6763;
					ped3B_y = -49.21457;
					ped3B_z = 4.9241;
					SetSped3 = 0;
				}
				else if (ped3_cord == 107)
				{
					ped3B_x = -552.5643;
					ped3B_y = -50.53316;
					ped3B_z = 5.2854;
					SetSped3 = 0;
				}
				else if (ped3_cord == 108)
				{
					ped3B_x = -549.1974;
					ped3B_y = -134.2322;
					ped3B_z = 5.5705;
					SetSped3 = 0;
				}
				else if (ped3_cord == 109)
				{
					ped3B_x = -623.8671;
					ped3B_y = -143.9434;
					ped3B_z = 5.5966;
					SetSped3 = 0;
				}
				else if (ped3_cord == 110)
				{
					ped3B_x = -694.3903;
					ped3B_y = -154.4668;
					ped3B_z = 5.5742;
					SetSped3 = 1;
				}
				else if (ped3_cord == 111)
				{
					ped3B_x = -678.81;
					ped3B_y = -256.525;
					ped3B_z = 5.6719;
					SetSped3 = 0;
				}
				else if (ped3_cord == 112)
				{
					ped3B_x = -638.51;
					ped3B_y = -332.631;
					ped3B_z = 6.3928;
					SetSped3 = 0;
				}
				else if (ped3_cord == 113)
				{
					ped3B_x = -562.409;
					ped3B_y = -413.213;
					ped3B_z = 8.658201;
					SetSped3 = 0;
				}
				else if (ped3_cord == 114)
				{
					ped3B_x = ped3B_x; 
					ped3B_y = ped3B_y;
					ped3B_z = ped3B_z;
					SetSped3 = 0;
					skip = 1;
					PRINT_STRING_IN_STRING("string", "OUTTIME", 5000, 1);//~r~Too slow, man, too slow!
					break;
				}
				TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(ped3, car3, ped3B_x, ped3B_y, ped3B_z, 4, 60.0, 2, 5, 10);// пед едит на нужные координаты("p1"-пед,"a2"-машины,хyz,какой-то флаг,скорость движения,какие-то флаги)
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
			if (time_m >= 10)
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
			if ( time_s >= 10 )
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
	SWITCH_ROADS_BACK_TO_ORIGINAL( -465.473, -529.89, -1.286, -759.523, -169.158, 80.0 );//  АКТИВИРУЕМ ТРАФИКА
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
		if (!IS_BIT_SET(G_SA_RACE, 5))
		{
			INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
		}
		MissionFailed();
	}
	else if (skip == 2)
	{
		SETTIMERA(0); //сбрасываем таймер 
		play_mission_complete_tune();
		MissionPassed(40000, "youhavewon", "CASH");
		ADD_SCORE( GetPlayerIndex(), +40000 );//даём игроку денег
		INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 40000);
		if (!IS_BIT_SET(G_SA_RACE, 5))
		{
			SET_BIT(&G_SA_RACE, 5);
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
