#pragma once

#include "Common.h"

//#define EARTH_DAY_LENGTH 86400.0//86164.096

#define G 6.67428E-11

double OrbitalPeriod(double MeanMotion);

uint64_t SemiMajorAxis(double Period);

uint64_t Apoapsis(double Eccentricity, uint64_t SemiMajorAxis);
uint64_t Periapsis(double Eccentricity, uint64_t SemiMajorAxis);
uint64_t OrbAlt(double Eccentricity, uint64_t SemiMajorAxis, double EccentricAnomaly);
uint64_t OrbAltTA(double Eccentricity, uint64_t SemiMajorAxis, double TrueAnomaly);

double KeplerEquation(double E, double e);
double KeplerPrime(double E, double e);

double AngularSpeed(double SemiMajorAxis);
double TrueAnomaly(double Eccentricity, double EccentricAnomaly);
double MeanLongitude(double MeanAno, double LNA, double ArgPeri);

double OrbSpeed(uint64_t altitude, uint64_t SemiMajorAxis);
double Lorentz(double speed);