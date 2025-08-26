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

float PlayX, PlayY, PlayZ, PlayR, set_race;
float textur, race_map, draw_map, help_wait, race_start, lap_all, add_money, best_time_m, best_time_s, spead_time, cam_x;
float timer_m_1, timer_s_1, timer_m_2, timer_s_2, timer_m_3, timer_s_3;
float timer_m_4, timer_s_4, timer_m_5, timer_s_5, timer_m_6, timer_s_6;
Texture map_fon;


void autosave()		/*rebusx*/
{
	DO_AUTO_SAVE();
	WAIT(500);
}


void start_race(void)
{
	float previous_cash = GET_FLOAT_STAT(STAT_MADE_FROM_MISSIONS);
	if (set_race == 1)
	{
		REQUEST_SCRIPT("sa_race1");
		while (!HAS_SCRIPT_LOADED("sa_race1")) WAIT(0);
		uint script = START_NEW_SCRIPT("sa_race1", 1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("sa_race1");
		while (IS_THREAD_ACTIVE(script)) WAIT(0);
	}
	else if (set_race == 2)
	{
		REQUEST_SCRIPT("sa_race2");
		while (!HAS_SCRIPT_LOADED("sa_race2")) WAIT(0);
		uint script = START_NEW_SCRIPT("sa_race2", 1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("sa_race2");
		while (IS_THREAD_ACTIVE(script)) WAIT(0);
	}
	else if (set_race == 3)
	{
		REQUEST_SCRIPT("sa_race3");
		while (!HAS_SCRIPT_LOADED("sa_race3")) WAIT(0);
		uint script = START_NEW_SCRIPT("sa_race3", 1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("sa_race3");
		while (IS_THREAD_ACTIVE(script)) WAIT(0);
	}
	else if (set_race == 4)
	{
		REQUEST_SCRIPT("sa_race4");
		while (!HAS_SCRIPT_LOADED("sa_race4")) WAIT(0);
		uint script = START_NEW_SCRIPT("sa_race4", 1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("sa_race4");
		while (IS_THREAD_ACTIVE(script)) WAIT(0);
	}
	else if (set_race == 5)
	{
		REQUEST_SCRIPT("sa_race5");
		while (!HAS_SCRIPT_LOADED("sa_race5")) WAIT(0);
		uint script = START_NEW_SCRIPT("sa_race5", 1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("sa_race5");
		while (IS_THREAD_ACTIVE(script)) WAIT(0);
	}
	else if (set_race == 6)
	{
		REQUEST_SCRIPT("sa_race6");
		while (!HAS_SCRIPT_LOADED("sa_race6")) WAIT(0);
		uint script = START_NEW_SCRIPT("sa_race6", 1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED("sa_race6");
		while (IS_THREAD_ACTIVE(script)) WAIT(0);
	}
	G_ONMISSION = 0;
	WAIT(1000);
	if (GET_FLOAT_STAT(STAT_MADE_FROM_MISSIONS) != previous_cash)
	{
		autosave();		/*rebusx*/
	}
}
void set_text_size(void)
{
	SET_TEXT_COLOUR(255, 255, 255, 255);
	SET_TEXT_SCALE(0.75, 1.3);
	SET_TEXT_EDGE(1, 1, 1, 1, 255);
	SET_TEXT_DROPSHADOW(0, 1, 1, 1, 255);
	SET_TEXT_CENTRE( 1 );
	return;
}
void race_launcher(void)
{
	int money_plaer;
	Object spript_map1, spript_map2, spript_map3, spript_map4, spript_map5, spript_map6;
	uint model_map1 = script_race_map1;
	uint model_map2 = script_race_map2;
	uint model_map3 = script_race_map3;
	uint model_map4 = script_race_map4;
	uint model_map5 = script_race_map5;
	uint model_map6 = script_race_map6;
	uint map_n, hour, min;
	uint rId9;
	Cam camera;
	Cam camera2;
	Cam camera3;
	timer_m_1 = 999;
	timer_s_1 = 90;
	timer_m_2 = 999;
	timer_s_2 = 90;
	timer_m_3 = 999;
	timer_s_3 = 90;
	timer_m_4 = 999;
	timer_s_4 = 90;
	timer_m_5 = 999;
	timer_s_5 = 90;
	timer_m_6 = 999;
	timer_s_6 = 90;
	while (true) 
	{
		WAIT(0);
		if ((G_ONMISSION == 0) && (G_BUSINES_SA >= 1))// 0-временно
		{
			DRAW_CHECKPOINT( -534.695, -294.287, 0.738626, 1.5, 160, 116, 209);//создание чекпойнт на координатах и его цвет
			GET_CHAR_COORDINATES(GetPlayerPed(),  &PlayX, &PlayY, &PlayZ);//вписываем координаты игрока в переменную
			GET_DISTANCE_BETWEEN_COORDS_3D( PlayX, PlayY, PlayZ, -534.695, -294.287, 0.738626, &PlayR);//проверка "игрок на координатах"
			if (( PlayR < 1.5) && (!IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				race_map = 1;
				draw_map = 1;
				help_wait = 2;
				race_start = 0;

				LOAD_ADDITIONAL_TEXT("TAXI1", 6);
				textur = LOAD_TXD( "sunshine_map" );
				map_fon = GET_TEXTURE( textur, "race_map" );

				REQUEST_MODEL(model_map1);
				REQUEST_MODEL(model_map2);
				REQUEST_MODEL(model_map3);
				REQUEST_MODEL(model_map4);
				REQUEST_MODEL(model_map5);
				REQUEST_MODEL(model_map6);
				while ((!HAS_MODEL_LOADED(model_map1)) || (!HAS_MODEL_LOADED(model_map2)) || (!HAS_MODEL_LOADED(model_map3)))WAIT(0);
				while ((!HAS_MODEL_LOADED(model_map4)) || (!HAS_MODEL_LOADED(model_map5)) || (!HAS_MODEL_LOADED(model_map6)))WAIT(0);

				CREATE_OBJECT_NO_OFFSET(model_map1, -532.551, -294.214, -0.63159, &spript_map1, TRUE);
				CREATE_OBJECT_NO_OFFSET(model_map2, -532.551, -294.214, -0.63159, &spript_map2, TRUE);
				CREATE_OBJECT_NO_OFFSET(model_map3, -532.551, -294.214, -0.63159, &spript_map3, TRUE);
				CREATE_OBJECT_NO_OFFSET(model_map4, -532.551, -294.214, -0.63159, &spript_map4, TRUE);
				CREATE_OBJECT_NO_OFFSET(model_map5, -532.551, -294.214, -0.63159, &spript_map5, TRUE);
				CREATE_OBJECT_NO_OFFSET(model_map6, -532.551, -294.214, -0.63159, &spript_map6, TRUE);

				GET_SCRIPT_RENDERTARGET_RENDER_ID(&rId9);
				SET_TEXT_RENDER_ID(rId9);
				DRAW_SPRITE( map_fon, 0.50000000, 0.50000000, 1.00000000, 1.00000000, 0.00000000, 255, 255, 255, 255 );

				CREATE_CAM( 14, &camera );
				SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 0, 0, 0 );//замараживаем игрока
				POINT_CAM_AT_COORD	( camera, -532.651, -294.214, 3.63159 ); // куда смотрит камера
				SET_CAM_POS			( camera, -535.251, -294.214, 3.63159 );//расположение камеры
				SET_CAM_ACTIVE( camera, 1 );
				SET_CAM_PROPAGATE( camera, 0 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);

				GET_GAME_CAM(&camera3);
				CREATE_CAM( 3, &camera2 );
				SET_CAM_INTERP_STYLE_DETAILED( camera2, 1, 1, 1, 1 );
				SET_CAM_INTERP_STYLE_CORE( camera2, camera3, camera, 500, 0 ); //перемещение камеры от игрока на точку указанную в координатах "SET_CAM_POS(camera, X, Y, Z)" 
				SET_CAM_ACTIVE( camera2, 1 );
				SET_CAM_PROPAGATE( camera2, 1 );
				ACTIVATE_SCRIPTED_CAMS(1, 1);

				SET_WIDESCREEN_BORDERS( 1 ); //отключаем инетрфейс
				SET_CHAR_COORDINATES(GetPlayerPed(), -590.215, -298.284, 1.57197);// убераем игрока из кадра

				while (true)
				{
					WAIT(0);
					if (help_wait == 1)
					{
						if (TIMERA() > 3000)
						{
							help_wait = 2;
						}
					}
					else if (help_wait == 2)
					{
						CLEAR_HELP(); // удаляем текст подсказки
						PRINT_HELP_FOREVER("VC2_RACE_HELP1"); // Тест подсказки "для выбора маршрута используйте клавиши (< и >) для продолжения нажмите ENTER для отмена нажмите BACKSPACE"*/
						help_wait = 0;
					}
					if ((IS_BUTTON_PRESSED( 0, 11 )) || (IS_GAME_KEYBOARD_NAV_RIGHT_PRESSED( 1 ))) //нажато вправо
					{
						SETTIMERA(0);
						while (true)
						{
							WAIT(0);
							if ((IS_BUTTON_PRESSED( 0, 11 )) || (IS_GAME_KEYBOARD_NAV_RIGHT_PRESSED( 1 ))) //нажато вправо
							{
								if (TIMERA() > 600)
								{
									break;
								}
							}
							else if ((!IS_BUTTON_PRESSED( 0, 11 )) || (!IS_GAME_KEYBOARD_NAV_RIGHT_PRESSED( 1 ))) //нажато вправо
							{
								break;
							}
						}
						if (race_map < 6)
						{
							race_map += 1;
							draw_map = 1;
						}
						else
						{
							race_map = 1;
							draw_map = 1;
						}
					}
					else if ((IS_BUTTON_PRESSED( 0, 10 )) || (IS_GAME_KEYBOARD_NAV_LEFT_PRESSED( 1 ))) //нажато влево
					{
						SETTIMERA(0);
						while (true)
						{
							WAIT(0);
							if ((IS_BUTTON_PRESSED( 0, 10 )) || (IS_GAME_KEYBOARD_NAV_LEFT_PRESSED( 1 ))) //нажато влево
							{
								if (TIMERA() > 600)
								{
									break;
								}
							}
							else if ((!IS_BUTTON_PRESSED( 0, 10 )) || (!IS_GAME_KEYBOARD_NAV_LEFT_PRESSED( 1 ))) //нажато влево
							{
								break;
							}
						}
						if (race_map > 1)
						{
							race_map -= 1;
							draw_map = 1;
						}
						else
						{
							race_map = 6;
							draw_map = 1;
						}
					}
					else if ((IS_BUTTON_PRESSED( 0, 17 )) || ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER()))) // BACKSPACE
					{
						break;
					}
					else if ((IS_BUTTON_PRESSED( 0, 16 )) || ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()))) //клавиатура ENTER
					{
						STORE_SCORE(GetPlayerIndex(), &money_plaer);// записываем средства игрока в переменную
						if ( money_plaer >= add_money )// проверяем хватает-дли средств
						{
							ADD_SCORE( GetPlayerIndex(), - (add_money));// отнимаем у игрока сумму
							race_start = 1;// активируем переменную старта гонки
							break;
						}
						else
						{
							if (help_wait == 0)
							{
								CLEAR_HELP(); // удаляем текст подсказки
								PRINT_HELP_FOREVER("VC2_RACE_HELP2"); // пишем недостаточно средств
								SETTIMERA(0);
								help_wait = 1;// переменная для активации таймера подсказки навигации
							}
						}
					}

					if (draw_map == 1)
					{
						draw_map = 0;
						SET_TEXT_RENDER_ID(rId9);
						if (race_map == 1)
						{
							SET_OBJECT_COORDINATES(spript_map1, -532.651, -294.214, 3.63159);
							SET_OBJECT_COORDINATES(spript_map2, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map3, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map4, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map5, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map6, -532.651, -294.214, -3.63159);

							set_race = 1;
							lap_all = 1;// количиства кругов
							add_money = 100;// сумма денежного взноса
							best_time_m = timer_m_1; //лучшее время минуты
							best_time_s = timer_s_1; //лучшее время секунды
						}
						else if (race_map == 2)
						{
							SET_OBJECT_COORDINATES(spript_map1, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map2, -532.651, -294.214, 3.63159);
							SET_OBJECT_COORDINATES(spript_map3, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map4, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map5, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map6, -532.651, -294.214, -3.63159);

							set_race = 2;
							lap_all = 1;// количиства кругов
							add_money = 500;// сумма денежного взноса
							best_time_m = timer_m_2; //лучшее время минуты
							best_time_s = timer_s_2; //лучшее время секунды
						}
						else if (race_map == 3)
						{
							SET_OBJECT_COORDINATES(spript_map1, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map2, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map3, -532.651, -294.214, 3.63159);
							SET_OBJECT_COORDINATES(spript_map4, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map5, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map6, -532.651, -294.214, -3.63159);

							set_race = 3;
							lap_all = 1;// количиства кругов
							add_money = 1000;// сумма денежного взноса
							best_time_m = timer_m_3; //лучшее время минуты
							best_time_s = timer_s_3; //лучшее время секунды
						}
						else if (race_map == 4)
						{
							SET_OBJECT_COORDINATES(spript_map1, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map2, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map3, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map4, -532.651, -294.214, 3.63159);
							SET_OBJECT_COORDINATES(spript_map5, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map6, -532.651, -294.214, -3.63159);

							set_race = 4;
							lap_all = 1;// количиства кругов
							add_money = 2000;// сумма денежного взноса
							best_time_m = timer_m_4; //лучшее время минуты
							best_time_s = timer_s_4; //лучшее время секунды
						}
						else if (race_map == 5)
						{
							SET_OBJECT_COORDINATES(spript_map1, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map2, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map3, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map4, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map5, -532.651, -294.214, 3.63159);
							SET_OBJECT_COORDINATES(spript_map6, -532.651, -294.214, -3.63159);

							set_race = 5;
							lap_all = 1;// количиства кругов
							add_money = 5000;// сумма денежного взноса
							best_time_m = timer_m_5; //лучшее время минуты
							best_time_s = timer_s_5; //лучшее время секунды
						}
						else if (race_map == 6)
						{
							SET_OBJECT_COORDINATES(spript_map1, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map2, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map3, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map4, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map5, -532.651, -294.214, -3.63159);
							SET_OBJECT_COORDINATES(spript_map6, -532.651, -294.214, 3.63159);

							set_race = 6;
							lap_all = 1;// количиства кругов
							add_money = 10000;// сумма денежного взноса
							best_time_m = timer_m_6; //лучшее время минуты
							best_time_s = timer_s_6; //лучшее время секунды
						}
						set_text_size();
						DISPLAY_TEXT_WITH_NUMBER(0.75097656, 0.01171875, "NE_SA_RACE1", race_map);// выводим текст номера гонки
						set_text_size();
						DISPLAY_TEXT_WITH_NUMBER(0.75097656, 0.13476562, "NE_SA_RACE2", lap_all);// выводим текст количиства кругов
						set_text_size();
						DISPLAY_TEXT_WITH_NUMBER(0.75097656, 0.25781249, "NE_SA_RACE3", add_money);// выводим текст денежного взноса

						/*/
						set_text_size();
						DISPLAY_TEXT(0.51269532, 0.38085936, "A_TMSG"); // текст "Лучшее время:"
						set_text_size();
						if (best_time_s == 90)
						{
							DISPLAY_TEXT(0.87402344, 0.38085936, "TAXNULL"); // текст "--:--:--"
						}
						else
						{
							if (best_time_m >= 10)
							{
								if (best_time_s >= 10)
								{
									DISPLAY_TEXT_WITH_2_NUMBERS(0.87402344, 0.38085936, "HOTR_T1", best_time_m, best_time_s);
								}
								else
								{
									DISPLAY_TEXT_WITH_2_NUMBERS(0.87402344, 0.38085936, "HOTR_T0", best_time_m, best_time_s);
								}
							}
							else
							{
								if (best_time_s >= 10)
								{
									DISPLAY_TEXT_WITH_2_NUMBERS(0.87402344, 0.38085936, "HOTR_T2", best_time_m, best_time_s);
								}
								else
								{
									DISPLAY_TEXT_WITH_2_NUMBERS(0.87402344, 0.38085936, "HOTR_T3", best_time_m, best_time_s);
								}
							}
						}
						//*/

						DRAW_SPRITE( map_fon, 0.50000000, 0.50000000, 1.00000000, 1.00000000, 0.00000000, 255, 255, 255, 255 );
					}
				}
				RELEASE_TEXTURE( map_fon );
				REMOVE_TXD( textur );

				CLEAR_HELP(); // удаляем текст подсказки
				SET_OBJECT_COORDINATES(spript_map1, -504.61, -287.35, -3.61); // прячем модель (фикс моргания модели чёрной заливкой)
				SET_OBJECT_COORDINATES(spript_map2, -504.61, -287.35, -3.61); // прячем модель (фикс моргания модели чёрной заливкой)
				SET_OBJECT_COORDINATES(spript_map3, -504.61, -287.35, -3.61); // прячем модель (фикс моргания модели чёрной заливкой)
				SET_OBJECT_COORDINATES(spript_map4, -504.61, -287.35, -3.61); // прячем модель (фикс моргания модели чёрной заливкой)
				SET_OBJECT_COORDINATES(spript_map5, -504.61, -287.35, -3.61); // прячем модель (фикс моргания модели чёрной заливкой)
				SET_OBJECT_COORDINATES(spript_map6, -504.61, -287.35, -3.61); // прячем модель (фикс моргания модели чёрной заливкой)
				SET_CHAR_COORDINATES(GetPlayerPed(), -590.215, -298.284, 1.57197);// убираем игрока из зоны
				WAIT(90);
				SET_CHAR_COORDINATES(GetPlayerPed(), -536.192, -295.507, 0.839274);// возвращаем игрока на исходную позицию рядом с чекпойнтом

				if (race_start == 0)
				{
					ACTIVATE_SCRIPTED_CAMS( 0, 0 );
					DESTROY_CAM( camera );
					DESTROY_CAM( camera2 );
					SET_WIDESCREEN_BORDERS( 0 ); //возвращаем инетрфейс
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// Размораживаем игрока
					G_ONMISSION = 0;
				}
				DELETE_OBJECT(&spript_map1);
				DELETE_OBJECT(&spript_map2);
				DELETE_OBJECT(&spript_map3);
				DELETE_OBJECT(&spript_map4);
				DELETE_OBJECT(&spript_map5);
				DELETE_OBJECT(&spript_map6);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&spript_map1);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&spript_map2);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&spript_map3);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&spript_map4);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&spript_map5);
				MARK_OBJECT_AS_NO_LONGER_NEEDED(&spript_map6);

				MARK_MODEL_AS_NO_LONGER_NEEDED(model_map1);
				MARK_MODEL_AS_NO_LONGER_NEEDED(model_map2);
				MARK_MODEL_AS_NO_LONGER_NEEDED(model_map3);
				MARK_MODEL_AS_NO_LONGER_NEEDED(model_map4);
				MARK_MODEL_AS_NO_LONGER_NEEDED(model_map5);
				MARK_MODEL_AS_NO_LONGER_NEEDED(model_map6);

				if (race_start == 1)
				{
					WAIT(100);
					GET_TIME_OF_DAY(&hour, &min);
					if ((hour < 22) && (hour > 4))
					{
						//выставляем камеру
						CREATE_CAM( 14, &camera );
						SET_CAM_POS			( camera, -542.888, -335.2, 8.443 );//расположение камеры
						POINT_CAM_AT_COORD	( camera, -580, -489.638, 85.291 ); // куда смотрит камера
						SET_CAM_FOV( camera, 80.20001000 );
						SET_CAM_ACTIVE( camera, 1 );
						SET_CAM_PROPAGATE( camera, 1 );
						ACTIVATE_SCRIPTED_CAMS(1, 1);
						SET_WIDESCREEN_BORDERS( 1 );
						SETTIMERA(0);
						spead_time = 1;
						cam_x = -580;
						while (true)
						{
							WAIT(0);
							DISABLE_PAUSE_MENU(1);// отключаем главное меню
							if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
							{
								break;
							}
							// если нажата клавиша для пропуска
							if ((IS_GAME_KEYBOARD_KEY_PRESSED(GAME_KEY_ESC)) || (IS_GAME_KEYBOARD_KEY_PRESSED(57)) || (IS_GAME_KEYBOARD_KEY_PRESSED(42)) || (IS_GAME_KEYBOARD_KEY_PRESSED(54)) || (IS_GAME_KEYBOARD_KEY_PRESSED(28)))
							{
								break;
							}
							if (TIMERA() > 30)
							{
								SETTIMERA(0);
								GET_TIME_OF_DAY(&hour, &min);
								POINT_CAM_AT_COORD	( camera, cam_x, -489.638, 85.291 ); // куда смотрит камера
								cam_x += 0.8;
								if (spead_time < 75)
								{
									spead_time +=1;
									FORWARD_TO_TIME_OF_DAY(hour, min + 2);
								}
								else if ((spead_time < 350) && (spead_time > 73))
								{
									spead_time +=2;
									FORWARD_TO_TIME_OF_DAY(hour, min + 3);
								}
								else if ((spead_time < 850) && (spead_time > 345))
								{
									spead_time +=2;
									FORWARD_TO_TIME_OF_DAY(hour, min + 5);
								}
								else if ((spead_time < 1150) && (spead_time > 845))
								{
									spead_time +=2;
									FORWARD_TO_TIME_OF_DAY(hour, min + 7);
								}
								else
								{
									FORWARD_TO_TIME_OF_DAY(hour, min + 8);
								}
								if (hour == 22)
								{
									break;
								}
							}
						}
						DO_SCREEN_FADE_OUT( 800 );// Затемняем экран
						SETTIMERA(0);
						while (true)
						{
							DISABLE_PAUSE_MENU(1);// отключаем главное меню
							if (TIMERA() > 30)
							{
								POINT_CAM_AT_COORD	( camera, cam_x, -489.638, 85.291 ); // куда смотрит камера
								cam_x += 0.8;
								SETTIMERA(0);
							}
							if ((IS_SCREEN_FADED_OUT()) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))) //если экран затемнился
							{
								break;
							}
							WAIT( 0 );
						}

						SETTIMERA(0);
						FORWARD_TO_TIME_OF_DAY(22, min);
						DO_SCREEN_FADE_IN( 800 );// убирается затемнение экрана
					}
					PRINT_STRING_IN_STRING("string", "VC2_RACE_TEXT10", 3500, 1);//Выводим на экран сообщение "Уже стемнело,отправляйтесь к месту проведения гонки."
					ACTIVATE_SCRIPTED_CAMS( 0, 0 );
					DESTROY_CAM( camera );
					DESTROY_CAM( camera2 );
					SET_WIDESCREEN_BORDERS( 0 ); //возвращаем инетрфейс;
					SET_PLAYER_CONTROL_ADVANCED( GetPlayerIndex(), 1, 1, 1 );// Размораживаем игрока
					start_race();
				}
			}
		}
	}
}
void main(void)
{
	race_launcher();
	while (TRUE) 
	{
		WAIT(0);
	}

}