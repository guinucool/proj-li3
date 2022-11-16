#include <stdio.h>
#include <stdlib.h>
#include "../../inc/io/read.h"
#include "../../inc/structs/ride.h"
#include "../../inc/structs/city.h"
#include "../../inc/utils.h"
#include "../../inc/structs/user.h"
#include "../../inc/structs/date.h"

void interUser(char args[][MAX_LINE], Global * glob)
{
    User* user = userCreate(args);

    put(glob->users, (void *)&user->username, (void *)user, hashKey_Int);
}

void interDriver(char args[][MAX_LINE], Global * glob)
{

}

/// @brief A função interRide interpreta e insere informação relativa às rides
///        na estrutura de dados global.
/**
 * A função interRide interpreta a informação que recebe (da leitura do ficheiro)
 * e insere a mesma nas respetivas estruturas de dados (Hashmaps).
 * 
 * Para isso, primeiro converte a informação toda em Ride e depois converte partes da mesma
 * em outros tipos de variáveis úteis para a execução do programa também.
 * 
 * No final insere toda a informação tratada na estrutura global nos respetivos
 * contentores.
 * 
 * @param args Informação recebida da leitura de uma linha do ficheiro.
 * 
 * @param glob Estrutura de dados global a ser atualizada.
 */ 
void interRide(char args[][MAX_LINE], Global * glob)
{
    short date[3];
    stringToDate(args[1], date);

    Ride * ride = createRide(atoi(args[0]), date, atoi(args[2]), args[3], args[4], (short)atoi(args[5]), (short)atoi(args[6]), (short)atoi(args[7]), atof(args[8]), args[9]);
    City * city = createCity(args[4], ride->id, 'r');

    put(glob->rides, (void *)&ride->id, (void *)ride, hashKey_Int);
    put(glob->cities, (void *)city->city, (void *)city, hashKey_Str);
}

void interCmd(char args[][MAX_LINE], Global * glob)
{

}