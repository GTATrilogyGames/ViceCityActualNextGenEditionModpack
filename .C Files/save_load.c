#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"

void main(void)
{
	if (G_LAWYER >= 1)
	{
		SET_CHAR_HEALTH(GetPlayerPed(), 200);
		SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, true);
		DO_SCREEN_FADE_OUT_UNHACKED(0);
		WAIT(5000);
		FORCE_LOADING_SCREEN(FALSE);
		DO_SCREEN_FADE_IN_UNHACKED(3000);
	}

	while (true)
	{
		WAIT(0);
	}
}
