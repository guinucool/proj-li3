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
 *  Esta função adquire a função necessária ao output de resultados através da estrutura
 *  de driver. De seguida, é impressa essa informação no ficheiro de outputs.
 *  
 *  @param driver driver a ser processado.
 * 
 *  @param city string contendo o nome da cidade.
 * 
 *  @param ignore Número de outputs que vai ter que ignorar.
 * 
 *  @param fp Ficheiro de output.
*/
void printerDriverCity(void * driver, void * city, int * ignore, FILE * fp)
{
    char name[MAX_STR_NAME];
    driver_name(name, driver);

    fprintf(fp,"%012d;%s;%.3f\n", driver_id(driver), name, driver_score(driver, city));
}

/// @brief Esta função descobre os top N condutores de numa determinada cidade
///        ordenados pela avaliação média do condutor.
/** 
 *  A função começa por verificar se a cidade existe. Caso existaa lista de drivers
 *  é ordenada pela função sortList com a função drivercmp que ordena os drivers por
 *  média de condutor. Por fim, os N condutores resultantes são impressos pela listOut 
 *  no ficheiro de output.
 *  
 *  @param N Número de condutores pretendido.
 * 
 *  @param city Cidade a ser processada.
 * 
 *  @param glob A global a ser considerada para os cálculos estatísticos.
 * 
 *  @param fp Ficheiro de output.
 */  
void query7(int N, char * city, Global glob, FILE * fp)
{
    City obj = get(glob_city(glob), city, equal_str, hashKey_Str);

    if (obj) sortList(city_drivers(obj), drivercmp, city);

    if (obj) listOut(city_drivers(obj), printerDriverCity, 0, N, city, fp);
}