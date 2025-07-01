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

#pragma pack(1)

typedef struct SysConf {
	string SysName[NAME_LENGTH];
	long double MassScale;
	long double DistScale;
	long double Epoch_TT;
	bool HeaderLine;
} SysConf;

#pragma pack()