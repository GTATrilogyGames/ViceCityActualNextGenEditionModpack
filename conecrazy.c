#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
#include "mission_passed.h"

																										 
int record_temp;

						 

int player_4x4, wanted_4x4;
int counter_4x4_pickups; 
int flag_timer, timer_4x4, timer_4x4_secs;
int intro_time_lapsed, timer_intro_now, timer_intro_start, flag_intro, flag_intro_jump;

int flag_truck_1, flag_truck_2, truck_1, truck_2, truck_driver1, truck_driver2;
int flag_launch_4x4_1_ok;
int blip_1, blip_2, blip_3;
int blip_4, blip_5, blip_6;
int blip_7, blip_8, blip_9;
int blip_10, blip_11, blip_12;
int blip_13, blip_14, blip_15;
int blip_16, blip_17, blip_18;
int blip_19, blip_20, blip_21;
int blip_22, blip_23, blip_24;

int flag_blip_1, flag_blip_2, flag_blip_3, flag_blip_4; 
int flag_blip_5, flag_blip_6, flag_blip_7, flag_blip_8; 
int flag_blip_9, flag_blip_10, flag_blip_11, flag_blip_12;
int flag_blip_13, flag_blip_14, flag_blip_15, flag_blip_16;
int flag_blip_17, flag_blip_18, flag_blip_19, flag_blip_20;
int flag_blip_21, flag_blip_22, flag_blip_23, flag_blip_24;

float cam_4x4_X; 
float cam_4x4_y; 
float cam_4x4_z;

int flag_cone_smashed;
int cp_seconds;

int cone_1, cone_2, cone_3, cone_4;
int cone_5, cone_6, cone_7, cone_8;
int cone_9, cone_10, cone_11, cone_12;
int cone_13, cone_14, cone_15, cone_16;
int cone_17, cone_18, cone_19, cone_20;
int cone_21, cone_22, cone_23, cone_24;
int cone_25, cone_26, cone_27, cone_28;
int cone_29, cone_30, cone_31, cone_32;
int cp1, cp2, cp3, cp4, cp5, cam;

int cp_minutes;

float x_cone_1, y_cone_1, z_cone; 
float x_cone_2, y_cone_2;  
float x_cone_3, y_cone_3;  
float x_cone_4, y_cone_4;  
float x_cone_5, y_cone_5;  
float x_cone_6, y_cone_6;  
float x_cone_7, y_cone_7; 
float x_cone_8, y_cone_8;  
float x_cone_9, y_cone_9;  
float x_cone_10, y_cone_10;  
float x_cone_11, y_cone_11;  
float x_cone_12, y_cone_12;  
float x_cone_13, y_cone_13;  
float x_cone_14, y_cone_14;  
float x_cone_15, y_cone_15; 

float x_1, y_1, z_1;
float x_2, y_2, z_2;
float x_3, y_3, z_3;
float x_4, y_4, z_4;
float x_5, y_5, z_5;
float x_6, y_6, z_6;
float x_7, y_7, z_7;
float x_8, y_8, z_8;
float x_9, y_9, z_9;
float x_10, y_10, z_10;
float x_11, y_11, z_11;
float x_12, y_12, z_12;
float x_13, y_13, z_13;
float x_14, y_14, z_14;
float x_15, y_15, z_15;
float x_16, y_16, z_16;
float x_17, y_17, z_17;
float x_18, y_18, z_18;
float x_19, y_19, z_19;
float x_20, y_20, z_20;
float x_21, y_21, z_21;
float x_22, y_22, z_22;

float circle_radius, cone_x, cone_y, theta;  
float circle_x, circle_y;
int textur, fon;


#define KEYBOARD_ENTER			28			/*rebusx*/
#define KEYBOARD_SPACE			57
#define CONTROL_KEYBOARD_HORN	54
#define CONTROL_MOUSE_LEFT		38

#define CONTROLLER_BUTTON_B		17

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

