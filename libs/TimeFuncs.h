#pragma once

#include "Common.h"

#define UTC_TAI_LEAP_SECONDS	37		// 37 leap seconds have to be applied
#define TAI_TT_DELTA			32.184L	// Difference between TAI and TT

typedef struct tm TimeStruct;

long double CurrentEpoch(long double relativeToJJ);
time_t JulianDayToTimestamp(long double JJ);