#pragma once

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>


#define PASS_SEAT_FRONT		0
#define PASS_SEAT_RL		1
#define PASS_SEAT_RR		2


int closest_pass_seat(Ped passenger_outside, Car car)
{
	float frontright_x, frontright_y, frontright_z;
	float rearleft_x, rearleft_y, rearleft_z;
	float rearright_x, rearright_y, rearright_z;
	GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(car, 1.0, 2.0, 0.0, &frontright_x, &frontright_y, &frontright_z);
	GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(car, -1.0, -2.0, 0.0, &rearleft_x, &rearleft_y, &rearleft_z);
	GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(car, 1.0, -2.0, 0.0, &rearright_x, &rearright_y, &rearright_z);

	float pass_x, pass_y, pass_z;
	GET_CHAR_COORDINATES(passenger_outside, &pass_x, &pass_y, &pass_z);
	float dist0, dist1, dist2;
	GET_DISTANCE_BETWEEN_COORDS_3D(pass_x, pass_y, pass_z, frontright_x, frontright_y, frontright_z, &dist0);
	GET_DISTANCE_BETWEEN_COORDS_3D(pass_x, pass_y, pass_z, rearleft_x, rearleft_y, rearleft_z, &dist1);
	GET_DISTANCE_BETWEEN_COORDS_3D(pass_x, pass_y, pass_z, rearright_x, rearright_y, rearright_z, &dist2);
	float distances[3];
	distances[0] = dist0;
	distances[1] = dist1;
	distances[2] = dist2;
	float least_dist = dist0;
	int least_dist_index = 0;
	int i = 1;
	for (; i < 3; i++)
	{
		if (distances[i] < least_dist)
		{
			least_dist = distances[i];
			least_dist_index = i;
		}
	}
	if (least_dist_index == 0)
	{
		return PASS_SEAT_FRONT;
	}
	else if (least_dist_index == 1)
	{
		return PASS_SEAT_RL;
	}
	else
	{
		return PASS_SEAT_RR;
	}
}


	/* ОБЯЗАТЕЛЬНО должно быть хотя бы 1 свободное место */
int closest_free_seat(Ped passenger_outside, Car car)
{
	float frontright_x, frontright_y, frontright_z;
	float rearleft_x, rearleft_y, rearleft_z;
	float rearright_x, rearright_y, rearright_z;
	GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(car, 1.0, 2.0, 0.0, &frontright_x, &frontright_y, &frontright_z);
	GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(car, -1.0, -2.0, 0.0, &rearleft_x, &rearleft_y, &rearleft_z);
	GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(car, 1.0, -2.0, 0.0, &rearright_x, &rearright_y, &rearright_z);

	float pass_x, pass_y, pass_z;
	GET_CHAR_COORDINATES(passenger_outside, &pass_x, &pass_y, &pass_z);
	float distances[3];
	int seat_indexes[3];
	int arr_length = 0;
	float dist;
	if (IS_CAR_PASSENGER_SEAT_FREE(car, PASS_SEAT_FRONT))
	{
		GET_DISTANCE_BETWEEN_COORDS_3D(pass_x, pass_y, pass_z, frontright_x, frontright_y, frontright_z, &dist);
		distances[arr_length] = dist;
		seat_indexes[arr_length] = PASS_SEAT_FRONT;
		arr_length++;
	}
	if (IS_CAR_PASSENGER_SEAT_FREE(car, PASS_SEAT_RL))
	{
		GET_DISTANCE_BETWEEN_COORDS_3D(pass_x, pass_y, pass_z, rearleft_x, rearleft_y, rearleft_z, &dist);
		distances[arr_length] = dist;
		seat_indexes[arr_length] = PASS_SEAT_RL;
		arr_length++;
	}
	if (IS_CAR_PASSENGER_SEAT_FREE(car, PASS_SEAT_RR))
	{
		GET_DISTANCE_BETWEEN_COORDS_3D(pass_x, pass_y, pass_z, rearright_x, rearright_y, rearright_z, &dist);
		distances[arr_length] = dist;
		seat_indexes[arr_length] = PASS_SEAT_RR;
		arr_length++;
	}
	float least_dist = distances[0];
	int least_dist_index = 0;
	int i = 1;
	for (; i < arr_length; i++)
	{
		if (distances[i] < least_dist)
		{
			least_dist = distances[i];
			least_dist_index = i;
		}
	}
	return seat_indexes[least_dist_index];
}
