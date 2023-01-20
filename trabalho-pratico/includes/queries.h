#ifndef _QUERIES_H_
#define _QUERIES_H_

#include "../includes/structs/ride.h"

typedef struct _GLOBAL_ Global;

int isUser(char*);
int isDriver(char*);

void query1(char*id, Global * glob);
void query2(int N, Global * glob);
void query3(int N, Global * glob);
double query4(char* city, Global * glob);
double query5(short* dateA , short* dateB, Global * glob);
double query6(char * cty, short * dateInf, short * dateUp, Global * glob);
char ** query7(int N,char* city, Global * glob);
char ** query8(char gender,int X, Global * glob);
void query9(short* dateA,short* dateB, Global * glob);

#endif