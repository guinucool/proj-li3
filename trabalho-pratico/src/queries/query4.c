#include <stdio.h>
#include "../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/city.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"
#include "../../includes/queries.h"

/// @brief A funcao query4 calcula o preco medio das viagens realizadas numa determinada cidade.
/**
 *  A função começa por adquirir a estrutura city a ser analisada através da hashmap de cities 
 *  depois a função chama a função city_averageMoney do modulo city que retorna o preço medio 
 *  das viagens realizadas nessa cidade. Por fim, é impresso em fp esse preço médio.
 *  
 *  @param city Cidade a ser processada.
 * 
 *  @param glob Estrutura de dados global a ser atualizada.
 * 
 *  @param fp Ficheiro de output.
 * 
 *  @return Retorna o preco medio das viagens realizadasnuma determinada cidade.
 */ 
void query4(char * name, Global glob, FILE * fp)
{
    // Aquisição do Hashmap de cities
    Hashmap cities = glob_city(glob);

    // Aquisição da struct da city a ser analisada
    City city = get(cities, name, equal_str, hashKey_Str);

    // Inicialização da variável que irá guardar a preço médio
    double preco_medio = 0;

    // Aquisição do preço médio da cidade a partir da struct city
    if (city) preco_medio = city_averageMoney(city);

    fprintf(fp, "%.3f\n", preco_medio);
}