/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011
***********************************************************************/

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
int pick_skin_1, pick_skin_2, pick_skin_3, pick_skin_4, pick_skin_5, pick_skin_6, pick_skin_7, pick_skin_8, pick_skin_9, pick_skin_10, pick_skin_11, pick_skin_12, pick_skin_13, pick_skin_14, pick_skin_15;
Pickup weap_1, weap_2, weap_3, weap_4, weap_5, weap_6, weap_7, weap_8, weap_9, weap_10, weap_11, weap_12, weap_13, weap_14, weap_15, weap_16, weap_17, weap_18, weap_19, weap_20, weap_21, weap_22, weap_23, weap_24, weap_25, weap_26, weap_27, weap_28, weap_29, weap_30, weap_31, weap_32, weap_33, weap_34, weap_35, weap_36, weap_37, weap_38, weap_39, weap_40, weap_41, weap_42, weap_43, weap_44, weap_45, weap_46, weap_47, weap_48, weap_49;
Pickup aid_1, aid_2, aid_3, aid_4, aid_5, aid_6, aid_7, aid_8, aid_9, aid_10, aid_11, aid_12, aid_13, aid_14, aid_15, aid_16, aid_17, aid_18, aid_19, aid_20, aid_21, aid_22, aid_23, aid_24, aid_25;
Pickup arm_1, arm_2, arm_3, arm_4, arm_5, arm_6, arm_7, arm_8, arm_9, arm_10, arm_11, arm_12, arm_13, arm_14, arm_15, arm_16, arm_17, arm_18;
Pickup skin_1, skin_2, skin_3, skin_4, skin_5, skin_6, skin_7, skin_8, skin_9, skin_10, skin_11, skin_12, skin_13, skin_14, skin_15, skin_16, skin_17, skin_100;
Pickup pack_weap_1, pack_weap_2, pack_weap_3, pack_weap_4, pack_weap_5, pack_weap_6, pack_weap_7, pack_weap_8, pack_weap_9, pack_weap_10, pack_weap_11, pack_weap_12, pack_weap_13, pack_weap_14, pack_weap_15, pack_weap_16, pack_weap_17, pack_weap_18, pack_weap_19, pack_weap_20, pack_weap_21, pack_weap_22;
int add_weap1, add_weap2, add_weap3, add_weap4, add_weap5, add_weap6, add_weap7, add_weap8;