void car_park_record(void) {
	cp_minutes = 0;
	cp_seconds = G_CARPRK_RECORD;
	while (cp_seconds > 59) {
		cp_seconds = cp_seconds - 60;
		cp_minutes++;
	}
	PRINT_WITH_2_NUMBERS_NOW("NEW_REC", cp_minutes, cp_seconds, 5000, 1);
	G_CARPRK_BONUS = G_CARPRK_BONUS - 1000;
	if (G_CARPRK_BONUS < 6000) {
		G_CARPRK_BONUS = 6000;
	}
	G_CARPRK_PRINT_BONUS--;
	if (G_CARPRK_PRINT_BONUS < 6) {
		G_CARPRK_PRINT_BONUS = 6;
	}

	SETTIMERA(0); //сбрасываем таймер 
	while (true)
	{
		SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
		SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
		SET_TEXT_EDGE(1, 0, 0, 0, 255); //
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
		SET_TEXT_CENTRE(1); // задаём центр текста
		DISPLAY_TEXT_WITH_NUMBER(0.5, 0.4, "M_PASS", G_CARPRK_REWARD);//
		
		WAIT( 0 );
		if ( TIMERA() > 4000 )
		{
			break;
		}
	}
	ADD_SCORE(GetPlayerIndex(), G_CARPRK_REWARD);
	INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, G_CARPRK_REWARD);

	return;
}

void delete_cones(void) {
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_1);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_2);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_3);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_4);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_5);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_6);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_7);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_8);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_9);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_10);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_11);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_12);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_13);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_14);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_15);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_16);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_17);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_18);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_19);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_20);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_21);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_22);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_23);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_24);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_25);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_26);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_27);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_28);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_29);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_30);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_31);
	MARK_OBJECT_AS_NO_LONGER_NEEDED(&cone_32);
	return;
}

void main(void);

void mission_cleanup_carpark1(void) {
	SET_INSTANT_WIDESCREEN_BORDERS(0);
	SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	REMOVE_BLIP(blip_1);
	REMOVE_BLIP(blip_2);
	REMOVE_BLIP(blip_3);
	REMOVE_BLIP(blip_4);
	REMOVE_BLIP(blip_5);
	delete_cones();
	MARK_MODEL_AS_NO_LONGER_NEEDED(GET_HASH_KEY("trafficcone"));
	//G_ONMISSION = 0;
	TERMINATE_THIS_SCRIPT();
	//main();
}

void mission_carpark1_passed(void) {
	if (G_CARPRK == 0) {
		G_CARPRK_RECORD = TIMERA();
		G_CARPRK_RECORD = G_CARPRK_RECORD / 1000;
		car_park_record();
	} else {
		record_temp = TIMERA();
		record_temp = record_temp / 1000;

		if (record_temp < G_CARPRK_RECORD)
		{
			G_CARPRK_RECORD = record_temp;
			G_CARPRK_REWARD = G_CARPRK_REWARD*2;
			car_park_record();
		}
		else
		{
			SETTIMERA(0); //сбрасываем таймер 
			while (true)
			{
				SET_TEXT_COLOUR(30, 215, 135, 255); // задаём цвет текста
				SET_TEXT_SCALE(0.5, 0.7); // размеры шрифта
				SET_TEXT_EDGE(1, 0, 0, 0, 255); //
				SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200); // задаём тень текста
				SET_TEXT_CENTRE(1); // задаём центр текста
				DISPLAY_TEXT_WITH_NUMBER(0.5, 0.4, "M_PASS", 200);//
				
				WAIT( 0 );
				if ( TIMERA() > 4000 )
				{
					break;
				}
			}
			ADD_SCORE(GetPlayerIndex(), 200);
			INCREMENT_FLOAT_STAT(STAT_MADE_FROM_MISSIONS, 200);
		}
    }  
	if (G_CARPRK == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_PASSED, 1);
		G_GAME_PROGRESS += 1;
		SET_FLOAT_STAT(STAT_GAME_PROGRESS, (float)G_GAME_PROGRESS * (float)100 / (float)150);
  

				   
  
		G_CARPRK = 1;
	}
				 


			 
  
						   
   
				  
					  
	
							
	
   
							
   
		 
   
  
													   
												   
			 
  
																		   
														  
									
																			 
															 
															
  
			
						
   
		 
   
  
										
														  
								   
						   
									 
										
								   
										   
					   
			
														 
											
	 
	 
	CLEAR_WANTED_LEVEL(GetPlayerIndex());
	mission_cleanup_carpark1();
}

void mission_carpark1_failed(void) {
	//PRINT_BIG ("M_FAIL", 2000, 1);								 
	if (G_CARPRK == 0)
	{
		INCREMENT_INT_STAT(STAT_MISSIONS_FAILED, 1);
	}

	MissionFailed();
	mission_cleanup_carpark1();
}

