#include "FileParser.h"
#include "Files.h"

void ExportBodies(BodyFile* bodyFile, SysConf* sysConf) {
	FILE* fp = fopen(sysConf->SysName, "w");

	SimplifiedBody* temp = (SimplifiedBody*)calloc(bodyFile->numberOfBodies, SIMPLIFIED_BODY_SIZE);

	for (size_t i = 0; i < bodyFile->numberOfBodies; i++) {
		Body bodyToCopy = bodyFile->bodies[i];

		SimplifiedBody* bodyToWrite = temp + i;

		bodyToWrite->bodyId = bodyToCopy.BodyId;
		memcpy(bodyToWrite->BodyName, bodyToCopy.BodyName, NAME_LENGTH);

		bodyToWrite->hasParent = bodyToCopy.hasParent;
		bodyToWrite->parentId = bodyToCopy.ParentId;

		bodyToWrite->Mass = bodyToCopy.BodyMass;
		bodyToWrite->SMA = bodyToCopy.SemiMajorAxis;
		bodyToWrite->Eccentricity = bodyToCopy.Eccentricity;
		bodyToWrite->Inclination = bodyToCopy.Inclination;
		bodyToWrite->AscNode = bodyToCopy.AscNodeLong;
		bodyToWrite->PeLNG = bodyToCopy.PeriLong;
		bodyToWrite->MeanLNG = bodyToCopy.MeanLong;
	}

	fwrite((void*)temp, SIMPLIFIED_BODY_SIZE, bodyFile->numberOfBodies, fp);

	fclose(fp);
}