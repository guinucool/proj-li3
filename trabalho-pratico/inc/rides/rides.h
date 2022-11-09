#ifndef _RIDES_H_
#define _RIDES_H_

#include "../../inc/rides/ride.h"
#include "../../inc/utils/hashmap.h"

void handleRide(Hashmap * rides, char info[10][200]);
Ride * getRide(Hashmap * rides, int key);
void destroyRides(Hashmap * rides);

#endif