void cone_circle(void) {
	while (true) {
		cone_x = SIN(theta);
		cone_x = cone_x * circle_radius;
		cone_x = cone_x + circle_x;
		cone_y = COS(theta);
		cone_y = cone_y * circle_radius;
		cone_y = cone_y + circle_y;
		
		if (theta == 0.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_16, 1);
			SET_OBJECT_COLLISION(cone_16, 1);
			SET_OBJECT_DYNAMIC(cone_16, 1);
		}
		if (theta == 18.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_17, 1);
			SET_OBJECT_COLLISION(cone_17, 1);
			SET_OBJECT_DYNAMIC(cone_17, 1);
		}
		if (theta == 36.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_18, 1);
			SET_OBJECT_COLLISION(cone_18, 1);
			SET_OBJECT_DYNAMIC(cone_18, 1);
		}
		if (theta == 54.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_19, 1);
			SET_OBJECT_COLLISION(cone_19, 1);
			SET_OBJECT_DYNAMIC(cone_19, 1);
		}
		if (theta == 72.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_20, 1);
			SET_OBJECT_COLLISION(cone_20, 1);
			SET_OBJECT_DYNAMIC(cone_20, 1);
		}
		if (theta == 90.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_21, 1);
			SET_OBJECT_COLLISION(cone_21, 1);
			SET_OBJECT_DYNAMIC(cone_21, 1);
		}
		if (theta == 108.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_22, 1);
			SET_OBJECT_COLLISION(cone_22, 1);
			SET_OBJECT_DYNAMIC(cone_22, 1);
		}
		if (theta == 126.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_23, 1);
			SET_OBJECT_COLLISION(cone_23, 1);
			SET_OBJECT_DYNAMIC(cone_23, 1);
		}
		if (theta == 144.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_24, 1);
			SET_OBJECT_COLLISION(cone_24, 1);
			SET_OBJECT_DYNAMIC(cone_24, 1);
		}
		if (theta == 162.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_25, 1);
			SET_OBJECT_COLLISION(cone_25, 1);
			SET_OBJECT_DYNAMIC(cone_25, 1);
		}
		if (theta == 180.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_26, 1);
			SET_OBJECT_COLLISION(cone_26, 1);
			SET_OBJECT_DYNAMIC(cone_26, 1);
		}
		if (theta == 198.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_27, 1);
			SET_OBJECT_COLLISION(cone_27, 1);
			SET_OBJECT_DYNAMIC(cone_27, 1);
		}
		if (theta == 216.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_28, 1);
			SET_OBJECT_COLLISION(cone_28, 1);
			SET_OBJECT_DYNAMIC(cone_28, 1);
		}
		if (theta == 234.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_29, 1);
			SET_OBJECT_COLLISION(cone_29, 1);
			SET_OBJECT_DYNAMIC(cone_29, 1);
		}
		if (theta == 252.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_30, 1);
			SET_OBJECT_COLLISION(cone_30, 1);
			SET_OBJECT_DYNAMIC(cone_30, 1);
		}
		if (theta == 270.0) {
			GET_GROUND_Z_FOR_3D_COORD(cone_x, cone_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), cone_x, cone_y, z_cone+0.3, &cone_31, 1);
			SET_OBJECT_COLLISION(cone_31, 1);
			SET_OBJECT_DYNAMIC(cone_31, 1);
		}
		theta = theta + 18.0;
		if (theta < 288.0) {
			continue;
		} else {
			break;
		}
	}
	return;
}

