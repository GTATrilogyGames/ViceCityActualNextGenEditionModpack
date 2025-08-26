#pragma once

#include <natives.h>
#include <common.h>
#include <types.h>
#include <consts.h>
#include "features.h"
#include "map_offset.h"
#include "mission_ids.h"
#include "globals.h"

enum
{
	CUTSCENE_INTRO,
	CUTSCENE_LAWYER,
	CUTSCENE_BARON,
	CUTSCENE_GENERAL,
	CUTSCENE_PORN,
	CUTSCENE_KENT,
	CUTSCENE_BANKJOB,
	CUTSCENE_PHIL,
	CUTSCENE_COUNTER,
	CUTSCENE_BIKER,
	CUTSCENE_ROCK,
	CUTSCENE_CUBAN,
	CUTSCENE_HAITIAN,
	CUTSCENE_TAXIWAR,
	CUTSCENE_SERGIO
};

char *mission_name;
uint mission_name_display_duration = 0;
#if defined SCRIPTED_CUTSCENES_BEFORE_ACTUAL_CUTSCENES && !defined MISSION_NAME_COMPATIBILITY // Added workaround for PRINT_BIG disappearing after cutscene starts
uint mission_name_display_start_time = 0;
#endif

void CUTSCENES_PRINT_BIG(char *gxtName, uint timeMS, boolean enable)
{
	#if !defined MISSION_NAME_COMPATIBILITY
	PRINT_BIG(gxtName, timeMS, enable);
	#else
	if (COMPARE_STRING(gxtName, "ASS_1")) // Rub Out
		G_MISSION_ID = MISSION_RUB_OUT;
	else if (COMPARE_STRING(gxtName, "BANK_1")) // No Escape?
		G_MISSION_ID = MISSION_NO_ESCAPE;
	else if (COMPARE_STRING(gxtName, "BANK_2")) // The Shootist
		G_MISSION_ID = MISSION_THE_SHOOTIST;
	else if (COMPARE_STRING(gxtName, "BANK_3")) // The Driver
		G_MISSION_ID = MISSION_THE_DRIVER;
	else if (COMPARE_STRING(gxtName, "BANK_4")) // The Job
		G_MISSION_ID = MISSION_THE_JOB;
	else if (COMPARE_STRING(gxtName, "BIKE_1")) // Alloy Wheels of Steel
		G_MISSION_ID = MISSION_ALLOY_WHEELS_OF_STEEL;
	else if (COMPARE_STRING(gxtName, "BIKE_2")) // Messing with the Man
		G_MISSION_ID = MISSION_MESSING_WITH_THE_MAN;
	else if (COMPARE_STRING(gxtName, "BIKE_3")) // Hog Tied
		G_MISSION_ID = MISSION_HOG_TIED;
	else if (COMPARE_STRING(gxtName, "BOAT_N")) // Checkpoint Charlie
		G_MISSION_ID = MISSION_CHECKPOINT_CHARLIE;
	else if (COMPARE_STRING(gxtName, "BUD_1")) // Shakedown
		G_MISSION_ID = MISSION_SHAKEDOWN;
	else if (COMPARE_STRING(gxtName, "BUD_2")) // Bar Brawl
		G_MISSION_ID = MISSION_BAR_BRAWL;
	else if (COMPARE_STRING(gxtName, "BUD_3")) // Cop Land
		G_MISSION_ID = MISSION_COP_LAND;
	else if (COMPARE_STRING(gxtName, "CAP_1")) // Cap the Collector
		G_MISSION_ID = MISSION_CAP_THE_COLLECTOR;
	else if (COMPARE_STRING(gxtName, "CNT_1")) // Spilling the Beans
		G_MISSION_ID = MISSION_SPILLING_THE_BEANS;
	else if (COMPARE_STRING(gxtName, "CNT_2")) // Hit the Courier
		G_MISSION_ID = MISSION_HIT_THE_COURIER;
	else if (COMPARE_STRING(gxtName, "COK_1")) // The Chase
		G_MISSION_ID = MISSION_THE_CHASE;
	else if (COMPARE_STRING(gxtName, "COK_2")) // Phnom Penh '86
		G_MISSION_ID = MISSION_PHNOM_PENH_86;
	else if (COMPARE_STRING(gxtName, "COK_3")) // The Fastest Boat
		G_MISSION_ID = MISSION_THE_FASTEST_BOAT;
	else if (COMPARE_STRING(gxtName, "COK_4")) // Supply & Demand
		G_MISSION_ID = MISSION_SUPPLY_AND_DEMAND;
	else if (COMPARE_STRING(gxtName, "COL_1")) // Treacherous Swine
		G_MISSION_ID = MISSION_TREACHEROUS_SWINE;
	else if (COMPARE_STRING(gxtName, "COL_2")) // Mall Shootout
		G_MISSION_ID = MISSION_MALL_SHOOTOUT;
	else if (COMPARE_STRING(gxtName, "COL_3")) // Guardian Angels
		G_MISSION_ID = MISSION_GUARDIAN_ANGELS;
	else if (COMPARE_STRING(gxtName, "COL_4")) // Sir, Yes Sir!
		G_MISSION_ID = MISSION_SIR_YES_SIR;
	else if (COMPARE_STRING(gxtName, "COL_5")) // All Hands On Deck!
		G_MISSION_ID = MISSION_ALL_HANDS_ON_DECK;
	else if (COMPARE_STRING(gxtName, "CREAM")) // Distribution
		G_MISSION_ID = MISSION_DISTRIBUTION;
	else if (COMPARE_STRING(gxtName, "CUB_1")) // Stunt Boat Challenge
		G_MISSION_ID = MISSION_STUNT_BOAT_CHALLENGE;
	else if (COMPARE_STRING(gxtName, "CUB_2")) // Cannon Fodder
		G_MISSION_ID = MISSION_CANNON_FODDER;
	else if (COMPARE_STRING(gxtName, "CUB_3")) // Naval Engagement
		G_MISSION_ID = MISSION_NAVAL_ENGAGEMENT;
	else if (COMPARE_STRING(gxtName, "CUB_4")) // Trojan Voodoo
		G_MISSION_ID = MISSION_TROJAN_VOODOO;
	else if (COMPARE_STRING(gxtName, "FIN_1")) // Keep your Friends Close...
		G_MISSION_ID = MISSION_KEEP_YOUR_FRIENDS_CLOSE;
	else if (COMPARE_STRING(gxtName, "HAT_1")) // Juju Scramble
		G_MISSION_ID = MISSION_JUJU_SCRAMBLE;
	else if (COMPARE_STRING(gxtName, "HAT_2")) // Bombs Away!
		G_MISSION_ID = MISSION_BOMBS_AWAY;
	else if (COMPARE_STRING(gxtName, "HAT_3")) // Dirty Lickin's
		G_MISSION_ID = MISSION_DIRTY_LICKINS;
	else if (COMPARE_STRING(gxtName, "INT_B")) // An Old Friend
		G_MISSION_ID = MISSION_AN_OLD_FRIEND;
	else if (COMPARE_STRING(gxtName, "JOB_1")) // Road Kill
		G_MISSION_ID = MISSION_ROAD_KILL;
	else if (COMPARE_STRING(gxtName, "JOB_2")) // Waste the Wife
		G_MISSION_ID = MISSION_WASTE_THE_WIFE;
	else if (COMPARE_STRING(gxtName, "JOB_3")) // Autocide
		G_MISSION_ID = MISSION_AUTOCIDE;
	else if (COMPARE_STRING(gxtName, "JOB_4")) // Check Out at the Check In
		G_MISSION_ID = MISSION_CHECK_OUT_AT_THE_CHECK_IN;
	else if (COMPARE_STRING(gxtName, "JOB_5")) // Loose Ends
		G_MISSION_ID = MISSION_LOOSE_ENDS;
	else if (COMPARE_STRING(gxtName, "KENT_1")) // Death Row
		G_MISSION_ID = MISSION_DEATH_ROW;
	else if (COMPARE_STRING(gxtName, "LAW_1")) // The Party
		G_MISSION_ID = MISSION_THE_PARTY;
	else if (COMPARE_STRING(gxtName, "LAW_2")) // Back Alley Brawl
		G_MISSION_ID = MISSION_BACK_ALLEY_BRAWL;
	else if (COMPARE_STRING(gxtName, "LAW_3")) // Jury Fury
		G_MISSION_ID = MISSION_JURY_FURY;
	else if (COMPARE_STRING(gxtName, "LAW_4")) // Riot
		G_MISSION_ID = MISSION_RIOT;
	else if (COMPARE_STRING(gxtName, "PHIL_1")) // Gun Runner
		G_MISSION_ID = MISSION_GUN_RUNNER;
	else if (COMPARE_STRING(gxtName, "PHIL_2")) // Boomshine Saigon
		G_MISSION_ID = MISSION_BOOMSHINE_SAIGON;
	else if (COMPARE_STRING(gxtName, "PORN_1")) // Recruitment Drive
		G_MISSION_ID = MISSION_RECRUITMENT_DRIVE;
	else if (COMPARE_STRING(gxtName, "PORN_2")) // Dildo Dodo
		G_MISSION_ID = MISSION_DILDO_DODO;
	else if (COMPARE_STRING(gxtName, "PORN_3")) // Martha's Mug Shot
		G_MISSION_ID = MISSION_MARTHAS_MUG_SHOT;
	else if (COMPARE_STRING(gxtName, "PORN_4")) // G-spotlight
		G_MISSION_ID = MISSION_GSPOTLIGHT;
	else if (COMPARE_STRING(gxtName, "ROCK_1")) // Love Juice
		G_MISSION_ID = MISSION_LOVE_JUICE;
	else if (COMPARE_STRING(gxtName, "ROCK_2")) // Psycho Killer
		G_MISSION_ID = MISSION_PSYCHO_KILLER;
	else if (COMPARE_STRING(gxtName, "ROCK_3")) // Publicity Tour
		G_MISSION_ID = MISSION_PUBLICITY_TOUR;
	else if (COMPARE_STRING(gxtName, "TAXI_1")) // V.I.P.
		G_MISSION_ID = MISSION_VIP;
	else if (COMPARE_STRING(gxtName, "TAXI_2")) // Friendly Rivalry
		G_MISSION_ID = MISSION_FRIENDLY_RIVALRY;
	else if (COMPARE_STRING(gxtName, "TAXI_3")) // Cabmaggedon
		G_MISSION_ID = MISSION_CABMAGGEDON;
	else if (COMPARE_STRING(gxtName, "TEX_1")) // Four Iron
		G_MISSION_ID = MISSION_FOUR_IRON;
	else if (COMPARE_STRING(gxtName, "TEX_2")) // Two Bit Hit
		G_MISSION_ID = MISSION_TWO_BIT_HIT;
	else if (COMPARE_STRING(gxtName, "TEX_3")) // Demolition Man
		G_MISSION_ID = MISSION_DEMOLITION_MAN;
	else
		return PRINT_BIG(gxtName, timeMS, enable);

	G_MISSION_NAME_DURATION = timeMS;

	REQUEST_SCRIPT("print_big");

	while (!HAS_SCRIPT_LOADED("print_big"))
	{
		WAIT(0);
	}

	uint script = START_NEW_SCRIPT("print_big", 1024);
	MARK_SCRIPT_AS_NO_LONGER_NEEDED("print_big");
	#endif
}

