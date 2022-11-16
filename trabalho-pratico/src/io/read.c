#include <stdlib.h>
#include <string.h>
#include "../../inc/io/read.h"

void interUser(char args[][MAX_LINE], Global * glob)
{
    User* user = userCreate(args);

    char * key = malloc(sizeof(char) * MAX_STR_NAME);
    strncpy(key, user->username, MAX_USER_STR);

    User * data = malloc(sizeof(User));
    *data = *user;

    put(glob->users, (void *)key, data, hashKey_Str);
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

    int * key = malloc(sizeof(int));
    *key = ride->id;

    Ride * data = malloc(sizeof(Ride));
    *data = *ride;
    
    City * city = createCity(args[4], ride->id, 'r');
    Date * dte = createDate(date, key, 'r');

    put(glob->rides, key, data, hashKey_Int);
    put(glob->cities, (void *)city->city, (void *)city, hashKey_Str);
    put(glob->dates, (void *)dte->date, (void *)dte, hashKey_date);
}

void interCmd(char args[][MAX_LINE], Global * glob)
{

}