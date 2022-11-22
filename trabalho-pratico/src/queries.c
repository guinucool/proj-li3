#include <stdlib.h>
#include <math.h>
#include "../includes/structs/hashmap.h"
#include "../includes/structs/global.h"
#include "../includes/queries.h"
#include "../includes/structs/driver.h"
#include "../includes/structs/ride.h"
#include "../includes/structs/city.h"
#include "../includes/structs/date.h"
#include "../includes/utils.h"

/// @brief A função preco_medio calcula o preco_medio de um certo filtro de viagens.
/**
 * A função preco_medio calcula o preco_medio de um certo filtro de viagens, percorrendo
 * todas as suas ocorrências no Hashmap de rides e no Hashmap de drivers, obtendo
 * assim as tarifas e a distancia percorrida de cada viagem.
 * 
 * Acaba por ir somando os vários preços calculados de cada viagem, e no final 
 * divide esta soma pelo número de viagens existentes no certo filtro.
 * 
 * @param list Lista de viagens no filtro.
 * 
 * @param glob A global que contém a informação recolhida na base de dados.
 * 
 * @param mode O tipo de filtro fornecido (d - datas, c - cidades).
 * 
 * @return O preço médio das viagens neste filtro.
 */
double preco_medio(HashmapNode * list, Global * glob, char mode)
{
    HashmapNode * tracker = list;
    int n = 0;
    double precoRide = 0, precoSum = 0;
    while(tracker != NULL)
    {
        void * key;
        if (mode == 'd')
        {
            Date * date = (Date*) node_Void(tracker, 'd');
            key = date_Key(date);
        }
        else
        {
            City * city = (City*) node_Void(tracker, 'd');
            int id = city_Key(city);
            key = (void*) &id;
        }
        Ride * ride = (Ride*) get(global_Hashmap(glob, 'r'), key, equal, hashKey_Int, 1);
        int did = ride_Int(ride, 'd');
        Driver * driver = (Driver*) get(global_Hashmap(glob, 'e'), (void*)&did, equal, hashKey_Int, 1);

        switch (driver_Char(driver, 'c'))
        {
            case 0:
                precoRide = 3.25 + 0.62 * ride_Short(ride, 'p');
                break;
        
            case 1:
                precoRide = 4 + 0.79 * ride_Short(ride, 'p');
                break;

            case 2:
                precoRide = 5.2 + 0.94 * ride_Short(ride, 'p');
                break;
        }

        precoSum += precoRide;
        n++;
        tracker = node_Node(tracker);
    }
    
    if (n != 0)
        return (precoSum/n);
    else
        return (0);
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
        HashmapNode * list = get(global_Hashmap(glob, 'd'), inf, equal_date, hashKey_date, 0);
        while (list != NULL)
        {
            Date * date = (Date*) node_Void(list, 'd');;
            if (date_Type(date) == type) result = createNode(node_Void(list, 'k'), node_Void(list, 'd'), result);
            list = node_Node(list); 
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
 *  @param city Lista das cidades
 *
 *  @param glob Estrutura de dados global a ser atualizada.
 * 
 *  @return Retorna o preco medio das viagens realizadasnuma determinada cidade.
 */ 
double query4(char* city, Global* glob)
{
    HashmapNode * cityList = (HashmapNode *) get(global_Hashmap(glob, 'c'), city, equal_str, hashKey_Str, 0);
    double result = preco_medio(cityList,glob,'c');
    return result;
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
double query5(short* dateA , short* dateB, Global* glob)
{
    HashmapNode * listRides = betweenDates(dateA, dateB, 'r', glob);
    double result = preco_medio(listRides,glob,'d');
    destroyNode(listRides, 0);
    return result;
}

double query6(char * cty, short * dateInf, short * dateUp, Global * glob)
{
    HashmapNode * cityList = (HashmapNode *) get(global_Hashmap(glob, 'c'), cty, equal_str, hashKey_Str, 0);

    double med = 0.f;
    double sum = 0.f;
    int i = 0;

    while (cityList != NULL)
    {
        City * city = (City *) node_Void(cityList, 'd');
        int key = city_Key(city);
        Ride * ride = (Ride *) get(global_Hashmap(glob, 'r'), (void *)&key, equal, hashKey_Int, 1);
        short date[3];
        ride_Date(date, ride);
        if (datecmp(dateInf, date) <= 0 && datecmp(date, dateUp) <= 0)
        {
            i++;
            sum += (double)ride_Short(ride, 'p');
        }
        cityList = node_Node(cityList);
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
