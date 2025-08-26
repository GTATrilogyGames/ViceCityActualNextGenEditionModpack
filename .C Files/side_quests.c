/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
int inamb = 0;
int incopcar = 0;
int inftk = 0;
int intaxi = 0;
int inpizza = 0;
int incrazy = 0;
int inbmx = 0;
int inpcj = 0;
int intopfun = 0;


#define CONTROLLER_DPAD_UP	8		/*rebusx*/


void autosave()		/*rebusx*/
{
	DO_AUTO_SAVE();
	WAIT(500);
}


void start_heli_mission(void)
{
	float previous_cash = GET_FLOAT_STAT(STAT_MADE_FROM_MISSIONS);
	REQUEST_SCRIPT("heli");
	while (!HAS_SCRIPT_LOADED("heli")) WAIT(0);
	G_ONMISSION = 1;
	uint script = START_NEW_SCRIPT("heli", 1024);
	MARK_SCRIPT_AS_NO_LONGER_NEEDED("heli");
	while (IS_THREAD_ACTIVE(script)) WAIT(0);
	G_ONMISSION = 0;
	WAIT(1000);
	if (previous_cash != GET_FLOAT_STAT(STAT_MADE_FROM_MISSIONS))
	{
		autosave();		/*rebusx*/
	}
}
void main(void)
{
	WAIT(0);
	while (TRUE) 
	{
		WAIT(0);
		if (G_ONMISSION == 0)
		{
			//------------------- Побочка -------------------
			int prev_passed_flag;		/*rebusx*/
			float previous_cash;
			
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("ambulance")))
			{
				if (inamb == 0)
				{
					PRINT_HELP("ATUTOR");
					inamb = 1;
				}
				if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER())))
				{
					prev_passed_flag = G_MEDIC;		/*rebusx*/
					REQUEST_SCRIPT("ambulance");
					while (!HAS_SCRIPT_LOADED("ambulance")) WAIT(0);
					G_ONMISSION = 1;
					uint script = START_NEW_SCRIPT("ambulance", 1024);
					MARK_SCRIPT_AS_NO_LONGER_NEEDED("ambulance");
					while (IS_THREAD_ACTIVE(script)) WAIT(0);
					G_ONMISSION = 0;
					WAIT(1000);
					if ((prev_passed_flag == 0) && (G_MEDIC > prev_passed_flag))
					{
						autosave();		/*rebusx*/
					}
				}
			}
			else
			{
				if (inamb == 1)
				{
					inamb = 0;
				}
			}

			if ((IS_CHAR_IN_ANY_POLICE_VEHICLE(GetPlayerPed())) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("annihilator"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("fbi"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("buzzard"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("apc"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("biff"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("patriot"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("polmav"))))
			{
				if (incopcar == 0)
				{
					PRINT_HELP("CTUTOR");
					incopcar = 1;
				}
				if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER())))
				{
					prev_passed_flag = G_COPCAR;		/*rebusx*/
					REQUEST_SCRIPT("vigilante");
					while (!HAS_SCRIPT_LOADED("vigilante")) WAIT(0);
					G_ONMISSION = 1;
					uint script = START_NEW_SCRIPT("vigilante", 1024);
					MARK_SCRIPT_AS_NO_LONGER_NEEDED("vigilante");
					while (IS_THREAD_ACTIVE(script)) WAIT(0);
					G_ONMISSION = 0;
					WAIT(1000);
					if ((prev_passed_flag == 0) && (G_COPCAR > prev_passed_flag))
					{
						autosave();		/*rebusx*/
					}
				}
			}
			else
			{
				if (incopcar == 1)
				{
					incopcar = 0;
				}
			}

			if (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("firetruk")))
			{
				if (inftk == 0)
				{
					PRINT_HELP("FTUTOR");
					inftk = 1;
				}
				if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER())))
				{
					prev_passed_flag = G_FIRE;		/*rebusx*/
					REQUEST_SCRIPT("firetruck");
					while (!HAS_SCRIPT_LOADED("firetruck")) WAIT(0);
					G_ONMISSION = 1;
					uint script = START_NEW_SCRIPT("firetruck", 1024);
					MARK_SCRIPT_AS_NO_LONGER_NEEDED("firetruck");
					while (IS_THREAD_ACTIVE(script)) WAIT(0);
					G_ONMISSION = 0;
					WAIT(1000);
					if ((prev_passed_flag == 0) && (G_FIRE > prev_passed_flag))
					{
						autosave();		/*rebusx*/
					}
				}
			}
			else
			{
				if (inftk == 1)
				{
					inftk = 0;
				}
			}

			if ((IS_CHAR_IN_TAXI(GetPlayerPed())) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_ROM)))
			{
				Vehicle car;
				GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car);
				Ped driver;
				GET_DRIVER_OF_CAR(car, &driver);
				if (GetPlayerPed() == driver)	/*rebusx: для совместимости с "Taxi Reborn", чтобы нельзя было запустить миссию сидя на пассажирском месте*/
				{
					if (intaxi == 0)
					{
						PRINT_HELP("TTUTOR");
						intaxi = 1;
					}
					if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER())))
					{
						prev_passed_flag = G_TAXI;		/*rebusx*/
						REQUEST_SCRIPT("taxi");
						while (!HAS_SCRIPT_LOADED("taxi")) WAIT(0);
						G_ONMISSION = 1;
						uint script = START_NEW_SCRIPT("taxi", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("taxi");
						while (IS_THREAD_ACTIVE(script)) WAIT(0);
						G_ONMISSION = 0;
						WAIT(1000);
						if ((prev_passed_flag == 0) && (G_TAXI > prev_passed_flag))
						{
							autosave();		/*rebusx*/
						}
					}
				}
			}
			else
			{
				if (intaxi == 1)
				{
					intaxi = 0;
				}
			}

			/*if ((G_PIZZA == 0) && (G_ONMISSION == 0) && (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("hellfury"))))*/	/*rebusx: возможность делать бонус-миссию повторно*/
			if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("hellfury"))) && (G_ONMISSION == 0) )
			{
				if ((IS_CHAR_IN_AREA_3D(GetPlayerPed(), -461.1, 1331.7, -4.0, -481.1, 1351.7, 16.0, 0)) || (IS_CHAR_IN_AREA_3D(GetPlayerPed(), -585.7, 611.6, -4.2, -605.7, 631.6, 16.2, 0)) || (IS_CHAR_IN_AREA_3D(GetPlayerPed(), 836.8, 620.7, -4.9, 856.8, 640.7, 15.9, 0)))
				{
					if (inpizza == 0)
					{
						prev_passed_flag = G_PIZZA;		/*rebusx*/
						REQUEST_SCRIPT("pizza");
						while (!HAS_SCRIPT_LOADED("pizza")) WAIT(0);
						G_ONMISSION = 1;
						inpizza = 1;
						uint script = START_NEW_SCRIPT("pizza", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("pizza");
						while (IS_THREAD_ACTIVE(script)) WAIT(0);
						G_ONMISSION = 0;
						WAIT(1000);
						if ((prev_passed_flag == 0) && (G_PIZZA > prev_passed_flag))
						{
							autosave();		/*rebusx*/
						}
					}
				}
			}
			else
			{
				if (inpizza == 1)
				{
					inpizza = 0;
				}
			}

			if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("stalion"))) && (IS_CHAR_IN_AREA_3D(GetPlayerPed(), 555.0, -610.0, 22.0, 567.0, -635.0, 28.0, 0)) && (G_ONMISSION == 0))
			{
				if (incrazy == 0)
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEHELP2"); //Press the ~PAD_LB~ button to activate the mission
					incrazy = 1;
				}
				if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER())))
				{
					prev_passed_flag = G_CARPRK;		/*rebusx*/
					REQUEST_SCRIPT("conecrazy");
					while (!HAS_SCRIPT_LOADED("conecrazy")) WAIT(0);
					G_ONMISSION = 1;
					uint script = START_NEW_SCRIPT("conecrazy", 1024);
					MARK_SCRIPT_AS_NO_LONGER_NEEDED("conecrazy");
					while (IS_THREAD_ACTIVE(script)) WAIT(0);
					G_ONMISSION = 0;
					WAIT(1000);
					if ((prev_passed_flag == 0) && (G_CARPRK > prev_passed_flag))
					{
						autosave();		/*rebusx*/
					}
				}
			}
			else
			{
				if (incrazy == 1)
				{
					incrazy = 0;
				}
			}

			if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sparrow"))) && (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), -136.1451, 1384.0923, 17.8402, 2.0, 2.0, 2.0, 0)) && (G_ONMISSION == 0))
			{
				start_heli_mission();
			}
			else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sparrow"))) && (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), 461.4463, -778.7614, 11.4712, 2.0, 2.0, 2.0, 0)) && (G_ONMISSION == 0))
			{
				start_heli_mission();
			}
			else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sparrow"))) && (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), 808.8450, 865.9194, 6.5155, 2.0, 2.0, 2.0, 0)) && (G_ONMISSION == 0))
			{
				start_heli_mission();
			}
			else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sparrow"))) && (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), -453.5938, 769.5693, 8.9773, 2.0, 2.0, 2.0, 0)) && (G_ONMISSION == 0))
			{
				start_heli_mission();
			}
			if ((prev_passed_flag <= 3) && (G_HELI1SC > prev_passed_flag))
			{
				autosave();		/*rebusx*/
			}

			if (IS_CHAR_IN_AREA_3D(GetPlayerPed(), 3.0, 1938.0, 3.5, 13.0, 1948.0, 7.5, 0) && (G_ONMISSION == 0))
			{
				if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sanchez"))) || (IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("landstalker"))))
				{
					if (inbmx == 0)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP("NEHELP2"); //Press the ~PAD_LB~ button to activate the mission
						inbmx = 1;
					}
					if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER())))
					{
						previous_cash = GET_FLOAT_STAT(STAT_MADE_FROM_MISSIONS);
						REQUEST_SCRIPT("bmx");
						while (!HAS_SCRIPT_LOADED("bmx")) WAIT(0);
						G_ONMISSION = 1;
						uint script = START_NEW_SCRIPT("bmx", 1024);
						MARK_SCRIPT_AS_NO_LONGER_NEEDED("bmx");
						while (IS_THREAD_ACTIVE(script)) WAIT(0);
						G_ONMISSION = 0;
						WAIT(1000);
						if (previous_cash != GET_FLOAT_STAT(STAT_MADE_FROM_MISSIONS))
						{
							autosave();		/*rebusx*/
						}
					}
				}
				else
				{
					if (inbmx == 1)
					{
						inbmx = 0;
					}
				}
			}
			else
			{
				if (inbmx == 1)
				{
					inbmx = 0;
				}
			}

			if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("pcj"))) && (IS_CHAR_IN_AREA_3D(GetPlayerPed(), 937.4, 222.8, 7.0, 943.4, 228.8, 9.0, 0)) && (G_ONMISSION == 0))
			{
				if (inpcj == 0)
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEHELP2"); //Press the ~PAD_LB~ button to activate the mission
					inpcj = 1;
				}
				if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER())))
				{
					prev_passed_flag = G_PCJ;		/*rebusx*/
					REQUEST_SCRIPT("pcj");
					while (!HAS_SCRIPT_LOADED("pcj")) WAIT(0);
					G_ONMISSION = 1;
					uint script = START_NEW_SCRIPT("pcj", 1024);
					MARK_SCRIPT_AS_NO_LONGER_NEEDED("pcj");
					while (IS_THREAD_ACTIVE(script)) WAIT(0);
					G_ONMISSION = 0;
					WAIT(1000);
					if ((prev_passed_flag == 0) && (G_PCJ > prev_passed_flag))
					{
						autosave();		/*rebusx*/
					}
				}
			}
			else
			{
				if (inpcj == 1)
				{
					inpcj = 0;
				}
			}

			if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SPEEDO)) && (IS_CHAR_IN_AREA_3D(GetPlayerPed(), 1165.666, 1220.26, 7.0, 1159.666, 1230.26, 12.0, 0)) && (G_ONMISSION == 0))
			{
				if (intopfun == 0)
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEHELP2"); //Press the ~PAD_LB~ button to activate the mission
					intopfun = 1;
				}
				if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER())))
				{
					previous_cash = GET_FLOAT_STAT(STAT_MADE_FROM_MISSIONS);
					REQUEST_SCRIPT("rcrace");
					while (!HAS_SCRIPT_LOADED("rcrace")) WAIT(0);
					G_ONMISSION = 1;
					uint script = START_NEW_SCRIPT("rcrace", 1024);
					MARK_SCRIPT_AS_NO_LONGER_NEEDED("rcrace");
					while (IS_THREAD_ACTIVE(script)) WAIT(0);
					G_ONMISSION = 0;
					WAIT(1000);
					if (previous_cash != GET_FLOAT_STAT(STAT_MADE_FROM_MISSIONS))
					{
						autosave();		/*rebusx*/
					}
				}
			}
			else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SPEEDO)) && (IS_CHAR_IN_AREA_3D(GetPlayerPed(), -797.529, -697.733, 8.282, -803.539, -705.255, 12.979, 0)) && (G_ONMISSION == 0))
			{
				if (intopfun == 0)
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEHELP2"); //Press the ~PAD_LB~ button to activate the mission
					intopfun = 1;
				}
				if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER())))
				{
					previous_cash = GET_FLOAT_STAT(STAT_MADE_FROM_MISSIONS);
					REQUEST_SCRIPT("rcheli");
					while (!HAS_SCRIPT_LOADED("rcheli")) WAIT(0);
					G_ONMISSION = 1;
					uint script = START_NEW_SCRIPT("rcheli", 1024);
					MARK_SCRIPT_AS_NO_LONGER_NEEDED("rcheli");
					while (IS_THREAD_ACTIVE(script)) WAIT(0);
					G_ONMISSION = 0;
					WAIT(1000);
					if (previous_cash != GET_FLOAT_STAT(STAT_MADE_FROM_MISSIONS))
					{
						autosave();		/*rebusx*/
					}
				}
			}
			else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SPEEDO)) && (IS_CHAR_IN_AREA_3D(GetPlayerPed(), 744.676, 1780.595, 21.0, 737.676, 1790.595, 27.0, 0)) && (G_ONMISSION == 0))
			{
				if (intopfun == 0)
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NEHELP2"); //Press the ~PAD_LB~ button to activate the mission
					intopfun = 1;
				}
				if (((IS_CONTROL_PRESSED(2, 23)) && (!IS_USING_CONTROLLER())) || ((IS_BUTTON_PRESSED(0, CONTROLLER_DPAD_UP)) && (IS_USING_CONTROLLER())))
				{
					previous_cash = GET_FLOAT_STAT(STAT_MADE_FROM_MISSIONS);
					REQUEST_SCRIPT("rcplne");
					while (!HAS_SCRIPT_LOADED("rcplne")) WAIT(0);
					G_ONMISSION = 1;
					uint script = START_NEW_SCRIPT("rcplne", 1024);
					MARK_SCRIPT_AS_NO_LONGER_NEEDED("rcplne");
					while (IS_THREAD_ACTIVE(script)) WAIT(0);
					G_ONMISSION = 0;
					WAIT(1000);
					if (previous_cash != GET_FLOAT_STAT(STAT_MADE_FROM_MISSIONS))
					{
						autosave();		/*rebusx*/
					}
				}
			}
			else
			{
				if (intopfun == 1)
				{
					intopfun = 0;
				}
			}
		}
	}
}
