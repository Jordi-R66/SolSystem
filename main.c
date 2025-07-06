#include "libs/FileParser.h"
#include "libs/Body.h"

#include "libs/Common.h"

#define DEFAULT_ITER 100000

time_t current_time;

void program(SysConf conf, BodyFile bodyFile);

int main(int argc, char* argv[]) {
	SysConf conf;
	BodyFile bodyFile;

	conf.MassScale = 1e25L;
	conf.DistScale = 149597870700.0L;
	conf.Epoch_TT = 2451545.0L;
	conf.HeaderLine = true;

	printf("%d arguments detected\n", argc);

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

			printf("Conf file : %s\nBodies file : %s\n", argv[1], argv[2]);

			conf = parseConfFile(argv[1]);
			bodyFile = parseBodiesFile(argv[2], &conf);

			printf("Everything has been loaded into memory!!\n");

			program(conf, bodyFile);

		default:
			fprintf(stderr, "Please specify a .bodies file followed by a .conf file. OR specify 'g' to generate default .conf and a template for your .bodies\n");
			exit(EXIT_FAILURE);
			break;

		}
}

void program(SysConf conf, BodyFile bodyFile) {

	printf("Main part of the program is running!\n");

	for (size_t i = 0; i < bodyFile.numberOfBodies; i++) {
		print_body(&bodyFile.bodies[i]);
		printf("\n\n");
	}

	free(bodyFile.bodies);

	exit(EXIT_SUCCESS);
}