#ifndef _QUERIES_H_
#define _QUERIES_H_

#include "./structs/ride.h"
#include "./structs/driver.h"
#include "./utils.h"
#include "./structs/hashmap.h"
#include "./structs/city.h"
#include "./structs/date.h"
#include "./structs/global.h"

double preco_medio(HashmapNode * list, Global * glob, char mode);
//HashmapNode * betweenDates(short * inf, short * up, char type, Global * glob);
void query1(char*id, Global * glob);
void query2(int N, Global * glob);
void query3(int N, Global * glob);
void query4(char* city, Global * glob);
int query5(short* dateA , short* dateB, Global * glob);
double query6(char * cty, short * dateInf, short * dateUp, Global * glob);
void query7(int N,char* city, Global * glob);
void query8(char* gender,int X, Global * glob);
void query9(short* dateA,short* dateB, Global * glob);



#endif