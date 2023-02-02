#include <stdio.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/city.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/queries.h"

/// @brief Esta função transforma a informação de um driver em string.
/**
 *  Esta função transforma a informação de um driver em string obtendo primeiro toda
 *  a informação necassaria, ou seja, id do driver, nome do driver e avaliação média
 *  do driver. Após ter toda a informação é contabilizado o espaço que a string com 
 *  a informação ocuparia e é alocada essa memoria. É armazenada a string com a 
 *  informação na memoria alocada através da função sprintf.
 *  
 *  @param driver driver a ser processado.
 * 
 *  @param city string contendo o nome da cidade.
 *  
 *  @return A string com a informação necessaria à querie 7.
*/
void printerDriverCity(void * driver, void * city, int * ignore, FILE * fp)
{
    char name[MAX_STR_NAME];
    driver_name(name, driver);

    fprintf(fp,"%012d;%s;%.3f\n", driver_id(driver), name, driver_score(driver, city));
}

/// @brief Esta função realiza o trabalho necessário à conclusão da querie 7.
/** 
 *  Esta função realiza o trabalho necessário à conclusão da querie 7 obtendo a 
 *  estrutura da City a ser analisada e usando a função listMap para percorrer a lista
 *  de drivers dessa cidade de forma a ordena
 *  
 *  @param N Data limite inferior.
 * 
 *  @param city Data limite superior.
 * 
 *  @param glob A global a ser considerada para os cálculos estatísticos.
 * 
 *  @return Lista de strings com os outputs.
 */  
void query7(int N, char * city, Global glob, FILE * fp)
{
    City obj = get(glob_city(glob), city, equal_str, hashKey_Str);

    sortList(city_drivers(obj), drivercmp, city);

    listOut(city_drivers(obj), printerDriverCity, 0, N, city, fp);
}