#include "OrbMaths.h"

// ------------------------------------------------------------------



long double OrbitalPeriod(Body* body) {
	long double Period;

	long double parentMu = body->hasParent ? ((Body*)((Body*)body->ParentPTR))->stdGravParam : 0.0l;

	Period = 2.0l * M_PIl * sqrtl(powl(body->SemiMajorAxis, 3.0l) / (body->stdGravParam + parentMu));

	return Period;
}

long double Apoapsis(Body* body) {
	long double Apoapsis = 0;

	Apoapsis = body->SemiMajorAxis * (1.0 + body->Eccentricity);

	return Apoapsis;
}

long double Periapsis(Body* body) {
	long double Periapsis = 0;

	Periapsis = body->SemiMajorAxis * (1.0l - body->Eccentricity);

	return Periapsis;
}

long double OrbAlt(Body* body, long double EccentricAnomaly) {
	return body->SemiMajorAxis * (1.0l - body->Eccentricity * cos(EccentricAnomaly));
}

long double OrbAltTA(Body* body, long double TrueAnomaly) {
	return body->SemiMajorAxis * (1.0l - powl(body->Eccentricity, 2.0l)) / (1.0l + body->Eccentricity * cosl(TrueAnomaly));
}



long double KeplerEquation(long double EccentricAnomaly, long double Eccentricity) {
	return EccentricAnomaly - Eccentricity * sinl(EccentricAnomaly);
}

long double KeplerPrime(long double EccentricAnomaly, long double Eccentricity) {
	return 1.0l - Eccentricity * cosl(EccentricAnomaly);
}

long double AngularSpeed(Body* body) {
	long double parentMu = body->hasParent ? ((Body*)body->ParentPTR)->stdGravParam : 0.0l;

	return sqrtl((body->stdGravParam + parentMu)/powl(body->SemiMajorAxis, 3.0l));
}

long double TrueAnomaly(long double Eccentricity, long double EccentricAnomaly) {
	// return 2.0 * atan(sqrt((1.0 + Eccentricity) / (1.0 - Eccentricity)) * tan(EccentricAnomaly/2.0));
	long double beta_ = Eccentricity / (1.0l + sqrtl(1.0l - Eccentricity*Eccentricity));
	long double nu_ = EccentricAnomaly + 2.0l * atanl((beta_*sinl(EccentricAnomaly)) / (1.0l - beta_ * cosl(EccentricAnomaly)));

	return nu_;
}
long double MeanLongitude(long double MeanAno, long double LNA, long double ArgPeri) {
	// MeanLNG = MeanAno + PeriLNG = MeanAno + LNA + ArgPeri

	// As described here https://fr.wikipedia.org/wiki/Longitude_moyenne

	return MeanAno + LNA + ArgPeri;
}


long double OrbSpeed(Body* body, long double altitude) {
	long double speed;

	long double parentMu = body->hasParent ? ((Body*)body->ParentPTR)->stdGravParam : 0.0l;

	speed = sqrtl((body->stdGravParam + parentMu) * (2.0l / (altitude) - 1.0l/body->SemiMajorAxis));

	return speed;
}

long double Lorentz(long double v) {
	const long double c_sqr = powl(299792458.0l, 2.0l);

	return 1.0l / sqrtl(1.0l - powl(v, 2.0l)/c_sqr);
}
