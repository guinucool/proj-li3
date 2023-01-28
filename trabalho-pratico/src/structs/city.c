#include <stdlib.h>
#include <string.h>
#include "../../includes/structs/linkedlist.h"
#include "../../includes/structs/city.h"

/// \struct Estrutura que define as variáveis do tipo cidade.
typedef struct _CITY_
{
    char * city;
    int preco_total;
    int rides;
    LinkedList drivers;                  
}*City, NPCity;

/// @brief A função createCity cria uma variável do tipo city.
/**
 * A função createCity cria uma variável do tipo city, alocando
 * o espaço necessário para a mesma na memória.
 * 
 * De seguida, irá associar a cada propriedade deste tipo
 * de variável um valor do input da função.
 * 
 * @param cty O nome da cidade da city.
 * 
 * @param preco_total O dinheiro total gasto por todos os users na cidade em questão.
 * 
 * @param rides Número total de viagens realizadas na cidade em questão.
 * 
 * @param drivers Lista de todos os drivers que fizeram viagens na cidade em questão.
 * 
 * @return A variável do tipo city criada e alocada.
 */ 
City * createCity(char * cty, int preco_total, int rides, LinkedList drivers)
{
    City city = (City)malloc(sizeof(NPCity));

    strncpy(city->city, cty, MAX_STR_NAME);
    city->preco_total = preco_total;
    city->rides = rides;
    city->drivers = drivers;

    return(city);
}

/// @brief Esta função autaliza a estrutura City.
/**
 *  Esta função autaliza a estrutura City, adicionando o dinheiro
 *  adquirido por uma nova viagem ao preço_total e incrementando 
 *  o número de rides da estrutura. Caso o driver ainda não tenha sido 
 *  adicionado à linkedList é feito isso.
 * 
 *  @param city Estrutura City a ser analisada.
 * 
 *  @param driver Void pointer contendo o driver da ride adicionada.
 * 
 *  @param money_received Dinheiro a ser adicionado ao preço_total.
 */
void updateCity(City city, void * driver, int money_received)
{   
    LinkedList drivers = city->drivers;

    city->preco_total += money_received;
    city->rides++;

    if(check_element(drivers,driver) == 0)
    {
    LinkedList new = createList(driver,drivers);
    drivers = new;
    }
}

/// @brief A função destroyCity destroí uma variável do tipo city.
/**
 * A função destroyCity destroí uma variável do tipo city, libertando
 * o espaço ocupado por esta e pela suas propriedades.
 * 
 * @param city A variável city a ser destruída.
 */
void destroyCity(City city)
{
    if (city != NULL)
        free(city);
}

void city_City(char * dest, City city)
{
    strcpy(dest, city->city);
}

int city_preco_total(City city)
{
    return city->preco_total;
    
}

int city_rides(City city)
{
    return(city->rides);
}

double city_preco_medio(City city)
{
    double preço_medio = (double)city->preco_total/city->rides;
    return preço_medio;
}