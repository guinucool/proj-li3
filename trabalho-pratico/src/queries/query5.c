#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/user.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/ride.h"
#include "../../includes/structs/datemap.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/queries.h"


void rideCostFilterNoTip(void * ride, double * res)
{
    *res += rideCost(ride,0);
}

/// @brief [DOCUMENTAÇÃO OUTDATED]A função query5 calcula o preço médio das viagens realizadas entre duas datas.
/**
 * A função chama a função betweenDates() para asquirir a lista ligada de HashmapNode 
 * de Date do intervalo de tempo entre as duas datas pretendidas e depois usa a função
 * preco_medio() para calcular o preço médio entre essas duas datas.
 * 
 * @param dateA Data em que começa o intervalo de tempo.
 * @param dateB Data em que termina o intervalo de tempo.
 * @param glob  Estrutura de dados global a ser atualizada.
 * 
 * @return Retorna o preço médio das viagens realizadas entre essas duas datas.
 */ 
char * query5(Date dateA, Date dateB, Global glob)
{ 
    double cost = 0, preco_medio = 0;
    int count = 0, key = 0;

    while (datecmp(dateA, dateB) <= 0)
    {
        key = dateA[2];

        DateMap anoA = get(glob_ride(glob), &key, equal, hashKey_Int);
        if (anoA) count += dateFilter(anoA, dateA, dateB, rideCostFilterNoTip, &cost);
        
        if (!anoA) dateA[2]++;
    }

    if (count != 0) preco_medio = (double)cost/count;

    return doublePrinter(preco_medio);
}