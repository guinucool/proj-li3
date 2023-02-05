#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../includes/structs/date.h"
#include "../../includes/structs/user.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/ride.h"
#include "../../includes/utils.h"

/// \struct Estrutura que define as variáveis do tipo ride.
typedef struct _RIDE_ {
    int id;                                         //!< Id da ride
    Date date;                                      //!< Date da ride                                       
    Driver driver;                                  //!< Driver da ride
    User user;                                      //!< Iser da ride 
    char city[MAX_STR_NAME];                        //!< Cidade da ride
    short distance;                                 //!< Distância
    short score_user;                               //!< Pontuação do user
    short score_driver;                             //!< Pontuação do driver
    double tip;                                     //!< Gorjeta da ride
    char comment[MAX_STR_COMM];                     //!< Comentário da ride
}*Ride, NPRide;

/// @brief A função createRide cria uma variável do tipo Ride.
/**
 * A função createRide cria uma variável do tipo Ride, alocando
 * o espaço necessário na memória para a mesma.
 * 
 * Assim sendo, irá depois, também, associar os respetivos valores de input
 * da função às repetivas propriedades da variável.
 * 
 * @param id O id da Ride.
 * @param date A data da Ride.
 * @param driver O apontador do driver da Ride.
 * @param user O apontador do user da Ride.
 * @param city A cidade da Ride.
 * @param distance A distância da Ride.
 * @param score_user O score dado ao user da Ride.
 * @param score_driver O score dado ao driver da Ride.
 * @param tip A gorjeta dada na Ride.
 * @param comment O comentário da Ride.
 * 
 * @return A Ride criada com as respetivas propriedades.
 */
Ride createRide(int id, Date date, Driver driver, User user, char * city, short distance, short score_user, short score_driver, double tip, char * comment)
{
    Ride ride = (Ride) malloc(sizeof(NPRide));
    if(ride == NULL) return NULL;
    
    ride->id = id;
    ride->date[0] = date[0];
    ride->date[1] = date[1];
    ride->date[2] = date[2];
    ride->driver = driver;
    ride->user = user;

    strncpy(ride->city, city, MAX_STR_NAME);

    ride->distance = distance;
    ride->score_user = score_user;
    ride->score_driver = score_driver;
    ride->tip = tip;

    strncpy(ride->comment, comment, MAX_STR_COMM);

    return ride;
}

/// @brief A função destroyRide destroí uma variável do tipo Ride.
/**
 * A função destroyRide destroí uma variável do tipo Ride, libertando
 * o espaço ocupado pela variável e pelas suas propriedades.
 * 
 * @param ride A variável do tipo Ride que vai ser destruída.
 */
void destroyRide(Ride ride)
{
    if (ride) 
    {
        free(ride);
        ride = NULL;
    }
}

/// @brief A função debugPrintRide imprime uma Ride.
/**
 * A função debugPrintRide imprime as informações acerca
 * de uma Ride com propósitos de debugging.
 * 
 * @param ride A Ride a ser impresa.
 */
void debugPrintRide(Ride ride)
{
    printf("[%p](Ride) {\n    id: %d\n    date: %d/%d/%d\n    driver: %p\n    user: %p\n    city: %s\n    distance: %d\n    score_user: %d\n    score_driver: %d\n    tip: %.3f\n    comment: %s\n}\n",
        ride,
        ride->id,
        ride->date[0],ride->date[1],ride->date[2],
        ride->driver,
        ride->user,
        ride->city,
        ride->distance,
        ride->score_user,
        ride->score_driver,
        ride->tip,
        ride->comment
    );
}

/// @brief A funçao parseRide converte informação numa Ride.
/**
 * A função parseRide converte, fazendo as devidas verificações,
 * uma array de strings numa variável do tipo Ride.
 * 
 * @param tokens O array de strings a converter.
 * @param driver O apontador para o driver da Ride.
 * @param user O apontador para o user da Ride.
 * 
 * @return A Ride convertida e criada.
 */
Ride parseRide(char tokens[10][200], Driver driver, User user)
{
    if (!driver || !user) return NULL;

    // Parse ID
    int id;
    id = atoi(tokens[0]);
    if(id == 0) return NULL;

    // Parse Date
    Date date;
    if(!parseDate(tokens[1],date)) return NULL;

    // Parse City
    char city[MAX_STR_NAME];
    strncpy(city, tokens[4], MAX_STR_NAME);
    if(strlen(tokens[4]) == 0) return NULL;

    // Parse Distance
    short distance;
    distance = (short)atoi(tokens[5]);
    if(distance < 1 || !isNumber(tokens[5], INT)) return NULL;

    //printf("%d\n", distance);

    // Parse Score_user
    short score_user;
    score_user = (short)atoi(tokens[6]);
    if(score_user < 1 || !isNumber(tokens[6],INT)) return NULL;

    // Parse Score_driver
    short score_driver;
    score_driver = (short)atoi(tokens[7]);
    if(score_driver < 1 || !isNumber(tokens[7],INT)) return NULL;

    // Parse Tip
    double tip;
    tip = atof(tokens[8]);
    if(tip < 0.0f || !isNumber(tokens[8],DOUBLE) || strlen(tokens[8]) == 0) return NULL;

    // Parse Comment
    char comment[MAX_STR_COMM];
    strncpy(comment, tokens[9], MAX_STR_COMM);

    return createRide(id, date, driver, user, city, distance, score_user, score_driver, tip, comment);
}

