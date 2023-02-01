#include "../../includes/utils.h"
#include "../../includes/structs/global.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/ride.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/datemap.h"


void linkedListRes(void * ride, List res)
{
    addOrdList(ride,res,ridecmp2);
}

char ** query9(Date dateA, Date dateB, Global glob){
    
    Hashmap calendario = glob_ride(glob); 
    Ride ride;
    List res;
    int size;

    while (dateA[2] != dateB[2]+1)
    {
        DateMap anoA = get(calendario,&dateA[2],equal,hashKey_Int);
        
        size += dateFilter(anoA,dateA,dateB,linkedListRes,res);
    }
    
    char ** resultados = malloc(sizeof(char*) * size);

    char * string;
    char * city;

    int strSize;
    int distSize,dist;
    int citySize;
    int tipSize,tip;

    Date date;

    for (int i = 0; i < size; i++)
    {
        ride = list_element(res);

        dist = ride_distance(ride);
        distSize = intLen(dist);

        ride_city(city,ride);
        citySize = strlen(city);
        
        tip = ride_tip(ride);
        tipSize = intLen(tip)+3;

        strSize = 26 + distSize + citySize + tipSize;

        string = malloc(strSize);

        ride_date(date,ride);

        sprintf(string,"%012d;%02d/%02d/%04d;%d;%s;%.3f",
                ride_id(ride),
                date[0],
                date[1],
                date[2],
                dist,
                city,
                tip
                );

        resultados[i] = string;

        list_next(res);
    }

    return resultados;
}