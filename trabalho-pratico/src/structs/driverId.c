#include <stdlib.h>

#include "../../inc/structs/driverId.h"

DriverId * createDriverId(int driverid, int key)
{
    DriverId * driverId = (DriverId *)malloc(sizeof(DriverId));

    driverId->key = key;
    driverId->id = driverid;

    return(driverId);
}

void destroyDriverId(DriverId * driverId)
{
    if (driverId != NULL)
        free(driverId);
}