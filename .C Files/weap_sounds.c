#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>z

int sState = 0;
int plWeap;
int cooldown = 0;
int lastAudio = -1;

#define AUDIO_LOW     0
#define AUDIO_HIGH    1
#define AUDIO_START   2
#define AUDIO_TOHIGH  3
#define AUDIO_TOLOW   4
#define AUDIO_OFF     5
#define AUDIO_PRELOAD 100

int isWeaponActive() {
	return plWeap == WEAPON_FTHROWER;
}

void forceStopMoviePlayback() {
	STOP_STREAM();
	RELEASE_MOVIE();
	WAIT(5);
	SET_CURRENT_MOVIE("");
	lastAudio = -1;
	cooldown = 0;
}

void playAudioOnce(int id, char* name) {
	if (!isWeaponActive()) return;

	if (id != lastAudio && cooldown == 0) {
		forceStopMoviePlayback();
		SET_CURRENT_MOVIE(name);
		PLAY_MOVIE();
		lastAudio = id;
		cooldown = 25;
	}
	else if (id == lastAudio && cooldown == 0) {
		PLAY_MOVIE();
		cooldown = 25;
	}
}

void main(void) {
	SETTIMERA(0);
	SETTIMERC(0);

	while (true) {
		WAIT(10);
		if (cooldown > 0) cooldown--;

		GET_CURRENT_CHAR_WEAPON(GetPlayerPed(), &plWeap);

		
		if (!isWeaponActive() && sState != 0 && sState != 99) {
			forceStopMoviePlayback();
			sState = 99;
			SETTIMERC(0);
			continue;
		}

		if (sState == 0) {
			if (isWeaponActive()) {
				SETTIMERC(0);
				sState = AUDIO_PRELOAD;
			}
		}

		else if (sState == AUDIO_PRELOAD) {
			if (!isWeaponActive()) {
				sState = 0;
			}
			else if (TIMERC() > 50) {
				SET_CURRENT_MOVIE("audio/START");
				forceStopMoviePlayback(); //
				sState = 1;
			}
		}

		else if (sState == 1) {
			if (TIMERC() > 716) {
				SETTIMERA(0);
				sState = 2;
			}
			else {
				playAudioOnce(AUDIO_START, "audio/START");
			}
		}

		else if (sState == 2) {
			if (IS_CONTROL_PRESSED(2, 4)) {
				SETTIMERC(0);
				sState = 3;
				playAudioOnce(AUDIO_TOHIGH, "audio/TOHIGH");
			}
			else {
				playAudioOnce(AUDIO_LOW, "audio/LOW");
			}
		}

		else if (sState == 3) {
			SETTIMERA(0);
			sState = 4;
		}

		else if (sState == 4) {
			if (!IS_CONTROL_PRESSED(2, 4)) {
				forceStopMoviePlayback();
				SETTIMERC(0);
				sState = 5;
				playAudioOnce(AUDIO_TOLOW, "audio/TOLOW");
			}
			else {
				playAudioOnce(AUDIO_HIGH, "audio/HIGH");
			}
		}

		else if (sState == 5) {
			SET_CHAR_AMMO(GetPlayerPed(), WEAPON_FTHROWER, AMMO_MAX);
			if (TIMERC() > 90) {
				SETTIMERA(0);
				sState = 2;
			}
		}

		else if (sState == 99) {
			if (lastAudio != -1) {
				playAudioOnce(AUDIO_OFF, "audio/OFF");
			}

			if (TIMERC() > 369) {
				forceStopMoviePlayback();
				sState = 0;
				SETTIMERA(0);
				SETTIMERC(0);
			}
		}
	}
}
