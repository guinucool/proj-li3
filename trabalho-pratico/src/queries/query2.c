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

void printerDrivers(void * driver, void * null, int * ignore, FILE * fp)
{
    if (*ignore <= 0)
    {
        char name[NAME_STR_SIZE];
        driver_name(name, driver);

        fprintf(fp,"%012d;%s;%.3f\n", driver_id(driver), name, driver_score(driver, NULL));
    }
    else *ignore -= 1;
}

int comparaDrivers(void * elem1, void * elem2)
{
    return drivercmp(elem1, elem2, NULL);
}

void query2(int N, Global glob, void * fp)
{
    sortList(glob_driverList(glob), comparaDrivers);
    listOut(glob_driverList(glob), printerDrivers, 0, N, NULL, fp);
}