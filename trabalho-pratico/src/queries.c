#include <stdio.h>
#include <math.h>

#include "../../inc/queries.h" 

void query1(char *id, Global *glob)
{
    /*// TODO: criar query one.

    printf("QUERY one:");

    // TODO: Testar id (string - utilizador ou integer - driver)

    int number = atoi(id);


    if (number != 0) {

        Driver *driver = getDriver(store->drivers, number);

        if (driver == NULL) {
            printf("No Driver to print.\n");
        } else {
            printDriver(driver);
        }
    } else {
        /*
        (User *) get(glob->users, (void *) key, equalStr, hashKey_Str, 1);


        if (user == NULL) {
            printf("No Driver to print. \n");
        } else {
            printUser(user);
        }
        // TODO: como extrair um utilizador (void *get)

        // TODO: Como extrair um utilizador?

        // User *user = getU
    }*/
}

void query2(int N, Global* glob){

}

void query3(int N, Global* glob){
    
}

void query4(char* city, Global* glob){
    
}

int query5(short* dateA , short* dateB, Global* glob){
    HashmapNode * listRides = betweenDates(dateA, dateB, glob->dates, 'c');
    return preço_medio(listRides,glob->drivers,glob->rides);
}

double query6(char * cty, short * dateInf, short * dateUp, Global * glob)
{
    HashmapNode * cityList = (HashmapNode *) get(glob->cities, cty, equal_str, hashKey_Str, 0);

    double med = 0.f;
    double sum = 0.f;
    int i = 0;

    while (cityList != NULL)
    {
        City * city = (City *) cityList->data;
        Ride * ride = (Ride *) get(glob->rides, (void *)&city->key, equal, hashKey_Int, 1);
        if (datecmp(dateInf, ride->date) <= 0 && datecmp(ride->date, dateUp) <= 0)
        {
            i++;
            sum += (double)ride->distance;
        }
        cityList = cityList->next;
    }
    
    if (i != 0)
        med = sum/i;

    return(med);
}

void query7(int N,char* city, Global * glob){

}

void query8(char* gender,int X, Global * glob){
    
}

void query9(short* dateA,short* dateB, Global * glob){
    
}

int preço_medio(HashmapNode * listRides, Hashmap * drivers, Hashmap* riders){
    HashmapNode * tracker = listRides;
    Ride* ride;
    Driver* driver;
    int preçoRide, preçoSum = 0,n = 0;
    while(tracker->next != NULL){
        ride = tracker->data;
        driver = get(drivers,ride->driver,equal,hashKey_Int,1);

        switch (driver->car_class)
        {
        case 0:
            preçoRide = 3,25 + 0,62 * ride->distance;
            break;
        
        case 1:
            preçoRide = 4 + 0,79 * ride->distance;
            break;

        case 2:
            preçoRide = 5,2 + 0,94 * ride->distance;
            break;

        default:
            break;
        }

        preçoSum += preçoRide;
        n++;
        tracker = tracker->next;
    }
    return preçoSum/n;
}

/*float preçoPorDriver(HashmapNode* driverIdList, Hashmap * drivers, Hashmap* riders){
    float preçoSum = 0;

    while(driverIdList->next != NULL){
        float preço;
        DriverId* driverId = driverIdList->data;
        Ride* ride = get(riders,driverId->key,equal,hashKey_Int,1);
        Driver * driver = get(drivers,driverId->id,equal,hashKey_Int,1);
        switch (driver->car_class)
        {
        case 0:
            preço = 3,25 + 0,62 * ride->distance;
            break;
        
        case 1:
            preço = 4 + 0,79 * ride->distance;
            break;

        case 2:
            preço = 5,2 + 0,94 * ride->distance;
            break;

        default:
            break;
        }

        preçoSum += preço;
    }

    return preçoSum;
}*/

HashmapNode * betweenDates(short * inf, short * up, char type, Global * glob)
{
    HashmapNode * result = NULL;

    while(datecmp(inf, up) <= 0)
    {
        HashmapNode * list = get(glob->dates, inf, equal_date, hashKey_date, 0);
        while (list != NULL)
        {
            Date * date = (Date*) list->data;
            if (date->type == type) result = createNode(list->key, list->data, result);
            list = list->next; 
        }
        nextDay(inf);
    }

    return result;
}