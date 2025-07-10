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

	fclose(fp);

	BodyFile output;

	output.numberOfBodies = nBodies;
	output.bodies = complexifyBodies(simplifiedBodies, nBodies, conf);

	free((void*)simplifiedBodies);

	simplifiedBodies = (SimplifiedBody*)NULL;
	tempPtr = NULL;

	return output;
}
