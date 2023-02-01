#include <stdio.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/global.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/linkedlist.h"
#include "../../includes/structs/city.h"
#include "../../includes/structs/driver.h"


void linkedListRes(void * driver, LinkedList res)
{
    if(driver_accountStatus(driver) == '1') addOrdList(driver,res,drivercmp);
}

char ** query7(int N,char* city, Global * glob){

    Hashmap cities = glob_city(glob);
    City cityS = get(cities,city,equal_str,hashKey_Str);
    LinkedList res;
    int size;

    size = listMap(city_drivers(cityS),linkedListRes,res);
    
    char ** resultados = malloc(sizeof(char*) * N);

    char * string, name;

    int strSize,nameSize,avMedSize;

    double avMed;

    for (int i = 0; i < N; i++)
    {
        Driver driver = city_drivers(cityS);

        driver_name(name, driver);
        nameSize = strlen(name);

        avMed = driver_score(driver, city);
        avMedSize = intLen(avMed) + 3;

        strSize = 12 + nameSize + avMedSize;

        sprintf(string,"%012d;%s;%.3f",
                driver_id(driver),
                name,
                avMed
                );

        resultados[i] = string;

        list_next(res);
    }

    return resultados;
}