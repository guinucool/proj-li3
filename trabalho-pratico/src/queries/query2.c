#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/io/page.h"
#include "../../includes/queries.h"

/// @brief Função que recebe a informação do driver e a imprime no ficheiro de output.
/// @param driver Driver a ser impresso.
/// @param null Placeholder para que listOut resulte.
/// @param ignore Número de outputs que vai ter que ignorar.
/// @param fp Ficheiro de output.
void printerDrivers(void * driver, void * null, int * ignore, FILE * fp)
{
    if (*ignore <= 0)
    {
        char name[NAME_STR_SIZE];
        driver_name(name, driver);

        if (fp) fprintf(fp,"%012d;%s;%.3f\n", driver_id(driver), name, driver_score(driver, NULL));
        else printf("%012d;%s;%.3f\n", driver_id(driver), name, driver_score(driver, NULL));
    }
    else *ignore -= 1;
}

/// @brief Esta função lista os N condutores com maior avaliação média.
/**
 *  A função começa por usar a função de ordem superior sortList que irá ordenar 
 *  a lista de condutores pela avaliação media através da função drivercmp.
 * 
 *  Tendo a lista ordenada é chamada a função de ordem superior listOut que irá 
 *  imprimir os N primeiros elementos da lista.
 * 
 *  @param N Número de condutores a ser impressos.
 * 
 *  @param glob Estrutura de dados global a ser atualizada.
 * 
 *  @param fp Ficheiro de output.
*/
void query2(int N, Global glob, FILE * fp)
{
    sortList(glob_driverList(glob), drivercmp, NULL);
    
    if (fp) listOut(glob_driverList(glob), printerDrivers, 0, N, NULL, fp);
    else page(glob_driverList(glob), printerDrivers, N, NULL);
}