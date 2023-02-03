#ifndef _QUERIES_H_
#define _QUERIES_H_

void query1(char * id, Global glob, FILE * fp);
void query2(int N, Global glob, FILE * fp);
void query3(int N, Global glob, FILE * fp);
void query4(char * name, Global glob, FILE * fp);
void query5(Date dateA, Date dateB, Global glob, FILE * fp);
void query6(char * city, Date dateA, Date dateB, Global glob, FILE * fp);
void query7(int N, char * city, Global glob, FILE * fp);
void query8(char gender, int X, Global glob, FILE * fp);
void query9(Date dateA, Date dateB, Global glob, FILE * fp);

#endif