#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/utils/utilities.h"
#include "../../inc/rides/ride.h"

Ride * createRide(int id, short dte[3], int drv, char * usr, char * cty, short dst, short scu, short scd, float tip, char * cmt)
{
    Ride * ride = (Ride*) malloc(sizeof(Ride));
    
    ride->id = id;
    ride->date[0] = dte[0];
    ride->date[1] = dte[1];
    ride->date[2] = dte[2];
    ride->driver = drv;
    strncpy(ride->user, usr, MAX_STR_NAME);
    strncpy(ride->city, cty, MAX_STR_NAME);
    ride->distance = dst;
    ride->score_user = scu;
    ride->score_driver = scd;
    ride->tip = tip;
    strncpy(ride->comment, cmt, MAX_STR_COMM);

    return ride;
}

Ride * convertRide(char info[10][200])
{
    short date[3];
    stringToDate(info[1], date);

    return createRide(atoi(info[0]), date, atoi(info[2]), info[3], info[4], (short)atoi(info[5]), (short)atoi(info[6]), (short)atoi(info[7]), atof(info[8]), info[9]);
}

void destroyRide(Ride * ride)
{
    free(ride);
}

void printRide(Ride* ride) {
    printf("Ride {id: %d, date: %02d/%02d/%04d, driver: %d,user: %s, city: %s, distance: %d,score_user: %d,score_driver: %d,tip: %f, comment: %s",
        ride->id,
        ride->date[0], ride->date[1], ride->date[2],
        ride->driver,
        ride->user,
        ride->city,
        ride->distance,
        ride->score_user,
        ride->score_driver,
        ride->tip,
        ride->comment
    );
}