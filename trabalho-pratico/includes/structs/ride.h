#ifndef _RIDE_H_
#define _RIDE_H_

#define MAX_STR_NAME 50
#define MAX_STR_COMM 100

// Estrutura
typedef struct _RIDE_ *Ride;

// Tratamentos
Ride createRide(int id, Driver driver, User user, char * city, short distance, short score_user, short score_driver, double tip, char * comment);
void destroyRide(Ride ride);
void debugPrintRide(Ride ride);
Ride parseRide(char tokens[10][200], Driver driver, User user);
int ridecmp(Ride ride1, Ride ride2);
double rideCost(Ride ride, char tip);

// Devoluções
int ride_id(Ride ride);
void * ride_driver(Ride ride);
void * ride_user(Ride ride);
void ride_city(char * dest, Ride ride);
short ride_distance(Ride ride);
short ride_scoreUser(Ride ride);
short ride_scoreDriver(Ride ride);
double ride_tip(Ride ride);

#endif