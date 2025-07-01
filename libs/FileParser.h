#pragma once

#include "CONVERSIONS.h"
#include "Body.h"

// Config parsing
SysConf parseConfFile(string* filename);

// Body parsing

#define DEFAULT_BODY_NUMBER 16

typedef struct BodyFile {
	size_t numberOfBodies;
	Body* bodies;
} BodyFile;

Body parse_line(string* line, SysConf* conf);
BodyFile parseBodiesFile(string* filename, SysConf* conf);

// ------------------------------------------------------------------
