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
float PlayX, PlayY, PlayZ, PlayR, blip_on, spisok, spisok_on, s_car_1, s_car_2, s_car_3, s_car_4, s_car_5, s_car_6, in_model, text, text2, cash, autosave;
float textur1;
int income, load_mashin, help, time_income, temp;

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
void Sunshine(void)
{
	Cam camera;
	blip_on = 0;
	autosave = 0;
	spisok_on = 0;
	Blip sun_ico;
	Texture fon_spiska, polosa_spiska;
	uint rId9, rId92;
	Car car1;
	load_mashin = 0;
	help = 0;
	s_car_1 = 0;
	s_car_2 = 0;
	s_car_3 = 0;
	s_car_4 = 0;
	s_car_5 = 0;
	s_car_6 = 0;
	in_model = 0;
	text = 0;
	text2 = 0;
	WAIT(3000);
	spisok = 1;

	while(true)
	{
		WAIT(0);
		if (autosave == 1)
		{
			autosave = 0;
			DO_AUTO_SAVE();
			WAIT(500);
		}
//============================== Sunshine Autos Import Garage ======================================
		if ((G_ONMISSION == 0) && (G_BUSINES_SA > 0))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-584.339, -331.17, 6.98854, &sun_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(sun_ico, BLIP_GARAGE);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(sun_ico, 1.1); // масштаб иконки на радаре
				SET_BLIP_AS_SHORT_RANGE(sun_ico, 1); // иконка пропадает если не в зоне радардиска
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(sun_ico, "LG_36");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(sun_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}

		if ((IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (G_BUSINES_SA > 0) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -538.322, -308.536, 0.405, -546.322, -296.536, 5.905, 0 )) && (IS_GARAGE_CLOSED("ab_auto")))
		{
			if (text == 0)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				PRINT_HELP("NECAR_SA1"); //Press ~INPUT_VEH_HORN~ to sound your horn to enter the garage.
				text = 1;
			}
			if (IS_PLAYER_PRESSING_HORN(0))// проверка "игрок посигналил"
			{
				if (G_ONMISSION == 1)
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NECAR_SA8"); //Come back when you're not so busy...
					while (true)
					{
						if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) || (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -538.322, -308.536, 0.405, -546.322, -296.536, 5.905, 0 )) )
						{
							CLEAR_HELP(); // удаляем текст подсказки
							break;
						}
						WAIT(0);
					}
				}
				else if (IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 0))//проверка на розыск
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("NECAR_SA9"); //There are too many cops about, lose your wanted level.
					while (true)
					{
						if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) || (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -538.322, -308.536, 0.405, -546.322, -296.536, 5.905, 0 )) )
						{
							CLEAR_HELP(); // удаляем текст подсказки
							break;
						}
						WAIT(0);
					}
				}
				else
				{
					if (spisok == 1)
					{
						if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_LANDSTALKER)) && (s_car_1 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_EMPEROR)) && (s_car_2 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SCHAFTER)) && (s_car_2 == 0)) in_model = 1;
						else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_ESPERANTO)) && (s_car_3 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_STALION)) && (s_car_4 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SULTAN)) && (s_car_4 == 0)) in_model = 1;
						else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_RANCHER)) && (s_car_5 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_BLISTA)) && (s_car_6 == 0)) in_model = 1;
						else
						{
							if (text2 == 0)
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NECAR_SA2", 5000, 1);//We do not work with this vehicle.
								text2 = 1;
							}
						}
					}
					else if (spisok == 2)
					{
						if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SABRE)) && (s_car_1 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SABRE2)) && (s_car_1 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_VIRGO)) && (s_car_2 == 0)) in_model = 1;
						else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SENTINEL)) && (s_car_3 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_STRETCH)) && (s_car_4 == 0)) in_model = 1;
						else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_WASHINGTON)) && (s_car_5 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_ADMIRAL)) && (s_car_6 == 0)) in_model = 1;
						else
						{
							if (text2 == 0)
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NECAR_SA2", 5000, 1);//We do not work with this vehicle.
								text2 = 1;
							}
						}
					}
					else if (spisok == 3)
					{
						if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_SUPERGT)) && (s_car_1 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_NOOSE)) && (s_car_1 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_HAKUMAI)) && (s_car_1 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_INFERNUS)) && (s_car_2 == 0)) in_model = 1;
						else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_BANSHEE)) && (s_car_3 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_RUINER)) && (s_car_4 == 0)) in_model = 1;
						else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_COMET)) && (s_car_5 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_LOKUS)) && (s_car_5 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_COQUETTE)) && (s_car_6 == 0)) in_model = 1;
						else
						{
							if (text2 == 0)
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NECAR_SA2", 5000, 1);//We do not work with this vehicle.
								text2 = 1;
							}
						}
					}
					else if (spisok == 4)
					{
						if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_VOODOO)) && (s_car_1 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_DUKES)) && (s_car_2 == 0)) in_model = 1;
						else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_HUNTLEY)) && (s_car_3 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_AIRTUG)) && (s_car_4 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_PERENNIAL2)) && (s_car_4 == 0)) in_model = 1;
						else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_MRTASTY)) && (s_car_5 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_HELLFURY)) && (s_car_6 == 0) || (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_FAGGIO)) && (s_car_6 == 0)) in_model = 1;
						else
						{
							if (text2 == 0)
							{
								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NECAR_SA2", 5000, 1);//We do not work with this vehicle.
								text2 = 1;
							}
						}
					}
					else if (spisok > 4)
					{
						if (text2 == 0)
						{
							CLEAR_PRINTS();
							PRINT_STRING_IN_STRING("string", "NECAR_SA2", 5000, 1);//We do not work with this vehicle.
							text2 = 1;
						}
					}

					if (in_model == 1)
					{
						OPEN_GARAGE("ab_auto");
						GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car1);
						G_ONMISSION = 1;
						CLEAR_PRINTS();
						PRINT_STRING_IN_STRING("string", "NECAR_SA3", 5000, 1);//Park the vehicle in the garage. 
						while (true)
						{
							WAIT(0);
							if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
							{
								MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
								in_model = 0;
								G_ONMISSION = 0;
								text = 0;
								text2 = 0;
								break;
							}
							if ((IS_CAR_IN_AREA_3D( car1, -532.398, -328.951, -0.405, -545.86, -307.877, 6.416, 0 )) && (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -532.398, -328.951, -0.515, -547.389, -305.558, 7.17, 0 ))) //гараж
							{
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );
								CLOSE_GARAGE("ab_auto");
								CLEAR_HELP(); // удаляем текст подсказки
								while (true)
								{
									WAIT(0);
									if (IS_GARAGE_CLOSED("ab_auto"))
									{
										break;
									}
								}
								if ((IS_CAR_MODEL(car1, MODEL_LANDSTALKER)) || (IS_CAR_MODEL(car1, MODEL_SABRE))  || (IS_CAR_MODEL(car1, MODEL_SABRE2)) || (IS_CAR_MODEL(car1, MODEL_HAKUMAI)) || (IS_CAR_MODEL(car1, MODEL_NOOSE)) || (IS_CAR_MODEL(car1, MODEL_HAKUMAI)) || (IS_CAR_MODEL(car1, MODEL_VOODOO)))
								{
									s_car_1 = 1;
								}
								else if ((IS_CAR_MODEL(car1, MODEL_SCHAFTER)) || (IS_CAR_MODEL(car1, MODEL_EMPEROR)) || (IS_CAR_MODEL(car1, MODEL_VIRGO)) || (IS_CAR_MODEL(car1, MODEL_INFERNUS)) || (IS_CAR_MODEL(car1, MODEL_DUKES)))
								{
									s_car_2 = 1;
								}
								else if ((IS_CAR_MODEL(car1, MODEL_ESPERANTO)) || (IS_CAR_MODEL(car1, MODEL_SENTINEL)) || (IS_CAR_MODEL(car1, MODEL_BANSHEE)) || (IS_CAR_MODEL(car1, MODEL_HUNTLEY)))
								{
									s_car_3 = 1;
								}
								else if ((IS_CAR_MODEL(car1, MODEL_SULTAN)) || (IS_CAR_MODEL(car1, MODEL_STALION)) || (IS_CAR_MODEL(car1, MODEL_STRETCH)) || (IS_CAR_MODEL(car1, MODEL_RUINER)) || (IS_CAR_MODEL(car1, MODEL_PERENNIAL2)) || (IS_CAR_MODEL(car1, MODEL_AIRTUG)))
								{
									s_car_4 = 1;
								}
								else if ((IS_CAR_MODEL(car1, MODEL_RANCHER)) || (IS_CAR_MODEL(car1, MODEL_WASHINGTON)) || (IS_CAR_MODEL(car1, MODEL_LOKUS)) || (IS_CAR_MODEL(car1, MODEL_COMET)) || (IS_CAR_MODEL(car1, MODEL_MRTASTY)))
								{
									s_car_5 = 1;
								}
								else if ((IS_CAR_MODEL(car1, MODEL_BLISTA)) || (IS_CAR_MODEL(car1, MODEL_ADMIRAL)) || (IS_CAR_MODEL(car1, MODEL_COQUETTE)) || (IS_CAR_MODEL(car1, MODEL_FAGGIO)) || (IS_CAR_MODEL(car1, MODEL_HELLFURY)))
								{
									s_car_6 = 1;
								}

								DELETE_CAR(&car1);
								MARK_CAR_AS_NO_LONGER_NEEDED(&car1);

								CLEAR_PRINTS();
								PRINT_STRING_IN_STRING("string", "NECAR_SA6", 5000, 1);//Delivered like a pro. Complete the list and there'll be a bonus for you.

								// демонстрация пиризовых авто тут
								if ((s_car_1 == 1) && (s_car_2 == 1) && (s_car_3 == 1) && (s_car_4 == 1) && (s_car_5 == 1) && (s_car_6 == 1))
								{
									if (spisok == 1)
									{
										DO_SCREEN_FADE_OUT( 2500 );// Затемняем экран
										while (true)
										{
											if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
											{
												break;
											}
											WAIT( 0 );
										}

										INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
										INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
										G_GAME_PROGRESS += 1;
										SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
										uint CarM1 = MODEL_FUTO;// Deluxo
										REQUEST_MODEL(CarM1);
										while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
  										Car a1;
  										CREATE_CAR(CarM1, -589.355, -333.968, 7.66709, &car1, TRUE);
  										SET_CAR_HEADING(car1, 160.0);
										SET_VEHICLE_DIRT_LEVEL(car1, 0);
										MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
										MARK_CAR_AS_NO_LONGER_NEEDED(&car1);	
										cash = 1500;
										time_income = 1920;
										G_BUSINES_SA = 2;
										autosave = 1;

										CREATE_CAM( 14, &camera );
										POINT_CAM_AT_COORD	( camera, -589.355, -333.968, 7.66709 ); // куда смотрит камера
										SET_CAM_POS			( camera, -583.815, -331.098, 8.7464 );//расположение камеры
										SET_CAM_ACTIVE( camera, 1 );
										SET_CAM_PROPAGATE( camera, 1 );
										ACTIVATE_SCRIPTED_CAMS(1, 1);
										SET_WIDESCREEN_BORDERS( 1 );
										SETTIMERA(0);

										DO_SCREEN_FADE_IN( 2500 );// убирается затемнение экрана

										while (true)
										{
											WAIT( 0 );
											DISABLE_PAUSE_MENU(1);// отключаем главное меню
											SET_TEXT_COLOUR(109, 205, 255, 255); // задаём цвет текста
											SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
											SET_TEXT_EDGE(1, 0, 0, 0, 255); //
											SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
											SET_TEXT_CENTRE(1); // задаём центр текста
											DISPLAY_TEXT(0.5, 0.4, "NECAR_SA7");//All the cars. NICE! Here's a little something.
											if (( TIMERA() > 4000 ) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
											{
												break;
											}
										}

										POINT_CAM_AT_COORD	( camera, -589.355, -333.968, 7.66709); // куда смотрит камера
										SET_CAM_POS			( camera, -587.284, -340.629, 8.38526); //расположение камеры
										SetTime(4000);

										DO_SCREEN_FADE_OUT( 1500 );// Затемняем экран
										while (true)
										{
											WAIT( 0 );
											if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
											{
												break;
											}
										}

										DO_SCREEN_FADE_IN( 1500 );// убирается затемнение экрана
										play_mission_complete_tune(); 
										SETTIMERA(0); //сбрасываем таймер 
										POINT_CAM_AT_COORD	( camera, -583.188, -334.591, 12.646); // куда смотрит камера
										SET_CAM_POS			( camera, -587.596, -389.758, 14.336); //расположение камеры	
										while (true)
										{
											WAIT( 0 );
											DISABLE_PAUSE_MENU(1);// отключаем главное меню
											SET_TEXT_COLOUR(109, 205, 255, 255); // задаём цвет текста
											SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
											SET_TEXT_EDGE(1, 0, 0, 0, 255); //
											SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
											SET_TEXT_CENTRE(1); // задаём центр текста
											DISPLAY_TEXT(0.5, 0.4, "CAR_AS1");//CAR SHOWROOM ASSET COMPLETED

											if (( TIMERA() > 5500 ) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
											{
												break;
											}
										}
									}
									else if (spisok == 2)
									{
										DO_SCREEN_FADE_OUT( 2500 );// Затемняем экран
										while (true)
										{
											if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
											{
												break;
											}
											WAIT( 0 );
										}

										INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
										INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
										G_GAME_PROGRESS += 1;
										SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
										uint CarM1 = MODEL_SABREGT;// Sabre Turbo
										REQUEST_MODEL(CarM1);
										while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
  										Car a1;
  										CREATE_CAR(CarM1, -580.991, -335.121, 7.66709, &car1, TRUE);
  										SET_CAR_HEADING(car1, -170.0);
										SET_VEHICLE_DIRT_LEVEL(car1, 0);
										MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
										MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
										cash = 3000;
										time_income = 960;
										G_BUSINES_SA = 3;
										autosave = 1;

										CREATE_CAM( 14, &camera );
										POINT_CAM_AT_COORD	( camera, -580.991,-335.121,7.66709 ); // куда смотрит камера
										SET_CAM_POS			( camera, -585.71,-330.921,8.26704 );//расположение камеры
										SET_CAM_ACTIVE( camera, 1 );
										SET_CAM_PROPAGATE( camera, 1 );
										ACTIVATE_SCRIPTED_CAMS(1, 1);
										SET_WIDESCREEN_BORDERS( 1 );
										SETTIMERA(0);

										DO_SCREEN_FADE_IN( 2500 );// убирается затемнение экрана

										while (true)
										{
											WAIT( 0 );
											DISABLE_PAUSE_MENU(1);// отключаем главное меню
											SET_TEXT_COLOUR(109, 205, 255, 255); // задаём цвет текста
											SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
											SET_TEXT_EDGE(1, 0, 0, 0, 255); //
											SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
											SET_TEXT_CENTRE(1); // задаём центр текста
											DISPLAY_TEXT(0.5, 0.4, "NECAR_SA7");//All the cars. NICE! Here's a little something.
											if (( TIMERA() > 4000 ) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
											{
												break;
											}
										}

										POINT_CAM_AT_COORD	( camera, -580.991,-335.121,7.66709); // куда смотрит камера
										SET_CAM_POS			( camera, -584.233,-341.182,8.18265); //расположение камеры
										SetTime(4000);

										DO_SCREEN_FADE_OUT( 1500 );// Затемняем экран
										while (true)
										{
											WAIT( 0 );
											if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
											{
												break;
											}
										}
										DO_SCREEN_FADE_IN( 2500 );// убирается затемнение экрана
									}
									else if (spisok == 3)
									{
										DO_SCREEN_FADE_OUT( 2500 );// Затемняем экран
										while (true)
										{
											if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
											{
												break;
											}
											WAIT( 0 );
										}

										INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
										INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
										G_GAME_PROGRESS += 1;
										SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
										uint CarM1 = MODEL_CAVALCADE;// Sandking
										REQUEST_MODEL(CarM1);
										while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
  										Car a1;
  										CREATE_CAR(CarM1, -580.991, -335.121, 12.5935, &car1, TRUE);
  										SET_CAR_HEADING(car1, -170.0);
										SET_VEHICLE_DIRT_LEVEL(car1, 0);
										MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
										MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
										cash = 6000;
										time_income = 480;
										G_BUSINES_SA = 4;
										autosave = 1;

										CREATE_CAM( 14, &camera );
										POINT_CAM_AT_COORD	( camera, -580.991, -335.121, 12.5935 ); // куда смотрит камера
										SET_CAM_POS			( camera, -584.981,-331.353,13.1934 );//расположение камеры
										SET_CAM_ACTIVE( camera, 1 );
										SET_CAM_PROPAGATE( camera, 1 );
										ACTIVATE_SCRIPTED_CAMS(1, 1);
										SET_WIDESCREEN_BORDERS( 1 );
										SETTIMERA(0);

										DO_SCREEN_FADE_IN( 2500 );// убирается затемнение экрана

										while (true)
										{
											WAIT( 0 );
											DISABLE_PAUSE_MENU(1);// отключаем главное меню
											SET_TEXT_COLOUR(109, 205, 255, 255); // задаём цвет текста
											SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
											SET_TEXT_EDGE(1, 0, 0, 0, 255); //
											SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
											SET_TEXT_CENTRE(1); // задаём центр текста
											DISPLAY_TEXT(0.5, 0.4, "NECAR_SA7");//All the cars. NICE! Here's a little something.
											if (( TIMERA() > 4000 ) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
											{
												break;
											}
										}

										POINT_CAM_AT_COORD	( camera, -580.991, -335.121, 12.5935); // куда смотрит камера
										SET_CAM_POS			( camera, -583.154,-340.068,13.109); //расположение камеры
										SetTime(4000);

										DO_SCREEN_FADE_OUT( 1500 );// Затемняем экран
										while (true)
										{
											WAIT( 0 );
											if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
											{
												break;
											}
										}
										DO_SCREEN_FADE_IN( 2500 );// убирается затемнение экрана
									}
									else if (spisok == 4)
									{
										DO_SCREEN_FADE_OUT( 2500 );// Затемняем экран
										while (true)
										{
											if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
											{
												break;
											}
											WAIT( 0 );
										}

										INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
										INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
										G_GAME_PROGRESS += 1;
										SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
										uint CarM1 = MODEL_FELTZER;// Hotring Racer
										REQUEST_MODEL(CarM1);
										while (!HAS_MODEL_LOADED(CarM1)) WAIT(100);
  										Car a1;
  										CREATE_CAR(CarM1, -589.355, -333.968, 12.5935, &car1, TRUE);
  										SET_CAR_HEADING(car1, 160.0);
										SET_VEHICLE_DIRT_LEVEL(car1, 0);
										MARK_MODEL_AS_NO_LONGER_NEEDED(CarM1);
										MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
										cash = 9000;
										time_income = 320;
										G_BUSINES_SA = 5;
										autosave = 1;

										CREATE_CAM( 14, &camera );
										POINT_CAM_AT_COORD	( camera, -589.355,-333.968,12.5935 ); // куда смотрит камера
										SET_CAM_POS			( camera, -583.815,-331.098,13.6728 );//расположение камеры
										SET_CAM_ACTIVE( camera, 1 );
										SET_CAM_PROPAGATE( camera, 1 );
										ACTIVATE_SCRIPTED_CAMS(1, 1);
										SET_WIDESCREEN_BORDERS( 1 );
										SETTIMERA(0);

										DO_SCREEN_FADE_IN( 2500 );// убирается затемнение экрана

										while (true)
										{
											WAIT( 0 );
											DISABLE_PAUSE_MENU(1);// отключаем главное меню
											SET_TEXT_COLOUR(109, 205, 255, 255); // задаём цвет текста
											SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
											SET_TEXT_EDGE(1, 0, 0, 0, 255); //
											SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
											SET_TEXT_CENTRE(1); // задаём центр текста
											DISPLAY_TEXT(0.5, 0.4, "NECAR_SA7");//All the cars. NICE! Here's a little something.
											if (( TIMERA() > 4000 ) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
											{
												break;
											}
										}

										POINT_CAM_AT_COORD	( camera, -589.355,-333.968,12.5935); // куда смотрит камера
										SET_CAM_POS			( camera, -587.284,-340.629,13.3116); //расположение камеры
										SetTime(4000);

										DO_SCREEN_FADE_OUT( 1500 );// Затемняем экран
										while (true)
										{
											WAIT( 0 );
											if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
											{
												break;
											}
										}
										DO_SCREEN_FADE_IN( 2500 );// убирается затемнение экрана
									}


									// камера на счёную машинку
									POINT_CAM_AT_COORD	( camera, -603.847, -312.336, 8.01287); // куда смотрит камера
									SET_CAM_POS			( camera, -605.552, -312.669, 9.08054); //расположение камеры
									PRINT_WITH_NUMBER("CAR_AS2", cash, 5500, 1);//~g~Sunshine Auto's will now generate revenue up to a maximum of $~1~. Make sure you collect it regularly.
									
									//МАШИНКА СЧЁТКА ДЕНЕГ
									SETTIMERA(0); //сбрасываем таймер 
									SETTIMERB(0); //сбрасываем таймер

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
									//WAIT( 100 );
									//SET_TEXT_RENDER_ID(rId92);
									//DRAW_RECT(0.5, 0.5, 1.0, 1.0, 0, 0, 0, 255);
									//*/

									DO_SCREEN_FADE_OUT( 2500 );// Затемняем экран
									while (true)
									{
										if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
										{
											break;
										}
										WAIT( 0 );
									}
									SET_CAM_BEHIND_PED( GetPlayerPed() );
									ACTIVATE_SCRIPTED_CAMS( 0, 0 );
									END_CAM_COMMANDS( &camera );
									SET_WIDESCREEN_BORDERS( 0 );
									DO_SCREEN_FADE_IN( 2500 );// убирается затемнение экрана
									ADD_SCORE( GetPlayerIndex(), +2000 );//  даём игроку сумму
									INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 2000);

									if (spisok < 4)
									{
										s_car_1 = 0;
										s_car_2 = 0;
										s_car_3 = 0;
										s_car_4 = 0;
										s_car_5 = 0;
										s_car_6 = 0;
									}
									spisok += 1;
								}
								
								SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// Размораживаем игрока
								ADD_SCORE( GetPlayerIndex(), +500 );//  даём игроку сумму
								INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 500);
								in_model = 0;
								spisok_on = 0;
								G_ONMISSION = 0;
								break;
							}
							else if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), -531.837, -329.17, -0.405, -548.592, -293.09, 7.193, 0 ))
							{
								G_ONMISSION = 0;
								CLOSE_GARAGE("ab_auto");
								while (true)
								{
									WAIT(0);
									if (IS_GARAGE_CLOSED("ab_auto"))
									{
										break;
									}
								}
								CLEAR_HELP(); // удаляем текст подсказки
								MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
								in_model = 0;
								text = 0;
								text2 = 0;
								break;
							}
						}
					}
				}
			}
		}
		else
		{
			if (text == 1)
			{
				CLEAR_HELP(); // удаляем текст подсказки
				text = 0;
				text2 = 0;
			}
		}
		if (G_BUSINES_SA > 1)
		{
			if ( TIMERC() > time_income)// время фарма
			{
				if (income < cash)// максимальный доход
				{
					income +=1;
				}
				SETTIMERC(0); //сбрасываем таймер 
			}
			if (G_COLLECTOR == 2)// ID Бизнеса
			{
				income = 0;
				G_COLLECTOR = 0;
			}

			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -600.648, -317.064, 5.527, -607.148, -309.064, 11.001, 0 ))
			{
				if (load_mashin == 0)
				{
					GET_SCRIPT_RENDERTARGET_RENDER_ID(&rId92);
					load_mashin = 1;
				}
				SET_TEXT_RENDER_ID(rId92);
				DRAW_SPRITE( 0, 0.5000000, 0.50000000, 1.00000000, 1.00000000, 0.00000000, 0, 0, 0, 255 );
				SET_TEXT_SCALE(4.0, 14.5);
				SET_TEXT_DROPSHADOW(45, 45, 45, 255, 0);
				SET_TEXT_COLOUR(51, 184, 18, 255);
				SET_TEXT_FONT(1);
				DISPLAY_TEXT_WITH_NUMBER(0.005, 0.005, "CASH", income);//пишем сумму из переменной
				if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -602.26, -314.467, -606.067, -310.806, 0))
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
					SET_TEXT_RENDER_ID(rId92);
					DRAW_RECT(0.5, 0.5, 1.0, 1.0, 35, 35, 35, 255);
					load_mashin = 0;
					help = 0;
				}
			}
		}

		// ----- Визуализация списков транспорта -----
		if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -509.54, -339.738, -4.0, -564.54, -284.738, 21.0, 0 ))//если игрок на кординатах
		{
			if (spisok_on == 0)
			{
				spisok_on = 1;
				textur1 = LOAD_TXD( "car_spisok" );
				fon_spiska = GET_TEXTURE( textur1, "fon_spiska" );
				polosa_spiska = GET_TEXTURE( textur1, "line" );
				GET_SCRIPT_RENDERTARGET_RENDER_ID(&rId9);
				SET_TEXT_RENDER_ID(rId9);
				DRAW_SPRITE( fon_spiska, 0.5000000, 0.50000000, 1.00000000, 1.00000000, 0.00000000, 255, 255, 255, 255 );

				if (G_BUSINES_SA >= 1)
				{
					// текст "Требуются машины"
					SET_TEXT_SCALE(1.3, 1.3);
					SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
					SET_TEXT_CENTRE(1);
					DISPLAY_TEXT(0.500, 0.0325, "NECAR_SA4"); //VEHICLES WANTED:

					// текст "Награда гарантирована"
					SET_TEXT_SCALE(1.3, 1.3);
					SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
					SET_TEXT_CENTRE(1);
					DISPLAY_TEXT(0.500, 0.860, "NECAR_SA5");//REWARDS OFFERED.

					if (s_car_1 == 1)
					{
						DRAW_SPRITE( polosa_spiska, 0.5000000, 0.21, 1.00000000, -0.1000000, 0.00000000, 255, 255, 255, 255 );
					}
					if (s_car_2 == 1)
					{
						DRAW_SPRITE( polosa_spiska, 0.5000000, 0.32, -1.00000000, 0.1000000, 0.00000000, 255, 255, 255, 255 );
					}
					if (s_car_3 == 1)
					{
						DRAW_SPRITE( polosa_spiska, 0.5000000, 0.43, 1.00000000, 0.1000000, 0.00000000, 255, 255, 255, 255 );
					}
					if (s_car_4 == 1)
					{
						DRAW_SPRITE( polosa_spiska, 0.5000000, 0.54, -1.00000000, -0.1000000, 0.00000000, 255, 255, 255, 255 );
					}
					if (s_car_5 == 1)
					{
						DRAW_SPRITE( polosa_spiska, 0.5000000, 0.65, 1.00000000, -0.1000000, 0.00000000, 255, 255, 255, 255 );
					}
					if (s_car_6 == 1)
					{
						DRAW_SPRITE( polosa_spiska, 0.5000000, 0.76, -1.00000000, 0.1000000, 0.00000000, 255, 255, 255, 255 );
					}

					if (spisok == 1)
					{
						if (s_car_1 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.16, "LANSTALK");
						}
						if (s_car_2 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.27, "EMPEROR");
						}
						if (s_car_3 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.38, "ESPERNTO");
						}
						if (s_car_4 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.49, "STALION");
						}
						if (s_car_5 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.6, "CAVCADE");
						}
						if (s_car_6 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.71, "BLISTA");
						}
					}
					else if (spisok == 2)
					{
						if (s_car_1 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.16, "SABRE");
						}
						if (s_car_2 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.27, "VIRGO");
						}
						if (s_car_3 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.38, "SENTI");
						}
						if (s_car_4 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.49, "STRETCH");
						}
						if (s_car_5 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.6, "WASHINGT");
						}
						if (s_car_6 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.71, "ADMIRAL");
						}
					}
					else if (spisok == 3)
					{
						if (s_car_1 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.16, "SUPER");
						}
						if (s_car_2 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.27, "INFERNUS");
						}
						if (s_car_3 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.38, "RUINER");
						}
						if (s_car_4 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.49, "DUKES");
						}
						if (s_car_5 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.6, "COMET");
						}
						if (s_car_6 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.71, "COQUETTE");
						}
					}
					else if (spisok == 4)
					{
						if (s_car_1 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.16, "VOODOO");
						}
						if (s_car_2 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.27, "BANSHEE");
						}
						if (s_car_3 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.38, "CADDY");
						}
						if (s_car_4 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.49, "AIRTUG");
						}
						if (s_car_5 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.6, "MRTASTY");
						}
						if (s_car_6 == 0)
						{
							SET_TEXT_SCALE(1.6, 1.6);
							SET_TEXT_DROPSHADOW(255, 255, 255, 255, 0);
							SET_TEXT_CENTRE(1);
							DISPLAY_TEXT(0.500, 0.71, "PIZBOY");
						}
					}
				}
			}
		}
		else
		{
			if (spisok_on == 1)
			{
				GET_SCRIPT_RENDERTARGET_RENDER_ID(&rId9);
				SET_TEXT_RENDER_ID(rId9);
				DRAW_RECT(0.5, 0.5, 1.0, 1.0, 35, 35, 35, 255);

				RELEASE_TEXTURE( fon_spiska );
				RELEASE_TEXTURE( polosa_spiska );
				REMOVE_TXD( textur1 );
				spisok_on = 0;
			}
		}
	}
}
void main(void)
{
	THIS_SCRIPT_SHOULD_BE_SAVED();
	Sunshine();
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
