#include <natives.h>
#include <types.h>
#include <consts.h>
#include "features.h"

void load_script(char *name)
{
	if (GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT(name) == 0)
	{
		REQUEST_SCRIPT(name);
		while (!HAS_SCRIPT_LOADED(name))
		{
			WAIT(0);
		}
		uint script = START_NEW_SCRIPT(name, 1024);
		MARK_SCRIPT_AS_NO_LONGER_NEEDED(name);	
	}
}

void main(void)
{
	THIS_SCRIPT_SHOULD_BE_SAVED();
	while (true)
	{
		if (GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT("save") == 0)
		{
			DO_SCREEN_FADE_OUT_UNHACKED(0);
		}

		load_script("traffic");
		load_script("LAWYER");
		load_script("AVERY");
		load_script("CORTEZ");
		load_script("DIAZ");
		load_script("PROTECT");
		load_script("KAUFMAN");
		load_script("ROCK");
		load_script("BIKE");
		load_script("PRON");
		load_script("COKERUN");
		load_script("ICECREAM");
		load_script("MALIBU");
		load_script("WORLD");
		#if defined BRIBES_STICKY_WANTED_ZONE_COMPATIBILITY
		load_script("bribestar_wanted");
		#endif
		load_script("PHIL");
		load_script("COUNT");
		load_script("CUBAN");
		load_script("HAITI");
		load_script("street_phone");
		load_script("sunshine_garages");
		load_script("sunshine_race");
		load_script("STRIP");
		load_script("business_sale");
		load_script("pickups");
		load_script("stadium");
		load_script("packages");
		load_script("save");
		load_script("mob_phone");
		load_script("intro");
		load_script("map_bounds");
		load_script("ambstreams");
		load_script("weap_sounds");
		load_script("side_quests");
		load_script("cheats");
		load_script("vc_sounds");
		load_script("vc_jump");
		WAIT(100);
	}
	return;
}
