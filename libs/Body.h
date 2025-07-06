#pragma once

#include "Common.h"

#pragma pack(1)

#define BODY_ID_LENGTH 5
#define ID_BITS 8

#define BODY_MASS_LENGTH 16

#define SMA_LENGTH 31
#define ECC_LENGTH 16
#define INCLINATION_LENGTH 11
#define LNG_LENGTH 11

#define FIELDS 10

#define LINE_LENGTH (NAME_LENGTH + 2 * BODY_ID_LENGTH + BODY_MASS_LENGTH + SMA_LENGTH + ECC_LENGTH + INCLINATION_LENGTH + 3 * LNG_LENGTH + 1)

typedef struct SimplifiedBody {
	bodyId_t bodyId;
	string BodyName[NAME_LENGTH];

	bool hasParent;
	bodyId_t parentId;

	long double Mass;
	long double SMA;
	long double Eccentricity;
	long double Inclination;
	long double AscNode;
	long double PeLNG;
	long double MeanLNG;
} SimplifiedBody;

#define SIMPLIFIED_BODY_SIZE sizeof(SimplifiedBody)

typedef struct BodyStruct {
	SysConf* sysConf;
	bodyId_t BodyId;

	bool hasParent;
	bodyId_t ParentId;
	void* ParentPTR;

	string BodyName[NAME_LENGTH];

	long double BodyMass;
	long double stdGravParam;

	long double SemiMajorAxis;
	long double Eccentricity;
	long double Inclination;
	long double AscNodeLong;
	long double PeriLong;
	long double MeanLong;

	long double PeriArg;
	long double MeanAnomaly;
	long double MeanMotion;

	long double x, y, z;
	long double v_x, v_y, v_z;

} Body;
#pragma pack()

#define BODY_SIZE sizeof(Body)

void print_body(Body* body);