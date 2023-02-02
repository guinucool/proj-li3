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

void rideDistFilter(void * ride, int * totalDist)
{
    *totalDist += ride_distance(ride);
}

/// @brief [OUTDATED]A função query6 calcula a média da distância percorrida
///        numa cidade dentro de um dado intervalo de tempo.
/**
 * A função query6 calcula a média da distância percorrida
 * numa cidade dentro de um dado intervalo de tempo. 
 * 
 * Para isso, irá encontrar a lista (filtro) referente à cidade
 * desejada, e irá percorrer as ocorrências desta uma a uma.
 * 
 * A cada ocorrência, irá verificar se a viagem referente à mesma
 * tem uma data compatível com o intervalo desejado, e usar o valor
 * da sua distância para o cálculo da média caso seja compatível.
 * 
 * @param cty A cidade a ser filtrada.
 * 
 * @param dateInf O limite inferior do intervalo.
 * 
 * @param dateUp O limite superior do intervalo.
 * 
 * @param glob A global a ser considerada para os cálculos estatísticos.
 * 
 * @return A média da distância total percorrida desejada.
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