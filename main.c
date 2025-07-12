#include "libs/FileParser.h"
#include "libs/TimeFuncs.h"
#include "libs/Files.h"
#include "libs/Body.h"

#include "libs/Common.h"

#define DEFAULT_ITER 100000

time_t current_time;

#pragma pack(1)
typedef struct ProgParams {
	SysConf conf;
	BodyFile bodyFile;
	bodyId_t bodyId;
} ProgParams;
#pragma pack()

ProgParams params;

SysConf solConf = {
	.SysName = "Sol",
	.DistScale = 149597870700.0L,
	.Epoch_TT = 2451545.0
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
	//{, "Ceres", true, 0, 9.46e20, 2.7666197l, 0.079184l, 10.5879l, 80.25414l, 153.53993l, 159.8853332l},
	//{, "Pluto", true, 0, 0.01303e24, 39.48168677, 0.24880766, 17.14175, 110.30347, 224.06676, 238.92881}
};

void program(void);

void prepareProgParams(bool loadFromMem, bodyId_t bodyId, char* confFilename, char* bodiesFilename) {
	ProgParams* output = &params;

	output->bodyId = bodyId;

	if (loadFromMem) {
		output->conf = solConf;
		output->bodyFile.numberOfBodies = sizeof(solBodies)/sizeof(SimplifiedBody);
		output->bodyFile.bodies = complexifyBodies(solBodies, output->bodyFile.numberOfBodies, &output->conf);
	} else {
		if (confFilename == (char*)NULL || bodiesFilename == (char*)NULL) {
			fprintf(stderr, "Make sure to provide both filenames\n");
			exit(EXIT_FAILURE);
		}

		output->conf = parseConfFile(confFilename);
		output->bodyFile = parseBodiesFile(bodiesFilename, &output->conf);

		bool inexistantId = true;

		for (bodyId_t i = 0; i < output->bodyFile.numberOfBodies; i++) {
			Body body = output->bodyFile.bodies[i];

			if (i == body.BodyId) {
				inexistantId = false;
			}
		}

		if (inexistantId) {
			memset(output->bodyFile.bodies, 0, output->bodyFile.numberOfBodies * BODY_SIZE);
			free(output->bodyFile.bodies);

			output->bodyFile.bodies = (Body*)NULL;
			output->bodyFile.numberOfBodies = 0;

			fprintf(stderr, "Unrecognised bodyId\n");
			exit(EXIT_FAILURE);
		}
	}
}

int main(int argc, char* argv[]) {
	memset(&params, 0, sizeof(ProgParams));

	char* endptr;

	bodyId_t lookingFor = -1;
	bool runProgram = false;

	printf("%d arguments detected\n", argc);

	switch (argc) {
		case 2:
			if (argv[1][0] == '-') {
				switch (argv[1][1]) {
					case 'g':
						FILE* fp = fopen("Sol.conf", "w");

						fwrite((void*)&solConf, sizeof(SysConf), 1, fp);
						fclose(fp);

						ExportSimplifiedBodies(solBodies, sizeof(solBodies)/sizeof(SimplifiedBody), &solConf);

						fprintf(stdout, "Generated all required files.\n");
						exit(EXIT_SUCCESS);
						break;

					default:
						fprintf(stderr, "Unknown parameter %s\n", argv[1]);
						exit(EXIT_FAILURE);
						break;
				}
			} else {
				lookingFor = (bodyId_t)strtoul(argv[1], &endptr, 10);

				prepareProgParams(true, lookingFor, NULL, NULL);
				runProgram = true;
			}

			break;

		case 4:
			lookingFor = (bodyId_t)strtoul(argv[1], &endptr, 10);
			prepareProgParams(false, lookingFor, argv[2], argv[3]);

			runProgram = true;
			break;

		default:
			fprintf(stderr, "Please specify a .bodies file followed by a .conf file. OR specify 'g' to generate default .conf and a template for your .bodies\n");
			exit(EXIT_FAILURE);
			break;
	}

	if (runProgram) {
		program();
	}
}

void program(void) {
	bool found = false;

	for (bodyId_t i = 0; i < params.bodyFile.numberOfBodies; i++) {
		Body* body = &params.bodyFile.bodies[i];

		if (body->BodyId == params.bodyId) {
			print_body(body, true);
			printf("\n\n");
			found = true;
			break;
		}
	}

	free(params.bodyFile.bodies);

	if (!found) {
		fprintf(stderr, "Couldn't find object with id %u.\n", params.bodyId);
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}