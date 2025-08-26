#pragma once

#include <natives.h>
#include <common.h>
#include <types.h>
#include <consts.h>
#include "features.h"
#include "globals.h"
#include "fast_travel.h"

void play_mission_complete_tune(void)
{
	REQUEST_SCRIPT("mission_complete_01");

	while (!HAS_SCRIPT_LOADED("mission_complete_01"))
	{
		WAIT(0);
	}

	uint script = START_NEW_SCRIPT("mission_complete_01", 1024);
	MARK_SCRIPT_AS_NO_LONGER_NEEDED("mission_complete_01");	
}

void MissionName(char gxt_name[], bool is_cutscene, uint time)
{
	#if !defined MISSION_NAME_COMPATIBILITY
	PRINT_BIG(gxt_name, 5000, 2);
	#else
	int alpha = 0;

	SET_TEXT_DRAW_BEFORE_FADE(true);
	SETTIMERA(0);

	while (true)
	{
		WAIT(0);

		if (is_cutscene)
		{
			if ((!HAS_CUTSCENE_FINISHED()) && (TIMERA() < time))
			{
				if (alpha < 254)
				{
					alpha += 2;
				}
				else
				{
					alpha = 255;
				}
			}

			if ((!HAS_CUTSCENE_FINISHED()) && (TIMERA() > time))
			{
				if (alpha > 1)
				{
					alpha -= 2;
				}
				else
				{
					alpha = 0;
					break;
				}
			}

			if (HAS_CUTSCENE_FINISHED())
			{
				alpha = 0;
				break;
			}
		}
		else
		{
			if ((!IS_SCREEN_FADED_OUT()) && (TIMERA() < time))
			{
				if (alpha < 254)
				{
					alpha += 2;
				}
				else
				{
					alpha = 255;
				}
			}

			if ((!IS_SCREEN_FADED_OUT()) && (TIMERA() > time))
			{
				if (alpha > 1)
				{
					alpha -= 2;
				}
				else
				{
					alpha = 0;
					break;
				}
			}
		}

		SET_TEXT_COLOUR(255, 230, 0, alpha);
		SET_TEXT_SCALE(0.55, 0.82);
		SET_TEXT_EDGE(1, 0, 0, 0, alpha);
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, alpha);
		SET_TEXT_CENTRE(1);
		SET_TEXT_RIGHT_JUSTIFY(1);
		SET_TEXT_FONT(6);
		DISPLAY_TEXT(0.50, 0.80, gxt_name);
	}

	SET_TEXT_DRAW_BEFORE_FADE(false);
	#endif
}
void MissionFailed(void)
{
	#if !defined MISSION_COMPLETE_COMPATIBILITY
	SETTIMERA(0);

	while (true)
	{
		WAIT(0);

		if (TIMERA() > 3000)
		{
			break;
		}

		SET_TEXT_COLOUR(255, 159, 255, 255);
		SET_TEXT_SCALE(0.5, 0.6);
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT(0.5, 0.45, "MISSION_FAILED");
	}
	#else
	TextureDict texture_dictionary = LOAD_TXD("hud");
	Texture texture = GET_TEXTURE(texture_dictionary, "missionfailed");
	int alpha = 0;

	SET_SPRITES_DRAW_BEFORE_FADE(true);
	SETTIMERA(0);

	while (true)
	{
		WAIT(0);

		if ((!IS_SCREEN_FADED_OUT()) && (TIMERA() < 6000))
		{
			if (alpha < 254)
			{
				alpha += 2;
			}
			else
			{
				alpha = 255;
			}
		}

		if ((!IS_CHAR_DEAD(GetPlayerPed())) || (!HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))
		{
			if ((!IS_SCREEN_FADED_OUT()) && (TIMERA() > 6000))
			{
				if (alpha > 1)
				{
					alpha -= 2;
				}
				else
				{
					alpha = 0;
					break;
				}
			}
		}

																	 
   
								   
				   
   
  
																	   
   
								   
				   

		if ((IS_SCREEN_FADED_OUT()) || (IS_SCREEN_FADING_IN()))
		{
			alpha = 0;
			break;
		}

		DRAW_SPRITE(texture, 0.5, 0.45, 0.6, 0.11, 0.0, 255, 255, 255, alpha);
	}

	SET_SPRITES_DRAW_BEFORE_FADE(false);

	RELEASE_TEXTURE(texture);
	REMOVE_TXD(texture_dictionary);
	#endif
}

void MissionPassed(int money, char texture_name[], char gxt_name[])
{
	RemoveShortCutDropOffPointForMission();
	ClearShortCut();
	#if !defined MISSION_COMPLETE_COMPATIBILITY
	SETTIMERA(0);

	while (true)
	{
		WAIT(0);

		if (TIMERA() > 4000)
		{
			break;
		}

		SET_TEXT_COLOUR(255, 159, 255, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT(0.5, 0.45, "MISSION_PASSED");

		if (money != 0)
		{
			SET_TEXT_COLOUR(255, 159, 255, 255);
			SET_TEXT_SCALE(0.5, 0.7);
			SET_TEXT_EDGE(1, 0, 0, 0, 255);
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200);
			SET_TEXT_CENTRE(1);
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, gxt_name, money);
		}
	}
	#else
	TextureDict texture_dictionary = LOAD_TXD("hud");
	Texture texture = GET_TEXTURE(texture_dictionary, texture_name);
	int alpha = 0;

	SETTIMERA(0);

	while (true)
	{
		WAIT(0);

		if ((!IS_SCREEN_FADED_OUT()) && (TIMERA() < 9000))
		{
			if (alpha < 254)
			{
				alpha += 2;
			}
			else
			{
				alpha = 255;
			}
		}

		if ((!IS_SCREEN_FADED_OUT()) && (TIMERA() > 9000))
		{
			if (alpha > 1)
			{
				alpha -= 2;
			}
			else
			{
				alpha = 0;
				break;
			}
		}

		DRAW_SPRITE(texture, 0.5, 0.45, 0.6, 0.11, 0.0, 255, 255, 255, alpha);

		if (money > 0)
		{
			SET_TEXT_COLOUR(255, 140, 217, alpha);
			SET_TEXT_SCALE(0.65, 0.65);
			SET_TEXT_DROPSHADOW(2.5, 0, 0, 0, alpha);
			SET_TEXT_CENTRE(1);
			SET_TEXT_FONT(4);
			DISPLAY_TEXT_WITH_NUMBER(0.5, 0.48, gxt_name, money);
		}
	}

	RELEASE_TEXTURE(texture);
	REMOVE_TXD(texture_dictionary);
	#endif
}