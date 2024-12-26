#include "FileParser.h"

#define EOS '\0'

void parse_line(string* line, SysConf* conf, Body* body) {
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

		ssize_t j = i - (last_comma + 1);

		switch (count) {
			case 0:
				BODY_ID[j] = c != ',' ? c : 0;
				break;

			case 1:
				BODY_NAME[j] = c != ',' ? c : 0;
				break;

			case 2:
				PARENT_ID[j] = c != ',' ? c : 0;
				break;

			case 3:
				BODY_MASS[j] = c != ',' ? c : 0;
				break;

			case 4:
				SEMI_MAJOR_AXIS[j] = c != ',' ? c : 0;
				break;

			case 5:
				ECCENTRICITY[j] = c != ',' ? c : 0;
				break;

			case 6:
				INCLINATION[j] = c != ',' ? c : 0;
				break;

			case 7:
				AN[j] = c != ',' ? c : 0;
				break;

			case 8:
				PERI_LONG[j] = c != ',' ? c : 0;
				break;

			case 9:
				MEAN_LONG[j] = c != ',' ? c : 0;
				break;

			default:
				break;
		}

		if (c == sep) {
			last_comma = i;
			count++;
		}
	}

	bool hasParent;

	//printf("\n%u, %u\n\n",current_field, separators_indexes[current_field + 1]);

	//printf("ID : %s\nName : %s\nParent : %s\n-------------------------------------------\nMass : %s * 10^24 kg\nSMA : %s AU\nECC : %s\nInclination : %s°\nAsc. Node : %s°\nPeri LNG : %s°\nMean LNG : %s°\n-------------------------------------------\n", BODY_ID, BODY_NAME, PARENT_ID, BODY_MASS, SEMI_MAJOR_AXIS, ECCENTRICITY, INCLINATION, AN, PERI_LONG, MEAN_LONG);

	return;
}
