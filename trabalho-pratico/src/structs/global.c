#include <stdio.h>
#include <stdlib.h>
#include "../../includes/utils.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/user.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/ride.h"
#include "../../includes/structs/city.h"
#include "../../includes/structs/list.h"
#include "../../includes/structs/datemap.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/structs/global.h"

/// \struct Estrutura global que segura toda a informação necessária à execução do programa.
typedef struct _GLOBAL_ {
    Hashmap users;          //!< Hashmap que armazena os users
    Hashmap drivers;        //!< Hashmap que armazena os drivers
    Hashmap rides;          //!< Hashmap que armazena as rides
    Hashmap cities;         //!< Hashmap que armazena as cidades
    List userList;          //!< Lista que aponta para os users de forma ordenada
    List driverList;        //!< Lista que aponta para os drivers de forma ordenada
    List rideList;          //!< Lista que aponta para os drivers de forma ordenada
}*Global, NPGlobal;

/// @brief A função createGlobal cria uma variável do tipo global.
/**
 * A função createGlobal cria uma variável do tipo global, alocando
 * o espaço necessário para esta ser guardada.
 * 
 * Assim sendo, irá também inicializar e alocar o espaço necessário
 * às suas propriedades.
 * 
 * @return A variável global (Glob) inicializada e alocada.
 */
Global createGlobal()
{
    Global glob = (Global) malloc(sizeof(NPGlobal));

    glob->users = createHashmap();
    glob->drivers = createHashmap();
    glob->rides = createHashmap();
    glob->cities = createHashmap();

    glob->userList = createList();
    glob->driverList = createList();
    glob->rideList = createList();

    return(glob);
}

/// @brief A função destroyMap combina a função de destruir DateMaps com a função de destruir Rides. 
void destroyMap(void * map)
{
    destroyDateMap(map, destroyRide);
}

/// @brief A função destroyGlobal destroí uma variável do tipo global.
/**
 * A função destroyGlobal destroí uma variável do tipo global e a suas propriedades,
 * libertando o espaço que esta e a suas propriedades ocupam.
 * 
 * @param glob A variável global a ser destruída.
 */
void destroyGlobal(Global glob)
{
    if (glob)
    {
        destroyHashmap(glob->users, destroyUser);
        destroyHashmap(glob->drivers, destroyDriver);
        destroyHashmap(glob->rides, destroyMap);
        destroyHashmap(glob->cities, destroyCity);

        destroyList(glob->userList, null, 0);
        destroyList(glob->driverList, null, 0);
        destroyList(glob->rideList, null, 0);

        free(glob);
    }
}

/// @brief A função glob_user devolve o apontador do hashmap dos Users. 
void * glob_user(Global glob)
{
    return glob->users;
}

/// @brief A função glob_driver devolve o apontador do hashmap dos Drivers.
void * glob_driver(Global glob)
{
    return glob->drivers;
}

/// @brief A função glob_ride devolve o apontador do hashmap das Rides.
void * glob_ride(Global glob)
{
    return glob->rides;
}

/// @brief A função glob_city devolve o apontador do hashmap das Cities.
void * glob_city(Global glob)
{
    return glob->cities;
}

/// @brief A função glob_userList devolve o apontador da lista dos Users.
void * glob_userList(Global glob)
{
    return glob->userList;
}

/// @brief A função glob_driverList devolve o apontador da lista dos Drivers.
void * glob_driverList(Global glob)
{
    return glob->driverList;
}

/// @brief A função glob_rideList devolve o apontador da lista das Rides.
void * glob_rideList(Global glob)
{
    return glob->rideList;
}