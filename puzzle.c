/***********************************************************************
	This file is a part of scocl project by Alexander Blade (c) 2011 
***********************************************************************/

/* required for internal game checks, not used in scripts */

#include <natives.h>
#include <common.h>
#include <strings.h>
#include <types.h>
#include <consts.h>

void main(void)
{
	PRINT_STRING_WITH_LITERAL_STRING_NOW("string", "DUMMY PUZZLE SCRIPT", 5000, 1);
	TERMINATE_THIS_SCRIPT();
}
