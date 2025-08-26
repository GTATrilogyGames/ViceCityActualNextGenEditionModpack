#pragma once

#include <natives.h>
#include <common.h>
#include <types.h>
#include <consts.h>
#include "globals.h"
#include "car_seats.h"

#define SHORTCUT_TAXI_COST (9)

enum
{
	SHORTCUT_NONE,
	SHORTCUT_INIT,
	SHORTCUT_IDLE,
	SHORTCUT_GETTING_IN,
	SHORTCUT_TRANSITION,
	SHORTCUT_ARRIVING,
	SHORTCUT_GETTING_OUT
};

void RemoveShortCutDropOffPointForMission(void)
{
	G_SHORT_CUT_DROP_OFF_FOR_MISSION_X = 0.0;
	G_SHORT_CUT_DROP_OFF_FOR_MISSION_Y = 0.0;
	G_SHORT_CUT_DROP_OFF_FOR_MISSION_Z = 0.0;
	G_SHORT_CUT_DROP_OFF_FOR_MISSION_ANGLE = 0.0;
}

void AddShortCutDropOffPointForMission(float x, float y, float z, float angle)
{
	G_SHORT_CUT_DROP_OFF_FOR_MISSION_X = x + (433.0004434);
	G_SHORT_CUT_DROP_OFF_FOR_MISSION_Y = y + (532.9998721);
	G_SHORT_CUT_DROP_OFF_FOR_MISSION_Z = z + (-5.00017432);
	G_SHORT_CUT_DROP_OFF_FOR_MISSION_ANGLE = angle;
}

void AddShortCutPointAfterDeath(float x, float y, float z, float angle)
{
	if (G_NUM_AFTER_DEATH_START_POINTS >= NUM_SHORTCUT_START_POINTS)
		return;
	G_AFTER_DEATH_START_POINTS_X[G_NUM_AFTER_DEATH_START_POINTS] = x + (433.0004434);
	G_AFTER_DEATH_START_POINTS_Y[G_NUM_AFTER_DEATH_START_POINTS] = y + (532.9998721);
	G_AFTER_DEATH_START_POINTS_Z[G_NUM_AFTER_DEATH_START_POINTS] = z + (-5.00017432);
	G_AFTER_DEATH_START_POINTS_ANGLE[G_NUM_AFTER_DEATH_START_POINTS] = angle;
	G_NUM_AFTER_DEATH_START_POINTS++;
}

void ClearShortCut(void)
{
	if (DOES_CHAR_EXIST(G_SHORT_CUT_DRIVER))
	{
		MARK_CHAR_AS_NO_LONGER_NEEDED(&G_SHORT_CUT_DRIVER);
	}
	if (DOES_BLIP_EXIST(G_SHORT_CUT_BLIP))
	{
		REMOVE_BLIP(G_SHORT_CUT_BLIP);
	}
	if (DOES_VEHICLE_EXIST(G_SHORT_CUT_VEHICLE))
	{
		MARK_CAR_AS_NO_LONGER_NEEDED(&G_SHORT_CUT_VEHICLE);
	}
	SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
	G_SHORT_CUT_STATE = SHORTCUT_NONE;
}

void SetUpShortCut(float vStartPosx, float vStartPosy, float vStartPosz, float fStartAngle, float vEndPosx, float vEndPosy, float vEndPosz, float fEndAngle)
{
	ClearShortCut();
	G_SHORT_CUT_STATE = SHORTCUT_INIT;
	G_SHORT_CUT_START_X = vStartPosx;
	G_SHORT_CUT_START_Y = vStartPosy;
	G_SHORT_CUT_START_Z = vStartPosz;
	G_SHORT_CUT_START_ANGLE = fStartAngle;
	G_SHORT_CUT_DESTINATION_X = vEndPosx;
	G_SHORT_CUT_DESTINATION_Y = vEndPosy;
	G_SHORT_CUT_DESTINATION_Z = vEndPosz;
	G_SHORT_CUT_DESTINATION_ANGLE = fEndAngle;
}

