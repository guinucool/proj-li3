#ifndef _DATE_H_
#define _DATE_H_

#define REF_DATE { 9, 10, 2022 }

// Estrutura

/// \struct Estrutura que define as variáveis do tipo Data.
typedef short Date[3];

// Tratamentos
void createDate(short day, short month, short year, Date res);
void nextDay(Date date);
void debugPrintDate(Date date);
int parseDate(char * str, Date date);
int datecmp(Date dateA, Date dateB);
short calculateAge(Date date);
int dateVal(char * str);

#endif