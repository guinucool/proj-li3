#include <stdlib.h>
#include <math.h>
#include "../inc/queries.h"
#include "../inc/structs/driver.h"
#include "../inc/structs/ride.h"
#include "../inc/structs/city.h"
#include "../inc/structs/date.h"
#include "../inc/utils.h"

double preco_medio(HashmapNode * list, Global * glob, char mode)
{
    HashmapNode * tracker = list;
    int n = 0;
    double precoRide = 0, precoSum = 0;
    while(tracker->next != NULL)
    {
        void * key;
        if (mode == 'd')
        {
            Date * date = (Date*) tracker->data;
            key = date->keyRef;
        }
        else
        {
            City * city = (City*) tracker->data;
            key = (void*) &city->key;
        }
        Ride * ride = (Ride*) get(glob->rides, key, equal, hashKey_Int, 1);
        Driver * driver = (Driver*) get(glob->drivers, (void*)&ride->driver, equal, hashKey_Int, 1);

        switch (driver->car_class)
        {
            case 0:
                precoRide = 3.25 + 0.62 * ride->distance;
                break;
        
            case 1:
                precoRide = 4 + 0.79 * ride->distance;
                break;

            case 2:
                precoRide = 5.2 + 0.94 * ride->distance;
                break;
        }

        precoSum += precoRide;
        n++;
        tracker = tracker->next;
    }
    
    return (precoSum/n);
}

/// @brief A função betweenDates fornece uma lista ligada de HashmapNode de 
///        Dates de um certo tipo dentro de um intervalo de tempo.
/** 
 *  A função betweenDates fornece uma lista ligada de HashmapNode de Dates de um certo tipo
 *  dentro de um intervalo de tempo, percorrendo todas as Dates do hashmap de Dates
 *  dentro desse intervalo de tempo.
 * 
 *  Quando a função encontrar alguma Date do tipo pretendido adiciona-a à lista ligada
 *  de HashmapNode de resultado.
 * 
 *  @param inf  Data em que começa o intervalo de tempo.
 *  @param up   Data em que termina o intervalo de tempo.
 *  @param type Tipo de data pretendido.
 *  @param glob Estrutura de dados global a ser atualizada.
 *  
 *  @return Retorna a lista ligada de HashmapNode de Dates no intervalo de tempo pretendido.
 */
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

/// @brief A funcao query4 calcula o preco medio das viagens realizadas numa determinada cidade.
/**
 *  
 *  @param city 
 *
 *  @param glob  Estrutura de dados global a ser atualizada.
 * 
 *  @return Retorna o preco medio das viagens realizadasnuma determinada cidade.
 */ 
void query4(char* city, Global* glob){
    HashmapNode * cityList = (HashmapNode *) get(glob->cities, city, equal_str, hashKey_Str, 0);
    return preco_medio(cityList,glob,'c');

}

/// @brief A função query5 calcula o preço médio das viagens realizadas entre duas datas.
/**
 *  A função chama a função betweenDates() para asquirir a lista ligada de HashmapNode 
 *  de Date do intervalo de tempo entre as duas datas pretendidas e depois usa a função
 *  preco_medio() para calcular o preço médio entre essas duas datas.
 * 
 *  @param dateA Data em que começa o intervalo de tempo.
 *  @param dateB Data em que termina o intervalo de tempo.
 *  @param glob  Estrutura de dados global a ser atualizada.
 * 
 *  @return Retorna o preço médio das viagens realizadas entre essas duas datas.
 */ 
int query5(short* dateA , short* dateB, Global* glob){
    HashmapNode * listRides = betweenDates(dateA, dateB, 'c', glob);
    return preco_medio(listRides,glob,'d');
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