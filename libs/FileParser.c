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
	memset(BODY_ID, 0, BODY_ID_LENGTH);
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
	size_t separators_indexes[10];

	for (size_t i = 0; i < line_length; i++) {
		c = line[i];

		if (c == sep) {
			separators_indexes[count] = i;
			printf("%u, %u\n", count, i);
			count++;
		}
	}

	separators_indexes[9] = line_length;

	size_t current_field = 0;
	int32_t BodyId, BodyParent;
	bool hasParent;

	for (size_t i = 0; i < separators_indexes[current_field]; i++) {
		size_t j = i - separators_indexes[current_field] + 1;
		BODY_ID[j] = line[i];
	}

	current_field++;

	for (size_t i = separators_indexes[current_field] + 1; i < separators_indexes[current_field + 1]; i++) {
		size_t j = i - separators_indexes[current_field] - 1;
		BODY_NAME[j] = line[i];
	}

	current_field++;

	for (size_t i = separators_indexes[current_field] + 1; i < separators_indexes[current_field + 1]; i++) {
		size_t j = i - separators_indexes[current_field] - 1;
		PARENT_ID[j] = line[i];
	}

	current_field++;

	for (size_t i = separators_indexes[current_field] + 1; i < separators_indexes[current_field + 1]; i++) {
		size_t j = i - separators_indexes[current_field] - 1;
		BODY_MASS[j] = line[i];
	}

	current_field++;

	for (size_t i = separators_indexes[current_field] + 1; i < separators_indexes[current_field + 1]; i++) {
		size_t j = i - separators_indexes[current_field] - 1;
		SEMI_MAJOR_AXIS[j] = line[i];
	}

	current_field++;

	for (size_t i = separators_indexes[current_field] + 1; i < separators_indexes[current_field + 1]; i++) {
		size_t j = i - separators_indexes[current_field] - 1;
		ECCENTRICITY[j] = line[i];
	}

	current_field++;

	for (size_t i = separators_indexes[current_field] + 1; i < separators_indexes[current_field + 1]; i++) {
		size_t j = i - separators_indexes[current_field] - 1;
		INCLINATION[j] = line[i];
	}

	current_field++;

	for (size_t i = separators_indexes[current_field] + 1; i < separators_indexes[current_field + 1]; i++) {
		size_t j = i - separators_indexes[current_field] - 1;
		AN[j] = line[i];
	}

	current_field++;

	for (size_t i = separators_indexes[current_field] + 1; i < separators_indexes[current_field + 1]; i++) {
		size_t j = i - separators_indexes[current_field] - 1;
		PERI_LONG[j] = line[i];
	}

	current_field++;

	for (size_t i = separators_indexes[current_field] + 1; i < separators_indexes[current_field + 1]; i++) {
		size_t j = i - separators_indexes[current_field] - 1;
		MEAN_LONG[j] = line[i];
	}

	printf("\n%u, %u",current_field, separators_indexes[current_field + 1]);

	//printf("ID : %s\nName : %s\nParent : %s\n-------------------------------------------\nMass : %s * 10^24 kg\nSMA : %s AU\nECC : %s\nInclination : %s°\nAsc. Node : %s°\n%s\n%s\n-------------------------------------------\n", BODY_ID, BODY_NAME, PARENT_ID, BODY_MASS, SEMI_MAJOR_AXIS, ECCENTRICITY, INCLINATION, AN, PERI_LONG, MEAN_LONG);

	return;
}

