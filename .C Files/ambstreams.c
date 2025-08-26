#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"

#define ZOMB_MAX 20
#define ZOMB_CREATE_MIN_DIST 35.0
float x, y, z, xdif, ydif;
float Tx, Ty, Tz;
float ZOMBIE_DEL;
float ZOMBIE_ON_OFF;
float in_int, in_int2, in_int3, in_int4;
int intHash, if_intMall;
float zgrnd, wh, xpl, ypl, zpl, dist;
float flowerbed1,flowerbed2,flowerbed3,flowerbed4;
Ped zombies[ZOMB_MAX];
uint ZOMB_MODEL, pHealth, del_ped, wait_fix, rancord;


void zombiecord(void)
{
	float x, y, z, xdif, ydif;
	//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "zapros", 1000, 1);
	while (TRUE) //  find coords for zombie creation
	{ 
		WAIT(0);
		GET_INTERIOR_FROM_CHAR(GetPlayerPed(), &intHash);
		if ( intHash != 258 ) // интрерьер Молл
		{
			break;
		}
		float zgrnd, wh, xpl, ypl, zpl, dist;
		GET_CHAR_COORDINATES(GetPlayerPed(), &xpl, &ypl, &zpl);
		if (zpl < 17.5)
		{
			GENERATE_RANDOM_FLOAT_IN_RANGE(-30.0, 30.0, &xdif);
			GENERATE_RANDOM_FLOAT_IN_RANGE(-30.0, 30.0, &ydif);
		}
		else
		{
			GENERATE_RANDOM_FLOAT_IN_RANGE(-40.0, 40.0, &xdif);
			GENERATE_RANDOM_FLOAT_IN_RANGE(-40.0, 40.0, &ydif);
		}

		GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(GetPlayerPed(), xdif, ydif, 0.0, &x, &y, &z);

		GET_DISTANCE_BETWEEN_COORDS_3D(x, y, z, xpl, ypl, zpl, &dist);
		if (dist < ZOMB_CREATE_MIN_DIST) continue;

		GET_GROUND_Z_FOR_3D_COORD(x, y, z, &zgrnd);

		if ( (zgrnd < z + 1.0) || (zgrnd > z - 1.0) ) 
		{
			z = zgrnd;
			// здесь координаты всех баз выжевших
			GET_DISTANCE_BETWEEN_COORDS_2D(x, y, 863.364, 1702.03, &flowerbed1);
			GET_DISTANCE_BETWEEN_COORDS_2D(x, y, 831.266, 1703.03, &flowerbed2);
			GET_DISTANCE_BETWEEN_COORDS_2D(x, y, 863.689, 1613.58, &flowerbed3);
			GET_DISTANCE_BETWEEN_COORDS_2D(x, y, 830.747, 1613.27, &flowerbed4);
			
			int pedint;
			GET_INTERIOR_AT_COORDS(x, y, z+1, &pedint);
			//DISPLAY_TEXT_WITH_NUMBER(0.9083334, 0.72787074, "CP_TIME_NOZERO", pedint);// 

			if ((flowerbed1 > 10) && (flowerbed2 > 10)  && (flowerbed3 > 10)  && (flowerbed4 > 10))
			{
				Ped ped;
				GET_RANDOM_CHAR_IN_AREA_OFFSET_NO_SAVE(x - 5, y - 5, z - 5, x + 5, y + 5, z + 5, &ped);
				if (pedint == 258)
				{
					if (ped <= 0)
					{
						if (zpl < 17.5)
						{
							Tx = x;
							Ty = y;
							Tz = z+0.2;
							break; // coords are good, lets go next	
						}
						else if ((zpl > 17.5) && (zgrnd > 17.5))
						{
							Tx = x;
							Ty = y;
							Tz = z+0.2;
							break; // coords are good, lets go next	
						}
						GENERATE_RANDOM_INT_IN_RANGE(0, 20, &rancord);
						if (((rancord > 8) && (rancord < 11)) || (rancord == 5) || (rancord == 18))
						{
							Tx = x;
							Ty = y;
							Tz = z+0.2;
							break; // coords are good, lets go next	
						}
					}
				}
			}
		}
	}
}
void CheckModelLoad(uint model)
{
	if ( !HAS_MODEL_LOADED(model) )
	{
		REQUEST_MODEL(model);
		while (!HAS_MODEL_LOADED(model)) WAIT(0);
	}
}


