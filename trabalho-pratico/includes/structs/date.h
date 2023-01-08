#ifndef _DATE_H_
#define _DATE_H_

/// \struct Estrutura que define as variáveis do tipo Data.
typedef short Date[3];

void createDate(char * date, Date res);
int dateDiffYears(Date *, Date *);

#endif