#pragma once

#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <sys/types.h>

#define M_PIl 3.141592653589793238462643383279502884L

#define DEGS2RADS M_PIl/180.0l
#define RADS2DEGS 180.0l/M_PIl

#define NAME_LENGTH 26

typedef char string;
typedef int8_t bodyId_t;

#pragma pack(1)

typedef struct SysConf_Struct {
	string SysName[NAME_LENGTH];
	long double MassScale;
	long double DistScale;
	long double Epoch_TT;
	bool HeaderLine;
} SysConf;

#pragma pack()