void swap_skin(int skinID)
{
	DO_SCREEN_FADE_OUT( 500 );// Затемняем экран
	while(true)
	{
		WAIT(0);
		if (IS_SCREEN_FADED_OUT())
		{
			break;
		}
	}
	if (!IS_WANTED_LEVEL_GREATER(GetPlayerIndex(), 2))
	{
		ALTER_WANTED_LEVEL(GetPlayerIndex(), 0);
		APPLY_WANTED_LEVEL_CHANGE_NOW(GetPlayerIndex());
	}
	SET_CHAR_COMPONENT_VARIATION(GetPlayerPed(), 1, skinID, 0);
	WAIT(500);
	DO_SCREEN_FADE_IN( 500 );// убирается затемнение экрана
}
void pickups(void)
{
	//============================== ОРУЖИЕ ==============================
	CREATE_PICKUP_ROTATE(w_knife, 2, 1, 551.7, -1013.1, 4.778, 90.0, 0.0, 0.0, &weap_1);
	CREATE_PICKUP_ROTATE(w_pumpshot, 2, 300, -926.01, -209.2, 8.848, 90.0, 0.0, 90.0, &weap_2);
	CREATE_PICKUP_ROTATE(w_rpg, 2, 300, -562.1, -650.57, 8.835, 80.0, 0.0, 0.0, &weap_3);
	CREATE_PICKUP_ROTATE(w_rifle, 2, 300, -1311.9, 245.871, 24.057, -90.0, -80.0, 90.0, &weap_4);
	CREATE_PICKUP_ROTATE(w_uzi2, 2, 300, 448.496, 1677.85, 18.737, 78.836, 0.337, -24.595, &weap_5);//uzi2//
	CREATE_PICKUP_ROTATE(w_m4, 2, 300, 400.2, 1552.2, 6.598, -85.0, 5.0, 0.0, &weap_6);
	CREATE_PICKUP_ROTATE(w_sniper, 2, 300, -309.1, -416.331, 3.883, -90.0, 0.0, 0.0, &weap_7); //sniper replaced//
	CREATE_PICKUP_ROTATE(w_fthrower, 2, 300, -582.1, -861.493, 6.027, 75.0, -75.0, -90.0, &weap_8);//fthrower replaced//
	CREATE_PICKUP_ROTATE(w_uzi, 2, 300, -278.017, -934.99, 5.227, 90.0, 0.0, 0.0, &weap_9);
	CREATE_PICKUP_ROTATE(w_uzi2, 2, 300, -112.911, 1227.60, 5.086, -90.0, 0.0, 0.0, &weap_10);
	CREATE_PICKUP_ROTATE(w_molotov, 2, 30, -320.331, 1881.96, 6.338, -16.406, -24.251, 5.128, &weap_11);
	CREATE_PICKUP_ROTATE(w_cue, 2, 1, 528.126, 809.666, 15.804, 5.0, 0.0, 0.0, &weap_12);
	CREATE_PICKUP_ROTATE(w_eagle, 2, 100, -750.509, 471.582, 5.45, -90.0, 0.0, 45.0, &weap_13);
	CREATE_PICKUP_ROTATE(w_buddyshot, 2, 14, -872.229, 709.083, 5.504, 90.0, 0.0, 0.0, &weap_14); //bubbyshot replaced//
	CREATE_PICKUP_ROTATE(w_m4, 2, 300, -548.187, 656.627, 3.598, -90.0, -75.0, 90.0, &weap_15);
	CREATE_PICKUP_ROTATE(w_grenade, 9, 10, -506.8, 68.1, 4.887, 100.0, 0.0, 0.0, &weap_16);
	CREATE_PICKUP_ROTATE(w_psg1, 100, 20, -681.3, -68.227, 20.452, -90.0, -75.0, 90.0, &weap_17);
	CREATE_PICKUP_ROTATE(w_m4, 2, 300, -786.583, -108.6, 6.814, 57.054, -72.036, 34.266, &weap_18);
	CREATE_PICKUP_ROTATE(w_fthrower, 2, 300, -113.649, 110.11, 5.241, 85.0, 0.0, 0.0, &weap_19);//fthrower replaced//
	CREATE_PICKUP_ROTATE(w_cleaver, 2, 1, 492.608, 72.374, 6.518, 0.0, 50.0, 0.0, &weap_20);
	CREATE_PICKUP_ROTATE(w_sniper, 2, 400, -41.2579, -38.2, 7.305, 90.0, -75.0, 0.0, &weap_21); //sniper replaced//
	CREATE_PICKUP_ROTATE(w_knife, 2, 1, -120.391, -13.893, 5.705, 0.0, 95.0, 90.0, &weap_22);
	CREATE_PICKUP_ROTATE(w_grenade, 2, 10, 796.769, 32.555, 6.364, -115.0, 0.0, 0.0, &weap_23);
	CREATE_PICKUP_ROTATE(w_uzi2, 2, 200, 720.901, 583.701, 4.686, 90.0, 0.0, 0.0, &weap_24);
	CREATE_PICKUP_ROTATE(w_glock, 2, 17, 773.5, 283.5, 6.430, 90.0, 0.0, 0.0, &weap_25);
	CREATE_PICKUP_ROTATE(w_e2_stickybomb, 2, 10, 988.576, 738.757, 8.435, 95.0, 0.0, 0.0, &weap_26); //replaced R grenade//
	CREATE_PICKUP_ROTATE(w_ak47, 2, 30, 851.9, 1126.31, 12.8296, -90.0, -75.0, 90.0, &weap_27);
	CREATE_PICKUP_ROTATE(w_knuckle, 2, 1, 657.01, -674.5, 5.164, 90.0, 0.0, 45.0, &weap_28); //brass knuckle//
	CREATE_PICKUP_ROTATE(w_bat, 2, 1, 640.164, -721.401, 6.145, 0.0, 15.0, 0.0, &weap_29);
	CREATE_PICKUP_ROTATE(w_shotgun, 2, 300, 1001.90, 83.701, 5.069, -85.076, 0.037, 74.133, &weap_30);
	CREATE_PICKUP_ROTATE(w_shotgun, 2, 300, 476.542, -426.2, 16.357, 63.697, -78.831, 26.74, &weap_31);
	CREATE_PICKUP_ROTATE(w_uzi2, 2, 300, 590.0, -362.301, 6.349, -90.0, 0.0, 0.0, &weap_32);//uzi2//
	CREATE_PICKUP_ROTATE(w_glock, 2, 300, 205.151, -784.942, 3.076, 90.0, 0.0, 45.0, &weap_33);
	CREATE_PICKUP_ROTATE(w_chnsaw, 2, 1000, 461.98, -797.197, 7.721, 0.0, 0.0, -100.0, &weap_34);
	CREATE_PICKUP_ROTATE(w_katana, 2, 1, 905.926, 1546.61, 14.274, -95.0, 15.0, 85.0, &weap_35);//katana
	CREATE_PICKUP_ROTATE(w_nitestick, 2, 1, 836.924, 46.756, 6.889, -95.0, 15.0, 85.0, &weap_36);
	CREATE_PICKUP_ROTATE(w_screwdriver, 2, 1, -242.285, -947.851, 7.955, -95.0, 15.0, 85.0, &weap_37);//screw//
	CREATE_PICKUP_ROTATE(w_tec9, 2, 200, 753.949, 556.006, 4.912, -95.0, 15.0, 85.0, &weap_38); //tec9//
	CREATE_PICKUP_ROTATE(w_tec9, 2, 200, -136.822, 112.795, 6.251, -95.0, 15.0, 85.0, &weap_40); //tec9//
	CREATE_PICKUP_ROTATE(w_fthrower, 2, 300, -192.860, 1417.217, 5.698, -95.0, 15.0, 85.0, &weap_42); //flameth secret//
	CREATE_PICKUP_ROTATE(w_machete, 2, 1, 256.188, 48.249, 5.395, -95.0, 15.0, 85.0, &weap_43); //machete//
	CREATE_PICKUP_ROTATE(w_minigun, 2, 1000, -208.109, -2.854, 18.305, -95.0, 15.0, 85.0, &weap_44); //minigun//
	CREATE_PICKUP_ROTATE(w_e2_stickybomb, 2, 10, -625.439, 857.349, 5.890, 95.0, 0.0, 0.0, &weap_45);
	CREATE_PICKUP_ROTATE(w_cleaver, 2, 1, 840.599, 633.892, 6.385, 95.0, 0.0, 0.0, &weap_46);
	CREATE_PICKUP_ROTATE(w_aug, 2, 120, 378.990, -875.081, 4.424, 90.0, 0.0, 0.0, &weap_47);
	CREATE_PICKUP_ROTATE(w_m16v2, 2, 600, 550.983, -297.427, 10.110, 90.0, 0.0, 20.0, &weap_48);
	CREATE_PICKUP_ROTATE(w_e2_p90, 2, 200, 437.728, -743.915, 4.429, 90.0, 0.0, 20.0, &weap_49);
	ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(weap_35, "mall_int");
	ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(weap_36, "cop_int");

//============================== АПТЕЧКИ ==============================
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -221.601, -972.362, 2.486, 0.0, 0.0, -20.0, &aid_1);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -258.261, -748.472, 5.022, -90.0, 0.0, 0.0, &aid_2);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 208.087, -623.869, 3.459, 95.983, -4.774, -45.064, &aid_3);//changed location//
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 318.327, -446.074, 5.168, 0.0, 0.0, -50.0, &aid_4);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -968.002, -332.395, 15.8187, 0.0, 0.0, 30.0, &aid_5);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 889.2, 61.601, 10.6653, 90.0, 0.0, 0.0, &aid_6);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -492.1, -105.3, 9.94311, -90.0, 0.0, 0.0, &aid_7);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 30.944, -56.445, 6.668, 0.0, 0.0, -90.0, &aid_8);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 25.326, -33.988, 14.805, 0.0, 0.0, -40.0, &aid_9);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -281.434, 30.116, 6.297, 0.0, 0.0, 0.0, &aid_10);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -453.171, 48.325, 8.346, 0.0, 0.0, 0.0, &aid_11);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -420.611, 453.63, 7.015, 0.0, 0.0, 0.0, &aid_12);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -711.631, 586.864, 6.708, 0.0, 0.0, 90.0, &aid_13);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -855.675, 616.592, 21.53, 0.0, 0.0, 0.0, &aid_14);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 517.086, 940.441, 14.967, 0.0, 0.0, 70.0, &aid_15);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 811.459, 999.218, 5.678, 90.0, 0.0, 25.0, &aid_16);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 905.049, 1228.09, 7.021, 0.0, 0.0, -3.0, &aid_17);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 820.144, 1290.76, 6.894, 0.0, 0.0, 90.0, &aid_18);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -399.766, 1271.39, 6.55, 0.0, 0.0, -5.0, &aid_19);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 443.701, 1632.01, 10.596, 90.0, 0.0, 0.0, &aid_20);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, 818.438, 1745.28, 14.621, 90.0, 0.0, -40.0, &aid_21);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -387.41, 1666.78, 6.8467, 0.0, 0.0, -25.0, &aid_22);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -388.801, 1677.81, 20.136, 90.0, 0.0, 0.0, &aid_23);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -239.693, 1797.82, 19.519, 0.0, 0.0, 0.0, &aid_24);
	CREATE_PICKUP_ROTATE(cj_first_aid_pickup, 2, 200, -45.101, 1971.501, 10.029, -65.037, -4.924, -89.13, &aid_25);
	ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(aid_9, "mansion_int");
	ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(aid_21, "mall_int");

