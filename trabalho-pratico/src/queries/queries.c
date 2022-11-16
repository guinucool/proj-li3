#include <stdio.h>
#include <math.h>

#include "../inc/queries/queries.h"

void query_one(int id) {
    // TODO: create query one.
}

int query_five(Date* dateA , Date* dateB, Global* glob){
    HashmapNode * listRides = betweenDates(dateA, dateB, glob->dates, 'c');
    return preço_medio(listRides,glob->drivers,glob->rides);
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

HashmapNode* betweenDates(Date* dateA, Date* dateB, Hashmap* dates, char type){
    short* inf_lim = dateA->date;
    short* upp_lim = dateB->date;
    HashmapNode* list = get(dates,inf_lim,equal_date,hashKey_date,0);
    Date* date = list->data;
    
    while(date->type != type){
        date = list->data;
        list = list->next;
        if(list == NULL){
            nextDay(inf_lim);
            list = get(dates,inf_lim,equal_date,hashKey_date,0);
        }
    }
    HashmapNode* result = createNode(list->key,list->data,NULL);
    HashmapNode* beggin = result;
    HashmapNode* tracker = list;

    while(inf_lim <= upp_lim){
        while (list != NULL)
        {
            date = list->data; 
            if(date->type == type)result->next = createNode(list->key,list->data,NULL);
            list = list->next; 
        }
        nextDay(inf_lim);
        HashmapNode* list = get(dates,inf_lim,equal_date,hashKey_date,0);
    }
    return beggin;
}