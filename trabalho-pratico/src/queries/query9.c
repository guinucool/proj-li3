#include <stdlib.h>
#include "../../includes/utils.h"
#include "../../includes/structs/global.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/ride.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/datemap.h"


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
char * printRide(void * ride)
{
    char * string;
    char * city;

    int strSize;
    int distSize,dist;
    int citySize;
    int tipSize,tip;

    Date date;

    dist = ride_distance(ride);
    distSize = intLen(dist);

    ride_city(city,ride);
    citySize = strlen(city);
        
    tip = ride_tip(ride);
    tipSize = intLen(tip)+3;

    strSize = 26 + distSize + citySize + tipSize;

    string = malloc(strSize);

    ride_date(date,ride);

    sprintf(string,"%012d;%02d/%02d/%04d;%d;%s;%.3f",
            ride_id(ride),
            date[0],
            date[1],
            date[2],
            dist,
            city,
            tip
            );
}

/// @brief Esta função chama a função a ser usada na dateFilter.
/**
 *  Esta função chama a função a ser usada na dateFilter, ou seja, chama a função
 *  sortList com a lista a ser processada e a função ridecmp2.
 * 
 * @param ride Ride a ser processada.
 * 
 * @param res Lista a ser processada.
 */  
 
void listRes(void * ride, List res)
{
    sortList(res,ridecmp2);
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
char ** query9(Date dateA, Date dateB, Global glob){
    
    Hashmap calendario = glob_ride(glob); 
    Ride ride;
    List res;
    int size;

    while (dateA[2] != dateB[2]+1)
    {
        DateMap anoA = get(calendario,&dateA[2],equal,hashKey_Int);
        
        size += dateFilter(anoA,dateA,dateB,listRes,res);
    }

    return listOut(res,printRide,size,NULL);
}