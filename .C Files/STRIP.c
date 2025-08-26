/***********************************************************************
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
int money_ped, income, load_mashin, help, autosave;
float PlayX, PlayY, PlayZ, PlayR, blip_on, skip, cash, cam_set;

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
void stripclub(void)
{
	blip_on = 0;
	autosave = 0;
	load_mashin = 0;
	help = 0;
	Blip strip_ico;	
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
//============================== Strip club ======================================
		if (((G_ONMISSION == 0) && (G_STRIP == 1)) || ((G_ONMISSION == 0) && (G_STRIP == 2)))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(526.212, -932.28, 4.34719, &strip_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(strip_ico, BLIP_STRIP_CLUB);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(strip_ico, 1.1); // масштаб иконки на радаре
				SET_BLIP_AS_SHORT_RANGE(strip_ico, 1); // иконка пропадает если не в зоне радардиска
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(strip_ico, "LG_37");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 502.818, -925.957, 4.029, 498.818, -921.957, 9.029, 0 )))
			{
				Cam camera;
				uint pedN, PedM1, uVar14;
				Ped ped1;
				Interior getint;
				G_ONMISSION = 1;
				REMOVE_BLIP(strip_ico);//Удаляем иконку на радаре
				blip_on = 0;
				cash = 0;
				cam_set = 2;
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

				// грузим модель тут
				GENERATE_RANDOM_INT_IN_RANGE( 1, 9, &pedN);//получаем рендомное число
				if ((pedN == 1) || (pedN == 4) || (pedN == 7) || (pedN == 3) || (pedN == 9))
				{
					PedM1 = MODEL_F_Y_STRIPPERC01;// strip 1
				}
				else if ((pedN == 2) || (pedN == 5) || (pedN == 8) || (pedN == 6))
				{
					PedM1 = MODEL_F_Y_STRIPPERC02;// strip 2
				}
				
				REQUEST_MODEL(PedM1);// 
				while (!HAS_MODEL_LOADED(PedM1));////проверка "пед загрузился" если нет то начанаем с начало
				CREATE_CHAR (26, PedM1, 530.858, -939.535, 4.89498, &ped1, TRUE);// SWAT
				SET_CHAR_COORDINATES(ped1, 499.141, -921.479, 4.83806);
				SET_CHAR_HEADING(ped1, 35.0);

				CLEAR_AREA(498.892, -920.29, 4.83806, 5.0, 1);//очещаем зону загрузки
				SET_CHAR_COORDINATES(GetPlayerPed(), 498.892, -920.29, 4.83806);
				SET_CHAR_HEADING(GetPlayerPed(), -155.0);
				FREEZE_CHAR_POSITION(GetPlayerPed(), 1);

				//грузим анимацию
				REQUEST_ANIMS( "missstripclub" );//загружаем файл с анимацией
				while (!HAVE_ANIMS_LOADED( "missstripclub" )) WAIT(0);

				GENERATE_RANDOM_INT_IN_RANGE( 1, 9, &pedN);//получаем рендомное число
				if ((pedN == 1) || (pedN == 4) || (pedN == 7))
				{
					TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "dance_ragga_2", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				}
				else if ((pedN == 2) || (pedN == 5) || (pedN == 8))
				{
					TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "dance_wisper_2", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				}
				if ((pedN == 3) || (pedN == 6) || (pedN == 9))
				{
					TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "pole_dance_a", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				}
				SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, TRUE);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "watch_lap_dance_loop", "missstripclub", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
				

				// камера ракурс 1
				CREATE_CAM( 14, &camera );
				POINT_CAM_AT_COORD	( camera, 499.844, -922.458, 5.91986 ); // куда смотрит камера
				SET_CAM_POS			( camera, 499.497, -926.378, 8.06714 );//расположение камеры
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);
				SET_CAM_FOV( camera, 45.0 );
				SET_WIDESCREEN_BORDERS( 1 );

				DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
				SETTIMERA( 0 );
				SETTIMERB( 0 );
				PRINT_HELP_FOREVER("EXIT_1"); //Press the ~INPUT_PHONE_CANCEL~ button to exit.

				while(true)
				{
					WAIT(0);
					if (TIMERB() > 10000)// поверка игрок мёртв/арестован
					{
						if (cam_set == 1) // ракурс 1
						{
							POINT_CAM_AT_COORD	( camera, 499.844, -922.458, 5.91986 ); // куда смотрит камера
							SET_CAM_POS			( camera, 499.497, -926.378, 8.06714 );//расположение камеры
							cam_set = 2;
						}
						else if (cam_set == 2) // ракурс 2
						{
							POINT_CAM_AT_COORD	( camera, 499.549, -921.961, 5.73907 ); // куда смотрит камера
							SET_CAM_POS			( camera, 497.191, -921.178, 5.56758 );//расположение камеры
							cam_set = 3;
						}
						else if (cam_set == 3) // ракурс 3
						{
							POINT_CAM_AT_COORD	( camera, 500.221, -922.671, 5.48178 ); // куда смотрит камера
							SET_CAM_POS			( camera, 501.433, -921.274, 4.80086 );//расположение камеры
							cam_set = 4;
						}
						else if (cam_set == 4) // ракурс 4
						{
							POINT_CAM_AT_COORD	( camera, 499.751, -921.807, 5.90821 ); // куда смотрит камера
							SET_CAM_POS			( camera, 498.881, -920.334, 7.61358 );//расположение камеры
							cam_set = 5;
						}
						else if (cam_set == 5) // ракурс 5
						{
							POINT_CAM_AT_COORD	( camera, 499.998, -921.742, 5.56992 ); // куда смотрит камера
							SET_CAM_POS			( camera, 500.307, -919.739, 4.72875 );//расположение камеры
							cam_set = 1;
						}
						SETTIMERB( 0 );
					}

					STORE_SCORE(GetPlayerIndex(), &money_ped);// записываем средства игрока в переменную
					if ((TIMERA() > 5000) && (money_ped > 10))// поверка игрок мёртв/арестован
					{
						SETTIMERA( 0 );
						cash += 1;
						ADD_SCORE( GetPlayerIndex(), -10 );// отнимаем у игрока сумму
						INCREMENT_FLOAT_STAT(STAT_SPENT_IN_STRIP_CLUBS, 10);
					}
					if ((IS_BUTTON_PRESSED( 0, 17 )) || ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) || (money_ped < 10)) //клавиатура BACKSPACE
					{
						CLEAR_HELP(); // удаляем текст подсказки
						if ((money_ped < 10) && (cash < 30))
						{
							PRINT_STRING_IN_STRING("string", "STRIP_1", 5000, 1);//~r~Not enough cash, you cheap sleazebag.
						}
						if ((cash >= 30) && (G_STRIP == 1))
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
							POINT_CAM_AT_COORD	( camera, 530.951, -939.898, 10.2194 ); // куда смотрит камера
							SET_CAM_POS			( camera, 538.559, -954.132, 13.486 );//расположение камеры
							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
							MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 1 );

							play_mission_complete_tune();
							SETTIMERA(0); //сбрасываем таймер 
							while (true)
							{
								SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
								SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
								SET_TEXT_EDGE(1, 0, 0, 0, 255); //
								SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
								SET_TEXT_CENTRE(1); // задаём центр текста
								DISPLAY_TEXT(0.5, 0.45, "ASSET_C");//POLE POSITION ASSET COMPLETED!
								WAIT( 0 );
								if ( TIMERA() > 5000 )
								{
									break;
								}
							}

							LOAD_SCENE( 499.998, -921.742, 5.56992 );
							GET_INTERIOR_AT_COORDS( 499.998, -921.742, 5.56992, &getint );
							uVar14 = GET_HASH_KEY("strip_mloroom");
							LOAD_SCENE_FOR_ROOM_BY_KEY( getint, uVar14 );
							MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 0 );

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, 499.998, -921.742, 5.56992 ); // куда смотрит камера
							SET_CAM_POS			( camera, 500.307, -919.739, 4.72875 );//расположение камеры
							SetTime(10);

							POINT_CAM_AT_COORD	( camera, 510.385, -915.861, 5.43983 ); // куда смотрит камера
							SET_CAM_POS			( camera, 510.517, -917.174, 6.08692 ); // расположение камеры

							PRINT_STRING_IN_STRING("string", "ASSET_D", 5000, 1);//~g~The Pole Position Club will now generate revenue up to a maximum of $4000 per day. Pick up your cash regularly!

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
							G_STRIP = 2;
							G_GAME_PROGRESS += 1;
							SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
							autosave = 1;
						}
						break;
					}
				}

				// чистим скрипт
				CLEAR_HELP(); // удаляем текст подсказки
				DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
				while(true)
				{
					WAIT(0);
					if (IS_SCREEN_FADED_OUT())
					{
						break;
					}
				}
				TASK_PLAY_ANIM_NON_INTERRUPTABLE( GetPlayerPed(), "watch_lap_dance_loop", "missstripclub", 8.0, 1, 0, 0, 0, 1 );//Воиспроизвидение анимации на педе
				SET_CHAR_COORDINATES(ped1, -70.955, 52.881, 8.097);
				SET_CHAR_COORDINATES(GetPlayerPed(), 503.799, -921.955, 4.83806);
				SET_CHAR_HEADING(GetPlayerPed(), -65.0);
				WAIT(500);

				//убираем камеру
				ACTIVATE_SCRIPTED_CAMS( 0, 0 );
				DESTROY_CAM( camera );
				SET_WIDESCREEN_BORDERS( 0 );
				DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

				// выгружвем модели
				MARK_MODEL_AS_NO_LONGER_NEEDED(PedM1);//выгружаем модель
				// выгружвем педов
				MARK_CHAR_AS_NO_LONGER_NEEDED(&ped1);//выгружаем модель педа(в последствии пед изчезнет

				FREEZE_CHAR_POSITION(GetPlayerPed(), 0);
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
				G_ONMISSION = 0;
			}
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(strip_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}
		if ((G_ONMISSION == 0) && (G_STRIP == 2))
		{
			if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 508.202, -911.547, 4.029, 501.752, -907.547, 9.029, 0 )))
			{
				G_ONMISSION = 1;
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
				MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 1 );
				SET_CHAR_COORDINATES(GetPlayerPed(), 501.266, -911.76, 4.76966);
				SET_CHAR_HEADING(GetPlayerPed(), 115.0);

				//------------ катсцена ----------------
				START_CUTSCENE_NOW("stripa");
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
				G_ONMISSION = 0;
				MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 0 );
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );//размораживаем игрока
			}
		}

		if (G_STRIP == 2)
		{
			if ( TIMERC() > 720)// время фарма
			{
				if (income < 4000)// максимальный доход
				{
					income +=1;
				}
				SETTIMERC(0); //сбрасываем таймер 
			}
			if (G_COLLECTOR == 8)// ID Бизнеса
			{
				income = 0;
				G_COLLECTOR = 0;
			}

			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), 512.403, -918.8, 4.419, 508.403, -913.8, 7.405, 0 ))
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
				if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), 511.637, -917.07, 509.957, -915.276, 0))
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
	stripclub();
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
