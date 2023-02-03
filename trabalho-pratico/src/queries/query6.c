#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/structs/global.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/datemap.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/ride.h"
#include "../../includes/utils.h"

/// @brief Esta função adiciona ao resultado a distancia de cada viagem.
/// @param ride Viagem a ser processada.
/// @param res Total a que a distancia será adicionada.
void rideDistFilter(void * ride, int * totalDist)
{
    *totalDist += ride_distance(ride);
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
double query6(char * city, Date dateA, Date dateB, Global * glob)
{
    int count = 0, key = 0, dist = 0;

    while (datecmp(dateA, dateB) <= 0)
    {
        key = dateA[2];

        DateMap anoA = get(glob_ride(glob), &key, equal, hashKey_Int);
        if (anoA) count += dateFilter(anoA, dateA, dateB, rideDistFilter, &dist);
        
        if (!anoA) dateA[2]++;
    }

    return dist;
}