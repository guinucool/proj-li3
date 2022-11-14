#include <stdio.h>
#include "../../inc/io/read.h"
#include "../../inc/structs/ride.h"

void interUser(char args[][MAX_LINE], Global * glob)
{

}

void interDriver(char args[][MAX_LINE], Global * glob)
{

}

void interRide(char args[][MAX_LINE], Global * glob)
{
    short date[3];
    stringToDate(args[1], date);

    Ride * ride = createRide(atoi(args[0]), date, atoi(args[2]), args[3], args[4], (short)atoi(args[5]), (short)atoi(args[6]), (short)atoi(args[7]), atof(args[8]), args[9]);

    printf("%d\n");
}

void interCmd(char args[][MAX_LINE], Global * glob)
{

}