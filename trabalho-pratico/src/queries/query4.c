#include "../includes/utils.h"
#include "../../includes/structs/global.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/city.h"
/// @brief [OUTDATED DOCUMENTACION]A funcao query4 calcula o preco medio das viagens realizadas numa determinada cidade.
/**
 *  A função vai usar a lista da cidade para calcular a média, após ter a lista ligada, vai passá-la 
 *  à função preco_medio, que vai percorrer a lista elemento por elemento. Após ter os valores, 
 *  a função vai calcular o preço, fazendo a média de todos os preços calculados. 
 *  
 *  @param city Cidade
 *  @param glob Estrutura de dados global a ser atualizada.
 *  @return Retorna o preco medio das viagens realizadasnuma determinada cidade.
 */ 
double query4(char* city, Global glob)
{
    // Aquisição do Hashmap de cities
    Hashmap cities = glob_city(glob);

    // Aquisição da struct da city a ser analisada
    City city = get(cities, city, equal_str, hashKey_Str);

    // Aquisição do preço médio da cidade a partir da struct city
    double preco_medio = city_averageMoney(city);

    return preco_medio;
}