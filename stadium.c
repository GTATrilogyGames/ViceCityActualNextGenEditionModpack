#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"


void autosave()		/*rebusx*/
{
	DO_AUTO_SAVE();
	WAIT(500);
}


void main(void) {
	int stadium_door_1, stadium_door_2, stadium_poster;
	int hours_s, minutes_s, day_flag, flag_stadium_doors, day_counter;
	
	REQUEST_MODEL(GET_HASH_KEY("dtn_staddoora"));
	REQUEST_MODEL(GET_HASH_KEY("dtn_staddoorb"));
	REQUEST_MODEL(GET_HASH_KEY("dthotring_a"));
	REQUEST_MODEL(GET_HASH_KEY("dtbloodring_a"));
	REQUEST_MODEL(GET_HASH_KEY("dtdirtring_a"));
	while ((!HAS_MODEL_LOADED(GET_HASH_KEY("dtn_staddoora"))) || (!HAS_MODEL_LOADED(GET_HASH_KEY("dtn_staddoorb"))) || (!HAS_MODEL_LOADED(GET_HASH_KEY("dthotring_a"))) || (!HAS_MODEL_LOADED(GET_HASH_KEY("dtbloodring_a"))) || (!HAS_MODEL_LOADED(GET_HASH_KEY("dtdirtring_a")))) {
		WAIT(0);
	}
	CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("dtn_staddoora"), -676.615, 1863.097, 15.372, &stadium_door_1, 1);
	FREEZE_OBJECT_POSITION(stadium_door_1, 1);
	DONT_REMOVE_OBJECT(stadium_door_1);
	CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("dtn_staddoorb"), -676.615, 1864.932, 15.372, &stadium_door_2, 1);
	FREEZE_OBJECT_POSITION(stadium_door_2, 1);
	DONT_REMOVE_OBJECT(stadium_door_2);
	CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("dthotring_a"), -604.08, 1873.258, 31.552, &stadium_poster, 1);
	FREEZE_OBJECT_POSITION(stadium_poster, 1);
	DONT_REMOVE_OBJECT(stadium_poster);
	
	while (true) {
		WAIT(0);
		GET_TIME_OF_DAY(&hours_s, &minutes_s);
		if (hours_s > 19) {
			if (G_ONMISSION == 0) {
				if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
					if (day_flag == 0) {
						day_flag = 1;
					}
					if (flag_stadium_doors == 1) {
						SET_OBJECT_HEADING(stadium_door_1, 90.0);
						SET_OBJECT_HEADING(stadium_door_2, -90.0);
						flag_stadium_doors = 0;
					}
					if (LOCATE_CHAR_ON_FOOT_3D(GetPlayerPed(), -677.3314, 1864.0956, 15.1119, 2.0, 2.0, 2.0, 0)) {
						G_ONMISSION = 1;
						DO_SCREEN_FADE_OUT(1500);
						while (IS_SCREEN_FADING()) {
							WAIT(0);
						}
						if (day_counter == 0) {
							int prev_passed_flag = G_HOTRING;
							REQUEST_SCRIPT("ovalring");
							while (!HAS_SCRIPT_LOADED("ovalring")) WAIT(0);
							uint script = START_NEW_SCRIPT("ovalring", 1024);
							MARK_SCRIPT_AS_NO_LONGER_NEEDED("ovalring");
							while (IS_THREAD_ACTIVE(script)) WAIT(0);
							SET_TIME_OF_DAY(1, 0);
							G_ONMISSION = 0;
							if ((prev_passed_flag == 0) && (G_HOTRING > prev_passed_flag))
							{
								autosave();		/*rebusx*/
							}
						}
						if (day_counter == 1) {
							int prev_passed_flag = G_BLOODRING;
							REQUEST_SCRIPT("bloodring");
							while (!HAS_SCRIPT_LOADED("bloodring")) WAIT(0);
							uint script = START_NEW_SCRIPT("bloodring", 1024);
							MARK_SCRIPT_AS_NO_LONGER_NEEDED("bloodring");
							while (IS_THREAD_ACTIVE(script)) WAIT(0);
							SET_TIME_OF_DAY(1, 0);
							G_ONMISSION = 0;
							if ((prev_passed_flag == 0) && (G_BLOODRING > prev_passed_flag))
							{
								autosave();		/*rebusx*/
							}
						}
						if (day_counter == 2) {
							int prev_passed_flag = G_DIRTRING;
							REQUEST_SCRIPT("kickstart");
							while (!HAS_SCRIPT_LOADED("kickstart")) WAIT(0);
							uint script = START_NEW_SCRIPT("kickstart", 1024);
							MARK_SCRIPT_AS_NO_LONGER_NEEDED("kickstart");
							while (IS_THREAD_ACTIVE(script)) WAIT(0);
							SET_TIME_OF_DAY(1, 0);
							G_ONMISSION = 0;
							if ((prev_passed_flag == 0) && (G_DIRTRING > prev_passed_flag))
							{
								autosave();		/*rebusx*/
							}
						}
					}
				}
			} else {
				if (flag_stadium_doors == 0) {
					if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
						if (!IS_CHAR_IN_AREA_3D(GetPlayerPed(), -685.978, 1859.515, 14.076, -675.978, 1868.515, 18.076, 0)) {
							SET_OBJECT_HEADING(stadium_door_1, 0.0);
							SET_OBJECT_HEADING(stadium_door_2, 0.0);
							flag_stadium_doors = 1;
						}
					}
				}
			}
		} else {
			if (flag_stadium_doors == 0) {
				if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
					if (!IS_CHAR_IN_AREA_3D(GetPlayerPed(), -685.978, 1859.515, 14.076, -675.978, 1868.515, 18.076, 0)) {
						SET_OBJECT_HEADING(stadium_door_1, 0.0);
						SET_OBJECT_HEADING(stadium_door_2, 0.0);
						flag_stadium_doors = 1;
					}
				}
			}
			if (day_flag == 1) {
				day_counter++;
				if (day_counter == 3) {
					day_counter = 0;
				}
				if (day_counter == 0) {
					DELETE_OBJECT(&stadium_poster);
					CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("dthotring_a"), -604.08, 1873.258, 31.552, &stadium_poster, 1);
					FREEZE_OBJECT_POSITION(stadium_poster, 1);
					DONT_REMOVE_OBJECT(stadium_poster);
				}
				if (day_counter == 1) {
					DELETE_OBJECT(&stadium_poster);
					CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("dtbloodring_a"), -604.08, 1873.258, 31.552, &stadium_poster, 1);
					FREEZE_OBJECT_POSITION(stadium_poster, 1);
					DONT_REMOVE_OBJECT(stadium_poster);
				}
				if (day_counter == 2) {
					DELETE_OBJECT(&stadium_poster);
					CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("dtdirtring_a"), -604.08, 1873.258, 31.552, &stadium_poster, 1);
					FREEZE_OBJECT_POSITION(stadium_poster, 1);
					DONT_REMOVE_OBJECT(stadium_poster);
				}
				day_flag = 0;
			}
		}
	}
}