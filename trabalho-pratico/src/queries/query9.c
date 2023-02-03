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
#include "../../includes/io/page.h"
#include "../../includes/queries.h"

/// @brief Esta função imprime a informação necessária para um ficheiro de output.
/**
 *  A função começa por verificar se o output será ignorado ou não. Caso seja a informação
 *  necessária é recolhida e é, por fim, impressa num ficheiro de output.
 *  
 *  @param ride Ride a ser processada.
 * 
 *  @param null Placeholder para que listOut resulte.
 * 
 *  @param ignore Número de outputs que vai ter que ignorar.
 * 
 *  @param fp Ficheiro de output.
*/
void printRide(void * ride, void * null, int * ignore, FILE * fp)
{
    if (*ignore <= 0)
    {
        char city[MAX_STR_NAME];

        Date date;
        ride_date(date,ride);

        ride_city(city,ride);

        if (fp) fprintf(fp, "%012d;%02d/%02d/%04d;%d;%s;%.3f\n", ride_id(ride), date[0], date[1], date[2], ride_distance(ride), city, ride_tip(ride));
        else printf("%012d;%02d/%02d/%04d;%d;%s;%.3f\n", ride_id(ride), date[0], date[1], date[2], ride_distance(ride), city, ride_tip(ride));
    }
    else *ignore -= 1;
}
 
/// @brief Esta função adiciona um novo node de ride a lista caso o passageiro tenha dado gorjeta.
/// @param ride Viagem a ser processada.
/// @param list Lista a que a ride é adicionada.
void createListTip(void * ride, void * list)
{
    if (ride_tip(ride) != 0) addList(ride, list);
}

/// @brief Esta função lista as viagens nas quais o passageiro deu gorjeta num intervalo de tempo.
/** 
 *  Esta começa por fazer um ciclo que passará, a cada iteração, por todas as 
 *  viagens de cada ano entre a data A e a data B. De seguida, a função cria uma lista 
 *  de rides em que o passageiro deu gorjeta. Depois a função ordena a lista criada
 *  com a função sortList que usa a função de comparação ridecmp2. Por fim, a função 
 *  imprime a informação resultante no file de output através da função listOut que usa 
 *  a função printRide. Por fim a lista criada é liberada com a função destroyList.
 * 
 *  @param dateA Data limite inferior.
 * 
 *  @param dateB Data limite superior.
 * 
 *  @param glob A global a ser considerada para os cálculos estatísticos.
 * 
 *  @param fp Ficheiro de output.
 */  
void query9(Date dateA, Date dateB, Global glob, FILE * fp)
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

    sortList(list, ridecmp2, NULL);

    if (fp) listOut(list, printRide, 0, size, NULL, fp);
    else page(list, printRide, size, NULL);

    destroyList(list, null, 0);
}