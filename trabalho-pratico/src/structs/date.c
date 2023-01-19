#include <stdlib.h>

#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/utils.h"
#include "../../includes/structs/datefilter.h"
#include "../../includes/structs/date.h"

/// @brief A função createDate cria uma variável do tipo Date.
/**
 * A função createDate cria uma variável do tipo Date, convertendo
 * uma string de com o formato correto de data em uma array de short com 
 * 3 elementos.
 * 
 * O primeiro elemento será o dia, o segundo o mês e o terceiro o ano.
 * 
 * @param date A data em formato string.
 * 
 * @return A variável do tipo Date criada.
 */ 
void createDate(char * date, Date res)
{   
    res[0] = (short)(10*(date[0]-48)+(date[1]-48));
    res[1] = (short)(10*(date[3]-48)+(date[4]-48));
    res[2] = (short)(1000*(date[6]-48)+100*(date[7]-48)+10*(date[8]-48)+(date[9]-48));
}

/// @brief A função equal compara duas datas.
/** 
 *  A função datecmp compara duas datas, comparando cada elemento da primeira data  
 *  ao respetivo elemento da segunda data pela ordem ano->mês->dia, verificando qual é maior.
 * 
 * @param dateA Data nº 1.
 * @param dateB Data nº 2.
 * 
 * @return Retorna -1 caso a dateA seja menor que a dateB, retorna 1 caso a dateA seja maior que a dateB e retorna 0 caso as datas sejam iguais.
 */ 
int datecmp(Date dateA, Date dateB)
{
    for (int i = 2; i >= 0; i--)
    {
        if (dateA[i] < dateB[i]) return -1;
        if (dateA[i] > dateB[i]) return 1;
    }

    return 0;
}

/// @brief A função modifica uma data para o dia seguinte.
/** 
 *  A função modifica uma data para o dia seguinte, incrementando 1 valor a data, tendo em conta 
 *  as mudanças de mês e ano.
 * 
 * @param date Data a ser mudada.
 */ 
void nextDay(Date date)
{    
    short day = 31;
    if ((date[1] < 8 && date[1] % 2 == 0) || (date[1] >= 8 && date[1] % 2 == 1)) day = 30;
    if (date[1] == 2)
    {
        if (date[2] % 4 == 0) day = 29;
        else day = 28;
    }
    short month = 12;

    date[0]++;
    
    if (date[0] > day)
    {
        date[0] = 1;
        date[1]++;
    }
    
    if (date[1] > month)
    {
        date[1] = 1;
        date[2]++;
    }
}

int dateDiffYears(Date *dateA, Date *dateB) {

    if (dateA[1] > dateB[1] || (dateA[1] == dateB[1] && dateA[0] > dateB[0])) {
        return dateB[2] - dateA[2];
    } else {
        return dateB[2] - dateA[2] - 1;
    }
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
            DateFilter * filter = (DateFilter*) node_Void(list, 'd');;
            if (filter_Type(filter) == type) result = createNode(node_Void(list, 'k'), node_Void(list, 'd'), result);
            list = node_Node(list); 
        }
        nextDay(inf);
    }

    return result;
}