//============================== БРОНЯ ==============================
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, 438.241, -706.2, 13.1521, -14.94, -1.29, -94.8, &arm_1);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, -299.696, -763.145, 6.318, 90.0, 0.0, 0.0, &arm_2);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, 638.701, -352.701, 6.241, 90.0, -180.0, 90.0, &arm_3);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, -745.573, -382.301, 8.833, -15.0, 0.0, 90.0, &arm_4);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, -735.809, 75.601, 4.701, -15.0, 0.0, -90.0, &arm_5);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, 582.991, 183.101, 2.734, -10.0, 0.0, -90.0, &arm_6);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, 953.392, 361.756, 7.905, -90.071, 1.651, -86.183, &arm_7);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, -625.901, 292.40, 12.22, -90.0, 0.0, -35.0, &arm_8);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, -1260.96, 243.60, 23.70, -10.0, 0.0, -90.0, &arm_9);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, 863.801, 692.826, 5.739, -14.945, 1.293, -155.17, &arm_10);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, 850.582, 1052.631, 6.264, -90.0, 0.0, 0.0, &arm_11);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, 362.201, 1043.601, 5.640, -90.0, 0.0, 0.0, &arm_12);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, -192.501, 1155.89, 5.628, -15.0, 0.0, 0.0, &arm_13);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, -488.901, 1256.61, 5.062, -15.0, 0.0, 0.0, &arm_14);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, 783.201, 1417.80, 19.492, -90.0, 0.0, 0.0, &arm_15);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, 475.8, 1484.101, 4.963, -90.0, 0.0, 0.0, &arm_16);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, 968.3, 1748.22, 12.953, -15.0, 0.0, 0.0, &arm_17);
	CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, -134.012, 1903.33, 10.7939, -90.0, 0.0, 0.0, &arm_18);

	pick_skin_1 = 0;
	pick_skin_2 = 0;
	pick_skin_3 = 0;
	pick_skin_4 = 0;
	pick_skin_5 = 0;
	pick_skin_6 = 0;
	pick_skin_7 = 0;
	pick_skin_8 = 0;
	pick_skin_9 = 0;
	pick_skin_10 = 0;
	pick_skin_11 = 0;
	pick_skin_12 = 0;
	pick_skin_13 = 0;
	pick_skin_14 = 0;
	pick_skin_15 = 0;
	skin_100 = 0;
	add_weap1 = 0;
	add_weap2 = 0;
	add_weap3 = 0;
	add_weap4 = 0;
	add_weap5 = 0;
	add_weap6 = 0;
	add_weap7 = 0;
	add_weap8 = 0;			   

	while (TRUE)
	{
		WAIT(0);
		//бонусное оружие сбора пакетов
		if ((G_PACKET == 1) && (add_weap1 == 0))
		{
			CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, 658.081, -738.753, 13.2342, -11.166, 0.252, 64.538, &pack_weap_1);// отель
			CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, 95.2247, -38.3479, 5.57377, -10.0, 0.0, 90.0, &pack_weap_2);// особняк
			CREATE_PICKUP_ROTATE(ec_bpjacket, 2, 100, -393.338, 1895.59, 60.7043, -15.0, 0.0, 0.0, &pack_weap_3);// хюман конго
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_2, "mansion_int");
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_1, "ocean_view_int");
			add_weap1 = 1;
		}
		if ((G_PACKET == 2) && (add_weap2 == 0))
		{
			CREATE_PICKUP_ROTATE(w_eagle, 2, 6, 654.738, -738.542, 13.2924, -91.638, -0.147, 87.579, &pack_weap_4);// отель
			CREATE_PICKUP_ROTATE(w_eagle, 2, 6, 101.028, -35.0397, 5.60441, -84.565, -0.019, 4.981, &pack_weap_5);// особняк
			CREATE_PICKUP_ROTATE(w_eagle, 2, 6, -394.505, 1895.02, 60.7353, -90.0, 0.0, 0.0, &pack_weap_6);// хюман конго
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_5, "mansion_int");
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_4, "ocean_view_int");
			add_weap2 = 1;
		}
		if ((G_PACKET == 3) && (add_weap3 == 0))
		{
			CREATE_PICKUP_ROTATE(w_chnsaw, 2, 1000, 654.881, -737.891, 13.3729, -2.117, 4.531, 64.916, &pack_weap_7);// отель
			CREATE_PICKUP_ROTATE(w_chnsaw, 2, 1000, 102.313, -35.2893, 5.72876, 0.0, 0.0, 0.0, &pack_weap_8);// особняк
			CREATE_PICKUP_ROTATE(w_chnsaw, 2, 1000, -385.332, 1895.79, 60.8665, 0.0, 0.0, -40.0, &pack_weap_9);// хюман конго
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_8, "mansion_int");
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_7, "ocean_view_int");
			add_weap3 = 1;
		}
		if ((G_PACKET == 4) && (add_weap4 == 0))
		{
			CREATE_PICKUP_ROTATE(w_mp5, 2, 30, 99.0192, -35.2361, 5.6018, -85.0, -5.0, 40.0, &pack_weap_11);// особняк
			CREATE_PICKUP_ROTATE(w_mp5, 2, 30, -392.622, 1894.95, 60.7353, -90.0, 0.0, 30.0, &pack_weap_12);// хюман конго
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_11, "mansion_int");
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_10, "ocean_view_int");
			add_weap4 = 1;
		}
		if ((G_PACKET == 5) && (add_weap5 == 0))
		{
			CREATE_PICKUP_ROTATE(w_psg1, 2, 20, 654.405, -739.743, 13.6601, 90.0, -65.0, 160.0, &pack_weap_13);// отель
			CREATE_PICKUP_ROTATE(w_psg1, 2, 20, 95.2833, -35.0347, 6.0449, 90.0, -105.0, 0.0, &pack_weap_14);// особняк
			CREATE_PICKUP_ROTATE(w_psg1, 2, 20, -402.12, 1895.18, 60.7539, -90.0, 0.0, 90.0, &pack_weap_15);// хюман конго
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_14, "mansion_int");
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_13, "ocean_view_int");
			add_weap5 = 1;
		}
		if ((G_PACKET == 6) && (add_weap6 == 0))
		{
			CREATE_PICKUP_ROTATE(w_rifle, 2, 100, 658.576, -738.166, 13.6815, 101.696, -64.536, 74.413, &pack_weap_16);// отель
			CREATE_PICKUP_ROTATE(w_rifle, 2, 100, 95.2652, -36.4558, 6.02537, -90.0, -75.0, -180.0, &pack_weap_17);// особняк
			CREATE_PICKUP_ROTATE(w_rifle, 2, 100, -403.225, 1894.99, 61.1544, -90.0, -75.0, 90.0, &pack_weap_18);// хюман конго
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_17, "mansion_int");
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_16, "ocean_view_int");
			add_weap6 = 1;
		}
		if ((G_PACKET == 7) && (add_weap7 == 0))
		{
			CREATE_PICKUP_ROTATE(w_rpg, 2, 8, 654.459, -739.168, 13.8412, -87.294, -112.761, -17.117, &pack_weap_19);// отель
			CREATE_PICKUP_ROTATE(w_rpg, 2, 8, 97.3453, -34.7902, 6.19572, -90.0, -75.0, 90.0, &pack_weap_20);// особняк
			CREATE_PICKUP_ROTATE(w_rpg, 2, 8, -404.197, 1894.61, 60.7386, -80.0, 0.0, 0.0, &pack_weap_21);// хюман конго
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_20, "mansion_int");
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(pack_weap_19, "ocean_view_int");
			add_weap7 = 1;
		}

		if (G_CUBAN == 6 && add_weap8 == 0)
		{
			CREATE_PICKUP_ROTATE(w_rifle, 2, 100, -1184.17 + 433.0004434, 102.62 + 532.9998721, 17.5 - 5.00017432 - 0.974, 90.0, 0.0, 180.0, &pack_weap_22);
			add_weap8 = 1;
		}

		if (skin_100 == 0 && GET_FLOAT_STAT(STAT_GAME_PROGRESS) >= (float)100)
		{
			PRINT_HELP("CUNTY"); //Congratulations, you've completed the game 100%. New clothes have been delivered to the Vercetti estate.
			skin_100 = 1;
		}

		//"Уличная Одежда" в отеле
		if ((G_LAWYER > 0) && (pick_skin_1 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_1, 2, 0, 663.82, -734.435, 14.5899, 0.0, 0.0, 96.0, &skin_1);
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(skin_1, "ocean_view_int");
			pick_skin_1 = 1;
		}
		//"Костюм Вечеринка" в отеле
		if ((G_LAWYER > 1) && (pick_skin_2 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_2, 2, 0, 662.679, -728.231, 14.5412, 0.0, 0.0, -14.0, &skin_2);
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(skin_2, "ocean_view_int");
			pick_skin_2 = 1;
		}
		//"Одежда Рабочего" в Молле
		if ((G_LAWYER > 4) && (pick_skin_3 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_3, 2, 0, 800.207, 1609.85, 13.9983, 0.0, -1.1, 120.0, &skin_3);
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(skin_3, "mall_int");
			pick_skin_3 = 1;
		}
		//"Одежда Гольф" в гольф клубе
		if ((G_AVERY > 1) && (pick_skin_4 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_4, 2, 0, 534.235, 791.449, 16.1144, -1.5, 5.4, 0.0, &skin_4);
			pick_skin_4 = 1;
		}
		//"Одежда Кубинца" в Маленькой Гаване
		if ((G_AVERY > 4) && (pick_skin_5 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_5, 2, 0, -594.04, 103.529, 5.75993, 31.683, 0.988, 94.333, &skin_5);
			pick_skin_5 = 1;
		}
		//"Одежда Полицейского" в Полицейском участке
		if ((G_CLUB > 2) && (pick_skin_6 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_6, 2, 0, 837.628, 46.0644, 6.7884, 0.0, 0.0, -50.0, &skin_6);
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(skin_6, "cop_int");
			pick_skin_6 = 1;
		}
		//"Одежда Грабитель" в Клубе Малибу
		if ((G_CLUB > 5) && (pick_skin_7 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_7, 2, 0, 899.435, 477.317, 10.4909, 0.0, 0.0, 120.0, &skin_7);
			pick_skin_7 = 1;
		}
		//"Одежда Казуал" в Молле
		if ((G_CORTEZ > 1) && (pick_skin_8 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_8, 2, 0, 842.74, 1578.96, 20.5903, 0.0, 0.0, -30.0, &skin_8);
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(skin_8, "mall_int");
			pick_skin_8 = 1;
		}
		//"Костюм Мр. Версетти" в Стрипклубе и в Особняке
		if ((G_STRIP > 0) && (pick_skin_9 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_9, 2, 0, 508.992, -916.912, 5.33723, 0.0, 0.0, -165.0, &skin_9);
			CREATE_PICKUP_ROTATE(vc_skin_9, 2, 0, 55.8635, -60.8588, 20.4881, 0.0, 0.0, -110.0, &skin_10);
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(skin_9, "stripclb_int");
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(skin_10, "mansion_int");
			pick_skin_9 = 1;
		}
		//"Одежда Чёрный спортивный костюм" в Даунтауне
		if ((G_DIAZ > 4) && (pick_skin_10 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_10, 2, 0, -485.187, 1416.45, 5.72155, 0.0, 0.0, 65.0, &skin_11);
			pick_skin_10 = 1;
		}
		//"Одежда Карсный спортивный костюм" в Маленькой Гаване
		if (pick_skin_11 == 0)
		{
			CREATE_PICKUP_ROTATE(vc_skin_11, 2, 0, -766.205, 210.277, 5.98091, 0.0, 0.0, -30.0, &skin_12);
			pick_skin_11 = 1;
		}
		//"Одежда Я прошёл Vice city..." в Особняке
		if ((skin_100 == 1) && (pick_skin_12 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_12, 2, 0, 59.4209, -59.5175, 20.2015, 0.0, 0.0, -175.0, &skin_13);
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(skin_13, "mansion_int");
			pick_skin_12 = 1;
		}
		//"Костюм Это просто бизнес" и "Костюм Старый друг" в Особняке
		if ((G_COUNT > 6) && (pick_skin_13 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_13, 2, 0, 25.4055, -31.6943, 14.7021, 0.0, 0.0, -115.0, &skin_14);
			CREATE_PICKUP_ROTATE(vc_skin_14, 2, 0, 32.3326, -31.8362, 13.9602, 0.0, 0.0, 45.0, &skin_15);
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(skin_14, "mansion_int");
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(skin_15, "mansion_int");
			pick_skin_13 = 1;
		}
		//"Уличная Одежда" в Особняке
		if ((G_PROTECT > 0) && (pick_skin_14 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_1, 2, 0, 50.4535, -60.2118, 20.2525, 0.0, 0.0, -70.0, &skin_16);
			ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(skin_16, "mansion_int");
			pick_skin_14 = 1;
		}
		//"Уличная Одежда" в Даунтауне
		if ((G_CONDO > 0) && (pick_skin_15 == 0))
		{
			CREATE_PICKUP_ROTATE(vc_skin_1, 2, 0, -383.022, 1895.62, 60.6947, 0.0, 0.0, -35.0, &skin_17);
			pick_skin_15 = 1;
		}

		if (((HAS_PICKUP_BEEN_COLLECTED(skin_1)) && (DOES_PICKUP_EXIST(skin_1))) || ((HAS_PICKUP_BEEN_COLLECTED(skin_16)) && (DOES_PICKUP_EXIST(skin_16))) || ((HAS_PICKUP_BEEN_COLLECTED(skin_17)) && (DOES_PICKUP_EXIST(skin_17))))
		{
			swap_skin(0); //Уличная Одежда
		}
		if ((HAS_PICKUP_BEEN_COLLECTED(skin_2)) && (DOES_PICKUP_EXIST(skin_2)))
		{
			swap_skin(1); //Костюм Вечеринка
		}
		if ((HAS_PICKUP_BEEN_COLLECTED(skin_3)) && (DOES_PICKUP_EXIST(skin_3)))
		{
			swap_skin(2); //Одежда Рабочего
		}
		if ((HAS_PICKUP_BEEN_COLLECTED(skin_4)) && (DOES_PICKUP_EXIST(skin_4)))
		{
			swap_skin(3); //Одежда Гольф
		}
		if ((HAS_PICKUP_BEEN_COLLECTED(skin_5)) && (DOES_PICKUP_EXIST(skin_5)))
		{
			swap_skin(4); //Одежда Кубинца
		}
		if ((HAS_PICKUP_BEEN_COLLECTED(skin_6)) && (DOES_PICKUP_EXIST(skin_6)))
		{
			swap_skin(5); //Одежда Полицейского
		}
		if ((HAS_PICKUP_BEEN_COLLECTED(skin_7)) && (DOES_PICKUP_EXIST(skin_7)))
		{
			swap_skin(6); //Одежда Грабитель
		}
		if ((HAS_PICKUP_BEEN_COLLECTED(skin_8)) && (DOES_PICKUP_EXIST(skin_8)))
		{
			swap_skin(7); //Одежда Казуал
		}
		if (((HAS_PICKUP_BEEN_COLLECTED(skin_9)) && (DOES_PICKUP_EXIST(skin_9))) || ((HAS_PICKUP_BEEN_COLLECTED(skin_10)) && (DOES_PICKUP_EXIST(skin_10))))
		{
			swap_skin(8); //Костюм Мр. Версетти
		}
		if ((HAS_PICKUP_BEEN_COLLECTED(skin_11)) && (DOES_PICKUP_EXIST(skin_11)))
		{
			swap_skin(9); //Одежда Чёрный спортивный костюм
		}
		if ((HAS_PICKUP_BEEN_COLLECTED(skin_12)) && (DOES_PICKUP_EXIST(skin_12)))
		{
			swap_skin(10); //Одежда Карсный спортивный костюм
		}
		if ((HAS_PICKUP_BEEN_COLLECTED(skin_13)) && (DOES_PICKUP_EXIST(skin_13)))
		{
			swap_skin(13); //Одежда Я прошёл Vice city...
		}
		if ((HAS_PICKUP_BEEN_COLLECTED(skin_14)) && (DOES_PICKUP_EXIST(skin_14)))
		{
			swap_skin(11); //Костюм Это просто бизнес
		}
		if ((HAS_PICKUP_BEEN_COLLECTED(skin_15)) && (DOES_PICKUP_EXIST(skin_15)))
		{
			swap_skin(12); //Костюм Старый друг
		}
	}
}
void main(void)
{
	THIS_SCRIPT_SHOULD_BE_SAVED();
	pickups();
	WAIT(2000);
	while (TRUE)
	{
		WAIT(0);
	}
    return;
}
