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

char * isUser(void * user)
{
    char name[MAX_USER_STR];
    user_name(name, user);

    char user_gender; 

    short user_age;  

    char * res = malloc(sizeof(char) * (14 + intLen(user_age(user)) + intLen(user_rides(user)) + strlen(name) + intLen((int)user_moneySpent(user))));
    sprintf(res,"%s;%c;%d;%0.3f;%d;%0.3f", user_name, user_gender, user_age, user_averageScore,user_moneySpent);

    return res;
}

char * isDriver(void * driver)
{
    char name[NAME_STR_SIZE];
    driver_name(name, driver);

    char gender; 

    short age;  

    char * res = malloc(sizeof(char) * (14 + intLen(drive_age(driver)) + intLen(driver_rides(driver)) + strlen(name) + intLen((int)driver_moneyReceived(driver))));
    sprintf(res,"%s;%c;%d;%0.3f;%d;%0.3f", driver_name, driver_gender, age, driver_score(driver, NULL), driver_rides, driver_moneyReceived);


    return res;
}



void query1(char *id, Global glob) {

    Hashmap map;
    User user;
    Driver driver;

    int total = 0, count = 0;

    if (isNumber(id, INT)) {

        map = glob_driver(glob);
        int key = atoi(id);
        driver = get(map, &key, equal, hashKey_Int);
        isDriver(driver); 

    } else {
        
        map = glob_user(glob);
        user = get(map, id, equal_str, hashKey_Str);
        isUser(user);
    }
}
