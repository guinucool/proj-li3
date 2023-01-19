#ifndef _DATE_H_
#define _DATE_H_

/// \struct Estrutura que define as variáveis do tipo Data.
typedef short Date[3];

void createDate(char * date, Date res);
int datecmp(Date dateA, Date dateB);
void nextDay(Date date);
int dateDiffYears(Date dateA, Date dateB);

#endif