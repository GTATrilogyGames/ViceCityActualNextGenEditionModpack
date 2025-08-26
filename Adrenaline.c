#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"

#define TOUCH_DISTANCE 1.0
#define RESPAWN_TIME 300

struct pill {
	int number;
	Object var;
	int resp_time;
};

struct pill pills[16];

void pill_coords(int num, float* x, float* y, float* z) {
	if (num == 1) { *x = 881.880; *y = 550.025; *z = 6.022; }
	else if (num == 2) { *x = 901.465; *y = 69.180; *z = 5.771; }
	else if (num == 3) { *x = 394.585; *y = -405.380; *z = 5.425; }
	else if (num == 4) { *x = 858.395; *y = 754.036; *z = 11.140; }
	else if (num == 5) { *x = 817.405; *y = 1285.265; *z = 6.709; }
	else if (num == 6) { *x = 861.446; *y = 1480.155; *z = 8.177; }
	else if (num == 7) { *x = 51.289; *y = 1598.780; *z = 7.985; }
	else if (num == 8) { *x = -297.527; *y = 1763.216; *z = 19.094; }
	else if (num == 9) { *x = -407.606; *y = 1274.375; *z = 6.257; }
	else if (num == 10) { *x = -447.139; *y = 644.287; *z = 4.338; }
	else if (num == 11) { *x = -662.356; *y = 632.375; *z = 7.773; }
	else if (num == 12) { *x = -424.879; *y = 449.549; *z = 6.526; }
	else if (num == 13) { *x = -533.790; *y = 470.359; *z = 5.950; }
	else if (num == 14) { *x = -587.643; *y = -14.465; *z = 6.182; }
	else if (num == 15) { *x = 58.706; *y = 29.815; *z = 7.055; }
	else if (num == 16) { *x = 90.406; *y = -54.885; *z = 31.900; }
}

void create_pill(struct pill* p) {
	REQUEST_MODEL(GET_HASH_KEY("adrenaline"));
	while (!HAS_MODEL_LOADED(GET_HASH_KEY("adrenaline"))) WAIT(0);
	REQUEST_ANIMS("Pickup_disc");
	while (!HAVE_ANIMS_LOADED("Pickup_disc")) WAIT(0);
	float x, y, z;
	pill_coords(p->number, &x, &y, &z);
	CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("adrenaline"), x, y, z, &(p->var), 1);
	PLAY_OBJECT_ANIM(p->var, "Pickup_disc", "pickup_disc", 10.0, 1, 0);  // ✅ FIXED
}

void apply_adrenaline_effect() {
	SETTIMERB(0);
	while (TIMERB() < 12700) {
		SET_TIME_SCALE(0.3);
		if (IS_CHAR_DEAD(GetPlayerPed()) || HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())) {
			break;
		}
		WAIT(0);
	}
	SET_TIME_SCALE(1.0);
}

void touch_pill(struct pill* p) {
	DELETE_OBJECT(&(p->var));
	PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
	p->resp_time = RESPAWN_TIME;
	apply_adrenaline_effect();
}

void monitor_pill(struct pill* p) {
	if (p->var == INVALID_HANDLE) return;

	float px, py, pz, ox, oy, oz, dist;
	GET_CHAR_COORDINATES(GetPlayerPed(), &px, &py, &pz);
	pill_coords(p->number, &ox, &oy, &oz);
	GET_DISTANCE_BETWEEN_COORDS_3D(px, py, pz, ox, oy, oz, &dist);
	if (dist < TOUCH_DISTANCE) {
		touch_pill(p);
	}
}

void decrement_respawns() {
	int i;
	for (i = 0; i < 16; i++) {
		if (pills[i].resp_time > 0) {
			pills[i].resp_time -= 1;
		}
	}
}

void check_respawns() {
	int i;
	for (i = 0; i < 16; i++) {
		if (pills[i].var == INVALID_HANDLE && pills[i].resp_time <= 0) {
			create_pill(&pills[i]);
		}
	}
}

void monitor() {
	SETTIMERA(0);
	while (1) {
		int i;
		for (i = 0; i < 16; i++) {
			monitor_pill(&pills[i]);
		}
		if (TIMERA() >= 1000) {
			decrement_respawns();
			check_respawns();
			SETTIMERA(0);
		}
		WAIT(0);
	}
}

void main(void) {
	THIS_SCRIPT_SHOULD_BE_SAVED();

	int i;
	for (i = 0; i < 16; i++) {
		pills[i].number = i + 1;
		pills[i].resp_time = 0;
		pills[i].var = INVALID_HANDLE;
	}

	monitor();
}
