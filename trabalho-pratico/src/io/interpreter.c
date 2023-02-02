#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
#include "../../includes/queries.h"
#include "../../includes/io/interpreter.h"


/// @brief A função interUser interpreta e insere informação relativa aos users
///        na estrutura de dados global.
/**
 * A função interUser interpreta a informação que recebe (da leitura do ficheiro)
 * e insere a mesma nas respetivas estruturas de dados (Hashmaps).
 * 
 * Para isso, primeiro converte a informação toda em User e depois converte partes da mesma
 * em outros tipos de variáveis úteis para a execução do programa também.
 * 
 * No final insere toda a informação tratada na estrutura global nos respetivos
 * contentores.
 * 
 * @param args Informação recebida da leitura de uma linha do ficheiro.
 * @param glob Estrutura de dados global a ser atualizada.
 */ 
void interUser(char args[][MAX_LINE], Global glob)
{
    User user = parseUser(args);

    if (user)
    {
        char * key = malloc(sizeof(char) * MAX_USER_STR);
        user_username(key, user);

        put(glob_user(glob), key, user, hashKey_Str);
        if (user_accountStatus(user)) addList(user, glob_userList(glob));
    }
}

/// @brief A função interDriver interpreta e insere informacao relativa aos drivers
///        na estrutura de dados global.
/**
 * A função interDriver interpreta a informacao que recebe (da leitura do ficheiro)
 * e insere a mesma nas respetivas estruturas de dados (Hashmaps).
 * 
 * No final insere toda a informacao tratada na estrutura global nos respetivos
 * contentores.
 * 
 * @param args Informacao recebida da leitura de uma linha do ficheiro.
 * @param glob Estrutura de dados global a ser atualizada.
 */ 
void interDriver(char args[][MAX_LINE], Global glob)
{   
    Driver driver = parseDriver(args);

    if (driver)
    {
        int * key = malloc(sizeof(int));
        *key = driver_id(driver);
        
        put(glob_driver(glob), key, driver, hashKey_Int);
        if (driver_accountStatus(driver)) addList(driver, glob_driverList(glob));
    }
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
 * @param glob Estrutura de dados global a ser atualizada.
 */ 
void interRide(char args[][MAX_LINE], Global glob)
{
    // Criação da Ride
    int id = atoi(args[2]);

    char username[MAX_USER_STR];
    strncpy(username, args[3], MAX_USER_STR);

    User user = get(glob_user(glob), &username, equal_str, hashKey_Str);
    Driver driver = get(glob_driver(glob), &id, equal, hashKey_Int);
    
    Ride ride = parseRide(args, driver, user);

    if (ride)
    {
        // Inserção da Ride
        Date date;
        parseDate(args[1], date);

        int year = (int)date[2];

        DateMap map = get(glob_ride(glob), &year, equal, hashKey_Int);
        char mapExist = map != NULL;

        if (!mapExist) map = createDateMap(date[2]);

        updateDateMap(map, date[0], date[1], ride);

        if (!mapExist)
        {
            int * key = malloc(sizeof(int));
            *key = (int)date[2];

            put(glob_ride(glob), key, map, hashKey_Int);
        }

        // Criação e inserção da city
        City city = get(glob_city(glob), args[4], equal_str, hashKey_Str);

        if(city) updateCity(city, rideCost(ride, 0));
        else
        {
            char * name = malloc(sizeof(char) * strlen(args[4]));
            strncpy(name, args[4], strlen(args[4]));

            city = createCity(args[4], rideCost(ride, 0));
            put(glob_city(glob), name, city, hashKey_Str);
        }

        // Atualiza user e driver
        userUpdate(user, ride_scoreUser(ride), rideCost(ride, 1), ride_distance(ride), date);
        int add = updateDriver(driver, ride_scoreDriver(ride), rideCost(ride, 1), args[4], date);

        if (add) addList(driver, city_drivers(city));
        if (user_accountStatus(user) && driver_accountStatus(driver) && user_gender(user) == driver_gender(driver)) addList(ride, glob_rideList(glob));
    }
}

/// @brief A função interCmd interpreta a informação relativa aos comandos acessa
///        qual query deve ser executada. 
/**
 * A função interCmd interpreta a informação que recebe (da leitura do ficheiro)
 * e acessa qual query deve ser executada.
 * 
 * Para isso, primeiro converte o primeiro elemento da lista de strings em Int 
 * e identifica a que query o comando diz respeito.
 * 
 * No final a informação do resto da lista de Strings é convertida nos tipos 
 * que as querys exigem e executa a query em questão com a informação do comando.
 * 
 * @param args Informação recebida da leitura de uma linha do ficheiro.
 * @param glob Estrutura de dados global a ser atualizada.
 * @param cmd Número do comando atual.
 */ 
void interCmd(char args[][MAX_LINE], Global glob, int cmd)
{
    Date dateA, dateB;
    char * filename = (char*) malloc(sizeof(char) * 100);

    sprintf(filename, "Resultados/command%d_output.txt", cmd);
    FILE * fp = fopen(filename, "w");

    char * uniRes;

    switch (atoi(args[0]))
    {
        case 1:
            query1(args[1], glob, fp);
            break;

        case 2:
            query2(atoi(args[1]), glob, fp);
            break;

        case 3:
            query3(atoi(args[1]), glob, fp);
            break;

        case 4:
            query4(args[1], glob, fp);
            break;

        case 5:
            parseDate(args[1],dateA);
            parseDate(args[2],dateB);

            query5(dateA, dateB, glob, fp);
            break;

        case 6:
            //stringToDate(args[2],dateA);
            //stringToDate(args[3],dateB);
            
            //fprintf(fp, "%.3f\n", query6(args[1],dateA,dateB,glob));
            break;

        case 7:
            query7(atoi(args[1]), args[2], glob, fp);
            break;

        case 8:
            //query8(args[1],atoi(args[2]),glob);
            break;

        case 9:
            parseDate(args[1],dateA);
            parseDate(args[2],dateB);

            query9(dateA, dateB, glob, fp);
            break;
    }

    fclose(fp);
}


