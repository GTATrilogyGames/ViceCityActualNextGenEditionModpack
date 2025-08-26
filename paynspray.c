/**
 * simple script to allow the player to respray additional vehicles
 * by alextwothousand
 */

// idfk why we have to include all this crap but yeah...
// would rather clean up the code but whatever
#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>

void main(void) {
	WAIT(0);

	// contrary to popular belief, I actually wanted to do this as a dynamic array.
	// but ANSI C is just tragic

	SET_CAN_RESPRAY_CAR(MODEL_NOOSE, true); // FBI cheetah

	// done kek
}