void main(void)
{
	uint PedM1, PedM2, PedM3, PedM4, PedM5, PedM6, PedM7, PedM8, PedM9, PedM10, PedM11, PedM12, PedM13, PedM14, PedM15;
	Ped ped1, ped2, ped3, ped4, ped5, ped6, ped7, ped8, ped9, ped10, ped11, ped12, ped13, ped14, ped15;
	Ped ped16, ped17, ped18, ped19, ped20, ped21, ped22, ped23, ped24, ped25, ped26, ped27, ped28, ped29, ped30;
	in_int = 0;
	in_int2 = 0;
	in_int3 = 0;
	in_int4 = 0;
	if_intMall = 0;
	SETTIMERA( 0 );
	ZOMBIE_DEL = 0;
	ZOMBIE_ON_OFF = 1;
		while (true) {
		WAIT(0);
		//------------------- педы в интерьерах -------------------
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 565.987, -962.529, 3.104, 490.988, -906.258, 11.197, 0 )) && (in_int == 0))// интрерьер Стрип клуба
		{
			PedM1 = MODEL_F_M_PLATIN_01;// strip 1
			PedM2 = MODEL_F_Y_HOOKER_03;// strip 2
			PedM3 = MODEL_F_Y_CDRESS_01;// strip 3
			PedM4 = MODEL_F_Y_HOOKER_01;// strip 4
			PedM5 = MODEL_F_Y_PEASTEURO_01;// bar 1
			PedM6 = MODEL_F_M_PJERSEY_02;//	  bar 2
			PedM7 = MODEL_M_M_PEASTEURO_01;// security 1
			PedM8 = MODEL_M_M_BUSINESS_02;//  security 2
			PedM9 = MODEL_M_Y_GALB_LO_01;//    guest 1
			PedM10 = MODEL_M_Y_GALB_LO_02;//   guest 2
			PedM11 = MODEL_M_Y_GENSTREET_34;// guest 3
			PedM12 = MODEL_M_O_HASID_01;//     guest 4
			PedM13 = MODEL_M_Y_GAFR_HI_01;//   guest 5
			PedM14 = MODEL_M_Y_GAFR_HI_02;//   guest 6
			PedM15 = MODEL_M_Y_GAFR_LO_02;//   guest 7

			REQUEST_MODEL(PedM1);// 
			REQUEST_MODEL(PedM2);// 
			REQUEST_MODEL(PedM3);// 
			REQUEST_MODEL(PedM4);// 
			REQUEST_MODEL(PedM5);// 
			REQUEST_MODEL(PedM6);// 
			REQUEST_MODEL(PedM7);// 
			REQUEST_MODEL(PedM8);// 
			REQUEST_MODEL(PedM9);// 
			REQUEST_MODEL(PedM10);// 
			REQUEST_MODEL(PedM11);// 
			REQUEST_MODEL(PedM12);// 
			REQUEST_MODEL(PedM13);// 
			REQUEST_MODEL(PedM14);// 
			REQUEST_MODEL(PedM15);// 

			while ((!HAS_MODEL_LOADED(PedM1)) || (!HAS_MODEL_LOADED(PedM2)) || (!HAS_MODEL_LOADED(PedM3)) || (!HAS_MODEL_LOADED(PedM4)) || (!HAS_MODEL_LOADED(PedM5)))
			{
				WAIT(0);
			}
			while ((!HAS_MODEL_LOADED(PedM6))|| (!HAS_MODEL_LOADED(PedM7)) || (!HAS_MODEL_LOADED(PedM8)) || (!HAS_MODEL_LOADED(PedM9))|| (!HAS_MODEL_LOADED(PedM10)))
			{
				WAIT(0);
			}
			while ((!HAS_MODEL_LOADED(PedM11)) || (!HAS_MODEL_LOADED(PedM12)) || (!HAS_MODEL_LOADED(PedM13)) || (!HAS_MODEL_LOADED(PedM14)) || (!HAS_MODEL_LOADED(PedM15)))
			{
				WAIT(0);
			}

			REQUEST_ANIMS( "missstripclub" );//загружаем файл с анимацией
			while (!HAVE_ANIMS_LOADED( "missstripclub" )) WAIT(0);
			REQUEST_ANIMS( "amb@strip_rail_idl" );//загружаем файл с анимацией
			while (!HAVE_ANIMS_LOADED( "amb@strip_rail_idl" )) WAIT(0);

			CREATE_CHAR (26, PedM1, 527.002, -870.002, 4.64608, &ped1, TRUE);// stripa 1
			CREATE_CHAR (26, PedM2, 530.002, -870.002, 4.64608, &ped2, TRUE);// stripa 2
			CREATE_CHAR (26, PedM3, 533.002, -870.002, 4.64608, &ped3, TRUE);// stripa 3
			CREATE_CHAR (26, PedM4, 536.002, -870.002, 4.64608, &ped4, TRUE);// stripa 4
			CREATE_CHAR (26, PedM5, 539.002, -870.002, 4.64608, &ped5, TRUE);// bar 1
			CREATE_CHAR (26, PedM6, 527.002, -872.002, 4.64608, &ped6, TRUE);// bar 2
			CREATE_CHAR (26, PedM7, 530.002, -872.002, 4.64608, &ped7, TRUE);// security 1
			CREATE_CHAR (26, PedM8, 533.002, -872.002, 4.64608, &ped8, TRUE);// security 2
			CREATE_CHAR (26, PedM9, 536.002, -872.002, 4.64608, &ped9, TRUE);//   guest 1
			CREATE_CHAR (26, PedM10, 539.002, -872.002, 4.64608, &ped10, TRUE);// guest 2
			CREATE_CHAR (26, PedM11, 527.002, -874.002, 4.64608, &ped11, TRUE);// guest 3
			CREATE_CHAR (26, PedM12, 530.002, -874.002, 4.64608, &ped12, TRUE);// guest 4
			CREATE_CHAR (26, PedM13, 533.002, -874.002, 4.64608, &ped13, TRUE);// guest 5
			CREATE_CHAR (26, PedM14, 536.002, -874.002, 4.64608, &ped14, TRUE);// guest 6
			CREATE_CHAR (26, PedM15, 539.002, -874.002, 4.64608, &ped15, TRUE);// guest 7

			UpdateWeaponOfPed(ped2, WEAPON_KNIFE);
			UpdateWeaponOfPed(ped6, WEAPON_EPISODIC_3);
			UpdateWeaponOfPed(ped7, WEAPON_BASEBALLBAT);
			UpdateWeaponOfPed(ped8, WEAPON_BASEBALLBAT);
			SET_CURRENT_CHAR_WEAPON(ped7, WEAPON_BASEBALLBAT, TRUE);

			SET_CHAR_RELATIONSHIP_GROUP(ped1, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped2, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped3, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped4, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped5, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped6, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped7, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped8, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped9, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped10, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped11, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped12, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped13, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped14, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped15, 10);
			SET_SENSE_RANGE(ped2, 50.0);
			SET_SENSE_RANGE(ped6, 50.0);
			SET_SENSE_RANGE(ped7, 50.0);
			SET_SENSE_RANGE(ped8, 50.0);

			FREEZE_CHAR_POSITION(ped9, 1);
			FREEZE_CHAR_POSITION(ped10, 1);
			FREEZE_CHAR_POSITION(ped11, 1);

			SET_CHAR_COORDINATES(ped1, 511.001, -933.147, 5.9515);
			SET_CHAR_COORDINATES(ped2, 512.047, -927.962, 6.0054);
			SET_CHAR_COORDINATES(ped3, 519.065, -930.284, 5.9515);
			SET_CHAR_COORDINATES(ped4, 514.279, -924.151, 6.0209);
			SET_CHAR_COORDINATES(ped5, 524.702, -923.151, 4.76645);
			SET_CHAR_COORDINATES(ped6, 521.085, -916.613, 4.76645);
			SET_CHAR_COORDINATES(ped7, 521.951, -928.173, 4.76645);
			SET_CHAR_COORDINATES(ped8, 523.132, -923.934, 4.76645);
			SET_CHAR_COORDINATES(ped9, 511.568, -933.934, 4.76645);
			SET_CHAR_COORDINATES(ped10, 510.487, -933.564, 4.76645);
			SET_CHAR_COORDINATES(ped11, 519.893, -931.011, 4.76645);
			SET_CHAR_COORDINATES(ped12, 513.101, -929.801, 4.76645);
			SET_CHAR_COORDINATES(ped13, 514.822, -926.866, 4.76645);
			SET_CHAR_COORDINATES(ped14, 516.455, -925.912, 4.76645);
			SET_CHAR_COORDINATES(ped15, 515.215, -922.371, 4.76645);

			SET_CHAR_HEADING(ped1, 35.0);
			SET_CHAR_HEADING(ped2, 35.0);
			SET_CHAR_HEADING(ped3, 35.0);
			SET_CHAR_HEADING(ped4, 35.0);
			SET_CHAR_HEADING(ped5, 110.0);
			SET_CHAR_HEADING(ped6, -40.0);
			SET_CHAR_HEADING(ped7, 30.0);
			SET_CHAR_HEADING(ped8, -65.0);
			SET_CHAR_HEADING(ped9, 30.0);
			SET_CHAR_HEADING(ped10, -60.0);
			SET_CHAR_HEADING(ped11, 30.0);
			SET_CHAR_HEADING(ped12, 30.0);
			SET_CHAR_HEADING(ped13, 5.0);
			SET_CHAR_HEADING(ped14, 55.0);
			SET_CHAR_HEADING(ped15, 150.0);

			SET_ROOM_FOR_CHAR_BY_NAME(ped1, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped2, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped3, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped4, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped5, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped6, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped7, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped8, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped9, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped10, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped11, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped12, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped13, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped14, "strip_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped15, "strip_mloroom");

			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "sitting_proposition", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped2, "dance_wisper_2", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped3, "sitting_proposition", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped4, "pole_dance_a", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "wipe_counter", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "clean_glass", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped9, "watch_lap_dance_loop", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped10, "watch_lap_dance_loop", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped11, "watch_lap_dance_loop", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped12, "lean_rail_a", "amb@strip_rail_idl", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped13, "lean_rail_d", "amb@strip_rail_idl", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped14, "lean_rail_e", "amb@strip_rail_idl", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped15, "niko_dance", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			in_int = 1;
		}
		else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 565.987, -962.529, 3.104, 490.988, -906.258, 11.197, 0 )) && (in_int == 1))// интрерьер Стрип клуба
		{
			// выгружвем модели
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM6);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM7);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM8);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM9);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM10);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM11);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM12);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM13);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM14);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM15);//выгружаем модель
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
			CLEAR_AREA(515.231, -914.803, 4.32348, 25.0, 1);//очещаем зону загрузки
			in_int = 0;
		}
		if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), 936.653, 431.187, 3.387, 886.653, 486.187, 18.387, 0 )) && (in_int2 == 0))// интрерьер клуб Малибу
		{
			PedM1 = MODEL_M_M_BUSINESS_02;// security
			if (G_CLUB >= 1)
			{
				PedM2 = MODEL_F_Y_STRIPPERC01;// bar 1
			}
			else
			{
				PedM2 = MODEL_F_M_PJERSEY_02;//	  bar 2
			}
			PedM3 = MODEL_M_M_FIRECHIEF;//  scene 1
			PedM4 = MODEL_M_M_TRUCKER_01;// scene 2
			PedM5 = MODEL_M_Y_GALB_LO_01;// scene 3
			PedM6 = MODEL_M_Y_GBIK_HI_01;// scene 4
			PedM7 = MODEL_M_Y_COP;//        scene 5
			PedM8 = MODEL_F_Y_HOOKER_03;//  guest 1 (шкура)
			PedM9 = MODEL_M_Y_GAFR_HI_01;//  guest 2 (чёрный в панаме)
			PedM10 = MODEL_F_M_PJERSEY_02;// guest 3 (шкура в тигре)
			PedM11 = MODEL_F_Y_PHARBRON_01;//  guest 4 (шкура бизнесс)
			PedM12 = MODEL_M_Y_GLAT_HI_01;//  guest 5 (кубинец)
			PedM13 = MODEL_M_M_PITALIAN_02;//  guest 6 (розовый костюм)

			REQUEST_MODEL(PedM1);// 
			REQUEST_MODEL(PedM2);// 
			REQUEST_MODEL(PedM3);// 
			REQUEST_MODEL(PedM4);// 
			REQUEST_MODEL(PedM5);// 
			REQUEST_MODEL(PedM6);// 
			REQUEST_MODEL(PedM7);// 
			REQUEST_MODEL(PedM8);// 
			REQUEST_MODEL(PedM9);// 
			REQUEST_MODEL(PedM10);// 
			REQUEST_MODEL(PedM11);// 
			REQUEST_MODEL(PedM12);// 
			REQUEST_MODEL(PedM13);// 
			while ((!HAS_MODEL_LOADED(PedM1)) || (!HAS_MODEL_LOADED(PedM2)) || (!HAS_MODEL_LOADED(PedM3)) || (!HAS_MODEL_LOADED(PedM4)) || (!HAS_MODEL_LOADED(PedM5)))
			{
				WAIT(0);
			}
			while ((!HAS_MODEL_LOADED(PedM6))|| (!HAS_MODEL_LOADED(PedM7)) || (!HAS_MODEL_LOADED(PedM8)) || (!HAS_MODEL_LOADED(PedM9))|| (!HAS_MODEL_LOADED(PedM10)))
			{
				WAIT(0);
			}
			while ((!HAS_MODEL_LOADED(PedM11)) || (!HAS_MODEL_LOADED(PedM12)) || (!HAS_MODEL_LOADED(PedM13)))
			{
				WAIT(0);
			}

			REQUEST_ANIMS( "vcne_dance" );//загружаем файл с анимацией
			while (!HAVE_ANIMS_LOADED( "vcne_dance" )) WAIT(0);
			REQUEST_ANIMS( "missstripclub" );//загружаем файл с анимацией
			while (!HAVE_ANIMS_LOADED( "missstripclub" )) WAIT(0);

			CREATE_CHAR (26, PedM1, 527.002, -870.002, 4.64608, &ped1, TRUE);// security 1
			CREATE_CHAR (26, PedM1, 530.002, -870.002, 4.64608, &ped2, TRUE);// security 2
			CREATE_CHAR (26, PedM1, 533.002, -870.002, 4.64608, &ped3, TRUE);// security 3
			CREATE_CHAR (26, PedM2, 536.002, -870.002, 4.64608, &ped4, TRUE);// bar 1 (stripa)
			CREATE_CHAR (26, PedM3, 539.002, -870.002, 4.64608, &ped5, TRUE);// scene 1
			CREATE_CHAR (26, PedM4, 527.002, -872.002, 4.64608, &ped6, TRUE);// scene 2
			CREATE_CHAR (26, PedM5, 530.002, -872.002, 4.64608, &ped7, TRUE);// scene 3
			CREATE_CHAR (26, PedM6, 533.002, -872.002, 4.64608, &ped8, TRUE);// scene 4
			CREATE_CHAR (26, PedM7, 536.002, -872.002, 4.64608, &ped9, TRUE);// scene 5
			CREATE_CHAR (26, PedM13, 539.002, -872.002, 4.64608, &ped10, TRUE);// guest 1
			CREATE_CHAR (26, PedM12, 527.002, -874.002, 4.64608, &ped11, TRUE);// guest 2
			CREATE_CHAR (26, PedM11, 530.002, -874.002, 4.64608, &ped12, TRUE);// guest 3
			CREATE_CHAR (26, PedM8, 533.002, -874.002, 4.64608, &ped13, TRUE);// guest 4
			CREATE_CHAR (26, PedM10, 536.002, -874.002, 4.64608, &ped14, TRUE);// guest 5
			CREATE_CHAR (26, PedM9, 539.002, -874.002, 4.64608, &ped15, TRUE);// guest 6
			CREATE_CHAR (26, PedM13, 527.002, -876.002, 4.64608, &ped16, TRUE);// guest 7
			CREATE_CHAR (26, PedM8, 530.002, -876.002, 4.64608, &ped17, TRUE);// guest 8
			CREATE_CHAR (26, PedM13, 533.002, -876.002, 4.64608, &ped18, TRUE);// guest 9
			CREATE_CHAR (26, PedM9, 536.002, -876.002, 4.64608, &ped19, TRUE);// guest 10
			CREATE_CHAR (26, PedM12, 539.002, -876.002, 4.64608, &ped20, TRUE);// guest 11
			CREATE_CHAR (26, PedM11, 527.002, -878.002, 4.64608, &ped21, TRUE);// guest 12
			CREATE_CHAR (26, PedM9, 530.002, -878.002, 4.64608, &ped22, TRUE);// guest 13
			CREATE_CHAR (26, PedM10, 533.002, -878.002, 4.64608, &ped23, TRUE);// guest 14
			CREATE_CHAR (26, PedM8, 536.002, -878.002, 4.64608, &ped24, TRUE);//  guest 15
			CREATE_CHAR (26, PedM10, 539.002, -878.002, 4.64608, &ped25, TRUE);// guest 16
			CREATE_CHAR (26, PedM10, 527.002, -880.002, 4.64608, &ped26, TRUE);// guest 17
			CREATE_CHAR (26, PedM12, 530.002, -880.002, 4.64608, &ped27, TRUE);// guest 18
			CREATE_CHAR (26, PedM10, 533.002, -880.002, 4.64608, &ped28, TRUE);// guest 19
			CREATE_CHAR (26, PedM9, 536.002, -880.002, 4.64608, &ped29, TRUE);// guest 20
			CREATE_CHAR (26, PedM8, 539.002, -880.002, 4.64608, &ped30, TRUE);// guest 21

			UpdateWeaponOfPed(ped1, WEAPON_BASEBALLBAT);
			UpdateWeaponOfPed(ped2, WEAPON_BASEBALLBAT);
			UpdateWeaponOfPed(ped3, WEAPON_BASEBALLBAT);
			UpdateWeaponOfPed(ped4, WEAPON_SHOTGUN);

			SET_CHAR_RELATIONSHIP_GROUP(ped1, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped2, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped3, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped4, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped5, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped6, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped7, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped8, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped9, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped10, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped11, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped12, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped13, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped14, 10);
			SET_CHAR_RELATIONSHIP_GROUP(ped15, 10);

			SET_SENSE_RANGE(ped1, 50.0);
			SET_SENSE_RANGE(ped2, 50.0);
			SET_SENSE_RANGE(ped3, 50.0);
			SET_SENSE_RANGE(ped4, 50.0);

			SET_CHAR_COORDINATES(ped1, 897.966, 474.762, 5.70474);
			SET_CHAR_COORDINATES(ped2, 921.068, 454.885, 5.70474);
			SET_CHAR_COORDINATES(ped3, 924.686, 458.321, 5.70474);
			SET_CHAR_COORDINATES(ped4, 899.902, 478.857, 5.70474);
			SET_CHAR_COORDINATES(ped5, 907.117, 460.876, 4.69996);
			SET_CHAR_COORDINATES(ped6, 906.203, 461.866, 4.69996);
			SET_CHAR_COORDINATES(ped7, 905.291, 462.857, 4.69996);
			SET_CHAR_COORDINATES(ped8, 904.376, 463.847, 4.69996);
			SET_CHAR_COORDINATES(ped9, 903.462, 464.838, 4.69996);
			SET_CHAR_COORDINATES(ped10, 908.546,464.934,4.2859);
			SET_CHAR_COORDINATES(ped11, 907.832,466.009,4.2859);
			SET_CHAR_COORDINATES(ped12, 909.088,465.815,4.2859);
			SET_CHAR_COORDINATES(ped13, 906.571, 468.175, 4.2859);
			SET_CHAR_COORDINATES(ped14, 905.726, 468.647, 4.2859);
			SET_CHAR_COORDINATES(ped15, 906.811, 469.028, 4.2859);
			SET_CHAR_COORDINATES(ped16, 907.591, 469.662, 4.2859);
			SET_CHAR_COORDINATES(ped17, 909.507, 468.637, 4.2859);
			SET_CHAR_COORDINATES(ped18, 908.651, 469.621, 4.2859);
			SET_CHAR_COORDINATES(ped19, 910.075, 470.021, 4.2859);
			SET_CHAR_COORDINATES(ped20, 911.761, 464.861, 4.2859);
			SET_CHAR_COORDINATES(ped21, 911.315, 465.771, 4.2859);
			SET_CHAR_COORDINATES(ped22, 912.434, 466.087, 4.2859);
			SET_CHAR_COORDINATES(ped23, 913.375, 465.669, 4.2859);
			SET_CHAR_COORDINATES(ped24, 913.777, 468.001, 4.2859);
			SET_CHAR_COORDINATES(ped25, 914.551, 468.994, 4.2859);
			SET_CHAR_COORDINATES(ped26, 908.449, 470.961, 4.2859);
			SET_CHAR_COORDINATES(ped27, 907.688, 471.589, 4.2859);
			SET_CHAR_COORDINATES(ped28, 911.885, 470.576, 4.2859);
			SET_CHAR_COORDINATES(ped29, 911.301, 472.306, 4.2859);
			SET_CHAR_COORDINATES(ped30, 912.794, 471.591, 4.2859);

			if (G_DIAZ != 7)
			{
				SET_CHAR_IN_CUTSCENE(ped1, 1);
				SET_CHAR_IN_CUTSCENE(ped2, 1);
				SET_CHAR_IN_CUTSCENE(ped3, 1);
				SET_CHAR_IN_CUTSCENE(ped4, 1);
				SET_CHAR_IN_CUTSCENE(ped5, 1);
				SET_CHAR_IN_CUTSCENE(ped6, 1);
				SET_CHAR_IN_CUTSCENE(ped7, 1);
				SET_CHAR_IN_CUTSCENE(ped8, 1);
				SET_CHAR_IN_CUTSCENE(ped9, 1);
				SET_CHAR_IN_CUTSCENE(ped10, 1);
				SET_CHAR_IN_CUTSCENE(ped11, 1);
				SET_CHAR_IN_CUTSCENE(ped12, 1);
				SET_CHAR_IN_CUTSCENE(ped13, 1);
				SET_CHAR_IN_CUTSCENE(ped14, 1);
				SET_CHAR_IN_CUTSCENE(ped15, 1);
				SET_CHAR_IN_CUTSCENE(ped16, 1);
				SET_CHAR_IN_CUTSCENE(ped17, 1);
				SET_CHAR_IN_CUTSCENE(ped18, 1);
				SET_CHAR_IN_CUTSCENE(ped19, 1);
				SET_CHAR_IN_CUTSCENE(ped20, 1);
				SET_CHAR_IN_CUTSCENE(ped21, 1);
				SET_CHAR_IN_CUTSCENE(ped22, 1);
				SET_CHAR_IN_CUTSCENE(ped23, 1);
				SET_CHAR_IN_CUTSCENE(ped24, 1);
				SET_CHAR_IN_CUTSCENE(ped25, 1);
				SET_CHAR_IN_CUTSCENE(ped26, 1);
				SET_CHAR_IN_CUTSCENE(ped27, 1);
				SET_CHAR_IN_CUTSCENE(ped28, 1);
				SET_CHAR_IN_CUTSCENE(ped29, 1);
				SET_CHAR_IN_CUTSCENE(ped30, 1);
			}

			SET_CHAR_HEADING(ped1, -135.0);
			SET_CHAR_HEADING(ped2, 45.0);
			SET_CHAR_HEADING(ped3, 45.0);
			SET_CHAR_HEADING(ped4, -135.0);
			SET_CHAR_HEADING(ped5, -45.0);
			SET_CHAR_HEADING(ped6, -45.0);
			SET_CHAR_HEADING(ped7, -45.0);
			SET_CHAR_HEADING(ped8, -45.0);
			SET_CHAR_HEADING(ped9, -45.0);
			SET_CHAR_HEADING(ped10, 0.0);
			SET_CHAR_HEADING(ped11, -130.0);
			SET_CHAR_HEADING(ped12, 135.0);
			SET_CHAR_HEADING(ped13, -15.0);
			SET_CHAR_HEADING(ped14, -70.0);
			SET_CHAR_HEADING(ped15, -145.0);
			SET_CHAR_HEADING(ped16, 115.0);
			SET_CHAR_HEADING(ped17, 0.0);
			SET_CHAR_HEADING(ped18, -45.0);
			SET_CHAR_HEADING(ped19, 120.0);
			SET_CHAR_HEADING(ped20, 0.0);
			SET_CHAR_HEADING(ped21, -60.0);
			SET_CHAR_HEADING(ped22, 115.0);
			SET_CHAR_HEADING(ped23, 70.0);
			SET_CHAR_HEADING(ped24, 0.0);
			SET_CHAR_HEADING(ped25, 100.0);
			SET_CHAR_HEADING(ped26, 0.0);
			SET_CHAR_HEADING(ped27, -125.0);
			SET_CHAR_HEADING(ped28, -60.0);
			SET_CHAR_HEADING(ped29, -175.0);
			SET_CHAR_HEADING(ped30, 0.0);

			SET_ROOM_FOR_CHAR_BY_NAME(ped1, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped2, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped3, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped4, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped5, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped6, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped7, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped8, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped9, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped10, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped11, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped12, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped13, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped14, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped15, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped16, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped17, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped18, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped19, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped20, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped21, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped22, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped23, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped24, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped25, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped26, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped27, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped28, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped29, "club_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped30, "club_mloroom");

			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped4, "wipe_counter", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped5, "f_loop_a", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped6, "m_loop_b", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped7, "m_loop_c", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped8, "f_loop_b", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped9, "f_loop_c", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped10, "m_loop_a", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped11, "m_loop_b", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped12, "f_loop_a", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped13, "f_loop_b", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped14, "f_loop_c", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped15, "m_loop_c", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped16, "m_loop_d", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped17, "f_loop_a", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped18, "m_loop_a", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped19, "m_loop_b", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped20, "m_loop_c", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped21, "f_loop_b", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped22, "m_loop_d", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped23, "f_loop_c", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped24, "f_loop_a", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped25, "f_loop_b", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped26, "f_loop_c", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped27, "m_loop_a", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped28, "f_loop_a", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped29, "m_loop_b", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped30, "f_loop_b", "vcne_dance", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
			in_int2 = 1;
		}
		else if ((!IS_CHAR_IN_AREA_3D( GetPlayerPed(), 936.653, 431.187, 3.387, 886.653, 486.187, 18.387, 0 )) && (in_int2 == 1))// интрерьер клуб Малибу
		{
			/*/ прячим педов
			SET_CHAR_COORDINATES(ped1, 11.001, 33.147, 5.6515);
			SET_CHAR_COORDINATES(ped2, 12.047, 27.962, 5.7054);
			SET_CHAR_COORDINATES(ped3, 19.065, 30.284, 5.6515);
			SET_CHAR_COORDINATES(ped4, 14.279, 24.151, 5.7209);
			SET_CHAR_COORDINATES(ped5, 24.702, 23.151, 4.76645);
			SET_CHAR_COORDINATES(ped6, 21.085, 16.613, 4.76645);
			SET_CHAR_COORDINATES(ped7, 21.951, 28.173, 4.76645);
			SET_CHAR_COORDINATES(ped8, 23.132, 23.934, 4.76645);
			SET_CHAR_COORDINATES(ped9, 11.492, 33.913, 4.76645);
			SET_CHAR_COORDINATES(ped10, 10.487, 33.564, 4.76645);
			SET_CHAR_COORDINATES(ped11, 19.893, 31.011, 4.76645);
			SET_CHAR_COORDINATES(ped12, 13.101, 29.801, 4.76645);
			SET_CHAR_COORDINATES(ped13, 14.822, 26.866, 4.76645);
			SET_CHAR_COORDINATES(ped14, 16.455, 25.912, 4.76645);
			SET_CHAR_COORDINATES(ped15, 15.215, 22.371, 4.76645);
			SET_CHAR_COORDINATES(ped16, 12.001, 33.147, 5.6515);
			SET_CHAR_COORDINATES(ped17, 14.047, 27.962, 5.7054);
			SET_CHAR_COORDINATES(ped18, 21.065, 30.284, 5.6515);
			SET_CHAR_COORDINATES(ped19, 16.279, 24.151, 5.7209);
			SET_CHAR_COORDINATES(ped20, 26.702, 23.151, 4.76645);
			SET_CHAR_COORDINATES(ped21, 23.085, 16.613, 4.76645);
			SET_CHAR_COORDINATES(ped22, 23.951, 28.173, 4.76645);
			SET_CHAR_COORDINATES(ped23, 25.132, 23.934, 4.76645);
			SET_CHAR_COORDINATES(ped24, 13.492, 33.913, 4.76645);
			SET_CHAR_COORDINATES(ped25, 12.487, 33.564, 4.76645);
			SET_CHAR_COORDINATES(ped26, 21.893, 31.011, 4.76645);
			SET_CHAR_COORDINATES(ped27, 15.101, 29.801, 4.76645);
			SET_CHAR_COORDINATES(ped28, 16.822, 26.866, 4.76645);
			SET_CHAR_COORDINATES(ped29, 18.455, 25.912, 4.76645);
			SET_CHAR_COORDINATES(ped30, 17.215, 22.371, 4.76645);
			//*/
			// выгружвем модели
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM2);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM3);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM4);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM5);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM6);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM7);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM8);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM9);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM10);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM11);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM12);//выгружаем модель
			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM13);//выгружаем модель
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
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped21);//выгружаем модель педа(в последствии пед изчезнет
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped22);//выгружаем модель педа(в последствии пед изчезнет
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped23);//выгружаем модель педа(в последствии пед изчезнет
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped24);//выгружаем модель педа(в последствии пед изчезнет
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped25);//выгружаем модель педа(в последствии пед изчезнет
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped26);//выгружаем модель педа(в последствии пед изчезнет
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped27);//выгружаем модель педа(в последствии пед изчезнет
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped28);//выгружаем модель педа(в последствии пед изчезнет
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped29);//выгружаем модель педа(в последствии пед изчезнет
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped30);//выгружаем модель педа(в последствии пед изчезнет
			CLEAR_AREA(910.625, 467.498, 4.35257, 18.0, 1);//очещаем зону загрузки
			in_int2 = 0;
		}

		GET_INTERIOR_FROM_CHAR(GetPlayerPed(), &intHash);
		//DISPLAY_TEXT_WITH_NUMBER(0.9083334, 0.72787074, "CP_TIME_NOZERO", intHash);// 
		if ((intHash == 770 ) && (in_int3 == 0))// интрерьер полицейский участок
		{
			PedM1 = MODEL_M_Y_COP;// Коп
			REQUEST_MODEL(PedM1);// Коп
			while (!HAS_MODEL_LOADED(PedM1)) WAIT(10);////проверка "пед загрузился" если нет то начанаем с начало

			CREATE_CHAR (26, PedM1, 527.002, -876.002, 4.64608, &ped1, TRUE);// коп
			CREATE_CHAR (26, PedM1, 533.002, -874.002, 4.64608, &ped2, TRUE);// коп
			CREATE_CHAR (26, PedM1, 536.002, -874.002, 4.64608, &ped3, TRUE);// коп
			CREATE_CHAR (26, PedM1, 539.002, -874.002, 4.64608, &ped4, TRUE);// коп

			SET_CHAR_RELATIONSHIP_GROUP(ped1, 3);
			SET_CHAR_RELATIONSHIP_GROUP(ped2, 3);
			SET_CHAR_RELATIONSHIP_GROUP(ped3, 3);
			SET_CHAR_RELATIONSHIP_GROUP(ped4, 3);

			SET_CHAR_COORDINATES(ped1, 808.124, 48.3821, 8.2391);// уходит
			SET_CHAR_COORDINATES(ped2, 808.714, 46.4646, 8.2391);// уходит
			SET_CHAR_COORDINATES(ped3, 813.005, 40.2273, 6.57517);// уходит
			SET_CHAR_COORDINATES(ped4, 820.292, 45.2293, 6.68949);// уходит

			SET_CHAR_HEADING(ped1, -129.0);
			SET_CHAR_HEADING(ped2, -129.0);
			SET_CHAR_HEADING(ped3, -34.0);
			SET_CHAR_HEADING(ped4, 51.0);

			SET_ROOM_FOR_CHAR_BY_NAME(ped1, "cop_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped2, "cop_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped3, "cop_mloroom");
			SET_ROOM_FOR_CHAR_BY_NAME(ped4, "cop_mloroom");

			UpdateWeaponOfPed(ped1, WEAPON_PISTOL);
			UpdateWeaponOfPed(ped2, WEAPON_PISTOL);
			UpdateWeaponOfPed(ped3, WEAPON_PISTOL);
			UpdateWeaponOfPed(ped4, WEAPON_PISTOL);

			MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped2);//выгружаем модель педа(в последствии пед изчезнет
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped3);//выгружаем модель педа(в последствии пед изчезнет
			MARK_CHAR_AS_NO_LONGER_NEEDED(&ped4);//выгружаем модель педа(в последствии пед изчезнет

			in_int3 = 1;
		}
		else if (( intHash != 770 ) && (in_int3 == 1))// интрерьер полицейский участок
		{
			in_int3 = 0;
		}

		if (( intHash == 258 ) && (if_intMall == 0)) // интрерьер Молл
		{
			if_intMall = 1;
		}


		if ( if_intMall == 1 ) // интрерьер Молл
		{
			if ( intHash != 258 )
			{
				ZOMBIE_DEL = 1;
			}
			if (TIMERA() > 400)
			{
				if (ZOMBIE_DEL == 1)
				{
					int i;
					for (i = 0; i < ZOMB_MAX; i++)
						if ( DOES_CHAR_EXIST(zombies[i]) )
						{
							DELETE_CHAR(&zombies[i]);//удаляем модель педа
							ZOMBIE_DEL = 0;
							if_intMall = 0;
						}
					continue;
				}
				// check for player died -> delete zombies
				if (IS_CHAR_DEAD(GetPlayerPed()))
				{
					while (IS_CHAR_DEAD(GetPlayerPed())) WAIT(0);
					int i;
					for (i = 0; i < ZOMB_MAX; i++)	DELETE_CHAR(&zombies[i]);
					WAIT(3000);
					continue;
				}
				// check if player is at the base -> next iteration
				if ( ZOMBIE_ON_OFF == 0 )
				{
			#ifdef DEBUG
					WAIT(0);
					//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "inside of the base", 1000, 1);
			#endif
					continue;
				}
				// check for player in the water -> next iteration
				if ( IS_CHAR_IN_WATER(GetPlayerPed()) ) continue;
				// zombie check cycle
				int i;
				for (i = 0; i < ZOMB_MAX; i++)
				{
					//WAIT(10);
					GENERATE_RANDOM_INT_IN_RANGE(0, 25, &wait_fix);
					if ((wait_fix == 5) ||(wait_fix == 10) ||(wait_fix == 15))
					{
						WAIT(10);
					}
					// delete unneeded zombie and make player drunk if he is near zombie
					if ( DOES_CHAR_EXIST(zombies[i]) )
					{
						float x, y, z, xpl, ypl, zpl, dist;
						GET_CHAR_COORDINATES(zombies[i], &x, &y, &z);
						GET_CHAR_COORDINATES(GetPlayerPed(), &xpl, &ypl, &zpl);
						GET_DISTANCE_BETWEEN_COORDS_3D(x, y, z, xpl, ypl, zpl, &dist);
						if ( (dist > 40.0) || IS_CHAR_DEAD(zombies[i]) || IS_CHAR_IN_WATER(zombies[i]) || IS_CHAR_IN_AIR(zombies[i])) 
						{

							if (IS_CHAR_DEAD(zombies[i]))
							{
								EXPLODE_CHAR_HEAD(zombies[i]);
								TASK_DIE(zombies[i]);
								MARK_CHAR_AS_NO_LONGER_NEEDED(&zombies[i]);
							}
							else
							{
								GENERATE_RANDOM_INT_IN_RANGE(0, 25, &del_ped);
								if ((del_ped == 5) || (del_ped == 10) || (del_ped == 15))
								{
									DELETE_CHAR(&zombies[i]);//удаляем модель педа
								}
								else
								{
									//рендом задержки тут
									zombiecord ();
									SET_CHAR_COORDINATES_NO_OFFSET(zombies[i],Tx, Ty, Tz);
									SET_ROOM_FOR_CHAR_BY_NAME(zombies[i], "mall_mloroom");
									//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "teleport", 1000, 1);
								}
							}
						}
						continue;
					}

					uint ranmodel;
					GENERATE_RANDOM_INT_IN_RANGE(0, 21, &ranmodel);
					if ((ranmodel == 0) || (ranmodel == 11))
					{
						ZOMB_MODEL = MODEL_F_M_PMANHAT_01;
					}
					else if ((ranmodel == 1) || (ranmodel == 12))
					{
						ZOMB_MODEL = MODEL_F_M_PRICH_01;
					}
					else if ((ranmodel == 2) || (ranmodel == 13))
					{
						ZOMB_MODEL = MODEL_F_Y_PHARLEM_01;
					}
					else if ((ranmodel == 3) || (ranmodel == 14))
					{
						ZOMB_MODEL = MODEL_M_M_PBUSINESS_01;
					}
					else if ((ranmodel == 4) || (ranmodel == 15))
					{
						ZOMB_MODEL = MODEL_F_Y_PMANHAT_01;
					}
					else if ((ranmodel == 5) || (ranmodel == 16))
					{
						ZOMB_MODEL = MODEL_M_M_TENNIS;
					}
					else if ((ranmodel == 6) || (ranmodel == 17))
					{
						ZOMB_MODEL = MODEL_F_Y_SHOP_04;
					}
					else if ((ranmodel == 7) || (ranmodel == 18))
					{
						ZOMB_MODEL = MODEL_F_Y_SOCIALITE;
					}
					else if ((ranmodel == 8) || (ranmodel == 19))
					{
						ZOMB_MODEL = MODEL_F_Y_STREET_05;
					}
					else if ((ranmodel == 9) || (ranmodel == 20))
					{
						ZOMB_MODEL = MODEL_F_Y_STREET_05;
					}
					else if ((ranmodel == 10) || (ranmodel == 21))
					{
						ZOMB_MODEL = MODEL_M_Y_COP;
					}

					GENERATE_RANDOM_INT_IN_RANGE(0, 25, &wait_fix);
					if (wait_fix == 5)
					{
						WAIT(100);
					}
					//zombiecord ();
					//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "ped gen", 1000, 1);

					uint randint;
					CheckModelLoad(ZOMB_MODEL);
					CREATE_CHAR (RELATIONSHIP_GROUP_DEALER, ZOMB_MODEL, 527.0, -870.0, 4.6, &zombies[i], 1);
					zombiecord ();
					SET_CHAR_COORDINATES_NO_OFFSET(zombies[i],Tx, Ty, Tz);
					GENERATE_RANDOM_INT_IN_RANGE(0, 360, &randint);
					SET_CHAR_HEADING(zombies[i], randint);
					SET_ROOM_FOR_CHAR_BY_NAME(zombies[i], "mall_mloroom");
					TASK_WANDER_STANDARD(zombies[i]);
					GENERATE_RANDOM_INT_IN_RANGE(0, 100, &randint);
					SET_CHAR_MONEY(zombies[i], randint);
					CANCEL_CURRENTLY_PLAYING_AMBIENT_SPEECH(zombies[i]);

			#ifdef DEBUG
					WAIT(0);
					//PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "new zombie created", 1000, 1);
			#endif
				}
				SETTIMERA( 0 );
			}
		}
	}
}