#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../includes/structs/global.h"
#include "../../includes/structs/hashmap.h"
#include "../../includes/io/read.h"
#include "../../includes/structs/user.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/ride.h"
#include "../../includes/structs/city.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/datefilter.h"
#include "../../includes/utils.h"
#include "../../includes/queries.h"


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
 * 
 * @param glob Estrutura de dados global a ser atualizada.
 */ 
void interUser(char args[][MAX_LINE], Global * glob)
{
    User* user = userCreate(args);

    char * key = malloc(sizeof(char) * MAX_USER_STR);
    user_Str(key, user, 'u');

    /*User * data = malloc(sizeof(User));
    *data = *user;*/

    put(global_Hashmap(glob, 'u'), (void *)key, user, hashKey_Str);
}

/// @brief A funcao interDriver interpreta e insere informacao relativa aos drivers
///        na estrutura de dados global.
/**
 * A funcao interDriver interpreta a informacao que recebe (da leitura do ficheiro)
 * e insere a mesma nas respetivas estruturas de dados (Hashmaps).
 * 
 * No final insere toda a informacao tratada na estrutura global nos respetivos
 * contentores.
 * 
 * @param args Informacao recebida da leitura de uma linha do ficheiro.
 * 
 * @param glob Estrutura de dados global a ser atualizada.
 */ 
void interDriver(char args[][MAX_LINE], Global * glob)
{   
    Driver* driver = parseDriver(args);

    int * key = malloc(sizeof(int));
    *key = driver_Id(driver);
    
    put(global_Hashmap(glob, 'e'), key, (void*)driver,hashKey_Int);
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
    Date date;
    createDate(args[1], date);

    int distance = atoi(args[5]);
    int score_user = atoi(args[6]);
    int score_driver = atoi(args[7]);

    Ride * ride = createRide(atoi(args[0]), date, atoi(args[2]), args[3], args[4], (short)distance, (short)score_user, (short)score_driver, atof(args[8]), args[9]);

    int * key = malloc(sizeof(int));
    *key = ride_Int(ride, 'i');

    /*Ride * data = malloc(sizeof(Ride));
    *data = *ride;*/
    
    City * city = createCity(args[4], *key, 'r');
    DateFilter * filter = createDateFilter(date, key, 'r');

    char * dest = malloc(sizeof(char) * MAX_STR_NAME);
    city_City(dest, city);

    short * destDte = malloc(sizeof(short) * 3);
    filter_Date(destDte, filter);

    double money = calculate_ride_cost(ride, glob);

    User * user = get(global_Hashmap(glob, 'u'), args[4], equal_str, hashKey_Str, 1);
    userUpdate(user, score_user, money, distance);

    put(global_Hashmap(glob, 'r'), key, ride, hashKey_Int);
    put(global_Hashmap(glob, 'c'), (void *)dest, (void *)city, hashKey_Str);
    put(global_Hashmap(glob, 'd'), (void *)destDte, (void *)filter, hashKey_date);
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
 * 
 * @param glob Estrutura de dados global a ser atualizada.
 */ 
void interCmd(char args[][MAX_LINE], Global * glob, int cmd)
{
    short dateA[3], dateB[3];
    char * filename = (char*) malloc(sizeof(char) * 100);

    sprintf(filename, "Resultados/command%d_output.txt", cmd);
    FILE * fp = fopen(filename, "w");

    switch (atoi(args[0]))
    {
        case 1:
            query1(args[1],glob);
            break;

        case 2:
            query2(atoi(args[1]),glob);
            break;

        case 3:
            query3(atoi(args[1]),glob);
            break;

        case 4:
            fprintf(fp, "%.3f\n", query4(args[1],glob));
            break;

        case 5:
            stringToDate(args[1],dateA);
            stringToDate(args[2],dateB);

            fprintf(fp, "%.3f\n", query5(dateA,dateB,glob));
            break;

        case 6:
            stringToDate(args[2],dateA);
            stringToDate(args[3],dateB);
            
            fprintf(fp, "%.3f\n", query6(args[1],dateA,dateB,glob));
            break;

        case 7:
            int N = atoi(args[1]);

            char ** res = query7(N,args[2],glob);

            for (int i = 0; i < N; i++)
            {
                fprintf(fp,"%s\n",res[i]);
            }
            
            break;

        case 8:
            query8(args[1],atoi(args[2]),glob);
            break;

        case 9:
            stringToDate(args[1],dateA);
            stringToDate(args[2],dateB);

            query9(dateA,dateB,glob);
            break;
    }

    fclose(fp);
}


