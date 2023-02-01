#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/queries.h"

char * printerDrivers(void * driver)
{
    char name[NAME_STR_SIZE];
    driver_name(name, driver);

    char * res = malloc(sizeof(char) * (20 + strlen(name)));
    sprintf(res,"%012d;%s;%.3f", driver_id(driver), name, driver_score(driver, NULL));

    return res;
}

int comparaDrivers(void * elem1, void * elem2)
{
    return drivercmp(elem1, elem2, NULL);
}

void createDriverList(void * element, void * list)
{
    if (driver_accountStatus(element)) addOrdList(element, list, comparaDrivers);
}

char ** query2(int N, Global glob)
{
    List ordDriver = glob_driverList(glob);

    if (listEmpty(ordDriver)) map(glob_driver(glob), nullMap, createDriverList, ordDriver);
    
    return listOut(ordDriver, printerDrivers, N);
}