void cone_check(void) {
	if ((HAS_OBJECT_BEEN_DAMAGED(cone_1)) || (HAS_OBJECT_BEEN_DAMAGED(cone_2)) || (HAS_OBJECT_BEEN_DAMAGED(cone_3))) {
		flag_cone_smashed = 1;
	}
	if ((HAS_OBJECT_BEEN_DAMAGED(cone_4)) || (HAS_OBJECT_BEEN_DAMAGED(cone_5)) || (HAS_OBJECT_BEEN_DAMAGED(cone_6))) {
		flag_cone_smashed = 1;
	}
	if ((HAS_OBJECT_BEEN_DAMAGED(cone_7)) || (HAS_OBJECT_BEEN_DAMAGED(cone_8)) || (HAS_OBJECT_BEEN_DAMAGED(cone_9))) {
		flag_cone_smashed = 1;
	}
	if ((HAS_OBJECT_BEEN_DAMAGED(cone_10)) || (HAS_OBJECT_BEEN_DAMAGED(cone_11)) || (HAS_OBJECT_BEEN_DAMAGED(cone_12))) {
		flag_cone_smashed = 1;
	}
	if ((HAS_OBJECT_BEEN_DAMAGED(cone_13)) || (HAS_OBJECT_BEEN_DAMAGED(cone_14)) || (HAS_OBJECT_BEEN_DAMAGED(cone_15))) {
		flag_cone_smashed = 1;
	}
	if ((HAS_OBJECT_BEEN_DAMAGED(cone_16)) || (HAS_OBJECT_BEEN_DAMAGED(cone_17)) || (HAS_OBJECT_BEEN_DAMAGED(cone_18))) {
		flag_cone_smashed = 1;
	}
	if ((HAS_OBJECT_BEEN_DAMAGED(cone_19)) || (HAS_OBJECT_BEEN_DAMAGED(cone_20)) || (HAS_OBJECT_BEEN_DAMAGED(cone_21))) {
		flag_cone_smashed = 1;
	}
	if ((HAS_OBJECT_BEEN_DAMAGED(cone_22)) || (HAS_OBJECT_BEEN_DAMAGED(cone_23)) || (HAS_OBJECT_BEEN_DAMAGED(cone_24))) {
		flag_cone_smashed = 1;
	}
	if ((HAS_OBJECT_BEEN_DAMAGED(cone_25)) || (HAS_OBJECT_BEEN_DAMAGED(cone_26)) || (HAS_OBJECT_BEEN_DAMAGED(cone_27))) {
		flag_cone_smashed = 1;
	}
	if ((HAS_OBJECT_BEEN_DAMAGED(cone_28)) || (HAS_OBJECT_BEEN_DAMAGED(cone_29)) || (HAS_OBJECT_BEEN_DAMAGED(cone_30))) {
		flag_cone_smashed = 1;
	}
	if ((HAS_OBJECT_BEEN_DAMAGED(cone_31)) || (HAS_OBJECT_BEEN_DAMAGED(cone_32))) {
		flag_cone_smashed = 1;
	}
	return;
}

