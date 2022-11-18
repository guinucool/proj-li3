#ifndef _READ_H_
#define _READ_H_

#include "../structs/global.h"
#include "../structs/user.h"
#include "../structs/ride.h"
#include "../structs/city.h"
#include "../structs/date.h"
#include "../structs/driver.h"
#include "../utils.h"

#define MAX_LINE 200

void interUser(char args[][MAX_LINE], Global * glob);
void interDriver(char args[][MAX_LINE], Global * glob);
void interRide(char args[][MAX_LINE], Global * glob);
void interCmd(char args[][MAX_LINE], Global * glob);

#endif