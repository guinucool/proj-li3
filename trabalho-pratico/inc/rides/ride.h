#ifndef _RIDE_H_
#define _RIDE_H_

#define MAX_STR_NAME 50
#define MAX_STR_COMM 100

typedef struct _RIDE_ {
    int id;
    short date[3];
    int driver;
    char user[MAX_STR_NAME], city[MAX_STR_NAME];
    short distance, score_user, score_driver;
    float tip;
    char comment[MAX_STR_COMM];
} Ride;

Ride * convertRide(char info[10][200]);
void destroyRide(Ride * ride);

#endif