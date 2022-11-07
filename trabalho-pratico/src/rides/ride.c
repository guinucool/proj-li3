#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void destroyRide(Ride * ride)
{
    free(ride);
}

int main()
{
    short date[3] = {22, 11, 2022};

    Ride * ride = createRide(1, date, 1, "MiTeixeira3", "Braga", 5, 5, 5, 2.0, "");

    printf("%s\n", ride->user);
}