#include "TimeFuncs.h"

long double CurrentEpoch(long double relativeToJJ) {
	time_t current_time = time(NULL);

	struct tm* utc = gmtime(&current_time);

	uint32_t Y = utc->tm_year + 1900;
	uint32_t M = utc->tm_mon + 1;
	uint32_t D = utc->tm_mday;
	uint32_t h = utc->tm_hour;
	uint32_t m = utc->tm_min;
	uint32_t s = utc->tm_sec;

	// printf("YEAR : %u\nMONTH : %u\n", Y, M);

	long double Epoch = JulianDay(Y, M, D, h, m, s);

	if (relativeToJJ != 0) {
		Epoch -= relativeToJJ;
	}

	return Epoch;
}

long double JulianDay(uint32_t Y, uint32_t M, uint32_t D, uint32_t h, uint32_t m, uint32_t s) {
	long double Q = (long double)D + ((long double)((h - 12) * 3600 + m * 60 + s)) / 86400.0l;

	long double JJ;

	if (M <= 2) {
		Y--;
		M += 12;
	}

	int S = Y / 100;
	int B = 2 - S + S / 4;

	JJ = (365.25l * Y) + (30.6001l * (long double)(M + 1)) + Q + (long double)B + 1720994.5l + .5l;

	return JJ;
}