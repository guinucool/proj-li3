#include <stdio.h>
#include <stdlib.h>
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

/// @brief Esta função transforma a informação de uma ride em string.
/**
 *  Esta função transforma a informação de uma ride em string obtendo primeiro toda
 *  a informação necassaria, ou seja, id da viagem, a data da viagem, a distancia, 
 *  a cidade e o valor da gorjeta. Após ter toda a informação é contabilizado o 
 *  espaço que a string com a informação ocuparia e é alocada essa memoria. É armazenada
 *  a string com a informação na memoria alocada através da função sprintf.
 *  
 *  @param ride Ride a ser processada.
 *  
 *  @return A string com a informação necessaria à querie 9.
*/
void printRide(void * ride, void * null, int * ignore, FILE * fp)
{
    if (*ignore <= 0)
    {
        char city[MAX_STR_NAME];

        Date date;
        ride_date(date,ride);

        ride_city(city,ride);

        fprintf(fp, "%012d;%02d/%02d/%04d;%d;%s;%.3f\n", ride_id(ride), date[0], date[1], date[2], ride_distance(city), city, ride_tip(ride));
    }
    else *ignore -= 1;
}
 
void createListTip(void * ride, void * list)
{
    if (ride_tip(ride) != 0) addList(ride, list);
}

/// @brief Esta função realiza o trabalho necessário à conclusão da querie 9.
/** 
 *  Esta função realiza o trabalho necessário à conclusão da querie 9 começando por
 *  fazer um ciclo que passará, a cada iteração, por todas as viagens de cada cano entre
 *  a data A e a data B. 
 * 
 *  Este feito é conseguido através da função dateFilter que recebe o DateMap do ano 
 *  a cada iteração do ciclo, as datas limite, a função listRes e o pointer onde a lista
 *  de resultados será armazenada.
 * 
 *  Uma vez adquirida a lista de resultados é retornada a lista de strings com o output
 *  através da função listOut que recebe a lista de resultados, a função printRide e o 
 *  tamanho da lista.
 *  
 *  @param dateA Data limite inferior.
 * 
 *  @param dateB Data limite superior.
 * 
 *  @param glob A global a ser considerada para os cálculos estatísticos.
 * 
 *  @return Lista de strings com os outputs.
 */  
void query9(Date dateA, Date dateB, Global glob, void * fp)
{ 
    List list = createList();
    int size = 0, key = 0;

    while (datecmp(dateA, dateB) <= 0)
    {
        key = dateA[2];

        DateMap anoA = get(glob_ride(glob), &key, equal, hashKey_Int);
        if (anoA) size += dateFilter(anoA, dateA, dateB, createListTip, list);

        if (!anoA) dateA[2]++;
    }

    sortList(list, ridecmp2);
    listOut(list, printRide, 0, size, NULL, fp);
    destroyList(list, null, 0);
}