#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../includes/utils.h"
#include "../../includes/structs/driver.h"
#include "../../includes/structs/user.h"
#include "../../includes/structs/date.h"
#include "../../includes/structs/ride.h"

typedef struct _RIDE_ Ride;
/// \struct Estrutura que define as variáveis do tipo ride.
typedef struct _RIDE_ {
    int id;                                         //!< Id da ride                                   //!< Data da ride
    Driver driver;                                  //!< Driver da ride
    User user;                                      //!< Iser da ride 
    char city[MAX_STR_NAME];                        //!< Cidade da ride
    short distance;                                 //!< Distância
    short score_user;                               //!< Pontuação do user
    short score_driver;                             //!< Pontuação do driver
    double tip;                                      //!< Gorjeta da ride
    char comment[MAX_STR_COMM];                     //!< Comentário da ride
} *Ride,NPRide;

// [DOCUMENTAÇÃO OUTDATED]
/// @brief A função createRide cria uma variável do tipo ride.
/**
 * A função createRide cria uma variável do tipo ride, alocando
 * o espaço necessário na memória para a mesma.
 * 
 * Assim sendo, irá depois, também, associar os respetivos valores de input
 * da função às repetivas propriedades da variável.
 * 
 * @param id O id da ride.
 * 
 * @param date A data da ride.
 * 
 * @param driver O id do driver da ride.
 * 
 * @param user O username do user da ride.
 * 
 * @param city A cidade da ride.
 * 
 * @param distance A distância da ride.
 * 
 * @param score_user O score dado ao user da ride.
 * 
 * @param score_driver O score dado ao driver da ride.
 * 
 * @param tip A gorjeta dada na ride.
 * 
 * @param comment O comentário da ride.
 * 
 * @return A ride criada com as respetivas propriedades.
 */
Ride createRide(int id, Driver driver, User user, char * city, short distance, short score_user, short score_driver, double tip, char * comment)
{
    Ride ride = (Ride) malloc(sizeof(Ride));
    
    ride->id = id; 
    ride->driver = driver;
    ride->user = user;
    ride->distance = distance;
    ride->score_user = score_user;
    ride->score_driver = score_driver;
    ride->tip = tip;
    strncpy(ride->comment, comment, MAX_STR_COMM);

    return ride;
}

Ride parseRide(char tokens[10][200], Driver driver, User user)
{
    // Parse ID
    int id = atoi(tokens[0]);
    if(id < 1) return NULL;

    // Parse City
    char city[MAX_STR_NAME];
    strcpy(city,tokens[4]);

    // Parce distance
    short distance = (short)atoi(tokens[5]);
    if(distance < 1) return NULL;

    //Parce score_user
    short score_user = (short)atoi(tokens[6]);
    if(score_user < 1) return NULL;

    //parce score_driver
    short score_driver = (short)atoi(tokens[7]);
    if(score_driver < 1) return NULL;

    //parce tip
    double tip = atoi(tokens[8]);
    if(tip < 1) return NULL;

    //parse comment 
    char comment[MAX_STR_COMM];
    strcpy(comment,tokens[9]);

    return createRide(id,driver,user,city,distance,score_user,score_driver,tip,comment);
}

int ride_cmp(Ride ride1, Ride ride2)
{
    int res;
    Date date1,date2;
    
    driver_accountCreation(date1,ride1->driver);
    driver_accountCreation(date2,ride2->driver);
    
    res = datecmp(date1,date2);

    if(res == 0)
    {
        user_accountCreation(date1,ride1->user);
        user_accountCreation(date2,ride2->user);

        res = datecmp(date1,date2);
        if(res == 0)
        {
            if(ride1->id > ride2->id) res = 1; 
        }
    }
    return res;
}

double calculate_ride_cost(Ride ride)
{
    double total = 0;

    switch(driver_carClass(ride->driver))
    {
        case BASIC:   // BASIC
            total = 3.25 + ride->distance * 0.62 + ride->tip; 
            break;

        case GREEN:   // GREEN
            total = 4.00 + ride->distance * 0.79 + ride->tip; 
            break;

        case PREMIUM: // PREMIUM
            total = 5.20 + ride->distance * 0.94 + ride->tip; 
            break;

        default:
            total = 0;
            break; 
    }

    return total;
}

/// @brief A função destroyRide destroí uma variável do tipo ride.
/**
 * A função destroyRide destroí uma variável do tipo ride, libertando
 * o espaço ocupado pela variável e pelas suas propriedades.
 * 
 * @param ride A variável do tipo ride que vai ser destruída.
 */
void destroyRide(Ride ride)
{
    if (ride != NULL)
        free(ride);
}

void debugPrintRide(Ride ride)
{
    printf("[Ride]\n    id: %d\n    driver: %p\n    user: %p\n    city: %s\n    distance: %d\n    score_user: %d\n    score_driver: %d\n    tip: %f\n    comment: %s\n    ",
        ride->id,
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

int ride_Id(Ride ride, char mode)
{
    return(ride->id);
}

Driver ride_driver(Ride ride)
{
    return ride->driver;
}

User ride_user(Ride ride)
{
    return ride->user;
}

void ride_Str(char * dest, Ride ride, char mode)
{
    switch (mode)
    {
        case 'c':
            strcpy(dest, ride->city);
            break;

        case 'o':
            strcpy(dest, ride->comment);
            break;
    }
}

short ride_Short(Ride ride, char mode)
{
    switch (mode)
    {
        case 'p':
            return(ride->distance);
            break;

        case 'u':
            return(ride->score_user);
            break;

        case 'd':
            return(ride->score_driver);
            break;
    }
    return 0;
}

short get_user_score(Ride ride) {
    return ride->score_user;
}

short get_driver_score(Ride ride) {
    return ride->score_driver;
}

double ride_Tip(Ride ride)
{
    return ride->tip;
}