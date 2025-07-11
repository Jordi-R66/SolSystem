#pragma once

#include "Common.h"
#include "Body.h"

//#define EARTH_DAY_LENGTH 86400.0//86164.096

long double OrbitalPeriod(Body* body);

long double Apoapsis(Body* body);
long double Periapsis(Body* body);
long double OrbAlt(Body* body, long double EccentricAnomaly);
long double OrbAltTA(Body* body, long double TrueAnomaly);

long double KeplerEquation(long double EccentricAnomaly, long double Eccentricity);
long double KeplerPrime(long double EccentricAnomaly, long double Eccentricity);

long double AngularSpeed(Body* body);
long double TrueAnomaly(long double Eccentricity, long double EccentricAnomaly);
long double MeanLongitude(long double MeanAno, long double LNA, long double ArgPeri);

long double OrbSpeed(Body* body, long double altitude);
long double Lorentz(long double v);

long double SphereOfInfluence(Body* body, long double dist);