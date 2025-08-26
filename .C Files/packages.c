#include <natives.h>
#include <common.h>
#include <types.h>
#include <consts.h>
#include "globals.h"

#define MAX_PACKAGES 100

Pickup package[MAX_PACKAGES];
int package_flag[MAX_PACKAGES], packages_collected;

void create_package(int id, float x, float y, float z)
{
	CREATE_PICKUP(vc_packages, 22, x, y, z, &package[id], 0);
}

void display_package_text(void)
{
	SETTIMERA(0);

	while (true)
	{
		WAIT(0);

		SET_TEXT_COLOUR(27, 89, 130, 255);
		SET_TEXT_SCALE(0.5, 0.7);
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 250);
		SET_TEXT_CENTRE(1);

		if (packages_collected == MAX_PACKAGES)
		{
			DISPLAY_TEXT(0.5, 0.35, "CO_ALL"); // You got all of them. Here's a little something...
		}
		else
		{
			DISPLAY_TEXT_WITH_2_NUMBERS(0.5, 0.35, "CO_ONE", packages_collected, MAX_PACKAGES); // Hidden Package ~1~ of ~1~
		}

		if (TIMERA() > 5000 || IS_CHAR_DEAD(GetPlayerPed()) || HAS_CHAR_BEEN_ARRESTED(GetPlayerPed()))
		{
			break;
		}
	}
}

void check_packages(void)
{
	int i;

	for (i = 0; i < MAX_PACKAGES; i++)
	{
		if (package_flag[i] == 1)
		{
			continue;
		}

		if (HAS_PICKUP_BEEN_COLLECTED(package[i]))
		{
			package_flag[i] = 1;
			packages_collected += 1;

			ADD_SCORE(GetPlayerIndex(), 100);

			if (packages_collected == MAX_PACKAGES)
			{
				ADD_SCORE(GetPlayerIndex(), 100000);
			}

			if (10 <= packages_collected <= 100 && packages_collected % 10 == 0)
			{
				G_GAME_PROGRESS += 1;
				SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);

				int reward = packages_collected / 10;

				G_PACKET = reward;

				if (reward == 1)
				{
					PRINT_HELP("PICK1"); // Body Armor delivered to Ocean View Hotel!
				}
				else if (reward == 2)
				{
					PRINT_HELP("PICK2"); // Chainsaw delivered to Ocean View Hotel!
				}
				else if (reward == 3)
				{
					PRINT_HELP("PICK3"); // 357 delivered to Ocean View Hotel!
				}
				else if (reward == 4)
				{
					PRINT_HELP("PICK4"); // MP5 delivered to Ocean View Hotel!
				}
				else if (reward == 5)
				{
					PRINT_HELP("PICK5"); // .308 Sniper delivered to Ocean View Hotel!
				}
				else if (reward == 6)
				{
					PRINT_HELP("PICK6"); // M60 delivered to Ocean View Hotel!
				}
				else if (reward == 7)
				{
					PRINT_HELP("PICK7"); // Rocket Launcher delivered to Ocean View Hotel!
				}
				else if (reward == 8)
				{
					PRINT_HELP("PICK8"); // Sparrow now available from the Mansion on Starfish Island!
				}
				else if (reward == 9)
				{
					PRINT_HELP("PICK9"); // Tank now available from the Army Barracks!
				}
				else if (reward == 10)
				{
					PRINT_HELP("PICK10"); // Hunter now available from the Army Barracks!
				}
			}

			display_package_text();

			if (!G_ONMISSION && !IS_AUTO_SAVE_IN_PROGRESS())
			{
				DO_AUTO_SAVE();
			}
			break;
		}
	}
}

