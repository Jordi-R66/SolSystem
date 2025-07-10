#include "TimeFuncs.h"

long double ENT(long double x) {
	return floorl(x);
}

time_t JulianDayToTimestamp(long double JJ) {
	int Z, alpha, S, B, C, D, E, Q;

	long double F;

	Z = (int)ENT(JJ);
	F = JJ - truncl(JJ) + .5l;

	alpha = ENT(((long double)Z - 1867216.25l) / 36524.25l);
	S = Z + 1 + alpha - (int)ENT(alpha / 4.0L);

	B = S + 1524;
	C = (int)ENT((long double)(B - 122.1l) / 365.25l);
	D = (int)ENT(365.25l * (long double)C);

	E = (int)ENT((long double)(B - D) / 30.6001l);

	Q = B - D - (int)ENT(30.6001l * E);

	int M, A;

	M = (E >= 14) ? E - 13 : E - 1;
	A = (M > 2) ? C - 4716 : C - 4715;

	int s, m, h;

	F *= 86400.l;
	F = ENT(F);

	h = (int)(F / 3600.0l);
	F = ENT(F - 3600.0l * h);

	m = (int)(F / 60.0l);
	s = (int)ENT(F - 60.0l * m);

	TimeStruct date = {s, m, h, Q, M - 1, A - 1900, 0, 0, 0};
	time_t output = mktime(&date) - (int)TAI_TT_DELTA - UTC_TAI_LEAP_SECONDS;

	return output;
}