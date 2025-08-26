#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
#include "mission_passed.h"
int heli, heli_blip, heli_2nd_blip, heli_cpcounter, heli_timer;
float heli_cp_x, heli_cp_y, heli_cp_z, heli_cp_2nd_x, heli_cp_2nd_y, heli_cp_2nd_z;
int heli_mission, heli_count;
int mins, seconds, temp_int;
int HG_HELI1SC = 99;//99999999
int HG_HELI2SC = 99;//99999999
int HG_HELI3SC = 99;//99999999
int HG_HELI4SC = 99;//99999999
int print_name = 0;
float cp0_x, cp0_y, cp0_z;
float cp1_x, cp1_y, cp1_z;
float cp2_x, cp2_y, cp2_z;
float cp3_x, cp3_y, cp3_z;
float cp4_x, cp4_y, cp4_z;
float cp5_x, cp5_y, cp5_z;
float cp6_x, cp6_y, cp6_z;
float cp7_x, cp7_y, cp7_z;
float cp8_x, cp8_y, cp8_z;
float cp9_x, cp9_y, cp9_z;
float cp10_x, cp10_y, cp10_z;
float cp11_x, cp11_y, cp11_z;
float cp12_x, cp12_y, cp12_z;
float cp13_x, cp13_y, cp13_z;
float cp14_x, cp14_y, cp14_z;
float cp15_x, cp15_y, cp15_z;
float cp16_x, cp16_y, cp16_z;
float cp17_x, cp17_y, cp17_z;
float cp18_x, cp18_y, cp18_z;
float cp19_x, cp19_y, cp19_z;
float cp20_x, cp20_y, cp20_z;
float cp21_x, cp21_y, cp21_z;
float cp22_x, cp22_y, cp22_z;
float cp23_x, cp23_y, cp23_z;
float cp24_x, cp24_y, cp24_z;
float cp25_x, cp25_y, cp25_z;
float cp26_x, cp26_y, cp26_z;
float cp27_x, cp27_y, cp27_z;
float cp28_x, cp28_y, cp28_z;
float cp29_x, cp29_y, cp29_z;
float cp30_x, cp30_y, cp30_z;
float cp31_x, cp31_y, cp31_z;
float cp32_x, cp32_y, cp32_z;
int heli_checkpoint1, heli_checkpoint2, fon, textur, best;

void main(void);

void setup_draw_text(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.156, 0.267);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
	return;
}

void setup_draw_value(void) {
	SET_TEXT_COLOUR(95, 195, 247, 255);
	SET_TEXT_SCALE(0.26, 0.445);
	SET_TEXT_DROPSHADOW(1, 26, 90, 128, 255);
	return;
}

void mission_cleanup_heli1(void) {
	G_ONMISSION = 0;
	REMOVE_BLIP(heli_blip);
	REMOVE_BLIP(heli_2nd_blip);
	MARK_CAR_AS_NO_LONGER_NEEDED(&heli);
	RELEASE_TEXTURE(fon);
	REMOVE_TXD(textur);
	//main();
	TERMINATE_THIS_SCRIPT();
}

void mission_heli1_passed(void) {
	if (!IS_BIT_SET(G_HELI1SC, heli_mission - 1))
	{
		SET_BIT(&G_HELI1SC, heli_mission - 1);
		INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
		G_GAME_PROGRESS += 1;
		SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
	}
	//PRINT_WITH_NUMBER_BIG("HELI_1B", 100, 5000, 1);
	ADD_SCORE(GetPlayerIndex(), 100);
	INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 100);

	CLEAR_WANTED_LEVEL(GetPlayerIndex());
	play_mission_complete_tune();
	heli_timer = heli_timer / 1000;
	mins = heli_timer / 60;
	temp_int = mins * 60;
	seconds = heli_timer - temp_int;
	if (heli_mission == 1) {
		if (HG_HELI1SC > heli_timer) {
			HG_HELI1SC = heli_timer;
			best = 1;
		}
	} else if (heli_mission == 2) {
		if (HG_HELI2SC > heli_timer) {
			HG_HELI2SC = heli_timer;
			best = 1;
		}
	} else if (heli_mission == 3) {
		if (HG_HELI3SC > heli_timer) {
			HG_HELI3SC = heli_timer;
			best = 1;
		}
	} else if (heli_mission == 4) {
		if (HG_HELI4SC > heli_timer) {
			HG_HELI4SC = heli_timer;
			best = 1;
		}
	}
	if (best == 1) {
		if (seconds > 9) {
			PRINT_WITH_2_NUMBERS_NOW("HELI_R3", mins, seconds, 10000, 1);
		} else {
			PRINT_WITH_2_NUMBERS_NOW("HELI_R4", mins, seconds, 10000, 1);
		}
	} else {
		if (seconds > 9) {
			PRINT_WITH_2_NUMBERS_NOW("HELI_R1", mins, seconds, 10000, 1);
		} else {
			PRINT_WITH_2_NUMBERS_NOW("HELI_R2", mins, seconds, 10000, 1);
		}
	}

	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(95, 195, 247, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.5, "HELI_1B", 100);//
		
		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	mission_cleanup_heli1();
}

