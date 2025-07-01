#include "libs/FileParser.h"
#include "libs/Body.h"

#include "libs/Common.h"

#define DEFAULT_ITER 100000

time_t current_time;

int32_t main(int argc, char* argv[]) {
	char line[] = "1,Mercury,0,0.33010,0.38709893,0.20563069,7.00487,48.33167,77.45645,252.25084";

	SysConf conf;
	Body Mercure;

	strcpy(conf.SysName, "Sol");
	conf.MassScale = 1e25f;
	conf.DistScale = 149597870700.f;
	conf.Epoch_TT = 2451545.0f;
	conf.HeaderLine = true;

	Mercure = parse_line(line, &conf);
	printf("%s\n", line);

	return 0;
}