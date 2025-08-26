#include <natives.h>
#include <common.h>
#include <types.h>
#include <consts.h>

void main(void)
{
	while (!REQUEST_AMBIENT_AUDIO_BANK("GPS/MISSION_COMPLETE_1"))
	{
		WAIT(0);
	}

	Vehicle player_vehicle = INVALID_HANDLE;

	if (IS_CHAR_SITTING_IN_ANY_CAR(GetPlayerPed()))
	{
		STORE_CAR_CHAR_IS_IN_NO_SAVE(GetPlayerPed(), &player_vehicle);
	}

	if (DOES_VEHICLE_EXIST(player_vehicle))
	{
		SET_LOUD_VEHICLE_RADIO(player_vehicle, false);
	}

	DISABLE_FRONTEND_RADIO();

	uint sound_id = GET_SOUND_ID();
	PLAY_SOUND_FRONTEND(sound_id, "MISSION_COMPLETE_01");

	while (!HAS_SOUND_FINISHED(sound_id))
	{
		WAIT(0);
	}

	if (DOES_VEHICLE_EXIST(player_vehicle))
	{
		SET_LOUD_VEHICLE_RADIO(player_vehicle, true);
	}

	ENABLE_FRONTEND_RADIO();

	RELEASE_SOUND_ID(sound_id);
	AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED();

	TERMINATE_THIS_SCRIPT();
}
