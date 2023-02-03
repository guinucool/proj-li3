#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/user.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/ride.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/datemap.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/queries.h"

/// @brief Esta função adiciona ao resultado a distancia de cada viagem.
/// @param ride Viagem a ser processada.
/// @param res Total a que a distancia será adicionada.
void rideDistFilter(void * ride, void * filter[])
{
    int * x = (int*)filter[0];
    int * c = (int*)filter[1];
    char * city = (char*)filter[2];
    char name[MAX_STR_NAME];
    ride_city(name, ride);

    if(strcmp(name, city) == 0)
    {
        *x += ride_distance(ride);
        *c += 1;
    }
}

/// @brief A função query6 calcula a distância média das viagens realizadas entre duas datas.
/**
 *  A função começa por estabelecer um ciclo que passará por todos os anos entre as duas datas.
 *  A cada iteração é chamada a função date filter que ira somar à distancia total a distancia total
 *  das viagens nesse ano, contabilizando o número de viagens totais. No final, é dado como
 *  output da distância média das viagens.
 * 
 *  @param city Cidade a ser processada.
 * 
 *  @param dateA Data em que começa o intervalo de tempo.
 * 
 *  @param dateB Data em que termina o intervalo de tempo.
 * 
 *  @param glob  Estrutura de dados global a ser atualizada.
 */ 
void query6(char * city, Date dateA, Date dateB, Global glob, FILE * fp)
{
    int count = 0, key = 0, dist = 0;
    double dist_media = 0;
    void * filter[3];

    filter[0] = &dist;
    filter[1] = &count;
    filter[2] = city;

    while (datecmp(dateA, dateB) <= 0)
    {
        key = dateA[2];

        DateMap anoA = get(glob_ride(glob), &key, equal, hashKey_Int);
        if (anoA) dateFilter(anoA, dateA, dateB, rideDistFilter, filter);
        
        if (!anoA) dateA[2]++;
    }

    if (count != 0) dist_media = (double) dist / count;

    if (count > 0)
    {
        if (fp) fprintf(fp, "%.3f\n", dist_media);
        else printf("%.3f\n", dist_media);
    }
}