void AfterDeathArrestSetUpShortCutTaxi(void)
{
	if (G_SHORT_CUT_DROP_OFF_FOR_MISSION_X == 0.0 && G_SHORT_CUT_DROP_OFF_FOR_MISSION_Y == 0.0 && G_SHORT_CUT_DROP_OFF_FOR_MISSION_Z == 0.0 && G_SHORT_CUT_DROP_OFF_FOR_MISSION_ANGLE == 0.0)
		return;
	uint nClosestPoint = -1;
	float fDistanceToPoint = 999999.9;
	Vector3 player;
	GET_CHAR_COORDINATES(GetPlayerPed(), &player.x, &player.y, &player.z);
	float dist;
	int i;
	for (i = 0; i < NUM_SHORTCUT_START_POINTS; i++)
	{
		GET_DISTANCE_BETWEEN_COORDS_3D(player.x, player.y, player.z, G_AFTER_DEATH_START_POINTS_X[i], G_AFTER_DEATH_START_POINTS_Y[i], G_AFTER_DEATH_START_POINTS_Z[i], &dist);
		if (dist < fDistanceToPoint) {
			fDistanceToPoint = dist;
			nClosestPoint = i;
		}
	}
	if (fDistanceToPoint < 100.0)
		SetUpShortCut(G_AFTER_DEATH_START_POINTS_X[nClosestPoint], G_AFTER_DEATH_START_POINTS_Y[nClosestPoint], G_AFTER_DEATH_START_POINTS_Z[nClosestPoint], G_AFTER_DEATH_START_POINTS_ANGLE[nClosestPoint], G_SHORT_CUT_DROP_OFF_FOR_MISSION_X, G_SHORT_CUT_DROP_OFF_FOR_MISSION_Y, G_SHORT_CUT_DROP_OFF_FOR_MISSION_Z, G_SHORT_CUT_DROP_OFF_FOR_MISSION_ANGLE);
	RemoveShortCutDropOffPointForMission();
}

void AbandonShortCutIfPlayerMilesAway(void)
{
	if (!DOES_VEHICLE_EXIST(G_SHORT_CUT_VEHICLE))
	{
		return;
	}
	Vector3 player;
	GET_CHAR_COORDINATES(GetPlayerPed(), &player.x, &player.y, &player.z);
	Vector3 taxi;
	GET_CAR_COORDINATES(G_SHORT_CUT_VEHICLE, &taxi.x, &taxi.y, &taxi.z);
	float distance;
	GET_DISTANCE_BETWEEN_COORDS_3D(player.x, player.y, player.z, taxi.x, taxi.y, taxi.z, &distance);
	if (distance > 120.0)
	{
		ClearShortCut();
	}
}

void AbandonShortCutIfTaxiHasBeenMessedWith(void)
{
	if (!DOES_VEHICLE_EXIST(G_SHORT_CUT_VEHICLE))
	{
		return;
	}
	if (!DOES_CHAR_EXIST(G_SHORT_CUT_DRIVER) ||
		IS_CHAR_DEAD(G_SHORT_CUT_DRIVER) ||
		!IS_CHAR_SITTING_IN_CAR(G_SHORT_CUT_DRIVER, G_SHORT_CUT_VEHICLE) ||
		IS_CAR_DEAD(G_SHORT_CUT_VEHICLE))
	{
		ClearShortCut();
	}
}

