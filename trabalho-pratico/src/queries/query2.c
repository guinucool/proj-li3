#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/linkedlist.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"

void createDriverList(void * element, void * list)
{
    list = addOrdList(element, list, drivercmp);
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