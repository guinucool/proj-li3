#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/utils/utilities.h"
#include "../../inc/rides/rides.h"

void pushRide(Hashmap * rides, Ride * ride)
{
    if (rides != NULL)
        put(rides, (void*)&ride->id, (void*)ride);
}

void handleRide(Hashmap * rides, char info[10][200])
{
    Ride * ride = convertRide(info);
    pushRide(rides, ride);
}

Ride * getRide(Hashmap * rides, int key)
{
    return (Ride*) get(rides, (void*)&key, equal);
}

void destroyRides(Hashmap * rides)
{
    destroyHashmap(rides);
}