#include <types.h>

#define NUM_SHORTCUT_START_POINTS 8

boolean G_ONMISSION;
boolean G_GAME_PROGRESS;
boolean G_LAWYER;
boolean G_AVERY;
boolean G_CORTEZ;
boolean G_DIAZ;
boolean G_ASSASSIN;
boolean G_PROTECT;

boolean G_CUBAN;
boolean G_HAITI;
boolean G_BIKE;
boolean G_ROCK;
boolean G_PHIL;

boolean G_CABS;
boolean G_CLUB;
boolean G_PRON;
boolean G_COKERUN;
boolean G_ICECREAM;
boolean G_BUSINES_SA;
boolean G_COUNT;
boolean G_STRIP;
boolean G_COLLECTOR;

boolean G_SALE_NO;
boolean G_MAIN_CALL;
boolean G_LANCE_CALL;
boolean G_AVERY_CALL;

boolean G_SWANKO;
boolean G_LINKS;
boolean G_CONDO;
boolean G_HEIGHS;
boolean G_WS_1102;
boolean G_VP_3321;
boolean G_SHACK;

boolean G_BLOODRING;
boolean G_HOTRING;
boolean G_DIRTRING;
boolean G_TAXI;
boolean G_PIZZA;
boolean G_MEDIC;
boolean G_FIRE;
boolean G_COPCAR;
boolean G_HELI1SC;
boolean G_BMX_1;
boolean G_BMX_2;
boolean G_CARPRK;
boolean G_PCJ;
boolean G_RC_1;
boolean G_PACKET;
boolean G_SA_RACE;

int G_SHORT_CUT_STATE;
Car G_SHORT_CUT_VEHICLE;
Ped G_SHORT_CUT_DRIVER;
Blip G_SHORT_CUT_BLIP;
uint G_SHORT_CUT_TIMER;
float G_SHORT_CUT_START_X;
float G_SHORT_CUT_START_Y;
float G_SHORT_CUT_START_Z;
float G_SHORT_CUT_START_ANGLE;
float G_SHORT_CUT_DESTINATION_X;
float G_SHORT_CUT_DESTINATION_Y;
float G_SHORT_CUT_DESTINATION_Z;
float G_SHORT_CUT_DESTINATION_ANGLE;
float G_SHORT_CUT_DROP_OFF_FOR_MISSION_X;
float G_SHORT_CUT_DROP_OFF_FOR_MISSION_Y;
float G_SHORT_CUT_DROP_OFF_FOR_MISSION_Z;
float G_SHORT_CUT_DROP_OFF_FOR_MISSION_ANGLE;
float G_AFTER_DEATH_START_POINTS_X[NUM_SHORTCUT_START_POINTS];
float G_AFTER_DEATH_START_POINTS_Y[NUM_SHORTCUT_START_POINTS];
float G_AFTER_DEATH_START_POINTS_Z[NUM_SHORTCUT_START_POINTS];
float G_AFTER_DEATH_START_POINTS_ANGLE[NUM_SHORTCUT_START_POINTS];
uint G_NUM_AFTER_DEATH_START_POINTS;

int G_MISSION_ID;
uint G_MISSION_NAME_DURATION;

bool G_IS_IN_CUTSCENE;

// Used in conecrazy.c
uint G_CARPRK_RECORD;
uint G_CARPRK_REWARD;
uint G_CARPRK_INTRO_BEFORE;
uint G_CARPRK_BONUS;
uint G_CARPRK_PRINT_BONUS; // This doesn't really have to be a global, just matching base game's logic