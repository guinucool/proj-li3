#ifndef _QUERIES_H_
#define _QUERIES_H_

#include "../inc/structs/driverId.h"
#include "../inc/structs/ride.h"
#include "../inc/drivers/driver.h"
#include "../inc/utils.h"
#include "../inc/structs/hashmap.h"
#include "../../inc/structs/date.h"
#include "../../inc/structs/global.h"

int query_five(Date* dateA , Date* dateB, Global* glob);
int preço_medio(HashmapNode * listRides, Hashmap * drivers, Hashmap* riders);
HashmapNode* betweenDates(Date* dateA, Date* dateB, Hashmap* dates, char type);

#endif