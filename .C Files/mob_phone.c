/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"

Object trubka_1;
int incoming_call = 0;
int call_drop = 0;
int COKERUN, BUSINES_SA, ICECREAM, CABS, PRON, CLUB, STRIP, FIN;

void SetTime(uint time)
{
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if (TIMERA() > time)
		{
			break;
		}
		else if ((IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// поверка игрок мёртв/арестован
		{
			SETTIMERA( 0 );
		}
	}
}
void SetSpeech(void)
{
	SETTIMERA( 0 );
	while(true)
	{
		WAIT(0);
		if (!IS_SCRIPTED_CONVERSATION_ONGOING())
		{
			break;
		}
		else if ((IS_CHAR_IN_WATER(GetPlayerPed())) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))//если игрок мёртв или аврестован
		{
			call_drop = 1;
			ABORT_SCRIPTED_CONVERSATION( 0 );
			break;
		}
		else if ((IS_BUTTON_PRESSED( 0, 17 )) || ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER()))) // BACKSPACE
		{
			call_drop = 1;
			ABORT_SCRIPTED_CONVERSATION( 0 );
			break;
		}
		else if (TIMERA() > 10000)
		{
			break;
		}
	}
}
void call_1(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R7_LA", "MOB52_A", 0, 0);//Hey Leo, I think we got a buyer for Diaz's merchandise.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R7_LB", "MOB52_B", 0, 0);//You gotta give him a ring, man, set up the deal, you know?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R7_MA", "MOB52_C", 0, 0);//Where are you now?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R7_NB", "MOB52_D", 0, 0);//You ok Leo? You sound kinda different.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R7_NE", "MOB52_E", 0, 0);//Just tell me where you are.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R7_NG", "MOB52_F", 0, 0);//Who the hell is this? Put Leo on, man!
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R7_PA", "MOB52_G", 0, 0);//Leo's gone away for a while, he left me in charge.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R7_PB", "MOB52_H", 0, 0);//Screw you, man!
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_2(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_AA", "MOB_40A", 0, 0);//Hey Tommy, it's Sonny. How's the sun tan?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_AB", "MOB_40B", 0, 0);//I ain't got no sun tan.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R8_AC", "MOB_40C", 0, 0);//Well, you ain't got my money, either, so I'm wondering to myself,
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_AD", "MOB_40D", 0, 0);//what are you doing? So, tell me, Tommy, what are you doing?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R8_AE", "MOB_40E", 0, 0);//I'm looking for the money, Sonny. Don't worry.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_AF", "MOB_40F", 0, 0);//I am worrying, Tommy, that's my style,
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_AG", "MOB_40G", 0, 0);// because I seem to have this problem in my life with unreliable people.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_AH", "MOB_40H", 0, 0);//Don't be an unreliable person, Tommy, please.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_A_BA", "MOB_40I", 0, 0);//Do us both a favor. I'm looking forward to hearing from you.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_3(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_A_CA", "MOB_99A", 0, 0);//Get to the payphone next to the mall in Washington.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_4(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_A_DA", "MOB_24A", 0, 0);//Hola, is this Mr. Vercetti?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_A_EA", "MOB_24B", 0, 0);//Yeah.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_A_FA", "MOB_24C", 0, 0);//This is Cortez. You were at my party.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_A_GA", "MOB_24D", 0, 0);//Yeah. I remember.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_A_HA", "MOB_24E", 0, 0);//Mr. Vercetti, it was a most unfortunate incident that happened with your business deal.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_A_IA", "MOB_24F", 0, 0);//I know.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_A_JA", "MOB_24G", 0, 0);//I want you to know me and my people are doing their utmost to get to the bottom of it.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R8_A_KA", "MOB_24H", 0, 0);//If you'd like to talk to me more privately, you can find me at the boat, eh? Okay? Good day, senor.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_5(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_BE", "MOB_62A", 0, 0);//Tommy, is Ricardo Diaz, I want to thank you for looking out for me my man.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_BF", "MOB_62B", 0, 0);//I ask that prick Cortez, he say you the real deal, my friend, why you not come see me.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_BG", "MOB_62C", 0, 0);//I need a guy like you. All I have now is dickheads,
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_BH", "MOB_62D", 0, 0);//dickheads everywhere, yo. I make you real rich.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_6(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_BI", "MOB_70A", 0, 0);//Tommy, it's me, Colonel Cortez. Look senor, I believe you are a man who can get things done. So please help me.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_BJ", "MOB_70B", 0, 0);//You can find me at the boat.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_7(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_VU", "NEMOB1", 0, 0);//Son, I have some work for you. Come to me when you have time.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_8(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_BK", "MOB46_A", 0, 0);//Yo, Tommy! It's Lance.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_BL", "MOB46_B", 0, 0);//Yeah?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_BM", "MOB46_C", 0, 0);//Oh, nice to hear from you, Lance. Come on, man, be cool, be cool.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_BN", "MOB46_D", 0, 0);//I'm in the middle of something. What do you want?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_FA", "MOB46_E", 0, 0);//Nothing. Just to say, you know. Look Tommy, we can do this thing.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_FB", "MOB46_F", 0, 0);//You and me, no problem. You know what I mean?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_FC", "MOB46_G", 0, 0);// We're going to have to do it, 'cause otherwise, we're going to be dead, Lance.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_A_FD", "MOB46_H", 0, 0);//We're in too far now. But thanks for the call. I'll speak to you later.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_9(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_BB", "MOB_01A", 0, 0);//Awright me ol'china! It's Paul. I might have a little result for you, but I need to speak to you in person.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_CC", "MOB_01B", 0, 0);//I'm enjoying a little R&R at the Club Malibu.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_CE", "MOB_01C", 0, 0);//Reckon you're gonna owe me a favor or two after this, sunshine. I'll see you later.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_10(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_GD", "MOB_25A", 0, 0);//Tommy, Thomas it's Cortez. Look, the French are giving me all kinds of trouble, amigo.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_VA", "MOB_25B", 0, 0);//Damn hypocrites. They spend a hundred years stealing from poor countries and they call me a thief!
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_VC", "MOB_25C", 0, 0);//I am going to need your help as soon as possible, amigo.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_WA", "MOB_25D", 0, 0);//So please hurry, Tommy, I need you, all right? I hate the damn French.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_11(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_WB", "MOB_20A", 0, 0);//Alright, Tommy, it's Paul. I just heard from a mush that you've been a real naughty boy.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_XA", "MOB_20B", 0, 0);//Somebody has taken offense to you acting like the big guy all of a sudden, giving it the big shot thing.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_YA", "MOB_20C", 0, 0);//Well, don't say I never warned you or nothing. Boasting is a mug's game, son.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_YB", "MOB_20D", 0, 0);//Anyway, I heard there's some price been put on your head and someone's going to have a crack at you,
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_YC", "MOB_20E", 0, 0);//so watch yourself, and remember me, mate.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_12(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_YD", "MOB_68A", 0, 0);//Tommy son, have I got a surprise for you
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_YE", "MOB_68B", 0, 0);//I'm down at the recording studios with some major artists
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_YF", "MOB_68C", 0, 0);//Why don't you pay us a visit?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_YG", "MOB_68D", 0, 0);//You know it makes sense, dontcha? See ya later.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_13(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_AB", "MOB_41A", 0, 0);//Tommy, remember me?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_AE", "MOB_41B", 0, 0);//Hello Sonny.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_EB", "MOB_41C", 0, 0);//That's right, Sonny. We're old friends,
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_FA", "MOB_41D", 0, 0);//You never write me, you never call. Don't you want to be friends no more?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_FB", "MOB_41E", 0, 0);//I've been busy trying to sort things out. You didn't give me a lot of support down here, Sonny.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_HB", "MOB_41F", 0, 0);//Oh, my fault is it? We'll I've heard you been busy all right.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_HC", "MOB_41G", 0, 0);//Busy killing drugs barons. Busy taking over.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_HD", "MOB_41H", 0, 0);//Don't forget about us, Tommy, 'cause I can assure you, I ain't forgotten about you.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_14(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_YH", "MOB_11A", 0, 0);//Howdy son, just thought I'd ring you up and give you some advice.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R12_YI", "MOB_11B", 0, 0);//Hey, Avery. What's eating you?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_YJ", "MOB_11C", 0, 0);//There's a lot of opportunity in this town if you own the right real estate, you catch my drift?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_YK", "MOB_11D", 0, 0);//I reckon so...
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_YL", "MOB_11E", 0, 0);//All I'm saying is keep your eyes open and you might find the perfect business opportunity. I'll catch y'later.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R12_YM", "MOB_11F", 0, 0);//Later, Avery.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_15(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_PB", "MOB45_A", 0, 0);//Tommy We gotta talk about stuff.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_QA", "MOB45_B", 0, 0);//What's the problem Lance?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_QB", "MOB45_C", 0, 0);//It's you, my friend, I feel you're not giving me a fair slice.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_SA", "MOB45_D", 0, 0);//And more than that, you been embarrassing me in front of the boys. I can't have that.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_SB", "MOB45_E", 0, 0);//Lance, it ain't like that. You've been making mistakes.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_TA", "MOB45_F", 0, 0);//Tommy, I'm not your message boy. I'm not your running boy.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_VA", "MOB45_G", 0, 0);//Lance, don't screw up, and we won't have any problems. I screw up, you can lay into me any time.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_VB", "MOB45_H", 0, 0);//Tommy, I've done everything for you, you treat me like a fool. Don't do that.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_VC", "MOB45_I", 0, 0);//Lance, I won't rip you off or stab you in the back, okay?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_ZA", "MOB45_J", 0, 0);//Just take it easy. This is tough enough without you getting all emotional on me.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_ZB", "MOB45_K", 0, 0);//Trust me. Do you hear me, do you hear me?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_ZC", "MOB45_L", 0, 0);//I hear you, Tommy, but I can't take this much more.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_ZD", "MOB45_M", 0, 0);//Lance, don't be like this. Now I'm warning you.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_ZE", "MOB45_N", 0, 0);//Do you hear me? Just relax, take a few days off. Okay? I'll talk to you.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_16(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_ZF", "MOB_72A", 0, 0);//Tommy, it's me, Lance. Keep your mouth shut there Tommy, 'cause I ain't got time to talk.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_A_ZG", "MOB_72B", 0, 0);//I ain't interested in what you got to say. Why should I be? You don't care about me, do you?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_BA", "MOB_72C", 0, 0);//You gotta look after me a bit better. Give me a fair slice. You know...
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_BB", "MOB_72D", 0, 0);//Tommy... oh, look, man, I'm sorry. It's just that...
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_BC", "MOB_72E", 0, 0);//People patronize me all my life, treat me like a little kid.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_B_AA", "MOB_72F", 0, 0);//My brother would do that. Please, man, don't do that.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_B_AB", "MOB_72G", 0, 0);//I gotta go.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_17(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_B_AC", "MOB_42A", 0, 0);//Tommy.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_B_AD", "MOB_42B", 0, 0);//Sonny.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_B_AE", "MOB_42C", 0, 0);//Obviously you are suffering from hearing problems, so I'll try again.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_B_AF", "MOB_42D", 0, 0);//Where's the goddamned money, where's the goddamned stuff, and where's my cut of your new action?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_B_AG", "MOB_42E", 0, 0);//You are making an idiot out of me, Tommy, and I'm not laughing yet.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_18(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_B_AH", "MOB_09A", 0, 0);//Hey Leo! I got some work for you!
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_B_AI", "MOB_09B", 0, 0);//This ain't Leo.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_B_AJ", "MOB_09C", 0, 0);//Hey, if Leo knows you got his phone, he gonna kill you!
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_B_HB", "MOB_09D", 0, 0);//Maybe Leo's already dead. Maybe I killed Leo and took his phone - you think of that prick?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_B_HC", "MOB_09E", 0, 0);//You killed Leo? You must have big cojones - wanna work for me?!
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_CA", "MOB_09F", 0, 0);//Drop by my father's cafe in Little Havana and we'll talk mano a mano.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_19(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_DA", "MOB_06A", 0, 0);//Tommy, 'nuf dead man been chattin' about you, my dear.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_DB", "MOB_06B", 0, 0);//Thought you might need something to make you feel better. So Auntie Poulet make you some stew, aye?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_DC", "MOB_06C", 0, 0);//Come by me kitchen some time, ok Tommy?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_20(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_WA", "NEMOB2", 0, 0);//Tommy, Tommy! These damn Haitians... We're going to kill them all! Tommy, we need you! I'm waiting for you at my father's cafe!
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_21(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_DD", "MOB_66A", 0, 0);//Tommy, Tommy why you coming back here for?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_DE", "MOB_66B", 0, 0);//I tell you we don't want to see you around here no more.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_22(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_DF", "MOB_30A", 0, 0);//Tommy, is Umberto Robina
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_DG", "MOB_30B", 0, 0);//Hey, how's the cafe?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_EA", "MOB_30C", 0, 0);//Oh, wonderful. Incredible. Tommy, incredible. No wimps, Tommy, just real men, and the beautiful women!
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_EB", "MOB_30D", 0, 0);//Anyway, I wanted to tell you, me and Papi, to us, you Cuban.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_EC", "MOB_30E", 0, 0);//You have proved yourself, man. You got big cojones.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_FA", "MOB_30F", 0, 0);//Well thank you, Umberto. Nobody's said that to me since I left jail. I'll see you around.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_23(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_FB", "MOB_98A", 0, 0);//Get to the pay phone in Vice Point.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_24(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_XB", "NEMOB3", 0, 0);//Tommy, the guys and I are going to a concert. Come to the recording studio, we'll be waiting for you.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_25(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_FC", "MOB_96A", 0, 0);//Get to the payphone at the airport terminal.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_26(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_FD", "MOB_95A", 0, 0);//Get to the payphone in Little Havana.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_27(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_FE", "MOB_04A", 0, 0);//How you doin' mate? It's Paulo again.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_FF", "MOB_04B", 0, 0);//Look Tommy, I forgot to mention we're going to need some extra muscle for the concert. A bit of security.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_FG", "MOB_04C", 0, 0);//There's a biker gang led by Mitch Baker, it would be great publicity. Very rock and roll, baby.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_GA", "MOB_04D", 0, 0);//Sort this out for me and I'll get you some back stage passes for the gig, awright?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_28(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_GB", "MOB_05A", 0, 0);//Hey, it's Mitch. You did good Tommy, it's good to have the old girl back.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_GC", "MOB_05B", 0, 0);//You tell Kent Paul he'll get his security for the gig.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_HA", "MOB_05C", 0, 0);//You have my word on that.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_HB", "MOB_05D", 0, 0);//Now keep yourself out of trouble.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_29(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_IA", "MOB_26A", 0, 0);//Hello, Tommy?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_IC", "MOB_26B", 0, 0);//Yeah?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_IE", "MOB_26C", 0, 0);//It's Baker. I just wanted to say I really enjoyed the show. 
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_MA", "MOB_26D", 0, 0);//Me and the boys want to thank you, and remind you,
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_NA", "MOB_26E", 0, 0);//you got our respect. Good day. Keep riding hard, son.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_30(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_BB", "MOB_14A", 0, 0);// Hey there Tommy, you're gonna love me mate.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_BC", "MOB_14B", 0, 0);//A little birdy told me that Vice City SWAT Division has a deposit box at a certain rather large banking establishment,
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_BD", "MOB_14C", 0, 0);//where they keep all the bribes they've taken over the years,
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_CA", "MOB_14D", 0, 0);//like some kind of old boys' retirement fund.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CB", "MOB_14E", 0, 0);//Of course, if this information should ever help you acquire any of that cash,
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CC", "MOB_14F", 0, 0);//I guess you'd feel obliged to push some of it my way?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_CD", "MOB_14G", 0, 0);//I'll bear that in mind, thanks Kent.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CE", "MOB_14H", 0, 0);//It's Paul. I'm from Kent, near London, you prat.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_31(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_NB", "MOB_34A", 0, 0);//Tommy, I really enjoyed working with you. Ain't had so much fun since the ridge in Nam, pal.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_OA", "MOB_34B", 0, 0);//Anyhows, you need anything, you call on me, you hear? 
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_OB", "MOB_34C", 0, 0);//I always remember those I served with,
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_PA", "MOB_34D", 0, 0);//and I am sure I can help you out, you hear?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_32(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_PB", "MOB_43A", 0, 0);//Tommy, Tommy, Tommy, I had Sonny on the phone, ok, are you with me?.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_QA", "MOB_43B", 0, 0);//I don't know about you, but there's something about a man threatening to murder my family
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_QB", "MOB_43C", 0, 0);//which really scares the crap out of me. What are you going to do?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_RA", "MOB_43D", 0, 0);//Ken, take it easy.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_RB", "MOB_43E", 0, 0);//I AM calm, calm as a man can be when he's fearing for his life!
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R13_SA", "MOB_43F", 0, 0);//Stay off the idiot fuel and look after yourself.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_SB", "MOB_43G", 0, 0);//No one's gonna take us out. I'll see you later.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_TC", "MOB_43H", 0, 0);//I am calm. Don't I sound calm? Must be impending death that is doing this to my voice.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_33(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_A_AC", "MOB_33A", 0, 0);//Tommy, it's Phil, now cut out all the reminiscing crap and listen to me, you hear?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_A_AD", "MOB_33B", 0, 0);//Good. I got me some extra strength boomshine nearing fermentation time and I was wondering if you'd fancy having a shot.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_A_BA", "MOB_33C", 0, 0);//Seriously, Tommy, if you like a drink, or if you need to strip paint, this stuff'll make a man out of you.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_BA", "MOB_33D", 0, 0);//Sure did out of me, even though I can't see out of one eye. I'll be waiting for you, y'hear.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_34(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R7_QB", "MOB_36A", 0, 0);//Tommy, it's Phil, I want to thank you for helping me out back there son,
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R7_RA", "MOB_36B", 0, 0);//Damn Charlie, he'll always ambush you somewhere or other,
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R7_SA", "MOB_36C", 0, 0);//Anyway the wound is healing well, and it means I'll no longer be defrauding the government on my disability check.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_35(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CF", "MOB_16A", 0, 0);//Tommy, Paulo here, que pasa amigo?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CG", "MOB_16B", 0, 0);//What do you want Paul? I don't want any fake label clothes.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CH", "MOB_16C", 0, 0);//Very funny, mate, but you know I don't touch bent gear. Nah, I was just calling to see if I get a part in one your movies.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CI", "MOB_16D", 0, 0);//Back in England I did a lot of blue stuff, mate. I'm packing more heat than you, my son.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_CJ", "MOB_16E", 0, 0);//Paul, thanks for the offer, I'll bear it in mind.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_CK", "MOB_16F", 0, 0);//Seriously, don't forget about me, after all I done for you.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_CL", "MOB_16G", 0, 0);//That's what I'm trying to forget about.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_36(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CM", "MOB_73A", 0, 0);//Tommy, it's Steve.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CN", "MOB_73C", 0, 0);//Hey indeed, genius. You're a marvel! I'm a marvel! They love us. We are re-writing the record books, pal.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_CO", "MOB_73D", 0, 0);//We are talking major awards here. Finally, I can put my dad in a home an tell him to shut up.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_CP", "MOB_73F", 0, 0);//Cool? It's hot, man. Hot. H. O. T. He never believed in me. Never thought I was an artist, and now I've made it.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CQ", "MOB_73G", 0, 0);//I'm the best damn skin flick director of all time, my friend. I just wanted to say, it's a pleasure to have met you.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CR", "MOB_73I", 0, 0);//I love you, baby. Don't go changing on me, you hear.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_37(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_CS", "MOB_02A", 0, 0);//Ssssnniiiiffffff Hey! Hello, Tommy? Tommy!
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CT", "MOB_02B", 0, 0);//We got a situation over at the Print Works. You better go and check it out.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CU", "MOB_02C", 0, 0);//Some kind of mess or other. Things are messed up. I gotta go.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_38(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R13_UB", "MOB_47A", 0, 0);//Tommy, Lance, we got big problems. Come down here. Right away.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_39(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_CV", "MOB_18A", 0, 0);//Tommy, it's Paulo, how are you? Right mate, anyway, thought I had to drop you a line.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_IA", "MOB_18B", 0, 0);//Oh my good lord, my son, you will not believe the quality of the brass I just encountered.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_IB", "MOB_18C", 0, 0);//Street walker or something, just down in Little Havana, mate.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_JA", "MOB_18D", 0, 0);//Said her name was Mercedes or something.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_JB", "MOB_18E", 0, 0);//Oh my god, mate. You gotta check this bird out.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_JC", "MOB_18F", 0, 0);//Could strip the lead out of a pencil. Said I was the best she ever had and all.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_SA", "MOB_18G", 0, 0);//Keep you potatoes skinned for her. Be seeing you.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_40(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_SB", "MOB21_A", 0, 0);//Tommy, Thomas, it's Cortez. Que pasa?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_TA", "MOB21_B", 0, 0);//Things are interesting. How are you, my friend?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_UA", "MOB21_G", 0, 0);//I wanted to ask you about Mercedes.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_UB", "MOB21_H", 0, 0);//Ok, what about her?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_UC", "MOB21_I", 0, 0);//Oh Tommy, Tommy. I, I hear these stories, all these stories - I don't know what to think.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_UD", "MOB21_K", 0, 0);//Maybe she thinks she can do what she likes, but Tommy, tell me, is it true?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_UE", "MOB21_M", 0, 0);//Is what true?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_UF", "MOB21_N", 0, 0);//These stories I hear. Is she really going to be a lawyer?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_UG", "MOB21_O", 0, 0);//Oh Tommy, the shame, the shame! You know, we Cortez's are a proud family.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_UH", "MOB21_P", 0, 0);//We would never allow a daughter of ours to become a lawyer. Please tell me it isn't so. I don't think I could take it.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_UI", "MOB21_Q", 0, 0);//Oh Colonel, I can assure you Mercedes is never going to become a lawyer. Don't worry about it.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_UJ", "MOB21_R", 0, 0);//Oh thank you, Tommy. Tommy, thank you. The shame would be unbearable. She is a lady, not a parasite, you know.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_UK", "MOB21_T", 0, 0);//Anyway, Tommy, you must excuse me, the new minister of the interior has arrived.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_UL", "MOB21_U", 0, 0);//Many years ago, I killed his father in a failed coup so I must be polite. Good day, amigo.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_41(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_UM", "MOB_17A", 0, 0);//Tommy Vercetti, how's it going, Mr. big shot? I hear all these things about you, some kind of player in town, now eh...
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_UN", "MOB_17B", 0, 0);//Paul, you're drunk.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_UO", "MOB_17C", 0, 0);//Nah, you stupid prat, I ain't drunk. I only had a couple and some treats, ain't been to bed for a couple of days, you know.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_UP", "MOB_17D", 0, 0);//Anyway, don't give me that. I ain't a mug. Who set you up in this town? Who? Me. That's who.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_VA", "MOB_17F", 0, 0);//Really?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_VB", "MOB_17G", 0, 0);//Don't give me that. Don't! I introduced you to people. I showed you the ropes, did a lot of stuff for you, and this is how you repay me.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_VC", "MOB_17H", 0, 0);//You ignore me. You won't give me a way in, after all I did for you! What do you think I am? A div or something?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_VD", "MOB_17I", 0, 0);//Paul, take it easy. I've been busy, don't be an idiot.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_VE", "MOB_17J", 0, 0);//I ain't no idiot, mush. That's what they said in borstal. Are you asking for trouble son, because you're going to get it!
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_VF", "MOB_17K", 0, 0);//Tommy, mate. Please. You was my big hope! Please, don't laugh at me!
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_VG", "MOB_17L", 0, 0);//Paul, get some sleep, seriously.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_42(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_VH", "MOB_63A", 0, 0);//Tommy, it's Earnest. Earnest Kelly.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_VI", "MOB_63B", 0, 0);//How are you?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_VJ", "MOB_63C", 0, 0);//I'm doing okay. I'll need a stick to walk, but I should be back at work soon enough.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_VK", "MOB_63D", 0, 0);//Good.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_VL", "MOB_63E", 0, 0);//I heard about Lance. What a little prick, eh?
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_VM", "MOB_63F", 0, 0);//Yes.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_VN", "MOB_63G", 0, 0);//Never trust a man who walks the streets in his pajamas. That's what I say. Glad you killed him. I hope it was painful for the prick.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_VO", "MOB_63H", 0, 0);//I think it was. I just didn't think he was like that...
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "NIKO");
		ADD_LINE_TO_CONVERSATION(0, "R14_VP", "MOB_63I", 0, 0);//Tommy, for a raging lunatic, you're pretty naive. I'll be back at work soon, teach you a thing or two about life, you hear.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R14_VQ", "MOB_63J", 0, 0);//Take your time, Earnest. Look after yourself.
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void call_43(void)
{
	if (call_drop == 0)
	{
		NEW_SCRIPTED_CONVERSATION();
		ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
		ADD_LINE_TO_CONVERSATION(0, "R7_QB", "MOB_36A", 0, 0);//
		START_SCRIPT_CONVERSATION(1, 1);
		SetSpeech();
	}
}
void set_anim_in(void)
{
	REQUEST_ANIMS( "cellphone" );//загружаем файл с анимацией
	while (!HAVE_ANIMS_LOADED( "cellphone" )) WAIT(0);
	
	ATTACH_OBJECT_TO_PED( trubka_1, GetPlayerPed(), 1232, 0.070, 0.052, 0.003, 3.30000000, 0.30000000, -0.45000000, 0 );
	
	SET_CURRENT_CHAR_WEAPON(GetPlayerPed(), WEAPON_UNARMED, TRUE);
	TASK_PLAY_ANIM_SECONDARY_UPPER_BODY( GetPlayerPed(), "cellphone_in", "cellphone", 8.0, 0, 0, 0, 1, -1 );//Воиспроизвидение анимации на педе
	WAIT(1000);
	TASK_PLAY_ANIM_SECONDARY_UPPER_BODY( GetPlayerPed(), "cellphone_talk", "cellphone", 8.0, 1, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
	incoming_call = 1;
}
void set_anim_out(void)
{
	TASK_PLAY_ANIM_SECONDARY_UPPER_BODY( GetPlayerPed(), "cellphone_out", "cellphone", 1.0, 0, 0, 0, 0, -1 );//Воиспроизвидение анимации на педе
	SetTime(1000);
	DETACH_OBJECT( trubka_1, 1 );
	SET_OBJECT_COORDINATES(trubka_1, 1.1, 1.1, -1.1);
	incoming_call = 0;
}
void melodi(void)
{
	//NEW_SCRIPTED_CONVERSATION();
	//ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
	//ADD_LINE_TO_CONVERSATION(0, "R14_WA", "MOB52_A", 0, 0);//
	//START_SCRIPT_CONVERSATION(1, 1);
	//SetSpeech();

	//NEW_SCRIPTED_CONVERSATION();
	//ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
	//ADD_LINE_TO_CONVERSATION(0, "R14_WC", "MOB52_B", 0, 0);//
	//START_SCRIPT_CONVERSATION(1, 1);
	//SetSpeech();

	//NEW_SCRIPTED_CONVERSATION();
	//ADD_NEW_CONVERSATION_SPEAKER(0, GetPlayerPed(), "ROMAN");
	//ADD_LINE_TO_CONVERSATION(0, "R14_XD", "MOB52_C", 0, 0);//
	//START_SCRIPT_CONVERSATION(1, 1);
	//SetSpeech();

	START_CUSTOM_MOBILE_PHONE_RINGING( 14 ); // 14 - "SOLO" из \audio\sfx\general.rpf\GENERAL\MUSIC_RINGTONES
	PRINT_HELP_FOREVER("NE_M_CALL"); //Press ~INPUT_PHONE_ACCEPT~ to answer a call. Press ~INPUT_PHONE_CANCEL~ to drop.
	SETTIMERA( 0 );

	while(true)
	{
		WAIT(0);

		if ((IS_BUTTON_PRESSED( 0, 16 )) || ((IS_CONTROL_PRESSED( 2, 181 )) && (! IS_USING_CONTROLLER()))) //клавиатура ENTER
		{
			// останавливаем воспроизведение звонка
			STOP_MOBILE_PHONE_RINGING();
			CLEAR_HELP(); // удаляем текст подсказки
			set_anim_in();
			call_drop = 0;
			break;
		}
		else if ((IS_BUTTON_PRESSED( 0, 17 )) || ((IS_CONTROL_PRESSED( 2, 182 )) && (! IS_USING_CONTROLLER()))) // BACKSPACE
		{
			// останавливаем воспроизведение звонка
			STOP_MOBILE_PHONE_RINGING();
			CLEAR_HELP(); // удаляем текст подсказки
			G_ONMISSION = 0;
			SetTime(25000);
			break;
		}
		else if ((TIMERA() > 15000) || (IS_CHAR_IN_WATER(GetPlayerPed())) || (IS_CHAR_DEAD(GetPlayerPed())) || (HAS_CHAR_BEEN_ARRESTED(GetPlayerPed())))// поверка игрок мёртв/арестован
		{
			// останавливаем воспроизведение звонка
			STOP_MOBILE_PHONE_RINGING();
			CLEAR_HELP(); // удаляем текст подсказки
			G_ONMISSION = 0;
			SetTime(25000);
			break;
		}
	}
}
void launcher(void)
{
	while (TRUE)
	{
		WAIT(0);
		if ((G_ONMISSION == 0) && (G_MAIN_CALL == 1)) // если миссия "Драка в переулке" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_1();// Звонок Лео ("Мы нашли Диазу покупателя.").
					set_anim_out();
					CLEAR_PRINTS();
					G_MAIN_CALL = 2;
					G_ONMISSION = 0;
				}
	
   
				else
   
				 
																 
	
					
			 
						   
	 
																  
					
					 
					 
	 
	
   
																																		 
   
				 
																 
	
					
			 
						   
				{
					continue;
					
					
					 
				}
			}
		}
		if ((G_LAWYER >= 5) && (G_ONMISSION == 0) && (G_CORTEZ == 0))  // если миссия "Безпорядки" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_4();// звонок от Кортеза (стари миссии "Веролоная свинья")
					set_anim_out();
					CLEAR_PRINTS();
					G_CORTEZ = 1;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_COUNT >= 7) && (G_ONMISSION == 0) && (G_MAIN_CALL == 6) && (G_CORTEZ > 7)) // если миссия "Держите друзей рядом..." пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_39();// звонок от Кента Пола ("...ты не поверишь какую девку я встретил...")
					set_anim_out();
					CLEAR_PRINTS();
					G_MAIN_CALL = 7;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_DIAZ >= 3) && (G_ONMISSION == 0) && (G_CORTEZ == 4))  // если миссия "Фон Пейн 86" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_6();// звонок от Кортеза (стари миссии "Сэр, есть сэр!")
					set_anim_out();
					CLEAR_PRINTS();
					G_CORTEZ = 5;
					G_ONMISSION = 0;
				}
				else
   
																															
   
				 
																 
	
					
			 
						   
				{
					continue;
					
				 
					 
				}
			}
		}
		else if ((G_COUNT >= 7) && (G_ONMISSION == 0) && (G_MAIN_CALL == 7)) // если миссия "Держите друзей рядом..." пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_40();// звонок от Кортеза ("...я стышал что она собирается стать адвокатом...")
					set_anim_out();
					CLEAR_PRINTS();
					G_MAIN_CALL = 8;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_DIAZ >= 8) && (G_ONMISSION == 0) && (G_CORTEZ == 6))  // если миссия "Камера смертников" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_10();// звонок от Кортеза (стари миссии "Свистать всех наверх.")
					set_anim_out();
					CLEAR_PRINTS();
					G_CORTEZ = 7;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_CORTEZ == 4) && (G_ONMISSION == 0) && (G_DIAZ == 0))  // если миссия "Ангел хранитель" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_5();// звонок от Диаза (стари миссии "Погоня")
					set_anim_out();
					CLEAR_PRINTS();
					G_DIAZ = 1;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_CORTEZ == 8) && (G_ONMISSION == 0))  // если миссия "Свистать всех наверх." пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_11();// звонок от Кента Пола ("За твою голову назначина награда")
					set_anim_out();
					CLEAR_PRINTS();
					G_CORTEZ = 9;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		else if ((G_DIAZ == 6) && (G_CORTEZ == 6) && (G_ONMISSION == 0))  // если миссия "Спрос и предложение" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_9();// звонок от Кента Пола (стари миссии "Камера смертников.")
					set_anim_out();
					CLEAR_PRINTS();
					G_DIAZ = 7;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}

		if (FIN < 6)
		{
			if ((G_COKERUN == 2) && (COKERUN == 0)) COKERUN = 1, FIN += 1;
			if ((G_BUSINES_SA >= 2) && (BUSINES_SA == 0)) BUSINES_SA = 1, FIN += 1;
			if ((G_ICECREAM == 2) && (ICECREAM == 0)) ICECREAM = 1, FIN += 1;
			if ((G_CABS == 4) && (CABS == 0)) CABS = 1, FIN += 1;
			if ((G_PRON >= 5) && (PRON == 0)) PRON = 1, FIN += 1;
			if ((G_CLUB >= 6) && (CLUB == 0)) CLUB = 1, FIN += 1;
			if ((G_STRIP >= 2) && (STRIP == 0)) STRIP = 1, FIN += 1;
		}

		if ((G_ONMISSION == 0) && (G_PROTECT >= 4) && (G_MAIN_CALL == 5) && (G_COUNT == 3) && (FIN >= 5)) // если Вся нужная недвижимость пройдина
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_37();// звонок от Работника типографии (старт миссии "Завали рэкетира")
					set_anim_out();
					CLEAR_PRINTS();
					G_COUNT = 4;
					G_MAIN_CALL = 6;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_DIAZ >= 9) && (G_ONMISSION == 0) && (G_ROCK == 0))  // если миссия "Вычищение" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_12();// звонок от Кента Пола (стари миссии "Сок любви.")
					set_anim_out();
					CLEAR_PRINTS();
					G_ROCK = 1;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_ROCK >= 2) && (G_ONMISSION == 0) && (G_BIKE == 0)) // если миссия "Сок Любви" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_27();// звонок от Кента Пола (старт миссии "Стальные колёса") 
					set_anim_out();
					CLEAR_PRINTS();
					G_BIKE = 1;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_BIKE == 4) && (G_ONMISSION == 0)) // если миссия "Связанный по рукам" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_28();// звонок от Митча Байкера ("Скажи Кенту Полу, что охрана на концерте будет.") 
					set_anim_out();
					CLEAR_PRINTS();
					G_BIKE = 5;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_ROCK >= 5) && (G_ONMISSION == 0) && (G_BIKE == 5)) // если миссия "Рекламный тур" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_29();// звонок от Митча Байкера ("Я хотел сказать, что мне очень понравилось шоу.") 
					set_anim_out();
					CLEAR_PRINTS();
					G_BIKE = 6;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_AVERY >= 5) && (G_ONMISSION == 0) && (G_CUBAN == 0))  // если миссия "Ту Би Хит" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_18();// звонок от Умберто (стари миссии "Трюки на лодке")
					set_anim_out();
					CLEAR_PRINTS();
					G_CUBAN = 1;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_CUBAN >= 2) && (G_ONMISSION == 0) && (G_HAITI == 0))  // если миссия "Трюки на лодке" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_19();// звонок от Тётушки Полет (стари миссии "Джу-Джу Скрембл")
					set_anim_out();
					CLEAR_PRINTS();
					G_HAITI = 1;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_HAITI == 5) && (G_ONMISSION == 0) && (IS_CHAR_IN_AREA_3D( GetPlayerPed(), -209.925, 216.375, -35.491, -917.502, 952.896, 150.0, 0 )))  // если миссия "Грязное дело" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_21();// звонок от Тётушки Полет (Зачем ты вернулся Томми? Ны не хотим тебя здесь видеть.)
					set_anim_out();
					CLEAR_PRINTS();
					G_HAITI = 6;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_PROTECT >= 2) && (G_ONMISSION == 0) && (G_AVERY_CALL == 0))  // если миссия "Шакдаун" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_14();// звонок от Эвери ("Привет сынок, хотел дать тебе совет...")
					set_anim_out();
					CLEAR_PRINTS();
					G_AVERY_CALL = 1;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_CLUB == 1) && (G_ONMISSION == 0)) // если "Клуб Малебу" куплен
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_30();// звонок от Кента Пола (старт миссии "Нет выхода.")
					set_anim_out();
					CLEAR_PRINTS();
					G_CLUB = 2;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_CUBAN == 6) && (G_ONMISSION == 0))  // если миссия "Троянский вуду" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_22();// звонок от Умберто (Томми, это Умберто Робина. Эй, как дела в кафе?)
					set_anim_out();
					CLEAR_PRINTS();
					G_CUBAN = 7;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_CLUB >= 6) && (G_ONMISSION == 0) && (G_PHIL == 0)) // если миссия "Работёнка" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_31();// звонок от Фила (старт миссии "Торговец оружием")
					set_anim_out();
					CLEAR_PRINTS();
					G_PHIL = 1;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_PHIL == 2) && (G_ONMISSION == 0)) // если миссия "Торговец оружием" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_33();// звонок от Фила (старт миссии "Бумшайн Сайгон")
					set_anim_out();
					CLEAR_PRINTS();
					G_PHIL = 3;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_PHIL == 4) && (G_ONMISSION == 0)) // если миссия "Бумшайн Сайгон" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_34();// звонок от Фила ("как бы там ни было, рана заживает хорошо...")
					set_anim_out();
					CLEAR_PRINTS();
					G_PHIL = 5;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_PRON == 5) && (G_ONMISSION == 0)) // если миссия "G - прожектор" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_35();// звонок от Кента Пола ("...я всего лишь позвонил чтобы узнать, не могу ли я сняться в одном из твоих фильмов...")
					set_anim_out();
					CLEAR_PRINTS();
					G_PRON = 6;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_DIAZ == 5) && (G_ONMISSION == 0) && (!IS_CHAR_IN_ZONE(GetPlayerPed(), "BOAB")))  // если миссия "Спрос и предложение" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_8();// звонок от Ленса (звонок "Мы можем это сделать.")
					set_anim_out();
					CLEAR_PRINTS();
					G_DIAZ = 6;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		else if ((G_COUNT == 7) && (G_ONMISSION == 0) && (IS_CHAR_IN_ZONE(GetPlayerPed(), "STHBO"))) // если миссия "Держите друзей рядом..." пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_42();// звонок от Эрнеста Келли ("...Никогда не доверяй человеку, который ходит по улице в пижаме...")
					set_anim_out();
					CLEAR_PRINTS();
				
					G_ONMISSION = 0;
					G_COUNT = 8;
				}
				else
				{
					continue;
				}
			}
		}
		else if ((G_LAWYER >= 4) && (G_ONMISSION == 0) && (G_MAIN_CALL == 2)) // если миссия "Гнев присяжных" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_2();// звонок от Сони ("как загар?")
					set_anim_out();
					CLEAR_PRINTS();
					G_MAIN_CALL = 3;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		else if ((G_COUNT >= 7) && (G_ONMISSION == 0) && (G_LAWYER == 5) && (IS_CHAR_IN_ZONE(GetPlayerPed(), "BOAB"))) // если миссия "Держите друзей рядом..." пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_41();// звонок от Кента Пола ("Томми Версетти, как дела, мистер большая шишка?")
					set_anim_out();
					CLEAR_PRINTS();
				
					G_ONMISSION = 0;
					G_LAWYER = 6;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_DIAZ >= 9) && (G_ONMISSION == 0) && (G_MAIN_CALL == 3))  // если миссия "Вычищение" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_13();// звонок от Сонни ("эй Томми, это я, Сонни. Твой станый друг...")
					set_anim_out();
					CLEAR_PRINTS();
					G_MAIN_CALL = 4;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		else if ((G_PRON == 6) && (G_ONMISSION == 0) && (G_COUNT >= 7) && (IS_CHAR_IN_ZONE(GetPlayerPed(), "STEIN"))) // если миссия "G - прожектор" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_36();// звонок от Стива Скотта ("...Никогда не верил, что я художник, и теперь я добился этого...")
					set_anim_out();
					CLEAR_PRINTS();
					G_PRON = 7;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if (((G_COUNT >= 2) || (G_PRON >= 2)) && ((G_ONMISSION == 0) && (G_MAIN_CALL == 4)))  // если миссия "Смешать карты" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_17();// звонок от Сонни ("Томми... Сонни... Очевидно, у вас проблемы со слухом, потому повторяю...")
					set_anim_out();
					CLEAR_PRINTS();
					G_MAIN_CALL = 5;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_CLUB == 6) && (G_COUNT >= 3) && (G_COUNT < 7) && (G_ONMISSION == 0) && (G_MAIN_CALL >= 5)) // если миссия "Работёнка" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_32();// звонок от Розенберга ("Томми, Томми, Томми, я говорил с Сонни. Слышишь?")
					set_anim_out();
					CLEAR_PRINTS();
					G_CLUB = 7;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_PROTECT >= 3) && (G_ONMISSION == 0) && (G_LANCE_CALL == 0) && (G_COUNT < 7))  // если миссия "Разборки в баре" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_15();// звонок от Ланса ("Томми, есть разговор...")
					set_anim_out();
					CLEAR_PRINTS();
					G_LANCE_CALL = 1;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_PROTECT >= 4) && (G_ONMISSION == 0) && (G_LANCE_CALL == 1))  // если миссия "Земля копов" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_16();// звонок от Ланса ("Томми, это я, Ланс. Заткнись и слушай, Томми, у меня мало времени..")
					set_anim_out();
					CLEAR_PRINTS();
					G_LANCE_CALL = 2;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_COUNT == 5) && (G_ONMISSION == 0)) // если миссия "Завали рэкетира" пройдена
			  
   
																 
																		  
																	
														
														
														
														   
   

																																											
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_38();// звонок от Ленса (старт миссии "Держите друзей рядом...")
					set_anim_out();
					CLEAR_PRINTS();
					G_COUNT = 6;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_LAWYER >= 4) && (G_ONMISSION == 0) && (G_ASSASSIN == 0)) // если миссия "Гнев присяжных" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_3();// звонок от заказчика (старт миссии "Дорожный убийца") 
					set_anim_out();
					CLEAR_PRINTS();
					G_ASSASSIN = 1;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		if ((G_ASSASSIN == 2) && (G_ONMISSION == 0) && (G_CORTEZ >= 3)) // если миссия "Дорожный убийца" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_23();// звонок от заказчика (старт миссии "Прикончить жену ") 
					set_anim_out();
					CLEAR_PRINTS();
					G_ASSASSIN = 3;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		else if ((G_ASSASSIN == 4) && (G_ONMISSION == 0) && (G_DIAZ >= 4)) // если миссия "Прикончить жену" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_3();// звонок от заказчика (старт миссии "Автоцид") 
					set_anim_out();
					CLEAR_PRINTS();
					G_ASSASSIN = 5;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		else if ((G_ASSASSIN == 6) && (G_ONMISSION == 0) && (G_PROTECT >= 2)) // если миссия "Автоцид" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_25();// звонок от заказчика (старт миссии "Смерть по прибытию") 
					set_anim_out();
					CLEAR_PRINTS();
					G_ASSASSIN = 7;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
		else if ((G_ASSASSIN == 8) && (G_ONMISSION == 0) && (G_CLUB >= 4)) // если миссия "Смерть по прибытию" пройдена
		{
			SetTime(8000);
			if ((G_ONMISSION == 0) && (!IS_CHAR_IN_WATER(GetPlayerPed())))
			{
				G_ONMISSION = 1;
				melodi();
				if (incoming_call == 1)
				{
					call_26();// звонок от заказчика (старт миссии "Конци в воду") 
					set_anim_out();
					CLEAR_PRINTS();
					G_ASSASSIN = 9;
					G_ONMISSION = 0;
				}
				else
				{
					continue;
				}
			}
		}
	}				
}
void main(void)
{
	WAIT(2000);
	uint trubka = vc_mob_phone;
	REQUEST_MODEL(trubka);
	while (!HAS_MODEL_LOADED(trubka)) WAIT(0);
	CREATE_OBJECT_NO_OFFSET(trubka, 1.1, 1.1, -1.1, &trubka_1, TRUE);
	launcher();
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
	return;
}