/*
TLE parse_block(string lines[][70]) {
	char *endptr;
	string *NAME_LINE = lines[0];
	string *FIRST_LINE = lines[1];
	string *SECOND_LINE = lines[2];

	// 0-th line

	string OBJ_NAME[NAME_LENGTH];

	// 1st line

	string NORAD_CAT[NORAD_ID_LENGTH];
	char CLASSIFICATION;
	string COSPAR_YR[YR_LENGTH];
	string LAUNCH_NB[LAUNCH_NB_LENGTH];
	string LAUNCH_PART[LAUNCH_PART_LENGTH];
	string EPOCH_YR[YR_LENGTH];
	string EPOCH_DAY[EPOCH_LENGTH];
	string DERIV_1[DERIV_1_LENGTH];
	string DERIV_2[DERIV_2_LENGTH];
	string BSTAR[BSTAR_LENGTH];

	// 2nd line

	string INCLI[INCLINATION_LENGTH];
	string AN[ASC_NODE_LENGTH];
	string ECC[ECC_LENGTH];
	string ARG_PE[ARG_PE_LENGTH];
	string MEAN_ANO[MEAN_ANO_LENGTH];
	string MEAN_MOTION[MEAN_MOTION_LENGTH];
	string REVOLUTIONS[REVS_LENGTH];

	// --------------------------- 1-ST LINE PARSING ---------------------------

	for (uint8_t i=0; i < NAME_LENGTH; i++) {
		OBJ_NAME[i] = NAME_LINE[i];
	}

	for (uint8_t i=0; i < NORAD_ID_LENGTH; i++) {
		if (i < 5) {
			NORAD_CAT[i] = FIRST_LINE[i+2];
		} else {
			CLASSIFICATION = FIRST_LINE[i+2];
		}
	}

	for (uint8_t i=0; i < (COSPAR_LENGTH-1); i++) {
		char c = FIRST_LINE[i+9];
		if (i < 2) {
			COSPAR_YR[i] = c;
		} else if (i < 5) {
			LAUNCH_NB[i-2] = c;
		} else {
			LAUNCH_PART[i-5] = c;
		}
	}

	for (uint8_t i=0; i < (EPOCH_LENGTH + YR_LENGTH - 1); i++) {
		char c = FIRST_LINE[i+18];
		if (i < (YR_LENGTH-1)) {
			EPOCH_YR[i] = c;
		} else {
			EPOCH_DAY[i-2] = c;
		}
	}

	for (uint8_t i=0; i < (DERIV_1_LENGTH-1); i++) {
		char c = FIRST_LINE[i+33];
		DERIV_1[i] = c;
	}

	for (uint8_t i=0; i < (DERIV_2_LENGTH-1); i++) {
		char c = FIRST_LINE[i+44];
		DERIV_2[i] = c;
	}

	for (uint8_t i=0; i < (BSTAR_LENGTH-1); i++) {
		char c = FIRST_LINE[i+53];
		BSTAR[i] = c;
	}

	NORAD_CAT[NORAD_ID_LENGTH-1] = EOS;
	COSPAR_YR[YR_LENGTH-1] = EOS;
	LAUNCH_NB[LAUNCH_NB_LENGTH-1] = EOS;
	LAUNCH_PART[LAUNCH_PART_LENGTH-1] = EOS;
	EPOCH_YR[YR_LENGTH-1] = EOS;
	EPOCH_DAY[EPOCH_LENGTH-1] = EOS;
	DERIV_1[DERIV_1_LENGTH-1] = EOS;
	DERIV_2[DERIV_2_LENGTH-1] = EOS;
	BSTAR[BSTAR_LENGTH-1] = EOS;

	// --------------------------- 2-ND LINE PARSING ---------------------------

	for (uint8_t i=0; i < (NORAD_ID_LENGTH-1); i++) {
		if (NORAD_CAT[i] != SECOND_LINE[i+2]) {
			printf("%s\n%s\n", FIRST_LINE, SECOND_LINE);
			perror("The NORAD Catalogue Number doesn't match up between line 1 and 2\n");
			exit(0);
		}
	}

	for (uint8_t i=0; i < (INCLINATION_LENGTH-1); i++) {
		char c = SECOND_LINE[i+8];

		INCLI[i] = c;
	}

	for (uint8_t i=0; i < (ASC_NODE_LENGTH-1); i++) {
		char c = SECOND_LINE[i+17];

		AN[i] = c;
	}

	for (uint8_t i=0; i < (ECC_LENGTH-1); i++) {
		char c = SECOND_LINE[i+25];

		ECC[i] = c;
	}

	for (uint8_t i=0; i < (ARG_PE_LENGTH-1); i++) {
		char c = SECOND_LINE[i+34];

		ARG_PE[i] = c;
	}

	for (uint8_t i=0; i < (MEAN_ANO_LENGTH-1); i++) {
		char c = SECOND_LINE[i+43];

		MEAN_ANO[i] = c;
	}

	for (uint8_t i=0; i < (MEAN_MOTION_LENGTH-1); i++) {
		char c = SECOND_LINE[i+52];

		MEAN_MOTION[i] = c;
	}

	for (uint8_t i=0; i < (REVS_LENGTH - 1); i++) {
		char c = SECOND_LINE[i+63];

		REVOLUTIONS[i] = c;
	}

	INCLI[INCLINATION_LENGTH-1] = EOS;
	AN[ASC_NODE_LENGTH-1] = EOS;
	ECC[0] = '.';
	ECC[ECC_LENGTH-1] = EOS;
	ARG_PE[ARG_PE_LENGTH-1] = EOS;
	MEAN_ANO[MEAN_ANO_LENGTH-1] = EOS;
	MEAN_MOTION[MEAN_MOTION_LENGTH-1] = EOS;
	REVOLUTIONS[REVS_LENGTH-1] = EOS;

	// ---------- Enregistrement des données dans la struct ----------

	static TLE output;

	strcpy(output.name, OBJ_NAME);

	output.NORAD_ID = (uint32_t)strint(NORAD_CAT);
	output.Classification = CLASSIFICATION;

	output.COSPAR_YR = (uint8_t)strint(COSPAR_YR);
	output.COSPAR_LN = (uint16_t)strint(LAUNCH_NB);
	strcpy(output.COSPAR_ID, LAUNCH_PART);

	output.EPOCH_YR = (uint8_t)strint(EPOCH_YR);
	output.EPOCH = strtod(EPOCH_DAY, &endptr);

	output.FIRST_DERIV_MEAN_MOTION = strtod(DERIV_1, &endptr) * 2.0;
	output.SECOND_DERIV_MEAN_MOTION = strtoscinotd(DERIV_2) * 6.0;
	output.B_STAR = strtoscinotd(BSTAR);

	output.Inclination = strtof(INCLI, &endptr);
	output.AscNodeLong = strtof(AN, &endptr);
	output.Eccentricity = strtof(ECC, &endptr);
	output.PeriArg = strtof(ARG_PE, &endptr);
	output.MeanAnomaly = strtof(MEAN_ANO, &endptr);
	output.MeanMotion = strtod(MEAN_MOTION, &endptr);

	output.Revolutions = (uint32_t)strint(REVOLUTIONS);

	return output;
}

TLE parse_lines(string NAME_LINE[25], string FIRST_LINE[70], string SECOND_LINE[70]) {
	string lines[3][70];

	for (int8_t l=0; l<3; l++) {
		for (int8_t col=0; col<70; col++) {
			lines[l][col] = 0;
		}
	}

	strcpy(lines[0], NAME_LINE);
	strcpy(lines[1], FIRST_LINE);
	strcpy(lines[2], SECOND_LINE);

	return parse_block(lines);
}
*/