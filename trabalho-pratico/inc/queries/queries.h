#ifndef _QUERIES_H_
#define _QUERIES_H_

#include "../structs/driverId.h"
#include "../structs/ride.h"
#include "../drivers/driver.h"
#include "../utils.h"
#include "../structs/hashmap.h"
#include "../structs/date.h"
#include "../structs/global.h"

//int query_five(Date* dateA , Date* dateB, Global* glob);
//int preço_medio(HashmapNode * listRides, Hashmap * drivers, Hashmap* riders);
HashmapNode * betweenDates(short * inf, short * up, char type, Global * glob);

#endif