#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
int ready_to_shark, shark_obj, state, curAnim, sID;
float px, py, pz, wh, heading;

void shark_event(void) {
	while (true) {
		WAIT(0);
		if (G_DIAZ < 3) {
			if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1939.0, -1782.0, 2227.0, 2684.0, 0)) {
				if ((!IS_CHAR_IN_AREA_2D(GetPlayerPed(), -582.0, -1782.0, -82.0, -157, 0)) && (!IS_CHAR_IN_AREA_2D(GetPlayerPed(), -530.0, -163.0, -281.0, 281.0, 0)) && (!IS_CHAR_IN_AREA_2D(GetPlayerPed(), -530.0, 264.0, -61.0, 869.0, 0)) && (!IS_CHAR_IN_AREA_2D(GetPlayerPed(), -402.0, 863.0, 41.0, 1327.0, 0)) && (!IS_CHAR_IN_AREA_2D(GetPlayerPed(), -270.0, 1313.0, 198.0, 2684.0, 0)) ) {
					ready_to_shark = 0;
					state = 0;
					return;
				}
			}	
		} else {
			if (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1939.0, -1782.0, 2227.0, 2684.0, 0)) {
				ready_to_shark = 0;
				state = 0;
				return;
			}
		}
		if ((IS_CHAR_SWIMMING(GetPlayerPed())) && (!IS_CHAR_IN_ANY_CAR(GetPlayerPed())) && (!IS_CHAR_IN_ANY_HELI(GetPlayerPed())) && (!IS_CHAR_IN_ANY_BOAT(GetPlayerPed())) ) {
			ready_to_shark = 1;
		} else {
			if (state != 6) {
				ready_to_shark = 0;
				state = 0;
			}
		}
		
		if (ready_to_shark == 1) {
			if (state == 0) {
				SETTIMERC(0);
				state++;
			} else if (state == 1) {
				if (TIMERC() > 5000) {
					state++;
				}
			} else if (state == 2) {
				GET_CHAR_COORDINATES(GetPlayerPed(), &px, &py, &pz);
				GET_CHAR_HEADING(GetPlayerPed(), &heading);
				GET_WATER_HEIGHT(px, py, pz, &wh);						
				CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("shark_ocean"), px, py, wh - 0.5, &shark_obj, 1);
				SET_OBJECT_HEADING(shark_obj, heading);
				GENERATE_RANDOM_INT_IN_RANGE(1, 7, &curAnim);
				if (curAnim == 1) {
					PLAY_OBJECT_ANIM(shark_obj, "near_left", "shark_anims", 10.0, 0, 1);
				} else if (curAnim == 2) {
					PLAY_OBJECT_ANIM(shark_obj, "near_right", "shark_anims", 10.0, 0, 1);
				} else if (curAnim == 3) {
					PLAY_OBJECT_ANIM(shark_obj, "near_right_front", "shark_anims", 10.0, 0, 1);
				} else if (curAnim == 4) {
					PLAY_OBJECT_ANIM(shark_obj, "near_left_front", "shark_anims", 10.0, 0, 1);
				} else if (curAnim == 5) {
					PLAY_OBJECT_ANIM(shark_obj, "near_front1", "shark_anims", 10.0, 0, 1);
				} else if (curAnim == 6) {
					PLAY_OBJECT_ANIM(shark_obj, "near_front2", "shark_anims", 10.0, 0, 1);
				}
				state++;
			} else if (state == 3) {
				if (curAnim == 1) {
					if (!IS_OBJECT_PLAYING_ANIM(shark_obj, "near_left", "shark_anims")) {
						DELETE_OBJECT(&shark_obj);
						state++;
					}
				} else if (curAnim == 2) {
					if (!IS_OBJECT_PLAYING_ANIM(shark_obj, "near_right", "shark_anims")) {
						DELETE_OBJECT(&shark_obj);
						state++;
					}
				} else if (curAnim == 3) {
					if (!IS_OBJECT_PLAYING_ANIM(shark_obj, "near_right_front", "shark_anims")) {
						DELETE_OBJECT(&shark_obj);
						state++;
					}
				} else if (curAnim == 4) {
					if (!IS_OBJECT_PLAYING_ANIM(shark_obj, "near_left_front", "shark_anims")) {
						DELETE_OBJECT(&shark_obj);
						state++;
					}
				} else if (curAnim == 5) {
					if (!IS_OBJECT_PLAYING_ANIM(shark_obj, "near_front1", "shark_anims")) {
						DELETE_OBJECT(&shark_obj);
						state++;
					}
				} else if (curAnim == 6) {
					if (!IS_OBJECT_PLAYING_ANIM(shark_obj, "near_front2", "shark_anims")) {
						DELETE_OBJECT(&shark_obj);
						state++;
					}
				}
			} else if (state == 4) {
				if (TIMERC() > 15000) {
					state++;
				}
			} else if (state == 5) {
				GET_CHAR_COORDINATES(GetPlayerPed(), &px, &py, &pz);
				GET_CHAR_HEADING(GetPlayerPed(), &heading);
				CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("shark_ocean"), px, py, pz, &shark_obj, 1);
				SET_OBJECT_HEADING(shark_obj, heading);
				FREEZE_CHAR_POSITION(GetPlayerPed(), 1);
				FREEZE_OBJECT_POSITION(shark_obj, 1);
				PLAY_OBJECT_ANIM(shark_obj, "shark_attack", "shark_anims", 10.0, 0, 1);
				TASK_PLAY_ANIM_NON_INTERRUPTABLE(GetPlayerPed(), "player_attack", "shark_anims", 8.0, 0, 0, 1, 0, -1);
				PLAY_SOUND_FRONTEND(sID, "SCRIPT_MISSION_SHARK_ATTACK");
				state++;
			} else if (state == 6) {
				if (!IS_CHAR_PLAYING_ANIM(GetPlayerPed(), "shark_anims", "player_attack")) {
					FREEZE_CHAR_POSITION(GetPlayerPed(), 0);
					FREEZE_OBJECT_POSITION(shark_obj, 0);
					DELETE_OBJECT(&shark_obj);
					EXPLODE_CHAR_HEAD(GetPlayerPed());
					state++;
					return;
				}
			}
		}
	}
}

