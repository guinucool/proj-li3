#include <stdio.h>
#include <stdlib.h>
#include "../../inc/io/read.h"
#include "../../inc/structs/ride.h"

void stringToDate(char* str,short int* date)
{
    date[0] = (short)(10*(str[0]-48)+(str[1]-48));
    date[1] = (short)(10*(str[3]-48)+(str[4]-48));
    date[2] = (short)(1000*(str[6]-48)+100*(str[7]-48)+10*(str[8]-48)+(str[9]-48));
}

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

    put(glob->rides, (void *)&ride->id, (void *)ride, hashKey_Int);
}

void interCmd(char args[][MAX_LINE], Global * glob)
{

}