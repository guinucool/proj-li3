#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../../inc/drivers/driver.h"

char car_class_str[][8] = {"BASIC", "GREEN", "PREMIUM"};
int car_class_size = 3;
char account_status_str[][9] = {"INACTIVE", "ACTIVE"};
int account_status_size = 2;

Driver *createDriver(int id, char *name, short birth_day[], char gender, char car_class, char license_plate[], char city[], short account_creation[], char account_status) {
	
	Driver *driver = (Driver*) malloc(sizeof(Driver));

	// TODO: Needs validating input data.

	driver->id = id;
	strncpy(driver->name, name, NAME_STR_SIZE);

	driver->birth_day[0] = birth_day[0];
	driver->birth_day[1] = birth_day[1];
	driver->birth_day[2] = birth_day[2];
	
	driver->gender = gender;
	driver->car_class = car_class;
	strncpy(driver->license_plate, license_plate, LICENSE_PLATE_STR_SIZE);
	strncpy(driver->city, city, CITY_STR_SIZE);
	driver->account_creation[0] = account_creation[0];
	driver->account_creation[1] = account_creation[1];
	driver->account_creation[2] = account_creation[2];
	driver->account_status = account_status; 

	return driver;
}

void destroyDriver(Driver *driver) {
	free(driver);
}

void printDriver(Driver* driver) {
	printf("Driver {id: %d, name: %s, birth_date: %02d/%02d/%04d, gender: %c, car_class: %s, license_plate: %s, city: %s, account_creation: %02d/%02d/%04d, account_status: %s}", 
		driver->id, 
		driver->name,
		driver->birth_day[0], driver->birth_day[1], driver->birth_day[2],
		driver->gender,
		car_class_str[driver->car_class],
		driver->license_plate,
		driver->city,
		driver->account_creation[0], driver->account_creation[1], driver->account_creation[2],
		account_status_str[driver->account_status]
	);
}

Driver *parseDriver(char* str) {
		
	char tokens[9][1024];

	int i = 0, id; 
	char name[NAME_STR_SIZE];
	short birth_day[3];
	char gender;
	int car_class;
	char license_plate[LICENSE_PLATE_STR_SIZE];
	char city[CITY_STR_SIZE];
	short account_creation[3];
	char account_status;
	char limit[] = {';', '\0'};
	char *token;

	// Get all parts (tokens) of the input string.
	token = strtok(str, limit);

	do {
		strncpy (tokens[i++], token, 1024);

	} while(token = strtok(NULL, limit));

	if (i != 9) {
		return NULL;
	}

	// Remove trailing cariage return ('\n').
	tokens[8][strlen(tokens[8])-2] = '\0';

	// Parse ID.
	if ((id = atoi(tokens[0])) == 0) {
		return NULL;
	}

	// Parse NAME.
	strncpy(name, tokens[1], NAME_STR_SIZE);

	// Parse BIRTTH DAY.
	if (!parseDate(tokens[2], birth_day)) {
		return NULL;
	}

	// Parse GENDER.
	gender = tokens[3][0];

	if (gender != MALE && gender != FEMALE) {
		return NULL;
	}

	// Parse CAR CLASS.

	for(int i = 0; tokens[4][i]; i++) {
		tokens[4][i] = toupper(tokens[4][i]);
	}

	car_class = -1;
	for (int i = 0; i < car_class_size; i++) {
		if (strcmp(tokens[4], car_class_str[i]) == 0) {
			car_class = i;
			break;
		}
	}

	if (car_class == -1) {
		return NULL;
	}

	// Parse LICENSE PLATE
	strncpy(license_plate, tokens[5], LICENSE_PLATE_STR_SIZE);

	// Parse CITY.
	strncpy(city, tokens[6], CITY_STR_SIZE);

	// Parse ACCOUNT CREATION.
	if (!parseDate(tokens[7], account_creation)) {
		return NULL;
	}

	// Parse ACCOUNT STATUS.
	for(int i = 0; tokens[8][i]; i++) {
		tokens[8][i] = toupper(tokens[8][i]);
	}

	account_status = 9;
	for (int i = 0; i < account_status_size; i++) {
		if (strcmp(tokens[8], account_status_str[i]) == 0) {
			account_status = i;
			break;
		}
	}

	if (account_status == 9) {
		return NULL;
	}

	// TODO: Remove before submission. Let this for testing purpose.
	/*printf("ID: %d, NAME: %s, BIRTH DAY: %02d/%02d/%04d, GENDER: %c, CAR CLASS: %s, LICENSE PLATE: %s, CITY: %s, ACCOUNT CREATION: %02d/%02d/%04d, ACCOUNT STATUS: %s\n", 
		id, 
		name, 
		birth_day[0], birth_day[1], birth_day[2],
		gender,
		car_class_str[car_class],
		license_plate,
		city,
		account_creation[0], account_creation[1], account_creation[2],
		account_status_str[account_status]
	);*/

	return createDriver(id, name, birth_day, gender, car_class, license_plate, city, account_creation, account_status);
}

int parseDate(char *str, short date[]) {

	char *token;
	char limit[] = {'/', '\0'};
	int n, i = 0;

	token = strtok(str, limit);

	do {
		if ((n = atoi(token)) == 0) {
			return 0;
		}

		date[i++] = n;

	} while(token = strtok(NULL, limit));

	return i==3;
}