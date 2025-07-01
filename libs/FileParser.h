#pragma once

#include "CONVERSIONS.h"
#include "Body.h"

// Config parsing


// Body parsing

Body parse_line(string* line, SysConf* conf);
Body* parseBodiesFile(string* filename, SysConf* conf);

// ------------------------------------------------------------------
