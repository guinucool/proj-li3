#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/utils/parser.h"
#include "../inc/rides/rides.h"

int main()
{
    Hashmap * rides = createCatalogue("../db", 2, handleRide);

    Ride * ride = getRide(rides, 1000000);

    printf("%d %d %s\n", ride->id, ride->driver, ride->user);
}