void main(void)
{
	THIS_SCRIPT_SHOULD_BE_SAVED();

	create_package(0, 913.0994, -1185.418, 9.736586);
	create_package(1, 1141.4, 34.79999, 6.45);
	create_package(2, 220, -1114.1, 7.25);
	create_package(3, 64.60001, -1200.2, 5.711996);
	create_package(4, 329.1829, -1067.684, 4.369797);
	create_package(5, 198.3, -549.6, 7.721842);
	create_package(6, 521, -458.7, 13.24603);
	create_package(7, 638.4, -355.9, 6.273831);
	create_package(8, 616.1, -119.9, 4.638478);
	create_package(9, 803.9, 63.5, 7.95);
	create_package(10, 731.8, 254.5, 6.038167);
	create_package(11, 754.8, -241.3, 16.95351);
	create_package(12, 924.8, 487.7, 4.136826);
	create_package(13, 903.6589, 646.4711, 5.319037);
	create_package(14, 813.2898, 744.5702, 5.467783);
	create_package(15, 723.1, 828.4, 7.652855);
	create_package(16, 903.9001, 1656.6, 18.65);
	create_package(17, 840.6, 1551.2, 19.45);
	create_package(18, 994.6, 1690.1, 13.05297);
	create_package(19, 1324.8, 1406.8, 10.46477);
	create_package(20, 786.7, -31.29999, 50.54806);
	create_package(21, 739.9, 1710.5, 11.52917);
	create_package(22, 704.3, 1465.9, 3.952188);
	create_package(23, 761.7, 1250.2, 16.98205);
	create_package(24, 906.6468, 550.4587, 27.14715);
	create_package(25, 785.9095, 817.0086, 13.7679);
	create_package(26, 503.1, 53.39999, 7.766345);
	create_package(27, 486.6, 86.5, 2.522359);
	create_package(28, 699.3, 283.1, 30.23756);
	create_package(29, 846.9, 1750.4, 12.52021);
	create_package(30, 260.6, -808.3001, -1.946664);
	create_package(31, 199.9, -398.2, 3.942791);
	create_package(32, 506.2901, -262.5063, 5.805548);
	create_package(33, 540.5, -18.90002, 8.809023);
	create_package(34, 666.9001, 400.8, 2.173814);
	create_package(35, 857.6684, 620.7336, 5.348907);
	create_package(36, 834.6, 964.1, 5.519434);
	create_package(37, 626.9, 1211.8, 7.05504);
	create_package(38, 1022.4, 569, 10.84004);
	create_package(39, 954.3518, 399.0195, 28.68931);
	create_package(40, 391.2, 1455.4, 13.50255);
	create_package(41, 416.9, 1524.7, 4.979584);
	create_package(42, 493.7, 1449.5, 4.894477);
	create_package(43, 365.0553, 1657, 11.15717);
	create_package(44, 515.7, 1646.8, 12.84051);
	create_package(45, 503.5, 1132.3, 8.654015);
	create_package(46, 608.7708, 784.417, 6.062229);
	create_package(47, 478.4369, 381.8303, 6.561998);
	create_package(48, 386.4, 790.7, 18.66698);
	create_package(49, 476.4, 518, 11.47937);
	create_package(50, 196.1, -55.09997, 4.441433);
	create_package(51, -85.29633, -66.29999, 4.461915);
	create_package(52, -144.5201, 109.6854, 13.92293);
	create_package(53, 124.0885, 117.9701, 4.197048);
	create_package(54, 188.9354, 209.1507, 4.385242);
	create_package(55, 186.1, 1752.5, 5.029903);
	create_package(56, -18, 1819.6, 6.764299);
	create_package(57, -328.48, 1796.41, 5.648621);
	create_package(58, -1117.1, 1936.1, 2.815067);
	create_package(59, -357.8, 1652.4, 3.945103);
	create_package(60, -18.5, 1652.7, 55.23894);
	create_package(61, -135.6018, 1310.199, 16.96159);
	create_package(62, -465.7, 963.4, 5.060403);
	create_package(63, -546.0205, 797.9848, 3.294796);
	create_package(64, -422.8667, 761.1909, 7.085114);
	create_package(65, -639.5, 884.7, 5.350351);
	create_package(66, -728.6, 964.1, 5.174026);
	create_package(67, -542.1, 724.9, 6.731517);
	create_package(68, -600.1119, 577.1001, 5.428432);
	create_package(69, -561, 282.7, 4.823392);
	create_package(70, -671.9, 412.1, 14.23516);
	create_package(71, -700.3439, 176.0698, 9.114492);
	create_package(72, -762.1999, 215.3, 5.026275);
	create_package(73, -660.7, -67.09998, 20.15);
	create_package(74, -746.9, -43.29999, 6.849563);
	create_package(75, -587.9405, -340.6171, 12.04838);
	create_package(76, -420.2476, -97.11122, 6.367052);
	create_package(77, -746.1999, -185.8, 16.95944);
	create_package(78, -369.9, -651.6, 5.189179);
	create_package(79, -189.7, -842.4, 15.85281);
	create_package(80, -585, -960.8001, 13.49348);
	create_package(81, -657.2, -666.1999, 5.283512);
	create_package(82, -396.2, -928, 6.702013);
	create_package(83, -727.6, -800.8, 9.01815);
	create_package(84, -936.3001, -722.6999, 12.24);
	create_package(85, -847.9, -613.5, 16.33602);
	create_package(86, -1340.8, -520.1999, 8.95146);
	create_package(87, -754.3, -508.4, 8.951916);
	create_package(88, -1036.48, -348.29, 28.0069);
	create_package(89, -1128.8, -526.5, 8.940001);
	create_package(90, -916.1, -557.4, 18.68271);
	create_package(91, -1134.3, -522.5, 15.44);
	create_package(92, -933.4, -395, 14.97058);
	create_package(93, -1090.5, -286.1, 8.958352);
	create_package(94, -1396.1, -354.6, 8.942764);
	create_package(95, -1293.5, 113.8, 8.950307);
	create_package(96, -1304.2, 233.8, 8.948702);
	create_package(97, -895, -4.099975, 8.003187);
	create_package(98, -630.5, -432.5, 8.949265);
	create_package(99, -832.8001, -813.9, 23.78222);

	while (true)
	{
		WAIT(0);

		check_packages();
	}
}