#define PRINT_BIG CUTSCENES_PRINT_BIG

void CUTSCENES_START_CUTSCENE_NOW(char *name)
{
	uint torso = GET_CHAR_DRAWABLE_VARIATION(GetPlayerPed(), 1);

	if (torso != 0 && torso != 1)
	{
		torso = 0;
	}

	if (COMPARE_STRING(name, "ass_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("ass_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("ass_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("ass_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("ass_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("ass_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("ass_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("ass_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("ass_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("ass_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("ass_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("ass_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("ass_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("ass_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("ass_1_13");
	}
	else if (COMPARE_STRING(name, "ass_2"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("ass_2");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("ass_2_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("ass_2_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("ass_2_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("ass_2_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("ass_2_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("ass_2_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("ass_2_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("ass_2_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("ass_2_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("ass_2_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("ass_2_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("ass_2_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("ass_2_13");
	}
	else if (COMPARE_STRING(name, "bank_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("bank_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("bank_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("bank_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("bank_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("bank_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("bank_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("bank_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("bank_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("bank_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("bank_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("bank_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("bank_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("bank_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("bank_1_13");
	}
	else if (COMPARE_STRING(name, "bank_2a"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("bank_2a");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("bank_2a_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("bank_2a_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("bank_2a_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("bank_2a_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("bank_2a_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("bank_2a_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("bank_2a_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("bank_2a_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("bank_2a_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("bank_2a_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("bank_2a_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("bank_2a_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("bank_2a_13");
	}
	else if (COMPARE_STRING(name, "bank_2b"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("bank_2b");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("bank_2b_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("bank_2b_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("bank_2b_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("bank_2b_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("bank_2b_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("bank_2b_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("bank_2b_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("bank_2b_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("bank_2b_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("bank_2b_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("bank_2b_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("bank_2b_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("bank_2b_13");
	}
	else if (COMPARE_STRING(name, "bank_3a"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("bank_3a");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("bank_3a_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("bank_3a_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("bank_3a_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("bank_3a_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("bank_3a_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("bank_3a_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("bank_3a_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("bank_3a_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("bank_3a_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("bank_3a_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("bank_3a_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("bank_3a_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("bank_3a_13");
	}
	else if (COMPARE_STRING(name, "bank_3b"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("bank_3b");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("bank_3b_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("bank_3b_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("bank_3b_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("bank_3b_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("bank_3b_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("bank_3b_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("bank_3b_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("bank_3b_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("bank_3b_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("bank_3b_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("bank_3b_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("bank_3b_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("bank_3b_13");
	}
	else if (COMPARE_STRING(name, "bank_4"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("bank_4");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("bank_4_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("bank_4_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("bank_4_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("bank_4_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("bank_4_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("bank_4_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("bank_4_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("bank_4_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("bank_4_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("bank_4_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("bank_4_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("bank_4_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("bank_4_13");
	}
	else if (COMPARE_STRING(name, "bike_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("bike_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("bike_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("bike_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("bike_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("bike_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("bike_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("bike_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("bike_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("bike_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("bike_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("bike_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("bike_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("bike_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("bike_1_13");
	}
	else if (COMPARE_STRING(name, "bike_2"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("bike_2");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("bike_2_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("bike_2_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("bike_2_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("bike_2_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("bike_2_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("bike_2_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("bike_2_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("bike_2_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("bike_2_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("bike_2_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("bike_2_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("bike_2_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("bike_2_13");
	}
	else if (COMPARE_STRING(name, "bike_3"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("bike_3");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("bike_3_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("bike_3_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("bike_3_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("bike_3_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("bike_3_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("bike_3_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("bike_3_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("bike_3_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("bike_3_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("bike_3_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("bike_3_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("bike_3_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("bike_3_13");
	}
	else if (COMPARE_STRING(name, "bud_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("bud_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("bud_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("bud_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("bud_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("bud_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("bud_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("bud_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("bud_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("bud_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("bud_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("bud_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("bud_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("bud_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("bud_1_13");
	}
	else if (COMPARE_STRING(name, "bud_2"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("bud_2");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("bud_2_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("bud_2_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("bud_2_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("bud_2_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("bud_2_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("bud_2_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("bud_2_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("bud_2_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("bud_2_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("bud_2_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("bud_2_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("bud_2_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("bud_2_13");
	}
	else if (COMPARE_STRING(name, "bud_3"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("bud_3");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("bud_3_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("bud_3_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("bud_3_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("bud_3_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("bud_3_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("bud_3_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("bud_3_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("bud_3_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("bud_3_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("bud_3_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("bud_3_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("bud_3_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("bud_3_13");
	}
	else if (COMPARE_STRING(name, "cap_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cap_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cap_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cap_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cap_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cap_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cap_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cap_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cap_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cap_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cap_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cap_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cap_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cap_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cap_1_13");
	}
	else if (COMPARE_STRING(name, "car_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("car_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("car_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("car_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("car_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("car_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("car_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("car_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("car_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("car_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("car_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("car_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("car_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("car_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("car_1_13");
	}
	else if (COMPARE_STRING(name, "cnt_1a"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cnt_1a");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cnt_1a_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cnt_1a_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cnt_1a_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cnt_1a_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cnt_1a_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cnt_1a_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cnt_1a_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cnt_1a_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cnt_1a_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cnt_1a_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cnt_1a_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cnt_1a_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cnt_1a_13");
	}
	else if (COMPARE_STRING(name, "cnt_1b"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cnt_1b");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cnt_1b_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cnt_1b_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cnt_1b_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cnt_1b_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cnt_1b_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cnt_1b_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cnt_1b_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cnt_1b_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cnt_1b_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cnt_1b_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cnt_1b_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cnt_1b_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cnt_1b_13");
	}
	else if (COMPARE_STRING(name, "cnt_2"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cnt_2");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cnt_2_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cnt_2_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cnt_2_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cnt_2_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cnt_2_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cnt_2_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cnt_2_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cnt_2_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cnt_2_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cnt_2_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cnt_2_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cnt_2_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cnt_2_13");
	}
	else if (COMPARE_STRING(name, "cok_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cok_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cok_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cok_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cok_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cok_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cok_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cok_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cok_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cok_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cok_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cok_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cok_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cok_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cok_1_13");
	}
	else if (COMPARE_STRING(name, "cok_2a"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cok_2a");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cok_2a_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cok_2a_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cok_2a_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cok_2a_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cok_2a_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cok_2a_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cok_2a_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cok_2a_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cok_2a_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cok_2a_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cok_2a_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cok_2a_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cok_2a_13");
	}
	else if (COMPARE_STRING(name, "cok_2b"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cok_2b");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cok_2b_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cok_2b_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cok_2b_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cok_2b_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cok_2b_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cok_2b_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cok_2b_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cok_2b_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cok_2b_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cok_2b_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cok_2b_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cok_2b_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cok_2b_13");
	}
	else if (COMPARE_STRING(name, "cok_3"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cok_3");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cok_3_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cok_3_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cok_3_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cok_3_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cok_3_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cok_3_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cok_3_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cok_3_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cok_3_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cok_3_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cok_3_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cok_3_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cok_3_13");
	}
	else if (COMPARE_STRING(name, "cok_4a"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cok_4a");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cok_4a_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cok_4a_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cok_4a_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cok_4a_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cok_4a_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cok_4a_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cok_4a_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cok_4a_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cok_4a_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cok_4a_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cok_4a_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cok_4a_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cok_4a_13");
	}
	else if (COMPARE_STRING(name, "cok_4a2"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cok_4a2");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cok_4a2_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cok_4a2_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cok_4a2_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cok_4a2_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cok_4a2_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cok_4a2_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cok_4a2_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cok_4a2_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cok_4a2_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cok_4a2_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cok_4a2_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cok_4a2_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cok_4a2_13");
	}
	else if (COMPARE_STRING(name, "cok_4b"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cok_4b");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cok_4b_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cok_4b_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cok_4b_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cok_4b_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cok_4b_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cok_4b_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cok_4b_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cok_4b_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cok_4b_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cok_4b_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cok_4b_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cok_4b_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cok_4b_13");
	}
	else if (COMPARE_STRING(name, "col_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("col_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("col_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("col_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("col_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("col_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("col_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("col_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("col_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("col_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("col_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("col_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("col_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("col_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("col_1_13");
	}
	else if (COMPARE_STRING(name, "col_2"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("col_2");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("col_2_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("col_2_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("col_2_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("col_2_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("col_2_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("col_2_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("col_2_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("col_2_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("col_2_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("col_2_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("col_2_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("col_2_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("col_2_13");
	}
	else if (COMPARE_STRING(name, "col_3a"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("col_3a");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("col_3a_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("col_3a_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("col_3a_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("col_3a_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("col_3a_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("col_3a_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("col_3a_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("col_3a_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("col_3a_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("col_3a_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("col_3a_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("col_3a_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("col_3a_13");
	}
	else if (COMPARE_STRING(name, "col_4a"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("col_4a");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("col_4a_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("col_4a_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("col_4a_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("col_4a_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("col_4a_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("col_4a_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("col_4a_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("col_4a_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("col_4a_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("col_4a_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("col_4a_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("col_4a_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("col_4a_13");
	}
	else if (COMPARE_STRING(name, "col_5a"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("col_5a");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("col_5a_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("col_5a_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("col_5a_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("col_5a_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("col_5a_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("col_5a_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("col_5a_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("col_5a_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("col_5a_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("col_5a_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("col_5a_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("col_5a_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("col_5a_13");
	}
	else if (COMPARE_STRING(name, "col_5b"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("col_5b");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("col_5b_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("col_5b_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("col_5b_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("col_5b_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("col_5b_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("col_5b_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("col_5b_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("col_5b_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("col_5b_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("col_5b_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("col_5b_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("col_5b_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("col_5b_13");
	}
	else if (COMPARE_STRING(name, "cub_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cub_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cub_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cub_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cub_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cub_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cub_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cub_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cub_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cub_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cub_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cub_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cub_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cub_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cub_1_13");
	}
	else if (COMPARE_STRING(name, "cub_2"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cub_2");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cub_2_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cub_2_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cub_2_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cub_2_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cub_2_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cub_2_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cub_2_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cub_2_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cub_2_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cub_2_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cub_2_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cub_2_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cub_2_13");
	}
	else if (COMPARE_STRING(name, "cub_3"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cub_3");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cub_3_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cub_3_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cub_3_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cub_3_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cub_3_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cub_3_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cub_3_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cub_3_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cub_3_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cub_3_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cub_3_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cub_3_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cub_3_13");
	}
	else if (COMPARE_STRING(name, "cub_4"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("cub_4");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("cub_4_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("cub_4_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("cub_4_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("cub_4_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("cub_4_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("cub_4_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("cub_4_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("cub_4_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("cub_4_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("cub_4_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("cub_4_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("cub_4_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("cub_4_13");
	}
	else if (COMPARE_STRING(name, "drug_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("drug_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("drug_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("drug_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("drug_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("drug_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("drug_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("drug_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("drug_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("drug_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("drug_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("drug_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("drug_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("drug_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("drug_1_13");
	}
	else if (COMPARE_STRING(name, "fin"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("fin");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("fin_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("fin_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("fin_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("fin_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("fin_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("fin_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("fin_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("fin_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("fin_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("fin_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("fin_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("fin_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("fin_13");
	}
	else if (COMPARE_STRING(name, "finale"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("finale");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("finale_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("finale_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("finale_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("finale_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("finale_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("finale_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("finale_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("finale_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("finale_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("finale_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("finale_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("finale_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("finale_13");
	}
	else if (COMPARE_STRING(name, "hat_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("hat_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("hat_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("hat_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("hat_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("hat_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("hat_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("hat_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("hat_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("hat_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("hat_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("hat_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("hat_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("hat_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("hat_1_13");
	}
	else if (COMPARE_STRING(name, "hat_2"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("hat_2");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("hat_2_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("hat_2_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("hat_2_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("hat_2_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("hat_2_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("hat_2_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("hat_2_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("hat_2_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("hat_2_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("hat_2_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("hat_2_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("hat_2_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("hat_2_13");
	}
	else if (COMPARE_STRING(name, "hat_3"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("hat_3");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("hat_3_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("hat_3_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("hat_3_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("hat_3_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("hat_3_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("hat_3_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("hat_3_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("hat_3_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("hat_3_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("hat_3_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("hat_3_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("hat_3_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("hat_3_13");
	}
	else if (COMPARE_STRING(name, "ice_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("ice_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("ice_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("ice_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("ice_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("ice_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("ice_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("ice_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("ice_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("ice_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("ice_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("ice_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("ice_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("ice_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("ice_1_13");
	}
	else if (COMPARE_STRING(name, "int_b"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("int_b");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("int_b_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("int_b_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("int_b_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("int_b_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("int_b_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("int_b_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("int_b_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("int_b_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("int_b_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("int_b_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("int_b_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("int_b_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("int_b_13");
	}
	else if (COMPARE_STRING(name, "int_d"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("int_d");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("int_d_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("int_d_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("int_d_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("int_d_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("int_d_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("int_d_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("int_d_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("int_d_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("int_d_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("int_d_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("int_d_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("int_d_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("int_d_13");
	}
	else if (COMPARE_STRING(name, "int_m"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("int_m");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("int_m_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("int_m_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("int_m_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("int_m_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("int_m_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("int_m_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("int_m_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("int_m_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("int_m_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("int_m_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("int_m_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("int_m_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("int_m_13");
	}
	else if (COMPARE_STRING(name, "law_1a"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("law_1a");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("law_1a_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("law_1a_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("law_1a_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("law_1a_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("law_1a_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("law_1a_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("law_1a_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("law_1a_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("law_1a_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("law_1a_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("law_1a_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("law_1a_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("law_1a_13");
	}
	else if (COMPARE_STRING(name, "law_1b"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("law_1b");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("law_1b_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("law_1b_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("law_1b_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("law_1b_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("law_1b_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("law_1b_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("law_1b_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("law_1b_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("law_1b_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("law_1b_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("law_1b_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("law_1b_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("law_1b_13");
	}
	else if (COMPARE_STRING(name, "law_2a"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("law_2a");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("law_2a_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("law_2a_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("law_2a_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("law_2a_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("law_2a_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("law_2a_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("law_2a_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("law_2a_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("law_2a_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("law_2a_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("law_2a_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("law_2a_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("law_2a_13");
	}
	else if (COMPARE_STRING(name, "law_2b"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("law_2b");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("law_2b_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("law_2b_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("law_2b_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("law_2b_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("law_2b_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("law_2b_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("law_2b_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("law_2b_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("law_2b_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("law_2b_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("law_2b_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("law_2b_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("law_2b_13");
	}
	else if (COMPARE_STRING(name, "law_2c"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("law_2c");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("law_2c_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("law_2c_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("law_2c_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("law_2c_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("law_2c_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("law_2c_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("law_2c_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("law_2c_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("law_2c_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("law_2c_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("law_2c_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("law_2c_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("law_2c_13");
	}
	else if (COMPARE_STRING(name, "law_3"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("law_3");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("law_3_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("law_3_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("law_3_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("law_3_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("law_3_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("law_3_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("law_3_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("law_3_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("law_3_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("law_3_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("law_3_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("law_3_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("law_3_13");
	}
	else if (COMPARE_STRING(name, "law_4"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("law_4");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("law_4_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("law_4_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("law_4_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("law_4_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("law_4_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("law_4_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("law_4_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("law_4_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("law_4_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("law_4_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("law_4_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("law_4_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("law_4_13");
	}
	else if (COMPARE_STRING(name, "phil_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("phil_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("phil_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("phil_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("phil_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("phil_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("phil_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("phil_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("phil_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("phil_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("phil_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("phil_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("phil_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("phil_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("phil_1_13");
	}
	else if (COMPARE_STRING(name, "phil_2"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("phil_2");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("phil_2_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("phil_2_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("phil_2_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("phil_2_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("phil_2_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("phil_2_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("phil_2_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("phil_2_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("phil_2_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("phil_2_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("phil_2_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("phil_2_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("phil_2_13");
	}
	else if (COMPARE_STRING(name, "porn_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("porn_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("porn_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("porn_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("porn_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("porn_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("porn_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("porn_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("porn_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("porn_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("porn_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("porn_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("porn_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("porn_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("porn_1_13");
	}
	else if (COMPARE_STRING(name, "porn_2"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("porn_2");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("porn_2_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("porn_2_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("porn_2_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("porn_2_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("porn_2_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("porn_2_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("porn_2_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("porn_2_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("porn_2_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("porn_2_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("porn_2_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("porn_2_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("porn_2_13");
	}
	else if (COMPARE_STRING(name, "porn_3"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("porn_3");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("porn_3_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("porn_3_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("porn_3_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("porn_3_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("porn_3_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("porn_3_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("porn_3_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("porn_3_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("porn_3_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("porn_3_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("porn_3_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("porn_3_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("porn_3_13");
	}
	else if (COMPARE_STRING(name, "porn_4"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("porn_4");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("porn_4_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("porn_4_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("porn_4_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("porn_4_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("porn_4_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("porn_4_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("porn_4_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("porn_4_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("porn_4_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("porn_4_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("porn_4_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("porn_4_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("porn_4_13");
	}
	else if (COMPARE_STRING(name, "resc_1a"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("resc_1a");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("resc_1a_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("resc_1a_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("resc_1a_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("resc_1a_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("resc_1a_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("resc_1a_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("resc_1a_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("resc_1a_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("resc_1a_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("resc_1a_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("resc_1a_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("resc_1a_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("resc_1a_13");
	}
	else if (COMPARE_STRING(name, "rok_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("rok_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("rok_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("rok_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("rok_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("rok_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("rok_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("rok_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("rok_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("rok_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("rok_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("rok_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("rok_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("rok_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("rok_1_13");
	}
	else if (COMPARE_STRING(name, "rok_2"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("rok_2");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("rok_2_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("rok_2_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("rok_2_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("rok_2_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("rok_2_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("rok_2_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("rok_2_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("rok_2_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("rok_2_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("rok_2_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("rok_2_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("rok_2_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("rok_2_13");
	}
	else if (COMPARE_STRING(name, "rok_3a"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("rok_3a");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("rok_3a_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("rok_3a_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("rok_3a_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("rok_3a_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("rok_3a_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("rok_3a_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("rok_3a_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("rok_3a_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("rok_3a_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("rok_3a_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("rok_3a_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("rok_3a_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("rok_3a_13");
	}
	else if (COMPARE_STRING(name, "stripa"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("stripa");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("stripa_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("stripa_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("stripa_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("stripa_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("stripa_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("stripa_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("stripa_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("stripa_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("stripa_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("stripa_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("stripa_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("stripa_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("stripa_13");
	}
	else if (COMPARE_STRING(name, "tax_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("tax_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("tax_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("tax_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("tax_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("tax_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("tax_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("tax_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("tax_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("tax_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("tax_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("tax_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("tax_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("tax_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("tax_1_13");
	}
	else if (COMPARE_STRING(name, "tex_1"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("tex_1");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("tex_1_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("tex_1_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("tex_1_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("tex_1_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("tex_1_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("tex_1_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("tex_1_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("tex_1_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("tex_1_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("tex_1_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("tex_1_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("tex_1_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("tex_1_13");
	}
	else if (COMPARE_STRING(name, "tex_2"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("tex_2");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("tex_2_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("tex_2_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("tex_2_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("tex_2_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("tex_2_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("tex_2_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("tex_2_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("tex_2_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("tex_2_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("tex_2_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("tex_2_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("tex_2_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("tex_2_13");
	}
	else if (COMPARE_STRING(name, "tex_3"))
	{
		if (torso == 0) // Street
			START_CUTSCENE_NOW("tex_3");
		else if (torso == 1) // Soiree
			START_CUTSCENE_NOW("tex_3_1");
		else if (torso == 2) // Coveralls
			START_CUTSCENE_NOW("tex_3_2");
		else if (torso == 3) // Country Club
			START_CUTSCENE_NOW("tex_3_3");
		else if (torso == 4) // Havana
			START_CUTSCENE_NOW("tex_3_4");
		else if (torso == 5) // Cop
			START_CUTSCENE_NOW("tex_3_5");
		else if (torso == 6) // Bank Job
			START_CUTSCENE_NOW("tex_3_6");
		else if (torso == 7) // Casual
			START_CUTSCENE_NOW("tex_3_7");
		else if (torso == 8) // Mr. Vercetti
			START_CUTSCENE_NOW("tex_3_8");
		else if (torso == 9) // Black tracksuit
			START_CUTSCENE_NOW("tex_3_9");
		else if (torso == 10) // Red tracksuit
			START_CUTSCENE_NOW("tex_3_10");
		else if (torso == 11) // Lance suit
			START_CUTSCENE_NOW("tex_3_11");
		else if (torso == 12) // Sonny suit
			START_CUTSCENE_NOW("tex_3_12");
		else if (torso == 13) // "I Completed Vice City and All I Got Was This Lousy T-shirt"
			START_CUTSCENE_NOW("tex_3_13");
	}
	else
	{
		START_CUTSCENE_NOW(name);
	}
}

#define START_CUTSCENE_NOW CUTSCENES_START_CUTSCENE_NOW

bool CUTSCENES_HAS_CUTSCENE_LOADED(void)
{
	bool result = HAS_CUTSCENE_LOADED();
	if (result)
	{
		G_IS_IN_CUTSCENE = true;
		INCREMENT_INT_STAT(STAT_CUTSCENES_WATCHED, 1);
		if (mission_name_display_duration != 0)
		{
			#if !defined SCRIPTED_CUTSCENES_BEFORE_ACTUAL_CUTSCENES
			PRINT_BIG(mission_name, mission_name_display_duration, 2);
			#elif defined SCRIPTED_CUTSCENES_BEFORE_ACTUAL_CUTSCENES && !defined MISSION_NAME_COMPATIBILITY // Added workaround for PRINT_BIG disappearing after cutscene starts
			uint current_time;
			GET_GAME_TIMER(&current_time);
			uint time_passed = current_time - mission_name_display_start_time;
			if (time_passed < mission_name_display_duration)
			{
				PRINT_BIG(mission_name, mission_name_display_duration - time_passed, 2);
			}
			mission_name_display_start_time = 0;
			#endif
		}
		mission_name_display_duration = 0;
	}
	return result;
}

#define HAS_CUTSCENE_LOADED CUTSCENES_HAS_CUTSCENE_LOADED

bool CUTSCENES_HAS_CUTSCENE_FINISHED(void)
{
	bool result = HAS_CUTSCENE_FINISHED();
	if (result)
	{
		mission_name_display_duration = 0;
		#if defined SCRIPTED_CUTSCENES_BEFORE_ACTUAL_CUTSCENES && !defined MISSION_NAME_COMPATIBILITY
		mission_name_display_start_time = 0;
		#endif
		G_IS_IN_CUTSCENE = false;
	}
	return result;
}

#define HAS_CUTSCENE_FINISHED CUTSCENES_HAS_CUTSCENE_FINISHED

void make_player_safe(void)
{
	if (IS_PLAYER_PLAYING(GetPlayerIndex()))
	{
		G_ONMISSION = 1;
		MAKE_PLAYER_SAFE_FOR_CUTSCENE(GetPlayerIndex());
		// SET_FADING_COLOUR 0 0 0
		DO_SCREEN_FADE_OUT(1500);
		#if !defined MISSION_NAME_COMPATIBILITY
		SWITCH_STREAMING(false);
		#endif
	}
}

void get_fading_status()
{
	while (IS_SCREEN_FADING())
	{
		WAIT(0);
	}

	if (IS_PLAYER_PLAYING(GetPlayerIndex()))
	{
		CLEAR_CHAR_TASKS_IMMEDIATELY(GetPlayerPed());
	}
}

void intro_script_cut(void)
{
    if (IS_PLAYER_PLAYING(GetPlayerIndex()))
    {   
		SET_CHAR_COORDINATES(GetPlayerPed(), 637.021 + MAP_OFFSET_X, -754.877 + MAP_OFFSET_Y, 8.832 + MAP_OFFSET_Z);
		SET_CHAR_HEADING(GetPlayerPed(), 0.1);
		TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 642.789 + MAP_OFFSET_X, -755.855 + MAP_OFFSET_Y, 5.974 + MAP_OFFSET_Z, 2, -2);

    }

    WAIT(1000);
}

void lawyer_script_cut(void)
{
	if (IS_PLAYER_PLAYING(GetPlayerIndex()))
	{	
		G_ONMISSION = 1;
		SET_WIDESCREEN_BORDERS(true);
		Cam camera;
		CREATE_CAM(14, &camera);
		SET_CAM_POS(camera, 91.925 + MAP_OFFSET_X, -818.489 + MAP_OFFSET_Y, 20.000 + MAP_OFFSET_Z + 2.0); // Increased Z by 1.0 to avoid obstruction from the new palm tree model
		POINT_CAM_AT_COORD(camera, 92.866 + MAP_OFFSET_X, -818.736 + MAP_OFFSET_Y, 19.769 + MAP_OFFSET_Z + 2.0); // Increased Z by 1.0 to avoid obstruction from the new palm tree model
		SET_CAM_FOV(camera, 45.0);
		SET_CAM_ACTIVE(camera, 1);
		SET_CAM_PROPAGATE(camera, 1);
		ACTIVATE_SCRIPTED_CAMS(1, 1);
		CLEAR_AREA(119.2 + MAP_OFFSET_X, -826.9 + MAP_OFFSET_Y, 10.0 + MAP_OFFSET_Z, 1.0, true);
		SET_CHAR_COORDINATES(GetPlayerPed(), 119.4 + MAP_OFFSET_X, -827.2 + MAP_OFFSET_Y, 9.7 + MAP_OFFSET_Z);
		SET_CHAR_HEADING(GetPlayerPed(), 230.0);
		TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 123.3 + MAP_OFFSET_X, -829.9 + MAP_OFFSET_Y, 9.7 + MAP_OFFSET_Z, 2, -1);
	}

	WAIT(1000);
}

void baron_script_cut(void)
{
	G_ONMISSION = 1;
	SET_WIDESCREEN_BORDERS(true);
	Cam camera;
	CREATE_CAM(14, &camera);
	SET_CAM_POS(camera, -381.923 + MAP_OFFSET_X, -473.339 + MAP_OFFSET_Y, 48.904 + MAP_OFFSET_Z);
	POINT_CAM_AT_COORD(camera, -381.898 + MAP_OFFSET_X, -474.247 + MAP_OFFSET_Y, 48.486 + MAP_OFFSET_Z); //View of Mansion front
	SET_CAM_FOV(camera, 45.0);
	SET_CAM_ACTIVE(camera, 1);
	SET_CAM_PROPAGATE(camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);

	WAIT(1000);
}

void general_script_cut(void)
{
	G_ONMISSION = 1;
	SET_WIDESCREEN_BORDERS(true);
	Cam camera;
	CREATE_CAM(14, &camera);
	SET_CAM_POS(camera, -229.438 + MAP_OFFSET_X, -1364.204 + MAP_OFFSET_Y, 12.607 + MAP_OFFSET_Z);
	POINT_CAM_AT_COORD(camera, -230.424 + MAP_OFFSET_X, -1364.068 + MAP_OFFSET_Y, 12.511 + MAP_OFFSET_Z); //View of boat
	SET_CAM_FOV(camera, 45.0);
	SET_CAM_ACTIVE(camera, 1);
	SET_CAM_PROPAGATE(camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	Vector3 player_position;
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_position.x, &player_position.y, &player_position.z);
	TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), -251.9 + MAP_OFFSET_X, -1360.8 + MAP_OFFSET_Y, player_position.z, 2, -1);

	WAIT(1000);
}

void porn_script_cut(void)
{
	G_ONMISSION = 1;
	SET_WIDESCREEN_BORDERS(true);
	Cam camera;
	CREATE_CAM(14, &camera);
	SET_CAM_POS(camera, -52.624 + MAP_OFFSET_X, 939.244 + MAP_OFFSET_Y, 10.011 + MAP_OFFSET_Z);
	POINT_CAM_AT_COORD(camera, -53.538 + MAP_OFFSET_X, 938.966 + MAP_OFFSET_Y, 10.306 + MAP_OFFSET_Z); //View of porn studio
	SET_CAM_FOV(camera, 45.0);
	SET_CAM_ACTIVE(camera, 1);
	SET_CAM_PROPAGATE(camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	Vector3 player_position;
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_position.x, &player_position.y, &player_position.z);
	TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), -76.3 + MAP_OFFSET_X, 931.3 + MAP_OFFSET_Y, player_position.z, 2, -1);

	WAIT(1000);
}

void kent_script_cut(void)
{
	G_ONMISSION = 1;
	SET_WIDESCREEN_BORDERS(true);
	Cam camera;
	CREATE_CAM(14, &camera);
	SET_CAM_POS(camera, 499.781 + MAP_OFFSET_X, -106.921 + MAP_OFFSET_Y, 12.057 + MAP_OFFSET_Z);
	POINT_CAM_AT_COORD(camera, 499.357 + MAP_OFFSET_X, -106.019 + MAP_OFFSET_Y, 12.139 + MAP_OFFSET_Z); //View of Malibu
	SET_CAM_FOV(camera, 45.0);
	SET_CAM_ACTIVE(camera, 1);
	SET_CAM_PROPAGATE(camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), 487.8 + MAP_OFFSET_X, -74.3 + MAP_OFFSET_Y, 9.9 + MAP_OFFSET_Z, 2, -1);

	WAIT(1000);
}

void bankjob_script_cut(void)
{
	G_ONMISSION = 1;
	SET_WIDESCREEN_BORDERS(true);
	Cam camera;
	CREATE_CAM(14, &camera);
	SET_CAM_POS(camera, 487.475 + MAP_OFFSET_X, -68.248 + MAP_OFFSET_Y, 11.147 + MAP_OFFSET_Z);
	POINT_CAM_AT_COORD(camera, 486.500 + MAP_OFFSET_X, -68.023 + MAP_OFFSET_Y, 11.150 + MAP_OFFSET_Z); //View of Inside Malibu
	SET_CAM_FOV(camera, 45.0);
	SET_CAM_ACTIVE(camera, 1);
	SET_CAM_PROPAGATE(camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	SET_CHAR_HEADING(GetPlayerPed(), 62.0);

	WAIT(1000);
}

void phil_script_cut(void)
{
	G_ONMISSION = 1;
	SET_WIDESCREEN_BORDERS(true);
	Cam camera;
	CREATE_CAM(14, &camera);
	SET_CAM_POS(camera, -1094.531 + MAP_OFFSET_X, 332.318 + MAP_OFFSET_Y, 14.799 + MAP_OFFSET_Z);
	POINT_CAM_AT_COORD(camera, -1095.238 + MAP_OFFSET_X, 332.993 + MAP_OFFSET_Y, 14.591 + MAP_OFFSET_Z); //View of Phil's caravan
	SET_CAM_FOV(camera, 45.0);
	SET_CAM_ACTIVE(camera, 1);
	SET_CAM_PROPAGATE(camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	Vector3 player_position;
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_position.x, &player_position.y, &player_position.z);
	TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), -1102.7 + MAP_OFFSET_X, 343.4 + MAP_OFFSET_Y, player_position.z, 2, -1);

	WAIT(1000);
}
	
void counter_script_cut(void)
{
	G_ONMISSION = 1;
	SET_WIDESCREEN_BORDERS(true);
	Cam camera;
	CREATE_CAM(14, &camera);
	SET_CAM_POS(camera, -1039.093 + MAP_OFFSET_X, -293.828 + MAP_OFFSET_Y, 27.810 + MAP_OFFSET_Z);
	POINT_CAM_AT_COORD(camera, -1039.811 + MAP_OFFSET_X, -293.283 + MAP_OFFSET_Y, 27.377 + MAP_OFFSET_Z); //View of Print works
	SET_CAM_FOV(camera, 45.0);
	SET_CAM_ACTIVE(camera, 1);
	SET_CAM_PROPAGATE(camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	Vector3 player_position;
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_position.x, &player_position.y, &player_position.z);
	TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), -1070.6 + MAP_OFFSET_X, -278.9 + MAP_OFFSET_Y, player_position.z, 2, -1);

	WAIT(1000);
}

void biker_script_cut(void)
{
	G_ONMISSION = 1;
	SET_WIDESCREEN_BORDERS(true);
	Cam camera;
	CREATE_CAM(14, &camera);
	SET_CAM_POS(camera, -609.208 + MAP_OFFSET_X, 660.793 + MAP_OFFSET_Y, 14.520 + MAP_OFFSET_Z);
	POINT_CAM_AT_COORD(camera, -608.458 + MAP_OFFSET_X, 660.156 + MAP_OFFSET_Y, 14.339 + MAP_OFFSET_Z); //View of Biker Bar
	SET_CAM_FOV(camera, 45.0);
	SET_CAM_ACTIVE(camera, 1);
	SET_CAM_PROPAGATE(camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	Vector3 player_position;
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_position.x, &player_position.y, &player_position.z);
	TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), -597.4 + MAP_OFFSET_X, 651.6 + MAP_OFFSET_Y, player_position.z, 2, -1);

	WAIT(1000);
}

void rock_script_cut(void)
{
	G_ONMISSION = 1;
	SET_WIDESCREEN_BORDERS(true);
	Cam camera;
	CREATE_CAM(14, &camera);
	SET_CAM_POS(camera, -870.590 + MAP_OFFSET_X, 1155.257 + MAP_OFFSET_Y, 10.356 + MAP_OFFSET_Z);
	POINT_CAM_AT_COORD(camera, -871.349 + MAP_OFFSET_X, 1155.864 + MAP_OFFSET_Y, 10.592 + MAP_OFFSET_Z); //View of Recording studio
	SET_CAM_FOV(camera, 45.0);
	SET_CAM_ACTIVE(camera, 1);
	SET_CAM_PROPAGATE(camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	Vector3 player_position;
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_position.x, &player_position.y, &player_position.z);
	TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), -883.1 + MAP_OFFSET_X, 1159.2 + MAP_OFFSET_Y, player_position.z, 2, -1);

	WAIT(1000);
}

void cuban_script_cut(void)
{
	G_ONMISSION = 1;
	SET_WIDESCREEN_BORDERS(true);
	Cam camera;
	CREATE_CAM(14, &camera);
	SET_CAM_POS(camera, -1179.528 + MAP_OFFSET_X, -605.912 + MAP_OFFSET_Y, 12.220 + MAP_OFFSET_Z);
	POINT_CAM_AT_COORD(camera, -1178.774 + MAP_OFFSET_X, -606.569 + MAP_OFFSET_Y, 12.223 + MAP_OFFSET_Z); //View of Cuban Cafe
	SET_CAM_FOV(camera, 45.0);
	SET_CAM_ACTIVE(camera, 1);
	SET_CAM_PROPAGATE(camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	SET_CHAR_COORDINATES(GetPlayerPed(), -1166.3 + MAP_OFFSET_X, -634.4 + MAP_OFFSET_Y, 10.6 + MAP_OFFSET_Z);

	WAIT(1000);
}

void haitian_script_cut(void)
{
	G_ONMISSION = 1;
	SET_WIDESCREEN_BORDERS(true);
	Cam camera;
	CREATE_CAM(14, &camera);
	SET_CAM_POS(camera, -969.554 + MAP_OFFSET_X, 139.730 + MAP_OFFSET_Y, 10.058 + MAP_OFFSET_Z);
	POINT_CAM_AT_COORD(camera, -968.921 + MAP_OFFSET_X, 140.503 + MAP_OFFSET_Y, 10.031 + MAP_OFFSET_Z); //View of Haitian shack
	SET_CAM_FOV(camera, 45.0);
	SET_CAM_ACTIVE(camera, 1);
	SET_CAM_PROPAGATE(camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	Vector3 player_position;
	GET_CHAR_COORDINATES(GetPlayerPed(), &player_position.x, &player_position.y, &player_position.z);
	TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), -962.6 + MAP_OFFSET_X, 146.1 + MAP_OFFSET_Y, player_position.z, 2, -1);

	WAIT(1000);
}

void taxiwar_script_cut(void)
{
	G_ONMISSION = 1;
	SET_PLAYER_CONTROL(GetPlayerIndex(), false);
	SET_WIDESCREEN_BORDERS(true);
	Cam camera;
	CREATE_CAM(14, &camera);
	SET_CAM_POS(camera, -994.919 + MAP_OFFSET_X, 210.472 + MAP_OFFSET_Y, 15.758 + MAP_OFFSET_Z);
	POINT_CAM_AT_COORD(camera, -995.722 + MAP_OFFSET_X, 210.020 + MAP_OFFSET_Y, 15.370 + MAP_OFFSET_Z);
	SET_CAM_FOV(camera, 45.0);
	SET_CAM_ACTIVE(camera, 1);
	SET_CAM_PROPAGATE(camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
}

void sergio_script_cut()
{
	SET_PLAYER_CONTROL(GetPlayerIndex(), false);
	SET_WIDESCREEN_BORDERS(true);

	CLEAR_AREA(299.0 + MAP_OFFSET_X, -205.0 + MAP_OFFSET_Y, 10.5 + MAP_OFFSET_Z, 5.0, true);
	CLEAR_AREA(305.0 + MAP_OFFSET_X, -219.5 + MAP_OFFSET_Y, 10.5 + MAP_OFFSET_Z, 10.0, true);
	SET_CHAR_COORDINATES(GetPlayerPed(), 299.0 + MAP_OFFSET_X, -205.0 + MAP_OFFSET_Y, 10.5 + MAP_OFFSET_Z);
	SET_CHAR_HEADING(GetPlayerPed(), 230.0);

	Cam static_camera;
	CREATE_CAM(14, &static_camera);
	SET_CAM_POS(static_camera, 297.0 + MAP_OFFSET_X, -204.7 + MAP_OFFSET_Y, 13.0 + MAP_OFFSET_Z);
	POINT_CAM_AT_COORD(static_camera, 318.5 + MAP_OFFSET_X, -219.23 + MAP_OFFSET_Y, 22.4 + MAP_OFFSET_Z);
	SET_CAM_FOV(static_camera, 45.0);
	SET_CAM_ACTIVE(static_camera, 1);
	SET_CAM_PROPAGATE(static_camera, 1);
	ACTIVATE_SCRIPTED_CAMS(1, 1);
	REQUEST_MODEL(MODEL_STRETCH);
	LOAD_SCENE(270.0 + MAP_OFFSET_X, -218.0 + MAP_OFFSET_Y, 13.4 + MAP_OFFSET_Z);
	while (!HAS_MODEL_LOADED(MODEL_STRETCH))
	{
		WAIT(0);
	}

	CLEAR_AREA(306.9 + MAP_OFFSET_X, -241.65 + MAP_OFFSET_Y, 12.3 + MAP_OFFSET_Z, 15.0, true);
	Vehicle scripted_cut_limo;
	CREATE_CAR(MODEL_STRETCH, 306.9 + MAP_OFFSET_X, -241.65 + MAP_OFFSET_Y, 12.3 + MAP_OFFSET_Z, &scripted_cut_limo, true);
	CHANGE_CAR_COLOUR(scripted_cut_limo, 0, 0);
	SET_CAR_HEADING(scripted_cut_limo, 0.0);

	DO_SCREEN_FADE_IN(1500);
	while (IS_SCREEN_FADING())
	{
		WAIT(0);
	}
	if (!IS_CAR_DEAD(scripted_cut_limo))
	{
		SET_CAR_FORWARD_SPEED(scripted_cut_limo, 15.0 - 3.0); // Reduced speed by 3.0 to prevent limo from hitting the wall
		TASK_CAR_TEMP_ACTION(INVALID_HANDLE, scripted_cut_limo, 9, 8000);
	}
	SETTIMERA(0);
	while (TIMERA() < 1000)
	{
		WAIT(0);
	}
	if (!IS_CAR_DEAD(scripted_cut_limo))
	{
		Cam dynamic_camera;
		CREATE_CAM(14, &dynamic_camera);
		SET_CAM_POS(dynamic_camera, 297.0 + MAP_OFFSET_X, -204.7 + MAP_OFFSET_Y, 13.0 + MAP_OFFSET_Z);
		POINT_CAM_AT_VEHICLE(dynamic_camera, scripted_cut_limo);
		SET_CAM_FOV(dynamic_camera, 45.0);
		SET_CAM_ACTIVE(dynamic_camera, 1);

		Cam interpolating_camera;
		CREATE_CAM(3, &interpolating_camera);
		SET_CAM_FOV(interpolating_camera, 45.0);
		SET_CAM_INTERP_STYLE_CORE(interpolating_camera, static_camera, dynamic_camera, 1000, 0);
        SET_CAM_ACTIVE(interpolating_camera, 1);
        SET_CAM_PROPAGATE(interpolating_camera, 1);

		while (IS_CAM_INTERPOLATING())
		{
			WAIT(0);
		}

		SET_CAM_ACTIVE(interpolating_camera, 0);
		SET_CAM_ACTIVE(static_camera, 0);

        SET_CAM_PROPAGATE(dynamic_camera, 1);
	}
	SETTIMERA(0);
	while (TIMERA() < 3000)
	{
		WAIT(0);
	}
	if (!IS_CAR_DEAD(scripted_cut_limo))
	{
		Vector3 vect;
		GET_CAR_COORDINATES(scripted_cut_limo, &vect.x, &vect.y, &vect.z);
		TASK_GO_STRAIGHT_TO_COORD(GetPlayerPed(), vect.x, vect.y, vect.z, 2, -1);
	}
	DO_SCREEN_FADE_OUT(1500);
	while (IS_SCREEN_FADING())
	{
		WAIT(0);
	}
	DELETE_CAR(&scripted_cut_limo);
	MARK_MODEL_AS_NO_LONGER_NEEDED(MODEL_STRETCH);
	// RESTORE_CAMERA
	CLEAR_CHAR_TASKS_IMMEDIATELY(GetPlayerPed());
	// CHAR_SET_IDLE scplayer
	SETTIMERA(0);
}

void start_scripted_cutscene(char *gxt_entry, uint duration, uint cutscene)
{
	mission_name = gxt_entry;
	mission_name_display_duration = duration;
	#if defined SCRIPTED_CUTSCENES_BEFORE_ACTUAL_CUTSCENES
	if (IS_PLAYER_PLAYING(GetPlayerIndex()))
	{
		if (G_ONMISSION == 0)
		{
			if (CAN_PLAYER_START_MISSION(GetPlayerIndex()))
			{
				G_ONMISSION = 1;
				MAKE_PLAYER_SAFE_FOR_CUTSCENE(GetPlayerIndex());
				if (cutscene == CUTSCENE_INTRO)
				{
					intro_script_cut();
				}
				else if (cutscene == CUTSCENE_LAWYER)
				{
					lawyer_script_cut();
				}
				else if (cutscene == CUTSCENE_BARON)
				{
					baron_script_cut();
				}
				else if (cutscene == CUTSCENE_GENERAL)
				{
					general_script_cut();
				}
				else if (cutscene == CUTSCENE_PORN)
				{
					porn_script_cut();
				}
				else if (cutscene == CUTSCENE_KENT)
				{
					kent_script_cut();
				}
				else if (cutscene == CUTSCENE_BANKJOB)
				{
					bankjob_script_cut();
				}
				else if (cutscene == CUTSCENE_PHIL)
				{
					phil_script_cut();
				}
				else if (cutscene == CUTSCENE_COUNTER)
				{
					counter_script_cut();
				}
				else if (cutscene == CUTSCENE_BIKER)
				{
					biker_script_cut();
				}
				else if (cutscene == CUTSCENE_ROCK)
				{
					rock_script_cut();
				}
				else if (cutscene == CUTSCENE_CUBAN)
				{
					cuban_script_cut();
				}
				else if (cutscene == CUTSCENE_HAITIAN)
				{
					haitian_script_cut();
				}
				else if (cutscene == CUTSCENE_TAXIWAR)
				{
					taxiwar_script_cut();
				}
				make_player_safe();
				#if !defined MISSION_NAME_COMPATIBILITY // Added workaround for PRINT_BIG disappearing after cutscene starts
				GET_GAME_TIMER(&mission_name_display_start_time);
				#endif
				PRINT_BIG(gxt_entry, duration, 2);
				get_fading_status();
				if (cutscene == CUTSCENE_SERGIO)
				{
					sergio_script_cut();
				}
				ACTIVATE_SCRIPTED_CAMS(0, 0);
				DESTROY_ALL_CAMS();
				SET_CAM_BEHIND_PED(GetPlayerPed());
				SET_WIDESCREEN_BORDERS(0);
				#if !defined MISSION_NAME_COMPATIBILITY
				SWITCH_STREAMING(true);
				#endif
			}
		}
	}
	#endif
}