#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "hashmap.h"

/// \struct Estrutura global que segura toda a informação necessária à execução do programa.
typedef struct _GLOBAL_
{
    Hashmap * users;    //!< Hashmap que armazena os users
    Hashmap * drivers;  //!< Hashmap que armazena os drivers
    Hashmap * rides;    //!< Hashmap que armazena as rides
    Hashmap * cities;   //!< Hashmap que armazena as cidades
    Hashmap * dates;    //!< Hashmap que armazena as datas
}Global;

Global *  createGlobal();
void destroyGlobal(Global * glob);

#endif