void mission_heli1_failed(void) {
	if (!IS_BIT_SET(G_HELI1SC, heli_mission - 1))
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
	}
	PRINT_NOW("HELI_F1", 5000, 1);
	DELETE_CHECKPOINT(heli_checkpoint1);
	DELETE_CHECKPOINT(heli_checkpoint2);
	mission_cleanup_heli1();
}

void get_next_heli1_checkpoint(void) {
	if (heli_cpcounter == 0) {
		heli_cp_x = cp1_x;
		heli_cp_y = cp1_y;
		heli_cp_z = cp1_z;
		heli_cp_2nd_x = cp2_x;
		heli_cp_2nd_y = cp2_y;
		heli_cp_2nd_z = cp2_z;
	}
	if (heli_cpcounter == 1) {
		heli_cp_x = cp2_x;
		heli_cp_y = cp2_y;
		heli_cp_z = cp2_z;
		heli_cp_2nd_x = cp3_x;
		heli_cp_2nd_y = cp3_y;
		heli_cp_2nd_z = cp3_z;
	}
	if (heli_cpcounter == 2) {
		heli_cp_x = cp3_x;
		heli_cp_y = cp3_y;
		heli_cp_z = cp3_z;
		heli_cp_2nd_x = cp4_x;
		heli_cp_2nd_y = cp4_y;
		heli_cp_2nd_z = cp4_z;
	}
	if (heli_cpcounter == 3) {
		heli_cp_x = cp4_x;
		heli_cp_y = cp4_y;
		heli_cp_z = cp4_z;
		heli_cp_2nd_x = cp5_x;
		heli_cp_2nd_y = cp5_y;
		heli_cp_2nd_z = cp5_z;
	}
	if (heli_cpcounter == 4) {
		heli_cp_x = cp5_x;
		heli_cp_y = cp5_y;
		heli_cp_z = cp5_z;
		heli_cp_2nd_x = cp6_x;
		heli_cp_2nd_y = cp6_y;
		heli_cp_2nd_z = cp6_z;
	}
	if (heli_cpcounter == 5) {
		heli_cp_x = cp6_x;
		heli_cp_y = cp6_y;
		heli_cp_z = cp6_z;
		heli_cp_2nd_x = cp7_x;
		heli_cp_2nd_y = cp7_y;
		heli_cp_2nd_z = cp7_z;
	}
	if (heli_cpcounter == 6) {
		heli_cp_x = cp7_x;
		heli_cp_y = cp7_y;
		heli_cp_z = cp7_z;
		heli_cp_2nd_x = cp8_x;
		heli_cp_2nd_y = cp8_y;
		heli_cp_2nd_z = cp8_z;
	}
	if (heli_cpcounter == 7) {
		heli_cp_x = cp8_x;
		heli_cp_y = cp8_y;
		heli_cp_z = cp8_z;
		heli_cp_2nd_x = cp9_x;
		heli_cp_2nd_y = cp9_y;
		heli_cp_2nd_z = cp9_z;
	}
	if (heli_cpcounter == 8) {
		heli_cp_x = cp9_x;
		heli_cp_y = cp9_y;
		heli_cp_z = cp9_z;
		heli_cp_2nd_x = cp10_x;
		heli_cp_2nd_y = cp10_y;
		heli_cp_2nd_z = cp10_z;
	}
	if (heli_cpcounter == 9) {
		heli_cp_x = cp10_x;
		heli_cp_y = cp10_y;
		heli_cp_z = cp10_z;
		heli_cp_2nd_x = cp11_x;
		heli_cp_2nd_y = cp11_y;
		heli_cp_2nd_z = cp11_z;
	}
	if (heli_cpcounter == 10) {
		heli_cp_x = cp11_x;
		heli_cp_y = cp11_y;
		heli_cp_z = cp11_z;
		heli_cp_2nd_x = cp12_x;
		heli_cp_2nd_y = cp12_y;
		heli_cp_2nd_z = cp12_z;
	}
	if (heli_cpcounter == 11) {
		heli_cp_x = cp12_x;
		heli_cp_y = cp12_y;
		heli_cp_z = cp12_z;
		heli_cp_2nd_x = cp13_x;
		heli_cp_2nd_y = cp13_y;
		heli_cp_2nd_z = cp13_z;
	}
	if (heli_cpcounter == 12) {
		heli_cp_x = cp13_x;
		heli_cp_y = cp13_y;
		heli_cp_z = cp13_z;
		heli_cp_2nd_x = cp14_x;
		heli_cp_2nd_y = cp14_y;
		heli_cp_2nd_z = cp14_z;
	}
	if (heli_cpcounter == 13) {
		heli_cp_x = cp14_x;
		heli_cp_y = cp14_y;
		heli_cp_z = cp14_z;
		heli_cp_2nd_x = cp15_x;
		heli_cp_2nd_y = cp15_y;
		heli_cp_2nd_z = cp15_z;
	}
	if (heli_cpcounter == 14) {
		heli_cp_x = cp15_x;
		heli_cp_y = cp15_y;
		heli_cp_z = cp15_z;
		heli_cp_2nd_x = cp16_x;
		heli_cp_2nd_y = cp16_y;
		heli_cp_2nd_z = cp16_z;
	}
	if (heli_cpcounter == 15) {
		heli_cp_x = cp16_x;
		heli_cp_y = cp16_y;
		heli_cp_z = cp16_z;
		heli_cp_2nd_x = cp17_x;
		heli_cp_2nd_y = cp17_y;
		heli_cp_2nd_z = cp17_z;
	}
	if (heli_cpcounter == 16) {
		heli_cp_x = cp17_x;
		heli_cp_y = cp17_y;
		heli_cp_z = cp17_z;
		heli_cp_2nd_x = cp18_x;
		heli_cp_2nd_y = cp18_y;
		heli_cp_2nd_z = cp18_z;
	}
	if (heli_cpcounter == 17) {
		heli_cp_x = cp18_x;
		heli_cp_y = cp18_y;
		heli_cp_z = cp18_z;
		heli_cp_2nd_x = cp19_x;
		heli_cp_2nd_y = cp19_y;
		heli_cp_2nd_z = cp19_z;
	}
	if (heli_cpcounter == 18) {
		heli_cp_x = cp19_x;
		heli_cp_y = cp19_y;
		heli_cp_z = cp19_z;
		heli_cp_2nd_x = cp20_x;
		heli_cp_2nd_y = cp20_y;
		heli_cp_2nd_z = cp20_z;
	}
	if (heli_cpcounter == 19) {
		heli_cp_x = cp20_x;
		heli_cp_y = cp20_y;
		heli_cp_z = cp20_z;
		heli_cp_2nd_x = cp21_x;
		heli_cp_2nd_y = cp21_y;
		heli_cp_2nd_z = cp21_z;
	}
	if (heli_cpcounter == 20) {
		heli_cp_x = cp21_x;
		heli_cp_y = cp21_y;
		heli_cp_z = cp21_z;
		heli_cp_2nd_x = cp22_x;
		heli_cp_2nd_y = cp22_y;
		heli_cp_2nd_z = cp22_z;
	}
	if (heli_cpcounter == 21) {
		heli_cp_x = cp22_x;
		heli_cp_y = cp22_y;
		heli_cp_z = cp22_z;
		heli_cp_2nd_x = cp23_x;
		heli_cp_2nd_y = cp23_y;
		heli_cp_2nd_z = cp23_z;
	}
	if (heli_cpcounter == 22) {
		heli_cp_x = cp23_x;
		heli_cp_y = cp23_y;
		heli_cp_z = cp23_z;
		heli_cp_2nd_x = cp24_x;
		heli_cp_2nd_y = cp24_y;
		heli_cp_2nd_z = cp24_z;
	}
	if (heli_cpcounter == 23) {
		heli_cp_x = cp24_x;
		heli_cp_y = cp24_y;
		heli_cp_z = cp24_z;
		heli_cp_2nd_x = cp25_x;
		heli_cp_2nd_y = cp25_y;
		heli_cp_2nd_z = cp25_z;
	}
	if (heli_cpcounter == 24) {
		heli_cp_x = cp25_x;
		heli_cp_y = cp25_y;
		heli_cp_z = cp25_z;
		heli_cp_2nd_x = cp26_x;
		heli_cp_2nd_y = cp26_y;
		heli_cp_2nd_z = cp26_z;
	}
	if (heli_cpcounter == 25) {
		heli_cp_x = cp26_x;
		heli_cp_y = cp26_y;
		heli_cp_z = cp26_z;
		heli_cp_2nd_x = cp27_x;
		heli_cp_2nd_y = cp27_y;
		heli_cp_2nd_z = cp27_z;
	}
	if (heli_cpcounter == 26) {
		heli_cp_x = cp27_x;
		heli_cp_y = cp27_y;
		heli_cp_z = cp27_z;
		heli_cp_2nd_x = cp28_x;
		heli_cp_2nd_y = cp28_y;
		heli_cp_2nd_z = cp28_z;
	}
	if (heli_cpcounter == 27) {
		heli_cp_x = cp28_x;
		heli_cp_y = cp28_y;
		heli_cp_z = cp28_z;
		heli_cp_2nd_x = cp29_x;
		heli_cp_2nd_y = cp29_y;
		heli_cp_2nd_z = cp29_z;
	}
	if (heli_cpcounter == 28) {
		heli_cp_x = cp29_x;
		heli_cp_y = cp29_y;
		heli_cp_z = cp29_z;
		heli_cp_2nd_x = cp29_x;
		heli_cp_2nd_y = cp29_y;
		heli_cp_2nd_z = cp29_z;
	}
	return;
}

