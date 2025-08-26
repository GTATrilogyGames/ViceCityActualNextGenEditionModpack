#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"

float text, cutscen;

void business(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "CAR_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("car_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "ICE_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("ice_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "TAX_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("tax_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(5))
		{
			LOAD_ADDITIONAL_TEXT( "DRUG_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("drug_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void rockers(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "ROK_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("rok_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "ROK_2", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("rok_2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "ROK_3A", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("rok_3a");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void versetty(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "BUD_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bud_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "BUD_2", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bud_2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "BUD_3", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bud_3");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void studio(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "PORN_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("porn_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "PORN_2", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("porn_2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "PORN_3", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("porn_3");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(5))
		{
			LOAD_ADDITIONAL_TEXT( "PORN_4", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("porn_4");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void phil(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "PHIL_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("phil_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "PHIL_2", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("phil_2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void club(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 1 );
			LOAD_ADDITIONAL_TEXT( "BANK_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bank_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 0 );
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 1 );
			LOAD_ADDITIONAL_TEXT( "BANK_2A", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bank_2a");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}

			MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 0 );
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "BANK_2B", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bank_2b");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}
			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(5))
		{
			MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 1 );
			LOAD_ADDITIONAL_TEXT( "BANK_3A", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bank_3a");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}
			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV( 0 );
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(6))
		{
			LOAD_ADDITIONAL_TEXT( "BANK_3B", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bank_3b");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}
			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(7))
		{
			LOAD_ADDITIONAL_TEXT( "BANK_4", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bank_4");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}
			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void lawyer(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "LAW_1A", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("law_1a");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "LAW_1B", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("law_1b");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "LAW_2A", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("law_2a");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(5))
		{
			LOAD_ADDITIONAL_TEXT( "LAW_2B", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("law_2b");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(6))
		{
			LOAD_ADDITIONAL_TEXT( "LAW_2C", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("law_2c");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(7))
		{
			LOAD_ADDITIONAL_TEXT( "LAW_3", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("law_3");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(8))
		{
			LOAD_ADDITIONAL_TEXT( "LAW_4", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("law_4");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void voodoo(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "HAT_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("hat_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "HAT_2", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("hat_2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "HAT_3", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("hat_3");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void baron_diaz(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "COK_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cok_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "COK_2A", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cok_2a");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			LOAD_ADDITIONAL_TEXT( "COK_2B", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cok_2b");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "COK_3", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cok_3");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(5))
		{
			LOAD_ADDITIONAL_TEXT( "COK_4A", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cok_4a");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(6))
		{
			LOAD_ADDITIONAL_TEXT( "COK_4A2", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cok_4a2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(7))
		{
			LOAD_ADDITIONAL_TEXT( "COK_4B", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cok_4b");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(8))
		{
			LOAD_ADDITIONAL_TEXT( "RESC_1A", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("resc_1a");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(9))
		{
			LOAD_ADDITIONAL_TEXT( "ASS_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("ass_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(10))
		{
			LOAD_ADDITIONAL_TEXT( "ASS_2", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("ass_2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
			  if (GET_CUTSCENE_AUDIO_TIME_MS()>27280)
			  {
				DRAW_RECT(0.5, 0.5, 1.0, 1.0, 0, 0, 0, 255);
			  }
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void umberto(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "CUB_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cub_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "CUB_2", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cub_2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "CUB_4", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cub_4");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(5))
		{
			LOAD_ADDITIONAL_TEXT( "CUB_3", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cub_3");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(6))
		{
			G_CUBAN = 99;
			START_CUTSCENE_NOW("destr2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			G_CUBAN = 5;
			WAIT(1000);
		}
	}
}
void fin(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "CAP_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cap_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT("fin", 0);
			int state = 0;
			START_CUTSCENE_NOW("fin");
			while (!HAS_CUTSCENE_LOADED()) {
				WAIT(0);
			}
			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED()) {
				WAIT(0);
				if ((state == 0) && (GET_CUTSCENE_AUDIO_TIME_MS() > 57100)) {
					DO_SCREEN_FADE_OUT(5000);
					state++;
				} else if ((state == 1) && (GET_CUTSCENE_AUDIO_TIME_MS() > 62500)) {
					DO_SCREEN_FADE_IN(2000);
					state++;
				} else if ((state == 2) && (GET_CUTSCENE_AUDIO_TIME_MS() > 150350)) {
					SET_SPRITES_DRAW_BEFORE_FADE(1);
					DRAW_RECT(0.5, 0.5, 1.0, 1.0, 0, 0, 0, 255);
				}
			}
			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT())) {
				if (GET_CUTSCENE_AUDIO_TIME_MS() > 150350) {
					SET_SPRITES_DRAW_BEFORE_FADE(1);
					DRAW_RECT(0.5, 0.5, 1.0, 1.0, 0, 0, 0, 255);
				}
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "FINALE", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("finale");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void typography(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "CNT_1A", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cnt_1a");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "CNT_1B", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cnt_1b");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "CNT_2", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("cnt_2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void cortez(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "COL_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("col_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "COL_2", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("col_2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "COL_3A", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("col_3a");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(5))
		{
			LOAD_ADDITIONAL_TEXT( "COL_4A", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("col_4a");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(6))
		{
			LOAD_ADDITIONAL_TEXT( "COL_5A", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("col_5a");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(7))
		{
			LOAD_ADDITIONAL_TEXT( "COL_5B", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("col_5b");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void biker(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "BIKE_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bike_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "BIKE_3", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bike_3");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "BIKE_2", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bike_2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void avery(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "TEX_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("tex_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
				}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "TEX_3", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("tex_3");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			G_AVERY = 99; // отключаем все модели стройки в WORLD.sco
			START_CUTSCENE_NOW("destr1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			G_AVERY = 3;
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(5))
		{
			LOAD_ADDITIONAL_TEXT( "TEX_2", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("tex_2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
	}
}
void temp(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		{
			text = 1;
			break;
		}

		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(2))
		{
			LOAD_ADDITIONAL_TEXT( "PHIL_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("phil_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(3))
		{
			LOAD_ADDITIONAL_TEXT( "PHIL_2", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("phil_2");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(4))
		{
			LOAD_ADDITIONAL_TEXT( "BANK_2B", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bank_2b");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(5))
		{
			LOAD_ADDITIONAL_TEXT( "BANK_3B", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bank_3b");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(6))
		{
			LOAD_ADDITIONAL_TEXT( "CAR_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("car_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(7))
		{
			LOAD_ADDITIONAL_TEXT( "BUD_3", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("bud_3");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(8))
		{
			LOAD_ADDITIONAL_TEXT( "ICE_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("ice_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(9))
		{
			LOAD_ADDITIONAL_TEXT( "TAX_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("tax_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		if (IS_GAME_KEYBOARD_KEY_JUST_PRESSED(10))
		{
			LOAD_ADDITIONAL_TEXT( "DRUG_1", 6 ); // загружаем субтитры из *.GTX
			START_CUTSCENE_NOW("drug_1");
			while (!HAS_CUTSCENE_LOADED())
			{
				WAIT(0);
			}

			DO_SCREEN_FADE_IN(0);
			while (!HAS_CUTSCENE_FINISHED())
			{
				WAIT(0);
			}

			if ((IS_SCREEN_FADING_OUT()) || (IS_SCREEN_FADED_OUT()))
			{
				DO_SCREEN_FADE_IN(0);
			}
			WAIT(1000);
		}
		
	}
}
void main(void)
{
	WAIT(5000);
	text = 1;
	cutscen = 1;
	//uint stat;
	//float x1, y1, z1, x2, y2, z2, pResult;
	//Cam camera3;
	//GET_GAME_CAM(&camera3);
	
	while (TRUE)
	{
		WAIT(0);

		//GET_CAM_POS(camera3, &x1, &y1, &z1);
		//GET_CHAR_COORDINATES(GetPlayerPed(),  &x2, &y2, &z2);//вписываем координаты игрока в переменную
		//GET_ANGLE_BETWEEN_2D_VECTORS( x1,  y1,  x2,  y2,  &pResult);
		//DISPLAY_TEXT_WITH_NUMBER(0.850052, 0.725462962, "CP_TIME_NOZERO", pResult);

		//DISPLAY_TEXT_WITH_NUMBER(0.850052, 0.785462962, "CP_TIME_NOZERO", x1);
		//DISPLAY_TEXT_WITH_NUMBER(0.850052, 0.825462962, "CP_TIME_NOZERO", y1);

		//if ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER())) //клавиатура BACKSPACE
		//{
		//	//// stat = GET_INT_STAT(0);
		//	//stat += 10;
		//	//// SET_INT_STAT(0, stat);
		//	//ADD_SCORE( GetPlayerIndex(), +50000 );//даём игроку денег
		//	G_CORTEZ = 7;
		//	PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "All Hands On Deck!", 5000, 4);
		//	WAIT(1000);
		//}
	}
//
	while (TRUE)
	{
		WAIT(0);
		if (IS_GAME_KEYBOARD_NAV_RIGHT_PRESSED( 1 )) //клавиатура RIGHT
		{
			if (cutscen > 15)
			{
				cutscen = 1;
			}
			else
			{
				cutscen += 1;
			}
			text = 1;
		}
		if (IS_GAME_KEYBOARD_NAV_LEFT_PRESSED( 1 )) //клавиатура LEFT
		{
			if (cutscen < 1)
			{
				cutscen = 15;
			}
			else
			{
				cutscen -= 1;
			}
			text = 1;
		}

		if ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER())) //клавиатура ENTER
		{
			PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "use buttons 1 2 3 4 5 ... ", 5000, 4);
			if (cutscen == 1)
			{
				avery();
			}
			else if (cutscen == 2)
			{
				biker();
			}
			else if (cutscen == 3)
			{
				cortez();
			}
			else if (cutscen == 4)
			{
				typography();
			}
			else if (cutscen == 5)
			{
				fin();
			}
			else if (cutscen == 6)
			{
				umberto();
			}
			else if (cutscen == 7)
			{
				baron_diaz();
			}
			else if (cutscen == 8)
			{
				voodoo();
			}
			else if (cutscen == 9)
			{
				lawyer();
			}
			else if (cutscen == 10)
			{
				club();
			}
			else if (cutscen == 11)
			{
				phil();
			}
			else if (cutscen == 12)
			{
				studio();
			}
			else if (cutscen == 13)
			{
				versetty();
			}
			else if (cutscen == 14)
			{
				rockers();
			}
			else if (cutscen == 15)
			{
				business();
			}
		}

		if (text == 1)
		{
			if (cutscen == 1)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "AVERY", 5000, 4);
			}
			else if (cutscen == 2)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "BIKER", 5000, 4);
			}
			else if (cutscen == 3)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "CORTEZ", 5000, 4);
			}
			else if (cutscen == 4)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "TYPOGRAPHY", 5000, 4);
			}
			else if (cutscen == 5)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "FINAL", 5000, 4);
			}
			else if (cutscen == 6)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "CUBAN", 5000, 4);
			}
			else if (cutscen == 7)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "DIAZ", 5000, 4);
			}
			else if (cutscen == 8)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "HAITI", 5000, 4);
			}
			else if (cutscen == 9)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "LAWYER", 5000, 4);
			}
			else if (cutscen == 10)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "MALIBU", 5000, 4);
			}
			else if (cutscen == 11)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "PHIL", 5000, 4);
			}
			else if (cutscen == 12)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "PRON", 5000, 4);
			}
			else if (cutscen == 13)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "VERSETTI MANSION", 5000, 4);
			}
			else if (cutscen == 14)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "ROCK", 5000, 4);
			}
			else if (cutscen == 15)
			{
				PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "BUYING A BUSINESS", 5000, 4);
			}
			WAIT(600);
			text = 0;
		}
	}
	//*/
	return;
}
