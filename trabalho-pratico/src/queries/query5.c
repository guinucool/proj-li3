#include "../../includes/utils.h"
#include "../../includes/structs/global.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/ride.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/datemap.h"


void rideCostFilterNoTip(void * ride, double * res)
{
    *res += rideCost(ride,0);
}
/// @brief [DOCUMENTAÇÃO OUTDATED]A função query5 calcula o preço médio das viagens realizadas entre duas datas.
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
double query5(Date dateA , Date dateB, Global glob)
{
    Hashmap calendario = glob_ride(glob); 
    Ride ride;
    double sum = 0,cost;
    int count = 0;

    while (dateA[2] != dateB[2]+1)
    {
        DateMap anoA = get(calendario,&dateA[2],equal,hashKey_Int);

        count += dateFilter(anoA,dateA,dateB,rideCostFilterNoTip,&cost);

        sum += cost;
    }

    return (double)sum/count;
}