void mission_start_heli1(void) {
	if (!IS_BIT_SET(G_HELI1SC, heli_mission - 1))
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
	}
	G_ONMISSION = 1;
	WAIT(0);
	LOAD_ADDITIONAL_TEXT("HELIMIS", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	best = 0;
	heli_cpcounter = 0;
	if (heli_mission == 1) {
		heli_count = 29;
		
		cp1_x = -216.0867;
		cp1_y = 1350.9553;
		cp1_z = 53.3261;

		cp2_x = -254.3981;
		cp2_y = 1410.8699;
		cp2_z = 14.2173;

		cp3_x = -247.991;
		cp3_y = 1562.6863;
		cp3_z = 9.8169;

		cp4_x = -252.7914;
		cp4_y = 1693.2183;
		cp4_z = 35.7844;

		cp5_x = -248.2288;
		cp5_y = 1761.007;
		cp5_z = 24.1385;

		cp6_x = -282.1163;
		cp6_y = 1801.3054;
		cp6_z = 13.9955;

		cp7_x = -306.7144;
		cp7_y = 1831.5422;
		cp7_z = 22.204;

		cp8_x = -339.5856;
		cp8_y = 1856.4967;
		cp8_z = 24.5571;

		cp9_x = -345.6165;
		cp9_y = 1897.6418;
		cp9_z = 23.01;

		cp10_x = -304.8626;
		cp10_y = 1918.7019;
		cp10_z = 12.6542;

		cp11_x = -260.7673;
		cp11_y = 1924.167;
		cp11_z = 13.0634;

		cp12_x = -188.21;
		cp12_y = 1925.3232;
		cp12_z = 20.7998;

		cp13_x = -135.3698;
		cp13_y = 1867.9393;
		cp13_z = 11.9687;

		cp14_x = -67.4854;
		cp14_y = 1871.7985;
		cp14_z = 19.1703;

		cp15_x = -17.2907;
		cp15_y = 1863.6907;
		cp15_z = 14.1265;

		cp16_x = -4.3096;
		cp16_y = 1824.9919;
		cp16_z = 14.5951;

		cp17_x = -4.1924;
		cp17_y = 1774.3704;
		cp17_z = 15.7499;

		cp18_x = -1.3281;
		cp18_y = 1704.0105;
		cp18_z = 31.3199;

		cp19_x = -.3098;
		cp19_y = 1663.8998;
		cp19_z = 54.1069;

		cp20_x = -38.9337;
		cp20_y = 1618.1798;
		cp20_z = 60.1073;

		cp21_x = -94.0311;
		cp21_y = 1563.0038;
		cp21_z = 75.0094;

		cp22_x = -93.2093;
		cp22_y = 1427.1246;
		cp22_z = 76.9624;

		cp23_x = -46.8936;
		cp23_y = 1362.2973;
		cp23_z = 33.6828;

		cp24_x = -63.4014;
		cp24_y = 1279.3392;
		cp24_z = 18.935;

		cp25_x = -101.4188;
		cp25_y = 1272.7785;
		cp25_z = 14.0812;

		cp26_x = -141.4543;
		cp26_y = 1275.6052;
		cp26_z = 13.3836;

		cp27_x = -221.6465;
		cp27_y = 1284.4898;
		cp27_z = 14.9269;

		cp28_x = -240.5525;
		cp28_y = 1352.5656;
		cp28_z = 15.429;

		cp29_x = -225.4943;
		cp29_y = 1450.7946;
		cp29_z = 17.8624;
		
		//PRINT_BIG("HELI_1", 15000, 5);
	} else if (heli_mission == 2) {
		heli_count = 17;
		
		cp1_x = 510.8349;
		cp1_y = -691.6879;
		cp1_z = 12.9498;

		cp2_x = 536.4742;
		cp2_y = -594.8851;
		cp2_z = 13.187;

		cp3_x = 636.3635;
		cp3_y = -602.5078;
		cp3_z = 16.531;

		cp4_x = 693.3221;
		cp4_y = -684.4844;
		cp4_z = 8.0769;

		cp5_x = 597.5704;
		cp5_y = -712.7279;
		cp5_z = 16.9229;

		cp6_x = 503.0126;
		cp6_y = -745.6166;
		cp6_z = 14.1218;

		cp7_x = 470.6583;
		cp7_y = -840.4507;
		cp7_z = 14.4852;

		cp8_x = 371.4364;
		cp8_y = -848.0027;
		cp8_z = 25.3879;

		cp9_x = 277.4324;
		cp9_y = -816.1412;
		cp9_z = 12.5384;

		cp10_x = 247.5294;
		cp10_y = -911.637;
		cp10_z = 9.7326;

		cp11_x = 319.0973;
		cp11_y = -980.1001;
		cp11_z = 24.4323;

		cp12_x = 405.9276;
		cp12_y = -1028.8441;
		cp12_z = 14.2416;

		cp13_x = 485.9751;
		cp13_y = -969.7623;
		cp13_z = 27.7119;

		cp14_x = 561.6115;
		cp14_y = -905.5127;
		cp14_z = 14.4189;

		cp15_x = 611.8131;
		cp15_y = -818.6604;
		cp15_z = 18.4365;

		cp16_x = 573.4057;
		cp16_y = -726.0345;
		cp16_z = 18.2808;

		cp17_x = 482.463;
		cp17_y = -767.5123;
		cp17_z = 13.1885;
		
		//PRINT_BIG("HELI_2", 15000, 5);
	} else if (heli_mission == 3) {
		heli_count = 17;
		
		cp1_x = 851.872;
		cp1_y = 957.212;
		cp1_z = 18.939;

		cp2_x = 901.2843;
		cp2_y = 1044.3465;
		cp2_z = 12.8339;

		cp3_x = 821.0189;
		cp3_y = 1103.6234;
		cp3_z = 19.7767;

		cp4_x = 835.4129;
		cp4_y = 1202.7875;
		cp4_z = 14.5342;

		cp5_x = 847.7332;
		cp5_y = 1301.9945;
		cp5_z = 21.2997;

		cp6_x = 837.726;
		cp6_y = 1401.2524;
		cp6_z = 31.0822;

		cp7_x = 864.2298;
		cp7_y = 1497.5178;
		cp7_z = 20.8298;

		cp8_x = 963.7483;
		cp8_y = 1487.3203;
		cp8_z = 14.5602;

		cp9_x = 993.0611;
		cp9_y = 1391.4435;
		cp9_z = 17.8934;

		cp10_x = 968.6741;
		cp10_y = 1294.8905;
		cp10_z = 29.4453;

		cp11_x = 869.7039;
		cp11_y = 1292.5037;
		cp11_z = 15.3001;

		cp12_x = 849.7489;
		cp12_y = 1194.619;
		cp12_z = 9.1113;

		cp13_x = 798.7069;
		cp13_y = 1108.3921;
		cp13_z = 8.7494;

		cp14_x = 801.4762;
		cp14_y = 1007.9647;
		cp14_z = 16.6989;

		cp15_x = 758.9177;
		cp15_y = 917.3626;
		cp15_z = 11.9171;

		cp16_x = 795.0646;
		cp16_y = 824.0115;
		cp16_z = 17.9123;

		cp17_x = 732.0425;
		cp17_y = 899.165;
		cp17_z = 39.0408;

		//PRINT_BIG("HELI_3", 15000, 5);
	} else if (heli_mission == 4) {
		heli_count = 22;
		
		cp1_x = -451.2508;
		cp1_y = 769.4205;
		cp1_z = 9.9104;

		cp2_x = -444.2639;
		cp2_y = 669.5762;
		cp2_z = 10.8618;

		cp3_x = -529.5753;
		cp3_y = 617.3949;
		cp3_z = 10.367;

		cp4_x = -575.9863;
		cp4_y = 528.8209;
		cp4_z = 15.8638;

		cp5_x = -591.4166;
		cp5_y = 429.801;
		cp5_z = 11.4677;

		cp6_x = -614.0552;
		cp6_y = 332.2674;
		cp6_z = 7.6881;

		cp7_x = -656.4003;
		cp7_y = 242.008;
		cp7_z = 16.5889;

		cp8_x = -674.3932;
		cp8_y = 143.4139;
		cp8_z = 11.4733;

		cp9_x = -638.6635;
		cp9_y = 50.0264;
		cp9_z = 7.8348;

		cp10_x = -608.9073;
		cp10_y = -45.0964;
		cp10_z = 19.6455;

		cp11_x = -664.6498;
		cp11_y = -128.3502;
		cp11_z = 21.4531;

		cp12_x = -738.5753;
		cp12_y = -61.0601;
		cp12_z = 18.3888;

		cp13_x = -718.2493;
		cp13_y = 37.1378;
		cp13_z = 18.6951;

		cp14_x = -717.5405;
		cp14_y = 137.0044;
		cp14_z = 9.4461;

		cp15_x = -687.8385;
		cp15_y = 232.4182;
		cp15_z = 14.9118;

		cp16_x = -721.1664;
		cp16_y = 326.7881;
		cp16_z = 23.8656;

		cp17_x = -741.708;
		cp17_y = 423.9469;
		cp17_z = 11.0939;

		cp18_x = -660.5431;
		cp18_y = 482.5883;
		cp18_z = 14.3924;

		cp19_x = -606.9673;
		cp19_y = 567.2455;
		cp19_z = 17.2088;

		cp20_x = -578.1069;
		cp20_y = 662.8569;
		cp20_z = 9.767;

		cp21_x = -511.9561;
		cp21_y = 737.9092;
		cp21_z = 12.2276;

		cp22_x = -461.7881;
		cp22_y = 823.9517;
		cp22_z = 22.5338;
	
		//PRINT_BIG("HELI_4", 15000, 5);
	}

	get_next_heli1_checkpoint();
	PRINT_NOW("HELI_1A", 15000, 1);

	heli_checkpoint1 = CREATE_CHECKPOINT(8, heli_cp_x, heli_cp_y, heli_cp_z, heli_cp_x, heli_cp_y, heli_cp_z, 1.0);
	ADD_BLIP_FOR_COORD(heli_cp_x, heli_cp_y, heli_cp_z, &heli_blip);
	CHANGE_BLIP_COLOUR(heli_blip, 5);
	CHANGE_BLIP_DISPLAY(heli_blip, 2);
	CHANGE_BLIP_SCALE(heli_blip, 1);

	heli_checkpoint2 = CREATE_CHECKPOINT(8, heli_cp_2nd_x, heli_cp_2nd_y, heli_cp_2nd_z, heli_cp_2nd_x, heli_cp_2nd_y, heli_cp_2nd_z, 1.0);
	ADD_BLIP_FOR_COORD(heli_cp_2nd_x, heli_cp_2nd_y, heli_cp_2nd_z, &heli_2nd_blip);
	CHANGE_BLIP_COLOUR(heli_2nd_blip, 5);
	CHANGE_BLIP_DISPLAY(heli_2nd_blip, 2);
	CHANGE_BLIP_SCALE(heli_2nd_blip, 0.8);
	DIM_BLIP(heli_2nd_blip, 1);

	heli_timer = 0;
	if (IS_CHAR_IN_ANY_CAR(GetPlayerPed())) {
		STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &heli);
	} else {
		mission_heli1_failed();
	}
	while (!(heli_cpcounter == heli_count)) {
		WAIT(0);
		if (TIMERC() >= 1000) {
			heli_timer += 1000;
			SETTIMERC(0);
		}

		if (print_name == 0)
		{
			SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
			SET_TEXT_SCALE(0.5, 0.6); // размеры шрифта
			SET_TEXT_EDGE(1, 0, 0, 0, 255); //
			SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
			SET_TEXT_CENTRE(1); // задаём центр текста
			if (heli_mission == 1)
			{
				DISPLAY_TEXT(0.5, 0.45, "HELI_1");//
			}
			else if (heli_mission == 2)
			{
				DISPLAY_TEXT(0.5, 0.45, "HELI_2");//
			}
			else if (heli_mission == 3)
			{
				DISPLAY_TEXT(0.5, 0.45, "HELI_3");//
			}
			else if (heli_mission == 4)
			{
				DISPLAY_TEXT(0.5, 0.45, "HELI_4");//
			}

			if ( TIMERA() > 3000 )
			{
				print_name = 1;
			}
		}

		DRAW_SPRITE(fon, 0.8765625, 0.7858, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
		int timemin, timesec, timetemp;
		timesec = heli_timer / 1000;
		timemin = timesec / 60;
		timetemp = timemin * 60;
		timesec -= timetemp;
		setup_draw_text();	
		DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
		//if ((timesec > 9) && (timemin > 9)) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T1", timemin, timesec);
		//} else if ((timesec <= 9) && (timemin <= 9)) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T3", timemin, timesec);
		//} else if ((timesec > 9) && (timemin <= 9)) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T2", timemin, timesec);
		//} else if ((timesec <= 9) && (timemin > 9)) {
		//	setup_draw_value();
		//	DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76831852, "HOTR_T0", timemin, timesec);
		//}
		if ((timesec > 9) && (timemin > 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T1", timemin, timesec);
		} else if ((timesec <= 9) && (timemin <= 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T3", timemin, timesec);
		} else if ((timesec > 9) && (timemin <= 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T2", timemin, timesec);
		} else if ((timesec <= 9) && (timemin > 9)) {
			setup_draw_value();
			DISPLAY_TEXT_WITH_2_NUMBERS(0.9018542, 0.76954074, "HOTR_T0", timemin, timesec);
		}

		if (IS_CAR_DEAD(heli)) {
			mission_heli1_failed();
		}
		if (!IS_CHAR_IN_CAR(GetPlayerPed(), heli)) {
			mission_heli1_failed();
		}
		if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), heli_cp_x, heli_cp_y, heli_cp_z, 5.0, 5.0, 5.0, 0)) {
			PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
			heli_cpcounter++;
			DELETE_CHECKPOINT(heli_checkpoint1);
			DELETE_CHECKPOINT(heli_checkpoint2);
			REMOVE_BLIP(heli_blip);
			REMOVE_BLIP(heli_2nd_blip);
			get_next_heli1_checkpoint();
			heli_checkpoint1 = CREATE_CHECKPOINT(8, heli_cp_x, heli_cp_y, heli_cp_z, heli_cp_x, heli_cp_y, heli_cp_z, 1.0);
			ADD_BLIP_FOR_COORD(heli_cp_x, heli_cp_y, heli_cp_z, &heli_blip);
			CHANGE_BLIP_COLOUR(heli_blip, 5);
			CHANGE_BLIP_DISPLAY(heli_blip, 2);
			CHANGE_BLIP_SCALE(heli_blip, 1);
			if (heli_cpcounter < heli_count - 1) {
				heli_checkpoint2 = CREATE_CHECKPOINT(8, heli_cp_2nd_x, heli_cp_2nd_y, heli_cp_2nd_z, heli_cp_2nd_x, heli_cp_2nd_y, heli_cp_2nd_z, 1.0);
				ADD_BLIP_FOR_COORD(heli_cp_2nd_x, heli_cp_2nd_y, heli_cp_2nd_z, &heli_2nd_blip);
				CHANGE_BLIP_DISPLAY(heli_2nd_blip, 2);
				CHANGE_BLIP_SCALE(heli_2nd_blip, 0.8);
				DIM_BLIP(heli_2nd_blip, 1);
				if (heli_cpcounter < heli_count - 2) {
					CHANGE_BLIP_COLOUR(heli_2nd_blip, 5);
				} else {
					CHANGE_BLIP_COLOUR(heli_2nd_blip, 1);
				}
			} else {
				CHANGE_BLIP_COLOUR(heli_blip, 1);
			}		
		}
	}
	mission_heli1_passed();
}

