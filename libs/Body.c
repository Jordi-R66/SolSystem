#include "Body.h"

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
	printf("MEAN MOTION : %.8Lf rev/(sid. day)\n", body->MeanMotion);
}