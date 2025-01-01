#pragma once

#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>

#undef M_PI
#define M_PI 3.141592653589793
#define DEGS2RADS M_PI/180.0
#define RADS2DEGS 180.0/M_PI

#define NAME_LENGTH 26

#define BODY_ID_LENGTH 5
#define ID_BITS 8

#define BODY_MASS_LENGTH 16

#define SMA_LENGTH 31
#define ECC_LENGTH 16
#define INCLINATION_LENGTH 11
#define LNG_LENGTH 11

#define FIELDS 10

#define LINE_LENGTH (NAME_LENGTH + 2 * BODY_ID_LENGTH + BODY_MASS_LENGTH + SMA_LENGTH + ECC_LENGTH + INCLINATION_LENGTH + 3 * LNG_LENGTH + 1)

typedef char string;
typedef int8_t id_t;

typedef struct SysConf {
	string SysName[NAME_LENGTH];
	float MassScale;
	float DistScale;
	float Epoch_TT;
	bool HeaderLine;
} SysConf;

typedef struct Body {
	SysConf* sysConf;
	id_t BodyId;
	id_t ParentId;

	string BodyName[NAME_LENGTH];

	bool hasParent;

	float BodyMass;

	float SemiMajorAxis;
	float Eccentricity;
	float Inclination;
	float AscNodeLong;
	float PeriLong;
	float MeanLong;

	float PeriArg;
	float MeanAnomaly;
	float MeanMotion;

	float x, y, z;
	float v_x, v_y, v_z, v;

} Body;