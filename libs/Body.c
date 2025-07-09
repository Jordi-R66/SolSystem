#include "Body.h"

#include "OrbMaths.h"

Body complexifyBody(SimplifiedBody simpleBody, SysConf* sysConf) {
	Body final;

	memset(&final, 0, BODY_SIZE);

	final.sysConf = sysConf;
	final.BodyId = simpleBody.bodyId;
	final.hasParent = simpleBody.hasParent;
	final.ParentId = simpleBody.parentId;

	memcpy(final.BodyName, simpleBody.BodyName, NAME_LENGTH);

	final.BodyMass = simpleBody.Mass;
	final.stdGravParam = final.BodyMass * G;

	final.SemiMajorAxis = simpleBody.SMA * sysConf->DistScale;
	final.Eccentricity = simpleBody.Eccentricity;
	final.Inclination = simpleBody.Inclination;
	final.AscNodeLong = simpleBody.AscNode;
	final.PeriLong = simpleBody.PeLNG;
	final.MeanLong = simpleBody.MeanLNG;

	final.PeriArg = final.PeriLong - final.AscNodeLong;
	final.MeanAnomaly = final.MeanLong - final.PeriLong;

	final.OrbPeriod = OrbitalPeriod(&final);

	return final;
}

Body* complexifyBodies(SimplifiedBody* simpleBodies, size_t numberOfBody, SysConf* sysConf) {
	void* tempBodies = calloc(numberOfBody, BODY_SIZE);
	void* tempKVP = calloc(numberOfBody, sizeof(Body*));

	bool failure = (tempBodies == NULL) || (tempKVP == NULL);
	uint8_t failureCount = 0;

	if (tempBodies == NULL) {
		fprintf(stderr, "Couldn't attribute enough memory for %zu bodies.\n", numberOfBody);
		failureCount++;
	}

	if (tempKVP == NULL) {
		fprintf(stderr, "Couldn't attribute enough memory to a kvp array for %zu bodies.\n", numberOfBody);
		failureCount++;
	}

	if (failure) {
		if (failureCount == 1) {
			if (tempBodies != NULL) {
				free(tempBodies);
			} else {
				free(tempKVP);
			}
		}

		exit(EXIT_FAILURE);
	}

	Body* bodyArray = (Body*)tempBodies;
	Body** kvpArray = (Body**)tempKVP;

	for (size_t i = 0; i < 10; i++) {
		SimplifiedBody* simpleBody = &simpleBodies[i];

		bodyArray[i] = complexifyBody(*simpleBody, sysConf);
		kvpArray[i] = simpleBody;
	}

	for (size_t i = 0; i < 10; i++) {
		if (bodyArray[i].hasParent) {
			bodyArray[i].ParentPTR = (void*)kvpArray[bodyArray->ParentId];
		}
	}

	return NULL;
}

void print_body(Body* body) {
	printf("Body name : %s\n", body->BodyName);

	printf("---------------------------------- DATA ----------------------------------\n");

	printf("BODY ID : %X\n", body->BodyId);
	printf("PARENT ID : %X\n", body->ParentId);

	printf("\n");

	printf("INCLINATION : %.4Lf degs\n", body->Inclination);
	printf("LONGITUDE OF ASC. NODE : %.4Lf degs\n", body->AscNodeLong);
	printf("ECCENTRICITY : %.7Lf\n", body->Eccentricity);
	printf("ARG. OF PERIAPSIS : %.4Lf degs\n", body->PeriArg);
	printf("MEAN ANOMALY : %.4Lf degs\n", body->MeanAnomaly);
	printf("ORBITAL PERIOD : %.8Lf seconds\n", body->OrbPeriod);
}