void engine_event(void) {
	int veh;
	STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &veh);
	SET_ENGINE_HEALTH(veh, 0.0);
	SET_CAR_ENGINE_ON(veh, 0, 0);
	MARK_CAR_AS_NO_LONGER_NEEDED(&veh);
	return;
}

void main(void) {
	WAIT(0);
	REQUEST_MODEL(GET_HASH_KEY("shark_ocean"));
	while (!HAS_MODEL_LOADED(GET_HASH_KEY("shark_ocean"))) WAIT(0);	
	REQUEST_ANIMS("shark_anims");
	while (!HAVE_ANIMS_LOADED("shark_anims")) WAIT(0);
	while (!REQUEST_AMBIENT_AUDIO_BANK("SCRIPT_MISSION/SHARK_EVENT")) {
		WAIT(0);
	}
	sID = GET_SOUND_ID();
	while (true) {
		WAIT(0);
		if (G_DIAZ < 3) {
			if ((IS_CHAR_IN_AREA_2D(GetPlayerPed(), -582.0, -1782.0, -82.0, -157.0, 0)) || (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -530.0, -163.0, -281.0, 281.0, 0)) || (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -530.0, 264.0, -61.0, 869.0, 0)) || (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -402.0, 863.0, 41.0, 1327.0, 0)) || (IS_CHAR_IN_AREA_2D(GetPlayerPed(), -270.0, 1313.0, 198.0, 2684.0, 0)) ) {
				if ((IS_CHAR_IN_ANY_HELI(GetPlayerPed())) || (IS_CHAR_IN_ANY_BOAT(GetPlayerPed()))) {
					engine_event();
				} else {
					shark_event();	
					state = 5;
				}
			}
		}
		if ((IS_CHAR_IN_ANY_CAR(GetPlayerPed())) || (IS_CHAR_IN_ANY_HELI(GetPlayerPed())) || (IS_CHAR_IN_ANY_BOAT(GetPlayerPed()))) {
			if (!IS_CHAR_IN_AREA_2D(GetPlayerPed(), -3000.0, -3000.0, 3000.0, 3000.0, 0)) {
				engine_event();
			}
		} else {
			if (!IS_CHAR_IN_AREA_2D(GetPlayerPed(), -1939.0, -1782.0, 2227.0, 2684.0, 0)) {
				shark_event();	
			}
		}
	}
}