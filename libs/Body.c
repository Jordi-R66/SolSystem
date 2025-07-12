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

	if (final.MeanAnomaly < 0.0l) {
		final.MeanAnomaly += 360.0l;
	}

	return final;
}

Body* complexifyBodies(SimplifiedBody* simpleBodies, size_t numberOfBody, SysConf* sysConf) {
	void* tempBodies = calloc(numberOfBody, BODY_SIZE);

	if (tempBodies == NULL) {
		fprintf(stderr, "Couldn't attribute enough memory for %zu bodies.\n", numberOfBody);
		exit(EXIT_FAILURE);
	}

	void* tempKvp = calloc(numberOfBody, KVP_SIZE);

	if (tempKvp == NULL) {
		fprintf(stderr, "Couldn't attribute enough memory for the kvp of %zu bodies.\n", numberOfBody);
		free(tempBodies);
		exit(EXIT_FAILURE);
	}

	Body* bodyArray = (Body*)tempBodies;
	kvp* bodiesKvp = (kvp*)tempKvp;
	Body* bodyPtr;

	tempBodies = NULL;
	tempKvp = NULL;

	for (size_t i = 0; i < numberOfBody; i++) {
		SimplifiedBody* simpleBody = &simpleBodies[i];

		bodyArray[i] = complexifyBody(*simpleBody, sysConf);
		bodiesKvp[i] = (kvp){simpleBody->bodyId, &bodyArray[i]};
	}

	for (size_t i = 0; i < numberOfBody; i++) {
		bodyPtr = &bodyArray[i];

		if (bodyPtr->hasParent) {
			for (size_t j = 0; j < numberOfBody; j++) {
				kvp KVP = bodiesKvp[j];

				if (KVP.id == bodyPtr->ParentId) {
					bodyPtr->ParentPTR = KVP.ptr;

					bodyPtr->MeanMotion = AngularSpeed(bodyPtr);

					bodyPtr->Apo = bodyPtr->SemiMajorAxis * (1.0l + bodyPtr->Eccentricity);
					bodyPtr->Peri = bodyPtr->SemiMajorAxis * (1.0l - bodyPtr->Eccentricity);
					break;
				}
			}
		}

		bodyPtr->sphereOfInfluence = SphereOfInfluence(bodyPtr, 0.0l);
	}

	memset((void*)bodiesKvp, 0, numberOfBody * KVP_SIZE);
	free((void*)bodiesKvp);

	bodiesKvp = (kvp*)NULL;

	return bodyArray;
}

void print_body(Body* body, bool simplifyUnits) {

	long double distCoeff = simplifyUnits ? 1.0l / body->sysConf->DistScale : 1.0l;
	long double timeCoeff = simplifyUnits ? 1.0l / 86400.0l : 1.0l;

	char timeUnitChar = simplifyUnits ? 'd' : 's';
	char distUnitChar = simplifyUnits ? 'A' : 'm';

	long double SOI_RANGE = (body->sphereOfInfluence - SphereOfInfluence(body, body->Peri)) * distCoeff;
	long double SMA_RANGE = (body->SemiMajorAxis * body->Eccentricity) * distCoeff;

	printf("Body name : %s\n", body->BodyName);

	printf("---------------------------------- DATA ----------------------------------\n");

	printf("BODY ID : %u\n", body->BodyId);
	printf("PARENT ID : %u\n", body->ParentId);

	printf("\n");

	printf("INCLINATION : %.4f degs\n", body->Inclination);
	printf("LONGITUDE OF ASC. NODE : %.4f degs\n", body->AscNodeLong);
	printf("ECCENTRICITY : %.7Lf\n", body->Eccentricity);
	printf("ARG. OF PERIAPSIS : %.4f degs\n", body->PeriArg);
	printf("MEAN ANOMALY : %.4f degs\n", body->MeanAnomaly);
	printf("ORBITAL PERIOD : %.4Lf %c\n", 2.0l * M_PIl / body->MeanMotion * timeCoeff, timeUnitChar);

	printf("DIST : %.4Lf +/- %.4Lf %c\n", body->SemiMajorAxis * distCoeff, SMA_RANGE, distUnitChar);
	printf("SOI : %.4Lf +/- %.4Lf %c\n", body->sphereOfInfluence * distCoeff, SOI_RANGE, distUnitChar);
}