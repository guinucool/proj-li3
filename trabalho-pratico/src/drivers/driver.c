#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../inc/drivers/driver.h"

char car_class_str[][8] = {"BASIC", "GREEN", "PREMIUM"};
char account_status_str[][9] = {"INACTIVE", "ACTIVE"};

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