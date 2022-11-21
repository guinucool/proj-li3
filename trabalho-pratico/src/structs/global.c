#include <stdlib.h>
#include "../../includes/structs/global.h"

/// \struct Estrutura global que segura toda a informação necessária à execução do programa.
typedef struct _GLOBAL_
{
    Hashmap * users;    //!< Hashmap que armazena os users
    Hashmap * drivers;  //!< Hashmap que armazena os drivers
    Hashmap * rides;    //!< Hashmap que armazena as rides
    Hashmap * cities;   //!< Hashmap que armazena as cidades
    Hashmap * dates;    //!< Hashmap que armazena as datas
}Global;

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
Global * createGlobal()
{
    Global * glob = (Global *) malloc(sizeof(Global));

    glob->users = createHashmap();
    glob->drivers = createHashmap();
    glob->rides = createHashmap();
    glob->cities = createHashmap();
    glob->dates = createHashmap();

    return(glob);
}

/// @brief A função destroyGlobal destroí uma variável do tipo global.
/**
 * A função destroyGlobal destroí uma variável do tipo global e a suas propriedades,
 * libertando o espaço que esta e a suas propriedades ocupam.
 * 
 * @param glob A variável global a ser destruída.
 */
void destroyGlobal(Global * glob)
{
    if (glob != NULL)
    {
        destroyHashmap(glob->users);
        destroyHashmap(glob->drivers);
        destroyHashmap(glob->rides);
        destroyHashmap(glob->dates);
        free(glob);
    }
}

Hashmap * global_Hashmap(Global * glob, char mode)
{
    switch (mode)
    {
        case 'u':
            return(glob->users);
            break;

        case 'e':
            return(glob->drivers);
            break;
        
        case 'r':
            return(glob->rides);
            break;

        case 'c':
            return(glob->cities);
            break;

        case 'd':
            return(glob->dates);
            break;
    }
    return(NULL);
}