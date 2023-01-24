#ifndef _DRIVER_H_
#define _DRIVER_H_

#define NAME_STR_SIZE 50
#define LICENSE_PLATE_STR_SIZE 10
#define CITY_STR_SIZE 30

#define BASIC 0
#define GREEN 1
#define PREMIUM 2

#define MALE 'M'
#define FEMALE 'F'

#define INACTIVE 0
#define ACTIVE 1

extern char car_class_str[][8];
#define CLASS_SIZE 3

extern char account_status_str[][9];
#define STATUS_SIZE 2

// Estrutura
typedef struct _DRIVER_ *Driver;

// Tratamentos
Driver createDriver(int id, char * name, short age, char gender, char car_class, char * license_plate, char * city, Date account_creation, char account_status);
void updateDriver(Driver driver, int score, double money_received, char * city, Date date);
void destroyDriver(Driver driver);
void debugPrintDriver(Driver driver);
Driver parseDriver(char tokens[9][200]);
int drivercmp(Driver driver1, Driver driver2, char * city);

// Devoluções
int driver_id(Driver driver);
void driver_name(char * dest, Driver driver);
short driver_age(Driver driver);
char driver_gender(Driver driver);
char driver_carClass(Driver driver);
void driver_accountCreation(Date dest, Driver driver);
char driver_accountStatus(Driver driver);
double driver_score(Driver driver, char * city);
int driver_rides(Driver driver);
double driver_moneyReceived(Driver driver);

#endif