void mission_start_carpark1(void) {
				   
  
												 
  
				   
	SETTIMERA(0);

	while (true)
	{
		WAIT(0);

		SET_TEXT_COLOUR(30, 215, 135, 255);
		SET_TEXT_SCALE(0.5, 0.6);
		SET_TEXT_EDGE(1, 0, 0, 0, 255);
		SET_TEXT_DROPSHADOW(1, 0, 0, 0, 200);
		SET_TEXT_CENTRE(1);
		DISPLAY_TEXT(0.5, 0.45, "MM_1");

			
		if (TIMERA() > 3000)
		{
			break;
		}
    }
	DO_SCREEN_FADE_OUT(1000);
	while (IS_SCREEN_FADING()) {
		WAIT(0);
	}
	LOAD_ADDITIONAL_TEXT("CARPAR1", 6);
	textur = LOAD_TXD("sunshine_race");
	fon = GET_TEXTURE(textur, "fon_hud");
	//PRINT_BIG("MM_1", 5000, 2);
	WAIT(0);
	counter_4x4_pickups = 0;
	timer_4x4 = 0;
	flag_intro = 0;
	flag_timer = 0;
	flag_intro_jump = 0;
	intro_time_lapsed = 0;
	flag_cone_smashed = 0;
	if (G_CARPRK == 0) {
		INCREMENT_INT_STAT(STAT_MISSIONS_ATTEMPTED, 1);
		G_CARPRK_BONUS = 12000;
		G_CARPRK_PRINT_BONUS = 12;
		G_CARPRK_REWARD = 200;
	}
	
	flag_truck_1 = 0;
	flag_truck_2 = 0;

	flag_blip_1 = 0;
	flag_blip_2 = 0;
	flag_blip_3 = 0;
	flag_blip_4 = 0;
	flag_blip_5 = 0;
	flag_blip_6 = 0;
	flag_blip_7 = 0;
	flag_blip_8 = 0;
	flag_blip_9 = 0;
	flag_blip_10 = 0;
	flag_blip_11 = 0;
	flag_blip_12 = 0;
	flag_blip_13 = 0;
	flag_blip_14 = 0;
	flag_blip_15 = 0;
	flag_blip_16 = 0;
	flag_blip_17 = 0;
	flag_blip_18 = 0;
	flag_blip_19 = 0;
	flag_blip_20 = 0;
	flag_blip_21 = 0;
	flag_blip_22 = 0;
	flag_blip_23 = 0;
	flag_blip_24 = 0;

	record_temp = 0;
	
	cam_4x4_X = 539.0;
	cam_4x4_y = -709.0;
	cam_4x4_z = 30.5;
	
	theta = 0.0;
	circle_x = 561.0;
	circle_y = -647.75;
	
	circle_radius = 8.0;
	
	z_cone = -105.0;
	
	x_cone_1 = 541.8;
	y_cone_1 = -699.9;

	x_cone_2 = 553.25;
	y_cone_2 = -697.6; 

	x_cone_3 = 544.2;
	y_cone_3 = -686.7; 

	x_cone_4 = 571.6;
	y_cone_4 = -678.8; 

	x_cone_5 = 571.6;
	y_cone_5 = -674.2; 

	x_cone_6 = 574.6;
	y_cone_6 = -674.2; 

	x_cone_7 = 574.6;
	y_cone_7 = -678.8; 

	x_cone_8 = 577.6;
	y_cone_8 = -674.2; 

	x_cone_9 = 580.6;
	y_cone_9 = -674.2; 

	x_cone_10 = 566.25;
	y_cone_10 = -613.5; 

	x_cone_11 = 566.25;
	y_cone_11 = -616.5; 

	x_cone_12 = 566.25;
	y_cone_12 = -622.5; 

	x_cone_13 = 542.25;
	y_cone_13 = -622.5; 

	x_cone_14 = 554.25;
	y_cone_14 = -622.5; 

	x_cone_15 = 550.25;
	y_cone_15 = -622.5; 

	x_1 = 541.8;    
	y_1 = -695.8;
	z_1 = 28.7;

	x_2 = 545.6;    
	y_2 = -699.9;
	z_2 = 28.7;

	x_3 = 573.3;   
	y_3 = -676.5; 
	z_3 = 26.5;

	x_4 = 541.8;   
	y_4 = -614.5; 
	z_4 = 26.5;

	x_5 = 564.5;   
	y_5 = -649.9; 
	z_5 = 26.5;

	x_6 = 625.2; 
	y_6 = -768.0; 
	z_6 = 5.6;

	x_7 = 679.0;   
	y_7 = -895.6; 
	z_7 = 6.0;

	x_8 = 644.8;   
	y_8 = -959.8; 
	z_8 = 6.5; 

	x_9 = 223.0;   
	y_9 = -747.5; 
	z_9 = 6.0;

	x_10 = 552.3;   
	y_10 = -1084.2;
	z_10 = 5.5;

	x_11 = 478.0;   
	y_11 = -1090.2;
	z_11 = 2.4;

	x_12 = 343.4; 
	y_12 = -1061.9; 
	z_12 = 6.3;

	x_13 = 274.3;    
	y_13 = -966.3;
	z_13 = 5.7;

	x_14 = 252.7;      
	y_14 = -684.4;
	z_14 = 5.4;

	x_15 = 374.8;  
	y_15 = -631.8;
	z_15 = 5.4;

	x_16 = 384.1;    
	y_16 = -551.3;
	z_16 = 5.4;

	x_17 = 437.7;    
	y_17 = -553.4;
	z_17 = 5.6;

	x_19 = 272.2;    
	y_19 = -856.3;
	z_19 = 5.4;

	x_20 = 439.8;  
	y_20 = -629.0;
	z_20 = 5.6;

	x_21 = 639.0;  
	y_21 = -677.4;
	z_21 = 6.3;

	x_22 = 660.7;  
	y_22 = -787.0;
	z_22 = 5.7;

	SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
	SET_INSTANT_WIDESCREEN_BORDERS(1);
	STORE_WANTED_LEVEL(GetPlayerIndex(), &wanted_4x4);
	CLEAR_WANTED_LEVEL(GetPlayerIndex());
	STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &player_4x4);
	if (!IS_CAR_DEAD(player_4x4)) {
		LOCK_CAR_DOORS(player_4x4, 1);
		SET_CAR_COORDINATES(player_4x4, 561.6019, -617.38, 25.893);
		SET_CAR_HEADING(player_4x4, 180.0);
	}
	//CLEAR_THIS_PRINT("M_PASS");
	//CLEAR_THIS_PRINT("M_FAIL");
	REQUEST_MODEL(GET_HASH_KEY("trafficcone"));
	while (!HAS_MODEL_LOADED(GET_HASH_KEY("trafficcone"))){
		WAIT(0);
	}
	ADD_BLIP_FOR_COORD(x_1, y_1, z_1, &blip_1);
	CHANGE_BLIP_COLOUR(blip_1, 5);
	ADD_BLIP_FOR_COORD(x_2, y_2, z_2, &blip_2);
	CHANGE_BLIP_COLOUR(blip_2, 5);
	ADD_BLIP_FOR_COORD(x_3, y_3, z_3, &blip_3);
	CHANGE_BLIP_COLOUR(blip_3, 5);
	ADD_BLIP_FOR_COORD(x_4, y_4, z_4, &blip_4);
	CHANGE_BLIP_COLOUR(blip_4, 5);
	ADD_BLIP_FOR_COORD(x_5, y_5, z_5, &blip_5);
	CHANGE_BLIP_COLOUR(blip_5, 5);
	cp1 = CREATE_CHECKPOINT(8, x_1, y_1, z_1, x_1, y_1, z_1, 0.2);
	cp2 = CREATE_CHECKPOINT(8, x_2, y_2, z_2, x_2, y_2, z_2, 0.2);
	cp3 = CREATE_CHECKPOINT(8, x_3, y_3, z_3, x_3, y_3, z_3, 0.2);
	cp4 = CREATE_CHECKPOINT(8, x_4, y_4, z_4, x_4, y_4, z_4, 0.2);
	cp5 = CREATE_CHECKPOINT(8, x_5, y_5, z_5, x_5, y_5, z_5, 0.2);
	SETTIMERB(0);
	while (counter_4x4_pickups < 5) {
		WAIT(0);
		if ((flag_intro == 4) && (flag_timer == 1)) {
			if (TIMERB() > 1000) {
				timer_4x4 -= 1000;
				SETTIMERB(0);
			}
			DRAW_SPRITE(fon, 0.8765625, 0.7858, 0.14322917, 0.0296, 0.0, 246, 151, 255, 155);
			int timemin, timesec, timetemp;
			timesec = timer_4x4 / 1000;
			timemin = timesec / 60;
			timetemp = timemin * 60;
			timesec -= timetemp;
			setup_draw_text();	
			DISPLAY_TEXT(0.78815097, 0.77731852, "A_TMSG");
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
		}
		if (flag_timer == 1) {
			if (timer_4x4 < 1) {
				PRINT_NOW("TIMEOUT", 3000, 1);
				mission_carpark1_failed();
			}
		}
		if ((counter_4x4_pickups == 1) && (flag_timer == 0)) {
			SETTIMERA(0);
			flag_timer = 1;
		}
		
		if (flag_blip_1 == 0) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_1, y_1, z_1, 2.5, 2.5, 3.5, 0)) {
				REMOVE_BLIP(blip_1);
				DELETE_CHECKPOINT(cp1);
				counter_4x4_pickups++;
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				timer_4x4 += G_CARPRK_BONUS;
				flag_blip_1 = 1;
			}
		}
		if (flag_blip_2 == 0) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_2, y_2, z_2, 2.5, 2.5, 3.5, 0)) {
				REMOVE_BLIP(blip_2);
				DELETE_CHECKPOINT(cp2);
				counter_4x4_pickups++;
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				timer_4x4 += G_CARPRK_BONUS;
				flag_blip_2 = 1;
			}
		}
		if (flag_blip_3 == 0) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_3, y_3, z_3, 2.5, 2.5, 3.5, 0)) {
				REMOVE_BLIP(blip_3);
				DELETE_CHECKPOINT(cp3);
				counter_4x4_pickups++;
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				timer_4x4 += G_CARPRK_BONUS;
				flag_blip_3 = 1;
			}
		}
		if (flag_blip_4 == 0) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_4, y_4, z_4, 2.5, 2.5, 3.5, 0)) {
				REMOVE_BLIP(blip_4);
				DELETE_CHECKPOINT(cp4);
				counter_4x4_pickups++;
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				timer_4x4 += G_CARPRK_BONUS;
				flag_blip_4 = 1;
			}
		}
		if (flag_blip_5 == 0) {
			if (LOCATE_CHAR_IN_CAR_3D(GetPlayerPed(), x_5, y_5, z_5, 2.5, 2.5, 3.5, 0)) {
				REMOVE_BLIP(blip_5);
				DELETE_CHECKPOINT(cp5);
				counter_4x4_pickups++;
				PLAY_AUDIO_EVENT("FRONTEND_OTHER_RACE_321");
				timer_4x4 += G_CARPRK_BONUS;
				flag_blip_5 = 1;
			}
		}
		
		if (G_CARPRK_INTRO_BEFORE == 1) {
			if ((flag_intro_jump == 0) && (flag_intro > 0) && (flag_intro < 4)) {
				if (IS_GAME_KEYBOARD_KEY_PRESSED(57)) {
					intro_time_lapsed = 9501;
					flag_intro = 3;
					flag_intro_jump = 1;
				}
			}
		}
		if (flag_intro == 0) {
			GET_GAME_TIMER(&timer_intro_start);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_1, y_cone_1, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_1, y_cone_1, z_cone+0.3, &cone_1, 1);
			SET_OBJECT_COLLISION(cone_1, 1);
			SET_OBJECT_DYNAMIC(cone_1, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_2, y_cone_2, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_2, y_cone_2, z_cone+0.3, &cone_2, 1);
			SET_OBJECT_COLLISION(cone_2, 1);
			SET_OBJECT_DYNAMIC(cone_2, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_3, y_cone_3, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_3, y_cone_3, z_cone+0.3, &cone_3, 1);
			SET_OBJECT_COLLISION(cone_3, 1);
			SET_OBJECT_DYNAMIC(cone_3, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_4, y_cone_4, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_4, y_cone_4, z_cone+0.3, &cone_4, 1);
			SET_OBJECT_COLLISION(cone_4, 1);
			SET_OBJECT_DYNAMIC(cone_4, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_5, y_cone_5, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_5, y_cone_5, z_cone+0.3, &cone_5, 1);
			SET_OBJECT_COLLISION(cone_5, 1);
			SET_OBJECT_DYNAMIC(cone_5, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_6, y_cone_6, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_6, y_cone_6, z_cone+0.3, &cone_6, 1);
			SET_OBJECT_COLLISION(cone_6, 1);
			SET_OBJECT_DYNAMIC(cone_6, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_7, y_cone_7, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_7, y_cone_7, z_cone+0.3, &cone_7, 1);
			SET_OBJECT_COLLISION(cone_7, 1);
			SET_OBJECT_DYNAMIC(cone_7, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_8, y_cone_8, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_8, y_cone_8, z_cone+0.3, &cone_8, 1);
			SET_OBJECT_COLLISION(cone_8, 1);
			SET_OBJECT_DYNAMIC(cone_8, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_9, y_cone_9, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_9, y_cone_9, z_cone+0.3, &cone_9, 1);
			SET_OBJECT_COLLISION(cone_9, 1);
			SET_OBJECT_DYNAMIC(cone_9, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_10, y_cone_10, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_10, y_cone_10, z_cone+0.3, &cone_10, 1);
			SET_OBJECT_COLLISION(cone_10, 1);
			SET_OBJECT_DYNAMIC(cone_10, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_11, y_cone_11, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_11, y_cone_11, z_cone+0.3, &cone_11, 1);
			SET_OBJECT_COLLISION(cone_11, 1);
			SET_OBJECT_DYNAMIC(cone_11, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_12, y_cone_12, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_12, y_cone_12, z_cone+0.3, &cone_12, 1);
			SET_OBJECT_COLLISION(cone_12, 1);
			SET_OBJECT_DYNAMIC(cone_12, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_13, y_cone_13, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_13, y_cone_13, z_cone+0.3, &cone_13, 1);
			SET_OBJECT_COLLISION(cone_13, 1);
			SET_OBJECT_DYNAMIC(cone_13, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_14, y_cone_14, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_14, y_cone_14, z_cone+0.3, &cone_14, 1);
			SET_OBJECT_COLLISION(cone_14, 1);
			SET_OBJECT_DYNAMIC(cone_14, 1);
			
			GET_GROUND_Z_FOR_3D_COORD(x_cone_15, y_cone_15, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), x_cone_15, y_cone_15, z_cone+0.3, &cone_15, 1);
			SET_OBJECT_COLLISION(cone_15, 1);
			SET_OBJECT_DYNAMIC(cone_15, 1);
			
			cone_circle();
			
			GET_GROUND_Z_FOR_3D_COORD(circle_x, circle_y, 200.0, &z_cone);
			CREATE_OBJECT_NO_OFFSET(GET_HASH_KEY("trafficcone"), circle_x, circle_y, z_cone+0.3, &cone_32, 1);
			SET_OBJECT_COLLISION(cone_32, 1);
			SET_OBJECT_DYNAMIC(cone_32, 1);
			
			LOAD_SCENE(cam_4x4_X, cam_4x4_y, cam_4x4_z);
			CREATE_CAM(14, &cam);
			SET_CAM_POS(cam, cam_4x4_X, cam_4x4_y, cam_4x4_z);
			POINT_CAM_AT_COORD(cam, x_2, y_2, z_2);
			SET_CAM_ACTIVE(cam, 1);
			SET_CAM_PROPAGATE(cam, 1);
			ACTIVATE_SCRIPTED_CAMS(1, 1);
			DO_SCREEN_FADE_IN(1000);
			while (IS_SCREEN_FADING()) {
				WAIT(0);
			}
			PRINT_NOW("MM_1_A", 5000, 1);
			flag_intro = 1;
		}
		
		if (flag_intro_jump == 0) {
			GET_GAME_TIMER(&timer_intro_now);
			intro_time_lapsed = timer_intro_now - timer_intro_start;
		}
		
		if ((intro_time_lapsed > 4000) && (flag_intro == 1)) {
			SET_CAM_POS(cam, 589.3, -687.1, 29.0);
			POINT_CAM_AT_COORD(cam, x_3, y_3, z_3);
			flag_intro = 2;			
		}
		
		if ((intro_time_lapsed > 7000) && (flag_intro == 2)) {
			SET_CAM_POS(cam, 539.5, -606.0, 33.13);
			POINT_CAM_AT_COORD(cam, x_4, y_4, z_4);
			PRINT_WITH_NUMBER_NOW("MM_1_C", G_CARPRK_PRINT_BONUS, 5000, 1);
			flag_intro = 3;
		}
		
						   
   
								  
   
  
		if ((intro_time_lapsed > 9500) && (flag_intro == 3)) {
			DO_SCREEN_FADE_OUT(1000);
			while (IS_SCREEN_FADING()) {
				WAIT(0);
			}
			CLEAR_PRINTS();
			ACTIVATE_SCRIPTED_CAMS(0, 0);
			SET_CAM_BEHIND_PED(GetPlayerPed());
			SET_INSTANT_WIDESCREEN_BORDERS(0);
			SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
			if (!IS_CAR_DEAD(player_4x4)) {
				LOCK_CAR_DOORS(player_4x4, 1);
			}
			ALTER_WANTED_LEVEL(GetPlayerIndex(), wanted_4x4);
			DO_SCREEN_FADE_IN(1000);
			while (IS_SCREEN_FADING()) {
				WAIT(0);
			}
			flag_intro = 4;
			G_CARPRK_INTRO_BEFORE = 1;
		}
		
		if (!IS_CHAR_IN_MODEL(GetPlayerPed(), GET_HASH_KEY("stalion"))) {
			PRINT_NOW("T4x4_F", 3000, 1);
			mission_carpark1_failed();
		}
		cone_check();
		
		if (flag_cone_smashed == 1) {
			PRINT_NOW("CONE_1", 5000, 1);
					
	
				 
	
	   
	
				 
	
			mission_carpark1_failed();
		}
	}
	
	if (counter_4x4_pickups == 5) {
		mission_carpark1_passed();
	}
}

void main(void) {
	if ((G_CARPRK == 0))
	{
		G_CARPRK_RECORD = 120;
	}
	mission_start_carpark1();
				 
									
						   
	 
											  
							
																																							  
								 
	   
																										
								   
			   
								
	   
												
												 
								  
		
	   
	  
	 
	
}