#include "Common.h"

#pragma pack(1)
typedef struct Body {
	SysConf* sysConf;
	id_t BodyId;
	id_t ParentId;
	Body* ParentPTR;

	string BodyName[NAME_LENGTH];

	bool hasParent;

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
	long double v_x, v_y, v_z, v;

} Body;
#pragma pack()

#define BODY_SIZE sizeof(Body)