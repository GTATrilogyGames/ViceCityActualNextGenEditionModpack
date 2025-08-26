/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
float part;

void trafic_script(void)
{

	WAIT(2000);
	uint CarM1, CarM2, CarM3, CarM4, CarM5;
	part = 1;
	while (TRUE)
	{
		if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -710.9, -1090.852, -47.421, -112.377, -519.577, 337.005, 0 )) // игрок в зоне доков
		{
			if (part == 1)
			{
				//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "dock_part_1", 5000, 4);	
				CarM1 = MODEL_BENSON;
				CarM2 = MODEL_BOBCAT;
				CarM3 = MODEL_BOXVILLE;
				CarM4 = MODEL_PACKER;
				CarM5 = MODEL_E109;
				part = 2;
			}
			else if (part == 2)
			{
				//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "dock_part_2", 5000, 4);	
				CarM1 = MODEL_EMPEROR;
				CarM2 = MODEL_ESPERANTO;
				CarM3 = MODEL_FACTION;
				CarM4 = MODEL_SABRE2;
				CarM5 = MODEL_FLATBED;
				part = 3;
			}
			else if (part == 3)
			{
				//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "dock_part_3", 5000, 4);	
				CarM1 = MODEL_FORTUNE;
				CarM2 = MODEL_STALION;
				CarM3 = MODEL_BOXVILLE;
				CarM4 = MODEL_PACKER;
				CarM5 = MODEL_PHANTOM;
				part = 1;
			}
		}
		else if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -1688.309, -1277.34, -47.421, -805.522, -286.471, 337.005, 0 )) // игрок в зоне јэропорта
		{
			if (part == 1)
			{
				//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "air_part_1", 5000, 4);	
				CarM1 = MODEL_AIRTUG;
				CarM2 = MODEL_BOXVILLE;
				CarM3 = MODEL_BUS;
				CarM4 = MODEL_MULE;
				CarM5 = MODEL_PERENNIAL2;
				part = 2;
			}
			else if (part == 2)
			{
				//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "air_part_2", 5000, 4);	
				CarM1 = MODEL_AIRTUG;
				CarM2 = MODEL_BOXVILLE;
				CarM3 = MODEL_FEROCI2;
				CarM4 = MODEL_MULE;
				CarM5 = MODEL_PERENNIAL2;
				part = 3;
			}
			else if (part == 3)
			{
				//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "air_part_3", 5000, 4);	
				CarM1 = MODEL_AIRTUG;
				CarM2 = MODEL_RIPLEY;
				CarM3 = MODEL_FEROCI2;
				CarM4 = MODEL_MULE;
				CarM5 = MODEL_PERENNIAL2;
				part = 1;
			}
		}
		else
		{
			if (part == 1)
			{
				//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "all_part_1", 5000, 4);	
				CarM1 = MODEL_ADMIRAL;
				CarM2 = MODEL_BANSHEE;
				CarM3 = MODEL_BOBCAT;
				CarM4 = MODEL_COMET;
				CarM5 = MODEL_COQUETTE;
				part = 2;
			}
			else if (part == 2)
			{
				//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "all_part_2", 5000, 4);	
				CarM1 = MODEL_INFERNUS;
				CarM2 = MODEL_RANCHER;
				CarM3 = MODEL_REBLA;
				CarM4 = MODEL_SABRE2;
				CarM5 = MODEL_RUINER;
				part = 3;
			}
			else if (part == 3)
			{
				//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "all_part_3", 5000, 4);	
				CarM1 = MODEL_SENTINEL;
				CarM2 = MODEL_STALION;
				CarM3 = MODEL_SULTANRS;
				CarM4 = MODEL_SUPERGT;
				CarM5 = MODEL_TURISMO;
				part = 1;
			}
		}


		// загрузчик
		REQUEST_MODEL(CarM1);
		while (!HAS_MODEL_LOADED(CarM1)) WAIT(10);
		REQUEST_MODEL(CarM2);
		while (!HAS_MODEL_LOADED(CarM2)) WAIT(10);
		REQUEST_MODEL(CarM3);
		while (!HAS_MODEL_LOADED(CarM3)) WAIT(10);
		REQUEST_MODEL(CarM4);
		while (!HAS_MODEL_LOADED(CarM4)) WAIT(10);
		REQUEST_MODEL(CarM5);
		while (!HAS_MODEL_LOADED(CarM5)) WAIT(10);


		WAIT(500);
		MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);//выгружаем модель машины
		MARK_MODEL_AS_NO_LONGER_NEEDED(CarM2);//выгружаем модель машины
		MARK_MODEL_AS_NO_LONGER_NEEDED(CarM3);//выгружаем модель машины
		MARK_MODEL_AS_NO_LONGER_NEEDED(CarM4);//выгружаем модель машины
		MARK_MODEL_AS_NO_LONGER_NEEDED(CarM5);//выгружаем модель машины
		WAIT(500);
		
	}
}
void main(void)
{
	trafic_script();
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
