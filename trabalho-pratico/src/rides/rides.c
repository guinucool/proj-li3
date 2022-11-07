#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../inc/utils/utilities.h"
#include "../../inc/rides/ride.h"
#include "../../inc/utils/hashmap.h"

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

int main()
{
    Hashmap * rides = createHashmap();
    char info[10][200] = { "000000000001", "29/11/2017", "000000009366", "MRibeiro33", "Setúbal", "5", "5", "1", "3.0", ""};
    char info1[10][200] = { "000000000002", "29/11/2017", "000000009367", "MRibeiro34", "Braga", "4", "5", "3", "2.0", "sd"};
    char info2[10][200] = { "000000000003", "29/11/2017", "000000009368", "MRibeiro35", "Porto", "3", "4", "4", "0.0", "sdasfdscs"};
    char info3[10][200] = { "000000000004", "29/11/2017", "000000009370", "MRibeiro36", "Lisboa", "2", "1", "2", "2.2", "LDAD"};
    char info4[10][200] = { "000000000005", "29/11/2017", "000000009371", "MRibeiro37", "Faro", "10", "3", "1", "1.5", "Ola ola ola ola"};

    handleRide(rides, info);
    handleRide(rides, info1);
    handleRide(rides, info2);
    handleRide(rides, info3);
    handleRide(rides, info4);

    Ride * ride = getRide(rides, 1);

    printf("%d\n", ride->driver);

    Ride * ride1 = getRide(rides, 3);

    printf("|%d\n", ride1->driver);
}