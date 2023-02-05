#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/city.h"

/// \struct Estrutura que define as variáveis do tipo cidade.
typedef struct _CITY_ {
    char city[MAX_STR_NAME];        //!< O nome da cidade.
    double money_spent;             //!< O preço total gasto na cidade.
    int rides;                      //!< O número de viagens feitas na cidade.
    List drivers;                   //!< A lista de drivers que fizeram viagens na cidade.      
}*City, NPCity;

/// @brief A função createCity cria uma City.
/**
 * A função createCity cria uma variável do tipo City, alocando
 * o espaço necessário para a mesma na memória.
 * 
 * De seguida, irá associar a cada propriedade deste tipo
 * de variável um valor do input da função.
 * 
 * @param name O nome da cidade.
 * @param money_spent O dinheiro gasto na viagem que originou esta City.
 * 
 * @return A variável do tipo City criada e alocada.
 */ 
City createCity(char * name, double money_spent)
{
    City city = (City) malloc(sizeof(NPCity));
    if(city == NULL)return NULL;

    strncpy(city->city, name, MAX_STR_NAME);

    city->money_spent = money_spent;
    city->rides = 1;
    city->drivers = createList();
    if(city->drivers == NULL)
    {
        free(city);
        return NULL;
    }

    return city;
}

/// @brief A função updateCity atualiza uma City.
/**
 * A função updateCity atualiza uma City, adicionando o dinheiro gasto
 * na viagem de atualização e incrementando o número de viagens.
 * 
 * @param city A City a ser atualizada.
 * @param money_spent O dinheiro gasto na viagem.
 */
void updateCity(City city, double money_spent)
{   
    city->money_spent += money_spent;
    city->rides++;
}

/// @brief A função destroyCity destroí uma City.
/**
 * A função destroyCity destroí uma variável do tipo city, libertando
 * o espaço ocupado por esta e pela suas propriedades.
 * 
 * @param city A variável city a ser destruída.
 */
void destroyCity(City city)
{
    if (city)
    {
        destroyList(city->drivers, null, 0);
        free(city);
    }
}

/// @brief A função debugPrintCity imprime uma City.
/**
 * A função debugPrintCity imprime uma City e a suas
 * propriedades para propósitos de debugging.
 * 
 * @param city A City a ser imprensa.
 * @param elemPrinter A função que imprime os elementos da lista da City.
 */
void debugPrintCity(City city, void (*elemPrinter)(void*))
{
    printf("[%p](City) {\n    city: %s\n    money_spent: %.3f\n    rides: %d\n    drivers:\n    ",
        city,
        city->city,
        city->money_spent,
        city->rides
    );
    debugPrintList(city->drivers, elemPrinter);
    printf("}\n");
}

/// @brief A função city_city devolve o nome da cidade.
void city_city(char * dest, City city)
{
    strcpy(dest, city->city);
}

/// @brief A função city_moneySpent devolve o preço total gasto na cidade.
double city_moneySpent(City city)
{
    return city->money_spent;
}

/// @brief A função city_rides devolve a quantidade de viagens realizadas na cidade.
int city_rides(City city)
{
    return city->rides;
}

/// @brief A função city_averageMoney devolve a média do preço de viagem por cidade. 
double city_averageMoney(City city)
{
    return city->money_spent / city->rides;
}

/// @brief A função city_drivers devolve o apontador da lista de drivers da cidade. 
void * city_drivers(City city)
{
    return city->drivers;
}