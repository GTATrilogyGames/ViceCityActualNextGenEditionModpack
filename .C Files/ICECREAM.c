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
float temp, prodano, speed, klient, zon_on, textur, help_text, PlayX, PlayY, PlayZ, PlayX2, PlayY2, PlayZ2, PlayR, autosave;
float x, x2, y, y2, PedX, PedY, PedZ, BortLX, BortLY, BortRX, BortRY, PedR1, PedR2, PedR3, skip, blip_on;
int income, load_mashin, help;

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
void whoopee(void)
{
	blip_on = 0;
	autosave = 0;
	Cam camera;
	Blip ice_ico;
	help_text = 0;
	temp = 0;
	load_mashin = 0;
	help = 0;
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
//============================== Distribution ======================================
		if ((G_ONMISSION == 0) && (G_ICECREAM > 0))
		{
			if (blip_on == 0)
			{
				ADD_BLIP_FOR_COORD(-443.132, -37.314, 5.065, &ice_ico);//создаем иконку на радаре
				CHANGE_BLIP_SPRITE(ice_ico, BLIP_BAR);//текстура иконки на радаре
				CHANGE_BLIP_SCALE(ice_ico, 1.1); // масштаб иконки на радаре
				SET_BLIP_AS_SHORT_RANGE(ice_ico, 1); // иконка пропадает если не в зоне радардиска
				CHANGE_BLIP_NAME_FROM_TEXT_FILE(ice_ico, "LG_17");//иконка на радаре называние в истории карты ""
				blip_on = 1;
			}
			if (IS_CHAR_IN_MODEL(GetPlayerPed(), MODEL_MRTASTY))//проверка игрок в определённой машине (MR TASTY)
			{
				
				if ((IS_CHAR_IN_AREA_3D( GetPlayerPed(), -423.987, -41.119, 4.062, -434.088, -33.443, 9.312, 0 )) && (temp == 0))//проверка игрок в зоне объяснения как работает миссия(при первом входе в автомобиль).
				{
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замараживаем игрока
					CREATE_CAM( 14, &camera );
					POINT_CAM_AT_COORD	( camera, -429.169, -37.004, 6.227 ); // куда смотрит камера
					SET_CAM_POS			( camera, -420.103, -41.6, 10.022 );//расположение камеры
					SET_CAM_ACTIVE( camera, 1 );
					SET_CAM_PROPAGATE( camera, 1 );
					ACTIVATE_SCRIPTED_CAMS(1, 1);
					SET_WIDESCREEN_BORDERS( 1 );
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP_FOREVER("ICC1_7"); //~g~You receive money for each transaction you make, but the more transactions you make the more police attention you get.
					SetTime(3500);
					
					POINT_CAM_AT_COORD	( camera, -429.169, -37.004, 6.227 ); // куда смотрит камера
					SET_CAM_POS			( camera, -420.103, -41.6, 10.022 );//расположение камеры
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP_FOREVER("ICC1_9"); //~g~Local gangs will not appreciate you doing business on their turf so expect hostility if you do so.
					SetTime(3500);

					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// Размораживаем игрока
					SET_CAM_BEHIND_PED( GetPlayerPed() );
					ACTIVATE_SCRIPTED_CAMS( 0, 0 );
					END_CAM_COMMANDS( &camera );
					SET_WIDESCREEN_BORDERS( 0 );
					temp = 1;
				}
				if (help_text == 0)
				{
					CLEAR_HELP(); // удаляем текст подсказки
					PRINT_HELP("ICC1_8"); //To make a transaction,park your van and press the ~PAD_LB~ button to play the ice cream jingle to attract customers.
					help_text = 1;
					temp = 1;
				}
				if (((IS_CONTROL_PRESSED( 2, 23 )) && (! IS_USING_CONTROLLER()) && (G_ICECREAM > 0) && (G_ONMISSION == 0)) || ((IS_BUTTON_PRESSED( 0, 4 )) && (IS_USING_CONTROLLER()) && (G_ICECREAM > 0) && (G_ONMISSION == 0)))
				{
					CLEAR_HELP(); // удаляем текст подсказки
					G_ONMISSION = 1;
					INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
					REMOVE_BLIP(ice_ico);//Удаляем иконку на радаре
					skip = 0;

					Car car1;
					uint all_klient, ped_type, addstar;
					Texture ice, fon;
					Ped ped1;
					prodano = 0;
					help_text = 0;
					addstar = 0;
					x = 1.35;
					y = 1;
					x2 = -1.35;
					y2 = -1;
					klient = 0;
					zon_on = 0;
					blip_on = 0;
					
					GET_CAR_CHAR_IS_USING(GetPlayerPed(), &car1);
					SWITCH_CAR_SIREN(car1, 1);
					GENERATE_RANDOM_INT_IN_RANGE( 1, 7, &all_klient);
					GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную

					REQUEST_ANIMS( "amb@atm" );//загружаем файл с анимацией
					while (!HAVE_ANIMS_LOADED( "amb@atm" )) WAIT(0);

					textur = LOAD_TXD( "sunshine_race" );
					fon = GET_TEXTURE( textur, "fon_hud" );
					ice = GET_TEXTURE( textur, "ice_hud" );
					PRINT_BIG("CREAM", 5000, 2);//Distribution

					while (TRUE)
					{
						WAIT(0);
						GET_CAR_SPEED(car1, &speed);

						// худ
						DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
						DRAW_SPRITE( ice, 0.8435625, 0.80925926, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.156, 0.267);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						DISPLAY_TEXT(0.80729167, 0.80277778, "ICC1_5"); //DEALS DONE:

						SET_TEXT_COLOUR(95, 195, 247, 255);
						SET_TEXT_SCALE(0.26, 0.445);
						SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
						SET_TEXT_CENTRE(1);
						if ((prodano > 9) && (prodano < 100))
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.795, "CP_TIME_NOZERO", prodano);// 
						}
						else if ((prodano > 100) || (prodano == 100))
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9307292, 0.795, "CP_TIME_NOZERO", prodano);// 
						}
						else
						{
							DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.795, "CP_TIME_ZERO", prodano);// 
						}
						//==============сама миссия==============
						if (!IS_CHAR_IN_AREA_3D( GetPlayerPed(), (PlayX+100), (PlayY+100), (PlayZ+100), (PlayX-100), (PlayY-100), (PlayZ-100), 0 ))
						{
							if (speed < 8)
							{
								klient = 0;
								GENERATE_RANDOM_INT_IN_RANGE( 1, 7, &all_klient);
								GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
							}
						}
						else
						{
							if (speed < 2)
							{
								if (klient < all_klient)
								{
									GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX2, &PlayY2, &PlayZ2);//вписываем координаты игрока в переменную
									GET_RANDOM_CHAR_IN_AREA_OFFSET_NO_SAVE(PlayX2, PlayY2, PlayZ2, 15.0, 15.0, 5.0, &ped1);
									if (ped1 != FALSE)
									{
										GET_PED_TYPE(ped1, &ped_type);
										GENERATE_RANDOM_INT_IN_RANGE( 1, 3, &addstar);
										if (ped_type == PED_TYPE_COP)
										{
											ALTER_WANTED_LEVEL(GetPlayerIndex(), 2);
											APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex()); // возможно нужно удалить не проверенная функция
											ped1 = FALSE;
										}
										else if ((ped_type == PED_TYPE_GANG_PUERTO_RICAN) || (ped_type == PED_TYPE_GANG_CHINESE_JAPANESE) || (ped_type == PED_TYPE_GANG_KOREAN) || (ped_type == PED_TYPE_GANG_AFRICAN_AMERICAN) || (ped_type == PED_TYPE_GANG_JAMAICAN) || (ped_type == PED_TYPE_GANG_IRISH_GANG) || (ped_type == PED_TYPE_GANG_RUSSIAN_GANG))
										{
											SET_CHAR_KEEP_TASK(ped1, 1);
											TASK_COMBAT(ped1, GetPlayerPed());
											SET_CHAR_WILL_USE_CARS_IN_COMBAT(ped1, 1);
											ped1 = FALSE;
										}
										else
										{
											GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX2, &PlayY2, &PlayZ2);//вписываем координаты игрока в переменную
											if (!IS_CHAR_IN_AREA_3D( ped1, (PlayX2+7), (PlayY2+7), (PlayZ2+7), (PlayX2-7), (PlayY2-7), (PlayZ2-7), 0 ))
											{
												klient += 1;
												if ((klient > 2) && (addstar == 2))
												{
													ALTER_WANTED_LEVEL(GetPlayerIndex(), 1);
													APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex()); // возможно нужно удалить не проверенная функция
													addstar = 1;
												}
												ADD_BLIP_FOR_CHAR(ped1, &ice_ico);
												CHANGE_BLIP_SPRITE(ice_ico, BLIP_DESTINATION);//иконка на радаре
												CHANGE_BLIP_COLOUR(ice_ico, 5);   //цвет иконкb на радаре
												CHANGE_BLIP_NAME_FROM_TEXT_FILE(ice_ico, "NE_ICE1");//иконка на радаре называние в истории карты
												CHANGE_BLIP_SCALE(ice_ico, 0.77999990); // масштаб иконки на радаре

												GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX2, &PlayY2, &PlayZ2);//вписываем координаты игрока в переменную
												GET_CHAR_HEADING(GetPlayerPed(), &PlayR);

												BortLX = (x*COS(PlayR+35)+y*SIN(PlayR+35))+PlayX2; // x- координата r- угол поворота
												BortLY = (y*SIN(PlayR+35)-x*COS(PlayR+35))+PlayY2; // y- координата r- угол поворота

												BortRX = ((x2*COS(PlayR+45))+y2*SIN(PlayR+45))+PlayX2; // x- координата r- угол поворота
												BortRY = (y2*SIN(PlayR+45)-(x2*COS(PlayR+45)))+PlayY2; // y- координата r- угол поворота

												GET_CHAR_COORDINATES(ped1, &PedX, &PedY, &PedZ);//вписываем координаты педа в переменную
												GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, BortLX, BortLY, PlayZ2, &PedR1);//проверка "игрок на координатах"
												GET_DISTANCE_BETWEEN_COORDS_3D( PedX, PedY, PedZ, BortRX, BortRY, PlayZ2, &PedR2);//проверка "игрок на координатах"

												if (PedR1 < PedR2)
												{
													TASK_GO_STRAIGHT_TO_COORD(ped1, BortLX, BortLY, PlayZ2, 4, -1);//заставляем педа идти к машине
													PedR3 = 1;
												}
												else
												{
													TASK_GO_STRAIGHT_TO_COORD(ped1, BortRX, BortRY, PlayZ2, 4, -1);//заставляем педа идти к машине
													PedR3 = 2;
												}

												
												while (true)
												{
													WAIT( 0 );
													GET_CAR_SPEED(car1, &speed);
													DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
													DRAW_SPRITE( ice, 0.8435625, 0.80925926, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.

													SET_TEXT_COLOUR(95, 195, 247, 255);
													SET_TEXT_SCALE(0.156, 0.267);
													SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
													DISPLAY_TEXT(0.80729167, 0.80277778, "ICC1_5"); //DEALS DONE:

													SET_TEXT_COLOUR(95, 195, 247, 255);
													SET_TEXT_SCALE(0.26, 0.445);
													SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
													SET_TEXT_CENTRE(1);
													if ((prodano > 9) && (prodano < 100))
													{
														DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.795, "CP_TIME_NOZERO", prodano);// 
													}
													else if ((prodano > 100) || (prodano == 100))
													{
														DISPLAY_TEXT_WITH_NUMBER(0.9307292, 0.795, "CP_TIME_NOZERO", prodano);// 
													}
													else
													{
														DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.795, "CP_TIME_ZERO", prodano);// 
													}
													if (speed > 2)
													{
														ped1 = FALSE;
														REMOVE_BLIP(ice_ico);//Удаляем иконку на радаре
														break;
													}
													else if (IS_CHAR_DEAD(ped1))
													{
														ped1 = FALSE;
														REMOVE_BLIP(ice_ico);//Удаляем иконку на радаре
														break;
													}
													else if (IS_CHAR_FATALLY_INJURED(ped1))
													{
														ped1 = FALSE;
														REMOVE_BLIP(ice_ico);//Удаляем иконку на радаре
														break;
													}
													else if (IS_CHAR_INJURED(ped1))
													{
														ped1 = FALSE;
														REMOVE_BLIP(ice_ico);//Удаляем иконку на радаре
														break;
													}
													else if ((IS_CHAR_IN_AREA_3D( ped1, (BortLX+0.8), (BortLY+0.8), (PlayZ2+2), (BortLX-0.8), (BortLY-0.8), (PlayZ2-3), 0 )) || (IS_CHAR_IN_AREA_3D( ped1, (BortRX+0.8), (BortRY+0.8), (PlayZ2+2), (BortRX-0.8), (BortRY-0.8), (PlayZ2-3), 0 )))
													{
														//поворачиваем педа на автомобиль
														if (PedR3 == 1)
														{
															SET_CHAR_HEADING(ped1, PlayR+90);
														}
														else if (PedR3 == 2)
														{
															SET_CHAR_HEADING(ped1, PlayR-90);
														}
														//проигрываем анимацию
														TASK_PLAY_ANIM_NON_INTERRUPTABLE( ped1, "m_insertcard", "amb@atm", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
														SETTIMERA(0);
														while (true)
														{
															WAIT( 0 );
															DRAW_SPRITE( fon, 0.8765625, 0.80925926, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155 );// рисуем фоновую текстуру.
															DRAW_SPRITE( ice, 0.8435625, 0.80925926, 0.14322917, 0.0592, 0.0, 255, 255, 255, 255 );// рисуем фоновую текстуру.

															SET_TEXT_COLOUR(95, 195, 247, 255);
															SET_TEXT_SCALE(0.156, 0.267);
															SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
															DISPLAY_TEXT(0.80729167, 0.80277778, "ICC1_5"); //DEALS DONE:

															SET_TEXT_COLOUR(95, 195, 247, 255);
															SET_TEXT_SCALE(0.26, 0.445);
															SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
															SET_TEXT_CENTRE(1);
															if ((prodano > 9) && (prodano < 100))
															{
																DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.795, "CP_TIME_NOZERO", prodano);// 
															}
															else if ((prodano > 100) || (prodano == 100))
															{
																DISPLAY_TEXT_WITH_NUMBER(0.9307292, 0.795, "CP_TIME_NOZERO", prodano);// 
															}
															else
															{
																DISPLAY_TEXT_WITH_NUMBER(0.9348959, 0.795, "CP_TIME_ZERO", prodano);// 
															}
															if ( TIMERA() > 2000 )
															{
																break;
															}
														}
														ADD_SCORE( GetPlayerIndex(), +20 );//даём игроку денег
														INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 20);
														prodano += 1;//добавляем количество проданых порций
														ped1 = FALSE;
														REMOVE_BLIP(ice_ico);//Удаляем иконку на радаре
														break;
													}
												}
											}
											else
											{
												ped1 = FALSE;
											}
										}
									}
								}
								else
								{
									if (zon_on == 0)
									{
										PRINT_STRING_IN_STRING("string", "ICC1_4", 5000, 1);//~g~There aren't any customers in this area try another one.
										zon_on = 1;
									}
								}
							}
							else
							{
								zon_on = 0;
								if (ped1 != FALSE)
								{
									ped1 = FALSE;
									REMOVE_BLIP(ice_ico);//Удаляем иконку на радаре
								}
							}
						}

						//прохождение/провал
						if ((!IS_CAR_SIREN_ON(car1)) || (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
						{
							if ((prodano >= 50) && (!HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())) && (!IS_CHAR_DEAD(GetPlayerPed())))
							{
								skip = 2;
								break;
							}
							else if (prodano < 50)
							{
								skip = 3;
								break;
							}
						}
						else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
						{
							skip = 1;
							break;
						}
					}


					// чистим скрипт тут
					WAIT(100);
					REMOVE_BLIP(ice_ico);//Удаляем иконку на радаре
					MARK_CAR_AS_NO_LONGER_NEEDED(&car1);
					if (ped1 != FALSE)
					{
						ped1 = FALSE;
					}

					RELEASE_TEXTURE( fon );
					RELEASE_TEXTURE( ice );
					REMOVE_TXD( textur );
					help_text = 0;

					if (skip == 2)
					{
						if (G_ICECREAM == 1)
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
							CREATE_CAM( 14, &camera );
							POINT_CAM_AT_COORD	( camera, -504.002, -10.755, 6.353 ); // куда смотрит камера
							SET_CAM_POS			( camera, -399.236, -60.687, 18.444 );//расположение камеры
							SET_CAM_ACTIVE( camera, 1 );
							SET_CAM_PROPAGATE( camera, 1 );
							ACTIVATE_SCRIPTED_CAMS(1, 1);
							SET_CAM_FOV( camera, 45.0 );
							SET_WIDESCREEN_BORDERS( 1 );
							SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замораживаем игрока
							DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана

							SETTIMERA(0); //сбрасываем таймер 
							while (true)
							{
								SET_TEXT_COLOUR(93, 200, 252, 255); // задаём цвет текста
								SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
								SET_TEXT_EDGE(1, 0, 0, 0, 255); //
								SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
								SET_TEXT_CENTRE(1); // задаём центр текста
								DISPLAY_TEXT(0.5, 0.45, "ICE_AT1");//ICECREAM FACTORY ASSET COMPLETED
								WAIT( 0 );
								if ( TIMERA() > 5000 )
								{
									break;
								}
							}

							// меняем ракурс
							POINT_CAM_AT_COORD	( camera, -450.462, -41.6111, 6.268 ); // куда смотрит камера
							SET_CAM_POS			( camera, -448.533, -43.4632, 7.208 ); // расположение камеры
							PRINT_STRING_IN_STRING("string", "ICE_AT2", 5000, 1);//~g~The Cherry Popper factory will now generate revenue up to a maximum of $3000. Make sure you collect it regularly.

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
							G_ICECREAM = 2;
							autosave = 1;

							SETTIMERA(0); //сбрасываем таймер 
							REGISTER_MISSION_PASSED( "S_CREAM" );//Distribution
							INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
							G_GAME_PROGRESS += 1;
							SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
							play_mission_complete_tune();
							MissionPassed(prodano, "missionpassed", "ICC1_19");
						}
						else
						{
							SETTIMERA(0); //сбрасываем таймер 
							while (true)
							{
								SET_TEXT_FONT(0);
								SET_TEXT_COLOUR(109, 205, 255, 255); // задаём цвет текста
								SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
								SET_TEXT_EDGE(1, 0, 0, 0, 255); //
								SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
								SET_TEXT_CENTRE(1); // задаём центр текста
								DISPLAY_TEXT_WITH_NUMBER(0.500, 0.500, "ICC1_19", prodano);//Total deals done: ~1~
								
								WAIT( 0 );
								if ( TIMERA() > 4000 )
								{
									break;
								}
							}
						}
					}
					else if (skip == 3)
					{
						SETTIMERA(0); //сбрасываем таймер 
						while (true)
						{
							SET_TEXT_FONT(0);
							SET_TEXT_COLOUR(109, 205, 255, 255); // задаём цвет текста
							SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
							SET_TEXT_EDGE(1, 0, 0, 0, 255); //
							SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
							SET_TEXT_CENTRE(1); // задаём центр текста
							DISPLAY_TEXT_WITH_NUMBER(0.500, 0.500, "ICC1_19", prodano);//Total deals done: ~1~
							
							WAIT( 0 );
							if ( TIMERA() > 4000 )
							{
								break;
							}
						}
					}
					G_ONMISSION = 0;
				}
			}
			if ((!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())) && (help_text == 1))
			{
				CLEAR_HELP(); // удаляем текст подсказки
				WAIT(3000);
				help_text = 0;
			}
		}
		else
		{
			if (blip_on == 1)
			{
				REMOVE_BLIP(ice_ico);//Удаляем иконку на радаре
				blip_on = 0;
			}
		}
		if (G_ICECREAM == 2)
		{
			if ( TIMERC() > 960)// время фарма
			{
				if (income < 3000)// максимальный доход
				{
					income +=1;
				}
				SETTIMERC(0); //сбрасываем таймер 
			}
			if (G_COLLECTOR == 4)// ID Бизнеса
			{
				income = 0;
				G_COLLECTOR = 0;
			}

			if (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -447.051, -49.867, 4.979, -455.17, -33.733, 9.08, 0 ))
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
				if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -448.675, -43.593, -451.601, -41.288, 0))
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
	whoopee();
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
