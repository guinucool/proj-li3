#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../includes/structs/ride.h"
#include "../../includes/structs/date.h"

typedef struct _RIDE_ Ride;
/// \struct Estrutura que define as variáveis do tipo ride.
typedef struct _RIDE_ {
    int id;                                         //!< Id da ride
    Date date;                                      //!< Data da ride
    int driver;                                     //!< Driver da ride
    char user[MAX_STR_NAME], city[MAX_STR_NAME];    //!< User e cidade da ride
    short distance, score_user, score_driver;       //!< Distância, pontuação do user e do driver
    double tip;                                      //!< Gorjeta da ride
    char comment[MAX_STR_COMM];                     //!< Comentário da ride
} Ride;

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
 * @param dte A data da ride.
 * 
 * @param drv O id do driver da ride.
 * 
 * @param usr O username do user da ride.
 * 
 * @param cty A cidade da ride.
 * 
 * @param dst A distância da ride.
 * 
 * @param scu O score dado ao user da ride.
 * 
 * @param scd O score dado ao driver da ride.
 * 
 * @param tip A gorjeta dada na ride.
 * 
 * @param cmt O comentário da ride.
 * 
 * @return A ride criada com as respetivas propriedades.
 */
Ride * createRide(int id, Date dte, int drv, char * usr, char * cty, short dst, short scu, short scd, float tip, char * cmt)
{
    Ride * ride = (Ride*) malloc(sizeof(Ride));
    
    ride->id = id; 
    ride->date[0] = dte[0];
    ride->date[1] = dte[1];
    ride->date[2] = dte[2];
    ride->driver = drv;
    strncpy(ride->user, usr, MAX_STR_NAME);
    strncpy(ride->city, cty, MAX_STR_NAME);
    ride->distance = dst;
    ride->score_user = scu;
    ride->score_driver = scd;
    ride->tip = tip;
    strncpy(ride->comment, cmt, MAX_STR_COMM);

    return ride;
}

/// @brief A função destroyRide destroí uma variável do tipo ride.
/**
 * A função destroyRide destroí uma variável do tipo ride, libertando
 * o espaço ocupado pela variável e pelas suas propriedades.
 * 
 * @param ride A variável do tipo ride que vai ser destruída.
 */
void destroyRide(Ride * ride)
{
    if (ride != NULL)
        free(ride);
}

void printRide(Ride * ride)
{
    printf("[Ride] -> {id: %d, date: %02d/%02d/%04d, driver: %d,user: %s, city: %s, distance: %d,score_user: %d,score_driver: %d,tip: %f, comment: %s}",
        ride->id,
        ride->date[0], ride->date[1], ride->date[2],
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

int ride_Int(Ride * ride, char mode)
{
    if (mode == 'i')
        return(ride->id);
    else
        return(ride->driver);
}

void ride_Date(Date dest, Ride * ride)
{
    dest[0] = ride->date[0];
    dest[1] = ride->date[1];
    dest[2] = ride->date[2];
}

void ride_Str(char * dest, Ride * ride, char mode)
{
    switch (mode)
    {
        case 'u':
            strcpy(dest, ride->user);
            break;

        case 'c':
            strcpy(dest, ride->city);
            break;

        case 'o':
            strcpy(dest, ride->comment);
            break;
    }
}

short ride_Short(Ride * ride, char mode)
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
    return(0);
}

double ride_Tip(Ride * ride)
{
    return(ride->tip);
}

short get_user_score(Ride *ride) {
    return ride->score_user;
}

short get_driver_score(Ride *ride) {
    return ride->score_driver;
}