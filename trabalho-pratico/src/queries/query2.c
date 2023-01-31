#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/linkedlist.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/queries.h"

int comparaDrivers(void * elem1, void * elem2)
{
    return drivercmp(elem1, elem2, NULL);
}

void createDriverList(void * element, void * list)
{
    if (driver_accountStatus(element)) list = addOrdList(element, list, comparaDrivers);
}

char ** query2(int N, Global glob)
{
    LinkedList ordDriver = glob_driverList(glob);

    if (!ordDriver) map(glob_driver(glob), nullMap, createDriverList, ordDriver);

    char ** res = malloc(sizeof(char*) * N);

    for (int i = 0; i < N && ordDriver; i++)
    {
        Driver driver = list_element(ordDriver);

        char name[NAME_STR_SIZE];
        driver_name(name, driver);

        res[i] = malloc(sizeof(char) * (20 + strlen(name)));
        sprintf(res[i],"%012d;%s;%.3f", driver_id(driver), name, driver_score(driver, NULL));
    }
    
    return res;
}