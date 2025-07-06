#include "FileParser.h"

#define EOS '\0'

SysConf parseConfFile(string* filename) {
	FILE* fp = fopen(filename, "r");

	SysConf conf;

	fread(&conf, sizeof(SysConf), 1, fp);
	fclose(fp);

	return conf;
}

BodyFile parseBodiesFile(string* filename, SysConf* conf) {
	FILE* fp = fopen(filename, "r");

	if (fp == NULL) {
		fprintf(stderr, "Couldn't open %s in read-only mode\n", filename);
		exit(EXIT_FAILURE);
	}

	long pos = 0;

	fseek(fp, 0, SEEK_END);
	pos = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	size_t nBodies = pos / SIMPLIFIED_BODY_SIZE;

	void* tempPtr = calloc(nBodies, SIMPLIFIED_BODY_SIZE);
	SimplifiedBody* simplifiedBodies = (SimplifiedBody*)tempPtr;

	if (tempPtr == NULL) {
		fprintf(stderr, "Couldn't prepare to parse %s\n", filename);
		exit(EXIT_FAILURE);
	}

	fread(simplifiedBodies, SIMPLIFIED_BODY_SIZE, nBodies, fp);
	tempPtr = calloc(nBodies, BODY_SIZE);

	fclose(fp);

	if (tempPtr == NULL) {
		fprintf(stderr, "Couldn't initiate the intermediate conversion process\n");
		exit(EXIT_FAILURE);
	}

	BodyFile output;

	output.numberOfBodies = nBodies;
	output.bodies = (Body*)tempPtr;

	for (size_t i = 0; i < nBodies; i++) {
		SimplifiedBody body = simplifiedBodies[i];

		output.bodies[i] = complexifyBody(body, conf);
	}

	return output;
}

Body parse_line(string* line, SysConf* conf) {
	Body body;

	/*body.sysConf = conf;

	char sep = ',';

	char* endptr;

	size_t line_length = strlen(line);

	string BODY_ID[BODY_ID_LENGTH];
	string BODY_NAME[NAME_LENGTH];
	string PARENT_ID[BODY_ID_LENGTH];

	string BODY_MASS[BODY_MASS_LENGTH];
	string SEMI_MAJOR_AXIS[SMA_LENGTH];
	string ECCENTRICITY[ECC_LENGTH];
	string INCLINATION[INCLINATION_LENGTH];
	string AN[LNG_LENGTH];
	string PERI_LONG[LNG_LENGTH];
	string MEAN_LONG[LNG_LENGTH];

	memset(BODY_ID, 0, BODY_ID_LENGTH);
	memset(BODY_NAME, 0, NAME_LENGTH);
	memset(PARENT_ID, 0, BODY_ID_LENGTH);

	memset(BODY_MASS, 0, BODY_MASS_LENGTH);
	memset(SEMI_MAJOR_AXIS, 0, SMA_LENGTH);
	memset(ECCENTRICITY, 0, ECC_LENGTH);
	memset(INCLINATION, 0, INCLINATION_LENGTH);
	memset(AN, 0, LNG_LENGTH);
	memset(PERI_LONG, 0, LNG_LENGTH);
	memset(MEAN_LONG, 0, LNG_LENGTH);

	// ------------------------------------------------------

	char c;

	uint8_t count = 0;
	ssize_t last_comma = -1;

	for (ssize_t i = 0; i < line_length; i++) {
		c = line[i];
		char char_copy = c != ',' ? c : 0;

		ssize_t j = i - (last_comma + 1);

		switch (count) {
			case 0:
				BODY_ID[j] = char_copy;
				break;

			case 1:
				BODY_NAME[j] = char_copy;
				break;

			case 2:
				PARENT_ID[j] = char_copy;
				break;

			case 3:
				BODY_MASS[j] = char_copy;
				break;

			case 4:
				SEMI_MAJOR_AXIS[j] = char_copy;
				break;

			case 5:
				ECCENTRICITY[j] = char_copy;
				break;

			case 6:
				INCLINATION[j] = char_copy;
				break;

			case 7:
				AN[j] = char_copy;
				break;

			case 8:
				PERI_LONG[j] = char_copy;
				break;

			case 9:
				MEAN_LONG[j] = char_copy;
				break;

			default:
				break;
		}

		if (c == sep) {
			last_comma = i;
			count++;
		}
	}

	// Information conversion

	bool hasParent;
	bodyId_t body_id, parent_id;
	long double mass, sma, ecc, inc, an, pl, mn;

	body_id = (bodyId_t)strtol(BODY_ID, &endptr, 10);
	parent_id = (bodyId_t)strtol(PARENT_ID, &endptr, 10);

	hasParent = (parent_id) && (1 << (ID_BITS - 1));

	mass = strtold(BODY_MASS, &endptr);
	sma = strtold(SEMI_MAJOR_AXIS, &endptr);
	ecc = strtold(ECCENTRICITY, &endptr);
	inc = strtold(INCLINATION, &endptr);
	an = strtold(AN, &endptr);
	pl = strtold(PERI_LONG, &endptr);
	mn = strtold(MEAN_LONG, &endptr);

	// Information saving

	body.BodyId = body_id;
	body.hasParent = hasParent;
	body.ParentId = parent_id;
	strcpy(body.BodyName, BODY_NAME);

	body.BodyMass = mass * powl(10.0l, conf->MassScale);
	body.SemiMajorAxis = sma * conf->DistScale;
	body.Eccentricity = ecc;
	body.Inclination = inc;
	body.AscNodeLong = an;
	body.PeriLong = pl;
	body.MeanLong = mn;

	body.PeriArg = pl - an;
	body.MeanAnomaly = NAN;
	body.MeanMotion = NAN;*/

	return body;
}
