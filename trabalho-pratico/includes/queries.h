#ifndef _QUERIES_H_
#define _QUERIES_H_

#include "../includes/structs/ride.h"

typedef struct _GLOBAL_ Global;

int isUser(char*);
int isDriver(char*);
double calculate_ride_cost(Ride*, Global*);

void query1(char*id, Global * glob);
void query2(int N, Global * glob);
void query3(int N, Global * glob);
double query4(char* city, Global * glob);
double query5(short* dateA , short* dateB, Global * glob);
double query6(char * cty, short * dateInf, short * dateUp, Global * glob);
void query7(int N,char* city, Global * glob);
void query8(char gender,int X, Global * glob);
void query9(short* dateA,short* dateB, Global * glob);

#endif