/// @brief A função ridecmp compara duas Rides.
/**
 * A função ridecmp compara duas Rides, devolvendo
 * o output na lógica das comparações (1 para maior,
 * etc...).
 * 
 * Irá considerar em primeiro lugar a data de
 * criação de contas dos Drivers de cada Ride.
 * 
 * Em segundo lugar, a data de criação de contas
 * dos Users de cada Ride.
 * 
 * E por último, caso ambos os anteriores
 * falhem, irá considerar o id de cada
 * Ride, por ordem crescente.
 * 
 * @param ride1 A ride número 1.
 * @param ride2 A ride número 2.
 * 
 * @return O típico resultado de comparação.
 */
int ridecmp(Ride ride1, Ride ride2)
{
    Date date1;
    driver_accountCreation(date1, ride1->driver);

    Date date2;
    driver_accountCreation(date2, ride2->driver);
    
    int res = datecmp(date2, date1);

    user_accountCreation(date1, ride1->user);
    user_accountCreation(date2, ride2->user);

    if(res == 0) res = datecmp(date2, date1);

    if(res == 0)
    {
        if (ride1->id < ride2->id) res = 1;
        else res = -1;
    }

    return res;
}

/// @brief A função ridecmp2 compara duas Rides.
/**
 * A função ridecmp2 compara duas Rides, devolvendo
 * a conclusão a que chegar.
 * 
 * Esta, porém, segue prioridades diferentes comparada
 * à anterior.
 * 
 * Primeiro irá considerar a distância percorrida de
 * cada viagem.
 * 
 * Em segundo comparará as datas de ambas as viagens.
 * 
 * Por último, se ambos os anteriores não chegarem
 * a nenhum conclusão, usará o id de viagem.
 * 
 * @param ride1 A viagem 1.
 * @param ride2 A viagem 2.
 * 
 * @return A conclusão a que chegou.
 */
int ridecmp2(Ride ride1, Ride ride2)
{
    int res = 0;

    if(ride1->distance > ride2->distance) res = 1;
    if(ride1->distance < ride2->distance) res = -1;

    if(res == 0) res = datecmp(ride1->date,ride2->date);
    
    if (res == 0)
    {
        if (ride1->id < ride2->id) res = -1;
        else res = 1;
    }

    return res;
}

/// @brief A função rideCost calcula o custo de uma Ride.
/**
 * A função rideCost calucla o custo de uma Ride,
 * considerando se deve ter em conta a gorjeta
 * e qual o tipo de veículo do Driver da
 * mesma.
 * 
 * @param ride A Ride da qual se quer calcular o custo.
 * @param tip Se se deve considerar ou não a gorjeta.
 * 
 * @return O custo da Ride.
 */
double rideCost(Ride ride, char tip)
{
    double total = 0;

    switch(driver_carClass(ride->driver))
    {
        case BASIC:
            total = 3.25 + ride->distance * 0.62; 
            break;

        case GREEN:
            total = 4.00 + ride->distance * 0.79; 
            break;

        case PREMIUM:
            total = 5.20 + ride->distance * 0.94; 
            break;
    }

    if (tip) total += ride->tip;

    return total;
}

/// @brief A função ride_id devolve o id de uma viagem.
int ride_id(Ride ride)
{
    return ride->id;
}

/// @brief A função ride_date da transfere uma data para um pointer de Date.
void ride_date(Date dest, Ride ride)
{   
    dest[0] = ride->date[0];
    dest[1] = ride->date[1];
    dest[2] = ride->date[2];
}

/// @brief A função ride_driver devolve o apontador do driver de uma viagem. 
void * ride_driver(Ride ride)
{
    return ride->driver;
}

/// @brief A função ride_user devolve o apontador do user de uma viagem. 
void * ride_user(Ride ride)
{
    return ride->user;
}

/// @brief A função ride_city devolve a cidade de uma viagem. 
void ride_city(char * dest, Ride ride)
{
    strncpy(dest, ride->city, MAX_STR_NAME);
}

/// @brief A função ride_distance devolve a distância de uma viagem.
short ride_distance(Ride ride)
{
    return ride->distance;
}

/// @brief A função ride_scoreUser devolve a pontuação de um User de uma viagem. 
short ride_scoreUser(Ride ride)
{
    return ride->score_user;
}

/// @brief A função ride_scoreDriver devolve a pontuação de um Driver de uma viagem. 
short ride_scoreDriver(Ride ride)
{
    return ride->score_driver;
}

/// @brief A função ride_tip devolve a gorjeta de uma viagem.
double ride_tip(Ride ride)
{
    return ride->tip;
}