#include "libs/FileParser.h"
#include "libs/Body.h"

#include "libs/Common.h"

#define DEFAULT_ITER 100000

time_t current_time;

int main(int argc, char* argv[]) {
	SysConf conf;

	conf.MassScale = 1e25L;
	conf.DistScale = 149597870700.0L;
	conf.Epoch_TT = 2451545.0L;
	conf.HeaderLine = true;

	switch (argc) {
		case 2:
			switch (argv[1][0]) {
				case 'g':
					FILE* fp = fopen("Sol.conf", "w");

					fwrite((void*)&conf, sizeof(SysConf), 1, fp);
					fclose(fp);

					fp = fopen("empty.bodies", "w");
					fprintf(fp, "BodyId,BodyName,BodyParent,Mass,SMA,Ecc,Incl,LNA,PeLNG,MeanLNG\n");
					fclose(fp);

					fprintf(stdout, "Generated all required files.\n");
					exit(EXIT_SUCCESS);
					break;

				default:
					fprintf(stderr, "Unknown parameter %s\n", argv[1]);
					exit(EXIT_FAILURE);
					break;
			}

		case 3:
			

		default:
			fprintf(stderr, "Please specify a .bodies file followed by a .conf file. OR specify 'g' to generate default .conf and a template for your .bodies\n");
			exit(EXIT_FAILURE);
			break;

		}
}

void program(SysConf conf, Body* bodies) {

	char line[] = "1,Mercury,0,0.33010,0.38709893,0.20563069,7.00487,48.33167,77.45645,252.25084";

	Body Mercure;

	strcpy(conf.SysName, "Sol");

	Mercure = parse_line(line, &conf);
	print_body(&Mercure);

	return;
}