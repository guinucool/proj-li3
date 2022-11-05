#ifndef _DRIVER_H_
#define _DRIVER_H_

#define MAX_NAME_STR 50

typedef struct _DRIVER_ {
	int id;
	char name[MAX_NAME_STR];
	//id;name;birth_day;gender;car_class;license_plate;city;account_creation;account_status
} Driver;

Driver *createDriver(int id, char *name);
void destroyDriver(Driver*);
void printDriver(Driver*);

#endif