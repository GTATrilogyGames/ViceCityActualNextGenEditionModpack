#include <natives.h>
#include <types.h>
#include <consts.h>
#include "mission_ids.h"
#include "globals.h"

void main(void)
{
	int mission_id = G_MISSION_ID;
	uint duration = G_MISSION_NAME_DURATION;
	char *mission_name;

	if (mission_id == MISSION_RUB_OUT)
		mission_name = "ASS_1"; // Rub Out
	else if (mission_id == MISSION_NO_ESCAPE)
		mission_name = "BANK_1"; // No Escape?
	else if (mission_id == MISSION_THE_SHOOTIST)
		mission_name = "BANK_2"; // The Shootist
	else if (mission_id == MISSION_THE_DRIVER)
		mission_name = "BANK_3"; // The Driver
	else if (mission_id == MISSION_THE_JOB)
		mission_name = "BANK_4"; // The Job
	else if (mission_id == MISSION_ALLOY_WHEELS_OF_STEEL)
		mission_name = "BIKE_1"; // Alloy Wheels of Steel
	else if (mission_id == MISSION_MESSING_WITH_THE_MAN)
		mission_name = "BIKE_2"; // Messing with the Man
	else if (mission_id == MISSION_HOG_TIED)
		mission_name = "BIKE_3"; // Hog Tied
	else if (mission_id == MISSION_CHECKPOINT_CHARLIE)
		mission_name = "BOAT_N"; // Checkpoint Charlie
	else if (mission_id == MISSION_SHAKEDOWN)
		mission_name = "BUD_1"; // Shakedown
	else if (mission_id == MISSION_BAR_BRAWL)
		mission_name = "BUD_2"; // Bar Brawl
	else if (mission_id == MISSION_COP_LAND)
		mission_name = "BUD_3"; // Cop Land
	else if (mission_id == MISSION_CAP_THE_COLLECTOR)
		mission_name = "CAP_1"; // Cap the Collector
	else if (mission_id == MISSION_SPILLING_THE_BEANS)
		mission_name = "CNT_1"; // Spilling the Beans
	else if (mission_id == MISSION_HIT_THE_COURIER)
		mission_name = "CNT_2"; // Hit the Courier
	else if (mission_id == MISSION_THE_CHASE)
		mission_name = "COK_1"; // The Chase
	else if (mission_id == MISSION_PHNOM_PENH_86)
		mission_name = "COK_2"; // Phnom Penh '86
	else if (mission_id == MISSION_THE_FASTEST_BOAT)
		mission_name = "COK_3"; // The Fastest Boat
	else if (mission_id == MISSION_SUPPLY_AND_DEMAND)
		mission_name = "COK_4"; // Supply & Demand
	else if (mission_id == MISSION_TREACHEROUS_SWINE)
		mission_name = "COL_1"; // Treacherous Swine
	else if (mission_id == MISSION_MALL_SHOOTOUT)
		mission_name = "COL_2"; // Mall Shootout
	else if (mission_id == MISSION_GUARDIAN_ANGELS)
		mission_name = "COL_3"; // Guardian Angels
	else if (mission_id == MISSION_SIR_YES_SIR)
		mission_name = "COL_4"; // Sir, Yes Sir!
	else if (mission_id == MISSION_ALL_HANDS_ON_DECK)
		mission_name = "COL_5"; // All Hands On Deck!
	else if (mission_id == MISSION_DISTRIBUTION)
		mission_name = "CREAM"; // Distribution
	else if (mission_id == MISSION_STUNT_BOAT_CHALLENGE)
		mission_name = "CUB_1"; // Stunt Boat Challenge
	else if (mission_id == MISSION_CANNON_FODDER)
		mission_name = "CUB_2"; // Cannon Fodder
	else if (mission_id == MISSION_NAVAL_ENGAGEMENT)
		mission_name = "CUB_3"; // Naval Engagement
	else if (mission_id == MISSION_TROJAN_VOODOO)
		mission_name = "CUB_4"; // Trojan Voodoo
	else if (mission_id == MISSION_KEEP_YOUR_FRIENDS_CLOSE)
		mission_name = "FIN_1"; // Keep your Friends Close...
	else if (mission_id == MISSION_JUJU_SCRAMBLE)
		mission_name = "HAT_1"; // Juju Scramble
	else if (mission_id == MISSION_BOMBS_AWAY)
		mission_name = "HAT_2"; // Bombs Away!
	else if (mission_id == MISSION_DIRTY_LICKINS)
		mission_name = "HAT_3"; // Dirty Lickin's
	else if (mission_id == MISSION_AN_OLD_FRIEND)
		mission_name = "INT_B"; // An Old Friend
	else if (mission_id == MISSION_ROAD_KILL)
		mission_name = "JOB_1"; // Road Kill
	else if (mission_id == MISSION_WASTE_THE_WIFE)
		mission_name = "JOB_2"; // Waste the Wife
	else if (mission_id == MISSION_AUTOCIDE)
		mission_name = "JOB_3"; // Autocide
	else if (mission_id == MISSION_CHECK_OUT_AT_THE_CHECK_IN)
		mission_name = "JOB_4"; // Check Out at the Check In
	else if (mission_id == MISSION_LOOSE_ENDS)
		mission_name = "JOB_5"; // Loose Ends
	else if (mission_id == MISSION_DEATH_ROW)
		mission_name = "KENT_1"; // Death Row
	else if (mission_id == MISSION_THE_PARTY)
		mission_name = "LAW_1"; // The Party
	else if (mission_id == MISSION_BACK_ALLEY_BRAWL)
		mission_name = "LAW_2"; // Back Alley Brawl
	else if (mission_id == MISSION_JURY_FURY)
		mission_name = "LAW_3"; // Jury Fury
	else if (mission_id == MISSION_RIOT)
		mission_name = "LAW_4"; // Riot
	else if (mission_id == MISSION_GUN_RUNNER)
		mission_name = "PHIL_1"; // Gun Runner
	else if (mission_id == MISSION_BOOMSHINE_SAIGON)
		mission_name = "PHIL_2"; // Boomshine Saigon
	else if (mission_id == MISSION_RECRUITMENT_DRIVE)
		mission_name = "PORN_1"; // Recruitment Drive
	else if (mission_id == MISSION_DILDO_DODO)
		mission_name = "PORN_2"; // Dildo Dodo
	else if (mission_id == MISSION_MARTHAS_MUG_SHOT)
		mission_name = "PORN_3"; // Martha's Mug Shot
	else if (mission_id == MISSION_GSPOTLIGHT)
		mission_name = "PORN_4"; // G-spotlight
	else if (mission_id == MISSION_LOVE_JUICE)
		mission_name = "ROCK_1"; // Love Juice
	else if (mission_id == MISSION_PSYCHO_KILLER)
		mission_name = "ROCK_2"; // Psycho Killer
	else if (mission_id == MISSION_PUBLICITY_TOUR)
		mission_name = "ROCK_3"; // Publicity Tour
	else if (mission_id == MISSION_VIP)
		mission_name = "TAXI_1"; // V.I.P.
	else if (mission_id == MISSION_FRIENDLY_RIVALRY)
		mission_name = "TAXI_2"; // Friendly Rivalry
	else if (mission_id == MISSION_CABMAGGEDON)
		mission_name = "TAXI_3"; // Cabmaggedon
	else if (mission_id == MISSION_FOUR_IRON)
		mission_name = "TEX_1"; // Four Iron
	else if (mission_id == MISSION_TWO_BIT_HIT)
		mission_name = "TEX_2"; // Two Bit Hit
	else if (mission_id == MISSION_DEMOLITION_MAN)
		mission_name = "TEX_3"; // Demolition Man

	int alpha = 0;
	int textfade = 0;				  
	bool is_in_cutscene = G_IS_IN_CUTSCENE;

	WAIT(1000);			
	SETTIMERA(0);

	while (true)
	{
		WAIT(0);

		if (is_in_cutscene && !G_IS_IN_CUTSCENE)
		{
			alpha = 0;
			break;
		}

		is_in_cutscene = G_IS_IN_CUTSCENE;

		if (TIMERA() < duration)
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
		
		if (IS_SCREEN_FADING() || IS_FRONTEND_FADING() && textfade == 0)
		{
			SET_TEXT_DRAW_BEFORE_FADE(1);
			textfade = 1;				
		}
		else
		{
			SET_TEXT_DRAW_BEFORE_FADE(0);
		}

		if (TIMERA() > duration)
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

		SET_TEXT_COLOUR(255, 230, 0, alpha);
		SET_TEXT_SCALE(0.55, 0.82);
		SET_TEXT_EDGE(1, 0, 0, 0, alpha);
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, alpha);
		SET_TEXT_CENTRE(1);
		SET_TEXT_RIGHT_JUSTIFY(1);
		SET_TEXT_FONT(6);
		DISPLAY_TEXT(0.50, 0.80, mission_name);
	}

	TERMINATE_THIS_SCRIPT();
}
