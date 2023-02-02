#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/user.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/queries.h"

void printUser(void * user, FILE * fp)
{
    char name[MAX_USER_STR];
    user_name(name, user);

    fprintf(fp, "%s;%c;%d;%0.3f;%d;%0.3f\n", name, user_gender(user), user_age(user), user_averageScore(user), user_rides(user), user_moneySpent(user));
}

void printDriver(void * driver, FILE * fp)
{
    char name[NAME_STR_SIZE];
    driver_name(name, driver);

    fprintf(fp, "%s;%c;%d;%0.3f;%d;%0.3f\n", name, driver_gender(driver), driver_age(driver), driver_score(driver, NULL), driver_rides(driver), driver_moneyReceived(driver));
}

void query1(char * id, Global glob, FILE * fp)
{
    if (isNumber(id, INT))
    {
        int key = atoi(id);

        Driver driver = get(glob_driver(glob), &key, equal, hashKey_Int);
        if (driver && driver_accountStatus(driver)) printDriver(driver, fp);
    }
    else
    {
        User user = get(glob_user(glob), id, equal_str, hashKey_Str);
        if (user && user_accountStatus(user)) printUser(user, fp);
    }
}
