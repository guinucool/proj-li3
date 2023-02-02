#ifndef _QUERIES_H_
#define _QUERIES_H_

//void query1(char*id, Global glob);
void query2(int N, Global glob, void * fp);
void query3(int N, Global glob, void * fp);
char * query4(char * name, Global glob);
char * query5(Date dateA, Date dateB, Global glob);
/*double query6(char * cty, short * dateInf, short * dateUp, Global glob);
char ** query7(int N,char* city, Global glob);
char ** query8(char gender,int X, Global glob);*/
void query9(Date dateA, Date dateB, Global glob, void * fp);

#endif