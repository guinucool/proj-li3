#ifndef _RIDE_H_
#define _RIDE_H_

#define MAX_STR_NAME 50
#define MAX_STR_COMM 100

/// \struct Estrutura que define as variáveis do tipo ride.
typedef struct _RIDE_ {
    int id;                                         //!< Id da ride
    short date[3];                                  //!< Data da ride
    int driver;                                     //!< Driver da ride
    char user[MAX_STR_NAME], city[MAX_STR_NAME];    //!< User e cidade da ride
    short distance, score_user, score_driver;       //!< Distância, pontuação do user e do driver
    float tip;                                      //!< Gorjeta da ride
    char comment[MAX_STR_COMM];                     //!< Comentário da ride
} Ride;

Ride * createRide(int id, short dte[3], int drv, char * usr, char * cty, short dst, short scu, short scd, float tip, char * cmt);
void destroyRide(Ride * ride);

#endif