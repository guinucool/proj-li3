#ifndef _DRIVER_H_
#define _DRIVER_H_

#define NAME_STR_SIZE 50
#define LICENSE_PLATE_STR_SIZE 10
#define CITY_STR_SIZE 30

#define BASIC 0
#define GREEN 1
#define PREMIUM 2

extern char car_class_str[][8];
extern int car_class_size;

#define MALE 'M'
#define FEMALE 'F'

#define INACTIVE 0
#define ACTIVE 1

extern char account_status_str[][9];
extern int account_status_size;

typedef struct _DRIVER_ {
	int id;                                      // INTEGER
	char name[NAME_STR_SIZE];                     // STRING
	short birth_day[3];                          // {day, month, year}
	char gender;                                 //  {'M' - MALE, 'F' - FEMALE}
	char car_class;                              // {0 - BASIC, 1 - GREEN, 2 - PREMIUM}
	char license_plate[LICENSE_PLATE_STR_SIZE];  // STRING
	char city[CITY_STR_SIZE];                    // STRING
	short account_creation[3];                   // {day, month, year}
	char account_status;                         // {0 - INACTIVE, 1 - ACTIVE}
} Driver;

Driver *createDriver(int, char *, short[], char, char, char[], char[], short[], char);
void destroyDriver(Driver*);
void printDriver(Driver*);
Driver *parseDriver(char*);
int parseDate(char*, short[]);

#endif