void main(void) {

	SETTIMERA(0); //сбрасываем таймер 
	if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sparrow"))) && (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), -136.1451, 1384.0923, 17.8402, 2.0, 2.0, 2.0, 0)))
	{
		heli_mission = 1;
	}
	else if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sparrow"))) && (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), 461.4463, -778.7614, 11.4712, 2.0, 2.0, 2.0, 0)))
	{
		heli_mission = 2;
	}
	if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sparrow"))) && (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), 808.8450, 865.9194, 6.5155, 2.0, 2.0, 2.0, 0)))
	{
		heli_mission = 3;
	}
	if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sparrow"))) && (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), -453.5938, 769.5693, 8.9773, 2.0, 2.0, 2.0, 0)))
	{
		heli_mission = 4;
	}
	mission_start_heli1();
	mission_heli1_failed();

	//while (true) {
	//	WAIT(0);
	//	if (IS_PLAYER_PLAYING(GetPlayerIndex())) {
	//		if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sparrow"))) && (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), -136.1451, 1384.0923, 17.8402, 2.0, 2.0, 2.0, 0))) {
	//			if (G_ONMISSION == 0) {
	//				heli_mission = 1;
	//				mission_start_heli1();
	//				if (HAS_DEATHARREST_EXECUTED()) {
	//					mission_heli1_failed();
	//				}
	//				mission_cleanup_heli1();
	//			}
	//		}
	//		if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sparrow"))) && (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), 461.4463, -778.7614, 11.4712, 2.0, 2.0, 2.0, 0))) {
	//			if (G_ONMISSION == 0) {
	//				heli_mission = 2;
	//				mission_start_heli1();
	//				if (HAS_DEATHARREST_EXECUTED()) {
	//					mission_heli1_failed();
	//				}
	//				mission_cleanup_heli1();
	//			}
	//		}
	//		if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sparrow"))) && (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), 808.8450, 865.9194, 6.5155, 2.0, 2.0, 2.0, 0))) {
	//			if (G_ONMISSION == 0) {
	//				heli_mission = 3;
	//				mission_start_heli1();
	//				if (HAS_DEATHARREST_EXECUTED()) {
	//					mission_heli1_failed();
	//				}
	//				mission_cleanup_heli1();
	//			}
	//		}
	//		if ((IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("sparrow"))) && (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), -453.5938, 769.5693, 8.9773, 2.0, 2.0, 2.0, 0))) {
	//			if (G_ONMISSION == 0) {
	//				heli_mission = 4;
	//				mission_start_heli1();
	//				if (HAS_DEATHARREST_EXECUTED()) {
	//					mission_heli1_failed();
	//				}
	//				mission_cleanup_heli1();
	//			}
	//		}
	//	}
	//}
}