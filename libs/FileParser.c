#include "FileParser.h"

#define EOS '\0'

void parse_line(string* line, Body* body) {
	SysConf* conf = body->sysConf;

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
	//string** fields = {(string*)BODY_ID, (string*)BODY_NAME, (string*)PARENT_ID, (string*)BODY_MASS, (string*)SEMI_MAJOR_AXIS, (string*)ECCENTRICITY, (string*)INCLINATION, (string*)AN, (string*)PERI_LONG, (string*)MEAN_LONG};
	//ssize_t field_number = 10;
	//string* current_field;

	for (ssize_t i = 0; i < line_length; i++) {
		c = line[i];
		char char_copy = c != ',' ? c : 0;

		ssize_t j = i - (last_comma + 1);

		//if (count < field_number) {
		//	current_field = fields[count];
		//	current_field[j] = char_copy;
		//}

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

	bool hasParent;



	//printf("ID : %s\nName : %s\nParent : %s\n-------------------------------------------\nMass : %s * 10^24 kg\nSMA : %s AU\nECC : %s\nInclination : %s°\nAsc. Node : %s°\nPeri LNG : %s°\nMean LNG : %s°\n-------------------------------------------\n", BODY_ID, BODY_NAME, PARENT_ID, BODY_MASS, SEMI_MAJOR_AXIS, ECCENTRICITY, INCLINATION, AN, PERI_LONG, MEAN_LONG);

	return;
}
