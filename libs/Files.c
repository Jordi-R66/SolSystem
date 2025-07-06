#include "FileParser.h"
#include "Files.h"

void ExportSimplifiedBodies(SimplifiedBody* bodies, size_t numberOfBodies, SysConf* sysConf) {
	FILE* fp = fopen(sysConf->SysName, "w");

	fwrite((void*)bodies, SIMPLIFIED_BODY_SIZE, numberOfBodies, fp);

	fclose(fp);
}