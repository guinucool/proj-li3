#ifndef _RIDE_H_
#define _RIDE_H_

#define MAX_STR_NAME 50
#define MAX_STR_COMM 100

typedef struct _RIDE_ Ride;

Ride * createRide(int id, short dte[3], int drv, char * usr, char * cty, short dst, short scu, short scd, float tip, char * cmt);
void destroyRide(Ride * ride);
void printRide(Ride * ride);
int ride_Int(Ride * ride, char mode);
void ride_Date(short * dest, Ride * ride);
void ride_Str(char * dest, Ride * ride, char mode);
short ride_Short(Ride * ride, char mode);
double ride_Tip(Ride * ride);

#endif