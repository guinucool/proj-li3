#include <stdio.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/global.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/city.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/driver.h"

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
char * printDriver(void * driver, void * city)
{
    char * name, city = city;

    int strSize,nameSize,avMedSize;

    double avMed;
    
    driver_name(name, driver);
    nameSize = strlen(name);

    avMed = driver_score(driver, city);
    avMedSize = intLen(avMed) + 3;

    strSize = 12 + nameSize + avMedSize;

    char * string = malloc(strSize);

    sprintf(string,"%012d;%s;%.3f",
            driver_id(driver),
            name,
            avMed
            );

    return string;
}

/// @brief Esta função verifica se o status é valido e se for adiciona a uma lista o driver.
/// @param driver Driver a ser analisado
/// @param res Lista onde o driver vai ser adicionado.
void ListRes(void * driver, List res)
{
    if(driver_accountStatus(driver) == '1') addList(driver,res);
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
char ** query7(int N,char* city, Global * glob){

    Hashmap drivers = glob_driver(glob);
    Driver driver = city_drivers(drivers);
    List res;
    int size;

    size = map(drivers,nullMap,ListRes,res);

    sortList(res,drivercmp);

    return listOut(res, printDriver, N, city);

}