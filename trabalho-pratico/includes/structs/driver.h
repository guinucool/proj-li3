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

typedef struct _DRIVER_ Driver;
typedef short Date[3];

Driver *createDriver(int, char *, Date, char, char, char[], char[], Date, char);
void updateDriver(Driver * driver, int score, double money_received, char * city);
void destroyDriver(Driver*);
void printDriver(Driver*);
Driver *parseDriver(char[9][200]);
int parseDate(char*, Date);
int driver_Id(Driver * driver);
void driver_Str(char * dest, Driver * driver, char mode);
void driver_Date(Date dest, Driver * driver, char mode);
char driver_Char(Driver * driver, char mode);

#endif