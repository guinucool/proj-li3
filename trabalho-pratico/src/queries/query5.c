#include <stdio.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/user.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/ride.h"
#include "../../includes/structs/datemap.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/queries.h"

/// @brief Esta função adiciona ao resultado o custo de cada viagem.
/// @param ride Viagem a ser processada.
/// @param res Total a que o custo será adicionado.
void rideCostFilterNoTip(void * ride, double * res)
{
    *res += rideCost(ride,0);
}

/// @brief A função query5 calcula o preço médio das viagens realizadas entre duas datas.
/**
 *  A função começa por estabelecer um ciclo que passará por todos os anos entre as duas datas.
 *  A cada iteração é chamada a função date filter que ira somar ao cust total o custo total
 *  das viagens nesse ano, contabilizando o número de viagens totais. No final, é dado como
 *  output do preço médio das viagens.
 * 
 * @param dateA Data em que começa o intervalo de tempo.
 * 
 * @param dateB Data em que termina o intervalo de tempo.
 * 
 * @param glob  Estrutura de dados global a ser atualizada.
 * 
 * @param fp Ficheiro de output.
 */ 
void query5(Date dateA, Date dateB, Global glob, FILE * fp)
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

    if (count > 0)
    {
        if (fp) fprintf(fp, "%.3f\n", preco_medio);
        else printf("%.3f\n", preco_medio);
    }
}