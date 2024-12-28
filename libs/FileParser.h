#pragma once

#include "CONVERSIONS.h"

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

/*
#define NORAD_ID_LENGTH 6
#define YR_LENGTH 3
#define LAUNCH_NB_LENGTH 4
#define LAUNCH_PART_LENGTH 4
#define EPOCH_LENGTH 13
#define DERIV_1_LENGTH 11
#define DERIV_2_LENGTH 9
#define BSTAR_LENGTH 9

#define INCLINATION_LENGTH 9
#define ASC_NODE_LENGTH 9
#define ECC_LENGTH 9
#define ARG_PE_LENGTH 9
#define MEAN_ANO_LENGTH 9
#define MEAN_MOTION_LENGTH 12

#define REVS_LENGTH 6

#define COSPAR_LENGTH (YR_LENGTH + LAUNCH_NB_LENGTH + LAUNCH_PART_LENGTH - 2)
*/

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

} Body;

void parse_line(string* line, Body* body);

// ------------------------------------------------------------------

/*
typedef struct TLE {
	string name[NAME_LENGTH];

	// First line

	uint32_t NORAD_ID;
	char Classification;

	uint8_t COSPAR_YR: 7; // Max value : 99
	uint16_t COSPAR_LN: 10;
	string COSPAR_ID[LAUNCH_PART_LENGTH];

	uint8_t EPOCH_YR: 7; // Max value : 99
	double EPOCH;

	double FIRST_DERIV_MEAN_MOTION;
	double SECOND_DERIV_MEAN_MOTION;

	double B_STAR;

	// Second line

	float Inclination;
	float AscNodeLong;
	float Eccentricity;
	float PeriArg;
	float MeanAnomaly;

	double MeanMotion;

	uint32_t Revolutions;
} TLE;

TLE parse_block(string lines[][70]);

TLE parse_lines(string NAME_LINE[25], string FIRST_LINE[70], string SECOND_LINE[70]);
*/
