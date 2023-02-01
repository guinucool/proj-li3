#include <stdio.h>
#include <stdlib.h>
#include "../../includes/structs/date.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/datemap.h"

/// \struct Estrutura que define as variáveis do tipo Filtro de Data.
typedef struct _DATE_MAP_ {
    short year;                         //!< O ano do DateMap
    List map[MONTHS][DAYS];       //!< O mapa de datas do DateMap
}*DateMap, NPDateMap;

/// @brief A função createDateMap cria um DateMap.
/**
 * A função createDateMap cria um DateMap, alocando
 * o espaço necessário para o mesmo na memória.
 * 
 * De seguida, irá associar ao mapa o respetivo
 * ano.
 * 
 * @param year O ano pretendido para o DateMap.
 * 
 * @return A variável DateMap criada e alocada.
 */ 
DateMap createDateMap(short year)
{
    DateMap map = (DateMap) malloc(sizeof(NPDateMap));

    map->year = year;

    for (int i = 0; i < MONTHS; i++)
        for (int j = 0; j < DAYS; j++)
            map->map[i][j] = createList();
    
    return map;
}

/// @brief A função updateDateMap irá adicionar um elemento a um DateMap.
/**
 * A função updateDateMap irá associar um novo elemento a uma data
 * de um DateMap.
 * 
 * @param map O mapa onde será adicionado o elemento.
 * @param day O dia em que será adicionado o elemento.
 * @param month O mês em que será adicionado o elemento.
 * @param element O elemento a ser adicionado.
 */
void updateDateMap(DateMap map, short day, short month, void * element)
{
    addList(element, map->map[month-1][day-1]);
}

/// @brief A função destroyDateMap destroí um DateMap.
/**
 * A função destroyDateMap destroí um DateMap e todos os seus elementos,
 * libertando espaço ocupado pelos mesmos na memória.
 * 
 * @param map O DateMap a ser destruído.
 * @param destroy A função que destroí os elementos do DateMap.
 */
void destroyDateMap(DateMap map, void (*destroy)(void*))
{
    if (map)
    {
        for (int i = 0; i < MONTHS; i++)
            for (int j = 0; j < DAYS; j++)
                destroyList(map->map[i][j], destroy, 1);

        free(map);
    }
}

/// @brief A função debugPrintDateMap imprime um DateMap.
/**
 * A função debugPrintDateMap imprime um DateMap e
 * os seus elementos para propósitos de debugging.
 * 
 * @param map O DateMap a ser imprenso.
 * @param elemPrinter A função que imprime os elementos do Mapa.
 */
void debugPrintDateMap(DateMap map, void (*elemPrinter)(void*))
{
    printf("[%p](DateMap) {\n    year: %d\n    dates:\n", map, map->year);
    for (int i = 0; i < MONTHS; i++)
    {
        for (int j = 0; j < DAYS; j++)
        {
            printf("    [%d][%d]:\n    ", i, j);
            debugPrintList(map->map[i][j], elemPrinter);
        }
    }
    printf("}\n");
}

/// @brief A função dateMapGet devolve os elementos presentes numa data.
/**
 * A função dateMapGet devolve a lista ligada de
 * elementos presentes numa data de um DateMap.
 * 
 * @param map O DateMap onde será feita a devolução.
 * @param day O dia a ser filtrado no DateMap.
 * @param month O mês a ser filtrado no DateMap.
 * 
 * @return O apontador da lista ligada de elementos.
 */
void * dateMapGet(DateMap map, short day, short month)
{
    return map->map[month-1][day-1];
}

/// @brief A função dateMap aplica uma mudança a todos os elementos de um DateMap.
/**
 * A função dateMap mapeia um DateMap, aplicando
 * a todos os seus elementos uma função fornecida
 * como input.
 * 
 * @param map O DateMap a ser mapeado.
 * @param function A função a ser aplicada a cada elemento.
 * @param second O segundo parâmetro da função a ser aplicada.
 * 
 * @return O número de operações executadas.
 */
int dateMap(DateMap map, void (*function)(void*, void*), void * second)
{
    int count = 0;

    for (int i = 0; i < MONTHS; i++)
        for (int j = 0; j < DAYS; j++)
            count += listMap(map->map[i][j], function, second);

    return count;
}

/// @brief A função dateFilter aplica uma mudança a certos elementos de um DateMap.
/**
 * A função dateFilter mapeia uma DateMap aplicando
 * uma função a elementos pertencentes a um certo
 * intervalo de datas fornecido no input.
 * 
 * @param map O DateMap a ser mapeado.
 * @param up O limite superior.
 * @param down O limite inferior.
 * @param function A função a ser aplicada.
 * @param second O segundo parâmetro da função a ser aplicada.
 * 
 * @return O número de operações executadas.
 */
int dateFilter(DateMap map, Date dateA, Date dateB, void (*function)(void*, void*), void * second)
{
    int count = 0;

    while(dateA[2] != map->year+1)
    {
        List lista_rides = dateMapGet(map,dateA[0],dateA[1]); 
        count += listMap(lista_rides, function, second);
        nextDay(dateA);
    }

    return count;
}

short datemap_year(DateMap map)
{
    return map->year;
}