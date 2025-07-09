#include "libs/FileParser.h"
#include "libs/Files.h"
#include "libs/Body.h"

#include "libs/Common.h"

#define DEFAULT_ITER 100000

time_t current_time;

SysConf solConf = {
	.SysName = "Sol",
	.DistScale = 149597870700.0L,
	.Epoch_TT = 2451545.0L
};

SimplifiedBody solBodies[] = {
	{0, "Sol", false, 0, 1.9884e30, 0, 0, 0, 0, 0, 0},
	{1, "Mercury", true, 0, 0.33010e24, 0.38709893, 0.20563069, 7.00487, 48.33167, 77.45645, 252.25084},
	{2, "Venus", true, 0, 4.8693e24, 0.72333199, 0.00677323, 3.39471, 76.68069, 131.53298, 181.97973},
	{3, "Earth", true, 0, 5.9722e24, 1.00000011, 0.01671022, 0.000005, -11.26064, 102.94719, 100.46435},
	{4, "Mars", true, 0, 0.64169e24, 1.52366231, 0.09341233, 1.85061, 49.57854, 336.04084, 355.45332},
	{5, "Jupiter", true, 0, 1898.13e24, 5.20336301, 0.04839266, 1.30530, 100.55615, 14.75385, 34.40438},
	{6, "Saturn", true, 0, 568.32e24, 9.53707032, 0.05415060, 2.48446, 113.71504, 92.43194, 49.94432},
	{7, "Uranus", true, 0, 86.811e24, 19.19126393, 0.04716771, 0.76986, 74.22988, 170.96424, 313.23218},
	{8, "Neptune", true, 0, 102.409e24, 30.06896348, 0.00858587, 1.76917, 131.72169, 44.97135, 304.88003},
	{9, "Pluto", true, 0, 0.01303e24, 39.48168677, 0.24880766, 17.14175, 110.30347, 224.06676, 238.92881},
};

void program(SysConf conf, BodyFile bodyFile);

int main(int argc, char* argv[]) {
	SysConf conf = solConf;
	BodyFile bodyFile;

	printf("%d arguments detected\n", argc);

	switch (argc) {
		case 1:
			bodyFile.numberOfBodies = 10;
			bodyFile.bodies = complexifyBodies(solBodies, 10, &conf);

			program(conf, bodyFile);
		case 2:
			switch (argv[1][0]) {
				case 'g':
					FILE* fp = fopen("Sol.conf", "w");

					fwrite((void*)&conf, sizeof(SysConf), 1, fp);
					fclose(fp);

					ExportSimplifiedBodies(solBodies, 10, &conf);

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