void UpdateShortCut(void)
{
	if (G_SHORT_CUT_STATE == SHORTCUT_INIT)
	{
		uint taxi_car_model = MODEL_CABBY;
		REQUEST_MODEL(taxi_car_model);
		while (!HAS_MODEL_LOADED(taxi_car_model))
		{
			WAIT(0);
		}
		uint taxi_driver_model = MODEL_M_M_TAXIDRIVER;
		REQUEST_MODEL(taxi_driver_model);
		while (!HAS_MODEL_LOADED(taxi_driver_model))
		{
			WAIT(0);
		}
		CREATE_CAR(taxi_car_model, G_SHORT_CUT_START_X, G_SHORT_CUT_START_Y, G_SHORT_CUT_START_Z, &G_SHORT_CUT_VEHICLE, true);
		MARK_MODEL_AS_NO_LONGER_NEEDED(taxi_car_model);
		SET_CAR_HEADING(G_SHORT_CUT_VEHICLE, G_SHORT_CUT_START_ANGLE);
		SET_TAXI_LIGHTS(G_SHORT_CUT_VEHICLE, true);
		CREATE_CHAR_INSIDE_CAR(G_SHORT_CUT_VEHICLE, 1, taxi_driver_model, &G_SHORT_CUT_DRIVER);
		MARK_MODEL_AS_NO_LONGER_NEEDED(taxi_driver_model);
		ADD_BLIP_FOR_CAR(G_SHORT_CUT_VEHICLE, &G_SHORT_CUT_BLIP);
		SET_BLIP_AS_FRIENDLY(G_SHORT_CUT_BLIP, 1);
		CHANGE_BLIP_COLOUR(G_SHORT_CUT_BLIP, 5);
		G_SHORT_CUT_STATE = SHORTCUT_IDLE;
		return;
	}
	if (G_SHORT_CUT_STATE == SHORTCUT_IDLE)
	{
		if(IS_CHAR_GETTING_IN_TO_A_CAR(GetPlayerPed()))
		{
			Vehicle vehicle;
			GET_VEHICLE_PLAYER_WOULD_ENTER(GetPlayerIndex(), &vehicle);
			if (vehicle == G_SHORT_CUT_VEHICLE)
			{
				SET_PLAYER_CONTROL(GetPlayerIndex(), 0);
				CLEAR_CHAR_TASKS_IMMEDIATELY(GetPlayerPed());
				TASK_ENTER_CAR_AS_PASSENGER(GetPlayerPed(), G_SHORT_CUT_VEHICLE, -1, closest_pass_seat(GetPlayerPed(), G_SHORT_CUT_VEHICLE));
				G_SHORT_CUT_STATE = SHORTCUT_GETTING_IN;
			}
		}
		AbandonShortCutIfTaxiHasBeenMessedWith();
		AbandonShortCutIfPlayerMilesAway();
		return;
	}
	if (G_SHORT_CUT_STATE == SHORTCUT_GETTING_IN)
	{
		if (IS_CHAR_SITTING_IN_CAR(GetPlayerPed(), G_SHORT_CUT_VEHICLE))
		{
			REMOVE_BLIP(G_SHORT_CUT_BLIP);
			SET_CHAR_CANT_BE_DRAGGED_OUT(GetPlayerPed(), true);
			SET_TAXI_LIGHTS(G_SHORT_CUT_VEHICLE, false);
			TASK_CAR_TEMP_ACTION(G_SHORT_CUT_DRIVER, G_SHORT_CUT_VEHICLE, 9, 2500);
			DO_SCREEN_FADE_OUT(2500);
			G_SHORT_CUT_STATE = SHORTCUT_TRANSITION;
			GET_GAME_TIMER(&G_SHORT_CUT_TIMER);
			G_SHORT_CUT_TIMER += 3000;
			PRINT_BIG("TAXI", 4500, 2);
		}
		AbandonShortCutIfTaxiHasBeenMessedWith();
		return;
	}
	if (G_SHORT_CUT_STATE == SHORTCUT_TRANSITION)
	{
		uint timer;
		GET_GAME_TIMER(&timer);
		if (timer > G_SHORT_CUT_TIMER)
		{
			LOAD_SCENE(G_SHORT_CUT_DESTINATION_X, G_SHORT_CUT_DESTINATION_Y, G_SHORT_CUT_DESTINATION_Z);
			SET_CAR_COORDINATES(G_SHORT_CUT_VEHICLE, G_SHORT_CUT_DESTINATION_X, G_SHORT_CUT_DESTINATION_Y, G_SHORT_CUT_DESTINATION_Z);
			SET_CAR_HEADING(G_SHORT_CUT_VEHICLE, G_SHORT_CUT_DESTINATION_ANGLE);
			GET_GAME_TIMER(&G_SHORT_CUT_TIMER);
			G_SHORT_CUT_TIMER += 1500;
			DO_SCREEN_FADE_IN(1000);
			G_SHORT_CUT_STATE = SHORTCUT_ARRIVING;
		}
		return;
	}
	if (G_SHORT_CUT_STATE == SHORTCUT_ARRIVING)
	{
		uint timer;
		GET_GAME_TIMER(&timer);
		if (timer > G_SHORT_CUT_TIMER)
		{
			int cost;
			cost = IS_SCORE_GREATER(GetPlayerIndex(), SHORTCUT_TAXI_COST - 1) ? SHORTCUT_TAXI_COST : 0;
			ADD_SCORE(GetPlayerIndex(), -cost);
			INCREMENT_FLOAT_STAT(STAT_SPENT_ON_TAXIS, cost);
			SET_CHAR_MONEY(G_SHORT_CUT_DRIVER, GET_CHAR_MONEY(G_SHORT_CUT_DRIVER) + cost);
			TASK_LEAVE_CAR(GetPlayerPed(), G_SHORT_CUT_VEHICLE);
			G_SHORT_CUT_STATE = SHORTCUT_GETTING_OUT;
		}
		AbandonShortCutIfTaxiHasBeenMessedWith();
		return;
	}
	if (G_SHORT_CUT_STATE == SHORTCUT_GETTING_OUT)
	{
		if (!IS_CHAR_IN_CAR(GetPlayerPed(), G_SHORT_CUT_VEHICLE))
		{
			SET_CHAR_CANT_BE_DRAGGED_OUT(GetPlayerPed(), false);
			SET_PLAYER_CONTROL(GetPlayerIndex(), 1);
			SET_TAXI_LIGHTS(G_SHORT_CUT_VEHICLE, true);
			MARK_CAR_AS_NO_LONGER_NEEDED(&G_SHORT_CUT_VEHICLE);
			MARK_CHAR_AS_NO_LONGER_NEEDED(&G_SHORT_CUT_DRIVER);
			G_SHORT_CUT_STATE = SHORTCUT_NONE;
		}
		AbandonShortCutIfTaxiHasBeenMessedWith();
		return;
	}
}