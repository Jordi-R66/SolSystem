#pragma once

#include "CONVERSIONS.h"
#include "Body.h"

// Config parsing
SysConf parseConfFile(string* filename);

// Body parsing

Body parse_line(string* line, SysConf* conf);
Body* parseBodiesFile(string* filename, SysConf* conf);

// ------------------------------------------------------------------
